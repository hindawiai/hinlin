<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

/*
 * Copyright 2020 Google LLC.
 */

#समावेश <त्रुटिसं.स>
#समावेश <linux/bpf.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/ip.h>
#समावेश <bpf/bpf_helpers.h>

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__uपूर्णांक(max_entries, 1);
	__type(key, __u32);
	__type(value, __u32);
पूर्ण test_result SEC(".maps");

SEC("cgroup_skb/egress")
पूर्णांक load_bytes_relative(काष्ठा __sk_buff *skb)
अणु
	काष्ठा ethhdr eth;
	काष्ठा iphdr iph;

	__u32 map_key = 0;
	__u32 test_passed = 0;

	/* MAC header is not set by the समय cgroup_skb/egress triggers */
	अगर (bpf_skb_load_bytes_relative(skb, 0, &eth, माप(eth),
					BPF_HDR_START_MAC) != -EFAULT)
		जाओ fail;

	अगर (bpf_skb_load_bytes_relative(skb, 0, &iph, माप(iph),
					BPF_HDR_START_NET))
		जाओ fail;

	अगर (bpf_skb_load_bytes_relative(skb, 0xffff, &iph, माप(iph),
					BPF_HDR_START_NET) != -EFAULT)
		जाओ fail;

	test_passed = 1;

fail:
	bpf_map_update_elem(&test_result, &map_key, &test_passed, BPF_ANY);

	वापस 1;
पूर्ण
