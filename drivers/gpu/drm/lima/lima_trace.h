<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */
/* Copyright 2020 Qiang Yu <yuq825@gmail.com> */

#अगर !defined(_LIMA_TRACE_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _LIMA_TRACE_H_

#समावेश <linux/tracepoपूर्णांक.h>

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM lima
#घोषणा TRACE_INCLUDE_खाता lima_trace

DECLARE_EVENT_CLASS(lima_task,
	TP_PROTO(काष्ठा lima_sched_task *task),
	TP_ARGS(task),
	TP_STRUCT__entry(
		__field(uपूर्णांक64_t, task_id)
		__field(अचिन्हित पूर्णांक, context)
		__field(अचिन्हित पूर्णांक, seqno)
		__string(pipe, task->base.sched->name)
		),

	TP_fast_assign(
		__entry->task_id = task->base.id;
		__entry->context = task->base.s_fence->finished.context;
		__entry->seqno = task->base.s_fence->finished.seqno;
		__assign_str(pipe, task->base.sched->name)
		),

	TP_prपूर्णांकk("task=%llu, context=%u seqno=%u pipe=%s",
		  __entry->task_id, __entry->context, __entry->seqno,
		  __get_str(pipe))
);

DEFINE_EVENT(lima_task, lima_task_submit,
	     TP_PROTO(काष्ठा lima_sched_task *task),
	     TP_ARGS(task)
);

DEFINE_EVENT(lima_task, lima_task_run,
	     TP_PROTO(काष्ठा lima_sched_task *task),
	     TP_ARGS(task)
);

#पूर्ण_अगर

/* This part must be outside protection */
#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH ../../drivers/gpu/drm/lima
#समावेश <trace/define_trace.h>
