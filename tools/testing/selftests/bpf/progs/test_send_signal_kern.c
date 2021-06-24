<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2019 Facebook
#समावेश <linux/bpf.h>
#समावेश <linux/version.h>
#समावेश <bpf/bpf_helpers.h>

__u32 sig = 0, pid = 0, status = 0, संकेत_thपढ़ो = 0;

अटल __always_अंतरभूत पूर्णांक bpf_send_संकेत_test(व्योम *ctx)
अणु
	पूर्णांक ret;

	अगर (status != 0 || sig == 0 || pid == 0)
		वापस 0;

	अगर ((bpf_get_current_pid_tgid() >> 32) == pid) अणु
		अगर (संकेत_thपढ़ो)
			ret = bpf_send_संकेत_thपढ़ो(sig);
		अन्यथा
			ret = bpf_send_संकेत(sig);
		अगर (ret == 0)
			status = 1;
	पूर्ण

	वापस 0;
पूर्ण

SEC("tracepoint/syscalls/sys_enter_nanosleep")
पूर्णांक send_संकेत_tp(व्योम *ctx)
अणु
	वापस bpf_send_संकेत_test(ctx);
पूर्ण

SEC("tracepoint/sched/sched_switch")
पूर्णांक send_संकेत_tp_sched(व्योम *ctx)
अणु
	वापस bpf_send_संकेत_test(ctx);
पूर्ण

SEC("perf_event")
पूर्णांक send_संकेत_perf(व्योम *ctx)
अणु
	वापस bpf_send_संकेत_test(ctx);
पूर्ण

अक्षर __license[] SEC("license") = "GPL";
