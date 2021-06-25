<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2019 Facebook
#समावेश <linux/sched.h>
#समावेश <linux/ptrace.h>
#समावेश <मानक_निवेशt.h>
#समावेश <मानकघोष.स>
#समावेश <stdbool.h>
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>

अक्षर _license[] SEC("license") = "GPL";

SEC("raw_tracepoint/consume_skb")
पूर्णांक जबतक_true(अस्थिर काष्ठा pt_regs* ctx)
अणु
	__u64 i = 0, sum = 0;
	करो अणु
		i++;
		sum += PT_REGS_RC(ctx);
	पूर्ण जबतक (i < 0x100000000ULL);
	वापस sum;
पूर्ण
