<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * IPVS:        Source Hashing scheduling module
 *
 * Authors:     Wensong Zhang <wensong@gnuchina.org>
 *
 * Changes:
 */

/*
 * The sh algorithm is to select server by the hash key of source IP
 * address. The pseuकरो code is as follows:
 *
 *       n <- servernode[src_ip];
 *       अगर (n is dead) OR
 *          (n is overloaded) or (n.weight <= 0) then
 *                 वापस शून्य;
 *
 *       वापस n;
 *
 * Notes that servernode is a 256-bucket hash table that maps the hash
 * index derived from packet source IP address to the current server
 * array. If the sh scheduler is used in cache cluster, it is good to
 * combine it with cache_bypass feature. When the अटलally asचिन्हित
 * server is dead or overloaded, the load balancer can bypass the cache
 * server and send requests to the original server directly.
 *
 * The weight destination attribute can be used to control the
 * distribution of connections to the destinations in servernode. The
 * greater the weight, the more connections the destination
 * will receive.
 *
 */

#घोषणा KMSG_COMPONENT "IPVS"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/ip.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/skbuff.h>

#समावेश <net/ip_vs.h>

#समावेश <net/tcp.h>
#समावेश <linux/udp.h>
#समावेश <linux/sctp.h>


/*
 *      IPVS SH bucket
 */
काष्ठा ip_vs_sh_bucket अणु
	काष्ठा ip_vs_dest __rcu	*dest;	/* real server (cache) */
पूर्ण;

/*
 *     क्रम IPVS SH entry hash table
 */
#अगर_अघोषित CONFIG_IP_VS_SH_TAB_BITS
#घोषणा CONFIG_IP_VS_SH_TAB_BITS        8
#पूर्ण_अगर
#घोषणा IP_VS_SH_TAB_BITS               CONFIG_IP_VS_SH_TAB_BITS
#घोषणा IP_VS_SH_TAB_SIZE               (1 << IP_VS_SH_TAB_BITS)
#घोषणा IP_VS_SH_TAB_MASK               (IP_VS_SH_TAB_SIZE - 1)

काष्ठा ip_vs_sh_state अणु
	काष्ठा rcu_head			rcu_head;
	काष्ठा ip_vs_sh_bucket		buckets[IP_VS_SH_TAB_SIZE];
पूर्ण;

/* Helper function to determine अगर server is unavailable */
अटल अंतरभूत bool is_unavailable(काष्ठा ip_vs_dest *dest)
अणु
	वापस atomic_पढ़ो(&dest->weight) <= 0 ||
	       dest->flags & IP_VS_DEST_F_OVERLOAD;
पूर्ण

/*
 *	Returns hash value क्रम IPVS SH entry
 */
अटल अंतरभूत अचिन्हित पूर्णांक
ip_vs_sh_hashkey(पूर्णांक af, स्थिर जोड़ nf_inet_addr *addr,
		 __be16 port, अचिन्हित पूर्णांक offset)
अणु
	__be32 addr_fold = addr->ip;

#अगर_घोषित CONFIG_IP_VS_IPV6
	अगर (af == AF_INET6)
		addr_fold = addr->ip6[0]^addr->ip6[1]^
			    addr->ip6[2]^addr->ip6[3];
#पूर्ण_अगर
	वापस (offset + hash_32(ntohs(port) + ntohl(addr_fold),
				 IP_VS_SH_TAB_BITS)) &
		IP_VS_SH_TAB_MASK;
पूर्ण


/*
 *      Get ip_vs_dest associated with supplied parameters.
 */
अटल अंतरभूत काष्ठा ip_vs_dest *
ip_vs_sh_get(काष्ठा ip_vs_service *svc, काष्ठा ip_vs_sh_state *s,
	     स्थिर जोड़ nf_inet_addr *addr, __be16 port)
अणु
	अचिन्हित पूर्णांक hash = ip_vs_sh_hashkey(svc->af, addr, port, 0);
	काष्ठा ip_vs_dest *dest = rcu_dereference(s->buckets[hash].dest);

	वापस (!dest || is_unavailable(dest)) ? शून्य : dest;
पूर्ण


/* As ip_vs_sh_get, but with fallback अगर selected server is unavailable
 *
 * The fallback strategy loops around the table starting from a "random"
 * poपूर्णांक (in fact, it is chosen to be the original hash value to make the
 * algorithm deterministic) to find a new server.
 */
अटल अंतरभूत काष्ठा ip_vs_dest *
ip_vs_sh_get_fallback(काष्ठा ip_vs_service *svc, काष्ठा ip_vs_sh_state *s,
		      स्थिर जोड़ nf_inet_addr *addr, __be16 port)
अणु
	अचिन्हित पूर्णांक offset, roffset;
	अचिन्हित पूर्णांक hash, ihash;
	काष्ठा ip_vs_dest *dest;

	/* first try the dest it's supposed to go to */
	ihash = ip_vs_sh_hashkey(svc->af, addr, port, 0);
	dest = rcu_dereference(s->buckets[ihash].dest);
	अगर (!dest)
		वापस शून्य;
	अगर (!is_unavailable(dest))
		वापस dest;

	IP_VS_DBG_BUF(6, "SH: selected unavailable server %s:%d, reselecting",
		      IP_VS_DBG_ADDR(dest->af, &dest->addr), ntohs(dest->port));

	/* अगर the original dest is unavailable, loop around the table
	 * starting from ihash to find a new dest
	 */
	क्रम (offset = 0; offset < IP_VS_SH_TAB_SIZE; offset++) अणु
		roffset = (offset + ihash) % IP_VS_SH_TAB_SIZE;
		hash = ip_vs_sh_hashkey(svc->af, addr, port, roffset);
		dest = rcu_dereference(s->buckets[hash].dest);
		अगर (!dest)
			अवरोध;
		अगर (!is_unavailable(dest))
			वापस dest;
		IP_VS_DBG_BUF(6, "SH: selected unavailable "
			      "server %s:%d (offset %d), reselecting",
			      IP_VS_DBG_ADDR(dest->af, &dest->addr),
			      ntohs(dest->port), roffset);
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 *      Assign all the hash buckets of the specअगरied table with the service.
 */
अटल पूर्णांक
ip_vs_sh_reassign(काष्ठा ip_vs_sh_state *s, काष्ठा ip_vs_service *svc)
अणु
	पूर्णांक i;
	काष्ठा ip_vs_sh_bucket *b;
	काष्ठा list_head *p;
	काष्ठा ip_vs_dest *dest;
	पूर्णांक d_count;
	bool empty;

	b = &s->buckets[0];
	p = &svc->destinations;
	empty = list_empty(p);
	d_count = 0;
	क्रम (i=0; i<IP_VS_SH_TAB_SIZE; i++) अणु
		dest = rcu_dereference_रक्षित(b->dest, 1);
		अगर (dest)
			ip_vs_dest_put(dest);
		अगर (empty)
			RCU_INIT_POINTER(b->dest, शून्य);
		अन्यथा अणु
			अगर (p == &svc->destinations)
				p = p->next;

			dest = list_entry(p, काष्ठा ip_vs_dest, n_list);
			ip_vs_dest_hold(dest);
			RCU_INIT_POINTER(b->dest, dest);

			IP_VS_DBG_BUF(6, "assigned i: %d dest: %s weight: %d\n",
				      i, IP_VS_DBG_ADDR(dest->af, &dest->addr),
				      atomic_पढ़ो(&dest->weight));

			/* Don't move to next dest until filling weight */
			अगर (++d_count >= atomic_पढ़ो(&dest->weight)) अणु
				p = p->next;
				d_count = 0;
			पूर्ण

		पूर्ण
		b++;
	पूर्ण
	वापस 0;
पूर्ण


/*
 *      Flush all the hash buckets of the specअगरied table.
 */
अटल व्योम ip_vs_sh_flush(काष्ठा ip_vs_sh_state *s)
अणु
	पूर्णांक i;
	काष्ठा ip_vs_sh_bucket *b;
	काष्ठा ip_vs_dest *dest;

	b = &s->buckets[0];
	क्रम (i=0; i<IP_VS_SH_TAB_SIZE; i++) अणु
		dest = rcu_dereference_रक्षित(b->dest, 1);
		अगर (dest) अणु
			ip_vs_dest_put(dest);
			RCU_INIT_POINTER(b->dest, शून्य);
		पूर्ण
		b++;
	पूर्ण
पूर्ण


अटल पूर्णांक ip_vs_sh_init_svc(काष्ठा ip_vs_service *svc)
अणु
	काष्ठा ip_vs_sh_state *s;

	/* allocate the SH table क्रम this service */
	s = kzalloc(माप(काष्ठा ip_vs_sh_state), GFP_KERNEL);
	अगर (s == शून्य)
		वापस -ENOMEM;

	svc->sched_data = s;
	IP_VS_DBG(6, "SH hash table (memory=%zdbytes) allocated for "
		  "current service\n",
		  माप(काष्ठा ip_vs_sh_bucket)*IP_VS_SH_TAB_SIZE);

	/* assign the hash buckets with current dests */
	ip_vs_sh_reassign(s, svc);

	वापस 0;
पूर्ण


अटल व्योम ip_vs_sh_करोne_svc(काष्ठा ip_vs_service *svc)
अणु
	काष्ठा ip_vs_sh_state *s = svc->sched_data;

	/* got to clean up hash buckets here */
	ip_vs_sh_flush(s);

	/* release the table itself */
	kमुक्त_rcu(s, rcu_head);
	IP_VS_DBG(6, "SH hash table (memory=%zdbytes) released\n",
		  माप(काष्ठा ip_vs_sh_bucket)*IP_VS_SH_TAB_SIZE);
पूर्ण


अटल पूर्णांक ip_vs_sh_dest_changed(काष्ठा ip_vs_service *svc,
				 काष्ठा ip_vs_dest *dest)
अणु
	काष्ठा ip_vs_sh_state *s = svc->sched_data;

	/* assign the hash buckets with the updated service */
	ip_vs_sh_reassign(s, svc);

	वापस 0;
पूर्ण


/* Helper function to get port number */
अटल अंतरभूत __be16
ip_vs_sh_get_port(स्थिर काष्ठा sk_buff *skb, काष्ठा ip_vs_iphdr *iph)
अणु
	__be16 _ports[2], *ports;

	/* At this poपूर्णांक we know that we have a valid packet of some kind.
	 * Because ICMP packets are only guaranteed to have the first 8
	 * bytes, let's just grab the ports.  Fortunately they're in the
	 * same position क्रम all three of the protocols we care about.
	 */
	चयन (iph->protocol) अणु
	हाल IPPROTO_TCP:
	हाल IPPROTO_UDP:
	हाल IPPROTO_SCTP:
		ports = skb_header_poपूर्णांकer(skb, iph->len, माप(_ports),
					   &_ports);
		अगर (unlikely(!ports))
			वापस 0;

		अगर (likely(!ip_vs_iph_inverse(iph)))
			वापस ports[0];
		अन्यथा
			वापस ports[1];
	शेष:
		वापस 0;
	पूर्ण
पूर्ण


/*
 *      Source Hashing scheduling
 */
अटल काष्ठा ip_vs_dest *
ip_vs_sh_schedule(काष्ठा ip_vs_service *svc, स्थिर काष्ठा sk_buff *skb,
		  काष्ठा ip_vs_iphdr *iph)
अणु
	काष्ठा ip_vs_dest *dest;
	काष्ठा ip_vs_sh_state *s;
	__be16 port = 0;
	स्थिर जोड़ nf_inet_addr *hash_addr;

	hash_addr = ip_vs_iph_inverse(iph) ? &iph->daddr : &iph->saddr;

	IP_VS_DBG(6, "ip_vs_sh_schedule(): Scheduling...\n");

	अगर (svc->flags & IP_VS_SVC_F_SCHED_SH_PORT)
		port = ip_vs_sh_get_port(skb, iph);

	s = (काष्ठा ip_vs_sh_state *) svc->sched_data;

	अगर (svc->flags & IP_VS_SVC_F_SCHED_SH_FALLBACK)
		dest = ip_vs_sh_get_fallback(svc, s, hash_addr, port);
	अन्यथा
		dest = ip_vs_sh_get(svc, s, hash_addr, port);

	अगर (!dest) अणु
		ip_vs_scheduler_err(svc, "no destination available");
		वापस शून्य;
	पूर्ण

	IP_VS_DBG_BUF(6, "SH: source IP address %s --> server %s:%d\n",
		      IP_VS_DBG_ADDR(svc->af, hash_addr),
		      IP_VS_DBG_ADDR(dest->af, &dest->addr),
		      ntohs(dest->port));

	वापस dest;
पूर्ण


/*
 *      IPVS SH Scheduler काष्ठाure
 */
अटल काष्ठा ip_vs_scheduler ip_vs_sh_scheduler =
अणु
	.name =			"sh",
	.refcnt =		ATOMIC_INIT(0),
	.module =		THIS_MODULE,
	.n_list	 =		LIST_HEAD_INIT(ip_vs_sh_scheduler.n_list),
	.init_service =		ip_vs_sh_init_svc,
	.करोne_service =		ip_vs_sh_करोne_svc,
	.add_dest =		ip_vs_sh_dest_changed,
	.del_dest =		ip_vs_sh_dest_changed,
	.upd_dest =		ip_vs_sh_dest_changed,
	.schedule =		ip_vs_sh_schedule,
पूर्ण;


अटल पूर्णांक __init ip_vs_sh_init(व्योम)
अणु
	वापस रेजिस्टर_ip_vs_scheduler(&ip_vs_sh_scheduler);
पूर्ण


अटल व्योम __निकास ip_vs_sh_cleanup(व्योम)
अणु
	unरेजिस्टर_ip_vs_scheduler(&ip_vs_sh_scheduler);
	synchronize_rcu();
पूर्ण


module_init(ip_vs_sh_init);
module_निकास(ip_vs_sh_cleanup);
MODULE_LICENSE("GPL");
