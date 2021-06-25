<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2020 Facebook */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM bpf_tesपंचांगod

#अगर !defined(_BPF_TESTMOD_EVENTS_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _BPF_TESTMOD_EVENTS_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश "bpf_testmod.h"

TRACE_EVENT(bpf_tesपंचांगod_test_पढ़ो,
	TP_PROTO(काष्ठा task_काष्ठा *task, काष्ठा bpf_tesपंचांगod_test_पढ़ो_ctx *ctx),
	TP_ARGS(task, ctx),
	TP_STRUCT__entry(
		__field(pid_t, pid)
		__array(अक्षर, comm, TASK_COMM_LEN)
		__field(loff_t, off)
		__field(माप_प्रकार, len)
	),
	TP_fast_assign(
		__entry->pid = task->pid;
		स_नकल(__entry->comm, task->comm, TASK_COMM_LEN);
		__entry->off = ctx->off;
		__entry->len = ctx->len;
	),
	TP_prपूर्णांकk("pid=%d comm=%s off=%llu len=%zu",
		  __entry->pid, __entry->comm, __entry->off, __entry->len)
);

/* A bare tracepoपूर्णांक with no event associated with it */
DECLARE_TRACE(bpf_tesपंचांगod_test_ग_लिखो_bare,
	TP_PROTO(काष्ठा task_काष्ठा *task, काष्ठा bpf_tesपंचांगod_test_ग_लिखो_ctx *ctx),
	TP_ARGS(task, ctx)
);

#पूर्ण_अगर /* _BPF_TESTMOD_EVENTS_H */

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#घोषणा TRACE_INCLUDE_खाता bpf_tesपंचांगod-events
#समावेश <trace/define_trace.h>
