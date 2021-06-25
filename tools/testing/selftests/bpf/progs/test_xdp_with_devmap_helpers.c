<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_DEVMAP);
	__uपूर्णांक(key_size, माप(__u32));
	__uपूर्णांक(value_size, माप(काष्ठा bpf_devmap_val));
	__uपूर्णांक(max_entries, 4);
पूर्ण dm_ports SEC(".maps");

SEC("xdp_redir")
पूर्णांक xdp_redir_prog(काष्ठा xdp_md *ctx)
अणु
	वापस bpf_redirect_map(&dm_ports, 1, 0);
पूर्ण

/* invalid program on DEVMAP entry;
 * SEC name means expected attach type not set
 */
SEC("xdp_dummy")
पूर्णांक xdp_dummy_prog(काष्ठा xdp_md *ctx)
अणु
	वापस XDP_PASS;
पूर्ण

/* valid program on DEVMAP entry via SEC name;
 * has access to egress and ingress अगरindex
 */
SEC("xdp_devmap/map_prog")
पूर्णांक xdp_dummy_dm(काष्ठा xdp_md *ctx)
अणु
	अक्षर fmt[] = "devmap redirect: dev %u -> dev %u len %u\n";
	व्योम *data_end = (व्योम *)(दीर्घ)ctx->data_end;
	व्योम *data = (व्योम *)(दीर्घ)ctx->data;
	अचिन्हित पूर्णांक len = data_end - data;

	bpf_trace_prपूर्णांकk(fmt, माप(fmt),
			 ctx->ingress_अगरindex, ctx->egress_अगरindex, len);

	वापस XDP_PASS;
पूर्ण
अक्षर _license[] SEC("license") = "GPL";
