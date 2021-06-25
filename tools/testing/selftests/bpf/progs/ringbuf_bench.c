<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2020 Facebook

#समावेश <linux/bpf.h>
#समावेश <मानक_निवेशt.h>
#समावेश <bpf/bpf_helpers.h>

अक्षर _license[] SEC("license") = "GPL";

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_RINGBUF);
पूर्ण ringbuf SEC(".maps");

स्थिर अस्थिर पूर्णांक batch_cnt = 0;
स्थिर अस्थिर दीर्घ use_output = 0;

दीर्घ sample_val = 42;
दीर्घ dropped __attribute__((aligned(128))) = 0;

स्थिर अस्थिर दीर्घ wakeup_data_size = 0;

अटल __always_अंतरभूत दीर्घ get_flags()
अणु
	दीर्घ sz;

	अगर (!wakeup_data_size)
		वापस 0;

	sz = bpf_ringbuf_query(&ringbuf, BPF_RB_AVAIL_DATA);
	वापस sz >= wakeup_data_size ? BPF_RB_FORCE_WAKEUP : BPF_RB_NO_WAKEUP;
पूर्ण

SEC("fentry/__x64_sys_getpgid")
पूर्णांक bench_ringbuf(व्योम *ctx)
अणु
	दीर्घ *sample, flags;
	पूर्णांक i;

	अगर (!use_output) अणु
		क्रम (i = 0; i < batch_cnt; i++) अणु
			sample = bpf_ringbuf_reserve(&ringbuf,
					             माप(sample_val), 0);
			अगर (!sample) अणु
				__sync_add_and_fetch(&dropped, 1);
			पूर्ण अन्यथा अणु
				*sample = sample_val;
				flags = get_flags();
				bpf_ringbuf_submit(sample, flags);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < batch_cnt; i++) अणु
			flags = get_flags();
			अगर (bpf_ringbuf_output(&ringbuf, &sample_val,
					       माप(sample_val), flags))
				__sync_add_and_fetch(&dropped, 1);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
