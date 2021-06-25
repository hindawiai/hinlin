<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2017 Facebook

#समावेश <linux/ptrace.h>
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>

पूर्णांक kprobe_res = 0;
पूर्णांक kretprobe_res = 0;
पूर्णांक uprobe_res = 0;
पूर्णांक uretprobe_res = 0;

SEC("kprobe/sys_nanosleep")
पूर्णांक handle_kprobe(काष्ठा pt_regs *ctx)
अणु
	kprobe_res = 1;
	वापस 0;
पूर्ण

SEC("kretprobe/sys_nanosleep")
पूर्णांक BPF_KRETPROBE(handle_kretprobe)
अणु
	kretprobe_res = 2;
	वापस 0;
पूर्ण

SEC("uprobe/trigger_func")
पूर्णांक handle_uprobe(काष्ठा pt_regs *ctx)
अणु
	uprobe_res = 3;
	वापस 0;
पूर्ण

SEC("uretprobe/trigger_func")
पूर्णांक handle_uretprobe(काष्ठा pt_regs *ctx)
अणु
	uretprobe_res = 4;
	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
