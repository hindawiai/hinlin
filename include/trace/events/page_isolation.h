<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM page_isolation

#अगर !defined(_TRACE_PAGE_ISOLATION_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_PAGE_ISOLATION_H

#समावेश <linux/tracepoपूर्णांक.h>

TRACE_EVENT(test_pages_isolated,

	TP_PROTO(
		अचिन्हित दीर्घ start_pfn,
		अचिन्हित दीर्घ end_pfn,
		अचिन्हित दीर्घ fin_pfn),

	TP_ARGS(start_pfn, end_pfn, fin_pfn),

	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ, start_pfn)
		__field(अचिन्हित दीर्घ, end_pfn)
		__field(अचिन्हित दीर्घ, fin_pfn)
	),

	TP_fast_assign(
		__entry->start_pfn = start_pfn;
		__entry->end_pfn = end_pfn;
		__entry->fin_pfn = fin_pfn;
	),

	TP_prपूर्णांकk("start_pfn=0x%lx end_pfn=0x%lx fin_pfn=0x%lx ret=%s",
		__entry->start_pfn, __entry->end_pfn, __entry->fin_pfn,
		__entry->end_pfn <= __entry->fin_pfn ? "success" : "fail")
);

#पूर्ण_अगर /* _TRACE_PAGE_ISOLATION_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
