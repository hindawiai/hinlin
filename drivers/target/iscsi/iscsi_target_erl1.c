<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*******************************************************************************
 * This file contains error recovery level one used by the iSCSI Target driver.
 *
 * (c) Copyright 2007-2013 Datera, Inc.
 *
 * Author: Nicholas A. Bellinger <nab@linux-iscsi.org>
 *
 ******************************************************************************/

#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <scsi/iscsi_proto.h>
#समावेश <target/target_core_base.h>
#समावेश <target/target_core_fabric.h>
#समावेश <target/iscsi/iscsi_transport.h>

#समावेश <target/iscsi/iscsi_target_core.h>
#समावेश "iscsi_target_seq_pdu_list.h"
#समावेश "iscsi_target_datain_values.h"
#समावेश "iscsi_target_device.h"
#समावेश "iscsi_target_tpg.h"
#समावेश "iscsi_target_util.h"
#समावेश "iscsi_target_erl0.h"
#समावेश "iscsi_target_erl1.h"
#समावेश "iscsi_target_erl2.h"
#समावेश "iscsi_target.h"

#घोषणा OFFLOAD_BUF_SIZE	32768U

/*
 *	Used to dump excess datain payload क्रम certain error recovery
 *	situations.  Receive in OFFLOAD_BUF_SIZE max of datain per rx_data().
 *
 *	dump_padding_digest denotes अगर padding and data digests need
 *	to be dumped.
 */
पूर्णांक iscsit_dump_data_payload(
	काष्ठा iscsi_conn *conn,
	u32 buf_len,
	पूर्णांक dump_padding_digest)
अणु
	अक्षर *buf;
	पूर्णांक ret = DATAOUT_WITHIN_COMMAND_RECOVERY, rx_got;
	u32 length, offset = 0, size;
	काष्ठा kvec iov;

	अगर (conn->sess->sess_ops->RDMAExtensions)
		वापस 0;

	अगर (dump_padding_digest) अणु
		buf_len = ALIGN(buf_len, 4);
		अगर (conn->conn_ops->DataDigest)
			buf_len += ISCSI_CRC_LEN;
	पूर्ण

	length = min(buf_len, OFFLOAD_BUF_SIZE);

	buf = kzalloc(length, GFP_ATOMIC);
	अगर (!buf) अणु
		pr_err("Unable to allocate %u bytes for offload"
				" buffer.\n", length);
		वापस -1;
	पूर्ण
	स_रखो(&iov, 0, माप(काष्ठा kvec));

	जबतक (offset < buf_len) अणु
		size = min(buf_len - offset, length);

		iov.iov_len = size;
		iov.iov_base = buf;

		rx_got = rx_data(conn, &iov, 1, size);
		अगर (rx_got != size) अणु
			ret = DATAOUT_CANNOT_RECOVER;
			अवरोध;
		पूर्ण

		offset += size;
	पूर्ण

	kमुक्त(buf);
	वापस ret;
पूर्ण

/*
 *	Used क्रम retransmitting R2Ts from a R2T SNACK request.
 */
अटल पूर्णांक iscsit_send_recovery_r2t_क्रम_snack(
	काष्ठा iscsi_cmd *cmd,
	काष्ठा iscsi_r2t *r2t)
अणु
	/*
	 * If the काष्ठा iscsi_r2t has not been sent yet, we can safely
	 * ignore retransmission
	 * of the R2TSN in question.
	 */
	spin_lock_bh(&cmd->r2t_lock);
	अगर (!r2t->sent_r2t) अणु
		spin_unlock_bh(&cmd->r2t_lock);
		वापस 0;
	पूर्ण
	r2t->sent_r2t = 0;
	spin_unlock_bh(&cmd->r2t_lock);

	iscsit_add_cmd_to_immediate_queue(cmd, cmd->conn, ISTATE_SEND_R2T);

	वापस 0;
पूर्ण

अटल पूर्णांक iscsit_handle_r2t_snack(
	काष्ठा iscsi_cmd *cmd,
	अचिन्हित अक्षर *buf,
	u32 begrun,
	u32 runlength)
अणु
	u32 last_r2tsn;
	काष्ठा iscsi_r2t *r2t;

	/*
	 * Make sure the initiator is not requesting retransmission
	 * of R2TSNs alपढ़ोy acknowledged by a TMR TASK_REASSIGN.
	 */
	अगर ((cmd->cmd_flags & ICF_GOT_DATACK_SNACK) &&
	    (begrun <= cmd->acked_data_sn)) अणु
		pr_err("ITT: 0x%08x, R2T SNACK requesting"
			" retransmission of R2TSN: 0x%08x to 0x%08x but already"
			" acked to  R2TSN: 0x%08x by TMR TASK_REASSIGN,"
			" protocol error.\n", cmd->init_task_tag, begrun,
			(begrun + runlength), cmd->acked_data_sn);

		वापस iscsit_reject_cmd(cmd, ISCSI_REASON_PROTOCOL_ERROR, buf);
	पूर्ण

	अगर (runlength) अणु
		अगर ((begrun + runlength) > cmd->r2t_sn) अणु
			pr_err("Command ITT: 0x%08x received R2T SNACK"
			" with BegRun: 0x%08x, RunLength: 0x%08x, exceeds"
			" current R2TSN: 0x%08x, protocol error.\n",
			cmd->init_task_tag, begrun, runlength, cmd->r2t_sn);
			वापस iscsit_reject_cmd(cmd,
					ISCSI_REASON_BOOKMARK_INVALID, buf);
		पूर्ण
		last_r2tsn = (begrun + runlength);
	पूर्ण अन्यथा
		last_r2tsn = cmd->r2t_sn;

	जबतक (begrun < last_r2tsn) अणु
		r2t = iscsit_get_holder_क्रम_r2tsn(cmd, begrun);
		अगर (!r2t)
			वापस -1;
		अगर (iscsit_send_recovery_r2t_क्रम_snack(cmd, r2t) < 0)
			वापस -1;

		begrun++;
	पूर्ण

	वापस 0;
पूर्ण

/*
 *	Generates Offsets and NextBurstLength based on Begrun and Runlength
 *	carried in a Data SNACK or ExpDataSN in TMR TASK_REASSIGN.
 *
 *	For DataSequenceInOrder=Yes and DataPDUInOrder=[Yes,No] only.
 *
 *	FIXME: How is this handled क्रम a RData SNACK?
 */
पूर्णांक iscsit_create_recovery_datain_values_datasequenceinorder_yes(
	काष्ठा iscsi_cmd *cmd,
	काष्ठा iscsi_datain_req *dr)
अणु
	u32 data_sn = 0, data_sn_count = 0;
	u32 pdu_start = 0, seq_no = 0;
	u32 begrun = dr->begrun;
	काष्ठा iscsi_conn *conn = cmd->conn;

	जबतक (begrun > data_sn++) अणु
		data_sn_count++;
		अगर ((dr->next_burst_len +
		     conn->conn_ops->MaxRecvDataSegmentLength) <
		     conn->sess->sess_ops->MaxBurstLength) अणु
			dr->पढ़ो_data_करोne +=
				conn->conn_ops->MaxRecvDataSegmentLength;
			dr->next_burst_len +=
				conn->conn_ops->MaxRecvDataSegmentLength;
		पूर्ण अन्यथा अणु
			dr->पढ़ो_data_करोne +=
				(conn->sess->sess_ops->MaxBurstLength -
				 dr->next_burst_len);
			dr->next_burst_len = 0;
			pdu_start += data_sn_count;
			data_sn_count = 0;
			seq_no++;
		पूर्ण
	पूर्ण

	अगर (!conn->sess->sess_ops->DataPDUInOrder) अणु
		cmd->seq_no = seq_no;
		cmd->pdu_start = pdu_start;
		cmd->pdu_send_order = data_sn_count;
	पूर्ण

	वापस 0;
पूर्ण

/*
 *	Generates Offsets and NextBurstLength based on Begrun and Runlength
 *	carried in a Data SNACK or ExpDataSN in TMR TASK_REASSIGN.
 *
 *	For DataSequenceInOrder=No and DataPDUInOrder=[Yes,No] only.
 *
 *	FIXME: How is this handled क्रम a RData SNACK?
 */
पूर्णांक iscsit_create_recovery_datain_values_datasequenceinorder_no(
	काष्ठा iscsi_cmd *cmd,
	काष्ठा iscsi_datain_req *dr)
अणु
	पूर्णांक found_seq = 0, i;
	u32 data_sn, पढ़ो_data_करोne = 0, seq_send_order = 0;
	u32 begrun = dr->begrun;
	u32 runlength = dr->runlength;
	काष्ठा iscsi_conn *conn = cmd->conn;
	काष्ठा iscsi_seq *first_seq = शून्य, *seq = शून्य;

	अगर (!cmd->seq_list) अणु
		pr_err("struct iscsi_cmd->seq_list is NULL!\n");
		वापस -1;
	पूर्ण

	/*
	 * Calculate पढ़ो_data_करोne क्रम all sequences containing a
	 * first_datasn and last_datasn less than the BegRun.
	 *
	 * Locate the काष्ठा iscsi_seq the BegRun lies within and calculate
	 * NextBurstLenghth up to the DataSN based on MaxRecvDataSegmentLength.
	 *
	 * Also use काष्ठा iscsi_seq->seq_send_order to determine where to start.
	 */
	क्रम (i = 0; i < cmd->seq_count; i++) अणु
		seq = &cmd->seq_list[i];

		अगर (!seq->seq_send_order)
			first_seq = seq;

		/*
		 * No data has been transferred क्रम this DataIN sequence, so the
		 * seq->first_datasn and seq->last_datasn have not been set.
		 */
		अगर (!seq->sent) अणु
			pr_err("Ignoring non-sent sequence 0x%08x ->"
				" 0x%08x\n\n", seq->first_datasn,
				seq->last_datasn);
			जारी;
		पूर्ण

		/*
		 * This DataIN sequence is precedes the received BegRun, add the
		 * total xfer_len of the sequence to पढ़ो_data_करोne and reset
		 * seq->pdu_send_order.
		 */
		अगर ((seq->first_datasn < begrun) &&
				(seq->last_datasn < begrun)) अणु
			pr_err("Pre BegRun sequence 0x%08x ->"
				" 0x%08x\n", seq->first_datasn,
				seq->last_datasn);

			पढ़ो_data_करोne += cmd->seq_list[i].xfer_len;
			seq->next_burst_len = seq->pdu_send_order = 0;
			जारी;
		पूर्ण

		/*
		 * The BegRun lies within this DataIN sequence.
		 */
		अगर ((seq->first_datasn <= begrun) &&
				(seq->last_datasn >= begrun)) अणु
			pr_err("Found sequence begrun: 0x%08x in"
				" 0x%08x -> 0x%08x\n", begrun,
				seq->first_datasn, seq->last_datasn);

			seq_send_order = seq->seq_send_order;
			data_sn = seq->first_datasn;
			seq->next_burst_len = seq->pdu_send_order = 0;
			found_seq = 1;

			/*
			 * For DataPDUInOrder=Yes, जबतक the first DataSN of
			 * the sequence is less than the received BegRun, add
			 * the MaxRecvDataSegmentLength to पढ़ो_data_करोne and
			 * to the sequence's next_burst_len;
			 *
			 * For DataPDUInOrder=No, जबतक the first DataSN of the
			 * sequence is less than the received BegRun, find the
			 * काष्ठा iscsi_pdu of the DataSN in question and add the
			 * MaxRecvDataSegmentLength to पढ़ो_data_करोne and to the
			 * sequence's next_burst_len;
			 */
			अगर (conn->sess->sess_ops->DataPDUInOrder) अणु
				जबतक (data_sn < begrun) अणु
					seq->pdu_send_order++;
					पढ़ो_data_करोne +=
						conn->conn_ops->MaxRecvDataSegmentLength;
					seq->next_burst_len +=
						conn->conn_ops->MaxRecvDataSegmentLength;
					data_sn++;
				पूर्ण
			पूर्ण अन्यथा अणु
				पूर्णांक j;
				काष्ठा iscsi_pdu *pdu;

				जबतक (data_sn < begrun) अणु
					seq->pdu_send_order++;

					क्रम (j = 0; j < seq->pdu_count; j++) अणु
						pdu = &cmd->pdu_list[
							seq->pdu_start + j];
						अगर (pdu->data_sn == data_sn) अणु
							पढ़ो_data_करोne +=
								pdu->length;
							seq->next_burst_len +=
								pdu->length;
						पूर्ण
					पूर्ण
					data_sn++;
				पूर्ण
			पूर्ण
			जारी;
		पूर्ण

		/*
		 * This DataIN sequence is larger than the received BegRun,
		 * reset seq->pdu_send_order and जारी.
		 */
		अगर ((seq->first_datasn > begrun) ||
				(seq->last_datasn > begrun)) अणु
			pr_err("Post BegRun sequence 0x%08x -> 0x%08x\n",
					seq->first_datasn, seq->last_datasn);

			seq->next_burst_len = seq->pdu_send_order = 0;
			जारी;
		पूर्ण
	पूर्ण

	अगर (!found_seq) अणु
		अगर (!begrun) अणु
			अगर (!first_seq) अणु
				pr_err("ITT: 0x%08x, Begrun: 0x%08x"
					" but first_seq is NULL\n",
					cmd->init_task_tag, begrun);
				वापस -1;
			पूर्ण
			seq_send_order = first_seq->seq_send_order;
			seq->next_burst_len = seq->pdu_send_order = 0;
			जाओ करोne;
		पूर्ण

		pr_err("Unable to locate struct iscsi_seq for ITT: 0x%08x,"
			" BegRun: 0x%08x, RunLength: 0x%08x while"
			" DataSequenceInOrder=No and DataPDUInOrder=%s.\n",
				cmd->init_task_tag, begrun, runlength,
			(conn->sess->sess_ops->DataPDUInOrder) ? "Yes" : "No");
		वापस -1;
	पूर्ण

करोne:
	dr->पढ़ो_data_करोne = पढ़ो_data_करोne;
	dr->seq_send_order = seq_send_order;

	वापस 0;
पूर्ण

अटल पूर्णांक iscsit_handle_recovery_datain(
	काष्ठा iscsi_cmd *cmd,
	अचिन्हित अक्षर *buf,
	u32 begrun,
	u32 runlength)
अणु
	काष्ठा iscsi_conn *conn = cmd->conn;
	काष्ठा iscsi_datain_req *dr;
	काष्ठा se_cmd *se_cmd = &cmd->se_cmd;

	अगर (!(se_cmd->transport_state & CMD_T_COMPLETE)) अणु
		pr_err("Ignoring ITT: 0x%08x Data SNACK\n",
				cmd->init_task_tag);
		वापस 0;
	पूर्ण

	/*
	 * Make sure the initiator is not requesting retransmission
	 * of DataSNs alपढ़ोy acknowledged by a Data ACK SNACK.
	 */
	अगर ((cmd->cmd_flags & ICF_GOT_DATACK_SNACK) &&
	    (begrun <= cmd->acked_data_sn)) अणु
		pr_err("ITT: 0x%08x, Data SNACK requesting"
			" retransmission of DataSN: 0x%08x to 0x%08x but"
			" already acked to DataSN: 0x%08x by Data ACK SNACK,"
			" protocol error.\n", cmd->init_task_tag, begrun,
			(begrun + runlength), cmd->acked_data_sn);

		वापस iscsit_reject_cmd(cmd, ISCSI_REASON_PROTOCOL_ERROR, buf);
	पूर्ण

	/*
	 * Make sure BegRun and RunLength in the Data SNACK are sane.
	 * Note: (cmd->data_sn - 1) will carry the maximum DataSN sent.
	 */
	अगर ((begrun + runlength) > (cmd->data_sn - 1)) अणु
		pr_err("Initiator requesting BegRun: 0x%08x, RunLength"
			": 0x%08x greater than maximum DataSN: 0x%08x.\n",
				begrun, runlength, (cmd->data_sn - 1));
		वापस iscsit_reject_cmd(cmd, ISCSI_REASON_BOOKMARK_INVALID,
					 buf);
	पूर्ण

	dr = iscsit_allocate_datain_req();
	अगर (!dr)
		वापस iscsit_reject_cmd(cmd, ISCSI_REASON_BOOKMARK_NO_RESOURCES,
					 buf);

	dr->data_sn = dr->begrun = begrun;
	dr->runlength = runlength;
	dr->generate_recovery_values = 1;
	dr->recovery = DATAIN_WITHIN_COMMAND_RECOVERY;

	iscsit_attach_datain_req(cmd, dr);

	cmd->i_state = ISTATE_SEND_DATAIN;
	iscsit_add_cmd_to_response_queue(cmd, conn, cmd->i_state);

	वापस 0;
पूर्ण

पूर्णांक iscsit_handle_recovery_datain_or_r2t(
	काष्ठा iscsi_conn *conn,
	अचिन्हित अक्षर *buf,
	itt_t init_task_tag,
	u32 targ_xfer_tag,
	u32 begrun,
	u32 runlength)
अणु
	काष्ठा iscsi_cmd *cmd;

	cmd = iscsit_find_cmd_from_itt(conn, init_task_tag);
	अगर (!cmd)
		वापस 0;

	/*
	 * FIXME: This will not work क्रम bidi commands.
	 */
	चयन (cmd->data_direction) अणु
	हाल DMA_TO_DEVICE:
		वापस iscsit_handle_r2t_snack(cmd, buf, begrun, runlength);
	हाल DMA_FROM_DEVICE:
		वापस iscsit_handle_recovery_datain(cmd, buf, begrun,
				runlength);
	शेष:
		pr_err("Unknown cmd->data_direction: 0x%02x\n",
				cmd->data_direction);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/* #warning FIXME: Status SNACK needs to be dependent on OPCODE!!! */
पूर्णांक iscsit_handle_status_snack(
	काष्ठा iscsi_conn *conn,
	itt_t init_task_tag,
	u32 targ_xfer_tag,
	u32 begrun,
	u32 runlength)
अणु
	काष्ठा iscsi_cmd *cmd = शून्य;
	u32 last_statsn;
	पूर्णांक found_cmd;

	अगर (!begrun) अणु
		begrun = conn->exp_statsn;
	पूर्ण अन्यथा अगर (conn->exp_statsn > begrun) अणु
		pr_err("Got Status SNACK Begrun: 0x%08x, RunLength:"
			" 0x%08x but already got ExpStatSN: 0x%08x on CID:"
			" %hu.\n", begrun, runlength, conn->exp_statsn,
			conn->cid);
		वापस 0;
	पूर्ण

	last_statsn = (!runlength) ? conn->stat_sn : (begrun + runlength);

	जबतक (begrun < last_statsn) अणु
		found_cmd = 0;

		spin_lock_bh(&conn->cmd_lock);
		list_क्रम_each_entry(cmd, &conn->conn_cmd_list, i_conn_node) अणु
			अगर (cmd->stat_sn == begrun) अणु
				found_cmd = 1;
				अवरोध;
			पूर्ण
		पूर्ण
		spin_unlock_bh(&conn->cmd_lock);

		अगर (!found_cmd) अणु
			pr_err("Unable to find StatSN: 0x%08x for"
				" a Status SNACK, assuming this was a"
				" protactic SNACK for an untransmitted"
				" StatSN, ignoring.\n", begrun);
			begrun++;
			जारी;
		पूर्ण

		spin_lock_bh(&cmd->istate_lock);
		अगर (cmd->i_state == ISTATE_SEND_DATAIN) अणु
			spin_unlock_bh(&cmd->istate_lock);
			pr_err("Ignoring Status SNACK for BegRun:"
				" 0x%08x, RunLength: 0x%08x, assuming this was"
				" a protactic SNACK for an untransmitted"
				" StatSN\n", begrun, runlength);
			begrun++;
			जारी;
		पूर्ण
		spin_unlock_bh(&cmd->istate_lock);

		cmd->i_state = ISTATE_SEND_STATUS_RECOVERY;
		iscsit_add_cmd_to_response_queue(cmd, conn, cmd->i_state);
		begrun++;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक iscsit_handle_data_ack(
	काष्ठा iscsi_conn *conn,
	u32 targ_xfer_tag,
	u32 begrun,
	u32 runlength)
अणु
	काष्ठा iscsi_cmd *cmd = शून्य;

	cmd = iscsit_find_cmd_from_ttt(conn, targ_xfer_tag);
	अगर (!cmd) अणु
		pr_err("Data ACK SNACK for TTT: 0x%08x is"
			" invalid.\n", targ_xfer_tag);
		वापस -1;
	पूर्ण

	अगर (begrun <= cmd->acked_data_sn) अणु
		pr_err("ITT: 0x%08x Data ACK SNACK BegRUN: 0x%08x is"
			" less than the already acked DataSN: 0x%08x.\n",
			cmd->init_task_tag, begrun, cmd->acked_data_sn);
		वापस -1;
	पूर्ण

	/*
	 * For Data ACK SNACK, BegRun is the next expected DataSN.
	 * (see iSCSI v19: 10.16.6)
	 */
	cmd->cmd_flags |= ICF_GOT_DATACK_SNACK;
	cmd->acked_data_sn = (begrun - 1);

	pr_debug("Received Data ACK SNACK for ITT: 0x%08x,"
		" updated acked DataSN to 0x%08x.\n",
			cmd->init_task_tag, cmd->acked_data_sn);

	वापस 0;
पूर्ण

अटल पूर्णांक iscsit_send_recovery_r2t(
	काष्ठा iscsi_cmd *cmd,
	u32 offset,
	u32 xfer_len)
अणु
	पूर्णांक ret;

	spin_lock_bh(&cmd->r2t_lock);
	ret = iscsit_add_r2t_to_list(cmd, offset, xfer_len, 1, 0);
	spin_unlock_bh(&cmd->r2t_lock);

	वापस ret;
पूर्ण

पूर्णांक iscsit_dataout_datapduinorder_no_fbit(
	काष्ठा iscsi_cmd *cmd,
	काष्ठा iscsi_pdu *pdu)
अणु
	पूर्णांक i, send_recovery_r2t = 0, recovery = 0;
	u32 length = 0, offset = 0, pdu_count = 0, xfer_len = 0;
	काष्ठा iscsi_conn *conn = cmd->conn;
	काष्ठा iscsi_pdu *first_pdu = शून्य;

	/*
	 * Get an काष्ठा iscsi_pdu poपूर्णांकer to the first PDU, and total PDU count
	 * of the DataOUT sequence.
	 */
	अगर (conn->sess->sess_ops->DataSequenceInOrder) अणु
		क्रम (i = 0; i < cmd->pdu_count; i++) अणु
			अगर (cmd->pdu_list[i].seq_no == pdu->seq_no) अणु
				अगर (!first_pdu)
					first_pdu = &cmd->pdu_list[i];
				xfer_len += cmd->pdu_list[i].length;
				pdu_count++;
			पूर्ण अन्यथा अगर (pdu_count)
				अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा iscsi_seq *seq = cmd->seq_ptr;

		first_pdu = &cmd->pdu_list[seq->pdu_start];
		pdu_count = seq->pdu_count;
	पूर्ण

	अगर (!first_pdu || !pdu_count)
		वापस DATAOUT_CANNOT_RECOVER;

	/*
	 * Loop through the ending DataOUT Sequence checking each काष्ठा iscsi_pdu.
	 * The following ugly logic करोes batching of not received PDUs.
	 */
	क्रम (i = 0; i < pdu_count; i++) अणु
		अगर (first_pdu[i].status == ISCSI_PDU_RECEIVED_OK) अणु
			अगर (!send_recovery_r2t)
				जारी;

			अगर (iscsit_send_recovery_r2t(cmd, offset, length) < 0)
				वापस DATAOUT_CANNOT_RECOVER;

			send_recovery_r2t = length = offset = 0;
			जारी;
		पूर्ण
		/*
		 * Set recovery = 1 क्रम any missing, CRC failed, or समयd
		 * out PDUs to let the DataOUT logic know that this sequence
		 * has not been completed yet.
		 *
		 * Also, only send a Recovery R2T क्रम ISCSI_PDU_NOT_RECEIVED.
		 * We assume अगर the PDU either failed CRC or समयd out
		 * that a Recovery R2T has alपढ़ोy been sent.
		 */
		recovery = 1;

		अगर (first_pdu[i].status != ISCSI_PDU_NOT_RECEIVED)
			जारी;

		अगर (!offset)
			offset = first_pdu[i].offset;
		length += first_pdu[i].length;

		send_recovery_r2t = 1;
	पूर्ण

	अगर (send_recovery_r2t)
		अगर (iscsit_send_recovery_r2t(cmd, offset, length) < 0)
			वापस DATAOUT_CANNOT_RECOVER;

	वापस (!recovery) ? DATAOUT_NORMAL : DATAOUT_WITHIN_COMMAND_RECOVERY;
पूर्ण

अटल पूर्णांक iscsit_recalculate_dataout_values(
	काष्ठा iscsi_cmd *cmd,
	u32 pdu_offset,
	u32 pdu_length,
	u32 *r2t_offset,
	u32 *r2t_length)
अणु
	पूर्णांक i;
	काष्ठा iscsi_conn *conn = cmd->conn;
	काष्ठा iscsi_pdu *pdu = शून्य;

	अगर (conn->sess->sess_ops->DataSequenceInOrder) अणु
		cmd->data_sn = 0;

		अगर (conn->sess->sess_ops->DataPDUInOrder) अणु
			*r2t_offset = cmd->ग_लिखो_data_करोne;
			*r2t_length = (cmd->seq_end_offset -
					cmd->ग_लिखो_data_करोne);
			वापस 0;
		पूर्ण

		*r2t_offset = cmd->seq_start_offset;
		*r2t_length = (cmd->seq_end_offset - cmd->seq_start_offset);

		क्रम (i = 0; i < cmd->pdu_count; i++) अणु
			pdu = &cmd->pdu_list[i];

			अगर (pdu->status != ISCSI_PDU_RECEIVED_OK)
				जारी;

			अगर ((pdu->offset >= cmd->seq_start_offset) &&
			   ((pdu->offset + pdu->length) <=
			     cmd->seq_end_offset)) अणु
				अगर (!cmd->unsolicited_data)
					cmd->next_burst_len -= pdu->length;
				अन्यथा
					cmd->first_burst_len -= pdu->length;

				cmd->ग_लिखो_data_करोne -= pdu->length;
				pdu->status = ISCSI_PDU_NOT_RECEIVED;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा iscsi_seq *seq = शून्य;

		seq = iscsit_get_seq_holder(cmd, pdu_offset, pdu_length);
		अगर (!seq)
			वापस -1;

		*r2t_offset = seq->orig_offset;
		*r2t_length = seq->xfer_len;

		cmd->ग_लिखो_data_करोne -= (seq->offset - seq->orig_offset);
		अगर (cmd->immediate_data)
			cmd->first_burst_len = cmd->ग_लिखो_data_करोne;

		seq->data_sn = 0;
		seq->offset = seq->orig_offset;
		seq->next_burst_len = 0;
		seq->status = DATAOUT_SEQUENCE_WITHIN_COMMAND_RECOVERY;

		अगर (conn->sess->sess_ops->DataPDUInOrder)
			वापस 0;

		क्रम (i = 0; i < seq->pdu_count; i++) अणु
			pdu = &cmd->pdu_list[i+seq->pdu_start];

			अगर (pdu->status != ISCSI_PDU_RECEIVED_OK)
				जारी;

			pdu->status = ISCSI_PDU_NOT_RECEIVED;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक iscsit_recover_dataout_sequence(
	काष्ठा iscsi_cmd *cmd,
	u32 pdu_offset,
	u32 pdu_length)
अणु
	u32 r2t_length = 0, r2t_offset = 0;

	spin_lock_bh(&cmd->istate_lock);
	cmd->cmd_flags |= ICF_WITHIN_COMMAND_RECOVERY;
	spin_unlock_bh(&cmd->istate_lock);

	अगर (iscsit_recalculate_dataout_values(cmd, pdu_offset, pdu_length,
			&r2t_offset, &r2t_length) < 0)
		वापस DATAOUT_CANNOT_RECOVER;

	iscsit_send_recovery_r2t(cmd, r2t_offset, r2t_length);

	वापस DATAOUT_WITHIN_COMMAND_RECOVERY;
पूर्ण

अटल काष्ठा iscsi_ooo_cmdsn *iscsit_allocate_ooo_cmdsn(व्योम)
अणु
	काष्ठा iscsi_ooo_cmdsn *ooo_cmdsn = शून्य;

	ooo_cmdsn = kmem_cache_zalloc(lio_ooo_cache, GFP_ATOMIC);
	अगर (!ooo_cmdsn) अणु
		pr_err("Unable to allocate memory for"
			" struct iscsi_ooo_cmdsn.\n");
		वापस शून्य;
	पूर्ण
	INIT_LIST_HEAD(&ooo_cmdsn->ooo_list);

	वापस ooo_cmdsn;
पूर्ण

अटल पूर्णांक iscsit_attach_ooo_cmdsn(
	काष्ठा iscsi_session *sess,
	काष्ठा iscsi_ooo_cmdsn *ooo_cmdsn)
अणु
	काष्ठा iscsi_ooo_cmdsn *ooo_tail, *ooo_पंचांगp;

	lockdep_निश्चित_held(&sess->cmdsn_mutex);

	/*
	 * We attach the काष्ठा iscsi_ooo_cmdsn entry to the out of order
	 * list in increasing CmdSN order.
	 * This allows iscsi_execute_ooo_cmdsns() to detect any
	 * additional CmdSN holes जबतक perक्रमming delayed execution.
	 */
	अगर (list_empty(&sess->sess_ooo_cmdsn_list))
		list_add_tail(&ooo_cmdsn->ooo_list,
				&sess->sess_ooo_cmdsn_list);
	अन्यथा अणु
		ooo_tail = list_entry(sess->sess_ooo_cmdsn_list.prev,
				typeof(*ooo_tail), ooo_list);
		/*
		 * CmdSN is greater than the tail of the list.
		 */
		अगर (iscsi_sna_lt(ooo_tail->cmdsn, ooo_cmdsn->cmdsn))
			list_add_tail(&ooo_cmdsn->ooo_list,
					&sess->sess_ooo_cmdsn_list);
		अन्यथा अणु
			/*
			 * CmdSN is either lower than the head,  or somewhere
			 * in the middle.
			 */
			list_क्रम_each_entry(ooo_पंचांगp, &sess->sess_ooo_cmdsn_list,
						ooo_list) अणु
				अगर (iscsi_sna_lt(ooo_पंचांगp->cmdsn, ooo_cmdsn->cmdsn))
					जारी;

				/* Insert beक्रमe this entry */
				list_add(&ooo_cmdsn->ooo_list,
					ooo_पंचांगp->ooo_list.prev);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 *	Removes an काष्ठा iscsi_ooo_cmdsn from a session's list,
 *	called with काष्ठा iscsi_session->cmdsn_mutex held.
 */
व्योम iscsit_हटाओ_ooo_cmdsn(
	काष्ठा iscsi_session *sess,
	काष्ठा iscsi_ooo_cmdsn *ooo_cmdsn)
अणु
	list_del(&ooo_cmdsn->ooo_list);
	kmem_cache_मुक्त(lio_ooo_cache, ooo_cmdsn);
पूर्ण

व्योम iscsit_clear_ooo_cmdsns_क्रम_conn(काष्ठा iscsi_conn *conn)
अणु
	काष्ठा iscsi_ooo_cmdsn *ooo_cmdsn;
	काष्ठा iscsi_session *sess = conn->sess;

	mutex_lock(&sess->cmdsn_mutex);
	list_क्रम_each_entry(ooo_cmdsn, &sess->sess_ooo_cmdsn_list, ooo_list) अणु
		अगर (ooo_cmdsn->cid != conn->cid)
			जारी;

		ooo_cmdsn->cmd = शून्य;
	पूर्ण
	mutex_unlock(&sess->cmdsn_mutex);
पूर्ण

पूर्णांक iscsit_execute_ooo_cmdsns(काष्ठा iscsi_session *sess)
अणु
	पूर्णांक ooo_count = 0;
	काष्ठा iscsi_cmd *cmd = शून्य;
	काष्ठा iscsi_ooo_cmdsn *ooo_cmdsn, *ooo_cmdsn_पंचांगp;

	lockdep_निश्चित_held(&sess->cmdsn_mutex);

	list_क्रम_each_entry_safe(ooo_cmdsn, ooo_cmdsn_पंचांगp,
				&sess->sess_ooo_cmdsn_list, ooo_list) अणु
		अगर (ooo_cmdsn->cmdsn != sess->exp_cmd_sn)
			जारी;

		अगर (!ooo_cmdsn->cmd) अणु
			sess->exp_cmd_sn++;
			iscsit_हटाओ_ooo_cmdsn(sess, ooo_cmdsn);
			जारी;
		पूर्ण

		cmd = ooo_cmdsn->cmd;
		cmd->i_state = cmd->deferred_i_state;
		ooo_count++;
		sess->exp_cmd_sn++;
		pr_debug("Executing out of order CmdSN: 0x%08x,"
			" incremented ExpCmdSN to 0x%08x.\n",
			cmd->cmd_sn, sess->exp_cmd_sn);

		iscsit_हटाओ_ooo_cmdsn(sess, ooo_cmdsn);

		अगर (iscsit_execute_cmd(cmd, 1) < 0)
			वापस -1;

		जारी;
	पूर्ण

	वापस ooo_count;
पूर्ण

/*
 *	Called either:
 *
 *	1. With sess->cmdsn_mutex held from iscsi_execute_ooo_cmdsns()
 *	or iscsi_check_received_cmdsn().
 *	2. With no locks held directly from iscsi_handle_XXX_pdu() functions
 *	क्रम immediate commands.
 */
पूर्णांक iscsit_execute_cmd(काष्ठा iscsi_cmd *cmd, पूर्णांक ooo)
अणु
	काष्ठा se_cmd *se_cmd = &cmd->se_cmd;
	काष्ठा iscsi_conn *conn = cmd->conn;
	पूर्णांक lr = 0;

	spin_lock_bh(&cmd->istate_lock);
	अगर (ooo)
		cmd->cmd_flags &= ~ICF_OOO_CMDSN;

	चयन (cmd->iscsi_opcode) अणु
	हाल ISCSI_OP_SCSI_CMD:
		/*
		 * Go ahead and send the CHECK_CONDITION status क्रम
		 * any SCSI CDB exceptions that may have occurred.
		 */
		अगर (cmd->sense_reason) अणु
			अगर (cmd->sense_reason == TCM_RESERVATION_CONFLICT) अणु
				cmd->i_state = ISTATE_SEND_STATUS;
				spin_unlock_bh(&cmd->istate_lock);
				iscsit_add_cmd_to_response_queue(cmd, cmd->conn,
						cmd->i_state);
				वापस 0;
			पूर्ण
			spin_unlock_bh(&cmd->istate_lock);
			अगर (cmd->se_cmd.transport_state & CMD_T_ABORTED)
				वापस 0;
			वापस transport_send_check_condition_and_sense(se_cmd,
					cmd->sense_reason, 0);
		पूर्ण
		/*
		 * Special हाल क्रम delayed CmdSN with Immediate
		 * Data and/or Unsolicited Data Out attached.
		 */
		अगर (cmd->immediate_data) अणु
			अगर (cmd->cmd_flags & ICF_GOT_LAST_DATAOUT) अणु
				spin_unlock_bh(&cmd->istate_lock);
				target_execute_cmd(&cmd->se_cmd);
				वापस 0;
			पूर्ण
			spin_unlock_bh(&cmd->istate_lock);

			अगर (!(cmd->cmd_flags &
					ICF_NON_IMMEDIATE_UNSOLICITED_DATA)) अणु
				अगर (cmd->se_cmd.transport_state & CMD_T_ABORTED)
					वापस 0;

				iscsit_set_dataout_sequence_values(cmd);
				conn->conn_transport->iscsit_get_dataout(conn, cmd, false);
			पूर्ण
			वापस 0;
		पूर्ण
		/*
		 * The शेष handler.
		 */
		spin_unlock_bh(&cmd->istate_lock);

		अगर ((cmd->data_direction == DMA_TO_DEVICE) &&
		    !(cmd->cmd_flags & ICF_NON_IMMEDIATE_UNSOLICITED_DATA)) अणु
			अगर (cmd->se_cmd.transport_state & CMD_T_ABORTED)
				वापस 0;

			iscsit_set_unsolicited_dataout(cmd);
		पूर्ण
		वापस transport_handle_cdb_direct(&cmd->se_cmd);

	हाल ISCSI_OP_NOOP_OUT:
	हाल ISCSI_OP_TEXT:
		spin_unlock_bh(&cmd->istate_lock);
		iscsit_add_cmd_to_response_queue(cmd, cmd->conn, cmd->i_state);
		अवरोध;
	हाल ISCSI_OP_SCSI_TMFUNC:
		अगर (cmd->se_cmd.se_पंचांगr_req->response) अणु
			spin_unlock_bh(&cmd->istate_lock);
			iscsit_add_cmd_to_response_queue(cmd, cmd->conn,
					cmd->i_state);
			वापस 0;
		पूर्ण
		spin_unlock_bh(&cmd->istate_lock);

		वापस transport_generic_handle_पंचांगr(&cmd->se_cmd);
	हाल ISCSI_OP_LOGOUT:
		spin_unlock_bh(&cmd->istate_lock);
		चयन (cmd->logout_reason) अणु
		हाल ISCSI_LOGOUT_REASON_CLOSE_SESSION:
			lr = iscsit_logout_बंदsession(cmd, cmd->conn);
			अवरोध;
		हाल ISCSI_LOGOUT_REASON_CLOSE_CONNECTION:
			lr = iscsit_logout_बंदconnection(cmd, cmd->conn);
			अवरोध;
		हाल ISCSI_LOGOUT_REASON_RECOVERY:
			lr = iscsit_logout_हटाओconnक्रमrecovery(cmd, cmd->conn);
			अवरोध;
		शेष:
			pr_err("Unknown iSCSI Logout Request Code:"
				" 0x%02x\n", cmd->logout_reason);
			वापस -1;
		पूर्ण

		वापस lr;
	शेष:
		spin_unlock_bh(&cmd->istate_lock);
		pr_err("Cannot perform out of order execution for"
		" unknown iSCSI Opcode: 0x%02x\n", cmd->iscsi_opcode);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

व्योम iscsit_मुक्त_all_ooo_cmdsns(काष्ठा iscsi_session *sess)
अणु
	काष्ठा iscsi_ooo_cmdsn *ooo_cmdsn, *ooo_cmdsn_पंचांगp;

	mutex_lock(&sess->cmdsn_mutex);
	list_क्रम_each_entry_safe(ooo_cmdsn, ooo_cmdsn_पंचांगp,
			&sess->sess_ooo_cmdsn_list, ooo_list) अणु

		list_del(&ooo_cmdsn->ooo_list);
		kmem_cache_मुक्त(lio_ooo_cache, ooo_cmdsn);
	पूर्ण
	mutex_unlock(&sess->cmdsn_mutex);
पूर्ण

पूर्णांक iscsit_handle_ooo_cmdsn(
	काष्ठा iscsi_session *sess,
	काष्ठा iscsi_cmd *cmd,
	u32 cmdsn)
अणु
	पूर्णांक batch = 0;
	काष्ठा iscsi_ooo_cmdsn *ooo_cmdsn = शून्य, *ooo_tail = शून्य;

	cmd->deferred_i_state		= cmd->i_state;
	cmd->i_state			= ISTATE_DEFERRED_CMD;
	cmd->cmd_flags			|= ICF_OOO_CMDSN;

	अगर (list_empty(&sess->sess_ooo_cmdsn_list))
		batch = 1;
	अन्यथा अणु
		ooo_tail = list_entry(sess->sess_ooo_cmdsn_list.prev,
				typeof(*ooo_tail), ooo_list);
		अगर (ooo_tail->cmdsn != (cmdsn - 1))
			batch = 1;
	पूर्ण

	ooo_cmdsn = iscsit_allocate_ooo_cmdsn();
	अगर (!ooo_cmdsn)
		वापस -ENOMEM;

	ooo_cmdsn->cmd			= cmd;
	ooo_cmdsn->batch_count		= (batch) ?
					  (cmdsn - sess->exp_cmd_sn) : 1;
	ooo_cmdsn->cid			= cmd->conn->cid;
	ooo_cmdsn->exp_cmdsn		= sess->exp_cmd_sn;
	ooo_cmdsn->cmdsn		= cmdsn;

	अगर (iscsit_attach_ooo_cmdsn(sess, ooo_cmdsn) < 0) अणु
		kmem_cache_मुक्त(lio_ooo_cache, ooo_cmdsn);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक iscsit_set_dataout_समयout_values(
	काष्ठा iscsi_cmd *cmd,
	u32 *offset,
	u32 *length)
अणु
	काष्ठा iscsi_conn *conn = cmd->conn;
	काष्ठा iscsi_r2t *r2t;

	अगर (cmd->unsolicited_data) अणु
		*offset = 0;
		*length = (conn->sess->sess_ops->FirstBurstLength >
			   cmd->se_cmd.data_length) ?
			   cmd->se_cmd.data_length :
			   conn->sess->sess_ops->FirstBurstLength;
		वापस 0;
	पूर्ण

	spin_lock_bh(&cmd->r2t_lock);
	अगर (list_empty(&cmd->cmd_r2t_list)) अणु
		pr_err("cmd->cmd_r2t_list is empty!\n");
		spin_unlock_bh(&cmd->r2t_lock);
		वापस -1;
	पूर्ण

	list_क्रम_each_entry(r2t, &cmd->cmd_r2t_list, r2t_list) अणु
		अगर (r2t->sent_r2t && !r2t->recovery_r2t && !r2t->seq_complete) अणु
			*offset = r2t->offset;
			*length = r2t->xfer_len;
			spin_unlock_bh(&cmd->r2t_lock);
			वापस 0;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&cmd->r2t_lock);

	pr_err("Unable to locate any incomplete DataOUT"
		" sequences for ITT: 0x%08x.\n", cmd->init_task_tag);

	वापस -1;
पूर्ण

/*
 *	NOTE: Called from पूर्णांकerrupt (समयr) context.
 */
व्योम iscsit_handle_dataout_समयout(काष्ठा समयr_list *t)
अणु
	u32 pdu_length = 0, pdu_offset = 0;
	u32 r2t_length = 0, r2t_offset = 0;
	काष्ठा iscsi_cmd *cmd = from_समयr(cmd, t, dataout_समयr);
	काष्ठा iscsi_conn *conn = cmd->conn;
	काष्ठा iscsi_session *sess = शून्य;
	काष्ठा iscsi_node_attrib *na;

	iscsit_inc_conn_usage_count(conn);

	spin_lock_bh(&cmd->dataout_समयout_lock);
	अगर (cmd->dataout_समयr_flags & ISCSI_TF_STOP) अणु
		spin_unlock_bh(&cmd->dataout_समयout_lock);
		iscsit_dec_conn_usage_count(conn);
		वापस;
	पूर्ण
	cmd->dataout_समयr_flags &= ~ISCSI_TF_RUNNING;
	sess = conn->sess;
	na = iscsit_tpg_get_node_attrib(sess);

	अगर (!sess->sess_ops->ErrorRecoveryLevel) अणु
		pr_err("Unable to recover from DataOut timeout while"
			" in ERL=0, closing iSCSI connection for I_T Nexus"
			" %s,i,0x%6phN,%s,t,0x%02x\n",
			sess->sess_ops->InitiatorName, sess->isid,
			sess->tpg->tpg_tiqn->tiqn, (u32)sess->tpg->tpgt);
		जाओ failure;
	पूर्ण

	अगर (++cmd->dataout_समयout_retries == na->dataout_समयout_retries) अणु
		pr_err("Command ITT: 0x%08x exceeded max retries"
			" for DataOUT timeout %u, closing iSCSI connection for"
			" I_T Nexus %s,i,0x%6phN,%s,t,0x%02x\n",
			cmd->init_task_tag, na->dataout_समयout_retries,
			sess->sess_ops->InitiatorName, sess->isid,
			sess->tpg->tpg_tiqn->tiqn, (u32)sess->tpg->tpgt);
		जाओ failure;
	पूर्ण

	cmd->cmd_flags |= ICF_WITHIN_COMMAND_RECOVERY;

	अगर (conn->sess->sess_ops->DataSequenceInOrder) अणु
		अगर (conn->sess->sess_ops->DataPDUInOrder) अणु
			pdu_offset = cmd->ग_लिखो_data_करोne;
			अगर ((pdu_offset + (conn->sess->sess_ops->MaxBurstLength -
			     cmd->next_burst_len)) > cmd->se_cmd.data_length)
				pdu_length = (cmd->se_cmd.data_length -
					cmd->ग_लिखो_data_करोne);
			अन्यथा
				pdu_length = (conn->sess->sess_ops->MaxBurstLength -
						cmd->next_burst_len);
		पूर्ण अन्यथा अणु
			pdu_offset = cmd->seq_start_offset;
			pdu_length = (cmd->seq_end_offset -
				cmd->seq_start_offset);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (iscsit_set_dataout_समयout_values(cmd, &pdu_offset,
				&pdu_length) < 0)
			जाओ failure;
	पूर्ण

	अगर (iscsit_recalculate_dataout_values(cmd, pdu_offset, pdu_length,
			&r2t_offset, &r2t_length) < 0)
		जाओ failure;

	pr_debug("Command ITT: 0x%08x timed out waiting for"
		" completion of %sDataOUT Sequence Offset: %u, Length: %u\n",
		cmd->init_task_tag, (cmd->unsolicited_data) ? "Unsolicited " :
		"", r2t_offset, r2t_length);

	अगर (iscsit_send_recovery_r2t(cmd, r2t_offset, r2t_length) < 0)
		जाओ failure;

	iscsit_start_dataout_समयr(cmd, conn);
	spin_unlock_bh(&cmd->dataout_समयout_lock);
	iscsit_dec_conn_usage_count(conn);

	वापस;

failure:
	spin_unlock_bh(&cmd->dataout_समयout_lock);
	iscsit_fill_cxn_समयout_err_stats(sess);
	iscsit_cause_connection_reinstatement(conn, 0);
	iscsit_dec_conn_usage_count(conn);
पूर्ण

व्योम iscsit_mod_dataout_समयr(काष्ठा iscsi_cmd *cmd)
अणु
	काष्ठा iscsi_conn *conn = cmd->conn;
	काष्ठा iscsi_session *sess = conn->sess;
	काष्ठा iscsi_node_attrib *na = iscsit_tpg_get_node_attrib(sess);

	spin_lock_bh(&cmd->dataout_समयout_lock);
	अगर (!(cmd->dataout_समयr_flags & ISCSI_TF_RUNNING)) अणु
		spin_unlock_bh(&cmd->dataout_समयout_lock);
		वापस;
	पूर्ण

	mod_समयr(&cmd->dataout_समयr,
		(get_jअगरfies_64() + na->dataout_समयout * HZ));
	pr_debug("Updated DataOUT timer for ITT: 0x%08x",
			cmd->init_task_tag);
	spin_unlock_bh(&cmd->dataout_समयout_lock);
पूर्ण

व्योम iscsit_start_dataout_समयr(
	काष्ठा iscsi_cmd *cmd,
	काष्ठा iscsi_conn *conn)
अणु
	काष्ठा iscsi_session *sess = conn->sess;
	काष्ठा iscsi_node_attrib *na = iscsit_tpg_get_node_attrib(sess);

	lockdep_निश्चित_held(&cmd->dataout_समयout_lock);

	अगर (cmd->dataout_समयr_flags & ISCSI_TF_RUNNING)
		वापस;

	pr_debug("Starting DataOUT timer for ITT: 0x%08x on"
		" CID: %hu.\n", cmd->init_task_tag, conn->cid);

	cmd->dataout_समयr_flags &= ~ISCSI_TF_STOP;
	cmd->dataout_समयr_flags |= ISCSI_TF_RUNNING;
	mod_समयr(&cmd->dataout_समयr, jअगरfies + na->dataout_समयout * HZ);
पूर्ण

व्योम iscsit_stop_dataout_समयr(काष्ठा iscsi_cmd *cmd)
अणु
	spin_lock_bh(&cmd->dataout_समयout_lock);
	अगर (!(cmd->dataout_समयr_flags & ISCSI_TF_RUNNING)) अणु
		spin_unlock_bh(&cmd->dataout_समयout_lock);
		वापस;
	पूर्ण
	cmd->dataout_समयr_flags |= ISCSI_TF_STOP;
	spin_unlock_bh(&cmd->dataout_समयout_lock);

	del_समयr_sync(&cmd->dataout_समयr);

	spin_lock_bh(&cmd->dataout_समयout_lock);
	cmd->dataout_समयr_flags &= ~ISCSI_TF_RUNNING;
	pr_debug("Stopped DataOUT Timer for ITT: 0x%08x\n",
			cmd->init_task_tag);
	spin_unlock_bh(&cmd->dataout_समयout_lock);
पूर्ण
EXPORT_SYMBOL(iscsit_stop_dataout_समयr);
