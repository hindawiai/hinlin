<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2018 Facebook

#समावेश <linux/bpf.h>
#समावेश <linux/pkt_cls.h>

#समावेश <माला.स>

#समावेश <bpf/bpf_helpers.h>

#घोषणा NUM_CGROUP_LEVELS	4

काष्ठा bpf_map_def SEC("maps") cgroup_ids = अणु
	.type = BPF_MAP_TYPE_ARRAY,
	.key_size = माप(__u32),
	.value_size = माप(__u64),
	.max_entries = NUM_CGROUP_LEVELS,
पूर्ण;

अटल __always_अंतरभूत व्योम log_nth_level(काष्ठा __sk_buff *skb, __u32 level)
अणु
	__u64 id;

	/* [1] &level passed to बाह्यal function that may change it, it's
	 *     incompatible with loop unroll.
	 */
	id = bpf_skb_ancestor_cgroup_id(skb, level);
	bpf_map_update_elem(&cgroup_ids, &level, &id, 0);
पूर्ण

SEC("cgroup_id_logger")
पूर्णांक log_cgroup_id(काष्ठा __sk_buff *skb)
अणु
	/* Loop unroll can't be used here due to [1]. Unrolling manually.
	 * Number of calls should be in sync with NUM_CGROUP_LEVELS.
	 */
	log_nth_level(skb, 0);
	log_nth_level(skb, 1);
	log_nth_level(skb, 2);
	log_nth_level(skb, 3);

	वापस TC_ACT_OK;
पूर्ण

पूर्णांक _version SEC("version") = 1;

अक्षर _license[] SEC("license") = "GPL";
