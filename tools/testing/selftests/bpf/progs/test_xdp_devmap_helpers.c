<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* fails to load without expected_attach_type = BPF_XDP_DEVMAP
 * because of access to egress_अगरindex
 */
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

SEC("xdp_dm_log")
पूर्णांक xdpdm_devlog(काष्ठा xdp_md *ctx)
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
