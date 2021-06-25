<शैली गुरु>
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM hyperv

#अगर !defined(_HV_TRACE_BALLOON_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _HV_TRACE_BALLOON_H

#समावेश <linux/tracepoपूर्णांक.h>

TRACE_EVENT(balloon_status,
	    TP_PROTO(u64 available, u64 committed,
		     अचिन्हित दीर्घ vm_memory_committed,
		     अचिन्हित दीर्घ pages_ballooned,
		     अचिन्हित दीर्घ pages_added,
		     अचिन्हित दीर्घ pages_onlined),
	    TP_ARGS(available, committed, vm_memory_committed,
		    pages_ballooned, pages_added, pages_onlined),
	    TP_STRUCT__entry(
		    __field(u64, available)
		    __field(u64, committed)
		    __field(अचिन्हित दीर्घ, vm_memory_committed)
		    __field(अचिन्हित दीर्घ, pages_ballooned)
		    __field(अचिन्हित दीर्घ, pages_added)
		    __field(अचिन्हित दीर्घ, pages_onlined)
		    ),
	    TP_fast_assign(
		    __entry->available = available;
		    __entry->committed = committed;
		    __entry->vm_memory_committed = vm_memory_committed;
		    __entry->pages_ballooned = pages_ballooned;
		    __entry->pages_added = pages_added;
		    __entry->pages_onlined = pages_onlined;
		    ),
	    TP_prपूर्णांकk("available %lld, committed %lld; vm_memory_committed %ld;"
		      " pages_ballooned %ld, pages_added %ld, pages_onlined %ld",
		      __entry->available, __entry->committed,
		      __entry->vm_memory_committed, __entry->pages_ballooned,
		      __entry->pages_added, __entry->pages_onlined
		    )
	);

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता hv_trace_balloon
#पूर्ण_अगर /* _HV_TRACE_BALLOON_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
