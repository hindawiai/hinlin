<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*******************************************************************************
 * This file contains the iSCSI Target specअगरic utility functions.
 *
 * (c) Copyright 2007-2013 Datera, Inc.
 *
 * Author: Nicholas A. Bellinger <nab@linux-iscsi.org>
 *
 ******************************************************************************/

#समावेश <linux/list.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <net/ipv6.h>         /* ipv6_addr_equal() */
#समावेश <scsi/scsi_tcq.h>
#समावेश <scsi/iscsi_proto.h>
#समावेश <target/target_core_base.h>
#समावेश <target/target_core_fabric.h>
#समावेश <target/iscsi/iscsi_transport.h>

#समावेश <target/iscsi/iscsi_target_core.h>
#समावेश "iscsi_target_parameters.h"
#समावेश "iscsi_target_seq_pdu_list.h"
#समावेश "iscsi_target_datain_values.h"
#समावेश "iscsi_target_erl0.h"
#समावेश "iscsi_target_erl1.h"
#समावेश "iscsi_target_erl2.h"
#समावेश "iscsi_target_tpg.h"
#समावेश "iscsi_target_util.h"
#समावेश "iscsi_target.h"

बाह्य काष्ठा list_head g_tiqn_list;
बाह्य spinlock_t tiqn_lock;

पूर्णांक iscsit_add_r2t_to_list(
	काष्ठा iscsi_cmd *cmd,
	u32 offset,
	u32 xfer_len,
	पूर्णांक recovery,
	u32 r2t_sn)
अणु
	काष्ठा iscsi_r2t *r2t;

	lockdep_निश्चित_held(&cmd->r2t_lock);

	WARN_ON_ONCE((s32)xfer_len < 0);

	r2t = kmem_cache_zalloc(lio_r2t_cache, GFP_ATOMIC);
	अगर (!r2t) अणु
		pr_err("Unable to allocate memory for struct iscsi_r2t.\n");
		वापस -1;
	पूर्ण
	INIT_LIST_HEAD(&r2t->r2t_list);

	r2t->recovery_r2t = recovery;
	r2t->r2t_sn = (!r2t_sn) ? cmd->r2t_sn++ : r2t_sn;
	r2t->offset = offset;
	r2t->xfer_len = xfer_len;
	list_add_tail(&r2t->r2t_list, &cmd->cmd_r2t_list);
	spin_unlock_bh(&cmd->r2t_lock);

	iscsit_add_cmd_to_immediate_queue(cmd, cmd->conn, ISTATE_SEND_R2T);

	spin_lock_bh(&cmd->r2t_lock);
	वापस 0;
पूर्ण

काष्ठा iscsi_r2t *iscsit_get_r2t_क्रम_eos(
	काष्ठा iscsi_cmd *cmd,
	u32 offset,
	u32 length)
अणु
	काष्ठा iscsi_r2t *r2t;

	spin_lock_bh(&cmd->r2t_lock);
	list_क्रम_each_entry(r2t, &cmd->cmd_r2t_list, r2t_list) अणु
		अगर ((r2t->offset <= offset) &&
		    (r2t->offset + r2t->xfer_len) >= (offset + length)) अणु
			spin_unlock_bh(&cmd->r2t_lock);
			वापस r2t;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&cmd->r2t_lock);

	pr_err("Unable to locate R2T for Offset: %u, Length:"
			" %u\n", offset, length);
	वापस शून्य;
पूर्ण

काष्ठा iscsi_r2t *iscsit_get_r2t_from_list(काष्ठा iscsi_cmd *cmd)
अणु
	काष्ठा iscsi_r2t *r2t;

	spin_lock_bh(&cmd->r2t_lock);
	list_क्रम_each_entry(r2t, &cmd->cmd_r2t_list, r2t_list) अणु
		अगर (!r2t->sent_r2t) अणु
			spin_unlock_bh(&cmd->r2t_lock);
			वापस r2t;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&cmd->r2t_lock);

	pr_err("Unable to locate next R2T to send for ITT:"
			" 0x%08x.\n", cmd->init_task_tag);
	वापस शून्य;
पूर्ण

व्योम iscsit_मुक्त_r2t(काष्ठा iscsi_r2t *r2t, काष्ठा iscsi_cmd *cmd)
अणु
	lockdep_निश्चित_held(&cmd->r2t_lock);

	list_del(&r2t->r2t_list);
	kmem_cache_मुक्त(lio_r2t_cache, r2t);
पूर्ण

व्योम iscsit_मुक्त_r2ts_from_list(काष्ठा iscsi_cmd *cmd)
अणु
	काष्ठा iscsi_r2t *r2t, *r2t_पंचांगp;

	spin_lock_bh(&cmd->r2t_lock);
	list_क्रम_each_entry_safe(r2t, r2t_पंचांगp, &cmd->cmd_r2t_list, r2t_list)
		iscsit_मुक्त_r2t(r2t, cmd);
	spin_unlock_bh(&cmd->r2t_lock);
पूर्ण

अटल पूर्णांक iscsit_रुको_क्रम_tag(काष्ठा se_session *se_sess, पूर्णांक state, पूर्णांक *cpup)
अणु
	पूर्णांक tag = -1;
	DEFINE_SBQ_WAIT(रुको);
	काष्ठा sbq_रुको_state *ws;
	काष्ठा sbiपंचांगap_queue *sbq;

	अगर (state == TASK_RUNNING)
		वापस tag;

	sbq = &se_sess->sess_tag_pool;
	ws = &sbq->ws[0];
	क्रम (;;) अणु
		sbiपंचांगap_prepare_to_रुको(sbq, ws, &रुको, state);
		अगर (संकेत_pending_state(state, current))
			अवरोध;
		tag = sbiपंचांगap_queue_get(sbq, cpup);
		अगर (tag >= 0)
			अवरोध;
		schedule();
	पूर्ण

	sbiपंचांगap_finish_रुको(sbq, ws, &रुको);
	वापस tag;
पूर्ण

/*
 * May be called from software पूर्णांकerrupt (समयr) context क्रम allocating
 * iSCSI NopINs.
 */
काष्ठा iscsi_cmd *iscsit_allocate_cmd(काष्ठा iscsi_conn *conn, पूर्णांक state)
अणु
	काष्ठा iscsi_cmd *cmd;
	काष्ठा se_session *se_sess = conn->sess->se_sess;
	पूर्णांक size, tag, cpu;

	tag = sbiपंचांगap_queue_get(&se_sess->sess_tag_pool, &cpu);
	अगर (tag < 0)
		tag = iscsit_रुको_क्रम_tag(se_sess, state, &cpu);
	अगर (tag < 0)
		वापस शून्य;

	size = माप(काष्ठा iscsi_cmd) + conn->conn_transport->priv_size;
	cmd = (काष्ठा iscsi_cmd *)(se_sess->sess_cmd_map + (tag * size));
	स_रखो(cmd, 0, size);

	cmd->se_cmd.map_tag = tag;
	cmd->se_cmd.map_cpu = cpu;
	cmd->conn = conn;
	cmd->data_direction = DMA_NONE;
	INIT_LIST_HEAD(&cmd->i_conn_node);
	INIT_LIST_HEAD(&cmd->datain_list);
	INIT_LIST_HEAD(&cmd->cmd_r2t_list);
	spin_lock_init(&cmd->datain_lock);
	spin_lock_init(&cmd->dataout_समयout_lock);
	spin_lock_init(&cmd->istate_lock);
	spin_lock_init(&cmd->error_lock);
	spin_lock_init(&cmd->r2t_lock);
	समयr_setup(&cmd->dataout_समयr, iscsit_handle_dataout_समयout, 0);

	वापस cmd;
पूर्ण
EXPORT_SYMBOL(iscsit_allocate_cmd);

काष्ठा iscsi_seq *iscsit_get_seq_holder_क्रम_datain(
	काष्ठा iscsi_cmd *cmd,
	u32 seq_send_order)
अणु
	u32 i;

	क्रम (i = 0; i < cmd->seq_count; i++)
		अगर (cmd->seq_list[i].seq_send_order == seq_send_order)
			वापस &cmd->seq_list[i];

	वापस शून्य;
पूर्ण

काष्ठा iscsi_seq *iscsit_get_seq_holder_क्रम_r2t(काष्ठा iscsi_cmd *cmd)
अणु
	u32 i;

	अगर (!cmd->seq_list) अणु
		pr_err("struct iscsi_cmd->seq_list is NULL!\n");
		वापस शून्य;
	पूर्ण

	क्रम (i = 0; i < cmd->seq_count; i++) अणु
		अगर (cmd->seq_list[i].type != SEQTYPE_NORMAL)
			जारी;
		अगर (cmd->seq_list[i].seq_send_order == cmd->seq_send_order) अणु
			cmd->seq_send_order++;
			वापस &cmd->seq_list[i];
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा iscsi_r2t *iscsit_get_holder_क्रम_r2tsn(
	काष्ठा iscsi_cmd *cmd,
	u32 r2t_sn)
अणु
	काष्ठा iscsi_r2t *r2t;

	spin_lock_bh(&cmd->r2t_lock);
	list_क्रम_each_entry(r2t, &cmd->cmd_r2t_list, r2t_list) अणु
		अगर (r2t->r2t_sn == r2t_sn) अणु
			spin_unlock_bh(&cmd->r2t_lock);
			वापस r2t;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&cmd->r2t_lock);

	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक iscsit_check_received_cmdsn(काष्ठा iscsi_session *sess, u32 cmdsn)
अणु
	u32 max_cmdsn;
	पूर्णांक ret;

	/*
	 * This is the proper method of checking received CmdSN against
	 * ExpCmdSN and MaxCmdSN values, as well as accounting क्रम out
	 * or order CmdSNs due to multiple connection sessions and/or
	 * CRC failures.
	 */
	max_cmdsn = atomic_पढ़ो(&sess->max_cmd_sn);
	अगर (iscsi_sna_gt(cmdsn, max_cmdsn)) अणु
		pr_err("Received CmdSN: 0x%08x is greater than"
		       " MaxCmdSN: 0x%08x, ignoring.\n", cmdsn, max_cmdsn);
		ret = CMDSN_MAXCMDSN_OVERRUN;

	पूर्ण अन्यथा अगर (cmdsn == sess->exp_cmd_sn) अणु
		sess->exp_cmd_sn++;
		pr_debug("Received CmdSN matches ExpCmdSN,"
		      " incremented ExpCmdSN to: 0x%08x\n",
		      sess->exp_cmd_sn);
		ret = CMDSN_NORMAL_OPERATION;

	पूर्ण अन्यथा अगर (iscsi_sna_gt(cmdsn, sess->exp_cmd_sn)) अणु
		pr_debug("Received CmdSN: 0x%08x is greater"
		      " than ExpCmdSN: 0x%08x, not acknowledging.\n",
		      cmdsn, sess->exp_cmd_sn);
		ret = CMDSN_HIGHER_THAN_EXP;

	पूर्ण अन्यथा अणु
		pr_err("Received CmdSN: 0x%08x is less than"
		       " ExpCmdSN: 0x%08x, ignoring.\n", cmdsn,
		       sess->exp_cmd_sn);
		ret = CMDSN_LOWER_THAN_EXP;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Commands may be received out of order अगर MC/S is in use.
 * Ensure they are executed in CmdSN order.
 */
पूर्णांक iscsit_sequence_cmd(काष्ठा iscsi_conn *conn, काष्ठा iscsi_cmd *cmd,
			अचिन्हित अक्षर *buf, __be32 cmdsn)
अणु
	पूर्णांक ret, cmdsn_ret;
	bool reject = false;
	u8 reason = ISCSI_REASON_BOOKMARK_NO_RESOURCES;

	mutex_lock(&conn->sess->cmdsn_mutex);

	cmdsn_ret = iscsit_check_received_cmdsn(conn->sess, be32_to_cpu(cmdsn));
	चयन (cmdsn_ret) अणु
	हाल CMDSN_NORMAL_OPERATION:
		ret = iscsit_execute_cmd(cmd, 0);
		अगर ((ret >= 0) && !list_empty(&conn->sess->sess_ooo_cmdsn_list))
			iscsit_execute_ooo_cmdsns(conn->sess);
		अन्यथा अगर (ret < 0) अणु
			reject = true;
			ret = CMDSN_ERROR_CANNOT_RECOVER;
		पूर्ण
		अवरोध;
	हाल CMDSN_HIGHER_THAN_EXP:
		ret = iscsit_handle_ooo_cmdsn(conn->sess, cmd, be32_to_cpu(cmdsn));
		अगर (ret < 0) अणु
			reject = true;
			ret = CMDSN_ERROR_CANNOT_RECOVER;
			अवरोध;
		पूर्ण
		ret = CMDSN_HIGHER_THAN_EXP;
		अवरोध;
	हाल CMDSN_LOWER_THAN_EXP:
	हाल CMDSN_MAXCMDSN_OVERRUN:
	शेष:
		cmd->i_state = ISTATE_REMOVE;
		iscsit_add_cmd_to_immediate_queue(cmd, conn, cmd->i_state);
		/*
		 * Existing callers क्रम iscsit_sequence_cmd() will silently
		 * ignore commands with CMDSN_LOWER_THAN_EXP, so क्रमce this
		 * वापस क्रम CMDSN_MAXCMDSN_OVERRUN as well..
		 */
		ret = CMDSN_LOWER_THAN_EXP;
		अवरोध;
	पूर्ण
	mutex_unlock(&conn->sess->cmdsn_mutex);

	अगर (reject)
		iscsit_reject_cmd(cmd, reason, buf);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(iscsit_sequence_cmd);

पूर्णांक iscsit_check_unsolicited_dataout(काष्ठा iscsi_cmd *cmd, अचिन्हित अक्षर *buf)
अणु
	काष्ठा iscsi_conn *conn = cmd->conn;
	काष्ठा se_cmd *se_cmd = &cmd->se_cmd;
	काष्ठा iscsi_data *hdr = (काष्ठा iscsi_data *) buf;
	u32 payload_length = ntoh24(hdr->dlength);

	अगर (conn->sess->sess_ops->InitialR2T) अणु
		pr_err("Received unexpected unsolicited data"
			" while InitialR2T=Yes, protocol error.\n");
		transport_send_check_condition_and_sense(se_cmd,
				TCM_UNEXPECTED_UNSOLICITED_DATA, 0);
		वापस -1;
	पूर्ण

	अगर ((cmd->first_burst_len + payload_length) >
	     conn->sess->sess_ops->FirstBurstLength) अणु
		pr_err("Total %u bytes exceeds FirstBurstLength: %u"
			" for this Unsolicited DataOut Burst.\n",
			(cmd->first_burst_len + payload_length),
				conn->sess->sess_ops->FirstBurstLength);
		transport_send_check_condition_and_sense(se_cmd,
				TCM_INCORRECT_AMOUNT_OF_DATA, 0);
		वापस -1;
	पूर्ण

	अगर (!(hdr->flags & ISCSI_FLAG_CMD_FINAL))
		वापस 0;

	अगर (((cmd->first_burst_len + payload_length) != cmd->se_cmd.data_length) &&
	    ((cmd->first_burst_len + payload_length) !=
	      conn->sess->sess_ops->FirstBurstLength)) अणु
		pr_err("Unsolicited non-immediate data received %u"
			" does not equal FirstBurstLength: %u, and does"
			" not equal ExpXferLen %u.\n",
			(cmd->first_burst_len + payload_length),
			conn->sess->sess_ops->FirstBurstLength, cmd->se_cmd.data_length);
		transport_send_check_condition_and_sense(se_cmd,
				TCM_INCORRECT_AMOUNT_OF_DATA, 0);
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

काष्ठा iscsi_cmd *iscsit_find_cmd_from_itt(
	काष्ठा iscsi_conn *conn,
	itt_t init_task_tag)
अणु
	काष्ठा iscsi_cmd *cmd;

	spin_lock_bh(&conn->cmd_lock);
	list_क्रम_each_entry(cmd, &conn->conn_cmd_list, i_conn_node) अणु
		अगर (cmd->init_task_tag == init_task_tag) अणु
			spin_unlock_bh(&conn->cmd_lock);
			वापस cmd;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&conn->cmd_lock);

	pr_err("Unable to locate ITT: 0x%08x on CID: %hu",
			init_task_tag, conn->cid);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(iscsit_find_cmd_from_itt);

काष्ठा iscsi_cmd *iscsit_find_cmd_from_itt_or_dump(
	काष्ठा iscsi_conn *conn,
	itt_t init_task_tag,
	u32 length)
अणु
	काष्ठा iscsi_cmd *cmd;

	spin_lock_bh(&conn->cmd_lock);
	list_क्रम_each_entry(cmd, &conn->conn_cmd_list, i_conn_node) अणु
		अगर (cmd->cmd_flags & ICF_GOT_LAST_DATAOUT)
			जारी;
		अगर (cmd->init_task_tag == init_task_tag) अणु
			spin_unlock_bh(&conn->cmd_lock);
			वापस cmd;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&conn->cmd_lock);

	pr_err("Unable to locate ITT: 0x%08x on CID: %hu,"
			" dumping payload\n", init_task_tag, conn->cid);
	अगर (length)
		iscsit_dump_data_payload(conn, length, 1);

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(iscsit_find_cmd_from_itt_or_dump);

काष्ठा iscsi_cmd *iscsit_find_cmd_from_ttt(
	काष्ठा iscsi_conn *conn,
	u32 targ_xfer_tag)
अणु
	काष्ठा iscsi_cmd *cmd = शून्य;

	spin_lock_bh(&conn->cmd_lock);
	list_क्रम_each_entry(cmd, &conn->conn_cmd_list, i_conn_node) अणु
		अगर (cmd->targ_xfer_tag == targ_xfer_tag) अणु
			spin_unlock_bh(&conn->cmd_lock);
			वापस cmd;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&conn->cmd_lock);

	pr_err("Unable to locate TTT: 0x%08x on CID: %hu\n",
			targ_xfer_tag, conn->cid);
	वापस शून्य;
पूर्ण

पूर्णांक iscsit_find_cmd_क्रम_recovery(
	काष्ठा iscsi_session *sess,
	काष्ठा iscsi_cmd **cmd_ptr,
	काष्ठा iscsi_conn_recovery **cr_ptr,
	itt_t init_task_tag)
अणु
	काष्ठा iscsi_cmd *cmd = शून्य;
	काष्ठा iscsi_conn_recovery *cr;
	/*
	 * Scan through the inactive connection recovery list's command list.
	 * If init_task_tag matches the command is still alligent.
	 */
	spin_lock(&sess->cr_i_lock);
	list_क्रम_each_entry(cr, &sess->cr_inactive_list, cr_list) अणु
		spin_lock(&cr->conn_recovery_cmd_lock);
		list_क्रम_each_entry(cmd, &cr->conn_recovery_cmd_list, i_conn_node) अणु
			अगर (cmd->init_task_tag == init_task_tag) अणु
				spin_unlock(&cr->conn_recovery_cmd_lock);
				spin_unlock(&sess->cr_i_lock);

				*cr_ptr = cr;
				*cmd_ptr = cmd;
				वापस -2;
			पूर्ण
		पूर्ण
		spin_unlock(&cr->conn_recovery_cmd_lock);
	पूर्ण
	spin_unlock(&sess->cr_i_lock);
	/*
	 * Scan through the active connection recovery list's command list.
	 * If init_task_tag matches the command is पढ़ोy to be reasचिन्हित.
	 */
	spin_lock(&sess->cr_a_lock);
	list_क्रम_each_entry(cr, &sess->cr_active_list, cr_list) अणु
		spin_lock(&cr->conn_recovery_cmd_lock);
		list_क्रम_each_entry(cmd, &cr->conn_recovery_cmd_list, i_conn_node) अणु
			अगर (cmd->init_task_tag == init_task_tag) अणु
				spin_unlock(&cr->conn_recovery_cmd_lock);
				spin_unlock(&sess->cr_a_lock);

				*cr_ptr = cr;
				*cmd_ptr = cmd;
				वापस 0;
			पूर्ण
		पूर्ण
		spin_unlock(&cr->conn_recovery_cmd_lock);
	पूर्ण
	spin_unlock(&sess->cr_a_lock);

	वापस -1;
पूर्ण

व्योम iscsit_add_cmd_to_immediate_queue(
	काष्ठा iscsi_cmd *cmd,
	काष्ठा iscsi_conn *conn,
	u8 state)
अणु
	काष्ठा iscsi_queue_req *qr;

	qr = kmem_cache_zalloc(lio_qr_cache, GFP_ATOMIC);
	अगर (!qr) अणु
		pr_err("Unable to allocate memory for"
				" struct iscsi_queue_req\n");
		वापस;
	पूर्ण
	INIT_LIST_HEAD(&qr->qr_list);
	qr->cmd = cmd;
	qr->state = state;

	spin_lock_bh(&conn->immed_queue_lock);
	list_add_tail(&qr->qr_list, &conn->immed_queue_list);
	atomic_inc(&cmd->immed_queue_count);
	atomic_set(&conn->check_immediate_queue, 1);
	spin_unlock_bh(&conn->immed_queue_lock);

	wake_up(&conn->queues_wq);
पूर्ण
EXPORT_SYMBOL(iscsit_add_cmd_to_immediate_queue);

काष्ठा iscsi_queue_req *iscsit_get_cmd_from_immediate_queue(काष्ठा iscsi_conn *conn)
अणु
	काष्ठा iscsi_queue_req *qr;

	spin_lock_bh(&conn->immed_queue_lock);
	अगर (list_empty(&conn->immed_queue_list)) अणु
		spin_unlock_bh(&conn->immed_queue_lock);
		वापस शून्य;
	पूर्ण
	qr = list_first_entry(&conn->immed_queue_list,
			      काष्ठा iscsi_queue_req, qr_list);

	list_del(&qr->qr_list);
	अगर (qr->cmd)
		atomic_dec(&qr->cmd->immed_queue_count);
	spin_unlock_bh(&conn->immed_queue_lock);

	वापस qr;
पूर्ण

अटल व्योम iscsit_हटाओ_cmd_from_immediate_queue(
	काष्ठा iscsi_cmd *cmd,
	काष्ठा iscsi_conn *conn)
अणु
	काष्ठा iscsi_queue_req *qr, *qr_पंचांगp;

	spin_lock_bh(&conn->immed_queue_lock);
	अगर (!atomic_पढ़ो(&cmd->immed_queue_count)) अणु
		spin_unlock_bh(&conn->immed_queue_lock);
		वापस;
	पूर्ण

	list_क्रम_each_entry_safe(qr, qr_पंचांगp, &conn->immed_queue_list, qr_list) अणु
		अगर (qr->cmd != cmd)
			जारी;

		atomic_dec(&qr->cmd->immed_queue_count);
		list_del(&qr->qr_list);
		kmem_cache_मुक्त(lio_qr_cache, qr);
	पूर्ण
	spin_unlock_bh(&conn->immed_queue_lock);

	अगर (atomic_पढ़ो(&cmd->immed_queue_count)) अणु
		pr_err("ITT: 0x%08x immed_queue_count: %d\n",
			cmd->init_task_tag,
			atomic_पढ़ो(&cmd->immed_queue_count));
	पूर्ण
पूर्ण

पूर्णांक iscsit_add_cmd_to_response_queue(
	काष्ठा iscsi_cmd *cmd,
	काष्ठा iscsi_conn *conn,
	u8 state)
अणु
	काष्ठा iscsi_queue_req *qr;

	qr = kmem_cache_zalloc(lio_qr_cache, GFP_ATOMIC);
	अगर (!qr) अणु
		pr_err("Unable to allocate memory for"
			" struct iscsi_queue_req\n");
		वापस -ENOMEM;
	पूर्ण
	INIT_LIST_HEAD(&qr->qr_list);
	qr->cmd = cmd;
	qr->state = state;

	spin_lock_bh(&conn->response_queue_lock);
	list_add_tail(&qr->qr_list, &conn->response_queue_list);
	atomic_inc(&cmd->response_queue_count);
	spin_unlock_bh(&conn->response_queue_lock);

	wake_up(&conn->queues_wq);
	वापस 0;
पूर्ण

काष्ठा iscsi_queue_req *iscsit_get_cmd_from_response_queue(काष्ठा iscsi_conn *conn)
अणु
	काष्ठा iscsi_queue_req *qr;

	spin_lock_bh(&conn->response_queue_lock);
	अगर (list_empty(&conn->response_queue_list)) अणु
		spin_unlock_bh(&conn->response_queue_lock);
		वापस शून्य;
	पूर्ण

	qr = list_first_entry(&conn->response_queue_list,
			      काष्ठा iscsi_queue_req, qr_list);

	list_del(&qr->qr_list);
	अगर (qr->cmd)
		atomic_dec(&qr->cmd->response_queue_count);
	spin_unlock_bh(&conn->response_queue_lock);

	वापस qr;
पूर्ण

अटल व्योम iscsit_हटाओ_cmd_from_response_queue(
	काष्ठा iscsi_cmd *cmd,
	काष्ठा iscsi_conn *conn)
अणु
	काष्ठा iscsi_queue_req *qr, *qr_पंचांगp;

	spin_lock_bh(&conn->response_queue_lock);
	अगर (!atomic_पढ़ो(&cmd->response_queue_count)) अणु
		spin_unlock_bh(&conn->response_queue_lock);
		वापस;
	पूर्ण

	list_क्रम_each_entry_safe(qr, qr_पंचांगp, &conn->response_queue_list,
				qr_list) अणु
		अगर (qr->cmd != cmd)
			जारी;

		atomic_dec(&qr->cmd->response_queue_count);
		list_del(&qr->qr_list);
		kmem_cache_मुक्त(lio_qr_cache, qr);
	पूर्ण
	spin_unlock_bh(&conn->response_queue_lock);

	अगर (atomic_पढ़ो(&cmd->response_queue_count)) अणु
		pr_err("ITT: 0x%08x response_queue_count: %d\n",
			cmd->init_task_tag,
			atomic_पढ़ो(&cmd->response_queue_count));
	पूर्ण
पूर्ण

bool iscsit_conn_all_queues_empty(काष्ठा iscsi_conn *conn)
अणु
	bool empty;

	spin_lock_bh(&conn->immed_queue_lock);
	empty = list_empty(&conn->immed_queue_list);
	spin_unlock_bh(&conn->immed_queue_lock);

	अगर (!empty)
		वापस empty;

	spin_lock_bh(&conn->response_queue_lock);
	empty = list_empty(&conn->response_queue_list);
	spin_unlock_bh(&conn->response_queue_lock);

	वापस empty;
पूर्ण

व्योम iscsit_मुक्त_queue_reqs_क्रम_conn(काष्ठा iscsi_conn *conn)
अणु
	काष्ठा iscsi_queue_req *qr, *qr_पंचांगp;

	spin_lock_bh(&conn->immed_queue_lock);
	list_क्रम_each_entry_safe(qr, qr_पंचांगp, &conn->immed_queue_list, qr_list) अणु
		list_del(&qr->qr_list);
		अगर (qr->cmd)
			atomic_dec(&qr->cmd->immed_queue_count);

		kmem_cache_मुक्त(lio_qr_cache, qr);
	पूर्ण
	spin_unlock_bh(&conn->immed_queue_lock);

	spin_lock_bh(&conn->response_queue_lock);
	list_क्रम_each_entry_safe(qr, qr_पंचांगp, &conn->response_queue_list,
			qr_list) अणु
		list_del(&qr->qr_list);
		अगर (qr->cmd)
			atomic_dec(&qr->cmd->response_queue_count);

		kmem_cache_मुक्त(lio_qr_cache, qr);
	पूर्ण
	spin_unlock_bh(&conn->response_queue_lock);
पूर्ण

व्योम iscsit_release_cmd(काष्ठा iscsi_cmd *cmd)
अणु
	काष्ठा iscsi_session *sess;
	काष्ठा se_cmd *se_cmd = &cmd->se_cmd;

	WARN_ON(!list_empty(&cmd->i_conn_node));

	अगर (cmd->conn)
		sess = cmd->conn->sess;
	अन्यथा
		sess = cmd->sess;

	BUG_ON(!sess || !sess->se_sess);

	kमुक्त(cmd->buf_ptr);
	kमुक्त(cmd->pdu_list);
	kमुक्त(cmd->seq_list);
	kमुक्त(cmd->पंचांगr_req);
	kमुक्त(cmd->overflow_buf);
	kमुक्त(cmd->iov_data);
	kमुक्त(cmd->text_in_ptr);

	target_मुक्त_tag(sess->se_sess, se_cmd);
पूर्ण
EXPORT_SYMBOL(iscsit_release_cmd);

व्योम __iscsit_मुक्त_cmd(काष्ठा iscsi_cmd *cmd, bool check_queues)
अणु
	काष्ठा iscsi_conn *conn = cmd->conn;

	WARN_ON(!list_empty(&cmd->i_conn_node));

	अगर (cmd->data_direction == DMA_TO_DEVICE) अणु
		iscsit_stop_dataout_समयr(cmd);
		iscsit_मुक्त_r2ts_from_list(cmd);
	पूर्ण
	अगर (cmd->data_direction == DMA_FROM_DEVICE)
		iscsit_मुक्त_all_datain_reqs(cmd);

	अगर (conn && check_queues) अणु
		iscsit_हटाओ_cmd_from_immediate_queue(cmd, conn);
		iscsit_हटाओ_cmd_from_response_queue(cmd, conn);
	पूर्ण

	अगर (conn && conn->conn_transport->iscsit_unmap_cmd)
		conn->conn_transport->iscsit_unmap_cmd(conn, cmd);
पूर्ण

व्योम iscsit_मुक्त_cmd(काष्ठा iscsi_cmd *cmd, bool shutकरोwn)
अणु
	काष्ठा se_cmd *se_cmd = cmd->se_cmd.se_tfo ? &cmd->se_cmd : शून्य;
	पूर्णांक rc;

	WARN_ON(!list_empty(&cmd->i_conn_node));

	__iscsit_मुक्त_cmd(cmd, shutकरोwn);
	अगर (se_cmd) अणु
		rc = transport_generic_मुक्त_cmd(se_cmd, shutकरोwn);
		अगर (!rc && shutकरोwn && se_cmd->se_sess) अणु
			__iscsit_मुक्त_cmd(cmd, shutकरोwn);
			target_put_sess_cmd(se_cmd);
		पूर्ण
	पूर्ण अन्यथा अणु
		iscsit_release_cmd(cmd);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(iscsit_मुक्त_cmd);

bool iscsit_check_session_usage_count(काष्ठा iscsi_session *sess,
				      bool can_sleep)
अणु
	spin_lock_bh(&sess->session_usage_lock);
	अगर (sess->session_usage_count != 0) अणु
		sess->session_रुकोing_on_uc = 1;
		spin_unlock_bh(&sess->session_usage_lock);
		अगर (!can_sleep)
			वापस true;

		रुको_क्रम_completion(&sess->session_रुकोing_on_uc_comp);
		वापस false;
	पूर्ण
	spin_unlock_bh(&sess->session_usage_lock);

	वापस false;
पूर्ण

व्योम iscsit_dec_session_usage_count(काष्ठा iscsi_session *sess)
अणु
	spin_lock_bh(&sess->session_usage_lock);
	sess->session_usage_count--;

	अगर (!sess->session_usage_count && sess->session_रुकोing_on_uc)
		complete(&sess->session_रुकोing_on_uc_comp);

	spin_unlock_bh(&sess->session_usage_lock);
पूर्ण

व्योम iscsit_inc_session_usage_count(काष्ठा iscsi_session *sess)
अणु
	spin_lock_bh(&sess->session_usage_lock);
	sess->session_usage_count++;
	spin_unlock_bh(&sess->session_usage_lock);
पूर्ण

काष्ठा iscsi_conn *iscsit_get_conn_from_cid(काष्ठा iscsi_session *sess, u16 cid)
अणु
	काष्ठा iscsi_conn *conn;

	spin_lock_bh(&sess->conn_lock);
	list_क्रम_each_entry(conn, &sess->sess_conn_list, conn_list) अणु
		अगर ((conn->cid == cid) &&
		    (conn->conn_state == TARG_CONN_STATE_LOGGED_IN)) अणु
			iscsit_inc_conn_usage_count(conn);
			spin_unlock_bh(&sess->conn_lock);
			वापस conn;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&sess->conn_lock);

	वापस शून्य;
पूर्ण

काष्ठा iscsi_conn *iscsit_get_conn_from_cid_rcfr(काष्ठा iscsi_session *sess, u16 cid)
अणु
	काष्ठा iscsi_conn *conn;

	spin_lock_bh(&sess->conn_lock);
	list_क्रम_each_entry(conn, &sess->sess_conn_list, conn_list) अणु
		अगर (conn->cid == cid) अणु
			iscsit_inc_conn_usage_count(conn);
			spin_lock(&conn->state_lock);
			atomic_set(&conn->connection_रुको_rcfr, 1);
			spin_unlock(&conn->state_lock);
			spin_unlock_bh(&sess->conn_lock);
			वापस conn;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&sess->conn_lock);

	वापस शून्य;
पूर्ण

व्योम iscsit_check_conn_usage_count(काष्ठा iscsi_conn *conn)
अणु
	spin_lock_bh(&conn->conn_usage_lock);
	अगर (conn->conn_usage_count != 0) अणु
		conn->conn_रुकोing_on_uc = 1;
		spin_unlock_bh(&conn->conn_usage_lock);

		रुको_क्रम_completion(&conn->conn_रुकोing_on_uc_comp);
		वापस;
	पूर्ण
	spin_unlock_bh(&conn->conn_usage_lock);
पूर्ण

व्योम iscsit_dec_conn_usage_count(काष्ठा iscsi_conn *conn)
अणु
	spin_lock_bh(&conn->conn_usage_lock);
	conn->conn_usage_count--;

	अगर (!conn->conn_usage_count && conn->conn_रुकोing_on_uc)
		complete(&conn->conn_रुकोing_on_uc_comp);

	spin_unlock_bh(&conn->conn_usage_lock);
पूर्ण

व्योम iscsit_inc_conn_usage_count(काष्ठा iscsi_conn *conn)
अणु
	spin_lock_bh(&conn->conn_usage_lock);
	conn->conn_usage_count++;
	spin_unlock_bh(&conn->conn_usage_lock);
पूर्ण

अटल पूर्णांक iscsit_add_nopin(काष्ठा iscsi_conn *conn, पूर्णांक want_response)
अणु
	u8 state;
	काष्ठा iscsi_cmd *cmd;

	cmd = iscsit_allocate_cmd(conn, TASK_RUNNING);
	अगर (!cmd)
		वापस -1;

	cmd->iscsi_opcode = ISCSI_OP_NOOP_IN;
	state = (want_response) ? ISTATE_SEND_NOPIN_WANT_RESPONSE :
				ISTATE_SEND_NOPIN_NO_RESPONSE;
	cmd->init_task_tag = RESERVED_ITT;
	cmd->targ_xfer_tag = (want_response) ?
			     session_get_next_ttt(conn->sess) : 0xFFFFFFFF;
	spin_lock_bh(&conn->cmd_lock);
	list_add_tail(&cmd->i_conn_node, &conn->conn_cmd_list);
	spin_unlock_bh(&conn->cmd_lock);

	अगर (want_response)
		iscsit_start_nopin_response_समयr(conn);
	iscsit_add_cmd_to_immediate_queue(cmd, conn, state);

	वापस 0;
पूर्ण

व्योम iscsit_handle_nopin_response_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा iscsi_conn *conn = from_समयr(conn, t, nopin_response_समयr);
	काष्ठा iscsi_session *sess = conn->sess;

	iscsit_inc_conn_usage_count(conn);

	spin_lock_bh(&conn->nopin_समयr_lock);
	अगर (conn->nopin_response_समयr_flags & ISCSI_TF_STOP) अणु
		spin_unlock_bh(&conn->nopin_समयr_lock);
		iscsit_dec_conn_usage_count(conn);
		वापस;
	पूर्ण

	pr_err("Did not receive response to NOPIN on CID: %hu, failing"
		" connection for I_T Nexus %s,i,0x%6phN,%s,t,0x%02x\n",
		conn->cid, sess->sess_ops->InitiatorName, sess->isid,
		sess->tpg->tpg_tiqn->tiqn, (u32)sess->tpg->tpgt);
	conn->nopin_response_समयr_flags &= ~ISCSI_TF_RUNNING;
	spin_unlock_bh(&conn->nopin_समयr_lock);

	iscsit_fill_cxn_समयout_err_stats(sess);
	iscsit_cause_connection_reinstatement(conn, 0);
	iscsit_dec_conn_usage_count(conn);
पूर्ण

व्योम iscsit_mod_nopin_response_समयr(काष्ठा iscsi_conn *conn)
अणु
	काष्ठा iscsi_session *sess = conn->sess;
	काष्ठा iscsi_node_attrib *na = iscsit_tpg_get_node_attrib(sess);

	spin_lock_bh(&conn->nopin_समयr_lock);
	अगर (!(conn->nopin_response_समयr_flags & ISCSI_TF_RUNNING)) अणु
		spin_unlock_bh(&conn->nopin_समयr_lock);
		वापस;
	पूर्ण

	mod_समयr(&conn->nopin_response_समयr,
		(get_jअगरfies_64() + na->nopin_response_समयout * HZ));
	spin_unlock_bh(&conn->nopin_समयr_lock);
पूर्ण

व्योम iscsit_start_nopin_response_समयr(काष्ठा iscsi_conn *conn)
अणु
	काष्ठा iscsi_session *sess = conn->sess;
	काष्ठा iscsi_node_attrib *na = iscsit_tpg_get_node_attrib(sess);

	spin_lock_bh(&conn->nopin_समयr_lock);
	अगर (conn->nopin_response_समयr_flags & ISCSI_TF_RUNNING) अणु
		spin_unlock_bh(&conn->nopin_समयr_lock);
		वापस;
	पूर्ण

	conn->nopin_response_समयr_flags &= ~ISCSI_TF_STOP;
	conn->nopin_response_समयr_flags |= ISCSI_TF_RUNNING;
	mod_समयr(&conn->nopin_response_समयr,
		  jअगरfies + na->nopin_response_समयout * HZ);

	pr_debug("Started NOPIN Response Timer on CID: %d to %u"
		" seconds\n", conn->cid, na->nopin_response_समयout);
	spin_unlock_bh(&conn->nopin_समयr_lock);
पूर्ण

व्योम iscsit_stop_nopin_response_समयr(काष्ठा iscsi_conn *conn)
अणु
	spin_lock_bh(&conn->nopin_समयr_lock);
	अगर (!(conn->nopin_response_समयr_flags & ISCSI_TF_RUNNING)) अणु
		spin_unlock_bh(&conn->nopin_समयr_lock);
		वापस;
	पूर्ण
	conn->nopin_response_समयr_flags |= ISCSI_TF_STOP;
	spin_unlock_bh(&conn->nopin_समयr_lock);

	del_समयr_sync(&conn->nopin_response_समयr);

	spin_lock_bh(&conn->nopin_समयr_lock);
	conn->nopin_response_समयr_flags &= ~ISCSI_TF_RUNNING;
	spin_unlock_bh(&conn->nopin_समयr_lock);
पूर्ण

व्योम iscsit_handle_nopin_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा iscsi_conn *conn = from_समयr(conn, t, nopin_समयr);

	iscsit_inc_conn_usage_count(conn);

	spin_lock_bh(&conn->nopin_समयr_lock);
	अगर (conn->nopin_समयr_flags & ISCSI_TF_STOP) अणु
		spin_unlock_bh(&conn->nopin_समयr_lock);
		iscsit_dec_conn_usage_count(conn);
		वापस;
	पूर्ण
	conn->nopin_समयr_flags &= ~ISCSI_TF_RUNNING;
	spin_unlock_bh(&conn->nopin_समयr_lock);

	iscsit_add_nopin(conn, 1);
	iscsit_dec_conn_usage_count(conn);
पूर्ण

व्योम __iscsit_start_nopin_समयr(काष्ठा iscsi_conn *conn)
अणु
	काष्ठा iscsi_session *sess = conn->sess;
	काष्ठा iscsi_node_attrib *na = iscsit_tpg_get_node_attrib(sess);

	lockdep_निश्चित_held(&conn->nopin_समयr_lock);

	/*
	* NOPIN समयout is disabled.
	 */
	अगर (!na->nopin_समयout)
		वापस;

	अगर (conn->nopin_समयr_flags & ISCSI_TF_RUNNING)
		वापस;

	conn->nopin_समयr_flags &= ~ISCSI_TF_STOP;
	conn->nopin_समयr_flags |= ISCSI_TF_RUNNING;
	mod_समयr(&conn->nopin_समयr, jअगरfies + na->nopin_समयout * HZ);

	pr_debug("Started NOPIN Timer on CID: %d at %u second"
		" interval\n", conn->cid, na->nopin_समयout);
पूर्ण

व्योम iscsit_start_nopin_समयr(काष्ठा iscsi_conn *conn)
अणु
	spin_lock_bh(&conn->nopin_समयr_lock);
	__iscsit_start_nopin_समयr(conn);
	spin_unlock_bh(&conn->nopin_समयr_lock);
पूर्ण

व्योम iscsit_stop_nopin_समयr(काष्ठा iscsi_conn *conn)
अणु
	spin_lock_bh(&conn->nopin_समयr_lock);
	अगर (!(conn->nopin_समयr_flags & ISCSI_TF_RUNNING)) अणु
		spin_unlock_bh(&conn->nopin_समयr_lock);
		वापस;
	पूर्ण
	conn->nopin_समयr_flags |= ISCSI_TF_STOP;
	spin_unlock_bh(&conn->nopin_समयr_lock);

	del_समयr_sync(&conn->nopin_समयr);

	spin_lock_bh(&conn->nopin_समयr_lock);
	conn->nopin_समयr_flags &= ~ISCSI_TF_RUNNING;
	spin_unlock_bh(&conn->nopin_समयr_lock);
पूर्ण

पूर्णांक iscsit_send_tx_data(
	काष्ठा iscsi_cmd *cmd,
	काष्ठा iscsi_conn *conn,
	पूर्णांक use_misc)
अणु
	पूर्णांक tx_sent, tx_size;
	u32 iov_count;
	काष्ठा kvec *iov;

send_data:
	tx_size = cmd->tx_size;

	अगर (!use_misc) अणु
		iov = &cmd->iov_data[0];
		iov_count = cmd->iov_data_count;
	पूर्ण अन्यथा अणु
		iov = &cmd->iov_misc[0];
		iov_count = cmd->iov_misc_count;
	पूर्ण

	tx_sent = tx_data(conn, &iov[0], iov_count, tx_size);
	अगर (tx_size != tx_sent) अणु
		अगर (tx_sent == -EAGAIN) अणु
			pr_err("tx_data() returned -EAGAIN\n");
			जाओ send_data;
		पूर्ण अन्यथा
			वापस -1;
	पूर्ण
	cmd->tx_size = 0;

	वापस 0;
पूर्ण

पूर्णांक iscsit_fe_sendpage_sg(
	काष्ठा iscsi_cmd *cmd,
	काष्ठा iscsi_conn *conn)
अणु
	काष्ठा scatterlist *sg = cmd->first_data_sg;
	काष्ठा kvec iov;
	u32 tx_hdr_size, data_len;
	u32 offset = cmd->first_data_sg_off;
	पूर्णांक tx_sent, iov_off;

send_hdr:
	tx_hdr_size = ISCSI_HDR_LEN;
	अगर (conn->conn_ops->HeaderDigest)
		tx_hdr_size += ISCSI_CRC_LEN;

	iov.iov_base = cmd->pdu;
	iov.iov_len = tx_hdr_size;

	tx_sent = tx_data(conn, &iov, 1, tx_hdr_size);
	अगर (tx_hdr_size != tx_sent) अणु
		अगर (tx_sent == -EAGAIN) अणु
			pr_err("tx_data() returned -EAGAIN\n");
			जाओ send_hdr;
		पूर्ण
		वापस -1;
	पूर्ण

	data_len = cmd->tx_size - tx_hdr_size - cmd->padding;
	/*
	 * Set iov_off used by padding and data digest tx_data() calls below
	 * in order to determine proper offset पूर्णांकo cmd->iov_data[]
	 */
	अगर (conn->conn_ops->DataDigest) अणु
		data_len -= ISCSI_CRC_LEN;
		अगर (cmd->padding)
			iov_off = (cmd->iov_data_count - 2);
		अन्यथा
			iov_off = (cmd->iov_data_count - 1);
	पूर्ण अन्यथा अणु
		iov_off = (cmd->iov_data_count - 1);
	पूर्ण
	/*
	 * Perक्रमm sendpage() क्रम each page in the scatterlist
	 */
	जबतक (data_len) अणु
		u32 space = (sg->length - offset);
		u32 sub_len = min_t(u32, data_len, space);
send_pg:
		tx_sent = conn->sock->ops->sendpage(conn->sock,
					sg_page(sg), sg->offset + offset, sub_len, 0);
		अगर (tx_sent != sub_len) अणु
			अगर (tx_sent == -EAGAIN) अणु
				pr_err("tcp_sendpage() returned"
						" -EAGAIN\n");
				जाओ send_pg;
			पूर्ण

			pr_err("tcp_sendpage() failure: %d\n",
					tx_sent);
			वापस -1;
		पूर्ण

		data_len -= sub_len;
		offset = 0;
		sg = sg_next(sg);
	पूर्ण

send_padding:
	अगर (cmd->padding) अणु
		काष्ठा kvec *iov_p = &cmd->iov_data[iov_off++];

		tx_sent = tx_data(conn, iov_p, 1, cmd->padding);
		अगर (cmd->padding != tx_sent) अणु
			अगर (tx_sent == -EAGAIN) अणु
				pr_err("tx_data() returned -EAGAIN\n");
				जाओ send_padding;
			पूर्ण
			वापस -1;
		पूर्ण
	पूर्ण

send_datacrc:
	अगर (conn->conn_ops->DataDigest) अणु
		काष्ठा kvec *iov_d = &cmd->iov_data[iov_off];

		tx_sent = tx_data(conn, iov_d, 1, ISCSI_CRC_LEN);
		अगर (ISCSI_CRC_LEN != tx_sent) अणु
			अगर (tx_sent == -EAGAIN) अणु
				pr_err("tx_data() returned -EAGAIN\n");
				जाओ send_datacrc;
			पूर्ण
			वापस -1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 *      This function is used क्रम मुख्यly sending a ISCSI_TARG_LOGIN_RSP PDU
 *      back to the Initiator when an expection condition occurs with the
 *      errors set in status_class and status_detail.
 *
 *      Parameters:     iSCSI Connection, Status Class, Status Detail.
 *      Returns:        0 on success, -1 on error.
 */
पूर्णांक iscsit_tx_login_rsp(काष्ठा iscsi_conn *conn, u8 status_class, u8 status_detail)
अणु
	काष्ठा iscsi_login_rsp *hdr;
	काष्ठा iscsi_login *login = conn->conn_login;

	login->login_failed = 1;
	iscsit_collect_login_stats(conn, status_class, status_detail);

	स_रखो(&login->rsp[0], 0, ISCSI_HDR_LEN);

	hdr	= (काष्ठा iscsi_login_rsp *)&login->rsp[0];
	hdr->opcode		= ISCSI_OP_LOGIN_RSP;
	hdr->status_class	= status_class;
	hdr->status_detail	= status_detail;
	hdr->itt		= conn->login_itt;

	वापस conn->conn_transport->iscsit_put_login_tx(conn, login, 0);
पूर्ण

व्योम iscsit_prपूर्णांक_session_params(काष्ठा iscsi_session *sess)
अणु
	काष्ठा iscsi_conn *conn;

	pr_debug("-----------------------------[Session Params for"
		" SID: %u]-----------------------------\n", sess->sid);
	spin_lock_bh(&sess->conn_lock);
	list_क्रम_each_entry(conn, &sess->sess_conn_list, conn_list)
		iscsi_dump_conn_ops(conn->conn_ops);
	spin_unlock_bh(&sess->conn_lock);

	iscsi_dump_sess_ops(sess->sess_ops);
पूर्ण

पूर्णांक rx_data(
	काष्ठा iscsi_conn *conn,
	काष्ठा kvec *iov,
	पूर्णांक iov_count,
	पूर्णांक data)
अणु
	पूर्णांक rx_loop = 0, total_rx = 0;
	काष्ठा msghdr msg;

	अगर (!conn || !conn->sock || !conn->conn_ops)
		वापस -1;

	स_रखो(&msg, 0, माप(काष्ठा msghdr));
	iov_iter_kvec(&msg.msg_iter, READ, iov, iov_count, data);

	जबतक (msg_data_left(&msg)) अणु
		rx_loop = sock_recvmsg(conn->sock, &msg, MSG_WAITALL);
		अगर (rx_loop <= 0) अणु
			pr_debug("rx_loop: %d total_rx: %d\n",
				rx_loop, total_rx);
			वापस rx_loop;
		पूर्ण
		total_rx += rx_loop;
		pr_debug("rx_loop: %d, total_rx: %d, data: %d\n",
				rx_loop, total_rx, data);
	पूर्ण

	वापस total_rx;
पूर्ण

पूर्णांक tx_data(
	काष्ठा iscsi_conn *conn,
	काष्ठा kvec *iov,
	पूर्णांक iov_count,
	पूर्णांक data)
अणु
	काष्ठा msghdr msg;
	पूर्णांक total_tx = 0;

	अगर (!conn || !conn->sock || !conn->conn_ops)
		वापस -1;

	अगर (data <= 0) अणु
		pr_err("Data length is: %d\n", data);
		वापस -1;
	पूर्ण

	स_रखो(&msg, 0, माप(काष्ठा msghdr));

	iov_iter_kvec(&msg.msg_iter, WRITE, iov, iov_count, data);

	जबतक (msg_data_left(&msg)) अणु
		पूर्णांक tx_loop = sock_sendmsg(conn->sock, &msg);
		अगर (tx_loop <= 0) अणु
			pr_debug("tx_loop: %d total_tx %d\n",
				tx_loop, total_tx);
			वापस tx_loop;
		पूर्ण
		total_tx += tx_loop;
		pr_debug("tx_loop: %d, total_tx: %d, data: %d\n",
					tx_loop, total_tx, data);
	पूर्ण

	वापस total_tx;
पूर्ण

व्योम iscsit_collect_login_stats(
	काष्ठा iscsi_conn *conn,
	u8 status_class,
	u8 status_detail)
अणु
	काष्ठा iscsi_param *पूर्णांकrname = शून्य;
	काष्ठा iscsi_tiqn *tiqn;
	काष्ठा iscsi_login_stats *ls;

	tiqn = iscsit_snmp_get_tiqn(conn);
	अगर (!tiqn)
		वापस;

	ls = &tiqn->login_stats;

	spin_lock(&ls->lock);
	अगर (status_class == ISCSI_STATUS_CLS_SUCCESS)
		ls->accepts++;
	अन्यथा अगर (status_class == ISCSI_STATUS_CLS_REसूचीECT) अणु
		ls->redirects++;
		ls->last_fail_type = ISCSI_LOGIN_FAIL_REसूचीECT;
	पूर्ण अन्यथा अगर ((status_class == ISCSI_STATUS_CLS_INITIATOR_ERR)  &&
		 (status_detail == ISCSI_LOGIN_STATUS_AUTH_FAILED)) अणु
		ls->authenticate_fails++;
		ls->last_fail_type =  ISCSI_LOGIN_FAIL_AUTHENTICATE;
	पूर्ण अन्यथा अगर ((status_class == ISCSI_STATUS_CLS_INITIATOR_ERR)  &&
		 (status_detail == ISCSI_LOGIN_STATUS_TGT_FORBIDDEN)) अणु
		ls->authorize_fails++;
		ls->last_fail_type = ISCSI_LOGIN_FAIL_AUTHORIZE;
	पूर्ण अन्यथा अगर ((status_class == ISCSI_STATUS_CLS_INITIATOR_ERR) &&
		 (status_detail == ISCSI_LOGIN_STATUS_INIT_ERR)) अणु
		ls->negotiate_fails++;
		ls->last_fail_type = ISCSI_LOGIN_FAIL_NEGOTIATE;
	पूर्ण अन्यथा अणु
		ls->other_fails++;
		ls->last_fail_type = ISCSI_LOGIN_FAIL_OTHER;
	पूर्ण

	/* Save initiator name, ip address and समय, अगर it is a failed login */
	अगर (status_class != ISCSI_STATUS_CLS_SUCCESS) अणु
		अगर (conn->param_list)
			पूर्णांकrname = iscsi_find_param_from_key(INITIATORNAME,
							     conn->param_list);
		strlcpy(ls->last_पूर्णांकr_fail_name,
		       (पूर्णांकrname ? पूर्णांकrname->value : "Unknown"),
		       माप(ls->last_पूर्णांकr_fail_name));

		ls->last_पूर्णांकr_fail_ip_family = conn->login_family;

		ls->last_पूर्णांकr_fail_sockaddr = conn->login_sockaddr;
		ls->last_fail_समय = get_jअगरfies_64();
	पूर्ण

	spin_unlock(&ls->lock);
पूर्ण

काष्ठा iscsi_tiqn *iscsit_snmp_get_tiqn(काष्ठा iscsi_conn *conn)
अणु
	काष्ठा iscsi_portal_group *tpg;

	अगर (!conn)
		वापस शून्य;

	tpg = conn->tpg;
	अगर (!tpg)
		वापस शून्य;

	अगर (!tpg->tpg_tiqn)
		वापस शून्य;

	वापस tpg->tpg_tiqn;
पूर्ण

व्योम iscsit_fill_cxn_समयout_err_stats(काष्ठा iscsi_session *sess)
अणु
	काष्ठा iscsi_portal_group *tpg = sess->tpg;
	काष्ठा iscsi_tiqn *tiqn = tpg->tpg_tiqn;

	अगर (!tiqn)
		वापस;

	spin_lock_bh(&tiqn->sess_err_stats.lock);
	strlcpy(tiqn->sess_err_stats.last_sess_fail_rem_name,
			sess->sess_ops->InitiatorName,
			माप(tiqn->sess_err_stats.last_sess_fail_rem_name));
	tiqn->sess_err_stats.last_sess_failure_type =
			ISCSI_SESS_ERR_CXN_TIMEOUT;
	tiqn->sess_err_stats.cxn_समयout_errors++;
	atomic_दीर्घ_inc(&sess->conn_समयout_errors);
	spin_unlock_bh(&tiqn->sess_err_stats.lock);
पूर्ण
