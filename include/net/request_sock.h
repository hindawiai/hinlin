<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * NET		Generic infraकाष्ठाure क्रम Network protocols.
 *
 *		Definitions क्रम request_sock
 *
 * Authors:	Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
 *
 * 		From code originally in include/net/tcp.h
 */
#अगर_अघोषित _REQUEST_SOCK_H
#घोषणा _REQUEST_SOCK_H

#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>
#समावेश <linux/bug.h>
#समावेश <linux/refcount.h>

#समावेश <net/sock.h>

काष्ठा request_sock;
काष्ठा sk_buff;
काष्ठा dst_entry;
काष्ठा proto;

काष्ठा request_sock_ops अणु
	पूर्णांक		family;
	अचिन्हित पूर्णांक	obj_size;
	काष्ठा kmem_cache	*slab;
	अक्षर		*slab_name;
	पूर्णांक		(*rtx_syn_ack)(स्थिर काष्ठा sock *sk,
				       काष्ठा request_sock *req);
	व्योम		(*send_ack)(स्थिर काष्ठा sock *sk, काष्ठा sk_buff *skb,
				    काष्ठा request_sock *req);
	व्योम		(*send_reset)(स्थिर काष्ठा sock *sk,
				      काष्ठा sk_buff *skb);
	व्योम		(*deकाष्ठाor)(काष्ठा request_sock *req);
	व्योम		(*syn_ack_समयout)(स्थिर काष्ठा request_sock *req);
पूर्ण;

पूर्णांक inet_rtx_syn_ack(स्थिर काष्ठा sock *parent, काष्ठा request_sock *req);

काष्ठा saved_syn अणु
	u32 mac_hdrlen;
	u32 network_hdrlen;
	u32 tcp_hdrlen;
	u8 data[];
पूर्ण;

/* काष्ठा request_sock - mini sock to represent a connection request
 */
काष्ठा request_sock अणु
	काष्ठा sock_common		__req_common;
#घोषणा rsk_refcnt			__req_common.skc_refcnt
#घोषणा rsk_hash			__req_common.skc_hash
#घोषणा rsk_listener			__req_common.skc_listener
#घोषणा rsk_winकरोw_clamp		__req_common.skc_winकरोw_clamp
#घोषणा rsk_rcv_wnd			__req_common.skc_rcv_wnd

	काष्ठा request_sock		*dl_next;
	u16				mss;
	u8				num_retrans; /* number of retransmits */
	u8				syncookie:1; /* syncookie: encode tcpopts in बारtamp */
	u8				num_समयout:7; /* number of समयouts */
	u32				ts_recent;
	काष्ठा समयr_list		rsk_समयr;
	स्थिर काष्ठा request_sock_ops	*rsk_ops;
	काष्ठा sock			*sk;
	काष्ठा saved_syn		*saved_syn;
	u32				secid;
	u32				peer_secid;
पूर्ण;

अटल अंतरभूत काष्ठा request_sock *inet_reqsk(स्थिर काष्ठा sock *sk)
अणु
	वापस (काष्ठा request_sock *)sk;
पूर्ण

अटल अंतरभूत काष्ठा sock *req_to_sk(काष्ठा request_sock *req)
अणु
	वापस (काष्ठा sock *)req;
पूर्ण

अटल अंतरभूत काष्ठा request_sock *
reqsk_alloc(स्थिर काष्ठा request_sock_ops *ops, काष्ठा sock *sk_listener,
	    bool attach_listener)
अणु
	काष्ठा request_sock *req;

	req = kmem_cache_alloc(ops->slab, GFP_ATOMIC | __GFP_NOWARN);
	अगर (!req)
		वापस शून्य;
	req->rsk_listener = शून्य;
	अगर (attach_listener) अणु
		अगर (unlikely(!refcount_inc_not_zero(&sk_listener->sk_refcnt))) अणु
			kmem_cache_मुक्त(ops->slab, req);
			वापस शून्य;
		पूर्ण
		req->rsk_listener = sk_listener;
	पूर्ण
	req->rsk_ops = ops;
	req_to_sk(req)->sk_prot = sk_listener->sk_prot;
	sk_node_init(&req_to_sk(req)->sk_node);
	sk_tx_queue_clear(req_to_sk(req));
	req->saved_syn = शून्य;
	req->num_समयout = 0;
	req->num_retrans = 0;
	req->sk = शून्य;
	refcount_set(&req->rsk_refcnt, 0);

	वापस req;
पूर्ण

अटल अंतरभूत व्योम __reqsk_मुक्त(काष्ठा request_sock *req)
अणु
	req->rsk_ops->deकाष्ठाor(req);
	अगर (req->rsk_listener)
		sock_put(req->rsk_listener);
	kमुक्त(req->saved_syn);
	kmem_cache_मुक्त(req->rsk_ops->slab, req);
पूर्ण

अटल अंतरभूत व्योम reqsk_मुक्त(काष्ठा request_sock *req)
अणु
	WARN_ON_ONCE(refcount_पढ़ो(&req->rsk_refcnt) != 0);
	__reqsk_मुक्त(req);
पूर्ण

अटल अंतरभूत व्योम reqsk_put(काष्ठा request_sock *req)
अणु
	अगर (refcount_dec_and_test(&req->rsk_refcnt))
		reqsk_मुक्त(req);
पूर्ण

/*
 * For a TCP Fast Open listener -
 *	lock - protects the access to all the reqsk, which is co-owned by
 *		the listener and the child socket.
 *	qlen - pending TFO requests (still in TCP_SYN_RECV).
 *	max_qlen - max TFO reqs allowed beक्रमe TFO is disabled.
 *
 *	XXX (TFO) - ideally these fields can be made as part of "listen_sock"
 *	काष्ठाure above. But there is some implementation dअगरficulty due to
 *	listen_sock being part of request_sock_queue hence will be मुक्तd when
 *	a listener is stopped. But TFO related fields may जारी to be
 *	accessed even after a listener is बंदd, until its sk_refcnt drops
 *	to 0 implying no more outstanding TFO reqs. One solution is to keep
 *	listen_opt around until	sk_refcnt drops to 0. But there is some other
 *	complनिकासy that needs to be resolved. E.g., a listener can be disabled
 *	temporarily through shutकरोwn()->tcp_disconnect(), and re-enabled later.
 */
काष्ठा fastखोलो_queue अणु
	काष्ठा request_sock	*rskq_rst_head; /* Keep track of past TFO */
	काष्ठा request_sock	*rskq_rst_tail; /* requests that caused RST.
						 * This is part of the defense
						 * against spoofing attack.
						 */
	spinlock_t	lock;
	पूर्णांक		qlen;		/* # of pending (TCP_SYN_RECV) reqs */
	पूर्णांक		max_qlen;	/* != 0 अगरf TFO is currently enabled */

	काष्ठा tcp_fastखोलो_context __rcu *ctx; /* cipher context क्रम cookie */
पूर्ण;

/** काष्ठा request_sock_queue - queue of request_socks
 *
 * @rskq_accept_head - FIFO head of established children
 * @rskq_accept_tail - FIFO tail of established children
 * @rskq_defer_accept - User रुकोs क्रम some data after accept()
 *
 */
काष्ठा request_sock_queue अणु
	spinlock_t		rskq_lock;
	u8			rskq_defer_accept;

	u32			synflood_warned;
	atomic_t		qlen;
	atomic_t		young;

	काष्ठा request_sock	*rskq_accept_head;
	काष्ठा request_sock	*rskq_accept_tail;
	काष्ठा fastखोलो_queue	fastखोलोq;  /* Check max_qlen != 0 to determine
					     * अगर TFO is enabled.
					     */
पूर्ण;

व्योम reqsk_queue_alloc(काष्ठा request_sock_queue *queue);

व्योम reqsk_fastखोलो_हटाओ(काष्ठा sock *sk, काष्ठा request_sock *req,
			   bool reset);

अटल अंतरभूत bool reqsk_queue_empty(स्थिर काष्ठा request_sock_queue *queue)
अणु
	वापस READ_ONCE(queue->rskq_accept_head) == शून्य;
पूर्ण

अटल अंतरभूत काष्ठा request_sock *reqsk_queue_हटाओ(काष्ठा request_sock_queue *queue,
						      काष्ठा sock *parent)
अणु
	काष्ठा request_sock *req;

	spin_lock_bh(&queue->rskq_lock);
	req = queue->rskq_accept_head;
	अगर (req) अणु
		sk_acceptq_हटाओd(parent);
		WRITE_ONCE(queue->rskq_accept_head, req->dl_next);
		अगर (queue->rskq_accept_head == शून्य)
			queue->rskq_accept_tail = शून्य;
	पूर्ण
	spin_unlock_bh(&queue->rskq_lock);
	वापस req;
पूर्ण

अटल अंतरभूत व्योम reqsk_queue_हटाओd(काष्ठा request_sock_queue *queue,
				       स्थिर काष्ठा request_sock *req)
अणु
	अगर (req->num_समयout == 0)
		atomic_dec(&queue->young);
	atomic_dec(&queue->qlen);
पूर्ण

अटल अंतरभूत व्योम reqsk_queue_added(काष्ठा request_sock_queue *queue)
अणु
	atomic_inc(&queue->young);
	atomic_inc(&queue->qlen);
पूर्ण

अटल अंतरभूत पूर्णांक reqsk_queue_len(स्थिर काष्ठा request_sock_queue *queue)
अणु
	वापस atomic_पढ़ो(&queue->qlen);
पूर्ण

अटल अंतरभूत पूर्णांक reqsk_queue_len_young(स्थिर काष्ठा request_sock_queue *queue)
अणु
	वापस atomic_पढ़ो(&queue->young);
पूर्ण

#पूर्ण_अगर /* _REQUEST_SOCK_H */
