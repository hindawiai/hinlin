<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2019 Carlos Neira cneirabustos@gmail.com */

#समावेश <linux/bpf.h>
#समावेश <मानक_निवेशt.h>
#समावेश <bpf/bpf_helpers.h>

__u64 user_pid = 0;
__u64 user_tgid = 0;
__u64 dev = 0;
__u64 ino = 0;

SEC("tracepoint/syscalls/sys_enter_nanosleep")
पूर्णांक handler(स्थिर व्योम *ctx)
अणु
	काष्ठा bpf_pidns_info nsdata;

	अगर (bpf_get_ns_current_pid_tgid(dev, ino, &nsdata, माप(काष्ठा bpf_pidns_info)))
		वापस 0;

	user_pid = nsdata.pid;
	user_tgid = nsdata.tgid;

	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
