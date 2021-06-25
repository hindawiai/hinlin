<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/*
 * If TRACE_SYSTEM is defined, that will be the directory created
 * in the ftrace directory under /sys/kernel/tracing/events/<प्रणाली>
 *
 * The define_trace.h below will also look क्रम a file name of
 * TRACE_SYSTEM.h where TRACE_SYSTEM is what is defined here.
 * In this हाल, it would look क्रम sample-trace.h
 *
 * If the header name will be dअगरferent than the प्रणाली name
 * (as in this हाल), then you can override the header name that
 * define_trace.h will look up by defining TRACE_INCLUDE_खाता
 *
 * This file is called sample-trace-array.h but we want the प्रणाली
 * to be called "sample-subsystem". Thereक्रमe we must define the name of this
 * file:
 *
 * #घोषणा TRACE_INCLUDE_खाता sample-trace-array
 *
 * As we करो in the bottom of this file.
 *
 * Notice that TRACE_SYSTEM should be defined outside of #अगर
 * protection, just like TRACE_INCLUDE_खाता.
 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM sample-subप्रणाली

/*
 * TRACE_SYSTEM is expected to be a C valid variable (alpha-numeric
 * and underscore), although it may start with numbers. If क्रम some
 * reason it is not, you need to add the following lines:
 */
#अघोषित TRACE_SYSTEM_VAR
#घोषणा TRACE_SYSTEM_VAR sample_subप्रणाली

/*
 * But the above is only needed अगर TRACE_SYSTEM is not alpha-numeric
 * and underscored. By शेष, TRACE_SYSTEM_VAR will be equal to
 * TRACE_SYSTEM. As TRACE_SYSTEM_VAR must be alpha-numeric, अगर
 * TRACE_SYSTEM is not, then TRACE_SYSTEM_VAR must be defined with
 * only alpha-numeric and underscores.
 *
 * The TRACE_SYSTEM_VAR is only used पूर्णांकernally and not visible to
 * user space.
 */

/*
 * Notice that this file is not रक्षित like a normal header.
 * We also must allow क्रम reपढ़ोing of this file. The
 *
 *  || defined(TRACE_HEADER_MULTI_READ)
 *
 * serves this purpose.
 */
#अगर !defined(_SAMPLE_TRACE_ARRAY_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _SAMPLE_TRACE_ARRAY_H

#समावेश <linux/tracepoपूर्णांक.h>
TRACE_EVENT(sample_event,

	TP_PROTO(पूर्णांक count, अचिन्हित दीर्घ समय),

	TP_ARGS(count, समय),

	TP_STRUCT__entry(
		__field(पूर्णांक, count)
		__field(अचिन्हित दीर्घ, समय)
	),

	TP_fast_assign(
		__entry->count = count;
		__entry->समय = समय;
	),

	TP_prपूर्णांकk("count value=%d at jiffies=%lu", __entry->count,
		__entry->समय)
	);
#पूर्ण_अगर

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#घोषणा TRACE_INCLUDE_खाता sample-trace-array
#समावेश <trace/define_trace.h>
