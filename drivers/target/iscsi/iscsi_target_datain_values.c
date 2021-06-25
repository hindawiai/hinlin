<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*******************************************************************************
 * This file contains the iSCSI Target DataIN value generation functions.
 *
 * (c) Copyright 2007-2013 Datera, Inc.
 *
 * Author: Nicholas A. Bellinger <nab@linux-iscsi.org>
 *
 ******************************************************************************/

#समावेश <linux/slab.h>
#समावेश <scsi/iscsi_proto.h>
#समावेश <target/iscsi/iscsi_target_core.h>
#समावेश "iscsi_target_seq_pdu_list.h"
#समावेश "iscsi_target_erl1.h"
#समावेश "iscsi_target_util.h"
#समावेश "iscsi_target.h"
#समावेश "iscsi_target_datain_values.h"

काष्ठा iscsi_datain_req *iscsit_allocate_datain_req(व्योम)
अणु
	काष्ठा iscsi_datain_req *dr;

	dr = kmem_cache_zalloc(lio_dr_cache, GFP_ATOMIC);
	अगर (!dr) अणु
		pr_err("Unable to allocate memory for"
				" struct iscsi_datain_req\n");
		वापस शून्य;
	पूर्ण
	INIT_LIST_HEAD(&dr->cmd_datain_node);

	वापस dr;
पूर्ण

व्योम iscsit_attach_datain_req(काष्ठा iscsi_cmd *cmd, काष्ठा iscsi_datain_req *dr)
अणु
	spin_lock(&cmd->datain_lock);
	list_add_tail(&dr->cmd_datain_node, &cmd->datain_list);
	spin_unlock(&cmd->datain_lock);
पूर्ण

व्योम iscsit_मुक्त_datain_req(काष्ठा iscsi_cmd *cmd, काष्ठा iscsi_datain_req *dr)
अणु
	spin_lock(&cmd->datain_lock);
	list_del(&dr->cmd_datain_node);
	spin_unlock(&cmd->datain_lock);

	kmem_cache_मुक्त(lio_dr_cache, dr);
पूर्ण

व्योम iscsit_मुक्त_all_datain_reqs(काष्ठा iscsi_cmd *cmd)
अणु
	काष्ठा iscsi_datain_req *dr, *dr_पंचांगp;

	spin_lock(&cmd->datain_lock);
	list_क्रम_each_entry_safe(dr, dr_पंचांगp, &cmd->datain_list, cmd_datain_node) अणु
		list_del(&dr->cmd_datain_node);
		kmem_cache_मुक्त(lio_dr_cache, dr);
	पूर्ण
	spin_unlock(&cmd->datain_lock);
पूर्ण

काष्ठा iscsi_datain_req *iscsit_get_datain_req(काष्ठा iscsi_cmd *cmd)
अणु
	अगर (list_empty(&cmd->datain_list)) अणु
		pr_err("cmd->datain_list is empty for ITT:"
			" 0x%08x\n", cmd->init_task_tag);
		वापस शून्य;
	पूर्ण

	वापस list_first_entry(&cmd->datain_list, काष्ठा iscsi_datain_req,
				cmd_datain_node);
पूर्ण

/*
 *	For Normal and Recovery DataSequenceInOrder=Yes and DataPDUInOrder=Yes.
 */
अटल काष्ठा iscsi_datain_req *iscsit_set_datain_values_yes_and_yes(
	काष्ठा iscsi_cmd *cmd,
	काष्ठा iscsi_datain *datain)
अणु
	u32 next_burst_len, पढ़ो_data_करोne, पढ़ो_data_left;
	काष्ठा iscsi_conn *conn = cmd->conn;
	काष्ठा iscsi_datain_req *dr;

	dr = iscsit_get_datain_req(cmd);
	अगर (!dr)
		वापस शून्य;

	अगर (dr->recovery && dr->generate_recovery_values) अणु
		अगर (iscsit_create_recovery_datain_values_datasequenceinorder_yes(
					cmd, dr) < 0)
			वापस शून्य;

		dr->generate_recovery_values = 0;
	पूर्ण

	next_burst_len = (!dr->recovery) ?
			cmd->next_burst_len : dr->next_burst_len;
	पढ़ो_data_करोne = (!dr->recovery) ?
			cmd->पढ़ो_data_करोne : dr->पढ़ो_data_करोne;

	पढ़ो_data_left = (cmd->se_cmd.data_length - पढ़ो_data_करोne);
	अगर (!पढ़ो_data_left) अणु
		pr_err("ITT: 0x%08x read_data_left is zero!\n",
				cmd->init_task_tag);
		वापस शून्य;
	पूर्ण

	अगर ((पढ़ो_data_left <= conn->conn_ops->MaxRecvDataSegmentLength) &&
	    (पढ़ो_data_left <= (conn->sess->sess_ops->MaxBurstLength -
	     next_burst_len))) अणु
		datain->length = पढ़ो_data_left;

		datain->flags |= (ISCSI_FLAG_CMD_FINAL | ISCSI_FLAG_DATA_STATUS);
		अगर (conn->sess->sess_ops->ErrorRecoveryLevel > 0)
			datain->flags |= ISCSI_FLAG_DATA_ACK;
	पूर्ण अन्यथा अणु
		अगर ((next_burst_len +
		     conn->conn_ops->MaxRecvDataSegmentLength) <
		     conn->sess->sess_ops->MaxBurstLength) अणु
			datain->length =
				conn->conn_ops->MaxRecvDataSegmentLength;
			next_burst_len += datain->length;
		पूर्ण अन्यथा अणु
			datain->length = (conn->sess->sess_ops->MaxBurstLength -
					  next_burst_len);
			next_burst_len = 0;

			datain->flags |= ISCSI_FLAG_CMD_FINAL;
			अगर (conn->sess->sess_ops->ErrorRecoveryLevel > 0)
				datain->flags |= ISCSI_FLAG_DATA_ACK;
		पूर्ण
	पूर्ण

	datain->data_sn = (!dr->recovery) ? cmd->data_sn++ : dr->data_sn++;
	datain->offset = पढ़ो_data_करोne;

	अगर (!dr->recovery) अणु
		cmd->next_burst_len = next_burst_len;
		cmd->पढ़ो_data_करोne += datain->length;
	पूर्ण अन्यथा अणु
		dr->next_burst_len = next_burst_len;
		dr->पढ़ो_data_करोne += datain->length;
	पूर्ण

	अगर (!dr->recovery) अणु
		अगर (datain->flags & ISCSI_FLAG_DATA_STATUS)
			dr->dr_complete = DATAIN_COMPLETE_NORMAL;

		वापस dr;
	पूर्ण

	अगर (!dr->runlength) अणु
		अगर (datain->flags & ISCSI_FLAG_DATA_STATUS) अणु
			dr->dr_complete =
			    (dr->recovery == DATAIN_WITHIN_COMMAND_RECOVERY) ?
				DATAIN_COMPLETE_WITHIN_COMMAND_RECOVERY :
				DATAIN_COMPLETE_CONNECTION_RECOVERY;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((dr->begrun + dr->runlength) == dr->data_sn) अणु
			dr->dr_complete =
			    (dr->recovery == DATAIN_WITHIN_COMMAND_RECOVERY) ?
				DATAIN_COMPLETE_WITHIN_COMMAND_RECOVERY :
				DATAIN_COMPLETE_CONNECTION_RECOVERY;
		पूर्ण
	पूर्ण

	वापस dr;
पूर्ण

/*
 *	For Normal and Recovery DataSequenceInOrder=No and DataPDUInOrder=Yes.
 */
अटल काष्ठा iscsi_datain_req *iscsit_set_datain_values_no_and_yes(
	काष्ठा iscsi_cmd *cmd,
	काष्ठा iscsi_datain *datain)
अणु
	u32 offset, पढ़ो_data_करोne, पढ़ो_data_left, seq_send_order;
	काष्ठा iscsi_conn *conn = cmd->conn;
	काष्ठा iscsi_datain_req *dr;
	काष्ठा iscsi_seq *seq;

	dr = iscsit_get_datain_req(cmd);
	अगर (!dr)
		वापस शून्य;

	अगर (dr->recovery && dr->generate_recovery_values) अणु
		अगर (iscsit_create_recovery_datain_values_datasequenceinorder_no(
					cmd, dr) < 0)
			वापस शून्य;

		dr->generate_recovery_values = 0;
	पूर्ण

	पढ़ो_data_करोne = (!dr->recovery) ?
			cmd->पढ़ो_data_करोne : dr->पढ़ो_data_करोne;
	seq_send_order = (!dr->recovery) ?
			cmd->seq_send_order : dr->seq_send_order;

	पढ़ो_data_left = (cmd->se_cmd.data_length - पढ़ो_data_करोne);
	अगर (!पढ़ो_data_left) अणु
		pr_err("ITT: 0x%08x read_data_left is zero!\n",
				cmd->init_task_tag);
		वापस शून्य;
	पूर्ण

	seq = iscsit_get_seq_holder_क्रम_datain(cmd, seq_send_order);
	अगर (!seq)
		वापस शून्य;

	seq->sent = 1;

	अगर (!dr->recovery && !seq->next_burst_len)
		seq->first_datasn = cmd->data_sn;

	offset = (seq->offset + seq->next_burst_len);

	अगर ((offset + conn->conn_ops->MaxRecvDataSegmentLength) >=
	     cmd->se_cmd.data_length) अणु
		datain->length = (cmd->se_cmd.data_length - offset);
		datain->offset = offset;

		datain->flags |= ISCSI_FLAG_CMD_FINAL;
		अगर (conn->sess->sess_ops->ErrorRecoveryLevel > 0)
			datain->flags |= ISCSI_FLAG_DATA_ACK;

		seq->next_burst_len = 0;
		seq_send_order++;
	पूर्ण अन्यथा अणु
		अगर ((seq->next_burst_len +
		     conn->conn_ops->MaxRecvDataSegmentLength) <
		     conn->sess->sess_ops->MaxBurstLength) अणु
			datain->length =
				conn->conn_ops->MaxRecvDataSegmentLength;
			datain->offset = (seq->offset + seq->next_burst_len);

			seq->next_burst_len += datain->length;
		पूर्ण अन्यथा अणु
			datain->length = (conn->sess->sess_ops->MaxBurstLength -
					  seq->next_burst_len);
			datain->offset = (seq->offset + seq->next_burst_len);

			datain->flags |= ISCSI_FLAG_CMD_FINAL;
			अगर (conn->sess->sess_ops->ErrorRecoveryLevel > 0)
				datain->flags |= ISCSI_FLAG_DATA_ACK;

			seq->next_burst_len = 0;
			seq_send_order++;
		पूर्ण
	पूर्ण

	अगर ((पढ़ो_data_करोne + datain->length) == cmd->se_cmd.data_length)
		datain->flags |= ISCSI_FLAG_DATA_STATUS;

	datain->data_sn = (!dr->recovery) ? cmd->data_sn++ : dr->data_sn++;
	अगर (!dr->recovery) अणु
		cmd->seq_send_order = seq_send_order;
		cmd->पढ़ो_data_करोne += datain->length;
	पूर्ण अन्यथा अणु
		dr->seq_send_order = seq_send_order;
		dr->पढ़ो_data_करोne += datain->length;
	पूर्ण

	अगर (!dr->recovery) अणु
		अगर (datain->flags & ISCSI_FLAG_CMD_FINAL)
			seq->last_datasn = datain->data_sn;
		अगर (datain->flags & ISCSI_FLAG_DATA_STATUS)
			dr->dr_complete = DATAIN_COMPLETE_NORMAL;

		वापस dr;
	पूर्ण

	अगर (!dr->runlength) अणु
		अगर (datain->flags & ISCSI_FLAG_DATA_STATUS) अणु
			dr->dr_complete =
			    (dr->recovery == DATAIN_WITHIN_COMMAND_RECOVERY) ?
				DATAIN_COMPLETE_WITHIN_COMMAND_RECOVERY :
				DATAIN_COMPLETE_CONNECTION_RECOVERY;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((dr->begrun + dr->runlength) == dr->data_sn) अणु
			dr->dr_complete =
			    (dr->recovery == DATAIN_WITHIN_COMMAND_RECOVERY) ?
				DATAIN_COMPLETE_WITHIN_COMMAND_RECOVERY :
				DATAIN_COMPLETE_CONNECTION_RECOVERY;
		पूर्ण
	पूर्ण

	वापस dr;
पूर्ण

/*
 *	For Normal and Recovery DataSequenceInOrder=Yes and DataPDUInOrder=No.
 */
अटल काष्ठा iscsi_datain_req *iscsit_set_datain_values_yes_and_no(
	काष्ठा iscsi_cmd *cmd,
	काष्ठा iscsi_datain *datain)
अणु
	u32 next_burst_len, पढ़ो_data_करोne, पढ़ो_data_left;
	काष्ठा iscsi_conn *conn = cmd->conn;
	काष्ठा iscsi_datain_req *dr;
	काष्ठा iscsi_pdu *pdu;

	dr = iscsit_get_datain_req(cmd);
	अगर (!dr)
		वापस शून्य;

	अगर (dr->recovery && dr->generate_recovery_values) अणु
		अगर (iscsit_create_recovery_datain_values_datasequenceinorder_yes(
					cmd, dr) < 0)
			वापस शून्य;

		dr->generate_recovery_values = 0;
	पूर्ण

	next_burst_len = (!dr->recovery) ?
			cmd->next_burst_len : dr->next_burst_len;
	पढ़ो_data_करोne = (!dr->recovery) ?
			cmd->पढ़ो_data_करोne : dr->पढ़ो_data_करोne;

	पढ़ो_data_left = (cmd->se_cmd.data_length - पढ़ो_data_करोne);
	अगर (!पढ़ो_data_left) अणु
		pr_err("ITT: 0x%08x read_data_left is zero!\n",
				cmd->init_task_tag);
		वापस dr;
	पूर्ण

	pdu = iscsit_get_pdu_holder_क्रम_seq(cmd, शून्य);
	अगर (!pdu)
		वापस dr;

	अगर ((पढ़ो_data_करोne + pdu->length) == cmd->se_cmd.data_length) अणु
		pdu->flags |= (ISCSI_FLAG_CMD_FINAL | ISCSI_FLAG_DATA_STATUS);
		अगर (conn->sess->sess_ops->ErrorRecoveryLevel > 0)
			pdu->flags |= ISCSI_FLAG_DATA_ACK;

		next_burst_len = 0;
	पूर्ण अन्यथा अणु
		अगर ((next_burst_len + conn->conn_ops->MaxRecvDataSegmentLength) <
		     conn->sess->sess_ops->MaxBurstLength)
			next_burst_len += pdu->length;
		अन्यथा अणु
			pdu->flags |= ISCSI_FLAG_CMD_FINAL;
			अगर (conn->sess->sess_ops->ErrorRecoveryLevel > 0)
				pdu->flags |= ISCSI_FLAG_DATA_ACK;

			next_burst_len = 0;
		पूर्ण
	पूर्ण

	pdu->data_sn = (!dr->recovery) ? cmd->data_sn++ : dr->data_sn++;
	अगर (!dr->recovery) अणु
		cmd->next_burst_len = next_burst_len;
		cmd->पढ़ो_data_करोne += pdu->length;
	पूर्ण अन्यथा अणु
		dr->next_burst_len = next_burst_len;
		dr->पढ़ो_data_करोne += pdu->length;
	पूर्ण

	datain->flags = pdu->flags;
	datain->length = pdu->length;
	datain->offset = pdu->offset;
	datain->data_sn = pdu->data_sn;

	अगर (!dr->recovery) अणु
		अगर (datain->flags & ISCSI_FLAG_DATA_STATUS)
			dr->dr_complete = DATAIN_COMPLETE_NORMAL;

		वापस dr;
	पूर्ण

	अगर (!dr->runlength) अणु
		अगर (datain->flags & ISCSI_FLAG_DATA_STATUS) अणु
			dr->dr_complete =
			    (dr->recovery == DATAIN_WITHIN_COMMAND_RECOVERY) ?
				DATAIN_COMPLETE_WITHIN_COMMAND_RECOVERY :
				DATAIN_COMPLETE_CONNECTION_RECOVERY;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((dr->begrun + dr->runlength) == dr->data_sn) अणु
			dr->dr_complete =
			    (dr->recovery == DATAIN_WITHIN_COMMAND_RECOVERY) ?
				DATAIN_COMPLETE_WITHIN_COMMAND_RECOVERY :
				DATAIN_COMPLETE_CONNECTION_RECOVERY;
		पूर्ण
	पूर्ण

	वापस dr;
पूर्ण

/*
 *	For Normal and Recovery DataSequenceInOrder=No and DataPDUInOrder=No.
 */
अटल काष्ठा iscsi_datain_req *iscsit_set_datain_values_no_and_no(
	काष्ठा iscsi_cmd *cmd,
	काष्ठा iscsi_datain *datain)
अणु
	u32 पढ़ो_data_करोne, पढ़ो_data_left, seq_send_order;
	काष्ठा iscsi_conn *conn = cmd->conn;
	काष्ठा iscsi_datain_req *dr;
	काष्ठा iscsi_pdu *pdu;
	काष्ठा iscsi_seq *seq = शून्य;

	dr = iscsit_get_datain_req(cmd);
	अगर (!dr)
		वापस शून्य;

	अगर (dr->recovery && dr->generate_recovery_values) अणु
		अगर (iscsit_create_recovery_datain_values_datasequenceinorder_no(
					cmd, dr) < 0)
			वापस शून्य;

		dr->generate_recovery_values = 0;
	पूर्ण

	पढ़ो_data_करोne = (!dr->recovery) ?
			cmd->पढ़ो_data_करोne : dr->पढ़ो_data_करोne;
	seq_send_order = (!dr->recovery) ?
			cmd->seq_send_order : dr->seq_send_order;

	पढ़ो_data_left = (cmd->se_cmd.data_length - पढ़ो_data_करोne);
	अगर (!पढ़ो_data_left) अणु
		pr_err("ITT: 0x%08x read_data_left is zero!\n",
				cmd->init_task_tag);
		वापस शून्य;
	पूर्ण

	seq = iscsit_get_seq_holder_क्रम_datain(cmd, seq_send_order);
	अगर (!seq)
		वापस शून्य;

	seq->sent = 1;

	अगर (!dr->recovery && !seq->next_burst_len)
		seq->first_datasn = cmd->data_sn;

	pdu = iscsit_get_pdu_holder_क्रम_seq(cmd, seq);
	अगर (!pdu)
		वापस शून्य;

	अगर (seq->pdu_send_order == seq->pdu_count) अणु
		pdu->flags |= ISCSI_FLAG_CMD_FINAL;
		अगर (conn->sess->sess_ops->ErrorRecoveryLevel > 0)
			pdu->flags |= ISCSI_FLAG_DATA_ACK;

		seq->next_burst_len = 0;
		seq_send_order++;
	पूर्ण अन्यथा
		seq->next_burst_len += pdu->length;

	अगर ((पढ़ो_data_करोne + pdu->length) == cmd->se_cmd.data_length)
		pdu->flags |= ISCSI_FLAG_DATA_STATUS;

	pdu->data_sn = (!dr->recovery) ? cmd->data_sn++ : dr->data_sn++;
	अगर (!dr->recovery) अणु
		cmd->seq_send_order = seq_send_order;
		cmd->पढ़ो_data_करोne += pdu->length;
	पूर्ण अन्यथा अणु
		dr->seq_send_order = seq_send_order;
		dr->पढ़ो_data_करोne += pdu->length;
	पूर्ण

	datain->flags = pdu->flags;
	datain->length = pdu->length;
	datain->offset = pdu->offset;
	datain->data_sn = pdu->data_sn;

	अगर (!dr->recovery) अणु
		अगर (datain->flags & ISCSI_FLAG_CMD_FINAL)
			seq->last_datasn = datain->data_sn;
		अगर (datain->flags & ISCSI_FLAG_DATA_STATUS)
			dr->dr_complete = DATAIN_COMPLETE_NORMAL;

		वापस dr;
	पूर्ण

	अगर (!dr->runlength) अणु
		अगर (datain->flags & ISCSI_FLAG_DATA_STATUS) अणु
			dr->dr_complete =
			    (dr->recovery == DATAIN_WITHIN_COMMAND_RECOVERY) ?
				DATAIN_COMPLETE_WITHIN_COMMAND_RECOVERY :
				DATAIN_COMPLETE_CONNECTION_RECOVERY;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((dr->begrun + dr->runlength) == dr->data_sn) अणु
			dr->dr_complete =
			    (dr->recovery == DATAIN_WITHIN_COMMAND_RECOVERY) ?
				DATAIN_COMPLETE_WITHIN_COMMAND_RECOVERY :
				DATAIN_COMPLETE_CONNECTION_RECOVERY;
		पूर्ण
	पूर्ण

	वापस dr;
पूर्ण

काष्ठा iscsi_datain_req *iscsit_get_datain_values(
	काष्ठा iscsi_cmd *cmd,
	काष्ठा iscsi_datain *datain)
अणु
	काष्ठा iscsi_conn *conn = cmd->conn;

	अगर (conn->sess->sess_ops->DataSequenceInOrder &&
	    conn->sess->sess_ops->DataPDUInOrder)
		वापस iscsit_set_datain_values_yes_and_yes(cmd, datain);
	अन्यथा अगर (!conn->sess->sess_ops->DataSequenceInOrder &&
		  conn->sess->sess_ops->DataPDUInOrder)
		वापस iscsit_set_datain_values_no_and_yes(cmd, datain);
	अन्यथा अगर (conn->sess->sess_ops->DataSequenceInOrder &&
		 !conn->sess->sess_ops->DataPDUInOrder)
		वापस iscsit_set_datain_values_yes_and_no(cmd, datain);
	अन्यथा अगर (!conn->sess->sess_ops->DataSequenceInOrder &&
		   !conn->sess->sess_ops->DataPDUInOrder)
		वापस iscsit_set_datain_values_no_and_no(cmd, datain);

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(iscsit_get_datain_values);
