<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */
#समावेश "bpf_iter.h"
#समावेश "bpf_tracing_net.h"
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>
#समावेश <bpf/bpf_endian.h>

अक्षर _license[] SEC("license") = "GPL";

अटल पूर्णांक hlist_unhashed_lockless(स्थिर काष्ठा hlist_node *h)
अणु
        वापस !(h->pprev);
पूर्ण

अटल पूर्णांक समयr_pending(स्थिर काष्ठा समयr_list * समयr)
अणु
	वापस !hlist_unhashed_lockless(&समयr->entry);
पूर्ण

बाह्य अचिन्हित CONFIG_HZ __kconfig;

#घोषणा USER_HZ		100
#घोषणा NSEC_PER_SEC	1000000000ULL
अटल घड़ी_प्रकार jअगरfies_to_घड़ी_प्रकार(अचिन्हित दीर्घ x)
अणु
	/* The implementation here tailored to a particular
	 * setting of USER_HZ.
	 */
	u64 tick_nsec = (NSEC_PER_SEC + CONFIG_HZ/2) / CONFIG_HZ;
	u64 user_hz_nsec = NSEC_PER_SEC / USER_HZ;

	अगर ((tick_nsec % user_hz_nsec) == 0) अणु
		अगर (CONFIG_HZ < USER_HZ)
			वापस x * (USER_HZ / CONFIG_HZ);
		अन्यथा
			वापस x / (CONFIG_HZ / USER_HZ);
	पूर्ण
	वापस x * tick_nsec/user_hz_nsec;
पूर्ण

अटल घड़ी_प्रकार jअगरfies_delta_to_घड़ी_प्रकार(दीर्घ delta)
अणु
	अगर (delta <= 0)
		वापस 0;

	वापस jअगरfies_to_घड़ी_प्रकार(delta);
पूर्ण

अटल दीर्घ sock_i_ino(स्थिर काष्ठा sock *sk)
अणु
	स्थिर काष्ठा socket *sk_socket = sk->sk_socket;
	स्थिर काष्ठा inode *inode;
	अचिन्हित दीर्घ ino;

	अगर (!sk_socket)
		वापस 0;

	inode = &container_of(sk_socket, काष्ठा socket_alloc, socket)->vfs_inode;
	bpf_probe_पढ़ो_kernel(&ino, माप(ino), &inode->i_ino);
	वापस ino;
पूर्ण

अटल bool
inet_csk_in_pingpong_mode(स्थिर काष्ठा inet_connection_sock *icsk)
अणु
	वापस icsk->icsk_ack.pingpong >= TCP_PINGPONG_THRESH;
पूर्ण

अटल bool tcp_in_initial_slowstart(स्थिर काष्ठा tcp_sock *tcp)
अणु
	वापस tcp->snd_ssthresh >= TCP_INFINITE_SSTHRESH;
पूर्ण

अटल पूर्णांक dump_tcp6_sock(काष्ठा seq_file *seq, काष्ठा tcp6_sock *tp,
			 uid_t uid, __u32 seq_num)
अणु
	स्थिर काष्ठा inet_connection_sock *icsk;
	स्थिर काष्ठा fastखोलो_queue *fastखोलोq;
	स्थिर काष्ठा in6_addr *dest, *src;
	स्थिर काष्ठा inet_sock *inet;
	अचिन्हित दीर्घ समयr_expires;
	स्थिर काष्ठा sock *sp;
	__u16 destp, srcp;
	पूर्णांक समयr_active;
	पूर्णांक rx_queue;
	पूर्णांक state;

	icsk = &tp->tcp.inet_conn;
	inet = &icsk->icsk_inet;
	sp = &inet->sk;
	fastखोलोq = &icsk->icsk_accept_queue.fastखोलोq;

	dest = &sp->sk_v6_daddr;
	src = &sp->sk_v6_rcv_saddr;
	destp = bpf_ntohs(inet->inet_dport);
	srcp = bpf_ntohs(inet->inet_sport);

	अगर (icsk->icsk_pending == ICSK_TIME_RETRANS ||
	    icsk->icsk_pending == ICSK_TIME_REO_TIMEOUT ||
	    icsk->icsk_pending == ICSK_TIME_LOSS_PROBE) अणु
		समयr_active = 1;
		समयr_expires = icsk->icsk_समयout;
	पूर्ण अन्यथा अगर (icsk->icsk_pending == ICSK_TIME_PROBE0) अणु
		समयr_active = 4;
		समयr_expires = icsk->icsk_समयout;
	पूर्ण अन्यथा अगर (समयr_pending(&sp->sk_समयr)) अणु
		समयr_active = 2;
		समयr_expires = sp->sk_समयr.expires;
	पूर्ण अन्यथा अणु
		समयr_active = 0;
		समयr_expires = bpf_jअगरfies64();
	पूर्ण

	state = sp->sk_state;
	अगर (state == TCP_LISTEN) अणु
		rx_queue = sp->sk_ack_backlog;
	पूर्ण अन्यथा अणु
		rx_queue = tp->tcp.rcv_nxt - tp->tcp.copied_seq;
		अगर (rx_queue < 0)
			rx_queue = 0;
	पूर्ण

	BPF_SEQ_PRINTF(seq, "%4d: %08X%08X%08X%08X:%04X %08X%08X%08X%08X:%04X ",
		       seq_num,
		       src->s6_addr32[0], src->s6_addr32[1],
		       src->s6_addr32[2], src->s6_addr32[3], srcp,
		       dest->s6_addr32[0], dest->s6_addr32[1],
		       dest->s6_addr32[2], dest->s6_addr32[3], destp);
	BPF_SEQ_PRINTF(seq, "%02X %08X:%08X %02X:%08lX %08X %5u %8d %lu %d ",
		       state,
		       tp->tcp.ग_लिखो_seq - tp->tcp.snd_una, rx_queue,
		       समयr_active,
		       jअगरfies_delta_to_घड़ी_प्रकार(समयr_expires - bpf_jअगरfies64()),
		       icsk->icsk_retransmits, uid,
		       icsk->icsk_probes_out,
		       sock_i_ino(sp),
		       sp->sk_refcnt.refs.counter);
	BPF_SEQ_PRINTF(seq, "%pK %lu %lu %u %u %d\n",
		       tp,
		       jअगरfies_to_घड़ी_प्रकार(icsk->icsk_rto),
		       jअगरfies_to_घड़ी_प्रकार(icsk->icsk_ack.ato),
		       (icsk->icsk_ack.quick << 1) | inet_csk_in_pingpong_mode(icsk),
		       tp->tcp.snd_cwnd,
		       state == TCP_LISTEN ? fastखोलोq->max_qlen
				: (tcp_in_initial_slowstart(&tp->tcp) ? -1
								      : tp->tcp.snd_ssthresh)
		      );

	वापस 0;
पूर्ण

अटल पूर्णांक dump_tw_sock(काष्ठा seq_file *seq, काष्ठा tcp_समयरुको_sock *ttw,
			uid_t uid, __u32 seq_num)
अणु
	काष्ठा inet_समयरुको_sock *tw = &ttw->tw_sk;
	स्थिर काष्ठा in6_addr *dest, *src;
	__u16 destp, srcp;
	दीर्घ delta;

	delta = tw->tw_समयr.expires - bpf_jअगरfies64();
	dest = &tw->tw_v6_daddr;
	src  = &tw->tw_v6_rcv_saddr;
	destp = bpf_ntohs(tw->tw_dport);
	srcp  = bpf_ntohs(tw->tw_sport);

	BPF_SEQ_PRINTF(seq, "%4d: %08X%08X%08X%08X:%04X %08X%08X%08X%08X:%04X ",
		       seq_num,
		       src->s6_addr32[0], src->s6_addr32[1],
		       src->s6_addr32[2], src->s6_addr32[3], srcp,
		       dest->s6_addr32[0], dest->s6_addr32[1],
		       dest->s6_addr32[2], dest->s6_addr32[3], destp);

	BPF_SEQ_PRINTF(seq, "%02X %08X:%08X %02X:%08lX %08X %5d %8d %d %d %pK\n",
		       tw->tw_substate, 0, 0,
		       3, jअगरfies_delta_to_घड़ी_प्रकार(delta), 0, 0, 0, 0,
		       tw->tw_refcnt.refs.counter, tw);

	वापस 0;
पूर्ण

अटल पूर्णांक dump_req_sock(काष्ठा seq_file *seq, काष्ठा tcp_request_sock *treq,
			 uid_t uid, __u32 seq_num)
अणु
	काष्ठा inet_request_sock *irsk = &treq->req;
	काष्ठा request_sock *req = &irsk->req;
	काष्ठा in6_addr *src, *dest;
	दीर्घ ttd;

	ttd = req->rsk_समयr.expires - bpf_jअगरfies64();
	src = &irsk->ir_v6_loc_addr;
	dest = &irsk->ir_v6_rmt_addr;

	अगर (ttd < 0)
		ttd = 0;

	BPF_SEQ_PRINTF(seq, "%4d: %08X%08X%08X%08X:%04X %08X%08X%08X%08X:%04X ",
		       seq_num,
		       src->s6_addr32[0], src->s6_addr32[1],
		       src->s6_addr32[2], src->s6_addr32[3],
		       irsk->ir_num,
		       dest->s6_addr32[0], dest->s6_addr32[1],
		       dest->s6_addr32[2], dest->s6_addr32[3],
		       bpf_ntohs(irsk->ir_rmt_port));
	BPF_SEQ_PRINTF(seq, "%02X %08X:%08X %02X:%08lX %08X %5d %8d %d %d %pK\n",
		       TCP_SYN_RECV, 0, 0, 1, jअगरfies_to_घड़ी_प्रकार(ttd),
		       req->num_समयout, uid, 0, 0, 0, req);

	वापस 0;
पूर्ण

SEC("iter/tcp")
पूर्णांक dump_tcp6(काष्ठा bpf_iter__tcp *ctx)
अणु
	काष्ठा sock_common *sk_common = ctx->sk_common;
	काष्ठा seq_file *seq = ctx->meta->seq;
	काष्ठा tcp_समयरुको_sock *tw;
	काष्ठा tcp_request_sock *req;
	काष्ठा tcp6_sock *tp;
	uid_t uid = ctx->uid;
	__u32 seq_num;

	अगर (sk_common == (व्योम *)0)
		वापस 0;

	seq_num = ctx->meta->seq_num;
	अगर (seq_num == 0)
		BPF_SEQ_PRINTF(seq, "  sl  "
				    "local_address                         "
				    "remote_address                        "
				    "st tx_queue rx_queue tr tm->when retrnsmt"
				    "   uid  timeout inode\n");

	अगर (sk_common->skc_family != AF_INET6)
		वापस 0;

	tp = bpf_skc_to_tcp6_sock(sk_common);
	अगर (tp)
		वापस dump_tcp6_sock(seq, tp, uid, seq_num);

	tw = bpf_skc_to_tcp_समयरुको_sock(sk_common);
	अगर (tw)
		वापस dump_tw_sock(seq, tw, uid, seq_num);

	req = bpf_skc_to_tcp_request_sock(sk_common);
	अगर (req)
		वापस dump_req_sock(seq, req, uid, seq_num);

	वापस 0;
पूर्ण
