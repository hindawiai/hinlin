<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*******************************************************************************
 * This file contains मुख्य functions related to the iSCSI Target Core Driver.
 *
 * (c) Copyright 2007-2013 Datera, Inc.
 *
 * Author: Nicholas A. Bellinger <nab@linux-iscsi.org>
 *
 ******************************************************************************/

#समावेश <crypto/hash.h>
#समावेश <linux/माला.स>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/completion.h>
#समावेश <linux/module.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/idr.h>
#समावेश <linux/delay.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/inet.h>
#समावेश <net/ipv6.h>
#समावेश <scsi/scsi_proto.h>
#समावेश <scsi/iscsi_proto.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <target/target_core_base.h>
#समावेश <target/target_core_fabric.h>

#समावेश <target/iscsi/iscsi_target_core.h>
#समावेश "iscsi_target_parameters.h"
#समावेश "iscsi_target_seq_pdu_list.h"
#समावेश "iscsi_target_datain_values.h"
#समावेश "iscsi_target_erl0.h"
#समावेश "iscsi_target_erl1.h"
#समावेश "iscsi_target_erl2.h"
#समावेश "iscsi_target_login.h"
#समावेश "iscsi_target_tmr.h"
#समावेश "iscsi_target_tpg.h"
#समावेश "iscsi_target_util.h"
#समावेश "iscsi_target.h"
#समावेश "iscsi_target_device.h"
#समावेश <target/iscsi/iscsi_target_स्थिति.स>

#समावेश <target/iscsi/iscsi_transport.h>

अटल LIST_HEAD(g_tiqn_list);
अटल LIST_HEAD(g_np_list);
अटल DEFINE_SPINLOCK(tiqn_lock);
अटल DEFINE_MUTEX(np_lock);

अटल काष्ठा idr tiqn_idr;
DEFINE_IDA(sess_ida);
काष्ठा mutex auth_id_lock;

काष्ठा iscsit_global *iscsit_global;

काष्ठा kmem_cache *lio_qr_cache;
काष्ठा kmem_cache *lio_dr_cache;
काष्ठा kmem_cache *lio_ooo_cache;
काष्ठा kmem_cache *lio_r2t_cache;

अटल पूर्णांक iscsit_handle_immediate_data(काष्ठा iscsi_cmd *,
			काष्ठा iscsi_scsi_req *, u32);

काष्ठा iscsi_tiqn *iscsit_get_tiqn_क्रम_login(अचिन्हित अक्षर *buf)
अणु
	काष्ठा iscsi_tiqn *tiqn = शून्य;

	spin_lock(&tiqn_lock);
	list_क्रम_each_entry(tiqn, &g_tiqn_list, tiqn_list) अणु
		अगर (!म_भेद(tiqn->tiqn, buf)) अणु

			spin_lock(&tiqn->tiqn_state_lock);
			अगर (tiqn->tiqn_state == TIQN_STATE_ACTIVE) अणु
				tiqn->tiqn_access_count++;
				spin_unlock(&tiqn->tiqn_state_lock);
				spin_unlock(&tiqn_lock);
				वापस tiqn;
			पूर्ण
			spin_unlock(&tiqn->tiqn_state_lock);
		पूर्ण
	पूर्ण
	spin_unlock(&tiqn_lock);

	वापस शून्य;
पूर्ण

अटल पूर्णांक iscsit_set_tiqn_shutकरोwn(काष्ठा iscsi_tiqn *tiqn)
अणु
	spin_lock(&tiqn->tiqn_state_lock);
	अगर (tiqn->tiqn_state == TIQN_STATE_ACTIVE) अणु
		tiqn->tiqn_state = TIQN_STATE_SHUTDOWN;
		spin_unlock(&tiqn->tiqn_state_lock);
		वापस 0;
	पूर्ण
	spin_unlock(&tiqn->tiqn_state_lock);

	वापस -1;
पूर्ण

व्योम iscsit_put_tiqn_क्रम_login(काष्ठा iscsi_tiqn *tiqn)
अणु
	spin_lock(&tiqn->tiqn_state_lock);
	tiqn->tiqn_access_count--;
	spin_unlock(&tiqn->tiqn_state_lock);
पूर्ण

/*
 * Note that IQN क्रमmatting is expected to be करोne in userspace, and
 * no explict IQN क्रमmat checks are करोne here.
 */
काष्ठा iscsi_tiqn *iscsit_add_tiqn(अचिन्हित अक्षर *buf)
अणु
	काष्ठा iscsi_tiqn *tiqn = शून्य;
	पूर्णांक ret;

	अगर (म_माप(buf) >= ISCSI_IQN_LEN) अणु
		pr_err("Target IQN exceeds %d bytes\n",
				ISCSI_IQN_LEN);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	tiqn = kzalloc(माप(*tiqn), GFP_KERNEL);
	अगर (!tiqn)
		वापस ERR_PTR(-ENOMEM);

	प्र_लिखो(tiqn->tiqn, "%s", buf);
	INIT_LIST_HEAD(&tiqn->tiqn_list);
	INIT_LIST_HEAD(&tiqn->tiqn_tpg_list);
	spin_lock_init(&tiqn->tiqn_state_lock);
	spin_lock_init(&tiqn->tiqn_tpg_lock);
	spin_lock_init(&tiqn->sess_err_stats.lock);
	spin_lock_init(&tiqn->login_stats.lock);
	spin_lock_init(&tiqn->logout_stats.lock);

	tiqn->tiqn_state = TIQN_STATE_ACTIVE;

	idr_preload(GFP_KERNEL);
	spin_lock(&tiqn_lock);

	ret = idr_alloc(&tiqn_idr, शून्य, 0, 0, GFP_NOWAIT);
	अगर (ret < 0) अणु
		pr_err("idr_alloc() failed for tiqn->tiqn_index\n");
		spin_unlock(&tiqn_lock);
		idr_preload_end();
		kमुक्त(tiqn);
		वापस ERR_PTR(ret);
	पूर्ण
	tiqn->tiqn_index = ret;
	list_add_tail(&tiqn->tiqn_list, &g_tiqn_list);

	spin_unlock(&tiqn_lock);
	idr_preload_end();

	pr_debug("CORE[0] - Added iSCSI Target IQN: %s\n", tiqn->tiqn);

	वापस tiqn;

पूर्ण

अटल व्योम iscsit_रुको_क्रम_tiqn(काष्ठा iscsi_tiqn *tiqn)
अणु
	/*
	 * Wait क्रम accesses to said काष्ठा iscsi_tiqn to end.
	 */
	spin_lock(&tiqn->tiqn_state_lock);
	जबतक (tiqn->tiqn_access_count != 0) अणु
		spin_unlock(&tiqn->tiqn_state_lock);
		msleep(10);
		spin_lock(&tiqn->tiqn_state_lock);
	पूर्ण
	spin_unlock(&tiqn->tiqn_state_lock);
पूर्ण

व्योम iscsit_del_tiqn(काष्ठा iscsi_tiqn *tiqn)
अणु
	/*
	 * iscsit_set_tiqn_shutकरोwn sets tiqn->tiqn_state = TIQN_STATE_SHUTDOWN
	 * जबतक holding tiqn->tiqn_state_lock.  This means that all subsequent
	 * attempts to access this काष्ठा iscsi_tiqn will fail from both transport
	 * fabric and control code paths.
	 */
	अगर (iscsit_set_tiqn_shutकरोwn(tiqn) < 0) अणु
		pr_err("iscsit_set_tiqn_shutdown() failed\n");
		वापस;
	पूर्ण

	iscsit_रुको_क्रम_tiqn(tiqn);

	spin_lock(&tiqn_lock);
	list_del(&tiqn->tiqn_list);
	idr_हटाओ(&tiqn_idr, tiqn->tiqn_index);
	spin_unlock(&tiqn_lock);

	pr_debug("CORE[0] - Deleted iSCSI Target IQN: %s\n",
			tiqn->tiqn);
	kमुक्त(tiqn);
पूर्ण

पूर्णांक iscsit_access_np(काष्ठा iscsi_np *np, काष्ठा iscsi_portal_group *tpg)
अणु
	पूर्णांक ret;
	/*
	 * Determine अगर the network portal is accepting storage traffic.
	 */
	spin_lock_bh(&np->np_thपढ़ो_lock);
	अगर (np->np_thपढ़ो_state != ISCSI_NP_THREAD_ACTIVE) अणु
		spin_unlock_bh(&np->np_thपढ़ो_lock);
		वापस -1;
	पूर्ण
	spin_unlock_bh(&np->np_thपढ़ो_lock);
	/*
	 * Determine अगर the portal group is accepting storage traffic.
	 */
	spin_lock_bh(&tpg->tpg_state_lock);
	अगर (tpg->tpg_state != TPG_STATE_ACTIVE) अणु
		spin_unlock_bh(&tpg->tpg_state_lock);
		वापस -1;
	पूर्ण
	spin_unlock_bh(&tpg->tpg_state_lock);

	/*
	 * Here we serialize access across the TIQN+TPG Tuple.
	 */
	ret = करोwn_पूर्णांकerruptible(&tpg->np_login_sem);
	अगर (ret != 0)
		वापस -1;

	spin_lock_bh(&tpg->tpg_state_lock);
	अगर (tpg->tpg_state != TPG_STATE_ACTIVE) अणु
		spin_unlock_bh(&tpg->tpg_state_lock);
		up(&tpg->np_login_sem);
		वापस -1;
	पूर्ण
	spin_unlock_bh(&tpg->tpg_state_lock);

	वापस 0;
पूर्ण

व्योम iscsit_login_kref_put(काष्ठा kref *kref)
अणु
	काष्ठा iscsi_tpg_np *tpg_np = container_of(kref,
				काष्ठा iscsi_tpg_np, tpg_np_kref);

	complete(&tpg_np->tpg_np_comp);
पूर्ण

पूर्णांक iscsit_deaccess_np(काष्ठा iscsi_np *np, काष्ठा iscsi_portal_group *tpg,
		       काष्ठा iscsi_tpg_np *tpg_np)
अणु
	काष्ठा iscsi_tiqn *tiqn = tpg->tpg_tiqn;

	up(&tpg->np_login_sem);

	अगर (tpg_np)
		kref_put(&tpg_np->tpg_np_kref, iscsit_login_kref_put);

	अगर (tiqn)
		iscsit_put_tiqn_क्रम_login(tiqn);

	वापस 0;
पूर्ण

bool iscsit_check_np_match(
	काष्ठा sockaddr_storage *sockaddr,
	काष्ठा iscsi_np *np,
	पूर्णांक network_transport)
अणु
	काष्ठा sockaddr_in *sock_in, *sock_in_e;
	काष्ठा sockaddr_in6 *sock_in6, *sock_in6_e;
	bool ip_match = false;
	u16 port, port_e;

	अगर (sockaddr->ss_family == AF_INET6) अणु
		sock_in6 = (काष्ठा sockaddr_in6 *)sockaddr;
		sock_in6_e = (काष्ठा sockaddr_in6 *)&np->np_sockaddr;

		अगर (!स_भेद(&sock_in6->sin6_addr.in6_u,
			    &sock_in6_e->sin6_addr.in6_u,
			    माप(काष्ठा in6_addr)))
			ip_match = true;

		port = ntohs(sock_in6->sin6_port);
		port_e = ntohs(sock_in6_e->sin6_port);
	पूर्ण अन्यथा अणु
		sock_in = (काष्ठा sockaddr_in *)sockaddr;
		sock_in_e = (काष्ठा sockaddr_in *)&np->np_sockaddr;

		अगर (sock_in->sin_addr.s_addr == sock_in_e->sin_addr.s_addr)
			ip_match = true;

		port = ntohs(sock_in->sin_port);
		port_e = ntohs(sock_in_e->sin_port);
	पूर्ण

	अगर (ip_match && (port_e == port) &&
	    (np->np_network_transport == network_transport))
		वापस true;

	वापस false;
पूर्ण

अटल काष्ठा iscsi_np *iscsit_get_np(
	काष्ठा sockaddr_storage *sockaddr,
	पूर्णांक network_transport)
अणु
	काष्ठा iscsi_np *np;
	bool match;

	lockdep_निश्चित_held(&np_lock);

	list_क्रम_each_entry(np, &g_np_list, np_list) अणु
		spin_lock_bh(&np->np_thपढ़ो_lock);
		अगर (np->np_thपढ़ो_state != ISCSI_NP_THREAD_ACTIVE) अणु
			spin_unlock_bh(&np->np_thपढ़ो_lock);
			जारी;
		पूर्ण

		match = iscsit_check_np_match(sockaddr, np, network_transport);
		अगर (match) अणु
			/*
			 * Increment the np_exports reference count now to
			 * prevent iscsit_del_np() below from being called
			 * जबतक iscsi_tpg_add_network_portal() is called.
			 */
			np->np_exports++;
			spin_unlock_bh(&np->np_thपढ़ो_lock);
			वापस np;
		पूर्ण
		spin_unlock_bh(&np->np_thपढ़ो_lock);
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा iscsi_np *iscsit_add_np(
	काष्ठा sockaddr_storage *sockaddr,
	पूर्णांक network_transport)
अणु
	काष्ठा iscsi_np *np;
	पूर्णांक ret;

	mutex_lock(&np_lock);

	/*
	 * Locate the existing काष्ठा iscsi_np अगर alपढ़ोy active..
	 */
	np = iscsit_get_np(sockaddr, network_transport);
	अगर (np) अणु
		mutex_unlock(&np_lock);
		वापस np;
	पूर्ण

	np = kzalloc(माप(*np), GFP_KERNEL);
	अगर (!np) अणु
		mutex_unlock(&np_lock);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	np->np_flags |= NPF_IP_NETWORK;
	np->np_network_transport = network_transport;
	spin_lock_init(&np->np_thपढ़ो_lock);
	init_completion(&np->np_restart_comp);
	INIT_LIST_HEAD(&np->np_list);

	समयr_setup(&np->np_login_समयr, iscsi_handle_login_thपढ़ो_समयout, 0);

	ret = iscsi_target_setup_login_socket(np, sockaddr);
	अगर (ret != 0) अणु
		kमुक्त(np);
		mutex_unlock(&np_lock);
		वापस ERR_PTR(ret);
	पूर्ण

	np->np_thपढ़ो = kthपढ़ो_run(iscsi_target_login_thपढ़ो, np, "iscsi_np");
	अगर (IS_ERR(np->np_thपढ़ो)) अणु
		pr_err("Unable to create kthread: iscsi_np\n");
		ret = PTR_ERR(np->np_thपढ़ो);
		kमुक्त(np);
		mutex_unlock(&np_lock);
		वापस ERR_PTR(ret);
	पूर्ण
	/*
	 * Increment the np_exports reference count now to prevent
	 * iscsit_del_np() below from being run जबतक a new call to
	 * iscsi_tpg_add_network_portal() क्रम a matching iscsi_np is
	 * active.  We करोn't need to hold np->np_thपढ़ो_lock at this
	 * poपूर्णांक because iscsi_np has not been added to g_np_list yet.
	 */
	np->np_exports = 1;
	np->np_thपढ़ो_state = ISCSI_NP_THREAD_ACTIVE;

	list_add_tail(&np->np_list, &g_np_list);
	mutex_unlock(&np_lock);

	pr_debug("CORE[0] - Added Network Portal: %pISpc on %s\n",
		&np->np_sockaddr, np->np_transport->name);

	वापस np;
पूर्ण

पूर्णांक iscsit_reset_np_thपढ़ो(
	काष्ठा iscsi_np *np,
	काष्ठा iscsi_tpg_np *tpg_np,
	काष्ठा iscsi_portal_group *tpg,
	bool shutकरोwn)
अणु
	spin_lock_bh(&np->np_thपढ़ो_lock);
	अगर (np->np_thपढ़ो_state == ISCSI_NP_THREAD_INACTIVE) अणु
		spin_unlock_bh(&np->np_thपढ़ो_lock);
		वापस 0;
	पूर्ण
	np->np_thपढ़ो_state = ISCSI_NP_THREAD_RESET;
	atomic_inc(&np->np_reset_count);

	अगर (np->np_thपढ़ो) अणु
		spin_unlock_bh(&np->np_thपढ़ो_lock);
		send_sig(संक_विघ्न, np->np_thपढ़ो, 1);
		रुको_क्रम_completion(&np->np_restart_comp);
		spin_lock_bh(&np->np_thपढ़ो_lock);
	पूर्ण
	spin_unlock_bh(&np->np_thपढ़ो_lock);

	अगर (tpg_np && shutकरोwn) अणु
		kref_put(&tpg_np->tpg_np_kref, iscsit_login_kref_put);

		रुको_क्रम_completion(&tpg_np->tpg_np_comp);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम iscsit_मुक्त_np(काष्ठा iscsi_np *np)
अणु
	अगर (np->np_socket)
		sock_release(np->np_socket);
पूर्ण

पूर्णांक iscsit_del_np(काष्ठा iscsi_np *np)
अणु
	spin_lock_bh(&np->np_thपढ़ो_lock);
	np->np_exports--;
	अगर (np->np_exports) अणु
		np->enabled = true;
		spin_unlock_bh(&np->np_thपढ़ो_lock);
		वापस 0;
	पूर्ण
	np->np_thपढ़ो_state = ISCSI_NP_THREAD_SHUTDOWN;
	spin_unlock_bh(&np->np_thपढ़ो_lock);

	अगर (np->np_thपढ़ो) अणु
		/*
		 * We need to send the संकेत to wakeup Linux/Net
		 * which may be sleeping in sock_accept()..
		 */
		send_sig(संक_विघ्न, np->np_thपढ़ो, 1);
		kthपढ़ो_stop(np->np_thपढ़ो);
		np->np_thपढ़ो = शून्य;
	पूर्ण

	np->np_transport->iscsit_मुक्त_np(np);

	mutex_lock(&np_lock);
	list_del(&np->np_list);
	mutex_unlock(&np_lock);

	pr_debug("CORE[0] - Removed Network Portal: %pISpc on %s\n",
		&np->np_sockaddr, np->np_transport->name);

	iscsit_put_transport(np->np_transport);
	kमुक्त(np);
	वापस 0;
पूर्ण

अटल व्योम iscsit_get_rx_pdu(काष्ठा iscsi_conn *);

पूर्णांक iscsit_queue_rsp(काष्ठा iscsi_conn *conn, काष्ठा iscsi_cmd *cmd)
अणु
	वापस iscsit_add_cmd_to_response_queue(cmd, cmd->conn, cmd->i_state);
पूर्ण
EXPORT_SYMBOL(iscsit_queue_rsp);

व्योम iscsit_पातed_task(काष्ठा iscsi_conn *conn, काष्ठा iscsi_cmd *cmd)
अणु
	spin_lock_bh(&conn->cmd_lock);
	अगर (!list_empty(&cmd->i_conn_node))
		list_del_init(&cmd->i_conn_node);
	spin_unlock_bh(&conn->cmd_lock);

	__iscsit_मुक्त_cmd(cmd, true);
पूर्ण
EXPORT_SYMBOL(iscsit_पातed_task);

अटल व्योम iscsit_करो_crypto_hash_buf(काष्ठा ahash_request *, स्थिर व्योम *,
				      u32, u32, स्थिर व्योम *, व्योम *);
अटल व्योम iscsit_tx_thपढ़ो_रुको_क्रम_tcp(काष्ठा iscsi_conn *);

अटल पूर्णांक
iscsit_xmit_nondatain_pdu(काष्ठा iscsi_conn *conn, काष्ठा iscsi_cmd *cmd,
			  स्थिर व्योम *data_buf, u32 data_buf_len)
अणु
	काष्ठा iscsi_hdr *hdr = (काष्ठा iscsi_hdr *)cmd->pdu;
	काष्ठा kvec *iov;
	u32 niov = 0, tx_size = ISCSI_HDR_LEN;
	पूर्णांक ret;

	iov = &cmd->iov_misc[0];
	iov[niov].iov_base	= cmd->pdu;
	iov[niov++].iov_len	= ISCSI_HDR_LEN;

	अगर (conn->conn_ops->HeaderDigest) अणु
		u32 *header_digest = (u32 *)&cmd->pdu[ISCSI_HDR_LEN];

		iscsit_करो_crypto_hash_buf(conn->conn_tx_hash, hdr,
					  ISCSI_HDR_LEN, 0, शून्य,
					  header_digest);

		iov[0].iov_len += ISCSI_CRC_LEN;
		tx_size += ISCSI_CRC_LEN;
		pr_debug("Attaching CRC32C HeaderDigest"
			 " to opcode 0x%x 0x%08x\n",
			 hdr->opcode, *header_digest);
	पूर्ण

	अगर (data_buf_len) अणु
		u32 padding = ((-data_buf_len) & 3);

		iov[niov].iov_base	= (व्योम *)data_buf;
		iov[niov++].iov_len	= data_buf_len;
		tx_size += data_buf_len;

		अगर (padding != 0) अणु
			iov[niov].iov_base = &cmd->pad_bytes;
			iov[niov++].iov_len = padding;
			tx_size += padding;
			pr_debug("Attaching %u additional"
				 " padding bytes.\n", padding);
		पूर्ण

		अगर (conn->conn_ops->DataDigest) अणु
			iscsit_करो_crypto_hash_buf(conn->conn_tx_hash,
						  data_buf, data_buf_len,
						  padding, &cmd->pad_bytes,
						  &cmd->data_crc);

			iov[niov].iov_base = &cmd->data_crc;
			iov[niov++].iov_len = ISCSI_CRC_LEN;
			tx_size += ISCSI_CRC_LEN;
			pr_debug("Attached DataDigest for %u"
				 " bytes opcode 0x%x, CRC 0x%08x\n",
				 data_buf_len, hdr->opcode, cmd->data_crc);
		पूर्ण
	पूर्ण

	cmd->iov_misc_count = niov;
	cmd->tx_size = tx_size;

	ret = iscsit_send_tx_data(cmd, conn, 1);
	अगर (ret < 0) अणु
		iscsit_tx_thपढ़ो_रुको_क्रम_tcp(conn);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक iscsit_map_iovec(काष्ठा iscsi_cmd *cmd, काष्ठा kvec *iov, पूर्णांक nvec,
			    u32 data_offset, u32 data_length);
अटल व्योम iscsit_unmap_iovec(काष्ठा iscsi_cmd *);
अटल u32 iscsit_करो_crypto_hash_sg(काष्ठा ahash_request *, काष्ठा iscsi_cmd *,
				    u32, u32, u32, u8 *);
अटल पूर्णांक
iscsit_xmit_datain_pdu(काष्ठा iscsi_conn *conn, काष्ठा iscsi_cmd *cmd,
		       स्थिर काष्ठा iscsi_datain *datain)
अणु
	काष्ठा kvec *iov;
	u32 iov_count = 0, tx_size = 0;
	पूर्णांक ret, iov_ret;

	iov = &cmd->iov_data[0];
	iov[iov_count].iov_base	= cmd->pdu;
	iov[iov_count++].iov_len = ISCSI_HDR_LEN;
	tx_size += ISCSI_HDR_LEN;

	अगर (conn->conn_ops->HeaderDigest) अणु
		u32 *header_digest = (u32 *)&cmd->pdu[ISCSI_HDR_LEN];

		iscsit_करो_crypto_hash_buf(conn->conn_tx_hash, cmd->pdu,
					  ISCSI_HDR_LEN, 0, शून्य,
					  header_digest);

		iov[0].iov_len += ISCSI_CRC_LEN;
		tx_size += ISCSI_CRC_LEN;

		pr_debug("Attaching CRC32 HeaderDigest for DataIN PDU 0x%08x\n",
			 *header_digest);
	पूर्ण

	iov_ret = iscsit_map_iovec(cmd, &cmd->iov_data[iov_count],
				   cmd->orig_iov_data_count - (iov_count + 2),
				   datain->offset, datain->length);
	अगर (iov_ret < 0)
		वापस -1;

	iov_count += iov_ret;
	tx_size += datain->length;

	cmd->padding = ((-datain->length) & 3);
	अगर (cmd->padding) अणु
		iov[iov_count].iov_base		= cmd->pad_bytes;
		iov[iov_count++].iov_len	= cmd->padding;
		tx_size += cmd->padding;

		pr_debug("Attaching %u padding bytes\n", cmd->padding);
	पूर्ण

	अगर (conn->conn_ops->DataDigest) अणु
		cmd->data_crc = iscsit_करो_crypto_hash_sg(conn->conn_tx_hash,
							 cmd, datain->offset,
							 datain->length,
							 cmd->padding,
							 cmd->pad_bytes);

		iov[iov_count].iov_base	= &cmd->data_crc;
		iov[iov_count++].iov_len = ISCSI_CRC_LEN;
		tx_size += ISCSI_CRC_LEN;

		pr_debug("Attached CRC32C DataDigest %d bytes, crc 0x%08x\n",
			 datain->length + cmd->padding, cmd->data_crc);
	पूर्ण

	cmd->iov_data_count = iov_count;
	cmd->tx_size = tx_size;

	ret = iscsit_fe_sendpage_sg(cmd, conn);

	iscsit_unmap_iovec(cmd);

	अगर (ret < 0) अणु
		iscsit_tx_thपढ़ो_रुको_क्रम_tcp(conn);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक iscsit_xmit_pdu(काष्ठा iscsi_conn *conn, काष्ठा iscsi_cmd *cmd,
			   काष्ठा iscsi_datain_req *dr, स्थिर व्योम *buf,
			   u32 buf_len)
अणु
	अगर (dr)
		वापस iscsit_xmit_datain_pdu(conn, cmd, buf);
	अन्यथा
		वापस iscsit_xmit_nondatain_pdu(conn, cmd, buf, buf_len);
पूर्ण

अटल क्रमागत target_prot_op iscsit_get_sup_prot_ops(काष्ठा iscsi_conn *conn)
अणु
	वापस TARGET_PROT_NORMAL;
पूर्ण

अटल काष्ठा iscsit_transport iscsi_target_transport = अणु
	.name			= "iSCSI/TCP",
	.transport_type		= ISCSI_TCP,
	.rdma_shutकरोwn		= false,
	.owner			= शून्य,
	.iscsit_setup_np	= iscsit_setup_np,
	.iscsit_accept_np	= iscsit_accept_np,
	.iscsit_मुक्त_np		= iscsit_मुक्त_np,
	.iscsit_get_login_rx	= iscsit_get_login_rx,
	.iscsit_put_login_tx	= iscsit_put_login_tx,
	.iscsit_get_dataout	= iscsit_build_r2ts_क्रम_cmd,
	.iscsit_immediate_queue	= iscsit_immediate_queue,
	.iscsit_response_queue	= iscsit_response_queue,
	.iscsit_queue_data_in	= iscsit_queue_rsp,
	.iscsit_queue_status	= iscsit_queue_rsp,
	.iscsit_पातed_task	= iscsit_पातed_task,
	.iscsit_xmit_pdu	= iscsit_xmit_pdu,
	.iscsit_get_rx_pdu	= iscsit_get_rx_pdu,
	.iscsit_get_sup_prot_ops = iscsit_get_sup_prot_ops,
पूर्ण;

अटल पूर्णांक __init iscsi_target_init_module(व्योम)
अणु
	पूर्णांक ret = 0, size;

	pr_debug("iSCSI-Target "ISCSIT_VERSION"\n");
	iscsit_global = kzalloc(माप(*iscsit_global), GFP_KERNEL);
	अगर (!iscsit_global)
		वापस -1;

	spin_lock_init(&iscsit_global->ts_biपंचांगap_lock);
	mutex_init(&auth_id_lock);
	idr_init(&tiqn_idr);

	ret = target_रेजिस्टर_ढाँचा(&iscsi_ops);
	अगर (ret)
		जाओ out;

	size = BITS_TO_LONGS(ISCSIT_BITMAP_BITS) * माप(दीर्घ);
	iscsit_global->ts_biपंचांगap = vzalloc(size);
	अगर (!iscsit_global->ts_biपंचांगap)
		जाओ configfs_out;

	lio_qr_cache = kmem_cache_create("lio_qr_cache",
			माप(काष्ठा iscsi_queue_req),
			__alignof__(काष्ठा iscsi_queue_req), 0, शून्य);
	अगर (!lio_qr_cache) अणु
		pr_err("Unable to kmem_cache_create() for"
				" lio_qr_cache\n");
		जाओ biपंचांगap_out;
	पूर्ण

	lio_dr_cache = kmem_cache_create("lio_dr_cache",
			माप(काष्ठा iscsi_datain_req),
			__alignof__(काष्ठा iscsi_datain_req), 0, शून्य);
	अगर (!lio_dr_cache) अणु
		pr_err("Unable to kmem_cache_create() for"
				" lio_dr_cache\n");
		जाओ qr_out;
	पूर्ण

	lio_ooo_cache = kmem_cache_create("lio_ooo_cache",
			माप(काष्ठा iscsi_ooo_cmdsn),
			__alignof__(काष्ठा iscsi_ooo_cmdsn), 0, शून्य);
	अगर (!lio_ooo_cache) अणु
		pr_err("Unable to kmem_cache_create() for"
				" lio_ooo_cache\n");
		जाओ dr_out;
	पूर्ण

	lio_r2t_cache = kmem_cache_create("lio_r2t_cache",
			माप(काष्ठा iscsi_r2t), __alignof__(काष्ठा iscsi_r2t),
			0, शून्य);
	अगर (!lio_r2t_cache) अणु
		pr_err("Unable to kmem_cache_create() for"
				" lio_r2t_cache\n");
		जाओ ooo_out;
	पूर्ण

	iscsit_रेजिस्टर_transport(&iscsi_target_transport);

	अगर (iscsit_load_discovery_tpg() < 0)
		जाओ r2t_out;

	वापस ret;
r2t_out:
	iscsit_unरेजिस्टर_transport(&iscsi_target_transport);
	kmem_cache_destroy(lio_r2t_cache);
ooo_out:
	kmem_cache_destroy(lio_ooo_cache);
dr_out:
	kmem_cache_destroy(lio_dr_cache);
qr_out:
	kmem_cache_destroy(lio_qr_cache);
biपंचांगap_out:
	vमुक्त(iscsit_global->ts_biपंचांगap);
configfs_out:
	/* XXX: this probably wants it to be it's own unwind step.. */
	अगर (iscsit_global->discovery_tpg)
		iscsit_tpg_disable_portal_group(iscsit_global->discovery_tpg, 1);
	target_unरेजिस्टर_ढाँचा(&iscsi_ops);
out:
	kमुक्त(iscsit_global);
	वापस -ENOMEM;
पूर्ण

अटल व्योम __निकास iscsi_target_cleanup_module(व्योम)
अणु
	iscsit_release_discovery_tpg();
	iscsit_unरेजिस्टर_transport(&iscsi_target_transport);
	kmem_cache_destroy(lio_qr_cache);
	kmem_cache_destroy(lio_dr_cache);
	kmem_cache_destroy(lio_ooo_cache);
	kmem_cache_destroy(lio_r2t_cache);

	/*
	 * Shutकरोwn discovery sessions and disable discovery TPG
	 */
	अगर (iscsit_global->discovery_tpg)
		iscsit_tpg_disable_portal_group(iscsit_global->discovery_tpg, 1);

	target_unरेजिस्टर_ढाँचा(&iscsi_ops);

	vमुक्त(iscsit_global->ts_biपंचांगap);
	kमुक्त(iscsit_global);
पूर्ण

पूर्णांक iscsit_add_reject(
	काष्ठा iscsi_conn *conn,
	u8 reason,
	अचिन्हित अक्षर *buf)
अणु
	काष्ठा iscsi_cmd *cmd;

	cmd = iscsit_allocate_cmd(conn, TASK_INTERRUPTIBLE);
	अगर (!cmd)
		वापस -1;

	cmd->iscsi_opcode = ISCSI_OP_REJECT;
	cmd->reject_reason = reason;

	cmd->buf_ptr = kmemdup(buf, ISCSI_HDR_LEN, GFP_KERNEL);
	अगर (!cmd->buf_ptr) अणु
		pr_err("Unable to allocate memory for cmd->buf_ptr\n");
		iscsit_मुक्त_cmd(cmd, false);
		वापस -1;
	पूर्ण

	spin_lock_bh(&conn->cmd_lock);
	list_add_tail(&cmd->i_conn_node, &conn->conn_cmd_list);
	spin_unlock_bh(&conn->cmd_lock);

	cmd->i_state = ISTATE_SEND_REJECT;
	iscsit_add_cmd_to_response_queue(cmd, conn, cmd->i_state);

	वापस -1;
पूर्ण
EXPORT_SYMBOL(iscsit_add_reject);

अटल पूर्णांक iscsit_add_reject_from_cmd(
	काष्ठा iscsi_cmd *cmd,
	u8 reason,
	bool add_to_conn,
	अचिन्हित अक्षर *buf)
अणु
	काष्ठा iscsi_conn *conn;
	स्थिर bool करो_put = cmd->se_cmd.se_tfo != शून्य;

	अगर (!cmd->conn) अणु
		pr_err("cmd->conn is NULL for ITT: 0x%08x\n",
				cmd->init_task_tag);
		वापस -1;
	पूर्ण
	conn = cmd->conn;

	cmd->iscsi_opcode = ISCSI_OP_REJECT;
	cmd->reject_reason = reason;

	cmd->buf_ptr = kmemdup(buf, ISCSI_HDR_LEN, GFP_KERNEL);
	अगर (!cmd->buf_ptr) अणु
		pr_err("Unable to allocate memory for cmd->buf_ptr\n");
		iscsit_मुक्त_cmd(cmd, false);
		वापस -1;
	पूर्ण

	अगर (add_to_conn) अणु
		spin_lock_bh(&conn->cmd_lock);
		list_add_tail(&cmd->i_conn_node, &conn->conn_cmd_list);
		spin_unlock_bh(&conn->cmd_lock);
	पूर्ण

	cmd->i_state = ISTATE_SEND_REJECT;
	iscsit_add_cmd_to_response_queue(cmd, conn, cmd->i_state);
	/*
	 * Perक्रमm the kref_put now अगर se_cmd has alपढ़ोy been setup by
	 * scsit_setup_scsi_cmd()
	 */
	अगर (करो_put) अणु
		pr_debug("iscsi reject: calling target_put_sess_cmd >>>>>>\n");
		target_put_sess_cmd(&cmd->se_cmd);
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक iscsit_add_reject_cmd(काष्ठा iscsi_cmd *cmd, u8 reason,
				 अचिन्हित अक्षर *buf)
अणु
	वापस iscsit_add_reject_from_cmd(cmd, reason, true, buf);
पूर्ण

पूर्णांक iscsit_reject_cmd(काष्ठा iscsi_cmd *cmd, u8 reason, अचिन्हित अक्षर *buf)
अणु
	वापस iscsit_add_reject_from_cmd(cmd, reason, false, buf);
पूर्ण
EXPORT_SYMBOL(iscsit_reject_cmd);

/*
 * Map some portion of the allocated scatterlist to an iovec, suitable क्रम
 * kernel sockets to copy data in/out.
 */
अटल पूर्णांक iscsit_map_iovec(काष्ठा iscsi_cmd *cmd, काष्ठा kvec *iov, पूर्णांक nvec,
			    u32 data_offset, u32 data_length)
अणु
	u32 i = 0, orig_data_length = data_length;
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक page_off;

	/*
	 * We know each entry in t_data_sg contains a page.
	 */
	u32 ent = data_offset / PAGE_SIZE;

	अगर (!data_length)
		वापस 0;

	अगर (ent >= cmd->se_cmd.t_data_nents) अणु
		pr_err("Initial page entry out-of-bounds\n");
		जाओ overflow;
	पूर्ण

	sg = &cmd->se_cmd.t_data_sg[ent];
	page_off = (data_offset % PAGE_SIZE);

	cmd->first_data_sg = sg;
	cmd->first_data_sg_off = page_off;

	जबतक (data_length) अणु
		u32 cur_len;

		अगर (WARN_ON_ONCE(!sg || i >= nvec))
			जाओ overflow;

		cur_len = min_t(u32, data_length, sg->length - page_off);

		iov[i].iov_base = kmap(sg_page(sg)) + sg->offset + page_off;
		iov[i].iov_len = cur_len;

		data_length -= cur_len;
		page_off = 0;
		sg = sg_next(sg);
		i++;
	पूर्ण

	cmd->kmapped_nents = i;

	वापस i;

overflow:
	pr_err("offset %d + length %d overflow; %d/%d; sg-list:\n",
	       data_offset, orig_data_length, i, nvec);
	क्रम_each_sg(cmd->se_cmd.t_data_sg, sg,
		    cmd->se_cmd.t_data_nents, i) अणु
		pr_err("[%d] off %d len %d\n",
		       i, sg->offset, sg->length);
	पूर्ण
	वापस -1;
पूर्ण

अटल व्योम iscsit_unmap_iovec(काष्ठा iscsi_cmd *cmd)
अणु
	u32 i;
	काष्ठा scatterlist *sg;

	sg = cmd->first_data_sg;

	क्रम (i = 0; i < cmd->kmapped_nents; i++)
		kunmap(sg_page(&sg[i]));
पूर्ण

अटल व्योम iscsit_ack_from_expstatsn(काष्ठा iscsi_conn *conn, u32 exp_statsn)
अणु
	LIST_HEAD(ack_list);
	काष्ठा iscsi_cmd *cmd, *cmd_p;

	conn->exp_statsn = exp_statsn;

	अगर (conn->sess->sess_ops->RDMAExtensions)
		वापस;

	spin_lock_bh(&conn->cmd_lock);
	list_क्रम_each_entry_safe(cmd, cmd_p, &conn->conn_cmd_list, i_conn_node) अणु
		spin_lock(&cmd->istate_lock);
		अगर ((cmd->i_state == ISTATE_SENT_STATUS) &&
		    iscsi_sna_lt(cmd->stat_sn, exp_statsn)) अणु
			cmd->i_state = ISTATE_REMOVE;
			spin_unlock(&cmd->istate_lock);
			list_move_tail(&cmd->i_conn_node, &ack_list);
			जारी;
		पूर्ण
		spin_unlock(&cmd->istate_lock);
	पूर्ण
	spin_unlock_bh(&conn->cmd_lock);

	list_क्रम_each_entry_safe(cmd, cmd_p, &ack_list, i_conn_node) अणु
		list_del_init(&cmd->i_conn_node);
		iscsit_मुक्त_cmd(cmd, false);
	पूर्ण
पूर्ण

अटल पूर्णांक iscsit_allocate_iovecs(काष्ठा iscsi_cmd *cmd)
अणु
	u32 iov_count = max(1UL, DIV_ROUND_UP(cmd->se_cmd.data_length, PAGE_SIZE));

	iov_count += ISCSI_IOV_DATA_BUFFER;
	cmd->iov_data = kसुस्मृति(iov_count, माप(*cmd->iov_data), GFP_KERNEL);
	अगर (!cmd->iov_data)
		वापस -ENOMEM;

	cmd->orig_iov_data_count = iov_count;
	वापस 0;
पूर्ण

पूर्णांक iscsit_setup_scsi_cmd(काष्ठा iscsi_conn *conn, काष्ठा iscsi_cmd *cmd,
			  अचिन्हित अक्षर *buf)
अणु
	पूर्णांक data_direction, payload_length;
	काष्ठा iscsi_scsi_req *hdr;
	पूर्णांक iscsi_task_attr;
	पूर्णांक sam_task_attr;

	atomic_दीर्घ_inc(&conn->sess->cmd_pdus);

	hdr			= (काष्ठा iscsi_scsi_req *) buf;
	payload_length		= ntoh24(hdr->dlength);

	/* FIXME; Add checks क्रम AdditionalHeaderSegment */

	अगर (!(hdr->flags & ISCSI_FLAG_CMD_WRITE) &&
	    !(hdr->flags & ISCSI_FLAG_CMD_FINAL)) अणु
		pr_err("ISCSI_FLAG_CMD_WRITE & ISCSI_FLAG_CMD_FINAL"
				" not set. Bad iSCSI Initiator.\n");
		वापस iscsit_add_reject_cmd(cmd,
					     ISCSI_REASON_BOOKMARK_INVALID, buf);
	पूर्ण

	अगर (((hdr->flags & ISCSI_FLAG_CMD_READ) ||
	     (hdr->flags & ISCSI_FLAG_CMD_WRITE)) && !hdr->data_length) अणु
		/*
		 * From RFC-3720 Section 10.3.1:
		 *
		 * "Either or both of R and W MAY be 1 when either the
		 *  Expected Data Transfer Length and/or Bidirectional Read
		 *  Expected Data Transfer Length are 0"
		 *
		 * For this हाल, go ahead and clear the unnecssary bits
		 * to aव्योम any confusion with ->data_direction.
		 */
		hdr->flags &= ~ISCSI_FLAG_CMD_READ;
		hdr->flags &= ~ISCSI_FLAG_CMD_WRITE;

		pr_warn("ISCSI_FLAG_CMD_READ or ISCSI_FLAG_CMD_WRITE"
			" set when Expected Data Transfer Length is 0 for"
			" CDB: 0x%02x, Fixing up flags\n", hdr->cdb[0]);
	पूर्ण

	अगर (!(hdr->flags & ISCSI_FLAG_CMD_READ) &&
	    !(hdr->flags & ISCSI_FLAG_CMD_WRITE) && (hdr->data_length != 0)) अणु
		pr_err("ISCSI_FLAG_CMD_READ and/or ISCSI_FLAG_CMD_WRITE"
			" MUST be set if Expected Data Transfer Length is not 0."
			" Bad iSCSI Initiator\n");
		वापस iscsit_add_reject_cmd(cmd,
					     ISCSI_REASON_BOOKMARK_INVALID, buf);
	पूर्ण

	अगर ((hdr->flags & ISCSI_FLAG_CMD_READ) &&
	    (hdr->flags & ISCSI_FLAG_CMD_WRITE)) अणु
		pr_err("Bidirectional operations not supported!\n");
		वापस iscsit_add_reject_cmd(cmd,
					     ISCSI_REASON_BOOKMARK_INVALID, buf);
	पूर्ण

	अगर (hdr->opcode & ISCSI_OP_IMMEDIATE) अणु
		pr_err("Illegally set Immediate Bit in iSCSI Initiator"
				" Scsi Command PDU.\n");
		वापस iscsit_add_reject_cmd(cmd,
					     ISCSI_REASON_BOOKMARK_INVALID, buf);
	पूर्ण

	अगर (payload_length && !conn->sess->sess_ops->ImmediateData) अणु
		pr_err("ImmediateData=No but DataSegmentLength=%u,"
			" protocol error.\n", payload_length);
		वापस iscsit_add_reject_cmd(cmd,
					     ISCSI_REASON_PROTOCOL_ERROR, buf);
	पूर्ण

	अगर ((be32_to_cpu(hdr->data_length) == payload_length) &&
	    (!(hdr->flags & ISCSI_FLAG_CMD_FINAL))) अणु
		pr_err("Expected Data Transfer Length and Length of"
			" Immediate Data are the same, but ISCSI_FLAG_CMD_FINAL"
			" bit is not set protocol error\n");
		वापस iscsit_add_reject_cmd(cmd,
					     ISCSI_REASON_PROTOCOL_ERROR, buf);
	पूर्ण

	अगर (payload_length > be32_to_cpu(hdr->data_length)) अणु
		pr_err("DataSegmentLength: %u is greater than"
			" EDTL: %u, protocol error.\n", payload_length,
				hdr->data_length);
		वापस iscsit_add_reject_cmd(cmd,
					     ISCSI_REASON_PROTOCOL_ERROR, buf);
	पूर्ण

	अगर (payload_length > conn->conn_ops->MaxXmitDataSegmentLength) अणु
		pr_err("DataSegmentLength: %u is greater than"
			" MaxXmitDataSegmentLength: %u, protocol error.\n",
			payload_length, conn->conn_ops->MaxXmitDataSegmentLength);
		वापस iscsit_add_reject_cmd(cmd,
					     ISCSI_REASON_PROTOCOL_ERROR, buf);
	पूर्ण

	अगर (payload_length > conn->sess->sess_ops->FirstBurstLength) अणु
		pr_err("DataSegmentLength: %u is greater than"
			" FirstBurstLength: %u, protocol error.\n",
			payload_length, conn->sess->sess_ops->FirstBurstLength);
		वापस iscsit_add_reject_cmd(cmd,
					     ISCSI_REASON_BOOKMARK_INVALID, buf);
	पूर्ण

	data_direction = (hdr->flags & ISCSI_FLAG_CMD_WRITE) ? DMA_TO_DEVICE :
			 (hdr->flags & ISCSI_FLAG_CMD_READ) ? DMA_FROM_DEVICE :
			  DMA_NONE;

	cmd->data_direction = data_direction;
	iscsi_task_attr = hdr->flags & ISCSI_FLAG_CMD_ATTR_MASK;
	/*
	 * Figure out the SAM Task Attribute क्रम the incoming SCSI CDB
	 */
	अगर ((iscsi_task_attr == ISCSI_ATTR_UNTAGGED) ||
	    (iscsi_task_attr == ISCSI_ATTR_SIMPLE))
		sam_task_attr = TCM_SIMPLE_TAG;
	अन्यथा अगर (iscsi_task_attr == ISCSI_ATTR_ORDERED)
		sam_task_attr = TCM_ORDERED_TAG;
	अन्यथा अगर (iscsi_task_attr == ISCSI_ATTR_HEAD_OF_QUEUE)
		sam_task_attr = TCM_HEAD_TAG;
	अन्यथा अगर (iscsi_task_attr == ISCSI_ATTR_ACA)
		sam_task_attr = TCM_ACA_TAG;
	अन्यथा अणु
		pr_debug("Unknown iSCSI Task Attribute: 0x%02x, using"
			" TCM_SIMPLE_TAG\n", iscsi_task_attr);
		sam_task_attr = TCM_SIMPLE_TAG;
	पूर्ण

	cmd->iscsi_opcode	= ISCSI_OP_SCSI_CMD;
	cmd->i_state		= ISTATE_NEW_CMD;
	cmd->immediate_cmd	= ((hdr->opcode & ISCSI_OP_IMMEDIATE) ? 1 : 0);
	cmd->immediate_data	= (payload_length) ? 1 : 0;
	cmd->unsolicited_data	= ((!(hdr->flags & ISCSI_FLAG_CMD_FINAL) &&
				     (hdr->flags & ISCSI_FLAG_CMD_WRITE)) ? 1 : 0);
	अगर (cmd->unsolicited_data)
		cmd->cmd_flags |= ICF_NON_IMMEDIATE_UNSOLICITED_DATA;

	conn->sess->init_task_tag = cmd->init_task_tag = hdr->itt;
	अगर (hdr->flags & ISCSI_FLAG_CMD_READ)
		cmd->targ_xfer_tag = session_get_next_ttt(conn->sess);
	अन्यथा
		cmd->targ_xfer_tag = 0xFFFFFFFF;
	cmd->cmd_sn		= be32_to_cpu(hdr->cmdsn);
	cmd->exp_stat_sn	= be32_to_cpu(hdr->exp_statsn);
	cmd->first_burst_len	= payload_length;

	अगर (!conn->sess->sess_ops->RDMAExtensions &&
	     cmd->data_direction == DMA_FROM_DEVICE) अणु
		काष्ठा iscsi_datain_req *dr;

		dr = iscsit_allocate_datain_req();
		अगर (!dr)
			वापस iscsit_add_reject_cmd(cmd,
					ISCSI_REASON_BOOKMARK_NO_RESOURCES, buf);

		iscsit_attach_datain_req(cmd, dr);
	पूर्ण

	/*
	 * Initialize काष्ठा se_cmd descriptor from target_core_mod infraकाष्ठाure
	 */
	__target_init_cmd(&cmd->se_cmd, &iscsi_ops,
			 conn->sess->se_sess, be32_to_cpu(hdr->data_length),
			 cmd->data_direction, sam_task_attr,
			 cmd->sense_buffer + 2, scsilun_to_पूर्णांक(&hdr->lun));

	pr_debug("Got SCSI Command, ITT: 0x%08x, CmdSN: 0x%08x,"
		" ExpXferLen: %u, Length: %u, CID: %hu\n", hdr->itt,
		hdr->cmdsn, be32_to_cpu(hdr->data_length), payload_length,
		conn->cid);

	target_get_sess_cmd(&cmd->se_cmd, true);

	cmd->se_cmd.tag = (__क्रमce u32)cmd->init_task_tag;
	cmd->sense_reason = target_cmd_init_cdb(&cmd->se_cmd, hdr->cdb,
						GFP_KERNEL);

	अगर (cmd->sense_reason) अणु
		अगर (cmd->sense_reason == TCM_OUT_OF_RESOURCES) अणु
			वापस iscsit_add_reject_cmd(cmd,
				ISCSI_REASON_BOOKMARK_NO_RESOURCES, buf);
		पूर्ण

		जाओ attach_cmd;
	पूर्ण

	cmd->sense_reason = transport_lookup_cmd_lun(&cmd->se_cmd);
	अगर (cmd->sense_reason)
		जाओ attach_cmd;

	cmd->sense_reason = target_cmd_parse_cdb(&cmd->se_cmd);
	अगर (cmd->sense_reason)
		जाओ attach_cmd;

	अगर (iscsit_build_pdu_and_seq_lists(cmd, payload_length) < 0) अणु
		वापस iscsit_add_reject_cmd(cmd,
				ISCSI_REASON_BOOKMARK_NO_RESOURCES, buf);
	पूर्ण

attach_cmd:
	spin_lock_bh(&conn->cmd_lock);
	list_add_tail(&cmd->i_conn_node, &conn->conn_cmd_list);
	spin_unlock_bh(&conn->cmd_lock);
	/*
	 * Check अगर we need to delay processing because of ALUA
	 * Active/NonOptimized primary access state..
	 */
	core_alua_check_nonop_delay(&cmd->se_cmd);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(iscsit_setup_scsi_cmd);

व्योम iscsit_set_unsolicited_dataout(काष्ठा iscsi_cmd *cmd)
अणु
	iscsit_set_dataout_sequence_values(cmd);

	spin_lock_bh(&cmd->dataout_समयout_lock);
	iscsit_start_dataout_समयr(cmd, cmd->conn);
	spin_unlock_bh(&cmd->dataout_समयout_lock);
पूर्ण
EXPORT_SYMBOL(iscsit_set_unsolicited_dataout);

पूर्णांक iscsit_process_scsi_cmd(काष्ठा iscsi_conn *conn, काष्ठा iscsi_cmd *cmd,
			    काष्ठा iscsi_scsi_req *hdr)
अणु
	पूर्णांक cmdsn_ret = 0;
	/*
	 * Check the CmdSN against ExpCmdSN/MaxCmdSN here अगर
	 * the Immediate Bit is not set, and no Immediate
	 * Data is attached.
	 *
	 * A PDU/CmdSN carrying Immediate Data can only
	 * be processed after the DataCRC has passed.
	 * If the DataCRC fails, the CmdSN MUST NOT
	 * be acknowledged. (See below)
	 */
	अगर (!cmd->immediate_data) अणु
		cmdsn_ret = iscsit_sequence_cmd(conn, cmd,
					(अचिन्हित अक्षर *)hdr, hdr->cmdsn);
		अगर (cmdsn_ret == CMDSN_ERROR_CANNOT_RECOVER)
			वापस -1;
		अन्यथा अगर (cmdsn_ret == CMDSN_LOWER_THAN_EXP) अणु
			target_put_sess_cmd(&cmd->se_cmd);
			वापस 0;
		पूर्ण
	पूर्ण

	iscsit_ack_from_expstatsn(conn, be32_to_cpu(hdr->exp_statsn));

	/*
	 * If no Immediate Data is attached, it's OK to वापस now.
	 */
	अगर (!cmd->immediate_data) अणु
		अगर (!cmd->sense_reason && cmd->unsolicited_data)
			iscsit_set_unsolicited_dataout(cmd);
		अगर (!cmd->sense_reason)
			वापस 0;

		target_put_sess_cmd(&cmd->se_cmd);
		वापस 0;
	पूर्ण

	/*
	 * Early CHECK_CONDITIONs with ImmediateData never make it to command
	 * execution.  These exceptions are processed in CmdSN order using
	 * iscsit_check_received_cmdsn() in iscsit_get_immediate_data() below.
	 */
	अगर (cmd->sense_reason)
		वापस 1;
	/*
	 * Call directly पूर्णांकo transport_generic_new_cmd() to perक्रमm
	 * the backend memory allocation.
	 */
	cmd->sense_reason = transport_generic_new_cmd(&cmd->se_cmd);
	अगर (cmd->sense_reason)
		वापस 1;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(iscsit_process_scsi_cmd);

अटल पूर्णांक
iscsit_get_immediate_data(काष्ठा iscsi_cmd *cmd, काष्ठा iscsi_scsi_req *hdr,
			  bool dump_payload)
अणु
	पूर्णांक cmdsn_ret = 0, immed_ret = IMMEDIATE_DATA_NORMAL_OPERATION;
	पूर्णांक rc;

	/*
	 * Special हाल क्रम Unsupported SAM WRITE Opcodes and ImmediateData=Yes.
	 */
	अगर (dump_payload) अणु
		u32 length = min(cmd->se_cmd.data_length - cmd->ग_लिखो_data_करोne,
				 cmd->first_burst_len);

		pr_debug("Dumping min(%d - %d, %d) = %d bytes of immediate data\n",
			 cmd->se_cmd.data_length, cmd->ग_लिखो_data_करोne,
			 cmd->first_burst_len, length);
		rc = iscsit_dump_data_payload(cmd->conn, length, 1);
		pr_debug("Finished dumping immediate data\n");
		अगर (rc < 0)
			immed_ret = IMMEDIATE_DATA_CANNOT_RECOVER;
	पूर्ण अन्यथा अणु
		immed_ret = iscsit_handle_immediate_data(cmd, hdr,
							 cmd->first_burst_len);
	पूर्ण

	अगर (immed_ret == IMMEDIATE_DATA_NORMAL_OPERATION) अणु
		/*
		 * A PDU/CmdSN carrying Immediate Data passed
		 * DataCRC, check against ExpCmdSN/MaxCmdSN अगर
		 * Immediate Bit is not set.
		 */
		cmdsn_ret = iscsit_sequence_cmd(cmd->conn, cmd,
					(अचिन्हित अक्षर *)hdr, hdr->cmdsn);
		अगर (cmdsn_ret == CMDSN_ERROR_CANNOT_RECOVER)
			वापस -1;

		अगर (cmd->sense_reason || cmdsn_ret == CMDSN_LOWER_THAN_EXP) अणु
			target_put_sess_cmd(&cmd->se_cmd);

			वापस 0;
		पूर्ण अन्यथा अगर (cmd->unsolicited_data)
			iscsit_set_unsolicited_dataout(cmd);

	पूर्ण अन्यथा अगर (immed_ret == IMMEDIATE_DATA_ERL1_CRC_FAILURE) अणु
		/*
		 * Immediate Data failed DataCRC and ERL>=1,
		 * silently drop this PDU and let the initiator
		 * plug the CmdSN gap.
		 *
		 * FIXME: Send Unsolicited NOPIN with reserved
		 * TTT here to help the initiator figure out
		 * the missing CmdSN, although they should be
		 * पूर्णांकelligent enough to determine the missing
		 * CmdSN and issue a retry to plug the sequence.
		 */
		cmd->i_state = ISTATE_REMOVE;
		iscsit_add_cmd_to_immediate_queue(cmd, cmd->conn, cmd->i_state);
	पूर्ण अन्यथा /* immed_ret == IMMEDIATE_DATA_CANNOT_RECOVER */
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक
iscsit_handle_scsi_cmd(काष्ठा iscsi_conn *conn, काष्ठा iscsi_cmd *cmd,
			   अचिन्हित अक्षर *buf)
अणु
	काष्ठा iscsi_scsi_req *hdr = (काष्ठा iscsi_scsi_req *)buf;
	पूर्णांक rc, immed_data;
	bool dump_payload = false;

	rc = iscsit_setup_scsi_cmd(conn, cmd, buf);
	अगर (rc < 0)
		वापस 0;
	/*
	 * Allocation iovecs needed क्रम काष्ठा socket operations क्रम
	 * traditional iSCSI block I/O.
	 */
	अगर (iscsit_allocate_iovecs(cmd) < 0) अणु
		वापस iscsit_reject_cmd(cmd,
				ISCSI_REASON_BOOKMARK_NO_RESOURCES, buf);
	पूर्ण
	immed_data = cmd->immediate_data;

	rc = iscsit_process_scsi_cmd(conn, cmd, hdr);
	अगर (rc < 0)
		वापस rc;
	अन्यथा अगर (rc > 0)
		dump_payload = true;

	अगर (!immed_data)
		वापस 0;

	वापस iscsit_get_immediate_data(cmd, hdr, dump_payload);
पूर्ण

अटल u32 iscsit_करो_crypto_hash_sg(
	काष्ठा ahash_request *hash,
	काष्ठा iscsi_cmd *cmd,
	u32 data_offset,
	u32 data_length,
	u32 padding,
	u8 *pad_bytes)
अणु
	u32 data_crc;
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक page_off;

	crypto_ahash_init(hash);

	sg = cmd->first_data_sg;
	page_off = cmd->first_data_sg_off;

	अगर (data_length && page_off) अणु
		काष्ठा scatterlist first_sg;
		u32 len = min_t(u32, data_length, sg->length - page_off);

		sg_init_table(&first_sg, 1);
		sg_set_page(&first_sg, sg_page(sg), len, sg->offset + page_off);

		ahash_request_set_crypt(hash, &first_sg, शून्य, len);
		crypto_ahash_update(hash);

		data_length -= len;
		sg = sg_next(sg);
	पूर्ण

	जबतक (data_length) अणु
		u32 cur_len = min_t(u32, data_length, sg->length);

		ahash_request_set_crypt(hash, sg, शून्य, cur_len);
		crypto_ahash_update(hash);

		data_length -= cur_len;
		/* iscsit_map_iovec has alपढ़ोy checked क्रम invalid sg poपूर्णांकers */
		sg = sg_next(sg);
	पूर्ण

	अगर (padding) अणु
		काष्ठा scatterlist pad_sg;

		sg_init_one(&pad_sg, pad_bytes, padding);
		ahash_request_set_crypt(hash, &pad_sg, (u8 *)&data_crc,
					padding);
		crypto_ahash_finup(hash);
	पूर्ण अन्यथा अणु
		ahash_request_set_crypt(hash, शून्य, (u8 *)&data_crc, 0);
		crypto_ahash_final(hash);
	पूर्ण

	वापस data_crc;
पूर्ण

अटल व्योम iscsit_करो_crypto_hash_buf(काष्ठा ahash_request *hash,
	स्थिर व्योम *buf, u32 payload_length, u32 padding,
	स्थिर व्योम *pad_bytes, व्योम *data_crc)
अणु
	काष्ठा scatterlist sg[2];

	sg_init_table(sg, ARRAY_SIZE(sg));
	sg_set_buf(sg, buf, payload_length);
	अगर (padding)
		sg_set_buf(sg + 1, pad_bytes, padding);

	ahash_request_set_crypt(hash, sg, data_crc, payload_length + padding);

	crypto_ahash_digest(hash);
पूर्ण

पूर्णांक
__iscsit_check_dataout_hdr(काष्ठा iscsi_conn *conn, व्योम *buf,
			   काष्ठा iscsi_cmd *cmd, u32 payload_length,
			   bool *success)
अणु
	काष्ठा iscsi_data *hdr = buf;
	काष्ठा se_cmd *se_cmd;
	पूर्णांक rc;

	/* iSCSI ग_लिखो */
	atomic_दीर्घ_add(payload_length, &conn->sess->rx_data_octets);

	pr_debug("Got DataOut ITT: 0x%08x, TTT: 0x%08x,"
		" DataSN: 0x%08x, Offset: %u, Length: %u, CID: %hu\n",
		hdr->itt, hdr->ttt, hdr->datasn, ntohl(hdr->offset),
		payload_length, conn->cid);

	अगर (cmd->cmd_flags & ICF_GOT_LAST_DATAOUT) अणु
		pr_err("Command ITT: 0x%08x received DataOUT after"
			" last DataOUT received, dumping payload\n",
			cmd->init_task_tag);
		वापस iscsit_dump_data_payload(conn, payload_length, 1);
	पूर्ण

	अगर (cmd->data_direction != DMA_TO_DEVICE) अणु
		pr_err("Command ITT: 0x%08x received DataOUT for a"
			" NON-WRITE command.\n", cmd->init_task_tag);
		वापस iscsit_dump_data_payload(conn, payload_length, 1);
	पूर्ण
	se_cmd = &cmd->se_cmd;
	iscsit_mod_dataout_समयr(cmd);

	अगर ((be32_to_cpu(hdr->offset) + payload_length) > cmd->se_cmd.data_length) अणु
		pr_err("DataOut Offset: %u, Length %u greater than iSCSI Command EDTL %u, protocol error.\n",
		       be32_to_cpu(hdr->offset), payload_length,
		       cmd->se_cmd.data_length);
		वापस iscsit_reject_cmd(cmd, ISCSI_REASON_BOOKMARK_INVALID, buf);
	पूर्ण

	अगर (cmd->unsolicited_data) अणु
		पूर्णांक dump_unsolicited_data = 0;

		अगर (conn->sess->sess_ops->InitialR2T) अणु
			pr_err("Received unexpected unsolicited data"
				" while InitialR2T=Yes, protocol error.\n");
			transport_send_check_condition_and_sense(&cmd->se_cmd,
					TCM_UNEXPECTED_UNSOLICITED_DATA, 0);
			वापस -1;
		पूर्ण
		/*
		 * Special हाल क्रम dealing with Unsolicited DataOUT
		 * and Unsupported SAM WRITE Opcodes and SE resource allocation
		 * failures;
		 */

		/* Something's amiss if we're not in WRITE_PENDING state... */
		WARN_ON(se_cmd->t_state != TRANSPORT_WRITE_PENDING);
		अगर (!(se_cmd->se_cmd_flags & SCF_SUPPORTED_SAM_OPCODE))
			dump_unsolicited_data = 1;

		अगर (dump_unsolicited_data) अणु
			/*
			 * Check अगर a delayed TASK_ABORTED status needs to
			 * be sent now अगर the ISCSI_FLAG_CMD_FINAL has been
			 * received with the unsolicited data out.
			 */
			अगर (hdr->flags & ISCSI_FLAG_CMD_FINAL)
				iscsit_stop_dataout_समयr(cmd);

			वापस iscsit_dump_data_payload(conn, payload_length, 1);
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * For the normal solicited data path:
		 *
		 * Check क्रम a delayed TASK_ABORTED status and dump any
		 * incoming data out payload अगर one exists.  Also, when the
		 * ISCSI_FLAG_CMD_FINAL is set to denote the end of the current
		 * data out sequence, we decrement outstanding_r2ts.  Once
		 * outstanding_r2ts reaches zero, go ahead and send the delayed
		 * TASK_ABORTED status.
		 */
		अगर (se_cmd->transport_state & CMD_T_ABORTED) अणु
			अगर (hdr->flags & ISCSI_FLAG_CMD_FINAL &&
			    --cmd->outstanding_r2ts < 1)
				iscsit_stop_dataout_समयr(cmd);

			वापस iscsit_dump_data_payload(conn, payload_length, 1);
		पूर्ण
	पूर्ण
	/*
	 * Perक्रमm DataSN, DataSequenceInOrder, DataPDUInOrder, and
	 * within-command recovery checks beक्रमe receiving the payload.
	 */
	rc = iscsit_check_pre_dataout(cmd, buf);
	अगर (rc == DATAOUT_WITHIN_COMMAND_RECOVERY)
		वापस 0;
	अन्यथा अगर (rc == DATAOUT_CANNOT_RECOVER)
		वापस -1;
	*success = true;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(__iscsit_check_dataout_hdr);

पूर्णांक
iscsit_check_dataout_hdr(काष्ठा iscsi_conn *conn, व्योम *buf,
			 काष्ठा iscsi_cmd **out_cmd)
अणु
	काष्ठा iscsi_data *hdr = buf;
	काष्ठा iscsi_cmd *cmd;
	u32 payload_length = ntoh24(hdr->dlength);
	पूर्णांक rc;
	bool success = false;

	अगर (!payload_length) अणु
		pr_warn_ratelimited("DataOUT payload is ZERO, ignoring.\n");
		वापस 0;
	पूर्ण

	अगर (payload_length > conn->conn_ops->MaxXmitDataSegmentLength) अणु
		pr_err_ratelimited("DataSegmentLength: %u is greater than"
			" MaxXmitDataSegmentLength: %u\n", payload_length,
			conn->conn_ops->MaxXmitDataSegmentLength);
		वापस iscsit_add_reject(conn, ISCSI_REASON_PROTOCOL_ERROR, buf);
	पूर्ण

	cmd = iscsit_find_cmd_from_itt_or_dump(conn, hdr->itt, payload_length);
	अगर (!cmd)
		वापस 0;

	rc = __iscsit_check_dataout_hdr(conn, buf, cmd, payload_length, &success);

	अगर (success)
		*out_cmd = cmd;

	वापस rc;
पूर्ण
EXPORT_SYMBOL(iscsit_check_dataout_hdr);

अटल पूर्णांक
iscsit_get_dataout(काष्ठा iscsi_conn *conn, काष्ठा iscsi_cmd *cmd,
		   काष्ठा iscsi_data *hdr)
अणु
	काष्ठा kvec *iov;
	u32 checksum, iov_count = 0, padding = 0, rx_got = 0, rx_size = 0;
	u32 payload_length;
	पूर्णांक iov_ret, data_crc_failed = 0;

	payload_length = min_t(u32, cmd->se_cmd.data_length,
			       ntoh24(hdr->dlength));
	rx_size += payload_length;
	iov = &cmd->iov_data[0];

	iov_ret = iscsit_map_iovec(cmd, iov, cmd->orig_iov_data_count - 2,
				   be32_to_cpu(hdr->offset), payload_length);
	अगर (iov_ret < 0)
		वापस -1;

	iov_count += iov_ret;

	padding = ((-payload_length) & 3);
	अगर (padding != 0) अणु
		iov[iov_count].iov_base	= cmd->pad_bytes;
		iov[iov_count++].iov_len = padding;
		rx_size += padding;
		pr_debug("Receiving %u padding bytes.\n", padding);
	पूर्ण

	अगर (conn->conn_ops->DataDigest) अणु
		iov[iov_count].iov_base = &checksum;
		iov[iov_count++].iov_len = ISCSI_CRC_LEN;
		rx_size += ISCSI_CRC_LEN;
	पूर्ण

	WARN_ON_ONCE(iov_count > cmd->orig_iov_data_count);
	rx_got = rx_data(conn, &cmd->iov_data[0], iov_count, rx_size);

	iscsit_unmap_iovec(cmd);

	अगर (rx_got != rx_size)
		वापस -1;

	अगर (conn->conn_ops->DataDigest) अणु
		u32 data_crc;

		data_crc = iscsit_करो_crypto_hash_sg(conn->conn_rx_hash, cmd,
						    be32_to_cpu(hdr->offset),
						    payload_length, padding,
						    cmd->pad_bytes);

		अगर (checksum != data_crc) अणु
			pr_err("ITT: 0x%08x, Offset: %u, Length: %u,"
				" DataSN: 0x%08x, CRC32C DataDigest 0x%08x"
				" does not match computed 0x%08x\n",
				hdr->itt, hdr->offset, payload_length,
				hdr->datasn, checksum, data_crc);
			data_crc_failed = 1;
		पूर्ण अन्यथा अणु
			pr_debug("Got CRC32C DataDigest 0x%08x for"
				" %u bytes of Data Out\n", checksum,
				payload_length);
		पूर्ण
	पूर्ण

	वापस data_crc_failed;
पूर्ण

पूर्णांक
iscsit_check_dataout_payload(काष्ठा iscsi_cmd *cmd, काष्ठा iscsi_data *hdr,
			     bool data_crc_failed)
अणु
	काष्ठा iscsi_conn *conn = cmd->conn;
	पूर्णांक rc, ooo_cmdsn;
	/*
	 * Increment post receive data and CRC values or perक्रमm
	 * within-command recovery.
	 */
	rc = iscsit_check_post_dataout(cmd, (अचिन्हित अक्षर *)hdr, data_crc_failed);
	अगर ((rc == DATAOUT_NORMAL) || (rc == DATAOUT_WITHIN_COMMAND_RECOVERY))
		वापस 0;
	अन्यथा अगर (rc == DATAOUT_SEND_R2T) अणु
		iscsit_set_dataout_sequence_values(cmd);
		conn->conn_transport->iscsit_get_dataout(conn, cmd, false);
	पूर्ण अन्यथा अगर (rc == DATAOUT_SEND_TO_TRANSPORT) अणु
		/*
		 * Handle extra special हाल क्रम out of order
		 * Unsolicited Data Out.
		 */
		spin_lock_bh(&cmd->istate_lock);
		ooo_cmdsn = (cmd->cmd_flags & ICF_OOO_CMDSN);
		cmd->cmd_flags |= ICF_GOT_LAST_DATAOUT;
		cmd->i_state = ISTATE_RECEIVED_LAST_DATAOUT;
		spin_unlock_bh(&cmd->istate_lock);

		iscsit_stop_dataout_समयr(cmd);
		अगर (ooo_cmdsn)
			वापस 0;
		target_execute_cmd(&cmd->se_cmd);
		वापस 0;
	पूर्ण अन्यथा /* DATAOUT_CANNOT_RECOVER */
		वापस -1;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(iscsit_check_dataout_payload);

अटल पूर्णांक iscsit_handle_data_out(काष्ठा iscsi_conn *conn, अचिन्हित अक्षर *buf)
अणु
	काष्ठा iscsi_cmd *cmd = शून्य;
	काष्ठा iscsi_data *hdr = (काष्ठा iscsi_data *)buf;
	पूर्णांक rc;
	bool data_crc_failed = false;

	rc = iscsit_check_dataout_hdr(conn, buf, &cmd);
	अगर (rc < 0)
		वापस 0;
	अन्यथा अगर (!cmd)
		वापस 0;

	rc = iscsit_get_dataout(conn, cmd, hdr);
	अगर (rc < 0)
		वापस rc;
	अन्यथा अगर (rc > 0)
		data_crc_failed = true;

	वापस iscsit_check_dataout_payload(cmd, hdr, data_crc_failed);
पूर्ण

पूर्णांक iscsit_setup_nop_out(काष्ठा iscsi_conn *conn, काष्ठा iscsi_cmd *cmd,
			 काष्ठा iscsi_nopout *hdr)
अणु
	u32 payload_length = ntoh24(hdr->dlength);

	अगर (!(hdr->flags & ISCSI_FLAG_CMD_FINAL)) अणु
		pr_err("NopOUT Flag's, Left Most Bit not set, protocol error.\n");
		अगर (!cmd)
			वापस iscsit_add_reject(conn, ISCSI_REASON_PROTOCOL_ERROR,
						 (अचिन्हित अक्षर *)hdr);
		
		वापस iscsit_reject_cmd(cmd, ISCSI_REASON_PROTOCOL_ERROR,
					 (अचिन्हित अक्षर *)hdr);
	पूर्ण

	अगर (hdr->itt == RESERVED_ITT && !(hdr->opcode & ISCSI_OP_IMMEDIATE)) अणु
		pr_err("NOPOUT ITT is reserved, but Immediate Bit is"
			" not set, protocol error.\n");
		अगर (!cmd)
			वापस iscsit_add_reject(conn, ISCSI_REASON_PROTOCOL_ERROR,
						 (अचिन्हित अक्षर *)hdr);

		वापस iscsit_reject_cmd(cmd, ISCSI_REASON_PROTOCOL_ERROR,
					 (अचिन्हित अक्षर *)hdr);
	पूर्ण

	अगर (payload_length > conn->conn_ops->MaxXmitDataSegmentLength) अणु
		pr_err("NOPOUT Ping Data DataSegmentLength: %u is"
			" greater than MaxXmitDataSegmentLength: %u, protocol"
			" error.\n", payload_length,
			conn->conn_ops->MaxXmitDataSegmentLength);
		अगर (!cmd)
			वापस iscsit_add_reject(conn, ISCSI_REASON_PROTOCOL_ERROR,
						 (अचिन्हित अक्षर *)hdr);

		वापस iscsit_reject_cmd(cmd, ISCSI_REASON_PROTOCOL_ERROR,
					 (अचिन्हित अक्षर *)hdr);
	पूर्ण

	pr_debug("Got NOPOUT Ping %s ITT: 0x%08x, TTT: 0x%08x,"
		" CmdSN: 0x%08x, ExpStatSN: 0x%08x, Length: %u\n",
		hdr->itt == RESERVED_ITT ? "Response" : "Request",
		hdr->itt, hdr->ttt, hdr->cmdsn, hdr->exp_statsn,
		payload_length);
	/*
	 * This is not a response to a Unsolicited NopIN, which means
	 * it can either be a NOPOUT ping request (with a valid ITT),
	 * or a NOPOUT not requesting a NOPIN (with a reserved ITT).
	 * Either way, make sure we allocate an काष्ठा iscsi_cmd, as both
	 * can contain ping data.
	 */
	अगर (hdr->ttt == cpu_to_be32(0xFFFFFFFF)) अणु
		cmd->iscsi_opcode	= ISCSI_OP_NOOP_OUT;
		cmd->i_state		= ISTATE_SEND_NOPIN;
		cmd->immediate_cmd	= ((hdr->opcode & ISCSI_OP_IMMEDIATE) ?
						1 : 0);
		conn->sess->init_task_tag = cmd->init_task_tag = hdr->itt;
		cmd->targ_xfer_tag	= 0xFFFFFFFF;
		cmd->cmd_sn		= be32_to_cpu(hdr->cmdsn);
		cmd->exp_stat_sn	= be32_to_cpu(hdr->exp_statsn);
		cmd->data_direction	= DMA_NONE;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(iscsit_setup_nop_out);

पूर्णांक iscsit_process_nop_out(काष्ठा iscsi_conn *conn, काष्ठा iscsi_cmd *cmd,
			   काष्ठा iscsi_nopout *hdr)
अणु
	काष्ठा iscsi_cmd *cmd_p = शून्य;
	पूर्णांक cmdsn_ret = 0;
	/*
	 * Initiator is expecting a NopIN ping reply..
	 */
	अगर (hdr->itt != RESERVED_ITT) अणु
		अगर (!cmd)
			वापस iscsit_add_reject(conn, ISCSI_REASON_PROTOCOL_ERROR,
						(अचिन्हित अक्षर *)hdr);

		spin_lock_bh(&conn->cmd_lock);
		list_add_tail(&cmd->i_conn_node, &conn->conn_cmd_list);
		spin_unlock_bh(&conn->cmd_lock);

		iscsit_ack_from_expstatsn(conn, be32_to_cpu(hdr->exp_statsn));

		अगर (hdr->opcode & ISCSI_OP_IMMEDIATE) अणु
			iscsit_add_cmd_to_response_queue(cmd, conn,
							 cmd->i_state);
			वापस 0;
		पूर्ण

		cmdsn_ret = iscsit_sequence_cmd(conn, cmd,
				(अचिन्हित अक्षर *)hdr, hdr->cmdsn);
                अगर (cmdsn_ret == CMDSN_LOWER_THAN_EXP)
			वापस 0;
		अगर (cmdsn_ret == CMDSN_ERROR_CANNOT_RECOVER)
			वापस -1;

		वापस 0;
	पूर्ण
	/*
	 * This was a response to a unsolicited NOPIN ping.
	 */
	अगर (hdr->ttt != cpu_to_be32(0xFFFFFFFF)) अणु
		cmd_p = iscsit_find_cmd_from_ttt(conn, be32_to_cpu(hdr->ttt));
		अगर (!cmd_p)
			वापस -EINVAL;

		iscsit_stop_nopin_response_समयr(conn);

		cmd_p->i_state = ISTATE_REMOVE;
		iscsit_add_cmd_to_immediate_queue(cmd_p, conn, cmd_p->i_state);

		iscsit_start_nopin_समयr(conn);
		वापस 0;
	पूर्ण
	/*
	 * Otherwise, initiator is not expecting a NOPIN is response.
	 * Just ignore क्रम now.
	 */

	अगर (cmd)
		iscsit_मुक्त_cmd(cmd, false);

        वापस 0;
पूर्ण
EXPORT_SYMBOL(iscsit_process_nop_out);

अटल पूर्णांक iscsit_handle_nop_out(काष्ठा iscsi_conn *conn, काष्ठा iscsi_cmd *cmd,
				 अचिन्हित अक्षर *buf)
अणु
	अचिन्हित अक्षर *ping_data = शून्य;
	काष्ठा iscsi_nopout *hdr = (काष्ठा iscsi_nopout *)buf;
	काष्ठा kvec *iov = शून्य;
	u32 payload_length = ntoh24(hdr->dlength);
	पूर्णांक ret;

	ret = iscsit_setup_nop_out(conn, cmd, hdr);
	अगर (ret < 0)
		वापस 0;
	/*
	 * Handle NOP-OUT payload क्रम traditional iSCSI sockets
	 */
	अगर (payload_length && hdr->ttt == cpu_to_be32(0xFFFFFFFF)) अणु
		u32 checksum, data_crc, padding = 0;
		पूर्णांक niov = 0, rx_got, rx_size = payload_length;

		ping_data = kzalloc(payload_length + 1, GFP_KERNEL);
		अगर (!ping_data) अणु
			ret = -1;
			जाओ out;
		पूर्ण

		iov = &cmd->iov_misc[0];
		iov[niov].iov_base	= ping_data;
		iov[niov++].iov_len	= payload_length;

		padding = ((-payload_length) & 3);
		अगर (padding != 0) अणु
			pr_debug("Receiving %u additional bytes"
				" for padding.\n", padding);
			iov[niov].iov_base	= &cmd->pad_bytes;
			iov[niov++].iov_len	= padding;
			rx_size += padding;
		पूर्ण
		अगर (conn->conn_ops->DataDigest) अणु
			iov[niov].iov_base	= &checksum;
			iov[niov++].iov_len	= ISCSI_CRC_LEN;
			rx_size += ISCSI_CRC_LEN;
		पूर्ण

		WARN_ON_ONCE(niov > ARRAY_SIZE(cmd->iov_misc));
		rx_got = rx_data(conn, &cmd->iov_misc[0], niov, rx_size);
		अगर (rx_got != rx_size) अणु
			ret = -1;
			जाओ out;
		पूर्ण

		अगर (conn->conn_ops->DataDigest) अणु
			iscsit_करो_crypto_hash_buf(conn->conn_rx_hash, ping_data,
						  payload_length, padding,
						  cmd->pad_bytes, &data_crc);

			अगर (checksum != data_crc) अणु
				pr_err("Ping data CRC32C DataDigest"
				" 0x%08x does not match computed 0x%08x\n",
					checksum, data_crc);
				अगर (!conn->sess->sess_ops->ErrorRecoveryLevel) अणु
					pr_err("Unable to recover from"
					" NOPOUT Ping DataCRC failure while in"
						" ERL=0.\n");
					ret = -1;
					जाओ out;
				पूर्ण अन्यथा अणु
					/*
					 * Silently drop this PDU and let the
					 * initiator plug the CmdSN gap.
					 */
					pr_debug("Dropping NOPOUT"
					" Command CmdSN: 0x%08x due to"
					" DataCRC error.\n", hdr->cmdsn);
					ret = 0;
					जाओ out;
				पूर्ण
			पूर्ण अन्यथा अणु
				pr_debug("Got CRC32C DataDigest"
				" 0x%08x for %u bytes of ping data.\n",
					checksum, payload_length);
			पूर्ण
		पूर्ण

		ping_data[payload_length] = '\0';
		/*
		 * Attach ping data to काष्ठा iscsi_cmd->buf_ptr.
		 */
		cmd->buf_ptr = ping_data;
		cmd->buf_ptr_size = payload_length;

		pr_debug("Got %u bytes of NOPOUT ping"
			" data.\n", payload_length);
		pr_debug("Ping Data: \"%s\"\n", ping_data);
	पूर्ण

	वापस iscsit_process_nop_out(conn, cmd, hdr);
out:
	अगर (cmd)
		iscsit_मुक्त_cmd(cmd, false);

	kमुक्त(ping_data);
	वापस ret;
पूर्ण

अटल क्रमागत tcm_पंचांगreq_table iscsit_convert_पंचांगf(u8 iscsi_पंचांगf)
अणु
	चयन (iscsi_पंचांगf) अणु
	हाल ISCSI_TM_FUNC_ABORT_TASK:
		वापस TMR_ABORT_TASK;
	हाल ISCSI_TM_FUNC_ABORT_TASK_SET:
		वापस TMR_ABORT_TASK_SET;
	हाल ISCSI_TM_FUNC_CLEAR_ACA:
		वापस TMR_CLEAR_ACA;
	हाल ISCSI_TM_FUNC_CLEAR_TASK_SET:
		वापस TMR_CLEAR_TASK_SET;
	हाल ISCSI_TM_FUNC_LOGICAL_UNIT_RESET:
		वापस TMR_LUN_RESET;
	हाल ISCSI_TM_FUNC_TARGET_WARM_RESET:
		वापस TMR_TARGET_WARM_RESET;
	हाल ISCSI_TM_FUNC_TARGET_COLD_RESET:
		वापस TMR_TARGET_COLD_RESET;
	शेष:
		वापस TMR_UNKNOWN;
	पूर्ण
पूर्ण

पूर्णांक
iscsit_handle_task_mgt_cmd(काष्ठा iscsi_conn *conn, काष्ठा iscsi_cmd *cmd,
			   अचिन्हित अक्षर *buf)
अणु
	काष्ठा se_पंचांगr_req *se_पंचांगr;
	काष्ठा iscsi_पंचांगr_req *पंचांगr_req;
	काष्ठा iscsi_पंचांग *hdr;
	पूर्णांक out_of_order_cmdsn = 0, ret;
	u8 function, tcm_function = TMR_UNKNOWN;

	hdr			= (काष्ठा iscsi_पंचांग *) buf;
	hdr->flags &= ~ISCSI_FLAG_CMD_FINAL;
	function = hdr->flags;

	pr_debug("Got Task Management Request ITT: 0x%08x, CmdSN:"
		" 0x%08x, Function: 0x%02x, RefTaskTag: 0x%08x, RefCmdSN:"
		" 0x%08x, CID: %hu\n", hdr->itt, hdr->cmdsn, function,
		hdr->rtt, hdr->refcmdsn, conn->cid);

	अगर ((function != ISCSI_TM_FUNC_ABORT_TASK) &&
	    ((function != ISCSI_TM_FUNC_TASK_REASSIGN) &&
	     hdr->rtt != RESERVED_ITT)) अणु
		pr_err("RefTaskTag should be set to 0xFFFFFFFF.\n");
		hdr->rtt = RESERVED_ITT;
	पूर्ण

	अगर ((function == ISCSI_TM_FUNC_TASK_REASSIGN) &&
			!(hdr->opcode & ISCSI_OP_IMMEDIATE)) अणु
		pr_err("Task Management Request TASK_REASSIGN not"
			" issued as immediate command, bad iSCSI Initiator"
				"implementation\n");
		वापस iscsit_add_reject_cmd(cmd,
					     ISCSI_REASON_PROTOCOL_ERROR, buf);
	पूर्ण
	अगर ((function != ISCSI_TM_FUNC_ABORT_TASK) &&
	    be32_to_cpu(hdr->refcmdsn) != ISCSI_RESERVED_TAG)
		hdr->refcmdsn = cpu_to_be32(ISCSI_RESERVED_TAG);

	cmd->data_direction = DMA_NONE;
	cmd->पंचांगr_req = kzalloc(माप(*cmd->पंचांगr_req), GFP_KERNEL);
	अगर (!cmd->पंचांगr_req) अणु
		वापस iscsit_add_reject_cmd(cmd,
					     ISCSI_REASON_BOOKMARK_NO_RESOURCES,
					     buf);
	पूर्ण

	__target_init_cmd(&cmd->se_cmd, &iscsi_ops,
			  conn->sess->se_sess, 0, DMA_NONE,
			  TCM_SIMPLE_TAG, cmd->sense_buffer + 2,
			  scsilun_to_पूर्णांक(&hdr->lun));

	target_get_sess_cmd(&cmd->se_cmd, true);

	/*
	 * TASK_REASSIGN क्रम ERL=2 / connection stays inside of
	 * LIO-Target $FABRIC_MOD
	 */
	अगर (function != ISCSI_TM_FUNC_TASK_REASSIGN) अणु
		tcm_function = iscsit_convert_पंचांगf(function);
		अगर (tcm_function == TMR_UNKNOWN) अणु
			pr_err("Unknown iSCSI TMR Function:"
			       " 0x%02x\n", function);
			वापस iscsit_add_reject_cmd(cmd,
				ISCSI_REASON_BOOKMARK_NO_RESOURCES, buf);
		पूर्ण
	पूर्ण
	ret = core_पंचांगr_alloc_req(&cmd->se_cmd, cmd->पंचांगr_req, tcm_function,
				 GFP_KERNEL);
	अगर (ret < 0)
		वापस iscsit_add_reject_cmd(cmd,
				ISCSI_REASON_BOOKMARK_NO_RESOURCES, buf);

	cmd->पंचांगr_req->se_पंचांगr_req = cmd->se_cmd.se_पंचांगr_req;

	cmd->iscsi_opcode	= ISCSI_OP_SCSI_TMFUNC;
	cmd->i_state		= ISTATE_SEND_TASKMGTRSP;
	cmd->immediate_cmd	= ((hdr->opcode & ISCSI_OP_IMMEDIATE) ? 1 : 0);
	cmd->init_task_tag	= hdr->itt;
	cmd->targ_xfer_tag	= 0xFFFFFFFF;
	cmd->cmd_sn		= be32_to_cpu(hdr->cmdsn);
	cmd->exp_stat_sn	= be32_to_cpu(hdr->exp_statsn);
	se_पंचांगr			= cmd->se_cmd.se_पंचांगr_req;
	पंचांगr_req			= cmd->पंचांगr_req;
	/*
	 * Locate the काष्ठा se_lun क्रम all TMRs not related to ERL=2 TASK_REASSIGN
	 */
	अगर (function != ISCSI_TM_FUNC_TASK_REASSIGN) अणु
		ret = transport_lookup_पंचांगr_lun(&cmd->se_cmd);
		अगर (ret < 0) अणु
			se_पंचांगr->response = ISCSI_TMF_RSP_NO_LUN;
			जाओ attach;
		पूर्ण
	पूर्ण

	चयन (function) अणु
	हाल ISCSI_TM_FUNC_ABORT_TASK:
		se_पंचांगr->response = iscsit_पंचांगr_पात_task(cmd, buf);
		अगर (se_पंचांगr->response)
			जाओ attach;
		अवरोध;
	हाल ISCSI_TM_FUNC_ABORT_TASK_SET:
	हाल ISCSI_TM_FUNC_CLEAR_ACA:
	हाल ISCSI_TM_FUNC_CLEAR_TASK_SET:
	हाल ISCSI_TM_FUNC_LOGICAL_UNIT_RESET:
		अवरोध;
	हाल ISCSI_TM_FUNC_TARGET_WARM_RESET:
		अगर (iscsit_पंचांगr_task_warm_reset(conn, पंचांगr_req, buf) < 0) अणु
			se_पंचांगr->response = ISCSI_TMF_RSP_AUTH_FAILED;
			जाओ attach;
		पूर्ण
		अवरोध;
	हाल ISCSI_TM_FUNC_TARGET_COLD_RESET:
		अगर (iscsit_पंचांगr_task_cold_reset(conn, पंचांगr_req, buf) < 0) अणु
			se_पंचांगr->response = ISCSI_TMF_RSP_AUTH_FAILED;
			जाओ attach;
		पूर्ण
		अवरोध;
	हाल ISCSI_TM_FUNC_TASK_REASSIGN:
		se_पंचांगr->response = iscsit_पंचांगr_task_reassign(cmd, buf);
		/*
		 * Perक्रमm sanity checks on the ExpDataSN only अगर the
		 * TASK_REASSIGN was successful.
		 */
		अगर (se_पंचांगr->response)
			अवरोध;

		अगर (iscsit_check_task_reassign_expdatasn(पंचांगr_req, conn) < 0)
			वापस iscsit_add_reject_cmd(cmd,
					ISCSI_REASON_BOOKMARK_INVALID, buf);
		अवरोध;
	शेष:
		pr_err("Unknown TMR function: 0x%02x, protocol"
			" error.\n", function);
		se_पंचांगr->response = ISCSI_TMF_RSP_NOT_SUPPORTED;
		जाओ attach;
	पूर्ण

	अगर ((function != ISCSI_TM_FUNC_TASK_REASSIGN) &&
	    (se_पंचांगr->response == ISCSI_TMF_RSP_COMPLETE))
		se_पंचांगr->call_transport = 1;
attach:
	spin_lock_bh(&conn->cmd_lock);
	list_add_tail(&cmd->i_conn_node, &conn->conn_cmd_list);
	spin_unlock_bh(&conn->cmd_lock);

	अगर (!(hdr->opcode & ISCSI_OP_IMMEDIATE)) अणु
		पूर्णांक cmdsn_ret = iscsit_sequence_cmd(conn, cmd, buf, hdr->cmdsn);
		अगर (cmdsn_ret == CMDSN_HIGHER_THAN_EXP) अणु
			out_of_order_cmdsn = 1;
		पूर्ण अन्यथा अगर (cmdsn_ret == CMDSN_LOWER_THAN_EXP) अणु
			target_put_sess_cmd(&cmd->se_cmd);
			वापस 0;
		पूर्ण अन्यथा अगर (cmdsn_ret == CMDSN_ERROR_CANNOT_RECOVER) अणु
			वापस -1;
		पूर्ण
	पूर्ण
	iscsit_ack_from_expstatsn(conn, be32_to_cpu(hdr->exp_statsn));

	अगर (out_of_order_cmdsn || !(hdr->opcode & ISCSI_OP_IMMEDIATE))
		वापस 0;
	/*
	 * Found the referenced task, send to transport क्रम processing.
	 */
	अगर (se_पंचांगr->call_transport)
		वापस transport_generic_handle_पंचांगr(&cmd->se_cmd);

	/*
	 * Could not find the referenced LUN, task, or Task Management
	 * command not authorized or supported.  Change state and
	 * let the tx_thपढ़ो send the response.
	 *
	 * For connection recovery, this is also the शेष action क्रम
	 * TMR TASK_REASSIGN.
	 */
	iscsit_add_cmd_to_response_queue(cmd, conn, cmd->i_state);
	target_put_sess_cmd(&cmd->se_cmd);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(iscsit_handle_task_mgt_cmd);

/* #warning FIXME: Support Text Command parameters besides SendTarमाला_लो */
पूर्णांक
iscsit_setup_text_cmd(काष्ठा iscsi_conn *conn, काष्ठा iscsi_cmd *cmd,
		      काष्ठा iscsi_text *hdr)
अणु
	u32 payload_length = ntoh24(hdr->dlength);

	अगर (payload_length > conn->conn_ops->MaxXmitDataSegmentLength) अणु
		pr_err("Unable to accept text parameter length: %u"
			"greater than MaxXmitDataSegmentLength %u.\n",
		       payload_length, conn->conn_ops->MaxXmitDataSegmentLength);
		वापस iscsit_reject_cmd(cmd, ISCSI_REASON_PROTOCOL_ERROR,
					 (अचिन्हित अक्षर *)hdr);
	पूर्ण

	अगर (!(hdr->flags & ISCSI_FLAG_CMD_FINAL) ||
	     (hdr->flags & ISCSI_FLAG_TEXT_CONTINUE)) अणु
		pr_err("Multi sequence text commands currently not supported\n");
		वापस iscsit_reject_cmd(cmd, ISCSI_REASON_CMD_NOT_SUPPORTED,
					(अचिन्हित अक्षर *)hdr);
	पूर्ण

	pr_debug("Got Text Request: ITT: 0x%08x, CmdSN: 0x%08x,"
		" ExpStatSN: 0x%08x, Length: %u\n", hdr->itt, hdr->cmdsn,
		hdr->exp_statsn, payload_length);

	cmd->iscsi_opcode	= ISCSI_OP_TEXT;
	cmd->i_state		= ISTATE_SEND_TEXTRSP;
	cmd->immediate_cmd	= ((hdr->opcode & ISCSI_OP_IMMEDIATE) ? 1 : 0);
	conn->sess->init_task_tag = cmd->init_task_tag  = hdr->itt;
	cmd->targ_xfer_tag	= 0xFFFFFFFF;
	cmd->cmd_sn		= be32_to_cpu(hdr->cmdsn);
	cmd->exp_stat_sn	= be32_to_cpu(hdr->exp_statsn);
	cmd->data_direction	= DMA_NONE;
	kमुक्त(cmd->text_in_ptr);
	cmd->text_in_ptr	= शून्य;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(iscsit_setup_text_cmd);

पूर्णांक
iscsit_process_text_cmd(काष्ठा iscsi_conn *conn, काष्ठा iscsi_cmd *cmd,
			काष्ठा iscsi_text *hdr)
अणु
	अचिन्हित अक्षर *text_in = cmd->text_in_ptr, *text_ptr;
	पूर्णांक cmdsn_ret;

	अगर (!text_in) अणु
		cmd->targ_xfer_tag = be32_to_cpu(hdr->ttt);
		अगर (cmd->targ_xfer_tag == 0xFFFFFFFF) अणु
			pr_err("Unable to locate text_in buffer for sendtargets"
			       " discovery\n");
			जाओ reject;
		पूर्ण
		जाओ empty_sendtarमाला_लो;
	पूर्ण
	अगर (म_भेदन("SendTargets=", text_in, 12) != 0) अणु
		pr_err("Received Text Data that is not"
			" SendTargets, cannot continue.\n");
		जाओ reject;
	पूर्ण
	/* '=' confirmed in म_भेदन */
	text_ptr = म_अक्षर(text_in, '=');
	BUG_ON(!text_ptr);
	अगर (!म_भेदन("=All", text_ptr, 5)) अणु
		cmd->cmd_flags |= ICF_SENDTARGETS_ALL;
	पूर्ण अन्यथा अगर (!म_भेदन("=iqn.", text_ptr, 5) ||
		   !म_भेदन("=eui.", text_ptr, 5)) अणु
		cmd->cmd_flags |= ICF_SENDTARGETS_SINGLE;
	पूर्ण अन्यथा अणु
		pr_err("Unable to locate valid SendTargets%s value\n",
		       text_ptr);
		जाओ reject;
	पूर्ण

	spin_lock_bh(&conn->cmd_lock);
	list_add_tail(&cmd->i_conn_node, &conn->conn_cmd_list);
	spin_unlock_bh(&conn->cmd_lock);

empty_sendtarमाला_लो:
	iscsit_ack_from_expstatsn(conn, be32_to_cpu(hdr->exp_statsn));

	अगर (!(hdr->opcode & ISCSI_OP_IMMEDIATE)) अणु
		cmdsn_ret = iscsit_sequence_cmd(conn, cmd,
				(अचिन्हित अक्षर *)hdr, hdr->cmdsn);
		अगर (cmdsn_ret == CMDSN_ERROR_CANNOT_RECOVER)
			वापस -1;

		वापस 0;
	पूर्ण

	वापस iscsit_execute_cmd(cmd, 0);

reject:
	वापस iscsit_reject_cmd(cmd, ISCSI_REASON_PROTOCOL_ERROR,
				 (अचिन्हित अक्षर *)hdr);
पूर्ण
EXPORT_SYMBOL(iscsit_process_text_cmd);

अटल पूर्णांक
iscsit_handle_text_cmd(काष्ठा iscsi_conn *conn, काष्ठा iscsi_cmd *cmd,
		       अचिन्हित अक्षर *buf)
अणु
	काष्ठा iscsi_text *hdr = (काष्ठा iscsi_text *)buf;
	अक्षर *text_in = शून्य;
	u32 payload_length = ntoh24(hdr->dlength);
	पूर्णांक rx_size, rc;

	rc = iscsit_setup_text_cmd(conn, cmd, hdr);
	अगर (rc < 0)
		वापस 0;

	rx_size = payload_length;
	अगर (payload_length) अणु
		u32 checksum = 0, data_crc = 0;
		u32 padding = 0;
		पूर्णांक niov = 0, rx_got;
		काष्ठा kvec iov[2];

		rx_size = ALIGN(payload_length, 4);
		text_in = kzalloc(rx_size, GFP_KERNEL);
		अगर (!text_in)
			जाओ reject;

		cmd->text_in_ptr = text_in;

		स_रखो(iov, 0, माप(iov));
		iov[niov].iov_base	= text_in;
		iov[niov++].iov_len	= rx_size;

		padding = rx_size - payload_length;
		अगर (padding)
			pr_debug("Receiving %u additional bytes"
					" for padding.\n", padding);
		अगर (conn->conn_ops->DataDigest) अणु
			iov[niov].iov_base	= &checksum;
			iov[niov++].iov_len	= ISCSI_CRC_LEN;
			rx_size += ISCSI_CRC_LEN;
		पूर्ण

		WARN_ON_ONCE(niov > ARRAY_SIZE(iov));
		rx_got = rx_data(conn, &iov[0], niov, rx_size);
		अगर (rx_got != rx_size)
			जाओ reject;

		अगर (conn->conn_ops->DataDigest) अणु
			iscsit_करो_crypto_hash_buf(conn->conn_rx_hash,
						  text_in, rx_size, 0, शून्य,
						  &data_crc);

			अगर (checksum != data_crc) अणु
				pr_err("Text data CRC32C DataDigest"
					" 0x%08x does not match computed"
					" 0x%08x\n", checksum, data_crc);
				अगर (!conn->sess->sess_ops->ErrorRecoveryLevel) अणु
					pr_err("Unable to recover from"
					" Text Data digest failure while in"
						" ERL=0.\n");
					जाओ reject;
				पूर्ण अन्यथा अणु
					/*
					 * Silently drop this PDU and let the
					 * initiator plug the CmdSN gap.
					 */
					pr_debug("Dropping Text"
					" Command CmdSN: 0x%08x due to"
					" DataCRC error.\n", hdr->cmdsn);
					kमुक्त(text_in);
					वापस 0;
				पूर्ण
			पूर्ण अन्यथा अणु
				pr_debug("Got CRC32C DataDigest"
					" 0x%08x for %u bytes of text data.\n",
						checksum, payload_length);
			पूर्ण
		पूर्ण
		text_in[payload_length - 1] = '\0';
		pr_debug("Successfully read %d bytes of text"
				" data.\n", payload_length);
	पूर्ण

	वापस iscsit_process_text_cmd(conn, cmd, hdr);

reject:
	kमुक्त(cmd->text_in_ptr);
	cmd->text_in_ptr = शून्य;
	वापस iscsit_reject_cmd(cmd, ISCSI_REASON_PROTOCOL_ERROR, buf);
पूर्ण

पूर्णांक iscsit_logout_बंदsession(काष्ठा iscsi_cmd *cmd, काष्ठा iscsi_conn *conn)
अणु
	काष्ठा iscsi_conn *conn_p;
	काष्ठा iscsi_session *sess = conn->sess;

	pr_debug("Received logout request CLOSESESSION on CID: %hu"
		" for SID: %u.\n", conn->cid, conn->sess->sid);

	atomic_set(&sess->session_logout, 1);
	atomic_set(&conn->conn_logout_हटाओ, 1);
	conn->conn_logout_reason = ISCSI_LOGOUT_REASON_CLOSE_SESSION;

	iscsit_inc_conn_usage_count(conn);
	iscsit_inc_session_usage_count(sess);

	spin_lock_bh(&sess->conn_lock);
	list_क्रम_each_entry(conn_p, &sess->sess_conn_list, conn_list) अणु
		अगर (conn_p->conn_state != TARG_CONN_STATE_LOGGED_IN)
			जारी;

		pr_debug("Moving to TARG_CONN_STATE_IN_LOGOUT.\n");
		conn_p->conn_state = TARG_CONN_STATE_IN_LOGOUT;
	पूर्ण
	spin_unlock_bh(&sess->conn_lock);

	iscsit_add_cmd_to_response_queue(cmd, conn, cmd->i_state);

	वापस 0;
पूर्ण

पूर्णांक iscsit_logout_बंदconnection(काष्ठा iscsi_cmd *cmd, काष्ठा iscsi_conn *conn)
अणु
	काष्ठा iscsi_conn *l_conn;
	काष्ठा iscsi_session *sess = conn->sess;

	pr_debug("Received logout request CLOSECONNECTION for CID:"
		" %hu on CID: %hu.\n", cmd->logout_cid, conn->cid);

	/*
	 * A Logout Request with a CLOSECONNECTION reason code क्रम a CID
	 * can arrive on a connection with a dअगरfering CID.
	 */
	अगर (conn->cid == cmd->logout_cid) अणु
		spin_lock_bh(&conn->state_lock);
		pr_debug("Moving to TARG_CONN_STATE_IN_LOGOUT.\n");
		conn->conn_state = TARG_CONN_STATE_IN_LOGOUT;

		atomic_set(&conn->conn_logout_हटाओ, 1);
		conn->conn_logout_reason = ISCSI_LOGOUT_REASON_CLOSE_CONNECTION;
		iscsit_inc_conn_usage_count(conn);

		spin_unlock_bh(&conn->state_lock);
	पूर्ण अन्यथा अणु
		/*
		 * Handle all dअगरferent cid CLOSECONNECTION requests in
		 * iscsit_logout_post_handler_dअगरfcid() as to give enough
		 * समय क्रम any non immediate command's CmdSN to be
		 * acknowledged on the connection in question.
		 *
		 * Here we simply make sure the CID is still around.
		 */
		l_conn = iscsit_get_conn_from_cid(sess,
				cmd->logout_cid);
		अगर (!l_conn) अणु
			cmd->logout_response = ISCSI_LOGOUT_CID_NOT_FOUND;
			iscsit_add_cmd_to_response_queue(cmd, conn,
					cmd->i_state);
			वापस 0;
		पूर्ण

		iscsit_dec_conn_usage_count(l_conn);
	पूर्ण

	iscsit_add_cmd_to_response_queue(cmd, conn, cmd->i_state);

	वापस 0;
पूर्ण

पूर्णांक iscsit_logout_हटाओconnक्रमrecovery(काष्ठा iscsi_cmd *cmd, काष्ठा iscsi_conn *conn)
अणु
	काष्ठा iscsi_session *sess = conn->sess;

	pr_debug("Received explicit REMOVECONNFORRECOVERY logout for"
		" CID: %hu on CID: %hu.\n", cmd->logout_cid, conn->cid);

	अगर (sess->sess_ops->ErrorRecoveryLevel != 2) अणु
		pr_err("Received Logout Request REMOVECONNFORRECOVERY"
			" while ERL!=2.\n");
		cmd->logout_response = ISCSI_LOGOUT_RECOVERY_UNSUPPORTED;
		iscsit_add_cmd_to_response_queue(cmd, conn, cmd->i_state);
		वापस 0;
	पूर्ण

	अगर (conn->cid == cmd->logout_cid) अणु
		pr_err("Received Logout Request REMOVECONNFORRECOVERY"
			" with CID: %hu on CID: %hu, implementation error.\n",
				cmd->logout_cid, conn->cid);
		cmd->logout_response = ISCSI_LOGOUT_CLEANUP_FAILED;
		iscsit_add_cmd_to_response_queue(cmd, conn, cmd->i_state);
		वापस 0;
	पूर्ण

	iscsit_add_cmd_to_response_queue(cmd, conn, cmd->i_state);

	वापस 0;
पूर्ण

पूर्णांक
iscsit_handle_logout_cmd(काष्ठा iscsi_conn *conn, काष्ठा iscsi_cmd *cmd,
			अचिन्हित अक्षर *buf)
अणु
	पूर्णांक cmdsn_ret, logout_हटाओ = 0;
	u8 reason_code = 0;
	काष्ठा iscsi_logout *hdr;
	काष्ठा iscsi_tiqn *tiqn = iscsit_snmp_get_tiqn(conn);

	hdr			= (काष्ठा iscsi_logout *) buf;
	reason_code		= (hdr->flags & 0x7f);

	अगर (tiqn) अणु
		spin_lock(&tiqn->logout_stats.lock);
		अगर (reason_code == ISCSI_LOGOUT_REASON_CLOSE_SESSION)
			tiqn->logout_stats.normal_logouts++;
		अन्यथा
			tiqn->logout_stats.abnormal_logouts++;
		spin_unlock(&tiqn->logout_stats.lock);
	पूर्ण

	pr_debug("Got Logout Request ITT: 0x%08x CmdSN: 0x%08x"
		" ExpStatSN: 0x%08x Reason: 0x%02x CID: %hu on CID: %hu\n",
		hdr->itt, hdr->cmdsn, hdr->exp_statsn, reason_code,
		hdr->cid, conn->cid);

	अगर (conn->conn_state != TARG_CONN_STATE_LOGGED_IN) अणु
		pr_err("Received logout request on connection that"
			" is not in logged in state, ignoring request.\n");
		iscsit_मुक्त_cmd(cmd, false);
		वापस 0;
	पूर्ण

	cmd->iscsi_opcode       = ISCSI_OP_LOGOUT;
	cmd->i_state            = ISTATE_SEND_LOGOUTRSP;
	cmd->immediate_cmd      = ((hdr->opcode & ISCSI_OP_IMMEDIATE) ? 1 : 0);
	conn->sess->init_task_tag = cmd->init_task_tag  = hdr->itt;
	cmd->targ_xfer_tag      = 0xFFFFFFFF;
	cmd->cmd_sn             = be32_to_cpu(hdr->cmdsn);
	cmd->exp_stat_sn        = be32_to_cpu(hdr->exp_statsn);
	cmd->logout_cid         = be16_to_cpu(hdr->cid);
	cmd->logout_reason      = reason_code;
	cmd->data_direction     = DMA_NONE;

	/*
	 * We need to sleep in these हालs (by वापसing 1) until the Logout
	 * Response माला_लो sent in the tx thपढ़ो.
	 */
	अगर ((reason_code == ISCSI_LOGOUT_REASON_CLOSE_SESSION) ||
	   ((reason_code == ISCSI_LOGOUT_REASON_CLOSE_CONNECTION) &&
	    be16_to_cpu(hdr->cid) == conn->cid))
		logout_हटाओ = 1;

	spin_lock_bh(&conn->cmd_lock);
	list_add_tail(&cmd->i_conn_node, &conn->conn_cmd_list);
	spin_unlock_bh(&conn->cmd_lock);

	अगर (reason_code != ISCSI_LOGOUT_REASON_RECOVERY)
		iscsit_ack_from_expstatsn(conn, be32_to_cpu(hdr->exp_statsn));

	/*
	 * Immediate commands are executed, well, immediately.
	 * Non-Immediate Logout Commands are executed in CmdSN order.
	 */
	अगर (cmd->immediate_cmd) अणु
		पूर्णांक ret = iscsit_execute_cmd(cmd, 0);

		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अणु
		cmdsn_ret = iscsit_sequence_cmd(conn, cmd, buf, hdr->cmdsn);
		अगर (cmdsn_ret == CMDSN_LOWER_THAN_EXP)
			logout_हटाओ = 0;
		अन्यथा अगर (cmdsn_ret == CMDSN_ERROR_CANNOT_RECOVER)
			वापस -1;
	पूर्ण

	वापस logout_हटाओ;
पूर्ण
EXPORT_SYMBOL(iscsit_handle_logout_cmd);

पूर्णांक iscsit_handle_snack(
	काष्ठा iscsi_conn *conn,
	अचिन्हित अक्षर *buf)
अणु
	काष्ठा iscsi_snack *hdr;

	hdr			= (काष्ठा iscsi_snack *) buf;
	hdr->flags		&= ~ISCSI_FLAG_CMD_FINAL;

	pr_debug("Got ISCSI_INIT_SNACK, ITT: 0x%08x, ExpStatSN:"
		" 0x%08x, Type: 0x%02x, BegRun: 0x%08x, RunLength: 0x%08x,"
		" CID: %hu\n", hdr->itt, hdr->exp_statsn, hdr->flags,
			hdr->begrun, hdr->runlength, conn->cid);

	अगर (!conn->sess->sess_ops->ErrorRecoveryLevel) अणु
		pr_err("Initiator sent SNACK request while in"
			" ErrorRecoveryLevel=0.\n");
		वापस iscsit_add_reject(conn, ISCSI_REASON_PROTOCOL_ERROR,
					 buf);
	पूर्ण
	/*
	 * SNACK_DATA and SNACK_R2T are both 0,  so check which function to
	 * call from inside iscsi_send_recovery_datain_or_r2t().
	 */
	चयन (hdr->flags & ISCSI_FLAG_SNACK_TYPE_MASK) अणु
	हाल 0:
		वापस iscsit_handle_recovery_datain_or_r2t(conn, buf,
			hdr->itt,
			be32_to_cpu(hdr->ttt),
			be32_to_cpu(hdr->begrun),
			be32_to_cpu(hdr->runlength));
	हाल ISCSI_FLAG_SNACK_TYPE_STATUS:
		वापस iscsit_handle_status_snack(conn, hdr->itt,
			be32_to_cpu(hdr->ttt),
			be32_to_cpu(hdr->begrun), be32_to_cpu(hdr->runlength));
	हाल ISCSI_FLAG_SNACK_TYPE_DATA_ACK:
		वापस iscsit_handle_data_ack(conn, be32_to_cpu(hdr->ttt),
			be32_to_cpu(hdr->begrun),
			be32_to_cpu(hdr->runlength));
	हाल ISCSI_FLAG_SNACK_TYPE_RDATA:
		/* FIXME: Support R-Data SNACK */
		pr_err("R-Data SNACK Not Supported.\n");
		वापस iscsit_add_reject(conn, ISCSI_REASON_PROTOCOL_ERROR,
					 buf);
	शेष:
		pr_err("Unknown SNACK type 0x%02x, protocol"
			" error.\n", hdr->flags & 0x0f);
		वापस iscsit_add_reject(conn, ISCSI_REASON_PROTOCOL_ERROR,
					 buf);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(iscsit_handle_snack);

अटल व्योम iscsit_rx_thपढ़ो_रुको_क्रम_tcp(काष्ठा iscsi_conn *conn)
अणु
	अगर ((conn->sock->sk->sk_shutकरोwn & SEND_SHUTDOWN) ||
	    (conn->sock->sk->sk_shutकरोwn & RCV_SHUTDOWN)) अणु
		रुको_क्रम_completion_पूर्णांकerruptible_समयout(
					&conn->rx_half_बंद_comp,
					ISCSI_RX_THREAD_TCP_TIMEOUT * HZ);
	पूर्ण
पूर्ण

अटल पूर्णांक iscsit_handle_immediate_data(
	काष्ठा iscsi_cmd *cmd,
	काष्ठा iscsi_scsi_req *hdr,
	u32 length)
अणु
	पूर्णांक iov_ret, rx_got = 0, rx_size = 0;
	u32 checksum, iov_count = 0, padding = 0;
	काष्ठा iscsi_conn *conn = cmd->conn;
	काष्ठा kvec *iov;
	व्योम *overflow_buf = शून्य;

	BUG_ON(cmd->ग_लिखो_data_करोne > cmd->se_cmd.data_length);
	rx_size = min(cmd->se_cmd.data_length - cmd->ग_लिखो_data_करोne, length);
	iov_ret = iscsit_map_iovec(cmd, cmd->iov_data,
				   cmd->orig_iov_data_count - 2,
				   cmd->ग_लिखो_data_करोne, rx_size);
	अगर (iov_ret < 0)
		वापस IMMEDIATE_DATA_CANNOT_RECOVER;

	iov_count = iov_ret;
	iov = &cmd->iov_data[0];
	अगर (rx_size < length) अणु
		/*
		 * Special हाल: length of immediate data exceeds the data
		 * buffer size derived from the CDB.
		 */
		overflow_buf = kदो_स्मृति(length - rx_size, GFP_KERNEL);
		अगर (!overflow_buf) अणु
			iscsit_unmap_iovec(cmd);
			वापस IMMEDIATE_DATA_CANNOT_RECOVER;
		पूर्ण
		cmd->overflow_buf = overflow_buf;
		iov[iov_count].iov_base = overflow_buf;
		iov[iov_count].iov_len = length - rx_size;
		iov_count++;
		rx_size = length;
	पूर्ण

	padding = ((-length) & 3);
	अगर (padding != 0) अणु
		iov[iov_count].iov_base	= cmd->pad_bytes;
		iov[iov_count++].iov_len = padding;
		rx_size += padding;
	पूर्ण

	अगर (conn->conn_ops->DataDigest) अणु
		iov[iov_count].iov_base		= &checksum;
		iov[iov_count++].iov_len	= ISCSI_CRC_LEN;
		rx_size += ISCSI_CRC_LEN;
	पूर्ण

	WARN_ON_ONCE(iov_count > cmd->orig_iov_data_count);
	rx_got = rx_data(conn, &cmd->iov_data[0], iov_count, rx_size);

	iscsit_unmap_iovec(cmd);

	अगर (rx_got != rx_size) अणु
		iscsit_rx_thपढ़ो_रुको_क्रम_tcp(conn);
		वापस IMMEDIATE_DATA_CANNOT_RECOVER;
	पूर्ण

	अगर (conn->conn_ops->DataDigest) अणु
		u32 data_crc;

		data_crc = iscsit_करो_crypto_hash_sg(conn->conn_rx_hash, cmd,
						    cmd->ग_लिखो_data_करोne, length, padding,
						    cmd->pad_bytes);

		अगर (checksum != data_crc) अणु
			pr_err("ImmediateData CRC32C DataDigest 0x%08x"
				" does not match computed 0x%08x\n", checksum,
				data_crc);

			अगर (!conn->sess->sess_ops->ErrorRecoveryLevel) अणु
				pr_err("Unable to recover from"
					" Immediate Data digest failure while"
					" in ERL=0.\n");
				iscsit_reject_cmd(cmd,
						ISCSI_REASON_DATA_DIGEST_ERROR,
						(अचिन्हित अक्षर *)hdr);
				वापस IMMEDIATE_DATA_CANNOT_RECOVER;
			पूर्ण अन्यथा अणु
				iscsit_reject_cmd(cmd,
						ISCSI_REASON_DATA_DIGEST_ERROR,
						(अचिन्हित अक्षर *)hdr);
				वापस IMMEDIATE_DATA_ERL1_CRC_FAILURE;
			पूर्ण
		पूर्ण अन्यथा अणु
			pr_debug("Got CRC32C DataDigest 0x%08x for"
				" %u bytes of Immediate Data\n", checksum,
				length);
		पूर्ण
	पूर्ण

	cmd->ग_लिखो_data_करोne += length;

	अगर (cmd->ग_लिखो_data_करोne == cmd->se_cmd.data_length) अणु
		spin_lock_bh(&cmd->istate_lock);
		cmd->cmd_flags |= ICF_GOT_LAST_DATAOUT;
		cmd->i_state = ISTATE_RECEIVED_LAST_DATAOUT;
		spin_unlock_bh(&cmd->istate_lock);
	पूर्ण

	वापस IMMEDIATE_DATA_NORMAL_OPERATION;
पूर्ण

/* #warning iscsi_build_conn_drop_async_message() only sends out on connections
	with active network पूर्णांकerface */
अटल व्योम iscsit_build_conn_drop_async_message(काष्ठा iscsi_conn *conn)
अणु
	काष्ठा iscsi_cmd *cmd;
	काष्ठा iscsi_conn *conn_p;
	bool found = false;

	lockdep_निश्चित_held(&conn->sess->conn_lock);

	/*
	 * Only send a Asynchronous Message on connections whos network
	 * पूर्णांकerface is still functional.
	 */
	list_क्रम_each_entry(conn_p, &conn->sess->sess_conn_list, conn_list) अणु
		अगर (conn_p->conn_state == TARG_CONN_STATE_LOGGED_IN) अणु
			iscsit_inc_conn_usage_count(conn_p);
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found)
		वापस;

	cmd = iscsit_allocate_cmd(conn_p, TASK_RUNNING);
	अगर (!cmd) अणु
		iscsit_dec_conn_usage_count(conn_p);
		वापस;
	पूर्ण

	cmd->logout_cid = conn->cid;
	cmd->iscsi_opcode = ISCSI_OP_ASYNC_EVENT;
	cmd->i_state = ISTATE_SEND_ASYNCMSG;

	spin_lock_bh(&conn_p->cmd_lock);
	list_add_tail(&cmd->i_conn_node, &conn_p->conn_cmd_list);
	spin_unlock_bh(&conn_p->cmd_lock);

	iscsit_add_cmd_to_response_queue(cmd, conn_p, cmd->i_state);
	iscsit_dec_conn_usage_count(conn_p);
पूर्ण

अटल पूर्णांक iscsit_send_conn_drop_async_message(
	काष्ठा iscsi_cmd *cmd,
	काष्ठा iscsi_conn *conn)
अणु
	काष्ठा iscsi_async *hdr;

	cmd->iscsi_opcode = ISCSI_OP_ASYNC_EVENT;

	hdr			= (काष्ठा iscsi_async *) cmd->pdu;
	hdr->opcode		= ISCSI_OP_ASYNC_EVENT;
	hdr->flags		= ISCSI_FLAG_CMD_FINAL;
	cmd->init_task_tag	= RESERVED_ITT;
	cmd->targ_xfer_tag	= 0xFFFFFFFF;
	put_unaligned_be64(0xFFFFFFFFFFFFFFFFULL, &hdr->rsvd4[0]);
	cmd->stat_sn		= conn->stat_sn++;
	hdr->statsn		= cpu_to_be32(cmd->stat_sn);
	hdr->exp_cmdsn		= cpu_to_be32(conn->sess->exp_cmd_sn);
	hdr->max_cmdsn		= cpu_to_be32((u32) atomic_पढ़ो(&conn->sess->max_cmd_sn));
	hdr->async_event	= ISCSI_ASYNC_MSG_DROPPING_CONNECTION;
	hdr->param1		= cpu_to_be16(cmd->logout_cid);
	hdr->param2		= cpu_to_be16(conn->sess->sess_ops->DefaultTime2Wait);
	hdr->param3		= cpu_to_be16(conn->sess->sess_ops->DefaultTime2Retain);

	pr_debug("Sending Connection Dropped Async Message StatSN:"
		" 0x%08x, for CID: %hu on CID: %hu\n", cmd->stat_sn,
			cmd->logout_cid, conn->cid);

	वापस conn->conn_transport->iscsit_xmit_pdu(conn, cmd, शून्य, शून्य, 0);
पूर्ण

अटल व्योम iscsit_tx_thपढ़ो_रुको_क्रम_tcp(काष्ठा iscsi_conn *conn)
अणु
	अगर ((conn->sock->sk->sk_shutकरोwn & SEND_SHUTDOWN) ||
	    (conn->sock->sk->sk_shutकरोwn & RCV_SHUTDOWN)) अणु
		रुको_क्रम_completion_पूर्णांकerruptible_समयout(
					&conn->tx_half_बंद_comp,
					ISCSI_TX_THREAD_TCP_TIMEOUT * HZ);
	पूर्ण
पूर्ण

व्योम
iscsit_build_datain_pdu(काष्ठा iscsi_cmd *cmd, काष्ठा iscsi_conn *conn,
			काष्ठा iscsi_datain *datain, काष्ठा iscsi_data_rsp *hdr,
			bool set_statsn)
अणु
	hdr->opcode		= ISCSI_OP_SCSI_DATA_IN;
	hdr->flags		= datain->flags;
	अगर (hdr->flags & ISCSI_FLAG_DATA_STATUS) अणु
		अगर (cmd->se_cmd.se_cmd_flags & SCF_OVERFLOW_BIT) अणु
			hdr->flags |= ISCSI_FLAG_DATA_OVERFLOW;
			hdr->residual_count = cpu_to_be32(cmd->se_cmd.residual_count);
		पूर्ण अन्यथा अगर (cmd->se_cmd.se_cmd_flags & SCF_UNDERFLOW_BIT) अणु
			hdr->flags |= ISCSI_FLAG_DATA_UNDERFLOW;
			hdr->residual_count = cpu_to_be32(cmd->se_cmd.residual_count);
		पूर्ण
	पूर्ण
	hton24(hdr->dlength, datain->length);
	अगर (hdr->flags & ISCSI_FLAG_DATA_ACK)
		पूर्णांक_to_scsilun(cmd->se_cmd.orig_fe_lun,
				(काष्ठा scsi_lun *)&hdr->lun);
	अन्यथा
		put_unaligned_le64(0xFFFFFFFFFFFFFFFFULL, &hdr->lun);

	hdr->itt		= cmd->init_task_tag;

	अगर (hdr->flags & ISCSI_FLAG_DATA_ACK)
		hdr->ttt		= cpu_to_be32(cmd->targ_xfer_tag);
	अन्यथा
		hdr->ttt		= cpu_to_be32(0xFFFFFFFF);
	अगर (set_statsn)
		hdr->statsn		= cpu_to_be32(cmd->stat_sn);
	अन्यथा
		hdr->statsn		= cpu_to_be32(0xFFFFFFFF);

	hdr->exp_cmdsn		= cpu_to_be32(conn->sess->exp_cmd_sn);
	hdr->max_cmdsn		= cpu_to_be32((u32) atomic_पढ़ो(&conn->sess->max_cmd_sn));
	hdr->datasn		= cpu_to_be32(datain->data_sn);
	hdr->offset		= cpu_to_be32(datain->offset);

	pr_debug("Built DataIN ITT: 0x%08x, StatSN: 0x%08x,"
		" DataSN: 0x%08x, Offset: %u, Length: %u, CID: %hu\n",
		cmd->init_task_tag, ntohl(hdr->statsn), ntohl(hdr->datasn),
		ntohl(hdr->offset), datain->length, conn->cid);
पूर्ण
EXPORT_SYMBOL(iscsit_build_datain_pdu);

अटल पूर्णांक iscsit_send_datain(काष्ठा iscsi_cmd *cmd, काष्ठा iscsi_conn *conn)
अणु
	काष्ठा iscsi_data_rsp *hdr = (काष्ठा iscsi_data_rsp *)&cmd->pdu[0];
	काष्ठा iscsi_datain datain;
	काष्ठा iscsi_datain_req *dr;
	पूर्णांक eodr = 0, ret;
	bool set_statsn = false;

	स_रखो(&datain, 0, माप(काष्ठा iscsi_datain));
	dr = iscsit_get_datain_values(cmd, &datain);
	अगर (!dr) अणु
		pr_err("iscsit_get_datain_values failed for ITT: 0x%08x\n",
				cmd->init_task_tag);
		वापस -1;
	पूर्ण
	/*
	 * Be paranoid and द्विगुन check the logic क्रम now.
	 */
	अगर ((datain.offset + datain.length) > cmd->se_cmd.data_length) अणु
		pr_err("Command ITT: 0x%08x, datain.offset: %u and"
			" datain.length: %u exceeds cmd->data_length: %u\n",
			cmd->init_task_tag, datain.offset, datain.length,
			cmd->se_cmd.data_length);
		वापस -1;
	पूर्ण

	atomic_दीर्घ_add(datain.length, &conn->sess->tx_data_octets);
	/*
	 * Special हाल क्रम successfully execution w/ both DATAIN
	 * and Sense Data.
	 */
	अगर ((datain.flags & ISCSI_FLAG_DATA_STATUS) &&
	    (cmd->se_cmd.se_cmd_flags & SCF_TRANSPORT_TASK_SENSE))
		datain.flags &= ~ISCSI_FLAG_DATA_STATUS;
	अन्यथा अणु
		अगर ((dr->dr_complete == DATAIN_COMPLETE_NORMAL) ||
		    (dr->dr_complete == DATAIN_COMPLETE_CONNECTION_RECOVERY)) अणु
			iscsit_increment_maxcmdsn(cmd, conn->sess);
			cmd->stat_sn = conn->stat_sn++;
			set_statsn = true;
		पूर्ण अन्यथा अगर (dr->dr_complete ==
			   DATAIN_COMPLETE_WITHIN_COMMAND_RECOVERY)
			set_statsn = true;
	पूर्ण

	iscsit_build_datain_pdu(cmd, conn, &datain, hdr, set_statsn);

	ret = conn->conn_transport->iscsit_xmit_pdu(conn, cmd, dr, &datain, 0);
	अगर (ret < 0)
		वापस ret;

	अगर (dr->dr_complete) अणु
		eodr = (cmd->se_cmd.se_cmd_flags & SCF_TRANSPORT_TASK_SENSE) ?
				2 : 1;
		iscsit_मुक्त_datain_req(cmd, dr);
	पूर्ण

	वापस eodr;
पूर्ण

पूर्णांक
iscsit_build_logout_rsp(काष्ठा iscsi_cmd *cmd, काष्ठा iscsi_conn *conn,
			काष्ठा iscsi_logout_rsp *hdr)
अणु
	काष्ठा iscsi_conn *logout_conn = शून्य;
	काष्ठा iscsi_conn_recovery *cr = शून्य;
	काष्ठा iscsi_session *sess = conn->sess;
	/*
	 * The actual shutting करोwn of Sessions and/or Connections
	 * क्रम CLOSESESSION and CLOSECONNECTION Logout Requests
	 * is करोne in scsi_logout_post_handler().
	 */
	चयन (cmd->logout_reason) अणु
	हाल ISCSI_LOGOUT_REASON_CLOSE_SESSION:
		pr_debug("iSCSI session logout successful, setting"
			" logout response to ISCSI_LOGOUT_SUCCESS.\n");
		cmd->logout_response = ISCSI_LOGOUT_SUCCESS;
		अवरोध;
	हाल ISCSI_LOGOUT_REASON_CLOSE_CONNECTION:
		अगर (cmd->logout_response == ISCSI_LOGOUT_CID_NOT_FOUND)
			अवरोध;
		/*
		 * For CLOSECONNECTION logout requests carrying
		 * a matching logout CID -> local CID, the reference
		 * क्रम the local CID will have been incremented in
		 * iscsi_logout_बंदconnection().
		 *
		 * For CLOSECONNECTION logout requests carrying
		 * a dअगरferent CID than the connection it arrived
		 * on, the connection responding to cmd->logout_cid
		 * is stopped in iscsit_logout_post_handler_dअगरfcid().
		 */

		pr_debug("iSCSI CID: %hu logout on CID: %hu"
			" successful.\n", cmd->logout_cid, conn->cid);
		cmd->logout_response = ISCSI_LOGOUT_SUCCESS;
		अवरोध;
	हाल ISCSI_LOGOUT_REASON_RECOVERY:
		अगर ((cmd->logout_response == ISCSI_LOGOUT_RECOVERY_UNSUPPORTED) ||
		    (cmd->logout_response == ISCSI_LOGOUT_CLEANUP_FAILED))
			अवरोध;
		/*
		 * If the connection is still active from our poपूर्णांक of view
		 * क्रमce connection recovery to occur.
		 */
		logout_conn = iscsit_get_conn_from_cid_rcfr(sess,
				cmd->logout_cid);
		अगर (logout_conn) अणु
			iscsit_connection_reinstatement_rcfr(logout_conn);
			iscsit_dec_conn_usage_count(logout_conn);
		पूर्ण

		cr = iscsit_get_inactive_connection_recovery_entry(
				conn->sess, cmd->logout_cid);
		अगर (!cr) अणु
			pr_err("Unable to locate CID: %hu for"
			" REMOVECONNFORRECOVERY Logout Request.\n",
				cmd->logout_cid);
			cmd->logout_response = ISCSI_LOGOUT_CID_NOT_FOUND;
			अवरोध;
		पूर्ण

		iscsit_discard_cr_cmds_by_expstatsn(cr, cmd->exp_stat_sn);

		pr_debug("iSCSI REMOVECONNFORRECOVERY logout"
			" for recovery for CID: %hu on CID: %hu successful.\n",
				cmd->logout_cid, conn->cid);
		cmd->logout_response = ISCSI_LOGOUT_SUCCESS;
		अवरोध;
	शेष:
		pr_err("Unknown cmd->logout_reason: 0x%02x\n",
				cmd->logout_reason);
		वापस -1;
	पूर्ण

	hdr->opcode		= ISCSI_OP_LOGOUT_RSP;
	hdr->flags		|= ISCSI_FLAG_CMD_FINAL;
	hdr->response		= cmd->logout_response;
	hdr->itt		= cmd->init_task_tag;
	cmd->stat_sn		= conn->stat_sn++;
	hdr->statsn		= cpu_to_be32(cmd->stat_sn);

	iscsit_increment_maxcmdsn(cmd, conn->sess);
	hdr->exp_cmdsn		= cpu_to_be32(conn->sess->exp_cmd_sn);
	hdr->max_cmdsn		= cpu_to_be32((u32) atomic_पढ़ो(&conn->sess->max_cmd_sn));

	pr_debug("Built Logout Response ITT: 0x%08x StatSN:"
		" 0x%08x Response: 0x%02x CID: %hu on CID: %hu\n",
		cmd->init_task_tag, cmd->stat_sn, hdr->response,
		cmd->logout_cid, conn->cid);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(iscsit_build_logout_rsp);

अटल पूर्णांक
iscsit_send_logout(काष्ठा iscsi_cmd *cmd, काष्ठा iscsi_conn *conn)
अणु
	पूर्णांक rc;

	rc = iscsit_build_logout_rsp(cmd, conn,
			(काष्ठा iscsi_logout_rsp *)&cmd->pdu[0]);
	अगर (rc < 0)
		वापस rc;

	वापस conn->conn_transport->iscsit_xmit_pdu(conn, cmd, शून्य, शून्य, 0);
पूर्ण

व्योम
iscsit_build_nopin_rsp(काष्ठा iscsi_cmd *cmd, काष्ठा iscsi_conn *conn,
		       काष्ठा iscsi_nopin *hdr, bool nopout_response)
अणु
	hdr->opcode		= ISCSI_OP_NOOP_IN;
	hdr->flags		|= ISCSI_FLAG_CMD_FINAL;
        hton24(hdr->dlength, cmd->buf_ptr_size);
	अगर (nopout_response)
		put_unaligned_le64(0xFFFFFFFFFFFFFFFFULL, &hdr->lun);
	hdr->itt		= cmd->init_task_tag;
	hdr->ttt		= cpu_to_be32(cmd->targ_xfer_tag);
	cmd->stat_sn		= (nopout_response) ? conn->stat_sn++ :
				  conn->stat_sn;
	hdr->statsn		= cpu_to_be32(cmd->stat_sn);

	अगर (nopout_response)
		iscsit_increment_maxcmdsn(cmd, conn->sess);

	hdr->exp_cmdsn		= cpu_to_be32(conn->sess->exp_cmd_sn);
	hdr->max_cmdsn		= cpu_to_be32((u32) atomic_पढ़ो(&conn->sess->max_cmd_sn));

	pr_debug("Built NOPIN %s Response ITT: 0x%08x, TTT: 0x%08x,"
		" StatSN: 0x%08x, Length %u\n", (nopout_response) ?
		"Solicited" : "Unsolicited", cmd->init_task_tag,
		cmd->targ_xfer_tag, cmd->stat_sn, cmd->buf_ptr_size);
पूर्ण
EXPORT_SYMBOL(iscsit_build_nopin_rsp);

/*
 *	Unsolicited NOPIN, either requesting a response or not.
 */
अटल पूर्णांक iscsit_send_unsolicited_nopin(
	काष्ठा iscsi_cmd *cmd,
	काष्ठा iscsi_conn *conn,
	पूर्णांक want_response)
अणु
	काष्ठा iscsi_nopin *hdr = (काष्ठा iscsi_nopin *)&cmd->pdu[0];
	पूर्णांक ret;

	iscsit_build_nopin_rsp(cmd, conn, hdr, false);

	pr_debug("Sending Unsolicited NOPIN TTT: 0x%08x StatSN:"
		" 0x%08x CID: %hu\n", hdr->ttt, cmd->stat_sn, conn->cid);

	ret = conn->conn_transport->iscsit_xmit_pdu(conn, cmd, शून्य, शून्य, 0);
	अगर (ret < 0)
		वापस ret;

	spin_lock_bh(&cmd->istate_lock);
	cmd->i_state = want_response ?
		ISTATE_SENT_NOPIN_WANT_RESPONSE : ISTATE_SENT_STATUS;
	spin_unlock_bh(&cmd->istate_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक
iscsit_send_nopin(काष्ठा iscsi_cmd *cmd, काष्ठा iscsi_conn *conn)
अणु
	काष्ठा iscsi_nopin *hdr = (काष्ठा iscsi_nopin *)&cmd->pdu[0];

	iscsit_build_nopin_rsp(cmd, conn, hdr, true);

	/*
	 * NOPOUT Ping Data is attached to काष्ठा iscsi_cmd->buf_ptr.
	 * NOPOUT DataSegmentLength is at काष्ठा iscsi_cmd->buf_ptr_size.
	 */
	pr_debug("Echoing back %u bytes of ping data.\n", cmd->buf_ptr_size);

	वापस conn->conn_transport->iscsit_xmit_pdu(conn, cmd, शून्य,
						     cmd->buf_ptr,
						     cmd->buf_ptr_size);
पूर्ण

अटल पूर्णांक iscsit_send_r2t(
	काष्ठा iscsi_cmd *cmd,
	काष्ठा iscsi_conn *conn)
अणु
	काष्ठा iscsi_r2t *r2t;
	काष्ठा iscsi_r2t_rsp *hdr;
	पूर्णांक ret;

	r2t = iscsit_get_r2t_from_list(cmd);
	अगर (!r2t)
		वापस -1;

	hdr			= (काष्ठा iscsi_r2t_rsp *) cmd->pdu;
	स_रखो(hdr, 0, ISCSI_HDR_LEN);
	hdr->opcode		= ISCSI_OP_R2T;
	hdr->flags		|= ISCSI_FLAG_CMD_FINAL;
	पूर्णांक_to_scsilun(cmd->se_cmd.orig_fe_lun,
			(काष्ठा scsi_lun *)&hdr->lun);
	hdr->itt		= cmd->init_task_tag;
	अगर (conn->conn_transport->iscsit_get_r2t_ttt)
		conn->conn_transport->iscsit_get_r2t_ttt(conn, cmd, r2t);
	अन्यथा
		r2t->targ_xfer_tag = session_get_next_ttt(conn->sess);
	hdr->ttt		= cpu_to_be32(r2t->targ_xfer_tag);
	hdr->statsn		= cpu_to_be32(conn->stat_sn);
	hdr->exp_cmdsn		= cpu_to_be32(conn->sess->exp_cmd_sn);
	hdr->max_cmdsn		= cpu_to_be32((u32) atomic_पढ़ो(&conn->sess->max_cmd_sn));
	hdr->r2tsn		= cpu_to_be32(r2t->r2t_sn);
	hdr->data_offset	= cpu_to_be32(r2t->offset);
	hdr->data_length	= cpu_to_be32(r2t->xfer_len);

	pr_debug("Built %sR2T, ITT: 0x%08x, TTT: 0x%08x, StatSN:"
		" 0x%08x, R2TSN: 0x%08x, Offset: %u, DDTL: %u, CID: %hu\n",
		(!r2t->recovery_r2t) ? "" : "Recovery ", cmd->init_task_tag,
		r2t->targ_xfer_tag, ntohl(hdr->statsn), r2t->r2t_sn,
			r2t->offset, r2t->xfer_len, conn->cid);

	spin_lock_bh(&cmd->r2t_lock);
	r2t->sent_r2t = 1;
	spin_unlock_bh(&cmd->r2t_lock);

	ret = conn->conn_transport->iscsit_xmit_pdu(conn, cmd, शून्य, शून्य, 0);
	अगर (ret < 0) अणु
		वापस ret;
	पूर्ण

	spin_lock_bh(&cmd->dataout_समयout_lock);
	iscsit_start_dataout_समयr(cmd, conn);
	spin_unlock_bh(&cmd->dataout_समयout_lock);

	वापस 0;
पूर्ण

/*
 *	@recovery: If called from iscsi_task_reassign_complete_ग_लिखो() क्रम
 *		connection recovery.
 */
पूर्णांक iscsit_build_r2ts_क्रम_cmd(
	काष्ठा iscsi_conn *conn,
	काष्ठा iscsi_cmd *cmd,
	bool recovery)
अणु
	पूर्णांक first_r2t = 1;
	u32 offset = 0, xfer_len = 0;

	spin_lock_bh(&cmd->r2t_lock);
	अगर (cmd->cmd_flags & ICF_SENT_LAST_R2T) अणु
		spin_unlock_bh(&cmd->r2t_lock);
		वापस 0;
	पूर्ण

	अगर (conn->sess->sess_ops->DataSequenceInOrder &&
	    !recovery)
		cmd->r2t_offset = max(cmd->r2t_offset, cmd->ग_लिखो_data_करोne);

	जबतक (cmd->outstanding_r2ts < conn->sess->sess_ops->MaxOutstandingR2T) अणु
		अगर (conn->sess->sess_ops->DataSequenceInOrder) अणु
			offset = cmd->r2t_offset;

			अगर (first_r2t && recovery) अणु
				पूर्णांक new_data_end = offset +
					conn->sess->sess_ops->MaxBurstLength -
					cmd->next_burst_len;

				अगर (new_data_end > cmd->se_cmd.data_length)
					xfer_len = cmd->se_cmd.data_length - offset;
				अन्यथा
					xfer_len =
						conn->sess->sess_ops->MaxBurstLength -
						cmd->next_burst_len;
			पूर्ण अन्यथा अणु
				पूर्णांक new_data_end = offset +
					conn->sess->sess_ops->MaxBurstLength;

				अगर (new_data_end > cmd->se_cmd.data_length)
					xfer_len = cmd->se_cmd.data_length - offset;
				अन्यथा
					xfer_len = conn->sess->sess_ops->MaxBurstLength;
			पूर्ण

			अगर ((s32)xfer_len < 0) अणु
				cmd->cmd_flags |= ICF_SENT_LAST_R2T;
				अवरोध;
			पूर्ण

			cmd->r2t_offset += xfer_len;

			अगर (cmd->r2t_offset == cmd->se_cmd.data_length)
				cmd->cmd_flags |= ICF_SENT_LAST_R2T;
		पूर्ण अन्यथा अणु
			काष्ठा iscsi_seq *seq;

			seq = iscsit_get_seq_holder_क्रम_r2t(cmd);
			अगर (!seq) अणु
				spin_unlock_bh(&cmd->r2t_lock);
				वापस -1;
			पूर्ण

			offset = seq->offset;
			xfer_len = seq->xfer_len;

			अगर (cmd->seq_send_order == cmd->seq_count)
				cmd->cmd_flags |= ICF_SENT_LAST_R2T;
		पूर्ण
		cmd->outstanding_r2ts++;
		first_r2t = 0;

		अगर (iscsit_add_r2t_to_list(cmd, offset, xfer_len, 0, 0) < 0) अणु
			spin_unlock_bh(&cmd->r2t_lock);
			वापस -1;
		पूर्ण

		अगर (cmd->cmd_flags & ICF_SENT_LAST_R2T)
			अवरोध;
	पूर्ण
	spin_unlock_bh(&cmd->r2t_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(iscsit_build_r2ts_क्रम_cmd);

व्योम iscsit_build_rsp_pdu(काष्ठा iscsi_cmd *cmd, काष्ठा iscsi_conn *conn,
			bool inc_stat_sn, काष्ठा iscsi_scsi_rsp *hdr)
अणु
	अगर (inc_stat_sn)
		cmd->stat_sn = conn->stat_sn++;

	atomic_दीर्घ_inc(&conn->sess->rsp_pdus);

	स_रखो(hdr, 0, ISCSI_HDR_LEN);
	hdr->opcode		= ISCSI_OP_SCSI_CMD_RSP;
	hdr->flags		|= ISCSI_FLAG_CMD_FINAL;
	अगर (cmd->se_cmd.se_cmd_flags & SCF_OVERFLOW_BIT) अणु
		hdr->flags |= ISCSI_FLAG_CMD_OVERFLOW;
		hdr->residual_count = cpu_to_be32(cmd->se_cmd.residual_count);
	पूर्ण अन्यथा अगर (cmd->se_cmd.se_cmd_flags & SCF_UNDERFLOW_BIT) अणु
		hdr->flags |= ISCSI_FLAG_CMD_UNDERFLOW;
		hdr->residual_count = cpu_to_be32(cmd->se_cmd.residual_count);
	पूर्ण
	hdr->response		= cmd->iscsi_response;
	hdr->cmd_status		= cmd->se_cmd.scsi_status;
	hdr->itt		= cmd->init_task_tag;
	hdr->statsn		= cpu_to_be32(cmd->stat_sn);

	iscsit_increment_maxcmdsn(cmd, conn->sess);
	hdr->exp_cmdsn		= cpu_to_be32(conn->sess->exp_cmd_sn);
	hdr->max_cmdsn		= cpu_to_be32((u32) atomic_पढ़ो(&conn->sess->max_cmd_sn));

	pr_debug("Built SCSI Response, ITT: 0x%08x, StatSN: 0x%08x,"
		" Response: 0x%02x, SAM Status: 0x%02x, CID: %hu\n",
		cmd->init_task_tag, cmd->stat_sn, cmd->se_cmd.scsi_status,
		cmd->se_cmd.scsi_status, conn->cid);
पूर्ण
EXPORT_SYMBOL(iscsit_build_rsp_pdu);

अटल पूर्णांक iscsit_send_response(काष्ठा iscsi_cmd *cmd, काष्ठा iscsi_conn *conn)
अणु
	काष्ठा iscsi_scsi_rsp *hdr = (काष्ठा iscsi_scsi_rsp *)&cmd->pdu[0];
	bool inc_stat_sn = (cmd->i_state == ISTATE_SEND_STATUS);
	व्योम *data_buf = शून्य;
	u32 padding = 0, data_buf_len = 0;

	iscsit_build_rsp_pdu(cmd, conn, inc_stat_sn, hdr);

	/*
	 * Attach SENSE DATA payload to iSCSI Response PDU
	 */
	अगर (cmd->se_cmd.sense_buffer &&
	   ((cmd->se_cmd.se_cmd_flags & SCF_TRANSPORT_TASK_SENSE) ||
	    (cmd->se_cmd.se_cmd_flags & SCF_EMULATED_TASK_SENSE))) अणु
		put_unaligned_be16(cmd->se_cmd.scsi_sense_length, cmd->sense_buffer);
		cmd->se_cmd.scsi_sense_length += माप (__be16);

		padding		= -(cmd->se_cmd.scsi_sense_length) & 3;
		hton24(hdr->dlength, (u32)cmd->se_cmd.scsi_sense_length);
		data_buf = cmd->sense_buffer;
		data_buf_len = cmd->se_cmd.scsi_sense_length + padding;

		अगर (padding) अणु
			स_रखो(cmd->sense_buffer +
				cmd->se_cmd.scsi_sense_length, 0, padding);
			pr_debug("Adding %u bytes of padding to"
				" SENSE.\n", padding);
		पूर्ण

		pr_debug("Attaching SENSE DATA: %u bytes to iSCSI"
				" Response PDU\n",
				cmd->se_cmd.scsi_sense_length);
	पूर्ण

	वापस conn->conn_transport->iscsit_xmit_pdu(conn, cmd, शून्य, data_buf,
						     data_buf_len);
पूर्ण

अटल u8 iscsit_convert_tcm_पंचांगr_rsp(काष्ठा se_पंचांगr_req *se_पंचांगr)
अणु
	चयन (se_पंचांगr->response) अणु
	हाल TMR_FUNCTION_COMPLETE:
		वापस ISCSI_TMF_RSP_COMPLETE;
	हाल TMR_TASK_DOES_NOT_EXIST:
		वापस ISCSI_TMF_RSP_NO_TASK;
	हाल TMR_LUN_DOES_NOT_EXIST:
		वापस ISCSI_TMF_RSP_NO_LUN;
	हाल TMR_TASK_MGMT_FUNCTION_NOT_SUPPORTED:
		वापस ISCSI_TMF_RSP_NOT_SUPPORTED;
	हाल TMR_FUNCTION_REJECTED:
	शेष:
		वापस ISCSI_TMF_RSP_REJECTED;
	पूर्ण
पूर्ण

व्योम
iscsit_build_task_mgt_rsp(काष्ठा iscsi_cmd *cmd, काष्ठा iscsi_conn *conn,
			  काष्ठा iscsi_पंचांग_rsp *hdr)
अणु
	काष्ठा se_पंचांगr_req *se_पंचांगr = cmd->se_cmd.se_पंचांगr_req;

	hdr->opcode		= ISCSI_OP_SCSI_TMFUNC_RSP;
	hdr->flags		= ISCSI_FLAG_CMD_FINAL;
	hdr->response		= iscsit_convert_tcm_पंचांगr_rsp(se_पंचांगr);
	hdr->itt		= cmd->init_task_tag;
	cmd->stat_sn		= conn->stat_sn++;
	hdr->statsn		= cpu_to_be32(cmd->stat_sn);

	iscsit_increment_maxcmdsn(cmd, conn->sess);
	hdr->exp_cmdsn		= cpu_to_be32(conn->sess->exp_cmd_sn);
	hdr->max_cmdsn		= cpu_to_be32((u32) atomic_पढ़ो(&conn->sess->max_cmd_sn));

	pr_debug("Built Task Management Response ITT: 0x%08x,"
		" StatSN: 0x%08x, Response: 0x%02x, CID: %hu\n",
		cmd->init_task_tag, cmd->stat_sn, hdr->response, conn->cid);
पूर्ण
EXPORT_SYMBOL(iscsit_build_task_mgt_rsp);

अटल पूर्णांक
iscsit_send_task_mgt_rsp(काष्ठा iscsi_cmd *cmd, काष्ठा iscsi_conn *conn)
अणु
	काष्ठा iscsi_पंचांग_rsp *hdr = (काष्ठा iscsi_पंचांग_rsp *)&cmd->pdu[0];

	iscsit_build_task_mgt_rsp(cmd, conn, hdr);

	वापस conn->conn_transport->iscsit_xmit_pdu(conn, cmd, शून्य, शून्य, 0);
पूर्ण

#घोषणा SENDTARGETS_BUF_LIMIT 32768U

अटल पूर्णांक
iscsit_build_sendtarमाला_लो_response(काष्ठा iscsi_cmd *cmd,
				  क्रमागत iscsit_transport_type network_transport,
				  पूर्णांक skip_bytes, bool *completed)
अणु
	अक्षर *payload = शून्य;
	काष्ठा iscsi_conn *conn = cmd->conn;
	काष्ठा iscsi_portal_group *tpg;
	काष्ठा iscsi_tiqn *tiqn;
	काष्ठा iscsi_tpg_np *tpg_np;
	पूर्णांक buffer_len, end_of_buf = 0, len = 0, payload_len = 0;
	पूर्णांक target_name_prपूर्णांकed;
	अचिन्हित अक्षर buf[ISCSI_IQN_LEN+12]; /* iqn + "TargetName=" + \0 */
	अचिन्हित अक्षर *text_in = cmd->text_in_ptr, *text_ptr = शून्य;
	bool active;

	buffer_len = min(conn->conn_ops->MaxRecvDataSegmentLength,
			 SENDTARGETS_BUF_LIMIT);

	payload = kzalloc(buffer_len, GFP_KERNEL);
	अगर (!payload)
		वापस -ENOMEM;

	/*
	 * Locate poपूर्णांकer to iqn./eui. string क्रम ICF_SENDTARGETS_SINGLE
	 * explicit हाल..
	 */
	अगर (cmd->cmd_flags & ICF_SENDTARGETS_SINGLE) अणु
		text_ptr = म_अक्षर(text_in, '=');
		अगर (!text_ptr) अणु
			pr_err("Unable to locate '=' string in text_in:"
			       " %s\n", text_in);
			kमुक्त(payload);
			वापस -EINVAL;
		पूर्ण
		/*
		 * Skip over '=' अक्षरacter..
		 */
		text_ptr += 1;
	पूर्ण

	spin_lock(&tiqn_lock);
	list_क्रम_each_entry(tiqn, &g_tiqn_list, tiqn_list) अणु
		अगर ((cmd->cmd_flags & ICF_SENDTARGETS_SINGLE) &&
		     म_भेद(tiqn->tiqn, text_ptr)) अणु
			जारी;
		पूर्ण

		target_name_prपूर्णांकed = 0;

		spin_lock(&tiqn->tiqn_tpg_lock);
		list_क्रम_each_entry(tpg, &tiqn->tiqn_tpg_list, tpg_list) अणु

			/* If demo_mode_discovery=0 and generate_node_acls=0
			 * (demo mode dislabed) करो not वापस
			 * TargetName+TargetAddress unless a NodeACL exists.
			 */

			अगर ((tpg->tpg_attrib.generate_node_acls == 0) &&
			    (tpg->tpg_attrib.demo_mode_discovery == 0) &&
			    (!target_tpg_has_node_acl(&tpg->tpg_se_tpg,
				cmd->conn->sess->sess_ops->InitiatorName))) अणु
				जारी;
			पूर्ण

			spin_lock(&tpg->tpg_state_lock);
			active = (tpg->tpg_state == TPG_STATE_ACTIVE);
			spin_unlock(&tpg->tpg_state_lock);

			अगर (!active && tpg->tpg_attrib.tpg_enabled_sendtarमाला_लो)
				जारी;

			spin_lock(&tpg->tpg_np_lock);
			list_क्रम_each_entry(tpg_np, &tpg->tpg_gnp_list,
						tpg_np_list) अणु
				काष्ठा iscsi_np *np = tpg_np->tpg_np;
				काष्ठा sockaddr_storage *sockaddr;

				अगर (np->np_network_transport != network_transport)
					जारी;

				अगर (!target_name_prपूर्णांकed) अणु
					len = प्र_लिखो(buf, "TargetName=%s",
						      tiqn->tiqn);
					len += 1;

					अगर ((len + payload_len) > buffer_len) अणु
						spin_unlock(&tpg->tpg_np_lock);
						spin_unlock(&tiqn->tiqn_tpg_lock);
						end_of_buf = 1;
						जाओ eob;
					पूर्ण

					अगर (skip_bytes && len <= skip_bytes) अणु
						skip_bytes -= len;
					पूर्ण अन्यथा अणु
						स_नकल(payload + payload_len, buf, len);
						payload_len += len;
						target_name_prपूर्णांकed = 1;
						अगर (len > skip_bytes)
							skip_bytes = 0;
					पूर्ण
				पूर्ण

				अगर (inet_addr_is_any((काष्ठा sockaddr *)&np->np_sockaddr))
					sockaddr = &conn->local_sockaddr;
				अन्यथा
					sockaddr = &np->np_sockaddr;

				len = प्र_लिखो(buf, "TargetAddress="
					      "%pISpc,%hu",
					      sockaddr,
					      tpg->tpgt);
				len += 1;

				अगर ((len + payload_len) > buffer_len) अणु
					spin_unlock(&tpg->tpg_np_lock);
					spin_unlock(&tiqn->tiqn_tpg_lock);
					end_of_buf = 1;
					जाओ eob;
				पूर्ण

				अगर (skip_bytes && len <= skip_bytes) अणु
					skip_bytes -= len;
				पूर्ण अन्यथा अणु
					स_नकल(payload + payload_len, buf, len);
					payload_len += len;
					अगर (len > skip_bytes)
						skip_bytes = 0;
				पूर्ण
			पूर्ण
			spin_unlock(&tpg->tpg_np_lock);
		पूर्ण
		spin_unlock(&tiqn->tiqn_tpg_lock);
eob:
		अगर (end_of_buf) अणु
			*completed = false;
			अवरोध;
		पूर्ण

		अगर (cmd->cmd_flags & ICF_SENDTARGETS_SINGLE)
			अवरोध;
	पूर्ण
	spin_unlock(&tiqn_lock);

	cmd->buf_ptr = payload;

	वापस payload_len;
पूर्ण

पूर्णांक
iscsit_build_text_rsp(काष्ठा iscsi_cmd *cmd, काष्ठा iscsi_conn *conn,
		      काष्ठा iscsi_text_rsp *hdr,
		      क्रमागत iscsit_transport_type network_transport)
अणु
	पूर्णांक text_length, padding;
	bool completed = true;

	text_length = iscsit_build_sendtarमाला_लो_response(cmd, network_transport,
							cmd->पढ़ो_data_करोne,
							&completed);
	अगर (text_length < 0)
		वापस text_length;

	अगर (completed) अणु
		hdr->flags = ISCSI_FLAG_CMD_FINAL;
	पूर्ण अन्यथा अणु
		hdr->flags = ISCSI_FLAG_TEXT_CONTINUE;
		cmd->पढ़ो_data_करोne += text_length;
		अगर (cmd->targ_xfer_tag == 0xFFFFFFFF)
			cmd->targ_xfer_tag = session_get_next_ttt(conn->sess);
	पूर्ण
	hdr->opcode = ISCSI_OP_TEXT_RSP;
	padding = ((-text_length) & 3);
	hton24(hdr->dlength, text_length);
	hdr->itt = cmd->init_task_tag;
	hdr->ttt = cpu_to_be32(cmd->targ_xfer_tag);
	cmd->stat_sn = conn->stat_sn++;
	hdr->statsn = cpu_to_be32(cmd->stat_sn);

	iscsit_increment_maxcmdsn(cmd, conn->sess);
	/*
	 * Reset maxcmdsn_inc in multi-part text payload exchanges to
	 * correctly increment MaxCmdSN क्रम each response answering a
	 * non immediate text request with a valid CmdSN.
	 */
	cmd->maxcmdsn_inc = 0;
	hdr->exp_cmdsn = cpu_to_be32(conn->sess->exp_cmd_sn);
	hdr->max_cmdsn = cpu_to_be32((u32) atomic_पढ़ो(&conn->sess->max_cmd_sn));

	pr_debug("Built Text Response: ITT: 0x%08x, TTT: 0x%08x, StatSN: 0x%08x,"
		" Length: %u, CID: %hu F: %d C: %d\n", cmd->init_task_tag,
		cmd->targ_xfer_tag, cmd->stat_sn, text_length, conn->cid,
		!!(hdr->flags & ISCSI_FLAG_CMD_FINAL),
		!!(hdr->flags & ISCSI_FLAG_TEXT_CONTINUE));

	वापस text_length + padding;
पूर्ण
EXPORT_SYMBOL(iscsit_build_text_rsp);

अटल पूर्णांक iscsit_send_text_rsp(
	काष्ठा iscsi_cmd *cmd,
	काष्ठा iscsi_conn *conn)
अणु
	काष्ठा iscsi_text_rsp *hdr = (काष्ठा iscsi_text_rsp *)cmd->pdu;
	पूर्णांक text_length;

	text_length = iscsit_build_text_rsp(cmd, conn, hdr,
				conn->conn_transport->transport_type);
	अगर (text_length < 0)
		वापस text_length;

	वापस conn->conn_transport->iscsit_xmit_pdu(conn, cmd, शून्य,
						     cmd->buf_ptr,
						     text_length);
पूर्ण

व्योम
iscsit_build_reject(काष्ठा iscsi_cmd *cmd, काष्ठा iscsi_conn *conn,
		    काष्ठा iscsi_reject *hdr)
अणु
	hdr->opcode		= ISCSI_OP_REJECT;
	hdr->reason		= cmd->reject_reason;
	hdr->flags		|= ISCSI_FLAG_CMD_FINAL;
	hton24(hdr->dlength, ISCSI_HDR_LEN);
	hdr->ffffffff		= cpu_to_be32(0xffffffff);
	cmd->stat_sn		= conn->stat_sn++;
	hdr->statsn		= cpu_to_be32(cmd->stat_sn);
	hdr->exp_cmdsn		= cpu_to_be32(conn->sess->exp_cmd_sn);
	hdr->max_cmdsn		= cpu_to_be32((u32) atomic_पढ़ो(&conn->sess->max_cmd_sn));

पूर्ण
EXPORT_SYMBOL(iscsit_build_reject);

अटल पूर्णांक iscsit_send_reject(
	काष्ठा iscsi_cmd *cmd,
	काष्ठा iscsi_conn *conn)
अणु
	काष्ठा iscsi_reject *hdr = (काष्ठा iscsi_reject *)&cmd->pdu[0];

	iscsit_build_reject(cmd, conn, hdr);

	pr_debug("Built Reject PDU StatSN: 0x%08x, Reason: 0x%02x,"
		" CID: %hu\n", ntohl(hdr->statsn), hdr->reason, conn->cid);

	वापस conn->conn_transport->iscsit_xmit_pdu(conn, cmd, शून्य,
						     cmd->buf_ptr,
						     ISCSI_HDR_LEN);
पूर्ण

व्योम iscsit_thपढ़ो_get_cpumask(काष्ठा iscsi_conn *conn)
अणु
	पूर्णांक ord, cpu;
	/*
	 * biपंचांगap_id is asचिन्हित from iscsit_global->ts_biपंचांगap from
	 * within iscsit_start_kthपढ़ोs()
	 *
	 * Here we use biपंचांगap_id to determine which CPU that this
	 * iSCSI connection's RX/TX thपढ़ोs will be scheduled to
	 * execute upon.
	 */
	ord = conn->biपंचांगap_id % cpumask_weight(cpu_online_mask);
	क्रम_each_online_cpu(cpu) अणु
		अगर (ord-- == 0) अणु
			cpumask_set_cpu(cpu, conn->conn_cpumask);
			वापस;
		पूर्ण
	पूर्ण
	/*
	 * This should never be reached..
	 */
	dump_stack();
	cpumask_setall(conn->conn_cpumask);
पूर्ण

पूर्णांक
iscsit_immediate_queue(काष्ठा iscsi_conn *conn, काष्ठा iscsi_cmd *cmd, पूर्णांक state)
अणु
	पूर्णांक ret;

	चयन (state) अणु
	हाल ISTATE_SEND_R2T:
		ret = iscsit_send_r2t(cmd, conn);
		अगर (ret < 0)
			जाओ err;
		अवरोध;
	हाल ISTATE_REMOVE:
		spin_lock_bh(&conn->cmd_lock);
		list_del_init(&cmd->i_conn_node);
		spin_unlock_bh(&conn->cmd_lock);

		iscsit_मुक्त_cmd(cmd, false);
		अवरोध;
	हाल ISTATE_SEND_NOPIN_WANT_RESPONSE:
		iscsit_mod_nopin_response_समयr(conn);
		ret = iscsit_send_unsolicited_nopin(cmd, conn, 1);
		अगर (ret < 0)
			जाओ err;
		अवरोध;
	हाल ISTATE_SEND_NOPIN_NO_RESPONSE:
		ret = iscsit_send_unsolicited_nopin(cmd, conn, 0);
		अगर (ret < 0)
			जाओ err;
		अवरोध;
	शेष:
		pr_err("Unknown Opcode: 0x%02x ITT:"
		       " 0x%08x, i_state: %d on CID: %hu\n",
		       cmd->iscsi_opcode, cmd->init_task_tag, state,
		       conn->cid);
		जाओ err;
	पूर्ण

	वापस 0;

err:
	वापस -1;
पूर्ण
EXPORT_SYMBOL(iscsit_immediate_queue);

अटल पूर्णांक
iscsit_handle_immediate_queue(काष्ठा iscsi_conn *conn)
अणु
	काष्ठा iscsit_transport *t = conn->conn_transport;
	काष्ठा iscsi_queue_req *qr;
	काष्ठा iscsi_cmd *cmd;
	u8 state;
	पूर्णांक ret;

	जबतक ((qr = iscsit_get_cmd_from_immediate_queue(conn))) अणु
		atomic_set(&conn->check_immediate_queue, 0);
		cmd = qr->cmd;
		state = qr->state;
		kmem_cache_मुक्त(lio_qr_cache, qr);

		ret = t->iscsit_immediate_queue(conn, cmd, state);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक
iscsit_response_queue(काष्ठा iscsi_conn *conn, काष्ठा iscsi_cmd *cmd, पूर्णांक state)
अणु
	पूर्णांक ret;

check_rsp_state:
	चयन (state) अणु
	हाल ISTATE_SEND_DATAIN:
		ret = iscsit_send_datain(cmd, conn);
		अगर (ret < 0)
			जाओ err;
		अन्यथा अगर (!ret)
			/* more drs */
			जाओ check_rsp_state;
		अन्यथा अगर (ret == 1) अणु
			/* all करोne */
			spin_lock_bh(&cmd->istate_lock);
			cmd->i_state = ISTATE_SENT_STATUS;
			spin_unlock_bh(&cmd->istate_lock);

			अगर (atomic_पढ़ो(&conn->check_immediate_queue))
				वापस 1;

			वापस 0;
		पूर्ण अन्यथा अगर (ret == 2) अणु
			/* Still must send status,
			   SCF_TRANSPORT_TASK_SENSE was set */
			spin_lock_bh(&cmd->istate_lock);
			cmd->i_state = ISTATE_SEND_STATUS;
			spin_unlock_bh(&cmd->istate_lock);
			state = ISTATE_SEND_STATUS;
			जाओ check_rsp_state;
		पूर्ण

		अवरोध;
	हाल ISTATE_SEND_STATUS:
	हाल ISTATE_SEND_STATUS_RECOVERY:
		ret = iscsit_send_response(cmd, conn);
		अवरोध;
	हाल ISTATE_SEND_LOGOUTRSP:
		ret = iscsit_send_logout(cmd, conn);
		अवरोध;
	हाल ISTATE_SEND_ASYNCMSG:
		ret = iscsit_send_conn_drop_async_message(
			cmd, conn);
		अवरोध;
	हाल ISTATE_SEND_NOPIN:
		ret = iscsit_send_nopin(cmd, conn);
		अवरोध;
	हाल ISTATE_SEND_REJECT:
		ret = iscsit_send_reject(cmd, conn);
		अवरोध;
	हाल ISTATE_SEND_TASKMGTRSP:
		ret = iscsit_send_task_mgt_rsp(cmd, conn);
		अगर (ret != 0)
			अवरोध;
		ret = iscsit_पंचांगr_post_handler(cmd, conn);
		अगर (ret != 0)
			iscsit_fall_back_to_erl0(conn->sess);
		अवरोध;
	हाल ISTATE_SEND_TEXTRSP:
		ret = iscsit_send_text_rsp(cmd, conn);
		अवरोध;
	शेष:
		pr_err("Unknown Opcode: 0x%02x ITT:"
		       " 0x%08x, i_state: %d on CID: %hu\n",
		       cmd->iscsi_opcode, cmd->init_task_tag,
		       state, conn->cid);
		जाओ err;
	पूर्ण
	अगर (ret < 0)
		जाओ err;

	चयन (state) अणु
	हाल ISTATE_SEND_LOGOUTRSP:
		अगर (!iscsit_logout_post_handler(cmd, conn))
			वापस -ECONNRESET;
		fallthrough;
	हाल ISTATE_SEND_STATUS:
	हाल ISTATE_SEND_ASYNCMSG:
	हाल ISTATE_SEND_NOPIN:
	हाल ISTATE_SEND_STATUS_RECOVERY:
	हाल ISTATE_SEND_TEXTRSP:
	हाल ISTATE_SEND_TASKMGTRSP:
	हाल ISTATE_SEND_REJECT:
		spin_lock_bh(&cmd->istate_lock);
		cmd->i_state = ISTATE_SENT_STATUS;
		spin_unlock_bh(&cmd->istate_lock);
		अवरोध;
	शेष:
		pr_err("Unknown Opcode: 0x%02x ITT:"
		       " 0x%08x, i_state: %d on CID: %hu\n",
		       cmd->iscsi_opcode, cmd->init_task_tag,
		       cmd->i_state, conn->cid);
		जाओ err;
	पूर्ण

	अगर (atomic_पढ़ो(&conn->check_immediate_queue))
		वापस 1;

	वापस 0;

err:
	वापस -1;
पूर्ण
EXPORT_SYMBOL(iscsit_response_queue);

अटल पूर्णांक iscsit_handle_response_queue(काष्ठा iscsi_conn *conn)
अणु
	काष्ठा iscsit_transport *t = conn->conn_transport;
	काष्ठा iscsi_queue_req *qr;
	काष्ठा iscsi_cmd *cmd;
	u8 state;
	पूर्णांक ret;

	जबतक ((qr = iscsit_get_cmd_from_response_queue(conn))) अणु
		cmd = qr->cmd;
		state = qr->state;
		kmem_cache_मुक्त(lio_qr_cache, qr);

		ret = t->iscsit_response_queue(conn, cmd, state);
		अगर (ret == 1 || ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक iscsi_target_tx_thपढ़ो(व्योम *arg)
अणु
	पूर्णांक ret = 0;
	काष्ठा iscsi_conn *conn = arg;
	bool conn_मुक्तd = false;

	/*
	 * Allow ourselves to be पूर्णांकerrupted by संक_विघ्न so that a
	 * connection recovery / failure event can be triggered बाह्यally.
	 */
	allow_संकेत(संक_विघ्न);

	जबतक (!kthपढ़ो_should_stop()) अणु
		/*
		 * Ensure that both TX and RX per connection kthपढ़ोs
		 * are scheduled to run on the same CPU.
		 */
		iscsit_thपढ़ो_check_cpumask(conn, current, 1);

		रुको_event_पूर्णांकerruptible(conn->queues_wq,
					 !iscsit_conn_all_queues_empty(conn));

		अगर (संकेत_pending(current))
			जाओ transport_err;

get_immediate:
		ret = iscsit_handle_immediate_queue(conn);
		अगर (ret < 0)
			जाओ transport_err;

		ret = iscsit_handle_response_queue(conn);
		अगर (ret == 1) अणु
			जाओ get_immediate;
		पूर्ण अन्यथा अगर (ret == -ECONNRESET) अणु
			conn_मुक्तd = true;
			जाओ out;
		पूर्ण अन्यथा अगर (ret < 0) अणु
			जाओ transport_err;
		पूर्ण
	पूर्ण

transport_err:
	/*
	 * Aव्योम the normal connection failure code-path अगर this connection
	 * is still within LOGIN mode, and iscsi_np process context is
	 * responsible क्रम cleaning up the early connection failure.
	 */
	अगर (conn->conn_state != TARG_CONN_STATE_IN_LOGIN)
		iscsit_take_action_क्रम_connection_निकास(conn, &conn_मुक्तd);
out:
	अगर (!conn_मुक्तd) अणु
		जबतक (!kthपढ़ो_should_stop()) अणु
			msleep(100);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक iscsi_target_rx_opcode(काष्ठा iscsi_conn *conn, अचिन्हित अक्षर *buf)
अणु
	काष्ठा iscsi_hdr *hdr = (काष्ठा iscsi_hdr *)buf;
	काष्ठा iscsi_cmd *cmd;
	पूर्णांक ret = 0;

	चयन (hdr->opcode & ISCSI_OPCODE_MASK) अणु
	हाल ISCSI_OP_SCSI_CMD:
		cmd = iscsit_allocate_cmd(conn, TASK_INTERRUPTIBLE);
		अगर (!cmd)
			जाओ reject;

		ret = iscsit_handle_scsi_cmd(conn, cmd, buf);
		अवरोध;
	हाल ISCSI_OP_SCSI_DATA_OUT:
		ret = iscsit_handle_data_out(conn, buf);
		अवरोध;
	हाल ISCSI_OP_NOOP_OUT:
		cmd = शून्य;
		अगर (hdr->ttt == cpu_to_be32(0xFFFFFFFF)) अणु
			cmd = iscsit_allocate_cmd(conn, TASK_INTERRUPTIBLE);
			अगर (!cmd)
				जाओ reject;
		पूर्ण
		ret = iscsit_handle_nop_out(conn, cmd, buf);
		अवरोध;
	हाल ISCSI_OP_SCSI_TMFUNC:
		cmd = iscsit_allocate_cmd(conn, TASK_INTERRUPTIBLE);
		अगर (!cmd)
			जाओ reject;

		ret = iscsit_handle_task_mgt_cmd(conn, cmd, buf);
		अवरोध;
	हाल ISCSI_OP_TEXT:
		अगर (hdr->ttt != cpu_to_be32(0xFFFFFFFF)) अणु
			cmd = iscsit_find_cmd_from_itt(conn, hdr->itt);
			अगर (!cmd)
				जाओ reject;
		पूर्ण अन्यथा अणु
			cmd = iscsit_allocate_cmd(conn, TASK_INTERRUPTIBLE);
			अगर (!cmd)
				जाओ reject;
		पूर्ण

		ret = iscsit_handle_text_cmd(conn, cmd, buf);
		अवरोध;
	हाल ISCSI_OP_LOGOUT:
		cmd = iscsit_allocate_cmd(conn, TASK_INTERRUPTIBLE);
		अगर (!cmd)
			जाओ reject;

		ret = iscsit_handle_logout_cmd(conn, cmd, buf);
		अगर (ret > 0)
			रुको_क्रम_completion_समयout(&conn->conn_logout_comp,
					SECONDS_FOR_LOGOUT_COMP * HZ);
		अवरोध;
	हाल ISCSI_OP_SNACK:
		ret = iscsit_handle_snack(conn, buf);
		अवरोध;
	शेष:
		pr_err("Got unknown iSCSI OpCode: 0x%02x\n", hdr->opcode);
		अगर (!conn->sess->sess_ops->ErrorRecoveryLevel) अणु
			pr_err("Cannot recover from unknown"
			" opcode while ERL=0, closing iSCSI connection.\n");
			वापस -1;
		पूर्ण
		pr_err("Unable to recover from unknown opcode while OFMarker=No,"
		       " closing iSCSI connection.\n");
		ret = -1;
		अवरोध;
	पूर्ण

	वापस ret;
reject:
	वापस iscsit_add_reject(conn, ISCSI_REASON_BOOKMARK_NO_RESOURCES, buf);
पूर्ण

अटल bool iscsi_target_check_conn_state(काष्ठा iscsi_conn *conn)
अणु
	bool ret;

	spin_lock_bh(&conn->state_lock);
	ret = (conn->conn_state != TARG_CONN_STATE_LOGGED_IN);
	spin_unlock_bh(&conn->state_lock);

	वापस ret;
पूर्ण

अटल व्योम iscsit_get_rx_pdu(काष्ठा iscsi_conn *conn)
अणु
	पूर्णांक ret;
	u8 *buffer, opcode;
	u32 checksum = 0, digest = 0;
	काष्ठा kvec iov;

	buffer = kसुस्मृति(ISCSI_HDR_LEN, माप(*buffer), GFP_KERNEL);
	अगर (!buffer)
		वापस;

	जबतक (!kthपढ़ो_should_stop()) अणु
		/*
		 * Ensure that both TX and RX per connection kthपढ़ोs
		 * are scheduled to run on the same CPU.
		 */
		iscsit_thपढ़ो_check_cpumask(conn, current, 0);

		स_रखो(&iov, 0, माप(काष्ठा kvec));

		iov.iov_base	= buffer;
		iov.iov_len	= ISCSI_HDR_LEN;

		ret = rx_data(conn, &iov, 1, ISCSI_HDR_LEN);
		अगर (ret != ISCSI_HDR_LEN) अणु
			iscsit_rx_thपढ़ो_रुको_क्रम_tcp(conn);
			अवरोध;
		पूर्ण

		अगर (conn->conn_ops->HeaderDigest) अणु
			iov.iov_base	= &digest;
			iov.iov_len	= ISCSI_CRC_LEN;

			ret = rx_data(conn, &iov, 1, ISCSI_CRC_LEN);
			अगर (ret != ISCSI_CRC_LEN) अणु
				iscsit_rx_thपढ़ो_रुको_क्रम_tcp(conn);
				अवरोध;
			पूर्ण

			iscsit_करो_crypto_hash_buf(conn->conn_rx_hash, buffer,
						  ISCSI_HDR_LEN, 0, शून्य,
						  &checksum);

			अगर (digest != checksum) अणु
				pr_err("HeaderDigest CRC32C failed,"
					" received 0x%08x, computed 0x%08x\n",
					digest, checksum);
				/*
				 * Set the PDU to 0xff so it will पूर्णांकentionally
				 * hit शेष in the चयन below.
				 */
				स_रखो(buffer, 0xff, ISCSI_HDR_LEN);
				atomic_दीर्घ_inc(&conn->sess->conn_digest_errors);
			पूर्ण अन्यथा अणु
				pr_debug("Got HeaderDigest CRC32C"
						" 0x%08x\n", checksum);
			पूर्ण
		पूर्ण

		अगर (conn->conn_state == TARG_CONN_STATE_IN_LOGOUT)
			अवरोध;

		opcode = buffer[0] & ISCSI_OPCODE_MASK;

		अगर (conn->sess->sess_ops->SessionType &&
		   ((!(opcode & ISCSI_OP_TEXT)) ||
		    (!(opcode & ISCSI_OP_LOGOUT)))) अणु
			pr_err("Received illegal iSCSI Opcode: 0x%02x"
			" while in Discovery Session, rejecting.\n", opcode);
			iscsit_add_reject(conn, ISCSI_REASON_PROTOCOL_ERROR,
					  buffer);
			अवरोध;
		पूर्ण

		ret = iscsi_target_rx_opcode(conn, buffer);
		अगर (ret < 0)
			अवरोध;
	पूर्ण

	kमुक्त(buffer);
पूर्ण

पूर्णांक iscsi_target_rx_thपढ़ो(व्योम *arg)
अणु
	पूर्णांक rc;
	काष्ठा iscsi_conn *conn = arg;
	bool conn_मुक्तd = false;

	/*
	 * Allow ourselves to be पूर्णांकerrupted by संक_विघ्न so that a
	 * connection recovery / failure event can be triggered बाह्यally.
	 */
	allow_संकेत(संक_विघ्न);
	/*
	 * Wait क्रम iscsi_post_login_handler() to complete beक्रमe allowing
	 * incoming iscsi/tcp socket I/O, and/or failing the connection.
	 */
	rc = रुको_क्रम_completion_पूर्णांकerruptible(&conn->rx_login_comp);
	अगर (rc < 0 || iscsi_target_check_conn_state(conn))
		जाओ out;

	अगर (!conn->conn_transport->iscsit_get_rx_pdu)
		वापस 0;

	conn->conn_transport->iscsit_get_rx_pdu(conn);

	अगर (!संकेत_pending(current))
		atomic_set(&conn->transport_failed, 1);
	iscsit_take_action_क्रम_connection_निकास(conn, &conn_मुक्तd);

out:
	अगर (!conn_मुक्तd) अणु
		जबतक (!kthपढ़ो_should_stop()) अणु
			msleep(100);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम iscsit_release_commands_from_conn(काष्ठा iscsi_conn *conn)
अणु
	LIST_HEAD(पंचांगp_list);
	काष्ठा iscsi_cmd *cmd = शून्य, *cmd_पंचांगp = शून्य;
	काष्ठा iscsi_session *sess = conn->sess;
	/*
	 * We expect this function to only ever be called from either RX or TX
	 * thपढ़ो context via iscsit_बंद_connection() once the other context
	 * has been reset -> वापसed sleeping pre-handler state.
	 */
	spin_lock_bh(&conn->cmd_lock);
	list_splice_init(&conn->conn_cmd_list, &पंचांगp_list);

	list_क्रम_each_entry_safe(cmd, cmd_पंचांगp, &पंचांगp_list, i_conn_node) अणु
		काष्ठा se_cmd *se_cmd = &cmd->se_cmd;

		अगर (se_cmd->se_tfo != शून्य) अणु
			spin_lock_irq(&se_cmd->t_state_lock);
			अगर (se_cmd->transport_state & CMD_T_ABORTED) अणु
				/*
				 * LIO's पात path owns the cleanup क्रम this,
				 * so put it back on the list and let
				 * पातed_task handle it.
				 */
				list_move_tail(&cmd->i_conn_node,
					       &conn->conn_cmd_list);
			पूर्ण अन्यथा अणु
				se_cmd->transport_state |= CMD_T_FABRIC_STOP;
			पूर्ण
			spin_unlock_irq(&se_cmd->t_state_lock);
		पूर्ण
	पूर्ण
	spin_unlock_bh(&conn->cmd_lock);

	list_क्रम_each_entry_safe(cmd, cmd_पंचांगp, &पंचांगp_list, i_conn_node) अणु
		list_del_init(&cmd->i_conn_node);

		iscsit_increment_maxcmdsn(cmd, sess);
		iscsit_मुक्त_cmd(cmd, true);

	पूर्ण
पूर्ण

अटल व्योम iscsit_stop_समयrs_क्रम_cmds(
	काष्ठा iscsi_conn *conn)
अणु
	काष्ठा iscsi_cmd *cmd;

	spin_lock_bh(&conn->cmd_lock);
	list_क्रम_each_entry(cmd, &conn->conn_cmd_list, i_conn_node) अणु
		अगर (cmd->data_direction == DMA_TO_DEVICE)
			iscsit_stop_dataout_समयr(cmd);
	पूर्ण
	spin_unlock_bh(&conn->cmd_lock);
पूर्ण

पूर्णांक iscsit_बंद_connection(
	काष्ठा iscsi_conn *conn)
अणु
	पूर्णांक conn_logout = (conn->conn_state == TARG_CONN_STATE_IN_LOGOUT);
	काष्ठा iscsi_session	*sess = conn->sess;

	pr_debug("Closing iSCSI connection CID %hu on SID:"
		" %u\n", conn->cid, sess->sid);
	/*
	 * Always up conn_logout_comp क्रम the traditional TCP and HW_OFFLOAD
	 * हाल just in हाल the RX Thपढ़ो in iscsi_target_rx_opcode() is
	 * sleeping and the logout response never got sent because the
	 * connection failed.
	 *
	 * However क्रम iser-target, isert_रुको4logout() is using conn_logout_comp
	 * to संकेत logout response TX पूर्णांकerrupt completion.  Go ahead and skip
	 * this क्रम iser since isert_rx_opcode() करोes not रुको on logout failure,
	 * and to aव्योम iscsi_conn poपूर्णांकer dereference in iser-target code.
	 */
	अगर (!conn->conn_transport->rdma_shutकरोwn)
		complete(&conn->conn_logout_comp);

	अगर (!म_भेद(current->comm, ISCSI_RX_THREAD_NAME)) अणु
		अगर (conn->tx_thपढ़ो &&
		    cmpxchg(&conn->tx_thपढ़ो_active, true, false)) अणु
			send_sig(संक_विघ्न, conn->tx_thपढ़ो, 1);
			kthपढ़ो_stop(conn->tx_thपढ़ो);
		पूर्ण
	पूर्ण अन्यथा अगर (!म_भेद(current->comm, ISCSI_TX_THREAD_NAME)) अणु
		अगर (conn->rx_thपढ़ो &&
		    cmpxchg(&conn->rx_thपढ़ो_active, true, false)) अणु
			send_sig(संक_विघ्न, conn->rx_thपढ़ो, 1);
			kthपढ़ो_stop(conn->rx_thपढ़ो);
		पूर्ण
	पूर्ण

	spin_lock(&iscsit_global->ts_biपंचांगap_lock);
	biपंचांगap_release_region(iscsit_global->ts_biपंचांगap, conn->biपंचांगap_id,
			      get_order(1));
	spin_unlock(&iscsit_global->ts_biपंचांगap_lock);

	iscsit_stop_समयrs_क्रम_cmds(conn);
	iscsit_stop_nopin_response_समयr(conn);
	iscsit_stop_nopin_समयr(conn);

	अगर (conn->conn_transport->iscsit_रुको_conn)
		conn->conn_transport->iscsit_रुको_conn(conn);

	/*
	 * During Connection recovery drop unacknowledged out of order
	 * commands क्रम this connection, and prepare the other commands
	 * क्रम reallegiance.
	 *
	 * During normal operation clear the out of order commands (but
	 * करो not मुक्त the काष्ठा iscsi_ooo_cmdsn's) and release all
	 * काष्ठा iscsi_cmds.
	 */
	अगर (atomic_पढ़ो(&conn->connection_recovery)) अणु
		iscsit_discard_unacknowledged_ooo_cmdsns_क्रम_conn(conn);
		iscsit_prepare_cmds_क्रम_reallegiance(conn);
	पूर्ण अन्यथा अणु
		iscsit_clear_ooo_cmdsns_क्रम_conn(conn);
		iscsit_release_commands_from_conn(conn);
	पूर्ण
	iscsit_मुक्त_queue_reqs_क्रम_conn(conn);

	/*
	 * Handle decrementing session or connection usage count अगर
	 * a logout response was not able to be sent because the
	 * connection failed.  Fall back to Session Recovery here.
	 */
	अगर (atomic_पढ़ो(&conn->conn_logout_हटाओ)) अणु
		अगर (conn->conn_logout_reason == ISCSI_LOGOUT_REASON_CLOSE_SESSION) अणु
			iscsit_dec_conn_usage_count(conn);
			iscsit_dec_session_usage_count(sess);
		पूर्ण
		अगर (conn->conn_logout_reason == ISCSI_LOGOUT_REASON_CLOSE_CONNECTION)
			iscsit_dec_conn_usage_count(conn);

		atomic_set(&conn->conn_logout_हटाओ, 0);
		atomic_set(&sess->session_reinstatement, 0);
		atomic_set(&sess->session_fall_back_to_erl0, 1);
	पूर्ण

	spin_lock_bh(&sess->conn_lock);
	list_del(&conn->conn_list);

	/*
	 * Attempt to let the Initiator know this connection failed by
	 * sending an Connection Dropped Async Message on another
	 * active connection.
	 */
	अगर (atomic_पढ़ो(&conn->connection_recovery))
		iscsit_build_conn_drop_async_message(conn);

	spin_unlock_bh(&sess->conn_lock);

	/*
	 * If connection reinstatement is being perक्रमmed on this connection,
	 * up the connection reinstatement semaphore that is being blocked on
	 * in iscsit_cause_connection_reinstatement().
	 */
	spin_lock_bh(&conn->state_lock);
	अगर (atomic_पढ़ो(&conn->sleep_on_conn_रुको_comp)) अणु
		spin_unlock_bh(&conn->state_lock);
		complete(&conn->conn_रुको_comp);
		रुको_क्रम_completion(&conn->conn_post_रुको_comp);
		spin_lock_bh(&conn->state_lock);
	पूर्ण

	/*
	 * If connection reinstatement is being perक्रमmed on this connection
	 * by receiving a REMOVECONNFORRECOVERY logout request, up the
	 * connection रुको rcfr semaphore that is being blocked on
	 * an iscsit_connection_reinstatement_rcfr().
	 */
	अगर (atomic_पढ़ो(&conn->connection_रुको_rcfr)) अणु
		spin_unlock_bh(&conn->state_lock);
		complete(&conn->conn_रुको_rcfr_comp);
		रुको_क्रम_completion(&conn->conn_post_रुको_comp);
		spin_lock_bh(&conn->state_lock);
	पूर्ण
	atomic_set(&conn->connection_reinstatement, 1);
	spin_unlock_bh(&conn->state_lock);

	/*
	 * If any other processes are accessing this connection poपूर्णांकer we
	 * must रुको until they have completed.
	 */
	iscsit_check_conn_usage_count(conn);

	ahash_request_मुक्त(conn->conn_tx_hash);
	अगर (conn->conn_rx_hash) अणु
		काष्ठा crypto_ahash *tfm;

		tfm = crypto_ahash_reqtfm(conn->conn_rx_hash);
		ahash_request_मुक्त(conn->conn_rx_hash);
		crypto_मुक्त_ahash(tfm);
	पूर्ण

	अगर (conn->sock)
		sock_release(conn->sock);

	अगर (conn->conn_transport->iscsit_मुक्त_conn)
		conn->conn_transport->iscsit_मुक्त_conn(conn);

	pr_debug("Moving to TARG_CONN_STATE_FREE.\n");
	conn->conn_state = TARG_CONN_STATE_FREE;
	iscsit_मुक्त_conn(conn);

	spin_lock_bh(&sess->conn_lock);
	atomic_dec(&sess->nconn);
	pr_debug("Decremented iSCSI connection count to %hu from node:"
		" %s\n", atomic_पढ़ो(&sess->nconn),
		sess->sess_ops->InitiatorName);
	/*
	 * Make sure that अगर one connection fails in an non ERL=2 iSCSI
	 * Session that they all fail.
	 */
	अगर ((sess->sess_ops->ErrorRecoveryLevel != 2) && !conn_logout &&
	     !atomic_पढ़ो(&sess->session_logout))
		atomic_set(&sess->session_fall_back_to_erl0, 1);

	/*
	 * If this was not the last connection in the session, and we are
	 * perक्रमming session reinstatement or falling back to ERL=0, call
	 * iscsit_stop_session() without sleeping to shutकरोwn the other
	 * active connections.
	 */
	अगर (atomic_पढ़ो(&sess->nconn)) अणु
		अगर (!atomic_पढ़ो(&sess->session_reinstatement) &&
		    !atomic_पढ़ो(&sess->session_fall_back_to_erl0)) अणु
			spin_unlock_bh(&sess->conn_lock);
			वापस 0;
		पूर्ण
		अगर (!atomic_पढ़ो(&sess->session_stop_active)) अणु
			atomic_set(&sess->session_stop_active, 1);
			spin_unlock_bh(&sess->conn_lock);
			iscsit_stop_session(sess, 0, 0);
			वापस 0;
		पूर्ण
		spin_unlock_bh(&sess->conn_lock);
		वापस 0;
	पूर्ण

	/*
	 * If this was the last connection in the session and one of the
	 * following is occurring:
	 *
	 * Session Reinstatement is not being perक्रमmed, and are falling back
	 * to ERL=0 call iscsit_बंद_session().
	 *
	 * Session Logout was requested.  iscsit_बंद_session() will be called
	 * अन्यथाwhere.
	 *
	 * Session Continuation is not being perक्रमmed, start the Time2Retain
	 * handler and check अगर sleep_on_sess_रुको_sem is active.
	 */
	अगर (!atomic_पढ़ो(&sess->session_reinstatement) &&
	     atomic_पढ़ो(&sess->session_fall_back_to_erl0)) अणु
		spin_unlock_bh(&sess->conn_lock);
		complete_all(&sess->session_रुको_comp);
		iscsit_बंद_session(sess, true);

		वापस 0;
	पूर्ण अन्यथा अगर (atomic_पढ़ो(&sess->session_logout)) अणु
		pr_debug("Moving to TARG_SESS_STATE_FREE.\n");
		sess->session_state = TARG_SESS_STATE_FREE;

		अगर (atomic_पढ़ो(&sess->session_बंद)) अणु
			spin_unlock_bh(&sess->conn_lock);
			complete_all(&sess->session_रुको_comp);
			iscsit_बंद_session(sess, true);
		पूर्ण अन्यथा अणु
			spin_unlock_bh(&sess->conn_lock);
		पूर्ण

		वापस 0;
	पूर्ण अन्यथा अणु
		pr_debug("Moving to TARG_SESS_STATE_FAILED.\n");
		sess->session_state = TARG_SESS_STATE_FAILED;

		अगर (!atomic_पढ़ो(&sess->session_continuation))
			iscsit_start_समय2retain_handler(sess);

		अगर (atomic_पढ़ो(&sess->session_बंद)) अणु
			spin_unlock_bh(&sess->conn_lock);
			complete_all(&sess->session_रुको_comp);
			iscsit_बंद_session(sess, true);
		पूर्ण अन्यथा अणु
			spin_unlock_bh(&sess->conn_lock);
		पूर्ण

		वापस 0;
	पूर्ण
पूर्ण

/*
 * If the iSCSI Session क्रम the iSCSI Initiator Node exists,
 * क्रमcefully shutकरोwn the iSCSI NEXUS.
 */
पूर्णांक iscsit_बंद_session(काष्ठा iscsi_session *sess, bool can_sleep)
अणु
	काष्ठा iscsi_portal_group *tpg = sess->tpg;
	काष्ठा se_portal_group *se_tpg = &tpg->tpg_se_tpg;

	अगर (atomic_पढ़ो(&sess->nconn)) अणु
		pr_err("%d connection(s) still exist for iSCSI session"
			" to %s\n", atomic_पढ़ो(&sess->nconn),
			sess->sess_ops->InitiatorName);
		BUG();
	पूर्ण

	spin_lock_bh(&se_tpg->session_lock);
	atomic_set(&sess->session_logout, 1);
	atomic_set(&sess->session_reinstatement, 1);
	iscsit_stop_समय2retain_समयr(sess);
	spin_unlock_bh(&se_tpg->session_lock);

	/*
	 * transport_deरेजिस्टर_session_configfs() will clear the
	 * काष्ठा se_node_acl->nacl_sess poपूर्णांकer now as a iscsi_np process context
	 * can be setting it again with __transport_रेजिस्टर_session() in
	 * iscsi_post_login_handler() again after the iscsit_stop_session()
	 * completes in iscsi_np context.
	 */
	transport_deरेजिस्टर_session_configfs(sess->se_sess);

	/*
	 * If any other processes are accessing this session poपूर्णांकer we must
	 * रुको until they have completed.  If we are in an पूर्णांकerrupt (the
	 * समय2retain handler) and contain and active session usage count we
	 * restart the समयr and निकास.
	 */
	अगर (iscsit_check_session_usage_count(sess, can_sleep)) अणु
		atomic_set(&sess->session_logout, 0);
		iscsit_start_समय2retain_handler(sess);
		वापस 0;
	पूर्ण

	transport_deरेजिस्टर_session(sess->se_sess);

	अगर (sess->sess_ops->ErrorRecoveryLevel == 2)
		iscsit_मुक्त_connection_recovery_entries(sess);

	iscsit_मुक्त_all_ooo_cmdsns(sess);

	spin_lock_bh(&se_tpg->session_lock);
	pr_debug("Moving to TARG_SESS_STATE_FREE.\n");
	sess->session_state = TARG_SESS_STATE_FREE;
	pr_debug("Released iSCSI session from node: %s\n",
			sess->sess_ops->InitiatorName);
	tpg->nsessions--;
	अगर (tpg->tpg_tiqn)
		tpg->tpg_tiqn->tiqn_nsessions--;

	pr_debug("Decremented number of active iSCSI Sessions on"
		" iSCSI TPG: %hu to %u\n", tpg->tpgt, tpg->nsessions);

	ida_मुक्त(&sess_ida, sess->session_index);
	kमुक्त(sess->sess_ops);
	sess->sess_ops = शून्य;
	spin_unlock_bh(&se_tpg->session_lock);

	kमुक्त(sess);
	वापस 0;
पूर्ण

अटल व्योम iscsit_logout_post_handler_बंदsession(
	काष्ठा iscsi_conn *conn)
अणु
	काष्ठा iscsi_session *sess = conn->sess;
	पूर्णांक sleep = 1;
	/*
	 * Traditional iscsi/tcp will invoke this logic from TX thपढ़ो
	 * context during session logout, so clear tx_thपढ़ो_active and
	 * sleep अगर iscsit_बंद_connection() has not alपढ़ोy occured.
	 *
	 * Since iser-target invokes this logic from it's own workqueue,
	 * always sleep रुकोing क्रम RX/TX thपढ़ो shutकरोwn to complete
	 * within iscsit_बंद_connection().
	 */
	अगर (!conn->conn_transport->rdma_shutकरोwn) अणु
		sleep = cmpxchg(&conn->tx_thपढ़ो_active, true, false);
		अगर (!sleep)
			वापस;
	पूर्ण

	atomic_set(&conn->conn_logout_हटाओ, 0);
	complete(&conn->conn_logout_comp);

	iscsit_dec_conn_usage_count(conn);
	atomic_set(&sess->session_बंद, 1);
	iscsit_stop_session(sess, sleep, sleep);
	iscsit_dec_session_usage_count(sess);
पूर्ण

अटल व्योम iscsit_logout_post_handler_samecid(
	काष्ठा iscsi_conn *conn)
अणु
	पूर्णांक sleep = 1;

	अगर (!conn->conn_transport->rdma_shutकरोwn) अणु
		sleep = cmpxchg(&conn->tx_thपढ़ो_active, true, false);
		अगर (!sleep)
			वापस;
	पूर्ण

	atomic_set(&conn->conn_logout_हटाओ, 0);
	complete(&conn->conn_logout_comp);

	iscsit_cause_connection_reinstatement(conn, sleep);
	iscsit_dec_conn_usage_count(conn);
पूर्ण

अटल व्योम iscsit_logout_post_handler_dअगरfcid(
	काष्ठा iscsi_conn *conn,
	u16 cid)
अणु
	काष्ठा iscsi_conn *l_conn;
	काष्ठा iscsi_session *sess = conn->sess;
	bool conn_found = false;

	अगर (!sess)
		वापस;

	spin_lock_bh(&sess->conn_lock);
	list_क्रम_each_entry(l_conn, &sess->sess_conn_list, conn_list) अणु
		अगर (l_conn->cid == cid) अणु
			iscsit_inc_conn_usage_count(l_conn);
			conn_found = true;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&sess->conn_lock);

	अगर (!conn_found)
		वापस;

	अगर (l_conn->sock)
		l_conn->sock->ops->shutकरोwn(l_conn->sock, RCV_SHUTDOWN);

	spin_lock_bh(&l_conn->state_lock);
	pr_debug("Moving to TARG_CONN_STATE_IN_LOGOUT.\n");
	l_conn->conn_state = TARG_CONN_STATE_IN_LOGOUT;
	spin_unlock_bh(&l_conn->state_lock);

	iscsit_cause_connection_reinstatement(l_conn, 1);
	iscsit_dec_conn_usage_count(l_conn);
पूर्ण

/*
 *	Return of 0 causes the TX thपढ़ो to restart.
 */
पूर्णांक iscsit_logout_post_handler(
	काष्ठा iscsi_cmd *cmd,
	काष्ठा iscsi_conn *conn)
अणु
	पूर्णांक ret = 0;

	चयन (cmd->logout_reason) अणु
	हाल ISCSI_LOGOUT_REASON_CLOSE_SESSION:
		चयन (cmd->logout_response) अणु
		हाल ISCSI_LOGOUT_SUCCESS:
		हाल ISCSI_LOGOUT_CLEANUP_FAILED:
		शेष:
			iscsit_logout_post_handler_बंदsession(conn);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल ISCSI_LOGOUT_REASON_CLOSE_CONNECTION:
		अगर (conn->cid == cmd->logout_cid) अणु
			चयन (cmd->logout_response) अणु
			हाल ISCSI_LOGOUT_SUCCESS:
			हाल ISCSI_LOGOUT_CLEANUP_FAILED:
			शेष:
				iscsit_logout_post_handler_samecid(conn);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			चयन (cmd->logout_response) अणु
			हाल ISCSI_LOGOUT_SUCCESS:
				iscsit_logout_post_handler_dअगरfcid(conn,
					cmd->logout_cid);
				अवरोध;
			हाल ISCSI_LOGOUT_CID_NOT_FOUND:
			हाल ISCSI_LOGOUT_CLEANUP_FAILED:
			शेष:
				अवरोध;
			पूर्ण
			ret = 1;
		पूर्ण
		अवरोध;
	हाल ISCSI_LOGOUT_REASON_RECOVERY:
		चयन (cmd->logout_response) अणु
		हाल ISCSI_LOGOUT_SUCCESS:
		हाल ISCSI_LOGOUT_CID_NOT_FOUND:
		हाल ISCSI_LOGOUT_RECOVERY_UNSUPPORTED:
		हाल ISCSI_LOGOUT_CLEANUP_FAILED:
		शेष:
			अवरोध;
		पूर्ण
		ret = 1;
		अवरोध;
	शेष:
		अवरोध;

	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL(iscsit_logout_post_handler);

व्योम iscsit_fail_session(काष्ठा iscsi_session *sess)
अणु
	काष्ठा iscsi_conn *conn;

	spin_lock_bh(&sess->conn_lock);
	list_क्रम_each_entry(conn, &sess->sess_conn_list, conn_list) अणु
		pr_debug("Moving to TARG_CONN_STATE_CLEANUP_WAIT.\n");
		conn->conn_state = TARG_CONN_STATE_CLEANUP_WAIT;
	पूर्ण
	spin_unlock_bh(&sess->conn_lock);

	pr_debug("Moving to TARG_SESS_STATE_FAILED.\n");
	sess->session_state = TARG_SESS_STATE_FAILED;
पूर्ण

व्योम iscsit_stop_session(
	काष्ठा iscsi_session *sess,
	पूर्णांक session_sleep,
	पूर्णांक connection_sleep)
अणु
	u16 conn_count = atomic_पढ़ो(&sess->nconn);
	काष्ठा iscsi_conn *conn, *conn_पंचांगp = शून्य;
	पूर्णांक is_last;

	spin_lock_bh(&sess->conn_lock);

	अगर (connection_sleep) अणु
		list_क्रम_each_entry_safe(conn, conn_पंचांगp, &sess->sess_conn_list,
				conn_list) अणु
			अगर (conn_count == 0)
				अवरोध;

			अगर (list_is_last(&conn->conn_list, &sess->sess_conn_list)) अणु
				is_last = 1;
			पूर्ण अन्यथा अणु
				iscsit_inc_conn_usage_count(conn_पंचांगp);
				is_last = 0;
			पूर्ण
			iscsit_inc_conn_usage_count(conn);

			spin_unlock_bh(&sess->conn_lock);
			iscsit_cause_connection_reinstatement(conn, 1);
			spin_lock_bh(&sess->conn_lock);

			iscsit_dec_conn_usage_count(conn);
			अगर (is_last == 0)
				iscsit_dec_conn_usage_count(conn_पंचांगp);
			conn_count--;
		पूर्ण
	पूर्ण अन्यथा अणु
		list_क्रम_each_entry(conn, &sess->sess_conn_list, conn_list)
			iscsit_cause_connection_reinstatement(conn, 0);
	पूर्ण

	अगर (session_sleep && atomic_पढ़ो(&sess->nconn)) अणु
		spin_unlock_bh(&sess->conn_lock);
		रुको_क्रम_completion(&sess->session_रुको_comp);
	पूर्ण अन्यथा
		spin_unlock_bh(&sess->conn_lock);
पूर्ण

पूर्णांक iscsit_release_sessions_क्रम_tpg(काष्ठा iscsi_portal_group *tpg, पूर्णांक क्रमce)
अणु
	काष्ठा iscsi_session *sess;
	काष्ठा se_portal_group *se_tpg = &tpg->tpg_se_tpg;
	काष्ठा se_session *se_sess, *se_sess_पंचांगp;
	LIST_HEAD(मुक्त_list);
	पूर्णांक session_count = 0;

	spin_lock_bh(&se_tpg->session_lock);
	अगर (tpg->nsessions && !क्रमce) अणु
		spin_unlock_bh(&se_tpg->session_lock);
		वापस -1;
	पूर्ण

	list_क्रम_each_entry_safe(se_sess, se_sess_पंचांगp, &se_tpg->tpg_sess_list,
			sess_list) अणु
		sess = (काष्ठा iscsi_session *)se_sess->fabric_sess_ptr;

		spin_lock(&sess->conn_lock);
		अगर (atomic_पढ़ो(&sess->session_fall_back_to_erl0) ||
		    atomic_पढ़ो(&sess->session_logout) ||
		    atomic_पढ़ो(&sess->session_बंद) ||
		    (sess->समय2retain_समयr_flags & ISCSI_TF_EXPIRED)) अणु
			spin_unlock(&sess->conn_lock);
			जारी;
		पूर्ण
		iscsit_inc_session_usage_count(sess);
		atomic_set(&sess->session_reinstatement, 1);
		atomic_set(&sess->session_fall_back_to_erl0, 1);
		atomic_set(&sess->session_बंद, 1);
		spin_unlock(&sess->conn_lock);

		list_move_tail(&se_sess->sess_list, &मुक्त_list);
	पूर्ण
	spin_unlock_bh(&se_tpg->session_lock);

	list_क्रम_each_entry_safe(se_sess, se_sess_पंचांगp, &मुक्त_list, sess_list) अणु
		sess = (काष्ठा iscsi_session *)se_sess->fabric_sess_ptr;

		list_del_init(&se_sess->sess_list);
		iscsit_stop_session(sess, 1, 1);
		iscsit_dec_session_usage_count(sess);
		session_count++;
	पूर्ण

	pr_debug("Released %d iSCSI Session(s) from Target Portal"
			" Group: %hu\n", session_count, tpg->tpgt);
	वापस 0;
पूर्ण

MODULE_DESCRIPTION("iSCSI-Target Driver for mainline target infrastructure");
MODULE_VERSION("4.1.x");
MODULE_AUTHOR("nab@Linux-iSCSI.org");
MODULE_LICENSE("GPL");

module_init(iscsi_target_init_module);
module_निकास(iscsi_target_cleanup_module);
