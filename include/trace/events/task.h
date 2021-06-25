<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM task

#अगर !defined(_TRACE_TASK_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_TASK_H
#समावेश <linux/tracepoपूर्णांक.h>

TRACE_EVENT(task_newtask,

	TP_PROTO(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ clone_flags),

	TP_ARGS(task, clone_flags),

	TP_STRUCT__entry(
		__field(	pid_t,	pid)
		__array(	अक्षर,	comm, TASK_COMM_LEN)
		__field( अचिन्हित दीर्घ, clone_flags)
		__field(	लघु,	oom_score_adj)
	),

	TP_fast_assign(
		__entry->pid = task->pid;
		स_नकल(__entry->comm, task->comm, TASK_COMM_LEN);
		__entry->clone_flags = clone_flags;
		__entry->oom_score_adj = task->संकेत->oom_score_adj;
	),

	TP_prपूर्णांकk("pid=%d comm=%s clone_flags=%lx oom_score_adj=%hd",
		__entry->pid, __entry->comm,
		__entry->clone_flags, __entry->oom_score_adj)
);

TRACE_EVENT(task_नाम,

	TP_PROTO(काष्ठा task_काष्ठा *task, स्थिर अक्षर *comm),

	TP_ARGS(task, comm),

	TP_STRUCT__entry(
		__field(	pid_t,	pid)
		__array(	अक्षर, oldcomm,  TASK_COMM_LEN)
		__array(	अक्षर, newcomm,  TASK_COMM_LEN)
		__field(	लघु,	oom_score_adj)
	),

	TP_fast_assign(
		__entry->pid = task->pid;
		स_नकल(entry->oldcomm, task->comm, TASK_COMM_LEN);
		strlcpy(entry->newcomm, comm, TASK_COMM_LEN);
		__entry->oom_score_adj = task->संकेत->oom_score_adj;
	),

	TP_prपूर्णांकk("pid=%d oldcomm=%s newcomm=%s oom_score_adj=%hd",
		__entry->pid, __entry->oldcomm,
		__entry->newcomm, __entry->oom_score_adj)
);

#पूर्ण_अगर

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
