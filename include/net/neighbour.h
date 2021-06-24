<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NET_NEIGHBOUR_H
#घोषणा _NET_NEIGHBOUR_H

#समावेश <linux/neighbour.h>

/*
 *	Generic neighbour manipulation
 *
 *	Authors:
 *	Pedro Roque		<roque@di.fc.ul.pt>
 *	Alexey Kuznetsov	<kuznet@ms2.inr.ac.ru>
 *
 * 	Changes:
 *
 *	Harald Welte:		<laक्रमge@gnumonks.org>
 *		- Add neighbour cache statistics like rtstat
 */

#समावेश <linux/atomic.h>
#समावेश <linux/refcount.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/biपंचांगap.h>

#समावेश <linux/err.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/workqueue.h>
#समावेश <net/rtnetlink.h>

/*
 * NUD stands क्रम "neighbor unreachability detection"
 */

#घोषणा NUD_IN_TIMER	(NUD_INCOMPLETE|NUD_REACHABLE|NUD_DELAY|NUD_PROBE)
#घोषणा NUD_VALID	(NUD_PERMANENT|NUD_NOARP|NUD_REACHABLE|NUD_PROBE|NUD_STALE|NUD_DELAY)
#घोषणा NUD_CONNECTED	(NUD_PERMANENT|NUD_NOARP|NUD_REACHABLE)

काष्ठा neighbour;

क्रमागत अणु
	NEIGH_VAR_MCAST_PROBES,
	NEIGH_VAR_UCAST_PROBES,
	NEIGH_VAR_APP_PROBES,
	NEIGH_VAR_MCAST_REPROBES,
	NEIGH_VAR_RETRANS_TIME,
	NEIGH_VAR_BASE_REACHABLE_TIME,
	NEIGH_VAR_DELAY_PROBE_TIME,
	NEIGH_VAR_GC_STALETIME,
	NEIGH_VAR_QUEUE_LEN_BYTES,
	NEIGH_VAR_PROXY_QLEN,
	NEIGH_VAR_ANYCAST_DELAY,
	NEIGH_VAR_PROXY_DELAY,
	NEIGH_VAR_LOCKTIME,
#घोषणा NEIGH_VAR_DATA_MAX (NEIGH_VAR_LOCKTIME + 1)
	/* Following are used as a second way to access one of the above */
	NEIGH_VAR_QUEUE_LEN, /* same data as NEIGH_VAR_QUEUE_LEN_BYTES */
	NEIGH_VAR_RETRANS_TIME_MS, /* same data as NEIGH_VAR_RETRANS_TIME */
	NEIGH_VAR_BASE_REACHABLE_TIME_MS, /* same data as NEIGH_VAR_BASE_REACHABLE_TIME */
	/* Following are used by "default" only */
	NEIGH_VAR_GC_INTERVAL,
	NEIGH_VAR_GC_THRESH1,
	NEIGH_VAR_GC_THRESH2,
	NEIGH_VAR_GC_THRESH3,
	NEIGH_VAR_MAX
पूर्ण;

काष्ठा neigh_parms अणु
	possible_net_t net;
	काष्ठा net_device *dev;
	काष्ठा list_head list;
	पूर्णांक	(*neigh_setup)(काष्ठा neighbour *);
	काष्ठा neigh_table *tbl;

	व्योम	*sysctl_table;

	पूर्णांक dead;
	refcount_t refcnt;
	काष्ठा rcu_head rcu_head;

	पूर्णांक	reachable_समय;
	पूर्णांक	data[NEIGH_VAR_DATA_MAX];
	DECLARE_BITMAP(data_state, NEIGH_VAR_DATA_MAX);
पूर्ण;

अटल अंतरभूत व्योम neigh_var_set(काष्ठा neigh_parms *p, पूर्णांक index, पूर्णांक val)
अणु
	set_bit(index, p->data_state);
	p->data[index] = val;
पूर्ण

#घोषणा NEIGH_VAR(p, attr) ((p)->data[NEIGH_VAR_ ## attr])

/* In nकरो_neigh_setup, NEIGH_VAR_INIT should be used.
 * In other हालs, NEIGH_VAR_SET should be used.
 */
#घोषणा NEIGH_VAR_INIT(p, attr, val) (NEIGH_VAR(p, attr) = val)
#घोषणा NEIGH_VAR_SET(p, attr, val) neigh_var_set(p, NEIGH_VAR_ ## attr, val)

अटल अंतरभूत व्योम neigh_parms_data_state_setall(काष्ठा neigh_parms *p)
अणु
	biपंचांगap_fill(p->data_state, NEIGH_VAR_DATA_MAX);
पूर्ण

अटल अंतरभूत व्योम neigh_parms_data_state_cleanall(काष्ठा neigh_parms *p)
अणु
	biपंचांगap_zero(p->data_state, NEIGH_VAR_DATA_MAX);
पूर्ण

काष्ठा neigh_statistics अणु
	अचिन्हित दीर्घ allocs;		/* number of allocated neighs */
	अचिन्हित दीर्घ destroys;		/* number of destroyed neighs */
	अचिन्हित दीर्घ hash_grows;	/* number of hash resizes */

	अचिन्हित दीर्घ res_failed;	/* number of failed resolutions */

	अचिन्हित दीर्घ lookups;		/* number of lookups */
	अचिन्हित दीर्घ hits;		/* number of hits (among lookups) */

	अचिन्हित दीर्घ rcv_probes_mcast;	/* number of received mcast ipv6 */
	अचिन्हित दीर्घ rcv_probes_ucast; /* number of received ucast ipv6 */

	अचिन्हित दीर्घ periodic_gc_runs;	/* number of periodic GC runs */
	अचिन्हित दीर्घ क्रमced_gc_runs;	/* number of क्रमced GC runs */

	अचिन्हित दीर्घ unres_discards;	/* number of unresolved drops */
	अचिन्हित दीर्घ table_fulls;      /* बार even gc couldn't help */
पूर्ण;

#घोषणा NEIGH_CACHE_STAT_INC(tbl, field) this_cpu_inc((tbl)->stats->field)

काष्ठा neighbour अणु
	काष्ठा neighbour __rcu	*next;
	काष्ठा neigh_table	*tbl;
	काष्ठा neigh_parms	*parms;
	अचिन्हित दीर्घ		confirmed;
	अचिन्हित दीर्घ		updated;
	rwlock_t		lock;
	refcount_t		refcnt;
	अचिन्हित पूर्णांक		arp_queue_len_bytes;
	काष्ठा sk_buff_head	arp_queue;
	काष्ठा समयr_list	समयr;
	अचिन्हित दीर्घ		used;
	atomic_t		probes;
	__u8			flags;
	__u8			nud_state;
	__u8			type;
	__u8			dead;
	u8			protocol;
	seqlock_t		ha_lock;
	अचिन्हित अक्षर		ha[ALIGN(MAX_ADDR_LEN, माप(अचिन्हित दीर्घ))] __aligned(8);
	काष्ठा hh_cache		hh;
	पूर्णांक			(*output)(काष्ठा neighbour *, काष्ठा sk_buff *);
	स्थिर काष्ठा neigh_ops	*ops;
	काष्ठा list_head	gc_list;
	काष्ठा rcu_head		rcu;
	काष्ठा net_device	*dev;
	u8			primary_key[0];
पूर्ण __अक्रमomize_layout;

काष्ठा neigh_ops अणु
	पूर्णांक			family;
	व्योम			(*solicit)(काष्ठा neighbour *, काष्ठा sk_buff *);
	व्योम			(*error_report)(काष्ठा neighbour *, काष्ठा sk_buff *);
	पूर्णांक			(*output)(काष्ठा neighbour *, काष्ठा sk_buff *);
	पूर्णांक			(*connected_output)(काष्ठा neighbour *, काष्ठा sk_buff *);
पूर्ण;

काष्ठा pneigh_entry अणु
	काष्ठा pneigh_entry	*next;
	possible_net_t		net;
	काष्ठा net_device	*dev;
	u8			flags;
	u8			protocol;
	u8			key[];
पूर्ण;

/*
 *	neighbour table manipulation
 */

#घोषणा NEIGH_NUM_HASH_RND	4

काष्ठा neigh_hash_table अणु
	काष्ठा neighbour __rcu	**hash_buckets;
	अचिन्हित पूर्णांक		hash_shअगरt;
	__u32			hash_rnd[NEIGH_NUM_HASH_RND];
	काष्ठा rcu_head		rcu;
पूर्ण;


काष्ठा neigh_table अणु
	पूर्णांक			family;
	अचिन्हित पूर्णांक		entry_size;
	अचिन्हित पूर्णांक		key_len;
	__be16			protocol;
	__u32			(*hash)(स्थिर व्योम *pkey,
					स्थिर काष्ठा net_device *dev,
					__u32 *hash_rnd);
	bool			(*key_eq)(स्थिर काष्ठा neighbour *, स्थिर व्योम *pkey);
	पूर्णांक			(*स्थिरructor)(काष्ठा neighbour *);
	पूर्णांक			(*pस्थिरructor)(काष्ठा pneigh_entry *);
	व्योम			(*pdeकाष्ठाor)(काष्ठा pneigh_entry *);
	व्योम			(*proxy_reकरो)(काष्ठा sk_buff *skb);
	पूर्णांक			(*is_multicast)(स्थिर व्योम *pkey);
	bool			(*allow_add)(स्थिर काष्ठा net_device *dev,
					     काष्ठा netlink_ext_ack *extack);
	अक्षर			*id;
	काष्ठा neigh_parms	parms;
	काष्ठा list_head	parms_list;
	पूर्णांक			gc_पूर्णांकerval;
	पूर्णांक			gc_thresh1;
	पूर्णांक			gc_thresh2;
	पूर्णांक			gc_thresh3;
	अचिन्हित दीर्घ		last_flush;
	काष्ठा delayed_work	gc_work;
	काष्ठा समयr_list 	proxy_समयr;
	काष्ठा sk_buff_head	proxy_queue;
	atomic_t		entries;
	atomic_t		gc_entries;
	काष्ठा list_head	gc_list;
	rwlock_t		lock;
	अचिन्हित दीर्घ		last_अक्रम;
	काष्ठा neigh_statistics	__percpu *stats;
	काष्ठा neigh_hash_table __rcu *nht;
	काष्ठा pneigh_entry	**phash_buckets;
पूर्ण;

क्रमागत अणु
	NEIGH_ARP_TABLE = 0,
	NEIGH_ND_TABLE = 1,
	NEIGH_DN_TABLE = 2,
	NEIGH_NR_TABLES,
	NEIGH_LINK_TABLE = NEIGH_NR_TABLES /* Pseuकरो table क्रम neigh_xmit */
पूर्ण;

अटल अंतरभूत पूर्णांक neigh_parms_family(काष्ठा neigh_parms *p)
अणु
	वापस p->tbl->family;
पूर्ण

#घोषणा NEIGH_PRIV_ALIGN	माप(दीर्घ दीर्घ)
#घोषणा NEIGH_ENTRY_SIZE(size)	ALIGN((size), NEIGH_PRIV_ALIGN)

अटल अंतरभूत व्योम *neighbour_priv(स्थिर काष्ठा neighbour *n)
अणु
	वापस (अक्षर *)n + n->tbl->entry_size;
पूर्ण

/* flags क्रम neigh_update() */
#घोषणा NEIGH_UPDATE_F_OVERRIDE			0x00000001
#घोषणा NEIGH_UPDATE_F_WEAK_OVERRIDE		0x00000002
#घोषणा NEIGH_UPDATE_F_OVERRIDE_ISROUTER	0x00000004
#घोषणा NEIGH_UPDATE_F_EXT_LEARNED		0x20000000
#घोषणा NEIGH_UPDATE_F_ISROUTER			0x40000000
#घोषणा NEIGH_UPDATE_F_ADMIN			0x80000000

बाह्य स्थिर काष्ठा nla_policy nda_policy[];

अटल अंतरभूत bool neigh_key_eq16(स्थिर काष्ठा neighbour *n, स्थिर व्योम *pkey)
अणु
	वापस *(स्थिर u16 *)n->primary_key == *(स्थिर u16 *)pkey;
पूर्ण

अटल अंतरभूत bool neigh_key_eq32(स्थिर काष्ठा neighbour *n, स्थिर व्योम *pkey)
अणु
	वापस *(स्थिर u32 *)n->primary_key == *(स्थिर u32 *)pkey;
पूर्ण

अटल अंतरभूत bool neigh_key_eq128(स्थिर काष्ठा neighbour *n, स्थिर व्योम *pkey)
अणु
	स्थिर u32 *n32 = (स्थिर u32 *)n->primary_key;
	स्थिर u32 *p32 = pkey;

	वापस ((n32[0] ^ p32[0]) | (n32[1] ^ p32[1]) |
		(n32[2] ^ p32[2]) | (n32[3] ^ p32[3])) == 0;
पूर्ण

अटल अंतरभूत काष्ठा neighbour *___neigh_lookup_noref(
	काष्ठा neigh_table *tbl,
	bool (*key_eq)(स्थिर काष्ठा neighbour *n, स्थिर व्योम *pkey),
	__u32 (*hash)(स्थिर व्योम *pkey,
		      स्थिर काष्ठा net_device *dev,
		      __u32 *hash_rnd),
	स्थिर व्योम *pkey,
	काष्ठा net_device *dev)
अणु
	काष्ठा neigh_hash_table *nht = rcu_dereference_bh(tbl->nht);
	काष्ठा neighbour *n;
	u32 hash_val;

	hash_val = hash(pkey, dev, nht->hash_rnd) >> (32 - nht->hash_shअगरt);
	क्रम (n = rcu_dereference_bh(nht->hash_buckets[hash_val]);
	     n != शून्य;
	     n = rcu_dereference_bh(n->next)) अणु
		अगर (n->dev == dev && key_eq(n, pkey))
			वापस n;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा neighbour *__neigh_lookup_noref(काष्ठा neigh_table *tbl,
						     स्थिर व्योम *pkey,
						     काष्ठा net_device *dev)
अणु
	वापस ___neigh_lookup_noref(tbl, tbl->key_eq, tbl->hash, pkey, dev);
पूर्ण

व्योम neigh_table_init(पूर्णांक index, काष्ठा neigh_table *tbl);
पूर्णांक neigh_table_clear(पूर्णांक index, काष्ठा neigh_table *tbl);
काष्ठा neighbour *neigh_lookup(काष्ठा neigh_table *tbl, स्थिर व्योम *pkey,
			       काष्ठा net_device *dev);
काष्ठा neighbour *neigh_lookup_nodev(काष्ठा neigh_table *tbl, काष्ठा net *net,
				     स्थिर व्योम *pkey);
काष्ठा neighbour *__neigh_create(काष्ठा neigh_table *tbl, स्थिर व्योम *pkey,
				 काष्ठा net_device *dev, bool want_ref);
अटल अंतरभूत काष्ठा neighbour *neigh_create(काष्ठा neigh_table *tbl,
					     स्थिर व्योम *pkey,
					     काष्ठा net_device *dev)
अणु
	वापस __neigh_create(tbl, pkey, dev, true);
पूर्ण
व्योम neigh_destroy(काष्ठा neighbour *neigh);
पूर्णांक __neigh_event_send(काष्ठा neighbour *neigh, काष्ठा sk_buff *skb);
पूर्णांक neigh_update(काष्ठा neighbour *neigh, स्थिर u8 *lladdr, u8 new, u32 flags,
		 u32 nlmsg_pid);
व्योम __neigh_set_probe_once(काष्ठा neighbour *neigh);
bool neigh_हटाओ_one(काष्ठा neighbour *ndel, काष्ठा neigh_table *tbl);
व्योम neigh_changeaddr(काष्ठा neigh_table *tbl, काष्ठा net_device *dev);
पूर्णांक neigh_अगरकरोwn(काष्ठा neigh_table *tbl, काष्ठा net_device *dev);
पूर्णांक neigh_carrier_करोwn(काष्ठा neigh_table *tbl, काष्ठा net_device *dev);
पूर्णांक neigh_resolve_output(काष्ठा neighbour *neigh, काष्ठा sk_buff *skb);
पूर्णांक neigh_connected_output(काष्ठा neighbour *neigh, काष्ठा sk_buff *skb);
पूर्णांक neigh_direct_output(काष्ठा neighbour *neigh, काष्ठा sk_buff *skb);
काष्ठा neighbour *neigh_event_ns(काष्ठा neigh_table *tbl,
						u8 *lladdr, व्योम *saddr,
						काष्ठा net_device *dev);

काष्ठा neigh_parms *neigh_parms_alloc(काष्ठा net_device *dev,
				      काष्ठा neigh_table *tbl);
व्योम neigh_parms_release(काष्ठा neigh_table *tbl, काष्ठा neigh_parms *parms);

अटल अंतरभूत
काष्ठा net *neigh_parms_net(स्थिर काष्ठा neigh_parms *parms)
अणु
	वापस पढ़ो_pnet(&parms->net);
पूर्ण

अचिन्हित दीर्घ neigh_अक्रम_reach_समय(अचिन्हित दीर्घ base);

व्योम pneigh_enqueue(काष्ठा neigh_table *tbl, काष्ठा neigh_parms *p,
		    काष्ठा sk_buff *skb);
काष्ठा pneigh_entry *pneigh_lookup(काष्ठा neigh_table *tbl, काष्ठा net *net,
				   स्थिर व्योम *key, काष्ठा net_device *dev,
				   पूर्णांक creat);
काष्ठा pneigh_entry *__pneigh_lookup(काष्ठा neigh_table *tbl, काष्ठा net *net,
				     स्थिर व्योम *key, काष्ठा net_device *dev);
पूर्णांक pneigh_delete(काष्ठा neigh_table *tbl, काष्ठा net *net, स्थिर व्योम *key,
		  काष्ठा net_device *dev);

अटल अंतरभूत काष्ठा net *pneigh_net(स्थिर काष्ठा pneigh_entry *pneigh)
अणु
	वापस पढ़ो_pnet(&pneigh->net);
पूर्ण

व्योम neigh_app_ns(काष्ठा neighbour *n);
व्योम neigh_क्रम_each(काष्ठा neigh_table *tbl,
		    व्योम (*cb)(काष्ठा neighbour *, व्योम *), व्योम *cookie);
व्योम __neigh_क्रम_each_release(काष्ठा neigh_table *tbl,
			      पूर्णांक (*cb)(काष्ठा neighbour *));
पूर्णांक neigh_xmit(पूर्णांक fam, काष्ठा net_device *, स्थिर व्योम *, काष्ठा sk_buff *);
व्योम pneigh_क्रम_each(काष्ठा neigh_table *tbl,
		     व्योम (*cb)(काष्ठा pneigh_entry *));

काष्ठा neigh_seq_state अणु
	काष्ठा seq_net_निजी p;
	काष्ठा neigh_table *tbl;
	काष्ठा neigh_hash_table *nht;
	व्योम *(*neigh_sub_iter)(काष्ठा neigh_seq_state *state,
				काष्ठा neighbour *n, loff_t *pos);
	अचिन्हित पूर्णांक bucket;
	अचिन्हित पूर्णांक flags;
#घोषणा NEIGH_SEQ_NEIGH_ONLY	0x00000001
#घोषणा NEIGH_SEQ_IS_PNEIGH	0x00000002
#घोषणा NEIGH_SEQ_SKIP_NOARP	0x00000004
पूर्ण;
व्योम *neigh_seq_start(काष्ठा seq_file *, loff_t *, काष्ठा neigh_table *,
		      अचिन्हित पूर्णांक);
व्योम *neigh_seq_next(काष्ठा seq_file *, व्योम *, loff_t *);
व्योम neigh_seq_stop(काष्ठा seq_file *, व्योम *);

पूर्णांक neigh_proc_करोपूर्णांकvec(काष्ठा ctl_table *ctl, पूर्णांक ग_लिखो,
			व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos);
पूर्णांक neigh_proc_करोपूर्णांकvec_jअगरfies(काष्ठा ctl_table *ctl, पूर्णांक ग_लिखो,
				व्योम *buffer,
				माप_प्रकार *lenp, loff_t *ppos);
पूर्णांक neigh_proc_करोपूर्णांकvec_ms_jअगरfies(काष्ठा ctl_table *ctl, पूर्णांक ग_लिखो,
				   व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos);

पूर्णांक neigh_sysctl_रेजिस्टर(काष्ठा net_device *dev, काष्ठा neigh_parms *p,
			  proc_handler *proc_handler);
व्योम neigh_sysctl_unरेजिस्टर(काष्ठा neigh_parms *p);

अटल अंतरभूत व्योम __neigh_parms_put(काष्ठा neigh_parms *parms)
अणु
	refcount_dec(&parms->refcnt);
पूर्ण

अटल अंतरभूत काष्ठा neigh_parms *neigh_parms_clone(काष्ठा neigh_parms *parms)
अणु
	refcount_inc(&parms->refcnt);
	वापस parms;
पूर्ण

/*
 *	Neighbour references
 */

अटल अंतरभूत व्योम neigh_release(काष्ठा neighbour *neigh)
अणु
	अगर (refcount_dec_and_test(&neigh->refcnt))
		neigh_destroy(neigh);
पूर्ण

अटल अंतरभूत काष्ठा neighbour * neigh_clone(काष्ठा neighbour *neigh)
अणु
	अगर (neigh)
		refcount_inc(&neigh->refcnt);
	वापस neigh;
पूर्ण

#घोषणा neigh_hold(n)	refcount_inc(&(n)->refcnt)

अटल अंतरभूत पूर्णांक neigh_event_send(काष्ठा neighbour *neigh, काष्ठा sk_buff *skb)
अणु
	अचिन्हित दीर्घ now = jअगरfies;
	
	अगर (READ_ONCE(neigh->used) != now)
		WRITE_ONCE(neigh->used, now);
	अगर (!(neigh->nud_state&(NUD_CONNECTED|NUD_DELAY|NUD_PROBE)))
		वापस __neigh_event_send(neigh, skb);
	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_BRIDGE_NETFILTER)
अटल अंतरभूत पूर्णांक neigh_hh_bridge(काष्ठा hh_cache *hh, काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक seq, hh_alen;

	करो अणु
		seq = पढ़ो_seqbegin(&hh->hh_lock);
		hh_alen = HH_DATA_ALIGN(ETH_HLEN);
		स_नकल(skb->data - hh_alen, hh->hh_data, ETH_ALEN + hh_alen - ETH_HLEN);
	पूर्ण जबतक (पढ़ो_seqretry(&hh->hh_lock, seq));
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक neigh_hh_output(स्थिर काष्ठा hh_cache *hh, काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक hh_alen = 0;
	अचिन्हित पूर्णांक seq;
	अचिन्हित पूर्णांक hh_len;

	करो अणु
		seq = पढ़ो_seqbegin(&hh->hh_lock);
		hh_len = READ_ONCE(hh->hh_len);
		अगर (likely(hh_len <= HH_DATA_MOD)) अणु
			hh_alen = HH_DATA_MOD;

			/* skb_push() would proceed silently अगर we have room क्रम
			 * the unaligned size but not क्रम the aligned size:
			 * check headroom explicitly.
			 */
			अगर (likely(skb_headroom(skb) >= HH_DATA_MOD)) अणु
				/* this is अंतरभूतd by gcc */
				स_नकल(skb->data - HH_DATA_MOD, hh->hh_data,
				       HH_DATA_MOD);
			पूर्ण
		पूर्ण अन्यथा अणु
			hh_alen = HH_DATA_ALIGN(hh_len);

			अगर (likely(skb_headroom(skb) >= hh_alen)) अणु
				स_नकल(skb->data - hh_alen, hh->hh_data,
				       hh_alen);
			पूर्ण
		पूर्ण
	पूर्ण जबतक (पढ़ो_seqretry(&hh->hh_lock, seq));

	अगर (WARN_ON_ONCE(skb_headroom(skb) < hh_alen)) अणु
		kमुक्त_skb(skb);
		वापस NET_XMIT_DROP;
	पूर्ण

	__skb_push(skb, hh_len);
	वापस dev_queue_xmit(skb);
पूर्ण

अटल अंतरभूत पूर्णांक neigh_output(काष्ठा neighbour *n, काष्ठा sk_buff *skb,
			       bool skip_cache)
अणु
	स्थिर काष्ठा hh_cache *hh = &n->hh;

	अगर ((n->nud_state & NUD_CONNECTED) && hh->hh_len && !skip_cache)
		वापस neigh_hh_output(hh, skb);
	अन्यथा
		वापस n->output(n, skb);
पूर्ण

अटल अंतरभूत काष्ठा neighbour *
__neigh_lookup(काष्ठा neigh_table *tbl, स्थिर व्योम *pkey, काष्ठा net_device *dev, पूर्णांक creat)
अणु
	काष्ठा neighbour *n = neigh_lookup(tbl, pkey, dev);

	अगर (n || !creat)
		वापस n;

	n = neigh_create(tbl, pkey, dev);
	वापस IS_ERR(n) ? शून्य : n;
पूर्ण

अटल अंतरभूत काष्ठा neighbour *
__neigh_lookup_त्रुटि_सं(काष्ठा neigh_table *tbl, स्थिर व्योम *pkey,
  काष्ठा net_device *dev)
अणु
	काष्ठा neighbour *n = neigh_lookup(tbl, pkey, dev);

	अगर (n)
		वापस n;

	वापस neigh_create(tbl, pkey, dev);
पूर्ण

काष्ठा neighbour_cb अणु
	अचिन्हित दीर्घ sched_next;
	अचिन्हित पूर्णांक flags;
पूर्ण;

#घोषणा LOCALLY_ENQUEUED 0x1

#घोषणा NEIGH_CB(skb)	((काष्ठा neighbour_cb *)(skb)->cb)

अटल अंतरभूत व्योम neigh_ha_snapshot(अक्षर *dst, स्थिर काष्ठा neighbour *n,
				     स्थिर काष्ठा net_device *dev)
अणु
	अचिन्हित पूर्णांक seq;

	करो अणु
		seq = पढ़ो_seqbegin(&n->ha_lock);
		स_नकल(dst, n->ha, dev->addr_len);
	पूर्ण जबतक (पढ़ो_seqretry(&n->ha_lock, seq));
पूर्ण

अटल अंतरभूत व्योम neigh_update_is_router(काष्ठा neighbour *neigh, u32 flags,
					  पूर्णांक *notअगरy)
अणु
	u8 ndm_flags = 0;

	ndm_flags |= (flags & NEIGH_UPDATE_F_ISROUTER) ? NTF_ROUTER : 0;
	अगर ((neigh->flags ^ ndm_flags) & NTF_ROUTER) अणु
		अगर (ndm_flags & NTF_ROUTER)
			neigh->flags |= NTF_ROUTER;
		अन्यथा
			neigh->flags &= ~NTF_ROUTER;
		*notअगरy = 1;
	पूर्ण
पूर्ण
#पूर्ण_अगर
