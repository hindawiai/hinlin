<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Trace poपूर्णांकs क्रम SSAM/SSH.
 *
 * Copyright (C) 2020 Maximilian Luz <luzmaximilian@gmail.com>
 */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM surface_aggregator

#अगर !defined(_SURFACE_AGGREGATOR_TRACE_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _SURFACE_AGGREGATOR_TRACE_H

#समावेश <linux/surface_aggregator/serial_hub.h>

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/tracepoपूर्णांक.h>

TRACE_DEFINE_ENUM(SSH_FRAME_TYPE_DATA_SEQ);
TRACE_DEFINE_ENUM(SSH_FRAME_TYPE_DATA_NSQ);
TRACE_DEFINE_ENUM(SSH_FRAME_TYPE_ACK);
TRACE_DEFINE_ENUM(SSH_FRAME_TYPE_NAK);

TRACE_DEFINE_ENUM(SSH_PACKET_SF_LOCKED_BIT);
TRACE_DEFINE_ENUM(SSH_PACKET_SF_QUEUED_BIT);
TRACE_DEFINE_ENUM(SSH_PACKET_SF_PENDING_BIT);
TRACE_DEFINE_ENUM(SSH_PACKET_SF_TRANSMITTING_BIT);
TRACE_DEFINE_ENUM(SSH_PACKET_SF_TRANSMITTED_BIT);
TRACE_DEFINE_ENUM(SSH_PACKET_SF_ACKED_BIT);
TRACE_DEFINE_ENUM(SSH_PACKET_SF_CANCELED_BIT);
TRACE_DEFINE_ENUM(SSH_PACKET_SF_COMPLETED_BIT);

TRACE_DEFINE_ENUM(SSH_PACKET_TY_FLUSH_BIT);
TRACE_DEFINE_ENUM(SSH_PACKET_TY_SEQUENCED_BIT);
TRACE_DEFINE_ENUM(SSH_PACKET_TY_BLOCKING_BIT);

TRACE_DEFINE_ENUM(SSH_PACKET_FLAGS_SF_MASK);
TRACE_DEFINE_ENUM(SSH_PACKET_FLAGS_TY_MASK);

TRACE_DEFINE_ENUM(SSH_REQUEST_SF_LOCKED_BIT);
TRACE_DEFINE_ENUM(SSH_REQUEST_SF_QUEUED_BIT);
TRACE_DEFINE_ENUM(SSH_REQUEST_SF_PENDING_BIT);
TRACE_DEFINE_ENUM(SSH_REQUEST_SF_TRANSMITTING_BIT);
TRACE_DEFINE_ENUM(SSH_REQUEST_SF_TRANSMITTED_BIT);
TRACE_DEFINE_ENUM(SSH_REQUEST_SF_RSPRCVD_BIT);
TRACE_DEFINE_ENUM(SSH_REQUEST_SF_CANCELED_BIT);
TRACE_DEFINE_ENUM(SSH_REQUEST_SF_COMPLETED_BIT);

TRACE_DEFINE_ENUM(SSH_REQUEST_TY_FLUSH_BIT);
TRACE_DEFINE_ENUM(SSH_REQUEST_TY_HAS_RESPONSE_BIT);

TRACE_DEFINE_ENUM(SSH_REQUEST_FLAGS_SF_MASK);
TRACE_DEFINE_ENUM(SSH_REQUEST_FLAGS_TY_MASK);

TRACE_DEFINE_ENUM(SSAM_SSH_TC_SAM);
TRACE_DEFINE_ENUM(SSAM_SSH_TC_BAT);
TRACE_DEFINE_ENUM(SSAM_SSH_TC_TMP);
TRACE_DEFINE_ENUM(SSAM_SSH_TC_PMC);
TRACE_DEFINE_ENUM(SSAM_SSH_TC_FAN);
TRACE_DEFINE_ENUM(SSAM_SSH_TC_PoM);
TRACE_DEFINE_ENUM(SSAM_SSH_TC_DBG);
TRACE_DEFINE_ENUM(SSAM_SSH_TC_KBD);
TRACE_DEFINE_ENUM(SSAM_SSH_TC_FWU);
TRACE_DEFINE_ENUM(SSAM_SSH_TC_UNI);
TRACE_DEFINE_ENUM(SSAM_SSH_TC_LPC);
TRACE_DEFINE_ENUM(SSAM_SSH_TC_TCL);
TRACE_DEFINE_ENUM(SSAM_SSH_TC_SFL);
TRACE_DEFINE_ENUM(SSAM_SSH_TC_KIP);
TRACE_DEFINE_ENUM(SSAM_SSH_TC_EXT);
TRACE_DEFINE_ENUM(SSAM_SSH_TC_BLD);
TRACE_DEFINE_ENUM(SSAM_SSH_TC_BAS);
TRACE_DEFINE_ENUM(SSAM_SSH_TC_SEN);
TRACE_DEFINE_ENUM(SSAM_SSH_TC_SRQ);
TRACE_DEFINE_ENUM(SSAM_SSH_TC_MCU);
TRACE_DEFINE_ENUM(SSAM_SSH_TC_HID);
TRACE_DEFINE_ENUM(SSAM_SSH_TC_TCH);
TRACE_DEFINE_ENUM(SSAM_SSH_TC_BKL);
TRACE_DEFINE_ENUM(SSAM_SSH_TC_TAM);
TRACE_DEFINE_ENUM(SSAM_SSH_TC_ACC);
TRACE_DEFINE_ENUM(SSAM_SSH_TC_UFI);
TRACE_DEFINE_ENUM(SSAM_SSH_TC_USC);
TRACE_DEFINE_ENUM(SSAM_SSH_TC_PEN);
TRACE_DEFINE_ENUM(SSAM_SSH_TC_VID);
TRACE_DEFINE_ENUM(SSAM_SSH_TC_AUD);
TRACE_DEFINE_ENUM(SSAM_SSH_TC_SMC);
TRACE_DEFINE_ENUM(SSAM_SSH_TC_KPD);
TRACE_DEFINE_ENUM(SSAM_SSH_TC_REG);

#घोषणा SSAM_PTR_UID_LEN		9
#घोषणा SSAM_U8_FIELD_NOT_APPLICABLE	((u16)-1)
#घोषणा SSAM_SEQ_NOT_APPLICABLE		((u16)-1)
#घोषणा SSAM_RQID_NOT_APPLICABLE	((u32)-1)
#घोषणा SSAM_SSH_TC_NOT_APPLICABLE	0

#अगर_अघोषित _SURFACE_AGGREGATOR_TRACE_HELPERS
#घोषणा _SURFACE_AGGREGATOR_TRACE_HELPERS

/**
 * ssam_trace_ptr_uid() - Convert the poपूर्णांकer to a non-poपूर्णांकer UID string.
 * @ptr: The poपूर्णांकer to convert.
 * @uid_str: A buffer of length SSAM_PTR_UID_LEN where the UID will be stored.
 *
 * Converts the given poपूर्णांकer पूर्णांकo a UID string that is safe to be shared
 * with userspace and logs, i.e. करोesn't give away the real memory location.
 */
अटल अंतरभूत व्योम ssam_trace_ptr_uid(स्थिर व्योम *ptr, अक्षर *uid_str)
अणु
	अक्षर buf[2 * माप(व्योम *) + 1];

	BUILD_BUG_ON(ARRAY_SIZE(buf) < SSAM_PTR_UID_LEN);

	snम_लिखो(buf, ARRAY_SIZE(buf), "%p", ptr);
	स_नकल(uid_str, &buf[ARRAY_SIZE(buf) - SSAM_PTR_UID_LEN],
	       SSAM_PTR_UID_LEN);
पूर्ण

/**
 * ssam_trace_get_packet_seq() - Read the packet's sequence ID.
 * @p: The packet.
 *
 * Return: Returns the packet's sequence ID (SEQ) field अगर present, or
 * %SSAM_SEQ_NOT_APPLICABLE अगर not (e.g. flush packet).
 */
अटल अंतरभूत u16 ssam_trace_get_packet_seq(स्थिर काष्ठा ssh_packet *p)
अणु
	अगर (!p->data.ptr || p->data.len < SSH_MESSAGE_LENGTH(0))
		वापस SSAM_SEQ_NOT_APPLICABLE;

	वापस p->data.ptr[SSH_MSGOFFSET_FRAME(seq)];
पूर्ण

/**
 * ssam_trace_get_request_id() - Read the packet's request ID.
 * @p: The packet.
 *
 * Return: Returns the packet's request ID (RQID) field अगर the packet
 * represents a request with command data, or %SSAM_RQID_NOT_APPLICABLE अगर not
 * (e.g. flush request, control packet).
 */
अटल अंतरभूत u32 ssam_trace_get_request_id(स्थिर काष्ठा ssh_packet *p)
अणु
	अगर (!p->data.ptr || p->data.len < SSH_COMMAND_MESSAGE_LENGTH(0))
		वापस SSAM_RQID_NOT_APPLICABLE;

	वापस get_unaligned_le16(&p->data.ptr[SSH_MSGOFFSET_COMMAND(rqid)]);
पूर्ण

/**
 * ssam_trace_get_request_tc() - Read the packet's request target category.
 * @p: The packet.
 *
 * Return: Returns the packet's request target category (TC) field अगर the
 * packet represents a request with command data, or %SSAM_TC_NOT_APPLICABLE
 * अगर not (e.g. flush request, control packet).
 */
अटल अंतरभूत u32 ssam_trace_get_request_tc(स्थिर काष्ठा ssh_packet *p)
अणु
	अगर (!p->data.ptr || p->data.len < SSH_COMMAND_MESSAGE_LENGTH(0))
		वापस SSAM_SSH_TC_NOT_APPLICABLE;

	वापस get_unaligned_le16(&p->data.ptr[SSH_MSGOFFSET_COMMAND(tc)]);
पूर्ण

#पूर्ण_अगर /* _SURFACE_AGGREGATOR_TRACE_HELPERS */

#घोषणा ssam_trace_get_command_field_u8(packet, field) \
	((!(packet) || (packet)->data.len < SSH_COMMAND_MESSAGE_LENGTH(0)) \
	 ? 0 : (packet)->data.ptr[SSH_MSGOFFSET_COMMAND(field)])

#घोषणा ssam_show_generic_u8_field(value)				\
	__prपूर्णांक_symbolic(value,						\
		अणु SSAM_U8_FIELD_NOT_APPLICABLE,		"N/A" पूर्ण		\
	)

#घोषणा ssam_show_frame_type(ty)					\
	__prपूर्णांक_symbolic(ty,						\
		अणु SSH_FRAME_TYPE_DATA_SEQ,		"DSEQ" पूर्ण,	\
		अणु SSH_FRAME_TYPE_DATA_NSQ,		"DNSQ" पूर्ण,	\
		अणु SSH_FRAME_TYPE_ACK,			"ACK"  पूर्ण,	\
		अणु SSH_FRAME_TYPE_NAK,			"NAK"  पूर्ण	\
	)

#घोषणा ssam_show_packet_type(type)					\
	__prपूर्णांक_flags(flags & SSH_PACKET_FLAGS_TY_MASK, "",		\
		अणु BIT(SSH_PACKET_TY_FLUSH_BIT),		"F" पूर्ण,		\
		अणु BIT(SSH_PACKET_TY_SEQUENCED_BIT),	"S" पूर्ण,		\
		अणु BIT(SSH_PACKET_TY_BLOCKING_BIT),	"B" पूर्ण		\
	)

#घोषणा ssam_show_packet_state(state)					\
	__prपूर्णांक_flags(flags & SSH_PACKET_FLAGS_SF_MASK, "",		\
		अणु BIT(SSH_PACKET_SF_LOCKED_BIT),	"L" पूर्ण,		\
		अणु BIT(SSH_PACKET_SF_QUEUED_BIT),	"Q" पूर्ण,		\
		अणु BIT(SSH_PACKET_SF_PENDING_BIT),	"P" पूर्ण,		\
		अणु BIT(SSH_PACKET_SF_TRANSMITTING_BIT),	"S" पूर्ण,		\
		अणु BIT(SSH_PACKET_SF_TRANSMITTED_BIT),	"T" पूर्ण,		\
		अणु BIT(SSH_PACKET_SF_ACKED_BIT),		"A" पूर्ण,		\
		अणु BIT(SSH_PACKET_SF_CANCELED_BIT),	"C" पूर्ण,		\
		अणु BIT(SSH_PACKET_SF_COMPLETED_BIT),	"F" पूर्ण		\
	)

#घोषणा ssam_show_packet_seq(seq)					\
	__prपूर्णांक_symbolic(seq,						\
		अणु SSAM_SEQ_NOT_APPLICABLE,		"N/A" पूर्ण		\
	)

#घोषणा ssam_show_request_type(flags)					\
	__prपूर्णांक_flags((flags) & SSH_REQUEST_FLAGS_TY_MASK, "",		\
		अणु BIT(SSH_REQUEST_TY_FLUSH_BIT),	"F" पूर्ण,		\
		अणु BIT(SSH_REQUEST_TY_HAS_RESPONSE_BIT),	"R" पूर्ण		\
	)

#घोषणा ssam_show_request_state(flags)					\
	__prपूर्णांक_flags((flags) & SSH_REQUEST_FLAGS_SF_MASK, "",		\
		अणु BIT(SSH_REQUEST_SF_LOCKED_BIT),	"L" पूर्ण,		\
		अणु BIT(SSH_REQUEST_SF_QUEUED_BIT),	"Q" पूर्ण,		\
		अणु BIT(SSH_REQUEST_SF_PENDING_BIT),	"P" पूर्ण,		\
		अणु BIT(SSH_REQUEST_SF_TRANSMITTING_BIT),	"S" पूर्ण,		\
		अणु BIT(SSH_REQUEST_SF_TRANSMITTED_BIT),	"T" पूर्ण,		\
		अणु BIT(SSH_REQUEST_SF_RSPRCVD_BIT),	"A" पूर्ण,		\
		अणु BIT(SSH_REQUEST_SF_CANCELED_BIT),	"C" पूर्ण,		\
		अणु BIT(SSH_REQUEST_SF_COMPLETED_BIT),	"F" पूर्ण		\
	)

#घोषणा ssam_show_request_id(rqid)					\
	__prपूर्णांक_symbolic(rqid,						\
		अणु SSAM_RQID_NOT_APPLICABLE,		"N/A" पूर्ण		\
	)

#घोषणा ssam_show_ssh_tc(rqid)						\
	__prपूर्णांक_symbolic(rqid,						\
		अणु SSAM_SSH_TC_NOT_APPLICABLE,		"N/A" पूर्ण,	\
		अणु SSAM_SSH_TC_SAM,			"SAM" पूर्ण,	\
		अणु SSAM_SSH_TC_BAT,			"BAT" पूर्ण,	\
		अणु SSAM_SSH_TC_TMP,			"TMP" पूर्ण,	\
		अणु SSAM_SSH_TC_PMC,			"PMC" पूर्ण,	\
		अणु SSAM_SSH_TC_FAN,			"FAN" पूर्ण,	\
		अणु SSAM_SSH_TC_PoM,			"PoM" पूर्ण,	\
		अणु SSAM_SSH_TC_DBG,			"DBG" पूर्ण,	\
		अणु SSAM_SSH_TC_KBD,			"KBD" पूर्ण,	\
		अणु SSAM_SSH_TC_FWU,			"FWU" पूर्ण,	\
		अणु SSAM_SSH_TC_UNI,			"UNI" पूर्ण,	\
		अणु SSAM_SSH_TC_LPC,			"LPC" पूर्ण,	\
		अणु SSAM_SSH_TC_TCL,			"TCL" पूर्ण,	\
		अणु SSAM_SSH_TC_SFL,			"SFL" पूर्ण,	\
		अणु SSAM_SSH_TC_KIP,			"KIP" पूर्ण,	\
		अणु SSAM_SSH_TC_EXT,			"EXT" पूर्ण,	\
		अणु SSAM_SSH_TC_BLD,			"BLD" पूर्ण,	\
		अणु SSAM_SSH_TC_BAS,			"BAS" पूर्ण,	\
		अणु SSAM_SSH_TC_SEN,			"SEN" पूर्ण,	\
		अणु SSAM_SSH_TC_SRQ,			"SRQ" पूर्ण,	\
		अणु SSAM_SSH_TC_MCU,			"MCU" पूर्ण,	\
		अणु SSAM_SSH_TC_HID,			"HID" पूर्ण,	\
		अणु SSAM_SSH_TC_TCH,			"TCH" पूर्ण,	\
		अणु SSAM_SSH_TC_BKL,			"BKL" पूर्ण,	\
		अणु SSAM_SSH_TC_TAM,			"TAM" पूर्ण,	\
		अणु SSAM_SSH_TC_ACC,			"ACC" पूर्ण,	\
		अणु SSAM_SSH_TC_UFI,			"UFI" पूर्ण,	\
		अणु SSAM_SSH_TC_USC,			"USC" पूर्ण,	\
		अणु SSAM_SSH_TC_PEN,			"PEN" पूर्ण,	\
		अणु SSAM_SSH_TC_VID,			"VID" पूर्ण,	\
		अणु SSAM_SSH_TC_AUD,			"AUD" पूर्ण,	\
		अणु SSAM_SSH_TC_SMC,			"SMC" पूर्ण,	\
		अणु SSAM_SSH_TC_KPD,			"KPD" पूर्ण,	\
		अणु SSAM_SSH_TC_REG,			"REG" पूर्ण		\
	)

DECLARE_EVENT_CLASS(ssam_frame_class,
	TP_PROTO(स्थिर काष्ठा ssh_frame *frame),

	TP_ARGS(frame),

	TP_STRUCT__entry(
		__field(u8, type)
		__field(u8, seq)
		__field(u16, len)
	),

	TP_fast_assign(
		__entry->type = frame->type;
		__entry->seq = frame->seq;
		__entry->len = get_unaligned_le16(&frame->len);
	),

	TP_prपूर्णांकk("ty=%s, seq=%#04x, len=%u",
		ssam_show_frame_type(__entry->type),
		__entry->seq,
		__entry->len
	)
);

#घोषणा DEFINE_SSAM_FRAME_EVENT(name)				\
	DEFINE_EVENT(ssam_frame_class, ssam_##name,		\
		TP_PROTO(स्थिर काष्ठा ssh_frame *frame),	\
		TP_ARGS(frame)					\
	)

DECLARE_EVENT_CLASS(ssam_command_class,
	TP_PROTO(स्थिर काष्ठा ssh_command *cmd, u16 len),

	TP_ARGS(cmd, len),

	TP_STRUCT__entry(
		__field(u16, rqid)
		__field(u16, len)
		__field(u8, tc)
		__field(u8, cid)
		__field(u8, iid)
	),

	TP_fast_assign(
		__entry->rqid = get_unaligned_le16(&cmd->rqid);
		__entry->tc = cmd->tc;
		__entry->cid = cmd->cid;
		__entry->iid = cmd->iid;
		__entry->len = len;
	),

	TP_prपूर्णांकk("rqid=%#06x, tc=%s, cid=%#04x, iid=%#04x, len=%u",
		__entry->rqid,
		ssam_show_ssh_tc(__entry->tc),
		__entry->cid,
		__entry->iid,
		__entry->len
	)
);

#घोषणा DEFINE_SSAM_COMMAND_EVENT(name)					\
	DEFINE_EVENT(ssam_command_class, ssam_##name,			\
		TP_PROTO(स्थिर काष्ठा ssh_command *cmd, u16 len),	\
		TP_ARGS(cmd, len)					\
	)

DECLARE_EVENT_CLASS(ssam_packet_class,
	TP_PROTO(स्थिर काष्ठा ssh_packet *packet),

	TP_ARGS(packet),

	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ, state)
		__array(अक्षर, uid, SSAM_PTR_UID_LEN)
		__field(u8, priority)
		__field(u16, length)
		__field(u16, seq)
	),

	TP_fast_assign(
		__entry->state = READ_ONCE(packet->state);
		ssam_trace_ptr_uid(packet, __entry->uid);
		__entry->priority = READ_ONCE(packet->priority);
		__entry->length = packet->data.len;
		__entry->seq = ssam_trace_get_packet_seq(packet);
	),

	TP_prपूर्णांकk("uid=%s, seq=%s, ty=%s, pri=%#04x, len=%u, sta=%s",
		__entry->uid,
		ssam_show_packet_seq(__entry->seq),
		ssam_show_packet_type(__entry->state),
		__entry->priority,
		__entry->length,
		ssam_show_packet_state(__entry->state)
	)
);

#घोषणा DEFINE_SSAM_PACKET_EVENT(name)				\
	DEFINE_EVENT(ssam_packet_class, ssam_##name,		\
		TP_PROTO(स्थिर काष्ठा ssh_packet *packet),	\
		TP_ARGS(packet)					\
	)

DECLARE_EVENT_CLASS(ssam_packet_status_class,
	TP_PROTO(स्थिर काष्ठा ssh_packet *packet, पूर्णांक status),

	TP_ARGS(packet, status),

	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ, state)
		__field(पूर्णांक, status)
		__array(अक्षर, uid, SSAM_PTR_UID_LEN)
		__field(u8, priority)
		__field(u16, length)
		__field(u16, seq)
	),

	TP_fast_assign(
		__entry->state = READ_ONCE(packet->state);
		__entry->status = status;
		ssam_trace_ptr_uid(packet, __entry->uid);
		__entry->priority = READ_ONCE(packet->priority);
		__entry->length = packet->data.len;
		__entry->seq = ssam_trace_get_packet_seq(packet);
	),

	TP_prपूर्णांकk("uid=%s, seq=%s, ty=%s, pri=%#04x, len=%u, sta=%s, status=%d",
		__entry->uid,
		ssam_show_packet_seq(__entry->seq),
		ssam_show_packet_type(__entry->state),
		__entry->priority,
		__entry->length,
		ssam_show_packet_state(__entry->state),
		__entry->status
	)
);

#घोषणा DEFINE_SSAM_PACKET_STATUS_EVENT(name)				\
	DEFINE_EVENT(ssam_packet_status_class, ssam_##name,		\
		TP_PROTO(स्थिर काष्ठा ssh_packet *packet, पूर्णांक status),	\
		TP_ARGS(packet, status)					\
	)

DECLARE_EVENT_CLASS(ssam_request_class,
	TP_PROTO(स्थिर काष्ठा ssh_request *request),

	TP_ARGS(request),

	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ, state)
		__field(u32, rqid)
		__array(अक्षर, uid, SSAM_PTR_UID_LEN)
		__field(u8, tc)
		__field(u16, cid)
		__field(u16, iid)
	),

	TP_fast_assign(
		स्थिर काष्ठा ssh_packet *p = &request->packet;

		/* Use packet क्रम UID so we can match requests to packets. */
		__entry->state = READ_ONCE(request->state);
		__entry->rqid = ssam_trace_get_request_id(p);
		ssam_trace_ptr_uid(p, __entry->uid);
		__entry->tc = ssam_trace_get_request_tc(p);
		__entry->cid = ssam_trace_get_command_field_u8(p, cid);
		__entry->iid = ssam_trace_get_command_field_u8(p, iid);
	),

	TP_prपूर्णांकk("uid=%s, rqid=%s, ty=%s, sta=%s, tc=%s, cid=%s, iid=%s",
		__entry->uid,
		ssam_show_request_id(__entry->rqid),
		ssam_show_request_type(__entry->state),
		ssam_show_request_state(__entry->state),
		ssam_show_ssh_tc(__entry->tc),
		ssam_show_generic_u8_field(__entry->cid),
		ssam_show_generic_u8_field(__entry->iid)
	)
);

#घोषणा DEFINE_SSAM_REQUEST_EVENT(name)				\
	DEFINE_EVENT(ssam_request_class, ssam_##name,		\
		TP_PROTO(स्थिर काष्ठा ssh_request *request),	\
		TP_ARGS(request)				\
	)

DECLARE_EVENT_CLASS(ssam_request_status_class,
	TP_PROTO(स्थिर काष्ठा ssh_request *request, पूर्णांक status),

	TP_ARGS(request, status),

	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ, state)
		__field(u32, rqid)
		__field(पूर्णांक, status)
		__array(अक्षर, uid, SSAM_PTR_UID_LEN)
		__field(u8, tc)
		__field(u16, cid)
		__field(u16, iid)
	),

	TP_fast_assign(
		स्थिर काष्ठा ssh_packet *p = &request->packet;

		/* Use packet क्रम UID so we can match requests to packets. */
		__entry->state = READ_ONCE(request->state);
		__entry->rqid = ssam_trace_get_request_id(p);
		__entry->status = status;
		ssam_trace_ptr_uid(p, __entry->uid);
		__entry->tc = ssam_trace_get_request_tc(p);
		__entry->cid = ssam_trace_get_command_field_u8(p, cid);
		__entry->iid = ssam_trace_get_command_field_u8(p, iid);
	),

	TP_prपूर्णांकk("uid=%s, rqid=%s, ty=%s, sta=%s, tc=%s, cid=%s, iid=%s, status=%d",
		__entry->uid,
		ssam_show_request_id(__entry->rqid),
		ssam_show_request_type(__entry->state),
		ssam_show_request_state(__entry->state),
		ssam_show_ssh_tc(__entry->tc),
		ssam_show_generic_u8_field(__entry->cid),
		ssam_show_generic_u8_field(__entry->iid),
		__entry->status
	)
);

#घोषणा DEFINE_SSAM_REQUEST_STATUS_EVENT(name)				\
	DEFINE_EVENT(ssam_request_status_class, ssam_##name,		\
		TP_PROTO(स्थिर काष्ठा ssh_request *request, पूर्णांक status),\
		TP_ARGS(request, status)				\
	)

DECLARE_EVENT_CLASS(ssam_alloc_class,
	TP_PROTO(व्योम *ptr, माप_प्रकार len),

	TP_ARGS(ptr, len),

	TP_STRUCT__entry(
		__field(माप_प्रकार, len)
		__array(अक्षर, uid, SSAM_PTR_UID_LEN)
	),

	TP_fast_assign(
		__entry->len = len;
		ssam_trace_ptr_uid(ptr, __entry->uid);
	),

	TP_prपूर्णांकk("uid=%s, len=%zu", __entry->uid, __entry->len)
);

#घोषणा DEFINE_SSAM_ALLOC_EVENT(name)					\
	DEFINE_EVENT(ssam_alloc_class, ssam_##name,			\
		TP_PROTO(व्योम *ptr, माप_प्रकार len),			\
		TP_ARGS(ptr, len)					\
	)

DECLARE_EVENT_CLASS(ssam_मुक्त_class,
	TP_PROTO(व्योम *ptr),

	TP_ARGS(ptr),

	TP_STRUCT__entry(
		__array(अक्षर, uid, SSAM_PTR_UID_LEN)
	),

	TP_fast_assign(
		ssam_trace_ptr_uid(ptr, __entry->uid);
	),

	TP_prपूर्णांकk("uid=%s", __entry->uid)
);

#घोषणा DEFINE_SSAM_FREE_EVENT(name)					\
	DEFINE_EVENT(ssam_मुक्त_class, ssam_##name,			\
		TP_PROTO(व्योम *ptr),					\
		TP_ARGS(ptr)						\
	)

DECLARE_EVENT_CLASS(ssam_pending_class,
	TP_PROTO(अचिन्हित पूर्णांक pending),

	TP_ARGS(pending),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, pending)
	),

	TP_fast_assign(
		__entry->pending = pending;
	),

	TP_prपूर्णांकk("pending=%u", __entry->pending)
);

#घोषणा DEFINE_SSAM_PENDING_EVENT(name)					\
	DEFINE_EVENT(ssam_pending_class, ssam_##name,			\
		TP_PROTO(अचिन्हित पूर्णांक pending),				\
		TP_ARGS(pending)					\
	)

DECLARE_EVENT_CLASS(ssam_data_class,
	TP_PROTO(माप_प्रकार length),

	TP_ARGS(length),

	TP_STRUCT__entry(
		__field(माप_प्रकार, length)
	),

	TP_fast_assign(
		__entry->length = length;
	),

	TP_prपूर्णांकk("length=%zu", __entry->length)
);

#घोषणा DEFINE_SSAM_DATA_EVENT(name)					\
	DEFINE_EVENT(ssam_data_class, ssam_##name,			\
		TP_PROTO(माप_प्रकार length),				\
		TP_ARGS(length)						\
	)

DEFINE_SSAM_FRAME_EVENT(rx_frame_received);
DEFINE_SSAM_COMMAND_EVENT(rx_response_received);
DEFINE_SSAM_COMMAND_EVENT(rx_event_received);

DEFINE_SSAM_PACKET_EVENT(packet_release);
DEFINE_SSAM_PACKET_EVENT(packet_submit);
DEFINE_SSAM_PACKET_EVENT(packet_resubmit);
DEFINE_SSAM_PACKET_EVENT(packet_समयout);
DEFINE_SSAM_PACKET_EVENT(packet_cancel);
DEFINE_SSAM_PACKET_STATUS_EVENT(packet_complete);
DEFINE_SSAM_PENDING_EVENT(ptl_समयout_reap);

DEFINE_SSAM_REQUEST_EVENT(request_submit);
DEFINE_SSAM_REQUEST_EVENT(request_समयout);
DEFINE_SSAM_REQUEST_EVENT(request_cancel);
DEFINE_SSAM_REQUEST_STATUS_EVENT(request_complete);
DEFINE_SSAM_PENDING_EVENT(rtl_समयout_reap);

DEFINE_SSAM_PACKET_EVENT(ei_tx_drop_ack_packet);
DEFINE_SSAM_PACKET_EVENT(ei_tx_drop_nak_packet);
DEFINE_SSAM_PACKET_EVENT(ei_tx_drop_dsq_packet);
DEFINE_SSAM_PACKET_STATUS_EVENT(ei_tx_fail_ग_लिखो);
DEFINE_SSAM_PACKET_EVENT(ei_tx_corrupt_data);
DEFINE_SSAM_DATA_EVENT(ei_rx_corrupt_syn);
DEFINE_SSAM_FRAME_EVENT(ei_rx_corrupt_data);
DEFINE_SSAM_REQUEST_EVENT(ei_rx_drop_response);

DEFINE_SSAM_ALLOC_EVENT(ctrl_packet_alloc);
DEFINE_SSAM_FREE_EVENT(ctrl_packet_मुक्त);

DEFINE_SSAM_ALLOC_EVENT(event_item_alloc);
DEFINE_SSAM_FREE_EVENT(event_item_मुक्त);

#पूर्ण_अगर /* _SURFACE_AGGREGATOR_TRACE_H */

/* This part must be outside protection */
#अघोषित TRACE_INCLUDE_PATH
#अघोषित TRACE_INCLUDE_खाता

#घोषणा TRACE_INCLUDE_PATH .
#घोषणा TRACE_INCLUDE_खाता trace

#समावेश <trace/define_trace.h>
