<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर !defined(_TRACE_QLA_H_) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_QLA_H_

#समावेश <linux/tracepoपूर्णांक.h>

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM qla

#घोषणा QLA_MSG_MAX 256

#आशय GCC diagnostic push
#अगर_अघोषित __clang__
#आशय GCC diagnostic ignored "-Wsuggest-attribute=format"
#पूर्ण_अगर

DECLARE_EVENT_CLASS(qla_log_event,
	TP_PROTO(स्थिर अक्षर *buf,
		काष्ठा va_क्रमmat *vaf),

	TP_ARGS(buf, vaf),

	TP_STRUCT__entry(
		__string(buf, buf)
		__dynamic_array(अक्षर, msg, QLA_MSG_MAX)
	),
	TP_fast_assign(
		__assign_str(buf, buf);
		vsnम_लिखो(__get_str(msg), QLA_MSG_MAX, vaf->fmt, *vaf->va);
	),

	TP_prपूर्णांकk("%s %s", __get_str(buf), __get_str(msg))
);

#आशय GCC diagnostic pop

DEFINE_EVENT(qla_log_event, ql_dbg_log,
	TP_PROTO(स्थिर अक्षर *buf, काष्ठा va_क्रमmat *vaf),
	TP_ARGS(buf, vaf)
);

#पूर्ण_अगर /* _TRACE_QLA_H */

#घोषणा TRACE_INCLUDE_खाता qla

#समावेश <trace/define_trace.h>
