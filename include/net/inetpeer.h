<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *		INETPEER - A storage क्रम permanent inक्रमmation about peers
 *
 *  Authors:	Andrey V. Savochkin <saw@msu.ru>
 */

#अगर_अघोषित _NET_INETPEER_H
#घोषणा _NET_INETPEER_H

#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/rtnetlink.h>
#समावेश <net/ipv6.h>
#समावेश <linux/atomic.h>

/* IPv4 address key क्रम cache lookups */
काष्ठा ipv4_addr_key अणु
	__be32	addr;
	पूर्णांक	vअगर;
पूर्ण;

#घोषणा INETPEER_MAXKEYSZ   (माप(काष्ठा in6_addr) / माप(u32))

काष्ठा inetpeer_addr अणु
	जोड़ अणु
		काष्ठा ipv4_addr_key	a4;
		काष्ठा in6_addr		a6;
		u32			key[INETPEER_MAXKEYSZ];
	पूर्ण;
	__u16				family;
पूर्ण;

काष्ठा inet_peer अणु
	काष्ठा rb_node		rb_node;
	काष्ठा inetpeer_addr	daddr;

	u32			metrics[RTAX_MAX];
	u32			rate_tokens;	/* rate limiting क्रम ICMP */
	u32			n_redirects;
	अचिन्हित दीर्घ		rate_last;
	/*
	 * Once inet_peer is queued क्रम deletion (refcnt == 0), following field
	 * is not available: rid
	 * We can share memory with rcu_head to help keep inet_peer small.
	 */
	जोड़ अणु
		काष्ठा अणु
			atomic_t			rid;		/* Frag reception counter */
		पूर्ण;
		काष्ठा rcu_head         rcu;
	पूर्ण;

	/* following fields might be frequently dirtied */
	__u32			dसमय;	/* the समय of last use of not referenced entries */
	refcount_t		refcnt;
पूर्ण;

काष्ठा inet_peer_base अणु
	काष्ठा rb_root		rb_root;
	seqlock_t		lock;
	पूर्णांक			total;
पूर्ण;

व्योम inet_peer_base_init(काष्ठा inet_peer_base *);

व्योम inet_initpeers(व्योम) __init;

#घोषणा INETPEER_METRICS_NEW	(~(u32) 0)

अटल अंतरभूत व्योम inetpeer_set_addr_v4(काष्ठा inetpeer_addr *iaddr, __be32 ip)
अणु
	iaddr->a4.addr = ip;
	iaddr->a4.vअगर = 0;
	iaddr->family = AF_INET;
पूर्ण

अटल अंतरभूत __be32 inetpeer_get_addr_v4(काष्ठा inetpeer_addr *iaddr)
अणु
	वापस iaddr->a4.addr;
पूर्ण

अटल अंतरभूत व्योम inetpeer_set_addr_v6(काष्ठा inetpeer_addr *iaddr,
					काष्ठा in6_addr *in6)
अणु
	iaddr->a6 = *in6;
	iaddr->family = AF_INET6;
पूर्ण

अटल अंतरभूत काष्ठा in6_addr *inetpeer_get_addr_v6(काष्ठा inetpeer_addr *iaddr)
अणु
	वापस &iaddr->a6;
पूर्ण

/* can be called with or without local BH being disabled */
काष्ठा inet_peer *inet_getpeer(काष्ठा inet_peer_base *base,
			       स्थिर काष्ठा inetpeer_addr *daddr,
			       पूर्णांक create);

अटल अंतरभूत काष्ठा inet_peer *inet_getpeer_v4(काष्ठा inet_peer_base *base,
						__be32 v4daddr,
						पूर्णांक vअगर, पूर्णांक create)
अणु
	काष्ठा inetpeer_addr daddr;

	daddr.a4.addr = v4daddr;
	daddr.a4.vअगर = vअगर;
	daddr.family = AF_INET;
	वापस inet_getpeer(base, &daddr, create);
पूर्ण

अटल अंतरभूत काष्ठा inet_peer *inet_getpeer_v6(काष्ठा inet_peer_base *base,
						स्थिर काष्ठा in6_addr *v6daddr,
						पूर्णांक create)
अणु
	काष्ठा inetpeer_addr daddr;

	daddr.a6 = *v6daddr;
	daddr.family = AF_INET6;
	वापस inet_getpeer(base, &daddr, create);
पूर्ण

अटल अंतरभूत पूर्णांक inetpeer_addr_cmp(स्थिर काष्ठा inetpeer_addr *a,
				    स्थिर काष्ठा inetpeer_addr *b)
अणु
	पूर्णांक i, n;

	अगर (a->family == AF_INET)
		n = माप(a->a4) / माप(u32);
	अन्यथा
		n = माप(a->a6) / माप(u32);

	क्रम (i = 0; i < n; i++) अणु
		अगर (a->key[i] == b->key[i])
			जारी;
		अगर (a->key[i] < b->key[i])
			वापस -1;
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/* can be called from BH context or outside */
व्योम inet_putpeer(काष्ठा inet_peer *p);
bool inet_peer_xrlim_allow(काष्ठा inet_peer *peer, पूर्णांक समयout);

व्योम inetpeer_invalidate_tree(काष्ठा inet_peer_base *);

#पूर्ण_अगर /* _NET_INETPEER_H */
