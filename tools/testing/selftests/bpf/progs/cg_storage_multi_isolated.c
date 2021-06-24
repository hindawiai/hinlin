<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

/*
 * Copyright 2020 Google LLC.
 */

#समावेश <त्रुटिसं.स>
#समावेश <linux/bpf.h>
#समावेश <linux/ip.h>
#समावेश <linux/udp.h>
#समावेश <bpf/bpf_helpers.h>

#समावेश "progs/cg_storage_multi.h"

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_CGROUP_STORAGE);
	__type(key, काष्ठा bpf_cgroup_storage_key);
	__type(value, काष्ठा cgroup_value);
पूर्ण cgroup_storage SEC(".maps");

__u32 invocations = 0;

SEC("cgroup_skb/egress/1")
पूर्णांक egress1(काष्ठा __sk_buff *skb)
अणु
	काष्ठा cgroup_value *ptr_cg_storage =
		bpf_get_local_storage(&cgroup_storage, 0);

	__sync_fetch_and_add(&ptr_cg_storage->egress_pkts, 1);
	__sync_fetch_and_add(&invocations, 1);

	वापस 1;
पूर्ण

SEC("cgroup_skb/egress/2")
पूर्णांक egress2(काष्ठा __sk_buff *skb)
अणु
	काष्ठा cgroup_value *ptr_cg_storage =
		bpf_get_local_storage(&cgroup_storage, 0);

	__sync_fetch_and_add(&ptr_cg_storage->egress_pkts, 1);
	__sync_fetch_and_add(&invocations, 1);

	वापस 1;
पूर्ण

SEC("cgroup_skb/ingress")
पूर्णांक ingress(काष्ठा __sk_buff *skb)
अणु
	काष्ठा cgroup_value *ptr_cg_storage =
		bpf_get_local_storage(&cgroup_storage, 0);

	__sync_fetch_and_add(&ptr_cg_storage->ingress_pkts, 1);
	__sync_fetch_and_add(&invocations, 1);

	वापस 1;
पूर्ण
