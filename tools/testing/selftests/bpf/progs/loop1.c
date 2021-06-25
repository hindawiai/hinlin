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

SEC("raw_tracepoint/kfree_skb")
पूर्णांक nested_loops(अस्थिर काष्ठा pt_regs* ctx)
अणु
	पूर्णांक i, j, sum = 0, m;

	क्रम (j = 0; j < 300; j++)
		क्रम (i = 0; i < j; i++) अणु
			अगर (j & 1)
				m = PT_REGS_RC(ctx);
			अन्यथा
				m = j;
			sum += i * m;
		पूर्ण

	वापस sum;
पूर्ण
