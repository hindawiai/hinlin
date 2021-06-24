<शैली गुरु>
#अगर_अघोषित _TCP_DCTCP_H
#घोषणा _TCP_DCTCP_H

अटल अंतरभूत व्योम dctcp_ece_ack_cwr(काष्ठा sock *sk, u32 ce_state)
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
अटल अंतरभूत व्योम dctcp_ece_ack_update(काष्ठा sock *sk, क्रमागत tcp_ca_event evt,
					u32 *prior_rcv_nxt, u32 *ce_state)
अणु
	u32 new_ce_state = (evt == CA_EVENT_ECN_IS_CE) ? 1 : 0;

	अगर (*ce_state != new_ce_state) अणु
		/* CE state has changed, क्रमce an immediate ACK to
		 * reflect the new CE state. If an ACK was delayed,
		 * send that first to reflect the prior CE state.
		 */
		अगर (inet_csk(sk)->icsk_ack.pending & ICSK_ACK_TIMER) अणु
			dctcp_ece_ack_cwr(sk, *ce_state);
			__tcp_send_ack(sk, *prior_rcv_nxt);
		पूर्ण
		inet_csk(sk)->icsk_ack.pending |= ICSK_ACK_NOW;
	पूर्ण
	*prior_rcv_nxt = tcp_sk(sk)->rcv_nxt;
	*ce_state = new_ce_state;
	dctcp_ece_ack_cwr(sk, new_ce_state);
पूर्ण

#पूर्ण_अगर
