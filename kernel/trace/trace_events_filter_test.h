<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM test

#अगर !defined(_TRACE_TEST_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_TEST_H

#समावेश <linux/tracepoपूर्णांक.h>

TRACE_EVENT(ftrace_test_filter,

	TP_PROTO(पूर्णांक a, पूर्णांक b, पूर्णांक c, पूर्णांक d, पूर्णांक e, पूर्णांक f, पूर्णांक g, पूर्णांक h),

	TP_ARGS(a, b, c, d, e, f, g, h),

	TP_STRUCT__entry(
		__field(पूर्णांक, a)
		__field(पूर्णांक, b)
		__field(पूर्णांक, c)
		__field(पूर्णांक, d)
		__field(पूर्णांक, e)
		__field(पूर्णांक, f)
		__field(पूर्णांक, g)
		__field(पूर्णांक, h)
	),

	TP_fast_assign(
		__entry->a = a;
		__entry->b = b;
		__entry->c = c;
		__entry->d = d;
		__entry->e = e;
		__entry->f = f;
		__entry->g = g;
		__entry->h = h;
	),

	TP_prपूर्णांकk("a %d, b %d, c %d, d %d, e %d, f %d, g %d, h %d",
		  __entry->a, __entry->b, __entry->c, __entry->d,
		  __entry->e, __entry->f, __entry->g, __entry->h)
);

#पूर्ण_अगर /* _TRACE_TEST_H || TRACE_HEADER_MULTI_READ */

#अघोषित TRACE_INCLUDE_PATH
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_PATH .
#घोषणा TRACE_INCLUDE_खाता trace_events_filter_test

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
