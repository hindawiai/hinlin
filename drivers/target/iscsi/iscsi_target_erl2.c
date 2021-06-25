<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*******************************************************************************
 * This file contains error recovery level two functions used by
 * the iSCSI Target driver.
 *
 * (c) Copyright 2007-2013 Datera, Inc.
 *
 * Author: Nicholas A. Bellinger <nab@linux-iscsi.org>
 *
 ******************************************************************************/

#समावेश <linux/slab.h>
#समावेश <scsi/iscsi_proto.h>
#समावेश <target/target_core_base.h>
#समावेश <target/target_core_fabric.h>

#समावेश <target/iscsi/iscsi_target_core.h>
#समावेश "iscsi_target_datain_values.h"
#समावेश "iscsi_target_util.h"
#समावेश "iscsi_target_erl0.h"
#समावेश "iscsi_target_erl1.h"
#समावेश "iscsi_target_erl2.h"
#समावेश "iscsi_target.h"

/*
 *	FIXME: Does RData SNACK apply here as well?
 */
व्योम iscsit_create_conn_recovery_datain_values(
	काष्ठा iscsi_cmd *cmd,
	__be32 exp_data_sn)
अणु
	u32 data_sn = 0;
	काष्ठा iscsi_conn *conn = cmd->conn;

	cmd->next_burst_len = 0;
	cmd->पढ़ो_data_करोne = 0;

	जबतक (be32_to_cpu(exp_data_sn) > data_sn) अणु
		अगर ((cmd->next_burst_len +
		     conn->conn_ops->MaxRecvDataSegmentLength) <
		     conn->sess->sess_ops->MaxBurstLength) अणु
			cmd->पढ़ो_data_करोne +=
			       conn->conn_ops->MaxRecvDataSegmentLength;
			cmd->next_burst_len +=
			       conn->conn_ops->MaxRecvDataSegmentLength;
		पूर्ण अन्यथा अणु
			cmd->पढ़ो_data_करोne +=
				(conn->sess->sess_ops->MaxBurstLength -
				cmd->next_burst_len);
			cmd->next_burst_len = 0;
		पूर्ण
		data_sn++;
	पूर्ण
पूर्ण

व्योम iscsit_create_conn_recovery_dataout_values(
	काष्ठा iscsi_cmd *cmd)
अणु
	u32 ग_लिखो_data_करोne = 0;
	काष्ठा iscsi_conn *conn = cmd->conn;

	cmd->data_sn = 0;
	cmd->next_burst_len = 0;

	जबतक (cmd->ग_लिखो_data_करोne > ग_लिखो_data_करोne) अणु
		अगर ((ग_लिखो_data_करोne + conn->sess->sess_ops->MaxBurstLength) <=
		     cmd->ग_लिखो_data_करोne)
			ग_लिखो_data_करोne += conn->sess->sess_ops->MaxBurstLength;
		अन्यथा
			अवरोध;
	पूर्ण

	cmd->ग_लिखो_data_करोne = ग_लिखो_data_करोne;
पूर्ण

अटल पूर्णांक iscsit_attach_active_connection_recovery_entry(
	काष्ठा iscsi_session *sess,
	काष्ठा iscsi_conn_recovery *cr)
अणु
	spin_lock(&sess->cr_a_lock);
	list_add_tail(&cr->cr_list, &sess->cr_active_list);
	spin_unlock(&sess->cr_a_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक iscsit_attach_inactive_connection_recovery_entry(
	काष्ठा iscsi_session *sess,
	काष्ठा iscsi_conn_recovery *cr)
अणु
	spin_lock(&sess->cr_i_lock);
	list_add_tail(&cr->cr_list, &sess->cr_inactive_list);

	sess->conn_recovery_count++;
	pr_debug("Incremented connection recovery count to %u for"
		" SID: %u\n", sess->conn_recovery_count, sess->sid);
	spin_unlock(&sess->cr_i_lock);

	वापस 0;
पूर्ण

काष्ठा iscsi_conn_recovery *iscsit_get_inactive_connection_recovery_entry(
	काष्ठा iscsi_session *sess,
	u16 cid)
अणु
	काष्ठा iscsi_conn_recovery *cr;

	spin_lock(&sess->cr_i_lock);
	list_क्रम_each_entry(cr, &sess->cr_inactive_list, cr_list) अणु
		अगर (cr->cid == cid) अणु
			spin_unlock(&sess->cr_i_lock);
			वापस cr;
		पूर्ण
	पूर्ण
	spin_unlock(&sess->cr_i_lock);

	वापस शून्य;
पूर्ण

व्योम iscsit_मुक्त_connection_recovery_entries(काष्ठा iscsi_session *sess)
अणु
	काष्ठा iscsi_cmd *cmd, *cmd_पंचांगp;
	काष्ठा iscsi_conn_recovery *cr, *cr_पंचांगp;

	spin_lock(&sess->cr_a_lock);
	list_क्रम_each_entry_safe(cr, cr_पंचांगp, &sess->cr_active_list, cr_list) अणु
		list_del(&cr->cr_list);
		spin_unlock(&sess->cr_a_lock);

		spin_lock(&cr->conn_recovery_cmd_lock);
		list_क्रम_each_entry_safe(cmd, cmd_पंचांगp,
				&cr->conn_recovery_cmd_list, i_conn_node) अणु

			list_del_init(&cmd->i_conn_node);
			cmd->conn = शून्य;
			spin_unlock(&cr->conn_recovery_cmd_lock);
			iscsit_मुक्त_cmd(cmd, true);
			spin_lock(&cr->conn_recovery_cmd_lock);
		पूर्ण
		spin_unlock(&cr->conn_recovery_cmd_lock);
		spin_lock(&sess->cr_a_lock);

		kमुक्त(cr);
	पूर्ण
	spin_unlock(&sess->cr_a_lock);

	spin_lock(&sess->cr_i_lock);
	list_क्रम_each_entry_safe(cr, cr_पंचांगp, &sess->cr_inactive_list, cr_list) अणु
		list_del(&cr->cr_list);
		spin_unlock(&sess->cr_i_lock);

		spin_lock(&cr->conn_recovery_cmd_lock);
		list_क्रम_each_entry_safe(cmd, cmd_पंचांगp,
				&cr->conn_recovery_cmd_list, i_conn_node) अणु

			list_del_init(&cmd->i_conn_node);
			cmd->conn = शून्य;
			spin_unlock(&cr->conn_recovery_cmd_lock);
			iscsit_मुक्त_cmd(cmd, true);
			spin_lock(&cr->conn_recovery_cmd_lock);
		पूर्ण
		spin_unlock(&cr->conn_recovery_cmd_lock);
		spin_lock(&sess->cr_i_lock);

		kमुक्त(cr);
	पूर्ण
	spin_unlock(&sess->cr_i_lock);
पूर्ण

पूर्णांक iscsit_हटाओ_active_connection_recovery_entry(
	काष्ठा iscsi_conn_recovery *cr,
	काष्ठा iscsi_session *sess)
अणु
	spin_lock(&sess->cr_a_lock);
	list_del(&cr->cr_list);

	sess->conn_recovery_count--;
	pr_debug("Decremented connection recovery count to %u for"
		" SID: %u\n", sess->conn_recovery_count, sess->sid);
	spin_unlock(&sess->cr_a_lock);

	kमुक्त(cr);

	वापस 0;
पूर्ण

अटल व्योम iscsit_हटाओ_inactive_connection_recovery_entry(
	काष्ठा iscsi_conn_recovery *cr,
	काष्ठा iscsi_session *sess)
अणु
	spin_lock(&sess->cr_i_lock);
	list_del(&cr->cr_list);
	spin_unlock(&sess->cr_i_lock);
पूर्ण

/*
 *	Called with cr->conn_recovery_cmd_lock help.
 */
पूर्णांक iscsit_हटाओ_cmd_from_connection_recovery(
	काष्ठा iscsi_cmd *cmd,
	काष्ठा iscsi_session *sess)
अणु
	काष्ठा iscsi_conn_recovery *cr;

	अगर (!cmd->cr) अणु
		pr_err("struct iscsi_conn_recovery pointer for ITT: 0x%08x"
			" is NULL!\n", cmd->init_task_tag);
		BUG();
	पूर्ण
	cr = cmd->cr;

	list_del_init(&cmd->i_conn_node);
	वापस --cr->cmd_count;
पूर्ण

व्योम iscsit_discard_cr_cmds_by_expstatsn(
	काष्ठा iscsi_conn_recovery *cr,
	u32 exp_statsn)
अणु
	u32 dropped_count = 0;
	काष्ठा iscsi_cmd *cmd, *cmd_पंचांगp;
	काष्ठा iscsi_session *sess = cr->sess;

	spin_lock(&cr->conn_recovery_cmd_lock);
	list_क्रम_each_entry_safe(cmd, cmd_पंचांगp,
			&cr->conn_recovery_cmd_list, i_conn_node) अणु

		अगर (((cmd->deferred_i_state != ISTATE_SENT_STATUS) &&
		     (cmd->deferred_i_state != ISTATE_REMOVE)) ||
		     (cmd->stat_sn >= exp_statsn)) अणु
			जारी;
		पूर्ण

		dropped_count++;
		pr_debug("Dropping Acknowledged ITT: 0x%08x, StatSN:"
			" 0x%08x, CID: %hu.\n", cmd->init_task_tag,
				cmd->stat_sn, cr->cid);

		iscsit_हटाओ_cmd_from_connection_recovery(cmd, sess);

		spin_unlock(&cr->conn_recovery_cmd_lock);
		iscsit_मुक्त_cmd(cmd, true);
		spin_lock(&cr->conn_recovery_cmd_lock);
	पूर्ण
	spin_unlock(&cr->conn_recovery_cmd_lock);

	pr_debug("Dropped %u total acknowledged commands on"
		" CID: %hu less than old ExpStatSN: 0x%08x\n",
			dropped_count, cr->cid, exp_statsn);

	अगर (!cr->cmd_count) अणु
		pr_debug("No commands to be reassigned for failed"
			" connection CID: %hu on SID: %u\n",
			cr->cid, sess->sid);
		iscsit_हटाओ_inactive_connection_recovery_entry(cr, sess);
		iscsit_attach_active_connection_recovery_entry(sess, cr);
		pr_debug("iSCSI connection recovery successful for CID:"
			" %hu on SID: %u\n", cr->cid, sess->sid);
		iscsit_हटाओ_active_connection_recovery_entry(cr, sess);
	पूर्ण अन्यथा अणु
		iscsit_हटाओ_inactive_connection_recovery_entry(cr, sess);
		iscsit_attach_active_connection_recovery_entry(sess, cr);
	पूर्ण
पूर्ण

पूर्णांक iscsit_discard_unacknowledged_ooo_cmdsns_क्रम_conn(काष्ठा iscsi_conn *conn)
अणु
	u32 dropped_count = 0;
	काष्ठा iscsi_cmd *cmd, *cmd_पंचांगp;
	काष्ठा iscsi_ooo_cmdsn *ooo_cmdsn, *ooo_cmdsn_पंचांगp;
	काष्ठा iscsi_session *sess = conn->sess;

	mutex_lock(&sess->cmdsn_mutex);
	list_क्रम_each_entry_safe(ooo_cmdsn, ooo_cmdsn_पंचांगp,
			&sess->sess_ooo_cmdsn_list, ooo_list) अणु

		अगर (ooo_cmdsn->cid != conn->cid)
			जारी;

		dropped_count++;
		pr_debug("Dropping unacknowledged CmdSN:"
		" 0x%08x during connection recovery on CID: %hu\n",
			ooo_cmdsn->cmdsn, conn->cid);
		iscsit_हटाओ_ooo_cmdsn(sess, ooo_cmdsn);
	पूर्ण
	mutex_unlock(&sess->cmdsn_mutex);

	spin_lock_bh(&conn->cmd_lock);
	list_क्रम_each_entry_safe(cmd, cmd_पंचांगp, &conn->conn_cmd_list, i_conn_node) अणु
		अगर (!(cmd->cmd_flags & ICF_OOO_CMDSN))
			जारी;

		list_del_init(&cmd->i_conn_node);

		spin_unlock_bh(&conn->cmd_lock);
		iscsit_मुक्त_cmd(cmd, true);
		spin_lock_bh(&conn->cmd_lock);
	पूर्ण
	spin_unlock_bh(&conn->cmd_lock);

	pr_debug("Dropped %u total unacknowledged commands on CID:"
		" %hu for ExpCmdSN: 0x%08x.\n", dropped_count, conn->cid,
				sess->exp_cmd_sn);
	वापस 0;
पूर्ण

पूर्णांक iscsit_prepare_cmds_क्रम_reallegiance(काष्ठा iscsi_conn *conn)
अणु
	u32 cmd_count = 0;
	काष्ठा iscsi_cmd *cmd, *cmd_पंचांगp;
	काष्ठा iscsi_conn_recovery *cr;

	/*
	 * Allocate an काष्ठा iscsi_conn_recovery क्रम this connection.
	 * Each काष्ठा iscsi_cmd contains an काष्ठा iscsi_conn_recovery poपूर्णांकer
	 * (काष्ठा iscsi_cmd->cr) so we need to allocate this beक्रमe preparing the
	 * connection's command list क्रम connection recovery.
	 */
	cr = kzalloc(माप(काष्ठा iscsi_conn_recovery), GFP_KERNEL);
	अगर (!cr) अणु
		pr_err("Unable to allocate memory for"
			" struct iscsi_conn_recovery.\n");
		वापस -1;
	पूर्ण
	INIT_LIST_HEAD(&cr->cr_list);
	INIT_LIST_HEAD(&cr->conn_recovery_cmd_list);
	spin_lock_init(&cr->conn_recovery_cmd_lock);
	/*
	 * Only perक्रमm connection recovery on ISCSI_OP_SCSI_CMD or
	 * ISCSI_OP_NOOP_OUT opcodes.  For all other opcodes call
	 * list_del_init(&cmd->i_conn_node); to release the command to the
	 * session pool and हटाओ it from the connection's list.
	 *
	 * Also stop the DataOUT समयr, which will be restarted after
	 * sending the TMR response.
	 */
	spin_lock_bh(&conn->cmd_lock);
	list_क्रम_each_entry_safe(cmd, cmd_पंचांगp, &conn->conn_cmd_list, i_conn_node) अणु

		अगर ((cmd->iscsi_opcode != ISCSI_OP_SCSI_CMD) &&
		    (cmd->iscsi_opcode != ISCSI_OP_NOOP_OUT)) अणु
			pr_debug("Not performing reallegiance on"
				" Opcode: 0x%02x, ITT: 0x%08x, CmdSN: 0x%08x,"
				" CID: %hu\n", cmd->iscsi_opcode,
				cmd->init_task_tag, cmd->cmd_sn, conn->cid);

			list_del_init(&cmd->i_conn_node);
			spin_unlock_bh(&conn->cmd_lock);
			iscsit_मुक्त_cmd(cmd, true);
			spin_lock_bh(&conn->cmd_lock);
			जारी;
		पूर्ण

		/*
		 * Special हाल where commands greater than or equal to
		 * the session's ExpCmdSN are attached to the connection
		 * list but not to the out of order CmdSN list.  The one
		 * obvious हाल is when a command with immediate data
		 * attached must only check the CmdSN against ExpCmdSN
		 * after the data is received.  The special हाल below
		 * is when the connection fails beक्रमe data is received,
		 * but also may apply to other PDUs, so it has been
		 * made generic here.
		 */
		अगर (!(cmd->cmd_flags & ICF_OOO_CMDSN) && !cmd->immediate_cmd &&
		     iscsi_sna_gte(cmd->cmd_sn, conn->sess->exp_cmd_sn)) अणु
			list_del_init(&cmd->i_conn_node);
			spin_unlock_bh(&conn->cmd_lock);
			iscsit_मुक्त_cmd(cmd, true);
			spin_lock_bh(&conn->cmd_lock);
			जारी;
		पूर्ण

		cmd_count++;
		pr_debug("Preparing Opcode: 0x%02x, ITT: 0x%08x,"
			" CmdSN: 0x%08x, StatSN: 0x%08x, CID: %hu for"
			" reallegiance.\n", cmd->iscsi_opcode,
			cmd->init_task_tag, cmd->cmd_sn, cmd->stat_sn,
			conn->cid);

		cmd->deferred_i_state = cmd->i_state;
		cmd->i_state = ISTATE_IN_CONNECTION_RECOVERY;

		अगर (cmd->data_direction == DMA_TO_DEVICE)
			iscsit_stop_dataout_समयr(cmd);

		cmd->sess = conn->sess;

		list_del_init(&cmd->i_conn_node);
		spin_unlock_bh(&conn->cmd_lock);

		iscsit_मुक्त_all_datain_reqs(cmd);

		transport_रुको_क्रम_tasks(&cmd->se_cmd);
		/*
		 * Add the काष्ठा iscsi_cmd to the connection recovery cmd list
		 */
		spin_lock(&cr->conn_recovery_cmd_lock);
		list_add_tail(&cmd->i_conn_node, &cr->conn_recovery_cmd_list);
		spin_unlock(&cr->conn_recovery_cmd_lock);

		spin_lock_bh(&conn->cmd_lock);
		cmd->cr = cr;
		cmd->conn = शून्य;
	पूर्ण
	spin_unlock_bh(&conn->cmd_lock);
	/*
	 * Fill in the various values in the pपुनः_स्मृतिated काष्ठा iscsi_conn_recovery.
	 */
	cr->cid = conn->cid;
	cr->cmd_count = cmd_count;
	cr->maxrecvdatasegmentlength = conn->conn_ops->MaxRecvDataSegmentLength;
	cr->maxxmitdatasegmentlength = conn->conn_ops->MaxXmitDataSegmentLength;
	cr->sess = conn->sess;

	iscsit_attach_inactive_connection_recovery_entry(conn->sess, cr);

	वापस 0;
पूर्ण

पूर्णांक iscsit_connection_recovery_transport_reset(काष्ठा iscsi_conn *conn)
अणु
	atomic_set(&conn->connection_recovery, 1);

	अगर (iscsit_बंद_connection(conn) < 0)
		वापस -1;

	वापस 0;
पूर्ण
