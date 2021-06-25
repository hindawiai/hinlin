<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2020 Facebook

#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

अक्षर _license[] SEC("license") = "GPL";

काष्ठा sample अणु
	पूर्णांक pid;
	पूर्णांक seq;
	दीर्घ value;
	अक्षर comm[16];
पूर्ण;

काष्ठा ringbuf_map अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_RINGBUF);
पूर्ण ringbuf1 SEC(".maps"),
  ringbuf2 SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY_OF_MAPS);
	__uपूर्णांक(max_entries, 4);
	__type(key, पूर्णांक);
	__array(values, काष्ठा ringbuf_map);
पूर्ण ringbuf_arr SEC(".maps") = अणु
	.values = अणु
		[0] = &ringbuf1,
		[2] = &ringbuf2,
	पूर्ण,
पूर्ण;

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH_OF_MAPS);
	__uपूर्णांक(max_entries, 1);
	__type(key, पूर्णांक);
	__array(values, काष्ठा ringbuf_map);
पूर्ण ringbuf_hash SEC(".maps") = अणु
	.values = अणु
		[0] = &ringbuf1,
	पूर्ण,
पूर्ण;

/* inमाला_दो */
पूर्णांक pid = 0;
पूर्णांक target_ring = 0;
दीर्घ value = 0;

/* outमाला_दो */
दीर्घ total = 0;
दीर्घ dropped = 0;
दीर्घ skipped = 0;

SEC("tp/syscalls/sys_enter_getpgid")
पूर्णांक test_ringbuf(व्योम *ctx)
अणु
	पूर्णांक cur_pid = bpf_get_current_pid_tgid() >> 32;
	काष्ठा sample *sample;
	व्योम *rb;
	पूर्णांक zero = 0;

	अगर (cur_pid != pid)
		वापस 0;

	rb = bpf_map_lookup_elem(&ringbuf_arr, &target_ring);
	अगर (!rb) अणु
		skipped += 1;
		वापस 1;
	पूर्ण

	sample = bpf_ringbuf_reserve(rb, माप(*sample), 0);
	अगर (!sample) अणु
		dropped += 1;
		वापस 1;
	पूर्ण

	sample->pid = pid;
	bpf_get_current_comm(sample->comm, माप(sample->comm));
	sample->value = value;

	sample->seq = total;
	total += 1;

	bpf_ringbuf_submit(sample, 0);

	वापस 0;
पूर्ण
