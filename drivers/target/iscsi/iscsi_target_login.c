<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*******************************************************************************
 * This file contains the login functions used by the iSCSI Target driver.
 *
 * (c) Copyright 2007-2013 Datera, Inc.
 *
 * Author: Nicholas A. Bellinger <nab@linux-iscsi.org>
 *
 ******************************************************************************/

#समावेश <crypto/hash.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/idr.h>
#समावेश <linux/tcp.h>        /* TCP_NODELAY */
#समावेश <net/ip.h>
#समावेश <net/ipv6.h>         /* ipv6_addr_v4mapped() */
#समावेश <scsi/iscsi_proto.h>
#समावेश <target/target_core_base.h>
#समावेश <target/target_core_fabric.h>

#समावेश <target/iscsi/iscsi_target_core.h>
#समावेश <target/iscsi/iscsi_target_स्थिति.स>
#समावेश "iscsi_target_device.h"
#समावेश "iscsi_target_nego.h"
#समावेश "iscsi_target_erl0.h"
#समावेश "iscsi_target_erl2.h"
#समावेश "iscsi_target_login.h"
#समावेश "iscsi_target_tpg.h"
#समावेश "iscsi_target_util.h"
#समावेश "iscsi_target.h"
#समावेश "iscsi_target_parameters.h"

#समावेश <target/iscsi/iscsi_transport.h>

अटल काष्ठा iscsi_login *iscsi_login_init_conn(काष्ठा iscsi_conn *conn)
अणु
	काष्ठा iscsi_login *login;

	login = kzalloc(माप(काष्ठा iscsi_login), GFP_KERNEL);
	अगर (!login) अणु
		pr_err("Unable to allocate memory for struct iscsi_login.\n");
		वापस शून्य;
	पूर्ण
	conn->login = login;
	login->conn = conn;
	login->first_request = 1;

	login->req_buf = kzalloc(MAX_KEY_VALUE_PAIRS, GFP_KERNEL);
	अगर (!login->req_buf) अणु
		pr_err("Unable to allocate memory for response buffer.\n");
		जाओ out_login;
	पूर्ण

	login->rsp_buf = kzalloc(MAX_KEY_VALUE_PAIRS, GFP_KERNEL);
	अगर (!login->rsp_buf) अणु
		pr_err("Unable to allocate memory for request buffer.\n");
		जाओ out_req_buf;
	पूर्ण

	conn->conn_login = login;

	वापस login;

out_req_buf:
	kमुक्त(login->req_buf);
out_login:
	kमुक्त(login);
	वापस शून्य;
पूर्ण

/*
 * Used by iscsi_target_nego.c:iscsi_target_locate_portal() to setup
 * per काष्ठा iscsi_conn libcrypto contexts क्रम crc32c and crc32-पूर्णांकel
 */
पूर्णांक iscsi_login_setup_crypto(काष्ठा iscsi_conn *conn)
अणु
	काष्ठा crypto_ahash *tfm;

	/*
	 * Setup slicing by CRC32C algorithm क्रम RX and TX libcrypto contexts
	 * which will शेष to crc32c_पूर्णांकel.ko क्रम cpu_has_xmm4_2, or fallback
	 * to software 1x8 byte slicing from crc32c.ko
	 */
	tfm = crypto_alloc_ahash("crc32c", 0, CRYPTO_ALG_ASYNC);
	अगर (IS_ERR(tfm)) अणु
		pr_err("crypto_alloc_ahash() failed\n");
		वापस -ENOMEM;
	पूर्ण

	conn->conn_rx_hash = ahash_request_alloc(tfm, GFP_KERNEL);
	अगर (!conn->conn_rx_hash) अणु
		pr_err("ahash_request_alloc() failed for conn_rx_hash\n");
		crypto_मुक्त_ahash(tfm);
		वापस -ENOMEM;
	पूर्ण
	ahash_request_set_callback(conn->conn_rx_hash, 0, शून्य, शून्य);

	conn->conn_tx_hash = ahash_request_alloc(tfm, GFP_KERNEL);
	अगर (!conn->conn_tx_hash) अणु
		pr_err("ahash_request_alloc() failed for conn_tx_hash\n");
		ahash_request_मुक्त(conn->conn_rx_hash);
		conn->conn_rx_hash = शून्य;
		crypto_मुक्त_ahash(tfm);
		वापस -ENOMEM;
	पूर्ण
	ahash_request_set_callback(conn->conn_tx_hash, 0, शून्य, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक iscsi_login_check_initiator_version(
	काष्ठा iscsi_conn *conn,
	u8 version_max,
	u8 version_min)
अणु
	अगर ((version_max != 0x00) || (version_min != 0x00)) अणु
		pr_err("Unsupported iSCSI IETF Pre-RFC Revision,"
			" version Min/Max 0x%02x/0x%02x, rejecting login.\n",
			version_min, version_max);
		iscsit_tx_login_rsp(conn, ISCSI_STATUS_CLS_INITIATOR_ERR,
				ISCSI_LOGIN_STATUS_NO_VERSION);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक iscsi_check_क्रम_session_reinstatement(काष्ठा iscsi_conn *conn)
अणु
	पूर्णांक sessiontype;
	काष्ठा iscsi_param *initiatorname_param = शून्य, *sessiontype_param = शून्य;
	काष्ठा iscsi_portal_group *tpg = conn->tpg;
	काष्ठा iscsi_session *sess = शून्य, *sess_p = शून्य;
	काष्ठा se_portal_group *se_tpg = &tpg->tpg_se_tpg;
	काष्ठा se_session *se_sess, *se_sess_पंचांगp;

	initiatorname_param = iscsi_find_param_from_key(
			INITIATORNAME, conn->param_list);
	sessiontype_param = iscsi_find_param_from_key(
			SESSIONTYPE, conn->param_list);
	अगर (!initiatorname_param || !sessiontype_param) अणु
		iscsit_tx_login_rsp(conn, ISCSI_STATUS_CLS_INITIATOR_ERR,
			ISCSI_LOGIN_STATUS_MISSING_FIELDS);
		वापस -1;
	पूर्ण

	sessiontype = (म_भेदन(sessiontype_param->value, NORMAL, 6)) ? 1 : 0;

	spin_lock_bh(&se_tpg->session_lock);
	list_क्रम_each_entry_safe(se_sess, se_sess_पंचांगp, &se_tpg->tpg_sess_list,
			sess_list) अणु

		sess_p = se_sess->fabric_sess_ptr;
		spin_lock(&sess_p->conn_lock);
		अगर (atomic_पढ़ो(&sess_p->session_fall_back_to_erl0) ||
		    atomic_पढ़ो(&sess_p->session_logout) ||
		    atomic_पढ़ो(&sess_p->session_बंद) ||
		    (sess_p->समय2retain_समयr_flags & ISCSI_TF_EXPIRED)) अणु
			spin_unlock(&sess_p->conn_lock);
			जारी;
		पूर्ण
		अगर (!स_भेद(sess_p->isid, conn->sess->isid, 6) &&
		   (!म_भेद(sess_p->sess_ops->InitiatorName,
			    initiatorname_param->value) &&
		   (sess_p->sess_ops->SessionType == sessiontype))) अणु
			atomic_set(&sess_p->session_reinstatement, 1);
			atomic_set(&sess_p->session_fall_back_to_erl0, 1);
			atomic_set(&sess_p->session_बंद, 1);
			spin_unlock(&sess_p->conn_lock);
			iscsit_inc_session_usage_count(sess_p);
			iscsit_stop_समय2retain_समयr(sess_p);
			sess = sess_p;
			अवरोध;
		पूर्ण
		spin_unlock(&sess_p->conn_lock);
	पूर्ण
	spin_unlock_bh(&se_tpg->session_lock);
	/*
	 * If the Time2Retain handler has expired, the session is alपढ़ोy gone.
	 */
	अगर (!sess)
		वापस 0;

	pr_debug("%s iSCSI Session SID %u is still active for %s,"
		" performing session reinstatement.\n", (sessiontype) ?
		"Discovery" : "Normal", sess->sid,
		sess->sess_ops->InitiatorName);

	spin_lock_bh(&sess->conn_lock);
	अगर (sess->session_state == TARG_SESS_STATE_FAILED) अणु
		spin_unlock_bh(&sess->conn_lock);
		iscsit_dec_session_usage_count(sess);
		वापस 0;
	पूर्ण
	spin_unlock_bh(&sess->conn_lock);

	iscsit_stop_session(sess, 1, 1);
	iscsit_dec_session_usage_count(sess);

	वापस 0;
पूर्ण

अटल पूर्णांक iscsi_login_set_conn_values(
	काष्ठा iscsi_session *sess,
	काष्ठा iscsi_conn *conn,
	__be16 cid)
अणु
	पूर्णांक ret;
	conn->sess		= sess;
	conn->cid		= be16_to_cpu(cid);
	/*
	 * Generate a अक्रमom Status sequence number (statsn) क्रम the new
	 * iSCSI connection.
	 */
	ret = get_अक्रमom_bytes_रुको(&conn->stat_sn, माप(u32));
	अगर (unlikely(ret))
		वापस ret;

	mutex_lock(&auth_id_lock);
	conn->auth_id		= iscsit_global->auth_id++;
	mutex_unlock(&auth_id_lock);
	वापस 0;
पूर्ण

__म_लिखो(2, 3) पूर्णांक iscsi_change_param_प्र_लिखो(
	काष्ठा iscsi_conn *conn,
	स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	अचिन्हित अक्षर buf[64];

	स_रखो(buf, 0, माप buf);

	बहु_शुरू(args, fmt);
	vsnम_लिखो(buf, माप buf, fmt, args);
	बहु_पूर्ण(args);

	अगर (iscsi_change_param_value(buf, conn->param_list, 0) < 0) अणु
		iscsit_tx_login_rsp(conn, ISCSI_STATUS_CLS_TARGET_ERR,
				ISCSI_LOGIN_STATUS_NO_RESOURCES);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(iscsi_change_param_प्र_लिखो);

/*
 *	This is the leading connection of a new session,
 *	or session reinstatement.
 */
अटल पूर्णांक iscsi_login_zero_tsih_s1(
	काष्ठा iscsi_conn *conn,
	अचिन्हित अक्षर *buf)
अणु
	काष्ठा iscsi_session *sess = शून्य;
	काष्ठा iscsi_login_req *pdu = (काष्ठा iscsi_login_req *)buf;
	पूर्णांक ret;

	sess = kzalloc(माप(काष्ठा iscsi_session), GFP_KERNEL);
	अगर (!sess) अणु
		iscsit_tx_login_rsp(conn, ISCSI_STATUS_CLS_TARGET_ERR,
				ISCSI_LOGIN_STATUS_NO_RESOURCES);
		pr_err("Could not allocate memory for session\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (iscsi_login_set_conn_values(sess, conn, pdu->cid))
		जाओ मुक्त_sess;

	sess->init_task_tag	= pdu->itt;
	स_नकल(&sess->isid, pdu->isid, 6);
	sess->exp_cmd_sn	= be32_to_cpu(pdu->cmdsn);
	INIT_LIST_HEAD(&sess->sess_conn_list);
	INIT_LIST_HEAD(&sess->sess_ooo_cmdsn_list);
	INIT_LIST_HEAD(&sess->cr_active_list);
	INIT_LIST_HEAD(&sess->cr_inactive_list);
	init_completion(&sess->async_msg_comp);
	init_completion(&sess->reinstatement_comp);
	init_completion(&sess->session_रुको_comp);
	init_completion(&sess->session_रुकोing_on_uc_comp);
	mutex_init(&sess->cmdsn_mutex);
	spin_lock_init(&sess->conn_lock);
	spin_lock_init(&sess->cr_a_lock);
	spin_lock_init(&sess->cr_i_lock);
	spin_lock_init(&sess->session_usage_lock);
	spin_lock_init(&sess->ttt_lock);

	समयr_setup(&sess->समय2retain_समयr,
		    iscsit_handle_समय2retain_समयout, 0);

	ret = ida_alloc(&sess_ida, GFP_KERNEL);
	अगर (ret < 0) अणु
		pr_err("Session ID allocation failed %d\n", ret);
		iscsit_tx_login_rsp(conn, ISCSI_STATUS_CLS_TARGET_ERR,
				ISCSI_LOGIN_STATUS_NO_RESOURCES);
		जाओ मुक्त_sess;
	पूर्ण

	sess->session_index = ret;
	sess->creation_समय = get_jअगरfies_64();
	/*
	 * The FFP CmdSN winकरोw values will be allocated from the TPG's
	 * Initiator Node's ACL once the login has been successfully completed.
	 */
	atomic_set(&sess->max_cmd_sn, be32_to_cpu(pdu->cmdsn));

	sess->sess_ops = kzalloc(माप(काष्ठा iscsi_sess_ops), GFP_KERNEL);
	अगर (!sess->sess_ops) अणु
		iscsit_tx_login_rsp(conn, ISCSI_STATUS_CLS_TARGET_ERR,
				ISCSI_LOGIN_STATUS_NO_RESOURCES);
		pr_err("Unable to allocate memory for"
				" struct iscsi_sess_ops.\n");
		जाओ मुक्त_id;
	पूर्ण

	sess->se_sess = transport_alloc_session(TARGET_PROT_NORMAL);
	अगर (IS_ERR(sess->se_sess)) अणु
		iscsit_tx_login_rsp(conn, ISCSI_STATUS_CLS_TARGET_ERR,
				ISCSI_LOGIN_STATUS_NO_RESOURCES);
		जाओ मुक्त_ops;
	पूर्ण

	वापस 0;

मुक्त_ops:
	kमुक्त(sess->sess_ops);
मुक्त_id:
	ida_मुक्त(&sess_ida, sess->session_index);
मुक्त_sess:
	kमुक्त(sess);
	conn->sess = शून्य;
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक iscsi_login_zero_tsih_s2(
	काष्ठा iscsi_conn *conn)
अणु
	काष्ठा iscsi_node_attrib *na;
	काष्ठा iscsi_session *sess = conn->sess;
	bool iser = false;

	sess->tpg = conn->tpg;

	/*
	 * Assign a new TPG Session Handle.  Note this is रक्षित with
	 * काष्ठा iscsi_portal_group->np_login_sem from iscsit_access_np().
	 */
	sess->tsih = ++sess->tpg->ntsih;
	अगर (!sess->tsih)
		sess->tsih = ++sess->tpg->ntsih;

	/*
	 * Create the शेष params from user defined values..
	 */
	अगर (iscsi_copy_param_list(&conn->param_list,
				conn->tpg->param_list, 1) < 0) अणु
		iscsit_tx_login_rsp(conn, ISCSI_STATUS_CLS_TARGET_ERR,
				ISCSI_LOGIN_STATUS_NO_RESOURCES);
		वापस -1;
	पूर्ण

	अगर (conn->conn_transport->transport_type == ISCSI_INFINIBAND)
		iser = true;

	iscsi_set_keys_to_negotiate(conn->param_list, iser);

	अगर (sess->sess_ops->SessionType)
		वापस iscsi_set_keys_irrelevant_क्रम_discovery(
				conn->param_list);

	na = iscsit_tpg_get_node_attrib(sess);

	/*
	 * Need to send TargetPortalGroupTag back in first login response
	 * on any iSCSI connection where the Initiator provides TargetName.
	 * See 5.3.1.  Login Phase Start
	 *
	 * In our हाल, we have alपढ़ोy located the काष्ठा iscsi_tiqn at this poपूर्णांक.
	 */
	अगर (iscsi_change_param_प्र_लिखो(conn, "TargetPortalGroupTag=%hu", sess->tpg->tpgt))
		वापस -1;

	/*
	 * Workaround क्रम Initiators that have broken connection recovery logic.
	 *
	 * "We would really like to get rid of this." Linux-iSCSI.org team
	 */
	अगर (iscsi_change_param_प्र_लिखो(conn, "ErrorRecoveryLevel=%d", na->शेष_erl))
		वापस -1;

	/*
	 * Set RDMAExtensions=Yes by शेष क्रम iSER enabled network portals
	 */
	अगर (iser) अणु
		काष्ठा iscsi_param *param;
		अचिन्हित दीर्घ mrdsl, off;
		पूर्णांक rc;

		अगर (iscsi_change_param_प्र_लिखो(conn, "RDMAExtensions=Yes"))
			वापस -1;

		/*
		 * Make MaxRecvDataSegmentLength PAGE_SIZE aligned क्रम
		 * Immediate Data + Unsolicited Data-OUT अगर necessary..
		 */
		param = iscsi_find_param_from_key("MaxRecvDataSegmentLength",
						  conn->param_list);
		अगर (!param) अणु
			iscsit_tx_login_rsp(conn, ISCSI_STATUS_CLS_TARGET_ERR,
				ISCSI_LOGIN_STATUS_NO_RESOURCES);
			वापस -1;
		पूर्ण
		rc = kम_से_अदीर्घ(param->value, 0, &mrdsl);
		अगर (rc < 0) अणु
			iscsit_tx_login_rsp(conn, ISCSI_STATUS_CLS_TARGET_ERR,
				ISCSI_LOGIN_STATUS_NO_RESOURCES);
			वापस -1;
		पूर्ण
		off = mrdsl % PAGE_SIZE;
		अगर (!off)
			जाओ check_prot;

		अगर (mrdsl < PAGE_SIZE)
			mrdsl = PAGE_SIZE;
		अन्यथा
			mrdsl -= off;

		pr_warn("Aligning ISER MaxRecvDataSegmentLength: %lu down"
			" to PAGE_SIZE\n", mrdsl);

		अगर (iscsi_change_param_प्र_लिखो(conn, "MaxRecvDataSegmentLength=%lu\n", mrdsl))
			वापस -1;
		/*
		 * ISER currently requires that ImmediateData + Unsolicited
		 * Data be disabled when protection / signature MRs are enabled.
		 */
check_prot:
		अगर (sess->se_sess->sup_prot_ops &
		   (TARGET_PROT_DOUT_STRIP | TARGET_PROT_DOUT_PASS |
		    TARGET_PROT_DOUT_INSERT)) अणु

			अगर (iscsi_change_param_प्र_लिखो(conn, "ImmediateData=No"))
				वापस -1;

			अगर (iscsi_change_param_प्र_लिखो(conn, "InitialR2T=Yes"))
				वापस -1;

			pr_debug("Forcing ImmediateData=No + InitialR2T=Yes for"
				 " T10-PI enabled ISER session\n");
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक iscsi_login_non_zero_tsih_s1(
	काष्ठा iscsi_conn *conn,
	अचिन्हित अक्षर *buf)
अणु
	काष्ठा iscsi_login_req *pdu = (काष्ठा iscsi_login_req *)buf;

	वापस iscsi_login_set_conn_values(शून्य, conn, pdu->cid);
पूर्ण

/*
 *	Add a new connection to an existing session.
 */
अटल पूर्णांक iscsi_login_non_zero_tsih_s2(
	काष्ठा iscsi_conn *conn,
	अचिन्हित अक्षर *buf)
अणु
	काष्ठा iscsi_portal_group *tpg = conn->tpg;
	काष्ठा iscsi_session *sess = शून्य, *sess_p = शून्य;
	काष्ठा se_portal_group *se_tpg = &tpg->tpg_se_tpg;
	काष्ठा se_session *se_sess, *se_sess_पंचांगp;
	काष्ठा iscsi_login_req *pdu = (काष्ठा iscsi_login_req *)buf;
	bool iser = false;

	spin_lock_bh(&se_tpg->session_lock);
	list_क्रम_each_entry_safe(se_sess, se_sess_पंचांगp, &se_tpg->tpg_sess_list,
			sess_list) अणु

		sess_p = (काष्ठा iscsi_session *)se_sess->fabric_sess_ptr;
		अगर (atomic_पढ़ो(&sess_p->session_fall_back_to_erl0) ||
		    atomic_पढ़ो(&sess_p->session_logout) ||
		    atomic_पढ़ो(&sess_p->session_बंद) ||
		   (sess_p->समय2retain_समयr_flags & ISCSI_TF_EXPIRED))
			जारी;
		अगर (!स_भेद(sess_p->isid, pdu->isid, 6) &&
		     (sess_p->tsih == be16_to_cpu(pdu->tsih))) अणु
			iscsit_inc_session_usage_count(sess_p);
			iscsit_stop_समय2retain_समयr(sess_p);
			sess = sess_p;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&se_tpg->session_lock);

	/*
	 * If the Time2Retain handler has expired, the session is alपढ़ोy gone.
	 */
	अगर (!sess) अणु
		pr_err("Initiator attempting to add a connection to"
			" a non-existent session, rejecting iSCSI Login.\n");
		iscsit_tx_login_rsp(conn, ISCSI_STATUS_CLS_INITIATOR_ERR,
				ISCSI_LOGIN_STATUS_NO_SESSION);
		वापस -1;
	पूर्ण

	/*
	 * Stop the Time2Retain समयr अगर this is a failed session, we restart
	 * the समयr अगर the login is not successful.
	 */
	spin_lock_bh(&sess->conn_lock);
	अगर (sess->session_state == TARG_SESS_STATE_FAILED)
		atomic_set(&sess->session_continuation, 1);
	spin_unlock_bh(&sess->conn_lock);

	अगर (iscsi_login_set_conn_values(sess, conn, pdu->cid) < 0 ||
	    iscsi_copy_param_list(&conn->param_list,
			conn->tpg->param_list, 0) < 0) अणु
		iscsit_tx_login_rsp(conn, ISCSI_STATUS_CLS_TARGET_ERR,
				ISCSI_LOGIN_STATUS_NO_RESOURCES);
		वापस -1;
	पूर्ण

	अगर (conn->conn_transport->transport_type == ISCSI_INFINIBAND)
		iser = true;

	iscsi_set_keys_to_negotiate(conn->param_list, iser);
	/*
	 * Need to send TargetPortalGroupTag back in first login response
	 * on any iSCSI connection where the Initiator provides TargetName.
	 * See 5.3.1.  Login Phase Start
	 *
	 * In our हाल, we have alपढ़ोy located the काष्ठा iscsi_tiqn at this poपूर्णांक.
	 */
	अगर (iscsi_change_param_प्र_लिखो(conn, "TargetPortalGroupTag=%hu", sess->tpg->tpgt))
		वापस -1;

	वापस 0;
पूर्ण

पूर्णांक iscsi_login_post_auth_non_zero_tsih(
	काष्ठा iscsi_conn *conn,
	u16 cid,
	u32 exp_statsn)
अणु
	काष्ठा iscsi_conn *conn_ptr = शून्य;
	काष्ठा iscsi_conn_recovery *cr = शून्य;
	काष्ठा iscsi_session *sess = conn->sess;

	/*
	 * By following item 5 in the login table,  अगर we have found
	 * an existing ISID and a valid/existing TSIH and an existing
	 * CID we करो connection reinstatement.  Currently we करोnt not
	 * support it so we send back an non-zero status class to the
	 * initiator and release the new connection.
	 */
	conn_ptr = iscsit_get_conn_from_cid_rcfr(sess, cid);
	अगर (conn_ptr) अणु
		pr_err("Connection exists with CID %hu for %s,"
			" performing connection reinstatement.\n",
			conn_ptr->cid, sess->sess_ops->InitiatorName);

		iscsit_connection_reinstatement_rcfr(conn_ptr);
		iscsit_dec_conn_usage_count(conn_ptr);
	पूर्ण

	/*
	 * Check क्रम any connection recovery entries containing CID.
	 * We use the original ExpStatSN sent in the first login request
	 * to acknowledge commands क्रम the failed connection.
	 *
	 * Also note that an explict logout may have alपढ़ोy been sent,
	 * but the response may not be sent due to additional connection
	 * loss.
	 */
	अगर (sess->sess_ops->ErrorRecoveryLevel == 2) अणु
		cr = iscsit_get_inactive_connection_recovery_entry(
				sess, cid);
		अगर (cr) अणु
			pr_debug("Performing implicit logout"
				" for connection recovery on CID: %hu\n",
					conn->cid);
			iscsit_discard_cr_cmds_by_expstatsn(cr, exp_statsn);
		पूर्ण
	पूर्ण

	/*
	 * Else we follow item 4 from the login table in that we have
	 * found an existing ISID and a valid/existing TSIH and a new
	 * CID we go ahead and जारी to add a new connection to the
	 * session.
	 */
	pr_debug("Adding CID %hu to existing session for %s.\n",
			cid, sess->sess_ops->InitiatorName);

	अगर ((atomic_पढ़ो(&sess->nconn) + 1) > sess->sess_ops->MaxConnections) अणु
		pr_err("Adding additional connection to this session"
			" would exceed MaxConnections %d, login failed.\n",
				sess->sess_ops->MaxConnections);
		iscsit_tx_login_rsp(conn, ISCSI_STATUS_CLS_INITIATOR_ERR,
				ISCSI_LOGIN_STATUS_ISID_ERROR);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम iscsi_post_login_start_समयrs(काष्ठा iscsi_conn *conn)
अणु
	काष्ठा iscsi_session *sess = conn->sess;
	/*
	 * FIXME: Unsolicited NopIN support क्रम ISER
	 */
	अगर (conn->conn_transport->transport_type == ISCSI_INFINIBAND)
		वापस;

	अगर (!sess->sess_ops->SessionType)
		iscsit_start_nopin_समयr(conn);
पूर्ण

पूर्णांक iscsit_start_kthपढ़ोs(काष्ठा iscsi_conn *conn)
अणु
	पूर्णांक ret = 0;

	spin_lock(&iscsit_global->ts_biपंचांगap_lock);
	conn->biपंचांगap_id = biपंचांगap_find_मुक्त_region(iscsit_global->ts_biपंचांगap,
					ISCSIT_BITMAP_BITS, get_order(1));
	spin_unlock(&iscsit_global->ts_biपंचांगap_lock);

	अगर (conn->biपंचांगap_id < 0) अणु
		pr_err("bitmap_find_free_region() failed for"
		       " iscsit_start_kthreads()\n");
		वापस -ENOMEM;
	पूर्ण

	conn->tx_thपढ़ो = kthपढ़ो_run(iscsi_target_tx_thपढ़ो, conn,
				      "%s", ISCSI_TX_THREAD_NAME);
	अगर (IS_ERR(conn->tx_thपढ़ो)) अणु
		pr_err("Unable to start iscsi_target_tx_thread\n");
		ret = PTR_ERR(conn->tx_thपढ़ो);
		जाओ out_biपंचांगap;
	पूर्ण
	conn->tx_thपढ़ो_active = true;

	conn->rx_thपढ़ो = kthपढ़ो_run(iscsi_target_rx_thपढ़ो, conn,
				      "%s", ISCSI_RX_THREAD_NAME);
	अगर (IS_ERR(conn->rx_thपढ़ो)) अणु
		pr_err("Unable to start iscsi_target_rx_thread\n");
		ret = PTR_ERR(conn->rx_thपढ़ो);
		जाओ out_tx;
	पूर्ण
	conn->rx_thपढ़ो_active = true;

	वापस 0;
out_tx:
	send_sig(संक_विघ्न, conn->tx_thपढ़ो, 1);
	kthपढ़ो_stop(conn->tx_thपढ़ो);
	conn->tx_thपढ़ो_active = false;
out_biपंचांगap:
	spin_lock(&iscsit_global->ts_biपंचांगap_lock);
	biपंचांगap_release_region(iscsit_global->ts_biपंचांगap, conn->biपंचांगap_id,
			      get_order(1));
	spin_unlock(&iscsit_global->ts_biपंचांगap_lock);
	वापस ret;
पूर्ण

व्योम iscsi_post_login_handler(
	काष्ठा iscsi_np *np,
	काष्ठा iscsi_conn *conn,
	u8 zero_tsih)
अणु
	पूर्णांक stop_समयr = 0;
	काष्ठा iscsi_session *sess = conn->sess;
	काष्ठा se_session *se_sess = sess->se_sess;
	काष्ठा iscsi_portal_group *tpg = sess->tpg;
	काष्ठा se_portal_group *se_tpg = &tpg->tpg_se_tpg;

	iscsit_inc_conn_usage_count(conn);

	iscsit_collect_login_stats(conn, ISCSI_STATUS_CLS_SUCCESS,
			ISCSI_LOGIN_STATUS_ACCEPT);

	pr_debug("Moving to TARG_CONN_STATE_LOGGED_IN.\n");
	conn->conn_state = TARG_CONN_STATE_LOGGED_IN;

	iscsi_set_connection_parameters(conn->conn_ops, conn->param_list);
	/*
	 * SCSI Initiator -> SCSI Target Port Mapping
	 */
	अगर (!zero_tsih) अणु
		iscsi_set_session_parameters(sess->sess_ops,
				conn->param_list, 0);
		iscsi_release_param_list(conn->param_list);
		conn->param_list = शून्य;

		spin_lock_bh(&sess->conn_lock);
		atomic_set(&sess->session_continuation, 0);
		अगर (sess->session_state == TARG_SESS_STATE_FAILED) अणु
			pr_debug("Moving to"
					" TARG_SESS_STATE_LOGGED_IN.\n");
			sess->session_state = TARG_SESS_STATE_LOGGED_IN;
			stop_समयr = 1;
		पूर्ण

		pr_debug("iSCSI Login successful on CID: %hu from %pISpc to"
			" %pISpc,%hu\n", conn->cid, &conn->login_sockaddr,
			&conn->local_sockaddr, tpg->tpgt);

		list_add_tail(&conn->conn_list, &sess->sess_conn_list);
		atomic_inc(&sess->nconn);
		pr_debug("Incremented iSCSI Connection count to %hu"
			" from node: %s\n", atomic_पढ़ो(&sess->nconn),
			sess->sess_ops->InitiatorName);
		spin_unlock_bh(&sess->conn_lock);

		iscsi_post_login_start_समयrs(conn);
		/*
		 * Determine CPU mask to ensure connection's RX and TX kthपढ़ोs
		 * are scheduled on the same CPU.
		 */
		iscsit_thपढ़ो_get_cpumask(conn);
		conn->conn_rx_reset_cpumask = 1;
		conn->conn_tx_reset_cpumask = 1;
		/*
		 * Wakeup the sleeping iscsi_target_rx_thपढ़ो() now that
		 * iscsi_conn is in TARG_CONN_STATE_LOGGED_IN state.
		 */
		complete(&conn->rx_login_comp);
		iscsit_dec_conn_usage_count(conn);

		अगर (stop_समयr) अणु
			spin_lock_bh(&se_tpg->session_lock);
			iscsit_stop_समय2retain_समयr(sess);
			spin_unlock_bh(&se_tpg->session_lock);
		पूर्ण
		iscsit_dec_session_usage_count(sess);
		वापस;
	पूर्ण

	iscsi_set_session_parameters(sess->sess_ops, conn->param_list, 1);
	iscsi_release_param_list(conn->param_list);
	conn->param_list = शून्य;

	iscsit_determine_maxcmdsn(sess);

	spin_lock_bh(&se_tpg->session_lock);
	__transport_रेजिस्टर_session(&sess->tpg->tpg_se_tpg,
			se_sess->se_node_acl, se_sess, sess);
	pr_debug("Moving to TARG_SESS_STATE_LOGGED_IN.\n");
	sess->session_state = TARG_SESS_STATE_LOGGED_IN;

	pr_debug("iSCSI Login successful on CID: %hu from %pISpc to %pISpc,%hu\n",
		conn->cid, &conn->login_sockaddr, &conn->local_sockaddr,
		tpg->tpgt);

	spin_lock_bh(&sess->conn_lock);
	list_add_tail(&conn->conn_list, &sess->sess_conn_list);
	atomic_inc(&sess->nconn);
	pr_debug("Incremented iSCSI Connection count to %hu from node:"
		" %s\n", atomic_पढ़ो(&sess->nconn),
		sess->sess_ops->InitiatorName);
	spin_unlock_bh(&sess->conn_lock);

	sess->sid = tpg->sid++;
	अगर (!sess->sid)
		sess->sid = tpg->sid++;
	pr_debug("Established iSCSI session from node: %s\n",
			sess->sess_ops->InitiatorName);

	tpg->nsessions++;
	अगर (tpg->tpg_tiqn)
		tpg->tpg_tiqn->tiqn_nsessions++;

	pr_debug("Incremented number of active iSCSI sessions to %u on"
		" iSCSI Target Portal Group: %hu\n", tpg->nsessions, tpg->tpgt);
	spin_unlock_bh(&se_tpg->session_lock);

	iscsi_post_login_start_समयrs(conn);
	/*
	 * Determine CPU mask to ensure connection's RX and TX kthपढ़ोs
	 * are scheduled on the same CPU.
	 */
	iscsit_thपढ़ो_get_cpumask(conn);
	conn->conn_rx_reset_cpumask = 1;
	conn->conn_tx_reset_cpumask = 1;
	/*
	 * Wakeup the sleeping iscsi_target_rx_thपढ़ो() now that
	 * iscsi_conn is in TARG_CONN_STATE_LOGGED_IN state.
	 */
	complete(&conn->rx_login_comp);
	iscsit_dec_conn_usage_count(conn);
पूर्ण

व्योम iscsi_handle_login_thपढ़ो_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा iscsi_np *np = from_समयr(np, t, np_login_समयr);

	spin_lock_bh(&np->np_thपढ़ो_lock);
	pr_err("iSCSI Login timeout on Network Portal %pISpc\n",
			&np->np_sockaddr);

	अगर (np->np_login_समयr_flags & ISCSI_TF_STOP) अणु
		spin_unlock_bh(&np->np_thपढ़ो_lock);
		वापस;
	पूर्ण

	अगर (np->np_thपढ़ो)
		send_sig(संक_विघ्न, np->np_thपढ़ो, 1);

	np->np_login_समयr_flags &= ~ISCSI_TF_RUNNING;
	spin_unlock_bh(&np->np_thपढ़ो_lock);
पूर्ण

अटल व्योम iscsi_start_login_thपढ़ो_समयr(काष्ठा iscsi_np *np)
अणु
	/*
	 * This used the TA_LOGIN_TIMEOUT स्थिरant because at this
	 * poपूर्णांक we करो not have access to ISCSI_TPG_ATTRIB(tpg)->login_समयout
	 */
	spin_lock_bh(&np->np_thपढ़ो_lock);
	np->np_login_समयr_flags &= ~ISCSI_TF_STOP;
	np->np_login_समयr_flags |= ISCSI_TF_RUNNING;
	mod_समयr(&np->np_login_समयr, jअगरfies + TA_LOGIN_TIMEOUT * HZ);

	pr_debug("Added timeout timer to iSCSI login request for"
			" %u seconds.\n", TA_LOGIN_TIMEOUT);
	spin_unlock_bh(&np->np_thपढ़ो_lock);
पूर्ण

अटल व्योम iscsi_stop_login_thपढ़ो_समयr(काष्ठा iscsi_np *np)
अणु
	spin_lock_bh(&np->np_thपढ़ो_lock);
	अगर (!(np->np_login_समयr_flags & ISCSI_TF_RUNNING)) अणु
		spin_unlock_bh(&np->np_thपढ़ो_lock);
		वापस;
	पूर्ण
	np->np_login_समयr_flags |= ISCSI_TF_STOP;
	spin_unlock_bh(&np->np_thपढ़ो_lock);

	del_समयr_sync(&np->np_login_समयr);

	spin_lock_bh(&np->np_thपढ़ो_lock);
	np->np_login_समयr_flags &= ~ISCSI_TF_RUNNING;
	spin_unlock_bh(&np->np_thपढ़ो_lock);
पूर्ण

पूर्णांक iscsit_setup_np(
	काष्ठा iscsi_np *np,
	काष्ठा sockaddr_storage *sockaddr)
अणु
	काष्ठा socket *sock = शून्य;
	पूर्णांक backlog = ISCSIT_TCP_BACKLOG, ret, len;

	चयन (np->np_network_transport) अणु
	हाल ISCSI_TCP:
		np->np_ip_proto = IPPROTO_TCP;
		np->np_sock_type = SOCK_STREAM;
		अवरोध;
	हाल ISCSI_SCTP_TCP:
		np->np_ip_proto = IPPROTO_SCTP;
		np->np_sock_type = SOCK_STREAM;
		अवरोध;
	हाल ISCSI_SCTP_UDP:
		np->np_ip_proto = IPPROTO_SCTP;
		np->np_sock_type = SOCK_SEQPACKET;
		अवरोध;
	शेष:
		pr_err("Unsupported network_transport: %d\n",
				np->np_network_transport);
		वापस -EINVAL;
	पूर्ण

	ret = sock_create(sockaddr->ss_family, np->np_sock_type,
			np->np_ip_proto, &sock);
	अगर (ret < 0) अणु
		pr_err("sock_create() failed.\n");
		वापस ret;
	पूर्ण
	np->np_socket = sock;
	/*
	 * Setup the np->np_sockaddr from the passed sockaddr setup
	 * in iscsi_target_configfs.c code..
	 */
	स_नकल(&np->np_sockaddr, sockaddr,
			माप(काष्ठा sockaddr_storage));

	अगर (sockaddr->ss_family == AF_INET6)
		len = माप(काष्ठा sockaddr_in6);
	अन्यथा
		len = माप(काष्ठा sockaddr_in);
	/*
	 * Set SO_REUSEADDR, and disable Nagle Algorithm with TCP_NODELAY.
	 */
	अगर (np->np_network_transport == ISCSI_TCP)
		tcp_sock_set_nodelay(sock->sk);
	sock_set_reuseaddr(sock->sk);
	ip_sock_set_मुक्तbind(sock->sk);

	ret = kernel_bind(sock, (काष्ठा sockaddr *)&np->np_sockaddr, len);
	अगर (ret < 0) अणु
		pr_err("kernel_bind() failed: %d\n", ret);
		जाओ fail;
	पूर्ण

	ret = kernel_listen(sock, backlog);
	अगर (ret != 0) अणु
		pr_err("kernel_listen() failed: %d\n", ret);
		जाओ fail;
	पूर्ण

	वापस 0;
fail:
	np->np_socket = शून्य;
	sock_release(sock);
	वापस ret;
पूर्ण

पूर्णांक iscsi_target_setup_login_socket(
	काष्ठा iscsi_np *np,
	काष्ठा sockaddr_storage *sockaddr)
अणु
	काष्ठा iscsit_transport *t;
	पूर्णांक rc;

	t = iscsit_get_transport(np->np_network_transport);
	अगर (!t)
		वापस -EINVAL;

	rc = t->iscsit_setup_np(np, sockaddr);
	अगर (rc < 0) अणु
		iscsit_put_transport(t);
		वापस rc;
	पूर्ण

	np->np_transport = t;
	np->enabled = true;
	वापस 0;
पूर्ण

पूर्णांक iscsit_accept_np(काष्ठा iscsi_np *np, काष्ठा iscsi_conn *conn)
अणु
	काष्ठा socket *new_sock, *sock = np->np_socket;
	काष्ठा sockaddr_in sock_in;
	काष्ठा sockaddr_in6 sock_in6;
	पूर्णांक rc;

	rc = kernel_accept(sock, &new_sock, 0);
	अगर (rc < 0)
		वापस rc;

	conn->sock = new_sock;
	conn->login_family = np->np_sockaddr.ss_family;

	अगर (np->np_sockaddr.ss_family == AF_INET6) अणु
		स_रखो(&sock_in6, 0, माप(काष्ठा sockaddr_in6));

		rc = conn->sock->ops->getname(conn->sock,
				(काष्ठा sockaddr *)&sock_in6, 1);
		अगर (rc >= 0) अणु
			अगर (!ipv6_addr_v4mapped(&sock_in6.sin6_addr)) अणु
				स_नकल(&conn->login_sockaddr, &sock_in6, माप(sock_in6));
			पूर्ण अन्यथा अणु
				/* Pretend to be an ipv4 socket */
				sock_in.sin_family = AF_INET;
				sock_in.sin_port = sock_in6.sin6_port;
				स_नकल(&sock_in.sin_addr, &sock_in6.sin6_addr.s6_addr32[3], 4);
				स_नकल(&conn->login_sockaddr, &sock_in, माप(sock_in));
			पूर्ण
		पूर्ण

		rc = conn->sock->ops->getname(conn->sock,
				(काष्ठा sockaddr *)&sock_in6, 0);
		अगर (rc >= 0) अणु
			अगर (!ipv6_addr_v4mapped(&sock_in6.sin6_addr)) अणु
				स_नकल(&conn->local_sockaddr, &sock_in6, माप(sock_in6));
			पूर्ण अन्यथा अणु
				/* Pretend to be an ipv4 socket */
				sock_in.sin_family = AF_INET;
				sock_in.sin_port = sock_in6.sin6_port;
				स_नकल(&sock_in.sin_addr, &sock_in6.sin6_addr.s6_addr32[3], 4);
				स_नकल(&conn->local_sockaddr, &sock_in, माप(sock_in));
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		स_रखो(&sock_in, 0, माप(काष्ठा sockaddr_in));

		rc = conn->sock->ops->getname(conn->sock,
				(काष्ठा sockaddr *)&sock_in, 1);
		अगर (rc >= 0)
			स_नकल(&conn->login_sockaddr, &sock_in, माप(sock_in));

		rc = conn->sock->ops->getname(conn->sock,
				(काष्ठा sockaddr *)&sock_in, 0);
		अगर (rc >= 0)
			स_नकल(&conn->local_sockaddr, &sock_in, माप(sock_in));
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक iscsit_get_login_rx(काष्ठा iscsi_conn *conn, काष्ठा iscsi_login *login)
अणु
	काष्ठा iscsi_login_req *login_req;
	u32 padding = 0, payload_length;

	अगर (iscsi_login_rx_data(conn, login->req, ISCSI_HDR_LEN) < 0)
		वापस -1;

	login_req = (काष्ठा iscsi_login_req *)login->req;
	payload_length	= ntoh24(login_req->dlength);
	padding = ((-payload_length) & 3);

	pr_debug("Got Login Command, Flags 0x%02x, ITT: 0x%08x,"
		" CmdSN: 0x%08x, ExpStatSN: 0x%08x, CID: %hu, Length: %u\n",
		login_req->flags, login_req->itt, login_req->cmdsn,
		login_req->exp_statsn, login_req->cid, payload_length);
	/*
	 * Setup the initial iscsi_login values from the leading
	 * login request PDU.
	 */
	अगर (login->first_request) अणु
		login_req = (काष्ठा iscsi_login_req *)login->req;
		login->leading_connection = (!login_req->tsih) ? 1 : 0;
		login->current_stage	= ISCSI_LOGIN_CURRENT_STAGE(login_req->flags);
		login->version_min	= login_req->min_version;
		login->version_max	= login_req->max_version;
		स_नकल(login->isid, login_req->isid, 6);
		login->cmd_sn		= be32_to_cpu(login_req->cmdsn);
		login->init_task_tag	= login_req->itt;
		login->initial_exp_statsn = be32_to_cpu(login_req->exp_statsn);
		login->cid		= be16_to_cpu(login_req->cid);
		login->tsih		= be16_to_cpu(login_req->tsih);
	पूर्ण

	अगर (iscsi_target_check_login_request(conn, login) < 0)
		वापस -1;

	स_रखो(login->req_buf, 0, MAX_KEY_VALUE_PAIRS);
	अगर (iscsi_login_rx_data(conn, login->req_buf,
				payload_length + padding) < 0)
		वापस -1;

	वापस 0;
पूर्ण

पूर्णांक iscsit_put_login_tx(काष्ठा iscsi_conn *conn, काष्ठा iscsi_login *login,
			u32 length)
अणु
	अगर (iscsi_login_tx_data(conn, login->rsp, login->rsp_buf, length) < 0)
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक
iscsit_conn_set_transport(काष्ठा iscsi_conn *conn, काष्ठा iscsit_transport *t)
अणु
	पूर्णांक rc;

	अगर (!t->owner) अणु
		conn->conn_transport = t;
		वापस 0;
	पूर्ण

	rc = try_module_get(t->owner);
	अगर (!rc) अणु
		pr_err("try_module_get() failed for %s\n", t->name);
		वापस -EINVAL;
	पूर्ण

	conn->conn_transport = t;
	वापस 0;
पूर्ण

अटल काष्ठा iscsi_conn *iscsit_alloc_conn(काष्ठा iscsi_np *np)
अणु
	काष्ठा iscsi_conn *conn;

	conn = kzalloc(माप(काष्ठा iscsi_conn), GFP_KERNEL);
	अगर (!conn) अणु
		pr_err("Could not allocate memory for new connection\n");
		वापस शून्य;
	पूर्ण
	pr_debug("Moving to TARG_CONN_STATE_FREE.\n");
	conn->conn_state = TARG_CONN_STATE_FREE;

	init_रुकोqueue_head(&conn->queues_wq);
	INIT_LIST_HEAD(&conn->conn_list);
	INIT_LIST_HEAD(&conn->conn_cmd_list);
	INIT_LIST_HEAD(&conn->immed_queue_list);
	INIT_LIST_HEAD(&conn->response_queue_list);
	init_completion(&conn->conn_post_रुको_comp);
	init_completion(&conn->conn_रुको_comp);
	init_completion(&conn->conn_रुको_rcfr_comp);
	init_completion(&conn->conn_रुकोing_on_uc_comp);
	init_completion(&conn->conn_logout_comp);
	init_completion(&conn->rx_half_बंद_comp);
	init_completion(&conn->tx_half_बंद_comp);
	init_completion(&conn->rx_login_comp);
	spin_lock_init(&conn->cmd_lock);
	spin_lock_init(&conn->conn_usage_lock);
	spin_lock_init(&conn->immed_queue_lock);
	spin_lock_init(&conn->nopin_समयr_lock);
	spin_lock_init(&conn->response_queue_lock);
	spin_lock_init(&conn->state_lock);

	समयr_setup(&conn->nopin_response_समयr,
		    iscsit_handle_nopin_response_समयout, 0);
	समयr_setup(&conn->nopin_समयr, iscsit_handle_nopin_समयout, 0);

	अगर (iscsit_conn_set_transport(conn, np->np_transport) < 0)
		जाओ मुक्त_conn;

	conn->conn_ops = kzalloc(माप(काष्ठा iscsi_conn_ops), GFP_KERNEL);
	अगर (!conn->conn_ops) अणु
		pr_err("Unable to allocate memory for struct iscsi_conn_ops.\n");
		जाओ put_transport;
	पूर्ण

	अगर (!zalloc_cpumask_var(&conn->conn_cpumask, GFP_KERNEL)) अणु
		pr_err("Unable to allocate conn->conn_cpumask\n");
		जाओ मुक्त_conn_ops;
	पूर्ण

	वापस conn;

मुक्त_conn_ops:
	kमुक्त(conn->conn_ops);
put_transport:
	iscsit_put_transport(conn->conn_transport);
मुक्त_conn:
	kमुक्त(conn);
	वापस शून्य;
पूर्ण

व्योम iscsit_मुक्त_conn(काष्ठा iscsi_conn *conn)
अणु
	मुक्त_cpumask_var(conn->conn_cpumask);
	kमुक्त(conn->conn_ops);
	iscsit_put_transport(conn->conn_transport);
	kमुक्त(conn);
पूर्ण

व्योम iscsi_target_login_sess_out(काष्ठा iscsi_conn *conn,
				 bool zero_tsih, bool new_sess)
अणु
	अगर (!new_sess)
		जाओ old_sess_out;

	pr_err("iSCSI Login negotiation failed.\n");
	iscsit_collect_login_stats(conn, ISCSI_STATUS_CLS_INITIATOR_ERR,
				   ISCSI_LOGIN_STATUS_INIT_ERR);
	अगर (!zero_tsih || !conn->sess)
		जाओ old_sess_out;

	transport_मुक्त_session(conn->sess->se_sess);
	ida_मुक्त(&sess_ida, conn->sess->session_index);
	kमुक्त(conn->sess->sess_ops);
	kमुक्त(conn->sess);
	conn->sess = शून्य;

old_sess_out:
	/*
	 * If login negotiation fails check अगर the Time2Retain समयr
	 * needs to be restarted.
	 */
	अगर (!zero_tsih && conn->sess) अणु
		spin_lock_bh(&conn->sess->conn_lock);
		अगर (conn->sess->session_state == TARG_SESS_STATE_FAILED) अणु
			काष्ठा se_portal_group *se_tpg =
					&conn->tpg->tpg_se_tpg;

			atomic_set(&conn->sess->session_continuation, 0);
			spin_unlock_bh(&conn->sess->conn_lock);
			spin_lock_bh(&se_tpg->session_lock);
			iscsit_start_समय2retain_handler(conn->sess);
			spin_unlock_bh(&se_tpg->session_lock);
		पूर्ण अन्यथा
			spin_unlock_bh(&conn->sess->conn_lock);
		iscsit_dec_session_usage_count(conn->sess);
	पूर्ण

	ahash_request_मुक्त(conn->conn_tx_hash);
	अगर (conn->conn_rx_hash) अणु
		काष्ठा crypto_ahash *tfm;

		tfm = crypto_ahash_reqtfm(conn->conn_rx_hash);
		ahash_request_मुक्त(conn->conn_rx_hash);
		crypto_मुक्त_ahash(tfm);
	पूर्ण

	अगर (conn->param_list) अणु
		iscsi_release_param_list(conn->param_list);
		conn->param_list = शून्य;
	पूर्ण
	iscsi_target_nego_release(conn);

	अगर (conn->sock) अणु
		sock_release(conn->sock);
		conn->sock = शून्य;
	पूर्ण

	अगर (conn->conn_transport->iscsit_रुको_conn)
		conn->conn_transport->iscsit_रुको_conn(conn);

	अगर (conn->conn_transport->iscsit_मुक्त_conn)
		conn->conn_transport->iscsit_मुक्त_conn(conn);

	iscsit_मुक्त_conn(conn);
पूर्ण

अटल पूर्णांक __iscsi_target_login_thपढ़ो(काष्ठा iscsi_np *np)
अणु
	u8 *buffer, zero_tsih = 0;
	पूर्णांक ret = 0, rc;
	काष्ठा iscsi_conn *conn = शून्य;
	काष्ठा iscsi_login *login;
	काष्ठा iscsi_portal_group *tpg = शून्य;
	काष्ठा iscsi_login_req *pdu;
	काष्ठा iscsi_tpg_np *tpg_np;
	bool new_sess = false;

	flush_संकेतs(current);

	spin_lock_bh(&np->np_thपढ़ो_lock);
	अगर (atomic_dec_अगर_positive(&np->np_reset_count) >= 0) अणु
		np->np_thपढ़ो_state = ISCSI_NP_THREAD_ACTIVE;
		spin_unlock_bh(&np->np_thपढ़ो_lock);
		complete(&np->np_restart_comp);
		वापस 1;
	पूर्ण अन्यथा अगर (np->np_thपढ़ो_state == ISCSI_NP_THREAD_SHUTDOWN) अणु
		spin_unlock_bh(&np->np_thपढ़ो_lock);
		जाओ निकास;
	पूर्ण अन्यथा अणु
		np->np_thपढ़ो_state = ISCSI_NP_THREAD_ACTIVE;
	पूर्ण
	spin_unlock_bh(&np->np_thपढ़ो_lock);

	conn = iscsit_alloc_conn(np);
	अगर (!conn) अणु
		/* Get another socket */
		वापस 1;
	पूर्ण

	rc = np->np_transport->iscsit_accept_np(np, conn);
	अगर (rc == -ENOSYS) अणु
		complete(&np->np_restart_comp);
		iscsit_मुक्त_conn(conn);
		जाओ निकास;
	पूर्ण अन्यथा अगर (rc < 0) अणु
		spin_lock_bh(&np->np_thपढ़ो_lock);
		अगर (atomic_dec_अगर_positive(&np->np_reset_count) >= 0) अणु
			np->np_thपढ़ो_state = ISCSI_NP_THREAD_ACTIVE;
			spin_unlock_bh(&np->np_thपढ़ो_lock);
			complete(&np->np_restart_comp);
			iscsit_मुक्त_conn(conn);
			/* Get another socket */
			वापस 1;
		पूर्ण
		spin_unlock_bh(&np->np_thपढ़ो_lock);
		iscsit_मुक्त_conn(conn);
		वापस 1;
	पूर्ण
	/*
	 * Perक्रमm the reमुख्यing iSCSI connection initialization items..
	 */
	login = iscsi_login_init_conn(conn);
	अगर (!login) अणु
		जाओ new_sess_out;
	पूर्ण

	iscsi_start_login_thपढ़ो_समयr(np);

	pr_debug("Moving to TARG_CONN_STATE_XPT_UP.\n");
	conn->conn_state = TARG_CONN_STATE_XPT_UP;
	/*
	 * This will process the first login request + payload..
	 */
	rc = np->np_transport->iscsit_get_login_rx(conn, login);
	अगर (rc == 1)
		वापस 1;
	अन्यथा अगर (rc < 0)
		जाओ new_sess_out;

	buffer = &login->req[0];
	pdu = (काष्ठा iscsi_login_req *)buffer;
	/*
	 * Used by iscsit_tx_login_rsp() क्रम Login Resonses PDUs
	 * when Status-Class != 0.
	*/
	conn->login_itt	= pdu->itt;

	spin_lock_bh(&np->np_thपढ़ो_lock);
	अगर (np->np_thपढ़ो_state != ISCSI_NP_THREAD_ACTIVE) अणु
		spin_unlock_bh(&np->np_thपढ़ो_lock);
		pr_err("iSCSI Network Portal on %pISpc currently not"
			" active.\n", &np->np_sockaddr);
		iscsit_tx_login_rsp(conn, ISCSI_STATUS_CLS_TARGET_ERR,
				ISCSI_LOGIN_STATUS_SVC_UNAVAILABLE);
		जाओ new_sess_out;
	पूर्ण
	spin_unlock_bh(&np->np_thपढ़ो_lock);

	conn->network_transport = np->np_network_transport;

	pr_debug("Received iSCSI login request from %pISpc on %s Network"
		" Portal %pISpc\n", &conn->login_sockaddr, np->np_transport->name,
		&conn->local_sockaddr);

	pr_debug("Moving to TARG_CONN_STATE_IN_LOGIN.\n");
	conn->conn_state	= TARG_CONN_STATE_IN_LOGIN;

	अगर (iscsi_login_check_initiator_version(conn, pdu->max_version,
			pdu->min_version) < 0)
		जाओ new_sess_out;

	zero_tsih = (pdu->tsih == 0x0000);
	अगर (zero_tsih) अणु
		/*
		 * This is the leading connection of a new session.
		 * We रुको until after authentication to check क्रम
		 * session reinstatement.
		 */
		अगर (iscsi_login_zero_tsih_s1(conn, buffer) < 0)
			जाओ new_sess_out;
	पूर्ण अन्यथा अणु
		/*
		 * Add a new connection to an existing session.
		 * We check क्रम a non-existant session in
		 * iscsi_login_non_zero_tsih_s2() below based
		 * on ISID/TSIH, but रुको until after authentication
		 * to check क्रम connection reinstatement, etc.
		 */
		अगर (iscsi_login_non_zero_tsih_s1(conn, buffer) < 0)
			जाओ new_sess_out;
	पूर्ण
	/*
	 * SessionType: Discovery
	 *
	 * 	Locates Default Portal
	 *
	 * SessionType: Normal
	 *
	 * 	Locates Target Portal from NP -> Target IQN
	 */
	rc = iscsi_target_locate_portal(np, conn, login);
	अगर (rc < 0) अणु
		tpg = conn->tpg;
		जाओ new_sess_out;
	पूर्ण
	login->zero_tsih = zero_tsih;

	अगर (conn->sess)
		conn->sess->se_sess->sup_prot_ops =
			conn->conn_transport->iscsit_get_sup_prot_ops(conn);

	tpg = conn->tpg;
	अगर (!tpg) अणु
		pr_err("Unable to locate struct iscsi_conn->tpg\n");
		जाओ new_sess_out;
	पूर्ण

	अगर (zero_tsih) अणु
		अगर (iscsi_login_zero_tsih_s2(conn) < 0)
			जाओ new_sess_out;
	पूर्ण अन्यथा अणु
		अगर (iscsi_login_non_zero_tsih_s2(conn, buffer) < 0)
			जाओ old_sess_out;
	पूर्ण

	अगर (conn->conn_transport->iscsit_validate_params) अणु
		ret = conn->conn_transport->iscsit_validate_params(conn);
		अगर (ret < 0) अणु
			अगर (zero_tsih)
				जाओ new_sess_out;
			अन्यथा
				जाओ old_sess_out;
		पूर्ण
	पूर्ण

	ret = iscsi_target_start_negotiation(login, conn);
	अगर (ret < 0)
		जाओ new_sess_out;

	iscsi_stop_login_thपढ़ो_समयr(np);

	अगर (ret == 1) अणु
		tpg_np = conn->tpg_np;

		iscsi_post_login_handler(np, conn, zero_tsih);
		iscsit_deaccess_np(np, tpg, tpg_np);
	पूर्ण

	tpg = शून्य;
	tpg_np = शून्य;
	/* Get another socket */
	वापस 1;

new_sess_out:
	new_sess = true;
old_sess_out:
	iscsi_stop_login_thपढ़ो_समयr(np);
	tpg_np = conn->tpg_np;
	iscsi_target_login_sess_out(conn, zero_tsih, new_sess);
	new_sess = false;

	अगर (tpg) अणु
		iscsit_deaccess_np(np, tpg, tpg_np);
		tpg = शून्य;
		tpg_np = शून्य;
	पूर्ण

	वापस 1;

निकास:
	iscsi_stop_login_thपढ़ो_समयr(np);
	spin_lock_bh(&np->np_thपढ़ो_lock);
	np->np_thपढ़ो_state = ISCSI_NP_THREAD_EXIT;
	spin_unlock_bh(&np->np_thपढ़ो_lock);

	वापस 0;
पूर्ण

पूर्णांक iscsi_target_login_thपढ़ो(व्योम *arg)
अणु
	काष्ठा iscsi_np *np = arg;
	पूर्णांक ret;

	allow_संकेत(संक_विघ्न);

	जबतक (1) अणु
		ret = __iscsi_target_login_thपढ़ो(np);
		/*
		 * We अवरोध and निकास here unless another sock_accept() call
		 * is expected.
		 */
		अगर (ret != 1)
			अवरोध;
	पूर्ण

	जबतक (!kthपढ़ो_should_stop()) अणु
		msleep(100);
	पूर्ण

	वापस 0;
पूर्ण
