<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश "vmlinux.h"
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>

__u64 fentry_called = 0;

SEC("fentry/test_pkt_md_access_new")
पूर्णांक BPF_PROG(fentry, काष्ठा sk_buff *skb)
अणु
	fentry_called = skb->len;
	वापस 0;
पूर्ण

__u64 fनिकास_called = 0;

SEC("fexit/test_pkt_md_access_new")
पूर्णांक BPF_PROG(fनिकास, काष्ठा sk_buff *skb)
अणु
	fनिकास_called = skb->len;
	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
