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
	पूर्णांक i = 0;

	जबतक (true) अणु
		अगर (PT_REGS_RC(ctx) & 1)
			i += 3;
		अन्यथा
			i += 7;
		अगर (i > 40)
			अवरोध;
	पूर्ण

	वापस i;
पूर्ण
