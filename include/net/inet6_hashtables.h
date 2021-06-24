<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 * Authors:	Lotsa people, from code originally in tcp
 */

#अगर_अघोषित _INET6_HASHTABLES_H
#घोषणा _INET6_HASHTABLES_H


#अगर IS_ENABLED(CONFIG_IPV6)
#समावेश <linux/in6.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/types.h>
#समावेश <linux/jhash.h>

#समावेश <net/inet_sock.h>

#समावेश <net/ipv6.h>
#समावेश <net/netns/hash.h>

काष्ठा inet_hashinfo;

अटल अंतरभूत अचिन्हित पूर्णांक __inet6_ehashfn(स्थिर u32 lhash,
				    स्थिर u16 lport,
				    स्थिर u32 fhash,
				    स्थिर __be16 fport,
				    स्थिर u32 initval)
अणु
	स्थिर u32 ports = (((u32)lport) << 16) | (__क्रमce u32)fport;
	वापस jhash_3words(lhash, fhash, ports, initval);
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
					स्थिर u16 hnum, स्थिर पूर्णांक dअगर,
					स्थिर पूर्णांक sdअगर);

काष्ठा sock *inet6_lookup_listener(काष्ठा net *net,
				   काष्ठा inet_hashinfo *hashinfo,
				   काष्ठा sk_buff *skb, पूर्णांक करोff,
				   स्थिर काष्ठा in6_addr *saddr,
				   स्थिर __be16 sport,
				   स्थिर काष्ठा in6_addr *daddr,
				   स्थिर अचिन्हित लघु hnum,
				   स्थिर पूर्णांक dअगर, स्थिर पूर्णांक sdअगर);

अटल अंतरभूत काष्ठा sock *__inet6_lookup(काष्ठा net *net,
					  काष्ठा inet_hashinfo *hashinfo,
					  काष्ठा sk_buff *skb, पूर्णांक करोff,
					  स्थिर काष्ठा in6_addr *saddr,
					  स्थिर __be16 sport,
					  स्थिर काष्ठा in6_addr *daddr,
					  स्थिर u16 hnum,
					  स्थिर पूर्णांक dअगर, स्थिर पूर्णांक sdअगर,
					  bool *refcounted)
अणु
	काष्ठा sock *sk = __inet6_lookup_established(net, hashinfo, saddr,
						     sport, daddr, hnum,
						     dअगर, sdअगर);
	*refcounted = true;
	अगर (sk)
		वापस sk;
	*refcounted = false;
	वापस inet6_lookup_listener(net, hashinfo, skb, करोff, saddr, sport,
				     daddr, hnum, dअगर, sdअगर);
पूर्ण

अटल अंतरभूत काष्ठा sock *__inet6_lookup_skb(काष्ठा inet_hashinfo *hashinfo,
					      काष्ठा sk_buff *skb, पूर्णांक करोff,
					      स्थिर __be16 sport,
					      स्थिर __be16 dport,
					      पूर्णांक iअगर, पूर्णांक sdअगर,
					      bool *refcounted)
अणु
	काष्ठा sock *sk = skb_steal_sock(skb, refcounted);

	अगर (sk)
		वापस sk;

	वापस __inet6_lookup(dev_net(skb_dst(skb)->dev), hashinfo, skb,
			      करोff, &ipv6_hdr(skb)->saddr, sport,
			      &ipv6_hdr(skb)->daddr, ntohs(dport),
			      iअगर, sdअगर, refcounted);
पूर्ण

काष्ठा sock *inet6_lookup(काष्ठा net *net, काष्ठा inet_hashinfo *hashinfo,
			  काष्ठा sk_buff *skb, पूर्णांक करोff,
			  स्थिर काष्ठा in6_addr *saddr, स्थिर __be16 sport,
			  स्थिर काष्ठा in6_addr *daddr, स्थिर __be16 dport,
			  स्थिर पूर्णांक dअगर);

पूर्णांक inet6_hash(काष्ठा sock *sk);
#पूर्ण_अगर /* IS_ENABLED(CONFIG_IPV6) */

#घोषणा INET6_MATCH(__sk, __net, __saddr, __daddr, __ports, __dअगर, __sdअगर) \
	(((__sk)->sk_portpair == (__ports))			&&	\
	 ((__sk)->sk_family == AF_INET6)			&&	\
	 ipv6_addr_equal(&(__sk)->sk_v6_daddr, (__saddr))		&&	\
	 ipv6_addr_equal(&(__sk)->sk_v6_rcv_saddr, (__daddr))	&&	\
	 (((__sk)->sk_bound_dev_अगर == (__dअगर))	||			\
	  ((__sk)->sk_bound_dev_अगर == (__sdअगर)))		&&	\
	 net_eq(sock_net(__sk), (__net)))

#पूर्ण_अगर /* _INET6_HASHTABLES_H */
