<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

अस्थिर स्थिर अक्षर bpf_metadata_a[] SEC(".rodata") = "foo";
अस्थिर स्थिर पूर्णांक bpf_metadata_b SEC(".rodata") = 1;

SEC("cgroup_skb/egress")
पूर्णांक prog(काष्ठा xdp_md *ctx)
अणु
	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
