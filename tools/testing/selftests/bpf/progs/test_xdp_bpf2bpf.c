<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_tracing.h>
#समावेश <bpf/bpf_helpers.h>

अक्षर _license[] SEC("license") = "GPL";

काष्ठा net_device अणु
	/* Structure करोes not need to contain all entries,
	 * as "preserve_access_index" will use BTF to fix this...
	 */
	पूर्णांक अगरindex;
पूर्ण __attribute__((preserve_access_index));

काष्ठा xdp_rxq_info अणु
	/* Structure करोes not need to contain all entries,
	 * as "preserve_access_index" will use BTF to fix this...
	 */
	काष्ठा net_device *dev;
	__u32 queue_index;
पूर्ण __attribute__((preserve_access_index));

काष्ठा xdp_buff अणु
	व्योम *data;
	व्योम *data_end;
	व्योम *data_meta;
	व्योम *data_hard_start;
	अचिन्हित दीर्घ handle;
	काष्ठा xdp_rxq_info *rxq;
पूर्ण __attribute__((preserve_access_index));

काष्ठा meta अणु
	पूर्णांक अगरindex;
	पूर्णांक pkt_len;
पूर्ण;

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERF_EVENT_ARRAY);
	__uपूर्णांक(key_size, माप(पूर्णांक));
	__uपूर्णांक(value_size, माप(पूर्णांक));
पूर्ण perf_buf_map SEC(".maps");

__u64 test_result_fentry = 0;
SEC("fentry/FUNC")
पूर्णांक BPF_PROG(trace_on_entry, काष्ठा xdp_buff *xdp)
अणु
	काष्ठा meta meta;
	व्योम *data_end = (व्योम *)(दीर्घ)xdp->data_end;
	व्योम *data = (व्योम *)(दीर्घ)xdp->data;

	meta.अगरindex = xdp->rxq->dev->अगरindex;
	meta.pkt_len = data_end - data;
	bpf_xdp_output(xdp, &perf_buf_map,
		       ((__u64) meta.pkt_len << 32) |
		       BPF_F_CURRENT_CPU,
		       &meta, माप(meta));

	test_result_fentry = xdp->rxq->dev->अगरindex;
	वापस 0;
पूर्ण

__u64 test_result_fनिकास = 0;
SEC("fexit/FUNC")
पूर्णांक BPF_PROG(trace_on_निकास, काष्ठा xdp_buff *xdp, पूर्णांक ret)
अणु
	test_result_fनिकास = ret;
	वापस 0;
पूर्ण
