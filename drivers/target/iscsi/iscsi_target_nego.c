<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*******************************************************************************
 * This file contains मुख्य functions related to iSCSI Parameter negotiation.
 *
 * (c) Copyright 2007-2013 Datera, Inc.
 *
 * Author: Nicholas A. Bellinger <nab@linux-iscsi.org>
 *
 ******************************************************************************/

#समावेश <linux/प्रकार.स>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <net/sock.h>
#समावेश <scsi/iscsi_proto.h>
#समावेश <target/target_core_base.h>
#समावेश <target/target_core_fabric.h>
#समावेश <target/iscsi/iscsi_transport.h>

#समावेश <target/iscsi/iscsi_target_core.h>
#समावेश "iscsi_target_parameters.h"
#समावेश "iscsi_target_login.h"
#समावेश "iscsi_target_nego.h"
#समावेश "iscsi_target_tpg.h"
#समावेश "iscsi_target_util.h"
#समावेश "iscsi_target.h"
#समावेश "iscsi_target_auth.h"

#घोषणा MAX_LOGIN_PDUS  7

व्योम convert_null_to_semi(अक्षर *buf, पूर्णांक len)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < len; i++)
		अगर (buf[i] == '\0')
			buf[i] = ';';
पूर्ण

अटल पूर्णांक म_माप_semi(अक्षर *buf)
अणु
	पूर्णांक i = 0;

	जबतक (buf[i] != '\0') अणु
		अगर (buf[i] == ';')
			वापस i;
		i++;
	पूर्ण

	वापस -1;
पूर्ण

पूर्णांक extract_param(
	स्थिर अक्षर *in_buf,
	स्थिर अक्षर *pattern,
	अचिन्हित पूर्णांक max_length,
	अक्षर *out_buf,
	अचिन्हित अक्षर *type)
अणु
	अक्षर *ptr;
	पूर्णांक len;

	अगर (!in_buf || !pattern || !out_buf || !type)
		वापस -1;

	ptr = म_माला(in_buf, pattern);
	अगर (!ptr)
		वापस -1;

	ptr = म_माला(ptr, "=");
	अगर (!ptr)
		वापस -1;

	ptr += 1;
	अगर (*ptr == '0' && (*(ptr+1) == 'x' || *(ptr+1) == 'X')) अणु
		ptr += 2; /* skip 0x */
		*type = HEX;
	पूर्ण अन्यथा
		*type = DECIMAL;

	len = म_माप_semi(ptr);
	अगर (len < 0)
		वापस -1;

	अगर (len >= max_length) अणु
		pr_err("Length of input: %d exceeds max_length:"
			" %d\n", len, max_length);
		वापस -1;
	पूर्ण
	स_नकल(out_buf, ptr, len);
	out_buf[len] = '\0';

	वापस 0;
पूर्ण

अटल u32 iscsi_handle_authentication(
	काष्ठा iscsi_conn *conn,
	अक्षर *in_buf,
	अक्षर *out_buf,
	पूर्णांक in_length,
	पूर्णांक *out_length,
	अचिन्हित अक्षर *authtype)
अणु
	काष्ठा iscsi_session *sess = conn->sess;
	काष्ठा iscsi_node_auth *auth;
	काष्ठा iscsi_node_acl *iscsi_nacl;
	काष्ठा iscsi_portal_group *iscsi_tpg;
	काष्ठा se_node_acl *se_nacl;

	अगर (!sess->sess_ops->SessionType) अणु
		/*
		 * For SessionType=Normal
		 */
		se_nacl = conn->sess->se_sess->se_node_acl;
		अगर (!se_nacl) अणु
			pr_err("Unable to locate struct se_node_acl for"
					" CHAP auth\n");
			वापस -1;
		पूर्ण
		iscsi_nacl = container_of(se_nacl, काष्ठा iscsi_node_acl,
				se_node_acl);
		अगर (!iscsi_nacl) अणु
			pr_err("Unable to locate struct iscsi_node_acl for"
					" CHAP auth\n");
			वापस -1;
		पूर्ण

		अगर (se_nacl->dynamic_node_acl) अणु
			iscsi_tpg = container_of(se_nacl->se_tpg,
					काष्ठा iscsi_portal_group, tpg_se_tpg);

			auth = &iscsi_tpg->tpg_demo_auth;
		पूर्ण अन्यथा अणु
			iscsi_nacl = container_of(se_nacl, काष्ठा iscsi_node_acl,
						  se_node_acl);

			auth = &iscsi_nacl->node_auth;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * For SessionType=Discovery
		 */
		auth = &iscsit_global->discovery_acl.node_auth;
	पूर्ण

	अगर (म_माला("CHAP", authtype))
		म_नकल(conn->sess->auth_type, "CHAP");
	अन्यथा
		म_नकल(conn->sess->auth_type, NONE);

	अगर (म_माला("None", authtype))
		वापस 1;
	अन्यथा अगर (म_माला("CHAP", authtype))
		वापस chap_मुख्य_loop(conn, auth, in_buf, out_buf,
				&in_length, out_length);
	/* SRP, SPKM1, SPKM2 and KRB5 are unsupported */
	वापस 2;
पूर्ण

अटल व्योम iscsi_हटाओ_failed_auth_entry(काष्ठा iscsi_conn *conn)
अणु
	kमुक्त(conn->auth_protocol);
पूर्ण

पूर्णांक iscsi_target_check_login_request(
	काष्ठा iscsi_conn *conn,
	काष्ठा iscsi_login *login)
अणु
	पूर्णांक req_csg, req_nsg;
	u32 payload_length;
	काष्ठा iscsi_login_req *login_req;

	login_req = (काष्ठा iscsi_login_req *) login->req;
	payload_length = ntoh24(login_req->dlength);

	चयन (login_req->opcode & ISCSI_OPCODE_MASK) अणु
	हाल ISCSI_OP_LOGIN:
		अवरोध;
	शेष:
		pr_err("Received unknown opcode 0x%02x.\n",
				login_req->opcode & ISCSI_OPCODE_MASK);
		iscsit_tx_login_rsp(conn, ISCSI_STATUS_CLS_INITIATOR_ERR,
				ISCSI_LOGIN_STATUS_INIT_ERR);
		वापस -1;
	पूर्ण

	अगर ((login_req->flags & ISCSI_FLAG_LOGIN_CONTINUE) &&
	    (login_req->flags & ISCSI_FLAG_LOGIN_TRANSIT)) अणु
		pr_err("Login request has both ISCSI_FLAG_LOGIN_CONTINUE"
			" and ISCSI_FLAG_LOGIN_TRANSIT set, protocol error.\n");
		iscsit_tx_login_rsp(conn, ISCSI_STATUS_CLS_INITIATOR_ERR,
				ISCSI_LOGIN_STATUS_INIT_ERR);
		वापस -1;
	पूर्ण

	req_csg = ISCSI_LOGIN_CURRENT_STAGE(login_req->flags);
	req_nsg = ISCSI_LOGIN_NEXT_STAGE(login_req->flags);

	अगर (req_csg != login->current_stage) अणु
		pr_err("Initiator unexpectedly changed login stage"
			" from %d to %d, login failed.\n", login->current_stage,
			req_csg);
		iscsit_tx_login_rsp(conn, ISCSI_STATUS_CLS_INITIATOR_ERR,
				ISCSI_LOGIN_STATUS_INIT_ERR);
		वापस -1;
	पूर्ण

	अगर ((req_nsg == 2) || (req_csg >= 2) ||
	   ((login_req->flags & ISCSI_FLAG_LOGIN_TRANSIT) &&
	    (req_nsg <= req_csg))) अणु
		pr_err("Illegal login_req->flags Combination, CSG: %d,"
			" NSG: %d, ISCSI_FLAG_LOGIN_TRANSIT: %d.\n", req_csg,
			req_nsg, (login_req->flags & ISCSI_FLAG_LOGIN_TRANSIT));
		iscsit_tx_login_rsp(conn, ISCSI_STATUS_CLS_INITIATOR_ERR,
				ISCSI_LOGIN_STATUS_INIT_ERR);
		वापस -1;
	पूर्ण

	अगर ((login_req->max_version != login->version_max) ||
	    (login_req->min_version != login->version_min)) अणु
		pr_err("Login request changed Version Max/Nin"
			" unexpectedly to 0x%02x/0x%02x, protocol error\n",
			login_req->max_version, login_req->min_version);
		iscsit_tx_login_rsp(conn, ISCSI_STATUS_CLS_INITIATOR_ERR,
				ISCSI_LOGIN_STATUS_INIT_ERR);
		वापस -1;
	पूर्ण

	अगर (स_भेद(login_req->isid, login->isid, 6) != 0) अणु
		pr_err("Login request changed ISID unexpectedly,"
				" protocol error.\n");
		iscsit_tx_login_rsp(conn, ISCSI_STATUS_CLS_INITIATOR_ERR,
				ISCSI_LOGIN_STATUS_INIT_ERR);
		वापस -1;
	पूर्ण

	अगर (login_req->itt != login->init_task_tag) अणु
		pr_err("Login request changed ITT unexpectedly to"
			" 0x%08x, protocol error.\n", login_req->itt);
		iscsit_tx_login_rsp(conn, ISCSI_STATUS_CLS_INITIATOR_ERR,
				ISCSI_LOGIN_STATUS_INIT_ERR);
		वापस -1;
	पूर्ण

	अगर (payload_length > MAX_KEY_VALUE_PAIRS) अणु
		pr_err("Login request payload exceeds default"
			" MaxRecvDataSegmentLength: %u, protocol error.\n",
				MAX_KEY_VALUE_PAIRS);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(iscsi_target_check_login_request);

अटल पूर्णांक iscsi_target_check_first_request(
	काष्ठा iscsi_conn *conn,
	काष्ठा iscsi_login *login)
अणु
	काष्ठा iscsi_param *param = शून्य;
	काष्ठा se_node_acl *se_nacl;

	login->first_request = 0;

	list_क्रम_each_entry(param, &conn->param_list->param_list, p_list) अणु
		अगर (!म_भेदन(param->name, SESSIONTYPE, 11)) अणु
			अगर (!IS_PSTATE_ACCEPTOR(param)) अणु
				pr_err("SessionType key not received"
					" in first login request.\n");
				iscsit_tx_login_rsp(conn, ISCSI_STATUS_CLS_INITIATOR_ERR,
					ISCSI_LOGIN_STATUS_MISSING_FIELDS);
				वापस -1;
			पूर्ण
			अगर (!म_भेदन(param->value, DISCOVERY, 9))
				वापस 0;
		पूर्ण

		अगर (!म_भेदन(param->name, INITIATORNAME, 13)) अणु
			अगर (!IS_PSTATE_ACCEPTOR(param)) अणु
				अगर (!login->leading_connection)
					जारी;

				pr_err("InitiatorName key not received"
					" in first login request.\n");
				iscsit_tx_login_rsp(conn, ISCSI_STATUS_CLS_INITIATOR_ERR,
					ISCSI_LOGIN_STATUS_MISSING_FIELDS);
				वापस -1;
			पूर्ण

			/*
			 * For non-leading connections, द्विगुन check that the
			 * received InitiatorName matches the existing session's
			 * काष्ठा iscsi_node_acl.
			 */
			अगर (!login->leading_connection) अणु
				se_nacl = conn->sess->se_sess->se_node_acl;
				अगर (!se_nacl) अणु
					pr_err("Unable to locate"
						" struct se_node_acl\n");
					iscsit_tx_login_rsp(conn,
							ISCSI_STATUS_CLS_INITIATOR_ERR,
							ISCSI_LOGIN_STATUS_TGT_NOT_FOUND);
					वापस -1;
				पूर्ण

				अगर (म_भेद(param->value,
						se_nacl->initiatorname)) अणु
					pr_err("Incorrect"
						" InitiatorName: %s for this"
						" iSCSI Initiator Node.\n",
						param->value);
					iscsit_tx_login_rsp(conn,
							ISCSI_STATUS_CLS_INITIATOR_ERR,
							ISCSI_LOGIN_STATUS_TGT_NOT_FOUND);
					वापस -1;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक iscsi_target_करो_tx_login_io(काष्ठा iscsi_conn *conn, काष्ठा iscsi_login *login)
अणु
	u32 padding = 0;
	काष्ठा iscsi_login_rsp *login_rsp;

	login_rsp = (काष्ठा iscsi_login_rsp *) login->rsp;

	login_rsp->opcode		= ISCSI_OP_LOGIN_RSP;
	hton24(login_rsp->dlength, login->rsp_length);
	स_नकल(login_rsp->isid, login->isid, 6);
	login_rsp->tsih			= cpu_to_be16(login->tsih);
	login_rsp->itt			= login->init_task_tag;
	login_rsp->statsn		= cpu_to_be32(conn->stat_sn++);
	login_rsp->exp_cmdsn		= cpu_to_be32(conn->sess->exp_cmd_sn);
	login_rsp->max_cmdsn		= cpu_to_be32((u32) atomic_पढ़ो(&conn->sess->max_cmd_sn));

	pr_debug("Sending Login Response, Flags: 0x%02x, ITT: 0x%08x,"
		" ExpCmdSN; 0x%08x, MaxCmdSN: 0x%08x, StatSN: 0x%08x, Length:"
		" %u\n", login_rsp->flags, (__क्रमce u32)login_rsp->itt,
		ntohl(login_rsp->exp_cmdsn), ntohl(login_rsp->max_cmdsn),
		ntohl(login_rsp->statsn), login->rsp_length);

	padding = ((-login->rsp_length) & 3);
	/*
	 * Beक्रमe sending the last login response containing the transition
	 * bit क्रम full-feature-phase, go ahead and start up TX/RX thपढ़ोs
	 * now to aव्योम potential resource allocation failures after the
	 * final login response has been sent.
	 */
	अगर (login->login_complete) अणु
		पूर्णांक rc = iscsit_start_kthपढ़ोs(conn);
		अगर (rc) अणु
			iscsit_tx_login_rsp(conn, ISCSI_STATUS_CLS_TARGET_ERR,
					    ISCSI_LOGIN_STATUS_NO_RESOURCES);
			वापस -1;
		पूर्ण
	पूर्ण

	अगर (conn->conn_transport->iscsit_put_login_tx(conn, login,
					login->rsp_length + padding) < 0)
		जाओ err;

	login->rsp_length		= 0;

	वापस 0;

err:
	अगर (login->login_complete) अणु
		अगर (conn->rx_thपढ़ो && conn->rx_thपढ़ो_active) अणु
			send_sig(संक_विघ्न, conn->rx_thपढ़ो, 1);
			complete(&conn->rx_login_comp);
			kthपढ़ो_stop(conn->rx_thपढ़ो);
		पूर्ण
		अगर (conn->tx_thपढ़ो && conn->tx_thपढ़ो_active) अणु
			send_sig(संक_विघ्न, conn->tx_thपढ़ो, 1);
			kthपढ़ो_stop(conn->tx_thपढ़ो);
		पूर्ण
		spin_lock(&iscsit_global->ts_biपंचांगap_lock);
		biपंचांगap_release_region(iscsit_global->ts_biपंचांगap, conn->biपंचांगap_id,
				      get_order(1));
		spin_unlock(&iscsit_global->ts_biपंचांगap_lock);
	पूर्ण
	वापस -1;
पूर्ण

अटल व्योम iscsi_target_sk_data_पढ़ोy(काष्ठा sock *sk)
अणु
	काष्ठा iscsi_conn *conn = sk->sk_user_data;
	bool rc;

	pr_debug("Entering iscsi_target_sk_data_ready: conn: %p\n", conn);

	ग_लिखो_lock_bh(&sk->sk_callback_lock);
	अगर (!sk->sk_user_data) अणु
		ग_लिखो_unlock_bh(&sk->sk_callback_lock);
		वापस;
	पूर्ण
	अगर (!test_bit(LOGIN_FLAGS_READY, &conn->login_flags)) अणु
		ग_लिखो_unlock_bh(&sk->sk_callback_lock);
		pr_debug("Got LOGIN_FLAGS_READY=0, conn: %p >>>>\n", conn);
		वापस;
	पूर्ण
	अगर (test_bit(LOGIN_FLAGS_CLOSED, &conn->login_flags)) अणु
		ग_लिखो_unlock_bh(&sk->sk_callback_lock);
		pr_debug("Got LOGIN_FLAGS_CLOSED=1, conn: %p >>>>\n", conn);
		वापस;
	पूर्ण
	अगर (test_and_set_bit(LOGIN_FLAGS_READ_ACTIVE, &conn->login_flags)) अणु
		ग_लिखो_unlock_bh(&sk->sk_callback_lock);
		pr_debug("Got LOGIN_FLAGS_READ_ACTIVE=1, conn: %p >>>>\n", conn);
		अगर (iscsi_target_sk_data_पढ़ोy == conn->orig_data_पढ़ोy)
			वापस;
		conn->orig_data_पढ़ोy(sk);
		वापस;
	पूर्ण

	rc = schedule_delayed_work(&conn->login_work, 0);
	अगर (!rc) अणु
		pr_debug("iscsi_target_sk_data_ready, schedule_delayed_work"
			 " got false\n");
	पूर्ण
	ग_लिखो_unlock_bh(&sk->sk_callback_lock);
पूर्ण

अटल व्योम iscsi_target_sk_state_change(काष्ठा sock *);

अटल व्योम iscsi_target_set_sock_callbacks(काष्ठा iscsi_conn *conn)
अणु
	काष्ठा sock *sk;

	अगर (!conn->sock)
		वापस;

	sk = conn->sock->sk;
	pr_debug("Entering iscsi_target_set_sock_callbacks: conn: %p\n", conn);

	ग_लिखो_lock_bh(&sk->sk_callback_lock);
	sk->sk_user_data = conn;
	conn->orig_data_पढ़ोy = sk->sk_data_पढ़ोy;
	conn->orig_state_change = sk->sk_state_change;
	sk->sk_data_पढ़ोy = iscsi_target_sk_data_पढ़ोy;
	sk->sk_state_change = iscsi_target_sk_state_change;
	ग_लिखो_unlock_bh(&sk->sk_callback_lock);

	sk->sk_sndसमयo = TA_LOGIN_TIMEOUT * HZ;
	sk->sk_rcvसमयo = TA_LOGIN_TIMEOUT * HZ;
पूर्ण

अटल व्योम iscsi_target_restore_sock_callbacks(काष्ठा iscsi_conn *conn)
अणु
	काष्ठा sock *sk;

	अगर (!conn->sock)
		वापस;

	sk = conn->sock->sk;
	pr_debug("Entering iscsi_target_restore_sock_callbacks: conn: %p\n", conn);

	ग_लिखो_lock_bh(&sk->sk_callback_lock);
	अगर (!sk->sk_user_data) अणु
		ग_लिखो_unlock_bh(&sk->sk_callback_lock);
		वापस;
	पूर्ण
	sk->sk_user_data = शून्य;
	sk->sk_data_पढ़ोy = conn->orig_data_पढ़ोy;
	sk->sk_state_change = conn->orig_state_change;
	ग_लिखो_unlock_bh(&sk->sk_callback_lock);

	sk->sk_sndसमयo = MAX_SCHEDULE_TIMEOUT;
	sk->sk_rcvसमयo = MAX_SCHEDULE_TIMEOUT;
पूर्ण

अटल पूर्णांक iscsi_target_करो_login(काष्ठा iscsi_conn *, काष्ठा iscsi_login *);

अटल bool __iscsi_target_sk_check_बंद(काष्ठा sock *sk)
अणु
	अगर (sk->sk_state == TCP_CLOSE_WAIT || sk->sk_state == TCP_CLOSE) अणु
		pr_debug("__iscsi_target_sk_check_close: TCP_CLOSE_WAIT|TCP_CLOSE,"
			"returning TRUE\n");
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool iscsi_target_sk_check_बंद(काष्ठा iscsi_conn *conn)
अणु
	bool state = false;

	अगर (conn->sock) अणु
		काष्ठा sock *sk = conn->sock->sk;

		पढ़ो_lock_bh(&sk->sk_callback_lock);
		state = (__iscsi_target_sk_check_बंद(sk) ||
			 test_bit(LOGIN_FLAGS_CLOSED, &conn->login_flags));
		पढ़ो_unlock_bh(&sk->sk_callback_lock);
	पूर्ण
	वापस state;
पूर्ण

अटल bool iscsi_target_sk_check_flag(काष्ठा iscsi_conn *conn, अचिन्हित पूर्णांक flag)
अणु
	bool state = false;

	अगर (conn->sock) अणु
		काष्ठा sock *sk = conn->sock->sk;

		पढ़ो_lock_bh(&sk->sk_callback_lock);
		state = test_bit(flag, &conn->login_flags);
		पढ़ो_unlock_bh(&sk->sk_callback_lock);
	पूर्ण
	वापस state;
पूर्ण

अटल bool iscsi_target_sk_check_and_clear(काष्ठा iscsi_conn *conn, अचिन्हित पूर्णांक flag)
अणु
	bool state = false;

	अगर (conn->sock) अणु
		काष्ठा sock *sk = conn->sock->sk;

		ग_लिखो_lock_bh(&sk->sk_callback_lock);
		state = (__iscsi_target_sk_check_बंद(sk) ||
			 test_bit(LOGIN_FLAGS_CLOSED, &conn->login_flags));
		अगर (!state)
			clear_bit(flag, &conn->login_flags);
		ग_लिखो_unlock_bh(&sk->sk_callback_lock);
	पूर्ण
	वापस state;
पूर्ण

अटल व्योम iscsi_target_login_drop(काष्ठा iscsi_conn *conn, काष्ठा iscsi_login *login)
अणु
	bool zero_tsih = login->zero_tsih;

	iscsi_हटाओ_failed_auth_entry(conn);
	iscsi_target_nego_release(conn);
	iscsi_target_login_sess_out(conn, zero_tsih, true);
पूर्ण

काष्ठा conn_समयout अणु
	काष्ठा समयr_list समयr;
	काष्ठा iscsi_conn *conn;
पूर्ण;

अटल व्योम iscsi_target_login_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा conn_समयout *समयout = from_समयr(समयout, t, समयr);
	काष्ठा iscsi_conn *conn = समयout->conn;

	pr_debug("Entering iscsi_target_login_timeout >>>>>>>>>>>>>>>>>>>\n");

	अगर (conn->login_kworker) अणु
		pr_debug("Sending SIGINT to conn->login_kworker %s/%d\n",
			 conn->login_kworker->comm, conn->login_kworker->pid);
		send_sig(संक_विघ्न, conn->login_kworker, 1);
	पूर्ण
पूर्ण

अटल व्योम iscsi_target_करो_login_rx(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा iscsi_conn *conn = container_of(work,
				काष्ठा iscsi_conn, login_work.work);
	काष्ठा iscsi_login *login = conn->login;
	काष्ठा iscsi_np *np = login->np;
	काष्ठा iscsi_portal_group *tpg = conn->tpg;
	काष्ठा iscsi_tpg_np *tpg_np = conn->tpg_np;
	काष्ठा conn_समयout समयout;
	पूर्णांक rc, zero_tsih = login->zero_tsih;
	bool state;

	pr_debug("entering iscsi_target_do_login_rx, conn: %p, %s:%d\n",
			conn, current->comm, current->pid);
	/*
	 * If iscsi_target_करो_login_rx() has been invoked by ->sk_data_पढ़ोy()
	 * beक्रमe initial PDU processing in iscsi_target_start_negotiation()
	 * has completed, go ahead and retry until it's cleared.
	 *
	 * Otherwise अगर the TCP connection drops जबतक this is occuring,
	 * iscsi_target_start_negotiation() will detect the failure, call
	 * cancel_delayed_work_sync(&conn->login_work), and cleanup the
	 * reमुख्यing iscsi connection resources from iscsi_np process context.
	 */
	अगर (iscsi_target_sk_check_flag(conn, LOGIN_FLAGS_INITIAL_PDU)) अणु
		schedule_delayed_work(&conn->login_work, msecs_to_jअगरfies(10));
		वापस;
	पूर्ण

	spin_lock(&tpg->tpg_state_lock);
	state = (tpg->tpg_state == TPG_STATE_ACTIVE);
	spin_unlock(&tpg->tpg_state_lock);

	अगर (!state) अणु
		pr_debug("iscsi_target_do_login_rx: tpg_state != TPG_STATE_ACTIVE\n");
		जाओ err;
	पूर्ण

	अगर (iscsi_target_sk_check_बंद(conn)) अणु
		pr_debug("iscsi_target_do_login_rx, TCP state CLOSE\n");
		जाओ err;
	पूर्ण

	conn->login_kworker = current;
	allow_संकेत(संक_विघ्न);

	समयout.conn = conn;
	समयr_setup_on_stack(&समयout.समयr, iscsi_target_login_समयout, 0);
	mod_समयr(&समयout.समयr, jअगरfies + TA_LOGIN_TIMEOUT * HZ);
	pr_debug("Starting login timer for %s/%d\n", current->comm, current->pid);

	rc = conn->conn_transport->iscsit_get_login_rx(conn, login);
	del_समयr_sync(&समयout.समयr);
	destroy_समयr_on_stack(&समयout.समयr);
	flush_संकेतs(current);
	conn->login_kworker = शून्य;

	अगर (rc < 0)
		जाओ err;

	pr_debug("iscsi_target_do_login_rx after rx_login_io, %p, %s:%d\n",
			conn, current->comm, current->pid);

	/*
	 * LOGIN_FLAGS_READ_ACTIVE is cleared so that sk_data_पढ़ोy
	 * could be triggered again after this.
	 *
	 * LOGIN_FLAGS_WRITE_ACTIVE is cleared after we successfully
	 * process a login PDU, so that sk_state_chage can करो login
	 * cleanup as needed अगर the socket is बंदd. If a delayed work is
	 * ongoing (LOGIN_FLAGS_WRITE_ACTIVE or LOGIN_FLAGS_READ_ACTIVE),
	 * sk_state_change will leave the cleanup to the delayed work or
	 * it will schedule a delayed work to करो cleanup.
	 */
	अगर (conn->sock) अणु
		काष्ठा sock *sk = conn->sock->sk;

		ग_लिखो_lock_bh(&sk->sk_callback_lock);
		अगर (!test_bit(LOGIN_FLAGS_INITIAL_PDU, &conn->login_flags)) अणु
			clear_bit(LOGIN_FLAGS_READ_ACTIVE, &conn->login_flags);
			set_bit(LOGIN_FLAGS_WRITE_ACTIVE, &conn->login_flags);
		पूर्ण
		ग_लिखो_unlock_bh(&sk->sk_callback_lock);
	पूर्ण

	rc = iscsi_target_करो_login(conn, login);
	अगर (rc < 0) अणु
		जाओ err;
	पूर्ण अन्यथा अगर (!rc) अणु
		अगर (iscsi_target_sk_check_and_clear(conn,
						    LOGIN_FLAGS_WRITE_ACTIVE))
			जाओ err;
	पूर्ण अन्यथा अगर (rc == 1) अणु
		cancel_delayed_work(&conn->login_work);
		iscsi_target_nego_release(conn);
		iscsi_post_login_handler(np, conn, zero_tsih);
		iscsit_deaccess_np(np, tpg, tpg_np);
	पूर्ण
	वापस;

err:
	iscsi_target_restore_sock_callbacks(conn);
	cancel_delayed_work(&conn->login_work);
	iscsi_target_login_drop(conn, login);
	iscsit_deaccess_np(np, tpg, tpg_np);
पूर्ण

अटल व्योम iscsi_target_sk_state_change(काष्ठा sock *sk)
अणु
	काष्ठा iscsi_conn *conn;
	व्योम (*orig_state_change)(काष्ठा sock *);
	bool state;

	pr_debug("Entering iscsi_target_sk_state_change\n");

	ग_लिखो_lock_bh(&sk->sk_callback_lock);
	conn = sk->sk_user_data;
	अगर (!conn) अणु
		ग_लिखो_unlock_bh(&sk->sk_callback_lock);
		वापस;
	पूर्ण
	orig_state_change = conn->orig_state_change;

	अगर (!test_bit(LOGIN_FLAGS_READY, &conn->login_flags)) अणु
		pr_debug("Got LOGIN_FLAGS_READY=0 sk_state_change conn: %p\n",
			 conn);
		ग_लिखो_unlock_bh(&sk->sk_callback_lock);
		orig_state_change(sk);
		वापस;
	पूर्ण
	state = __iscsi_target_sk_check_बंद(sk);
	pr_debug("__iscsi_target_sk_close_change: state: %d\n", state);

	अगर (test_bit(LOGIN_FLAGS_READ_ACTIVE, &conn->login_flags) ||
	    test_bit(LOGIN_FLAGS_WRITE_ACTIVE, &conn->login_flags)) अणु
		pr_debug("Got LOGIN_FLAGS_{READ|WRITE}_ACTIVE=1"
			 " sk_state_change conn: %p\n", conn);
		अगर (state)
			set_bit(LOGIN_FLAGS_CLOSED, &conn->login_flags);
		ग_लिखो_unlock_bh(&sk->sk_callback_lock);
		orig_state_change(sk);
		वापस;
	पूर्ण
	अगर (test_bit(LOGIN_FLAGS_CLOSED, &conn->login_flags)) अणु
		pr_debug("Got LOGIN_FLAGS_CLOSED=1 sk_state_change conn: %p\n",
			 conn);
		ग_लिखो_unlock_bh(&sk->sk_callback_lock);
		orig_state_change(sk);
		वापस;
	पूर्ण
	/*
	 * If the TCP connection has dropped, go ahead and set LOGIN_FLAGS_CLOSED,
	 * but only queue conn->login_work -> iscsi_target_करो_login_rx()
	 * processing अगर LOGIN_FLAGS_INITIAL_PDU has alपढ़ोy been cleared.
	 *
	 * When iscsi_target_करो_login_rx() runs, iscsi_target_sk_check_बंद()
	 * will detect the dropped TCP connection from delayed workqueue context.
	 *
	 * If LOGIN_FLAGS_INITIAL_PDU is still set, which means the initial
	 * iscsi_target_start_negotiation() is running, iscsi_target_करो_login()
	 * via iscsi_target_sk_check_बंद() or iscsi_target_start_negotiation()
	 * via iscsi_target_sk_check_and_clear() is responsible क्रम detecting the
	 * dropped TCP connection in iscsi_np process context, and cleaning up
	 * the reमुख्यing iscsi connection resources.
	 */
	अगर (state) अणु
		pr_debug("iscsi_target_sk_state_change got failed state\n");
		set_bit(LOGIN_FLAGS_CLOSED, &conn->login_flags);
		state = test_bit(LOGIN_FLAGS_INITIAL_PDU, &conn->login_flags);
		ग_लिखो_unlock_bh(&sk->sk_callback_lock);

		orig_state_change(sk);

		अगर (!state)
			schedule_delayed_work(&conn->login_work, 0);
		वापस;
	पूर्ण
	ग_लिखो_unlock_bh(&sk->sk_callback_lock);

	orig_state_change(sk);
पूर्ण

/*
 *	NOTE: We check क्रम existing sessions or connections AFTER the initiator
 *	has been successfully authenticated in order to protect against faked
 *	ISID/TSIH combinations.
 */
अटल पूर्णांक iscsi_target_check_क्रम_existing_instances(
	काष्ठा iscsi_conn *conn,
	काष्ठा iscsi_login *login)
अणु
	अगर (login->checked_क्रम_existing)
		वापस 0;

	login->checked_क्रम_existing = 1;

	अगर (!login->tsih)
		वापस iscsi_check_क्रम_session_reinstatement(conn);
	अन्यथा
		वापस iscsi_login_post_auth_non_zero_tsih(conn, login->cid,
				login->initial_exp_statsn);
पूर्ण

अटल पूर्णांक iscsi_target_करो_authentication(
	काष्ठा iscsi_conn *conn,
	काष्ठा iscsi_login *login)
अणु
	पूर्णांक authret;
	u32 payload_length;
	काष्ठा iscsi_param *param;
	काष्ठा iscsi_login_req *login_req;
	काष्ठा iscsi_login_rsp *login_rsp;

	login_req = (काष्ठा iscsi_login_req *) login->req;
	login_rsp = (काष्ठा iscsi_login_rsp *) login->rsp;
	payload_length = ntoh24(login_req->dlength);

	param = iscsi_find_param_from_key(AUTHMETHOD, conn->param_list);
	अगर (!param)
		वापस -1;

	authret = iscsi_handle_authentication(
			conn,
			login->req_buf,
			login->rsp_buf,
			payload_length,
			&login->rsp_length,
			param->value);
	चयन (authret) अणु
	हाल 0:
		pr_debug("Received OK response"
		" from LIO Authentication, continuing.\n");
		अवरोध;
	हाल 1:
		pr_debug("iSCSI security negotiation"
			" completed successfully.\n");
		login->auth_complete = 1;
		अगर ((login_req->flags & ISCSI_FLAG_LOGIN_NEXT_STAGE1) &&
		    (login_req->flags & ISCSI_FLAG_LOGIN_TRANSIT)) अणु
			login_rsp->flags |= (ISCSI_FLAG_LOGIN_NEXT_STAGE1 |
					     ISCSI_FLAG_LOGIN_TRANSIT);
			login->current_stage = 1;
		पूर्ण
		वापस iscsi_target_check_क्रम_existing_instances(
				conn, login);
	हाल 2:
		pr_err("Security negotiation"
			" failed.\n");
		iscsit_tx_login_rsp(conn, ISCSI_STATUS_CLS_INITIATOR_ERR,
				ISCSI_LOGIN_STATUS_AUTH_FAILED);
		वापस -1;
	शेष:
		pr_err("Received unknown error %d from LIO"
				" Authentication\n", authret);
		iscsit_tx_login_rsp(conn, ISCSI_STATUS_CLS_TARGET_ERR,
				ISCSI_LOGIN_STATUS_TARGET_ERROR);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक iscsi_target_handle_csg_zero(
	काष्ठा iscsi_conn *conn,
	काष्ठा iscsi_login *login)
अणु
	पूर्णांक ret;
	u32 payload_length;
	काष्ठा iscsi_param *param;
	काष्ठा iscsi_login_req *login_req;
	काष्ठा iscsi_login_rsp *login_rsp;

	login_req = (काष्ठा iscsi_login_req *) login->req;
	login_rsp = (काष्ठा iscsi_login_rsp *) login->rsp;
	payload_length = ntoh24(login_req->dlength);

	param = iscsi_find_param_from_key(AUTHMETHOD, conn->param_list);
	अगर (!param)
		वापस -1;

	ret = iscsi_decode_text_input(
			PHASE_SECURITY|PHASE_DECLARATIVE,
			SENDER_INITIATOR|SENDER_RECEIVER,
			login->req_buf,
			payload_length,
			conn);
	अगर (ret < 0)
		वापस -1;

	अगर (ret > 0) अणु
		अगर (login->auth_complete) अणु
			pr_err("Initiator has already been"
				" successfully authenticated, but is still"
				" sending %s keys.\n", param->value);
			iscsit_tx_login_rsp(conn, ISCSI_STATUS_CLS_INITIATOR_ERR,
					ISCSI_LOGIN_STATUS_INIT_ERR);
			वापस -1;
		पूर्ण

		जाओ करो_auth;
	पूर्ण अन्यथा अगर (!payload_length) अणु
		pr_err("Initiator sent zero length security payload,"
		       " login failed\n");
		iscsit_tx_login_rsp(conn, ISCSI_STATUS_CLS_INITIATOR_ERR,
				    ISCSI_LOGIN_STATUS_AUTH_FAILED);
		वापस -1;
	पूर्ण

	अगर (login->first_request)
		अगर (iscsi_target_check_first_request(conn, login) < 0)
			वापस -1;

	ret = iscsi_encode_text_output(
			PHASE_SECURITY|PHASE_DECLARATIVE,
			SENDER_TARGET,
			login->rsp_buf,
			&login->rsp_length,
			conn->param_list,
			conn->tpg->tpg_attrib.login_keys_workaround);
	अगर (ret < 0)
		वापस -1;

	अगर (!iscsi_check_negotiated_keys(conn->param_list)) अणु
		अगर (conn->tpg->tpg_attrib.authentication &&
		    !म_भेदन(param->value, NONE, 4)) अणु
			pr_err("Initiator sent AuthMethod=None but"
				" Target is enforcing iSCSI Authentication,"
					" login failed.\n");
			iscsit_tx_login_rsp(conn, ISCSI_STATUS_CLS_INITIATOR_ERR,
					ISCSI_LOGIN_STATUS_AUTH_FAILED);
			वापस -1;
		पूर्ण

		अगर (conn->tpg->tpg_attrib.authentication &&
		    !login->auth_complete)
			वापस 0;

		अगर (म_भेदन(param->value, NONE, 4) && !login->auth_complete)
			वापस 0;

		अगर ((login_req->flags & ISCSI_FLAG_LOGIN_NEXT_STAGE1) &&
		    (login_req->flags & ISCSI_FLAG_LOGIN_TRANSIT)) अणु
			login_rsp->flags |= ISCSI_FLAG_LOGIN_NEXT_STAGE1 |
					    ISCSI_FLAG_LOGIN_TRANSIT;
			login->current_stage = 1;
		पूर्ण
	पूर्ण

	वापस 0;
करो_auth:
	वापस iscsi_target_करो_authentication(conn, login);
पूर्ण

अटल पूर्णांक iscsi_target_handle_csg_one(काष्ठा iscsi_conn *conn, काष्ठा iscsi_login *login)
अणु
	पूर्णांक ret;
	u32 payload_length;
	काष्ठा iscsi_login_req *login_req;
	काष्ठा iscsi_login_rsp *login_rsp;

	login_req = (काष्ठा iscsi_login_req *) login->req;
	login_rsp = (काष्ठा iscsi_login_rsp *) login->rsp;
	payload_length = ntoh24(login_req->dlength);

	ret = iscsi_decode_text_input(
			PHASE_OPERATIONAL|PHASE_DECLARATIVE,
			SENDER_INITIATOR|SENDER_RECEIVER,
			login->req_buf,
			payload_length,
			conn);
	अगर (ret < 0) अणु
		iscsit_tx_login_rsp(conn, ISCSI_STATUS_CLS_INITIATOR_ERR,
				ISCSI_LOGIN_STATUS_INIT_ERR);
		वापस -1;
	पूर्ण

	अगर (login->first_request)
		अगर (iscsi_target_check_first_request(conn, login) < 0)
			वापस -1;

	अगर (iscsi_target_check_क्रम_existing_instances(conn, login) < 0)
		वापस -1;

	ret = iscsi_encode_text_output(
			PHASE_OPERATIONAL|PHASE_DECLARATIVE,
			SENDER_TARGET,
			login->rsp_buf,
			&login->rsp_length,
			conn->param_list,
			conn->tpg->tpg_attrib.login_keys_workaround);
	अगर (ret < 0) अणु
		iscsit_tx_login_rsp(conn, ISCSI_STATUS_CLS_INITIATOR_ERR,
				ISCSI_LOGIN_STATUS_INIT_ERR);
		वापस -1;
	पूर्ण

	अगर (!login->auth_complete &&
	     conn->tpg->tpg_attrib.authentication) अणु
		pr_err("Initiator is requesting CSG: 1, has not been"
			 " successfully authenticated, and the Target is"
			" enforcing iSCSI Authentication, login failed.\n");
		iscsit_tx_login_rsp(conn, ISCSI_STATUS_CLS_INITIATOR_ERR,
				ISCSI_LOGIN_STATUS_AUTH_FAILED);
		वापस -1;
	पूर्ण

	अगर (!iscsi_check_negotiated_keys(conn->param_list))
		अगर ((login_req->flags & ISCSI_FLAG_LOGIN_NEXT_STAGE3) &&
		    (login_req->flags & ISCSI_FLAG_LOGIN_TRANSIT))
			login_rsp->flags |= ISCSI_FLAG_LOGIN_NEXT_STAGE3 |
					    ISCSI_FLAG_LOGIN_TRANSIT;

	वापस 0;
पूर्ण

अटल पूर्णांक iscsi_target_करो_login(काष्ठा iscsi_conn *conn, काष्ठा iscsi_login *login)
अणु
	पूर्णांक pdu_count = 0;
	काष्ठा iscsi_login_req *login_req;
	काष्ठा iscsi_login_rsp *login_rsp;

	login_req = (काष्ठा iscsi_login_req *) login->req;
	login_rsp = (काष्ठा iscsi_login_rsp *) login->rsp;

	जबतक (1) अणु
		अगर (++pdu_count > MAX_LOGIN_PDUS) अणु
			pr_err("MAX_LOGIN_PDUS count reached.\n");
			iscsit_tx_login_rsp(conn, ISCSI_STATUS_CLS_TARGET_ERR,
					ISCSI_LOGIN_STATUS_TARGET_ERROR);
			वापस -1;
		पूर्ण

		चयन (ISCSI_LOGIN_CURRENT_STAGE(login_req->flags)) अणु
		हाल 0:
			login_rsp->flags &= ~ISCSI_FLAG_LOGIN_CURRENT_STAGE_MASK;
			अगर (iscsi_target_handle_csg_zero(conn, login) < 0)
				वापस -1;
			अवरोध;
		हाल 1:
			login_rsp->flags |= ISCSI_FLAG_LOGIN_CURRENT_STAGE1;
			अगर (iscsi_target_handle_csg_one(conn, login) < 0)
				वापस -1;
			अगर (login_rsp->flags & ISCSI_FLAG_LOGIN_TRANSIT) अणु
				/*
				 * Check to make sure the TCP connection has not
				 * dropped asynchronously जबतक session reinstatement
				 * was occuring in this kthपढ़ो context, beक्रमe
				 * transitioning to full feature phase operation.
				 */
				अगर (iscsi_target_sk_check_बंद(conn))
					वापस -1;

				login->tsih = conn->sess->tsih;
				login->login_complete = 1;
				iscsi_target_restore_sock_callbacks(conn);
				अगर (iscsi_target_करो_tx_login_io(conn,
						login) < 0)
					वापस -1;
				वापस 1;
			पूर्ण
			अवरोध;
		शेष:
			pr_err("Illegal CSG: %d received from"
				" Initiator, protocol error.\n",
				ISCSI_LOGIN_CURRENT_STAGE(login_req->flags));
			अवरोध;
		पूर्ण

		अगर (iscsi_target_करो_tx_login_io(conn, login) < 0)
			वापस -1;

		अगर (login_rsp->flags & ISCSI_FLAG_LOGIN_TRANSIT) अणु
			login_rsp->flags &= ~ISCSI_FLAG_LOGIN_TRANSIT;
			login_rsp->flags &= ~ISCSI_FLAG_LOGIN_NEXT_STAGE_MASK;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम iscsi_initiatorname_छोटे(
	अक्षर *param_buf)
अणु
	अक्षर *c;
	u32 iqn_size = म_माप(param_buf), i;

	क्रम (i = 0; i < iqn_size; i++) अणु
		c = &param_buf[i];
		अगर (!है_बड़ा(*c))
			जारी;

		*c = छोटे(*c);
	पूर्ण
पूर्ण

/*
 * Processes the first Login Request..
 */
पूर्णांक iscsi_target_locate_portal(
	काष्ठा iscsi_np *np,
	काष्ठा iscsi_conn *conn,
	काष्ठा iscsi_login *login)
अणु
	अक्षर *i_buf = शून्य, *s_buf = शून्य, *t_buf = शून्य;
	अक्षर *पंचांगpbuf, *start = शून्य, *end = शून्य, *key, *value;
	काष्ठा iscsi_session *sess = conn->sess;
	काष्ठा iscsi_tiqn *tiqn;
	काष्ठा iscsi_tpg_np *tpg_np = शून्य;
	काष्ठा iscsi_login_req *login_req;
	काष्ठा se_node_acl *se_nacl;
	u32 payload_length, queue_depth = 0;
	पूर्णांक sessiontype = 0, ret = 0, tag_num, tag_size;

	INIT_DELAYED_WORK(&conn->login_work, iscsi_target_करो_login_rx);
	iscsi_target_set_sock_callbacks(conn);

	login->np = np;

	login_req = (काष्ठा iscsi_login_req *) login->req;
	payload_length = ntoh24(login_req->dlength);

	पंचांगpbuf = kzalloc(payload_length + 1, GFP_KERNEL);
	अगर (!पंचांगpbuf) अणु
		pr_err("Unable to allocate memory for tmpbuf.\n");
		वापस -1;
	पूर्ण

	स_नकल(पंचांगpbuf, login->req_buf, payload_length);
	पंचांगpbuf[payload_length] = '\0';
	start = पंचांगpbuf;
	end = (start + payload_length);

	/*
	 * Locate the initial keys expected from the Initiator node in
	 * the first login request in order to progress with the login phase.
	 */
	जबतक (start < end) अणु
		अगर (iscsi_extract_key_value(start, &key, &value) < 0) अणु
			ret = -1;
			जाओ out;
		पूर्ण

		अगर (!म_भेदन(key, "InitiatorName", 13))
			i_buf = value;
		अन्यथा अगर (!म_भेदन(key, "SessionType", 11))
			s_buf = value;
		अन्यथा अगर (!म_भेदन(key, "TargetName", 10))
			t_buf = value;

		start += म_माप(key) + म_माप(value) + 2;
	पूर्ण
	/*
	 * See 5.3.  Login Phase.
	 */
	अगर (!i_buf) अणु
		pr_err("InitiatorName key not received"
			" in first login request.\n");
		iscsit_tx_login_rsp(conn, ISCSI_STATUS_CLS_INITIATOR_ERR,
			ISCSI_LOGIN_STATUS_MISSING_FIELDS);
		ret = -1;
		जाओ out;
	पूर्ण
	/*
	 * Convert the incoming InitiatorName to lowerहाल following
	 * RFC-3720 3.2.6.1. section c) that says that iSCSI IQNs
	 * are NOT हाल sensitive.
	 */
	iscsi_initiatorname_छोटे(i_buf);

	अगर (!s_buf) अणु
		अगर (!login->leading_connection)
			जाओ get_target;

		pr_err("SessionType key not received"
			" in first login request.\n");
		iscsit_tx_login_rsp(conn, ISCSI_STATUS_CLS_INITIATOR_ERR,
			ISCSI_LOGIN_STATUS_MISSING_FIELDS);
		ret = -1;
		जाओ out;
	पूर्ण

	/*
	 * Use शेष portal group क्रम discovery sessions.
	 */
	sessiontype = म_भेदन(s_buf, DISCOVERY, 9);
	अगर (!sessiontype) अणु
		conn->tpg = iscsit_global->discovery_tpg;
		अगर (!login->leading_connection)
			जाओ get_target;

		sess->sess_ops->SessionType = 1;
		/*
		 * Setup crc32c modules from libcrypto
		 */
		अगर (iscsi_login_setup_crypto(conn) < 0) अणु
			pr_err("iscsi_login_setup_crypto() failed\n");
			ret = -1;
			जाओ out;
		पूर्ण
		/*
		 * Serialize access across the discovery काष्ठा iscsi_portal_group to
		 * process login attempt.
		 */
		अगर (iscsit_access_np(np, conn->tpg) < 0) अणु
			iscsit_tx_login_rsp(conn, ISCSI_STATUS_CLS_TARGET_ERR,
				ISCSI_LOGIN_STATUS_SVC_UNAVAILABLE);
			ret = -1;
			जाओ out;
		पूर्ण
		ret = 0;
		जाओ alloc_tags;
	पूर्ण

get_target:
	अगर (!t_buf) अणु
		pr_err("TargetName key not received"
			" in first login request while"
			" SessionType=Normal.\n");
		iscsit_tx_login_rsp(conn, ISCSI_STATUS_CLS_INITIATOR_ERR,
			ISCSI_LOGIN_STATUS_MISSING_FIELDS);
		ret = -1;
		जाओ out;
	पूर्ण

	/*
	 * Locate Target IQN from Storage Node.
	 */
	tiqn = iscsit_get_tiqn_क्रम_login(t_buf);
	अगर (!tiqn) अणु
		pr_err("Unable to locate Target IQN: %s in"
			" Storage Node\n", t_buf);
		iscsit_tx_login_rsp(conn, ISCSI_STATUS_CLS_TARGET_ERR,
				ISCSI_LOGIN_STATUS_SVC_UNAVAILABLE);
		ret = -1;
		जाओ out;
	पूर्ण
	pr_debug("Located Storage Object: %s\n", tiqn->tiqn);

	/*
	 * Locate Target Portal Group from Storage Node.
	 */
	conn->tpg = iscsit_get_tpg_from_np(tiqn, np, &tpg_np);
	अगर (!conn->tpg) अणु
		pr_err("Unable to locate Target Portal Group"
				" on %s\n", tiqn->tiqn);
		iscsit_put_tiqn_क्रम_login(tiqn);
		iscsit_tx_login_rsp(conn, ISCSI_STATUS_CLS_TARGET_ERR,
				ISCSI_LOGIN_STATUS_SVC_UNAVAILABLE);
		ret = -1;
		जाओ out;
	पूर्ण
	conn->tpg_np = tpg_np;
	pr_debug("Located Portal Group Object: %hu\n", conn->tpg->tpgt);
	/*
	 * Setup crc32c modules from libcrypto
	 */
	अगर (iscsi_login_setup_crypto(conn) < 0) अणु
		pr_err("iscsi_login_setup_crypto() failed\n");
		kref_put(&tpg_np->tpg_np_kref, iscsit_login_kref_put);
		iscsit_put_tiqn_क्रम_login(tiqn);
		conn->tpg = शून्य;
		ret = -1;
		जाओ out;
	पूर्ण
	/*
	 * Serialize access across the काष्ठा iscsi_portal_group to
	 * process login attempt.
	 */
	अगर (iscsit_access_np(np, conn->tpg) < 0) अणु
		kref_put(&tpg_np->tpg_np_kref, iscsit_login_kref_put);
		iscsit_put_tiqn_क्रम_login(tiqn);
		iscsit_tx_login_rsp(conn, ISCSI_STATUS_CLS_TARGET_ERR,
				ISCSI_LOGIN_STATUS_SVC_UNAVAILABLE);
		conn->tpg = शून्य;
		ret = -1;
		जाओ out;
	पूर्ण

	/*
	 * conn->sess->node_acl will be set when the referenced
	 * काष्ठा iscsi_session is located from received ISID+TSIH in
	 * iscsi_login_non_zero_tsih_s2().
	 */
	अगर (!login->leading_connection) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	/*
	 * This value is required in iscsi_login_zero_tsih_s2()
	 */
	sess->sess_ops->SessionType = 0;

	/*
	 * Locate incoming Initiator IQN reference from Storage Node.
	 */
	sess->se_sess->se_node_acl = core_tpg_check_initiator_node_acl(
			&conn->tpg->tpg_se_tpg, i_buf);
	अगर (!sess->se_sess->se_node_acl) अणु
		pr_err("iSCSI Initiator Node: %s is not authorized to"
			" access iSCSI target portal group: %hu.\n",
				i_buf, conn->tpg->tpgt);
		iscsit_tx_login_rsp(conn, ISCSI_STATUS_CLS_INITIATOR_ERR,
				ISCSI_LOGIN_STATUS_TGT_FORBIDDEN);
		ret = -1;
		जाओ out;
	पूर्ण
	se_nacl = sess->se_sess->se_node_acl;
	queue_depth = se_nacl->queue_depth;
	/*
	 * Setup pre-allocated tags based upon allowed per NodeACL CmdSN
	 * depth क्रम non immediate commands, plus extra tags क्रम immediate
	 * commands.
	 *
	 * Also enक्रमce a ISCSIT_MIN_TAGS to prevent unnecessary contention
	 * in per-cpu-ida tag allocation logic + small queue_depth.
	 */
alloc_tags:
	tag_num = max_t(u32, ISCSIT_MIN_TAGS, queue_depth);
	tag_num = (tag_num * 2) + ISCSIT_EXTRA_TAGS;
	tag_size = माप(काष्ठा iscsi_cmd) + conn->conn_transport->priv_size;

	ret = transport_alloc_session_tags(sess->se_sess, tag_num, tag_size);
	अगर (ret < 0) अणु
		iscsit_tx_login_rsp(conn, ISCSI_STATUS_CLS_TARGET_ERR,
				    ISCSI_LOGIN_STATUS_NO_RESOURCES);
		ret = -1;
	पूर्ण
out:
	kमुक्त(पंचांगpbuf);
	वापस ret;
पूर्ण

पूर्णांक iscsi_target_start_negotiation(
	काष्ठा iscsi_login *login,
	काष्ठा iscsi_conn *conn)
अणु
	पूर्णांक ret;

	अगर (conn->sock) अणु
		काष्ठा sock *sk = conn->sock->sk;

		ग_लिखो_lock_bh(&sk->sk_callback_lock);
		set_bit(LOGIN_FLAGS_READY, &conn->login_flags);
		set_bit(LOGIN_FLAGS_INITIAL_PDU, &conn->login_flags);
		ग_लिखो_unlock_bh(&sk->sk_callback_lock);
	पूर्ण
	/*
	 * If iscsi_target_करो_login वापसs zero to संकेत more PDU
	 * exchanges are required to complete the login, go ahead and
	 * clear LOGIN_FLAGS_INITIAL_PDU but only अगर the TCP connection
	 * is still active.
	 *
	 * Otherwise अगर TCP connection dropped asynchronously, go ahead
	 * and perक्रमm connection cleanup now.
	 */
	ret = iscsi_target_करो_login(conn, login);
	अगर (!ret && iscsi_target_sk_check_and_clear(conn, LOGIN_FLAGS_INITIAL_PDU))
		ret = -1;

	अगर (ret < 0) अणु
		cancel_delayed_work_sync(&conn->login_work);
		iscsi_target_restore_sock_callbacks(conn);
		iscsi_हटाओ_failed_auth_entry(conn);
	पूर्ण
	अगर (ret != 0)
		iscsi_target_nego_release(conn);

	वापस ret;
पूर्ण

व्योम iscsi_target_nego_release(काष्ठा iscsi_conn *conn)
अणु
	काष्ठा iscsi_login *login = conn->conn_login;

	अगर (!login)
		वापस;

	kमुक्त(login->req_buf);
	kमुक्त(login->rsp_buf);
	kमुक्त(login);

	conn->conn_login = शून्य;
पूर्ण
