<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */

#समावेश <माला.स>
#समावेश <त्रुटिसं.स>
#समावेश <netinet/in.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/bpf.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/tcp.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/pkt_cls.h>

#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_endian.h>
#समावेश "bpf_tcp_helpers.h"

काष्ठा sockaddr_in6 srv_sa6 = अणुपूर्ण;
__u16 listen_tp_sport = 0;
__u16 req_sk_sport = 0;
__u32 recv_cookie = 0;
__u32 gen_cookie = 0;
__u32 linum = 0;

#घोषणा LOG() (अणु अगर (!linum) linum = __LINE__; पूर्ण)

अटल व्योम test_syncookie_helper(काष्ठा ipv6hdr *ip6h, काष्ठा tcphdr *th,
				  काष्ठा tcp_sock *tp,
				  काष्ठा __sk_buff *skb)
अणु
	अगर (th->syn) अणु
		__s64 mss_cookie;
		व्योम *data_end;

		data_end = (व्योम *)(दीर्घ)(skb->data_end);

		अगर (th->करोff * 4 != 40) अणु
			LOG();
			वापस;
		पूर्ण

		अगर ((व्योम *)th + 40 > data_end) अणु
			LOG();
			वापस;
		पूर्ण

		mss_cookie = bpf_tcp_gen_syncookie(tp, ip6h, माप(*ip6h),
						   th, 40);
		अगर (mss_cookie < 0) अणु
			अगर (mss_cookie != -ENOENT)
				LOG();
		पूर्ण अन्यथा अणु
			gen_cookie = (__u32)mss_cookie;
		पूर्ण
	पूर्ण अन्यथा अगर (gen_cookie) अणु
		/* It was in cookie mode */
		पूर्णांक ret = bpf_tcp_check_syncookie(tp, ip6h, माप(*ip6h),
						  th, माप(*th));

		अगर (ret < 0) अणु
			अगर (ret != -ENOENT)
				LOG();
		पूर्ण अन्यथा अणु
			recv_cookie = bpf_ntohl(th->ack_seq) - 1;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक handle_ip6_tcp(काष्ठा ipv6hdr *ip6h, काष्ठा __sk_buff *skb)
अणु
	काष्ठा bpf_sock_tuple *tuple;
	काष्ठा bpf_sock *bpf_skc;
	अचिन्हित पूर्णांक tuple_len;
	काष्ठा tcphdr *th;
	व्योम *data_end;

	data_end = (व्योम *)(दीर्घ)(skb->data_end);

	th = (काष्ठा tcphdr *)(ip6h + 1);
	अगर (th + 1 > data_end)
		वापस TC_ACT_OK;

	/* Is it the testing traffic? */
	अगर (th->dest != srv_sa6.sin6_port)
		वापस TC_ACT_OK;

	tuple_len = माप(tuple->ipv6);
	tuple = (काष्ठा bpf_sock_tuple *)&ip6h->saddr;
	अगर ((व्योम *)tuple + tuple_len > data_end) अणु
		LOG();
		वापस TC_ACT_OK;
	पूर्ण

	bpf_skc = bpf_skc_lookup_tcp(skb, tuple, tuple_len,
				     BPF_F_CURRENT_NETNS, 0);
	अगर (!bpf_skc) अणु
		LOG();
		वापस TC_ACT_OK;
	पूर्ण

	अगर (bpf_skc->state == BPF_TCP_NEW_SYN_RECV) अणु
		काष्ठा request_sock *req_sk;

		req_sk = (काष्ठा request_sock *)bpf_skc_to_tcp_request_sock(bpf_skc);
		अगर (!req_sk) अणु
			LOG();
			जाओ release;
		पूर्ण

		अगर (bpf_sk_assign(skb, req_sk, 0)) अणु
			LOG();
			जाओ release;
		पूर्ण

		req_sk_sport = req_sk->__req_common.skc_num;

		bpf_sk_release(req_sk);
		वापस TC_ACT_OK;
	पूर्ण अन्यथा अगर (bpf_skc->state == BPF_TCP_LISTEN) अणु
		काष्ठा tcp_sock *tp;

		tp = bpf_skc_to_tcp_sock(bpf_skc);
		अगर (!tp) अणु
			LOG();
			जाओ release;
		पूर्ण

		अगर (bpf_sk_assign(skb, tp, 0)) अणु
			LOG();
			जाओ release;
		पूर्ण

		listen_tp_sport = tp->inet_conn.icsk_inet.sk.__sk_common.skc_num;

		test_syncookie_helper(ip6h, th, tp, skb);
		bpf_sk_release(tp);
		वापस TC_ACT_OK;
	पूर्ण

	अगर (bpf_sk_assign(skb, bpf_skc, 0))
		LOG();

release:
	bpf_sk_release(bpf_skc);
	वापस TC_ACT_OK;
पूर्ण

SEC("classifier/ingress")
पूर्णांक cls_ingress(काष्ठा __sk_buff *skb)
अणु
	काष्ठा ipv6hdr *ip6h;
	काष्ठा ethhdr *eth;
	व्योम *data_end;

	data_end = (व्योम *)(दीर्घ)(skb->data_end);

	eth = (काष्ठा ethhdr *)(दीर्घ)(skb->data);
	अगर (eth + 1 > data_end)
		वापस TC_ACT_OK;

	अगर (eth->h_proto != bpf_htons(ETH_P_IPV6))
		वापस TC_ACT_OK;

	ip6h = (काष्ठा ipv6hdr *)(eth + 1);
	अगर (ip6h + 1 > data_end)
		वापस TC_ACT_OK;

	अगर (ip6h->nexthdr == IPPROTO_TCP)
		वापस handle_ip6_tcp(ip6h, skb);

	वापस TC_ACT_OK;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
