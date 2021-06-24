<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM resctrl

#अगर !defined(_TRACE_PSEUDO_LOCK_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_PSEUDO_LOCK_H

#समावेश <linux/tracepoपूर्णांक.h>

TRACE_EVENT(pseuकरो_lock_mem_latency,
	    TP_PROTO(u32 latency),
	    TP_ARGS(latency),
	    TP_STRUCT__entry(__field(u32, latency)),
	    TP_fast_assign(__entry->latency = latency),
	    TP_prपूर्णांकk("latency=%u", __entry->latency)
	   );

TRACE_EVENT(pseuकरो_lock_l2,
	    TP_PROTO(u64 l2_hits, u64 l2_miss),
	    TP_ARGS(l2_hits, l2_miss),
	    TP_STRUCT__entry(__field(u64, l2_hits)
			     __field(u64, l2_miss)),
	    TP_fast_assign(__entry->l2_hits = l2_hits;
			   __entry->l2_miss = l2_miss;),
	    TP_prपूर्णांकk("hits=%llu miss=%llu",
		      __entry->l2_hits, __entry->l2_miss));

TRACE_EVENT(pseuकरो_lock_l3,
	    TP_PROTO(u64 l3_hits, u64 l3_miss),
	    TP_ARGS(l3_hits, l3_miss),
	    TP_STRUCT__entry(__field(u64, l3_hits)
			     __field(u64, l3_miss)),
	    TP_fast_assign(__entry->l3_hits = l3_hits;
			   __entry->l3_miss = l3_miss;),
	    TP_prपूर्णांकk("hits=%llu miss=%llu",
		      __entry->l3_hits, __entry->l3_miss));

#पूर्ण_अगर /* _TRACE_PSEUDO_LOCK_H */

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#घोषणा TRACE_INCLUDE_खाता pseuकरो_lock_event
#समावेश <trace/define_trace.h>
