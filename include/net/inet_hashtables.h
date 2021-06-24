<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 * Authors:	Lotsa people, from code originally in tcp
 */

#अगर_अघोषित _INET_HASHTABLES_H
#घोषणा _INET_HASHTABLES_H


#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/socket.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>
#समावेश <linux/रुको.h>

#समावेश <net/inet_connection_sock.h>
#समावेश <net/inet_sock.h>
#समावेश <net/sock.h>
#समावेश <net/route.h>
#समावेश <net/tcp_states.h>
#समावेश <net/netns/hash.h>

#समावेश <linux/refcount.h>
#समावेश <यंत्र/byteorder.h>

/* This is क्रम all connections with a full identity, no wildcards.
 * The 'e' prefix stands क्रम Establish, but we really put all sockets
 * but LISTEN ones.
 */
काष्ठा inet_ehash_bucket अणु
	काष्ठा hlist_nulls_head chain;
पूर्ण;

/* There are a few simple rules, which allow क्रम local port reuse by
 * an application.  In essence:
 *
 *	1) Sockets bound to dअगरferent पूर्णांकerfaces may share a local port.
 *	   Failing that, जाओ test 2.
 *	2) If all sockets have sk->sk_reuse set, and none of them are in
 *	   TCP_LISTEN state, the port may be shared.
 *	   Failing that, जाओ test 3.
 *	3) If all sockets are bound to a specअगरic inet_sk(sk)->rcv_saddr local
 *	   address, and none of them are the same, the port may be
 *	   shared.
 *	   Failing this, the port cannot be shared.
 *
 * The पूर्णांकeresting poपूर्णांक, is test #2.  This is what an FTP server करोes
 * all day.  To optimize this हाल we use a specअगरic flag bit defined
 * below.  As we add sockets to a bind bucket list, we perक्रमm a
 * check of: (newsk->sk_reuse && (newsk->sk_state != TCP_LISTEN))
 * As दीर्घ as all sockets added to a bind bucket pass this test,
 * the flag bit will be set.
 * The resulting situation is that tcp_v[46]_verअगरy_bind() can just check
 * क्रम this flag bit, अगर it is set and the socket trying to bind has
 * sk->sk_reuse set, we करोn't even have to walk the owners list at all,
 * we वापस that it is ok to bind this socket to the requested local port.
 *
 * Sounds like a lot of work, but it is worth it.  In a more naive
 * implementation (ie. current FreeBSD etc.) the entire list of ports
 * must be walked क्रम each data port खोलोed by an ftp server.  Needless
 * to say, this करोes not scale at all.  With a couple thousand FTP
 * users logged onto your box, isn't it nice to know that new data
 * ports are created in O(1) समय?  I thought so. ;-)	-DaveM
 */
#घोषणा FASTREUSEPORT_ANY	1
#घोषणा FASTREUSEPORT_STRICT	2

काष्ठा inet_bind_bucket अणु
	possible_net_t		ib_net;
	पूर्णांक			l3mdev;
	अचिन्हित लघु		port;
	चिन्हित अक्षर		fastreuse;
	चिन्हित अक्षर		fastreuseport;
	kuid_t			fastuid;
#अगर IS_ENABLED(CONFIG_IPV6)
	काष्ठा in6_addr		fast_v6_rcv_saddr;
#पूर्ण_अगर
	__be32			fast_rcv_saddr;
	अचिन्हित लघु		fast_sk_family;
	bool			fast_ipv6_only;
	काष्ठा hlist_node	node;
	काष्ठा hlist_head	owners;
पूर्ण;

अटल अंतरभूत काष्ठा net *ib_net(काष्ठा inet_bind_bucket *ib)
अणु
	वापस पढ़ो_pnet(&ib->ib_net);
पूर्ण

#घोषणा inet_bind_bucket_क्रम_each(tb, head) \
	hlist_क्रम_each_entry(tb, head, node)

काष्ठा inet_bind_hashbucket अणु
	spinlock_t		lock;
	काष्ठा hlist_head	chain;
पूर्ण;

/* Sockets can be hashed in established or listening table.
 * We must use dअगरferent 'nulls' end-of-chain value क्रम all hash buckets :
 * A socket might transition from ESTABLISH to LISTEN state without
 * RCU grace period. A lookup in ehash table needs to handle this हाल.
 */
#घोषणा LISTENING_शून्यS_BASE (1U << 29)
काष्ठा inet_listen_hashbucket अणु
	spinlock_t		lock;
	अचिन्हित पूर्णांक		count;
	जोड़ अणु
		काष्ठा hlist_head	head;
		काष्ठा hlist_nulls_head	nulls_head;
	पूर्ण;
पूर्ण;

/* This is क्रम listening sockets, thus all sockets which possess wildcards. */
#घोषणा INET_LHTABLE_SIZE	32	/* Yes, really, this is all you need. */

काष्ठा inet_hashinfo अणु
	/* This is क्रम sockets with full identity only.  Sockets here will
	 * always be without wildcards and will have the following invariant:
	 *
	 *          TCP_ESTABLISHED <= sk->sk_state < TCP_CLOSE
	 *
	 */
	काष्ठा inet_ehash_bucket	*ehash;
	spinlock_t			*ehash_locks;
	अचिन्हित पूर्णांक			ehash_mask;
	अचिन्हित पूर्णांक			ehash_locks_mask;

	/* Ok, let's try this, I give up, we करो need a local binding
	 * TCP hash as well as the others क्रम fast bind/connect.
	 */
	काष्ठा kmem_cache		*bind_bucket_cachep;
	काष्ठा inet_bind_hashbucket	*bhash;
	अचिन्हित पूर्णांक			bhash_size;

	/* The 2nd listener table hashed by local port and address */
	अचिन्हित पूर्णांक			lhash2_mask;
	काष्ठा inet_listen_hashbucket	*lhash2;

	/* All the above members are written once at bootup and
	 * never written again _or_ are preकरोminantly पढ़ो-access.
	 *
	 * Now align to a new cache line as all the following members
	 * might be often dirty.
	 */
	/* All sockets in TCP_LISTEN state will be in listening_hash.
	 * This is the only table where wildcard'd TCP sockets can
	 * exist.  listening_hash is only hashed by local port number.
	 * If lhash2 is initialized, the same socket will also be hashed
	 * to lhash2 by port and address.
	 */
	काष्ठा inet_listen_hashbucket	listening_hash[INET_LHTABLE_SIZE]
					____cacheline_aligned_in_smp;
पूर्ण;

#घोषणा inet_lhash2_क्रम_each_icsk_rcu(__icsk, list) \
	hlist_क्रम_each_entry_rcu(__icsk, list, icsk_listen_portaddr_node)

अटल अंतरभूत काष्ठा inet_listen_hashbucket *
inet_lhash2_bucket(काष्ठा inet_hashinfo *h, u32 hash)
अणु
	वापस &h->lhash2[hash & h->lhash2_mask];
पूर्ण

अटल अंतरभूत काष्ठा inet_ehash_bucket *inet_ehash_bucket(
	काष्ठा inet_hashinfo *hashinfo,
	अचिन्हित पूर्णांक hash)
अणु
	वापस &hashinfo->ehash[hash & hashinfo->ehash_mask];
पूर्ण

अटल अंतरभूत spinlock_t *inet_ehash_lockp(
	काष्ठा inet_hashinfo *hashinfo,
	अचिन्हित पूर्णांक hash)
अणु
	वापस &hashinfo->ehash_locks[hash & hashinfo->ehash_locks_mask];
पूर्ण

पूर्णांक inet_ehash_locks_alloc(काष्ठा inet_hashinfo *hashinfo);

अटल अंतरभूत व्योम inet_hashinfo2_मुक्त_mod(काष्ठा inet_hashinfo *h)
अणु
	kमुक्त(h->lhash2);
	h->lhash2 = शून्य;
पूर्ण

अटल अंतरभूत व्योम inet_ehash_locks_मुक्त(काष्ठा inet_hashinfo *hashinfo)
अणु
	kvमुक्त(hashinfo->ehash_locks);
	hashinfo->ehash_locks = शून्य;
पूर्ण

अटल अंतरभूत bool inet_sk_bound_dev_eq(काष्ठा net *net, पूर्णांक bound_dev_अगर,
					पूर्णांक dअगर, पूर्णांक sdअगर)
अणु
#अगर IS_ENABLED(CONFIG_NET_L3_MASTER_DEV)
	वापस inet_bound_dev_eq(!!net->ipv4.sysctl_tcp_l3mdev_accept,
				 bound_dev_अगर, dअगर, sdअगर);
#अन्यथा
	वापस inet_bound_dev_eq(true, bound_dev_अगर, dअगर, sdअगर);
#पूर्ण_अगर
पूर्ण

काष्ठा inet_bind_bucket *
inet_bind_bucket_create(काष्ठा kmem_cache *cachep, काष्ठा net *net,
			काष्ठा inet_bind_hashbucket *head,
			स्थिर अचिन्हित लघु snum, पूर्णांक l3mdev);
व्योम inet_bind_bucket_destroy(काष्ठा kmem_cache *cachep,
			      काष्ठा inet_bind_bucket *tb);

अटल अंतरभूत u32 inet_bhashfn(स्थिर काष्ठा net *net, स्थिर __u16 lport,
			       स्थिर u32 bhash_size)
अणु
	वापस (lport + net_hash_mix(net)) & (bhash_size - 1);
पूर्ण

व्योम inet_bind_hash(काष्ठा sock *sk, काष्ठा inet_bind_bucket *tb,
		    स्थिर अचिन्हित लघु snum);

/* These can have wildcards, करोn't try too hard. */
अटल अंतरभूत u32 inet_lhashfn(स्थिर काष्ठा net *net, स्थिर अचिन्हित लघु num)
अणु
	वापस (num + net_hash_mix(net)) & (INET_LHTABLE_SIZE - 1);
पूर्ण

अटल अंतरभूत पूर्णांक inet_sk_listen_hashfn(स्थिर काष्ठा sock *sk)
अणु
	वापस inet_lhashfn(sock_net(sk), inet_sk(sk)->inet_num);
पूर्ण

/* Caller must disable local BH processing. */
पूर्णांक __inet_inherit_port(स्थिर काष्ठा sock *sk, काष्ठा sock *child);

व्योम inet_put_port(काष्ठा sock *sk);

व्योम inet_hashinfo_init(काष्ठा inet_hashinfo *h);
व्योम inet_hashinfo2_init(काष्ठा inet_hashinfo *h, स्थिर अक्षर *name,
			 अचिन्हित दीर्घ numentries, पूर्णांक scale,
			 अचिन्हित दीर्घ low_limit,
			 अचिन्हित दीर्घ high_limit);
पूर्णांक inet_hashinfo2_init_mod(काष्ठा inet_hashinfo *h);

bool inet_ehash_insert(काष्ठा sock *sk, काष्ठा sock *osk, bool *found_dup_sk);
bool inet_ehash_nolisten(काष्ठा sock *sk, काष्ठा sock *osk,
			 bool *found_dup_sk);
पूर्णांक __inet_hash(काष्ठा sock *sk, काष्ठा sock *osk);
पूर्णांक inet_hash(काष्ठा sock *sk);
व्योम inet_unhash(काष्ठा sock *sk);

काष्ठा sock *__inet_lookup_listener(काष्ठा net *net,
				    काष्ठा inet_hashinfo *hashinfo,
				    काष्ठा sk_buff *skb, पूर्णांक करोff,
				    स्थिर __be32 saddr, स्थिर __be16 sport,
				    स्थिर __be32 daddr,
				    स्थिर अचिन्हित लघु hnum,
				    स्थिर पूर्णांक dअगर, स्थिर पूर्णांक sdअगर);

अटल अंतरभूत काष्ठा sock *inet_lookup_listener(काष्ठा net *net,
		काष्ठा inet_hashinfo *hashinfo,
		काष्ठा sk_buff *skb, पूर्णांक करोff,
		__be32 saddr, __be16 sport,
		__be32 daddr, __be16 dport, पूर्णांक dअगर, पूर्णांक sdअगर)
अणु
	वापस __inet_lookup_listener(net, hashinfo, skb, करोff, saddr, sport,
				      daddr, ntohs(dport), dअगर, sdअगर);
पूर्ण

/* Socket demux engine toys. */
/* What happens here is ugly; there's a pair of adjacent fields in
   काष्ठा inet_sock; __be16 dport followed by __u16 num.  We want to
   search by pair, so we combine the keys पूर्णांकo a single 32bit value
   and compare with 32bit value पढ़ो from &...->dport.  Let's at least
   make sure that it's not mixed with anything अन्यथा...
   On 64bit tarमाला_लो we combine comparisons with pair of adjacent __be32
   fields in the same way.
*/
#अगर_घोषित __BIG_ENDIAN
#घोषणा INET_COMBINED_PORTS(__sport, __dport) \
	((__क्रमce __portpair)(((__क्रमce __u32)(__be16)(__sport) << 16) | (__u32)(__dport)))
#अन्यथा /* __LITTLE_ENDIAN */
#घोषणा INET_COMBINED_PORTS(__sport, __dport) \
	((__क्रमce __portpair)(((__u32)(__dport) << 16) | (__क्रमce __u32)(__be16)(__sport)))
#पूर्ण_अगर

#अगर (BITS_PER_LONG == 64)
#अगर_घोषित __BIG_ENDIAN
#घोषणा INET_ADDR_COOKIE(__name, __saddr, __daddr) \
	स्थिर __addrpair __name = (__क्रमce __addrpair) ( \
				   (((__क्रमce __u64)(__be32)(__saddr)) << 32) | \
				   ((__क्रमce __u64)(__be32)(__daddr)))
#अन्यथा /* __LITTLE_ENDIAN */
#घोषणा INET_ADDR_COOKIE(__name, __saddr, __daddr) \
	स्थिर __addrpair __name = (__क्रमce __addrpair) ( \
				   (((__क्रमce __u64)(__be32)(__daddr)) << 32) | \
				   ((__क्रमce __u64)(__be32)(__saddr)))
#पूर्ण_अगर /* __BIG_ENDIAN */
#घोषणा INET_MATCH(__sk, __net, __cookie, __saddr, __daddr, __ports, __dअगर, __sdअगर) \
	(((__sk)->sk_portpair == (__ports))			&&	\
	 ((__sk)->sk_addrpair == (__cookie))			&&	\
	 (((__sk)->sk_bound_dev_अगर == (__dअगर))			||	\
	  ((__sk)->sk_bound_dev_अगर == (__sdअगर)))		&&	\
	 net_eq(sock_net(__sk), (__net)))
#अन्यथा /* 32-bit arch */
#घोषणा INET_ADDR_COOKIE(__name, __saddr, __daddr) \
	स्थिर पूर्णांक __name __deprecated __attribute__((unused))

#घोषणा INET_MATCH(__sk, __net, __cookie, __saddr, __daddr, __ports, __dअगर, __sdअगर) \
	(((__sk)->sk_portpair == (__ports))		&&		\
	 ((__sk)->sk_daddr	== (__saddr))		&&		\
	 ((__sk)->sk_rcv_saddr	== (__daddr))		&&		\
	 (((__sk)->sk_bound_dev_अगर == (__dअगर))		||		\
	  ((__sk)->sk_bound_dev_अगर == (__sdअगर)))	&&		\
	 net_eq(sock_net(__sk), (__net)))
#पूर्ण_अगर /* 64-bit arch */

/* Sockets in TCP_CLOSE state are _always_ taken out of the hash, so we need
 * not check it क्रम lookups anymore, thanks Alexey. -DaveM
 */
काष्ठा sock *__inet_lookup_established(काष्ठा net *net,
				       काष्ठा inet_hashinfo *hashinfo,
				       स्थिर __be32 saddr, स्थिर __be16 sport,
				       स्थिर __be32 daddr, स्थिर u16 hnum,
				       स्थिर पूर्णांक dअगर, स्थिर पूर्णांक sdअगर);

अटल अंतरभूत काष्ठा sock *
	inet_lookup_established(काष्ठा net *net, काष्ठा inet_hashinfo *hashinfo,
				स्थिर __be32 saddr, स्थिर __be16 sport,
				स्थिर __be32 daddr, स्थिर __be16 dport,
				स्थिर पूर्णांक dअगर)
अणु
	वापस __inet_lookup_established(net, hashinfo, saddr, sport, daddr,
					 ntohs(dport), dअगर, 0);
पूर्ण

अटल अंतरभूत काष्ठा sock *__inet_lookup(काष्ठा net *net,
					 काष्ठा inet_hashinfo *hashinfo,
					 काष्ठा sk_buff *skb, पूर्णांक करोff,
					 स्थिर __be32 saddr, स्थिर __be16 sport,
					 स्थिर __be32 daddr, स्थिर __be16 dport,
					 स्थिर पूर्णांक dअगर, स्थिर पूर्णांक sdअगर,
					 bool *refcounted)
अणु
	u16 hnum = ntohs(dport);
	काष्ठा sock *sk;

	sk = __inet_lookup_established(net, hashinfo, saddr, sport,
				       daddr, hnum, dअगर, sdअगर);
	*refcounted = true;
	अगर (sk)
		वापस sk;
	*refcounted = false;
	वापस __inet_lookup_listener(net, hashinfo, skb, करोff, saddr,
				      sport, daddr, hnum, dअगर, sdअगर);
पूर्ण

अटल अंतरभूत काष्ठा sock *inet_lookup(काष्ठा net *net,
				       काष्ठा inet_hashinfo *hashinfo,
				       काष्ठा sk_buff *skb, पूर्णांक करोff,
				       स्थिर __be32 saddr, स्थिर __be16 sport,
				       स्थिर __be32 daddr, स्थिर __be16 dport,
				       स्थिर पूर्णांक dअगर)
अणु
	काष्ठा sock *sk;
	bool refcounted;

	sk = __inet_lookup(net, hashinfo, skb, करोff, saddr, sport, daddr,
			   dport, dअगर, 0, &refcounted);

	अगर (sk && !refcounted && !refcount_inc_not_zero(&sk->sk_refcnt))
		sk = शून्य;
	वापस sk;
पूर्ण

अटल अंतरभूत काष्ठा sock *__inet_lookup_skb(काष्ठा inet_hashinfo *hashinfo,
					     काष्ठा sk_buff *skb,
					     पूर्णांक करोff,
					     स्थिर __be16 sport,
					     स्थिर __be16 dport,
					     स्थिर पूर्णांक sdअगर,
					     bool *refcounted)
अणु
	काष्ठा sock *sk = skb_steal_sock(skb, refcounted);
	स्थिर काष्ठा iphdr *iph = ip_hdr(skb);

	अगर (sk)
		वापस sk;

	वापस __inet_lookup(dev_net(skb_dst(skb)->dev), hashinfo, skb,
			     करोff, iph->saddr, sport,
			     iph->daddr, dport, inet_iअगर(skb), sdअगर,
			     refcounted);
पूर्ण

u32 inet6_ehashfn(स्थिर काष्ठा net *net,
		  स्थिर काष्ठा in6_addr *laddr, स्थिर u16 lport,
		  स्थिर काष्ठा in6_addr *faddr, स्थिर __be16 fport);

अटल अंतरभूत व्योम sk_daddr_set(काष्ठा sock *sk, __be32 addr)
अणु
	sk->sk_daddr = addr; /* alias of inet_daddr */
#अगर IS_ENABLED(CONFIG_IPV6)
	ipv6_addr_set_v4mapped(addr, &sk->sk_v6_daddr);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम sk_rcv_saddr_set(काष्ठा sock *sk, __be32 addr)
अणु
	sk->sk_rcv_saddr = addr; /* alias of inet_rcv_saddr */
#अगर IS_ENABLED(CONFIG_IPV6)
	ipv6_addr_set_v4mapped(addr, &sk->sk_v6_rcv_saddr);
#पूर्ण_अगर
पूर्ण

पूर्णांक __inet_hash_connect(काष्ठा inet_समयरुको_death_row *death_row,
			काष्ठा sock *sk, u32 port_offset,
			पूर्णांक (*check_established)(काष्ठा inet_समयरुको_death_row *,
						 काष्ठा sock *, __u16,
						 काष्ठा inet_समयरुको_sock **));

पूर्णांक inet_hash_connect(काष्ठा inet_समयरुको_death_row *death_row,
		      काष्ठा sock *sk);
#पूर्ण_अगर /* _INET_HASHTABLES_H */
