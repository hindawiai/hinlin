<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2019 Facebook
#समावेश <linux/bpf.h>
#समावेश <stdbool.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_endian.h>
#समावेश <bpf/bpf_tracing.h>

__u64 ext_called = 0;

SEC("freplace/test_pkt_md_access")
पूर्णांक test_pkt_md_access_new(काष्ठा __sk_buff *skb)
अणु
	ext_called = skb->len;
	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
