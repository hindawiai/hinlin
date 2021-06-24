<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानक_निवेशt.h>
#समावेश <stdbool.h>
#समावेश <मानकघोष.स>

#समावेश <linux/bpf.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/pkt_cls.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>

#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_endian.h>

#अगर_अघोषित ctx_ptr
# define ctx_ptr(field)		(व्योम *)(दीर्घ)(field)
#पूर्ण_अगर

#घोषणा AF_INET 2
#घोषणा AF_INET6 10

अटल __always_अंतरभूत पूर्णांक fill_fib_params_v4(काष्ठा __sk_buff *skb,
					      काष्ठा bpf_fib_lookup *fib_params)
अणु
	व्योम *data_end = ctx_ptr(skb->data_end);
	व्योम *data = ctx_ptr(skb->data);
	काष्ठा iphdr *ip4h;

	अगर (data + माप(काष्ठा ethhdr) > data_end)
		वापस -1;

	ip4h = (काष्ठा iphdr *)(data + माप(काष्ठा ethhdr));
	अगर ((व्योम *)(ip4h + 1) > data_end)
		वापस -1;

	fib_params->family = AF_INET;
	fib_params->tos = ip4h->tos;
	fib_params->l4_protocol = ip4h->protocol;
	fib_params->sport = 0;
	fib_params->dport = 0;
	fib_params->tot_len = bpf_ntohs(ip4h->tot_len);
	fib_params->ipv4_src = ip4h->saddr;
	fib_params->ipv4_dst = ip4h->daddr;

	वापस 0;
पूर्ण

अटल __always_अंतरभूत पूर्णांक fill_fib_params_v6(काष्ठा __sk_buff *skb,
					      काष्ठा bpf_fib_lookup *fib_params)
अणु
	काष्ठा in6_addr *src = (काष्ठा in6_addr *)fib_params->ipv6_src;
	काष्ठा in6_addr *dst = (काष्ठा in6_addr *)fib_params->ipv6_dst;
	व्योम *data_end = ctx_ptr(skb->data_end);
	व्योम *data = ctx_ptr(skb->data);
	काष्ठा ipv6hdr *ip6h;

	अगर (data + माप(काष्ठा ethhdr) > data_end)
		वापस -1;

	ip6h = (काष्ठा ipv6hdr *)(data + माप(काष्ठा ethhdr));
	अगर ((व्योम *)(ip6h + 1) > data_end)
		वापस -1;

	fib_params->family = AF_INET6;
	fib_params->flowinfo = 0;
	fib_params->l4_protocol = ip6h->nexthdr;
	fib_params->sport = 0;
	fib_params->dport = 0;
	fib_params->tot_len = bpf_ntohs(ip6h->payload_len);
	*src = ip6h->saddr;
	*dst = ip6h->daddr;

	वापस 0;
पूर्ण

SEC("classifier/chk_egress")
पूर्णांक tc_chk(काष्ठा __sk_buff *skb)
अणु
	व्योम *data_end = ctx_ptr(skb->data_end);
	व्योम *data = ctx_ptr(skb->data);
	__u32 *raw = data;

	अगर (data + माप(काष्ठा ethhdr) > data_end)
		वापस TC_ACT_SHOT;

	वापस !raw[0] && !raw[1] && !raw[2] ? TC_ACT_SHOT : TC_ACT_OK;
पूर्ण

अटल __always_अंतरभूत पूर्णांक tc_redir(काष्ठा __sk_buff *skb)
अणु
	काष्ठा bpf_fib_lookup fib_params = अणु .अगरindex = skb->ingress_अगरindex पूर्ण;
	__u8 zero[ETH_ALEN * 2];
	पूर्णांक ret = -1;

	चयन (skb->protocol) अणु
	हाल __bpf_स्थिरant_htons(ETH_P_IP):
		ret = fill_fib_params_v4(skb, &fib_params);
		अवरोध;
	हाल __bpf_स्थिरant_htons(ETH_P_IPV6):
		ret = fill_fib_params_v6(skb, &fib_params);
		अवरोध;
	पूर्ण

	अगर (ret)
		वापस TC_ACT_OK;

	ret = bpf_fib_lookup(skb, &fib_params, माप(fib_params), 0);
	अगर (ret == BPF_FIB_LKUP_RET_NOT_FWDED || ret < 0)
		वापस TC_ACT_OK;

	__builtin_स_रखो(&zero, 0, माप(zero));
	अगर (bpf_skb_store_bytes(skb, 0, &zero, माप(zero), 0) < 0)
		वापस TC_ACT_SHOT;

	अगर (ret == BPF_FIB_LKUP_RET_NO_NEIGH) अणु
		काष्ठा bpf_redir_neigh nh_params = अणुपूर्ण;

		nh_params.nh_family = fib_params.family;
		__builtin_स_नकल(&nh_params.ipv6_nh, &fib_params.ipv6_dst,
				 माप(nh_params.ipv6_nh));

		वापस bpf_redirect_neigh(fib_params.अगरindex, &nh_params,
					  माप(nh_params), 0);

	पूर्ण अन्यथा अगर (ret == BPF_FIB_LKUP_RET_SUCCESS) अणु
		व्योम *data_end = ctx_ptr(skb->data_end);
		काष्ठा ethhdr *eth = ctx_ptr(skb->data);

		अगर (eth + 1 > data_end)
			वापस TC_ACT_SHOT;

		__builtin_स_नकल(eth->h_dest, fib_params.dmac, ETH_ALEN);
		__builtin_स_नकल(eth->h_source, fib_params.smac, ETH_ALEN);

		वापस bpf_redirect(fib_params.अगरindex, 0);
	पूर्ण

	वापस TC_ACT_SHOT;
पूर्ण

/* these are identical, but keep them separate क्रम compatibility with the
 * section names expected by test_tc_redirect.sh
 */
SEC("classifier/dst_ingress")
पूर्णांक tc_dst(काष्ठा __sk_buff *skb)
अणु
	वापस tc_redir(skb);
पूर्ण

SEC("classifier/src_ingress")
पूर्णांक tc_src(काष्ठा __sk_buff *skb)
अणु
	वापस tc_redir(skb);
पूर्ण

अक्षर __license[] SEC("license") = "GPL";
