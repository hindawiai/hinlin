<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2019 Facebook */

#समावेश <linux/bpf.h>
#समावेश <netinet/in.h>
#समावेश <stdbool.h>

#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_endian.h>
#समावेश "bpf_tcp_helpers.h"

क्रमागत bpf_linum_array_idx अणु
	EGRESS_LINUM_IDX,
	INGRESS_LINUM_IDX,
	__NR_BPF_LINUM_ARRAY_IDX,
पूर्ण;

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__uपूर्णांक(max_entries, __NR_BPF_LINUM_ARRAY_IDX);
	__type(key, __u32);
	__type(value, __u32);
पूर्ण linum_map SEC(".maps");

काष्ठा bpf_spinlock_cnt अणु
	काष्ठा bpf_spin_lock lock;
	__u32 cnt;
पूर्ण;

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_SK_STORAGE);
	__uपूर्णांक(map_flags, BPF_F_NO_PREALLOC);
	__type(key, पूर्णांक);
	__type(value, काष्ठा bpf_spinlock_cnt);
पूर्ण sk_pkt_out_cnt SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_SK_STORAGE);
	__uपूर्णांक(map_flags, BPF_F_NO_PREALLOC);
	__type(key, पूर्णांक);
	__type(value, काष्ठा bpf_spinlock_cnt);
पूर्ण sk_pkt_out_cnt10 SEC(".maps");

काष्ठा bpf_tcp_sock listen_tp = अणुपूर्ण;
काष्ठा sockaddr_in6 srv_sa6 = अणुपूर्ण;
काष्ठा bpf_tcp_sock cli_tp = अणुपूर्ण;
काष्ठा bpf_tcp_sock srv_tp = अणुपूर्ण;
काष्ठा bpf_sock listen_sk = अणुपूर्ण;
काष्ठा bpf_sock srv_sk = अणुपूर्ण;
काष्ठा bpf_sock cli_sk = अणुपूर्ण;
__u64 parent_cg_id = 0;
__u64 child_cg_id = 0;
__u64 lsndसमय = 0;

अटल bool is_loopback6(__u32 *a6)
अणु
	वापस !a6[0] && !a6[1] && !a6[2] && a6[3] == bpf_htonl(1);
पूर्ण

अटल व्योम skcpy(काष्ठा bpf_sock *dst,
		  स्थिर काष्ठा bpf_sock *src)
अणु
	dst->bound_dev_अगर = src->bound_dev_अगर;
	dst->family = src->family;
	dst->type = src->type;
	dst->protocol = src->protocol;
	dst->mark = src->mark;
	dst->priority = src->priority;
	dst->src_ip4 = src->src_ip4;
	dst->src_ip6[0] = src->src_ip6[0];
	dst->src_ip6[1] = src->src_ip6[1];
	dst->src_ip6[2] = src->src_ip6[2];
	dst->src_ip6[3] = src->src_ip6[3];
	dst->src_port = src->src_port;
	dst->dst_ip4 = src->dst_ip4;
	dst->dst_ip6[0] = src->dst_ip6[0];
	dst->dst_ip6[1] = src->dst_ip6[1];
	dst->dst_ip6[2] = src->dst_ip6[2];
	dst->dst_ip6[3] = src->dst_ip6[3];
	dst->dst_port = src->dst_port;
	dst->state = src->state;
पूर्ण

अटल व्योम tpcpy(काष्ठा bpf_tcp_sock *dst,
		  स्थिर काष्ठा bpf_tcp_sock *src)
अणु
	dst->snd_cwnd = src->snd_cwnd;
	dst->srtt_us = src->srtt_us;
	dst->rtt_min = src->rtt_min;
	dst->snd_ssthresh = src->snd_ssthresh;
	dst->rcv_nxt = src->rcv_nxt;
	dst->snd_nxt = src->snd_nxt;
	dst->snd_una = src->snd_una;
	dst->mss_cache = src->mss_cache;
	dst->ecn_flags = src->ecn_flags;
	dst->rate_delivered = src->rate_delivered;
	dst->rate_पूर्णांकerval_us = src->rate_पूर्णांकerval_us;
	dst->packets_out = src->packets_out;
	dst->retrans_out = src->retrans_out;
	dst->total_retrans = src->total_retrans;
	dst->segs_in = src->segs_in;
	dst->data_segs_in = src->data_segs_in;
	dst->segs_out = src->segs_out;
	dst->data_segs_out = src->data_segs_out;
	dst->lost_out = src->lost_out;
	dst->sacked_out = src->sacked_out;
	dst->bytes_received = src->bytes_received;
	dst->bytes_acked = src->bytes_acked;
पूर्ण

/* Always वापस CG_OK so that no pkt will be filtered out */
#घोषणा CG_OK 1

#घोषणा RET_LOG() (अणु						\
	linum = __LINE__;					\
	bpf_map_update_elem(&linum_map, &linum_idx, &linum, BPF_NOEXIST);	\
	वापस CG_OK;						\
पूर्ण)

SEC("cgroup_skb/egress")
पूर्णांक egress_पढ़ो_sock_fields(काष्ठा __sk_buff *skb)
अणु
	काष्ठा bpf_spinlock_cnt cli_cnt_init = अणु .lock = 0, .cnt = 0xeB9F पूर्ण;
	काष्ठा bpf_spinlock_cnt *pkt_out_cnt, *pkt_out_cnt10;
	काष्ठा bpf_tcp_sock *tp, *tp_ret;
	काष्ठा bpf_sock *sk, *sk_ret;
	__u32 linum, linum_idx;
	काष्ठा tcp_sock *ktp;

	linum_idx = EGRESS_LINUM_IDX;

	sk = skb->sk;
	अगर (!sk)
		RET_LOG();

	/* Not the testing egress traffic or
	 * TCP_LISTEN (10) socket will be copied at the ingress side.
	 */
	अगर (sk->family != AF_INET6 || !is_loopback6(sk->src_ip6) ||
	    sk->state == 10)
		वापस CG_OK;

	अगर (sk->src_port == bpf_ntohs(srv_sa6.sin6_port)) अणु
		/* Server socket */
		sk_ret = &srv_sk;
		tp_ret = &srv_tp;
	पूर्ण अन्यथा अगर (sk->dst_port == srv_sa6.sin6_port) अणु
		/* Client socket */
		sk_ret = &cli_sk;
		tp_ret = &cli_tp;
	पूर्ण अन्यथा अणु
		/* Not the testing egress traffic */
		वापस CG_OK;
	पूर्ण

	/* It must be a fullsock क्रम cgroup_skb/egress prog */
	sk = bpf_sk_fullsock(sk);
	अगर (!sk)
		RET_LOG();

	/* Not the testing egress traffic */
	अगर (sk->protocol != IPPROTO_TCP)
		वापस CG_OK;

	tp = bpf_tcp_sock(sk);
	अगर (!tp)
		RET_LOG();

	skcpy(sk_ret, sk);
	tpcpy(tp_ret, tp);

	अगर (sk_ret == &srv_sk) अणु
		ktp = bpf_skc_to_tcp_sock(sk);

		अगर (!ktp)
			RET_LOG();

		lsndसमय = ktp->lsndसमय;

		child_cg_id = bpf_sk_cgroup_id(ktp);
		अगर (!child_cg_id)
			RET_LOG();

		parent_cg_id = bpf_sk_ancestor_cgroup_id(ktp, 2);
		अगर (!parent_cg_id)
			RET_LOG();

		/* The userspace has created it क्रम srv sk */
		pkt_out_cnt = bpf_sk_storage_get(&sk_pkt_out_cnt, ktp, 0, 0);
		pkt_out_cnt10 = bpf_sk_storage_get(&sk_pkt_out_cnt10, ktp,
						   0, 0);
	पूर्ण अन्यथा अणु
		pkt_out_cnt = bpf_sk_storage_get(&sk_pkt_out_cnt, sk,
						 &cli_cnt_init,
						 BPF_SK_STORAGE_GET_F_CREATE);
		pkt_out_cnt10 = bpf_sk_storage_get(&sk_pkt_out_cnt10,
						   sk, &cli_cnt_init,
						   BPF_SK_STORAGE_GET_F_CREATE);
	पूर्ण

	अगर (!pkt_out_cnt || !pkt_out_cnt10)
		RET_LOG();

	/* Even both cnt and cnt10 have lock defined in their BTF,
	 * पूर्णांकentionally one cnt takes lock जबतक one करोes not
	 * as a test क्रम the spinlock support in BPF_MAP_TYPE_SK_STORAGE.
	 */
	pkt_out_cnt->cnt += 1;
	bpf_spin_lock(&pkt_out_cnt10->lock);
	pkt_out_cnt10->cnt += 10;
	bpf_spin_unlock(&pkt_out_cnt10->lock);

	वापस CG_OK;
पूर्ण

SEC("cgroup_skb/ingress")
पूर्णांक ingress_पढ़ो_sock_fields(काष्ठा __sk_buff *skb)
अणु
	काष्ठा bpf_tcp_sock *tp;
	__u32 linum, linum_idx;
	काष्ठा bpf_sock *sk;

	linum_idx = INGRESS_LINUM_IDX;

	sk = skb->sk;
	अगर (!sk)
		RET_LOG();

	/* Not the testing ingress traffic to the server */
	अगर (sk->family != AF_INET6 || !is_loopback6(sk->src_ip6) ||
	    sk->src_port != bpf_ntohs(srv_sa6.sin6_port))
		वापस CG_OK;

	/* Only पूर्णांकerested in TCP_LISTEN */
	अगर (sk->state != 10)
		वापस CG_OK;

	/* It must be a fullsock क्रम cgroup_skb/ingress prog */
	sk = bpf_sk_fullsock(sk);
	अगर (!sk)
		RET_LOG();

	tp = bpf_tcp_sock(sk);
	अगर (!tp)
		RET_LOG();

	skcpy(&listen_sk, sk);
	tpcpy(&listen_tp, tp);

	वापस CG_OK;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
