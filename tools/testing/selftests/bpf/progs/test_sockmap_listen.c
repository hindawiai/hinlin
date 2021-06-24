<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2020 Cloudflare

#समावेश <त्रुटिसं.स>
#समावेश <stdbool.h>
#समावेश <linux/bpf.h>

#समावेश <bpf/bpf_helpers.h>

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_SOCKMAP);
	__uपूर्णांक(max_entries, 2);
	__type(key, __u32);
	__type(value, __u64);
पूर्ण sock_map SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_SOCKHASH);
	__uपूर्णांक(max_entries, 2);
	__type(key, __u32);
	__type(value, __u64);
पूर्ण sock_hash SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__uपूर्णांक(max_entries, 2);
	__type(key, पूर्णांक);
	__type(value, अचिन्हित पूर्णांक);
पूर्ण verdict_map SEC(".maps");

अटल अस्थिर bool test_sockmap; /* toggled by user-space */
अटल अस्थिर bool test_ingress; /* toggled by user-space */

SEC("sk_skb/stream_parser")
पूर्णांक prog_stream_parser(काष्ठा __sk_buff *skb)
अणु
	वापस skb->len;
पूर्ण

SEC("sk_skb/stream_verdict")
पूर्णांक prog_stream_verdict(काष्ठा __sk_buff *skb)
अणु
	अचिन्हित पूर्णांक *count;
	__u32 zero = 0;
	पूर्णांक verdict;

	अगर (test_sockmap)
		verdict = bpf_sk_redirect_map(skb, &sock_map, zero, 0);
	अन्यथा
		verdict = bpf_sk_redirect_hash(skb, &sock_hash, &zero, 0);

	count = bpf_map_lookup_elem(&verdict_map, &verdict);
	अगर (count)
		(*count)++;

	वापस verdict;
पूर्ण

SEC("sk_skb/skb_verdict")
पूर्णांक prog_skb_verdict(काष्ठा __sk_buff *skb)
अणु
	अचिन्हित पूर्णांक *count;
	__u32 zero = 0;
	पूर्णांक verdict;

	अगर (test_sockmap)
		verdict = bpf_sk_redirect_map(skb, &sock_map, zero,
					      test_ingress ? BPF_F_INGRESS : 0);
	अन्यथा
		verdict = bpf_sk_redirect_hash(skb, &sock_hash, &zero,
					       test_ingress ? BPF_F_INGRESS : 0);

	count = bpf_map_lookup_elem(&verdict_map, &verdict);
	अगर (count)
		(*count)++;

	वापस verdict;
पूर्ण

SEC("sk_msg")
पूर्णांक prog_msg_verdict(काष्ठा sk_msg_md *msg)
अणु
	अचिन्हित पूर्णांक *count;
	__u32 zero = 0;
	पूर्णांक verdict;

	अगर (test_sockmap)
		verdict = bpf_msg_redirect_map(msg, &sock_map, zero, 0);
	अन्यथा
		verdict = bpf_msg_redirect_hash(msg, &sock_hash, &zero, 0);

	count = bpf_map_lookup_elem(&verdict_map, &verdict);
	अगर (count)
		(*count)++;

	वापस verdict;
पूर्ण

SEC("sk_reuseport")
पूर्णांक prog_reuseport(काष्ठा sk_reuseport_md *reuse)
अणु
	अचिन्हित पूर्णांक *count;
	पूर्णांक err, verdict;
	__u32 zero = 0;

	अगर (test_sockmap)
		err = bpf_sk_select_reuseport(reuse, &sock_map, &zero, 0);
	अन्यथा
		err = bpf_sk_select_reuseport(reuse, &sock_hash, &zero, 0);
	verdict = err ? SK_DROP : SK_PASS;

	count = bpf_map_lookup_elem(&verdict_map, &verdict);
	अगर (count)
		(*count)++;

	वापस verdict;
पूर्ण

पूर्णांक _version SEC("version") = 1;
अक्षर _license[] SEC("license") = "GPL";
