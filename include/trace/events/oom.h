<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM oom

#अगर !defined(_TRACE_OOM_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_OOM_H
#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <trace/events/mmflags.h>

TRACE_EVENT(oom_score_adj_update,

	TP_PROTO(काष्ठा task_काष्ठा *task),

	TP_ARGS(task),

	TP_STRUCT__entry(
		__field(	pid_t,	pid)
		__array(	अक्षर,	comm,	TASK_COMM_LEN )
		__field(	लघु,	oom_score_adj)
	),

	TP_fast_assign(
		__entry->pid = task->pid;
		स_नकल(__entry->comm, task->comm, TASK_COMM_LEN);
		__entry->oom_score_adj = task->संकेत->oom_score_adj;
	),

	TP_prपूर्णांकk("pid=%d comm=%s oom_score_adj=%hd",
		__entry->pid, __entry->comm, __entry->oom_score_adj)
);

TRACE_EVENT(reclaim_retry_zone,

	TP_PROTO(काष्ठा zoneref *zoneref,
		पूर्णांक order,
		अचिन्हित दीर्घ reclaimable,
		अचिन्हित दीर्घ available,
		अचिन्हित दीर्घ min_wmark,
		पूर्णांक no_progress_loops,
		bool wmark_check),

	TP_ARGS(zoneref, order, reclaimable, available, min_wmark, no_progress_loops, wmark_check),

	TP_STRUCT__entry(
		__field(	पूर्णांक, node)
		__field(	पूर्णांक, zone_idx)
		__field(	पूर्णांक,	order)
		__field(	अचिन्हित दीर्घ,	reclaimable)
		__field(	अचिन्हित दीर्घ,	available)
		__field(	अचिन्हित दीर्घ,	min_wmark)
		__field(	पूर्णांक,	no_progress_loops)
		__field(	bool,	wmark_check)
	),

	TP_fast_assign(
		__entry->node = zone_to_nid(zoneref->zone);
		__entry->zone_idx = zoneref->zone_idx;
		__entry->order = order;
		__entry->reclaimable = reclaimable;
		__entry->available = available;
		__entry->min_wmark = min_wmark;
		__entry->no_progress_loops = no_progress_loops;
		__entry->wmark_check = wmark_check;
	),

	TP_prपूर्णांकk("node=%d zone=%-8s order=%d reclaimable=%lu available=%lu min_wmark=%lu no_progress_loops=%d wmark_check=%d",
			__entry->node, __prपूर्णांक_symbolic(__entry->zone_idx, ZONE_TYPE),
			__entry->order,
			__entry->reclaimable, __entry->available, __entry->min_wmark,
			__entry->no_progress_loops,
			__entry->wmark_check)
);

TRACE_EVENT(mark_victim,
	TP_PROTO(पूर्णांक pid),

	TP_ARGS(pid),

	TP_STRUCT__entry(
		__field(पूर्णांक, pid)
	),

	TP_fast_assign(
		__entry->pid = pid;
	),

	TP_prपूर्णांकk("pid=%d", __entry->pid)
);

TRACE_EVENT(wake_reaper,
	TP_PROTO(पूर्णांक pid),

	TP_ARGS(pid),

	TP_STRUCT__entry(
		__field(पूर्णांक, pid)
	),

	TP_fast_assign(
		__entry->pid = pid;
	),

	TP_prपूर्णांकk("pid=%d", __entry->pid)
);

TRACE_EVENT(start_task_reaping,
	TP_PROTO(पूर्णांक pid),

	TP_ARGS(pid),

	TP_STRUCT__entry(
		__field(पूर्णांक, pid)
	),

	TP_fast_assign(
		__entry->pid = pid;
	),

	TP_prपूर्णांकk("pid=%d", __entry->pid)
);

TRACE_EVENT(finish_task_reaping,
	TP_PROTO(पूर्णांक pid),

	TP_ARGS(pid),

	TP_STRUCT__entry(
		__field(पूर्णांक, pid)
	),

	TP_fast_assign(
		__entry->pid = pid;
	),

	TP_prपूर्णांकk("pid=%d", __entry->pid)
);

TRACE_EVENT(skip_task_reaping,
	TP_PROTO(पूर्णांक pid),

	TP_ARGS(pid),

	TP_STRUCT__entry(
		__field(पूर्णांक, pid)
	),

	TP_fast_assign(
		__entry->pid = pid;
	),

	TP_prपूर्णांकk("pid=%d", __entry->pid)
);

#अगर_घोषित CONFIG_COMPACTION
TRACE_EVENT(compact_retry,

	TP_PROTO(पूर्णांक order,
		क्रमागत compact_priority priority,
		क्रमागत compact_result result,
		पूर्णांक retries,
		पूर्णांक max_retries,
		bool ret),

	TP_ARGS(order, priority, result, retries, max_retries, ret),

	TP_STRUCT__entry(
		__field(	पूर्णांक, order)
		__field(	पूर्णांक, priority)
		__field(	पूर्णांक, result)
		__field(	पूर्णांक, retries)
		__field(	पूर्णांक, max_retries)
		__field(	bool, ret)
	),

	TP_fast_assign(
		__entry->order = order;
		__entry->priority = priority;
		__entry->result = compact_result_to_feedback(result);
		__entry->retries = retries;
		__entry->max_retries = max_retries;
		__entry->ret = ret;
	),

	TP_prपूर्णांकk("order=%d priority=%s compaction_result=%s retries=%d max_retries=%d should_retry=%d",
			__entry->order,
			__prपूर्णांक_symbolic(__entry->priority, COMPACTION_PRIORITY),
			__prपूर्णांक_symbolic(__entry->result, COMPACTION_FEEDBACK),
			__entry->retries, __entry->max_retries,
			__entry->ret)
);
#पूर्ण_अगर /* CONFIG_COMPACTION */
#पूर्ण_अगर

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
