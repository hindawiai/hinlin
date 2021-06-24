<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2019 Facebook */

/* WARNING: This implemenation is not necessarily the same
 * as the tcp_dctcp.c.  The purpose is मुख्यly क्रम testing
 * the kernel BPF logic.
 */

#समावेश <मानकघोष.स>
#समावेश <linux/bpf.h>
#समावेश <linux/types.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/tcp.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>
#समावेश "bpf_tcp_helpers.h"

अक्षर _license[] SEC("license") = "GPL";

पूर्णांक stg_result = 0;

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_SK_STORAGE);
	__uपूर्णांक(map_flags, BPF_F_NO_PREALLOC);
	__type(key, पूर्णांक);
	__type(value, पूर्णांक);
पूर्ण sk_stg_map SEC(".maps");

#घोषणा DCTCP_MAX_ALPHA	1024U

काष्ठा dctcp अणु
	__u32 old_delivered;
	__u32 old_delivered_ce;
	__u32 prior_rcv_nxt;
	__u32 dctcp_alpha;
	__u32 next_seq;
	__u32 ce_state;
	__u32 loss_cwnd;
पूर्ण;

अटल अचिन्हित पूर्णांक dctcp_shअगरt_g = 4; /* g = 1/2^4 */
अटल अचिन्हित पूर्णांक dctcp_alpha_on_init = DCTCP_MAX_ALPHA;

अटल __always_अंतरभूत व्योम dctcp_reset(स्थिर काष्ठा tcp_sock *tp,
					काष्ठा dctcp *ca)
अणु
	ca->next_seq = tp->snd_nxt;

	ca->old_delivered = tp->delivered;
	ca->old_delivered_ce = tp->delivered_ce;
पूर्ण

SEC("struct_ops/dctcp_init")
व्योम BPF_PROG(dctcp_init, काष्ठा sock *sk)
अणु
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा dctcp *ca = inet_csk_ca(sk);
	पूर्णांक *stg;

	ca->prior_rcv_nxt = tp->rcv_nxt;
	ca->dctcp_alpha = min(dctcp_alpha_on_init, DCTCP_MAX_ALPHA);
	ca->loss_cwnd = 0;
	ca->ce_state = 0;

	stg = bpf_sk_storage_get(&sk_stg_map, (व्योम *)tp, शून्य, 0);
	अगर (stg) अणु
		stg_result = *stg;
		bpf_sk_storage_delete(&sk_stg_map, (व्योम *)tp);
	पूर्ण
	dctcp_reset(tp, ca);
पूर्ण

SEC("struct_ops/dctcp_ssthresh")
__u32 BPF_PROG(dctcp_ssthresh, काष्ठा sock *sk)
अणु
	काष्ठा dctcp *ca = inet_csk_ca(sk);
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	ca->loss_cwnd = tp->snd_cwnd;
	वापस max(tp->snd_cwnd - ((tp->snd_cwnd * ca->dctcp_alpha) >> 11U), 2U);
पूर्ण

SEC("struct_ops/dctcp_update_alpha")
व्योम BPF_PROG(dctcp_update_alpha, काष्ठा sock *sk, __u32 flags)
अणु
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(sk);
	काष्ठा dctcp *ca = inet_csk_ca(sk);

	/* Expired RTT */
	अगर (!beक्रमe(tp->snd_una, ca->next_seq)) अणु
		__u32 delivered_ce = tp->delivered_ce - ca->old_delivered_ce;
		__u32 alpha = ca->dctcp_alpha;

		/* alpha = (1 - g) * alpha + g * F */

		alpha -= min_not_zero(alpha, alpha >> dctcp_shअगरt_g);
		अगर (delivered_ce) अणु
			__u32 delivered = tp->delivered - ca->old_delivered;

			/* If dctcp_shअगरt_g == 1, a 32bit value would overflow
			 * after 8 M packets.
			 */
			delivered_ce <<= (10 - dctcp_shअगरt_g);
			delivered_ce /= max(1U, delivered);

			alpha = min(alpha + delivered_ce, DCTCP_MAX_ALPHA);
		पूर्ण
		ca->dctcp_alpha = alpha;
		dctcp_reset(tp, ca);
	पूर्ण
पूर्ण

अटल __always_अंतरभूत व्योम dctcp_react_to_loss(काष्ठा sock *sk)
अणु
	काष्ठा dctcp *ca = inet_csk_ca(sk);
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	ca->loss_cwnd = tp->snd_cwnd;
	tp->snd_ssthresh = max(tp->snd_cwnd >> 1U, 2U);
पूर्ण

SEC("struct_ops/dctcp_state")
व्योम BPF_PROG(dctcp_state, काष्ठा sock *sk, __u8 new_state)
अणु
	अगर (new_state == TCP_CA_Recovery &&
	    new_state != BPF_CORE_READ_BITFIELD(inet_csk(sk), icsk_ca_state))
		dctcp_react_to_loss(sk);
	/* We handle RTO in dctcp_cwnd_event to ensure that we perक्रमm only
	 * one loss-adjusपंचांगent per RTT.
	 */
पूर्ण

अटल __always_अंतरभूत व्योम dctcp_ece_ack_cwr(काष्ठा sock *sk, __u32 ce_state)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(sk);

	अगर (ce_state == 1)
		tp->ecn_flags |= TCP_ECN_DEMAND_CWR;
	अन्यथा
		tp->ecn_flags &= ~TCP_ECN_DEMAND_CWR;
पूर्ण

/* Minimal DCTP CE state machine:
 *
 * S:	0 <- last pkt was non-CE
 *	1 <- last pkt was CE
 */
अटल __always_अंतरभूत
व्योम dctcp_ece_ack_update(काष्ठा sock *sk, क्रमागत tcp_ca_event evt,
			  __u32 *prior_rcv_nxt, __u32 *ce_state)
अणु
	__u32 new_ce_state = (evt == CA_EVENT_ECN_IS_CE) ? 1 : 0;

	अगर (*ce_state != new_ce_state) अणु
		/* CE state has changed, क्रमce an immediate ACK to
		 * reflect the new CE state. If an ACK was delayed,
		 * send that first to reflect the prior CE state.
		 */
		अगर (inet_csk(sk)->icsk_ack.pending & ICSK_ACK_TIMER) अणु
			dctcp_ece_ack_cwr(sk, *ce_state);
			bpf_tcp_send_ack(sk, *prior_rcv_nxt);
		पूर्ण
		inet_csk(sk)->icsk_ack.pending |= ICSK_ACK_NOW;
	पूर्ण
	*prior_rcv_nxt = tcp_sk(sk)->rcv_nxt;
	*ce_state = new_ce_state;
	dctcp_ece_ack_cwr(sk, new_ce_state);
पूर्ण

SEC("struct_ops/dctcp_cwnd_event")
व्योम BPF_PROG(dctcp_cwnd_event, काष्ठा sock *sk, क्रमागत tcp_ca_event ev)
अणु
	काष्ठा dctcp *ca = inet_csk_ca(sk);

	चयन (ev) अणु
	हाल CA_EVENT_ECN_IS_CE:
	हाल CA_EVENT_ECN_NO_CE:
		dctcp_ece_ack_update(sk, ev, &ca->prior_rcv_nxt, &ca->ce_state);
		अवरोध;
	हाल CA_EVENT_LOSS:
		dctcp_react_to_loss(sk);
		अवरोध;
	शेष:
		/* Don't care क्रम the rest. */
		अवरोध;
	पूर्ण
पूर्ण

SEC("struct_ops/dctcp_cwnd_undo")
__u32 BPF_PROG(dctcp_cwnd_unकरो, काष्ठा sock *sk)
अणु
	स्थिर काष्ठा dctcp *ca = inet_csk_ca(sk);

	वापस max(tcp_sk(sk)->snd_cwnd, ca->loss_cwnd);
पूर्ण

बाह्य व्योम tcp_reno_cong_aव्योम(काष्ठा sock *sk, __u32 ack, __u32 acked) __ksym;

SEC("struct_ops/dctcp_reno_cong_avoid")
व्योम BPF_PROG(dctcp_cong_aव्योम, काष्ठा sock *sk, __u32 ack, __u32 acked)
अणु
	tcp_reno_cong_aव्योम(sk, ack, acked);
पूर्ण

SEC(".struct_ops")
काष्ठा tcp_congestion_ops dctcp_nouse = अणु
	.init		= (व्योम *)dctcp_init,
	.set_state	= (व्योम *)dctcp_state,
	.flags		= TCP_CONG_NEEDS_ECN,
	.name		= "bpf_dctcp_nouse",
पूर्ण;

SEC(".struct_ops")
काष्ठा tcp_congestion_ops dctcp = अणु
	.init		= (व्योम *)dctcp_init,
	.in_ack_event   = (व्योम *)dctcp_update_alpha,
	.cwnd_event	= (व्योम *)dctcp_cwnd_event,
	.ssthresh	= (व्योम *)dctcp_ssthresh,
	.cong_aव्योम	= (व्योम *)dctcp_cong_aव्योम,
	.unकरो_cwnd	= (व्योम *)dctcp_cwnd_unकरो,
	.set_state	= (व्योम *)dctcp_state,
	.flags		= TCP_CONG_NEEDS_ECN,
	.name		= "bpf_dctcp",
पूर्ण;
