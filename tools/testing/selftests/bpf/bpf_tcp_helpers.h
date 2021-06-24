<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __BPF_TCP_HELPERS_H
#घोषणा __BPF_TCP_HELPERS_H

#समावेश <stdbool.h>
#समावेश <linux/types.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_core_पढ़ो.h>
#समावेश <bpf/bpf_tracing.h>

#घोषणा BPF_STRUCT_OPS(name, args...) \
SEC("struct_ops/"#name) \
BPF_PROG(name, args)

#घोषणा tcp_jअगरfies32 ((__u32)bpf_jअगरfies64())

काष्ठा sock_common अणु
	अचिन्हित अक्षर	skc_state;
	__u16		skc_num;
पूर्ण __attribute__((preserve_access_index));

क्रमागत sk_pacing अणु
	SK_PACING_NONE		= 0,
	SK_PACING_NEEDED	= 1,
	SK_PACING_FQ		= 2,
पूर्ण;

काष्ठा sock अणु
	काष्ठा sock_common	__sk_common;
	अचिन्हित दीर्घ		sk_pacing_rate;
	__u32			sk_pacing_status; /* see क्रमागत sk_pacing */
पूर्ण __attribute__((preserve_access_index));

काष्ठा inet_sock अणु
	काष्ठा sock		sk;
पूर्ण __attribute__((preserve_access_index));

काष्ठा inet_connection_sock अणु
	काष्ठा inet_sock	  icsk_inet;
	__u8			  icsk_ca_state:6,
				  icsk_ca_setsockopt:1,
				  icsk_ca_dst_locked:1;
	काष्ठा अणु
		__u8		  pending;
	पूर्ण icsk_ack;
	__u64			  icsk_ca_priv[104 / माप(__u64)];
पूर्ण __attribute__((preserve_access_index));

काष्ठा request_sock अणु
	काष्ठा sock_common		__req_common;
पूर्ण __attribute__((preserve_access_index));

काष्ठा tcp_sock अणु
	काष्ठा inet_connection_sock	inet_conn;

	__u32	rcv_nxt;
	__u32	snd_nxt;
	__u32	snd_una;
	__u32	winकरोw_clamp;
	__u8	ecn_flags;
	__u32	delivered;
	__u32	delivered_ce;
	__u32	snd_cwnd;
	__u32	snd_cwnd_cnt;
	__u32	snd_cwnd_clamp;
	__u32	snd_ssthresh;
	__u8	syn_data:1,	/* SYN includes data */
		syn_fastखोलो:1,	/* SYN includes Fast Open option */
		syn_fastखोलो_exp:1,/* SYN includes Fast Open exp. option */
		syn_fastखोलो_ch:1, /* Active TFO re-enabling probe */
		syn_data_acked:1,/* data in SYN is acked by SYN-ACK */
		save_syn:1,	/* Save headers of SYN packet */
		is_cwnd_limited:1,/* क्रमward progress limited by snd_cwnd? */
		syn_smc:1;	/* SYN includes SMC */
	__u32	max_packets_out;
	__u32	lsndसमय;
	__u32	prior_cwnd;
	__u64	tcp_mstamp;	/* most recent packet received/sent */
पूर्ण __attribute__((preserve_access_index));

अटल __always_अंतरभूत काष्ठा inet_connection_sock *inet_csk(स्थिर काष्ठा sock *sk)
अणु
	वापस (काष्ठा inet_connection_sock *)sk;
पूर्ण

अटल __always_अंतरभूत व्योम *inet_csk_ca(स्थिर काष्ठा sock *sk)
अणु
	वापस (व्योम *)inet_csk(sk)->icsk_ca_priv;
पूर्ण

अटल __always_अंतरभूत काष्ठा tcp_sock *tcp_sk(स्थिर काष्ठा sock *sk)
अणु
	वापस (काष्ठा tcp_sock *)sk;
पूर्ण

अटल __always_अंतरभूत bool beक्रमe(__u32 seq1, __u32 seq2)
अणु
	वापस (__s32)(seq1-seq2) < 0;
पूर्ण
#घोषणा after(seq2, seq1) 	beक्रमe(seq1, seq2)

#घोषणा	TCP_ECN_OK		1
#घोषणा	TCP_ECN_QUEUE_CWR	2
#घोषणा	TCP_ECN_DEMAND_CWR	4
#घोषणा	TCP_ECN_SEEN		8

क्रमागत inet_csk_ack_state_t अणु
	ICSK_ACK_SCHED	= 1,
	ICSK_ACK_TIMER  = 2,
	ICSK_ACK_PUSHED = 4,
	ICSK_ACK_PUSHED2 = 8,
	ICSK_ACK_NOW = 16	/* Send the next ACK immediately (once) */
पूर्ण;

क्रमागत tcp_ca_event अणु
	CA_EVENT_TX_START = 0,
	CA_EVENT_CWND_RESTART = 1,
	CA_EVENT_COMPLETE_CWR = 2,
	CA_EVENT_LOSS = 3,
	CA_EVENT_ECN_NO_CE = 4,
	CA_EVENT_ECN_IS_CE = 5,
पूर्ण;

काष्ठा ack_sample अणु
	__u32 pkts_acked;
	__s32 rtt_us;
	__u32 in_flight;
पूर्ण __attribute__((preserve_access_index));

काष्ठा rate_sample अणु
	__u64  prior_mstamp; /* starting बारtamp क्रम पूर्णांकerval */
	__u32  prior_delivered;	/* tp->delivered at "prior_mstamp" */
	__s32  delivered;		/* number of packets delivered over पूर्णांकerval */
	दीर्घ पूर्णांकerval_us;	/* समय क्रम tp->delivered to incr "delivered" */
	__u32 snd_पूर्णांकerval_us;	/* snd पूर्णांकerval क्रम delivered packets */
	__u32 rcv_पूर्णांकerval_us;	/* rcv पूर्णांकerval क्रम delivered packets */
	दीर्घ rtt_us;		/* RTT of last (S)ACKed packet (or -1) */
	पूर्णांक  losses;		/* number of packets marked lost upon ACK */
	__u32  acked_sacked;	/* number of packets newly (S)ACKed upon ACK */
	__u32  prior_in_flight;	/* in flight beक्रमe this ACK */
	bool is_app_limited;	/* is sample from packet with bubble in pipe? */
	bool is_retrans;	/* is sample from retransmission? */
	bool is_ack_delayed;	/* is this (likely) a delayed ACK? */
पूर्ण __attribute__((preserve_access_index));

#घोषणा TCP_CA_NAME_MAX		16
#घोषणा TCP_CONG_NEEDS_ECN	0x2

काष्ठा tcp_congestion_ops अणु
	अक्षर name[TCP_CA_NAME_MAX];
	__u32 flags;

	/* initialize निजी data (optional) */
	व्योम (*init)(काष्ठा sock *sk);
	/* cleanup निजी data  (optional) */
	व्योम (*release)(काष्ठा sock *sk);

	/* वापस slow start threshold (required) */
	__u32 (*ssthresh)(काष्ठा sock *sk);
	/* करो new cwnd calculation (required) */
	व्योम (*cong_aव्योम)(काष्ठा sock *sk, __u32 ack, __u32 acked);
	/* call beक्रमe changing ca_state (optional) */
	व्योम (*set_state)(काष्ठा sock *sk, __u8 new_state);
	/* call when cwnd event occurs (optional) */
	व्योम (*cwnd_event)(काष्ठा sock *sk, क्रमागत tcp_ca_event ev);
	/* call when ack arrives (optional) */
	व्योम (*in_ack_event)(काष्ठा sock *sk, __u32 flags);
	/* new value of cwnd after loss (required) */
	__u32  (*unकरो_cwnd)(काष्ठा sock *sk);
	/* hook क्रम packet ack accounting (optional) */
	व्योम (*pkts_acked)(काष्ठा sock *sk, स्थिर काष्ठा ack_sample *sample);
	/* override sysctl_tcp_min_tso_segs */
	__u32 (*min_tso_segs)(काष्ठा sock *sk);
	/* वापसs the multiplier used in tcp_sndbuf_expand (optional) */
	__u32 (*sndbuf_expand)(काष्ठा sock *sk);
	/* call when packets are delivered to update cwnd and pacing rate,
	 * after all the ca_state processing. (optional)
	 */
	व्योम (*cong_control)(काष्ठा sock *sk, स्थिर काष्ठा rate_sample *rs);
	व्योम *owner;
पूर्ण;

#घोषणा min(a, b) ((a) < (b) ? (a) : (b))
#घोषणा max(a, b) ((a) > (b) ? (a) : (b))
#घोषणा min_not_zero(x, y) (अणु			\
	typeof(x) __x = (x);			\
	typeof(y) __y = (y);			\
	__x == 0 ? __y : ((__y == 0) ? __x : min(__x, __y)); पूर्ण)

अटल __always_अंतरभूत bool tcp_in_slow_start(स्थिर काष्ठा tcp_sock *tp)
अणु
	वापस tp->snd_cwnd < tp->snd_ssthresh;
पूर्ण

अटल __always_अंतरभूत bool tcp_is_cwnd_limited(स्थिर काष्ठा sock *sk)
अणु
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk);

	/* If in slow start, ensure cwnd grows to twice what was ACKed. */
	अगर (tcp_in_slow_start(tp))
		वापस tp->snd_cwnd < 2 * tp->max_packets_out;

	वापस !!BPF_CORE_READ_BITFIELD(tp, is_cwnd_limited);
पूर्ण

बाह्य __u32 tcp_slow_start(काष्ठा tcp_sock *tp, __u32 acked) __ksym;
बाह्य व्योम tcp_cong_aव्योम_ai(काष्ठा tcp_sock *tp, __u32 w, __u32 acked) __ksym;

#पूर्ण_अगर
