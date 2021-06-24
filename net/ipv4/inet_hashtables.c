<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		Generic INET transport hashtables
 *
 * Authors:	Lotsa people, from code originally in tcp
 */

#समावेश <linux/module.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/रुको.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/memblock.h>

#समावेश <net/addrconf.h>
#समावेश <net/inet_connection_sock.h>
#समावेश <net/inet_hashtables.h>
#अगर IS_ENABLED(CONFIG_IPV6)
#समावेश <net/inet6_hashtables.h>
#पूर्ण_अगर
#समावेश <net/secure_seq.h>
#समावेश <net/ip.h>
#समावेश <net/tcp.h>
#समावेश <net/sock_reuseport.h>

अटल u32 inet_ehashfn(स्थिर काष्ठा net *net, स्थिर __be32 laddr,
			स्थिर __u16 lport, स्थिर __be32 faddr,
			स्थिर __be16 fport)
अणु
	अटल u32 inet_ehash_secret __पढ़ो_mostly;

	net_get_अक्रमom_once(&inet_ehash_secret, माप(inet_ehash_secret));

	वापस __inet_ehashfn(laddr, lport, faddr, fport,
			      inet_ehash_secret + net_hash_mix(net));
पूर्ण

/* This function handles inet_sock, but also समयरुको and request sockets
 * क्रम IPv4/IPv6.
 */
अटल u32 sk_ehashfn(स्थिर काष्ठा sock *sk)
अणु
#अगर IS_ENABLED(CONFIG_IPV6)
	अगर (sk->sk_family == AF_INET6 &&
	    !ipv6_addr_v4mapped(&sk->sk_v6_daddr))
		वापस inet6_ehashfn(sock_net(sk),
				     &sk->sk_v6_rcv_saddr, sk->sk_num,
				     &sk->sk_v6_daddr, sk->sk_dport);
#पूर्ण_अगर
	वापस inet_ehashfn(sock_net(sk),
			    sk->sk_rcv_saddr, sk->sk_num,
			    sk->sk_daddr, sk->sk_dport);
पूर्ण

/*
 * Allocate and initialize a new local port bind bucket.
 * The bindhash mutex क्रम snum's hash chain must be held here.
 */
काष्ठा inet_bind_bucket *inet_bind_bucket_create(काष्ठा kmem_cache *cachep,
						 काष्ठा net *net,
						 काष्ठा inet_bind_hashbucket *head,
						 स्थिर अचिन्हित लघु snum,
						 पूर्णांक l3mdev)
अणु
	काष्ठा inet_bind_bucket *tb = kmem_cache_alloc(cachep, GFP_ATOMIC);

	अगर (tb) अणु
		ग_लिखो_pnet(&tb->ib_net, net);
		tb->l3mdev    = l3mdev;
		tb->port      = snum;
		tb->fastreuse = 0;
		tb->fastreuseport = 0;
		INIT_HLIST_HEAD(&tb->owners);
		hlist_add_head(&tb->node, &head->chain);
	पूर्ण
	वापस tb;
पूर्ण

/*
 * Caller must hold hashbucket lock क्रम this tb with local BH disabled
 */
व्योम inet_bind_bucket_destroy(काष्ठा kmem_cache *cachep, काष्ठा inet_bind_bucket *tb)
अणु
	अगर (hlist_empty(&tb->owners)) अणु
		__hlist_del(&tb->node);
		kmem_cache_मुक्त(cachep, tb);
	पूर्ण
पूर्ण

व्योम inet_bind_hash(काष्ठा sock *sk, काष्ठा inet_bind_bucket *tb,
		    स्थिर अचिन्हित लघु snum)
अणु
	inet_sk(sk)->inet_num = snum;
	sk_add_bind_node(sk, &tb->owners);
	inet_csk(sk)->icsk_bind_hash = tb;
पूर्ण

/*
 * Get rid of any references to a local port held by the given sock.
 */
अटल व्योम __inet_put_port(काष्ठा sock *sk)
अणु
	काष्ठा inet_hashinfo *hashinfo = sk->sk_prot->h.hashinfo;
	स्थिर पूर्णांक bhash = inet_bhashfn(sock_net(sk), inet_sk(sk)->inet_num,
			hashinfo->bhash_size);
	काष्ठा inet_bind_hashbucket *head = &hashinfo->bhash[bhash];
	काष्ठा inet_bind_bucket *tb;

	spin_lock(&head->lock);
	tb = inet_csk(sk)->icsk_bind_hash;
	__sk_del_bind_node(sk);
	inet_csk(sk)->icsk_bind_hash = शून्य;
	inet_sk(sk)->inet_num = 0;
	inet_bind_bucket_destroy(hashinfo->bind_bucket_cachep, tb);
	spin_unlock(&head->lock);
पूर्ण

व्योम inet_put_port(काष्ठा sock *sk)
अणु
	local_bh_disable();
	__inet_put_port(sk);
	local_bh_enable();
पूर्ण
EXPORT_SYMBOL(inet_put_port);

पूर्णांक __inet_inherit_port(स्थिर काष्ठा sock *sk, काष्ठा sock *child)
अणु
	काष्ठा inet_hashinfo *table = sk->sk_prot->h.hashinfo;
	अचिन्हित लघु port = inet_sk(child)->inet_num;
	स्थिर पूर्णांक bhash = inet_bhashfn(sock_net(sk), port,
			table->bhash_size);
	काष्ठा inet_bind_hashbucket *head = &table->bhash[bhash];
	काष्ठा inet_bind_bucket *tb;
	पूर्णांक l3mdev;

	spin_lock(&head->lock);
	tb = inet_csk(sk)->icsk_bind_hash;
	अगर (unlikely(!tb)) अणु
		spin_unlock(&head->lock);
		वापस -ENOENT;
	पूर्ण
	अगर (tb->port != port) अणु
		l3mdev = inet_sk_bound_l3mdev(sk);

		/* NOTE: using tproxy and redirecting skbs to a proxy
		 * on a dअगरferent listener port अवरोधs the assumption
		 * that the listener socket's icsk_bind_hash is the same
		 * as that of the child socket. We have to look up or
		 * create a new bind bucket क्रम the child here. */
		inet_bind_bucket_क्रम_each(tb, &head->chain) अणु
			अगर (net_eq(ib_net(tb), sock_net(sk)) &&
			    tb->l3mdev == l3mdev && tb->port == port)
				अवरोध;
		पूर्ण
		अगर (!tb) अणु
			tb = inet_bind_bucket_create(table->bind_bucket_cachep,
						     sock_net(sk), head, port,
						     l3mdev);
			अगर (!tb) अणु
				spin_unlock(&head->lock);
				वापस -ENOMEM;
			पूर्ण
		पूर्ण
		inet_csk_update_fastreuse(tb, child);
	पूर्ण
	inet_bind_hash(child, tb, port);
	spin_unlock(&head->lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(__inet_inherit_port);

अटल काष्ठा inet_listen_hashbucket *
inet_lhash2_bucket_sk(काष्ठा inet_hashinfo *h, काष्ठा sock *sk)
अणु
	u32 hash;

#अगर IS_ENABLED(CONFIG_IPV6)
	अगर (sk->sk_family == AF_INET6)
		hash = ipv6_portaddr_hash(sock_net(sk),
					  &sk->sk_v6_rcv_saddr,
					  inet_sk(sk)->inet_num);
	अन्यथा
#पूर्ण_अगर
		hash = ipv4_portaddr_hash(sock_net(sk),
					  inet_sk(sk)->inet_rcv_saddr,
					  inet_sk(sk)->inet_num);
	वापस inet_lhash2_bucket(h, hash);
पूर्ण

अटल व्योम inet_hash2(काष्ठा inet_hashinfo *h, काष्ठा sock *sk)
अणु
	काष्ठा inet_listen_hashbucket *ilb2;

	अगर (!h->lhash2)
		वापस;

	ilb2 = inet_lhash2_bucket_sk(h, sk);

	spin_lock(&ilb2->lock);
	अगर (sk->sk_reuseport && sk->sk_family == AF_INET6)
		hlist_add_tail_rcu(&inet_csk(sk)->icsk_listen_portaddr_node,
				   &ilb2->head);
	अन्यथा
		hlist_add_head_rcu(&inet_csk(sk)->icsk_listen_portaddr_node,
				   &ilb2->head);
	ilb2->count++;
	spin_unlock(&ilb2->lock);
पूर्ण

अटल व्योम inet_unhash2(काष्ठा inet_hashinfo *h, काष्ठा sock *sk)
अणु
	काष्ठा inet_listen_hashbucket *ilb2;

	अगर (!h->lhash2 ||
	    WARN_ON_ONCE(hlist_unhashed(&inet_csk(sk)->icsk_listen_portaddr_node)))
		वापस;

	ilb2 = inet_lhash2_bucket_sk(h, sk);

	spin_lock(&ilb2->lock);
	hlist_del_init_rcu(&inet_csk(sk)->icsk_listen_portaddr_node);
	ilb2->count--;
	spin_unlock(&ilb2->lock);
पूर्ण

अटल अंतरभूत पूर्णांक compute_score(काष्ठा sock *sk, काष्ठा net *net,
				स्थिर अचिन्हित लघु hnum, स्थिर __be32 daddr,
				स्थिर पूर्णांक dअगर, स्थिर पूर्णांक sdअगर)
अणु
	पूर्णांक score = -1;

	अगर (net_eq(sock_net(sk), net) && sk->sk_num == hnum &&
			!ipv6_only_sock(sk)) अणु
		अगर (sk->sk_rcv_saddr != daddr)
			वापस -1;

		अगर (!inet_sk_bound_dev_eq(net, sk->sk_bound_dev_अगर, dअगर, sdअगर))
			वापस -1;

		score = sk->sk_family == PF_INET ? 2 : 1;
		अगर (READ_ONCE(sk->sk_incoming_cpu) == raw_smp_processor_id())
			score++;
	पूर्ण
	वापस score;
पूर्ण

अटल अंतरभूत काष्ठा sock *lookup_reuseport(काष्ठा net *net, काष्ठा sock *sk,
					    काष्ठा sk_buff *skb, पूर्णांक करोff,
					    __be32 saddr, __be16 sport,
					    __be32 daddr, अचिन्हित लघु hnum)
अणु
	काष्ठा sock *reuse_sk = शून्य;
	u32 phash;

	अगर (sk->sk_reuseport) अणु
		phash = inet_ehashfn(net, daddr, hnum, saddr, sport);
		reuse_sk = reuseport_select_sock(sk, phash, skb, करोff);
	पूर्ण
	वापस reuse_sk;
पूर्ण

/*
 * Here are some nice properties to exploit here. The BSD API
 * करोes not allow a listening sock to specअगरy the remote port nor the
 * remote address क्रम the connection. So always assume those are both
 * wildcarded during the search since they can never be otherwise.
 */

/* called with rcu_पढ़ो_lock() : No refcount taken on the socket */
अटल काष्ठा sock *inet_lhash2_lookup(काष्ठा net *net,
				काष्ठा inet_listen_hashbucket *ilb2,
				काष्ठा sk_buff *skb, पूर्णांक करोff,
				स्थिर __be32 saddr, __be16 sport,
				स्थिर __be32 daddr, स्थिर अचिन्हित लघु hnum,
				स्थिर पूर्णांक dअगर, स्थिर पूर्णांक sdअगर)
अणु
	काष्ठा inet_connection_sock *icsk;
	काष्ठा sock *sk, *result = शून्य;
	पूर्णांक score, hiscore = 0;

	inet_lhash2_क्रम_each_icsk_rcu(icsk, &ilb2->head) अणु
		sk = (काष्ठा sock *)icsk;
		score = compute_score(sk, net, hnum, daddr, dअगर, sdअगर);
		अगर (score > hiscore) अणु
			result = lookup_reuseport(net, sk, skb, करोff,
						  saddr, sport, daddr, hnum);
			अगर (result)
				वापस result;

			result = sk;
			hiscore = score;
		पूर्ण
	पूर्ण

	वापस result;
पूर्ण

अटल अंतरभूत काष्ठा sock *inet_lookup_run_bpf(काष्ठा net *net,
					       काष्ठा inet_hashinfo *hashinfo,
					       काष्ठा sk_buff *skb, पूर्णांक करोff,
					       __be32 saddr, __be16 sport,
					       __be32 daddr, u16 hnum)
अणु
	काष्ठा sock *sk, *reuse_sk;
	bool no_reuseport;

	अगर (hashinfo != &tcp_hashinfo)
		वापस शून्य; /* only TCP is supported */

	no_reuseport = bpf_sk_lookup_run_v4(net, IPPROTO_TCP,
					    saddr, sport, daddr, hnum, &sk);
	अगर (no_reuseport || IS_ERR_OR_शून्य(sk))
		वापस sk;

	reuse_sk = lookup_reuseport(net, sk, skb, करोff, saddr, sport, daddr, hnum);
	अगर (reuse_sk)
		sk = reuse_sk;
	वापस sk;
पूर्ण

काष्ठा sock *__inet_lookup_listener(काष्ठा net *net,
				    काष्ठा inet_hashinfo *hashinfo,
				    काष्ठा sk_buff *skb, पूर्णांक करोff,
				    स्थिर __be32 saddr, __be16 sport,
				    स्थिर __be32 daddr, स्थिर अचिन्हित लघु hnum,
				    स्थिर पूर्णांक dअगर, स्थिर पूर्णांक sdअगर)
अणु
	काष्ठा inet_listen_hashbucket *ilb2;
	काष्ठा sock *result = शून्य;
	अचिन्हित पूर्णांक hash2;

	/* Lookup redirect from BPF */
	अगर (अटल_branch_unlikely(&bpf_sk_lookup_enabled)) अणु
		result = inet_lookup_run_bpf(net, hashinfo, skb, करोff,
					     saddr, sport, daddr, hnum);
		अगर (result)
			जाओ करोne;
	पूर्ण

	hash2 = ipv4_portaddr_hash(net, daddr, hnum);
	ilb2 = inet_lhash2_bucket(hashinfo, hash2);

	result = inet_lhash2_lookup(net, ilb2, skb, करोff,
				    saddr, sport, daddr, hnum,
				    dअगर, sdअगर);
	अगर (result)
		जाओ करोne;

	/* Lookup lhash2 with INADDR_ANY */
	hash2 = ipv4_portaddr_hash(net, htonl(INADDR_ANY), hnum);
	ilb2 = inet_lhash2_bucket(hashinfo, hash2);

	result = inet_lhash2_lookup(net, ilb2, skb, करोff,
				    saddr, sport, htonl(INADDR_ANY), hnum,
				    dअगर, sdअगर);
करोne:
	अगर (IS_ERR(result))
		वापस शून्य;
	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(__inet_lookup_listener);

/* All sockets share common refcount, but have dअगरferent deकाष्ठाors */
व्योम sock_gen_put(काष्ठा sock *sk)
अणु
	अगर (!refcount_dec_and_test(&sk->sk_refcnt))
		वापस;

	अगर (sk->sk_state == TCP_TIME_WAIT)
		inet_twsk_मुक्त(inet_twsk(sk));
	अन्यथा अगर (sk->sk_state == TCP_NEW_SYN_RECV)
		reqsk_मुक्त(inet_reqsk(sk));
	अन्यथा
		sk_मुक्त(sk);
पूर्ण
EXPORT_SYMBOL_GPL(sock_gen_put);

व्योम sock_edemux(काष्ठा sk_buff *skb)
अणु
	sock_gen_put(skb->sk);
पूर्ण
EXPORT_SYMBOL(sock_edemux);

काष्ठा sock *__inet_lookup_established(काष्ठा net *net,
				  काष्ठा inet_hashinfo *hashinfo,
				  स्थिर __be32 saddr, स्थिर __be16 sport,
				  स्थिर __be32 daddr, स्थिर u16 hnum,
				  स्थिर पूर्णांक dअगर, स्थिर पूर्णांक sdअगर)
अणु
	INET_ADDR_COOKIE(acookie, saddr, daddr);
	स्थिर __portpair ports = INET_COMBINED_PORTS(sport, hnum);
	काष्ठा sock *sk;
	स्थिर काष्ठा hlist_nulls_node *node;
	/* Optimize here क्रम direct hit, only listening connections can
	 * have wildcards anyways.
	 */
	अचिन्हित पूर्णांक hash = inet_ehashfn(net, daddr, hnum, saddr, sport);
	अचिन्हित पूर्णांक slot = hash & hashinfo->ehash_mask;
	काष्ठा inet_ehash_bucket *head = &hashinfo->ehash[slot];

begin:
	sk_nulls_क्रम_each_rcu(sk, node, &head->chain) अणु
		अगर (sk->sk_hash != hash)
			जारी;
		अगर (likely(INET_MATCH(sk, net, acookie,
				      saddr, daddr, ports, dअगर, sdअगर))) अणु
			अगर (unlikely(!refcount_inc_not_zero(&sk->sk_refcnt)))
				जाओ out;
			अगर (unlikely(!INET_MATCH(sk, net, acookie,
						 saddr, daddr, ports,
						 dअगर, sdअगर))) अणु
				sock_gen_put(sk);
				जाओ begin;
			पूर्ण
			जाओ found;
		पूर्ण
	पूर्ण
	/*
	 * अगर the nulls value we got at the end of this lookup is
	 * not the expected one, we must restart lookup.
	 * We probably met an item that was moved to another chain.
	 */
	अगर (get_nulls_value(node) != slot)
		जाओ begin;
out:
	sk = शून्य;
found:
	वापस sk;
पूर्ण
EXPORT_SYMBOL_GPL(__inet_lookup_established);

/* called with local bh disabled */
अटल पूर्णांक __inet_check_established(काष्ठा inet_समयरुको_death_row *death_row,
				    काष्ठा sock *sk, __u16 lport,
				    काष्ठा inet_समयरुको_sock **twp)
अणु
	काष्ठा inet_hashinfo *hinfo = death_row->hashinfo;
	काष्ठा inet_sock *inet = inet_sk(sk);
	__be32 daddr = inet->inet_rcv_saddr;
	__be32 saddr = inet->inet_daddr;
	पूर्णांक dअगर = sk->sk_bound_dev_अगर;
	काष्ठा net *net = sock_net(sk);
	पूर्णांक sdअगर = l3mdev_master_अगरindex_by_index(net, dअगर);
	INET_ADDR_COOKIE(acookie, saddr, daddr);
	स्थिर __portpair ports = INET_COMBINED_PORTS(inet->inet_dport, lport);
	अचिन्हित पूर्णांक hash = inet_ehashfn(net, daddr, lport,
					 saddr, inet->inet_dport);
	काष्ठा inet_ehash_bucket *head = inet_ehash_bucket(hinfo, hash);
	spinlock_t *lock = inet_ehash_lockp(hinfo, hash);
	काष्ठा sock *sk2;
	स्थिर काष्ठा hlist_nulls_node *node;
	काष्ठा inet_समयरुको_sock *tw = शून्य;

	spin_lock(lock);

	sk_nulls_क्रम_each(sk2, node, &head->chain) अणु
		अगर (sk2->sk_hash != hash)
			जारी;

		अगर (likely(INET_MATCH(sk2, net, acookie,
					 saddr, daddr, ports, dअगर, sdअगर))) अणु
			अगर (sk2->sk_state == TCP_TIME_WAIT) अणु
				tw = inet_twsk(sk2);
				अगर (twsk_unique(sk, sk2, twp))
					अवरोध;
			पूर्ण
			जाओ not_unique;
		पूर्ण
	पूर्ण

	/* Must record num and sport now. Otherwise we will see
	 * in hash table socket with a funny identity.
	 */
	inet->inet_num = lport;
	inet->inet_sport = htons(lport);
	sk->sk_hash = hash;
	WARN_ON(!sk_unhashed(sk));
	__sk_nulls_add_node_rcu(sk, &head->chain);
	अगर (tw) अणु
		sk_nulls_del_node_init_rcu((काष्ठा sock *)tw);
		__NET_INC_STATS(net, LINUX_MIB_TIMEWAITRECYCLED);
	पूर्ण
	spin_unlock(lock);
	sock_prot_inuse_add(sock_net(sk), sk->sk_prot, 1);

	अगर (twp) अणु
		*twp = tw;
	पूर्ण अन्यथा अगर (tw) अणु
		/* Silly. Should hash-dance instead... */
		inet_twsk_deschedule_put(tw);
	पूर्ण
	वापस 0;

not_unique:
	spin_unlock(lock);
	वापस -EADDRNOTAVAIL;
पूर्ण

अटल u32 inet_sk_port_offset(स्थिर काष्ठा sock *sk)
अणु
	स्थिर काष्ठा inet_sock *inet = inet_sk(sk);

	वापस secure_ipv4_port_ephemeral(inet->inet_rcv_saddr,
					  inet->inet_daddr,
					  inet->inet_dport);
पूर्ण

/* Searches क्रम an exsiting socket in the ehash bucket list.
 * Returns true अगर found, false otherwise.
 */
अटल bool inet_ehash_lookup_by_sk(काष्ठा sock *sk,
				    काष्ठा hlist_nulls_head *list)
अणु
	स्थिर __portpair ports = INET_COMBINED_PORTS(sk->sk_dport, sk->sk_num);
	स्थिर पूर्णांक sdअगर = sk->sk_bound_dev_अगर;
	स्थिर पूर्णांक dअगर = sk->sk_bound_dev_अगर;
	स्थिर काष्ठा hlist_nulls_node *node;
	काष्ठा net *net = sock_net(sk);
	काष्ठा sock *esk;

	INET_ADDR_COOKIE(acookie, sk->sk_daddr, sk->sk_rcv_saddr);

	sk_nulls_क्रम_each_rcu(esk, node, list) अणु
		अगर (esk->sk_hash != sk->sk_hash)
			जारी;
		अगर (sk->sk_family == AF_INET) अणु
			अगर (unlikely(INET_MATCH(esk, net, acookie,
						sk->sk_daddr,
						sk->sk_rcv_saddr,
						ports, dअगर, sdअगर))) अणु
				वापस true;
			पूर्ण
		पूर्ण
#अगर IS_ENABLED(CONFIG_IPV6)
		अन्यथा अगर (sk->sk_family == AF_INET6) अणु
			अगर (unlikely(INET6_MATCH(esk, net,
						 &sk->sk_v6_daddr,
						 &sk->sk_v6_rcv_saddr,
						 ports, dअगर, sdअगर))) अणु
				वापस true;
			पूर्ण
		पूर्ण
#पूर्ण_अगर
	पूर्ण
	वापस false;
पूर्ण

/* Insert a socket पूर्णांकo ehash, and eventually हटाओ another one
 * (The another one can be a SYN_RECV or TIMEWAIT)
 * If an existing socket alपढ़ोy exists, socket sk is not inserted,
 * and sets found_dup_sk parameter to true.
 */
bool inet_ehash_insert(काष्ठा sock *sk, काष्ठा sock *osk, bool *found_dup_sk)
अणु
	काष्ठा inet_hashinfo *hashinfo = sk->sk_prot->h.hashinfo;
	काष्ठा hlist_nulls_head *list;
	काष्ठा inet_ehash_bucket *head;
	spinlock_t *lock;
	bool ret = true;

	WARN_ON_ONCE(!sk_unhashed(sk));

	sk->sk_hash = sk_ehashfn(sk);
	head = inet_ehash_bucket(hashinfo, sk->sk_hash);
	list = &head->chain;
	lock = inet_ehash_lockp(hashinfo, sk->sk_hash);

	spin_lock(lock);
	अगर (osk) अणु
		WARN_ON_ONCE(sk->sk_hash != osk->sk_hash);
		ret = sk_nulls_del_node_init_rcu(osk);
	पूर्ण अन्यथा अगर (found_dup_sk) अणु
		*found_dup_sk = inet_ehash_lookup_by_sk(sk, list);
		अगर (*found_dup_sk)
			ret = false;
	पूर्ण

	अगर (ret)
		__sk_nulls_add_node_rcu(sk, list);

	spin_unlock(lock);

	वापस ret;
पूर्ण

bool inet_ehash_nolisten(काष्ठा sock *sk, काष्ठा sock *osk, bool *found_dup_sk)
अणु
	bool ok = inet_ehash_insert(sk, osk, found_dup_sk);

	अगर (ok) अणु
		sock_prot_inuse_add(sock_net(sk), sk->sk_prot, 1);
	पूर्ण अन्यथा अणु
		percpu_counter_inc(sk->sk_prot->orphan_count);
		inet_sk_set_state(sk, TCP_CLOSE);
		sock_set_flag(sk, SOCK_DEAD);
		inet_csk_destroy_sock(sk);
	पूर्ण
	वापस ok;
पूर्ण
EXPORT_SYMBOL_GPL(inet_ehash_nolisten);

अटल पूर्णांक inet_reuseport_add_sock(काष्ठा sock *sk,
				   काष्ठा inet_listen_hashbucket *ilb)
अणु
	काष्ठा inet_bind_bucket *tb = inet_csk(sk)->icsk_bind_hash;
	स्थिर काष्ठा hlist_nulls_node *node;
	काष्ठा sock *sk2;
	kuid_t uid = sock_i_uid(sk);

	sk_nulls_क्रम_each_rcu(sk2, node, &ilb->nulls_head) अणु
		अगर (sk2 != sk &&
		    sk2->sk_family == sk->sk_family &&
		    ipv6_only_sock(sk2) == ipv6_only_sock(sk) &&
		    sk2->sk_bound_dev_अगर == sk->sk_bound_dev_अगर &&
		    inet_csk(sk2)->icsk_bind_hash == tb &&
		    sk2->sk_reuseport && uid_eq(uid, sock_i_uid(sk2)) &&
		    inet_rcv_saddr_equal(sk, sk2, false))
			वापस reuseport_add_sock(sk, sk2,
						  inet_rcv_saddr_any(sk));
	पूर्ण

	वापस reuseport_alloc(sk, inet_rcv_saddr_any(sk));
पूर्ण

पूर्णांक __inet_hash(काष्ठा sock *sk, काष्ठा sock *osk)
अणु
	काष्ठा inet_hashinfo *hashinfo = sk->sk_prot->h.hashinfo;
	काष्ठा inet_listen_hashbucket *ilb;
	पूर्णांक err = 0;

	अगर (sk->sk_state != TCP_LISTEN) अणु
		inet_ehash_nolisten(sk, osk, शून्य);
		वापस 0;
	पूर्ण
	WARN_ON(!sk_unhashed(sk));
	ilb = &hashinfo->listening_hash[inet_sk_listen_hashfn(sk)];

	spin_lock(&ilb->lock);
	अगर (sk->sk_reuseport) अणु
		err = inet_reuseport_add_sock(sk, ilb);
		अगर (err)
			जाओ unlock;
	पूर्ण
	अगर (IS_ENABLED(CONFIG_IPV6) && sk->sk_reuseport &&
		sk->sk_family == AF_INET6)
		__sk_nulls_add_node_tail_rcu(sk, &ilb->nulls_head);
	अन्यथा
		__sk_nulls_add_node_rcu(sk, &ilb->nulls_head);
	inet_hash2(hashinfo, sk);
	ilb->count++;
	sock_set_flag(sk, SOCK_RCU_FREE);
	sock_prot_inuse_add(sock_net(sk), sk->sk_prot, 1);
unlock:
	spin_unlock(&ilb->lock);

	वापस err;
पूर्ण
EXPORT_SYMBOL(__inet_hash);

पूर्णांक inet_hash(काष्ठा sock *sk)
अणु
	पूर्णांक err = 0;

	अगर (sk->sk_state != TCP_CLOSE) अणु
		local_bh_disable();
		err = __inet_hash(sk, शून्य);
		local_bh_enable();
	पूर्ण

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(inet_hash);

व्योम inet_unhash(काष्ठा sock *sk)
अणु
	काष्ठा inet_hashinfo *hashinfo = sk->sk_prot->h.hashinfo;
	काष्ठा inet_listen_hashbucket *ilb = शून्य;
	spinlock_t *lock;

	अगर (sk_unhashed(sk))
		वापस;

	अगर (sk->sk_state == TCP_LISTEN) अणु
		ilb = &hashinfo->listening_hash[inet_sk_listen_hashfn(sk)];
		lock = &ilb->lock;
	पूर्ण अन्यथा अणु
		lock = inet_ehash_lockp(hashinfo, sk->sk_hash);
	पूर्ण
	spin_lock_bh(lock);
	अगर (sk_unhashed(sk))
		जाओ unlock;

	अगर (rcu_access_poपूर्णांकer(sk->sk_reuseport_cb))
		reuseport_detach_sock(sk);
	अगर (ilb) अणु
		inet_unhash2(hashinfo, sk);
		ilb->count--;
	पूर्ण
	__sk_nulls_del_node_init_rcu(sk);
	sock_prot_inuse_add(sock_net(sk), sk->sk_prot, -1);
unlock:
	spin_unlock_bh(lock);
पूर्ण
EXPORT_SYMBOL_GPL(inet_unhash);

/* RFC 6056 3.3.4.  Algorithm 4: Double-Hash Port Selection Algorithm
 * Note that we use 32bit पूर्णांकegers (vs RFC 'short integers')
 * because 2^16 is not a multiple of num_ephemeral and this
 * property might be used by clever attacker.
 * RFC claims using TABLE_LENGTH=10 buckets gives an improvement,
 * we use 256 instead to really give more isolation and
 * privacy, this only consumes 1 KB of kernel memory.
 */
#घोषणा INET_TABLE_PERTURB_SHIFT 8
अटल u32 table_perturb[1 << INET_TABLE_PERTURB_SHIFT];

पूर्णांक __inet_hash_connect(काष्ठा inet_समयरुको_death_row *death_row,
		काष्ठा sock *sk, u32 port_offset,
		पूर्णांक (*check_established)(काष्ठा inet_समयरुको_death_row *,
			काष्ठा sock *, __u16, काष्ठा inet_समयरुको_sock **))
अणु
	काष्ठा inet_hashinfo *hinfo = death_row->hashinfo;
	काष्ठा inet_समयरुको_sock *tw = शून्य;
	काष्ठा inet_bind_hashbucket *head;
	पूर्णांक port = inet_sk(sk)->inet_num;
	काष्ठा net *net = sock_net(sk);
	काष्ठा inet_bind_bucket *tb;
	u32 reमुख्यing, offset;
	पूर्णांक ret, i, low, high;
	पूर्णांक l3mdev;
	u32 index;

	अगर (port) अणु
		head = &hinfo->bhash[inet_bhashfn(net, port,
						  hinfo->bhash_size)];
		tb = inet_csk(sk)->icsk_bind_hash;
		spin_lock_bh(&head->lock);
		अगर (sk_head(&tb->owners) == sk && !sk->sk_bind_node.next) अणु
			inet_ehash_nolisten(sk, शून्य, शून्य);
			spin_unlock_bh(&head->lock);
			वापस 0;
		पूर्ण
		spin_unlock(&head->lock);
		/* No definite answer... Walk to established hash table */
		ret = check_established(death_row, sk, port, शून्य);
		local_bh_enable();
		वापस ret;
	पूर्ण

	l3mdev = inet_sk_bound_l3mdev(sk);

	inet_get_local_port_range(net, &low, &high);
	high++; /* [32768, 60999] -> [32768, 61000[ */
	reमुख्यing = high - low;
	अगर (likely(reमुख्यing > 1))
		reमुख्यing &= ~1U;

	net_get_अक्रमom_once(table_perturb, माप(table_perturb));
	index = hash_32(port_offset, INET_TABLE_PERTURB_SHIFT);

	offset = (READ_ONCE(table_perturb[index]) + port_offset) % reमुख्यing;
	/* In first pass we try ports of @low parity.
	 * inet_csk_get_port() करोes the opposite choice.
	 */
	offset &= ~1U;
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

		/* Does not bother with rcv_saddr checks, because
		 * the established check is alपढ़ोy unique enough.
		 */
		inet_bind_bucket_क्रम_each(tb, &head->chain) अणु
			अगर (net_eq(ib_net(tb), net) && tb->l3mdev == l3mdev &&
			    tb->port == port) अणु
				अगर (tb->fastreuse >= 0 ||
				    tb->fastreuseport >= 0)
					जाओ next_port;
				WARN_ON(hlist_empty(&tb->owners));
				अगर (!check_established(death_row, sk,
						       port, &tw))
					जाओ ok;
				जाओ next_port;
			पूर्ण
		पूर्ण

		tb = inet_bind_bucket_create(hinfo->bind_bucket_cachep,
					     net, head, port, l3mdev);
		अगर (!tb) अणु
			spin_unlock_bh(&head->lock);
			वापस -ENOMEM;
		पूर्ण
		tb->fastreuse = -1;
		tb->fastreuseport = -1;
		जाओ ok;
next_port:
		spin_unlock_bh(&head->lock);
		cond_resched();
	पूर्ण

	offset++;
	अगर ((offset & 1) && reमुख्यing > 1)
		जाओ other_parity_scan;

	वापस -EADDRNOTAVAIL;

ok:
	/* If our first attempt found a candidate, skip next candidate
	 * in 1/16 of हालs to add some noise.
	 */
	अगर (!i && !(pअक्रमom_u32() % 16))
		i = 2;
	WRITE_ONCE(table_perturb[index], READ_ONCE(table_perturb[index]) + i + 2);

	/* Head lock still held and bh's disabled */
	inet_bind_hash(sk, tb, port);
	अगर (sk_unhashed(sk)) अणु
		inet_sk(sk)->inet_sport = htons(port);
		inet_ehash_nolisten(sk, (काष्ठा sock *)tw, शून्य);
	पूर्ण
	अगर (tw)
		inet_twsk_bind_unhash(tw, hinfo);
	spin_unlock(&head->lock);
	अगर (tw)
		inet_twsk_deschedule_put(tw);
	local_bh_enable();
	वापस 0;
पूर्ण

/*
 * Bind a port क्रम a connect operation and hash it.
 */
पूर्णांक inet_hash_connect(काष्ठा inet_समयरुको_death_row *death_row,
		      काष्ठा sock *sk)
अणु
	u32 port_offset = 0;

	अगर (!inet_sk(sk)->inet_num)
		port_offset = inet_sk_port_offset(sk);
	वापस __inet_hash_connect(death_row, sk, port_offset,
				   __inet_check_established);
पूर्ण
EXPORT_SYMBOL_GPL(inet_hash_connect);

व्योम inet_hashinfo_init(काष्ठा inet_hashinfo *h)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < INET_LHTABLE_SIZE; i++) अणु
		spin_lock_init(&h->listening_hash[i].lock);
		INIT_HLIST_शून्यS_HEAD(&h->listening_hash[i].nulls_head,
				      i + LISTENING_शून्यS_BASE);
		h->listening_hash[i].count = 0;
	पूर्ण

	h->lhash2 = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(inet_hashinfo_init);

अटल व्योम init_hashinfo_lhash2(काष्ठा inet_hashinfo *h)
अणु
	पूर्णांक i;

	क्रम (i = 0; i <= h->lhash2_mask; i++) अणु
		spin_lock_init(&h->lhash2[i].lock);
		INIT_HLIST_HEAD(&h->lhash2[i].head);
		h->lhash2[i].count = 0;
	पूर्ण
पूर्ण

व्योम __init inet_hashinfo2_init(काष्ठा inet_hashinfo *h, स्थिर अक्षर *name,
				अचिन्हित दीर्घ numentries, पूर्णांक scale,
				अचिन्हित दीर्घ low_limit,
				अचिन्हित दीर्घ high_limit)
अणु
	h->lhash2 = alloc_large_प्रणाली_hash(name,
					    माप(*h->lhash2),
					    numentries,
					    scale,
					    0,
					    शून्य,
					    &h->lhash2_mask,
					    low_limit,
					    high_limit);
	init_hashinfo_lhash2(h);
पूर्ण

पूर्णांक inet_hashinfo2_init_mod(काष्ठा inet_hashinfo *h)
अणु
	h->lhash2 = kदो_स्मृति_array(INET_LHTABLE_SIZE, माप(*h->lhash2), GFP_KERNEL);
	अगर (!h->lhash2)
		वापस -ENOMEM;

	h->lhash2_mask = INET_LHTABLE_SIZE - 1;
	/* INET_LHTABLE_SIZE must be a घातer of 2 */
	BUG_ON(INET_LHTABLE_SIZE & h->lhash2_mask);

	init_hashinfo_lhash2(h);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(inet_hashinfo2_init_mod);

पूर्णांक inet_ehash_locks_alloc(काष्ठा inet_hashinfo *hashinfo)
अणु
	अचिन्हित पूर्णांक locksz = माप(spinlock_t);
	अचिन्हित पूर्णांक i, nblocks = 1;

	अगर (locksz != 0) अणु
		/* allocate 2 cache lines or at least one spinlock per cpu */
		nblocks = max(2U * L1_CACHE_BYTES / locksz, 1U);
		nblocks = roundup_घात_of_two(nblocks * num_possible_cpus());

		/* no more locks than number of hash buckets */
		nblocks = min(nblocks, hashinfo->ehash_mask + 1);

		hashinfo->ehash_locks = kvदो_स्मृति_array(nblocks, locksz, GFP_KERNEL);
		अगर (!hashinfo->ehash_locks)
			वापस -ENOMEM;

		क्रम (i = 0; i < nblocks; i++)
			spin_lock_init(&hashinfo->ehash_locks[i]);
	पूर्ण
	hashinfo->ehash_locks_mask = nblocks - 1;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(inet_ehash_locks_alloc);
