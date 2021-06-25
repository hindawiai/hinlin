<शैली गुरु>
/* Copyright (c) 2016 Facebook
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 */
#समावेश <uapi/linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

/* from /sys/kernel/debug/tracing/events/task/task_नाम/क्रमmat */
काष्ठा task_नाम अणु
	__u64 pad;
	__u32 pid;
	अक्षर oldcomm[16];
	अक्षर newcomm[16];
	__u16 oom_score_adj;
पूर्ण;
SEC("tracepoint/task/task_rename")
पूर्णांक prog(काष्ठा task_नाम *ctx)
अणु
	वापस 0;
पूर्ण

/* from /sys/kernel/debug/tracing/events/अक्रमom/uअक्रमom_पढ़ो/क्रमmat */
काष्ठा uअक्रमom_पढ़ो अणु
	__u64 pad;
	पूर्णांक got_bits;
	पूर्णांक pool_left;
	पूर्णांक input_left;
पूर्ण;
SEC("tracepoint/random/urandom_read")
पूर्णांक prog2(काष्ठा uअक्रमom_पढ़ो *ctx)
अणु
	वापस 0;
पूर्ण
अक्षर _license[] SEC("license") = "GPL";
