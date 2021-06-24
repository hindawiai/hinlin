<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM nmi

#अगर !defined(_TRACE_NMI_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_NMI_H

#समावेश <linux/kसमय.स>
#समावेश <linux/tracepoपूर्णांक.h>

TRACE_EVENT(nmi_handler,

	TP_PROTO(व्योम *handler, s64 delta_ns, पूर्णांक handled),

	TP_ARGS(handler, delta_ns, handled),

	TP_STRUCT__entry(
		__field(	व्योम *,		handler	)
		__field(	s64,		delta_ns)
		__field(	पूर्णांक,		handled	)
	),

	TP_fast_assign(
		__entry->handler = handler;
		__entry->delta_ns = delta_ns;
		__entry->handled = handled;
	),

	TP_prपूर्णांकk("%ps() delta_ns: %lld handled: %d",
		__entry->handler,
		__entry->delta_ns,
		__entry->handled)
);

#पूर्ण_अगर /* _TRACE_NMI_H */

/* This part ust be outside protection */
#समावेश <trace/define_trace.h>
