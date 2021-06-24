<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM tlb

#अगर !defined(_TRACE_TLB_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_TLB_H

#समावेश <linux/mm_types.h>
#समावेश <linux/tracepoपूर्णांक.h>

#घोषणा TLB_FLUSH_REASON						\
	EM(  TLB_FLUSH_ON_TASK_SWITCH,	"flush on task switch" )	\
	EM(  TLB_REMOTE_SHOOTDOWN,	"remote shootdown" )		\
	EM(  TLB_LOCAL_SHOOTDOWN,	"local shootdown" )		\
	EM(  TLB_LOCAL_MM_SHOOTDOWN,	"local mm shootdown" )		\
	EMe( TLB_REMOTE_SEND_IPI,	"remote ipi send" )

/*
 * First define the क्रमागतs in TLB_FLUSH_REASON to be exported to userspace
 * via TRACE_DEFINE_ENUM().
 */
#अघोषित EM
#अघोषित EMe
#घोषणा EM(a,b)		TRACE_DEFINE_ENUM(a);
#घोषणा EMe(a,b)	TRACE_DEFINE_ENUM(a);

TLB_FLUSH_REASON

/*
 * Now redefine the EM() and EMe() macros to map the क्रमागतs to the strings
 * that will be prपूर्णांकed in the output.
 */
#अघोषित EM
#अघोषित EMe
#घोषणा EM(a,b)		अणु a, b पूर्ण,
#घोषणा EMe(a,b)	अणु a, b पूर्ण

TRACE_EVENT(tlb_flush,

	TP_PROTO(पूर्णांक reason, अचिन्हित दीर्घ pages),
	TP_ARGS(reason, pages),

	TP_STRUCT__entry(
		__field(	  पूर्णांक, reason)
		__field(अचिन्हित दीर्घ,  pages)
	),

	TP_fast_assign(
		__entry->reason = reason;
		__entry->pages  = pages;
	),

	TP_prपूर्णांकk("pages:%ld reason:%s (%d)",
		__entry->pages,
		__prपूर्णांक_symbolic(__entry->reason, TLB_FLUSH_REASON),
		__entry->reason)
);

#पूर्ण_अगर /* _TRACE_TLB_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
