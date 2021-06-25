<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2020 Facebook

#समावेश <linux/bpf.h>
#समावेश <मानक_निवेशt.h>
#समावेश <bpf/bpf_helpers.h>

अक्षर _license[] SEC("license") = "GPL";

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERF_EVENT_ARRAY);
	__uपूर्णांक(value_size, माप(पूर्णांक));
	__uपूर्णांक(key_size, माप(पूर्णांक));
पूर्ण perfbuf SEC(".maps");

स्थिर अस्थिर पूर्णांक batch_cnt = 0;

दीर्घ sample_val = 42;
दीर्घ dropped __attribute__((aligned(128))) = 0;

SEC("fentry/__x64_sys_getpgid")
पूर्णांक bench_perfbuf(व्योम *ctx)
अणु
	__u64 *sample;
	पूर्णांक i;

	क्रम (i = 0; i < batch_cnt; i++) अणु
		अगर (bpf_perf_event_output(ctx, &perfbuf, BPF_F_CURRENT_CPU,
					  &sample_val, माप(sample_val)))
			__sync_add_and_fetch(&dropped, 1);
	पूर्ण
	वापस 0;
पूर्ण
