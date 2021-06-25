<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM पूर्णांकel-sst

/*
 * The TRACE_SYSTEM_VAR शेषs to TRACE_SYSTEM, but must be a
 * legitimate C variable. It is not exported to user space.
 */
#अघोषित TRACE_SYSTEM_VAR
#घोषणा TRACE_SYSTEM_VAR पूर्णांकel_sst

#अगर !defined(_TRACE_INTEL_SST_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_INTEL_SST_H

#समावेश <linux/types.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/tracepoपूर्णांक.h>

DECLARE_EVENT_CLASS(sst_ipc_msg,

	TP_PROTO(अचिन्हित पूर्णांक val),

	TP_ARGS(val),

	TP_STRUCT__entry(
		__field(	अचिन्हित पूर्णांक,	val		)
	),

	TP_fast_assign(
		__entry->val = val;
	),

	TP_prपूर्णांकk("0x%8.8x", (अचिन्हित पूर्णांक)__entry->val)
);

DEFINE_EVENT(sst_ipc_msg, sst_ipc_msg_tx,

	TP_PROTO(अचिन्हित पूर्णांक val),

	TP_ARGS(val)

);

DEFINE_EVENT(sst_ipc_msg, sst_ipc_msg_rx,

	TP_PROTO(अचिन्हित पूर्णांक val),

	TP_ARGS(val)

);

DECLARE_EVENT_CLASS(sst_ipc_mailbox,

	TP_PROTO(अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक val),

	TP_ARGS(offset, val),

	TP_STRUCT__entry(
		__field(	अचिन्हित पूर्णांक,	offset		)
		__field(	अचिन्हित पूर्णांक,	val		)
	),

	TP_fast_assign(
		__entry->offset = offset;
		__entry->val = val;
	),

	TP_prपूर्णांकk(" 0x%4.4x = 0x%8.8x",
		(अचिन्हित पूर्णांक)__entry->offset, (अचिन्हित पूर्णांक)__entry->val)
);

DEFINE_EVENT(sst_ipc_mailbox, sst_ipc_inbox_rdata,

	TP_PROTO(अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक val),

	TP_ARGS(offset, val)

);

DEFINE_EVENT(sst_ipc_mailbox, sst_ipc_inbox_wdata,

	TP_PROTO(अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक val),

	TP_ARGS(offset, val)

);

DEFINE_EVENT(sst_ipc_mailbox, sst_ipc_outbox_rdata,

	TP_PROTO(अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक val),

	TP_ARGS(offset, val)

);

DEFINE_EVENT(sst_ipc_mailbox, sst_ipc_outbox_wdata,

	TP_PROTO(अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक val),

	TP_ARGS(offset, val)

);

DECLARE_EVENT_CLASS(sst_ipc_mailbox_info,

	TP_PROTO(अचिन्हित पूर्णांक size),

	TP_ARGS(size),

	TP_STRUCT__entry(
		__field(	अचिन्हित पूर्णांक,	size		)
	),

	TP_fast_assign(
		__entry->size = size;
	),

	TP_prपूर्णांकk("Mailbox bytes 0x%8.8x", (अचिन्हित पूर्णांक)__entry->size)
);

DEFINE_EVENT(sst_ipc_mailbox_info, sst_ipc_inbox_पढ़ो,

	TP_PROTO(अचिन्हित पूर्णांक size),

	TP_ARGS(size)

);

DEFINE_EVENT(sst_ipc_mailbox_info, sst_ipc_inbox_ग_लिखो,

	TP_PROTO(अचिन्हित पूर्णांक size),

	TP_ARGS(size)

);

DEFINE_EVENT(sst_ipc_mailbox_info, sst_ipc_outbox_पढ़ो,

	TP_PROTO(अचिन्हित पूर्णांक size),

	TP_ARGS(size)

);

DEFINE_EVENT(sst_ipc_mailbox_info, sst_ipc_outbox_ग_लिखो,

	TP_PROTO(अचिन्हित पूर्णांक size),

	TP_ARGS(size)

);

#पूर्ण_अगर /* _TRACE_SST_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
