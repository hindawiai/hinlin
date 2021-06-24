<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_DEVMAP);
	__uपूर्णांक(max_entries, 8);
	__uपूर्णांक(key_size, माप(पूर्णांक));
	__uपूर्णांक(value_size, माप(पूर्णांक));
पूर्ण tx_port SEC(".maps");

SEC("redirect_map_0")
पूर्णांक xdp_redirect_map_0(काष्ठा xdp_md *xdp)
अणु
	वापस bpf_redirect_map(&tx_port, 0, 0);
पूर्ण

SEC("redirect_map_1")
पूर्णांक xdp_redirect_map_1(काष्ठा xdp_md *xdp)
अणु
	वापस bpf_redirect_map(&tx_port, 1, 0);
पूर्ण

SEC("redirect_map_2")
पूर्णांक xdp_redirect_map_2(काष्ठा xdp_md *xdp)
अणु
	वापस bpf_redirect_map(&tx_port, 2, 0);
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
