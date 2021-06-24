<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM thp

#अगर !defined(_TRACE_THP_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_THP_H

#समावेश <linux/types.h>
#समावेश <linux/tracepoपूर्णांक.h>

TRACE_EVENT(hugepage_invalidate,

	    TP_PROTO(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ pte),
	    TP_ARGS(addr, pte),
	    TP_STRUCT__entry(
		    __field(अचिन्हित दीर्घ, addr)
		    __field(अचिन्हित दीर्घ, pte)
		    ),

	    TP_fast_assign(
		    __entry->addr = addr;
		    __entry->pte = pte;
		    ),

	    TP_prपूर्णांकk("hugepage invalidate at addr 0x%lx and pte = 0x%lx",
		      __entry->addr, __entry->pte)
);

TRACE_EVENT(hugepage_set_pmd,

	    TP_PROTO(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ pmd),
	    TP_ARGS(addr, pmd),
	    TP_STRUCT__entry(
		    __field(अचिन्हित दीर्घ, addr)
		    __field(अचिन्हित दीर्घ, pmd)
		    ),

	    TP_fast_assign(
		    __entry->addr = addr;
		    __entry->pmd = pmd;
		    ),

	    TP_prपूर्णांकk("Set pmd with 0x%lx with 0x%lx", __entry->addr, __entry->pmd)
);


TRACE_EVENT(hugepage_update,

	    TP_PROTO(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ pte, अचिन्हित दीर्घ clr, अचिन्हित दीर्घ set),
	    TP_ARGS(addr, pte, clr, set),
	    TP_STRUCT__entry(
		    __field(अचिन्हित दीर्घ, addr)
		    __field(अचिन्हित दीर्घ, pte)
		    __field(अचिन्हित दीर्घ, clr)
		    __field(अचिन्हित दीर्घ, set)
		    ),

	    TP_fast_assign(
		    __entry->addr = addr;
		    __entry->pte = pte;
		    __entry->clr = clr;
		    __entry->set = set;

		    ),

	    TP_prपूर्णांकk("hugepage update at addr 0x%lx and pte = 0x%lx clr = 0x%lx, set = 0x%lx", __entry->addr, __entry->pte, __entry->clr, __entry->set)
);
TRACE_EVENT(hugepage_splitting,

	    TP_PROTO(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ pte),
	    TP_ARGS(addr, pte),
	    TP_STRUCT__entry(
		    __field(अचिन्हित दीर्घ, addr)
		    __field(अचिन्हित दीर्घ, pte)
		    ),

	    TP_fast_assign(
		    __entry->addr = addr;
		    __entry->pte = pte;
		    ),

	    TP_prपूर्णांकk("hugepage splitting at addr 0x%lx and pte = 0x%lx",
		      __entry->addr, __entry->pte)
);

#पूर्ण_अगर /* _TRACE_THP_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
