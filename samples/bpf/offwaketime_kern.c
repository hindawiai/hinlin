<शैली गुरु>
/* Copyright (c) 2016 Facebook
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 */
#समावेश <uapi/linux/bpf.h>
#समावेश <uapi/linux/ptrace.h>
#समावेश <uapi/linux/perf_event.h>
#समावेश <linux/version.h>
#समावेश <linux/sched.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>

#घोषणा _(P)                                                                   \
	(अणु                                                                     \
		typeof(P) val;                                                 \
		bpf_probe_पढ़ो_kernel(&val, माप(val), &(P));                \
		val;                                                           \
	पूर्ण)

#घोषणा MINBLOCK_US	1

काष्ठा key_t अणु
	अक्षर waker[TASK_COMM_LEN];
	अक्षर target[TASK_COMM_LEN];
	u32 wret;
	u32 tret;
पूर्ण;

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH);
	__type(key, काष्ठा key_t);
	__type(value, u64);
	__uपूर्णांक(max_entries, 10000);
पूर्ण counts SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH);
	__type(key, u32);
	__type(value, u64);
	__uपूर्णांक(max_entries, 10000);
पूर्ण start SEC(".maps");

काष्ठा wokeby_t अणु
	अक्षर name[TASK_COMM_LEN];
	u32 ret;
पूर्ण;

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH);
	__type(key, u32);
	__type(value, काष्ठा wokeby_t);
	__uपूर्णांक(max_entries, 10000);
पूर्ण wokeby SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_STACK_TRACE);
	__uपूर्णांक(key_size, माप(u32));
	__uपूर्णांक(value_size, PERF_MAX_STACK_DEPTH * माप(u64));
	__uपूर्णांक(max_entries, 10000);
पूर्ण stackmap SEC(".maps");

#घोषणा STACKID_FLAGS (0 | BPF_F_FAST_STACK_CMP)

SEC("kprobe/try_to_wake_up")
पूर्णांक waker(काष्ठा pt_regs *ctx)
अणु
	काष्ठा task_काष्ठा *p = (व्योम *) PT_REGS_PARM1(ctx);
	काष्ठा wokeby_t woke;
	u32 pid;

	pid = _(p->pid);

	bpf_get_current_comm(&woke.name, माप(woke.name));
	woke.ret = bpf_get_stackid(ctx, &stackmap, STACKID_FLAGS);

	bpf_map_update_elem(&wokeby, &pid, &woke, BPF_ANY);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक update_counts(व्योम *ctx, u32 pid, u64 delta)
अणु
	काष्ठा wokeby_t *woke;
	u64 zero = 0, *val;
	काष्ठा key_t key;

	__builtin_स_रखो(&key.waker, 0, माप(key.waker));
	bpf_get_current_comm(&key.target, माप(key.target));
	key.tret = bpf_get_stackid(ctx, &stackmap, STACKID_FLAGS);
	key.wret = 0;

	woke = bpf_map_lookup_elem(&wokeby, &pid);
	अगर (woke) अणु
		key.wret = woke->ret;
		__builtin_स_नकल(&key.waker, woke->name, माप(key.waker));
		bpf_map_delete_elem(&wokeby, &pid);
	पूर्ण

	val = bpf_map_lookup_elem(&counts, &key);
	अगर (!val) अणु
		bpf_map_update_elem(&counts, &key, &zero, BPF_NOEXIST);
		val = bpf_map_lookup_elem(&counts, &key);
		अगर (!val)
			वापस 0;
	पूर्ण
	(*val) += delta;
	वापस 0;
पूर्ण

#अगर 1
/* taken from /sys/kernel/debug/tracing/events/sched/sched_चयन/क्रमmat */
काष्ठा sched_चयन_args अणु
	अचिन्हित दीर्घ दीर्घ pad;
	अक्षर prev_comm[16];
	पूर्णांक prev_pid;
	पूर्णांक prev_prio;
	दीर्घ दीर्घ prev_state;
	अक्षर next_comm[16];
	पूर्णांक next_pid;
	पूर्णांक next_prio;
पूर्ण;
SEC("tracepoint/sched/sched_switch")
पूर्णांक oncpu(काष्ठा sched_चयन_args *ctx)
अणु
	/* record previous thपढ़ो sleep समय */
	u32 pid = ctx->prev_pid;
#अन्यथा
SEC("kprobe/finish_task_switch")
पूर्णांक oncpu(काष्ठा pt_regs *ctx)
अणु
	काष्ठा task_काष्ठा *p = (व्योम *) PT_REGS_PARM1(ctx);
	/* record previous thपढ़ो sleep समय */
	u32 pid = _(p->pid);
#पूर्ण_अगर
	u64 delta, ts, *tsp;

	ts = bpf_kसमय_get_ns();
	bpf_map_update_elem(&start, &pid, &ts, BPF_ANY);

	/* calculate current thपढ़ो's delta समय */
	pid = bpf_get_current_pid_tgid();
	tsp = bpf_map_lookup_elem(&start, &pid);
	अगर (!tsp)
		/* missed start or filtered */
		वापस 0;

	delta = bpf_kसमय_get_ns() - *tsp;
	bpf_map_delete_elem(&start, &pid);
	delta = delta / 1000;
	अगर (delta < MINBLOCK_US)
		वापस 0;

	वापस update_counts(ctx, pid, delta);
पूर्ण
अक्षर _license[] SEC("license") = "GPL";
u32 _version SEC("version") = LINUX_VERSION_CODE;
