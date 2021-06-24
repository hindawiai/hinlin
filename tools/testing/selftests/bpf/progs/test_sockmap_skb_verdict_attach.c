<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "vmlinux.h"
#समावेश <bpf/bpf_helpers.h>

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_SOCKMAP);
	__uपूर्णांक(max_entries, 2);
	__type(key, __u32);
	__type(value, __u64);
पूर्ण sock_map SEC(".maps");

SEC("sk_skb/skb_verdict")
पूर्णांक prog_skb_verdict(काष्ठा __sk_buff *skb)
अणु
	वापस SK_DROP;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
