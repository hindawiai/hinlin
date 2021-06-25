<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2017 Facebook

#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

/* taken from /sys/kernel/debug/tracing/events/sched/sched_चयन/क्रमmat */
काष्ठा sched_चयन_args अणु
	अचिन्हित दीर्घ दीर्घ pad;
	अक्षर prev_comm[16];
	पूर्णांक prev_pid;
	पूर्णांक prev_prio;
	दीर्घ दीर्घ prev_state;
	अक्षर next_comm[16];
	पूर्णांक next_pid;
	पूर्णांक next_prio;
पूर्ण;

SEC("tracepoint/sched/sched_switch")
पूर्णांक oncpu(काष्ठा sched_चयन_args *ctx)
अणु
	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
__u32 _version SEC("version") = 1; /* ignored by tracepoपूर्णांकs, required by libbpf.a */
