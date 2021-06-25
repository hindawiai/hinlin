<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM kyber

#अगर !defined(_TRACE_KYBER_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_KYBER_H

#समावेश <linux/blkdev.h>
#समावेश <linux/tracepoपूर्णांक.h>

#घोषणा DOMAIN_LEN		16
#घोषणा LATENCY_TYPE_LEN	8

TRACE_EVENT(kyber_latency,

	TP_PROTO(काष्ठा request_queue *q, स्थिर अक्षर *करोमुख्य, स्थिर अक्षर *type,
		 अचिन्हित पूर्णांक percentile, अचिन्हित पूर्णांक numerator,
		 अचिन्हित पूर्णांक denominator, अचिन्हित पूर्णांक samples),

	TP_ARGS(q, करोमुख्य, type, percentile, numerator, denominator, samples),

	TP_STRUCT__entry(
		__field(	dev_t,	dev				)
		__array(	अक्षर,	करोमुख्य,	DOMAIN_LEN		)
		__array(	अक्षर,	type,	LATENCY_TYPE_LEN	)
		__field(	u8,	percentile			)
		__field(	u8,	numerator			)
		__field(	u8,	denominator			)
		__field(	अचिन्हित पूर्णांक,	samples			)
	),

	TP_fast_assign(
		__entry->dev		= disk_devt(queue_to_disk(q));
		strlcpy(__entry->करोमुख्य, करोमुख्य, माप(__entry->करोमुख्य));
		strlcpy(__entry->type, type, माप(__entry->type));
		__entry->percentile	= percentile;
		__entry->numerator	= numerator;
		__entry->denominator	= denominator;
		__entry->samples	= samples;
	),

	TP_prपूर्णांकk("%d,%d %s %s p%u %u/%u samples=%u",
		  MAJOR(__entry->dev), MINOR(__entry->dev), __entry->करोमुख्य,
		  __entry->type, __entry->percentile, __entry->numerator,
		  __entry->denominator, __entry->samples)
);

TRACE_EVENT(kyber_adjust,

	TP_PROTO(काष्ठा request_queue *q, स्थिर अक्षर *करोमुख्य,
		 अचिन्हित पूर्णांक depth),

	TP_ARGS(q, करोमुख्य, depth),

	TP_STRUCT__entry(
		__field(	dev_t,	dev			)
		__array(	अक्षर,	करोमुख्य,	DOMAIN_LEN	)
		__field(	अचिन्हित पूर्णांक,	depth		)
	),

	TP_fast_assign(
		__entry->dev		= disk_devt(queue_to_disk(q));
		strlcpy(__entry->करोमुख्य, करोमुख्य, माप(__entry->करोमुख्य));
		__entry->depth		= depth;
	),

	TP_prपूर्णांकk("%d,%d %s %u",
		  MAJOR(__entry->dev), MINOR(__entry->dev), __entry->करोमुख्य,
		  __entry->depth)
);

TRACE_EVENT(kyber_throttled,

	TP_PROTO(काष्ठा request_queue *q, स्थिर अक्षर *करोमुख्य),

	TP_ARGS(q, करोमुख्य),

	TP_STRUCT__entry(
		__field(	dev_t,	dev			)
		__array(	अक्षर,	करोमुख्य,	DOMAIN_LEN	)
	),

	TP_fast_assign(
		__entry->dev		= disk_devt(queue_to_disk(q));
		strlcpy(__entry->करोमुख्य, करोमुख्य, माप(__entry->करोमुख्य));
	),

	TP_prपूर्णांकk("%d,%d %s", MAJOR(__entry->dev), MINOR(__entry->dev),
		  __entry->करोमुख्य)
);

#घोषणा _TRACE_KYBER_H
#पूर्ण_अगर /* _TRACE_KYBER_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
