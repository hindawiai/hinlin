<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		Generic INET6 transport hashtables
 *
 * Authors:	Lotsa people, from code originally in tcp, generalised here
 *		by Arnalकरो Carvalho de Melo <acme@mandriva.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/अक्रमom.h>

#समावेश <net/addrconf.h>
#समावेश <net/inet_connection_sock.h>
#समावेश <net/inet_hashtables.h>
#समावेश <net/inet6_hashtables.h>
#समावेश <net/secure_seq.h>
#समावेश <net/ip.h>
#समावेश <net/sock_reuseport.h>

बाह्य काष्ठा inet_hashinfo tcp_hashinfo;

u32 inet6_ehashfn(स्थिर काष्ठा net *net,
		  स्थिर काष्ठा in6_addr *laddr, स्थिर u16 lport,
		  स्थिर काष्ठा in6_addr *faddr, स्थिर __be16 fport)
अणु
	अटल u32 inet6_ehash_secret __पढ़ो_mostly;
	अटल u32 ipv6_hash_secret __पढ़ो_mostly;

	u32 lhash, fhash;

	net_get_अक्रमom_once(&inet6_ehash_secret, माप(inet6_ehash_secret));
	net_get_अक्रमom_once(&ipv6_hash_secret, माप(ipv6_hash_secret));

	lhash = (__क्रमce u32)laddr->s6_addr32[3];
	fhash = __ipv6_addr_jhash(faddr, ipv6_hash_secret);

	वापस __inet6_ehashfn(lhash, lport, fhash, fport,
			       inet6_ehash_secret + net_hash_mix(net));
पूर्ण

/*
 * Sockets in TCP_CLOSE state are _always_ taken out of the hash, so
 * we need not check it क्रम TCP lookups anymore, thanks Alexey. -DaveM
 *
 * The sockhash lock must be held as a पढ़ोer here.
 */
काष्ठा sock *__inet6_lookup_established(काष्ठा net *net,
					काष्ठा inet_hashinfo *hashinfo,
					   स्थिर काष्ठा in6_addr *saddr,
					   स्थिर __be16 sport,
					   स्थिर काष्ठा in6_addr *daddr,
					   स्थिर u16 hnum,
					   स्थिर पूर्णांक dअगर, स्थिर पूर्णांक sdअगर)
अणु
	काष्ठा sock *sk;
	स्थिर काष्ठा hlist_nulls_node *node;
	स्थिर __portpair ports = INET_COMBINED_PORTS(sport, hnum);
	/* Optimize here क्रम direct hit, only listening connections can
	 * have wildcards anyways.
	 */
	अचिन्हित पूर्णांक hash = inet6_ehashfn(net, daddr, hnum, saddr, sport);
	अचिन्हित पूर्णांक slot = hash & hashinfo->ehash_mask;
	काष्ठा inet_ehash_bucket *head = &hashinfo->ehash[slot];


begin:
	sk_nulls_क्रम_each_rcu(sk, node, &head->chain) अणु
		अगर (sk->sk_hash != hash)
			जारी;
		अगर (!INET6_MATCH(sk, net, saddr, daddr, ports, dअगर, sdअगर))
			जारी;
		अगर (unlikely(!refcount_inc_not_zero(&sk->sk_refcnt)))
			जाओ out;

		अगर (unlikely(!INET6_MATCH(sk, net, saddr, daddr, ports, dअगर, sdअगर))) अणु
			sock_gen_put(sk);
			जाओ begin;
		पूर्ण
		जाओ found;
	पूर्ण
	अगर (get_nulls_value(node) != slot)
		जाओ begin;
out:
	sk = शून्य;
found:
	वापस sk;
पूर्ण
EXPORT_SYMBOL(__inet6_lookup_established);

अटल अंतरभूत पूर्णांक compute_score(काष्ठा sock *sk, काष्ठा net *net,
				स्थिर अचिन्हित लघु hnum,
				स्थिर काष्ठा in6_addr *daddr,
				स्थिर पूर्णांक dअगर, स्थिर पूर्णांक sdअगर)
अणु
	पूर्णांक score = -1;

	अगर (net_eq(sock_net(sk), net) && inet_sk(sk)->inet_num == hnum &&
	    sk->sk_family == PF_INET6) अणु
		अगर (!ipv6_addr_equal(&sk->sk_v6_rcv_saddr, daddr))
			वापस -1;

		अगर (!inet_sk_bound_dev_eq(net, sk->sk_bound_dev_अगर, dअगर, sdअगर))
			वापस -1;

		score = 1;
		अगर (READ_ONCE(sk->sk_incoming_cpu) == raw_smp_processor_id())
			score++;
	पूर्ण
	वापस score;
पूर्ण

अटल अंतरभूत काष्ठा sock *lookup_reuseport(काष्ठा net *net, काष्ठा sock *sk,
					    काष्ठा sk_buff *skb, पूर्णांक करोff,
					    स्थिर काष्ठा in6_addr *saddr,
					    __be16 sport,
					    स्थिर काष्ठा in6_addr *daddr,
					    अचिन्हित लघु hnum)
अणु
	काष्ठा sock *reuse_sk = शून्य;
	u32 phash;

	अगर (sk->sk_reuseport) अणु
		phash = inet6_ehashfn(net, daddr, hnum, saddr, sport);
		reuse_sk = reuseport_select_sock(sk, phash, skb, करोff);
	पूर्ण
	वापस reuse_sk;
पूर्ण

/* called with rcu_पढ़ो_lock() */
अटल काष्ठा sock *inet6_lhash2_lookup(काष्ठा net *net,
		काष्ठा inet_listen_hashbucket *ilb2,
		काष्ठा sk_buff *skb, पूर्णांक करोff,
		स्थिर काष्ठा in6_addr *saddr,
		स्थिर __be16 sport, स्थिर काष्ठा in6_addr *daddr,
		स्थिर अचिन्हित लघु hnum, स्थिर पूर्णांक dअगर, स्थिर पूर्णांक sdअगर)
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

अटल अंतरभूत काष्ठा sock *inet6_lookup_run_bpf(काष्ठा net *net,
						काष्ठा inet_hashinfo *hashinfo,
						काष्ठा sk_buff *skb, पूर्णांक करोff,
						स्थिर काष्ठा in6_addr *saddr,
						स्थिर __be16 sport,
						स्थिर काष्ठा in6_addr *daddr,
						स्थिर u16 hnum)
अणु
	काष्ठा sock *sk, *reuse_sk;
	bool no_reuseport;

	अगर (hashinfo != &tcp_hashinfo)
		वापस शून्य; /* only TCP is supported */

	no_reuseport = bpf_sk_lookup_run_v6(net, IPPROTO_TCP,
					    saddr, sport, daddr, hnum, &sk);
	अगर (no_reuseport || IS_ERR_OR_शून्य(sk))
		वापस sk;

	reuse_sk = lookup_reuseport(net, sk, skb, करोff, saddr, sport, daddr, hnum);
	अगर (reuse_sk)
		sk = reuse_sk;
	वापस sk;
पूर्ण

काष्ठा sock *inet6_lookup_listener(काष्ठा net *net,
		काष्ठा inet_hashinfo *hashinfo,
		काष्ठा sk_buff *skb, पूर्णांक करोff,
		स्थिर काष्ठा in6_addr *saddr,
		स्थिर __be16 sport, स्थिर काष्ठा in6_addr *daddr,
		स्थिर अचिन्हित लघु hnum, स्थिर पूर्णांक dअगर, स्थिर पूर्णांक sdअगर)
अणु
	काष्ठा inet_listen_hashbucket *ilb2;
	काष्ठा sock *result = शून्य;
	अचिन्हित पूर्णांक hash2;

	/* Lookup redirect from BPF */
	अगर (अटल_branch_unlikely(&bpf_sk_lookup_enabled)) अणु
		result = inet6_lookup_run_bpf(net, hashinfo, skb, करोff,
					      saddr, sport, daddr, hnum);
		अगर (result)
			जाओ करोne;
	पूर्ण

	hash2 = ipv6_portaddr_hash(net, daddr, hnum);
	ilb2 = inet_lhash2_bucket(hashinfo, hash2);

	result = inet6_lhash2_lookup(net, ilb2, skb, करोff,
				     saddr, sport, daddr, hnum,
				     dअगर, sdअगर);
	अगर (result)
		जाओ करोne;

	/* Lookup lhash2 with in6addr_any */
	hash2 = ipv6_portaddr_hash(net, &in6addr_any, hnum);
	ilb2 = inet_lhash2_bucket(hashinfo, hash2);

	result = inet6_lhash2_lookup(net, ilb2, skb, करोff,
				     saddr, sport, &in6addr_any, hnum,
				     dअगर, sdअगर);
करोne:
	अगर (IS_ERR(result))
		वापस शून्य;
	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(inet6_lookup_listener);

काष्ठा sock *inet6_lookup(काष्ठा net *net, काष्ठा inet_hashinfo *hashinfo,
			  काष्ठा sk_buff *skb, पूर्णांक करोff,
			  स्थिर काष्ठा in6_addr *saddr, स्थिर __be16 sport,
			  स्थिर काष्ठा in6_addr *daddr, स्थिर __be16 dport,
			  स्थिर पूर्णांक dअगर)
अणु
	काष्ठा sock *sk;
	bool refcounted;

	sk = __inet6_lookup(net, hashinfo, skb, करोff, saddr, sport, daddr,
			    ntohs(dport), dअगर, 0, &refcounted);
	अगर (sk && !refcounted && !refcount_inc_not_zero(&sk->sk_refcnt))
		sk = शून्य;
	वापस sk;
पूर्ण
EXPORT_SYMBOL_GPL(inet6_lookup);

अटल पूर्णांक __inet6_check_established(काष्ठा inet_समयरुको_death_row *death_row,
				     काष्ठा sock *sk, स्थिर __u16 lport,
				     काष्ठा inet_समयरुको_sock **twp)
अणु
	काष्ठा inet_hashinfo *hinfo = death_row->hashinfo;
	काष्ठा inet_sock *inet = inet_sk(sk);
	स्थिर काष्ठा in6_addr *daddr = &sk->sk_v6_rcv_saddr;
	स्थिर काष्ठा in6_addr *saddr = &sk->sk_v6_daddr;
	स्थिर पूर्णांक dअगर = sk->sk_bound_dev_अगर;
	काष्ठा net *net = sock_net(sk);
	स्थिर पूर्णांक sdअगर = l3mdev_master_अगरindex_by_index(net, dअगर);
	स्थिर __portpair ports = INET_COMBINED_PORTS(inet->inet_dport, lport);
	स्थिर अचिन्हित पूर्णांक hash = inet6_ehashfn(net, daddr, lport, saddr,
						inet->inet_dport);
	काष्ठा inet_ehash_bucket *head = inet_ehash_bucket(hinfo, hash);
	spinlock_t *lock = inet_ehash_lockp(hinfo, hash);
	काष्ठा sock *sk2;
	स्थिर काष्ठा hlist_nulls_node *node;
	काष्ठा inet_समयरुको_sock *tw = शून्य;

	spin_lock(lock);

	sk_nulls_क्रम_each(sk2, node, &head->chain) अणु
		अगर (sk2->sk_hash != hash)
			जारी;

		अगर (likely(INET6_MATCH(sk2, net, saddr, daddr, ports,
				       dअगर, sdअगर))) अणु
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

अटल u32 inet6_sk_port_offset(स्थिर काष्ठा sock *sk)
अणु
	स्थिर काष्ठा inet_sock *inet = inet_sk(sk);

	वापस secure_ipv6_port_ephemeral(sk->sk_v6_rcv_saddr.s6_addr32,
					  sk->sk_v6_daddr.s6_addr32,
					  inet->inet_dport);
पूर्ण

पूर्णांक inet6_hash_connect(काष्ठा inet_समयरुको_death_row *death_row,
		       काष्ठा sock *sk)
अणु
	u32 port_offset = 0;

	अगर (!inet_sk(sk)->inet_num)
		port_offset = inet6_sk_port_offset(sk);
	वापस __inet_hash_connect(death_row, sk, port_offset,
				   __inet6_check_established);
पूर्ण
EXPORT_SYMBOL_GPL(inet6_hash_connect);

पूर्णांक inet6_hash(काष्ठा sock *sk)
अणु
	पूर्णांक err = 0;

	अगर (sk->sk_state != TCP_CLOSE) अणु
		local_bh_disable();
		err = __inet_hash(sk, शून्य);
		local_bh_enable();
	पूर्ण

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(inet6_hash);
