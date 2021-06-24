<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM vsyscall

#अगर !defined(__VSYSCALL_TRACE_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा __VSYSCALL_TRACE_H

#समावेश <linux/tracepoपूर्णांक.h>

TRACE_EVENT(emulate_vsyscall,

	    TP_PROTO(पूर्णांक nr),

	    TP_ARGS(nr),

	    TP_STRUCT__entry(__field(पूर्णांक, nr)),

	    TP_fast_assign(
			   __entry->nr = nr;
			   ),

	    TP_prपूर्णांकk("nr = %d", __entry->nr)
);

#पूर्ण_अगर

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH ../../arch/x86/entry/vsyscall/
#घोषणा TRACE_INCLUDE_खाता vsyscall_trace
#समावेश <trace/define_trace.h>
