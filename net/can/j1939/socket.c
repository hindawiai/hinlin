<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2010-2011 EIA Electronics,
//                         Pieter Beyens <pieter.beyens@eia.be>
// Copyright (c) 2010-2011 EIA Electronics,
//                         Kurt Van Dijck <kurt.van.dijck@eia.be>
// Copyright (c) 2018 Protonic,
//                         Robin van der Gracht <robin@protonic.nl>
// Copyright (c) 2017-2019 Pengutronix,
//                         Marc Kleine-Budde <kernel@pengutronix.de>
// Copyright (c) 2017-2019 Pengutronix,
//                         Oleksij Rempel <kernel@pengutronix.de>

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/can/can-ml.h>
#समावेश <linux/can/core.h>
#समावेश <linux/can/skb.h>
#समावेश <linux/errqueue.h>
#समावेश <linux/अगर_arp.h>

#समावेश "j1939-priv.h"

#घोषणा J1939_MIN_NAMELEN CAN_REQUIRED_SIZE(काष्ठा sockaddr_can, can_addr.j1939)

/* conversion function between काष्ठा sock::sk_priority from linux and
 * j1939 priority field
 */
अटल अंतरभूत priority_t j1939_prio(u32 sk_priority)
अणु
	sk_priority = min(sk_priority, 7U);

	वापस 7 - sk_priority;
पूर्ण

अटल अंतरभूत u32 j1939_to_sk_priority(priority_t prio)
अणु
	वापस 7 - prio;
पूर्ण

/* function to see अगर pgn is to be evaluated */
अटल अंतरभूत bool j1939_pgn_is_valid(pgn_t pgn)
अणु
	वापस pgn <= J1939_PGN_MAX;
पूर्ण

/* test function to aव्योम non-zero DA placeholder क्रम pdu1 pgn's */
अटल अंतरभूत bool j1939_pgn_is_clean_pdu(pgn_t pgn)
अणु
	अगर (j1939_pgn_is_pdu1(pgn))
		वापस !(pgn & 0xff);
	अन्यथा
		वापस true;
पूर्ण

अटल अंतरभूत व्योम j1939_sock_pending_add(काष्ठा sock *sk)
अणु
	काष्ठा j1939_sock *jsk = j1939_sk(sk);

	atomic_inc(&jsk->skb_pending);
पूर्ण

अटल पूर्णांक j1939_sock_pending_get(काष्ठा sock *sk)
अणु
	काष्ठा j1939_sock *jsk = j1939_sk(sk);

	वापस atomic_पढ़ो(&jsk->skb_pending);
पूर्ण

व्योम j1939_sock_pending_del(काष्ठा sock *sk)
अणु
	काष्ठा j1939_sock *jsk = j1939_sk(sk);

	/* atomic_dec_वापस वापसs the new value */
	अगर (!atomic_dec_वापस(&jsk->skb_pending))
		wake_up(&jsk->रुकोq);	/* no pending SKB's */
पूर्ण

अटल व्योम j1939_jsk_add(काष्ठा j1939_priv *priv, काष्ठा j1939_sock *jsk)
अणु
	jsk->state |= J1939_SOCK_BOUND;
	j1939_priv_get(priv);

	spin_lock_bh(&priv->j1939_socks_lock);
	list_add_tail(&jsk->list, &priv->j1939_socks);
	spin_unlock_bh(&priv->j1939_socks_lock);
पूर्ण

अटल व्योम j1939_jsk_del(काष्ठा j1939_priv *priv, काष्ठा j1939_sock *jsk)
अणु
	spin_lock_bh(&priv->j1939_socks_lock);
	list_del_init(&jsk->list);
	spin_unlock_bh(&priv->j1939_socks_lock);

	j1939_priv_put(priv);
	jsk->state &= ~J1939_SOCK_BOUND;
पूर्ण

अटल bool j1939_sk_queue_session(काष्ठा j1939_session *session)
अणु
	काष्ठा j1939_sock *jsk = j1939_sk(session->sk);
	bool empty;

	spin_lock_bh(&jsk->sk_session_queue_lock);
	empty = list_empty(&jsk->sk_session_queue);
	j1939_session_get(session);
	list_add_tail(&session->sk_session_queue_entry, &jsk->sk_session_queue);
	spin_unlock_bh(&jsk->sk_session_queue_lock);
	j1939_sock_pending_add(&jsk->sk);

	वापस empty;
पूर्ण

अटल काष्ठा
j1939_session *j1939_sk_get_incomplete_session(काष्ठा j1939_sock *jsk)
अणु
	काष्ठा j1939_session *session = शून्य;

	spin_lock_bh(&jsk->sk_session_queue_lock);
	अगर (!list_empty(&jsk->sk_session_queue)) अणु
		session = list_last_entry(&jsk->sk_session_queue,
					  काष्ठा j1939_session,
					  sk_session_queue_entry);
		अगर (session->total_queued_size == session->total_message_size)
			session = शून्य;
		अन्यथा
			j1939_session_get(session);
	पूर्ण
	spin_unlock_bh(&jsk->sk_session_queue_lock);

	वापस session;
पूर्ण

अटल व्योम j1939_sk_queue_drop_all(काष्ठा j1939_priv *priv,
				    काष्ठा j1939_sock *jsk, पूर्णांक err)
अणु
	काष्ठा j1939_session *session, *पंचांगp;

	netdev_dbg(priv->ndev, "%s: err: %i\n", __func__, err);
	spin_lock_bh(&jsk->sk_session_queue_lock);
	list_क्रम_each_entry_safe(session, पंचांगp, &jsk->sk_session_queue,
				 sk_session_queue_entry) अणु
		list_del_init(&session->sk_session_queue_entry);
		session->err = err;
		j1939_session_put(session);
	पूर्ण
	spin_unlock_bh(&jsk->sk_session_queue_lock);
पूर्ण

अटल व्योम j1939_sk_queue_activate_next_locked(काष्ठा j1939_session *session)
अणु
	काष्ठा j1939_sock *jsk;
	काष्ठा j1939_session *first;
	पूर्णांक err;

	/* RX-Session करोn't have a socket (yet) */
	अगर (!session->sk)
		वापस;

	jsk = j1939_sk(session->sk);
	lockdep_निश्चित_held(&jsk->sk_session_queue_lock);

	err = session->err;

	first = list_first_entry_or_null(&jsk->sk_session_queue,
					 काष्ठा j1939_session,
					 sk_session_queue_entry);

	/* Some अन्यथा has alपढ़ोy activated the next session */
	अगर (first != session)
		वापस;

activate_next:
	list_del_init(&first->sk_session_queue_entry);
	j1939_session_put(first);
	first = list_first_entry_or_null(&jsk->sk_session_queue,
					 काष्ठा j1939_session,
					 sk_session_queue_entry);
	अगर (!first)
		वापस;

	अगर (WARN_ON_ONCE(j1939_session_activate(first))) अणु
		first->err = -EBUSY;
		जाओ activate_next;
	पूर्ण अन्यथा अणु
		/* Give receiver some समय (arbitrary chosen) to recover */
		पूर्णांक समय_ms = 0;

		अगर (err)
			समय_ms = 10 + pअक्रमom_u32_max(16);

		j1939_tp_schedule_txसमयr(first, समय_ms);
	पूर्ण
पूर्ण

व्योम j1939_sk_queue_activate_next(काष्ठा j1939_session *session)
अणु
	काष्ठा j1939_sock *jsk;

	अगर (!session->sk)
		वापस;

	jsk = j1939_sk(session->sk);

	spin_lock_bh(&jsk->sk_session_queue_lock);
	j1939_sk_queue_activate_next_locked(session);
	spin_unlock_bh(&jsk->sk_session_queue_lock);
पूर्ण

अटल bool j1939_sk_match_dst(काष्ठा j1939_sock *jsk,
			       स्थिर काष्ठा j1939_sk_buff_cb *skcb)
अणु
	अगर ((jsk->state & J1939_SOCK_PROMISC))
		वापस true;

	/* Destination address filter */
	अगर (jsk->addr.src_name && skcb->addr.dst_name) अणु
		अगर (jsk->addr.src_name != skcb->addr.dst_name)
			वापस false;
	पूर्ण अन्यथा अणु
		/* receive (all sockets) अगर
		 * - all packages that match our bind() address
		 * - all broadcast on a socket अगर SO_BROADCAST
		 *   is set
		 */
		अगर (j1939_address_is_unicast(skcb->addr.da)) अणु
			अगर (jsk->addr.sa != skcb->addr.da)
				वापस false;
		पूर्ण अन्यथा अगर (!sock_flag(&jsk->sk, SOCK_BROADCAST)) अणु
			/* receiving broadcast without SO_BROADCAST
			 * flag is not allowed
			 */
			वापस false;
		पूर्ण
	पूर्ण

	/* Source address filter */
	अगर (jsk->state & J1939_SOCK_CONNECTED) अणु
		/* receive (all sockets) अगर
		 * - all packages that match our connect() name or address
		 */
		अगर (jsk->addr.dst_name && skcb->addr.src_name) अणु
			अगर (jsk->addr.dst_name != skcb->addr.src_name)
				वापस false;
		पूर्ण अन्यथा अणु
			अगर (jsk->addr.da != skcb->addr.sa)
				वापस false;
		पूर्ण
	पूर्ण

	/* PGN filter */
	अगर (j1939_pgn_is_valid(jsk->pgn_rx_filter) &&
	    jsk->pgn_rx_filter != skcb->addr.pgn)
		वापस false;

	वापस true;
पूर्ण

/* matches skb control buffer (addr) with a j1939 filter */
अटल bool j1939_sk_match_filter(काष्ठा j1939_sock *jsk,
				  स्थिर काष्ठा j1939_sk_buff_cb *skcb)
अणु
	स्थिर काष्ठा j1939_filter *f = jsk->filters;
	पूर्णांक nfilter = jsk->nfilters;

	अगर (!nfilter)
		/* receive all when no filters are asचिन्हित */
		वापस true;

	क्रम (; nfilter; ++f, --nfilter) अणु
		अगर ((skcb->addr.pgn & f->pgn_mask) != f->pgn)
			जारी;
		अगर ((skcb->addr.sa & f->addr_mask) != f->addr)
			जारी;
		अगर ((skcb->addr.src_name & f->name_mask) != f->name)
			जारी;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool j1939_sk_recv_match_one(काष्ठा j1939_sock *jsk,
				    स्थिर काष्ठा j1939_sk_buff_cb *skcb)
अणु
	अगर (!(jsk->state & J1939_SOCK_BOUND))
		वापस false;

	अगर (!j1939_sk_match_dst(jsk, skcb))
		वापस false;

	अगर (!j1939_sk_match_filter(jsk, skcb))
		वापस false;

	वापस true;
पूर्ण

अटल व्योम j1939_sk_recv_one(काष्ठा j1939_sock *jsk, काष्ठा sk_buff *oskb)
अणु
	स्थिर काष्ठा j1939_sk_buff_cb *oskcb = j1939_skb_to_cb(oskb);
	काष्ठा j1939_sk_buff_cb *skcb;
	काष्ठा sk_buff *skb;

	अगर (oskb->sk == &jsk->sk)
		वापस;

	अगर (!j1939_sk_recv_match_one(jsk, oskcb))
		वापस;

	skb = skb_clone(oskb, GFP_ATOMIC);
	अगर (!skb) अणु
		pr_warn("skb clone failed\n");
		वापस;
	पूर्ण
	can_skb_set_owner(skb, oskb->sk);

	skcb = j1939_skb_to_cb(skb);
	skcb->msg_flags &= ~(MSG_DONTROUTE);
	अगर (skb->sk)
		skcb->msg_flags |= MSG_DONTROUTE;

	अगर (sock_queue_rcv_skb(&jsk->sk, skb) < 0)
		kमुक्त_skb(skb);
पूर्ण

bool j1939_sk_recv_match(काष्ठा j1939_priv *priv, काष्ठा j1939_sk_buff_cb *skcb)
अणु
	काष्ठा j1939_sock *jsk;
	bool match = false;

	spin_lock_bh(&priv->j1939_socks_lock);
	list_क्रम_each_entry(jsk, &priv->j1939_socks, list) अणु
		match = j1939_sk_recv_match_one(jsk, skcb);
		अगर (match)
			अवरोध;
	पूर्ण
	spin_unlock_bh(&priv->j1939_socks_lock);

	वापस match;
पूर्ण

व्योम j1939_sk_recv(काष्ठा j1939_priv *priv, काष्ठा sk_buff *skb)
अणु
	काष्ठा j1939_sock *jsk;

	spin_lock_bh(&priv->j1939_socks_lock);
	list_क्रम_each_entry(jsk, &priv->j1939_socks, list) अणु
		j1939_sk_recv_one(jsk, skb);
	पूर्ण
	spin_unlock_bh(&priv->j1939_socks_lock);
पूर्ण

अटल व्योम j1939_sk_sock_deकाष्ठा(काष्ठा sock *sk)
अणु
	काष्ठा j1939_sock *jsk = j1939_sk(sk);

	/* This function will be call by the generic networking code, when then
	 * the socket is ultimately बंदd (sk->sk_deकाष्ठा).
	 *
	 * The race between
	 * - processing a received CAN frame
	 *   (can_receive -> j1939_can_recv)
	 *   and accessing j1939_priv
	 * ... and ...
	 * - closing a socket
	 *   (j1939_can_rx_unरेजिस्टर -> can_rx_unरेजिस्टर)
	 *   and calling the final j1939_priv_put()
	 *
	 * is aव्योमed by calling the final j1939_priv_put() from this
	 * RCU deferred cleanup call.
	 */
	अगर (jsk->priv) अणु
		j1939_priv_put(jsk->priv);
		jsk->priv = शून्य;
	पूर्ण

	/* call generic CAN sock deकाष्ठा */
	can_sock_deकाष्ठा(sk);
पूर्ण

अटल पूर्णांक j1939_sk_init(काष्ठा sock *sk)
अणु
	काष्ठा j1939_sock *jsk = j1939_sk(sk);

	/* Ensure that "sk" is first member in "struct j1939_sock", so that we
	 * can skip it during स_रखो().
	 */
	BUILD_BUG_ON(दुरत्व(काष्ठा j1939_sock, sk) != 0);
	स_रखो((व्योम *)jsk + माप(jsk->sk), 0x0,
	       माप(*jsk) - माप(jsk->sk));

	INIT_LIST_HEAD(&jsk->list);
	init_रुकोqueue_head(&jsk->रुकोq);
	jsk->sk.sk_priority = j1939_to_sk_priority(6);
	jsk->sk.sk_reuse = 1; /* per शेष */
	jsk->addr.sa = J1939_NO_ADDR;
	jsk->addr.da = J1939_NO_ADDR;
	jsk->addr.pgn = J1939_NO_PGN;
	jsk->pgn_rx_filter = J1939_NO_PGN;
	atomic_set(&jsk->skb_pending, 0);
	spin_lock_init(&jsk->sk_session_queue_lock);
	INIT_LIST_HEAD(&jsk->sk_session_queue);
	sk->sk_deकाष्ठा = j1939_sk_sock_deकाष्ठा;
	sk->sk_protocol = CAN_J1939;

	वापस 0;
पूर्ण

अटल पूर्णांक j1939_sk_sanity_check(काष्ठा sockaddr_can *addr, पूर्णांक len)
अणु
	अगर (!addr)
		वापस -EDESTADDRREQ;
	अगर (len < J1939_MIN_NAMELEN)
		वापस -EINVAL;
	अगर (addr->can_family != AF_CAN)
		वापस -EINVAL;
	अगर (!addr->can_अगरindex)
		वापस -ENODEV;
	अगर (j1939_pgn_is_valid(addr->can_addr.j1939.pgn) &&
	    !j1939_pgn_is_clean_pdu(addr->can_addr.j1939.pgn))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक j1939_sk_bind(काष्ठा socket *sock, काष्ठा sockaddr *uaddr, पूर्णांक len)
अणु
	काष्ठा sockaddr_can *addr = (काष्ठा sockaddr_can *)uaddr;
	काष्ठा j1939_sock *jsk = j1939_sk(sock->sk);
	काष्ठा j1939_priv *priv;
	काष्ठा sock *sk;
	काष्ठा net *net;
	पूर्णांक ret = 0;

	ret = j1939_sk_sanity_check(addr, len);
	अगर (ret)
		वापस ret;

	lock_sock(sock->sk);

	priv = jsk->priv;
	sk = sock->sk;
	net = sock_net(sk);

	/* Alपढ़ोy bound to an पूर्णांकerface? */
	अगर (jsk->state & J1939_SOCK_BOUND) अणु
		/* A re-bind() to a dअगरferent पूर्णांकerface is not
		 * supported.
		 */
		अगर (jsk->अगरindex != addr->can_अगरindex) अणु
			ret = -EINVAL;
			जाओ out_release_sock;
		पूर्ण

		/* drop old references */
		j1939_jsk_del(priv, jsk);
		j1939_local_ecu_put(priv, jsk->addr.src_name, jsk->addr.sa);
	पूर्ण अन्यथा अणु
		काष्ठा can_ml_priv *can_ml;
		काष्ठा net_device *ndev;

		ndev = dev_get_by_index(net, addr->can_अगरindex);
		अगर (!ndev) अणु
			ret = -ENODEV;
			जाओ out_release_sock;
		पूर्ण

		can_ml = can_get_ml_priv(ndev);
		अगर (!can_ml) अणु
			dev_put(ndev);
			ret = -ENODEV;
			जाओ out_release_sock;
		पूर्ण

		अगर (!(ndev->flags & IFF_UP)) अणु
			dev_put(ndev);
			ret = -ENETDOWN;
			जाओ out_release_sock;
		पूर्ण

		priv = j1939_netdev_start(ndev);
		dev_put(ndev);
		अगर (IS_ERR(priv)) अणु
			ret = PTR_ERR(priv);
			जाओ out_release_sock;
		पूर्ण

		jsk->अगरindex = addr->can_अगरindex;

		/* the corresponding j1939_priv_put() is called via
		 * sk->sk_deकाष्ठा, which poपूर्णांकs to j1939_sk_sock_deकाष्ठा()
		 */
		j1939_priv_get(priv);
		jsk->priv = priv;
	पूर्ण

	/* set शेष transmit pgn */
	अगर (j1939_pgn_is_valid(addr->can_addr.j1939.pgn))
		jsk->pgn_rx_filter = addr->can_addr.j1939.pgn;
	jsk->addr.src_name = addr->can_addr.j1939.name;
	jsk->addr.sa = addr->can_addr.j1939.addr;

	/* get new references */
	ret = j1939_local_ecu_get(priv, jsk->addr.src_name, jsk->addr.sa);
	अगर (ret) अणु
		j1939_netdev_stop(priv);
		जाओ out_release_sock;
	पूर्ण

	j1939_jsk_add(priv, jsk);

 out_release_sock: /* fall through */
	release_sock(sock->sk);

	वापस ret;
पूर्ण

अटल पूर्णांक j1939_sk_connect(काष्ठा socket *sock, काष्ठा sockaddr *uaddr,
			    पूर्णांक len, पूर्णांक flags)
अणु
	काष्ठा sockaddr_can *addr = (काष्ठा sockaddr_can *)uaddr;
	काष्ठा j1939_sock *jsk = j1939_sk(sock->sk);
	पूर्णांक ret = 0;

	ret = j1939_sk_sanity_check(addr, len);
	अगर (ret)
		वापस ret;

	lock_sock(sock->sk);

	/* bind() beक्रमe connect() is mandatory */
	अगर (!(jsk->state & J1939_SOCK_BOUND)) अणु
		ret = -EINVAL;
		जाओ out_release_sock;
	पूर्ण

	/* A connect() to a dअगरferent पूर्णांकerface is not supported. */
	अगर (jsk->अगरindex != addr->can_अगरindex) अणु
		ret = -EINVAL;
		जाओ out_release_sock;
	पूर्ण

	अगर (!addr->can_addr.j1939.name &&
	    addr->can_addr.j1939.addr == J1939_NO_ADDR &&
	    !sock_flag(&jsk->sk, SOCK_BROADCAST)) अणु
		/* broadcast, but SO_BROADCAST not set */
		ret = -EACCES;
		जाओ out_release_sock;
	पूर्ण

	jsk->addr.dst_name = addr->can_addr.j1939.name;
	jsk->addr.da = addr->can_addr.j1939.addr;

	अगर (j1939_pgn_is_valid(addr->can_addr.j1939.pgn))
		jsk->addr.pgn = addr->can_addr.j1939.pgn;

	jsk->state |= J1939_SOCK_CONNECTED;

 out_release_sock: /* fall through */
	release_sock(sock->sk);

	वापस ret;
पूर्ण

अटल व्योम j1939_sk_sock2sockaddr_can(काष्ठा sockaddr_can *addr,
				       स्थिर काष्ठा j1939_sock *jsk, पूर्णांक peer)
अणु
	/* There are two holes (2 bytes and 3 bytes) to clear to aव्योम
	 * leaking kernel inक्रमmation to user space.
	 */
	स_रखो(addr, 0, J1939_MIN_NAMELEN);

	addr->can_family = AF_CAN;
	addr->can_अगरindex = jsk->अगरindex;
	addr->can_addr.j1939.pgn = jsk->addr.pgn;
	अगर (peer) अणु
		addr->can_addr.j1939.name = jsk->addr.dst_name;
		addr->can_addr.j1939.addr = jsk->addr.da;
	पूर्ण अन्यथा अणु
		addr->can_addr.j1939.name = jsk->addr.src_name;
		addr->can_addr.j1939.addr = jsk->addr.sa;
	पूर्ण
पूर्ण

अटल पूर्णांक j1939_sk_getname(काष्ठा socket *sock, काष्ठा sockaddr *uaddr,
			    पूर्णांक peer)
अणु
	काष्ठा sockaddr_can *addr = (काष्ठा sockaddr_can *)uaddr;
	काष्ठा sock *sk = sock->sk;
	काष्ठा j1939_sock *jsk = j1939_sk(sk);
	पूर्णांक ret = 0;

	lock_sock(sk);

	अगर (peer && !(jsk->state & J1939_SOCK_CONNECTED)) अणु
		ret = -EADDRNOTAVAIL;
		जाओ failure;
	पूर्ण

	j1939_sk_sock2sockaddr_can(addr, jsk, peer);
	ret = J1939_MIN_NAMELEN;

 failure:
	release_sock(sk);

	वापस ret;
पूर्ण

अटल पूर्णांक j1939_sk_release(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा j1939_sock *jsk;

	अगर (!sk)
		वापस 0;

	lock_sock(sk);
	jsk = j1939_sk(sk);

	अगर (jsk->state & J1939_SOCK_BOUND) अणु
		काष्ठा j1939_priv *priv = jsk->priv;

		अगर (रुको_event_पूर्णांकerruptible(jsk->रुकोq,
					     !j1939_sock_pending_get(&jsk->sk))) अणु
			j1939_cancel_active_session(priv, sk);
			j1939_sk_queue_drop_all(priv, jsk, ESHUTDOWN);
		पूर्ण

		j1939_jsk_del(priv, jsk);

		j1939_local_ecu_put(priv, jsk->addr.src_name,
				    jsk->addr.sa);

		j1939_netdev_stop(priv);
	पूर्ण

	kमुक्त(jsk->filters);
	sock_orphan(sk);
	sock->sk = शून्य;

	release_sock(sk);
	sock_put(sk);

	वापस 0;
पूर्ण

अटल पूर्णांक j1939_sk_setsockopt_flag(काष्ठा j1939_sock *jsk, sockptr_t optval,
				    अचिन्हित पूर्णांक optlen, पूर्णांक flag)
अणु
	पूर्णांक पंचांगp;

	अगर (optlen != माप(पंचांगp))
		वापस -EINVAL;
	अगर (copy_from_sockptr(&पंचांगp, optval, optlen))
		वापस -EFAULT;
	lock_sock(&jsk->sk);
	अगर (पंचांगp)
		jsk->state |= flag;
	अन्यथा
		jsk->state &= ~flag;
	release_sock(&jsk->sk);
	वापस पंचांगp;
पूर्ण

अटल पूर्णांक j1939_sk_setsockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
			       sockptr_t optval, अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा j1939_sock *jsk = j1939_sk(sk);
	पूर्णांक पंचांगp, count = 0, ret = 0;
	काष्ठा j1939_filter *filters = शून्य, *ofilters;

	अगर (level != SOL_CAN_J1939)
		वापस -EINVAL;

	चयन (optname) अणु
	हाल SO_J1939_FILTER:
		अगर (!sockptr_is_null(optval)) अणु
			काष्ठा j1939_filter *f;
			पूर्णांक c;

			अगर (optlen % माप(*filters) != 0)
				वापस -EINVAL;

			अगर (optlen > J1939_FILTER_MAX *
			    माप(काष्ठा j1939_filter))
				वापस -EINVAL;

			count = optlen / माप(*filters);
			filters = memdup_sockptr(optval, optlen);
			अगर (IS_ERR(filters))
				वापस PTR_ERR(filters);

			क्रम (f = filters, c = count; c; f++, c--) अणु
				f->name &= f->name_mask;
				f->pgn &= f->pgn_mask;
				f->addr &= f->addr_mask;
			पूर्ण
		पूर्ण

		lock_sock(&jsk->sk);
		ofilters = jsk->filters;
		jsk->filters = filters;
		jsk->nfilters = count;
		release_sock(&jsk->sk);
		kमुक्त(ofilters);
		वापस 0;
	हाल SO_J1939_PROMISC:
		वापस j1939_sk_setsockopt_flag(jsk, optval, optlen,
						J1939_SOCK_PROMISC);
	हाल SO_J1939_ERRQUEUE:
		ret = j1939_sk_setsockopt_flag(jsk, optval, optlen,
					       J1939_SOCK_ERRQUEUE);
		अगर (ret < 0)
			वापस ret;

		अगर (!(jsk->state & J1939_SOCK_ERRQUEUE))
			skb_queue_purge(&sk->sk_error_queue);
		वापस ret;
	हाल SO_J1939_SEND_PRIO:
		अगर (optlen != माप(पंचांगp))
			वापस -EINVAL;
		अगर (copy_from_sockptr(&पंचांगp, optval, optlen))
			वापस -EFAULT;
		अगर (पंचांगp < 0 || पंचांगp > 7)
			वापस -गलत_तर्क;
		अगर (पंचांगp < 2 && !capable(CAP_NET_ADMIN))
			वापस -EPERM;
		lock_sock(&jsk->sk);
		jsk->sk.sk_priority = j1939_to_sk_priority(पंचांगp);
		release_sock(&jsk->sk);
		वापस 0;
	शेष:
		वापस -ENOPROTOOPT;
	पूर्ण
पूर्ण

अटल पूर्णांक j1939_sk_माला_लोockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
			       अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा j1939_sock *jsk = j1939_sk(sk);
	पूर्णांक ret, ulen;
	/* set शेषs क्रम using 'int' properties */
	पूर्णांक पंचांगp = 0;
	पूर्णांक len = माप(पंचांगp);
	व्योम *val = &पंचांगp;

	अगर (level != SOL_CAN_J1939)
		वापस -EINVAL;
	अगर (get_user(ulen, optlen))
		वापस -EFAULT;
	अगर (ulen < 0)
		वापस -EINVAL;

	lock_sock(&jsk->sk);
	चयन (optname) अणु
	हाल SO_J1939_PROMISC:
		पंचांगp = (jsk->state & J1939_SOCK_PROMISC) ? 1 : 0;
		अवरोध;
	हाल SO_J1939_ERRQUEUE:
		पंचांगp = (jsk->state & J1939_SOCK_ERRQUEUE) ? 1 : 0;
		अवरोध;
	हाल SO_J1939_SEND_PRIO:
		पंचांगp = j1939_prio(jsk->sk.sk_priority);
		अवरोध;
	शेष:
		ret = -ENOPROTOOPT;
		जाओ no_copy;
	पूर्ण

	/* copy to user, based on 'len' & 'val'
	 * but most sockopt's are 'int' properties, and have 'len' & 'val'
	 * left unchanged, but instead modअगरied 'tmp'
	 */
	अगर (len > ulen)
		ret = -EFAULT;
	अन्यथा अगर (put_user(len, optlen))
		ret = -EFAULT;
	अन्यथा अगर (copy_to_user(optval, val, len))
		ret = -EFAULT;
	अन्यथा
		ret = 0;
 no_copy:
	release_sock(&jsk->sk);
	वापस ret;
पूर्ण

अटल पूर्णांक j1939_sk_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg,
			    माप_प्रकार size, पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा sk_buff *skb;
	काष्ठा j1939_sk_buff_cb *skcb;
	पूर्णांक ret = 0;

	अगर (flags & ~(MSG_DONTWAIT | MSG_ERRQUEUE))
		वापस -EINVAL;

	अगर (flags & MSG_ERRQUEUE)
		वापस sock_recv_errqueue(sock->sk, msg, size, SOL_CAN_J1939,
					  SCM_J1939_ERRQUEUE);

	skb = skb_recv_datagram(sk, flags, 0, &ret);
	अगर (!skb)
		वापस ret;

	अगर (size < skb->len)
		msg->msg_flags |= MSG_TRUNC;
	अन्यथा
		size = skb->len;

	ret = स_नकल_to_msg(msg, skb->data, size);
	अगर (ret < 0) अणु
		skb_मुक्त_datagram(sk, skb);
		वापस ret;
	पूर्ण

	skcb = j1939_skb_to_cb(skb);
	अगर (j1939_address_is_valid(skcb->addr.da))
		put_cmsg(msg, SOL_CAN_J1939, SCM_J1939_DEST_ADDR,
			 माप(skcb->addr.da), &skcb->addr.da);

	अगर (skcb->addr.dst_name)
		put_cmsg(msg, SOL_CAN_J1939, SCM_J1939_DEST_NAME,
			 माप(skcb->addr.dst_name), &skcb->addr.dst_name);

	put_cmsg(msg, SOL_CAN_J1939, SCM_J1939_PRIO,
		 माप(skcb->priority), &skcb->priority);

	अगर (msg->msg_name) अणु
		काष्ठा sockaddr_can *paddr = msg->msg_name;

		msg->msg_namelen = J1939_MIN_NAMELEN;
		स_रखो(msg->msg_name, 0, msg->msg_namelen);
		paddr->can_family = AF_CAN;
		paddr->can_अगरindex = skb->skb_iअगर;
		paddr->can_addr.j1939.name = skcb->addr.src_name;
		paddr->can_addr.j1939.addr = skcb->addr.sa;
		paddr->can_addr.j1939.pgn = skcb->addr.pgn;
	पूर्ण

	sock_recv_ts_and_drops(msg, sk, skb);
	msg->msg_flags |= skcb->msg_flags;
	skb_मुक्त_datagram(sk, skb);

	वापस size;
पूर्ण

अटल काष्ठा sk_buff *j1939_sk_alloc_skb(काष्ठा net_device *ndev,
					  काष्ठा sock *sk,
					  काष्ठा msghdr *msg, माप_प्रकार size,
					  पूर्णांक *errcode)
अणु
	काष्ठा j1939_sock *jsk = j1939_sk(sk);
	काष्ठा j1939_sk_buff_cb *skcb;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	skb = sock_alloc_send_skb(sk,
				  size +
				  माप(काष्ठा can_frame) -
				  माप(((काष्ठा can_frame *)शून्य)->data) +
				  माप(काष्ठा can_skb_priv),
				  msg->msg_flags & MSG_DONTWAIT, &ret);
	अगर (!skb)
		जाओ failure;

	can_skb_reserve(skb);
	can_skb_prv(skb)->अगरindex = ndev->अगरindex;
	can_skb_prv(skb)->skbcnt = 0;
	skb_reserve(skb, दुरत्व(काष्ठा can_frame, data));

	ret = स_नकल_from_msg(skb_put(skb, size), msg, size);
	अगर (ret < 0)
		जाओ मुक्त_skb;

	skb->dev = ndev;

	skcb = j1939_skb_to_cb(skb);
	स_रखो(skcb, 0, माप(*skcb));
	skcb->addr = jsk->addr;
	skcb->priority = j1939_prio(sk->sk_priority);

	अगर (msg->msg_name) अणु
		काष्ठा sockaddr_can *addr = msg->msg_name;

		अगर (addr->can_addr.j1939.name ||
		    addr->can_addr.j1939.addr != J1939_NO_ADDR) अणु
			skcb->addr.dst_name = addr->can_addr.j1939.name;
			skcb->addr.da = addr->can_addr.j1939.addr;
		पूर्ण
		अगर (j1939_pgn_is_valid(addr->can_addr.j1939.pgn))
			skcb->addr.pgn = addr->can_addr.j1939.pgn;
	पूर्ण

	*errcode = ret;
	वापस skb;

मुक्त_skb:
	kमुक्त_skb(skb);
failure:
	*errcode = ret;
	वापस शून्य;
पूर्ण

अटल माप_प्रकार j1939_sk_opt_stats_get_size(व्योम)
अणु
	वापस
		nla_total_size(माप(u32)) + /* J1939_NLA_BYTES_ACKED */
		0;
पूर्ण

अटल काष्ठा sk_buff *
j1939_sk_get_बारtamping_opt_stats(काष्ठा j1939_session *session)
अणु
	काष्ठा sk_buff *stats;
	u32 size;

	stats = alloc_skb(j1939_sk_opt_stats_get_size(), GFP_ATOMIC);
	अगर (!stats)
		वापस शून्य;

	अगर (session->skcb.addr.type == J1939_SIMPLE)
		size = session->total_message_size;
	अन्यथा
		size = min(session->pkt.tx_acked * 7,
			   session->total_message_size);

	nla_put_u32(stats, J1939_NLA_BYTES_ACKED, size);

	वापस stats;
पूर्ण

व्योम j1939_sk_errqueue(काष्ठा j1939_session *session,
		       क्रमागत j1939_sk_errqueue_type type)
अणु
	काष्ठा j1939_priv *priv = session->priv;
	काष्ठा sock *sk = session->sk;
	काष्ठा j1939_sock *jsk;
	काष्ठा sock_exterr_skb *serr;
	काष्ठा sk_buff *skb;
	अक्षर *state = "UNK";
	पूर्णांक err;

	/* currently we have no sk क्रम the RX session */
	अगर (!sk)
		वापस;

	jsk = j1939_sk(sk);

	अगर (!(jsk->state & J1939_SOCK_ERRQUEUE))
		वापस;

	skb = j1939_sk_get_बारtamping_opt_stats(session);
	अगर (!skb)
		वापस;

	skb->tstamp = kसमय_get_real();

	BUILD_BUG_ON(माप(काष्ठा sock_exterr_skb) > माप(skb->cb));

	serr = SKB_EXT_ERR(skb);
	स_रखो(serr, 0, माप(*serr));
	चयन (type) अणु
	हाल J1939_ERRQUEUE_ACK:
		अगर (!(sk->sk_tsflags & SOF_TIMESTAMPING_TX_ACK)) अणु
			kमुक्त_skb(skb);
			वापस;
		पूर्ण

		serr->ee.ee_त्रुटि_सं = ENOMSG;
		serr->ee.ee_origin = SO_EE_ORIGIN_TIMESTAMPING;
		serr->ee.ee_info = SCM_TSTAMP_ACK;
		state = "ACK";
		अवरोध;
	हाल J1939_ERRQUEUE_SCHED:
		अगर (!(sk->sk_tsflags & SOF_TIMESTAMPING_TX_SCHED)) अणु
			kमुक्त_skb(skb);
			वापस;
		पूर्ण

		serr->ee.ee_त्रुटि_सं = ENOMSG;
		serr->ee.ee_origin = SO_EE_ORIGIN_TIMESTAMPING;
		serr->ee.ee_info = SCM_TSTAMP_SCHED;
		state = "SCH";
		अवरोध;
	हाल J1939_ERRQUEUE_ABORT:
		serr->ee.ee_त्रुटि_सं = session->err;
		serr->ee.ee_origin = SO_EE_ORIGIN_LOCAL;
		serr->ee.ee_info = J1939_EE_INFO_TX_ABORT;
		state = "ABT";
		अवरोध;
	शेष:
		netdev_err(priv->ndev, "Unknown errqueue type %i\n", type);
	पूर्ण

	serr->opt_stats = true;
	अगर (sk->sk_tsflags & SOF_TIMESTAMPING_OPT_ID)
		serr->ee.ee_data = session->tskey;

	netdev_dbg(session->priv->ndev, "%s: 0x%p tskey: %i, state: %s\n",
		   __func__, session, session->tskey, state);
	err = sock_queue_err_skb(sk, skb);

	अगर (err)
		kमुक्त_skb(skb);
पूर्ण;

व्योम j1939_sk_send_loop_पात(काष्ठा sock *sk, पूर्णांक err)
अणु
	sk->sk_err = err;

	sk->sk_error_report(sk);
पूर्ण

अटल पूर्णांक j1939_sk_send_loop(काष्ठा j1939_priv *priv,  काष्ठा sock *sk,
			      काष्ठा msghdr *msg, माप_प्रकार size)

अणु
	काष्ठा j1939_sock *jsk = j1939_sk(sk);
	काष्ठा j1939_session *session = j1939_sk_get_incomplete_session(jsk);
	काष्ठा sk_buff *skb;
	माप_प्रकार segment_size, toकरो_size;
	पूर्णांक ret = 0;

	अगर (session &&
	    session->total_message_size != session->total_queued_size + size) अणु
		j1939_session_put(session);
		वापस -EIO;
	पूर्ण

	toकरो_size = size;

	जबतक (toकरो_size) अणु
		काष्ठा j1939_sk_buff_cb *skcb;

		segment_size = min_t(माप_प्रकार, J1939_MAX_TP_PACKET_SIZE,
				     toकरो_size);

		/* Allocate skb क्रम one segment */
		skb = j1939_sk_alloc_skb(priv->ndev, sk, msg, segment_size,
					 &ret);
		अगर (ret)
			अवरोध;

		skcb = j1939_skb_to_cb(skb);

		अगर (!session) अणु
			/* at this poपूर्णांक the size should be full size
			 * of the session
			 */
			skcb->offset = 0;
			session = j1939_tp_send(priv, skb, size);
			अगर (IS_ERR(session)) अणु
				ret = PTR_ERR(session);
				जाओ kमुक्त_skb;
			पूर्ण
			अगर (j1939_sk_queue_session(session)) अणु
				/* try to activate session अगर we a
				 * fist in the queue
				 */
				अगर (!j1939_session_activate(session)) अणु
					j1939_tp_schedule_txसमयr(session, 0);
				पूर्ण अन्यथा अणु
					ret = -EBUSY;
					session->err = ret;
					j1939_sk_queue_drop_all(priv, jsk,
								EBUSY);
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			skcb->offset = session->total_queued_size;
			j1939_session_skb_queue(session, skb);
		पूर्ण

		toकरो_size -= segment_size;
		session->total_queued_size += segment_size;
	पूर्ण

	चयन (ret) अणु
	हाल 0: /* OK */
		अगर (toकरो_size)
			netdev_warn(priv->ndev,
				    "no error found and not completely queued?! %zu\n",
				    toकरो_size);
		ret = size;
		अवरोध;
	हाल -ERESTARTSYS:
		ret = -EINTR;
		fallthrough;
	हाल -EAGAIN: /* OK */
		अगर (toकरो_size != size)
			ret = size - toकरो_size;
		अवरोध;
	शेष: /* ERROR */
		अवरोध;
	पूर्ण

	अगर (session)
		j1939_session_put(session);

	वापस ret;

 kमुक्त_skb:
	kमुक्त_skb(skb);
	वापस ret;
पूर्ण

अटल पूर्णांक j1939_sk_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg,
			    माप_प्रकार size)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा j1939_sock *jsk = j1939_sk(sk);
	काष्ठा j1939_priv *priv;
	पूर्णांक अगरindex;
	पूर्णांक ret;

	lock_sock(sock->sk);
	/* various socket state tests */
	अगर (!(jsk->state & J1939_SOCK_BOUND)) अणु
		ret = -EBADFD;
		जाओ sendmsg_करोne;
	पूर्ण

	priv = jsk->priv;
	अगरindex = jsk->अगरindex;

	अगर (!jsk->addr.src_name && jsk->addr.sa == J1939_NO_ADDR) अणु
		/* no source address asचिन्हित yet */
		ret = -EBADFD;
		जाओ sendmsg_करोne;
	पूर्ण

	/* deal with provided destination address info */
	अगर (msg->msg_name) अणु
		काष्ठा sockaddr_can *addr = msg->msg_name;

		अगर (msg->msg_namelen < J1939_MIN_NAMELEN) अणु
			ret = -EINVAL;
			जाओ sendmsg_करोne;
		पूर्ण

		अगर (addr->can_family != AF_CAN) अणु
			ret = -EINVAL;
			जाओ sendmsg_करोne;
		पूर्ण

		अगर (addr->can_अगरindex && addr->can_अगरindex != अगरindex) अणु
			ret = -EBADFD;
			जाओ sendmsg_करोne;
		पूर्ण

		अगर (j1939_pgn_is_valid(addr->can_addr.j1939.pgn) &&
		    !j1939_pgn_is_clean_pdu(addr->can_addr.j1939.pgn)) अणु
			ret = -EINVAL;
			जाओ sendmsg_करोne;
		पूर्ण

		अगर (!addr->can_addr.j1939.name &&
		    addr->can_addr.j1939.addr == J1939_NO_ADDR &&
		    !sock_flag(sk, SOCK_BROADCAST)) अणु
			/* broadcast, but SO_BROADCAST not set */
			ret = -EACCES;
			जाओ sendmsg_करोne;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!jsk->addr.dst_name && jsk->addr.da == J1939_NO_ADDR &&
		    !sock_flag(sk, SOCK_BROADCAST)) अणु
			/* broadcast, but SO_BROADCAST not set */
			ret = -EACCES;
			जाओ sendmsg_करोne;
		पूर्ण
	पूर्ण

	ret = j1939_sk_send_loop(priv, sk, msg, size);

sendmsg_करोne:
	release_sock(sock->sk);

	वापस ret;
पूर्ण

व्योम j1939_sk_netdev_event_netकरोwn(काष्ठा j1939_priv *priv)
अणु
	काष्ठा j1939_sock *jsk;
	पूर्णांक error_code = ENETDOWN;

	spin_lock_bh(&priv->j1939_socks_lock);
	list_क्रम_each_entry(jsk, &priv->j1939_socks, list) अणु
		jsk->sk.sk_err = error_code;
		अगर (!sock_flag(&jsk->sk, SOCK_DEAD))
			jsk->sk.sk_error_report(&jsk->sk);

		j1939_sk_queue_drop_all(priv, jsk, error_code);
	पूर्ण
	spin_unlock_bh(&priv->j1939_socks_lock);
पूर्ण

अटल पूर्णांक j1939_sk_no_ioctlcmd(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd,
				अचिन्हित दीर्घ arg)
अणु
	/* no ioctls क्रम socket layer -> hand it करोwn to NIC layer */
	वापस -ENOIOCTLCMD;
पूर्ण

अटल स्थिर काष्ठा proto_ops j1939_ops = अणु
	.family = PF_CAN,
	.release = j1939_sk_release,
	.bind = j1939_sk_bind,
	.connect = j1939_sk_connect,
	.socketpair = sock_no_socketpair,
	.accept = sock_no_accept,
	.getname = j1939_sk_getname,
	.poll = datagram_poll,
	.ioctl = j1939_sk_no_ioctlcmd,
	.listen = sock_no_listen,
	.shutकरोwn = sock_no_shutकरोwn,
	.setsockopt = j1939_sk_setsockopt,
	.माला_लोockopt = j1939_sk_माला_लोockopt,
	.sendmsg = j1939_sk_sendmsg,
	.recvmsg = j1939_sk_recvmsg,
	.mmap = sock_no_mmap,
	.sendpage = sock_no_sendpage,
पूर्ण;

अटल काष्ठा proto j1939_proto __पढ़ो_mostly = अणु
	.name = "CAN_J1939",
	.owner = THIS_MODULE,
	.obj_size = माप(काष्ठा j1939_sock),
	.init = j1939_sk_init,
पूर्ण;

स्थिर काष्ठा can_proto j1939_can_proto = अणु
	.type = SOCK_DGRAM,
	.protocol = CAN_J1939,
	.ops = &j1939_ops,
	.prot = &j1939_proto,
पूर्ण;
