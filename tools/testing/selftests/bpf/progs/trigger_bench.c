<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2020 Facebook

#समावेश <linux/bpf.h>
#समावेश <यंत्र/unistd.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>

अक्षर _license[] SEC("license") = "GPL";

दीर्घ hits = 0;

SEC("tp/syscalls/sys_enter_getpgid")
पूर्णांक bench_trigger_tp(व्योम *ctx)
अणु
	__sync_add_and_fetch(&hits, 1);
	वापस 0;
पूर्ण

SEC("raw_tp/sys_enter")
पूर्णांक BPF_PROG(bench_trigger_raw_tp, काष्ठा pt_regs *regs, दीर्घ id)
अणु
	अगर (id == __NR_getpgid)
		__sync_add_and_fetch(&hits, 1);
	वापस 0;
पूर्ण

SEC("kprobe/__x64_sys_getpgid")
पूर्णांक bench_trigger_kprobe(व्योम *ctx)
अणु
	__sync_add_and_fetch(&hits, 1);
	वापस 0;
पूर्ण

SEC("fentry/__x64_sys_getpgid")
पूर्णांक bench_trigger_fentry(व्योम *ctx)
अणु
	__sync_add_and_fetch(&hits, 1);
	वापस 0;
पूर्ण

SEC("fentry.s/__x64_sys_getpgid")
पूर्णांक bench_trigger_fentry_sleep(व्योम *ctx)
अणु
	__sync_add_and_fetch(&hits, 1);
	वापस 0;
पूर्ण

SEC("fmod_ret/__x64_sys_getpgid")
पूर्णांक bench_trigger_भ_शेषret(व्योम *ctx)
अणु
	__sync_add_and_fetch(&hits, 1);
	वापस -22;
पूर्ण
