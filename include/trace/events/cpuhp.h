<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM cpuhp

#अगर !defined(_TRACE_CPUHP_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_CPUHP_H

#समावेश <linux/tracepoपूर्णांक.h>

TRACE_EVENT(cpuhp_enter,

	TP_PROTO(अचिन्हित पूर्णांक cpu,
		 पूर्णांक target,
		 पूर्णांक idx,
		 पूर्णांक (*fun)(अचिन्हित पूर्णांक)),

	TP_ARGS(cpu, target, idx, fun),

	TP_STRUCT__entry(
		__field( अचिन्हित पूर्णांक,	cpu		)
		__field( पूर्णांक,		target		)
		__field( पूर्णांक,		idx		)
		__field( व्योम *,	fun		)
	),

	TP_fast_assign(
		__entry->cpu	= cpu;
		__entry->target	= target;
		__entry->idx	= idx;
		__entry->fun	= fun;
	),

	TP_prपूर्णांकk("cpu: %04u target: %3d step: %3d (%ps)",
		  __entry->cpu, __entry->target, __entry->idx, __entry->fun)
);

TRACE_EVENT(cpuhp_multi_enter,

	TP_PROTO(अचिन्हित पूर्णांक cpu,
		 पूर्णांक target,
		 पूर्णांक idx,
		 पूर्णांक (*fun)(अचिन्हित पूर्णांक, काष्ठा hlist_node *),
		 काष्ठा hlist_node *node),

	TP_ARGS(cpu, target, idx, fun, node),

	TP_STRUCT__entry(
		__field( अचिन्हित पूर्णांक,	cpu		)
		__field( पूर्णांक,		target		)
		__field( पूर्णांक,		idx		)
		__field( व्योम *,	fun		)
	),

	TP_fast_assign(
		__entry->cpu	= cpu;
		__entry->target	= target;
		__entry->idx	= idx;
		__entry->fun	= fun;
	),

	TP_prपूर्णांकk("cpu: %04u target: %3d step: %3d (%ps)",
		  __entry->cpu, __entry->target, __entry->idx, __entry->fun)
);

TRACE_EVENT(cpuhp_निकास,

	TP_PROTO(अचिन्हित पूर्णांक cpu,
		 पूर्णांक state,
		 पूर्णांक idx,
		 पूर्णांक ret),

	TP_ARGS(cpu, state, idx, ret),

	TP_STRUCT__entry(
		__field( अचिन्हित पूर्णांक,	cpu		)
		__field( पूर्णांक,		state		)
		__field( पूर्णांक,		idx		)
		__field( पूर्णांक,		ret		)
	),

	TP_fast_assign(
		__entry->cpu	= cpu;
		__entry->state	= state;
		__entry->idx	= idx;
		__entry->ret	= ret;
	),

	TP_prपूर्णांकk(" cpu: %04u  state: %3d step: %3d ret: %d",
		  __entry->cpu, __entry->state, __entry->idx,  __entry->ret)
);

#पूर्ण_अगर

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
