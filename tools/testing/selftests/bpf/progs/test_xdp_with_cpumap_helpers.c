<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

#घोषणा IFINDEX_LO	1

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_CPUMAP);
	__uपूर्णांक(key_size, माप(__u32));
	__uपूर्णांक(value_size, माप(काष्ठा bpf_cpumap_val));
	__uपूर्णांक(max_entries, 4);
पूर्ण cpu_map SEC(".maps");

SEC("xdp_redir")
पूर्णांक xdp_redir_prog(काष्ठा xdp_md *ctx)
अणु
	वापस bpf_redirect_map(&cpu_map, 1, 0);
पूर्ण

SEC("xdp_dummy")
पूर्णांक xdp_dummy_prog(काष्ठा xdp_md *ctx)
अणु
	वापस XDP_PASS;
पूर्ण

SEC("xdp_cpumap/dummy_cm")
पूर्णांक xdp_dummy_cm(काष्ठा xdp_md *ctx)
अणु
	अगर (ctx->ingress_अगरindex == IFINDEX_LO)
		वापस XDP_DROP;

	वापस XDP_PASS;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
