<शैली गुरु>
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM rtc

#अगर !defined(_TRACE_RTC_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_RTC_H

#समावेश <linux/rtc.h>
#समावेश <linux/tracepoपूर्णांक.h>

DECLARE_EVENT_CLASS(rtc_समय_alarm_class,

	TP_PROTO(समय64_t secs, पूर्णांक err),

	TP_ARGS(secs, err),

	TP_STRUCT__entry(
		__field(समय64_t, secs)
		__field(पूर्णांक, err)
	),

	TP_fast_assign(
		__entry->secs = secs;
		__entry->err = err;
	),

	TP_prपूर्णांकk("UTC (%lld) (%d)",
		  __entry->secs, __entry->err
	)
);

DEFINE_EVENT(rtc_समय_alarm_class, rtc_set_समय,

	TP_PROTO(समय64_t secs, पूर्णांक err),

	TP_ARGS(secs, err)
);

DEFINE_EVENT(rtc_समय_alarm_class, rtc_पढ़ो_समय,

	TP_PROTO(समय64_t secs, पूर्णांक err),

	TP_ARGS(secs, err)
);

DEFINE_EVENT(rtc_समय_alarm_class, rtc_set_alarm,

	TP_PROTO(समय64_t secs, पूर्णांक err),

	TP_ARGS(secs, err)
);

DEFINE_EVENT(rtc_समय_alarm_class, rtc_पढ़ो_alarm,

	TP_PROTO(समय64_t secs, पूर्णांक err),

	TP_ARGS(secs, err)
);

TRACE_EVENT(rtc_irq_set_freq,

	TP_PROTO(पूर्णांक freq, पूर्णांक err),

	TP_ARGS(freq, err),

	TP_STRUCT__entry(
		__field(पूर्णांक, freq)
		__field(पूर्णांक, err)
	),

	TP_fast_assign(
		__entry->freq = freq;
		__entry->err = err;
	),

	TP_prपूर्णांकk("set RTC periodic IRQ frequency:%u (%d)",
		  __entry->freq, __entry->err
	)
);

TRACE_EVENT(rtc_irq_set_state,

	TP_PROTO(पूर्णांक enabled, पूर्णांक err),

	TP_ARGS(enabled, err),

	TP_STRUCT__entry(
		__field(पूर्णांक, enabled)
		__field(पूर्णांक, err)
	),

	TP_fast_assign(
		__entry->enabled = enabled;
		__entry->err = err;
	),

	TP_prपूर्णांकk("%s RTC 2^N Hz periodic IRQs (%d)",
		  __entry->enabled ? "enable" : "disable",
		  __entry->err
	)
);

TRACE_EVENT(rtc_alarm_irq_enable,

	TP_PROTO(अचिन्हित पूर्णांक enabled, पूर्णांक err),

	TP_ARGS(enabled, err),

	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, enabled)
		__field(पूर्णांक, err)
	),

	TP_fast_assign(
		__entry->enabled = enabled;
		__entry->err = err;
	),

	TP_prपूर्णांकk("%s RTC alarm IRQ (%d)",
		  __entry->enabled ? "enable" : "disable",
		  __entry->err
	)
);

DECLARE_EVENT_CLASS(rtc_offset_class,

	TP_PROTO(दीर्घ offset, पूर्णांक err),

	TP_ARGS(offset, err),

	TP_STRUCT__entry(
		__field(दीर्घ, offset)
		__field(पूर्णांक, err)
	),

	TP_fast_assign(
		__entry->offset = offset;
		__entry->err = err;
	),

	TP_prपूर्णांकk("RTC offset: %ld (%d)",
		  __entry->offset, __entry->err
	)
);

DEFINE_EVENT(rtc_offset_class, rtc_set_offset,

	TP_PROTO(दीर्घ offset, पूर्णांक err),

	TP_ARGS(offset, err)
);

DEFINE_EVENT(rtc_offset_class, rtc_पढ़ो_offset,

	TP_PROTO(दीर्घ offset, पूर्णांक err),

	TP_ARGS(offset, err)
);

DECLARE_EVENT_CLASS(rtc_समयr_class,

	TP_PROTO(काष्ठा rtc_समयr *समयr),

	TP_ARGS(समयr),

	TP_STRUCT__entry(
		__field(काष्ठा rtc_समयr *, समयr)
		__field(kसमय_प्रकार, expires)
		__field(kसमय_प्रकार, period)
	),

	TP_fast_assign(
		__entry->समयr = समयr;
		__entry->expires = समयr->node.expires;
		__entry->period = समयr->period;
	),

	TP_prपूर्णांकk("RTC timer:(%p) expires:%lld period:%lld",
		  __entry->समयr, __entry->expires, __entry->period
	)
);

DEFINE_EVENT(rtc_समयr_class, rtc_समयr_enqueue,

	TP_PROTO(काष्ठा rtc_समयr *समयr),

	TP_ARGS(समयr)
);

DEFINE_EVENT(rtc_समयr_class, rtc_समयr_dequeue,

	TP_PROTO(काष्ठा rtc_समयr *समयr),

	TP_ARGS(समयr)
);

DEFINE_EVENT(rtc_समयr_class, rtc_समयr_fired,

	TP_PROTO(काष्ठा rtc_समयr *समयr),

	TP_ARGS(समयr)
);

#पूर्ण_अगर /* _TRACE_RTC_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
