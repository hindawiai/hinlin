<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM scmi

#अगर !defined(_TRACE_SCMI_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_SCMI_H

#समावेश <linux/tracepoपूर्णांक.h>

TRACE_EVENT(scmi_xfer_begin,
	TP_PROTO(पूर्णांक transfer_id, u8 msg_id, u8 protocol_id, u16 seq,
		 bool poll),
	TP_ARGS(transfer_id, msg_id, protocol_id, seq, poll),

	TP_STRUCT__entry(
		__field(पूर्णांक, transfer_id)
		__field(u8, msg_id)
		__field(u8, protocol_id)
		__field(u16, seq)
		__field(bool, poll)
	),

	TP_fast_assign(
		__entry->transfer_id = transfer_id;
		__entry->msg_id = msg_id;
		__entry->protocol_id = protocol_id;
		__entry->seq = seq;
		__entry->poll = poll;
	),

	TP_prपूर्णांकk("transfer_id=%d msg_id=%u protocol_id=%u seq=%u poll=%u",
		__entry->transfer_id, __entry->msg_id, __entry->protocol_id,
		__entry->seq, __entry->poll)
);

TRACE_EVENT(scmi_xfer_end,
	TP_PROTO(पूर्णांक transfer_id, u8 msg_id, u8 protocol_id, u16 seq,
		 पूर्णांक status),
	TP_ARGS(transfer_id, msg_id, protocol_id, seq, status),

	TP_STRUCT__entry(
		__field(पूर्णांक, transfer_id)
		__field(u8, msg_id)
		__field(u8, protocol_id)
		__field(u16, seq)
		__field(पूर्णांक, status)
	),

	TP_fast_assign(
		__entry->transfer_id = transfer_id;
		__entry->msg_id = msg_id;
		__entry->protocol_id = protocol_id;
		__entry->seq = seq;
		__entry->status = status;
	),

	TP_prपूर्णांकk("transfer_id=%d msg_id=%u protocol_id=%u seq=%u status=%d",
		__entry->transfer_id, __entry->msg_id, __entry->protocol_id,
		__entry->seq, __entry->status)
);

TRACE_EVENT(scmi_rx_करोne,
	TP_PROTO(पूर्णांक transfer_id, u8 msg_id, u8 protocol_id, u16 seq,
		 u8 msg_type),
	TP_ARGS(transfer_id, msg_id, protocol_id, seq, msg_type),

	TP_STRUCT__entry(
		__field(पूर्णांक, transfer_id)
		__field(u8, msg_id)
		__field(u8, protocol_id)
		__field(u16, seq)
		__field(u8, msg_type)
	),

	TP_fast_assign(
		__entry->transfer_id = transfer_id;
		__entry->msg_id = msg_id;
		__entry->protocol_id = protocol_id;
		__entry->seq = seq;
		__entry->msg_type = msg_type;
	),

	TP_prपूर्णांकk("transfer_id=%d msg_id=%u protocol_id=%u seq=%u msg_type=%u",
		__entry->transfer_id, __entry->msg_id, __entry->protocol_id,
		__entry->seq, __entry->msg_type)
);
#पूर्ण_अगर /* _TRACE_SCMI_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
