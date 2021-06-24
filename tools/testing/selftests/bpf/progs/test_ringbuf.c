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

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_RINGBUF);
पूर्ण ringbuf SEC(".maps");

/* inमाला_दो */
पूर्णांक pid = 0;
दीर्घ value = 0;
दीर्घ flags = 0;

/* outमाला_दो */
दीर्घ total = 0;
दीर्घ discarded = 0;
दीर्घ dropped = 0;

दीर्घ avail_data = 0;
दीर्घ ring_size = 0;
दीर्घ cons_pos = 0;
दीर्घ prod_pos = 0;

/* inner state */
दीर्घ seq = 0;

SEC("tp/syscalls/sys_enter_getpgid")
पूर्णांक test_ringbuf(व्योम *ctx)
अणु
	पूर्णांक cur_pid = bpf_get_current_pid_tgid() >> 32;
	काष्ठा sample *sample;
	पूर्णांक zero = 0;

	अगर (cur_pid != pid)
		वापस 0;

	sample = bpf_ringbuf_reserve(&ringbuf, माप(*sample), 0);
	अगर (!sample) अणु
		__sync_fetch_and_add(&dropped, 1);
		वापस 1;
	पूर्ण

	sample->pid = pid;
	bpf_get_current_comm(sample->comm, माप(sample->comm));
	sample->value = value;

	sample->seq = seq++;
	__sync_fetch_and_add(&total, 1);

	अगर (sample->seq & 1) अणु
		/* copy from reserved sample to a new one... */
		bpf_ringbuf_output(&ringbuf, sample, माप(*sample), flags);
		/* ...and then discard reserved sample */
		bpf_ringbuf_discard(sample, flags);
		__sync_fetch_and_add(&discarded, 1);
	पूर्ण अन्यथा अणु
		bpf_ringbuf_submit(sample, flags);
	पूर्ण

	avail_data = bpf_ringbuf_query(&ringbuf, BPF_RB_AVAIL_DATA);
	ring_size = bpf_ringbuf_query(&ringbuf, BPF_RB_RING_SIZE);
	cons_pos = bpf_ringbuf_query(&ringbuf, BPF_RB_CONS_POS);
	prod_pos = bpf_ringbuf_query(&ringbuf, BPF_RB_PROD_POS);

	वापस 0;
पूर्ण
