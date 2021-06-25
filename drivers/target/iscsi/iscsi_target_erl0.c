<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/******************************************************************************
 * This file contains error recovery level zero functions used by
 * the iSCSI Target driver.
 *
 * (c) Copyright 2007-2013 Datera, Inc.
 *
 * Author: Nicholas A. Bellinger <nab@linux-iscsi.org>
 *
 ******************************************************************************/

#समावेश <linux/sched/संकेत.स>

#समावेश <scsi/iscsi_proto.h>
#समावेश <target/target_core_base.h>
#समावेश <target/target_core_fabric.h>

#समावेश <target/iscsi/iscsi_target_core.h>
#समावेश "iscsi_target_seq_pdu_list.h"
#समावेश "iscsi_target_erl0.h"
#समावेश "iscsi_target_erl1.h"
#समावेश "iscsi_target_erl2.h"
#समावेश "iscsi_target_util.h"
#समावेश "iscsi_target.h"

/*
 *	Used to set values in काष्ठा iscsi_cmd that iscsit_dataout_check_sequence()
 *	checks against to determine a PDU's Offset+Length is within the current
 *	DataOUT Sequence.  Used क्रम DataSequenceInOrder=Yes only.
 */
व्योम iscsit_set_dataout_sequence_values(
	काष्ठा iscsi_cmd *cmd)
अणु
	काष्ठा iscsi_conn *conn = cmd->conn;
	/*
	 * Still set seq_start_offset and seq_end_offset क्रम Unsolicited
	 * DataOUT, even अगर DataSequenceInOrder=No.
	 */
	अगर (cmd->unsolicited_data) अणु
		cmd->seq_start_offset = cmd->ग_लिखो_data_करोne;
		cmd->seq_end_offset = min(cmd->se_cmd.data_length,
					conn->sess->sess_ops->FirstBurstLength);
		वापस;
	पूर्ण

	अगर (!conn->sess->sess_ops->DataSequenceInOrder)
		वापस;

	अगर (!cmd->seq_start_offset && !cmd->seq_end_offset) अणु
		cmd->seq_start_offset = cmd->ग_लिखो_data_करोne;
		cmd->seq_end_offset = (cmd->se_cmd.data_length >
			conn->sess->sess_ops->MaxBurstLength) ?
			(cmd->ग_लिखो_data_करोne +
			conn->sess->sess_ops->MaxBurstLength) : cmd->se_cmd.data_length;
	पूर्ण अन्यथा अणु
		cmd->seq_start_offset = cmd->seq_end_offset;
		cmd->seq_end_offset = ((cmd->seq_end_offset +
			conn->sess->sess_ops->MaxBurstLength) >=
			cmd->se_cmd.data_length) ? cmd->se_cmd.data_length :
			(cmd->seq_end_offset +
			 conn->sess->sess_ops->MaxBurstLength);
	पूर्ण
पूर्ण

अटल पूर्णांक iscsit_dataout_within_command_recovery_check(
	काष्ठा iscsi_cmd *cmd,
	अचिन्हित अक्षर *buf)
अणु
	काष्ठा iscsi_conn *conn = cmd->conn;
	काष्ठा iscsi_data *hdr = (काष्ठा iscsi_data *) buf;
	u32 payload_length = ntoh24(hdr->dlength);

	/*
	 * We करो the within-command recovery checks here as it is
	 * the first function called in iscsi_check_pre_dataout().
	 * Basically, अगर we are in within-command recovery and
	 * the PDU करोes not contain the offset the sequence needs,
	 * dump the payload.
	 *
	 * This only applies to DataPDUInOrder=Yes, क्रम
	 * DataPDUInOrder=No we only re-request the failed PDU
	 * and check that all PDUs in a sequence are received
	 * upon end of sequence.
	 */
	अगर (conn->sess->sess_ops->DataSequenceInOrder) अणु
		अगर ((cmd->cmd_flags & ICF_WITHIN_COMMAND_RECOVERY) &&
		    cmd->ग_लिखो_data_करोne != be32_to_cpu(hdr->offset))
			जाओ dump;

		cmd->cmd_flags &= ~ICF_WITHIN_COMMAND_RECOVERY;
	पूर्ण अन्यथा अणु
		काष्ठा iscsi_seq *seq;

		seq = iscsit_get_seq_holder(cmd, be32_to_cpu(hdr->offset),
					    payload_length);
		अगर (!seq)
			वापस DATAOUT_CANNOT_RECOVER;
		/*
		 * Set the काष्ठा iscsi_seq poपूर्णांकer to reuse later.
		 */
		cmd->seq_ptr = seq;

		अगर (conn->sess->sess_ops->DataPDUInOrder) अणु
			अगर (seq->status ==
			    DATAOUT_SEQUENCE_WITHIN_COMMAND_RECOVERY &&
			   (seq->offset != be32_to_cpu(hdr->offset) ||
			    seq->data_sn != be32_to_cpu(hdr->datasn)))
				जाओ dump;
		पूर्ण अन्यथा अणु
			अगर (seq->status ==
			     DATAOUT_SEQUENCE_WITHIN_COMMAND_RECOVERY &&
			    seq->data_sn != be32_to_cpu(hdr->datasn))
				जाओ dump;
		पूर्ण

		अगर (seq->status == DATAOUT_SEQUENCE_COMPLETE)
			जाओ dump;

		अगर (seq->status != DATAOUT_SEQUENCE_COMPLETE)
			seq->status = 0;
	पूर्ण

	वापस DATAOUT_NORMAL;

dump:
	pr_err("Dumping DataOUT PDU Offset: %u Length: %d DataSN:"
		" 0x%08x\n", hdr->offset, payload_length, hdr->datasn);
	वापस iscsit_dump_data_payload(conn, payload_length, 1);
पूर्ण

अटल पूर्णांक iscsit_dataout_check_unsolicited_sequence(
	काष्ठा iscsi_cmd *cmd,
	अचिन्हित अक्षर *buf)
अणु
	u32 first_burst_len;
	काष्ठा iscsi_conn *conn = cmd->conn;
	काष्ठा iscsi_data *hdr = (काष्ठा iscsi_data *) buf;
	u32 payload_length = ntoh24(hdr->dlength);


	अगर ((be32_to_cpu(hdr->offset) < cmd->seq_start_offset) ||
	   ((be32_to_cpu(hdr->offset) + payload_length) > cmd->seq_end_offset)) अणु
		pr_err("Command ITT: 0x%08x with Offset: %u,"
		" Length: %u outside of Unsolicited Sequence %u:%u while"
		" DataSequenceInOrder=Yes.\n", cmd->init_task_tag,
		be32_to_cpu(hdr->offset), payload_length, cmd->seq_start_offset,
			cmd->seq_end_offset);
		वापस DATAOUT_CANNOT_RECOVER;
	पूर्ण

	first_burst_len = (cmd->first_burst_len + payload_length);

	अगर (first_burst_len > conn->sess->sess_ops->FirstBurstLength) अणु
		pr_err("Total %u bytes exceeds FirstBurstLength: %u"
			" for this Unsolicited DataOut Burst.\n",
			first_burst_len, conn->sess->sess_ops->FirstBurstLength);
		transport_send_check_condition_and_sense(&cmd->se_cmd,
				TCM_INCORRECT_AMOUNT_OF_DATA, 0);
		वापस DATAOUT_CANNOT_RECOVER;
	पूर्ण

	/*
	 * Perक्रमm various MaxBurstLength and ISCSI_FLAG_CMD_FINAL sanity
	 * checks क्रम the current Unsolicited DataOUT Sequence.
	 */
	अगर (hdr->flags & ISCSI_FLAG_CMD_FINAL) अणु
		/*
		 * Ignore ISCSI_FLAG_CMD_FINAL checks जबतक DataPDUInOrder=No, end of
		 * sequence checks are handled in
		 * iscsit_dataout_datapduinorder_no_fbit().
		 */
		अगर (!conn->sess->sess_ops->DataPDUInOrder)
			जाओ out;

		अगर ((first_burst_len != cmd->se_cmd.data_length) &&
		    (first_burst_len != conn->sess->sess_ops->FirstBurstLength)) अणु
			pr_err("Unsolicited non-immediate data"
			" received %u does not equal FirstBurstLength: %u, and"
			" does not equal ExpXferLen %u.\n", first_burst_len,
				conn->sess->sess_ops->FirstBurstLength,
				cmd->se_cmd.data_length);
			transport_send_check_condition_and_sense(&cmd->se_cmd,
					TCM_INCORRECT_AMOUNT_OF_DATA, 0);
			वापस DATAOUT_CANNOT_RECOVER;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (first_burst_len == conn->sess->sess_ops->FirstBurstLength) अणु
			pr_err("Command ITT: 0x%08x reached"
			" FirstBurstLength: %u, but ISCSI_FLAG_CMD_FINAL is not set. protocol"
				" error.\n", cmd->init_task_tag,
				conn->sess->sess_ops->FirstBurstLength);
			वापस DATAOUT_CANNOT_RECOVER;
		पूर्ण
		अगर (first_burst_len == cmd->se_cmd.data_length) अणु
			pr_err("Command ITT: 0x%08x reached"
			" ExpXferLen: %u, but ISCSI_FLAG_CMD_FINAL is not set. protocol"
			" error.\n", cmd->init_task_tag, cmd->se_cmd.data_length);
			वापस DATAOUT_CANNOT_RECOVER;
		पूर्ण
	पूर्ण

out:
	वापस DATAOUT_NORMAL;
पूर्ण

अटल पूर्णांक iscsit_dataout_check_sequence(
	काष्ठा iscsi_cmd *cmd,
	अचिन्हित अक्षर *buf)
अणु
	u32 next_burst_len;
	काष्ठा iscsi_conn *conn = cmd->conn;
	काष्ठा iscsi_seq *seq = शून्य;
	काष्ठा iscsi_data *hdr = (काष्ठा iscsi_data *) buf;
	u32 payload_length = ntoh24(hdr->dlength);

	/*
	 * For DataSequenceInOrder=Yes: Check that the offset and offset+length
	 * is within range as defined by iscsi_set_dataout_sequence_values().
	 *
	 * For DataSequenceInOrder=No: Check that an काष्ठा iscsi_seq exists क्रम
	 * offset+length tuple.
	 */
	अगर (conn->sess->sess_ops->DataSequenceInOrder) अणु
		/*
		 * Due to possibility of recovery DataOUT sent by the initiator
		 * fullfilling an Recovery R2T, it's best to just dump the
		 * payload here, instead of erroring out.
		 */
		अगर ((be32_to_cpu(hdr->offset) < cmd->seq_start_offset) ||
		   ((be32_to_cpu(hdr->offset) + payload_length) > cmd->seq_end_offset)) अणु
			pr_err("Command ITT: 0x%08x with Offset: %u,"
			" Length: %u outside of Sequence %u:%u while"
			" DataSequenceInOrder=Yes.\n", cmd->init_task_tag,
			be32_to_cpu(hdr->offset), payload_length, cmd->seq_start_offset,
				cmd->seq_end_offset);

			अगर (iscsit_dump_data_payload(conn, payload_length, 1) < 0)
				वापस DATAOUT_CANNOT_RECOVER;
			वापस DATAOUT_WITHIN_COMMAND_RECOVERY;
		पूर्ण

		next_burst_len = (cmd->next_burst_len + payload_length);
	पूर्ण अन्यथा अणु
		seq = iscsit_get_seq_holder(cmd, be32_to_cpu(hdr->offset),
					    payload_length);
		अगर (!seq)
			वापस DATAOUT_CANNOT_RECOVER;
		/*
		 * Set the काष्ठा iscsi_seq poपूर्णांकer to reuse later.
		 */
		cmd->seq_ptr = seq;

		अगर (seq->status == DATAOUT_SEQUENCE_COMPLETE) अणु
			अगर (iscsit_dump_data_payload(conn, payload_length, 1) < 0)
				वापस DATAOUT_CANNOT_RECOVER;
			वापस DATAOUT_WITHIN_COMMAND_RECOVERY;
		पूर्ण

		next_burst_len = (seq->next_burst_len + payload_length);
	पूर्ण

	अगर (next_burst_len > conn->sess->sess_ops->MaxBurstLength) अणु
		pr_err("Command ITT: 0x%08x, NextBurstLength: %u and"
			" Length: %u exceeds MaxBurstLength: %u. protocol"
			" error.\n", cmd->init_task_tag,
			(next_burst_len - payload_length),
			payload_length, conn->sess->sess_ops->MaxBurstLength);
		वापस DATAOUT_CANNOT_RECOVER;
	पूर्ण

	/*
	 * Perक्रमm various MaxBurstLength and ISCSI_FLAG_CMD_FINAL sanity
	 * checks क्रम the current DataOUT Sequence.
	 */
	अगर (hdr->flags & ISCSI_FLAG_CMD_FINAL) अणु
		/*
		 * Ignore ISCSI_FLAG_CMD_FINAL checks जबतक DataPDUInOrder=No, end of
		 * sequence checks are handled in
		 * iscsit_dataout_datapduinorder_no_fbit().
		 */
		अगर (!conn->sess->sess_ops->DataPDUInOrder)
			जाओ out;

		अगर (conn->sess->sess_ops->DataSequenceInOrder) अणु
			अगर ((next_burst_len <
			     conn->sess->sess_ops->MaxBurstLength) &&
			   ((cmd->ग_लिखो_data_करोne + payload_length) <
			     cmd->se_cmd.data_length)) अणु
				pr_err("Command ITT: 0x%08x set ISCSI_FLAG_CMD_FINAL"
				" before end of DataOUT sequence, protocol"
				" error.\n", cmd->init_task_tag);
				वापस DATAOUT_CANNOT_RECOVER;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (next_burst_len < seq->xfer_len) अणु
				pr_err("Command ITT: 0x%08x set ISCSI_FLAG_CMD_FINAL"
				" before end of DataOUT sequence, protocol"
				" error.\n", cmd->init_task_tag);
				वापस DATAOUT_CANNOT_RECOVER;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (conn->sess->sess_ops->DataSequenceInOrder) अणु
			अगर (next_burst_len ==
					conn->sess->sess_ops->MaxBurstLength) अणु
				pr_err("Command ITT: 0x%08x reached"
				" MaxBurstLength: %u, but ISCSI_FLAG_CMD_FINAL is"
				" not set, protocol error.", cmd->init_task_tag,
					conn->sess->sess_ops->MaxBurstLength);
				वापस DATAOUT_CANNOT_RECOVER;
			पूर्ण
			अगर ((cmd->ग_लिखो_data_करोne + payload_length) ==
					cmd->se_cmd.data_length) अणु
				pr_err("Command ITT: 0x%08x reached"
				" last DataOUT PDU in sequence but ISCSI_FLAG_"
				"CMD_FINAL is not set, protocol error.\n",
					cmd->init_task_tag);
				वापस DATAOUT_CANNOT_RECOVER;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (next_burst_len == seq->xfer_len) अणु
				pr_err("Command ITT: 0x%08x reached"
				" last DataOUT PDU in sequence but ISCSI_FLAG_"
				"CMD_FINAL is not set, protocol error.\n",
					cmd->init_task_tag);
				वापस DATAOUT_CANNOT_RECOVER;
			पूर्ण
		पूर्ण
	पूर्ण

out:
	वापस DATAOUT_NORMAL;
पूर्ण

अटल पूर्णांक iscsit_dataout_check_datasn(
	काष्ठा iscsi_cmd *cmd,
	अचिन्हित अक्षर *buf)
अणु
	u32 data_sn = 0;
	काष्ठा iscsi_conn *conn = cmd->conn;
	काष्ठा iscsi_data *hdr = (काष्ठा iscsi_data *) buf;
	u32 payload_length = ntoh24(hdr->dlength);

	/*
	 * Considering the target has no method of re-requesting DataOUT
	 * by DataSN, अगर we receieve a greater DataSN than expected we
	 * assume the functions क्रम DataPDUInOrder=[Yes,No] below will
	 * handle it.
	 *
	 * If the DataSN is less than expected, dump the payload.
	 */
	अगर (conn->sess->sess_ops->DataSequenceInOrder)
		data_sn = cmd->data_sn;
	अन्यथा अणु
		काष्ठा iscsi_seq *seq = cmd->seq_ptr;
		data_sn = seq->data_sn;
	पूर्ण

	अगर (be32_to_cpu(hdr->datasn) > data_sn) अणु
		pr_err("Command ITT: 0x%08x, received DataSN: 0x%08x"
			" higher than expected 0x%08x.\n", cmd->init_task_tag,
				be32_to_cpu(hdr->datasn), data_sn);
		जाओ recover;
	पूर्ण अन्यथा अगर (be32_to_cpu(hdr->datasn) < data_sn) अणु
		pr_err("Command ITT: 0x%08x, received DataSN: 0x%08x"
			" lower than expected 0x%08x, discarding payload.\n",
			cmd->init_task_tag, be32_to_cpu(hdr->datasn), data_sn);
		जाओ dump;
	पूर्ण

	वापस DATAOUT_NORMAL;

recover:
	अगर (!conn->sess->sess_ops->ErrorRecoveryLevel) अणु
		pr_err("Unable to perform within-command recovery"
				" while ERL=0.\n");
		वापस DATAOUT_CANNOT_RECOVER;
	पूर्ण
dump:
	अगर (iscsit_dump_data_payload(conn, payload_length, 1) < 0)
		वापस DATAOUT_CANNOT_RECOVER;

	वापस DATAOUT_WITHIN_COMMAND_RECOVERY;
पूर्ण

अटल पूर्णांक iscsit_dataout_pre_datapduinorder_yes(
	काष्ठा iscsi_cmd *cmd,
	अचिन्हित अक्षर *buf)
अणु
	पूर्णांक dump = 0, recovery = 0;
	काष्ठा iscsi_conn *conn = cmd->conn;
	काष्ठा iscsi_data *hdr = (काष्ठा iscsi_data *) buf;
	u32 payload_length = ntoh24(hdr->dlength);

	/*
	 * For DataSequenceInOrder=Yes: If the offset is greater than the global
	 * DataPDUInOrder=Yes offset counter in काष्ठा iscsi_cmd a protcol error has
	 * occurred and fail the connection.
	 *
	 * For DataSequenceInOrder=No: If the offset is greater than the per
	 * sequence DataPDUInOrder=Yes offset counter in काष्ठा iscsi_seq a protocol
	 * error has occurred and fail the connection.
	 */
	अगर (conn->sess->sess_ops->DataSequenceInOrder) अणु
		अगर (be32_to_cpu(hdr->offset) != cmd->ग_लिखो_data_करोne) अणु
			pr_err("Command ITT: 0x%08x, received offset"
			" %u different than expected %u.\n", cmd->init_task_tag,
				be32_to_cpu(hdr->offset), cmd->ग_लिखो_data_करोne);
			recovery = 1;
			जाओ recover;
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा iscsi_seq *seq = cmd->seq_ptr;

		अगर (be32_to_cpu(hdr->offset) > seq->offset) अणु
			pr_err("Command ITT: 0x%08x, received offset"
			" %u greater than expected %u.\n", cmd->init_task_tag,
				be32_to_cpu(hdr->offset), seq->offset);
			recovery = 1;
			जाओ recover;
		पूर्ण अन्यथा अगर (be32_to_cpu(hdr->offset) < seq->offset) अणु
			pr_err("Command ITT: 0x%08x, received offset"
			" %u less than expected %u, discarding payload.\n",
				cmd->init_task_tag, be32_to_cpu(hdr->offset),
				seq->offset);
			dump = 1;
			जाओ dump;
		पूर्ण
	पूर्ण

	वापस DATAOUT_NORMAL;

recover:
	अगर (!conn->sess->sess_ops->ErrorRecoveryLevel) अणु
		pr_err("Unable to perform within-command recovery"
				" while ERL=0.\n");
		वापस DATAOUT_CANNOT_RECOVER;
	पूर्ण
dump:
	अगर (iscsit_dump_data_payload(conn, payload_length, 1) < 0)
		वापस DATAOUT_CANNOT_RECOVER;

	वापस (recovery) ? iscsit_recover_dataout_sequence(cmd,
		be32_to_cpu(hdr->offset), payload_length) :
	       (dump) ? DATAOUT_WITHIN_COMMAND_RECOVERY : DATAOUT_NORMAL;
पूर्ण

अटल पूर्णांक iscsit_dataout_pre_datapduinorder_no(
	काष्ठा iscsi_cmd *cmd,
	अचिन्हित अक्षर *buf)
अणु
	काष्ठा iscsi_pdu *pdu;
	काष्ठा iscsi_data *hdr = (काष्ठा iscsi_data *) buf;
	u32 payload_length = ntoh24(hdr->dlength);

	pdu = iscsit_get_pdu_holder(cmd, be32_to_cpu(hdr->offset),
				    payload_length);
	अगर (!pdu)
		वापस DATAOUT_CANNOT_RECOVER;

	cmd->pdu_ptr = pdu;

	चयन (pdu->status) अणु
	हाल ISCSI_PDU_NOT_RECEIVED:
	हाल ISCSI_PDU_CRC_FAILED:
	हाल ISCSI_PDU_TIMED_OUT:
		अवरोध;
	हाल ISCSI_PDU_RECEIVED_OK:
		pr_err("Command ITT: 0x%08x received already gotten"
			" Offset: %u, Length: %u\n", cmd->init_task_tag,
				be32_to_cpu(hdr->offset), payload_length);
		वापस iscsit_dump_data_payload(cmd->conn, payload_length, 1);
	शेष:
		वापस DATAOUT_CANNOT_RECOVER;
	पूर्ण

	वापस DATAOUT_NORMAL;
पूर्ण

अटल पूर्णांक iscsit_dataout_update_r2t(काष्ठा iscsi_cmd *cmd, u32 offset, u32 length)
अणु
	काष्ठा iscsi_r2t *r2t;

	अगर (cmd->unsolicited_data)
		वापस 0;

	r2t = iscsit_get_r2t_क्रम_eos(cmd, offset, length);
	अगर (!r2t)
		वापस -1;

	spin_lock_bh(&cmd->r2t_lock);
	r2t->seq_complete = 1;
	cmd->outstanding_r2ts--;
	spin_unlock_bh(&cmd->r2t_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक iscsit_dataout_update_datapduinorder_no(
	काष्ठा iscsi_cmd *cmd,
	u32 data_sn,
	पूर्णांक f_bit)
अणु
	पूर्णांक ret = 0;
	काष्ठा iscsi_pdu *pdu = cmd->pdu_ptr;

	pdu->data_sn = data_sn;

	चयन (pdu->status) अणु
	हाल ISCSI_PDU_NOT_RECEIVED:
		pdu->status = ISCSI_PDU_RECEIVED_OK;
		अवरोध;
	हाल ISCSI_PDU_CRC_FAILED:
		pdu->status = ISCSI_PDU_RECEIVED_OK;
		अवरोध;
	हाल ISCSI_PDU_TIMED_OUT:
		pdu->status = ISCSI_PDU_RECEIVED_OK;
		अवरोध;
	शेष:
		वापस DATAOUT_CANNOT_RECOVER;
	पूर्ण

	अगर (f_bit) अणु
		ret = iscsit_dataout_datapduinorder_no_fbit(cmd, pdu);
		अगर (ret == DATAOUT_CANNOT_RECOVER)
			वापस ret;
	पूर्ण

	वापस DATAOUT_NORMAL;
पूर्ण

अटल पूर्णांक iscsit_dataout_post_crc_passed(
	काष्ठा iscsi_cmd *cmd,
	अचिन्हित अक्षर *buf)
अणु
	पूर्णांक ret, send_r2t = 0;
	काष्ठा iscsi_conn *conn = cmd->conn;
	काष्ठा iscsi_seq *seq = शून्य;
	काष्ठा iscsi_data *hdr = (काष्ठा iscsi_data *) buf;
	u32 payload_length = ntoh24(hdr->dlength);

	अगर (cmd->unsolicited_data) अणु
		अगर ((cmd->first_burst_len + payload_length) ==
		     conn->sess->sess_ops->FirstBurstLength) अणु
			अगर (iscsit_dataout_update_r2t(cmd, be32_to_cpu(hdr->offset),
					payload_length) < 0)
				वापस DATAOUT_CANNOT_RECOVER;
			send_r2t = 1;
		पूर्ण

		अगर (!conn->sess->sess_ops->DataPDUInOrder) अणु
			ret = iscsit_dataout_update_datapduinorder_no(cmd,
				be32_to_cpu(hdr->datasn),
				(hdr->flags & ISCSI_FLAG_CMD_FINAL));
			अगर (ret == DATAOUT_CANNOT_RECOVER)
				वापस ret;
		पूर्ण

		cmd->first_burst_len += payload_length;

		अगर (conn->sess->sess_ops->DataSequenceInOrder)
			cmd->data_sn++;
		अन्यथा अणु
			seq = cmd->seq_ptr;
			seq->data_sn++;
			seq->offset += payload_length;
		पूर्ण

		अगर (send_r2t) अणु
			अगर (seq)
				seq->status = DATAOUT_SEQUENCE_COMPLETE;
			cmd->first_burst_len = 0;
			cmd->unsolicited_data = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (conn->sess->sess_ops->DataSequenceInOrder) अणु
			अगर ((cmd->next_burst_len + payload_length) ==
			     conn->sess->sess_ops->MaxBurstLength) अणु
				अगर (iscsit_dataout_update_r2t(cmd,
						be32_to_cpu(hdr->offset),
						payload_length) < 0)
					वापस DATAOUT_CANNOT_RECOVER;
				send_r2t = 1;
			पूर्ण

			अगर (!conn->sess->sess_ops->DataPDUInOrder) अणु
				ret = iscsit_dataout_update_datapduinorder_no(
						cmd, be32_to_cpu(hdr->datasn),
						(hdr->flags & ISCSI_FLAG_CMD_FINAL));
				अगर (ret == DATAOUT_CANNOT_RECOVER)
					वापस ret;
			पूर्ण

			cmd->next_burst_len += payload_length;
			cmd->data_sn++;

			अगर (send_r2t)
				cmd->next_burst_len = 0;
		पूर्ण अन्यथा अणु
			seq = cmd->seq_ptr;

			अगर ((seq->next_burst_len + payload_length) ==
			     seq->xfer_len) अणु
				अगर (iscsit_dataout_update_r2t(cmd,
						be32_to_cpu(hdr->offset),
						payload_length) < 0)
					वापस DATAOUT_CANNOT_RECOVER;
				send_r2t = 1;
			पूर्ण

			अगर (!conn->sess->sess_ops->DataPDUInOrder) अणु
				ret = iscsit_dataout_update_datapduinorder_no(
						cmd, be32_to_cpu(hdr->datasn),
						(hdr->flags & ISCSI_FLAG_CMD_FINAL));
				अगर (ret == DATAOUT_CANNOT_RECOVER)
					वापस ret;
			पूर्ण

			seq->data_sn++;
			seq->offset += payload_length;
			seq->next_burst_len += payload_length;

			अगर (send_r2t) अणु
				seq->next_burst_len = 0;
				seq->status = DATAOUT_SEQUENCE_COMPLETE;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (send_r2t && conn->sess->sess_ops->DataSequenceInOrder)
		cmd->data_sn = 0;

	cmd->ग_लिखो_data_करोne += payload_length;

	अगर (cmd->ग_लिखो_data_करोne == cmd->se_cmd.data_length)
		वापस DATAOUT_SEND_TO_TRANSPORT;
	अन्यथा अगर (send_r2t)
		वापस DATAOUT_SEND_R2T;
	अन्यथा
		वापस DATAOUT_NORMAL;
पूर्ण

अटल पूर्णांक iscsit_dataout_post_crc_failed(
	काष्ठा iscsi_cmd *cmd,
	अचिन्हित अक्षर *buf)
अणु
	काष्ठा iscsi_conn *conn = cmd->conn;
	काष्ठा iscsi_pdu *pdu;
	काष्ठा iscsi_data *hdr = (काष्ठा iscsi_data *) buf;
	u32 payload_length = ntoh24(hdr->dlength);

	अगर (conn->sess->sess_ops->DataPDUInOrder)
		जाओ recover;
	/*
	 * The rest of this function is only called when DataPDUInOrder=No.
	 */
	pdu = cmd->pdu_ptr;

	चयन (pdu->status) अणु
	हाल ISCSI_PDU_NOT_RECEIVED:
		pdu->status = ISCSI_PDU_CRC_FAILED;
		अवरोध;
	हाल ISCSI_PDU_CRC_FAILED:
		अवरोध;
	हाल ISCSI_PDU_TIMED_OUT:
		pdu->status = ISCSI_PDU_CRC_FAILED;
		अवरोध;
	शेष:
		वापस DATAOUT_CANNOT_RECOVER;
	पूर्ण

recover:
	वापस iscsit_recover_dataout_sequence(cmd, be32_to_cpu(hdr->offset),
						payload_length);
पूर्ण

/*
 *	Called from iscsit_handle_data_out() beक्रमe DataOUT Payload is received
 *	and CRC computed.
 */
पूर्णांक iscsit_check_pre_dataout(
	काष्ठा iscsi_cmd *cmd,
	अचिन्हित अक्षर *buf)
अणु
	पूर्णांक ret;
	काष्ठा iscsi_conn *conn = cmd->conn;

	ret = iscsit_dataout_within_command_recovery_check(cmd, buf);
	अगर ((ret == DATAOUT_WITHIN_COMMAND_RECOVERY) ||
	    (ret == DATAOUT_CANNOT_RECOVER))
		वापस ret;

	ret = iscsit_dataout_check_datasn(cmd, buf);
	अगर ((ret == DATAOUT_WITHIN_COMMAND_RECOVERY) ||
	    (ret == DATAOUT_CANNOT_RECOVER))
		वापस ret;

	अगर (cmd->unsolicited_data) अणु
		ret = iscsit_dataout_check_unsolicited_sequence(cmd, buf);
		अगर ((ret == DATAOUT_WITHIN_COMMAND_RECOVERY) ||
		    (ret == DATAOUT_CANNOT_RECOVER))
			वापस ret;
	पूर्ण अन्यथा अणु
		ret = iscsit_dataout_check_sequence(cmd, buf);
		अगर ((ret == DATAOUT_WITHIN_COMMAND_RECOVERY) ||
		    (ret == DATAOUT_CANNOT_RECOVER))
			वापस ret;
	पूर्ण

	वापस (conn->sess->sess_ops->DataPDUInOrder) ?
		iscsit_dataout_pre_datapduinorder_yes(cmd, buf) :
		iscsit_dataout_pre_datapduinorder_no(cmd, buf);
पूर्ण

/*
 *	Called from iscsit_handle_data_out() after DataOUT Payload is received
 *	and CRC computed.
 */
पूर्णांक iscsit_check_post_dataout(
	काष्ठा iscsi_cmd *cmd,
	अचिन्हित अक्षर *buf,
	u8 data_crc_failed)
अणु
	काष्ठा iscsi_conn *conn = cmd->conn;

	cmd->dataout_समयout_retries = 0;

	अगर (!data_crc_failed)
		वापस iscsit_dataout_post_crc_passed(cmd, buf);
	अन्यथा अणु
		अगर (!conn->sess->sess_ops->ErrorRecoveryLevel) अणु
			pr_err("Unable to recover from DataOUT CRC"
				" failure while ERL=0, closing session.\n");
			iscsit_reject_cmd(cmd, ISCSI_REASON_DATA_DIGEST_ERROR,
					  buf);
			वापस DATAOUT_CANNOT_RECOVER;
		पूर्ण

		iscsit_reject_cmd(cmd, ISCSI_REASON_DATA_DIGEST_ERROR, buf);
		वापस iscsit_dataout_post_crc_failed(cmd, buf);
	पूर्ण
पूर्ण

व्योम iscsit_handle_समय2retain_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा iscsi_session *sess = from_समयr(sess, t, समय2retain_समयr);
	काष्ठा iscsi_portal_group *tpg = sess->tpg;
	काष्ठा se_portal_group *se_tpg = &tpg->tpg_se_tpg;

	spin_lock_bh(&se_tpg->session_lock);
	अगर (sess->समय2retain_समयr_flags & ISCSI_TF_STOP) अणु
		spin_unlock_bh(&se_tpg->session_lock);
		वापस;
	पूर्ण
	अगर (atomic_पढ़ो(&sess->session_reinstatement)) अणु
		pr_err("Exiting Time2Retain handler because"
				" session_reinstatement=1\n");
		spin_unlock_bh(&se_tpg->session_lock);
		वापस;
	पूर्ण
	sess->समय2retain_समयr_flags |= ISCSI_TF_EXPIRED;

	pr_err("Time2Retain timer expired for SID: %u, cleaning up"
			" iSCSI session.\n", sess->sid);

	iscsit_fill_cxn_समयout_err_stats(sess);
	spin_unlock_bh(&se_tpg->session_lock);
	iscsit_बंद_session(sess, false);
पूर्ण

व्योम iscsit_start_समय2retain_handler(काष्ठा iscsi_session *sess)
अणु
	पूर्णांक tpg_active;
	/*
	 * Only start Time2Retain समयr when the associated TPG is still in
	 * an ACTIVE (eg: not disabled or shutकरोwn) state.
	 */
	spin_lock(&sess->tpg->tpg_state_lock);
	tpg_active = (sess->tpg->tpg_state == TPG_STATE_ACTIVE);
	spin_unlock(&sess->tpg->tpg_state_lock);

	अगर (!tpg_active)
		वापस;

	अगर (sess->समय2retain_समयr_flags & ISCSI_TF_RUNNING)
		वापस;

	pr_debug("Starting Time2Retain timer for %u seconds on"
		" SID: %u\n", sess->sess_ops->DefaultTime2Retain, sess->sid);

	sess->समय2retain_समयr_flags &= ~ISCSI_TF_STOP;
	sess->समय2retain_समयr_flags |= ISCSI_TF_RUNNING;
	mod_समयr(&sess->समय2retain_समयr,
		  jअगरfies + sess->sess_ops->DefaultTime2Retain * HZ);
पूर्ण

पूर्णांक iscsit_stop_समय2retain_समयr(काष्ठा iscsi_session *sess)
अणु
	काष्ठा iscsi_portal_group *tpg = sess->tpg;
	काष्ठा se_portal_group *se_tpg = &tpg->tpg_se_tpg;

	lockdep_निश्चित_held(&se_tpg->session_lock);

	अगर (sess->समय2retain_समयr_flags & ISCSI_TF_EXPIRED)
		वापस -1;

	अगर (!(sess->समय2retain_समयr_flags & ISCSI_TF_RUNNING))
		वापस 0;

	sess->समय2retain_समयr_flags |= ISCSI_TF_STOP;
	spin_unlock(&se_tpg->session_lock);

	del_समयr_sync(&sess->समय2retain_समयr);

	spin_lock(&se_tpg->session_lock);
	sess->समय2retain_समयr_flags &= ~ISCSI_TF_RUNNING;
	pr_debug("Stopped Time2Retain Timer for SID: %u\n",
			sess->sid);
	वापस 0;
पूर्ण

व्योम iscsit_connection_reinstatement_rcfr(काष्ठा iscsi_conn *conn)
अणु
	spin_lock_bh(&conn->state_lock);
	अगर (atomic_पढ़ो(&conn->connection_निकास)) अणु
		spin_unlock_bh(&conn->state_lock);
		जाओ sleep;
	पूर्ण

	अगर (atomic_पढ़ो(&conn->transport_failed)) अणु
		spin_unlock_bh(&conn->state_lock);
		जाओ sleep;
	पूर्ण
	spin_unlock_bh(&conn->state_lock);

	अगर (conn->tx_thपढ़ो && conn->tx_thपढ़ो_active)
		send_sig(संक_विघ्न, conn->tx_thपढ़ो, 1);
	अगर (conn->rx_thपढ़ो && conn->rx_thपढ़ो_active)
		send_sig(संक_विघ्न, conn->rx_thपढ़ो, 1);

sleep:
	रुको_क्रम_completion(&conn->conn_रुको_rcfr_comp);
	complete(&conn->conn_post_रुको_comp);
पूर्ण

व्योम iscsit_cause_connection_reinstatement(काष्ठा iscsi_conn *conn, पूर्णांक sleep)
अणु
	spin_lock_bh(&conn->state_lock);
	अगर (atomic_पढ़ो(&conn->connection_निकास)) अणु
		spin_unlock_bh(&conn->state_lock);
		वापस;
	पूर्ण

	अगर (atomic_पढ़ो(&conn->transport_failed)) अणु
		spin_unlock_bh(&conn->state_lock);
		वापस;
	पूर्ण

	अगर (atomic_पढ़ो(&conn->connection_reinstatement)) अणु
		spin_unlock_bh(&conn->state_lock);
		वापस;
	पूर्ण

	अगर (conn->tx_thपढ़ो && conn->tx_thपढ़ो_active)
		send_sig(संक_विघ्न, conn->tx_thपढ़ो, 1);
	अगर (conn->rx_thपढ़ो && conn->rx_thपढ़ो_active)
		send_sig(संक_विघ्न, conn->rx_thपढ़ो, 1);

	atomic_set(&conn->connection_reinstatement, 1);
	अगर (!sleep) अणु
		spin_unlock_bh(&conn->state_lock);
		वापस;
	पूर्ण

	atomic_set(&conn->sleep_on_conn_रुको_comp, 1);
	spin_unlock_bh(&conn->state_lock);

	रुको_क्रम_completion(&conn->conn_रुको_comp);
	complete(&conn->conn_post_रुको_comp);
पूर्ण
EXPORT_SYMBOL(iscsit_cause_connection_reinstatement);

व्योम iscsit_fall_back_to_erl0(काष्ठा iscsi_session *sess)
अणु
	pr_debug("Falling back to ErrorRecoveryLevel=0 for SID:"
			" %u\n", sess->sid);

	atomic_set(&sess->session_fall_back_to_erl0, 1);
पूर्ण

अटल व्योम iscsit_handle_connection_cleanup(काष्ठा iscsi_conn *conn)
अणु
	काष्ठा iscsi_session *sess = conn->sess;

	अगर ((sess->sess_ops->ErrorRecoveryLevel == 2) &&
	    !atomic_पढ़ो(&sess->session_reinstatement) &&
	    !atomic_पढ़ो(&sess->session_fall_back_to_erl0))
		iscsit_connection_recovery_transport_reset(conn);
	अन्यथा अणु
		pr_debug("Performing cleanup for failed iSCSI"
			" Connection ID: %hu from %s\n", conn->cid,
			sess->sess_ops->InitiatorName);
		iscsit_बंद_connection(conn);
	पूर्ण
पूर्ण

व्योम iscsit_take_action_क्रम_connection_निकास(काष्ठा iscsi_conn *conn, bool *conn_मुक्तd)
अणु
	*conn_मुक्तd = false;

	spin_lock_bh(&conn->state_lock);
	अगर (atomic_पढ़ो(&conn->connection_निकास)) अणु
		spin_unlock_bh(&conn->state_lock);
		वापस;
	पूर्ण
	atomic_set(&conn->connection_निकास, 1);

	अगर (conn->conn_state == TARG_CONN_STATE_IN_LOGOUT) अणु
		spin_unlock_bh(&conn->state_lock);
		iscsit_बंद_connection(conn);
		*conn_मुक्तd = true;
		वापस;
	पूर्ण

	अगर (conn->conn_state == TARG_CONN_STATE_CLEANUP_WAIT) अणु
		spin_unlock_bh(&conn->state_lock);
		वापस;
	पूर्ण

	pr_debug("Moving to TARG_CONN_STATE_CLEANUP_WAIT.\n");
	conn->conn_state = TARG_CONN_STATE_CLEANUP_WAIT;
	spin_unlock_bh(&conn->state_lock);

	iscsit_handle_connection_cleanup(conn);
	*conn_मुक्तd = true;
पूर्ण
