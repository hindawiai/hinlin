<शैली गुरु>
/* Copyright (c) 2016 Facebook
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 */
#समावेश <linux/ptrace.h>
#समावेश <uapi/linux/bpf.h>
#समावेश <uapi/linux/bpf_perf_event.h>
#समावेश <uapi/linux/perf_event.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>

काष्ठा key_t अणु
	अक्षर comm[TASK_COMM_LEN];
	u32 kernstack;
	u32 userstack;
पूर्ण;

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH);
	__type(key, काष्ठा key_t);
	__type(value, u64);
	__uपूर्णांक(max_entries, 10000);
पूर्ण counts SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_STACK_TRACE);
	__uपूर्णांक(key_size, माप(u32));
	__uपूर्णांक(value_size, PERF_MAX_STACK_DEPTH * माप(u64));
	__uपूर्णांक(max_entries, 10000);
पूर्ण stackmap SEC(".maps");

#घोषणा KERN_STACKID_FLAGS (0 | BPF_F_FAST_STACK_CMP)
#घोषणा USER_STACKID_FLAGS (0 | BPF_F_FAST_STACK_CMP | BPF_F_USER_STACK)

SEC("perf_event")
पूर्णांक bpf_prog1(काष्ठा bpf_perf_event_data *ctx)
अणु
	अक्षर समय_fmt1[] = "Time Enabled: %llu, Time Running: %llu";
	अक्षर समय_fmt2[] = "Get Time Failed, ErrCode: %d";
	अक्षर addr_fmt[] = "Address recorded on event: %llx";
	अक्षर fmt[] = "CPU-%d period %lld ip %llx";
	u32 cpu = bpf_get_smp_processor_id();
	काष्ठा bpf_perf_event_value value_buf;
	काष्ठा key_t key;
	u64 *val, one = 1;
	पूर्णांक ret;

	अगर (ctx->sample_period < 10000)
		/* ignore warmup */
		वापस 0;
	bpf_get_current_comm(&key.comm, माप(key.comm));
	key.kernstack = bpf_get_stackid(ctx, &stackmap, KERN_STACKID_FLAGS);
	key.userstack = bpf_get_stackid(ctx, &stackmap, USER_STACKID_FLAGS);
	अगर ((पूर्णांक)key.kernstack < 0 && (पूर्णांक)key.userstack < 0) अणु
		bpf_trace_prपूर्णांकk(fmt, माप(fmt), cpu, ctx->sample_period,
				 PT_REGS_IP(&ctx->regs));
		वापस 0;
	पूर्ण

	ret = bpf_perf_prog_पढ़ो_value(ctx, (व्योम *)&value_buf, माप(काष्ठा bpf_perf_event_value));
	अगर (!ret)
	  bpf_trace_prपूर्णांकk(समय_fmt1, माप(समय_fmt1), value_buf.enabled, value_buf.running);
	अन्यथा
	  bpf_trace_prपूर्णांकk(समय_fmt2, माप(समय_fmt2), ret);

	अगर (ctx->addr != 0)
	  bpf_trace_prपूर्णांकk(addr_fmt, माप(addr_fmt), ctx->addr);

	val = bpf_map_lookup_elem(&counts, &key);
	अगर (val)
		(*val)++;
	अन्यथा
		bpf_map_update_elem(&counts, &key, &one, BPF_NOEXIST);
	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
