<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM cma

#अगर !defined(_TRACE_CMA_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_CMA_H

#समावेश <linux/types.h>
#समावेश <linux/tracepoपूर्णांक.h>

DECLARE_EVENT_CLASS(cma_alloc_class,

	TP_PROTO(स्थिर अक्षर *name, अचिन्हित दीर्घ pfn, स्थिर काष्ठा page *page,
		 अचिन्हित दीर्घ count, अचिन्हित पूर्णांक align),

	TP_ARGS(name, pfn, page, count, align),

	TP_STRUCT__entry(
		__string(name, name)
		__field(अचिन्हित दीर्घ, pfn)
		__field(स्थिर काष्ठा page *, page)
		__field(अचिन्हित दीर्घ, count)
		__field(अचिन्हित पूर्णांक, align)
	),

	TP_fast_assign(
		__assign_str(name, name);
		__entry->pfn = pfn;
		__entry->page = page;
		__entry->count = count;
		__entry->align = align;
	),

	TP_prपूर्णांकk("name=%s pfn=%lx page=%p count=%lu align=%u",
		  __get_str(name),
		  __entry->pfn,
		  __entry->page,
		  __entry->count,
		  __entry->align)
);

TRACE_EVENT(cma_release,

	TP_PROTO(स्थिर अक्षर *name, अचिन्हित दीर्घ pfn, स्थिर काष्ठा page *page,
		 अचिन्हित दीर्घ count),

	TP_ARGS(name, pfn, page, count),

	TP_STRUCT__entry(
		__string(name, name)
		__field(अचिन्हित दीर्घ, pfn)
		__field(स्थिर काष्ठा page *, page)
		__field(अचिन्हित दीर्घ, count)
	),

	TP_fast_assign(
		__assign_str(name, name);
		__entry->pfn = pfn;
		__entry->page = page;
		__entry->count = count;
	),

	TP_prपूर्णांकk("name=%s pfn=%lx page=%p count=%lu",
		  __get_str(name),
		  __entry->pfn,
		  __entry->page,
		  __entry->count)
);

TRACE_EVENT(cma_alloc_start,

	TP_PROTO(स्थिर अक्षर *name, अचिन्हित दीर्घ count, अचिन्हित पूर्णांक align),

	TP_ARGS(name, count, align),

	TP_STRUCT__entry(
		__string(name, name)
		__field(अचिन्हित दीर्घ, count)
		__field(अचिन्हित पूर्णांक, align)
	),

	TP_fast_assign(
		__assign_str(name, name);
		__entry->count = count;
		__entry->align = align;
	),

	TP_prपूर्णांकk("name=%s count=%lu align=%u",
		  __get_str(name),
		  __entry->count,
		  __entry->align)
);

DEFINE_EVENT(cma_alloc_class, cma_alloc_finish,

	TP_PROTO(स्थिर अक्षर *name, अचिन्हित दीर्घ pfn, स्थिर काष्ठा page *page,
		 अचिन्हित दीर्घ count, अचिन्हित पूर्णांक align),

	TP_ARGS(name, pfn, page, count, align)
);

DEFINE_EVENT(cma_alloc_class, cma_alloc_busy_retry,

	TP_PROTO(स्थिर अक्षर *name, अचिन्हित दीर्घ pfn, स्थिर काष्ठा page *page,
		 अचिन्हित दीर्घ count, अचिन्हित पूर्णांक align),

	TP_ARGS(name, pfn, page, count, align)
);

#पूर्ण_अगर /* _TRACE_CMA_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
