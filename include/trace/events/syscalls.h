<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM raw_syscalls
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता syscalls

#अगर !defined(_TRACE_EVENTS_SYSCALLS_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_EVENTS_SYSCALLS_H

#समावेश <linux/tracepoपूर्णांक.h>

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/syscall.h>


#अगर_घोषित CONFIG_HAVE_SYSCALL_TRACEPOINTS

TRACE_EVENT_FN(sys_enter,

	TP_PROTO(काष्ठा pt_regs *regs, दीर्घ id),

	TP_ARGS(regs, id),

	TP_STRUCT__entry(
		__field(	दीर्घ,		id		)
		__array(	अचिन्हित दीर्घ,	args,	6	)
	),

	TP_fast_assign(
		__entry->id	= id;
		syscall_get_arguments(current, regs, __entry->args);
	),

	TP_prपूर्णांकk("NR %ld (%lx, %lx, %lx, %lx, %lx, %lx)",
		  __entry->id,
		  __entry->args[0], __entry->args[1], __entry->args[2],
		  __entry->args[3], __entry->args[4], __entry->args[5]),

	syscall_regfunc, syscall_unregfunc
);

TRACE_EVENT_FLAGS(sys_enter, TRACE_EVENT_FL_CAP_ANY)

TRACE_EVENT_FN(sys_निकास,

	TP_PROTO(काष्ठा pt_regs *regs, दीर्घ ret),

	TP_ARGS(regs, ret),

	TP_STRUCT__entry(
		__field(	दीर्घ,	id	)
		__field(	दीर्घ,	ret	)
	),

	TP_fast_assign(
		__entry->id	= syscall_get_nr(current, regs);
		__entry->ret	= ret;
	),

	TP_prपूर्णांकk("NR %ld = %ld",
		  __entry->id, __entry->ret),

	syscall_regfunc, syscall_unregfunc
);

TRACE_EVENT_FLAGS(sys_निकास, TRACE_EVENT_FL_CAP_ANY)

#पूर्ण_अगर /* CONFIG_HAVE_SYSCALL_TRACEPOINTS */

#पूर्ण_अगर /* _TRACE_EVENTS_SYSCALLS_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>

