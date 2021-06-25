<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM पूर्णांकel_ish

#अगर !defined(_TRACE_INTEL_ISH_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_INTEL_ISH_H

#समावेश <linux/tracepoपूर्णांक.h>

TRACE_EVENT(ishtp_dump,

	TP_PROTO(स्थिर अक्षर *message),

	TP_ARGS(message),

	TP_STRUCT__entry(
		__string(message, message)
	),

	TP_fast_assign(
		__assign_str(message, message);
	),

	TP_prपूर्णांकk("%s", __get_str(message))
);


#पूर्ण_अगर /* _TRACE_INTEL_ISH_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
