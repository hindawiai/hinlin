<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		Support क्रम INET connection oriented protocols.
 *
 * Authors:	See the TCP sources
 */

#समावेश <linux/module.h>
#समावेश <linux/jhash.h>

#समावेश <net/inet_connection_sock.h>
#समावेश <net/inet_hashtables.h>
#समावेश <net/inet_समयरुको_sock.h>
#समावेश <net/ip.h>
#समावेश <net/route.h>
#समावेश <net/tcp_states.h>
#समावेश <net/xfrm.h>
#समावेश <net/tcp.h>
#समावेश <net/sock_reuseport.h>
#समावेश <net/addrconf.h>

#अगर IS_ENABLED(CONFIG_IPV6)
/* match_sk*_wildcard == true:  IPV6_ADDR_ANY equals to any IPv6 addresses
 *				अगर IPv6 only, and any IPv4 addresses
 *				अगर not IPv6 only
 * match_sk*_wildcard == false: addresses must be exactly the same, i.e.
 *				IPV6_ADDR_ANY only equals to IPV6_ADDR_ANY,
 *				and 0.0.0.0 equals to 0.0.0.0 only
 */
अटल bool ipv6_rcv_saddr_equal(स्थिर काष्ठा in6_addr *sk1_rcv_saddr6,
				 स्थिर काष्ठा in6_addr *sk2_rcv_saddr6,
				 __be32 sk1_rcv_saddr, __be32 sk2_rcv_saddr,
				 bool sk1_ipv6only, bool sk2_ipv6only,
				 bool match_sk1_wildcard,
				 bool match_sk2_wildcard)
अणु
	पूर्णांक addr_type = ipv6_addr_type(sk1_rcv_saddr6);
	पूर्णांक addr_type2 = sk2_rcv_saddr6 ? ipv6_addr_type(sk2_rcv_saddr6) : IPV6_ADDR_MAPPED;

	/* अगर both are mapped, treat as IPv4 */
	अगर (addr_type == IPV6_ADDR_MAPPED && addr_type2 == IPV6_ADDR_MAPPED) अणु
		अगर (!sk2_ipv6only) अणु
			अगर (sk1_rcv_saddr == sk2_rcv_saddr)
				वापस true;
			वापस (match_sk1_wildcard && !sk1_rcv_saddr) ||
				(match_sk2_wildcard && !sk2_rcv_saddr);
		पूर्ण
		वापस false;
	पूर्ण

	अगर (addr_type == IPV6_ADDR_ANY && addr_type2 == IPV6_ADDR_ANY)
		वापस true;

	अगर (addr_type2 == IPV6_ADDR_ANY && match_sk2_wildcard &&
	    !(sk2_ipv6only && addr_type == IPV6_ADDR_MAPPED))
		वापस true;

	अगर (addr_type == IPV6_ADDR_ANY && match_sk1_wildcard &&
	    !(sk1_ipv6only && addr_type2 == IPV6_ADDR_MAPPED))
		वापस true;

	अगर (sk2_rcv_saddr6 &&
	    ipv6_addr_equal(sk1_rcv_saddr6, sk2_rcv_saddr6))
		वापस true;

	वापस false;
पूर्ण
#पूर्ण_अगर

/* match_sk*_wildcard == true:  0.0.0.0 equals to any IPv4 addresses
 * match_sk*_wildcard == false: addresses must be exactly the same, i.e.
 *				0.0.0.0 only equals to 0.0.0.0
 */
अटल bool ipv4_rcv_saddr_equal(__be32 sk1_rcv_saddr, __be32 sk2_rcv_saddr,
				 bool sk2_ipv6only, bool match_sk1_wildcard,
				 bool match_sk2_wildcard)
अणु
	अगर (!sk2_ipv6only) अणु
		अगर (sk1_rcv_saddr == sk2_rcv_saddr)
			वापस true;
		वापस (match_sk1_wildcard && !sk1_rcv_saddr) ||
			(match_sk2_wildcard && !sk2_rcv_saddr);
	पूर्ण
	वापस false;
पूर्ण

bool inet_rcv_saddr_equal(स्थिर काष्ठा sock *sk, स्थिर काष्ठा sock *sk2,
			  bool match_wildcard)
अणु
#अगर IS_ENABLED(CONFIG_IPV6)
	अगर (sk->sk_family == AF_INET6)
		वापस ipv6_rcv_saddr_equal(&sk->sk_v6_rcv_saddr,
					    inet6_rcv_saddr(sk2),
					    sk->sk_rcv_saddr,
					    sk2->sk_rcv_saddr,
					    ipv6_only_sock(sk),
					    ipv6_only_sock(sk2),
					    match_wildcard,
					    match_wildcard);
#पूर्ण_अगर
	वापस ipv4_rcv_saddr_equal(sk->sk_rcv_saddr, sk2->sk_rcv_saddr,
				    ipv6_only_sock(sk2), match_wildcard,
				    match_wildcard);
पूर्ण
EXPORT_SYMBOL(inet_rcv_saddr_equal);

bool inet_rcv_saddr_any(स्थिर काष्ठा sock *sk)
अणु
#अगर IS_ENABLED(CONFIG_IPV6)
	अगर (sk->sk_family == AF_INET6)
		वापस ipv6_addr_any(&sk->sk_v6_rcv_saddr);
#पूर्ण_अगर
	वापस !sk->sk_rcv_saddr;
पूर्ण

व्योम inet_get_local_port_range(काष्ठा net *net, पूर्णांक *low, पूर्णांक *high)
अणु
	अचिन्हित पूर्णांक seq;

	करो अणु
		seq = पढ़ो_seqbegin(&net->ipv4.ip_local_ports.lock);

		*low = net->ipv4.ip_local_ports.range[0];
		*high = net->ipv4.ip_local_ports.range[1];
	पूर्ण जबतक (पढ़ो_seqretry(&net->ipv4.ip_local_ports.lock, seq));
पूर्ण
EXPORT_SYMBOL(inet_get_local_port_range);

अटल पूर्णांक inet_csk_bind_conflict(स्थिर काष्ठा sock *sk,
				  स्थिर काष्ठा inet_bind_bucket *tb,
				  bool relax, bool reuseport_ok)
अणु
	काष्ठा sock *sk2;
	bool reuse = sk->sk_reuse;
	bool reuseport = !!sk->sk_reuseport;
	kuid_t uid = sock_i_uid((काष्ठा sock *)sk);

	/*
	 * Unlike other sk lookup places we करो not check
	 * क्रम sk_net here, since _all_ the socks listed
	 * in tb->owners list beदीर्घ to the same net - the
	 * one this bucket beदीर्घs to.
	 */

	sk_क्रम_each_bound(sk2, &tb->owners) अणु
		अगर (sk != sk2 &&
		    (!sk->sk_bound_dev_अगर ||
		     !sk2->sk_bound_dev_अगर ||
		     sk->sk_bound_dev_अगर == sk2->sk_bound_dev_अगर)) अणु
			अगर (reuse && sk2->sk_reuse &&
			    sk2->sk_state != TCP_LISTEN) अणु
				अगर ((!relax ||
				     (!reuseport_ok &&
				      reuseport && sk2->sk_reuseport &&
				      !rcu_access_poपूर्णांकer(sk->sk_reuseport_cb) &&
				      (sk2->sk_state == TCP_TIME_WAIT ||
				       uid_eq(uid, sock_i_uid(sk2))))) &&
				    inet_rcv_saddr_equal(sk, sk2, true))
					अवरोध;
			पूर्ण अन्यथा अगर (!reuseport_ok ||
				   !reuseport || !sk2->sk_reuseport ||
				   rcu_access_poपूर्णांकer(sk->sk_reuseport_cb) ||
				   (sk2->sk_state != TCP_TIME_WAIT &&
				    !uid_eq(uid, sock_i_uid(sk2)))) अणु
				अगर (inet_rcv_saddr_equal(sk, sk2, true))
					अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस sk2 != शून्य;
पूर्ण

/*
 * Find an खोलो port number क्रम the socket.  Returns with the
 * inet_bind_hashbucket lock held.
 */
अटल काष्ठा inet_bind_hashbucket *
inet_csk_find_खोलो_port(काष्ठा sock *sk, काष्ठा inet_bind_bucket **tb_ret, पूर्णांक *port_ret)
अणु
	काष्ठा inet_hashinfo *hinfo = sk->sk_prot->h.hashinfo;
	पूर्णांक port = 0;
	काष्ठा inet_bind_hashbucket *head;
	काष्ठा net *net = sock_net(sk);
	bool relax = false;
	पूर्णांक i, low, high, attempt_half;
	काष्ठा inet_bind_bucket *tb;
	u32 reमुख्यing, offset;
	पूर्णांक l3mdev;

	l3mdev = inet_sk_bound_l3mdev(sk);
ports_exhausted:
	attempt_half = (sk->sk_reuse == SK_CAN_REUSE) ? 1 : 0;
other_half_scan:
	inet_get_local_port_range(net, &low, &high);
	high++; /* [32768, 60999] -> [32768, 61000[ */
	अगर (high - low < 4)
		attempt_half = 0;
	अगर (attempt_half) अणु
		पूर्णांक half = low + (((high - low) >> 2) << 1);

		अगर (attempt_half == 1)
			high = half;
		अन्यथा
			low = half;
	पूर्ण
	reमुख्यing = high - low;
	अगर (likely(reमुख्यing > 1))
		reमुख्यing &= ~1U;

	offset = pअक्रमom_u32() % reमुख्यing;
	/* __inet_hash_connect() favors ports having @low parity
	 * We करो the opposite to not pollute connect() users.
	 */
	offset |= 1U;

other_parity_scan:
	port = low + offset;
	क्रम (i = 0; i < reमुख्यing; i += 2, port += 2) अणु
		अगर (unlikely(port >= high))
			port -= reमुख्यing;
		अगर (inet_is_local_reserved_port(net, port))
			जारी;
		head = &hinfo->bhash[inet_bhashfn(net, port,
						  hinfo->bhash_size)];
		spin_lock_bh(&head->lock);
		inet_bind_bucket_क्रम_each(tb, &head->chain)
			अगर (net_eq(ib_net(tb), net) && tb->l3mdev == l3mdev &&
			    tb->port == port) अणु
				अगर (!inet_csk_bind_conflict(sk, tb, relax, false))
					जाओ success;
				जाओ next_port;
			पूर्ण
		tb = शून्य;
		जाओ success;
next_port:
		spin_unlock_bh(&head->lock);
		cond_resched();
	पूर्ण

	offset--;
	अगर (!(offset & 1))
		जाओ other_parity_scan;

	अगर (attempt_half == 1) अणु
		/* OK we now try the upper half of the range */
		attempt_half = 2;
		जाओ other_half_scan;
	पूर्ण

	अगर (net->ipv4.sysctl_ip_स्वतःbind_reuse && !relax) अणु
		/* We still have a chance to connect to dअगरferent destinations */
		relax = true;
		जाओ ports_exhausted;
	पूर्ण
	वापस शून्य;
success:
	*port_ret = port;
	*tb_ret = tb;
	वापस head;
पूर्ण

अटल अंतरभूत पूर्णांक sk_reuseport_match(काष्ठा inet_bind_bucket *tb,
				     काष्ठा sock *sk)
अणु
	kuid_t uid = sock_i_uid(sk);

	अगर (tb->fastreuseport <= 0)
		वापस 0;
	अगर (!sk->sk_reuseport)
		वापस 0;
	अगर (rcu_access_poपूर्णांकer(sk->sk_reuseport_cb))
		वापस 0;
	अगर (!uid_eq(tb->fastuid, uid))
		वापस 0;
	/* We only need to check the rcv_saddr अगर this tb was once marked
	 * without fastreuseport and then was reset, as we can only know that
	 * the fast_*rcv_saddr करोesn't have any conflicts with the socks on the
	 * owners list.
	 */
	अगर (tb->fastreuseport == FASTREUSEPORT_ANY)
		वापस 1;
#अगर IS_ENABLED(CONFIG_IPV6)
	अगर (tb->fast_sk_family == AF_INET6)
		वापस ipv6_rcv_saddr_equal(&tb->fast_v6_rcv_saddr,
					    inet6_rcv_saddr(sk),
					    tb->fast_rcv_saddr,
					    sk->sk_rcv_saddr,
					    tb->fast_ipv6_only,
					    ipv6_only_sock(sk), true, false);
#पूर्ण_अगर
	वापस ipv4_rcv_saddr_equal(tb->fast_rcv_saddr, sk->sk_rcv_saddr,
				    ipv6_only_sock(sk), true, false);
पूर्ण

व्योम inet_csk_update_fastreuse(काष्ठा inet_bind_bucket *tb,
			       काष्ठा sock *sk)
अणु
	kuid_t uid = sock_i_uid(sk);
	bool reuse = sk->sk_reuse && sk->sk_state != TCP_LISTEN;

	अगर (hlist_empty(&tb->owners)) अणु
		tb->fastreuse = reuse;
		अगर (sk->sk_reuseport) अणु
			tb->fastreuseport = FASTREUSEPORT_ANY;
			tb->fastuid = uid;
			tb->fast_rcv_saddr = sk->sk_rcv_saddr;
			tb->fast_ipv6_only = ipv6_only_sock(sk);
			tb->fast_sk_family = sk->sk_family;
#अगर IS_ENABLED(CONFIG_IPV6)
			tb->fast_v6_rcv_saddr = sk->sk_v6_rcv_saddr;
#पूर्ण_अगर
		पूर्ण अन्यथा अणु
			tb->fastreuseport = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!reuse)
			tb->fastreuse = 0;
		अगर (sk->sk_reuseport) अणु
			/* We didn't match or we don't have fastreuseport set on
			 * the tb, but we have sk_reuseport set on this socket
			 * and we know that there are no bind conflicts with
			 * this socket in this tb, so reset our tb's reuseport
			 * settings so that any subsequent sockets that match
			 * our current socket will be put on the fast path.
			 *
			 * If we reset we need to set FASTREUSEPORT_STRICT so we
			 * करो extra checking क्रम all subsequent sk_reuseport
			 * socks.
			 */
			अगर (!sk_reuseport_match(tb, sk)) अणु
				tb->fastreuseport = FASTREUSEPORT_STRICT;
				tb->fastuid = uid;
				tb->fast_rcv_saddr = sk->sk_rcv_saddr;
				tb->fast_ipv6_only = ipv6_only_sock(sk);
				tb->fast_sk_family = sk->sk_family;
#अगर IS_ENABLED(CONFIG_IPV6)
				tb->fast_v6_rcv_saddr = sk->sk_v6_rcv_saddr;
#पूर्ण_अगर
			पूर्ण
		पूर्ण अन्यथा अणु
			tb->fastreuseport = 0;
		पूर्ण
	पूर्ण
पूर्ण

/* Obtain a reference to a local port क्रम the given sock,
 * अगर snum is zero it means select any available local port.
 * We try to allocate an odd port (and leave even ports क्रम connect())
 */
पूर्णांक inet_csk_get_port(काष्ठा sock *sk, अचिन्हित लघु snum)
अणु
	bool reuse = sk->sk_reuse && sk->sk_state != TCP_LISTEN;
	काष्ठा inet_hashinfo *hinfo = sk->sk_prot->h.hashinfo;
	पूर्णांक ret = 1, port = snum;
	काष्ठा inet_bind_hashbucket *head;
	काष्ठा net *net = sock_net(sk);
	काष्ठा inet_bind_bucket *tb = शून्य;
	पूर्णांक l3mdev;

	l3mdev = inet_sk_bound_l3mdev(sk);

	अगर (!port) अणु
		head = inet_csk_find_खोलो_port(sk, &tb, &port);
		अगर (!head)
			वापस ret;
		अगर (!tb)
			जाओ tb_not_found;
		जाओ success;
	पूर्ण
	head = &hinfo->bhash[inet_bhashfn(net, port,
					  hinfo->bhash_size)];
	spin_lock_bh(&head->lock);
	inet_bind_bucket_क्रम_each(tb, &head->chain)
		अगर (net_eq(ib_net(tb), net) && tb->l3mdev == l3mdev &&
		    tb->port == port)
			जाओ tb_found;
tb_not_found:
	tb = inet_bind_bucket_create(hinfo->bind_bucket_cachep,
				     net, head, port, l3mdev);
	अगर (!tb)
		जाओ fail_unlock;
tb_found:
	अगर (!hlist_empty(&tb->owners)) अणु
		अगर (sk->sk_reuse == SK_FORCE_REUSE)
			जाओ success;

		अगर ((tb->fastreuse > 0 && reuse) ||
		    sk_reuseport_match(tb, sk))
			जाओ success;
		अगर (inet_csk_bind_conflict(sk, tb, true, true))
			जाओ fail_unlock;
	पूर्ण
success:
	inet_csk_update_fastreuse(tb, sk);

	अगर (!inet_csk(sk)->icsk_bind_hash)
		inet_bind_hash(sk, tb, port);
	WARN_ON(inet_csk(sk)->icsk_bind_hash != tb);
	ret = 0;

fail_unlock:
	spin_unlock_bh(&head->lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(inet_csk_get_port);

/*
 * Wait क्रम an incoming connection, aव्योम race conditions. This must be called
 * with the socket locked.
 */
अटल पूर्णांक inet_csk_रुको_क्रम_connect(काष्ठा sock *sk, दीर्घ समयo)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	DEFINE_WAIT(रुको);
	पूर्णांक err;

	/*
	 * True wake-one mechanism क्रम incoming connections: only
	 * one process माला_लो woken up, not the 'whole herd'.
	 * Since we करो not 'race & poll' क्रम established sockets
	 * anymore, the common हाल will execute the loop only once.
	 *
	 * Subtle issue: "add_wait_queue_exclusive()" will be added
	 * after any current non-exclusive रुकोers, and we know that
	 * it will always _stay_ after any new non-exclusive रुकोers
	 * because all non-exclusive रुकोers are added at the
	 * beginning of the रुको-queue. As such, it's ok to "drop"
	 * our exclusiveness temporarily when we get woken up without
	 * having to हटाओ and re-insert us on the रुको queue.
	 */
	क्रम (;;) अणु
		prepare_to_रुको_exclusive(sk_sleep(sk), &रुको,
					  TASK_INTERRUPTIBLE);
		release_sock(sk);
		अगर (reqsk_queue_empty(&icsk->icsk_accept_queue))
			समयo = schedule_समयout(समयo);
		sched_annotate_sleep();
		lock_sock(sk);
		err = 0;
		अगर (!reqsk_queue_empty(&icsk->icsk_accept_queue))
			अवरोध;
		err = -EINVAL;
		अगर (sk->sk_state != TCP_LISTEN)
			अवरोध;
		err = sock_पूर्णांकr_त्रुटि_सं(समयo);
		अगर (संकेत_pending(current))
			अवरोध;
		err = -EAGAIN;
		अगर (!समयo)
			अवरोध;
	पूर्ण
	finish_रुको(sk_sleep(sk), &रुको);
	वापस err;
पूर्ण

/*
 * This will accept the next outstanding connection.
 */
काष्ठा sock *inet_csk_accept(काष्ठा sock *sk, पूर्णांक flags, पूर्णांक *err, bool kern)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	काष्ठा request_sock_queue *queue = &icsk->icsk_accept_queue;
	काष्ठा request_sock *req;
	काष्ठा sock *newsk;
	पूर्णांक error;

	lock_sock(sk);

	/* We need to make sure that this socket is listening,
	 * and that it has something pending.
	 */
	error = -EINVAL;
	अगर (sk->sk_state != TCP_LISTEN)
		जाओ out_err;

	/* Find alपढ़ोy established connection */
	अगर (reqsk_queue_empty(queue)) अणु
		दीर्घ समयo = sock_rcvसमयo(sk, flags & O_NONBLOCK);

		/* If this is a non blocking socket करोn't sleep */
		error = -EAGAIN;
		अगर (!समयo)
			जाओ out_err;

		error = inet_csk_रुको_क्रम_connect(sk, समयo);
		अगर (error)
			जाओ out_err;
	पूर्ण
	req = reqsk_queue_हटाओ(queue, sk);
	newsk = req->sk;

	अगर (sk->sk_protocol == IPPROTO_TCP &&
	    tcp_rsk(req)->tfo_listener) अणु
		spin_lock_bh(&queue->fastखोलोq.lock);
		अगर (tcp_rsk(req)->tfo_listener) अणु
			/* We are still रुकोing क्रम the final ACK from 3WHS
			 * so can't मुक्त req now. Instead, we set req->sk to
			 * शून्य to signअगरy that the child socket is taken
			 * so reqsk_fastखोलो_हटाओ() will मुक्त the req
			 * when 3WHS finishes (or is पातed).
			 */
			req->sk = शून्य;
			req = शून्य;
		पूर्ण
		spin_unlock_bh(&queue->fastखोलोq.lock);
	पूर्ण

out:
	release_sock(sk);
	अगर (newsk && mem_cgroup_sockets_enabled) अणु
		पूर्णांक amt;

		/* atomically get the memory usage, set and अक्षरge the
		 * newsk->sk_memcg.
		 */
		lock_sock(newsk);

		/* The socket has not been accepted yet, no need to look at
		 * newsk->sk_wmem_queued.
		 */
		amt = sk_mem_pages(newsk->sk_क्रमward_alloc +
				   atomic_पढ़ो(&newsk->sk_rmem_alloc));
		mem_cgroup_sk_alloc(newsk);
		अगर (newsk->sk_memcg && amt)
			mem_cgroup_अक्षरge_skmem(newsk->sk_memcg, amt);

		release_sock(newsk);
	पूर्ण
	अगर (req)
		reqsk_put(req);
	वापस newsk;
out_err:
	newsk = शून्य;
	req = शून्य;
	*err = error;
	जाओ out;
पूर्ण
EXPORT_SYMBOL(inet_csk_accept);

/*
 * Using dअगरferent समयrs क्रम retransmit, delayed acks and probes
 * We may wish use just one समयr मुख्यtaining a list of expire jअगरfies
 * to optimize.
 */
व्योम inet_csk_init_xmit_समयrs(काष्ठा sock *sk,
			       व्योम (*retransmit_handler)(काष्ठा समयr_list *t),
			       व्योम (*delack_handler)(काष्ठा समयr_list *t),
			       व्योम (*keepalive_handler)(काष्ठा समयr_list *t))
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);

	समयr_setup(&icsk->icsk_retransmit_समयr, retransmit_handler, 0);
	समयr_setup(&icsk->icsk_delack_समयr, delack_handler, 0);
	समयr_setup(&sk->sk_समयr, keepalive_handler, 0);
	icsk->icsk_pending = icsk->icsk_ack.pending = 0;
पूर्ण
EXPORT_SYMBOL(inet_csk_init_xmit_समयrs);

व्योम inet_csk_clear_xmit_समयrs(काष्ठा sock *sk)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);

	icsk->icsk_pending = icsk->icsk_ack.pending = 0;

	sk_stop_समयr(sk, &icsk->icsk_retransmit_समयr);
	sk_stop_समयr(sk, &icsk->icsk_delack_समयr);
	sk_stop_समयr(sk, &sk->sk_समयr);
पूर्ण
EXPORT_SYMBOL(inet_csk_clear_xmit_समयrs);

व्योम inet_csk_delete_keepalive_समयr(काष्ठा sock *sk)
अणु
	sk_stop_समयr(sk, &sk->sk_समयr);
पूर्ण
EXPORT_SYMBOL(inet_csk_delete_keepalive_समयr);

व्योम inet_csk_reset_keepalive_समयr(काष्ठा sock *sk, अचिन्हित दीर्घ len)
अणु
	sk_reset_समयr(sk, &sk->sk_समयr, jअगरfies + len);
पूर्ण
EXPORT_SYMBOL(inet_csk_reset_keepalive_समयr);

काष्ठा dst_entry *inet_csk_route_req(स्थिर काष्ठा sock *sk,
				     काष्ठा flowi4 *fl4,
				     स्थिर काष्ठा request_sock *req)
अणु
	स्थिर काष्ठा inet_request_sock *ireq = inet_rsk(req);
	काष्ठा net *net = पढ़ो_pnet(&ireq->ireq_net);
	काष्ठा ip_options_rcu *opt;
	काष्ठा rtable *rt;

	rcu_पढ़ो_lock();
	opt = rcu_dereference(ireq->ireq_opt);

	flowi4_init_output(fl4, ireq->ir_iअगर, ireq->ir_mark,
			   RT_CONN_FLAGS(sk), RT_SCOPE_UNIVERSE,
			   sk->sk_protocol, inet_sk_flowi_flags(sk),
			   (opt && opt->opt.srr) ? opt->opt.faddr : ireq->ir_rmt_addr,
			   ireq->ir_loc_addr, ireq->ir_rmt_port,
			   htons(ireq->ir_num), sk->sk_uid);
	security_req_classअगरy_flow(req, flowi4_to_flowi_common(fl4));
	rt = ip_route_output_flow(net, fl4, sk);
	अगर (IS_ERR(rt))
		जाओ no_route;
	अगर (opt && opt->opt.is_strictroute && rt->rt_uses_gateway)
		जाओ route_err;
	rcu_पढ़ो_unlock();
	वापस &rt->dst;

route_err:
	ip_rt_put(rt);
no_route:
	rcu_पढ़ो_unlock();
	__IP_INC_STATS(net, IPSTATS_MIB_OUTNOROUTES);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(inet_csk_route_req);

काष्ठा dst_entry *inet_csk_route_child_sock(स्थिर काष्ठा sock *sk,
					    काष्ठा sock *newsk,
					    स्थिर काष्ठा request_sock *req)
अणु
	स्थिर काष्ठा inet_request_sock *ireq = inet_rsk(req);
	काष्ठा net *net = पढ़ो_pnet(&ireq->ireq_net);
	काष्ठा inet_sock *newinet = inet_sk(newsk);
	काष्ठा ip_options_rcu *opt;
	काष्ठा flowi4 *fl4;
	काष्ठा rtable *rt;

	opt = rcu_dereference(ireq->ireq_opt);
	fl4 = &newinet->cork.fl.u.ip4;

	flowi4_init_output(fl4, ireq->ir_iअगर, ireq->ir_mark,
			   RT_CONN_FLAGS(sk), RT_SCOPE_UNIVERSE,
			   sk->sk_protocol, inet_sk_flowi_flags(sk),
			   (opt && opt->opt.srr) ? opt->opt.faddr : ireq->ir_rmt_addr,
			   ireq->ir_loc_addr, ireq->ir_rmt_port,
			   htons(ireq->ir_num), sk->sk_uid);
	security_req_classअगरy_flow(req, flowi4_to_flowi_common(fl4));
	rt = ip_route_output_flow(net, fl4, sk);
	अगर (IS_ERR(rt))
		जाओ no_route;
	अगर (opt && opt->opt.is_strictroute && rt->rt_uses_gateway)
		जाओ route_err;
	वापस &rt->dst;

route_err:
	ip_rt_put(rt);
no_route:
	__IP_INC_STATS(net, IPSTATS_MIB_OUTNOROUTES);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(inet_csk_route_child_sock);

/* Decide when to expire the request and when to resend SYN-ACK */
अटल व्योम syn_ack_recalc(काष्ठा request_sock *req,
			   स्थिर पूर्णांक max_syn_ack_retries,
			   स्थिर u8 rskq_defer_accept,
			   पूर्णांक *expire, पूर्णांक *resend)
अणु
	अगर (!rskq_defer_accept) अणु
		*expire = req->num_समयout >= max_syn_ack_retries;
		*resend = 1;
		वापस;
	पूर्ण
	*expire = req->num_समयout >= max_syn_ack_retries &&
		  (!inet_rsk(req)->acked || req->num_समयout >= rskq_defer_accept);
	/* Do not resend जबतक रुकोing क्रम data after ACK,
	 * start to resend on end of deferring period to give
	 * last chance क्रम data or ACK to create established socket.
	 */
	*resend = !inet_rsk(req)->acked ||
		  req->num_समयout >= rskq_defer_accept - 1;
पूर्ण

पूर्णांक inet_rtx_syn_ack(स्थिर काष्ठा sock *parent, काष्ठा request_sock *req)
अणु
	पूर्णांक err = req->rsk_ops->rtx_syn_ack(parent, req);

	अगर (!err)
		req->num_retrans++;
	वापस err;
पूर्ण
EXPORT_SYMBOL(inet_rtx_syn_ack);

/* वापस true अगर req was found in the ehash table */
अटल bool reqsk_queue_unlink(काष्ठा request_sock *req)
अणु
	काष्ठा inet_hashinfo *hashinfo = req_to_sk(req)->sk_prot->h.hashinfo;
	bool found = false;

	अगर (sk_hashed(req_to_sk(req))) अणु
		spinlock_t *lock = inet_ehash_lockp(hashinfo, req->rsk_hash);

		spin_lock(lock);
		found = __sk_nulls_del_node_init_rcu(req_to_sk(req));
		spin_unlock(lock);
	पूर्ण
	अगर (समयr_pending(&req->rsk_समयr) && del_समयr_sync(&req->rsk_समयr))
		reqsk_put(req);
	वापस found;
पूर्ण

bool inet_csk_reqsk_queue_drop(काष्ठा sock *sk, काष्ठा request_sock *req)
अणु
	bool unlinked = reqsk_queue_unlink(req);

	अगर (unlinked) अणु
		reqsk_queue_हटाओd(&inet_csk(sk)->icsk_accept_queue, req);
		reqsk_put(req);
	पूर्ण
	वापस unlinked;
पूर्ण
EXPORT_SYMBOL(inet_csk_reqsk_queue_drop);

व्योम inet_csk_reqsk_queue_drop_and_put(काष्ठा sock *sk, काष्ठा request_sock *req)
अणु
	inet_csk_reqsk_queue_drop(sk, req);
	reqsk_put(req);
पूर्ण
EXPORT_SYMBOL(inet_csk_reqsk_queue_drop_and_put);

अटल व्योम reqsk_समयr_handler(काष्ठा समयr_list *t)
अणु
	काष्ठा request_sock *req = from_समयr(req, t, rsk_समयr);
	काष्ठा sock *sk_listener = req->rsk_listener;
	काष्ठा net *net = sock_net(sk_listener);
	काष्ठा inet_connection_sock *icsk = inet_csk(sk_listener);
	काष्ठा request_sock_queue *queue = &icsk->icsk_accept_queue;
	पूर्णांक max_syn_ack_retries, qlen, expire = 0, resend = 0;

	अगर (inet_sk_state_load(sk_listener) != TCP_LISTEN)
		जाओ drop;

	max_syn_ack_retries = icsk->icsk_syn_retries ? : net->ipv4.sysctl_tcp_synack_retries;
	/* Normally all the खोलोreqs are young and become mature
	 * (i.e. converted to established socket) क्रम first समयout.
	 * If synack was not acknowledged क्रम 1 second, it means
	 * one of the following things: synack was lost, ack was lost,
	 * rtt is high or nobody planned to ack (i.e. synflood).
	 * When server is a bit loaded, queue is populated with old
	 * खोलो requests, reducing effective size of queue.
	 * When server is well loaded, queue size reduces to zero
	 * after several minutes of work. It is not synflood,
	 * it is normal operation. The solution is pruning
	 * too old entries overriding normal समयout, when
	 * situation becomes dangerous.
	 *
	 * Essentially, we reserve half of room क्रम young
	 * embrions; and पात old ones without pity, अगर old
	 * ones are about to clog our table.
	 */
	qlen = reqsk_queue_len(queue);
	अगर ((qlen << 1) > max(8U, READ_ONCE(sk_listener->sk_max_ack_backlog))) अणु
		पूर्णांक young = reqsk_queue_len_young(queue) << 1;

		जबतक (max_syn_ack_retries > 2) अणु
			अगर (qlen < young)
				अवरोध;
			max_syn_ack_retries--;
			young <<= 1;
		पूर्ण
	पूर्ण
	syn_ack_recalc(req, max_syn_ack_retries, READ_ONCE(queue->rskq_defer_accept),
		       &expire, &resend);
	req->rsk_ops->syn_ack_समयout(req);
	अगर (!expire &&
	    (!resend ||
	     !inet_rtx_syn_ack(sk_listener, req) ||
	     inet_rsk(req)->acked)) अणु
		अचिन्हित दीर्घ समयo;

		अगर (req->num_समयout++ == 0)
			atomic_dec(&queue->young);
		समयo = min(TCP_TIMEOUT_INIT << req->num_समयout, TCP_RTO_MAX);
		mod_समयr(&req->rsk_समयr, jअगरfies + समयo);
		वापस;
	पूर्ण
drop:
	inet_csk_reqsk_queue_drop_and_put(sk_listener, req);
पूर्ण

अटल व्योम reqsk_queue_hash_req(काष्ठा request_sock *req,
				 अचिन्हित दीर्घ समयout)
अणु
	समयr_setup(&req->rsk_समयr, reqsk_समयr_handler, TIMER_PINNED);
	mod_समयr(&req->rsk_समयr, jअगरfies + समयout);

	inet_ehash_insert(req_to_sk(req), शून्य, शून्य);
	/* beक्रमe letting lookups find us, make sure all req fields
	 * are committed to memory and refcnt initialized.
	 */
	smp_wmb();
	refcount_set(&req->rsk_refcnt, 2 + 1);
पूर्ण

व्योम inet_csk_reqsk_queue_hash_add(काष्ठा sock *sk, काष्ठा request_sock *req,
				   अचिन्हित दीर्घ समयout)
अणु
	reqsk_queue_hash_req(req, समयout);
	inet_csk_reqsk_queue_added(sk);
पूर्ण
EXPORT_SYMBOL_GPL(inet_csk_reqsk_queue_hash_add);

अटल व्योम inet_clone_ulp(स्थिर काष्ठा request_sock *req, काष्ठा sock *newsk,
			   स्थिर gfp_t priority)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(newsk);

	अगर (!icsk->icsk_ulp_ops)
		वापस;

	अगर (icsk->icsk_ulp_ops->clone)
		icsk->icsk_ulp_ops->clone(req, newsk, priority);
पूर्ण

/**
 *	inet_csk_clone_lock - clone an inet socket, and lock its clone
 *	@sk: the socket to clone
 *	@req: request_sock
 *	@priority: क्रम allocation (%GFP_KERNEL, %GFP_ATOMIC, etc)
 *
 *	Caller must unlock socket even in error path (bh_unlock_sock(newsk))
 */
काष्ठा sock *inet_csk_clone_lock(स्थिर काष्ठा sock *sk,
				 स्थिर काष्ठा request_sock *req,
				 स्थिर gfp_t priority)
अणु
	काष्ठा sock *newsk = sk_clone_lock(sk, priority);

	अगर (newsk) अणु
		काष्ठा inet_connection_sock *newicsk = inet_csk(newsk);

		inet_sk_set_state(newsk, TCP_SYN_RECV);
		newicsk->icsk_bind_hash = शून्य;

		inet_sk(newsk)->inet_dport = inet_rsk(req)->ir_rmt_port;
		inet_sk(newsk)->inet_num = inet_rsk(req)->ir_num;
		inet_sk(newsk)->inet_sport = htons(inet_rsk(req)->ir_num);

		/* listeners have SOCK_RCU_FREE, not the children */
		sock_reset_flag(newsk, SOCK_RCU_FREE);

		inet_sk(newsk)->mc_list = शून्य;

		newsk->sk_mark = inet_rsk(req)->ir_mark;
		atomic64_set(&newsk->sk_cookie,
			     atomic64_पढ़ो(&inet_rsk(req)->ir_cookie));

		newicsk->icsk_retransmits = 0;
		newicsk->icsk_backoff	  = 0;
		newicsk->icsk_probes_out  = 0;
		newicsk->icsk_probes_tstamp = 0;

		/* Deinitialize accept_queue to trap illegal accesses. */
		स_रखो(&newicsk->icsk_accept_queue, 0, माप(newicsk->icsk_accept_queue));

		inet_clone_ulp(req, newsk, priority);

		security_inet_csk_clone(newsk, req);
	पूर्ण
	वापस newsk;
पूर्ण
EXPORT_SYMBOL_GPL(inet_csk_clone_lock);

/*
 * At this poपूर्णांक, there should be no process reference to this
 * socket, and thus no user references at all.  Thereक्रमe we
 * can assume the socket रुकोqueue is inactive and nobody will
 * try to jump onto it.
 */
व्योम inet_csk_destroy_sock(काष्ठा sock *sk)
अणु
	WARN_ON(sk->sk_state != TCP_CLOSE);
	WARN_ON(!sock_flag(sk, SOCK_DEAD));

	/* It cannot be in hash table! */
	WARN_ON(!sk_unhashed(sk));

	/* If it has not 0 inet_sk(sk)->inet_num, it must be bound */
	WARN_ON(inet_sk(sk)->inet_num && !inet_csk(sk)->icsk_bind_hash);

	sk->sk_prot->destroy(sk);

	sk_stream_समाप्त_queues(sk);

	xfrm_sk_मुक्त_policy(sk);

	sk_refcnt_debug_release(sk);

	percpu_counter_dec(sk->sk_prot->orphan_count);

	sock_put(sk);
पूर्ण
EXPORT_SYMBOL(inet_csk_destroy_sock);

/* This function allows to क्रमce a closure of a socket after the call to
 * tcp/dccp_create_खोलोreq_child().
 */
व्योम inet_csk_prepare_क्रमced_बंद(काष्ठा sock *sk)
	__releases(&sk->sk_lock.slock)
अणु
	/* sk_clone_lock locked the socket and set refcnt to 2 */
	bh_unlock_sock(sk);
	sock_put(sk);
	inet_csk_prepare_क्रम_destroy_sock(sk);
	inet_sk(sk)->inet_num = 0;
पूर्ण
EXPORT_SYMBOL(inet_csk_prepare_क्रमced_बंद);

पूर्णांक inet_csk_listen_start(काष्ठा sock *sk, पूर्णांक backlog)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	काष्ठा inet_sock *inet = inet_sk(sk);
	पूर्णांक err = -EADDRINUSE;

	reqsk_queue_alloc(&icsk->icsk_accept_queue);

	sk->sk_ack_backlog = 0;
	inet_csk_delack_init(sk);

	/* There is race winकरोw here: we announce ourselves listening,
	 * but this transition is still not validated by get_port().
	 * It is OK, because this socket enters to hash table only
	 * after validation is complete.
	 */
	inet_sk_state_store(sk, TCP_LISTEN);
	अगर (!sk->sk_prot->get_port(sk, inet->inet_num)) अणु
		inet->inet_sport = htons(inet->inet_num);

		sk_dst_reset(sk);
		err = sk->sk_prot->hash(sk);

		अगर (likely(!err))
			वापस 0;
	पूर्ण

	inet_sk_set_state(sk, TCP_CLOSE);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(inet_csk_listen_start);

अटल व्योम inet_child_क्रमget(काष्ठा sock *sk, काष्ठा request_sock *req,
			      काष्ठा sock *child)
अणु
	sk->sk_prot->disconnect(child, O_NONBLOCK);

	sock_orphan(child);

	percpu_counter_inc(sk->sk_prot->orphan_count);

	अगर (sk->sk_protocol == IPPROTO_TCP && tcp_rsk(req)->tfo_listener) अणु
		BUG_ON(rcu_access_poपूर्णांकer(tcp_sk(child)->fastखोलो_rsk) != req);
		BUG_ON(sk != req->rsk_listener);

		/* Paranoid, to prevent race condition अगर
		 * an inbound pkt destined क्रम child is
		 * blocked by sock lock in tcp_v4_rcv().
		 * Also to satisfy an निश्चितion in
		 * tcp_v4_destroy_sock().
		 */
		RCU_INIT_POINTER(tcp_sk(child)->fastखोलो_rsk, शून्य);
	पूर्ण
	inet_csk_destroy_sock(child);
पूर्ण

काष्ठा sock *inet_csk_reqsk_queue_add(काष्ठा sock *sk,
				      काष्ठा request_sock *req,
				      काष्ठा sock *child)
अणु
	काष्ठा request_sock_queue *queue = &inet_csk(sk)->icsk_accept_queue;

	spin_lock(&queue->rskq_lock);
	अगर (unlikely(sk->sk_state != TCP_LISTEN)) अणु
		inet_child_क्रमget(sk, req, child);
		child = शून्य;
	पूर्ण अन्यथा अणु
		req->sk = child;
		req->dl_next = शून्य;
		अगर (queue->rskq_accept_head == शून्य)
			WRITE_ONCE(queue->rskq_accept_head, req);
		अन्यथा
			queue->rskq_accept_tail->dl_next = req;
		queue->rskq_accept_tail = req;
		sk_acceptq_added(sk);
	पूर्ण
	spin_unlock(&queue->rskq_lock);
	वापस child;
पूर्ण
EXPORT_SYMBOL(inet_csk_reqsk_queue_add);

काष्ठा sock *inet_csk_complete_hashdance(काष्ठा sock *sk, काष्ठा sock *child,
					 काष्ठा request_sock *req, bool own_req)
अणु
	अगर (own_req) अणु
		inet_csk_reqsk_queue_drop(sk, req);
		reqsk_queue_हटाओd(&inet_csk(sk)->icsk_accept_queue, req);
		अगर (inet_csk_reqsk_queue_add(sk, req, child))
			वापस child;
	पूर्ण
	/* Too bad, another child took ownership of the request, unकरो. */
	bh_unlock_sock(child);
	sock_put(child);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(inet_csk_complete_hashdance);

/*
 *	This routine बंदs sockets which have been at least partially
 *	खोलोed, but not yet accepted.
 */
व्योम inet_csk_listen_stop(काष्ठा sock *sk)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	काष्ठा request_sock_queue *queue = &icsk->icsk_accept_queue;
	काष्ठा request_sock *next, *req;

	/* Following specs, it would be better either to send FIN
	 * (and enter FIN-WAIT-1, it is normal बंद)
	 * or to send active reset (पात).
	 * Certainly, it is pretty dangerous जबतक synflood, but it is
	 * bad justअगरication क्रम our negligence 8)
	 * To be honest, we are not able to make either
	 * of the variants now.			--ANK
	 */
	जबतक ((req = reqsk_queue_हटाओ(queue, sk)) != शून्य) अणु
		काष्ठा sock *child = req->sk;

		local_bh_disable();
		bh_lock_sock(child);
		WARN_ON(sock_owned_by_user(child));
		sock_hold(child);

		inet_child_क्रमget(sk, req, child);
		reqsk_put(req);
		bh_unlock_sock(child);
		local_bh_enable();
		sock_put(child);

		cond_resched();
	पूर्ण
	अगर (queue->fastखोलोq.rskq_rst_head) अणु
		/* Free all the reqs queued in rskq_rst_head. */
		spin_lock_bh(&queue->fastखोलोq.lock);
		req = queue->fastखोलोq.rskq_rst_head;
		queue->fastखोलोq.rskq_rst_head = शून्य;
		spin_unlock_bh(&queue->fastखोलोq.lock);
		जबतक (req != शून्य) अणु
			next = req->dl_next;
			reqsk_put(req);
			req = next;
		पूर्ण
	पूर्ण
	WARN_ON_ONCE(sk->sk_ack_backlog);
पूर्ण
EXPORT_SYMBOL_GPL(inet_csk_listen_stop);

व्योम inet_csk_addr2sockaddr(काष्ठा sock *sk, काष्ठा sockaddr *uaddr)
अणु
	काष्ठा sockaddr_in *sin = (काष्ठा sockaddr_in *)uaddr;
	स्थिर काष्ठा inet_sock *inet = inet_sk(sk);

	sin->sin_family		= AF_INET;
	sin->sin_addr.s_addr	= inet->inet_daddr;
	sin->sin_port		= inet->inet_dport;
पूर्ण
EXPORT_SYMBOL_GPL(inet_csk_addr2sockaddr);

अटल काष्ठा dst_entry *inet_csk_rebuild_route(काष्ठा sock *sk, काष्ठा flowi *fl)
अणु
	स्थिर काष्ठा inet_sock *inet = inet_sk(sk);
	स्थिर काष्ठा ip_options_rcu *inet_opt;
	__be32 daddr = inet->inet_daddr;
	काष्ठा flowi4 *fl4;
	काष्ठा rtable *rt;

	rcu_पढ़ो_lock();
	inet_opt = rcu_dereference(inet->inet_opt);
	अगर (inet_opt && inet_opt->opt.srr)
		daddr = inet_opt->opt.faddr;
	fl4 = &fl->u.ip4;
	rt = ip_route_output_ports(sock_net(sk), fl4, sk, daddr,
				   inet->inet_saddr, inet->inet_dport,
				   inet->inet_sport, sk->sk_protocol,
				   RT_CONN_FLAGS(sk), sk->sk_bound_dev_अगर);
	अगर (IS_ERR(rt))
		rt = शून्य;
	अगर (rt)
		sk_setup_caps(sk, &rt->dst);
	rcu_पढ़ो_unlock();

	वापस &rt->dst;
पूर्ण

काष्ठा dst_entry *inet_csk_update_pmtu(काष्ठा sock *sk, u32 mtu)
अणु
	काष्ठा dst_entry *dst = __sk_dst_check(sk, 0);
	काष्ठा inet_sock *inet = inet_sk(sk);

	अगर (!dst) अणु
		dst = inet_csk_rebuild_route(sk, &inet->cork.fl);
		अगर (!dst)
			जाओ out;
	पूर्ण
	dst->ops->update_pmtu(dst, sk, शून्य, mtu, true);

	dst = __sk_dst_check(sk, 0);
	अगर (!dst)
		dst = inet_csk_rebuild_route(sk, &inet->cork.fl);
out:
	वापस dst;
पूर्ण
EXPORT_SYMBOL_GPL(inet_csk_update_pmtu);
