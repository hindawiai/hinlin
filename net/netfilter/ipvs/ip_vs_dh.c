<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * IPVS:        Destination Hashing scheduling module
 *
 * Authors:     Wensong Zhang <wensong@gnuchina.org>
 *
 *              Inspired by the consistent hashing scheduler patch from
 *              Thomas Proell <proellt@gmx.de>
 *
 * Changes:
 */

/*
 * The dh algorithm is to select server by the hash key of destination IP
 * address. The pseuकरो code is as follows:
 *
 *       n <- servernode[dest_ip];
 *       अगर (n is dead) OR
 *          (n is overloaded) OR (n.weight <= 0) then
 *                 वापस शून्य;
 *
 *       वापस n;
 *
 * Notes that servernode is a 256-bucket hash table that maps the hash
 * index derived from packet destination IP address to the current server
 * array. If the dh scheduler is used in cache cluster, it is good to
 * combine it with cache_bypass feature. When the अटलally asचिन्हित
 * server is dead or overloaded, the load balancer can bypass the cache
 * server and send requests to the original server directly.
 *
 */

#घोषणा KMSG_COMPONENT "IPVS"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/ip.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/hash.h>

#समावेश <net/ip_vs.h>


/*
 *      IPVS DH bucket
 */
काष्ठा ip_vs_dh_bucket अणु
	काष्ठा ip_vs_dest __rcu	*dest;	/* real server (cache) */
पूर्ण;

/*
 *     क्रम IPVS DH entry hash table
 */
#अगर_अघोषित CONFIG_IP_VS_DH_TAB_BITS
#घोषणा CONFIG_IP_VS_DH_TAB_BITS        8
#पूर्ण_अगर
#घोषणा IP_VS_DH_TAB_BITS               CONFIG_IP_VS_DH_TAB_BITS
#घोषणा IP_VS_DH_TAB_SIZE               (1 << IP_VS_DH_TAB_BITS)
#घोषणा IP_VS_DH_TAB_MASK               (IP_VS_DH_TAB_SIZE - 1)

काष्ठा ip_vs_dh_state अणु
	काष्ठा ip_vs_dh_bucket		buckets[IP_VS_DH_TAB_SIZE];
	काष्ठा rcu_head			rcu_head;
पूर्ण;

/*
 *	Returns hash value क्रम IPVS DH entry
 */
अटल अंतरभूत अचिन्हित पूर्णांक ip_vs_dh_hashkey(पूर्णांक af, स्थिर जोड़ nf_inet_addr *addr)
अणु
	__be32 addr_fold = addr->ip;

#अगर_घोषित CONFIG_IP_VS_IPV6
	अगर (af == AF_INET6)
		addr_fold = addr->ip6[0]^addr->ip6[1]^
			    addr->ip6[2]^addr->ip6[3];
#पूर्ण_अगर
	वापस hash_32(ntohl(addr_fold), IP_VS_DH_TAB_BITS);
पूर्ण


/*
 *      Get ip_vs_dest associated with supplied parameters.
 */
अटल अंतरभूत काष्ठा ip_vs_dest *
ip_vs_dh_get(पूर्णांक af, काष्ठा ip_vs_dh_state *s, स्थिर जोड़ nf_inet_addr *addr)
अणु
	वापस rcu_dereference(s->buckets[ip_vs_dh_hashkey(af, addr)].dest);
पूर्ण


/*
 *      Assign all the hash buckets of the specअगरied table with the service.
 */
अटल पूर्णांक
ip_vs_dh_reassign(काष्ठा ip_vs_dh_state *s, काष्ठा ip_vs_service *svc)
अणु
	पूर्णांक i;
	काष्ठा ip_vs_dh_bucket *b;
	काष्ठा list_head *p;
	काष्ठा ip_vs_dest *dest;
	bool empty;

	b = &s->buckets[0];
	p = &svc->destinations;
	empty = list_empty(p);
	क्रम (i=0; i<IP_VS_DH_TAB_SIZE; i++) अणु
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

			p = p->next;
		पूर्ण
		b++;
	पूर्ण
	वापस 0;
पूर्ण


/*
 *      Flush all the hash buckets of the specअगरied table.
 */
अटल व्योम ip_vs_dh_flush(काष्ठा ip_vs_dh_state *s)
अणु
	पूर्णांक i;
	काष्ठा ip_vs_dh_bucket *b;
	काष्ठा ip_vs_dest *dest;

	b = &s->buckets[0];
	क्रम (i=0; i<IP_VS_DH_TAB_SIZE; i++) अणु
		dest = rcu_dereference_रक्षित(b->dest, 1);
		अगर (dest) अणु
			ip_vs_dest_put(dest);
			RCU_INIT_POINTER(b->dest, शून्य);
		पूर्ण
		b++;
	पूर्ण
पूर्ण


अटल पूर्णांक ip_vs_dh_init_svc(काष्ठा ip_vs_service *svc)
अणु
	काष्ठा ip_vs_dh_state *s;

	/* allocate the DH table क्रम this service */
	s = kzalloc(माप(काष्ठा ip_vs_dh_state), GFP_KERNEL);
	अगर (s == शून्य)
		वापस -ENOMEM;

	svc->sched_data = s;
	IP_VS_DBG(6, "DH hash table (memory=%zdbytes) allocated for "
		  "current service\n",
		  माप(काष्ठा ip_vs_dh_bucket)*IP_VS_DH_TAB_SIZE);

	/* assign the hash buckets with current dests */
	ip_vs_dh_reassign(s, svc);

	वापस 0;
पूर्ण


अटल व्योम ip_vs_dh_करोne_svc(काष्ठा ip_vs_service *svc)
अणु
	काष्ठा ip_vs_dh_state *s = svc->sched_data;

	/* got to clean up hash buckets here */
	ip_vs_dh_flush(s);

	/* release the table itself */
	kमुक्त_rcu(s, rcu_head);
	IP_VS_DBG(6, "DH hash table (memory=%zdbytes) released\n",
		  माप(काष्ठा ip_vs_dh_bucket)*IP_VS_DH_TAB_SIZE);
पूर्ण


अटल पूर्णांक ip_vs_dh_dest_changed(काष्ठा ip_vs_service *svc,
				 काष्ठा ip_vs_dest *dest)
अणु
	काष्ठा ip_vs_dh_state *s = svc->sched_data;

	/* assign the hash buckets with the updated service */
	ip_vs_dh_reassign(s, svc);

	वापस 0;
पूर्ण


/*
 *      If the dest flags is set with IP_VS_DEST_F_OVERLOAD,
 *      consider that the server is overloaded here.
 */
अटल अंतरभूत पूर्णांक is_overloaded(काष्ठा ip_vs_dest *dest)
अणु
	वापस dest->flags & IP_VS_DEST_F_OVERLOAD;
पूर्ण


/*
 *      Destination hashing scheduling
 */
अटल काष्ठा ip_vs_dest *
ip_vs_dh_schedule(काष्ठा ip_vs_service *svc, स्थिर काष्ठा sk_buff *skb,
		  काष्ठा ip_vs_iphdr *iph)
अणु
	काष्ठा ip_vs_dest *dest;
	काष्ठा ip_vs_dh_state *s;

	IP_VS_DBG(6, "%s(): Scheduling...\n", __func__);

	s = (काष्ठा ip_vs_dh_state *) svc->sched_data;
	dest = ip_vs_dh_get(svc->af, s, &iph->daddr);
	अगर (!dest
	    || !(dest->flags & IP_VS_DEST_F_AVAILABLE)
	    || atomic_पढ़ो(&dest->weight) <= 0
	    || is_overloaded(dest)) अणु
		ip_vs_scheduler_err(svc, "no destination available");
		वापस शून्य;
	पूर्ण

	IP_VS_DBG_BUF(6, "DH: destination IP address %s --> server %s:%d\n",
		      IP_VS_DBG_ADDR(svc->af, &iph->daddr),
		      IP_VS_DBG_ADDR(dest->af, &dest->addr),
		      ntohs(dest->port));

	वापस dest;
पूर्ण


/*
 *      IPVS DH Scheduler काष्ठाure
 */
अटल काष्ठा ip_vs_scheduler ip_vs_dh_scheduler =
अणु
	.name =			"dh",
	.refcnt =		ATOMIC_INIT(0),
	.module =		THIS_MODULE,
	.n_list =		LIST_HEAD_INIT(ip_vs_dh_scheduler.n_list),
	.init_service =		ip_vs_dh_init_svc,
	.करोne_service =		ip_vs_dh_करोne_svc,
	.add_dest =		ip_vs_dh_dest_changed,
	.del_dest =		ip_vs_dh_dest_changed,
	.schedule =		ip_vs_dh_schedule,
पूर्ण;


अटल पूर्णांक __init ip_vs_dh_init(व्योम)
अणु
	वापस रेजिस्टर_ip_vs_scheduler(&ip_vs_dh_scheduler);
पूर्ण


अटल व्योम __निकास ip_vs_dh_cleanup(व्योम)
अणु
	unरेजिस्टर_ip_vs_scheduler(&ip_vs_dh_scheduler);
	synchronize_rcu();
पूर्ण


module_init(ip_vs_dh_init);
module_निकास(ip_vs_dh_cleanup);
MODULE_LICENSE("GPL");
