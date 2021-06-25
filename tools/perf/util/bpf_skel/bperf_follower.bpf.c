<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
// Copyright (c) 2021 Facebook
#समावेश <linux/bpf.h>
#समावेश <linux/perf_event.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>
#समावेश "bperf.h"
#समावेश "bperf_u.h"

पढ़ोing_map dअगरf_पढ़ोings SEC(".maps");
पढ़ोing_map accum_पढ़ोings SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH);
	__uपूर्णांक(key_size, माप(__u32));
	__uपूर्णांक(value_size, माप(__u32));
पूर्ण filter SEC(".maps");

क्रमागत bperf_filter_type type = 0;
पूर्णांक enabled = 0;

SEC("fexit/XXX")
पूर्णांक BPF_PROG(fनिकास_XXX)
अणु
	काष्ठा bpf_perf_event_value *dअगरf_val, *accum_val;
	__u32 filter_key, zero = 0;
	__u32 *accum_key;

	अगर (!enabled)
		वापस 0;

	चयन (type) अणु
	हाल BPERF_FILTER_GLOBAL:
		accum_key = &zero;
		जाओ करो_add;
	हाल BPERF_FILTER_CPU:
		filter_key = bpf_get_smp_processor_id();
		अवरोध;
	हाल BPERF_FILTER_PID:
		filter_key = bpf_get_current_pid_tgid() & 0xffffffff;
		अवरोध;
	हाल BPERF_FILTER_TGID:
		filter_key = bpf_get_current_pid_tgid() >> 32;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	accum_key = bpf_map_lookup_elem(&filter, &filter_key);
	अगर (!accum_key)
		वापस 0;

करो_add:
	dअगरf_val = bpf_map_lookup_elem(&dअगरf_पढ़ोings, &zero);
	अगर (!dअगरf_val)
		वापस 0;

	accum_val = bpf_map_lookup_elem(&accum_पढ़ोings, accum_key);
	अगर (!accum_val)
		वापस 0;

	accum_val->counter += dअगरf_val->counter;
	accum_val->enabled += dअगरf_val->enabled;
	accum_val->running += dअगरf_val->running;

	वापस 0;
पूर्ण

अक्षर LICENSE[] SEC("license") = "Dual BSD/GPL";
