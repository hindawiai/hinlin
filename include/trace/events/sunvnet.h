<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM sunvnet

#अगर !defined(_TRACE_SUNVNET_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_SUNVNET_H

#समावेश <linux/tracepoपूर्णांक.h>

TRACE_EVENT(vnet_rx_one,

	TP_PROTO(पूर्णांक lsid, पूर्णांक rsid, पूर्णांक index, पूर्णांक needs_ack),

	TP_ARGS(lsid, rsid, index, needs_ack),

	TP_STRUCT__entry(
		__field(पूर्णांक, lsid)
		__field(पूर्णांक, rsid)
		__field(पूर्णांक, index)
		__field(पूर्णांक, needs_ack)
	),

	TP_fast_assign(
		__entry->lsid = lsid;
		__entry->rsid = rsid;
		__entry->index = index;
		__entry->needs_ack = needs_ack;
	),

	TP_prपूर्णांकk("(%x:%x) walk_rx_one index %d; needs_ack %d",
		__entry->lsid, __entry->rsid,
		__entry->index, __entry->needs_ack)
);

DECLARE_EVENT_CLASS(vnet_tx_stopped_ack_ढाँचा,

	TP_PROTO(पूर्णांक lsid, पूर्णांक rsid, पूर्णांक ack_end, पूर्णांक npkts),

	TP_ARGS(lsid, rsid, ack_end, npkts),

	TP_STRUCT__entry(
		__field(पूर्णांक, lsid)
		__field(पूर्णांक, rsid)
		__field(पूर्णांक, ack_end)
		__field(पूर्णांक, npkts)
	),

	TP_fast_assign(
		__entry->lsid = lsid;
		__entry->rsid = rsid;
		__entry->ack_end = ack_end;
		__entry->npkts = npkts;
	),

	TP_prपूर्णांकk("(%x:%x) stopped ack for %d; npkts %d",
		__entry->lsid, __entry->rsid,
		__entry->ack_end, __entry->npkts)
);
DEFINE_EVENT(vnet_tx_stopped_ack_ढाँचा, vnet_tx_send_stopped_ack,
	     TP_PROTO(पूर्णांक lsid, पूर्णांक rsid, पूर्णांक ack_end, पूर्णांक npkts),
	     TP_ARGS(lsid, rsid, ack_end, npkts));
DEFINE_EVENT(vnet_tx_stopped_ack_ढाँचा, vnet_tx_defer_stopped_ack,
	     TP_PROTO(पूर्णांक lsid, पूर्णांक rsid, पूर्णांक ack_end, पूर्णांक npkts),
	     TP_ARGS(lsid, rsid, ack_end, npkts));
DEFINE_EVENT(vnet_tx_stopped_ack_ढाँचा, vnet_tx_pending_stopped_ack,
	     TP_PROTO(पूर्णांक lsid, पूर्णांक rsid, पूर्णांक ack_end, पूर्णांक npkts),
	     TP_ARGS(lsid, rsid, ack_end, npkts));

TRACE_EVENT(vnet_rx_stopped_ack,

	TP_PROTO(पूर्णांक lsid, पूर्णांक rsid, पूर्णांक end),

	TP_ARGS(lsid, rsid, end),

	TP_STRUCT__entry(
		__field(पूर्णांक, lsid)
		__field(पूर्णांक, rsid)
		__field(पूर्णांक, end)
	),

	TP_fast_assign(
		__entry->lsid = lsid;
		__entry->rsid = rsid;
		__entry->end = end;
	),

	TP_prपूर्णांकk("(%x:%x) stopped ack for index %d",
		__entry->lsid, __entry->rsid, __entry->end)
);

TRACE_EVENT(vnet_tx_trigger,

	TP_PROTO(पूर्णांक lsid, पूर्णांक rsid, पूर्णांक start, पूर्णांक err),

	TP_ARGS(lsid, rsid, start, err),

	TP_STRUCT__entry(
		__field(पूर्णांक, lsid)
		__field(पूर्णांक, rsid)
		__field(पूर्णांक, start)
		__field(पूर्णांक, err)
	),

	TP_fast_assign(
		__entry->lsid = lsid;
		__entry->rsid = rsid;
		__entry->start = start;
		__entry->err = err;
	),

	TP_prपूर्णांकk("(%x:%x) Tx trigger for %d sent with err %d %s",
		__entry->lsid, __entry->rsid, __entry->start,
		__entry->err, __entry->err > 0 ? "(ok)" : " ")
);

TRACE_EVENT(vnet_skip_tx_trigger,

	TP_PROTO(पूर्णांक lsid, पूर्णांक rsid, पूर्णांक last),

	TP_ARGS(lsid, rsid, last),

	TP_STRUCT__entry(
		__field(पूर्णांक, lsid)
		__field(पूर्णांक, rsid)
		__field(पूर्णांक, last)
	),

	TP_fast_assign(
		__entry->lsid = lsid;
		__entry->rsid = rsid;
		__entry->last = last;
	),

	TP_prपूर्णांकk("(%x:%x) Skip Tx trigger. Last trigger sent was %d",
		__entry->lsid, __entry->rsid, __entry->last)
);
#पूर्ण_अगर /* _TRACE_SOCK_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
