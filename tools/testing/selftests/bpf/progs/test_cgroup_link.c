<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2020 Facebook
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

पूर्णांक calls = 0;
पूर्णांक alt_calls = 0;

SEC("cgroup_skb/egress1")
पूर्णांक egress(काष्ठा __sk_buff *skb)
अणु
	__sync_fetch_and_add(&calls, 1);
	वापस 1;
पूर्ण

SEC("cgroup_skb/egress2")
पूर्णांक egress_alt(काष्ठा __sk_buff *skb)
अणु
	__sync_fetch_and_add(&alt_calls, 1);
	वापस 1;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";

