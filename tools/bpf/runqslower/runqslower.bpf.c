<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2019 Facebook
#समावेश "vmlinux.h"
#समावेश <bpf/bpf_helpers.h>
#समावेश "runqslower.h"

#घोषणा TASK_RUNNING 0
#घोषणा BPF_F_CURRENT_CPU 0xffffffffULL

स्थिर अस्थिर __u64 min_us = 0;
स्थिर अस्थिर pid_t targ_pid = 0;

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_TASK_STORAGE);
	__uपूर्णांक(map_flags, BPF_F_NO_PREALLOC);
	__type(key, पूर्णांक);
	__type(value, u64);
पूर्ण start SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERF_EVENT_ARRAY);
	__uपूर्णांक(key_size, माप(u32));
	__uपूर्णांक(value_size, माप(u32));
पूर्ण events SEC(".maps");

/* record enqueue बारtamp */
__always_अंतरभूत
अटल पूर्णांक trace_enqueue(काष्ठा task_काष्ठा *t)
अणु
	u32 pid = t->pid;
	u64 *ptr;

	अगर (!pid || (targ_pid && targ_pid != pid))
		वापस 0;

	ptr = bpf_task_storage_get(&start, t, 0,
				   BPF_LOCAL_STORAGE_GET_F_CREATE);
	अगर (!ptr)
		वापस 0;

	*ptr = bpf_kसमय_get_ns();
	वापस 0;
पूर्ण

SEC("tp_btf/sched_wakeup")
पूर्णांक handle__sched_wakeup(u64 *ctx)
अणु
	/* TP_PROTO(काष्ठा task_काष्ठा *p) */
	काष्ठा task_काष्ठा *p = (व्योम *)ctx[0];

	वापस trace_enqueue(p);
पूर्ण

SEC("tp_btf/sched_wakeup_new")
पूर्णांक handle__sched_wakeup_new(u64 *ctx)
अणु
	/* TP_PROTO(काष्ठा task_काष्ठा *p) */
	काष्ठा task_काष्ठा *p = (व्योम *)ctx[0];

	वापस trace_enqueue(p);
पूर्ण

SEC("tp_btf/sched_switch")
पूर्णांक handle__sched_चयन(u64 *ctx)
अणु
	/* TP_PROTO(bool preempt, काष्ठा task_काष्ठा *prev,
	 *	    काष्ठा task_काष्ठा *next)
	 */
	काष्ठा task_काष्ठा *prev = (काष्ठा task_काष्ठा *)ctx[1];
	काष्ठा task_काष्ठा *next = (काष्ठा task_काष्ठा *)ctx[2];
	काष्ठा event event = अणुपूर्ण;
	u64 *tsp, delta_us;
	दीर्घ state;
	u32 pid;

	/* ivcsw: treat like an enqueue event and store बारtamp */
	अगर (prev->state == TASK_RUNNING)
		trace_enqueue(prev);

	pid = next->pid;

	/* For pid mismatch, save a bpf_task_storage_get */
	अगर (!pid || (targ_pid && targ_pid != pid))
		वापस 0;

	/* fetch बारtamp and calculate delta */
	tsp = bpf_task_storage_get(&start, next, 0, 0);
	अगर (!tsp)
		वापस 0;   /* missed enqueue */

	delta_us = (bpf_kसमय_get_ns() - *tsp) / 1000;
	अगर (min_us && delta_us <= min_us)
		वापस 0;

	event.pid = pid;
	event.delta_us = delta_us;
	bpf_get_current_comm(&event.task, माप(event.task));

	/* output */
	bpf_perf_event_output(ctx, &events, BPF_F_CURRENT_CPU,
			      &event, माप(event));

	bpf_task_storage_delete(&start, next);
	वापस 0;
पूर्ण

अक्षर LICENSE[] SEC("license") = "GPL";
