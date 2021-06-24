<शैली गुरु>
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM netlink

#अगर !defined(_TRACE_NETLINK_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_NETLINK_H

#समावेश <linux/tracepoपूर्णांक.h>

TRACE_EVENT(netlink_extack,

	TP_PROTO(स्थिर अक्षर *msg),

	TP_ARGS(msg),

	TP_STRUCT__entry(
		__string(	msg,	msg	)
	),

	TP_fast_assign(
		__assign_str(msg, msg);
	),

	TP_prपूर्णांकk("msg=%s", __get_str(msg))
);

#पूर्ण_अगर /* _TRACE_NETLINK_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
