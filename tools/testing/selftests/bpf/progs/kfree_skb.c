<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2019 Facebook
#समावेश <linux/bpf.h>
#समावेश <stdbool.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_endian.h>
#समावेश <bpf/bpf_tracing.h>

अक्षर _license[] SEC("license") = "GPL";
काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERF_EVENT_ARRAY);
	__uपूर्णांक(key_size, माप(पूर्णांक));
	__uपूर्णांक(value_size, माप(पूर्णांक));
पूर्ण perf_buf_map SEC(".maps");

#घोषणा _(P) (__builtin_preserve_access_index(P))

/* define few काष्ठा-s that bpf program needs to access */
काष्ठा callback_head अणु
	काष्ठा callback_head *next;
	व्योम (*func)(काष्ठा callback_head *head);
पूर्ण;
काष्ठा dev_अगरalias अणु
	काष्ठा callback_head rcuhead;
पूर्ण;

काष्ठा net_device /* same as kernel's काष्ठा net_device */ अणु
	पूर्णांक अगरindex;
	काष्ठा dev_अगरalias *अगरalias;
पूर्ण;

प्रकार काष्ठा अणु
        पूर्णांक counter;
पूर्ण atomic_t;
प्रकार काष्ठा refcount_काष्ठा अणु
        atomic_t refs;
पूर्ण refcount_t;

काष्ठा sk_buff अणु
	/* field names and sizes should match to those in the kernel */
	अचिन्हित पूर्णांक len, data_len;
	__u16 mac_len, hdr_len, queue_mapping;
	काष्ठा net_device *dev;
	/* order of the fields करोesn't matter */
	refcount_t users;
	अचिन्हित अक्षर *data;
	अक्षर __pkt_type_offset[0];
	अक्षर cb[48];
पूर्ण;

काष्ठा meta अणु
	पूर्णांक अगरindex;
	__u32 cb32_0;
	__u8 cb8_0;
पूर्ण;

/* TRACE_EVENT(kमुक्त_skb,
 *         TP_PROTO(काष्ठा sk_buff *skb, व्योम *location),
 */
SEC("tp_btf/kfree_skb")
पूर्णांक BPF_PROG(trace_kमुक्त_skb, काष्ठा sk_buff *skb, व्योम *location)
अणु
	काष्ठा net_device *dev;
	काष्ठा callback_head *ptr;
	व्योम *func;
	पूर्णांक users;
	अचिन्हित अक्षर *data;
	अचिन्हित लघु pkt_data;
	काष्ठा meta meta = अणुपूर्ण;
	अक्षर pkt_type;
	__u32 *cb32;
	__u8 *cb8;

	__builtin_preserve_access_index((अणु
		users = skb->users.refs.counter;
		data = skb->data;
		dev = skb->dev;
		ptr = dev->अगरalias->rcuhead.next;
		func = ptr->func;
		cb8 = (__u8 *)&skb->cb;
		cb32 = (__u32 *)&skb->cb;
	पूर्ण));

	meta.अगरindex = _(dev->अगरindex);
	meta.cb8_0 = cb8[8];
	meta.cb32_0 = cb32[2];

	bpf_probe_पढ़ो_kernel(&pkt_type, माप(pkt_type), _(&skb->__pkt_type_offset));
	pkt_type &= 7;

	/* पढ़ो eth proto */
	bpf_probe_पढ़ो_kernel(&pkt_data, माप(pkt_data), data + 12);

	bpf_prपूर्णांकk("rcuhead.next %llx func %llx\n", ptr, func);
	bpf_prपूर्णांकk("skb->len %d users %d pkt_type %x\n",
		   _(skb->len), users, pkt_type);
	bpf_prपूर्णांकk("skb->queue_mapping %d\n", _(skb->queue_mapping));
	bpf_prपूर्णांकk("dev->ifindex %d data %llx pkt_data %x\n",
		   meta.अगरindex, data, pkt_data);
	bpf_prपूर्णांकk("cb8_0:%x cb32_0:%x\n", meta.cb8_0, meta.cb32_0);

	अगर (users != 1 || pkt_data != bpf_htons(0x86dd) || meta.अगरindex != 1)
		/* raw tp ignores वापस value */
		वापस 0;

	/* send first 72 byte of the packet to user space */
	bpf_skb_output(skb, &perf_buf_map, (72ull << 32) | BPF_F_CURRENT_CPU,
		       &meta, माप(meta));
	वापस 0;
पूर्ण

अटल अस्थिर काष्ठा अणु
	bool fentry_test_ok;
	bool fनिकास_test_ok;
पूर्ण result;

SEC("fentry/eth_type_trans")
पूर्णांक BPF_PROG(fentry_eth_type_trans, काष्ठा sk_buff *skb, काष्ठा net_device *dev,
	     अचिन्हित लघु protocol)
अणु
	पूर्णांक len, अगरindex;

	__builtin_preserve_access_index((अणु
		len = skb->len;
		अगरindex = dev->अगरindex;
	पूर्ण));

	/* fentry sees full packet including L2 header */
	अगर (len != 74 || अगरindex != 1)
		वापस 0;
	result.fentry_test_ok = true;
	वापस 0;
पूर्ण

SEC("fexit/eth_type_trans")
पूर्णांक BPF_PROG(fनिकास_eth_type_trans, काष्ठा sk_buff *skb, काष्ठा net_device *dev,
	     अचिन्हित लघु protocol)
अणु
	पूर्णांक len, अगरindex;

	__builtin_preserve_access_index((अणु
		len = skb->len;
		अगरindex = dev->अगरindex;
	पूर्ण));

	/* fनिकास sees packet without L2 header that eth_type_trans should have
	 * consumed.
	 */
	अगर (len != 60 || protocol != bpf_htons(0x86dd) || अगरindex != 1)
		वापस 0;
	result.fनिकास_test_ok = true;
	वापस 0;
पूर्ण
