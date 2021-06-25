<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2020 Facebook

#समावेश <linux/bpf.h>
#समावेश <मानक_निवेशt.h>
#समावेश <linux/types.h>
#समावेश <bpf/bpf_helpers.h>

अक्षर _license[] SEC("license") = "GPL";

__u64 count = 0;

SEC("raw_tracepoint/sys_enter")
पूर्णांक test_enable_stats(व्योम *ctx)
अणु
	count += 1;
	वापस 0;
पूर्ण
