<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM workqueue

#अगर !defined(_TRACE_WORKQUEUE_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_WORKQUEUE_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/workqueue.h>

काष्ठा pool_workqueue;

/**
 * workqueue_queue_work - called when a work माला_लो queued
 * @req_cpu:	the requested cpu
 * @pwq:	poपूर्णांकer to काष्ठा pool_workqueue
 * @work:	poपूर्णांकer to काष्ठा work_काष्ठा
 *
 * This event occurs when a work is queued immediately or once a
 * delayed work is actually queued on a workqueue (ie: once the delay
 * has been reached).
 */
TRACE_EVENT(workqueue_queue_work,

	TP_PROTO(अचिन्हित पूर्णांक req_cpu, काष्ठा pool_workqueue *pwq,
		 काष्ठा work_काष्ठा *work),

	TP_ARGS(req_cpu, pwq, work),

	TP_STRUCT__entry(
		__field( व्योम *,	work	)
		__field( व्योम *,	function)
		__string( workqueue,	pwq->wq->name)
		__field( अचिन्हित पूर्णांक,	req_cpu	)
		__field( अचिन्हित पूर्णांक,	cpu	)
	),

	TP_fast_assign(
		__entry->work		= work;
		__entry->function	= work->func;
		__assign_str(workqueue, pwq->wq->name);
		__entry->req_cpu	= req_cpu;
		__entry->cpu		= pwq->pool->cpu;
	),

	TP_prपूर्णांकk("work struct=%p function=%ps workqueue=%s req_cpu=%u cpu=%u",
		  __entry->work, __entry->function, __get_str(workqueue),
		  __entry->req_cpu, __entry->cpu)
);

/**
 * workqueue_activate_work - called when a work माला_लो activated
 * @work:	poपूर्णांकer to काष्ठा work_काष्ठा
 *
 * This event occurs when a queued work is put on the active queue,
 * which happens immediately after queueing unless @max_active limit
 * is reached.
 */
TRACE_EVENT(workqueue_activate_work,

	TP_PROTO(काष्ठा work_काष्ठा *work),

	TP_ARGS(work),

	TP_STRUCT__entry(
		__field( व्योम *,	work	)
	),

	TP_fast_assign(
		__entry->work		= work;
	),

	TP_prपूर्णांकk("work struct %p", __entry->work)
);

/**
 * workqueue_execute_start - called immediately beक्रमe the workqueue callback
 * @work:	poपूर्णांकer to काष्ठा work_काष्ठा
 *
 * Allows to track workqueue execution.
 */
TRACE_EVENT(workqueue_execute_start,

	TP_PROTO(काष्ठा work_काष्ठा *work),

	TP_ARGS(work),

	TP_STRUCT__entry(
		__field( व्योम *,	work	)
		__field( व्योम *,	function)
	),

	TP_fast_assign(
		__entry->work		= work;
		__entry->function	= work->func;
	),

	TP_prपूर्णांकk("work struct %p: function %ps", __entry->work, __entry->function)
);

/**
 * workqueue_execute_end - called immediately after the workqueue callback
 * @work:	poपूर्णांकer to काष्ठा work_काष्ठा
 * @function:   poपूर्णांकer to worker function
 *
 * Allows to track workqueue execution.
 */
TRACE_EVENT(workqueue_execute_end,

	TP_PROTO(काष्ठा work_काष्ठा *work, work_func_t function),

	TP_ARGS(work, function),

	TP_STRUCT__entry(
		__field( व्योम *,	work	)
		__field( व्योम *,	function)
	),

	TP_fast_assign(
		__entry->work		= work;
		__entry->function	= function;
	),

	TP_prपूर्णांकk("work struct %p: function %ps", __entry->work, __entry->function)
);

#पूर्ण_अगर /*  _TRACE_WORKQUEUE_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
