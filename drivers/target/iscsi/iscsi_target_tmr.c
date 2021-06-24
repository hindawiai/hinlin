<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*******************************************************************************
 * This file contains the iSCSI Target specअगरic Task Management functions.
 *
 * (c) Copyright 2007-2013 Datera, Inc.
 *
 * Author: Nicholas A. Bellinger <nab@linux-iscsi.org>
 *
 ******************************************************************************/

#समावेश <यंत्र/unaligned.h>
#समावेश <scsi/scsi_proto.h>
#समावेश <scsi/iscsi_proto.h>
#समावेश <target/target_core_base.h>
#समावेश <target/target_core_fabric.h>
#समावेश <target/iscsi/iscsi_transport.h>

#समावेश <target/iscsi/iscsi_target_core.h>
#समावेश "iscsi_target_seq_pdu_list.h"
#समावेश "iscsi_target_datain_values.h"
#समावेश "iscsi_target_device.h"
#समावेश "iscsi_target_erl0.h"
#समावेश "iscsi_target_erl1.h"
#समावेश "iscsi_target_erl2.h"
#समावेश "iscsi_target_tmr.h"
#समावेश "iscsi_target_tpg.h"
#समावेश "iscsi_target_util.h"
#समावेश "iscsi_target.h"

u8 iscsit_पंचांगr_पात_task(
	काष्ठा iscsi_cmd *cmd,
	अचिन्हित अक्षर *buf)
अणु
	काष्ठा iscsi_cmd *ref_cmd;
	काष्ठा iscsi_conn *conn = cmd->conn;
	काष्ठा iscsi_पंचांगr_req *पंचांगr_req = cmd->पंचांगr_req;
	काष्ठा se_पंचांगr_req *se_पंचांगr = cmd->se_cmd.se_पंचांगr_req;
	काष्ठा iscsi_पंचांग *hdr = (काष्ठा iscsi_पंचांग *) buf;

	ref_cmd = iscsit_find_cmd_from_itt(conn, hdr->rtt);
	अगर (!ref_cmd) अणु
		pr_err("Unable to locate RefTaskTag: 0x%08x on CID:"
			" %hu.\n", hdr->rtt, conn->cid);
		वापस (iscsi_sna_gte(be32_to_cpu(hdr->refcmdsn), conn->sess->exp_cmd_sn) &&
			iscsi_sna_lte(be32_to_cpu(hdr->refcmdsn), (u32) atomic_पढ़ो(&conn->sess->max_cmd_sn))) ?
			ISCSI_TMF_RSP_COMPLETE : ISCSI_TMF_RSP_NO_TASK;
	पूर्ण
	अगर (ref_cmd->cmd_sn != be32_to_cpu(hdr->refcmdsn)) अणु
		pr_err("RefCmdSN 0x%08x does not equal"
			" task's CmdSN 0x%08x. Rejecting ABORT_TASK.\n",
			hdr->refcmdsn, ref_cmd->cmd_sn);
		वापस ISCSI_TMF_RSP_REJECTED;
	पूर्ण

	se_पंचांगr->ref_task_tag		= (__क्रमce u32)hdr->rtt;
	पंचांगr_req->ref_cmd		= ref_cmd;
	पंचांगr_req->exp_data_sn		= be32_to_cpu(hdr->exp_datasn);

	वापस ISCSI_TMF_RSP_COMPLETE;
पूर्ण

/*
 *	Called from iscsit_handle_task_mgt_cmd().
 */
पूर्णांक iscsit_पंचांगr_task_warm_reset(
	काष्ठा iscsi_conn *conn,
	काष्ठा iscsi_पंचांगr_req *पंचांगr_req,
	अचिन्हित अक्षर *buf)
अणु
	काष्ठा iscsi_session *sess = conn->sess;
	काष्ठा iscsi_node_attrib *na = iscsit_tpg_get_node_attrib(sess);

	अगर (!na->पंचांगr_warm_reset) अणु
		pr_err("TMR Opcode TARGET_WARM_RESET authorization"
			" failed for Initiator Node: %s\n",
			sess->se_sess->se_node_acl->initiatorname);
		वापस -1;
	पूर्ण
	/*
	 * Do the real work in transport_generic_करो_पंचांगr().
	 */
	वापस 0;
पूर्ण

पूर्णांक iscsit_पंचांगr_task_cold_reset(
	काष्ठा iscsi_conn *conn,
	काष्ठा iscsi_पंचांगr_req *पंचांगr_req,
	अचिन्हित अक्षर *buf)
अणु
	काष्ठा iscsi_session *sess = conn->sess;
	काष्ठा iscsi_node_attrib *na = iscsit_tpg_get_node_attrib(sess);

	अगर (!na->पंचांगr_cold_reset) अणु
		pr_err("TMR Opcode TARGET_COLD_RESET authorization"
			" failed for Initiator Node: %s\n",
			sess->se_sess->se_node_acl->initiatorname);
		वापस -1;
	पूर्ण
	/*
	 * Do the real work in transport_generic_करो_पंचांगr().
	 */
	वापस 0;
पूर्ण

u8 iscsit_पंचांगr_task_reassign(
	काष्ठा iscsi_cmd *cmd,
	अचिन्हित अक्षर *buf)
अणु
	काष्ठा iscsi_cmd *ref_cmd = शून्य;
	काष्ठा iscsi_conn *conn = cmd->conn;
	काष्ठा iscsi_conn_recovery *cr = शून्य;
	काष्ठा iscsi_पंचांगr_req *पंचांगr_req = cmd->पंचांगr_req;
	काष्ठा se_पंचांगr_req *se_पंचांगr = cmd->se_cmd.se_पंचांगr_req;
	काष्ठा iscsi_पंचांग *hdr = (काष्ठा iscsi_पंचांग *) buf;
	u64 ret, ref_lun;

	pr_debug("Got TASK_REASSIGN TMR ITT: 0x%08x,"
		" RefTaskTag: 0x%08x, ExpDataSN: 0x%08x, CID: %hu\n",
		hdr->itt, hdr->rtt, hdr->exp_datasn, conn->cid);

	अगर (conn->sess->sess_ops->ErrorRecoveryLevel != 2) अणु
		pr_err("TMR TASK_REASSIGN not supported in ERL<2,"
				" ignoring request.\n");
		वापस ISCSI_TMF_RSP_NOT_SUPPORTED;
	पूर्ण

	ret = iscsit_find_cmd_क्रम_recovery(conn->sess, &ref_cmd, &cr, hdr->rtt);
	अगर (ret == -2) अणु
		pr_err("Command ITT: 0x%08x is still alligent to CID:"
			" %hu\n", ref_cmd->init_task_tag, cr->cid);
		वापस ISCSI_TMF_RSP_TASK_ALLEGIANT;
	पूर्ण अन्यथा अगर (ret == -1) अणु
		pr_err("Unable to locate RefTaskTag: 0x%08x in"
			" connection recovery command list.\n", hdr->rtt);
		वापस ISCSI_TMF_RSP_NO_TASK;
	पूर्ण
	/*
	 * Temporary check to prevent connection recovery क्रम
	 * connections with a dअगरfering Max*DataSegmentLength.
	 */
	अगर (cr->maxrecvdatasegmentlength !=
	    conn->conn_ops->MaxRecvDataSegmentLength) अणु
		pr_err("Unable to perform connection recovery for"
			" differing MaxRecvDataSegmentLength, rejecting"
			" TMR TASK_REASSIGN.\n");
		वापस ISCSI_TMF_RSP_REJECTED;
	पूर्ण
	अगर (cr->maxxmitdatasegmentlength !=
	    conn->conn_ops->MaxXmitDataSegmentLength) अणु
		pr_err("Unable to perform connection recovery for"
			" differing MaxXmitDataSegmentLength, rejecting"
			" TMR TASK_REASSIGN.\n");
		वापस ISCSI_TMF_RSP_REJECTED;
	पूर्ण

	ref_lun = scsilun_to_पूर्णांक(&hdr->lun);
	अगर (ref_lun != ref_cmd->se_cmd.orig_fe_lun) अणु
		pr_err("Unable to perform connection recovery for"
			" differing ref_lun: %llu ref_cmd orig_fe_lun: %llu\n",
			ref_lun, ref_cmd->se_cmd.orig_fe_lun);
		वापस ISCSI_TMF_RSP_REJECTED;
	पूर्ण

	se_पंचांगr->ref_task_tag		= (__क्रमce u32)hdr->rtt;
	पंचांगr_req->ref_cmd		= ref_cmd;
	पंचांगr_req->exp_data_sn		= be32_to_cpu(hdr->exp_datasn);
	पंचांगr_req->conn_recovery		= cr;
	पंचांगr_req->task_reassign		= 1;
	/*
	 * Command can now be reasचिन्हित to a new connection.
	 * The task management response must be sent beक्रमe the
	 * reassignment actually happens.  See iscsi_पंचांगr_post_handler().
	 */
	वापस ISCSI_TMF_RSP_COMPLETE;
पूर्ण

अटल व्योम iscsit_task_reassign_हटाओ_cmd(
	काष्ठा iscsi_cmd *cmd,
	काष्ठा iscsi_conn_recovery *cr,
	काष्ठा iscsi_session *sess)
अणु
	पूर्णांक ret;

	spin_lock(&cr->conn_recovery_cmd_lock);
	ret = iscsit_हटाओ_cmd_from_connection_recovery(cmd, sess);
	spin_unlock(&cr->conn_recovery_cmd_lock);
	अगर (!ret) अणु
		pr_debug("iSCSI connection recovery successful for CID:"
			" %hu on SID: %u\n", cr->cid, sess->sid);
		iscsit_हटाओ_active_connection_recovery_entry(cr, sess);
	पूर्ण
पूर्ण

अटल पूर्णांक iscsit_task_reassign_complete_nop_out(
	काष्ठा iscsi_पंचांगr_req *पंचांगr_req,
	काष्ठा iscsi_conn *conn)
अणु
	काष्ठा iscsi_cmd *cmd = पंचांगr_req->ref_cmd;
	काष्ठा iscsi_conn_recovery *cr;

	अगर (!cmd->cr) अणु
		pr_err("struct iscsi_conn_recovery pointer for ITT: 0x%08x"
			" is NULL!\n", cmd->init_task_tag);
		वापस -1;
	पूर्ण
	cr = cmd->cr;

	/*
	 * Reset the StatSN so a new one क्रम this commands new connection
	 * will be asचिन्हित.
	 * Reset the ExpStatSN as well so we may receive Status SNACKs.
	 */
	cmd->stat_sn = cmd->exp_stat_sn = 0;

	iscsit_task_reassign_हटाओ_cmd(cmd, cr, conn->sess);

	spin_lock_bh(&conn->cmd_lock);
	list_add_tail(&cmd->i_conn_node, &conn->conn_cmd_list);
	spin_unlock_bh(&conn->cmd_lock);

	cmd->i_state = ISTATE_SEND_NOPIN;
	iscsit_add_cmd_to_response_queue(cmd, conn, cmd->i_state);
	वापस 0;
पूर्ण

अटल पूर्णांक iscsit_task_reassign_complete_ग_लिखो(
	काष्ठा iscsi_cmd *cmd,
	काष्ठा iscsi_पंचांगr_req *पंचांगr_req)
अणु
	पूर्णांक no_build_r2ts = 0;
	u32 length = 0, offset = 0;
	काष्ठा iscsi_conn *conn = cmd->conn;
	काष्ठा se_cmd *se_cmd = &cmd->se_cmd;
	/*
	 * The Initiator must not send a R2T SNACK with a Begrun less than
	 * the TMR TASK_REASSIGN's ExpDataSN.
	 */
	अगर (!पंचांगr_req->exp_data_sn) अणु
		cmd->cmd_flags &= ~ICF_GOT_DATACK_SNACK;
		cmd->acked_data_sn = 0;
	पूर्ण अन्यथा अणु
		cmd->cmd_flags |= ICF_GOT_DATACK_SNACK;
		cmd->acked_data_sn = (पंचांगr_req->exp_data_sn - 1);
	पूर्ण

	/*
	 * The TMR TASK_REASSIGN's ExpDataSN contains the next R2TSN the
	 * Initiator is expecting.  The Target controls all WRITE operations
	 * so अगर we have received all DataOUT we can safety ignore Initiator.
	 */
	अगर (cmd->cmd_flags & ICF_GOT_LAST_DATAOUT) अणु
		अगर (!(cmd->se_cmd.transport_state & CMD_T_SENT)) अणु
			pr_debug("WRITE ITT: 0x%08x: t_state: %d"
				" never sent to transport\n",
				cmd->init_task_tag, cmd->se_cmd.t_state);
			target_execute_cmd(se_cmd);
			वापस 0;
		पूर्ण

		cmd->i_state = ISTATE_SEND_STATUS;
		iscsit_add_cmd_to_response_queue(cmd, conn, cmd->i_state);
		वापस 0;
	पूर्ण

	/*
	 * Special हाल to deal with DataSequenceInOrder=No and Non-Immeidate
	 * Unsolicited DataOut.
	 */
	अगर (cmd->unsolicited_data) अणु
		cmd->unsolicited_data = 0;

		offset = cmd->next_burst_len = cmd->ग_लिखो_data_करोne;

		अगर ((conn->sess->sess_ops->FirstBurstLength - offset) >=
		     cmd->se_cmd.data_length) अणु
			no_build_r2ts = 1;
			length = (cmd->se_cmd.data_length - offset);
		पूर्ण अन्यथा
			length = (conn->sess->sess_ops->FirstBurstLength - offset);

		spin_lock_bh(&cmd->r2t_lock);
		अगर (iscsit_add_r2t_to_list(cmd, offset, length, 0, 0) < 0) अणु
			spin_unlock_bh(&cmd->r2t_lock);
			वापस -1;
		पूर्ण
		cmd->outstanding_r2ts++;
		spin_unlock_bh(&cmd->r2t_lock);

		अगर (no_build_r2ts)
			वापस 0;
	पूर्ण
	/*
	 * iscsit_build_r2ts_क्रम_cmd() can handle the rest from here.
	 */
	वापस conn->conn_transport->iscsit_get_dataout(conn, cmd, true);
पूर्ण

अटल पूर्णांक iscsit_task_reassign_complete_पढ़ो(
	काष्ठा iscsi_cmd *cmd,
	काष्ठा iscsi_पंचांगr_req *पंचांगr_req)
अणु
	काष्ठा iscsi_conn *conn = cmd->conn;
	काष्ठा iscsi_datain_req *dr;
	काष्ठा se_cmd *se_cmd = &cmd->se_cmd;
	/*
	 * The Initiator must not send a Data SNACK with a BegRun less than
	 * the TMR TASK_REASSIGN's ExpDataSN.
	 */
	अगर (!पंचांगr_req->exp_data_sn) अणु
		cmd->cmd_flags &= ~ICF_GOT_DATACK_SNACK;
		cmd->acked_data_sn = 0;
	पूर्ण अन्यथा अणु
		cmd->cmd_flags |= ICF_GOT_DATACK_SNACK;
		cmd->acked_data_sn = (पंचांगr_req->exp_data_sn - 1);
	पूर्ण

	अगर (!(cmd->se_cmd.transport_state & CMD_T_SENT)) अणु
		pr_debug("READ ITT: 0x%08x: t_state: %d never sent to"
			" transport\n", cmd->init_task_tag,
			cmd->se_cmd.t_state);
		transport_handle_cdb_direct(se_cmd);
		वापस 0;
	पूर्ण

	अगर (!(se_cmd->transport_state & CMD_T_COMPLETE)) अणु
		pr_err("READ ITT: 0x%08x: t_state: %d, never returned"
			" from transport\n", cmd->init_task_tag,
			cmd->se_cmd.t_state);
		वापस -1;
	पूर्ण

	dr = iscsit_allocate_datain_req();
	अगर (!dr)
		वापस -1;
	/*
	 * The TMR TASK_REASSIGN's ExpDataSN contains the next DataSN the
	 * Initiator is expecting.
	 */
	dr->data_sn = dr->begrun = पंचांगr_req->exp_data_sn;
	dr->runlength = 0;
	dr->generate_recovery_values = 1;
	dr->recovery = DATAIN_CONNECTION_RECOVERY;

	iscsit_attach_datain_req(cmd, dr);

	cmd->i_state = ISTATE_SEND_DATAIN;
	iscsit_add_cmd_to_response_queue(cmd, conn, cmd->i_state);
	वापस 0;
पूर्ण

अटल पूर्णांक iscsit_task_reassign_complete_none(
	काष्ठा iscsi_cmd *cmd,
	काष्ठा iscsi_पंचांगr_req *पंचांगr_req)
अणु
	काष्ठा iscsi_conn *conn = cmd->conn;

	cmd->i_state = ISTATE_SEND_STATUS;
	iscsit_add_cmd_to_response_queue(cmd, conn, cmd->i_state);
	वापस 0;
पूर्ण

अटल पूर्णांक iscsit_task_reassign_complete_scsi_cmnd(
	काष्ठा iscsi_पंचांगr_req *पंचांगr_req,
	काष्ठा iscsi_conn *conn)
अणु
	काष्ठा iscsi_cmd *cmd = पंचांगr_req->ref_cmd;
	काष्ठा iscsi_conn_recovery *cr;

	अगर (!cmd->cr) अणु
		pr_err("struct iscsi_conn_recovery pointer for ITT: 0x%08x"
			" is NULL!\n", cmd->init_task_tag);
		वापस -1;
	पूर्ण
	cr = cmd->cr;

	/*
	 * Reset the StatSN so a new one क्रम this commands new connection
	 * will be asचिन्हित.
	 * Reset the ExpStatSN as well so we may receive Status SNACKs.
	 */
	cmd->stat_sn = cmd->exp_stat_sn = 0;

	iscsit_task_reassign_हटाओ_cmd(cmd, cr, conn->sess);

	spin_lock_bh(&conn->cmd_lock);
	list_add_tail(&cmd->i_conn_node, &conn->conn_cmd_list);
	spin_unlock_bh(&conn->cmd_lock);

	अगर (cmd->se_cmd.se_cmd_flags & SCF_SENT_CHECK_CONDITION) अणु
		cmd->i_state = ISTATE_SEND_STATUS;
		iscsit_add_cmd_to_response_queue(cmd, conn, cmd->i_state);
		वापस 0;
	पूर्ण

	चयन (cmd->data_direction) अणु
	हाल DMA_TO_DEVICE:
		वापस iscsit_task_reassign_complete_ग_लिखो(cmd, पंचांगr_req);
	हाल DMA_FROM_DEVICE:
		वापस iscsit_task_reassign_complete_पढ़ो(cmd, पंचांगr_req);
	हाल DMA_NONE:
		वापस iscsit_task_reassign_complete_none(cmd, पंचांगr_req);
	शेष:
		pr_err("Unknown cmd->data_direction: 0x%02x\n",
				cmd->data_direction);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक iscsit_task_reassign_complete(
	काष्ठा iscsi_पंचांगr_req *पंचांगr_req,
	काष्ठा iscsi_conn *conn)
अणु
	काष्ठा iscsi_cmd *cmd;
	पूर्णांक ret = 0;

	अगर (!पंचांगr_req->ref_cmd) अणु
		pr_err("TMR Request is missing a RefCmd struct iscsi_cmd.\n");
		वापस -1;
	पूर्ण
	cmd = पंचांगr_req->ref_cmd;

	cmd->conn = conn;

	चयन (cmd->iscsi_opcode) अणु
	हाल ISCSI_OP_NOOP_OUT:
		ret = iscsit_task_reassign_complete_nop_out(पंचांगr_req, conn);
		अवरोध;
	हाल ISCSI_OP_SCSI_CMD:
		ret = iscsit_task_reassign_complete_scsi_cmnd(पंचांगr_req, conn);
		अवरोध;
	शेष:
		 pr_err("Illegal iSCSI Opcode 0x%02x during"
			" command reallegiance\n", cmd->iscsi_opcode);
		वापस -1;
	पूर्ण

	अगर (ret != 0)
		वापस ret;

	pr_debug("Completed connection reallegiance for Opcode: 0x%02x,"
		" ITT: 0x%08x to CID: %hu.\n", cmd->iscsi_opcode,
			cmd->init_task_tag, conn->cid);

	वापस 0;
पूर्ण

/*
 *	Handles special after-the-fact actions related to TMRs.
 *	Right now the only one that its really needed क्रम is
 *	connection recovery releated TASK_REASSIGN.
 */
पूर्णांक iscsit_पंचांगr_post_handler(काष्ठा iscsi_cmd *cmd, काष्ठा iscsi_conn *conn)
अणु
	काष्ठा iscsi_पंचांगr_req *पंचांगr_req = cmd->पंचांगr_req;
	काष्ठा se_पंचांगr_req *se_पंचांगr = cmd->se_cmd.se_पंचांगr_req;

	अगर (पंचांगr_req->task_reassign &&
	   (se_पंचांगr->response == ISCSI_TMF_RSP_COMPLETE))
		वापस iscsit_task_reassign_complete(पंचांगr_req, conn);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(iscsit_पंचांगr_post_handler);

/*
 *	Nothing to करो here, but leave it क्रम good measure. :-)
 */
अटल पूर्णांक iscsit_task_reassign_prepare_पढ़ो(
	काष्ठा iscsi_पंचांगr_req *पंचांगr_req,
	काष्ठा iscsi_conn *conn)
अणु
	वापस 0;
पूर्ण

अटल व्योम iscsit_task_reassign_prepare_unsolicited_dataout(
	काष्ठा iscsi_cmd *cmd,
	काष्ठा iscsi_conn *conn)
अणु
	पूर्णांक i, j;
	काष्ठा iscsi_pdu *pdu = शून्य;
	काष्ठा iscsi_seq *seq = शून्य;

	अगर (conn->sess->sess_ops->DataSequenceInOrder) अणु
		cmd->data_sn = 0;

		अगर (cmd->immediate_data)
			cmd->r2t_offset += (cmd->first_burst_len -
				cmd->seq_start_offset);

		अगर (conn->sess->sess_ops->DataPDUInOrder) अणु
			cmd->ग_लिखो_data_करोne -= (cmd->immediate_data) ?
						(cmd->first_burst_len -
						 cmd->seq_start_offset) :
						 cmd->first_burst_len;
			cmd->first_burst_len = 0;
			वापस;
		पूर्ण

		क्रम (i = 0; i < cmd->pdu_count; i++) अणु
			pdu = &cmd->pdu_list[i];

			अगर (pdu->status != ISCSI_PDU_RECEIVED_OK)
				जारी;

			अगर ((pdu->offset >= cmd->seq_start_offset) &&
			   ((pdu->offset + pdu->length) <=
			     cmd->seq_end_offset)) अणु
				cmd->first_burst_len -= pdu->length;
				cmd->ग_लिखो_data_करोne -= pdu->length;
				pdu->status = ISCSI_PDU_NOT_RECEIVED;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < cmd->seq_count; i++) अणु
			seq = &cmd->seq_list[i];

			अगर (seq->type != SEQTYPE_UNSOLICITED)
				जारी;

			cmd->ग_लिखो_data_करोne -=
					(seq->offset - seq->orig_offset);
			cmd->first_burst_len = 0;
			seq->data_sn = 0;
			seq->offset = seq->orig_offset;
			seq->next_burst_len = 0;
			seq->status = DATAOUT_SEQUENCE_WITHIN_COMMAND_RECOVERY;

			अगर (conn->sess->sess_ops->DataPDUInOrder)
				जारी;

			क्रम (j = 0; j < seq->pdu_count; j++) अणु
				pdu = &cmd->pdu_list[j+seq->pdu_start];

				अगर (pdu->status != ISCSI_PDU_RECEIVED_OK)
					जारी;

				pdu->status = ISCSI_PDU_NOT_RECEIVED;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक iscsit_task_reassign_prepare_ग_लिखो(
	काष्ठा iscsi_पंचांगr_req *पंचांगr_req,
	काष्ठा iscsi_conn *conn)
अणु
	काष्ठा iscsi_cmd *cmd = पंचांगr_req->ref_cmd;
	काष्ठा iscsi_pdu *pdu = शून्य;
	काष्ठा iscsi_r2t *r2t = शून्य, *r2t_पंचांगp;
	पूर्णांक first_incomplete_r2t = 1, i = 0;

	/*
	 * The command was in the process of receiving Unsolicited DataOUT when
	 * the connection failed.
	 */
	अगर (cmd->unsolicited_data)
		iscsit_task_reassign_prepare_unsolicited_dataout(cmd, conn);

	/*
	 * The Initiator is requesting R2Ts starting from zero,  skip
	 * checking acknowledged R2Ts and start checking काष्ठा iscsi_r2ts
	 * greater than zero.
	 */
	अगर (!पंचांगr_req->exp_data_sn)
		जाओ drop_unacknowledged_r2ts;

	/*
	 * We now check that the PDUs in DataOUT sequences below
	 * the TMR TASK_REASSIGN ExpDataSN (R2TSN the Initiator is
	 * expecting next) have all the DataOUT they require to complete
	 * the DataOUT sequence.  First scan from R2TSN 0 to TMR
	 * TASK_REASSIGN ExpDataSN-1.
	 *
	 * If we have not received all DataOUT in question,  we must
	 * make sure to make the appropriate changes to values in
	 * काष्ठा iscsi_cmd (and अन्यथाwhere depending on session parameters)
	 * so iscsit_build_r2ts_क्रम_cmd() in iscsit_task_reassign_complete_ग_लिखो()
	 * will resend a new R2T क्रम the DataOUT sequences in question.
	 */
	spin_lock_bh(&cmd->r2t_lock);
	अगर (list_empty(&cmd->cmd_r2t_list)) अणु
		spin_unlock_bh(&cmd->r2t_lock);
		वापस -1;
	पूर्ण

	list_क्रम_each_entry(r2t, &cmd->cmd_r2t_list, r2t_list) अणु

		अगर (r2t->r2t_sn >= पंचांगr_req->exp_data_sn)
			जारी;
		/*
		 * Safely ignore Recovery R2Ts and R2Ts that have completed
		 * DataOUT sequences.
		 */
		अगर (r2t->seq_complete)
			जारी;

		अगर (r2t->recovery_r2t)
			जारी;

		/*
		 *                 DataSequenceInOrder=Yes:
		 *
		 * Taking पूर्णांकo account the iSCSI implementation requirement of
		 * MaxOutstandingR2T=1 जबतक ErrorRecoveryLevel>0 and
		 * DataSequenceInOrder=Yes, we must take पूर्णांकo consideration
		 * the following:
		 *
		 *                  DataSequenceInOrder=No:
		 *
		 * Taking पूर्णांकo account that the Initiator controls the (possibly
		 * अक्रमom) PDU Order in (possibly अक्रमom) Sequence Order of
		 * DataOUT the target requests with R2Ts,  we must take पूर्णांकo
		 * consideration the following:
		 *
		 *      DataPDUInOrder=Yes क्रम DataSequenceInOrder=[Yes,No]:
		 *
		 * While processing non-complete R2T DataOUT sequence requests
		 * the Target will re-request only the total sequence length
		 * minus current received offset.  This is because we must
		 * assume the initiator will जारी sending DataOUT from the
		 * last PDU beक्रमe the connection failed.
		 *
		 *      DataPDUInOrder=No क्रम DataSequenceInOrder=[Yes,No]:
		 *
		 * While processing non-complete R2T DataOUT sequence requests
		 * the Target will re-request the entire DataOUT sequence अगर
		 * any single PDU is missing from the sequence.  This is because
		 * we have no logical method to determine the next PDU offset,
		 * and we must assume the Initiator will be sending any अक्रमom
		 * PDU offset in the current sequence after TASK_REASSIGN
		 * has completed.
		 */
		अगर (conn->sess->sess_ops->DataSequenceInOrder) अणु
			अगर (!first_incomplete_r2t) अणु
				cmd->r2t_offset -= r2t->xfer_len;
				जाओ next;
			पूर्ण

			अगर (conn->sess->sess_ops->DataPDUInOrder) अणु
				cmd->data_sn = 0;
				cmd->r2t_offset -= (r2t->xfer_len -
					cmd->next_burst_len);
				first_incomplete_r2t = 0;
				जाओ next;
			पूर्ण

			cmd->data_sn = 0;
			cmd->r2t_offset -= r2t->xfer_len;

			क्रम (i = 0; i < cmd->pdu_count; i++) अणु
				pdu = &cmd->pdu_list[i];

				अगर (pdu->status != ISCSI_PDU_RECEIVED_OK)
					जारी;

				अगर ((pdu->offset >= r2t->offset) &&
				    (pdu->offset < (r2t->offset +
						r2t->xfer_len))) अणु
					cmd->next_burst_len -= pdu->length;
					cmd->ग_लिखो_data_करोne -= pdu->length;
					pdu->status = ISCSI_PDU_NOT_RECEIVED;
				पूर्ण
			पूर्ण

			first_incomplete_r2t = 0;
		पूर्ण अन्यथा अणु
			काष्ठा iscsi_seq *seq;

			seq = iscsit_get_seq_holder(cmd, r2t->offset,
					r2t->xfer_len);
			अगर (!seq) अणु
				spin_unlock_bh(&cmd->r2t_lock);
				वापस -1;
			पूर्ण

			cmd->ग_लिखो_data_करोne -=
					(seq->offset - seq->orig_offset);
			seq->data_sn = 0;
			seq->offset = seq->orig_offset;
			seq->next_burst_len = 0;
			seq->status = DATAOUT_SEQUENCE_WITHIN_COMMAND_RECOVERY;

			cmd->seq_send_order--;

			अगर (conn->sess->sess_ops->DataPDUInOrder)
				जाओ next;

			क्रम (i = 0; i < seq->pdu_count; i++) अणु
				pdu = &cmd->pdu_list[i+seq->pdu_start];

				अगर (pdu->status != ISCSI_PDU_RECEIVED_OK)
					जारी;

				pdu->status = ISCSI_PDU_NOT_RECEIVED;
			पूर्ण
		पूर्ण

next:
		cmd->outstanding_r2ts--;
	पूर्ण
	spin_unlock_bh(&cmd->r2t_lock);

	/*
	 * We now drop all unacknowledged R2Ts, ie: ExpDataSN from TMR
	 * TASK_REASSIGN to the last R2T in the list..  We are also careful
	 * to check that the Initiator is not requesting R2Ts क्रम DataOUT
	 * sequences it has alपढ़ोy completed.
	 *
	 * Free each R2T in question and adjust values in काष्ठा iscsi_cmd
	 * accordingly so iscsit_build_r2ts_क्रम_cmd() करो the rest of
	 * the work after the TMR TASK_REASSIGN Response is sent.
	 */
drop_unacknowledged_r2ts:

	cmd->cmd_flags &= ~ICF_SENT_LAST_R2T;
	cmd->r2t_sn = पंचांगr_req->exp_data_sn;

	spin_lock_bh(&cmd->r2t_lock);
	list_क्रम_each_entry_safe(r2t, r2t_पंचांगp, &cmd->cmd_r2t_list, r2t_list) अणु
		/*
		 * Skip up to the R2T Sequence number provided by the
		 * iSCSI TASK_REASSIGN TMR
		 */
		अगर (r2t->r2t_sn < पंचांगr_req->exp_data_sn)
			जारी;

		अगर (r2t->seq_complete) अणु
			pr_err("Initiator is requesting R2Ts from"
				" R2TSN: 0x%08x, but R2TSN: 0x%08x, Offset: %u,"
				" Length: %u is already complete."
				"   BAD INITIATOR ERL=2 IMPLEMENTATION!\n",
				पंचांगr_req->exp_data_sn, r2t->r2t_sn,
				r2t->offset, r2t->xfer_len);
			spin_unlock_bh(&cmd->r2t_lock);
			वापस -1;
		पूर्ण

		अगर (r2t->recovery_r2t) अणु
			iscsit_मुक्त_r2t(r2t, cmd);
			जारी;
		पूर्ण

		/*		   DataSequenceInOrder=Yes:
		 *
		 * Taking पूर्णांकo account the iSCSI implementation requirement of
		 * MaxOutstandingR2T=1 जबतक ErrorRecoveryLevel>0 and
		 * DataSequenceInOrder=Yes, it's safe to subtract the R2Ts
		 * entire transfer length from the commands R2T offset marker.
		 *
		 *		   DataSequenceInOrder=No:
		 *
		 * We subtract the dअगरference from काष्ठा iscsi_seq between the
		 * current offset and original offset from cmd->ग_लिखो_data_करोne
		 * क्रम account क्रम DataOUT PDUs alपढ़ोy received.  Then reset
		 * the current offset to the original and zero out the current
		 * burst length,  to make sure we re-request the entire DataOUT
		 * sequence.
		 */
		अगर (conn->sess->sess_ops->DataSequenceInOrder)
			cmd->r2t_offset -= r2t->xfer_len;
		अन्यथा
			cmd->seq_send_order--;

		cmd->outstanding_r2ts--;
		iscsit_मुक्त_r2t(r2t, cmd);
	पूर्ण
	spin_unlock_bh(&cmd->r2t_lock);

	वापस 0;
पूर्ण

/*
 *	Perक्रमms sanity checks TMR TASK_REASSIGN's ExpDataSN क्रम
 *	a given काष्ठा iscsi_cmd.
 */
पूर्णांक iscsit_check_task_reassign_expdatasn(
	काष्ठा iscsi_पंचांगr_req *पंचांगr_req,
	काष्ठा iscsi_conn *conn)
अणु
	काष्ठा iscsi_cmd *ref_cmd = पंचांगr_req->ref_cmd;

	अगर (ref_cmd->iscsi_opcode != ISCSI_OP_SCSI_CMD)
		वापस 0;

	अगर (ref_cmd->se_cmd.se_cmd_flags & SCF_SENT_CHECK_CONDITION)
		वापस 0;

	अगर (ref_cmd->data_direction == DMA_NONE)
		वापस 0;

	/*
	 * For READs the TMR TASK_REASSIGNs ExpDataSN contains the next DataSN
	 * of DataIN the Initiator is expecting.
	 *
	 * Also check that the Initiator is not re-requesting DataIN that has
	 * alपढ़ोy been acknowledged with a DataAck SNACK.
	 */
	अगर (ref_cmd->data_direction == DMA_FROM_DEVICE) अणु
		अगर (पंचांगr_req->exp_data_sn > ref_cmd->data_sn) अणु
			pr_err("Received ExpDataSN: 0x%08x for READ"
				" in TMR TASK_REASSIGN greater than command's"
				" DataSN: 0x%08x.\n", पंचांगr_req->exp_data_sn,
				ref_cmd->data_sn);
			वापस -1;
		पूर्ण
		अगर ((ref_cmd->cmd_flags & ICF_GOT_DATACK_SNACK) &&
		    (पंचांगr_req->exp_data_sn <= ref_cmd->acked_data_sn)) अणु
			pr_err("Received ExpDataSN: 0x%08x for READ"
				" in TMR TASK_REASSIGN for previously"
				" acknowledged DataIN: 0x%08x,"
				" protocol error\n", पंचांगr_req->exp_data_sn,
				ref_cmd->acked_data_sn);
			वापस -1;
		पूर्ण
		वापस iscsit_task_reassign_prepare_पढ़ो(पंचांगr_req, conn);
	पूर्ण

	/*
	 * For WRITEs the TMR TASK_REASSIGNs ExpDataSN contains the next R2TSN
	 * क्रम R2Ts the Initiator is expecting.
	 *
	 * Do the magic in iscsit_task_reassign_prepare_ग_लिखो().
	 */
	अगर (ref_cmd->data_direction == DMA_TO_DEVICE) अणु
		अगर (पंचांगr_req->exp_data_sn > ref_cmd->r2t_sn) अणु
			pr_err("Received ExpDataSN: 0x%08x for WRITE"
				" in TMR TASK_REASSIGN greater than command's"
				" R2TSN: 0x%08x.\n", पंचांगr_req->exp_data_sn,
					ref_cmd->r2t_sn);
			वापस -1;
		पूर्ण
		वापस iscsit_task_reassign_prepare_ग_लिखो(पंचांगr_req, conn);
	पूर्ण

	pr_err("Unknown iSCSI data_direction: 0x%02x\n",
			ref_cmd->data_direction);

	वापस -1;
पूर्ण
