<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Copyright 2020 Google LLC.
 */

#समावेश "vmlinux.h"
#समावेश <त्रुटिसं.स>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>

u32 monitored_pid = 0;

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_RINGBUF);
	__uपूर्णांक(max_entries, 1 << 12);
पूर्ण ringbuf SEC(".maps");

अक्षर _license[] SEC("license") = "GPL";

SEC("lsm.s/bprm_committed_creds")
व्योम BPF_PROG(ima, काष्ठा linux_binprm *bprm)
अणु
	u64 ima_hash = 0;
	u64 *sample;
	पूर्णांक ret;
	u32 pid;

	pid = bpf_get_current_pid_tgid() >> 32;
	अगर (pid == monitored_pid) अणु
		ret = bpf_ima_inode_hash(bprm->file->f_inode, &ima_hash,
					 माप(ima_hash));
		अगर (ret < 0 || ima_hash == 0)
			वापस;

		sample = bpf_ringbuf_reserve(&ringbuf, माप(u64), 0);
		अगर (!sample)
			वापस;

		*sample = ima_hash;
		bpf_ringbuf_submit(sample, 0);
	पूर्ण

	वापस;
पूर्ण
