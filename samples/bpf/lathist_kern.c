<शैली गुरु>
/* Copyright (c) 2013-2015 PLUMgrid, http://plumgrid.com
 * Copyright (c) 2015 BMW Car IT GmbH
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 */
#समावेश <linux/version.h>
#समावेश <linux/ptrace.h>
#समावेश <uapi/linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

#घोषणा MAX_ENTRIES	20
#घोषणा MAX_CPU		4

/* We need to stick to अटल allocated memory (an array instead of
 * hash table) because managing dynamic memory from the
 * trace_preempt_[on|off] tracepoपूर्णांकs hooks is not supported.
 */

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__type(key, पूर्णांक);
	__type(value, u64);
	__uपूर्णांक(max_entries, MAX_CPU);
पूर्ण my_map SEC(".maps");

SEC("kprobe/trace_preempt_off")
पूर्णांक bpf_prog1(काष्ठा pt_regs *ctx)
अणु
	पूर्णांक cpu = bpf_get_smp_processor_id();
	u64 *ts = bpf_map_lookup_elem(&my_map, &cpu);

	अगर (ts)
		*ts = bpf_kसमय_get_ns();

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक log2(अचिन्हित पूर्णांक v)
अणु
	अचिन्हित पूर्णांक r;
	अचिन्हित पूर्णांक shअगरt;

	r = (v > 0xFFFF) << 4; v >>= r;
	shअगरt = (v > 0xFF) << 3; v >>= shअगरt; r |= shअगरt;
	shअगरt = (v > 0xF) << 2; v >>= shअगरt; r |= shअगरt;
	shअगरt = (v > 0x3) << 1; v >>= shअगरt; r |= shअगरt;
	r |= (v >> 1);

	वापस r;
पूर्ण

अटल अचिन्हित पूर्णांक log2l(अचिन्हित दीर्घ v)
अणु
	अचिन्हित पूर्णांक hi = v >> 32;

	अगर (hi)
		वापस log2(hi) + 32;
	अन्यथा
		वापस log2(v);
पूर्ण

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__type(key, पूर्णांक);
	__type(value, दीर्घ);
	__uपूर्णांक(max_entries, MAX_CPU * MAX_ENTRIES);
पूर्ण my_lat SEC(".maps");

SEC("kprobe/trace_preempt_on")
पूर्णांक bpf_prog2(काष्ठा pt_regs *ctx)
अणु
	u64 *ts, cur_ts, delta;
	पूर्णांक key, cpu;
	दीर्घ *val;

	cpu = bpf_get_smp_processor_id();
	ts = bpf_map_lookup_elem(&my_map, &cpu);
	अगर (!ts)
		वापस 0;

	cur_ts = bpf_kसमय_get_ns();
	delta = log2l(cur_ts - *ts);

	अगर (delta > MAX_ENTRIES - 1)
		delta = MAX_ENTRIES - 1;

	key = cpu * MAX_ENTRIES + delta;
	val = bpf_map_lookup_elem(&my_lat, &key);
	अगर (val)
		__sync_fetch_and_add((दीर्घ *)val, 1);

	वापस 0;

पूर्ण

अक्षर _license[] SEC("license") = "GPL";
u32 _version SEC("version") = LINUX_VERSION_CODE;
