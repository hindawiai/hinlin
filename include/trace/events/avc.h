<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Authors:	Thiथऊbaud Weksteen <tweek@google.com>
 *		Peter Enderborg <Peter.Enderborg@sony.com>
 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM avc

#अगर !defined(_TRACE_SELINUX_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_SELINUX_H

#समावेश <linux/tracepoपूर्णांक.h>

TRACE_EVENT(selinux_audited,

	TP_PROTO(काष्ठा selinux_audit_data *sad,
		अक्षर *scontext,
		अक्षर *tcontext,
		स्थिर अक्षर *tclass
	),

	TP_ARGS(sad, scontext, tcontext, tclass),

	TP_STRUCT__entry(
		__field(u32, requested)
		__field(u32, denied)
		__field(u32, audited)
		__field(पूर्णांक, result)
		__string(scontext, scontext)
		__string(tcontext, tcontext)
		__string(tclass, tclass)
	),

	TP_fast_assign(
		__entry->requested	= sad->requested;
		__entry->denied		= sad->denied;
		__entry->audited	= sad->audited;
		__entry->result		= sad->result;
		__assign_str(tcontext, tcontext);
		__assign_str(scontext, scontext);
		__assign_str(tclass, tclass);
	),

	TP_prपूर्णांकk("requested=0x%x denied=0x%x audited=0x%x result=%d scontext=%s tcontext=%s tclass=%s",
		__entry->requested, __entry->denied, __entry->audited, __entry->result,
		__get_str(scontext), __get_str(tcontext), __get_str(tclass)
	)
);

#पूर्ण_अगर

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
