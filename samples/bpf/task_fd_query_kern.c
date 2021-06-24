<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/version.h>
#समावेश <linux/ptrace.h>
#समावेश <uapi/linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

SEC("kprobe/blk_mq_start_request")
पूर्णांक bpf_prog1(काष्ठा pt_regs *ctx)
अणु
	वापस 0;
पूर्ण

SEC("kretprobe/blk_account_io_done")
पूर्णांक bpf_prog2(काष्ठा pt_regs *ctx)
अणु
	वापस 0;
पूर्ण
अक्षर _license[] SEC("license") = "GPL";
u32 _version SEC("version") = LINUX_VERSION_CODE;
