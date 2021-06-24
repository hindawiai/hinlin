<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM context_tracking

#अगर !defined(_TRACE_CONTEXT_TRACKING_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_CONTEXT_TRACKING_H

#समावेश <linux/tracepoपूर्णांक.h>

DECLARE_EVENT_CLASS(context_tracking_user,

	TP_PROTO(पूर्णांक dummy),

	TP_ARGS(dummy),

	TP_STRUCT__entry(
		__field( पूर्णांक,	dummy	)
	),

	TP_fast_assign(
		__entry->dummy		= dummy;
	),

	TP_prपूर्णांकk("%s", "")
);

/**
 * user_enter - called when the kernel resumes to userspace
 * @dummy:	dummy arg to make trace event macro happy
 *
 * This event occurs when the kernel resumes to userspace  after
 * an exception or a syscall.
 */
DEFINE_EVENT(context_tracking_user, user_enter,

	TP_PROTO(पूर्णांक dummy),

	TP_ARGS(dummy)
);

/**
 * user_निकास - called when userspace enters the kernel
 * @dummy:	dummy arg to make trace event macro happy
 *
 * This event occurs when userspace enters the kernel through
 * an exception or a syscall.
 */
DEFINE_EVENT(context_tracking_user, user_निकास,

	TP_PROTO(पूर्णांक dummy),

	TP_ARGS(dummy)
);


#पूर्ण_अगर /*  _TRACE_CONTEXT_TRACKING_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
