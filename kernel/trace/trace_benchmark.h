<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM benchmark

#अगर !defined(_TRACE_BENCHMARK_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_BENCHMARK_H

#समावेश <linux/tracepoपूर्णांक.h>

बाह्य पूर्णांक trace_benchmark_reg(व्योम);
बाह्य व्योम trace_benchmark_unreg(व्योम);

#घोषणा BENCHMARK_EVENT_STRLEN		128

TRACE_EVENT_FN(benchmark_event,

	TP_PROTO(स्थिर अक्षर *str),

	TP_ARGS(str),

	TP_STRUCT__entry(
		__array(	अक्षर,	str,	BENCHMARK_EVENT_STRLEN	)
	),

	TP_fast_assign(
		स_नकल(__entry->str, str, BENCHMARK_EVENT_STRLEN);
	),

	TP_prपूर्णांकk("%s", __entry->str),

	trace_benchmark_reg, trace_benchmark_unreg
);

#पूर्ण_अगर /* _TRACE_BENCHMARK_H */

#अघोषित TRACE_INCLUDE_खाता
#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#घोषणा TRACE_INCLUDE_खाता trace_benchmark

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
