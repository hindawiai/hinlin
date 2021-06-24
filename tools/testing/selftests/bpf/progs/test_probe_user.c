<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/ptrace.h>
#समावेश <linux/bpf.h>

#समावेश <netinet/in.h>

#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>

अटल काष्ठा sockaddr_in old;

SEC("kprobe/__sys_connect")
पूर्णांक BPF_KPROBE(handle_sys_connect)
अणु
	व्योम *ptr = (व्योम *)PT_REGS_PARM2(ctx);
	काष्ठा sockaddr_in new;

	bpf_probe_पढ़ो_user(&old, माप(old), ptr);
	__builtin_स_रखो(&new, 0xab, माप(new));
	bpf_probe_ग_लिखो_user(ptr, &new, माप(new));

	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
