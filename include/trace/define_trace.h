<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Trace files that want to स्वतःmate creation of all tracepoपूर्णांकs defined
 * in their file should include this file. The following are macros that the
 * trace file may define:
 *
 * TRACE_SYSTEM defines the प्रणाली the tracepoपूर्णांक is क्रम
 *
 * TRACE_INCLUDE_खाता अगर the file name is something other than TRACE_SYSTEM.h
 *     This macro may be defined to tell define_trace.h what file to include.
 *     Note, leave off the ".h".
 *
 * TRACE_INCLUDE_PATH अगर the path is something other than core kernel include/trace
 *     then this macro can define the path to use. Note, the path is relative to
 *     define_trace.h, not the file including it. Full path names क्रम out of tree
 *     modules must be used.
 */

#अगर_घोषित CREATE_TRACE_POINTS

/* Prevent recursion */
#अघोषित CREATE_TRACE_POINTS

#समावेश <linux/stringअगरy.h>

#अघोषित TRACE_EVENT
#घोषणा TRACE_EVENT(name, proto, args, tकाष्ठा, assign, prपूर्णांक)	\
	DEFINE_TRACE(name, PARAMS(proto), PARAMS(args))

#अघोषित TRACE_EVENT_CONDITION
#घोषणा TRACE_EVENT_CONDITION(name, proto, args, cond, tकाष्ठा, assign, prपूर्णांक) \
	TRACE_EVENT(name,						\
		PARAMS(proto),						\
		PARAMS(args),						\
		PARAMS(tकाष्ठा),					\
		PARAMS(assign),						\
		PARAMS(prपूर्णांक))

#अघोषित TRACE_EVENT_FN
#घोषणा TRACE_EVENT_FN(name, proto, args, tकाष्ठा,		\
		assign, prपूर्णांक, reg, unreg)			\
	DEFINE_TRACE_FN(name, reg, unreg, PARAMS(proto), PARAMS(args))

#अघोषित TRACE_EVENT_FN_COND
#घोषणा TRACE_EVENT_FN_COND(name, proto, args, cond, tकाष्ठा,		\
		assign, prपूर्णांक, reg, unreg)			\
	DEFINE_TRACE_FN(name, reg, unreg, PARAMS(proto), PARAMS(args))

#अघोषित TRACE_EVENT_NOP
#घोषणा TRACE_EVENT_NOP(name, proto, args, काष्ठा, assign, prपूर्णांक)

#अघोषित DEFINE_EVENT_NOP
#घोषणा DEFINE_EVENT_NOP(ढाँचा, name, proto, args)

#अघोषित DEFINE_EVENT
#घोषणा DEFINE_EVENT(ढाँचा, name, proto, args) \
	DEFINE_TRACE(name, PARAMS(proto), PARAMS(args))

#अघोषित DEFINE_EVENT_FN
#घोषणा DEFINE_EVENT_FN(ढाँचा, name, proto, args, reg, unreg) \
	DEFINE_TRACE_FN(name, reg, unreg, PARAMS(proto), PARAMS(args))

#अघोषित DEFINE_EVENT_PRINT
#घोषणा DEFINE_EVENT_PRINT(ढाँचा, name, proto, args, prपूर्णांक)	\
	DEFINE_TRACE(name, PARAMS(proto), PARAMS(args))

#अघोषित DEFINE_EVENT_CONDITION
#घोषणा DEFINE_EVENT_CONDITION(ढाँचा, name, proto, args, cond) \
	DEFINE_EVENT(ढाँचा, name, PARAMS(proto), PARAMS(args))

#अघोषित DECLARE_TRACE
#घोषणा DECLARE_TRACE(name, proto, args)	\
	DEFINE_TRACE(name, PARAMS(proto), PARAMS(args))

#अघोषित TRACE_INCLUDE
#अघोषित __TRACE_INCLUDE

#अगर_अघोषित TRACE_INCLUDE_खाता
# define TRACE_INCLUDE_खाता TRACE_SYSTEM
# define UNDEF_TRACE_INCLUDE_खाता
#पूर्ण_अगर

#अगर_अघोषित TRACE_INCLUDE_PATH
# define __TRACE_INCLUDE(प्रणाली) <trace/events/प्रणाली.h>
# define UNDEF_TRACE_INCLUDE_PATH
#अन्यथा
# define __TRACE_INCLUDE(प्रणाली) __stringअगरy(TRACE_INCLUDE_PATH/प्रणाली.h)
#पूर्ण_अगर

# define TRACE_INCLUDE(प्रणाली) __TRACE_INCLUDE(प्रणाली)

/* Let the trace headers be reपढ़ो */
#घोषणा TRACE_HEADER_MULTI_READ

#समावेश TRACE_INCLUDE(TRACE_INCLUDE_खाता)

/* Make all खोलो coded DECLARE_TRACE nops */
#अघोषित DECLARE_TRACE
#घोषणा DECLARE_TRACE(name, proto, args)

#अगर_घोषित TRACEPOINTS_ENABLED
#समावेश <trace/trace_events.h>
#समावेश <trace/perf.h>
#समावेश <trace/bpf_probe.h>
#पूर्ण_अगर

#अघोषित TRACE_EVENT
#अघोषित TRACE_EVENT_FN
#अघोषित TRACE_EVENT_FN_COND
#अघोषित TRACE_EVENT_CONDITION
#अघोषित TRACE_EVENT_NOP
#अघोषित DEFINE_EVENT_NOP
#अघोषित DECLARE_EVENT_CLASS
#अघोषित DEFINE_EVENT
#अघोषित DEFINE_EVENT_FN
#अघोषित DEFINE_EVENT_PRINT
#अघोषित DEFINE_EVENT_CONDITION
#अघोषित TRACE_HEADER_MULTI_READ
#अघोषित DECLARE_TRACE

/* Only undef what we defined in this file */
#अगर_घोषित UNDEF_TRACE_INCLUDE_खाता
# undef TRACE_INCLUDE_खाता
# undef UNDEF_TRACE_INCLUDE_खाता
#पूर्ण_अगर

#अगर_घोषित UNDEF_TRACE_INCLUDE_PATH
# undef TRACE_INCLUDE_PATH
# undef UNDEF_TRACE_INCLUDE_PATH
#पूर्ण_अगर

/* We may be processing more files */
#घोषणा CREATE_TRACE_POINTS

#पूर्ण_अगर /* CREATE_TRACE_POINTS */
