<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ISCSI_SEQ_AND_PDU_LIST_H
#घोषणा ISCSI_SEQ_AND_PDU_LIST_H

#समावेश <linux/types.h>
#समावेश <linux/cache.h>

/* काष्ठा iscsi_pdu->status */
#घोषणा DATAOUT_PDU_SENT			1

/* काष्ठा iscsi_seq->type */
#घोषणा SEQTYPE_IMMEDIATE			1
#घोषणा SEQTYPE_UNSOLICITED			2
#घोषणा SEQTYPE_NORMAL				3

/* काष्ठा iscsi_seq->status */
#घोषणा DATAOUT_SEQUENCE_GOT_R2T		1
#घोषणा DATAOUT_SEQUENCE_WITHIN_COMMAND_RECOVERY 2
#घोषणा DATAOUT_SEQUENCE_COMPLETE		3

/* iscsi_determine_counts_क्रम_list() type */
#घोषणा PDULIST_NORMAL				1
#घोषणा PDULIST_IMMEDIATE			2
#घोषणा PDULIST_UNSOLICITED			3
#घोषणा PDULIST_IMMEDIATE_AND_UNSOLICITED	4

/* काष्ठा iscsi_pdu->type */
#घोषणा PDUTYPE_IMMEDIATE			1
#घोषणा PDUTYPE_UNSOLICITED			2
#घोषणा PDUTYPE_NORMAL				3

/* काष्ठा iscsi_pdu->status */
#घोषणा ISCSI_PDU_NOT_RECEIVED			0
#घोषणा ISCSI_PDU_RECEIVED_OK			1
#घोषणा ISCSI_PDU_CRC_FAILED			2
#घोषणा ISCSI_PDU_TIMED_OUT			3

/* काष्ठा iscsi_build_list->अक्रमomize */
#घोषणा RANDOM_DATAIN_PDU_OFFSETS		0x01
#घोषणा RANDOM_DATAIN_SEQ_OFFSETS		0x02
#घोषणा RANDOM_DATAOUT_PDU_OFFSETS		0x04
#घोषणा RANDOM_R2T_OFFSETS			0x08

/* काष्ठा iscsi_build_list->data_direction */
#घोषणा ISCSI_PDU_READ				0x01
#घोषणा ISCSI_PDU_WRITE				0x02

काष्ठा iscsi_build_list अणु
	पूर्णांक		data_direction;
	पूर्णांक		अक्रमomize;
	पूर्णांक		type;
	पूर्णांक		immediate_data_length;
पूर्ण;

काष्ठा iscsi_pdu अणु
	पूर्णांक		status;
	पूर्णांक		type;
	u8		flags;
	u32		data_sn;
	u32		length;
	u32		offset;
	u32		pdu_send_order;
	u32		seq_no;
पूर्ण ____cacheline_aligned;

काष्ठा iscsi_seq अणु
	पूर्णांक		sent;
	पूर्णांक		status;
	पूर्णांक		type;
	u32		data_sn;
	u32		first_datasn;
	u32		last_datasn;
	u32		next_burst_len;
	u32		pdu_start;
	u32		pdu_count;
	u32		offset;
	u32		orig_offset;
	u32		pdu_send_order;
	u32		r2t_sn;
	u32		seq_send_order;
	u32		seq_no;
	u32		xfer_len;
पूर्ण ____cacheline_aligned;

काष्ठा iscsi_cmd;

बाह्य पूर्णांक iscsit_build_pdu_and_seq_lists(काष्ठा iscsi_cmd *, u32);
बाह्य काष्ठा iscsi_pdu *iscsit_get_pdu_holder(काष्ठा iscsi_cmd *, u32, u32);
बाह्य काष्ठा iscsi_pdu *iscsit_get_pdu_holder_क्रम_seq(काष्ठा iscsi_cmd *, काष्ठा iscsi_seq *);
बाह्य काष्ठा iscsi_seq *iscsit_get_seq_holder(काष्ठा iscsi_cmd *, u32, u32);

#पूर्ण_अगर /* ISCSI_SEQ_AND_PDU_LIST_H */
