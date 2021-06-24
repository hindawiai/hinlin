<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * IPVS:        Locality-Based Least-Connection with Replication scheduler
 *
 * Authors:     Wensong Zhang <wensong@gnuchina.org>
 *
 * Changes:
 *     Julian Anastasov        :    Added the missing (dest->weight>0)
 *                                  condition in the ip_vs_dest_set_max.
 */

/*
 * The lblc/r algorithm is as follows (pseuकरो code):
 *
 *       अगर serverSet[dest_ip] is null then
 *               n, serverSet[dest_ip] <- अणुweighted least-conn nodeपूर्ण;
 *       अन्यथा
 *               n <- अणुleast-conn (alive) node in serverSet[dest_ip]पूर्ण;
 *               अगर (n is null) OR
 *                  (n.conns>n.weight AND
 *                   there is a node m with m.conns<m.weight/2) then
 *                   n <- अणुweighted least-conn nodeपूर्ण;
 *                   add n to serverSet[dest_ip];
 *               अगर |serverSet[dest_ip]| > 1 AND
 *                   now - serverSet[dest_ip].lastMod > T then
 *                   m <- अणुmost conn node in serverSet[dest_ip]पूर्ण;
 *                   हटाओ m from serverSet[dest_ip];
 *       अगर serverSet[dest_ip] changed then
 *               serverSet[dest_ip].lastMod <- now;
 *
 *       वापस n;
 *
 */

#घोषणा KMSG_COMPONENT "IPVS"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/ip.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/hash.h>

/* क्रम sysctl */
#समावेश <linux/fs.h>
#समावेश <linux/sysctl.h>
#समावेश <net/net_namespace.h>

#समावेश <net/ip_vs.h>


/*
 *    It is क्रम garbage collection of stale IPVS lblcr entries,
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
 *     क्रम IPVS lblcr entry hash table
 */
#अगर_अघोषित CONFIG_IP_VS_LBLCR_TAB_BITS
#घोषणा CONFIG_IP_VS_LBLCR_TAB_BITS      10
#पूर्ण_अगर
#घोषणा IP_VS_LBLCR_TAB_BITS     CONFIG_IP_VS_LBLCR_TAB_BITS
#घोषणा IP_VS_LBLCR_TAB_SIZE     (1 << IP_VS_LBLCR_TAB_BITS)
#घोषणा IP_VS_LBLCR_TAB_MASK     (IP_VS_LBLCR_TAB_SIZE - 1)


/*
 *      IPVS destination set काष्ठाure and operations
 */
काष्ठा ip_vs_dest_set_elem अणु
	काष्ठा list_head	list;          /* list link */
	काष्ठा ip_vs_dest	*dest;		/* destination server */
	काष्ठा rcu_head		rcu_head;
पूर्ण;

काष्ठा ip_vs_dest_set अणु
	atomic_t                size;           /* set size */
	अचिन्हित दीर्घ           lasपंचांगod;        /* last modअगरied समय */
	काष्ठा list_head	list;           /* destination list */
पूर्ण;


अटल व्योम ip_vs_dest_set_insert(काष्ठा ip_vs_dest_set *set,
				  काष्ठा ip_vs_dest *dest, bool check)
अणु
	काष्ठा ip_vs_dest_set_elem *e;

	अगर (check) अणु
		list_क्रम_each_entry(e, &set->list, list) अणु
			अगर (e->dest == dest)
				वापस;
		पूर्ण
	पूर्ण

	e = kदो_स्मृति(माप(*e), GFP_ATOMIC);
	अगर (e == शून्य)
		वापस;

	ip_vs_dest_hold(dest);
	e->dest = dest;

	list_add_rcu(&e->list, &set->list);
	atomic_inc(&set->size);

	set->lasपंचांगod = jअगरfies;
पूर्ण

अटल व्योम ip_vs_lblcr_elem_rcu_मुक्त(काष्ठा rcu_head *head)
अणु
	काष्ठा ip_vs_dest_set_elem *e;

	e = container_of(head, काष्ठा ip_vs_dest_set_elem, rcu_head);
	ip_vs_dest_put_and_मुक्त(e->dest);
	kमुक्त(e);
पूर्ण

अटल व्योम
ip_vs_dest_set_erase(काष्ठा ip_vs_dest_set *set, काष्ठा ip_vs_dest *dest)
अणु
	काष्ठा ip_vs_dest_set_elem *e;

	list_क्रम_each_entry(e, &set->list, list) अणु
		अगर (e->dest == dest) अणु
			/* HIT */
			atomic_dec(&set->size);
			set->lasपंचांगod = jअगरfies;
			list_del_rcu(&e->list);
			call_rcu(&e->rcu_head, ip_vs_lblcr_elem_rcu_मुक्त);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ip_vs_dest_set_eraseall(काष्ठा ip_vs_dest_set *set)
अणु
	काष्ठा ip_vs_dest_set_elem *e, *ep;

	list_क्रम_each_entry_safe(e, ep, &set->list, list) अणु
		list_del_rcu(&e->list);
		call_rcu(&e->rcu_head, ip_vs_lblcr_elem_rcu_मुक्त);
	पूर्ण
पूर्ण

/* get weighted least-connection node in the destination set */
अटल अंतरभूत काष्ठा ip_vs_dest *ip_vs_dest_set_min(काष्ठा ip_vs_dest_set *set)
अणु
	काष्ठा ip_vs_dest_set_elem *e;
	काष्ठा ip_vs_dest *dest, *least;
	पूर्णांक loh, करोh;

	/* select the first destination server, whose weight > 0 */
	list_क्रम_each_entry_rcu(e, &set->list, list) अणु
		least = e->dest;
		अगर (least->flags & IP_VS_DEST_F_OVERLOAD)
			जारी;

		अगर ((atomic_पढ़ो(&least->weight) > 0)
		    && (least->flags & IP_VS_DEST_F_AVAILABLE)) अणु
			loh = ip_vs_dest_conn_overhead(least);
			जाओ nextstage;
		पूर्ण
	पूर्ण
	वापस शून्य;

	/* find the destination with the weighted least load */
  nextstage:
	list_क्रम_each_entry_जारी_rcu(e, &set->list, list) अणु
		dest = e->dest;
		अगर (dest->flags & IP_VS_DEST_F_OVERLOAD)
			जारी;

		करोh = ip_vs_dest_conn_overhead(dest);
		अगर (((__s64)loh * atomic_पढ़ो(&dest->weight) >
		     (__s64)करोh * atomic_पढ़ो(&least->weight))
		    && (dest->flags & IP_VS_DEST_F_AVAILABLE)) अणु
			least = dest;
			loh = करोh;
		पूर्ण
	पूर्ण

	IP_VS_DBG_BUF(6, "%s(): server %s:%d "
		      "activeconns %d refcnt %d weight %d overhead %d\n",
		      __func__,
		      IP_VS_DBG_ADDR(least->af, &least->addr),
		      ntohs(least->port),
		      atomic_पढ़ो(&least->activeconns),
		      refcount_पढ़ो(&least->refcnt),
		      atomic_पढ़ो(&least->weight), loh);
	वापस least;
पूर्ण


/* get weighted most-connection node in the destination set */
अटल अंतरभूत काष्ठा ip_vs_dest *ip_vs_dest_set_max(काष्ठा ip_vs_dest_set *set)
अणु
	काष्ठा ip_vs_dest_set_elem *e;
	काष्ठा ip_vs_dest *dest, *most;
	पूर्णांक moh, करोh;

	अगर (set == शून्य)
		वापस शून्य;

	/* select the first destination server, whose weight > 0 */
	list_क्रम_each_entry(e, &set->list, list) अणु
		most = e->dest;
		अगर (atomic_पढ़ो(&most->weight) > 0) अणु
			moh = ip_vs_dest_conn_overhead(most);
			जाओ nextstage;
		पूर्ण
	पूर्ण
	वापस शून्य;

	/* find the destination with the weighted most load */
  nextstage:
	list_क्रम_each_entry_जारी(e, &set->list, list) अणु
		dest = e->dest;
		करोh = ip_vs_dest_conn_overhead(dest);
		/* moh/mw < करोh/dw ==> moh*dw < करोh*mw, where mw,dw>0 */
		अगर (((__s64)moh * atomic_पढ़ो(&dest->weight) <
		     (__s64)करोh * atomic_पढ़ो(&most->weight))
		    && (atomic_पढ़ो(&dest->weight) > 0)) अणु
			most = dest;
			moh = करोh;
		पूर्ण
	पूर्ण

	IP_VS_DBG_BUF(6, "%s(): server %s:%d "
		      "activeconns %d refcnt %d weight %d overhead %d\n",
		      __func__,
		      IP_VS_DBG_ADDR(most->af, &most->addr), ntohs(most->port),
		      atomic_पढ़ो(&most->activeconns),
		      refcount_पढ़ो(&most->refcnt),
		      atomic_पढ़ो(&most->weight), moh);
	वापस most;
पूर्ण


/*
 *      IPVS lblcr entry represents an association between destination
 *      IP address and its destination server set
 */
काष्ठा ip_vs_lblcr_entry अणु
	काष्ठा hlist_node       list;
	पूर्णांक			af;		/* address family */
	जोड़ nf_inet_addr      addr;           /* destination IP address */
	काष्ठा ip_vs_dest_set   set;            /* destination server set */
	अचिन्हित दीर्घ           lastuse;        /* last used समय */
	काष्ठा rcu_head		rcu_head;
पूर्ण;


/*
 *      IPVS lblcr hash table
 */
काष्ठा ip_vs_lblcr_table अणु
	काष्ठा rcu_head		rcu_head;
	काष्ठा hlist_head	bucket[IP_VS_LBLCR_TAB_SIZE];  /* hash bucket */
	atomic_t                entries;        /* number of entries */
	पूर्णांक                     max_size;       /* maximum size of entries */
	काष्ठा समयr_list       periodic_समयr; /* collect stale entries */
	काष्ठा ip_vs_service	*svc;		/* poपूर्णांकer back to service */
	पूर्णांक                     rover;          /* rover क्रम expire check */
	पूर्णांक                     counter;        /* counter क्रम no expire */
	bool			dead;
पूर्ण;


#अगर_घोषित CONFIG_SYSCTL
/*
 *      IPVS LBLCR sysctl table
 */

अटल काष्ठा ctl_table vs_vars_table[] = अणु
	अणु
		.procname	= "lblcr_expiration",
		.data		= शून्य,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
#पूर्ण_अगर

अटल अंतरभूत व्योम ip_vs_lblcr_मुक्त(काष्ठा ip_vs_lblcr_entry *en)
अणु
	hlist_del_rcu(&en->list);
	ip_vs_dest_set_eraseall(&en->set);
	kमुक्त_rcu(en, rcu_head);
पूर्ण


/*
 *	Returns hash value क्रम IPVS LBLCR entry
 */
अटल अंतरभूत अचिन्हित पूर्णांक
ip_vs_lblcr_hashkey(पूर्णांक af, स्थिर जोड़ nf_inet_addr *addr)
अणु
	__be32 addr_fold = addr->ip;

#अगर_घोषित CONFIG_IP_VS_IPV6
	अगर (af == AF_INET6)
		addr_fold = addr->ip6[0]^addr->ip6[1]^
			    addr->ip6[2]^addr->ip6[3];
#पूर्ण_अगर
	वापस hash_32(ntohl(addr_fold), IP_VS_LBLCR_TAB_BITS);
पूर्ण


/*
 *	Hash an entry in the ip_vs_lblcr_table.
 *	वापसs bool success.
 */
अटल व्योम
ip_vs_lblcr_hash(काष्ठा ip_vs_lblcr_table *tbl, काष्ठा ip_vs_lblcr_entry *en)
अणु
	अचिन्हित पूर्णांक hash = ip_vs_lblcr_hashkey(en->af, &en->addr);

	hlist_add_head_rcu(&en->list, &tbl->bucket[hash]);
	atomic_inc(&tbl->entries);
पूर्ण


/* Get ip_vs_lblcr_entry associated with supplied parameters. */
अटल अंतरभूत काष्ठा ip_vs_lblcr_entry *
ip_vs_lblcr_get(पूर्णांक af, काष्ठा ip_vs_lblcr_table *tbl,
		स्थिर जोड़ nf_inet_addr *addr)
अणु
	अचिन्हित पूर्णांक hash = ip_vs_lblcr_hashkey(af, addr);
	काष्ठा ip_vs_lblcr_entry *en;

	hlist_क्रम_each_entry_rcu(en, &tbl->bucket[hash], list)
		अगर (ip_vs_addr_equal(af, &en->addr, addr))
			वापस en;

	वापस शून्य;
पूर्ण


/*
 * Create or update an ip_vs_lblcr_entry, which is a mapping of a destination
 * IP address to a server. Called under spin lock.
 */
अटल अंतरभूत काष्ठा ip_vs_lblcr_entry *
ip_vs_lblcr_new(काष्ठा ip_vs_lblcr_table *tbl, स्थिर जोड़ nf_inet_addr *daddr,
		u16 af, काष्ठा ip_vs_dest *dest)
अणु
	काष्ठा ip_vs_lblcr_entry *en;

	en = ip_vs_lblcr_get(af, tbl, daddr);
	अगर (!en) अणु
		en = kदो_स्मृति(माप(*en), GFP_ATOMIC);
		अगर (!en)
			वापस शून्य;

		en->af = af;
		ip_vs_addr_copy(af, &en->addr, daddr);
		en->lastuse = jअगरfies;

		/* initialize its dest set */
		atomic_set(&(en->set.size), 0);
		INIT_LIST_HEAD(&en->set.list);

		ip_vs_dest_set_insert(&en->set, dest, false);

		ip_vs_lblcr_hash(tbl, en);
		वापस en;
	पूर्ण

	ip_vs_dest_set_insert(&en->set, dest, true);

	वापस en;
पूर्ण


/*
 *      Flush all the entries of the specअगरied table.
 */
अटल व्योम ip_vs_lblcr_flush(काष्ठा ip_vs_service *svc)
अणु
	काष्ठा ip_vs_lblcr_table *tbl = svc->sched_data;
	पूर्णांक i;
	काष्ठा ip_vs_lblcr_entry *en;
	काष्ठा hlist_node *next;

	spin_lock_bh(&svc->sched_lock);
	tbl->dead = true;
	क्रम (i = 0; i < IP_VS_LBLCR_TAB_SIZE; i++) अणु
		hlist_क्रम_each_entry_safe(en, next, &tbl->bucket[i], list) अणु
			ip_vs_lblcr_मुक्त(en);
		पूर्ण
	पूर्ण
	spin_unlock_bh(&svc->sched_lock);
पूर्ण

अटल पूर्णांक sysctl_lblcr_expiration(काष्ठा ip_vs_service *svc)
अणु
#अगर_घोषित CONFIG_SYSCTL
	वापस svc->ipvs->sysctl_lblcr_expiration;
#अन्यथा
	वापस DEFAULT_EXPIRATION;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम ip_vs_lblcr_full_check(काष्ठा ip_vs_service *svc)
अणु
	काष्ठा ip_vs_lblcr_table *tbl = svc->sched_data;
	अचिन्हित दीर्घ now = jअगरfies;
	पूर्णांक i, j;
	काष्ठा ip_vs_lblcr_entry *en;
	काष्ठा hlist_node *next;

	क्रम (i = 0, j = tbl->rover; i < IP_VS_LBLCR_TAB_SIZE; i++) अणु
		j = (j + 1) & IP_VS_LBLCR_TAB_MASK;

		spin_lock(&svc->sched_lock);
		hlist_क्रम_each_entry_safe(en, next, &tbl->bucket[j], list) अणु
			अगर (समय_after(en->lastuse +
				       sysctl_lblcr_expiration(svc), now))
				जारी;

			ip_vs_lblcr_मुक्त(en);
			atomic_dec(&tbl->entries);
		पूर्ण
		spin_unlock(&svc->sched_lock);
	पूर्ण
	tbl->rover = j;
पूर्ण


/*
 *      Periodical समयr handler क्रम IPVS lblcr table
 *      It is used to collect stale entries when the number of entries
 *      exceeds the maximum size of the table.
 *
 *      Fixme: we probably need more complicated algorithm to collect
 *             entries that have not been used क्रम a दीर्घ समय even
 *             अगर the number of entries करोesn't exceed the maximum size
 *             of the table.
 *      The full expiration check is क्रम this purpose now.
 */
अटल व्योम ip_vs_lblcr_check_expire(काष्ठा समयr_list *t)
अणु
	काष्ठा ip_vs_lblcr_table *tbl = from_समयr(tbl, t, periodic_समयr);
	काष्ठा ip_vs_service *svc = tbl->svc;
	अचिन्हित दीर्घ now = jअगरfies;
	पूर्णांक goal;
	पूर्णांक i, j;
	काष्ठा ip_vs_lblcr_entry *en;
	काष्ठा hlist_node *next;

	अगर ((tbl->counter % COUNT_FOR_FULL_EXPIRATION) == 0) अणु
		/* करो full expiration check */
		ip_vs_lblcr_full_check(svc);
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

	क्रम (i = 0, j = tbl->rover; i < IP_VS_LBLCR_TAB_SIZE; i++) अणु
		j = (j + 1) & IP_VS_LBLCR_TAB_MASK;

		spin_lock(&svc->sched_lock);
		hlist_क्रम_each_entry_safe(en, next, &tbl->bucket[j], list) अणु
			अगर (समय_beक्रमe(now, en->lastuse+ENTRY_TIMEOUT))
				जारी;

			ip_vs_lblcr_मुक्त(en);
			atomic_dec(&tbl->entries);
			goal--;
		पूर्ण
		spin_unlock(&svc->sched_lock);
		अगर (goal <= 0)
			अवरोध;
	पूर्ण
	tbl->rover = j;

  out:
	mod_समयr(&tbl->periodic_समयr, jअगरfies+CHECK_EXPIRE_INTERVAL);
पूर्ण

अटल पूर्णांक ip_vs_lblcr_init_svc(काष्ठा ip_vs_service *svc)
अणु
	पूर्णांक i;
	काष्ठा ip_vs_lblcr_table *tbl;

	/*
	 *    Allocate the ip_vs_lblcr_table क्रम this service
	 */
	tbl = kदो_स्मृति(माप(*tbl), GFP_KERNEL);
	अगर (tbl == शून्य)
		वापस -ENOMEM;

	svc->sched_data = tbl;
	IP_VS_DBG(6, "LBLCR hash table (memory=%zdbytes) allocated for "
		  "current service\n", माप(*tbl));

	/*
	 *    Initialize the hash buckets
	 */
	क्रम (i = 0; i < IP_VS_LBLCR_TAB_SIZE; i++) अणु
		INIT_HLIST_HEAD(&tbl->bucket[i]);
	पूर्ण
	tbl->max_size = IP_VS_LBLCR_TAB_SIZE*16;
	tbl->rover = 0;
	tbl->counter = 1;
	tbl->dead = false;
	tbl->svc = svc;
	atomic_set(&tbl->entries, 0);

	/*
	 *    Hook periodic समयr क्रम garbage collection
	 */
	समयr_setup(&tbl->periodic_समयr, ip_vs_lblcr_check_expire, 0);
	mod_समयr(&tbl->periodic_समयr, jअगरfies + CHECK_EXPIRE_INTERVAL);

	वापस 0;
पूर्ण


अटल व्योम ip_vs_lblcr_करोne_svc(काष्ठा ip_vs_service *svc)
अणु
	काष्ठा ip_vs_lblcr_table *tbl = svc->sched_data;

	/* हटाओ periodic समयr */
	del_समयr_sync(&tbl->periodic_समयr);

	/* got to clean up table entries here */
	ip_vs_lblcr_flush(svc);

	/* release the table itself */
	kमुक्त_rcu(tbl, rcu_head);
	IP_VS_DBG(6, "LBLCR hash table (memory=%zdbytes) released\n",
		  माप(*tbl));
पूर्ण


अटल अंतरभूत काष्ठा ip_vs_dest *
__ip_vs_lblcr_schedule(काष्ठा ip_vs_service *svc)
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

	IP_VS_DBG_BUF(6, "LBLCR: server %s:%d "
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
ip_vs_lblcr_schedule(काष्ठा ip_vs_service *svc, स्थिर काष्ठा sk_buff *skb,
		     काष्ठा ip_vs_iphdr *iph)
अणु
	काष्ठा ip_vs_lblcr_table *tbl = svc->sched_data;
	काष्ठा ip_vs_dest *dest;
	काष्ठा ip_vs_lblcr_entry *en;

	IP_VS_DBG(6, "%s(): Scheduling...\n", __func__);

	/* First look in our cache */
	en = ip_vs_lblcr_get(svc->af, tbl, &iph->daddr);
	अगर (en) अणु
		en->lastuse = jअगरfies;

		/* Get the least loaded destination */
		dest = ip_vs_dest_set_min(&en->set);

		/* More than one destination + enough समय passed by, cleanup */
		अगर (atomic_पढ़ो(&en->set.size) > 1 &&
		    समय_after(jअगरfies, en->set.lasपंचांगod +
				sysctl_lblcr_expiration(svc))) अणु
			spin_lock_bh(&svc->sched_lock);
			अगर (atomic_पढ़ो(&en->set.size) > 1) अणु
				काष्ठा ip_vs_dest *m;

				m = ip_vs_dest_set_max(&en->set);
				अगर (m)
					ip_vs_dest_set_erase(&en->set, m);
			पूर्ण
			spin_unlock_bh(&svc->sched_lock);
		पूर्ण

		/* If the destination is not overloaded, use it */
		अगर (dest && !is_overloaded(dest, svc))
			जाओ out;

		/* The cache entry is invalid, समय to schedule */
		dest = __ip_vs_lblcr_schedule(svc);
		अगर (!dest) अणु
			ip_vs_scheduler_err(svc, "no destination available");
			वापस शून्य;
		पूर्ण

		/* Update our cache entry */
		spin_lock_bh(&svc->sched_lock);
		अगर (!tbl->dead)
			ip_vs_dest_set_insert(&en->set, dest, true);
		spin_unlock_bh(&svc->sched_lock);
		जाओ out;
	पूर्ण

	/* No cache entry, समय to schedule */
	dest = __ip_vs_lblcr_schedule(svc);
	अगर (!dest) अणु
		IP_VS_DBG(1, "no destination available\n");
		वापस शून्य;
	पूर्ण

	/* If we fail to create a cache entry, we'll just use the valid dest */
	spin_lock_bh(&svc->sched_lock);
	अगर (!tbl->dead)
		ip_vs_lblcr_new(tbl, &iph->daddr, svc->af, dest);
	spin_unlock_bh(&svc->sched_lock);

out:
	IP_VS_DBG_BUF(6, "LBLCR: destination IP address %s --> server %s:%d\n",
		      IP_VS_DBG_ADDR(svc->af, &iph->daddr),
		      IP_VS_DBG_ADDR(dest->af, &dest->addr), ntohs(dest->port));

	वापस dest;
पूर्ण


/*
 *      IPVS LBLCR Scheduler काष्ठाure
 */
अटल काष्ठा ip_vs_scheduler ip_vs_lblcr_scheduler =
अणु
	.name =			"lblcr",
	.refcnt =		ATOMIC_INIT(0),
	.module =		THIS_MODULE,
	.n_list =		LIST_HEAD_INIT(ip_vs_lblcr_scheduler.n_list),
	.init_service =		ip_vs_lblcr_init_svc,
	.करोne_service =		ip_vs_lblcr_करोne_svc,
	.schedule =		ip_vs_lblcr_schedule,
पूर्ण;

/*
 *  per netns init.
 */
#अगर_घोषित CONFIG_SYSCTL
अटल पूर्णांक __net_init __ip_vs_lblcr_init(काष्ठा net *net)
अणु
	काष्ठा netns_ipvs *ipvs = net_ipvs(net);

	अगर (!ipvs)
		वापस -ENOENT;

	अगर (!net_eq(net, &init_net)) अणु
		ipvs->lblcr_ctl_table = kmemdup(vs_vars_table,
						माप(vs_vars_table),
						GFP_KERNEL);
		अगर (ipvs->lblcr_ctl_table == शून्य)
			वापस -ENOMEM;

		/* Don't export sysctls to unprivileged users */
		अगर (net->user_ns != &init_user_ns)
			ipvs->lblcr_ctl_table[0].procname = शून्य;
	पूर्ण अन्यथा
		ipvs->lblcr_ctl_table = vs_vars_table;
	ipvs->sysctl_lblcr_expiration = DEFAULT_EXPIRATION;
	ipvs->lblcr_ctl_table[0].data = &ipvs->sysctl_lblcr_expiration;

	ipvs->lblcr_ctl_header =
		रेजिस्टर_net_sysctl(net, "net/ipv4/vs", ipvs->lblcr_ctl_table);
	अगर (!ipvs->lblcr_ctl_header) अणु
		अगर (!net_eq(net, &init_net))
			kमुक्त(ipvs->lblcr_ctl_table);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __net_निकास __ip_vs_lblcr_निकास(काष्ठा net *net)
अणु
	काष्ठा netns_ipvs *ipvs = net_ipvs(net);

	unरेजिस्टर_net_sysctl_table(ipvs->lblcr_ctl_header);

	अगर (!net_eq(net, &init_net))
		kमुक्त(ipvs->lblcr_ctl_table);
पूर्ण

#अन्यथा

अटल पूर्णांक __net_init __ip_vs_lblcr_init(काष्ठा net *net) अणु वापस 0; पूर्ण
अटल व्योम __net_निकास __ip_vs_lblcr_निकास(काष्ठा net *net) अणु पूर्ण

#पूर्ण_अगर

अटल काष्ठा pernet_operations ip_vs_lblcr_ops = अणु
	.init = __ip_vs_lblcr_init,
	.निकास = __ip_vs_lblcr_निकास,
पूर्ण;

अटल पूर्णांक __init ip_vs_lblcr_init(व्योम)
अणु
	पूर्णांक ret;

	ret = रेजिस्टर_pernet_subsys(&ip_vs_lblcr_ops);
	अगर (ret)
		वापस ret;

	ret = रेजिस्टर_ip_vs_scheduler(&ip_vs_lblcr_scheduler);
	अगर (ret)
		unरेजिस्टर_pernet_subsys(&ip_vs_lblcr_ops);
	वापस ret;
पूर्ण

अटल व्योम __निकास ip_vs_lblcr_cleanup(व्योम)
अणु
	unरेजिस्टर_ip_vs_scheduler(&ip_vs_lblcr_scheduler);
	unरेजिस्टर_pernet_subsys(&ip_vs_lblcr_ops);
	rcu_barrier();
पूर्ण


module_init(ip_vs_lblcr_init);
module_निकास(ip_vs_lblcr_cleanup);
MODULE_LICENSE("GPL");
