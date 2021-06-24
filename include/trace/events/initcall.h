<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM initcall

#अगर !defined(_TRACE_INITCALL_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_INITCALL_H

#समावेश <linux/tracepoपूर्णांक.h>

TRACE_EVENT(initcall_level,

	TP_PROTO(स्थिर अक्षर *level),

	TP_ARGS(level),

	TP_STRUCT__entry(
		__string(level, level)
	),

	TP_fast_assign(
		__assign_str(level, level);
	),

	TP_prपूर्णांकk("level=%s", __get_str(level))
);

TRACE_EVENT(initcall_start,

	TP_PROTO(initcall_t func),

	TP_ARGS(func),

	TP_STRUCT__entry(
		/*
		 * Use field_काष्ठा to aव्योम is_चिन्हित_type()
		 * comparison of a function poपूर्णांकer
		 */
		__field_काष्ठा(initcall_t, func)
	),

	TP_fast_assign(
		__entry->func = func;
	),

	TP_prपूर्णांकk("func=%pS", __entry->func)
);

TRACE_EVENT(initcall_finish,

	TP_PROTO(initcall_t func, पूर्णांक ret),

	TP_ARGS(func, ret),

	TP_STRUCT__entry(
		/*
		 * Use field_काष्ठा to aव्योम is_चिन्हित_type()
		 * comparison of a function poपूर्णांकer
		 */
		__field_काष्ठा(initcall_t,	func)
		__field(पूर्णांक,			ret)
	),

	TP_fast_assign(
		__entry->func = func;
		__entry->ret = ret;
	),

	TP_prपूर्णांकk("func=%pS ret=%d", __entry->func, __entry->ret)
);

#पूर्ण_अगर /* अगर !defined(_TRACE_GPIO_H) || defined(TRACE_HEADER_MULTI_READ) */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
