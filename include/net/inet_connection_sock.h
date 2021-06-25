<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * NET		Generic infraकाष्ठाure क्रम INET connection oriented protocols.
 *
 *		Definitions क्रम inet_connection_sock 
 *
 * Authors:	Many people, see the TCP sources
 *
 * 		From code originally in TCP
 */
#अगर_अघोषित _INET_CONNECTION_SOCK_H
#घोषणा _INET_CONNECTION_SOCK_H

#समावेश <linux/compiler.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/poll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sockptr.h>

#समावेश <net/inet_sock.h>
#समावेश <net/request_sock.h>

/* Cancel समयrs, when they are not required. */
#अघोषित INET_CSK_CLEAR_TIMERS

काष्ठा inet_bind_bucket;
काष्ठा tcp_congestion_ops;

/*
 * Poपूर्णांकers to address related TCP functions
 * (i.e. things that depend on the address family)
 */
काष्ठा inet_connection_sock_af_ops अणु
	पूर्णांक	    (*queue_xmit)(काष्ठा sock *sk, काष्ठा sk_buff *skb, काष्ठा flowi *fl);
	व्योम	    (*send_check)(काष्ठा sock *sk, काष्ठा sk_buff *skb);
	पूर्णांक	    (*rebuild_header)(काष्ठा sock *sk);
	व्योम	    (*sk_rx_dst_set)(काष्ठा sock *sk, स्थिर काष्ठा sk_buff *skb);
	पूर्णांक	    (*conn_request)(काष्ठा sock *sk, काष्ठा sk_buff *skb);
	काष्ठा sock *(*syn_recv_sock)(स्थिर काष्ठा sock *sk, काष्ठा sk_buff *skb,
				      काष्ठा request_sock *req,
				      काष्ठा dst_entry *dst,
				      काष्ठा request_sock *req_unhash,
				      bool *own_req);
	u16	    net_header_len;
	u16	    net_frag_header_len;
	u16	    sockaddr_len;
	पूर्णांक	    (*setsockopt)(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname,
				  sockptr_t optval, अचिन्हित पूर्णांक optlen);
	पूर्णांक	    (*माला_लोockopt)(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname,
				  अक्षर __user *optval, पूर्णांक __user *optlen);
	व्योम	    (*addr2sockaddr)(काष्ठा sock *sk, काष्ठा sockaddr *);
	व्योम	    (*mtu_reduced)(काष्ठा sock *sk);
पूर्ण;

/** inet_connection_sock - INET connection oriented sock
 *
 * @icsk_accept_queue:	   FIFO of established children
 * @icsk_bind_hash:	   Bind node
 * @icsk_समयout:	   Timeout
 * @icsk_retransmit_समयr: Resend (no ack)
 * @icsk_rto:		   Retransmit समयout
 * @icsk_pmtu_cookie	   Last pmtu seen by socket
 * @icsk_ca_ops		   Pluggable congestion control hook
 * @icsk_af_ops		   Operations which are AF_INETअणु4,6पूर्ण specअगरic
 * @icsk_ulp_ops	   Pluggable ULP control hook
 * @icsk_ulp_data	   ULP निजी data
 * @icsk_clean_acked	   Clean acked data hook
 * @icsk_listen_portaddr_node	hash to the portaddr listener hashtable
 * @icsk_ca_state:	   Congestion control state
 * @icsk_retransmits:	   Number of unrecovered [RTO] समयouts
 * @icsk_pending:	   Scheduled समयr event
 * @icsk_backoff:	   Backoff
 * @icsk_syn_retries:      Number of allowed SYN (or equivalent) retries
 * @icsk_probes_out:	   unanswered 0 winकरोw probes
 * @icsk_ext_hdr_len:	   Network protocol overhead (IP/IPv6 options)
 * @icsk_ack:		   Delayed ACK control data
 * @icsk_mtup;		   MTU probing control data
 * @icsk_probes_tstamp:    Probe बारtamp (cleared by non-zero winकरोw ack)
 * @icsk_user_समयout:	   TCP_USER_TIMEOUT value
 */
काष्ठा inet_connection_sock अणु
	/* inet_sock has to be the first member! */
	काष्ठा inet_sock	  icsk_inet;
	काष्ठा request_sock_queue icsk_accept_queue;
	काष्ठा inet_bind_bucket	  *icsk_bind_hash;
	अचिन्हित दीर्घ		  icsk_समयout;
 	काष्ठा समयr_list	  icsk_retransmit_समयr;
 	काष्ठा समयr_list	  icsk_delack_समयr;
	__u32			  icsk_rto;
	__u32                     icsk_rto_min;
	__u32                     icsk_delack_max;
	__u32			  icsk_pmtu_cookie;
	स्थिर काष्ठा tcp_congestion_ops *icsk_ca_ops;
	स्थिर काष्ठा inet_connection_sock_af_ops *icsk_af_ops;
	स्थिर काष्ठा tcp_ulp_ops  *icsk_ulp_ops;
	व्योम __rcu		  *icsk_ulp_data;
	व्योम (*icsk_clean_acked)(काष्ठा sock *sk, u32 acked_seq);
	काष्ठा hlist_node         icsk_listen_portaddr_node;
	अचिन्हित पूर्णांक		  (*icsk_sync_mss)(काष्ठा sock *sk, u32 pmtu);
	__u8			  icsk_ca_state:5,
				  icsk_ca_initialized:1,
				  icsk_ca_setsockopt:1,
				  icsk_ca_dst_locked:1;
	__u8			  icsk_retransmits;
	__u8			  icsk_pending;
	__u8			  icsk_backoff;
	__u8			  icsk_syn_retries;
	__u8			  icsk_probes_out;
	__u16			  icsk_ext_hdr_len;
	काष्ठा अणु
		__u8		  pending;	 /* ACK is pending			   */
		__u8		  quick;	 /* Scheduled number of quick acks	   */
		__u8		  pingpong;	 /* The session is पूर्णांकeractive		   */
		__u8		  retry;	 /* Number of attempts			   */
		__u32		  ato;		 /* Predicted tick of soft घड़ी	   */
		अचिन्हित दीर्घ	  समयout;	 /* Currently scheduled समयout		   */
		__u32		  lrcvसमय;	 /* बारtamp of last received data packet */
		__u16		  last_seg_size; /* Size of last incoming segment	   */
		__u16		  rcv_mss;	 /* MSS used क्रम delayed ACK decisions	   */
	पूर्ण icsk_ack;
	काष्ठा अणु
		/* Range of MTUs to search */
		पूर्णांक		  search_high;
		पूर्णांक		  search_low;

		/* Inक्रमmation on the current probe. */
		u32		  probe_size:31,
		/* Is the MTUP feature enabled क्रम this connection? */
				  enabled:1;

		u32		  probe_बारtamp;
	पूर्ण icsk_mtup;
	u32			  icsk_probes_tstamp;
	u32			  icsk_user_समयout;

	u64			  icsk_ca_priv[104 / माप(u64)];
#घोषणा ICSK_CA_PRIV_SIZE      (13 * माप(u64))
पूर्ण;

#घोषणा ICSK_TIME_RETRANS	1	/* Retransmit समयr */
#घोषणा ICSK_TIME_DACK		2	/* Delayed ack समयr */
#घोषणा ICSK_TIME_PROBE0	3	/* Zero winकरोw probe समयr */
#घोषणा ICSK_TIME_LOSS_PROBE	5	/* Tail loss probe समयr */
#घोषणा ICSK_TIME_REO_TIMEOUT	6	/* Reordering समयr */

अटल अंतरभूत काष्ठा inet_connection_sock *inet_csk(स्थिर काष्ठा sock *sk)
अणु
	वापस (काष्ठा inet_connection_sock *)sk;
पूर्ण

अटल अंतरभूत व्योम *inet_csk_ca(स्थिर काष्ठा sock *sk)
अणु
	वापस (व्योम *)inet_csk(sk)->icsk_ca_priv;
पूर्ण

काष्ठा sock *inet_csk_clone_lock(स्थिर काष्ठा sock *sk,
				 स्थिर काष्ठा request_sock *req,
				 स्थिर gfp_t priority);

क्रमागत inet_csk_ack_state_t अणु
	ICSK_ACK_SCHED	= 1,
	ICSK_ACK_TIMER  = 2,
	ICSK_ACK_PUSHED = 4,
	ICSK_ACK_PUSHED2 = 8,
	ICSK_ACK_NOW = 16	/* Send the next ACK immediately (once) */
पूर्ण;

व्योम inet_csk_init_xmit_समयrs(काष्ठा sock *sk,
			       व्योम (*retransmit_handler)(काष्ठा समयr_list *),
			       व्योम (*delack_handler)(काष्ठा समयr_list *),
			       व्योम (*keepalive_handler)(काष्ठा समयr_list *));
व्योम inet_csk_clear_xmit_समयrs(काष्ठा sock *sk);

अटल अंतरभूत व्योम inet_csk_schedule_ack(काष्ठा sock *sk)
अणु
	inet_csk(sk)->icsk_ack.pending |= ICSK_ACK_SCHED;
पूर्ण

अटल अंतरभूत पूर्णांक inet_csk_ack_scheduled(स्थिर काष्ठा sock *sk)
अणु
	वापस inet_csk(sk)->icsk_ack.pending & ICSK_ACK_SCHED;
पूर्ण

अटल अंतरभूत व्योम inet_csk_delack_init(काष्ठा sock *sk)
अणु
	स_रखो(&inet_csk(sk)->icsk_ack, 0, माप(inet_csk(sk)->icsk_ack));
पूर्ण

व्योम inet_csk_delete_keepalive_समयr(काष्ठा sock *sk);
व्योम inet_csk_reset_keepalive_समयr(काष्ठा sock *sk, अचिन्हित दीर्घ समयout);

अटल अंतरभूत व्योम inet_csk_clear_xmit_समयr(काष्ठा sock *sk, स्थिर पूर्णांक what)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);

	अगर (what == ICSK_TIME_RETRANS || what == ICSK_TIME_PROBE0) अणु
		icsk->icsk_pending = 0;
#अगर_घोषित INET_CSK_CLEAR_TIMERS
		sk_stop_समयr(sk, &icsk->icsk_retransmit_समयr);
#पूर्ण_अगर
	पूर्ण अन्यथा अगर (what == ICSK_TIME_DACK) अणु
		icsk->icsk_ack.pending = 0;
		icsk->icsk_ack.retry = 0;
#अगर_घोषित INET_CSK_CLEAR_TIMERS
		sk_stop_समयr(sk, &icsk->icsk_delack_समयr);
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		pr_debug("inet_csk BUG: unknown timer value\n");
	पूर्ण
पूर्ण

/*
 *	Reset the retransmission समयr
 */
अटल अंतरभूत व्योम inet_csk_reset_xmit_समयr(काष्ठा sock *sk, स्थिर पूर्णांक what,
					     अचिन्हित दीर्घ when,
					     स्थिर अचिन्हित दीर्घ max_when)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);

	अगर (when > max_when) अणु
		pr_debug("reset_xmit_timer: sk=%p %d when=0x%lx, caller=%p\n",
			 sk, what, when, (व्योम *)_THIS_IP_);
		when = max_when;
	पूर्ण

	अगर (what == ICSK_TIME_RETRANS || what == ICSK_TIME_PROBE0 ||
	    what == ICSK_TIME_LOSS_PROBE || what == ICSK_TIME_REO_TIMEOUT) अणु
		icsk->icsk_pending = what;
		icsk->icsk_समयout = jअगरfies + when;
		sk_reset_समयr(sk, &icsk->icsk_retransmit_समयr, icsk->icsk_समयout);
	पूर्ण अन्यथा अगर (what == ICSK_TIME_DACK) अणु
		icsk->icsk_ack.pending |= ICSK_ACK_TIMER;
		icsk->icsk_ack.समयout = jअगरfies + when;
		sk_reset_समयr(sk, &icsk->icsk_delack_समयr, icsk->icsk_ack.समयout);
	पूर्ण अन्यथा अणु
		pr_debug("inet_csk BUG: unknown timer value\n");
	पूर्ण
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
inet_csk_rto_backoff(स्थिर काष्ठा inet_connection_sock *icsk,
		     अचिन्हित दीर्घ max_when)
अणु
        u64 when = (u64)icsk->icsk_rto << icsk->icsk_backoff;

        वापस (अचिन्हित दीर्घ)min_t(u64, when, max_when);
पूर्ण

काष्ठा sock *inet_csk_accept(काष्ठा sock *sk, पूर्णांक flags, पूर्णांक *err, bool kern);

पूर्णांक inet_csk_get_port(काष्ठा sock *sk, अचिन्हित लघु snum);

काष्ठा dst_entry *inet_csk_route_req(स्थिर काष्ठा sock *sk, काष्ठा flowi4 *fl4,
				     स्थिर काष्ठा request_sock *req);
काष्ठा dst_entry *inet_csk_route_child_sock(स्थिर काष्ठा sock *sk,
					    काष्ठा sock *newsk,
					    स्थिर काष्ठा request_sock *req);

काष्ठा sock *inet_csk_reqsk_queue_add(काष्ठा sock *sk,
				      काष्ठा request_sock *req,
				      काष्ठा sock *child);
व्योम inet_csk_reqsk_queue_hash_add(काष्ठा sock *sk, काष्ठा request_sock *req,
				   अचिन्हित दीर्घ समयout);
काष्ठा sock *inet_csk_complete_hashdance(काष्ठा sock *sk, काष्ठा sock *child,
					 काष्ठा request_sock *req,
					 bool own_req);

अटल अंतरभूत व्योम inet_csk_reqsk_queue_added(काष्ठा sock *sk)
अणु
	reqsk_queue_added(&inet_csk(sk)->icsk_accept_queue);
पूर्ण

अटल अंतरभूत पूर्णांक inet_csk_reqsk_queue_len(स्थिर काष्ठा sock *sk)
अणु
	वापस reqsk_queue_len(&inet_csk(sk)->icsk_accept_queue);
पूर्ण

अटल अंतरभूत पूर्णांक inet_csk_reqsk_queue_is_full(स्थिर काष्ठा sock *sk)
अणु
	वापस inet_csk_reqsk_queue_len(sk) >= sk->sk_max_ack_backlog;
पूर्ण

bool inet_csk_reqsk_queue_drop(काष्ठा sock *sk, काष्ठा request_sock *req);
व्योम inet_csk_reqsk_queue_drop_and_put(काष्ठा sock *sk, काष्ठा request_sock *req);

अटल अंतरभूत व्योम inet_csk_prepare_क्रम_destroy_sock(काष्ठा sock *sk)
अणु
	/* The below has to be करोne to allow calling inet_csk_destroy_sock */
	sock_set_flag(sk, SOCK_DEAD);
	percpu_counter_inc(sk->sk_prot->orphan_count);
पूर्ण

व्योम inet_csk_destroy_sock(काष्ठा sock *sk);
व्योम inet_csk_prepare_क्रमced_बंद(काष्ठा sock *sk);

/*
 * LISTEN is a special हाल क्रम poll..
 */
अटल अंतरभूत __poll_t inet_csk_listen_poll(स्थिर काष्ठा sock *sk)
अणु
	वापस !reqsk_queue_empty(&inet_csk(sk)->icsk_accept_queue) ?
			(EPOLLIN | EPOLLRDNORM) : 0;
पूर्ण

पूर्णांक inet_csk_listen_start(काष्ठा sock *sk, पूर्णांक backlog);
व्योम inet_csk_listen_stop(काष्ठा sock *sk);

व्योम inet_csk_addr2sockaddr(काष्ठा sock *sk, काष्ठा sockaddr *uaddr);

/* update the fast reuse flag when adding a socket */
व्योम inet_csk_update_fastreuse(काष्ठा inet_bind_bucket *tb,
			       काष्ठा sock *sk);

काष्ठा dst_entry *inet_csk_update_pmtu(काष्ठा sock *sk, u32 mtu);

#घोषणा TCP_PINGPONG_THRESH	3

अटल अंतरभूत व्योम inet_csk_enter_pingpong_mode(काष्ठा sock *sk)
अणु
	inet_csk(sk)->icsk_ack.pingpong = TCP_PINGPONG_THRESH;
पूर्ण

अटल अंतरभूत व्योम inet_csk_निकास_pingpong_mode(काष्ठा sock *sk)
अणु
	inet_csk(sk)->icsk_ack.pingpong = 0;
पूर्ण

अटल अंतरभूत bool inet_csk_in_pingpong_mode(काष्ठा sock *sk)
अणु
	वापस inet_csk(sk)->icsk_ack.pingpong >= TCP_PINGPONG_THRESH;
पूर्ण

अटल अंतरभूत व्योम inet_csk_inc_pingpong_cnt(काष्ठा sock *sk)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);

	अगर (icsk->icsk_ack.pingpong < U8_MAX)
		icsk->icsk_ack.pingpong++;
पूर्ण

अटल अंतरभूत bool inet_csk_has_ulp(काष्ठा sock *sk)
अणु
	वापस inet_sk(sk)->is_icsk && !!inet_csk(sk)->icsk_ulp_ops;
पूर्ण

#पूर्ण_अगर /* _INET_CONNECTION_SOCK_H */
