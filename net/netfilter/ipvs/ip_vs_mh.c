<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* IPVS:	Maglev Hashing scheduling module
 *
 * Authors:	Inju Song <inju.song@navercorp.com>
 *
 */

/* The mh algorithm is to assignत a preference list of all the lookup
 * table positions to each destination and populate the table with
 * the most-preferred position of destinations. Then it is to select
 * destination with the hash key of source IP addressत through looking
 * up a the lookup table.
 *
 * The algorithm is detailed in:
 * [3.4 Consistent Hasing]
https://www.usenix.org/प्रणाली/files/conference/nsdi16/nsdi16-paper-eisenbud.pdf
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

#समावेश <linux/siphash.h>
#समावेश <linux/bitops.h>
#समावेश <linux/gcd.h>

#घोषणा IP_VS_SVC_F_SCHED_MH_FALLBACK	IP_VS_SVC_F_SCHED1 /* MH fallback */
#घोषणा IP_VS_SVC_F_SCHED_MH_PORT	IP_VS_SVC_F_SCHED2 /* MH use port */

काष्ठा ip_vs_mh_lookup अणु
	काष्ठा ip_vs_dest __rcu	*dest;	/* real server (cache) */
पूर्ण;

काष्ठा ip_vs_mh_dest_setup अणु
	अचिन्हित पूर्णांक	offset; /* starting offset */
	अचिन्हित पूर्णांक	skip;	/* skip */
	अचिन्हित पूर्णांक	perm;	/* next_offset */
	पूर्णांक		turns;	/* weight / gcd() and rshअगरt */
पूर्ण;

/* Available prime numbers क्रम MH table */
अटल पूर्णांक primes[] = अणु251, 509, 1021, 2039, 4093,
		       8191, 16381, 32749, 65521, 131071पूर्ण;

/* For IPVS MH entry hash table */
#अगर_अघोषित CONFIG_IP_VS_MH_TAB_INDEX
#घोषणा CONFIG_IP_VS_MH_TAB_INDEX	12
#पूर्ण_अगर
#घोषणा IP_VS_MH_TAB_BITS		(CONFIG_IP_VS_MH_TAB_INDEX / 2)
#घोषणा IP_VS_MH_TAB_INDEX		(CONFIG_IP_VS_MH_TAB_INDEX - 8)
#घोषणा IP_VS_MH_TAB_SIZE               primes[IP_VS_MH_TAB_INDEX]

काष्ठा ip_vs_mh_state अणु
	काष्ठा rcu_head			rcu_head;
	काष्ठा ip_vs_mh_lookup		*lookup;
	काष्ठा ip_vs_mh_dest_setup	*dest_setup;
	hsiphash_key_t			hash1, hash2;
	पूर्णांक				gcd;
	पूर्णांक				rshअगरt;
पूर्ण;

अटल अंतरभूत व्योम generate_hash_secret(hsiphash_key_t *hash1,
					hsiphash_key_t *hash2)
अणु
	hash1->key[0] = 2654435761UL;
	hash1->key[1] = 2654435761UL;

	hash2->key[0] = 2654446892UL;
	hash2->key[1] = 2654446892UL;
पूर्ण

/* Helper function to determine अगर server is unavailable */
अटल अंतरभूत bool is_unavailable(काष्ठा ip_vs_dest *dest)
अणु
	वापस atomic_पढ़ो(&dest->weight) <= 0 ||
	       dest->flags & IP_VS_DEST_F_OVERLOAD;
पूर्ण

/* Returns hash value क्रम IPVS MH entry */
अटल अंतरभूत अचिन्हित पूर्णांक
ip_vs_mh_hashkey(पूर्णांक af, स्थिर जोड़ nf_inet_addr *addr,
		 __be16 port, hsiphash_key_t *key, अचिन्हित पूर्णांक offset)
अणु
	अचिन्हित पूर्णांक v;
	__be32 addr_fold = addr->ip;

#अगर_घोषित CONFIG_IP_VS_IPV6
	अगर (af == AF_INET6)
		addr_fold = addr->ip6[0] ^ addr->ip6[1] ^
			    addr->ip6[2] ^ addr->ip6[3];
#पूर्ण_अगर
	v = (offset + ntohs(port) + ntohl(addr_fold));
	वापस hsiphash(&v, माप(v), key);
पूर्ण

/* Reset all the hash buckets of the specअगरied table. */
अटल व्योम ip_vs_mh_reset(काष्ठा ip_vs_mh_state *s)
अणु
	पूर्णांक i;
	काष्ठा ip_vs_mh_lookup *l;
	काष्ठा ip_vs_dest *dest;

	l = &s->lookup[0];
	क्रम (i = 0; i < IP_VS_MH_TAB_SIZE; i++) अणु
		dest = rcu_dereference_रक्षित(l->dest, 1);
		अगर (dest) अणु
			ip_vs_dest_put(dest);
			RCU_INIT_POINTER(l->dest, शून्य);
		पूर्ण
		l++;
	पूर्ण
पूर्ण

अटल पूर्णांक ip_vs_mh_permutate(काष्ठा ip_vs_mh_state *s,
			      काष्ठा ip_vs_service *svc)
अणु
	काष्ठा list_head *p;
	काष्ठा ip_vs_mh_dest_setup *ds;
	काष्ठा ip_vs_dest *dest;
	पूर्णांक lw;

	/* If gcd is smaller then 1, number of dests or
	 * all last_weight of dests are zero. So, skip
	 * permutation क्रम the dests.
	 */
	अगर (s->gcd < 1)
		वापस 0;

	/* Set dest_setup क्रम the dests permutation */
	p = &svc->destinations;
	ds = &s->dest_setup[0];
	जबतक ((p = p->next) != &svc->destinations) अणु
		dest = list_entry(p, काष्ठा ip_vs_dest, n_list);

		ds->offset = ip_vs_mh_hashkey(svc->af, &dest->addr,
					      dest->port, &s->hash1, 0) %
					      IP_VS_MH_TAB_SIZE;
		ds->skip = ip_vs_mh_hashkey(svc->af, &dest->addr,
					    dest->port, &s->hash2, 0) %
					    (IP_VS_MH_TAB_SIZE - 1) + 1;
		ds->perm = ds->offset;

		lw = atomic_पढ़ो(&dest->last_weight);
		ds->turns = ((lw / s->gcd) >> s->rshअगरt) ? : (lw != 0);
		ds++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ip_vs_mh_populate(काष्ठा ip_vs_mh_state *s,
			     काष्ठा ip_vs_service *svc)
अणु
	पूर्णांक n, c, dt_count;
	अचिन्हित दीर्घ *table;
	काष्ठा list_head *p;
	काष्ठा ip_vs_mh_dest_setup *ds;
	काष्ठा ip_vs_dest *dest, *new_dest;

	/* If gcd is smaller then 1, number of dests or
	 * all last_weight of dests are zero. So, skip
	 * the population क्रम the dests and reset lookup table.
	 */
	अगर (s->gcd < 1) अणु
		ip_vs_mh_reset(s);
		वापस 0;
	पूर्ण

	table = kसुस्मृति(BITS_TO_LONGS(IP_VS_MH_TAB_SIZE),
			माप(अचिन्हित दीर्घ), GFP_KERNEL);
	अगर (!table)
		वापस -ENOMEM;

	p = &svc->destinations;
	n = 0;
	dt_count = 0;
	जबतक (n < IP_VS_MH_TAB_SIZE) अणु
		अगर (p == &svc->destinations)
			p = p->next;

		ds = &s->dest_setup[0];
		जबतक (p != &svc->destinations) अणु
			/* Ignore added server with zero weight */
			अगर (ds->turns < 1) अणु
				p = p->next;
				ds++;
				जारी;
			पूर्ण

			c = ds->perm;
			जबतक (test_bit(c, table)) अणु
				/* Add skip, mod IP_VS_MH_TAB_SIZE */
				ds->perm += ds->skip;
				अगर (ds->perm >= IP_VS_MH_TAB_SIZE)
					ds->perm -= IP_VS_MH_TAB_SIZE;
				c = ds->perm;
			पूर्ण

			__set_bit(c, table);

			dest = rcu_dereference_रक्षित(s->lookup[c].dest, 1);
			new_dest = list_entry(p, काष्ठा ip_vs_dest, n_list);
			अगर (dest != new_dest) अणु
				अगर (dest)
					ip_vs_dest_put(dest);
				ip_vs_dest_hold(new_dest);
				RCU_INIT_POINTER(s->lookup[c].dest, new_dest);
			पूर्ण

			अगर (++n == IP_VS_MH_TAB_SIZE)
				जाओ out;

			अगर (++dt_count >= ds->turns) अणु
				dt_count = 0;
				p = p->next;
				ds++;
			पूर्ण
		पूर्ण
	पूर्ण

out:
	kमुक्त(table);
	वापस 0;
पूर्ण

/* Get ip_vs_dest associated with supplied parameters. */
अटल अंतरभूत काष्ठा ip_vs_dest *
ip_vs_mh_get(काष्ठा ip_vs_service *svc, काष्ठा ip_vs_mh_state *s,
	     स्थिर जोड़ nf_inet_addr *addr, __be16 port)
अणु
	अचिन्हित पूर्णांक hash = ip_vs_mh_hashkey(svc->af, addr, port, &s->hash1, 0)
					     % IP_VS_MH_TAB_SIZE;
	काष्ठा ip_vs_dest *dest = rcu_dereference(s->lookup[hash].dest);

	वापस (!dest || is_unavailable(dest)) ? शून्य : dest;
पूर्ण

/* As ip_vs_mh_get, but with fallback अगर selected server is unavailable */
अटल अंतरभूत काष्ठा ip_vs_dest *
ip_vs_mh_get_fallback(काष्ठा ip_vs_service *svc, काष्ठा ip_vs_mh_state *s,
		      स्थिर जोड़ nf_inet_addr *addr, __be16 port)
अणु
	अचिन्हित पूर्णांक offset, roffset;
	अचिन्हित पूर्णांक hash, ihash;
	काष्ठा ip_vs_dest *dest;

	/* First try the dest it's supposed to go to */
	ihash = ip_vs_mh_hashkey(svc->af, addr, port,
				 &s->hash1, 0) % IP_VS_MH_TAB_SIZE;
	dest = rcu_dereference(s->lookup[ihash].dest);
	अगर (!dest)
		वापस शून्य;
	अगर (!is_unavailable(dest))
		वापस dest;

	IP_VS_DBG_BUF(6, "MH: selected unavailable server %s:%u, reselecting",
		      IP_VS_DBG_ADDR(dest->af, &dest->addr), ntohs(dest->port));

	/* If the original dest is unavailable, loop around the table
	 * starting from ihash to find a new dest
	 */
	क्रम (offset = 0; offset < IP_VS_MH_TAB_SIZE; offset++) अणु
		roffset = (offset + ihash) % IP_VS_MH_TAB_SIZE;
		hash = ip_vs_mh_hashkey(svc->af, addr, port, &s->hash1,
					roffset) % IP_VS_MH_TAB_SIZE;
		dest = rcu_dereference(s->lookup[hash].dest);
		अगर (!dest)
			अवरोध;
		अगर (!is_unavailable(dest))
			वापस dest;
		IP_VS_DBG_BUF(6,
			      "MH: selected unavailable server %s:%u (offset %u), reselecting",
			      IP_VS_DBG_ADDR(dest->af, &dest->addr),
			      ntohs(dest->port), roffset);
	पूर्ण

	वापस शून्य;
पूर्ण

/* Assign all the hash buckets of the specअगरied table with the service. */
अटल पूर्णांक ip_vs_mh_reassign(काष्ठा ip_vs_mh_state *s,
			     काष्ठा ip_vs_service *svc)
अणु
	पूर्णांक ret;

	अगर (svc->num_dests > IP_VS_MH_TAB_SIZE)
		वापस -EINVAL;

	अगर (svc->num_dests >= 1) अणु
		s->dest_setup = kसुस्मृति(svc->num_dests,
					माप(काष्ठा ip_vs_mh_dest_setup),
					GFP_KERNEL);
		अगर (!s->dest_setup)
			वापस -ENOMEM;
	पूर्ण

	ip_vs_mh_permutate(s, svc);

	ret = ip_vs_mh_populate(s, svc);
	अगर (ret < 0)
		जाओ out;

	IP_VS_DBG_BUF(6, "MH: reassign lookup table of %s:%u\n",
		      IP_VS_DBG_ADDR(svc->af, &svc->addr),
		      ntohs(svc->port));

out:
	अगर (svc->num_dests >= 1) अणु
		kमुक्त(s->dest_setup);
		s->dest_setup = शून्य;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक ip_vs_mh_gcd_weight(काष्ठा ip_vs_service *svc)
अणु
	काष्ठा ip_vs_dest *dest;
	पूर्णांक weight;
	पूर्णांक g = 0;

	list_क्रम_each_entry(dest, &svc->destinations, n_list) अणु
		weight = atomic_पढ़ो(&dest->last_weight);
		अगर (weight > 0) अणु
			अगर (g > 0)
				g = gcd(weight, g);
			अन्यथा
				g = weight;
		पूर्ण
	पूर्ण
	वापस g;
पूर्ण

/* To aव्योम assigning huge weight क्रम the MH table,
 * calculate shअगरt value with gcd.
 */
अटल पूर्णांक ip_vs_mh_shअगरt_weight(काष्ठा ip_vs_service *svc, पूर्णांक gcd)
अणु
	काष्ठा ip_vs_dest *dest;
	पूर्णांक new_weight, weight = 0;
	पूर्णांक mw, shअगरt;

	/* If gcd is smaller then 1, number of dests or
	 * all last_weight of dests are zero. So, वापस
	 * shअगरt value as zero.
	 */
	अगर (gcd < 1)
		वापस 0;

	list_क्रम_each_entry(dest, &svc->destinations, n_list) अणु
		new_weight = atomic_पढ़ो(&dest->last_weight);
		अगर (new_weight > weight)
			weight = new_weight;
	पूर्ण

	/* Because gcd is greater than zero,
	 * the maximum weight and gcd are always greater than zero
	 */
	mw = weight / gcd;

	/* shअगरt = occupied bits of weight/gcd - MH highest bits */
	shअगरt = fls(mw) - IP_VS_MH_TAB_BITS;
	वापस (shअगरt >= 0) ? shअगरt : 0;
पूर्ण

अटल व्योम ip_vs_mh_state_मुक्त(काष्ठा rcu_head *head)
अणु
	काष्ठा ip_vs_mh_state *s;

	s = container_of(head, काष्ठा ip_vs_mh_state, rcu_head);
	kमुक्त(s->lookup);
	kमुक्त(s);
पूर्ण

अटल पूर्णांक ip_vs_mh_init_svc(काष्ठा ip_vs_service *svc)
अणु
	पूर्णांक ret;
	काष्ठा ip_vs_mh_state *s;

	/* Allocate the MH table क्रम this service */
	s = kzalloc(माप(*s), GFP_KERNEL);
	अगर (!s)
		वापस -ENOMEM;

	s->lookup = kसुस्मृति(IP_VS_MH_TAB_SIZE, माप(काष्ठा ip_vs_mh_lookup),
			    GFP_KERNEL);
	अगर (!s->lookup) अणु
		kमुक्त(s);
		वापस -ENOMEM;
	पूर्ण

	generate_hash_secret(&s->hash1, &s->hash2);
	s->gcd = ip_vs_mh_gcd_weight(svc);
	s->rshअगरt = ip_vs_mh_shअगरt_weight(svc, s->gcd);

	IP_VS_DBG(6,
		  "MH lookup table (memory=%zdbytes) allocated for current service\n",
		  माप(काष्ठा ip_vs_mh_lookup) * IP_VS_MH_TAB_SIZE);

	/* Assign the lookup table with current dests */
	ret = ip_vs_mh_reassign(s, svc);
	अगर (ret < 0) अणु
		ip_vs_mh_reset(s);
		ip_vs_mh_state_मुक्त(&s->rcu_head);
		वापस ret;
	पूर्ण

	/* No more failures, attach state */
	svc->sched_data = s;
	वापस 0;
पूर्ण

अटल व्योम ip_vs_mh_करोne_svc(काष्ठा ip_vs_service *svc)
अणु
	काष्ठा ip_vs_mh_state *s = svc->sched_data;

	/* Got to clean up lookup entry here */
	ip_vs_mh_reset(s);

	call_rcu(&s->rcu_head, ip_vs_mh_state_मुक्त);
	IP_VS_DBG(6, "MH lookup table (memory=%zdbytes) released\n",
		  माप(काष्ठा ip_vs_mh_lookup) * IP_VS_MH_TAB_SIZE);
पूर्ण

अटल पूर्णांक ip_vs_mh_dest_changed(काष्ठा ip_vs_service *svc,
				 काष्ठा ip_vs_dest *dest)
अणु
	काष्ठा ip_vs_mh_state *s = svc->sched_data;

	s->gcd = ip_vs_mh_gcd_weight(svc);
	s->rshअगरt = ip_vs_mh_shअगरt_weight(svc, s->gcd);

	/* Assign the lookup table with the updated service */
	वापस ip_vs_mh_reassign(s, svc);
पूर्ण

/* Helper function to get port number */
अटल अंतरभूत __be16
ip_vs_mh_get_port(स्थिर काष्ठा sk_buff *skb, काष्ठा ip_vs_iphdr *iph)
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

/* Maglev Hashing scheduling */
अटल काष्ठा ip_vs_dest *
ip_vs_mh_schedule(काष्ठा ip_vs_service *svc, स्थिर काष्ठा sk_buff *skb,
		  काष्ठा ip_vs_iphdr *iph)
अणु
	काष्ठा ip_vs_dest *dest;
	काष्ठा ip_vs_mh_state *s;
	__be16 port = 0;
	स्थिर जोड़ nf_inet_addr *hash_addr;

	hash_addr = ip_vs_iph_inverse(iph) ? &iph->daddr : &iph->saddr;

	IP_VS_DBG(6, "%s : Scheduling...\n", __func__);

	अगर (svc->flags & IP_VS_SVC_F_SCHED_MH_PORT)
		port = ip_vs_mh_get_port(skb, iph);

	s = (काष्ठा ip_vs_mh_state *)svc->sched_data;

	अगर (svc->flags & IP_VS_SVC_F_SCHED_MH_FALLBACK)
		dest = ip_vs_mh_get_fallback(svc, s, hash_addr, port);
	अन्यथा
		dest = ip_vs_mh_get(svc, s, hash_addr, port);

	अगर (!dest) अणु
		ip_vs_scheduler_err(svc, "no destination available");
		वापस शून्य;
	पूर्ण

	IP_VS_DBG_BUF(6, "MH: source IP address %s:%u --> server %s:%u\n",
		      IP_VS_DBG_ADDR(svc->af, hash_addr),
		      ntohs(port),
		      IP_VS_DBG_ADDR(dest->af, &dest->addr),
		      ntohs(dest->port));

	वापस dest;
पूर्ण

/* IPVS MH Scheduler काष्ठाure */
अटल काष्ठा ip_vs_scheduler ip_vs_mh_scheduler = अणु
	.name =			"mh",
	.refcnt =		ATOMIC_INIT(0),
	.module =		THIS_MODULE,
	.n_list	 =		LIST_HEAD_INIT(ip_vs_mh_scheduler.n_list),
	.init_service =		ip_vs_mh_init_svc,
	.करोne_service =		ip_vs_mh_करोne_svc,
	.add_dest =		ip_vs_mh_dest_changed,
	.del_dest =		ip_vs_mh_dest_changed,
	.upd_dest =		ip_vs_mh_dest_changed,
	.schedule =		ip_vs_mh_schedule,
पूर्ण;

अटल पूर्णांक __init ip_vs_mh_init(व्योम)
अणु
	वापस रेजिस्टर_ip_vs_scheduler(&ip_vs_mh_scheduler);
पूर्ण

अटल व्योम __निकास ip_vs_mh_cleanup(व्योम)
अणु
	unरेजिस्टर_ip_vs_scheduler(&ip_vs_mh_scheduler);
	rcu_barrier();
पूर्ण

module_init(ip_vs_mh_init);
module_निकास(ip_vs_mh_cleanup);
MODULE_DESCRIPTION("Maglev hashing ipvs scheduler");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Inju Song <inju.song@navercorp.com>");
