<शैली गुरु>
/* Copyright 2016 Netflix, Inc.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 */
#समावेश <linux/ptrace.h>
#समावेश <uapi/linux/bpf.h>
#समावेश <uapi/linux/bpf_perf_event.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>

#घोषणा MAX_IPS		8192

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH);
	__type(key, u64);
	__type(value, u32);
	__uपूर्णांक(max_entries, MAX_IPS);
पूर्ण ip_map SEC(".maps");

SEC("perf_event")
पूर्णांक करो_sample(काष्ठा bpf_perf_event_data *ctx)
अणु
	u64 ip;
	u32 *value, init_val = 1;

	ip = PT_REGS_IP(&ctx->regs);
	value = bpf_map_lookup_elem(&ip_map, &ip);
	अगर (value)
		*value += 1;
	अन्यथा
		/* E2BIG not tested क्रम this example only */
		bpf_map_update_elem(&ip_map, &ip, &init_val, BPF_NOEXIST);

	वापस 0;
पूर्ण
अक्षर _license[] SEC("license") = "GPL";
