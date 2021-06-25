<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM exceptions

#अगर !defined(_TRACE_PAGE_FAULT_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_PAGE_FAULT_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <यंत्र/trace/common.h>

बाह्य पूर्णांक trace_pagefault_reg(व्योम);
बाह्य व्योम trace_pagefault_unreg(व्योम);

DECLARE_EVENT_CLASS(x86_exceptions,

	TP_PROTO(अचिन्हित दीर्घ address, काष्ठा pt_regs *regs,
		 अचिन्हित दीर्घ error_code),

	TP_ARGS(address, regs, error_code),

	TP_STRUCT__entry(
		__field(		अचिन्हित दीर्घ, address	)
		__field(		अचिन्हित दीर्घ, ip	)
		__field(		अचिन्हित दीर्घ, error_code )
	),

	TP_fast_assign(
		__entry->address = address;
		__entry->ip = regs->ip;
		__entry->error_code = error_code;
	),

	TP_prपूर्णांकk("address=%ps ip=%ps error_code=0x%lx",
		  (व्योम *)__entry->address, (व्योम *)__entry->ip,
		  __entry->error_code) );

#घोषणा DEFINE_PAGE_FAULT_EVENT(name)				\
DEFINE_EVENT_FN(x86_exceptions, name,				\
	TP_PROTO(अचिन्हित दीर्घ address,	काष्ठा pt_regs *regs,	\
		 अचिन्हित दीर्घ error_code),			\
	TP_ARGS(address, regs, error_code),			\
	trace_pagefault_reg, trace_pagefault_unreg);

DEFINE_PAGE_FAULT_EVENT(page_fault_user);
DEFINE_PAGE_FAULT_EVENT(page_fault_kernel);

#अघोषित TRACE_INCLUDE_PATH
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_PATH .
#घोषणा TRACE_INCLUDE_खाता exceptions
#पूर्ण_अगर /*  _TRACE_PAGE_FAULT_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
