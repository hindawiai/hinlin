<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * IPVS:        Locality-Based Least-Connection scheduling module
 *
 * Authors:     Wensong Zhang <wensong@gnuchina.org>
 *
 * Changes:
 *     Martin Hamilton         :    fixed the terrible locking bugs
 *                                   *lock(tbl->lock) ==> *lock(&tbl->lock)
 *     Wensong Zhang           :    fixed the uninitialized tbl->lock bug
 *     Wensong Zhang           :    added करोing full expiration check to
 *                                   collect stale entries of 24+ hours when
 *                                   no partial expire check in a half hour
 *     Julian Anastasov        :    replaced del_समयr call with del_समयr_sync
 *                                   to aव्योम the possible race between समयr
 *                                   handler and del_समयr thपढ़ो in SMP
 */

/*
 * The lblc algorithm is as follows (pseuकरो code):
 *
 *       अगर cachenode[dest_ip] is null then
 *               n, cachenode[dest_ip] <- अणुweighted least-conn nodeपूर्ण;
 *       अन्यथा
 *               n <- cachenode[dest_ip];
 *               अगर (n is dead) OR
 *                  (n.conns>n.weight AND
 *                   there is a node m with m.conns<m.weight/2) then
 *                 n, cachenode[dest_ip] <- अणुweighted least-conn nodeपूर्ण;
 *
 *       वापस n;
 *
 * Thanks must go to Wenzhuo Zhang क्रम talking WCCP to me and pushing
 * me to ग_लिखो this module.
 */

#घोषणा KMSG_COMPONENT "IPVS"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/ip.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/hash.h>

/* क्रम sysctl */
#समावेश <linux/fs.h>
#समावेश <linux/sysctl.h>

#समावेश <net/ip_vs.h>


/*
 *    It is क्रम garbage collection of stale IPVS lblc entries,
 *    when the table is full.
 */
#घोषणा CHECK_EXPIRE_INTERVAL   (60*HZ)
#घोषणा ENTRY_TIMEOUT           (6*60*HZ)

#घोषणा DEFAULT_EXPIRATION	(24*60*60*HZ)

/*
 *    It is क्रम full expiration check.
 *    When there is no partial expiration check (garbage collection)
 *    in a half hour, करो a full expiration check to collect stale
 *    entries that haven't been touched क्रम a day.
 */
#घोषणा COUNT_FOR_FULL_EXPIRATION   30


/*
 *     क्रम IPVS lblc entry hash table
 */
#अगर_अघोषित CONFIG_IP_VS_LBLC_TAB_BITS
#घोषणा CONFIG_IP_VS_LBLC_TAB_BITS      10
#पूर्ण_अगर
#घोषणा IP_VS_LBLC_TAB_BITS     CONFIG_IP_VS_LBLC_TAB_BITS
#घोषणा IP_VS_LBLC_TAB_SIZE     (1 << IP_VS_LBLC_TAB_BITS)
#घोषणा IP_VS_LBLC_TAB_MASK     (IP_VS_LBLC_TAB_SIZE - 1)


/*
 *      IPVS lblc entry represents an association between destination
 *      IP address and its destination server
 */
काष्ठा ip_vs_lblc_entry अणु
	काष्ठा hlist_node	list;
	पूर्णांक			af;		/* address family */
	जोड़ nf_inet_addr      addr;           /* destination IP address */
	काष्ठा ip_vs_dest	*dest;          /* real server (cache) */
	अचिन्हित दीर्घ           lastuse;        /* last used समय */
	काष्ठा rcu_head		rcu_head;
पूर्ण;


/*
 *      IPVS lblc hash table
 */
काष्ठा ip_vs_lblc_table अणु
	काष्ठा rcu_head		rcu_head;
	काष्ठा hlist_head	bucket[IP_VS_LBLC_TAB_SIZE];  /* hash bucket */
	काष्ठा समयr_list       periodic_समयr; /* collect stale entries */
	काष्ठा ip_vs_service	*svc;		/* poपूर्णांकer back to service */
	atomic_t                entries;        /* number of entries */
	पूर्णांक                     max_size;       /* maximum size of entries */
	पूर्णांक                     rover;          /* rover क्रम expire check */
	पूर्णांक                     counter;        /* counter क्रम no expire */
	bool			dead;
पूर्ण;


/*
 *      IPVS LBLC sysctl table
 */
#अगर_घोषित CONFIG_SYSCTL
अटल काष्ठा ctl_table vs_vars_table[] = अणु
	अणु
		.procname	= "lblc_expiration",
		.data		= शून्य,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
#पूर्ण_अगर

अटल व्योम ip_vs_lblc_rcu_मुक्त(काष्ठा rcu_head *head)
अणु
	काष्ठा ip_vs_lblc_entry *en = container_of(head,
						   काष्ठा ip_vs_lblc_entry,
						   rcu_head);

	ip_vs_dest_put_and_मुक्त(en->dest);
	kमुक्त(en);
पूर्ण

अटल अंतरभूत व्योम ip_vs_lblc_del(काष्ठा ip_vs_lblc_entry *en)
अणु
	hlist_del_rcu(&en->list);
	call_rcu(&en->rcu_head, ip_vs_lblc_rcu_मुक्त);
पूर्ण

/*
 *	Returns hash value क्रम IPVS LBLC entry
 */
अटल अंतरभूत अचिन्हित पूर्णांक
ip_vs_lblc_hashkey(पूर्णांक af, स्थिर जोड़ nf_inet_addr *addr)
अणु
	__be32 addr_fold = addr->ip;

#अगर_घोषित CONFIG_IP_VS_IPV6
	अगर (af == AF_INET6)
		addr_fold = addr->ip6[0]^addr->ip6[1]^
			    addr->ip6[2]^addr->ip6[3];
#पूर्ण_अगर
	वापस hash_32(ntohl(addr_fold), IP_VS_LBLC_TAB_BITS);
पूर्ण


/*
 *	Hash an entry in the ip_vs_lblc_table.
 *	वापसs bool success.
 */
अटल व्योम
ip_vs_lblc_hash(काष्ठा ip_vs_lblc_table *tbl, काष्ठा ip_vs_lblc_entry *en)
अणु
	अचिन्हित पूर्णांक hash = ip_vs_lblc_hashkey(en->af, &en->addr);

	hlist_add_head_rcu(&en->list, &tbl->bucket[hash]);
	atomic_inc(&tbl->entries);
पूर्ण


/* Get ip_vs_lblc_entry associated with supplied parameters. */
अटल अंतरभूत काष्ठा ip_vs_lblc_entry *
ip_vs_lblc_get(पूर्णांक af, काष्ठा ip_vs_lblc_table *tbl,
	       स्थिर जोड़ nf_inet_addr *addr)
अणु
	अचिन्हित पूर्णांक hash = ip_vs_lblc_hashkey(af, addr);
	काष्ठा ip_vs_lblc_entry *en;

	hlist_क्रम_each_entry_rcu(en, &tbl->bucket[hash], list)
		अगर (ip_vs_addr_equal(af, &en->addr, addr))
			वापस en;

	वापस शून्य;
पूर्ण


/*
 * Create or update an ip_vs_lblc_entry, which is a mapping of a destination IP
 * address to a server. Called under spin lock.
 */
अटल अंतरभूत काष्ठा ip_vs_lblc_entry *
ip_vs_lblc_new(काष्ठा ip_vs_lblc_table *tbl, स्थिर जोड़ nf_inet_addr *daddr,
	       u16 af, काष्ठा ip_vs_dest *dest)
अणु
	काष्ठा ip_vs_lblc_entry *en;

	en = ip_vs_lblc_get(af, tbl, daddr);
	अगर (en) अणु
		अगर (en->dest == dest)
			वापस en;
		ip_vs_lblc_del(en);
	पूर्ण
	en = kदो_स्मृति(माप(*en), GFP_ATOMIC);
	अगर (!en)
		वापस शून्य;

	en->af = af;
	ip_vs_addr_copy(af, &en->addr, daddr);
	en->lastuse = jअगरfies;

	ip_vs_dest_hold(dest);
	en->dest = dest;

	ip_vs_lblc_hash(tbl, en);

	वापस en;
पूर्ण


/*
 *      Flush all the entries of the specअगरied table.
 */
अटल व्योम ip_vs_lblc_flush(काष्ठा ip_vs_service *svc)
अणु
	काष्ठा ip_vs_lblc_table *tbl = svc->sched_data;
	काष्ठा ip_vs_lblc_entry *en;
	काष्ठा hlist_node *next;
	पूर्णांक i;

	spin_lock_bh(&svc->sched_lock);
	tbl->dead = true;
	क्रम (i = 0; i < IP_VS_LBLC_TAB_SIZE; i++) अणु
		hlist_क्रम_each_entry_safe(en, next, &tbl->bucket[i], list) अणु
			ip_vs_lblc_del(en);
			atomic_dec(&tbl->entries);
		पूर्ण
	पूर्ण
	spin_unlock_bh(&svc->sched_lock);
पूर्ण

अटल पूर्णांक sysctl_lblc_expiration(काष्ठा ip_vs_service *svc)
अणु
#अगर_घोषित CONFIG_SYSCTL
	वापस svc->ipvs->sysctl_lblc_expiration;
#अन्यथा
	वापस DEFAULT_EXPIRATION;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम ip_vs_lblc_full_check(काष्ठा ip_vs_service *svc)
अणु
	काष्ठा ip_vs_lblc_table *tbl = svc->sched_data;
	काष्ठा ip_vs_lblc_entry *en;
	काष्ठा hlist_node *next;
	अचिन्हित दीर्घ now = jअगरfies;
	पूर्णांक i, j;

	क्रम (i = 0, j = tbl->rover; i < IP_VS_LBLC_TAB_SIZE; i++) अणु
		j = (j + 1) & IP_VS_LBLC_TAB_MASK;

		spin_lock(&svc->sched_lock);
		hlist_क्रम_each_entry_safe(en, next, &tbl->bucket[j], list) अणु
			अगर (समय_beक्रमe(now,
					en->lastuse +
					sysctl_lblc_expiration(svc)))
				जारी;

			ip_vs_lblc_del(en);
			atomic_dec(&tbl->entries);
		पूर्ण
		spin_unlock(&svc->sched_lock);
	पूर्ण
	tbl->rover = j;
पूर्ण


/*
 *      Periodical समयr handler क्रम IPVS lblc table
 *      It is used to collect stale entries when the number of entries
 *      exceeds the maximum size of the table.
 *
 *      Fixme: we probably need more complicated algorithm to collect
 *             entries that have not been used क्रम a दीर्घ समय even
 *             अगर the number of entries करोesn't exceed the maximum size
 *             of the table.
 *      The full expiration check is क्रम this purpose now.
 */
अटल व्योम ip_vs_lblc_check_expire(काष्ठा समयr_list *t)
अणु
	काष्ठा ip_vs_lblc_table *tbl = from_समयr(tbl, t, periodic_समयr);
	काष्ठा ip_vs_service *svc = tbl->svc;
	अचिन्हित दीर्घ now = jअगरfies;
	पूर्णांक goal;
	पूर्णांक i, j;
	काष्ठा ip_vs_lblc_entry *en;
	काष्ठा hlist_node *next;

	अगर ((tbl->counter % COUNT_FOR_FULL_EXPIRATION) == 0) अणु
		/* करो full expiration check */
		ip_vs_lblc_full_check(svc);
		tbl->counter = 1;
		जाओ out;
	पूर्ण

	अगर (atomic_पढ़ो(&tbl->entries) <= tbl->max_size) अणु
		tbl->counter++;
		जाओ out;
	पूर्ण

	goal = (atomic_पढ़ो(&tbl->entries) - tbl->max_size)*4/3;
	अगर (goal > tbl->max_size/2)
		goal = tbl->max_size/2;

	क्रम (i = 0, j = tbl->rover; i < IP_VS_LBLC_TAB_SIZE; i++) अणु
		j = (j + 1) & IP_VS_LBLC_TAB_MASK;

		spin_lock(&svc->sched_lock);
		hlist_क्रम_each_entry_safe(en, next, &tbl->bucket[j], list) अणु
			अगर (समय_beक्रमe(now, en->lastuse + ENTRY_TIMEOUT))
				जारी;

			ip_vs_lblc_del(en);
			atomic_dec(&tbl->entries);
			goal--;
		पूर्ण
		spin_unlock(&svc->sched_lock);
		अगर (goal <= 0)
			अवरोध;
	पूर्ण
	tbl->rover = j;

  out:
	mod_समयr(&tbl->periodic_समयr, jअगरfies + CHECK_EXPIRE_INTERVAL);
पूर्ण


अटल पूर्णांक ip_vs_lblc_init_svc(काष्ठा ip_vs_service *svc)
अणु
	पूर्णांक i;
	काष्ठा ip_vs_lblc_table *tbl;

	/*
	 *    Allocate the ip_vs_lblc_table क्रम this service
	 */
	tbl = kदो_स्मृति(माप(*tbl), GFP_KERNEL);
	अगर (tbl == शून्य)
		वापस -ENOMEM;

	svc->sched_data = tbl;
	IP_VS_DBG(6, "LBLC hash table (memory=%zdbytes) allocated for "
		  "current service\n", माप(*tbl));

	/*
	 *    Initialize the hash buckets
	 */
	क्रम (i = 0; i < IP_VS_LBLC_TAB_SIZE; i++) अणु
		INIT_HLIST_HEAD(&tbl->bucket[i]);
	पूर्ण
	tbl->max_size = IP_VS_LBLC_TAB_SIZE*16;
	tbl->rover = 0;
	tbl->counter = 1;
	tbl->dead = false;
	tbl->svc = svc;
	atomic_set(&tbl->entries, 0);

	/*
	 *    Hook periodic समयr क्रम garbage collection
	 */
	समयr_setup(&tbl->periodic_समयr, ip_vs_lblc_check_expire, 0);
	mod_समयr(&tbl->periodic_समयr, jअगरfies + CHECK_EXPIRE_INTERVAL);

	वापस 0;
पूर्ण


अटल व्योम ip_vs_lblc_करोne_svc(काष्ठा ip_vs_service *svc)
अणु
	काष्ठा ip_vs_lblc_table *tbl = svc->sched_data;

	/* हटाओ periodic समयr */
	del_समयr_sync(&tbl->periodic_समयr);

	/* got to clean up table entries here */
	ip_vs_lblc_flush(svc);

	/* release the table itself */
	kमुक्त_rcu(tbl, rcu_head);
	IP_VS_DBG(6, "LBLC hash table (memory=%zdbytes) released\n",
		  माप(*tbl));
पूर्ण


अटल अंतरभूत काष्ठा ip_vs_dest *
__ip_vs_lblc_schedule(काष्ठा ip_vs_service *svc)
अणु
	काष्ठा ip_vs_dest *dest, *least;
	पूर्णांक loh, करोh;

	/*
	 * We use the following क्रमmula to estimate the load:
	 *                (dest overhead) / dest->weight
	 *
	 * Remember -- no भग्नs in kernel mode!!!
	 * The comparison of h1*w2 > h2*w1 is equivalent to that of
	 *                h1/w1 > h2/w2
	 * अगर every weight is larger than zero.
	 *
	 * The server with weight=0 is quiesced and will not receive any
	 * new connection.
	 */
	list_क्रम_each_entry_rcu(dest, &svc->destinations, n_list) अणु
		अगर (dest->flags & IP_VS_DEST_F_OVERLOAD)
			जारी;
		अगर (atomic_पढ़ो(&dest->weight) > 0) अणु
			least = dest;
			loh = ip_vs_dest_conn_overhead(least);
			जाओ nextstage;
		पूर्ण
	पूर्ण
	वापस शून्य;

	/*
	 *    Find the destination with the least load.
	 */
  nextstage:
	list_क्रम_each_entry_जारी_rcu(dest, &svc->destinations, n_list) अणु
		अगर (dest->flags & IP_VS_DEST_F_OVERLOAD)
			जारी;

		करोh = ip_vs_dest_conn_overhead(dest);
		अगर ((__s64)loh * atomic_पढ़ो(&dest->weight) >
		    (__s64)करोh * atomic_पढ़ो(&least->weight)) अणु
			least = dest;
			loh = करोh;
		पूर्ण
	पूर्ण

	IP_VS_DBG_BUF(6, "LBLC: server %s:%d "
		      "activeconns %d refcnt %d weight %d overhead %d\n",
		      IP_VS_DBG_ADDR(least->af, &least->addr),
		      ntohs(least->port),
		      atomic_पढ़ो(&least->activeconns),
		      refcount_पढ़ो(&least->refcnt),
		      atomic_पढ़ो(&least->weight), loh);

	वापस least;
पूर्ण


/*
 *   If this destination server is overloaded and there is a less loaded
 *   server, then वापस true.
 */
अटल अंतरभूत पूर्णांक
is_overloaded(काष्ठा ip_vs_dest *dest, काष्ठा ip_vs_service *svc)
अणु
	अगर (atomic_पढ़ो(&dest->activeconns) > atomic_पढ़ो(&dest->weight)) अणु
		काष्ठा ip_vs_dest *d;

		list_क्रम_each_entry_rcu(d, &svc->destinations, n_list) अणु
			अगर (atomic_पढ़ो(&d->activeconns)*2
			    < atomic_पढ़ो(&d->weight)) अणु
				वापस 1;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण


/*
 *    Locality-Based (weighted) Least-Connection scheduling
 */
अटल काष्ठा ip_vs_dest *
ip_vs_lblc_schedule(काष्ठा ip_vs_service *svc, स्थिर काष्ठा sk_buff *skb,
		    काष्ठा ip_vs_iphdr *iph)
अणु
	काष्ठा ip_vs_lblc_table *tbl = svc->sched_data;
	काष्ठा ip_vs_dest *dest = शून्य;
	काष्ठा ip_vs_lblc_entry *en;

	IP_VS_DBG(6, "%s(): Scheduling...\n", __func__);

	/* First look in our cache */
	en = ip_vs_lblc_get(svc->af, tbl, &iph->daddr);
	अगर (en) अणु
		/* We only hold a पढ़ो lock, but this is atomic */
		en->lastuse = jअगरfies;

		/*
		 * If the destination is not available, i.e. it's in the trash,
		 * we must ignore it, as it may be हटाओd from under our feet,
		 * अगर someone drops our reference count. Our caller only makes
		 * sure that destinations, that are not in the trash, are not
		 * moved to the trash, जबतक we are scheduling. But anyone can
		 * मुक्त up entries from the trash at any समय.
		 */

		dest = en->dest;
		अगर ((dest->flags & IP_VS_DEST_F_AVAILABLE) &&
		    atomic_पढ़ो(&dest->weight) > 0 && !is_overloaded(dest, svc))
			जाओ out;
	पूर्ण

	/* No cache entry or it is invalid, समय to schedule */
	dest = __ip_vs_lblc_schedule(svc);
	अगर (!dest) अणु
		ip_vs_scheduler_err(svc, "no destination available");
		वापस शून्य;
	पूर्ण

	/* If we fail to create a cache entry, we'll just use the valid dest */
	spin_lock_bh(&svc->sched_lock);
	अगर (!tbl->dead)
		ip_vs_lblc_new(tbl, &iph->daddr, svc->af, dest);
	spin_unlock_bh(&svc->sched_lock);

out:
	IP_VS_DBG_BUF(6, "LBLC: destination IP address %s --> server %s:%d\n",
		      IP_VS_DBG_ADDR(svc->af, &iph->daddr),
		      IP_VS_DBG_ADDR(dest->af, &dest->addr), ntohs(dest->port));

	वापस dest;
पूर्ण


/*
 *      IPVS LBLC Scheduler काष्ठाure
 */
अटल काष्ठा ip_vs_scheduler ip_vs_lblc_scheduler = अणु
	.name =			"lblc",
	.refcnt =		ATOMIC_INIT(0),
	.module =		THIS_MODULE,
	.n_list =		LIST_HEAD_INIT(ip_vs_lblc_scheduler.n_list),
	.init_service =		ip_vs_lblc_init_svc,
	.करोne_service =		ip_vs_lblc_करोne_svc,
	.schedule =		ip_vs_lblc_schedule,
पूर्ण;

/*
 *  per netns init.
 */
#अगर_घोषित CONFIG_SYSCTL
अटल पूर्णांक __net_init __ip_vs_lblc_init(काष्ठा net *net)
अणु
	काष्ठा netns_ipvs *ipvs = net_ipvs(net);

	अगर (!ipvs)
		वापस -ENOENT;

	अगर (!net_eq(net, &init_net)) अणु
		ipvs->lblc_ctl_table = kmemdup(vs_vars_table,
						माप(vs_vars_table),
						GFP_KERNEL);
		अगर (ipvs->lblc_ctl_table == शून्य)
			वापस -ENOMEM;

		/* Don't export sysctls to unprivileged users */
		अगर (net->user_ns != &init_user_ns)
			ipvs->lblc_ctl_table[0].procname = शून्य;

	पूर्ण अन्यथा
		ipvs->lblc_ctl_table = vs_vars_table;
	ipvs->sysctl_lblc_expiration = DEFAULT_EXPIRATION;
	ipvs->lblc_ctl_table[0].data = &ipvs->sysctl_lblc_expiration;

	ipvs->lblc_ctl_header =
		रेजिस्टर_net_sysctl(net, "net/ipv4/vs", ipvs->lblc_ctl_table);
	अगर (!ipvs->lblc_ctl_header) अणु
		अगर (!net_eq(net, &init_net))
			kमुक्त(ipvs->lblc_ctl_table);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __net_निकास __ip_vs_lblc_निकास(काष्ठा net *net)
अणु
	काष्ठा netns_ipvs *ipvs = net_ipvs(net);

	unरेजिस्टर_net_sysctl_table(ipvs->lblc_ctl_header);

	अगर (!net_eq(net, &init_net))
		kमुक्त(ipvs->lblc_ctl_table);
पूर्ण

#अन्यथा

अटल पूर्णांक __net_init __ip_vs_lblc_init(काष्ठा net *net) अणु वापस 0; पूर्ण
अटल व्योम __net_निकास __ip_vs_lblc_निकास(काष्ठा net *net) अणु पूर्ण

#पूर्ण_अगर

अटल काष्ठा pernet_operations ip_vs_lblc_ops = अणु
	.init = __ip_vs_lblc_init,
	.निकास = __ip_vs_lblc_निकास,
पूर्ण;

अटल पूर्णांक __init ip_vs_lblc_init(व्योम)
अणु
	पूर्णांक ret;

	ret = रेजिस्टर_pernet_subsys(&ip_vs_lblc_ops);
	अगर (ret)
		वापस ret;

	ret = रेजिस्टर_ip_vs_scheduler(&ip_vs_lblc_scheduler);
	अगर (ret)
		unरेजिस्टर_pernet_subsys(&ip_vs_lblc_ops);
	वापस ret;
पूर्ण

अटल व्योम __निकास ip_vs_lblc_cleanup(व्योम)
अणु
	unरेजिस्टर_ip_vs_scheduler(&ip_vs_lblc_scheduler);
	unरेजिस्टर_pernet_subsys(&ip_vs_lblc_ops);
	rcu_barrier();
पूर्ण


module_init(ip_vs_lblc_init);
module_निकास(ip_vs_lblc_cleanup);
MODULE_LICENSE("GPL");
