<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Multipath TCP
 *
 * Copyright (c) 2017 - 2019, Intel Corporation.
 */

#घोषणा pr_fmt(fmt) "MPTCP: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/atomic.h>
#समावेश <net/sock.h>
#समावेश <net/inet_common.h>
#समावेश <net/inet_hashtables.h>
#समावेश <net/protocol.h>
#समावेश <net/tcp.h>
#समावेश <net/tcp_states.h>
#अगर IS_ENABLED(CONFIG_MPTCP_IPV6)
#समावेश <net/transp_v6.h>
#पूर्ण_अगर
#समावेश <net/mptcp.h>
#समावेश <net/xfrm.h>
#समावेश "protocol.h"
#समावेश "mib.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/mptcp.h>

#अगर IS_ENABLED(CONFIG_MPTCP_IPV6)
काष्ठा mptcp6_sock अणु
	काष्ठा mptcp_sock msk;
	काष्ठा ipv6_pinfo np;
पूर्ण;
#पूर्ण_अगर

काष्ठा mptcp_skb_cb अणु
	u64 map_seq;
	u64 end_seq;
	u32 offset;
पूर्ण;

#घोषणा MPTCP_SKB_CB(__skb)	((काष्ठा mptcp_skb_cb *)&((__skb)->cb[0]))

अटल काष्ठा percpu_counter mptcp_sockets_allocated;

अटल व्योम __mptcp_destroy_sock(काष्ठा sock *sk);
अटल व्योम __mptcp_check_send_data_fin(काष्ठा sock *sk);

DEFINE_PER_CPU(काष्ठा mptcp_delegated_action, mptcp_delegated_actions);
अटल काष्ठा net_device mptcp_napi_dev;

/* If msk has an initial subflow socket, and the MP_CAPABLE handshake has not
 * completed yet or has failed, वापस the subflow socket.
 * Otherwise वापस शून्य.
 */
काष्ठा socket *__mptcp_nmpc_socket(स्थिर काष्ठा mptcp_sock *msk)
अणु
	अगर (!msk->subflow || READ_ONCE(msk->can_ack))
		वापस शून्य;

	वापस msk->subflow;
पूर्ण

/* Returns end sequence number of the receiver's advertised winकरोw */
अटल u64 mptcp_wnd_end(स्थिर काष्ठा mptcp_sock *msk)
अणु
	वापस READ_ONCE(msk->wnd_end);
पूर्ण

अटल bool mptcp_is_tcpsk(काष्ठा sock *sk)
अणु
	काष्ठा socket *sock = sk->sk_socket;

	अगर (unlikely(sk->sk_prot == &tcp_prot)) अणु
		/* we are being invoked after mptcp_accept() has
		 * accepted a non-mp-capable flow: sk is a tcp_sk,
		 * not an mptcp one.
		 *
		 * Hand the socket over to tcp so all further socket ops
		 * bypass mptcp.
		 */
		sock->ops = &inet_stream_ops;
		वापस true;
#अगर IS_ENABLED(CONFIG_MPTCP_IPV6)
	पूर्ण अन्यथा अगर (unlikely(sk->sk_prot == &tcpv6_prot)) अणु
		sock->ops = &inet6_stream_ops;
		वापस true;
#पूर्ण_अगर
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक __mptcp_socket_create(काष्ठा mptcp_sock *msk)
अणु
	काष्ठा mptcp_subflow_context *subflow;
	काष्ठा sock *sk = (काष्ठा sock *)msk;
	काष्ठा socket *ssock;
	पूर्णांक err;

	err = mptcp_subflow_create_socket(sk, &ssock);
	अगर (err)
		वापस err;

	msk->first = ssock->sk;
	msk->subflow = ssock;
	subflow = mptcp_subflow_ctx(ssock->sk);
	list_add(&subflow->node, &msk->conn_list);
	sock_hold(ssock->sk);
	subflow->request_mptcp = 1;
	mptcp_sock_graft(msk->first, sk->sk_socket);

	वापस 0;
पूर्ण

अटल व्योम mptcp_drop(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	sk_drops_add(sk, skb);
	__kमुक्त_skb(skb);
पूर्ण

अटल bool mptcp_try_coalesce(काष्ठा sock *sk, काष्ठा sk_buff *to,
			       काष्ठा sk_buff *from)
अणु
	bool fragstolen;
	पूर्णांक delta;

	अगर (MPTCP_SKB_CB(from)->offset ||
	    !skb_try_coalesce(to, from, &fragstolen, &delta))
		वापस false;

	pr_debug("colesced seq %llx into %llx new len %d new end seq %llx",
		 MPTCP_SKB_CB(from)->map_seq, MPTCP_SKB_CB(to)->map_seq,
		 to->len, MPTCP_SKB_CB(from)->end_seq);
	MPTCP_SKB_CB(to)->end_seq = MPTCP_SKB_CB(from)->end_seq;
	kमुक्त_skb_partial(from, fragstolen);
	atomic_add(delta, &sk->sk_rmem_alloc);
	sk_mem_अक्षरge(sk, delta);
	वापस true;
पूर्ण

अटल bool mptcp_ooo_try_coalesce(काष्ठा mptcp_sock *msk, काष्ठा sk_buff *to,
				   काष्ठा sk_buff *from)
अणु
	अगर (MPTCP_SKB_CB(from)->map_seq != MPTCP_SKB_CB(to)->end_seq)
		वापस false;

	वापस mptcp_try_coalesce((काष्ठा sock *)msk, to, from);
पूर्ण

/* "inspired" by tcp_data_queue_ofo(), मुख्य dअगरferences:
 * - use mptcp seqs
 * - करोn't cope with sacks
 */
अटल व्योम mptcp_data_queue_ofo(काष्ठा mptcp_sock *msk, काष्ठा sk_buff *skb)
अणु
	काष्ठा sock *sk = (काष्ठा sock *)msk;
	काष्ठा rb_node **p, *parent;
	u64 seq, end_seq, max_seq;
	काष्ठा sk_buff *skb1;

	seq = MPTCP_SKB_CB(skb)->map_seq;
	end_seq = MPTCP_SKB_CB(skb)->end_seq;
	max_seq = READ_ONCE(msk->rcv_wnd_sent);

	pr_debug("msk=%p seq=%llx limit=%llx empty=%d", msk, seq, max_seq,
		 RB_EMPTY_ROOT(&msk->out_of_order_queue));
	अगर (after64(end_seq, max_seq)) अणु
		/* out of winकरोw */
		mptcp_drop(sk, skb);
		pr_debug("oow by %lld, rcv_wnd_sent %llu\n",
			 (अचिन्हित दीर्घ दीर्घ)end_seq - (अचिन्हित दीर्घ)max_seq,
			 (अचिन्हित दीर्घ दीर्घ)msk->rcv_wnd_sent);
		MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_NODSSWINDOW);
		वापस;
	पूर्ण

	p = &msk->out_of_order_queue.rb_node;
	MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_OFOQUEUE);
	अगर (RB_EMPTY_ROOT(&msk->out_of_order_queue)) अणु
		rb_link_node(&skb->rbnode, शून्य, p);
		rb_insert_color(&skb->rbnode, &msk->out_of_order_queue);
		msk->ooo_last_skb = skb;
		जाओ end;
	पूर्ण

	/* with 2 subflows, adding at end of ooo queue is quite likely
	 * Use of ooo_last_skb aव्योमs the O(Log(N)) rbtree lookup.
	 */
	अगर (mptcp_ooo_try_coalesce(msk, msk->ooo_last_skb, skb)) अणु
		MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_OFOMERGE);
		MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_OFOQUEUETAIL);
		वापस;
	पूर्ण

	/* Can aव्योम an rbtree lookup अगर we are adding skb after ooo_last_skb */
	अगर (!beक्रमe64(seq, MPTCP_SKB_CB(msk->ooo_last_skb)->end_seq)) अणु
		MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_OFOQUEUETAIL);
		parent = &msk->ooo_last_skb->rbnode;
		p = &parent->rb_right;
		जाओ insert;
	पूर्ण

	/* Find place to insert this segment. Handle overlaps on the way. */
	parent = शून्य;
	जबतक (*p) अणु
		parent = *p;
		skb1 = rb_to_skb(parent);
		अगर (beक्रमe64(seq, MPTCP_SKB_CB(skb1)->map_seq)) अणु
			p = &parent->rb_left;
			जारी;
		पूर्ण
		अगर (beक्रमe64(seq, MPTCP_SKB_CB(skb1)->end_seq)) अणु
			अगर (!after64(end_seq, MPTCP_SKB_CB(skb1)->end_seq)) अणु
				/* All the bits are present. Drop. */
				mptcp_drop(sk, skb);
				MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_DUPDATA);
				वापस;
			पूर्ण
			अगर (after64(seq, MPTCP_SKB_CB(skb1)->map_seq)) अणु
				/* partial overlap:
				 *     |     skb      |
				 *  |     skb1    |
				 * जारी traversing
				 */
			पूर्ण अन्यथा अणु
				/* skb's seq == skb1's seq and skb covers skb1.
				 * Replace skb1 with skb.
				 */
				rb_replace_node(&skb1->rbnode, &skb->rbnode,
						&msk->out_of_order_queue);
				mptcp_drop(sk, skb1);
				MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_DUPDATA);
				जाओ merge_right;
			पूर्ण
		पूर्ण अन्यथा अगर (mptcp_ooo_try_coalesce(msk, skb1, skb)) अणु
			MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_OFOMERGE);
			वापस;
		पूर्ण
		p = &parent->rb_right;
	पूर्ण

insert:
	/* Insert segment पूर्णांकo RB tree. */
	rb_link_node(&skb->rbnode, parent, p);
	rb_insert_color(&skb->rbnode, &msk->out_of_order_queue);

merge_right:
	/* Remove other segments covered by skb. */
	जबतक ((skb1 = skb_rb_next(skb)) != शून्य) अणु
		अगर (beक्रमe64(end_seq, MPTCP_SKB_CB(skb1)->end_seq))
			अवरोध;
		rb_erase(&skb1->rbnode, &msk->out_of_order_queue);
		mptcp_drop(sk, skb1);
		MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_DUPDATA);
	पूर्ण
	/* If there is no skb after us, we are the last_skb ! */
	अगर (!skb1)
		msk->ooo_last_skb = skb;

end:
	skb_condense(skb);
	skb_set_owner_r(skb, sk);
पूर्ण

अटल bool __mptcp_move_skb(काष्ठा mptcp_sock *msk, काष्ठा sock *ssk,
			     काष्ठा sk_buff *skb, अचिन्हित पूर्णांक offset,
			     माप_प्रकार copy_len)
अणु
	काष्ठा mptcp_subflow_context *subflow = mptcp_subflow_ctx(ssk);
	काष्ठा sock *sk = (काष्ठा sock *)msk;
	काष्ठा sk_buff *tail;

	__skb_unlink(skb, &ssk->sk_receive_queue);

	skb_ext_reset(skb);
	skb_orphan(skb);

	/* try to fetch required memory from subflow */
	अगर (!sk_rmem_schedule(sk, skb, skb->truesize)) अणु
		पूर्णांक amount = sk_mem_pages(skb->truesize) << SK_MEM_QUANTUM_SHIFT;

		अगर (ssk->sk_क्रमward_alloc < amount)
			जाओ drop;

		ssk->sk_क्रमward_alloc -= amount;
		sk->sk_क्रमward_alloc += amount;
	पूर्ण

	/* the skb map_seq accounts क्रम the skb offset:
	 * mptcp_subflow_get_mapped_dsn() is based on the current tp->copied_seq
	 * value
	 */
	MPTCP_SKB_CB(skb)->map_seq = mptcp_subflow_get_mapped_dsn(subflow);
	MPTCP_SKB_CB(skb)->end_seq = MPTCP_SKB_CB(skb)->map_seq + copy_len;
	MPTCP_SKB_CB(skb)->offset = offset;

	अगर (MPTCP_SKB_CB(skb)->map_seq == msk->ack_seq) अणु
		/* in sequence */
		WRITE_ONCE(msk->ack_seq, msk->ack_seq + copy_len);
		tail = skb_peek_tail(&sk->sk_receive_queue);
		अगर (tail && mptcp_try_coalesce(sk, tail, skb))
			वापस true;

		skb_set_owner_r(skb, sk);
		__skb_queue_tail(&sk->sk_receive_queue, skb);
		वापस true;
	पूर्ण अन्यथा अगर (after64(MPTCP_SKB_CB(skb)->map_seq, msk->ack_seq)) अणु
		mptcp_data_queue_ofo(msk, skb);
		वापस false;
	पूर्ण

	/* old data, keep it simple and drop the whole pkt, sender
	 * will retransmit as needed, अगर needed.
	 */
	MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_DUPDATA);
drop:
	mptcp_drop(sk, skb);
	वापस false;
पूर्ण

अटल व्योम mptcp_stop_समयr(काष्ठा sock *sk)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);

	sk_stop_समयr(sk, &icsk->icsk_retransmit_समयr);
	mptcp_sk(sk)->समयr_ival = 0;
पूर्ण

अटल व्योम mptcp_बंद_wake_up(काष्ठा sock *sk)
अणु
	अगर (sock_flag(sk, SOCK_DEAD))
		वापस;

	sk->sk_state_change(sk);
	अगर (sk->sk_shutकरोwn == SHUTDOWN_MASK ||
	    sk->sk_state == TCP_CLOSE)
		sk_wake_async(sk, SOCK_WAKE_WAITD, POLL_HUP);
	अन्यथा
		sk_wake_async(sk, SOCK_WAKE_WAITD, POLL_IN);
पूर्ण

अटल bool mptcp_pending_data_fin_ack(काष्ठा sock *sk)
अणु
	काष्ठा mptcp_sock *msk = mptcp_sk(sk);

	वापस !__mptcp_check_fallback(msk) &&
	       ((1 << sk->sk_state) &
		(TCPF_FIN_WAIT1 | TCPF_CLOSING | TCPF_LAST_ACK)) &&
	       msk->ग_लिखो_seq == READ_ONCE(msk->snd_una);
पूर्ण

अटल व्योम mptcp_check_data_fin_ack(काष्ठा sock *sk)
अणु
	काष्ठा mptcp_sock *msk = mptcp_sk(sk);

	/* Look क्रम an acknowledged DATA_FIN */
	अगर (mptcp_pending_data_fin_ack(sk)) अणु
		WRITE_ONCE(msk->snd_data_fin_enable, 0);

		चयन (sk->sk_state) अणु
		हाल TCP_FIN_WAIT1:
			inet_sk_state_store(sk, TCP_FIN_WAIT2);
			अवरोध;
		हाल TCP_CLOSING:
		हाल TCP_LAST_ACK:
			inet_sk_state_store(sk, TCP_CLOSE);
			अवरोध;
		पूर्ण

		mptcp_बंद_wake_up(sk);
	पूर्ण
पूर्ण

अटल bool mptcp_pending_data_fin(काष्ठा sock *sk, u64 *seq)
अणु
	काष्ठा mptcp_sock *msk = mptcp_sk(sk);

	अगर (READ_ONCE(msk->rcv_data_fin) &&
	    ((1 << sk->sk_state) &
	     (TCPF_ESTABLISHED | TCPF_FIN_WAIT1 | TCPF_FIN_WAIT2))) अणु
		u64 rcv_data_fin_seq = READ_ONCE(msk->rcv_data_fin_seq);

		अगर (msk->ack_seq == rcv_data_fin_seq) अणु
			अगर (seq)
				*seq = rcv_data_fin_seq;

			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम mptcp_set_datafin_समयout(स्थिर काष्ठा sock *sk)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);

	mptcp_sk(sk)->समयr_ival = min(TCP_RTO_MAX,
				       TCP_RTO_MIN << icsk->icsk_retransmits);
पूर्ण

अटल व्योम mptcp_set_समयout(स्थिर काष्ठा sock *sk, स्थिर काष्ठा sock *ssk)
अणु
	दीर्घ tout = ssk && inet_csk(ssk)->icsk_pending ?
				      inet_csk(ssk)->icsk_समयout - jअगरfies : 0;

	अगर (tout <= 0)
		tout = mptcp_sk(sk)->समयr_ival;
	mptcp_sk(sk)->समयr_ival = tout > 0 ? tout : TCP_RTO_MIN;
पूर्ण

अटल bool tcp_can_send_ack(स्थिर काष्ठा sock *ssk)
अणु
	वापस !((1 << inet_sk_state_load(ssk)) &
	       (TCPF_SYN_SENT | TCPF_SYN_RECV | TCPF_TIME_WAIT | TCPF_CLOSE | TCPF_LISTEN));
पूर्ण

अटल व्योम mptcp_send_ack(काष्ठा mptcp_sock *msk)
अणु
	काष्ठा mptcp_subflow_context *subflow;

	mptcp_क्रम_each_subflow(msk, subflow) अणु
		काष्ठा sock *ssk = mptcp_subflow_tcp_sock(subflow);

		lock_sock(ssk);
		अगर (tcp_can_send_ack(ssk))
			tcp_send_ack(ssk);
		release_sock(ssk);
	पूर्ण
पूर्ण

अटल bool mptcp_subflow_cleanup_rbuf(काष्ठा sock *ssk)
अणु
	पूर्णांक ret;

	lock_sock(ssk);
	ret = tcp_can_send_ack(ssk);
	अगर (ret)
		tcp_cleanup_rbuf(ssk, 1);
	release_sock(ssk);
	वापस ret;
पूर्ण

अटल व्योम mptcp_cleanup_rbuf(काष्ठा mptcp_sock *msk)
अणु
	काष्ठा sock *ack_hपूर्णांक = READ_ONCE(msk->ack_hपूर्णांक);
	पूर्णांक old_space = READ_ONCE(msk->old_wspace);
	काष्ठा mptcp_subflow_context *subflow;
	काष्ठा sock *sk = (काष्ठा sock *)msk;
	bool cleanup;

	/* this is a simple superset of what tcp_cleanup_rbuf() implements
	 * so that we करोn't have to acquire the ssk socket lock most of the समय
	 * to करो actually nothing
	 */
	cleanup = __mptcp_space(sk) - old_space >= max(0, old_space);
	अगर (!cleanup)
		वापस;

	/* अगर the hपूर्णांकed ssk is still active, try to use it */
	अगर (likely(ack_hपूर्णांक)) अणु
		mptcp_क्रम_each_subflow(msk, subflow) अणु
			काष्ठा sock *ssk = mptcp_subflow_tcp_sock(subflow);

			अगर (ack_hपूर्णांक == ssk && mptcp_subflow_cleanup_rbuf(ssk))
				वापस;
		पूर्ण
	पूर्ण

	/* otherwise pick the first active subflow */
	mptcp_क्रम_each_subflow(msk, subflow)
		अगर (mptcp_subflow_cleanup_rbuf(mptcp_subflow_tcp_sock(subflow)))
			वापस;
पूर्ण

अटल bool mptcp_check_data_fin(काष्ठा sock *sk)
अणु
	काष्ठा mptcp_sock *msk = mptcp_sk(sk);
	u64 rcv_data_fin_seq;
	bool ret = false;

	अगर (__mptcp_check_fallback(msk))
		वापस ret;

	/* Need to ack a DATA_FIN received from a peer जबतक this side
	 * of the connection is in ESTABLISHED, FIN_WAIT1, or FIN_WAIT2.
	 * msk->rcv_data_fin was set when parsing the incoming options
	 * at the subflow level and the msk lock was not held, so this
	 * is the first opportunity to act on the DATA_FIN and change
	 * the msk state.
	 *
	 * If we are caught up to the sequence number of the incoming
	 * DATA_FIN, send the DATA_ACK now and करो state transition.  If
	 * not caught up, करो nothing and let the recv code send DATA_ACK
	 * when catching up.
	 */

	अगर (mptcp_pending_data_fin(sk, &rcv_data_fin_seq)) अणु
		WRITE_ONCE(msk->ack_seq, msk->ack_seq + 1);
		WRITE_ONCE(msk->rcv_data_fin, 0);

		sk->sk_shutकरोwn |= RCV_SHUTDOWN;
		smp_mb__beक्रमe_atomic(); /* SHUTDOWN must be visible first */
		set_bit(MPTCP_DATA_READY, &msk->flags);

		चयन (sk->sk_state) अणु
		हाल TCP_ESTABLISHED:
			inet_sk_state_store(sk, TCP_CLOSE_WAIT);
			अवरोध;
		हाल TCP_FIN_WAIT1:
			inet_sk_state_store(sk, TCP_CLOSING);
			अवरोध;
		हाल TCP_FIN_WAIT2:
			inet_sk_state_store(sk, TCP_CLOSE);
			अवरोध;
		शेष:
			/* Other states not expected */
			WARN_ON_ONCE(1);
			अवरोध;
		पूर्ण

		ret = true;
		mptcp_set_समयout(sk, शून्य);
		mptcp_send_ack(msk);
		mptcp_बंद_wake_up(sk);
	पूर्ण
	वापस ret;
पूर्ण

अटल bool __mptcp_move_skbs_from_subflow(काष्ठा mptcp_sock *msk,
					   काष्ठा sock *ssk,
					   अचिन्हित पूर्णांक *bytes)
अणु
	काष्ठा mptcp_subflow_context *subflow = mptcp_subflow_ctx(ssk);
	काष्ठा sock *sk = (काष्ठा sock *)msk;
	अचिन्हित पूर्णांक moved = 0;
	bool more_data_avail;
	काष्ठा tcp_sock *tp;
	bool करोne = false;
	पूर्णांक sk_rbuf;

	sk_rbuf = READ_ONCE(sk->sk_rcvbuf);

	अगर (!(sk->sk_userlocks & SOCK_RCVBUF_LOCK)) अणु
		पूर्णांक ssk_rbuf = READ_ONCE(ssk->sk_rcvbuf);

		अगर (unlikely(ssk_rbuf > sk_rbuf)) अणु
			WRITE_ONCE(sk->sk_rcvbuf, ssk_rbuf);
			sk_rbuf = ssk_rbuf;
		पूर्ण
	पूर्ण

	pr_debug("msk=%p ssk=%p", msk, ssk);
	tp = tcp_sk(ssk);
	करो अणु
		u32 map_reमुख्यing, offset;
		u32 seq = tp->copied_seq;
		काष्ठा sk_buff *skb;
		bool fin;

		/* try to move as much data as available */
		map_reमुख्यing = subflow->map_data_len -
				mptcp_subflow_get_map_offset(subflow);

		skb = skb_peek(&ssk->sk_receive_queue);
		अगर (!skb) अणु
			/* अगर no data is found, a racing workqueue/recvmsg
			 * alपढ़ोy processed the new data, stop here or we
			 * can enter an infinite loop
			 */
			अगर (!moved)
				करोne = true;
			अवरोध;
		पूर्ण

		अगर (__mptcp_check_fallback(msk)) अणु
			/* अगर we are running under the workqueue, TCP could have
			 * collapsed skbs between dummy map creation and now
			 * be sure to adjust the size
			 */
			map_reमुख्यing = skb->len;
			subflow->map_data_len = skb->len;
		पूर्ण

		offset = seq - TCP_SKB_CB(skb)->seq;
		fin = TCP_SKB_CB(skb)->tcp_flags & TCPHDR_FIN;
		अगर (fin) अणु
			करोne = true;
			seq++;
		पूर्ण

		अगर (offset < skb->len) अणु
			माप_प्रकार len = skb->len - offset;

			अगर (tp->urg_data)
				करोne = true;

			अगर (__mptcp_move_skb(msk, ssk, skb, offset, len))
				moved += len;
			seq += len;

			अगर (WARN_ON_ONCE(map_reमुख्यing < len))
				अवरोध;
		पूर्ण अन्यथा अणु
			WARN_ON_ONCE(!fin);
			sk_eat_skb(ssk, skb);
			करोne = true;
		पूर्ण

		WRITE_ONCE(tp->copied_seq, seq);
		more_data_avail = mptcp_subflow_data_available(ssk);

		अगर (atomic_पढ़ो(&sk->sk_rmem_alloc) > sk_rbuf) अणु
			करोne = true;
			अवरोध;
		पूर्ण
	पूर्ण जबतक (more_data_avail);
	WRITE_ONCE(msk->ack_hपूर्णांक, ssk);

	*bytes += moved;
	वापस करोne;
पूर्ण

अटल bool __mptcp_ofo_queue(काष्ठा mptcp_sock *msk)
अणु
	काष्ठा sock *sk = (काष्ठा sock *)msk;
	काष्ठा sk_buff *skb, *tail;
	bool moved = false;
	काष्ठा rb_node *p;
	u64 end_seq;

	p = rb_first(&msk->out_of_order_queue);
	pr_debug("msk=%p empty=%d", msk, RB_EMPTY_ROOT(&msk->out_of_order_queue));
	जबतक (p) अणु
		skb = rb_to_skb(p);
		अगर (after64(MPTCP_SKB_CB(skb)->map_seq, msk->ack_seq))
			अवरोध;

		p = rb_next(p);
		rb_erase(&skb->rbnode, &msk->out_of_order_queue);

		अगर (unlikely(!after64(MPTCP_SKB_CB(skb)->end_seq,
				      msk->ack_seq))) अणु
			mptcp_drop(sk, skb);
			MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_DUPDATA);
			जारी;
		पूर्ण

		end_seq = MPTCP_SKB_CB(skb)->end_seq;
		tail = skb_peek_tail(&sk->sk_receive_queue);
		अगर (!tail || !mptcp_ooo_try_coalesce(msk, tail, skb)) अणु
			पूर्णांक delta = msk->ack_seq - MPTCP_SKB_CB(skb)->map_seq;

			/* skip overlapping data, अगर any */
			pr_debug("uncoalesced seq=%llx ack seq=%llx delta=%d",
				 MPTCP_SKB_CB(skb)->map_seq, msk->ack_seq,
				 delta);
			MPTCP_SKB_CB(skb)->offset += delta;
			__skb_queue_tail(&sk->sk_receive_queue, skb);
		पूर्ण
		msk->ack_seq = end_seq;
		moved = true;
	पूर्ण
	वापस moved;
पूर्ण

/* In most हालs we will be able to lock the mptcp socket.  If its alपढ़ोy
 * owned, we need to defer to the work queue to aव्योम ABBA deadlock.
 */
अटल bool move_skbs_to_msk(काष्ठा mptcp_sock *msk, काष्ठा sock *ssk)
अणु
	काष्ठा sock *sk = (काष्ठा sock *)msk;
	अचिन्हित पूर्णांक moved = 0;

	अगर (inet_sk_state_load(sk) == TCP_CLOSE)
		वापस false;

	__mptcp_move_skbs_from_subflow(msk, ssk, &moved);
	__mptcp_ofo_queue(msk);
	अगर (unlikely(ssk->sk_err)) अणु
		अगर (!sock_owned_by_user(sk))
			__mptcp_error_report(sk);
		अन्यथा
			set_bit(MPTCP_ERROR_REPORT,  &msk->flags);
	पूर्ण

	/* If the moves have caught up with the DATA_FIN sequence number
	 * it's समय to ack the DATA_FIN and change socket state, but
	 * this is not a good place to change state. Let the workqueue
	 * करो it.
	 */
	अगर (mptcp_pending_data_fin(sk, शून्य))
		mptcp_schedule_work(sk);
	वापस moved > 0;
पूर्ण

व्योम mptcp_data_पढ़ोy(काष्ठा sock *sk, काष्ठा sock *ssk)
अणु
	काष्ठा mptcp_subflow_context *subflow = mptcp_subflow_ctx(ssk);
	काष्ठा mptcp_sock *msk = mptcp_sk(sk);
	पूर्णांक sk_rbuf, ssk_rbuf;

	/* The peer can send data जबतक we are shutting करोwn this
	 * subflow at msk deकाष्ठाion समय, but we must aव्योम enqueuing
	 * more data to the msk receive queue
	 */
	अगर (unlikely(subflow->disposable))
		वापस;

	ssk_rbuf = READ_ONCE(ssk->sk_rcvbuf);
	sk_rbuf = READ_ONCE(sk->sk_rcvbuf);
	अगर (unlikely(ssk_rbuf > sk_rbuf))
		sk_rbuf = ssk_rbuf;

	/* over limit? can't append more skbs to msk, Also, no need to wake-up*/
	अगर (atomic_पढ़ो(&sk->sk_rmem_alloc) > sk_rbuf)
		वापस;

	/* Wake-up the पढ़ोer only क्रम in-sequence data */
	mptcp_data_lock(sk);
	अगर (move_skbs_to_msk(msk, ssk)) अणु
		set_bit(MPTCP_DATA_READY, &msk->flags);
		sk->sk_data_पढ़ोy(sk);
	पूर्ण
	mptcp_data_unlock(sk);
पूर्ण

अटल bool mptcp_करो_flush_join_list(काष्ठा mptcp_sock *msk)
अणु
	काष्ठा mptcp_subflow_context *subflow;
	bool ret = false;

	अगर (likely(list_empty(&msk->join_list)))
		वापस false;

	spin_lock_bh(&msk->join_list_lock);
	list_क्रम_each_entry(subflow, &msk->join_list, node) अणु
		u32 sseq = READ_ONCE(subflow->setsockopt_seq);

		mptcp_propagate_sndbuf((काष्ठा sock *)msk, mptcp_subflow_tcp_sock(subflow));
		अगर (READ_ONCE(msk->setsockopt_seq) != sseq)
			ret = true;
	पूर्ण
	list_splice_tail_init(&msk->join_list, &msk->conn_list);
	spin_unlock_bh(&msk->join_list_lock);

	वापस ret;
पूर्ण

व्योम __mptcp_flush_join_list(काष्ठा mptcp_sock *msk)
अणु
	अगर (likely(!mptcp_करो_flush_join_list(msk)))
		वापस;

	अगर (!test_and_set_bit(MPTCP_WORK_SYNC_SETSOCKOPT, &msk->flags))
		mptcp_schedule_work((काष्ठा sock *)msk);
पूर्ण

अटल व्योम mptcp_flush_join_list(काष्ठा mptcp_sock *msk)
अणु
	bool sync_needed = test_and_clear_bit(MPTCP_WORK_SYNC_SETSOCKOPT, &msk->flags);

	might_sleep();

	अगर (!mptcp_करो_flush_join_list(msk) && !sync_needed)
		वापस;

	mptcp_sockopt_sync_all(msk);
पूर्ण

अटल bool mptcp_समयr_pending(काष्ठा sock *sk)
अणु
	वापस समयr_pending(&inet_csk(sk)->icsk_retransmit_समयr);
पूर्ण

अटल व्योम mptcp_reset_समयr(काष्ठा sock *sk)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	अचिन्हित दीर्घ tout;

	/* prevent rescheduling on बंद */
	अगर (unlikely(inet_sk_state_load(sk) == TCP_CLOSE))
		वापस;

	/* should never be called with mptcp level समयr cleared */
	tout = READ_ONCE(mptcp_sk(sk)->समयr_ival);
	अगर (WARN_ON_ONCE(!tout))
		tout = TCP_RTO_MIN;
	sk_reset_समयr(sk, &icsk->icsk_retransmit_समयr, jअगरfies + tout);
पूर्ण

bool mptcp_schedule_work(काष्ठा sock *sk)
अणु
	अगर (inet_sk_state_load(sk) != TCP_CLOSE &&
	    schedule_work(&mptcp_sk(sk)->work)) अणु
		/* each subflow alपढ़ोy holds a reference to the sk, and the
		 * workqueue is invoked by a subflow, so sk can't go away here.
		 */
		sock_hold(sk);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

व्योम mptcp_subflow_eof(काष्ठा sock *sk)
अणु
	अगर (!test_and_set_bit(MPTCP_WORK_खातापूर्ण, &mptcp_sk(sk)->flags))
		mptcp_schedule_work(sk);
पूर्ण

अटल व्योम mptcp_check_क्रम_eof(काष्ठा mptcp_sock *msk)
अणु
	काष्ठा mptcp_subflow_context *subflow;
	काष्ठा sock *sk = (काष्ठा sock *)msk;
	पूर्णांक receivers = 0;

	mptcp_क्रम_each_subflow(msk, subflow)
		receivers += !subflow->rx_eof;
	अगर (receivers)
		वापस;

	अगर (!(sk->sk_shutकरोwn & RCV_SHUTDOWN)) अणु
		/* hopefully temporary hack: propagate shutकरोwn status
		 * to msk, when all subflows agree on it
		 */
		sk->sk_shutकरोwn |= RCV_SHUTDOWN;

		smp_mb__beक्रमe_atomic(); /* SHUTDOWN must be visible first */
		set_bit(MPTCP_DATA_READY, &msk->flags);
		sk->sk_data_पढ़ोy(sk);
	पूर्ण

	चयन (sk->sk_state) अणु
	हाल TCP_ESTABLISHED:
		inet_sk_state_store(sk, TCP_CLOSE_WAIT);
		अवरोध;
	हाल TCP_FIN_WAIT1:
		inet_sk_state_store(sk, TCP_CLOSING);
		अवरोध;
	हाल TCP_FIN_WAIT2:
		inet_sk_state_store(sk, TCP_CLOSE);
		अवरोध;
	शेष:
		वापस;
	पूर्ण
	mptcp_बंद_wake_up(sk);
पूर्ण

अटल काष्ठा sock *mptcp_subflow_recv_lookup(स्थिर काष्ठा mptcp_sock *msk)
अणु
	काष्ठा mptcp_subflow_context *subflow;
	काष्ठा sock *sk = (काष्ठा sock *)msk;

	sock_owned_by_me(sk);

	mptcp_क्रम_each_subflow(msk, subflow) अणु
		अगर (READ_ONCE(subflow->data_avail))
			वापस mptcp_subflow_tcp_sock(subflow);
	पूर्ण

	वापस शून्य;
पूर्ण

अटल bool mptcp_skb_can_collapse_to(u64 ग_लिखो_seq,
				      स्थिर काष्ठा sk_buff *skb,
				      स्थिर काष्ठा mptcp_ext *mpext)
अणु
	अगर (!tcp_skb_can_collapse_to(skb))
		वापस false;

	/* can collapse only अगर MPTCP level sequence is in order and this
	 * mapping has not been xmitted yet
	 */
	वापस mpext && mpext->data_seq + mpext->data_len == ग_लिखो_seq &&
	       !mpext->frozen;
पूर्ण

/* we can append data to the given data frag अगर:
 * - there is space available in the backing page_frag
 * - the data frag tail matches the current page_frag मुक्त offset
 * - the data frag end sequence number matches the current ग_लिखो seq
 */
अटल bool mptcp_frag_can_collapse_to(स्थिर काष्ठा mptcp_sock *msk,
				       स्थिर काष्ठा page_frag *pfrag,
				       स्थिर काष्ठा mptcp_data_frag *df)
अणु
	वापस df && pfrag->page == df->page &&
		pfrag->size - pfrag->offset > 0 &&
		pfrag->offset == (df->offset + df->data_len) &&
		df->data_seq + df->data_len == msk->ग_लिखो_seq;
पूर्ण

अटल पूर्णांक mptcp_wmem_with_overhead(काष्ठा sock *sk, पूर्णांक size)
अणु
	काष्ठा mptcp_sock *msk = mptcp_sk(sk);
	पूर्णांक ret, skbs;

	ret = size + ((माप(काष्ठा mptcp_data_frag) * size) >> PAGE_SHIFT);
	skbs = (msk->tx_pending_data + size) / msk->size_goal_cache;
	अगर (skbs < msk->skb_tx_cache.qlen)
		वापस ret;

	वापस ret + (skbs - msk->skb_tx_cache.qlen) * SKB_TRUESIZE(MAX_TCP_HEADER);
पूर्ण

अटल व्योम __mptcp_wmem_reserve(काष्ठा sock *sk, पूर्णांक size)
अणु
	पूर्णांक amount = mptcp_wmem_with_overhead(sk, size);
	काष्ठा mptcp_sock *msk = mptcp_sk(sk);

	WARN_ON_ONCE(msk->wmem_reserved);
	अगर (WARN_ON_ONCE(amount < 0))
		amount = 0;

	अगर (amount <= sk->sk_क्रमward_alloc)
		जाओ reserve;

	/* under memory pressure try to reserve at most a single page
	 * otherwise try to reserve the full estimate and fallback
	 * to a single page beक्रमe entering the error path
	 */
	अगर ((tcp_under_memory_pressure(sk) && amount > PAGE_SIZE) ||
	    !sk_wmem_schedule(sk, amount)) अणु
		अगर (amount <= PAGE_SIZE)
			जाओ nomem;

		amount = PAGE_SIZE;
		अगर (!sk_wmem_schedule(sk, amount))
			जाओ nomem;
	पूर्ण

reserve:
	msk->wmem_reserved = amount;
	sk->sk_क्रमward_alloc -= amount;
	वापस;

nomem:
	/* we will रुको क्रम memory on next allocation */
	msk->wmem_reserved = -1;
पूर्ण

अटल व्योम __mptcp_update_wmem(काष्ठा sock *sk)
अणु
	काष्ठा mptcp_sock *msk = mptcp_sk(sk);

#अगर_घोषित CONFIG_LOCKDEP
	WARN_ON_ONCE(!lockdep_is_held(&sk->sk_lock.slock));
#पूर्ण_अगर

	अगर (!msk->wmem_reserved)
		वापस;

	अगर (msk->wmem_reserved < 0)
		msk->wmem_reserved = 0;
	अगर (msk->wmem_reserved > 0) अणु
		sk->sk_क्रमward_alloc += msk->wmem_reserved;
		msk->wmem_reserved = 0;
	पूर्ण
पूर्ण

अटल bool mptcp_wmem_alloc(काष्ठा sock *sk, पूर्णांक size)
अणु
	काष्ठा mptcp_sock *msk = mptcp_sk(sk);

	/* check क्रम pre-existing error condition */
	अगर (msk->wmem_reserved < 0)
		वापस false;

	अगर (msk->wmem_reserved >= size)
		जाओ account;

	mptcp_data_lock(sk);
	अगर (!sk_wmem_schedule(sk, size)) अणु
		mptcp_data_unlock(sk);
		वापस false;
	पूर्ण

	sk->sk_क्रमward_alloc -= size;
	msk->wmem_reserved += size;
	mptcp_data_unlock(sk);

account:
	msk->wmem_reserved -= size;
	वापस true;
पूर्ण

अटल व्योम mptcp_wmem_unअक्षरge(काष्ठा sock *sk, पूर्णांक size)
अणु
	काष्ठा mptcp_sock *msk = mptcp_sk(sk);

	अगर (msk->wmem_reserved < 0)
		msk->wmem_reserved = 0;
	msk->wmem_reserved += size;
पूर्ण

अटल व्योम mptcp_mem_reclaim_partial(काष्ठा sock *sk)
अणु
	काष्ठा mptcp_sock *msk = mptcp_sk(sk);

	/* अगर we are experiencing a transपूर्णांक allocation error,
	 * the क्रमward allocation memory has been alपढ़ोy
	 * released
	 */
	अगर (msk->wmem_reserved < 0)
		वापस;

	mptcp_data_lock(sk);
	sk->sk_क्रमward_alloc += msk->wmem_reserved;
	sk_mem_reclaim_partial(sk);
	msk->wmem_reserved = sk->sk_क्रमward_alloc;
	sk->sk_क्रमward_alloc = 0;
	mptcp_data_unlock(sk);
पूर्ण

अटल व्योम dfrag_unअक्षरge(काष्ठा sock *sk, पूर्णांक len)
अणु
	sk_mem_unअक्षरge(sk, len);
	sk_wmem_queued_add(sk, -len);
पूर्ण

अटल व्योम dfrag_clear(काष्ठा sock *sk, काष्ठा mptcp_data_frag *dfrag)
अणु
	पूर्णांक len = dfrag->data_len + dfrag->overhead;

	list_del(&dfrag->list);
	dfrag_unअक्षरge(sk, len);
	put_page(dfrag->page);
पूर्ण

अटल व्योम __mptcp_clean_una(काष्ठा sock *sk)
अणु
	काष्ठा mptcp_sock *msk = mptcp_sk(sk);
	काष्ठा mptcp_data_frag *dपंचांगp, *dfrag;
	bool cleaned = false;
	u64 snd_una;

	/* on fallback we just need to ignore snd_una, as this is really
	 * plain TCP
	 */
	अगर (__mptcp_check_fallback(msk))
		msk->snd_una = READ_ONCE(msk->snd_nxt);

	snd_una = msk->snd_una;
	list_क्रम_each_entry_safe(dfrag, dपंचांगp, &msk->rtx_queue, list) अणु
		अगर (after64(dfrag->data_seq + dfrag->data_len, snd_una))
			अवरोध;

		अगर (WARN_ON_ONCE(dfrag == msk->first_pending))
			अवरोध;
		dfrag_clear(sk, dfrag);
		cleaned = true;
	पूर्ण

	dfrag = mptcp_rtx_head(sk);
	अगर (dfrag && after64(snd_una, dfrag->data_seq)) अणु
		u64 delta = snd_una - dfrag->data_seq;

		अगर (WARN_ON_ONCE(delta > dfrag->alपढ़ोy_sent))
			जाओ out;

		dfrag->data_seq += delta;
		dfrag->offset += delta;
		dfrag->data_len -= delta;
		dfrag->alपढ़ोy_sent -= delta;

		dfrag_unअक्षरge(sk, delta);
		cleaned = true;
	पूर्ण

out:
	अगर (cleaned) अणु
		अगर (tcp_under_memory_pressure(sk)) अणु
			__mptcp_update_wmem(sk);
			sk_mem_reclaim_partial(sk);
		पूर्ण
	पूर्ण

	अगर (snd_una == READ_ONCE(msk->snd_nxt)) अणु
		अगर (msk->समयr_ival && !mptcp_data_fin_enabled(msk))
			mptcp_stop_समयr(sk);
	पूर्ण अन्यथा अणु
		mptcp_reset_समयr(sk);
	पूर्ण
पूर्ण

अटल व्योम __mptcp_clean_una_wakeup(काष्ठा sock *sk)
अणु
#अगर_घोषित CONFIG_LOCKDEP
	WARN_ON_ONCE(!lockdep_is_held(&sk->sk_lock.slock));
#पूर्ण_अगर
	__mptcp_clean_una(sk);
	mptcp_ग_लिखो_space(sk);
पूर्ण

अटल व्योम mptcp_clean_una_wakeup(काष्ठा sock *sk)
अणु
	mptcp_data_lock(sk);
	__mptcp_clean_una_wakeup(sk);
	mptcp_data_unlock(sk);
पूर्ण

अटल व्योम mptcp_enter_memory_pressure(काष्ठा sock *sk)
अणु
	काष्ठा mptcp_subflow_context *subflow;
	काष्ठा mptcp_sock *msk = mptcp_sk(sk);
	bool first = true;

	sk_stream_moderate_sndbuf(sk);
	mptcp_क्रम_each_subflow(msk, subflow) अणु
		काष्ठा sock *ssk = mptcp_subflow_tcp_sock(subflow);

		अगर (first)
			tcp_enter_memory_pressure(ssk);
		sk_stream_moderate_sndbuf(ssk);
		first = false;
	पूर्ण
पूर्ण

/* ensure we get enough memory क्रम the frag hdr, beyond some minimal amount of
 * data
 */
अटल bool mptcp_page_frag_refill(काष्ठा sock *sk, काष्ठा page_frag *pfrag)
अणु
	अगर (likely(skb_page_frag_refill(32U + माप(काष्ठा mptcp_data_frag),
					pfrag, sk->sk_allocation)))
		वापस true;

	mptcp_enter_memory_pressure(sk);
	वापस false;
पूर्ण

अटल काष्ठा mptcp_data_frag *
mptcp_carve_data_frag(स्थिर काष्ठा mptcp_sock *msk, काष्ठा page_frag *pfrag,
		      पूर्णांक orig_offset)
अणु
	पूर्णांक offset = ALIGN(orig_offset, माप(दीर्घ));
	काष्ठा mptcp_data_frag *dfrag;

	dfrag = (काष्ठा mptcp_data_frag *)(page_to_virt(pfrag->page) + offset);
	dfrag->data_len = 0;
	dfrag->data_seq = msk->ग_लिखो_seq;
	dfrag->overhead = offset - orig_offset + माप(काष्ठा mptcp_data_frag);
	dfrag->offset = offset + माप(काष्ठा mptcp_data_frag);
	dfrag->alपढ़ोy_sent = 0;
	dfrag->page = pfrag->page;

	वापस dfrag;
पूर्ण

काष्ठा mptcp_sendmsg_info अणु
	पूर्णांक mss_now;
	पूर्णांक size_goal;
	u16 limit;
	u16 sent;
	अचिन्हित पूर्णांक flags;
पूर्ण;

अटल पूर्णांक mptcp_check_allowed_size(काष्ठा mptcp_sock *msk, u64 data_seq,
				    पूर्णांक avail_size)
अणु
	u64 winकरोw_end = mptcp_wnd_end(msk);

	अगर (__mptcp_check_fallback(msk))
		वापस avail_size;

	अगर (!beक्रमe64(data_seq + avail_size, winकरोw_end)) अणु
		u64 allowed_size = winकरोw_end - data_seq;

		वापस min_t(अचिन्हित पूर्णांक, allowed_size, avail_size);
	पूर्ण

	वापस avail_size;
पूर्ण

अटल bool __mptcp_add_ext(काष्ठा sk_buff *skb, gfp_t gfp)
अणु
	काष्ठा skb_ext *mpext = __skb_ext_alloc(gfp);

	अगर (!mpext)
		वापस false;
	__skb_ext_set(skb, SKB_EXT_MPTCP, mpext);
	वापस true;
पूर्ण

अटल काष्ठा sk_buff *__mptcp_करो_alloc_tx_skb(काष्ठा sock *sk, gfp_t gfp)
अणु
	काष्ठा sk_buff *skb;

	skb = alloc_skb_fclone(MAX_TCP_HEADER, gfp);
	अगर (likely(skb)) अणु
		अगर (likely(__mptcp_add_ext(skb, gfp))) अणु
			skb_reserve(skb, MAX_TCP_HEADER);
			skb->reserved_tailroom = skb->end - skb->tail;
			वापस skb;
		पूर्ण
		__kमुक्त_skb(skb);
	पूर्ण अन्यथा अणु
		mptcp_enter_memory_pressure(sk);
	पूर्ण
	वापस शून्य;
पूर्ण

अटल bool mptcp_tx_cache_refill(काष्ठा sock *sk, पूर्णांक size,
				  काष्ठा sk_buff_head *skbs, पूर्णांक *total_ts)
अणु
	काष्ठा mptcp_sock *msk = mptcp_sk(sk);
	काष्ठा sk_buff *skb;
	पूर्णांक space_needed;

	अगर (unlikely(tcp_under_memory_pressure(sk))) अणु
		mptcp_mem_reclaim_partial(sk);

		/* under pressure pre-allocate at most a single skb */
		अगर (msk->skb_tx_cache.qlen)
			वापस true;
		space_needed = msk->size_goal_cache;
	पूर्ण अन्यथा अणु
		space_needed = msk->tx_pending_data + size -
			       msk->skb_tx_cache.qlen * msk->size_goal_cache;
	पूर्ण

	जबतक (space_needed > 0) अणु
		skb = __mptcp_करो_alloc_tx_skb(sk, sk->sk_allocation);
		अगर (unlikely(!skb)) अणु
			/* under memory pressure, try to pass the caller a
			 * single skb to allow क्रमward progress
			 */
			जबतक (skbs->qlen > 1) अणु
				skb = __skb_dequeue_tail(skbs);
				*total_ts -= skb->truesize;
				__kमुक्त_skb(skb);
			पूर्ण
			वापस skbs->qlen > 0;
		पूर्ण

		*total_ts += skb->truesize;
		__skb_queue_tail(skbs, skb);
		space_needed -= msk->size_goal_cache;
	पूर्ण
	वापस true;
पूर्ण

अटल bool __mptcp_alloc_tx_skb(काष्ठा sock *sk, काष्ठा sock *ssk, gfp_t gfp)
अणु
	काष्ठा mptcp_sock *msk = mptcp_sk(sk);
	काष्ठा sk_buff *skb;

	अगर (ssk->sk_tx_skb_cache) अणु
		skb = ssk->sk_tx_skb_cache;
		अगर (unlikely(!skb_ext_find(skb, SKB_EXT_MPTCP) &&
			     !__mptcp_add_ext(skb, gfp)))
			वापस false;
		वापस true;
	पूर्ण

	skb = skb_peek(&msk->skb_tx_cache);
	अगर (skb) अणु
		अगर (likely(sk_wmem_schedule(ssk, skb->truesize))) अणु
			skb = __skb_dequeue(&msk->skb_tx_cache);
			अगर (WARN_ON_ONCE(!skb))
				वापस false;

			mptcp_wmem_unअक्षरge(sk, skb->truesize);
			ssk->sk_tx_skb_cache = skb;
			वापस true;
		पूर्ण

		/* over memory limit, no poपूर्णांक to try to allocate a new skb */
		वापस false;
	पूर्ण

	skb = __mptcp_करो_alloc_tx_skb(sk, gfp);
	अगर (!skb)
		वापस false;

	अगर (likely(sk_wmem_schedule(ssk, skb->truesize))) अणु
		ssk->sk_tx_skb_cache = skb;
		वापस true;
	पूर्ण
	kमुक्त_skb(skb);
	वापस false;
पूर्ण

अटल bool mptcp_must_reclaim_memory(काष्ठा sock *sk, काष्ठा sock *ssk)
अणु
	वापस !ssk->sk_tx_skb_cache &&
	       !skb_peek(&mptcp_sk(sk)->skb_tx_cache) &&
	       tcp_under_memory_pressure(sk);
पूर्ण

अटल bool mptcp_alloc_tx_skb(काष्ठा sock *sk, काष्ठा sock *ssk)
अणु
	अगर (unlikely(mptcp_must_reclaim_memory(sk, ssk)))
		mptcp_mem_reclaim_partial(sk);
	वापस __mptcp_alloc_tx_skb(sk, ssk, sk->sk_allocation);
पूर्ण

अटल पूर्णांक mptcp_sendmsg_frag(काष्ठा sock *sk, काष्ठा sock *ssk,
			      काष्ठा mptcp_data_frag *dfrag,
			      काष्ठा mptcp_sendmsg_info *info)
अणु
	u64 data_seq = dfrag->data_seq + info->sent;
	काष्ठा mptcp_sock *msk = mptcp_sk(sk);
	bool zero_winकरोw_probe = false;
	काष्ठा mptcp_ext *mpext = शून्य;
	काष्ठा sk_buff *skb, *tail;
	bool can_collapse = false;
	पूर्णांक size_bias = 0;
	पूर्णांक avail_size;
	माप_प्रकार ret = 0;

	pr_debug("msk=%p ssk=%p sending dfrag at seq=%llu len=%u already sent=%u",
		 msk, ssk, dfrag->data_seq, dfrag->data_len, info->sent);

	/* compute send limit */
	info->mss_now = tcp_send_mss(ssk, &info->size_goal, info->flags);
	avail_size = info->size_goal;
	msk->size_goal_cache = info->size_goal;
	skb = tcp_ग_लिखो_queue_tail(ssk);
	अगर (skb) अणु
		/* Limit the ग_लिखो to the size available in the
		 * current skb, अगर any, so that we create at most a new skb.
		 * Explicitly tells TCP पूर्णांकernals to aव्योम collapsing on later
		 * queue management operation, to aव्योम अवरोधing the ext <->
		 * SSN association set here
		 */
		mpext = skb_ext_find(skb, SKB_EXT_MPTCP);
		can_collapse = (info->size_goal - skb->len > 0) &&
			 mptcp_skb_can_collapse_to(data_seq, skb, mpext);
		अगर (!can_collapse) अणु
			TCP_SKB_CB(skb)->eor = 1;
		पूर्ण अन्यथा अणु
			size_bias = skb->len;
			avail_size = info->size_goal - skb->len;
		पूर्ण
	पूर्ण

	/* Zero winकरोw and all data acked? Probe. */
	avail_size = mptcp_check_allowed_size(msk, data_seq, avail_size);
	अगर (avail_size == 0) अणु
		u64 snd_una = READ_ONCE(msk->snd_una);

		अगर (skb || snd_una != msk->snd_nxt)
			वापस 0;
		zero_winकरोw_probe = true;
		data_seq = snd_una - 1;
		avail_size = 1;
	पूर्ण

	अगर (WARN_ON_ONCE(info->sent > info->limit ||
			 info->limit > dfrag->data_len))
		वापस 0;

	ret = info->limit - info->sent;
	tail = tcp_build_frag(ssk, avail_size + size_bias, info->flags,
			      dfrag->page, dfrag->offset + info->sent, &ret);
	अगर (!tail) अणु
		tcp_हटाओ_empty_skb(sk, tcp_ग_लिखो_queue_tail(ssk));
		वापस -ENOMEM;
	पूर्ण

	/* अगर the tail skb is still the cached one, collapsing really happened.
	 */
	अगर (skb == tail) अणु
		TCP_SKB_CB(tail)->tcp_flags &= ~TCPHDR_PSH;
		mpext->data_len += ret;
		WARN_ON_ONCE(!can_collapse);
		WARN_ON_ONCE(zero_winकरोw_probe);
		जाओ out;
	पूर्ण

	mpext = skb_ext_find(tail, SKB_EXT_MPTCP);
	अगर (WARN_ON_ONCE(!mpext)) अणु
		/* should never reach here, stream corrupted */
		वापस -EINVAL;
	पूर्ण

	स_रखो(mpext, 0, माप(*mpext));
	mpext->data_seq = data_seq;
	mpext->subflow_seq = mptcp_subflow_ctx(ssk)->rel_ग_लिखो_seq;
	mpext->data_len = ret;
	mpext->use_map = 1;
	mpext->dsn64 = 1;

	pr_debug("data_seq=%llu subflow_seq=%u data_len=%u dsn64=%d",
		 mpext->data_seq, mpext->subflow_seq, mpext->data_len,
		 mpext->dsn64);

	अगर (zero_winकरोw_probe) अणु
		mptcp_subflow_ctx(ssk)->rel_ग_लिखो_seq += ret;
		mpext->frozen = 1;
		ret = 0;
		tcp_push_pending_frames(ssk);
	पूर्ण
out:
	mptcp_subflow_ctx(ssk)->rel_ग_लिखो_seq += ret;
	वापस ret;
पूर्ण

#घोषणा MPTCP_SEND_BURST_SIZE		((1 << 16) - \
					 माप(काष्ठा tcphdr) - \
					 MAX_TCP_OPTION_SPACE - \
					 माप(काष्ठा ipv6hdr) - \
					 माप(काष्ठा frag_hdr))

काष्ठा subflow_send_info अणु
	काष्ठा sock *ssk;
	u64 ratio;
पूर्ण;

अटल काष्ठा sock *mptcp_subflow_get_send(काष्ठा mptcp_sock *msk)
अणु
	काष्ठा subflow_send_info send_info[2];
	काष्ठा mptcp_subflow_context *subflow;
	पूर्णांक i, nr_active = 0;
	काष्ठा sock *ssk;
	u64 ratio;
	u32 pace;

	sock_owned_by_me((काष्ठा sock *)msk);

	अगर (__mptcp_check_fallback(msk)) अणु
		अगर (!msk->first)
			वापस शून्य;
		वापस sk_stream_memory_मुक्त(msk->first) ? msk->first : शून्य;
	पूर्ण

	/* re-use last subflow, अगर the burst allow that */
	अगर (msk->last_snd && msk->snd_burst > 0 &&
	    sk_stream_memory_मुक्त(msk->last_snd) &&
	    mptcp_subflow_active(mptcp_subflow_ctx(msk->last_snd)))
		वापस msk->last_snd;

	/* pick the subflow with the lower wmem/wspace ratio */
	क्रम (i = 0; i < 2; ++i) अणु
		send_info[i].ssk = शून्य;
		send_info[i].ratio = -1;
	पूर्ण
	mptcp_क्रम_each_subflow(msk, subflow) अणु
		trace_mptcp_subflow_get_send(subflow);
		ssk =  mptcp_subflow_tcp_sock(subflow);
		अगर (!mptcp_subflow_active(subflow))
			जारी;

		nr_active += !subflow->backup;
		अगर (!sk_stream_memory_मुक्त(subflow->tcp_sock) || !tcp_sk(ssk)->snd_wnd)
			जारी;

		pace = READ_ONCE(ssk->sk_pacing_rate);
		अगर (!pace)
			जारी;

		ratio = भाग_u64((u64)READ_ONCE(ssk->sk_wmem_queued) << 32,
				pace);
		अगर (ratio < send_info[subflow->backup].ratio) अणु
			send_info[subflow->backup].ssk = ssk;
			send_info[subflow->backup].ratio = ratio;
		पूर्ण
	पूर्ण

	/* pick the best backup अगर no other subflow is active */
	अगर (!nr_active)
		send_info[0].ssk = send_info[1].ssk;

	अगर (send_info[0].ssk) अणु
		msk->last_snd = send_info[0].ssk;
		msk->snd_burst = min_t(पूर्णांक, MPTCP_SEND_BURST_SIZE,
				       tcp_sk(msk->last_snd)->snd_wnd);
		वापस msk->last_snd;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम mptcp_push_release(काष्ठा sock *sk, काष्ठा sock *ssk,
			       काष्ठा mptcp_sendmsg_info *info)
अणु
	mptcp_set_समयout(sk, ssk);
	tcp_push(ssk, 0, info->mss_now, tcp_sk(ssk)->nonagle, info->size_goal);
	release_sock(ssk);
पूर्ण

अटल व्योम __mptcp_push_pending(काष्ठा sock *sk, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा sock *prev_ssk = शून्य, *ssk = शून्य;
	काष्ठा mptcp_sock *msk = mptcp_sk(sk);
	काष्ठा mptcp_sendmsg_info info = अणु
				.flags = flags,
	पूर्ण;
	काष्ठा mptcp_data_frag *dfrag;
	पूर्णांक len, copied = 0;

	जबतक ((dfrag = mptcp_send_head(sk))) अणु
		info.sent = dfrag->alपढ़ोy_sent;
		info.limit = dfrag->data_len;
		len = dfrag->data_len - dfrag->alपढ़ोy_sent;
		जबतक (len > 0) अणु
			पूर्णांक ret = 0;

			prev_ssk = ssk;
			mptcp_flush_join_list(msk);
			ssk = mptcp_subflow_get_send(msk);

			/* try to keep the subflow socket lock across
			 * consecutive xmit on the same socket
			 */
			अगर (ssk != prev_ssk && prev_ssk)
				mptcp_push_release(sk, prev_ssk, &info);
			अगर (!ssk)
				जाओ out;

			अगर (ssk != prev_ssk || !prev_ssk)
				lock_sock(ssk);

			/* keep it simple and always provide a new skb क्रम the
			 * subflow, even अगर we will not use it when collapsing
			 * on the pending one
			 */
			अगर (!mptcp_alloc_tx_skb(sk, ssk)) अणु
				mptcp_push_release(sk, ssk, &info);
				जाओ out;
			पूर्ण

			ret = mptcp_sendmsg_frag(sk, ssk, dfrag, &info);
			अगर (ret <= 0) अणु
				mptcp_push_release(sk, ssk, &info);
				जाओ out;
			पूर्ण

			info.sent += ret;
			dfrag->alपढ़ोy_sent += ret;
			msk->snd_nxt += ret;
			msk->snd_burst -= ret;
			msk->tx_pending_data -= ret;
			copied += ret;
			len -= ret;
		पूर्ण
		WRITE_ONCE(msk->first_pending, mptcp_send_next(sk));
	पूर्ण

	/* at this poपूर्णांक we held the socket lock क्रम the last subflow we used */
	अगर (ssk)
		mptcp_push_release(sk, ssk, &info);

out:
	अगर (copied) अणु
		/* start the समयr, अगर it's not pending */
		अगर (!mptcp_समयr_pending(sk))
			mptcp_reset_समयr(sk);
		__mptcp_check_send_data_fin(sk);
	पूर्ण
पूर्ण

अटल व्योम __mptcp_subflow_push_pending(काष्ठा sock *sk, काष्ठा sock *ssk)
अणु
	काष्ठा mptcp_sock *msk = mptcp_sk(sk);
	काष्ठा mptcp_sendmsg_info info;
	काष्ठा mptcp_data_frag *dfrag;
	काष्ठा sock *xmit_ssk;
	पूर्णांक len, copied = 0;
	bool first = true;

	info.flags = 0;
	जबतक ((dfrag = mptcp_send_head(sk))) अणु
		info.sent = dfrag->alपढ़ोy_sent;
		info.limit = dfrag->data_len;
		len = dfrag->data_len - dfrag->alपढ़ोy_sent;
		जबतक (len > 0) अणु
			पूर्णांक ret = 0;

			/* the caller alपढ़ोy invoked the packet scheduler,
			 * check क्रम a dअगरferent subflow usage only after
			 * spooling the first chunk of data
			 */
			xmit_ssk = first ? ssk : mptcp_subflow_get_send(mptcp_sk(sk));
			अगर (!xmit_ssk)
				जाओ out;
			अगर (xmit_ssk != ssk) अणु
				mptcp_subflow_delegate(mptcp_subflow_ctx(xmit_ssk));
				जाओ out;
			पूर्ण

			अगर (unlikely(mptcp_must_reclaim_memory(sk, ssk))) अणु
				__mptcp_update_wmem(sk);
				sk_mem_reclaim_partial(sk);
			पूर्ण
			अगर (!__mptcp_alloc_tx_skb(sk, ssk, GFP_ATOMIC))
				जाओ out;

			ret = mptcp_sendmsg_frag(sk, ssk, dfrag, &info);
			अगर (ret <= 0)
				जाओ out;

			info.sent += ret;
			dfrag->alपढ़ोy_sent += ret;
			msk->snd_nxt += ret;
			msk->snd_burst -= ret;
			msk->tx_pending_data -= ret;
			copied += ret;
			len -= ret;
			first = false;
		पूर्ण
		WRITE_ONCE(msk->first_pending, mptcp_send_next(sk));
	पूर्ण

out:
	/* __mptcp_alloc_tx_skb could have released some wmem and we are
	 * not going to flush it via release_sock()
	 */
	__mptcp_update_wmem(sk);
	अगर (copied) अणु
		mptcp_set_समयout(sk, ssk);
		tcp_push(ssk, 0, info.mss_now, tcp_sk(ssk)->nonagle,
			 info.size_goal);
		अगर (!mptcp_समयr_pending(sk))
			mptcp_reset_समयr(sk);

		अगर (msk->snd_data_fin_enable &&
		    msk->snd_nxt + 1 == msk->ग_लिखो_seq)
			mptcp_schedule_work(sk);
	पूर्ण
पूर्ण

अटल व्योम mptcp_set_nospace(काष्ठा sock *sk)
अणु
	/* enable स्वतःtune */
	set_bit(SOCK_NOSPACE, &sk->sk_socket->flags);

	/* will be cleared on avail space */
	set_bit(MPTCP_NOSPACE, &mptcp_sk(sk)->flags);
पूर्ण

अटल पूर्णांक mptcp_sendmsg(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार len)
अणु
	काष्ठा mptcp_sock *msk = mptcp_sk(sk);
	काष्ठा page_frag *pfrag;
	माप_प्रकार copied = 0;
	पूर्णांक ret = 0;
	दीर्घ समयo;

	/* we करोn't support FASTOPEN yet */
	अगर (msg->msg_flags & MSG_FASTOPEN)
		वापस -EOPNOTSUPP;

	/* silently ignore everything अन्यथा */
	msg->msg_flags &= MSG_MORE | MSG_DONTWAIT | MSG_NOSIGNAL;

	mptcp_lock_sock(sk, __mptcp_wmem_reserve(sk, min_t(माप_प्रकार, 1 << 20, len)));

	समयo = sock_sndसमयo(sk, msg->msg_flags & MSG_DONTWAIT);

	अगर ((1 << sk->sk_state) & ~(TCPF_ESTABLISHED | TCPF_CLOSE_WAIT)) अणु
		ret = sk_stream_रुको_connect(sk, &समयo);
		अगर (ret)
			जाओ out;
	पूर्ण

	pfrag = sk_page_frag(sk);

	जबतक (msg_data_left(msg)) अणु
		पूर्णांक total_ts, frag_truesize = 0;
		काष्ठा mptcp_data_frag *dfrag;
		काष्ठा sk_buff_head skbs;
		bool dfrag_collapsed;
		माप_प्रकार psize, offset;

		अगर (sk->sk_err || (sk->sk_shutकरोwn & SEND_SHUTDOWN)) अणु
			ret = -EPIPE;
			जाओ out;
		पूर्ण

		/* reuse tail pfrag, अगर possible, or carve a new one from the
		 * page allocator
		 */
		dfrag = mptcp_pending_tail(sk);
		dfrag_collapsed = mptcp_frag_can_collapse_to(msk, pfrag, dfrag);
		अगर (!dfrag_collapsed) अणु
			अगर (!sk_stream_memory_मुक्त(sk))
				जाओ रुको_क्रम_memory;

			अगर (!mptcp_page_frag_refill(sk, pfrag))
				जाओ रुको_क्रम_memory;

			dfrag = mptcp_carve_data_frag(msk, pfrag, pfrag->offset);
			frag_truesize = dfrag->overhead;
		पूर्ण

		/* we करो not bound vs wspace, to allow a single packet.
		 * memory accounting will prevent execessive memory usage
		 * anyway
		 */
		offset = dfrag->offset + dfrag->data_len;
		psize = pfrag->size - offset;
		psize = min_t(माप_प्रकार, psize, msg_data_left(msg));
		total_ts = psize + frag_truesize;
		__skb_queue_head_init(&skbs);
		अगर (!mptcp_tx_cache_refill(sk, psize, &skbs, &total_ts))
			जाओ रुको_क्रम_memory;

		अगर (!mptcp_wmem_alloc(sk, total_ts)) अणु
			__skb_queue_purge(&skbs);
			जाओ रुको_क्रम_memory;
		पूर्ण

		skb_queue_splice_tail(&skbs, &msk->skb_tx_cache);
		अगर (copy_page_from_iter(dfrag->page, offset, psize,
					&msg->msg_iter) != psize) अणु
			mptcp_wmem_unअक्षरge(sk, psize + frag_truesize);
			ret = -EFAULT;
			जाओ out;
		पूर्ण

		/* data successfully copied पूर्णांकo the ग_लिखो queue */
		copied += psize;
		dfrag->data_len += psize;
		frag_truesize += psize;
		pfrag->offset += frag_truesize;
		WRITE_ONCE(msk->ग_लिखो_seq, msk->ग_लिखो_seq + psize);
		msk->tx_pending_data += psize;

		/* अक्षरge data on mptcp pending queue to the msk socket
		 * Note: we अक्षरge such data both to sk and ssk
		 */
		sk_wmem_queued_add(sk, frag_truesize);
		अगर (!dfrag_collapsed) अणु
			get_page(dfrag->page);
			list_add_tail(&dfrag->list, &msk->rtx_queue);
			अगर (!msk->first_pending)
				WRITE_ONCE(msk->first_pending, dfrag);
		पूर्ण
		pr_debug("msk=%p dfrag at seq=%llu len=%u sent=%u new=%d", msk,
			 dfrag->data_seq, dfrag->data_len, dfrag->alपढ़ोy_sent,
			 !dfrag_collapsed);

		जारी;

रुको_क्रम_memory:
		mptcp_set_nospace(sk);
		__mptcp_push_pending(sk, msg->msg_flags);
		ret = sk_stream_रुको_memory(sk, &समयo);
		अगर (ret)
			जाओ out;
	पूर्ण

	अगर (copied)
		__mptcp_push_pending(sk, msg->msg_flags);

out:
	release_sock(sk);
	वापस copied ? : ret;
पूर्ण

अटल व्योम mptcp_रुको_data(काष्ठा sock *sk, दीर्घ *समयo)
अणु
	DEFINE_WAIT_FUNC(रुको, woken_wake_function);
	काष्ठा mptcp_sock *msk = mptcp_sk(sk);

	add_रुको_queue(sk_sleep(sk), &रुको);
	sk_set_bit(SOCKWQ_ASYNC_WAITDATA, sk);

	sk_रुको_event(sk, समयo,
		      test_and_clear_bit(MPTCP_DATA_READY, &msk->flags), &रुको);

	sk_clear_bit(SOCKWQ_ASYNC_WAITDATA, sk);
	हटाओ_रुको_queue(sk_sleep(sk), &रुको);
पूर्ण

अटल पूर्णांक __mptcp_recvmsg_mskq(काष्ठा mptcp_sock *msk,
				काष्ठा msghdr *msg,
				माप_प्रकार len, पूर्णांक flags)
अणु
	काष्ठा sk_buff *skb, *पंचांगp;
	पूर्णांक copied = 0;

	skb_queue_walk_safe(&msk->receive_queue, skb, पंचांगp) अणु
		u32 offset = MPTCP_SKB_CB(skb)->offset;
		u32 data_len = skb->len - offset;
		u32 count = min_t(माप_प्रकार, len - copied, data_len);
		पूर्णांक err;

		अगर (!(flags & MSG_TRUNC)) अणु
			err = skb_copy_datagram_msg(skb, offset, msg, count);
			अगर (unlikely(err < 0)) अणु
				अगर (!copied)
					वापस err;
				अवरोध;
			पूर्ण
		पूर्ण

		copied += count;

		अगर (count < data_len) अणु
			अगर (!(flags & MSG_PEEK))
				MPTCP_SKB_CB(skb)->offset += count;
			अवरोध;
		पूर्ण

		अगर (!(flags & MSG_PEEK)) अणु
			/* we will bulk release the skb memory later */
			skb->deकाष्ठाor = शून्य;
			msk->rmem_released += skb->truesize;
			__skb_unlink(skb, &msk->receive_queue);
			__kमुक्त_skb(skb);
		पूर्ण

		अगर (copied >= len)
			अवरोध;
	पूर्ण

	वापस copied;
पूर्ण

/* receive buffer स्वतःtuning.  See tcp_rcv_space_adjust क्रम more inक्रमmation.
 *
 * Only dअगरference: Use highest rtt estimate of the subflows in use.
 */
अटल व्योम mptcp_rcv_space_adjust(काष्ठा mptcp_sock *msk, पूर्णांक copied)
अणु
	काष्ठा mptcp_subflow_context *subflow;
	काष्ठा sock *sk = (काष्ठा sock *)msk;
	u32 समय, advmss = 1;
	u64 rtt_us, mstamp;

	sock_owned_by_me(sk);

	अगर (copied <= 0)
		वापस;

	msk->rcvq_space.copied += copied;

	mstamp = भाग_u64(tcp_घड़ी_ns(), NSEC_PER_USEC);
	समय = tcp_stamp_us_delta(mstamp, msk->rcvq_space.समय);

	rtt_us = msk->rcvq_space.rtt_us;
	अगर (rtt_us && समय < (rtt_us >> 3))
		वापस;

	rtt_us = 0;
	mptcp_क्रम_each_subflow(msk, subflow) अणु
		स्थिर काष्ठा tcp_sock *tp;
		u64 sf_rtt_us;
		u32 sf_advmss;

		tp = tcp_sk(mptcp_subflow_tcp_sock(subflow));

		sf_rtt_us = READ_ONCE(tp->rcv_rtt_est.rtt_us);
		sf_advmss = READ_ONCE(tp->advmss);

		rtt_us = max(sf_rtt_us, rtt_us);
		advmss = max(sf_advmss, advmss);
	पूर्ण

	msk->rcvq_space.rtt_us = rtt_us;
	अगर (समय < (rtt_us >> 3) || rtt_us == 0)
		वापस;

	अगर (msk->rcvq_space.copied <= msk->rcvq_space.space)
		जाओ new_measure;

	अगर (sock_net(sk)->ipv4.sysctl_tcp_moderate_rcvbuf &&
	    !(sk->sk_userlocks & SOCK_RCVBUF_LOCK)) अणु
		पूर्णांक rcvmem, rcvbuf;
		u64 rcvwin, grow;

		rcvwin = ((u64)msk->rcvq_space.copied << 1) + 16 * advmss;

		grow = rcvwin * (msk->rcvq_space.copied - msk->rcvq_space.space);

		करो_भाग(grow, msk->rcvq_space.space);
		rcvwin += (grow << 1);

		rcvmem = SKB_TRUESIZE(advmss + MAX_TCP_HEADER);
		जबतक (tcp_win_from_space(sk, rcvmem) < advmss)
			rcvmem += 128;

		करो_भाग(rcvwin, advmss);
		rcvbuf = min_t(u64, rcvwin * rcvmem,
			       sock_net(sk)->ipv4.sysctl_tcp_rmem[2]);

		अगर (rcvbuf > sk->sk_rcvbuf) अणु
			u32 winकरोw_clamp;

			winकरोw_clamp = tcp_win_from_space(sk, rcvbuf);
			WRITE_ONCE(sk->sk_rcvbuf, rcvbuf);

			/* Make subflows follow aदीर्घ.  If we करो not करो this, we
			 * get drops at subflow level अगर skbs can't be moved to
			 * the mptcp rx queue fast enough (announced rcv_win can
			 * exceed ssk->sk_rcvbuf).
			 */
			mptcp_क्रम_each_subflow(msk, subflow) अणु
				काष्ठा sock *ssk;
				bool slow;

				ssk = mptcp_subflow_tcp_sock(subflow);
				slow = lock_sock_fast(ssk);
				WRITE_ONCE(ssk->sk_rcvbuf, rcvbuf);
				tcp_sk(ssk)->winकरोw_clamp = winकरोw_clamp;
				tcp_cleanup_rbuf(ssk, 1);
				unlock_sock_fast(ssk, slow);
			पूर्ण
		पूर्ण
	पूर्ण

	msk->rcvq_space.space = msk->rcvq_space.copied;
new_measure:
	msk->rcvq_space.copied = 0;
	msk->rcvq_space.समय = mstamp;
पूर्ण

अटल व्योम __mptcp_update_rmem(काष्ठा sock *sk)
अणु
	काष्ठा mptcp_sock *msk = mptcp_sk(sk);

	अगर (!msk->rmem_released)
		वापस;

	atomic_sub(msk->rmem_released, &sk->sk_rmem_alloc);
	sk_mem_unअक्षरge(sk, msk->rmem_released);
	msk->rmem_released = 0;
पूर्ण

अटल व्योम __mptcp_splice_receive_queue(काष्ठा sock *sk)
अणु
	काष्ठा mptcp_sock *msk = mptcp_sk(sk);

	skb_queue_splice_tail_init(&sk->sk_receive_queue, &msk->receive_queue);
पूर्ण

अटल bool __mptcp_move_skbs(काष्ठा mptcp_sock *msk)
अणु
	काष्ठा sock *sk = (काष्ठा sock *)msk;
	अचिन्हित पूर्णांक moved = 0;
	bool ret, करोne;

	mptcp_flush_join_list(msk);
	करो अणु
		काष्ठा sock *ssk = mptcp_subflow_recv_lookup(msk);
		bool slowpath;

		/* we can have data pending in the subflows only अगर the msk
		 * receive buffer was full at subflow_data_पढ़ोy() समय,
		 * that is an unlikely slow path.
		 */
		अगर (likely(!ssk))
			अवरोध;

		slowpath = lock_sock_fast(ssk);
		mptcp_data_lock(sk);
		__mptcp_update_rmem(sk);
		करोne = __mptcp_move_skbs_from_subflow(msk, ssk, &moved);
		mptcp_data_unlock(sk);
		tcp_cleanup_rbuf(ssk, moved);

		अगर (unlikely(ssk->sk_err))
			__mptcp_error_report(sk);
		unlock_sock_fast(ssk, slowpath);
	पूर्ण जबतक (!करोne);

	/* acquire the data lock only अगर some input data is pending */
	ret = moved > 0;
	अगर (!RB_EMPTY_ROOT(&msk->out_of_order_queue) ||
	    !skb_queue_empty_lockless(&sk->sk_receive_queue)) अणु
		mptcp_data_lock(sk);
		__mptcp_update_rmem(sk);
		ret |= __mptcp_ofo_queue(msk);
		__mptcp_splice_receive_queue(sk);
		mptcp_data_unlock(sk);
		mptcp_cleanup_rbuf(msk);
	पूर्ण
	अगर (ret)
		mptcp_check_data_fin((काष्ठा sock *)msk);
	वापस !skb_queue_empty(&msk->receive_queue);
पूर्ण

अटल पूर्णांक mptcp_recvmsg(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार len,
			 पूर्णांक nonblock, पूर्णांक flags, पूर्णांक *addr_len)
अणु
	काष्ठा mptcp_sock *msk = mptcp_sk(sk);
	पूर्णांक copied = 0;
	पूर्णांक target;
	दीर्घ समयo;

	/* MSG_ERRQUEUE is really a no-op till we support IP_RECVERR */
	अगर (unlikely(flags & MSG_ERRQUEUE))
		वापस inet_recv_error(sk, msg, len, addr_len);

	mptcp_lock_sock(sk, __mptcp_splice_receive_queue(sk));
	अगर (unlikely(sk->sk_state == TCP_LISTEN)) अणु
		copied = -ENOTCONN;
		जाओ out_err;
	पूर्ण

	समयo = sock_rcvसमयo(sk, nonblock);

	len = min_t(माप_प्रकार, len, पूर्णांक_उच्च);
	target = sock_rcvlowat(sk, flags & MSG_WAITALL, len);

	जबतक (copied < len) अणु
		पूर्णांक bytes_पढ़ो;

		bytes_पढ़ो = __mptcp_recvmsg_mskq(msk, msg, len - copied, flags);
		अगर (unlikely(bytes_पढ़ो < 0)) अणु
			अगर (!copied)
				copied = bytes_पढ़ो;
			जाओ out_err;
		पूर्ण

		copied += bytes_पढ़ो;

		/* be sure to advertise winकरोw change */
		mptcp_cleanup_rbuf(msk);

		अगर (skb_queue_empty(&msk->receive_queue) && __mptcp_move_skbs(msk))
			जारी;

		/* only the master socket status is relevant here. The निकास
		 * conditions mirror बंदly tcp_recvmsg()
		 */
		अगर (copied >= target)
			अवरोध;

		अगर (copied) अणु
			अगर (sk->sk_err ||
			    sk->sk_state == TCP_CLOSE ||
			    (sk->sk_shutकरोwn & RCV_SHUTDOWN) ||
			    !समयo ||
			    संकेत_pending(current))
				अवरोध;
		पूर्ण अन्यथा अणु
			अगर (sk->sk_err) अणु
				copied = sock_error(sk);
				अवरोध;
			पूर्ण

			अगर (test_and_clear_bit(MPTCP_WORK_खातापूर्ण, &msk->flags))
				mptcp_check_क्रम_eof(msk);

			अगर (sk->sk_shutकरोwn & RCV_SHUTDOWN) अणु
				/* race अवरोधer: the shutकरोwn could be after the
				 * previous receive queue check
				 */
				अगर (__mptcp_move_skbs(msk))
					जारी;
				अवरोध;
			पूर्ण

			अगर (sk->sk_state == TCP_CLOSE) अणु
				copied = -ENOTCONN;
				अवरोध;
			पूर्ण

			अगर (!समयo) अणु
				copied = -EAGAIN;
				अवरोध;
			पूर्ण

			अगर (संकेत_pending(current)) अणु
				copied = sock_पूर्णांकr_त्रुटि_सं(समयo);
				अवरोध;
			पूर्ण
		पूर्ण

		pr_debug("block timeout %ld", समयo);
		mptcp_रुको_data(sk, &समयo);
	पूर्ण

	अगर (skb_queue_empty_lockless(&sk->sk_receive_queue) &&
	    skb_queue_empty(&msk->receive_queue)) अणु
		/* entire backlog drained, clear DATA_READY. */
		clear_bit(MPTCP_DATA_READY, &msk->flags);

		/* .. race-अवरोधer: ssk might have gotten new data
		 * after last __mptcp_move_skbs() वापसed false.
		 */
		अगर (unlikely(__mptcp_move_skbs(msk)))
			set_bit(MPTCP_DATA_READY, &msk->flags);
	पूर्ण अन्यथा अगर (unlikely(!test_bit(MPTCP_DATA_READY, &msk->flags))) अणु
		/* data to पढ़ो but mptcp_रुको_data() cleared DATA_READY */
		set_bit(MPTCP_DATA_READY, &msk->flags);
	पूर्ण
out_err:
	pr_debug("msk=%p data_ready=%d rx queue empty=%d copied=%d",
		 msk, test_bit(MPTCP_DATA_READY, &msk->flags),
		 skb_queue_empty_lockless(&sk->sk_receive_queue), copied);
	अगर (!(flags & MSG_PEEK))
		mptcp_rcv_space_adjust(msk, copied);

	release_sock(sk);
	वापस copied;
पूर्ण

अटल व्योम mptcp_retransmit_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा inet_connection_sock *icsk = from_समयr(icsk, t,
						       icsk_retransmit_समयr);
	काष्ठा sock *sk = &icsk->icsk_inet.sk;
	काष्ठा mptcp_sock *msk = mptcp_sk(sk);

	bh_lock_sock(sk);
	अगर (!sock_owned_by_user(sk)) अणु
		/* we need a process context to retransmit */
		अगर (!test_and_set_bit(MPTCP_WORK_RTX, &msk->flags))
			mptcp_schedule_work(sk);
	पूर्ण अन्यथा अणु
		/* delegate our work to tcp_release_cb() */
		set_bit(MPTCP_RETRANSMIT, &msk->flags);
	पूर्ण
	bh_unlock_sock(sk);
	sock_put(sk);
पूर्ण

अटल व्योम mptcp_समयout_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा sock *sk = from_समयr(sk, t, sk_समयr);

	mptcp_schedule_work(sk);
	sock_put(sk);
पूर्ण

/* Find an idle subflow.  Return शून्य अगर there is unacked data at tcp
 * level.
 *
 * A backup subflow is वापसed only अगर that is the only kind available.
 */
अटल काष्ठा sock *mptcp_subflow_get_retrans(स्थिर काष्ठा mptcp_sock *msk)
अणु
	काष्ठा mptcp_subflow_context *subflow;
	काष्ठा sock *backup = शून्य;

	sock_owned_by_me((स्थिर काष्ठा sock *)msk);

	अगर (__mptcp_check_fallback(msk))
		वापस शून्य;

	mptcp_क्रम_each_subflow(msk, subflow) अणु
		काष्ठा sock *ssk = mptcp_subflow_tcp_sock(subflow);

		अगर (!mptcp_subflow_active(subflow))
			जारी;

		/* still data outstanding at TCP level?  Don't retransmit. */
		अगर (!tcp_ग_लिखो_queue_empty(ssk)) अणु
			अगर (inet_csk(ssk)->icsk_ca_state >= TCP_CA_Loss)
				जारी;
			वापस शून्य;
		पूर्ण

		अगर (subflow->backup) अणु
			अगर (!backup)
				backup = ssk;
			जारी;
		पूर्ण

		वापस ssk;
	पूर्ण

	वापस backup;
पूर्ण

अटल व्योम mptcp_dispose_initial_subflow(काष्ठा mptcp_sock *msk)
अणु
	अगर (msk->subflow) अणु
		iput(SOCK_INODE(msk->subflow));
		msk->subflow = शून्य;
	पूर्ण
पूर्ण

/* subflow sockets can be either outgoing (connect) or incoming
 * (accept).
 *
 * Outgoing subflows use in-kernel sockets.
 * Incoming subflows करो not have their own 'struct socket' allocated,
 * so we need to use tcp_बंद() after detaching them from the mptcp
 * parent socket.
 */
अटल व्योम __mptcp_बंद_ssk(काष्ठा sock *sk, काष्ठा sock *ssk,
			      काष्ठा mptcp_subflow_context *subflow)
अणु
	काष्ठा mptcp_sock *msk = mptcp_sk(sk);

	list_del(&subflow->node);

	lock_sock_nested(ssk, SINGLE_DEPTH_NESTING);

	/* अगर we are invoked by the msk cleanup code, the subflow is
	 * alपढ़ोy orphaned
	 */
	अगर (ssk->sk_socket)
		sock_orphan(ssk);

	subflow->disposable = 1;

	/* अगर ssk hit tcp_करोne(), tcp_cleanup_ulp() cleared the related ops
	 * the ssk has been alपढ़ोy destroyed, we just need to release the
	 * reference owned by msk;
	 */
	अगर (!inet_csk(ssk)->icsk_ulp_ops) अणु
		kमुक्त_rcu(subflow, rcu);
	पूर्ण अन्यथा अणु
		/* otherwise tcp will dispose of the ssk and subflow ctx */
		__tcp_बंद(ssk, 0);

		/* बंद acquired an extra ref */
		__sock_put(ssk);
	पूर्ण
	release_sock(ssk);

	sock_put(ssk);

	अगर (ssk == msk->last_snd)
		msk->last_snd = शून्य;

	अगर (ssk == msk->ack_hपूर्णांक)
		msk->ack_hपूर्णांक = शून्य;

	अगर (ssk == msk->first)
		msk->first = शून्य;

	अगर (msk->subflow && ssk == msk->subflow->sk)
		mptcp_dispose_initial_subflow(msk);
पूर्ण

व्योम mptcp_बंद_ssk(काष्ठा sock *sk, काष्ठा sock *ssk,
		     काष्ठा mptcp_subflow_context *subflow)
अणु
	अगर (sk->sk_state == TCP_ESTABLISHED)
		mptcp_event(MPTCP_EVENT_SUB_CLOSED, mptcp_sk(sk), ssk, GFP_KERNEL);
	__mptcp_बंद_ssk(sk, ssk, subflow);
पूर्ण

अटल अचिन्हित पूर्णांक mptcp_sync_mss(काष्ठा sock *sk, u32 pmtu)
अणु
	वापस 0;
पूर्ण

अटल व्योम __mptcp_बंद_subflow(काष्ठा mptcp_sock *msk)
अणु
	काष्ठा mptcp_subflow_context *subflow, *पंचांगp;

	might_sleep();

	list_क्रम_each_entry_safe(subflow, पंचांगp, &msk->conn_list, node) अणु
		काष्ठा sock *ssk = mptcp_subflow_tcp_sock(subflow);

		अगर (inet_sk_state_load(ssk) != TCP_CLOSE)
			जारी;

		/* 'subflow_data_ready' will re-sched once rx queue is empty */
		अगर (!skb_queue_empty_lockless(&ssk->sk_receive_queue))
			जारी;

		mptcp_बंद_ssk((काष्ठा sock *)msk, ssk, subflow);
	पूर्ण
पूर्ण

अटल bool mptcp_check_बंद_समयout(स्थिर काष्ठा sock *sk)
अणु
	s32 delta = tcp_jअगरfies32 - inet_csk(sk)->icsk_mtup.probe_बारtamp;
	काष्ठा mptcp_subflow_context *subflow;

	अगर (delta >= TCP_TIMEWAIT_LEN)
		वापस true;

	/* अगर all subflows are in बंदd status करोn't bother with additional
	 * समयout
	 */
	mptcp_क्रम_each_subflow(mptcp_sk(sk), subflow) अणु
		अगर (inet_sk_state_load(mptcp_subflow_tcp_sock(subflow)) !=
		    TCP_CLOSE)
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल व्योम mptcp_check_fastबंद(काष्ठा mptcp_sock *msk)
अणु
	काष्ठा mptcp_subflow_context *subflow, *पंचांगp;
	काष्ठा sock *sk = &msk->sk.icsk_inet.sk;

	अगर (likely(!READ_ONCE(msk->rcv_fastबंद)))
		वापस;

	mptcp_token_destroy(msk);

	list_क्रम_each_entry_safe(subflow, पंचांगp, &msk->conn_list, node) अणु
		काष्ठा sock *tcp_sk = mptcp_subflow_tcp_sock(subflow);

		lock_sock(tcp_sk);
		अगर (tcp_sk->sk_state != TCP_CLOSE) अणु
			tcp_send_active_reset(tcp_sk, GFP_ATOMIC);
			tcp_set_state(tcp_sk, TCP_CLOSE);
		पूर्ण
		release_sock(tcp_sk);
	पूर्ण

	inet_sk_state_store(sk, TCP_CLOSE);
	sk->sk_shutकरोwn = SHUTDOWN_MASK;
	smp_mb__beक्रमe_atomic(); /* SHUTDOWN must be visible first */
	set_bit(MPTCP_DATA_READY, &msk->flags);
	set_bit(MPTCP_WORK_CLOSE_SUBFLOW, &msk->flags);

	mptcp_बंद_wake_up(sk);
पूर्ण

अटल व्योम __mptcp_retrans(काष्ठा sock *sk)
अणु
	काष्ठा mptcp_sock *msk = mptcp_sk(sk);
	काष्ठा mptcp_sendmsg_info info = अणुपूर्ण;
	काष्ठा mptcp_data_frag *dfrag;
	माप_प्रकार copied = 0;
	काष्ठा sock *ssk;
	पूर्णांक ret;

	mptcp_clean_una_wakeup(sk);
	dfrag = mptcp_rtx_head(sk);
	अगर (!dfrag) अणु
		अगर (mptcp_data_fin_enabled(msk)) अणु
			काष्ठा inet_connection_sock *icsk = inet_csk(sk);

			icsk->icsk_retransmits++;
			mptcp_set_datafin_समयout(sk);
			mptcp_send_ack(msk);

			जाओ reset_समयr;
		पूर्ण

		वापस;
	पूर्ण

	ssk = mptcp_subflow_get_retrans(msk);
	अगर (!ssk)
		जाओ reset_समयr;

	lock_sock(ssk);

	/* limit retransmission to the bytes alपढ़ोy sent on some subflows */
	info.sent = 0;
	info.limit = dfrag->alपढ़ोy_sent;
	जबतक (info.sent < dfrag->alपढ़ोy_sent) अणु
		अगर (!mptcp_alloc_tx_skb(sk, ssk))
			अवरोध;

		ret = mptcp_sendmsg_frag(sk, ssk, dfrag, &info);
		अगर (ret <= 0)
			अवरोध;

		MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_RETRANSSEGS);
		copied += ret;
		info.sent += ret;
	पूर्ण
	अगर (copied)
		tcp_push(ssk, 0, info.mss_now, tcp_sk(ssk)->nonagle,
			 info.size_goal);

	mptcp_set_समयout(sk, ssk);
	release_sock(ssk);

reset_समयr:
	अगर (!mptcp_समयr_pending(sk))
		mptcp_reset_समयr(sk);
पूर्ण

अटल व्योम mptcp_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mptcp_sock *msk = container_of(work, काष्ठा mptcp_sock, work);
	काष्ठा sock *sk = &msk->sk.icsk_inet.sk;
	पूर्णांक state;

	lock_sock(sk);
	state = sk->sk_state;
	अगर (unlikely(state == TCP_CLOSE))
		जाओ unlock;

	mptcp_check_data_fin_ack(sk);
	mptcp_flush_join_list(msk);

	mptcp_check_fastबंद(msk);

	अगर (msk->pm.status)
		mptcp_pm_nl_work(msk);

	अगर (test_and_clear_bit(MPTCP_WORK_खातापूर्ण, &msk->flags))
		mptcp_check_क्रम_eof(msk);

	__mptcp_check_send_data_fin(sk);
	mptcp_check_data_fin(sk);

	/* There is no poपूर्णांक in keeping around an orphaned sk समयकरोut or
	 * बंदd, but we need the msk around to reply to incoming DATA_FIN,
	 * even अगर it is orphaned and in FIN_WAIT2 state
	 */
	अगर (sock_flag(sk, SOCK_DEAD) &&
	    (mptcp_check_बंद_समयout(sk) || sk->sk_state == TCP_CLOSE)) अणु
		inet_sk_state_store(sk, TCP_CLOSE);
		__mptcp_destroy_sock(sk);
		जाओ unlock;
	पूर्ण

	अगर (test_and_clear_bit(MPTCP_WORK_CLOSE_SUBFLOW, &msk->flags))
		__mptcp_बंद_subflow(msk);

	अगर (test_and_clear_bit(MPTCP_WORK_RTX, &msk->flags))
		__mptcp_retrans(sk);

unlock:
	release_sock(sk);
	sock_put(sk);
पूर्ण

अटल पूर्णांक __mptcp_init_sock(काष्ठा sock *sk)
अणु
	काष्ठा mptcp_sock *msk = mptcp_sk(sk);

	spin_lock_init(&msk->join_list_lock);

	INIT_LIST_HEAD(&msk->conn_list);
	INIT_LIST_HEAD(&msk->join_list);
	INIT_LIST_HEAD(&msk->rtx_queue);
	INIT_WORK(&msk->work, mptcp_worker);
	__skb_queue_head_init(&msk->receive_queue);
	__skb_queue_head_init(&msk->skb_tx_cache);
	msk->out_of_order_queue = RB_ROOT;
	msk->first_pending = शून्य;
	msk->wmem_reserved = 0;
	msk->rmem_released = 0;
	msk->tx_pending_data = 0;
	msk->size_goal_cache = TCP_BASE_MSS;

	msk->ack_hपूर्णांक = शून्य;
	msk->first = शून्य;
	inet_csk(sk)->icsk_sync_mss = mptcp_sync_mss;

	mptcp_pm_data_init(msk);

	/* re-use the csk retrans समयr क्रम MPTCP-level retrans */
	समयr_setup(&msk->sk.icsk_retransmit_समयr, mptcp_retransmit_समयr, 0);
	समयr_setup(&sk->sk_समयr, mptcp_समयout_समयr, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक mptcp_init_sock(काष्ठा sock *sk)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	काष्ठा net *net = sock_net(sk);
	पूर्णांक ret;

	ret = __mptcp_init_sock(sk);
	अगर (ret)
		वापस ret;

	अगर (!mptcp_is_enabled(net))
		वापस -ENOPROTOOPT;

	अगर (unlikely(!net->mib.mptcp_statistics) && !mptcp_mib_alloc(net))
		वापस -ENOMEM;

	ret = __mptcp_socket_create(mptcp_sk(sk));
	अगर (ret)
		वापस ret;

	/* fetch the ca name; करो it outside __mptcp_init_sock(), so that clone will
	 * propagate the correct value
	 */
	tcp_assign_congestion_control(sk);
	म_नकल(mptcp_sk(sk)->ca_name, icsk->icsk_ca_ops->name);

	/* no need to keep a reference to the ops, the name will suffice */
	tcp_cleanup_congestion_control(sk);
	icsk->icsk_ca_ops = शून्य;

	sk_sockets_allocated_inc(sk);
	sk->sk_rcvbuf = sock_net(sk)->ipv4.sysctl_tcp_rmem[1];
	sk->sk_sndbuf = sock_net(sk)->ipv4.sysctl_tcp_wmem[1];

	वापस 0;
पूर्ण

अटल व्योम __mptcp_clear_xmit(काष्ठा sock *sk)
अणु
	काष्ठा mptcp_sock *msk = mptcp_sk(sk);
	काष्ठा mptcp_data_frag *dपंचांगp, *dfrag;
	काष्ठा sk_buff *skb;

	WRITE_ONCE(msk->first_pending, शून्य);
	list_क्रम_each_entry_safe(dfrag, dपंचांगp, &msk->rtx_queue, list)
		dfrag_clear(sk, dfrag);
	जबतक ((skb = __skb_dequeue(&msk->skb_tx_cache)) != शून्य) अणु
		sk->sk_क्रमward_alloc += skb->truesize;
		kमुक्त_skb(skb);
	पूर्ण
पूर्ण

अटल व्योम mptcp_cancel_work(काष्ठा sock *sk)
अणु
	काष्ठा mptcp_sock *msk = mptcp_sk(sk);

	अगर (cancel_work_sync(&msk->work))
		__sock_put(sk);
पूर्ण

व्योम mptcp_subflow_shutकरोwn(काष्ठा sock *sk, काष्ठा sock *ssk, पूर्णांक how)
अणु
	lock_sock(ssk);

	चयन (ssk->sk_state) अणु
	हाल TCP_LISTEN:
		अगर (!(how & RCV_SHUTDOWN))
			अवरोध;
		fallthrough;
	हाल TCP_SYN_SENT:
		tcp_disconnect(ssk, O_NONBLOCK);
		अवरोध;
	शेष:
		अगर (__mptcp_check_fallback(mptcp_sk(sk))) अणु
			pr_debug("Fallback");
			ssk->sk_shutकरोwn |= how;
			tcp_shutकरोwn(ssk, how);
		पूर्ण अन्यथा अणु
			pr_debug("Sending DATA_FIN on subflow %p", ssk);
			mptcp_set_समयout(sk, ssk);
			tcp_send_ack(ssk);
			अगर (!mptcp_समयr_pending(sk))
				mptcp_reset_समयr(sk);
		पूर्ण
		अवरोध;
	पूर्ण

	release_sock(ssk);
पूर्ण

अटल स्थिर अचिन्हित अक्षर new_state[16] = अणु
	/* current state:     new state:      action:	*/
	[0 /* (Invalid) */] = TCP_CLOSE,
	[TCP_ESTABLISHED]   = TCP_FIN_WAIT1 | TCP_ACTION_FIN,
	[TCP_SYN_SENT]      = TCP_CLOSE,
	[TCP_SYN_RECV]      = TCP_FIN_WAIT1 | TCP_ACTION_FIN,
	[TCP_FIN_WAIT1]     = TCP_FIN_WAIT1,
	[TCP_FIN_WAIT2]     = TCP_FIN_WAIT2,
	[TCP_TIME_WAIT]     = TCP_CLOSE,	/* should not happen ! */
	[TCP_CLOSE]         = TCP_CLOSE,
	[TCP_CLOSE_WAIT]    = TCP_LAST_ACK  | TCP_ACTION_FIN,
	[TCP_LAST_ACK]      = TCP_LAST_ACK,
	[TCP_LISTEN]        = TCP_CLOSE,
	[TCP_CLOSING]       = TCP_CLOSING,
	[TCP_NEW_SYN_RECV]  = TCP_CLOSE,	/* should not happen ! */
पूर्ण;

अटल पूर्णांक mptcp_बंद_state(काष्ठा sock *sk)
अणु
	पूर्णांक next = (पूर्णांक)new_state[sk->sk_state];
	पूर्णांक ns = next & TCP_STATE_MASK;

	inet_sk_state_store(sk, ns);

	वापस next & TCP_ACTION_FIN;
पूर्ण

अटल व्योम __mptcp_check_send_data_fin(काष्ठा sock *sk)
अणु
	काष्ठा mptcp_subflow_context *subflow;
	काष्ठा mptcp_sock *msk = mptcp_sk(sk);

	pr_debug("msk=%p snd_data_fin_enable=%d pending=%d snd_nxt=%llu write_seq=%llu",
		 msk, msk->snd_data_fin_enable, !!mptcp_send_head(sk),
		 msk->snd_nxt, msk->ग_लिखो_seq);

	/* we still need to enqueue subflows or not really shutting करोwn,
	 * skip this
	 */
	अगर (!msk->snd_data_fin_enable || msk->snd_nxt + 1 != msk->ग_लिखो_seq ||
	    mptcp_send_head(sk))
		वापस;

	WRITE_ONCE(msk->snd_nxt, msk->ग_लिखो_seq);

	/* fallback socket will not get data_fin/ack, can move to the next
	 * state now
	 */
	अगर (__mptcp_check_fallback(msk)) अणु
		अगर ((1 << sk->sk_state) & (TCPF_CLOSING | TCPF_LAST_ACK)) अणु
			inet_sk_state_store(sk, TCP_CLOSE);
			mptcp_बंद_wake_up(sk);
		पूर्ण अन्यथा अगर (sk->sk_state == TCP_FIN_WAIT1) अणु
			inet_sk_state_store(sk, TCP_FIN_WAIT2);
		पूर्ण
	पूर्ण

	mptcp_flush_join_list(msk);
	mptcp_क्रम_each_subflow(msk, subflow) अणु
		काष्ठा sock *tcp_sk = mptcp_subflow_tcp_sock(subflow);

		mptcp_subflow_shutकरोwn(sk, tcp_sk, SEND_SHUTDOWN);
	पूर्ण
पूर्ण

अटल व्योम __mptcp_wr_shutकरोwn(काष्ठा sock *sk)
अणु
	काष्ठा mptcp_sock *msk = mptcp_sk(sk);

	pr_debug("msk=%p snd_data_fin_enable=%d shutdown=%x state=%d pending=%d",
		 msk, msk->snd_data_fin_enable, sk->sk_shutकरोwn, sk->sk_state,
		 !!mptcp_send_head(sk));

	/* will be ignored by fallback sockets */
	WRITE_ONCE(msk->ग_लिखो_seq, msk->ग_लिखो_seq + 1);
	WRITE_ONCE(msk->snd_data_fin_enable, 1);

	__mptcp_check_send_data_fin(sk);
पूर्ण

अटल व्योम __mptcp_destroy_sock(काष्ठा sock *sk)
अणु
	काष्ठा mptcp_subflow_context *subflow, *पंचांगp;
	काष्ठा mptcp_sock *msk = mptcp_sk(sk);
	LIST_HEAD(conn_list);

	pr_debug("msk=%p", msk);

	might_sleep();

	/* be sure to always acquire the join list lock, to sync vs
	 * mptcp_finish_join().
	 */
	spin_lock_bh(&msk->join_list_lock);
	list_splice_tail_init(&msk->join_list, &msk->conn_list);
	spin_unlock_bh(&msk->join_list_lock);
	list_splice_init(&msk->conn_list, &conn_list);

	sk_stop_समयr(sk, &msk->sk.icsk_retransmit_समयr);
	sk_stop_समयr(sk, &sk->sk_समयr);
	msk->pm.status = 0;

	list_क्रम_each_entry_safe(subflow, पंचांगp, &conn_list, node) अणु
		काष्ठा sock *ssk = mptcp_subflow_tcp_sock(subflow);
		__mptcp_बंद_ssk(sk, ssk, subflow);
	पूर्ण

	sk->sk_prot->destroy(sk);

	WARN_ON_ONCE(msk->wmem_reserved);
	WARN_ON_ONCE(msk->rmem_released);
	sk_stream_समाप्त_queues(sk);
	xfrm_sk_मुक्त_policy(sk);

	sk_refcnt_debug_release(sk);
	mptcp_dispose_initial_subflow(msk);
	sock_put(sk);
पूर्ण

अटल व्योम mptcp_बंद(काष्ठा sock *sk, दीर्घ समयout)
अणु
	काष्ठा mptcp_subflow_context *subflow;
	bool करो_cancel_work = false;

	lock_sock(sk);
	sk->sk_shutकरोwn = SHUTDOWN_MASK;

	अगर ((1 << sk->sk_state) & (TCPF_LISTEN | TCPF_CLOSE)) अणु
		inet_sk_state_store(sk, TCP_CLOSE);
		जाओ cleanup;
	पूर्ण

	अगर (mptcp_बंद_state(sk))
		__mptcp_wr_shutकरोwn(sk);

	sk_stream_रुको_बंद(sk, समयout);

cleanup:
	/* orphan all the subflows */
	inet_csk(sk)->icsk_mtup.probe_बारtamp = tcp_jअगरfies32;
	mptcp_क्रम_each_subflow(mptcp_sk(sk), subflow) अणु
		काष्ठा sock *ssk = mptcp_subflow_tcp_sock(subflow);
		bool slow = lock_sock_fast(ssk);

		sock_orphan(ssk);
		unlock_sock_fast(ssk, slow);
	पूर्ण
	sock_orphan(sk);

	sock_hold(sk);
	pr_debug("msk=%p state=%d", sk, sk->sk_state);
	अगर (sk->sk_state == TCP_CLOSE) अणु
		__mptcp_destroy_sock(sk);
		करो_cancel_work = true;
	पूर्ण अन्यथा अणु
		sk_reset_समयr(sk, &sk->sk_समयr, jअगरfies + TCP_TIMEWAIT_LEN);
	पूर्ण
	release_sock(sk);
	अगर (करो_cancel_work)
		mptcp_cancel_work(sk);

	अगर (mptcp_sk(sk)->token)
		mptcp_event(MPTCP_EVENT_CLOSED, mptcp_sk(sk), शून्य, GFP_KERNEL);

	sock_put(sk);
पूर्ण

अटल व्योम mptcp_copy_inaddrs(काष्ठा sock *msk, स्थिर काष्ठा sock *ssk)
अणु
#अगर IS_ENABLED(CONFIG_MPTCP_IPV6)
	स्थिर काष्ठा ipv6_pinfo *ssk6 = inet6_sk(ssk);
	काष्ठा ipv6_pinfo *msk6 = inet6_sk(msk);

	msk->sk_v6_daddr = ssk->sk_v6_daddr;
	msk->sk_v6_rcv_saddr = ssk->sk_v6_rcv_saddr;

	अगर (msk6 && ssk6) अणु
		msk6->saddr = ssk6->saddr;
		msk6->flow_label = ssk6->flow_label;
	पूर्ण
#पूर्ण_अगर

	inet_sk(msk)->inet_num = inet_sk(ssk)->inet_num;
	inet_sk(msk)->inet_dport = inet_sk(ssk)->inet_dport;
	inet_sk(msk)->inet_sport = inet_sk(ssk)->inet_sport;
	inet_sk(msk)->inet_daddr = inet_sk(ssk)->inet_daddr;
	inet_sk(msk)->inet_saddr = inet_sk(ssk)->inet_saddr;
	inet_sk(msk)->inet_rcv_saddr = inet_sk(ssk)->inet_rcv_saddr;
पूर्ण

अटल पूर्णांक mptcp_disconnect(काष्ठा sock *sk, पूर्णांक flags)
अणु
	काष्ठा mptcp_subflow_context *subflow;
	काष्ठा mptcp_sock *msk = mptcp_sk(sk);

	mptcp_करो_flush_join_list(msk);

	mptcp_क्रम_each_subflow(msk, subflow) अणु
		काष्ठा sock *ssk = mptcp_subflow_tcp_sock(subflow);

		lock_sock(ssk);
		tcp_disconnect(ssk, flags);
		release_sock(ssk);
	पूर्ण
	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_MPTCP_IPV6)
अटल काष्ठा ipv6_pinfo *mptcp_inet6_sk(स्थिर काष्ठा sock *sk)
अणु
	अचिन्हित पूर्णांक offset = माप(काष्ठा mptcp6_sock) - माप(काष्ठा ipv6_pinfo);

	वापस (काष्ठा ipv6_pinfo *)(((u8 *)sk) + offset);
पूर्ण
#पूर्ण_अगर

काष्ठा sock *mptcp_sk_clone(स्थिर काष्ठा sock *sk,
			    स्थिर काष्ठा mptcp_options_received *mp_opt,
			    काष्ठा request_sock *req)
अणु
	काष्ठा mptcp_subflow_request_sock *subflow_req = mptcp_subflow_rsk(req);
	काष्ठा sock *nsk = sk_clone_lock(sk, GFP_ATOMIC);
	काष्ठा mptcp_sock *msk;
	u64 ack_seq;

	अगर (!nsk)
		वापस शून्य;

#अगर IS_ENABLED(CONFIG_MPTCP_IPV6)
	अगर (nsk->sk_family == AF_INET6)
		inet_sk(nsk)->pinet6 = mptcp_inet6_sk(nsk);
#पूर्ण_अगर

	__mptcp_init_sock(nsk);

	msk = mptcp_sk(nsk);
	msk->local_key = subflow_req->local_key;
	msk->token = subflow_req->token;
	msk->subflow = शून्य;
	WRITE_ONCE(msk->fully_established, false);

	msk->ग_लिखो_seq = subflow_req->idsn + 1;
	msk->snd_nxt = msk->ग_लिखो_seq;
	msk->snd_una = msk->ग_लिखो_seq;
	msk->wnd_end = msk->snd_nxt + req->rsk_rcv_wnd;
	msk->setsockopt_seq = mptcp_sk(sk)->setsockopt_seq;

	अगर (mp_opt->mp_capable) अणु
		msk->can_ack = true;
		msk->remote_key = mp_opt->sndr_key;
		mptcp_crypto_key_sha(msk->remote_key, शून्य, &ack_seq);
		ack_seq++;
		WRITE_ONCE(msk->ack_seq, ack_seq);
		WRITE_ONCE(msk->rcv_wnd_sent, ack_seq);
	पूर्ण

	sock_reset_flag(nsk, SOCK_RCU_FREE);
	/* will be fully established after successful MPC subflow creation */
	inet_sk_state_store(nsk, TCP_SYN_RECV);

	security_inet_csk_clone(nsk, req);
	bh_unlock_sock(nsk);

	/* keep a single reference */
	__sock_put(nsk);
	वापस nsk;
पूर्ण

व्योम mptcp_rcv_space_init(काष्ठा mptcp_sock *msk, स्थिर काष्ठा sock *ssk)
अणु
	स्थिर काष्ठा tcp_sock *tp = tcp_sk(ssk);

	msk->rcvq_space.copied = 0;
	msk->rcvq_space.rtt_us = 0;

	msk->rcvq_space.समय = tp->tcp_mstamp;

	/* initial rcv_space offering made to peer */
	msk->rcvq_space.space = min_t(u32, tp->rcv_wnd,
				      TCP_INIT_CWND * tp->advmss);
	अगर (msk->rcvq_space.space == 0)
		msk->rcvq_space.space = TCP_INIT_CWND * TCP_MSS_DEFAULT;

	WRITE_ONCE(msk->wnd_end, msk->snd_nxt + tcp_sk(ssk)->snd_wnd);
पूर्ण

अटल काष्ठा sock *mptcp_accept(काष्ठा sock *sk, पूर्णांक flags, पूर्णांक *err,
				 bool kern)
अणु
	काष्ठा mptcp_sock *msk = mptcp_sk(sk);
	काष्ठा socket *listener;
	काष्ठा sock *newsk;

	listener = __mptcp_nmpc_socket(msk);
	अगर (WARN_ON_ONCE(!listener)) अणु
		*err = -EINVAL;
		वापस शून्य;
	पूर्ण

	pr_debug("msk=%p, listener=%p", msk, mptcp_subflow_ctx(listener->sk));
	newsk = inet_csk_accept(listener->sk, flags, err, kern);
	अगर (!newsk)
		वापस शून्य;

	pr_debug("msk=%p, subflow is mptcp=%d", msk, sk_is_mptcp(newsk));
	अगर (sk_is_mptcp(newsk)) अणु
		काष्ठा mptcp_subflow_context *subflow;
		काष्ठा sock *new_mptcp_sock;

		subflow = mptcp_subflow_ctx(newsk);
		new_mptcp_sock = subflow->conn;

		/* is_mptcp should be false अगर subflow->conn is missing, see
		 * subflow_syn_recv_sock()
		 */
		अगर (WARN_ON_ONCE(!new_mptcp_sock)) अणु
			tcp_sk(newsk)->is_mptcp = 0;
			वापस newsk;
		पूर्ण

		/* acquire the 2nd reference क्रम the owning socket */
		sock_hold(new_mptcp_sock);
		newsk = new_mptcp_sock;
		MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_MPCAPABLEPASSIVEACK);
	पूर्ण अन्यथा अणु
		MPTCP_INC_STATS(sock_net(sk),
				MPTCP_MIB_MPCAPABLEPASSIVEFALLBACK);
	पूर्ण

	वापस newsk;
पूर्ण

व्योम mptcp_destroy_common(काष्ठा mptcp_sock *msk)
अणु
	काष्ठा sock *sk = (काष्ठा sock *)msk;

	__mptcp_clear_xmit(sk);

	/* move to sk_receive_queue, sk_stream_समाप्त_queues will purge it */
	skb_queue_splice_tail_init(&msk->receive_queue, &sk->sk_receive_queue);

	skb_rbtree_purge(&msk->out_of_order_queue);
	mptcp_token_destroy(msk);
	mptcp_pm_मुक्त_anno_list(msk);
पूर्ण

अटल व्योम mptcp_destroy(काष्ठा sock *sk)
अणु
	काष्ठा mptcp_sock *msk = mptcp_sk(sk);

	mptcp_destroy_common(msk);
	sk_sockets_allocated_dec(sk);
पूर्ण

व्योम __mptcp_data_acked(काष्ठा sock *sk)
अणु
	अगर (!sock_owned_by_user(sk))
		__mptcp_clean_una(sk);
	अन्यथा
		set_bit(MPTCP_CLEAN_UNA, &mptcp_sk(sk)->flags);

	अगर (mptcp_pending_data_fin_ack(sk))
		mptcp_schedule_work(sk);
पूर्ण

व्योम __mptcp_check_push(काष्ठा sock *sk, काष्ठा sock *ssk)
अणु
	अगर (!mptcp_send_head(sk))
		वापस;

	अगर (!sock_owned_by_user(sk)) अणु
		काष्ठा sock *xmit_ssk = mptcp_subflow_get_send(mptcp_sk(sk));

		अगर (xmit_ssk == ssk)
			__mptcp_subflow_push_pending(sk, ssk);
		अन्यथा अगर (xmit_ssk)
			mptcp_subflow_delegate(mptcp_subflow_ctx(xmit_ssk));
	पूर्ण अन्यथा अणु
		set_bit(MPTCP_PUSH_PENDING, &mptcp_sk(sk)->flags);
	पूर्ण
पूर्ण

/* processes deferred events and flush wmem */
अटल व्योम mptcp_release_cb(काष्ठा sock *sk)
अणु
	क्रम (;;) अणु
		अचिन्हित दीर्घ flags = 0;

		अगर (test_and_clear_bit(MPTCP_PUSH_PENDING, &mptcp_sk(sk)->flags))
			flags |= BIT(MPTCP_PUSH_PENDING);
		अगर (test_and_clear_bit(MPTCP_RETRANSMIT, &mptcp_sk(sk)->flags))
			flags |= BIT(MPTCP_RETRANSMIT);
		अगर (!flags)
			अवरोध;

		/* the following actions acquire the subflow socket lock
		 *
		 * 1) can't be invoked in atomic scope
		 * 2) must aव्योम ABBA deadlock with msk socket spinlock: the RX
		 *    datapath acquires the msk socket spinlock जबतक helding
		 *    the subflow socket lock
		 */

		spin_unlock_bh(&sk->sk_lock.slock);
		अगर (flags & BIT(MPTCP_PUSH_PENDING))
			__mptcp_push_pending(sk, 0);
		अगर (flags & BIT(MPTCP_RETRANSMIT))
			__mptcp_retrans(sk);

		cond_resched();
		spin_lock_bh(&sk->sk_lock.slock);
	पूर्ण

	अगर (test_and_clear_bit(MPTCP_CLEAN_UNA, &mptcp_sk(sk)->flags))
		__mptcp_clean_una_wakeup(sk);
	अगर (test_and_clear_bit(MPTCP_ERROR_REPORT, &mptcp_sk(sk)->flags))
		__mptcp_error_report(sk);

	/* push_pending may touch wmem_reserved, ensure we करो the cleanup
	 * later
	 */
	__mptcp_update_wmem(sk);
	__mptcp_update_rmem(sk);
पूर्ण

व्योम mptcp_subflow_process_delegated(काष्ठा sock *ssk)
अणु
	काष्ठा mptcp_subflow_context *subflow = mptcp_subflow_ctx(ssk);
	काष्ठा sock *sk = subflow->conn;

	mptcp_data_lock(sk);
	अगर (!sock_owned_by_user(sk))
		__mptcp_subflow_push_pending(sk, ssk);
	अन्यथा
		set_bit(MPTCP_PUSH_PENDING, &mptcp_sk(sk)->flags);
	mptcp_data_unlock(sk);
	mptcp_subflow_delegated_करोne(subflow);
पूर्ण

अटल पूर्णांक mptcp_hash(काष्ठा sock *sk)
अणु
	/* should never be called,
	 * we hash the TCP subflows not the master socket
	 */
	WARN_ON_ONCE(1);
	वापस 0;
पूर्ण

अटल व्योम mptcp_unhash(काष्ठा sock *sk)
अणु
	/* called from sk_common_release(), but nothing to करो here */
पूर्ण

अटल पूर्णांक mptcp_get_port(काष्ठा sock *sk, अचिन्हित लघु snum)
अणु
	काष्ठा mptcp_sock *msk = mptcp_sk(sk);
	काष्ठा socket *ssock;

	ssock = __mptcp_nmpc_socket(msk);
	pr_debug("msk=%p, subflow=%p", msk, ssock);
	अगर (WARN_ON_ONCE(!ssock))
		वापस -EINVAL;

	वापस inet_csk_get_port(ssock->sk, snum);
पूर्ण

व्योम mptcp_finish_connect(काष्ठा sock *ssk)
अणु
	काष्ठा mptcp_subflow_context *subflow;
	काष्ठा mptcp_sock *msk;
	काष्ठा sock *sk;
	u64 ack_seq;

	subflow = mptcp_subflow_ctx(ssk);
	sk = subflow->conn;
	msk = mptcp_sk(sk);

	pr_debug("msk=%p, token=%u", sk, subflow->token);

	mptcp_crypto_key_sha(subflow->remote_key, शून्य, &ack_seq);
	ack_seq++;
	subflow->map_seq = ack_seq;
	subflow->map_subflow_seq = 1;

	/* the socket is not connected yet, no msk/subflow ops can access/race
	 * accessing the field below
	 */
	WRITE_ONCE(msk->remote_key, subflow->remote_key);
	WRITE_ONCE(msk->local_key, subflow->local_key);
	WRITE_ONCE(msk->ग_लिखो_seq, subflow->idsn + 1);
	WRITE_ONCE(msk->snd_nxt, msk->ग_लिखो_seq);
	WRITE_ONCE(msk->ack_seq, ack_seq);
	WRITE_ONCE(msk->rcv_wnd_sent, ack_seq);
	WRITE_ONCE(msk->can_ack, 1);
	WRITE_ONCE(msk->snd_una, msk->ग_लिखो_seq);

	mptcp_pm_new_connection(msk, ssk, 0);

	mptcp_rcv_space_init(msk, ssk);
पूर्ण

व्योम mptcp_sock_graft(काष्ठा sock *sk, काष्ठा socket *parent)
अणु
	ग_लिखो_lock_bh(&sk->sk_callback_lock);
	rcu_assign_poपूर्णांकer(sk->sk_wq, &parent->wq);
	sk_set_socket(sk, parent);
	sk->sk_uid = SOCK_INODE(parent)->i_uid;
	ग_लिखो_unlock_bh(&sk->sk_callback_lock);
पूर्ण

bool mptcp_finish_join(काष्ठा sock *ssk)
अणु
	काष्ठा mptcp_subflow_context *subflow = mptcp_subflow_ctx(ssk);
	काष्ठा mptcp_sock *msk = mptcp_sk(subflow->conn);
	काष्ठा sock *parent = (व्योम *)msk;
	काष्ठा socket *parent_sock;
	bool ret;

	pr_debug("msk=%p, subflow=%p", msk, subflow);

	/* mptcp socket alपढ़ोy closing? */
	अगर (!mptcp_is_fully_established(parent)) अणु
		subflow->reset_reason = MPTCP_RST_EMPTCP;
		वापस false;
	पूर्ण

	अगर (!msk->pm.server_side)
		जाओ out;

	अगर (!mptcp_pm_allow_new_subflow(msk)) अणु
		subflow->reset_reason = MPTCP_RST_EPROHIBIT;
		वापस false;
	पूर्ण

	/* active connections are alपढ़ोy on conn_list, and we can't acquire
	 * msk lock here.
	 * use the join list lock as synchronization poपूर्णांक and द्विगुन-check
	 * msk status to aव्योम racing with __mptcp_destroy_sock()
	 */
	spin_lock_bh(&msk->join_list_lock);
	ret = inet_sk_state_load(parent) == TCP_ESTABLISHED;
	अगर (ret && !WARN_ON_ONCE(!list_empty(&subflow->node))) अणु
		list_add_tail(&subflow->node, &msk->join_list);
		sock_hold(ssk);
	पूर्ण
	spin_unlock_bh(&msk->join_list_lock);
	अगर (!ret) अणु
		subflow->reset_reason = MPTCP_RST_EPROHIBIT;
		वापस false;
	पूर्ण

	/* attach to msk socket only after we are sure he will deal with us
	 * at बंद समय
	 */
	parent_sock = READ_ONCE(parent->sk_socket);
	अगर (parent_sock && !ssk->sk_socket)
		mptcp_sock_graft(ssk, parent_sock);
	subflow->map_seq = READ_ONCE(msk->ack_seq);
out:
	mptcp_event(MPTCP_EVENT_SUB_ESTABLISHED, msk, ssk, GFP_ATOMIC);
	वापस true;
पूर्ण

अटल व्योम mptcp_shutकरोwn(काष्ठा sock *sk, पूर्णांक how)
अणु
	pr_debug("sk=%p, how=%d", sk, how);

	अगर ((how & SEND_SHUTDOWN) && mptcp_बंद_state(sk))
		__mptcp_wr_shutकरोwn(sk);
पूर्ण

अटल काष्ठा proto mptcp_prot = अणु
	.name		= "MPTCP",
	.owner		= THIS_MODULE,
	.init		= mptcp_init_sock,
	.disconnect	= mptcp_disconnect,
	.बंद		= mptcp_बंद,
	.accept		= mptcp_accept,
	.setsockopt	= mptcp_setsockopt,
	.माला_लोockopt	= mptcp_माला_लोockopt,
	.shutकरोwn	= mptcp_shutकरोwn,
	.destroy	= mptcp_destroy,
	.sendmsg	= mptcp_sendmsg,
	.recvmsg	= mptcp_recvmsg,
	.release_cb	= mptcp_release_cb,
	.hash		= mptcp_hash,
	.unhash		= mptcp_unhash,
	.get_port	= mptcp_get_port,
	.sockets_allocated	= &mptcp_sockets_allocated,
	.memory_allocated	= &tcp_memory_allocated,
	.memory_pressure	= &tcp_memory_pressure,
	.sysctl_wmem_offset	= दुरत्व(काष्ठा net, ipv4.sysctl_tcp_wmem),
	.sysctl_rmem_offset	= दुरत्व(काष्ठा net, ipv4.sysctl_tcp_rmem),
	.sysctl_mem	= sysctl_tcp_mem,
	.obj_size	= माप(काष्ठा mptcp_sock),
	.slab_flags	= SLAB_TYPESAFE_BY_RCU,
	.no_स्वतःbind	= true,
पूर्ण;

अटल पूर्णांक mptcp_bind(काष्ठा socket *sock, काष्ठा sockaddr *uaddr, पूर्णांक addr_len)
अणु
	काष्ठा mptcp_sock *msk = mptcp_sk(sock->sk);
	काष्ठा socket *ssock;
	पूर्णांक err;

	lock_sock(sock->sk);
	ssock = __mptcp_nmpc_socket(msk);
	अगर (!ssock) अणु
		err = -EINVAL;
		जाओ unlock;
	पूर्ण

	err = ssock->ops->bind(ssock, uaddr, addr_len);
	अगर (!err)
		mptcp_copy_inaddrs(sock->sk, ssock->sk);

unlock:
	release_sock(sock->sk);
	वापस err;
पूर्ण

अटल व्योम mptcp_subflow_early_fallback(काष्ठा mptcp_sock *msk,
					 काष्ठा mptcp_subflow_context *subflow)
अणु
	subflow->request_mptcp = 0;
	__mptcp_करो_fallback(msk);
पूर्ण

अटल पूर्णांक mptcp_stream_connect(काष्ठा socket *sock, काष्ठा sockaddr *uaddr,
				पूर्णांक addr_len, पूर्णांक flags)
अणु
	काष्ठा mptcp_sock *msk = mptcp_sk(sock->sk);
	काष्ठा mptcp_subflow_context *subflow;
	काष्ठा socket *ssock;
	पूर्णांक err;

	lock_sock(sock->sk);
	अगर (sock->state != SS_UNCONNECTED && msk->subflow) अणु
		/* pending connection or invalid state, let existing subflow
		 * cope with that
		 */
		ssock = msk->subflow;
		जाओ करो_connect;
	पूर्ण

	ssock = __mptcp_nmpc_socket(msk);
	अगर (!ssock) अणु
		err = -EINVAL;
		जाओ unlock;
	पूर्ण

	mptcp_token_destroy(msk);
	inet_sk_state_store(sock->sk, TCP_SYN_SENT);
	subflow = mptcp_subflow_ctx(ssock->sk);
#अगर_घोषित CONFIG_TCP_MD5SIG
	/* no MPTCP अगर MD5SIG is enabled on this socket or we may run out of
	 * TCP option space.
	 */
	अगर (rcu_access_poपूर्णांकer(tcp_sk(ssock->sk)->md5sig_info))
		mptcp_subflow_early_fallback(msk, subflow);
#पूर्ण_अगर
	अगर (subflow->request_mptcp && mptcp_token_new_connect(ssock->sk)) अणु
		MPTCP_INC_STATS(sock_net(ssock->sk), MPTCP_MIB_TOKENFALLBACKINIT);
		mptcp_subflow_early_fallback(msk, subflow);
	पूर्ण
	अगर (likely(!__mptcp_check_fallback(msk)))
		MPTCP_INC_STATS(sock_net(sock->sk), MPTCP_MIB_MPCAPABLEACTIVE);

करो_connect:
	err = ssock->ops->connect(ssock, uaddr, addr_len, flags);
	sock->state = ssock->state;

	/* on successful connect, the msk state will be moved to established by
	 * subflow_finish_connect()
	 */
	अगर (!err || err == -EINPROGRESS)
		mptcp_copy_inaddrs(sock->sk, ssock->sk);
	अन्यथा
		inet_sk_state_store(sock->sk, inet_sk_state_load(ssock->sk));

unlock:
	release_sock(sock->sk);
	वापस err;
पूर्ण

अटल पूर्णांक mptcp_listen(काष्ठा socket *sock, पूर्णांक backlog)
अणु
	काष्ठा mptcp_sock *msk = mptcp_sk(sock->sk);
	काष्ठा socket *ssock;
	पूर्णांक err;

	pr_debug("msk=%p", msk);

	lock_sock(sock->sk);
	ssock = __mptcp_nmpc_socket(msk);
	अगर (!ssock) अणु
		err = -EINVAL;
		जाओ unlock;
	पूर्ण

	mptcp_token_destroy(msk);
	inet_sk_state_store(sock->sk, TCP_LISTEN);
	sock_set_flag(sock->sk, SOCK_RCU_FREE);

	err = ssock->ops->listen(ssock, backlog);
	inet_sk_state_store(sock->sk, inet_sk_state_load(ssock->sk));
	अगर (!err)
		mptcp_copy_inaddrs(sock->sk, ssock->sk);

unlock:
	release_sock(sock->sk);
	वापस err;
पूर्ण

अटल पूर्णांक mptcp_stream_accept(काष्ठा socket *sock, काष्ठा socket *newsock,
			       पूर्णांक flags, bool kern)
अणु
	काष्ठा mptcp_sock *msk = mptcp_sk(sock->sk);
	काष्ठा socket *ssock;
	पूर्णांक err;

	pr_debug("msk=%p", msk);

	lock_sock(sock->sk);
	अगर (sock->sk->sk_state != TCP_LISTEN)
		जाओ unlock_fail;

	ssock = __mptcp_nmpc_socket(msk);
	अगर (!ssock)
		जाओ unlock_fail;

	clear_bit(MPTCP_DATA_READY, &msk->flags);
	sock_hold(ssock->sk);
	release_sock(sock->sk);

	err = ssock->ops->accept(sock, newsock, flags, kern);
	अगर (err == 0 && !mptcp_is_tcpsk(newsock->sk)) अणु
		काष्ठा mptcp_sock *msk = mptcp_sk(newsock->sk);
		काष्ठा mptcp_subflow_context *subflow;
		काष्ठा sock *newsk = newsock->sk;

		lock_sock(newsk);

		/* PM/worker can now acquire the first subflow socket
		 * lock without racing with listener queue cleanup,
		 * we can notअगरy it, अगर needed.
		 *
		 * Even अगर remote has reset the initial subflow by now
		 * the refcnt is still at least one.
		 */
		subflow = mptcp_subflow_ctx(msk->first);
		list_add(&subflow->node, &msk->conn_list);
		sock_hold(msk->first);
		अगर (mptcp_is_fully_established(newsk))
			mptcp_pm_fully_established(msk, msk->first, GFP_KERNEL);

		mptcp_copy_inaddrs(newsk, msk->first);
		mptcp_rcv_space_init(msk, msk->first);
		mptcp_propagate_sndbuf(newsk, msk->first);

		/* set ssk->sk_socket of accept()ed flows to mptcp socket.
		 * This is needed so NOSPACE flag can be set from tcp stack.
		 */
		mptcp_flush_join_list(msk);
		mptcp_क्रम_each_subflow(msk, subflow) अणु
			काष्ठा sock *ssk = mptcp_subflow_tcp_sock(subflow);

			अगर (!ssk->sk_socket)
				mptcp_sock_graft(ssk, newsock);
		पूर्ण
		release_sock(newsk);
	पूर्ण

	अगर (inet_csk_listen_poll(ssock->sk))
		set_bit(MPTCP_DATA_READY, &msk->flags);
	sock_put(ssock->sk);
	वापस err;

unlock_fail:
	release_sock(sock->sk);
	वापस -EINVAL;
पूर्ण

अटल __poll_t mptcp_check_पढ़ोable(काष्ठा mptcp_sock *msk)
अणु
	वापस test_bit(MPTCP_DATA_READY, &msk->flags) ? EPOLLIN | EPOLLRDNORM :
	       0;
पूर्ण

अटल __poll_t mptcp_check_ग_लिखोable(काष्ठा mptcp_sock *msk)
अणु
	काष्ठा sock *sk = (काष्ठा sock *)msk;

	अगर (unlikely(sk->sk_shutकरोwn & SEND_SHUTDOWN))
		वापस EPOLLOUT | EPOLLWRNORM;

	अगर (sk_stream_is_ग_लिखोable(sk))
		वापस EPOLLOUT | EPOLLWRNORM;

	mptcp_set_nospace(sk);
	smp_mb__after_atomic(); /* msk->flags is changed by ग_लिखो_space cb */
	अगर (sk_stream_is_ग_लिखोable(sk))
		वापस EPOLLOUT | EPOLLWRNORM;

	वापस 0;
पूर्ण

अटल __poll_t mptcp_poll(काष्ठा file *file, काष्ठा socket *sock,
			   काष्ठा poll_table_काष्ठा *रुको)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा mptcp_sock *msk;
	__poll_t mask = 0;
	पूर्णांक state;

	msk = mptcp_sk(sk);
	sock_poll_रुको(file, sock, रुको);

	state = inet_sk_state_load(sk);
	pr_debug("msk=%p state=%d flags=%lx", msk, state, msk->flags);
	अगर (state == TCP_LISTEN)
		वापस mptcp_check_पढ़ोable(msk);

	अगर (state != TCP_SYN_SENT && state != TCP_SYN_RECV) अणु
		mask |= mptcp_check_पढ़ोable(msk);
		mask |= mptcp_check_ग_लिखोable(msk);
	पूर्ण
	अगर (sk->sk_shutकरोwn == SHUTDOWN_MASK || state == TCP_CLOSE)
		mask |= EPOLLHUP;
	अगर (sk->sk_shutकरोwn & RCV_SHUTDOWN)
		mask |= EPOLLIN | EPOLLRDNORM | EPOLLRDHUP;

	/* This barrier is coupled with smp_wmb() in tcp_reset() */
	smp_rmb();
	अगर (sk->sk_err)
		mask |= EPOLLERR;

	वापस mask;
पूर्ण

अटल स्थिर काष्ठा proto_ops mptcp_stream_ops = अणु
	.family		   = PF_INET,
	.owner		   = THIS_MODULE,
	.release	   = inet_release,
	.bind		   = mptcp_bind,
	.connect	   = mptcp_stream_connect,
	.socketpair	   = sock_no_socketpair,
	.accept		   = mptcp_stream_accept,
	.getname	   = inet_getname,
	.poll		   = mptcp_poll,
	.ioctl		   = inet_ioctl,
	.gettstamp	   = sock_gettstamp,
	.listen		   = mptcp_listen,
	.shutकरोwn	   = inet_shutकरोwn,
	.setsockopt	   = sock_common_setsockopt,
	.माला_लोockopt	   = sock_common_माला_लोockopt,
	.sendmsg	   = inet_sendmsg,
	.recvmsg	   = inet_recvmsg,
	.mmap		   = sock_no_mmap,
	.sendpage	   = inet_sendpage,
पूर्ण;

अटल काष्ठा inet_protosw mptcp_protosw = अणु
	.type		= SOCK_STREAM,
	.protocol	= IPPROTO_MPTCP,
	.prot		= &mptcp_prot,
	.ops		= &mptcp_stream_ops,
	.flags		= INET_PROTOSW_ICSK,
पूर्ण;

अटल पूर्णांक mptcp_napi_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा mptcp_delegated_action *delegated;
	काष्ठा mptcp_subflow_context *subflow;
	पूर्णांक work_करोne = 0;

	delegated = container_of(napi, काष्ठा mptcp_delegated_action, napi);
	जबतक ((subflow = mptcp_subflow_delegated_next(delegated)) != शून्य) अणु
		काष्ठा sock *ssk = mptcp_subflow_tcp_sock(subflow);

		bh_lock_sock_nested(ssk);
		अगर (!sock_owned_by_user(ssk) &&
		    mptcp_subflow_has_delegated_action(subflow))
			mptcp_subflow_process_delegated(ssk);
		/* ... अन्यथाwhere tcp_release_cb_override alपढ़ोy processed
		 * the action or will करो at next release_sock().
		 * In both हाल must dequeue the subflow here - on the same
		 * CPU that scheduled it.
		 */
		bh_unlock_sock(ssk);
		sock_put(ssk);

		अगर (++work_करोne == budget)
			वापस budget;
	पूर्ण

	/* always provide a 0 'work_done' argument, so that napi_complete_करोne
	 * will not try accessing the शून्य napi->dev ptr
	 */
	napi_complete_करोne(napi, 0);
	वापस work_करोne;
पूर्ण

व्योम __init mptcp_proto_init(व्योम)
अणु
	काष्ठा mptcp_delegated_action *delegated;
	पूर्णांक cpu;

	mptcp_prot.h.hashinfo = tcp_prot.h.hashinfo;

	अगर (percpu_counter_init(&mptcp_sockets_allocated, 0, GFP_KERNEL))
		panic("Failed to allocate MPTCP pcpu counter\n");

	init_dummy_netdev(&mptcp_napi_dev);
	क्रम_each_possible_cpu(cpu) अणु
		delegated = per_cpu_ptr(&mptcp_delegated_actions, cpu);
		INIT_LIST_HEAD(&delegated->head);
		netअगर_tx_napi_add(&mptcp_napi_dev, &delegated->napi, mptcp_napi_poll,
				  NAPI_POLL_WEIGHT);
		napi_enable(&delegated->napi);
	पूर्ण

	mptcp_subflow_init();
	mptcp_pm_init();
	mptcp_token_init();

	अगर (proto_रेजिस्टर(&mptcp_prot, 1) != 0)
		panic("Failed to register MPTCP proto.\n");

	inet_रेजिस्टर_protosw(&mptcp_protosw);

	BUILD_BUG_ON(माप(काष्ठा mptcp_skb_cb) > माप_field(काष्ठा sk_buff, cb));
पूर्ण

#अगर IS_ENABLED(CONFIG_MPTCP_IPV6)
अटल स्थिर काष्ठा proto_ops mptcp_v6_stream_ops = अणु
	.family		   = PF_INET6,
	.owner		   = THIS_MODULE,
	.release	   = inet6_release,
	.bind		   = mptcp_bind,
	.connect	   = mptcp_stream_connect,
	.socketpair	   = sock_no_socketpair,
	.accept		   = mptcp_stream_accept,
	.getname	   = inet6_getname,
	.poll		   = mptcp_poll,
	.ioctl		   = inet6_ioctl,
	.gettstamp	   = sock_gettstamp,
	.listen		   = mptcp_listen,
	.shutकरोwn	   = inet_shutकरोwn,
	.setsockopt	   = sock_common_setsockopt,
	.माला_लोockopt	   = sock_common_माला_लोockopt,
	.sendmsg	   = inet6_sendmsg,
	.recvmsg	   = inet6_recvmsg,
	.mmap		   = sock_no_mmap,
	.sendpage	   = inet_sendpage,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	   = inet6_compat_ioctl,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा proto mptcp_v6_prot;

अटल व्योम mptcp_v6_destroy(काष्ठा sock *sk)
अणु
	mptcp_destroy(sk);
	inet6_destroy_sock(sk);
पूर्ण

अटल काष्ठा inet_protosw mptcp_v6_protosw = अणु
	.type		= SOCK_STREAM,
	.protocol	= IPPROTO_MPTCP,
	.prot		= &mptcp_v6_prot,
	.ops		= &mptcp_v6_stream_ops,
	.flags		= INET_PROTOSW_ICSK,
पूर्ण;

पूर्णांक __init mptcp_proto_v6_init(व्योम)
अणु
	पूर्णांक err;

	mptcp_v6_prot = mptcp_prot;
	म_नकल(mptcp_v6_prot.name, "MPTCPv6");
	mptcp_v6_prot.slab = शून्य;
	mptcp_v6_prot.destroy = mptcp_v6_destroy;
	mptcp_v6_prot.obj_size = माप(काष्ठा mptcp6_sock);

	err = proto_रेजिस्टर(&mptcp_v6_prot, 1);
	अगर (err)
		वापस err;

	err = inet6_रेजिस्टर_protosw(&mptcp_v6_protosw);
	अगर (err)
		proto_unरेजिस्टर(&mptcp_v6_prot);

	वापस err;
पूर्ण
#पूर्ण_अगर
