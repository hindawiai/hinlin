<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/ptrace.h>
#समावेश <linux/version.h>
#समावेश <uapi/linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

#घोषणा SAMPLE_SIZE 64ul

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERF_EVENT_ARRAY);
	__uपूर्णांक(key_size, माप(पूर्णांक));
	__uपूर्णांक(value_size, माप(u32));
पूर्ण my_map SEC(".maps");

SEC("xdp_sample")
पूर्णांक xdp_sample_prog(काष्ठा xdp_md *ctx)
अणु
	व्योम *data_end = (व्योम *)(दीर्घ)ctx->data_end;
	व्योम *data = (व्योम *)(दीर्घ)ctx->data;

	/* Metadata will be in the perf event beक्रमe the packet data. */
	काष्ठा S अणु
		u16 cookie;
		u16 pkt_len;
	पूर्ण __packed metadata;

	अगर (data < data_end) अणु
		/* The XDP perf_event_output handler will use the upper 32 bits
		 * of the flags argument as a number of bytes to include of the
		 * packet payload in the event data. If the size is too big, the
		 * call to bpf_perf_event_output will fail and वापस -EFAULT.
		 *
		 * See bpf_xdp_event_output in net/core/filter.c.
		 *
		 * The BPF_F_CURRENT_CPU flag means that the event output fd
		 * will be indexed by the CPU number in the event map.
		 */
		u64 flags = BPF_F_CURRENT_CPU;
		u16 sample_size;
		पूर्णांक ret;

		metadata.cookie = 0xdead;
		metadata.pkt_len = (u16)(data_end - data);
		sample_size = min(metadata.pkt_len, SAMPLE_SIZE);
		flags |= (u64)sample_size << 32;

		ret = bpf_perf_event_output(ctx, &my_map, flags,
					    &metadata, माप(metadata));
		अगर (ret)
			bpf_prपूर्णांकk("perf_event_output failed: %d\n", ret);
	पूर्ण

	वापस XDP_PASS;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
u32 _version SEC("version") = LINUX_VERSION_CODE;
