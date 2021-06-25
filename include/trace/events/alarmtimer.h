<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM alarmसमयr

#अगर !defined(_TRACE_ALARMTIMER_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_ALARMTIMER_H

#समावेश <linux/alarmसमयr.h>
#समावेश <linux/rtc.h>
#समावेश <linux/tracepoपूर्णांक.h>

TRACE_DEFINE_ENUM(ALARM_REALTIME);
TRACE_DEFINE_ENUM(ALARM_BOOTTIME);
TRACE_DEFINE_ENUM(ALARM_REALTIME_FREEZER);
TRACE_DEFINE_ENUM(ALARM_BOOTTIME_FREEZER);

#घोषणा show_alarm_type(type)	__prपूर्णांक_flags(type, " | ",	\
	अणु 1 << ALARM_REALTIME, "REALTIME" पूर्ण,			\
	अणु 1 << ALARM_BOOTTIME, "BOOTTIME" पूर्ण,			\
	अणु 1 << ALARM_REALTIME_FREEZER, "REALTIME Freezer" पूर्ण,	\
	अणु 1 << ALARM_BOOTTIME_FREEZER, "BOOTTIME Freezer" पूर्ण)

TRACE_EVENT(alarmसमयr_suspend,

	TP_PROTO(kसमय_प्रकार expires, पूर्णांक flag),

	TP_ARGS(expires, flag),

	TP_STRUCT__entry(
		__field(s64, expires)
		__field(अचिन्हित अक्षर, alarm_type)
	),

	TP_fast_assign(
		__entry->expires = expires;
		__entry->alarm_type = flag;
	),

	TP_prपूर्णांकk("alarmtimer type:%s expires:%llu",
		  show_alarm_type((1 << __entry->alarm_type)),
		  __entry->expires
	)
);

DECLARE_EVENT_CLASS(alarm_class,

	TP_PROTO(काष्ठा alarm *alarm, kसमय_प्रकार now),

	TP_ARGS(alarm, now),

	TP_STRUCT__entry(
		__field(व्योम *,	alarm)
		__field(अचिन्हित अक्षर, alarm_type)
		__field(s64, expires)
		__field(s64, now)
	),

	TP_fast_assign(
		__entry->alarm = alarm;
		__entry->alarm_type = alarm->type;
		__entry->expires = alarm->node.expires;
		__entry->now = now;
	),

	TP_prपूर्णांकk("alarmtimer:%p type:%s expires:%llu now:%llu",
		  __entry->alarm,
		  show_alarm_type((1 << __entry->alarm_type)),
		  __entry->expires,
		  __entry->now
	)
);

DEFINE_EVENT(alarm_class, alarmसमयr_fired,

	TP_PROTO(काष्ठा alarm *alarm, kसमय_प्रकार now),

	TP_ARGS(alarm, now)
);

DEFINE_EVENT(alarm_class, alarmसमयr_start,

	TP_PROTO(काष्ठा alarm *alarm, kसमय_प्रकार now),

	TP_ARGS(alarm, now)
);

DEFINE_EVENT(alarm_class, alarmसमयr_cancel,

	TP_PROTO(काष्ठा alarm *alarm, kसमय_प्रकार now),

	TP_ARGS(alarm, now)
);

#पूर्ण_अगर /* _TRACE_ALARMTIMER_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
