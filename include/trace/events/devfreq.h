<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM devfreq

#अगर !defined(_TRACE_DEVFREQ_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_DEVFREQ_H

#समावेश <linux/devfreq.h>
#समावेश <linux/tracepoपूर्णांक.h>

TRACE_EVENT(devfreq_frequency,
	TP_PROTO(काष्ठा devfreq *devfreq, अचिन्हित दीर्घ freq,
		 अचिन्हित दीर्घ prev_freq),

	TP_ARGS(devfreq, freq, prev_freq),

	TP_STRUCT__entry(
		__string(dev_name, dev_name(&devfreq->dev))
		__field(अचिन्हित दीर्घ, freq)
		__field(अचिन्हित दीर्घ, prev_freq)
		__field(अचिन्हित दीर्घ, busy_समय)
		__field(अचिन्हित दीर्घ, total_समय)
	),

	TP_fast_assign(
		__assign_str(dev_name, dev_name(&devfreq->dev));
		__entry->freq = freq;
		__entry->prev_freq = prev_freq;
		__entry->busy_समय = devfreq->last_status.busy_समय;
		__entry->total_समय = devfreq->last_status.total_समय;
	),

	TP_prपूर्णांकk("dev_name=%-30s freq=%-12lu prev_freq=%-12lu load=%-2lu",
		__get_str(dev_name), __entry->freq, __entry->prev_freq,
		__entry->total_समय == 0 ? 0 :
			(100 * __entry->busy_समय) / __entry->total_समय)
);

TRACE_EVENT(devfreq_monitor,
	TP_PROTO(काष्ठा devfreq *devfreq),

	TP_ARGS(devfreq),

	TP_STRUCT__entry(
		__field(अचिन्हित दीर्घ, freq)
		__field(अचिन्हित दीर्घ, busy_समय)
		__field(अचिन्हित दीर्घ, total_समय)
		__field(अचिन्हित पूर्णांक, polling_ms)
		__string(dev_name, dev_name(&devfreq->dev))
	),

	TP_fast_assign(
		__entry->freq = devfreq->previous_freq;
		__entry->busy_समय = devfreq->last_status.busy_समय;
		__entry->total_समय = devfreq->last_status.total_समय;
		__entry->polling_ms = devfreq->profile->polling_ms;
		__assign_str(dev_name, dev_name(&devfreq->dev));
	),

	TP_prपूर्णांकk("dev_name=%-30s freq=%-12lu polling_ms=%-3u load=%-2lu",
		__get_str(dev_name), __entry->freq, __entry->polling_ms,
		__entry->total_समय == 0 ? 0 :
			(100 * __entry->busy_समय) / __entry->total_समय)
);
#पूर्ण_अगर /* _TRACE_DEVFREQ_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
