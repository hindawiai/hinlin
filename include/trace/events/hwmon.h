<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM hwmon

#अगर !defined(_TRACE_HWMON_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_HWMON_H

#समावेश <linux/tracepoपूर्णांक.h>

DECLARE_EVENT_CLASS(hwmon_attr_class,

	TP_PROTO(पूर्णांक index, स्थिर अक्षर *attr_name, दीर्घ val),

	TP_ARGS(index, attr_name, val),

	TP_STRUCT__entry(
		__field(पूर्णांक, index)
		__string(attr_name, attr_name)
		__field(दीर्घ, val)
	),

	TP_fast_assign(
		__entry->index = index;
		__assign_str(attr_name, attr_name);
		__entry->val = val;
	),

	TP_prपूर्णांकk("index=%d, attr_name=%s, val=%ld",
		  __entry->index,  __get_str(attr_name), __entry->val)
);

DEFINE_EVENT(hwmon_attr_class, hwmon_attr_show,

	TP_PROTO(पूर्णांक index, स्थिर अक्षर *attr_name, दीर्घ val),

	TP_ARGS(index, attr_name, val)
);

DEFINE_EVENT(hwmon_attr_class, hwmon_attr_store,

	TP_PROTO(पूर्णांक index, स्थिर अक्षर *attr_name, दीर्घ val),

	TP_ARGS(index, attr_name, val)
);

TRACE_EVENT(hwmon_attr_show_string,

	TP_PROTO(पूर्णांक index, स्थिर अक्षर *attr_name, स्थिर अक्षर *s),

	TP_ARGS(index, attr_name, s),

	TP_STRUCT__entry(
		__field(पूर्णांक, index)
		__string(attr_name, attr_name)
		__string(label, s)
	),

	TP_fast_assign(
		__entry->index = index;
		__assign_str(attr_name, attr_name);
		__assign_str(label, s);
	),

	TP_prपूर्णांकk("index=%d, attr_name=%s, val=%s",
		  __entry->index, __get_str(attr_name), __get_str(label))
);

#पूर्ण_अगर /* _TRACE_HWMON_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
