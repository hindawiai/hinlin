<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*******************************************************************************
 * This file contains मुख्य functions related to iSCSI DataSequenceInOrder=No
 * and DataPDUInOrder=No.
 *
 * (c) Copyright 2007-2013 Datera, Inc.
 *
 * Author: Nicholas A. Bellinger <nab@linux-iscsi.org>
 *
 ******************************************************************************/

#समावेश <linux/slab.h>
#समावेश <linux/अक्रमom.h>

#समावेश <target/iscsi/iscsi_target_core.h>
#समावेश "iscsi_target_util.h"
#समावेश "iscsi_target_tpg.h"
#समावेश "iscsi_target_seq_pdu_list.h"

#अगर_घोषित DEBUG
अटल व्योम iscsit_dump_seq_list(काष्ठा iscsi_cmd *cmd)
अणु
	पूर्णांक i;
	काष्ठा iscsi_seq *seq;

	pr_debug("Dumping Sequence List for ITT: 0x%08x:\n",
			cmd->init_task_tag);

	क्रम (i = 0; i < cmd->seq_count; i++) अणु
		seq = &cmd->seq_list[i];
		pr_debug("i: %d, pdu_start: %d, pdu_count: %d,"
			" offset: %d, xfer_len: %d, seq_send_order: %d,"
			" seq_no: %d\n", i, seq->pdu_start, seq->pdu_count,
			seq->offset, seq->xfer_len, seq->seq_send_order,
			seq->seq_no);
	पूर्ण
पूर्ण

अटल व्योम iscsit_dump_pdu_list(काष्ठा iscsi_cmd *cmd)
अणु
	पूर्णांक i;
	काष्ठा iscsi_pdu *pdu;

	pr_debug("Dumping PDU List for ITT: 0x%08x:\n",
			cmd->init_task_tag);

	क्रम (i = 0; i < cmd->pdu_count; i++) अणु
		pdu = &cmd->pdu_list[i];
		pr_debug("i: %d, offset: %d, length: %d,"
			" pdu_send_order: %d, seq_no: %d\n", i, pdu->offset,
			pdu->length, pdu->pdu_send_order, pdu->seq_no);
	पूर्ण
पूर्ण
#अन्यथा
अटल व्योम iscsit_dump_seq_list(काष्ठा iscsi_cmd *cmd) अणुपूर्ण
अटल व्योम iscsit_dump_pdu_list(काष्ठा iscsi_cmd *cmd) अणुपूर्ण
#पूर्ण_अगर

अटल व्योम iscsit_ordered_seq_lists(
	काष्ठा iscsi_cmd *cmd,
	u8 type)
अणु
	u32 i, seq_count = 0;

	क्रम (i = 0; i < cmd->seq_count; i++) अणु
		अगर (cmd->seq_list[i].type != SEQTYPE_NORMAL)
			जारी;
		cmd->seq_list[i].seq_send_order = seq_count++;
	पूर्ण
पूर्ण

अटल व्योम iscsit_ordered_pdu_lists(
	काष्ठा iscsi_cmd *cmd,
	u8 type)
अणु
	u32 i, pdu_send_order = 0, seq_no = 0;

	क्रम (i = 0; i < cmd->pdu_count; i++) अणु
reकरो:
		अगर (cmd->pdu_list[i].seq_no == seq_no) अणु
			cmd->pdu_list[i].pdu_send_order = pdu_send_order++;
			जारी;
		पूर्ण
		seq_no++;
		pdu_send_order = 0;
		जाओ reकरो;
	पूर्ण
पूर्ण

/*
 *	Generate count अक्रमom values पूर्णांकo array.
 *	Use 0x80000000 to mark generates valued in array[].
 */
अटल व्योम iscsit_create_अक्रमom_array(u32 *array, u32 count)
अणु
	पूर्णांक i, j, k;

	अगर (count == 1) अणु
		array[0] = 0;
		वापस;
	पूर्ण

	क्रम (i = 0; i < count; i++) अणु
reकरो:
		get_अक्रमom_bytes(&j, माप(u32));
		j = (1 + (पूर्णांक) (9999 + 1) - j) % count;
		क्रम (k = 0; k < i + 1; k++) अणु
			j |= 0x80000000;
			अगर ((array[k] & 0x80000000) && (array[k] == j))
				जाओ reकरो;
		पूर्ण
		array[i] = j;
	पूर्ण

	क्रम (i = 0; i < count; i++)
		array[i] &= ~0x80000000;
पूर्ण

अटल पूर्णांक iscsit_अक्रमomize_pdu_lists(
	काष्ठा iscsi_cmd *cmd,
	u8 type)
अणु
	पूर्णांक i = 0;
	u32 *array, pdu_count, seq_count = 0, seq_no = 0, seq_offset = 0;

	क्रम (pdu_count = 0; pdu_count < cmd->pdu_count; pdu_count++) अणु
reकरो:
		अगर (cmd->pdu_list[pdu_count].seq_no == seq_no) अणु
			seq_count++;
			जारी;
		पूर्ण
		array = kसुस्मृति(seq_count, माप(u32), GFP_KERNEL);
		अगर (!array) अणु
			pr_err("Unable to allocate memory"
				" for random array.\n");
			वापस -ENOMEM;
		पूर्ण
		iscsit_create_अक्रमom_array(array, seq_count);

		क्रम (i = 0; i < seq_count; i++)
			cmd->pdu_list[seq_offset+i].pdu_send_order = array[i];

		kमुक्त(array);

		seq_offset += seq_count;
		seq_count = 0;
		seq_no++;
		जाओ reकरो;
	पूर्ण

	अगर (seq_count) अणु
		array = kसुस्मृति(seq_count, माप(u32), GFP_KERNEL);
		अगर (!array) अणु
			pr_err("Unable to allocate memory for"
				" random array.\n");
			वापस -ENOMEM;
		पूर्ण
		iscsit_create_अक्रमom_array(array, seq_count);

		क्रम (i = 0; i < seq_count; i++)
			cmd->pdu_list[seq_offset+i].pdu_send_order = array[i];

		kमुक्त(array);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक iscsit_अक्रमomize_seq_lists(
	काष्ठा iscsi_cmd *cmd,
	u8 type)
अणु
	पूर्णांक i, j = 0;
	u32 *array, seq_count = cmd->seq_count;

	अगर ((type == PDULIST_IMMEDIATE) || (type == PDULIST_UNSOLICITED))
		seq_count--;
	अन्यथा अगर (type == PDULIST_IMMEDIATE_AND_UNSOLICITED)
		seq_count -= 2;

	अगर (!seq_count)
		वापस 0;

	array = kसुस्मृति(seq_count, माप(u32), GFP_KERNEL);
	अगर (!array) अणु
		pr_err("Unable to allocate memory for random array.\n");
		वापस -ENOMEM;
	पूर्ण
	iscsit_create_अक्रमom_array(array, seq_count);

	क्रम (i = 0; i < cmd->seq_count; i++) अणु
		अगर (cmd->seq_list[i].type != SEQTYPE_NORMAL)
			जारी;
		cmd->seq_list[i].seq_send_order = array[j++];
	पूर्ण

	kमुक्त(array);
	वापस 0;
पूर्ण

अटल व्योम iscsit_determine_counts_क्रम_list(
	काष्ठा iscsi_cmd *cmd,
	काष्ठा iscsi_build_list *bl,
	u32 *seq_count,
	u32 *pdu_count)
अणु
	पूर्णांक check_immediate = 0;
	u32 burstlength = 0, offset = 0;
	u32 unsolicited_data_length = 0;
	u32 mdsl;
	काष्ठा iscsi_conn *conn = cmd->conn;

	अगर (cmd->se_cmd.data_direction == DMA_TO_DEVICE)
		mdsl = cmd->conn->conn_ops->MaxXmitDataSegmentLength;
	अन्यथा
		mdsl = cmd->conn->conn_ops->MaxRecvDataSegmentLength;

	अगर ((bl->type == PDULIST_IMMEDIATE) ||
	    (bl->type == PDULIST_IMMEDIATE_AND_UNSOLICITED))
		check_immediate = 1;

	अगर ((bl->type == PDULIST_UNSOLICITED) ||
	    (bl->type == PDULIST_IMMEDIATE_AND_UNSOLICITED))
		unsolicited_data_length = min(cmd->se_cmd.data_length,
			conn->sess->sess_ops->FirstBurstLength);

	जबतक (offset < cmd->se_cmd.data_length) अणु
		*pdu_count += 1;

		अगर (check_immediate) अणु
			check_immediate = 0;
			offset += bl->immediate_data_length;
			*seq_count += 1;
			अगर (unsolicited_data_length)
				unsolicited_data_length -=
					bl->immediate_data_length;
			जारी;
		पूर्ण
		अगर (unsolicited_data_length > 0) अणु
			अगर ((offset + mdsl) >= cmd->se_cmd.data_length) अणु
				unsolicited_data_length -=
					(cmd->se_cmd.data_length - offset);
				offset += (cmd->se_cmd.data_length - offset);
				जारी;
			पूर्ण
			अगर ((offset + mdsl)
					>= conn->sess->sess_ops->FirstBurstLength) अणु
				unsolicited_data_length -=
					(conn->sess->sess_ops->FirstBurstLength -
					offset);
				offset += (conn->sess->sess_ops->FirstBurstLength -
					offset);
				burstlength = 0;
				*seq_count += 1;
				जारी;
			पूर्ण

			offset += mdsl;
			unsolicited_data_length -= mdsl;
			जारी;
		पूर्ण
		अगर ((offset + mdsl) >= cmd->se_cmd.data_length) अणु
			offset += (cmd->se_cmd.data_length - offset);
			जारी;
		पूर्ण
		अगर ((burstlength + mdsl) >=
		     conn->sess->sess_ops->MaxBurstLength) अणु
			offset += (conn->sess->sess_ops->MaxBurstLength -
					burstlength);
			burstlength = 0;
			*seq_count += 1;
			जारी;
		पूर्ण

		burstlength += mdsl;
		offset += mdsl;
	पूर्ण
पूर्ण


/*
 *	Builds PDU and/or Sequence list, called जबतक DataSequenceInOrder=No
 *	or DataPDUInOrder=No.
 */
अटल पूर्णांक iscsit_करो_build_pdu_and_seq_lists(
	काष्ठा iscsi_cmd *cmd,
	काष्ठा iscsi_build_list *bl)
अणु
	पूर्णांक check_immediate = 0, datapduinorder, datasequenceinorder;
	u32 burstlength = 0, offset = 0, i = 0, mdsl;
	u32 pdu_count = 0, seq_no = 0, unsolicited_data_length = 0;
	काष्ठा iscsi_conn *conn = cmd->conn;
	काष्ठा iscsi_pdu *pdu = cmd->pdu_list;
	काष्ठा iscsi_seq *seq = cmd->seq_list;

	अगर (cmd->se_cmd.data_direction == DMA_TO_DEVICE)
		mdsl = cmd->conn->conn_ops->MaxXmitDataSegmentLength;
	अन्यथा
		mdsl = cmd->conn->conn_ops->MaxRecvDataSegmentLength;

	datapduinorder = conn->sess->sess_ops->DataPDUInOrder;
	datasequenceinorder = conn->sess->sess_ops->DataSequenceInOrder;

	अगर ((bl->type == PDULIST_IMMEDIATE) ||
	    (bl->type == PDULIST_IMMEDIATE_AND_UNSOLICITED))
		check_immediate = 1;

	अगर ((bl->type == PDULIST_UNSOLICITED) ||
	    (bl->type == PDULIST_IMMEDIATE_AND_UNSOLICITED))
		unsolicited_data_length = min(cmd->se_cmd.data_length,
			conn->sess->sess_ops->FirstBurstLength);

	जबतक (offset < cmd->se_cmd.data_length) अणु
		pdu_count++;
		अगर (!datapduinorder) अणु
			pdu[i].offset = offset;
			pdu[i].seq_no = seq_no;
		पूर्ण
		अगर (!datasequenceinorder && (pdu_count == 1)) अणु
			seq[seq_no].pdu_start = i;
			seq[seq_no].seq_no = seq_no;
			seq[seq_no].offset = offset;
			seq[seq_no].orig_offset = offset;
		पूर्ण

		अगर (check_immediate) अणु
			check_immediate = 0;
			अगर (!datapduinorder) अणु
				pdu[i].type = PDUTYPE_IMMEDIATE;
				pdu[i++].length = bl->immediate_data_length;
			पूर्ण
			अगर (!datasequenceinorder) अणु
				seq[seq_no].type = SEQTYPE_IMMEDIATE;
				seq[seq_no].pdu_count = 1;
				seq[seq_no].xfer_len =
					bl->immediate_data_length;
			पूर्ण
			offset += bl->immediate_data_length;
			pdu_count = 0;
			seq_no++;
			अगर (unsolicited_data_length)
				unsolicited_data_length -=
					bl->immediate_data_length;
			जारी;
		पूर्ण
		अगर (unsolicited_data_length > 0) अणु
			अगर ((offset + mdsl) >= cmd->se_cmd.data_length) अणु
				अगर (!datapduinorder) अणु
					pdu[i].type = PDUTYPE_UNSOLICITED;
					pdu[i].length =
						(cmd->se_cmd.data_length - offset);
				पूर्ण
				अगर (!datasequenceinorder) अणु
					seq[seq_no].type = SEQTYPE_UNSOLICITED;
					seq[seq_no].pdu_count = pdu_count;
					seq[seq_no].xfer_len = (burstlength +
						(cmd->se_cmd.data_length - offset));
				पूर्ण
				unsolicited_data_length -=
						(cmd->se_cmd.data_length - offset);
				offset += (cmd->se_cmd.data_length - offset);
				जारी;
			पूर्ण
			अगर ((offset + mdsl) >=
					conn->sess->sess_ops->FirstBurstLength) अणु
				अगर (!datapduinorder) अणु
					pdu[i].type = PDUTYPE_UNSOLICITED;
					pdu[i++].length =
					   (conn->sess->sess_ops->FirstBurstLength -
						offset);
				पूर्ण
				अगर (!datasequenceinorder) अणु
					seq[seq_no].type = SEQTYPE_UNSOLICITED;
					seq[seq_no].pdu_count = pdu_count;
					seq[seq_no].xfer_len = (burstlength +
					   (conn->sess->sess_ops->FirstBurstLength -
						offset));
				पूर्ण
				unsolicited_data_length -=
					(conn->sess->sess_ops->FirstBurstLength -
						offset);
				offset += (conn->sess->sess_ops->FirstBurstLength -
						offset);
				burstlength = 0;
				pdu_count = 0;
				seq_no++;
				जारी;
			पूर्ण

			अगर (!datapduinorder) अणु
				pdu[i].type = PDUTYPE_UNSOLICITED;
				pdu[i++].length = mdsl;
			पूर्ण
			burstlength += mdsl;
			offset += mdsl;
			unsolicited_data_length -= mdsl;
			जारी;
		पूर्ण
		अगर ((offset + mdsl) >= cmd->se_cmd.data_length) अणु
			अगर (!datapduinorder) अणु
				pdu[i].type = PDUTYPE_NORMAL;
				pdu[i].length = (cmd->se_cmd.data_length - offset);
			पूर्ण
			अगर (!datasequenceinorder) अणु
				seq[seq_no].type = SEQTYPE_NORMAL;
				seq[seq_no].pdu_count = pdu_count;
				seq[seq_no].xfer_len = (burstlength +
					(cmd->se_cmd.data_length - offset));
			पूर्ण
			offset += (cmd->se_cmd.data_length - offset);
			जारी;
		पूर्ण
		अगर ((burstlength + mdsl) >=
		     conn->sess->sess_ops->MaxBurstLength) अणु
			अगर (!datapduinorder) अणु
				pdu[i].type = PDUTYPE_NORMAL;
				pdu[i++].length =
					(conn->sess->sess_ops->MaxBurstLength -
						burstlength);
			पूर्ण
			अगर (!datasequenceinorder) अणु
				seq[seq_no].type = SEQTYPE_NORMAL;
				seq[seq_no].pdu_count = pdu_count;
				seq[seq_no].xfer_len = (burstlength +
					(conn->sess->sess_ops->MaxBurstLength -
					burstlength));
			पूर्ण
			offset += (conn->sess->sess_ops->MaxBurstLength -
					burstlength);
			burstlength = 0;
			pdu_count = 0;
			seq_no++;
			जारी;
		पूर्ण

		अगर (!datapduinorder) अणु
			pdu[i].type = PDUTYPE_NORMAL;
			pdu[i++].length = mdsl;
		पूर्ण
		burstlength += mdsl;
		offset += mdsl;
	पूर्ण

	अगर (!datasequenceinorder) अणु
		अगर (bl->data_direction & ISCSI_PDU_WRITE) अणु
			अगर (bl->अक्रमomize & RANDOM_R2T_OFFSETS) अणु
				अगर (iscsit_अक्रमomize_seq_lists(cmd, bl->type)
						< 0)
					वापस -1;
			पूर्ण अन्यथा
				iscsit_ordered_seq_lists(cmd, bl->type);
		पूर्ण अन्यथा अगर (bl->data_direction & ISCSI_PDU_READ) अणु
			अगर (bl->अक्रमomize & RANDOM_DATAIN_SEQ_OFFSETS) अणु
				अगर (iscsit_अक्रमomize_seq_lists(cmd, bl->type)
						< 0)
					वापस -1;
			पूर्ण अन्यथा
				iscsit_ordered_seq_lists(cmd, bl->type);
		पूर्ण

		iscsit_dump_seq_list(cmd);
	पूर्ण
	अगर (!datapduinorder) अणु
		अगर (bl->data_direction & ISCSI_PDU_WRITE) अणु
			अगर (bl->अक्रमomize & RANDOM_DATAOUT_PDU_OFFSETS) अणु
				अगर (iscsit_अक्रमomize_pdu_lists(cmd, bl->type)
						< 0)
					वापस -1;
			पूर्ण अन्यथा
				iscsit_ordered_pdu_lists(cmd, bl->type);
		पूर्ण अन्यथा अगर (bl->data_direction & ISCSI_PDU_READ) अणु
			अगर (bl->अक्रमomize & RANDOM_DATAIN_PDU_OFFSETS) अणु
				अगर (iscsit_अक्रमomize_pdu_lists(cmd, bl->type)
						< 0)
					वापस -1;
			पूर्ण अन्यथा
				iscsit_ordered_pdu_lists(cmd, bl->type);
		पूर्ण

		iscsit_dump_pdu_list(cmd);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक iscsit_build_pdu_and_seq_lists(
	काष्ठा iscsi_cmd *cmd,
	u32 immediate_data_length)
अणु
	काष्ठा iscsi_build_list bl;
	u32 pdu_count = 0, seq_count = 1;
	काष्ठा iscsi_conn *conn = cmd->conn;
	काष्ठा iscsi_pdu *pdu = शून्य;
	काष्ठा iscsi_seq *seq = शून्य;

	काष्ठा iscsi_session *sess = conn->sess;
	काष्ठा iscsi_node_attrib *na;

	/*
	 * Do nothing अगर no OOO shenanigans
	 */
	अगर (sess->sess_ops->DataSequenceInOrder &&
	    sess->sess_ops->DataPDUInOrder)
		वापस 0;

	अगर (cmd->data_direction == DMA_NONE)
		वापस 0;

	na = iscsit_tpg_get_node_attrib(sess);
	स_रखो(&bl, 0, माप(काष्ठा iscsi_build_list));

	अगर (cmd->data_direction == DMA_FROM_DEVICE) अणु
		bl.data_direction = ISCSI_PDU_READ;
		bl.type = PDULIST_NORMAL;
		अगर (na->अक्रमom_datain_pdu_offsets)
			bl.अक्रमomize |= RANDOM_DATAIN_PDU_OFFSETS;
		अगर (na->अक्रमom_datain_seq_offsets)
			bl.अक्रमomize |= RANDOM_DATAIN_SEQ_OFFSETS;
	पूर्ण अन्यथा अणु
		bl.data_direction = ISCSI_PDU_WRITE;
		bl.immediate_data_length = immediate_data_length;
		अगर (na->अक्रमom_r2t_offsets)
			bl.अक्रमomize |= RANDOM_R2T_OFFSETS;

		अगर (!cmd->immediate_data && !cmd->unsolicited_data)
			bl.type = PDULIST_NORMAL;
		अन्यथा अगर (cmd->immediate_data && !cmd->unsolicited_data)
			bl.type = PDULIST_IMMEDIATE;
		अन्यथा अगर (!cmd->immediate_data && cmd->unsolicited_data)
			bl.type = PDULIST_UNSOLICITED;
		अन्यथा अगर (cmd->immediate_data && cmd->unsolicited_data)
			bl.type = PDULIST_IMMEDIATE_AND_UNSOLICITED;
	पूर्ण

	iscsit_determine_counts_क्रम_list(cmd, &bl, &seq_count, &pdu_count);

	अगर (!conn->sess->sess_ops->DataSequenceInOrder) अणु
		seq = kसुस्मृति(seq_count, माप(काष्ठा iscsi_seq), GFP_ATOMIC);
		अगर (!seq) अणु
			pr_err("Unable to allocate struct iscsi_seq list\n");
			वापस -ENOMEM;
		पूर्ण
		cmd->seq_list = seq;
		cmd->seq_count = seq_count;
	पूर्ण

	अगर (!conn->sess->sess_ops->DataPDUInOrder) अणु
		pdu = kसुस्मृति(pdu_count, माप(काष्ठा iscsi_pdu), GFP_ATOMIC);
		अगर (!pdu) अणु
			pr_err("Unable to allocate struct iscsi_pdu list.\n");
			kमुक्त(seq);
			वापस -ENOMEM;
		पूर्ण
		cmd->pdu_list = pdu;
		cmd->pdu_count = pdu_count;
	पूर्ण

	वापस iscsit_करो_build_pdu_and_seq_lists(cmd, &bl);
पूर्ण

काष्ठा iscsi_pdu *iscsit_get_pdu_holder(
	काष्ठा iscsi_cmd *cmd,
	u32 offset,
	u32 length)
अणु
	u32 i;
	काष्ठा iscsi_pdu *pdu = शून्य;

	अगर (!cmd->pdu_list) अणु
		pr_err("struct iscsi_cmd->pdu_list is NULL!\n");
		वापस शून्य;
	पूर्ण

	pdu = &cmd->pdu_list[0];

	क्रम (i = 0; i < cmd->pdu_count; i++)
		अगर ((pdu[i].offset == offset) && (pdu[i].length == length))
			वापस &pdu[i];

	pr_err("Unable to locate PDU holder for ITT: 0x%08x, Offset:"
		" %u, Length: %u\n", cmd->init_task_tag, offset, length);
	वापस शून्य;
पूर्ण

काष्ठा iscsi_pdu *iscsit_get_pdu_holder_क्रम_seq(
	काष्ठा iscsi_cmd *cmd,
	काष्ठा iscsi_seq *seq)
अणु
	u32 i;
	काष्ठा iscsi_conn *conn = cmd->conn;
	काष्ठा iscsi_pdu *pdu = शून्य;

	अगर (!cmd->pdu_list) अणु
		pr_err("struct iscsi_cmd->pdu_list is NULL!\n");
		वापस शून्य;
	पूर्ण

	अगर (conn->sess->sess_ops->DataSequenceInOrder) अणु
reकरो:
		pdu = &cmd->pdu_list[cmd->pdu_start];

		क्रम (i = 0; pdu[i].seq_no != cmd->seq_no; i++) अणु
			pr_debug("pdu[i].seq_no: %d, pdu[i].pdu"
				"_send_order: %d, pdu[i].offset: %d,"
				" pdu[i].length: %d\n", pdu[i].seq_no,
				pdu[i].pdu_send_order, pdu[i].offset,
				pdu[i].length);

			अगर (pdu[i].pdu_send_order == cmd->pdu_send_order) अणु
				cmd->pdu_send_order++;
				वापस &pdu[i];
			पूर्ण
		पूर्ण

		cmd->pdu_start += cmd->pdu_send_order;
		cmd->pdu_send_order = 0;
		cmd->seq_no++;

		अगर (cmd->pdu_start < cmd->pdu_count)
			जाओ reकरो;

		pr_err("Command ITT: 0x%08x unable to locate"
			" struct iscsi_pdu for cmd->pdu_send_order: %u.\n",
			cmd->init_task_tag, cmd->pdu_send_order);
		वापस शून्य;
	पूर्ण अन्यथा अणु
		अगर (!seq) अणु
			pr_err("struct iscsi_seq is NULL!\n");
			वापस शून्य;
		पूर्ण

		pr_debug("seq->pdu_start: %d, seq->pdu_count: %d,"
			" seq->seq_no: %d\n", seq->pdu_start, seq->pdu_count,
			seq->seq_no);

		pdu = &cmd->pdu_list[seq->pdu_start];

		अगर (seq->pdu_send_order == seq->pdu_count) अणु
			pr_err("Command ITT: 0x%08x seq->pdu_send"
				"_order: %u equals seq->pdu_count: %u\n",
				cmd->init_task_tag, seq->pdu_send_order,
				seq->pdu_count);
			वापस शून्य;
		पूर्ण

		क्रम (i = 0; i < seq->pdu_count; i++) अणु
			अगर (pdu[i].pdu_send_order == seq->pdu_send_order) अणु
				seq->pdu_send_order++;
				वापस &pdu[i];
			पूर्ण
		पूर्ण

		pr_err("Command ITT: 0x%08x unable to locate iscsi"
			"_pdu_t for seq->pdu_send_order: %u.\n",
			cmd->init_task_tag, seq->pdu_send_order);
		वापस शून्य;
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा iscsi_seq *iscsit_get_seq_holder(
	काष्ठा iscsi_cmd *cmd,
	u32 offset,
	u32 length)
अणु
	u32 i;

	अगर (!cmd->seq_list) अणु
		pr_err("struct iscsi_cmd->seq_list is NULL!\n");
		वापस शून्य;
	पूर्ण

	क्रम (i = 0; i < cmd->seq_count; i++) अणु
		pr_debug("seq_list[i].orig_offset: %d, seq_list[i]."
			"xfer_len: %d, seq_list[i].seq_no %u\n",
			cmd->seq_list[i].orig_offset, cmd->seq_list[i].xfer_len,
			cmd->seq_list[i].seq_no);

		अगर ((cmd->seq_list[i].orig_offset +
				cmd->seq_list[i].xfer_len) >=
				(offset + length))
			वापस &cmd->seq_list[i];
	पूर्ण

	pr_err("Unable to locate Sequence holder for ITT: 0x%08x,"
		" Offset: %u, Length: %u\n", cmd->init_task_tag, offset,
		length);
	वापस शून्य;
पूर्ण
