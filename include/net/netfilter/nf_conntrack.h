<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Connection state tracking क्रम netfilter.  This is separated from,
 * but required by, the (future) NAT layer; it can also be used by an iptables
 * extension.
 *
 * 16 Dec 2003: Yasuyuki Kozakai @USAGI <yasuyuki.kozakai@toshiba.co.jp>
 *	- generalize L3 protocol dependent part.
 *
 * Derived from include/linux/netfiter_ipv4/ip_conntrack.h
 */

#अगर_अघोषित _NF_CONNTRACK_H
#घोषणा _NF_CONNTRACK_H

#समावेश <linux/bitops.h>
#समावेश <linux/compiler.h>

#समावेश <linux/netfilter/nf_conntrack_common.h>
#समावेश <linux/netfilter/nf_conntrack_tcp.h>
#समावेश <linux/netfilter/nf_conntrack_dccp.h>
#समावेश <linux/netfilter/nf_conntrack_sctp.h>
#समावेश <linux/netfilter/nf_conntrack_proto_gre.h>

#समावेश <net/netfilter/nf_conntrack_tuple.h>

काष्ठा nf_ct_udp अणु
	अचिन्हित दीर्घ	stream_ts;
पूर्ण;

/* per conntrack: protocol निजी data */
जोड़ nf_conntrack_proto अणु
	/* insert conntrack proto निजी data here */
	काष्ठा nf_ct_dccp dccp;
	काष्ठा ip_ct_sctp sctp;
	काष्ठा ip_ct_tcp tcp;
	काष्ठा nf_ct_udp udp;
	काष्ठा nf_ct_gre gre;
	अचिन्हित पूर्णांक पंचांगpl_padto;
पूर्ण;

जोड़ nf_conntrack_expect_proto अणु
	/* insert expect proto निजी data here */
पूर्ण;

काष्ठा nf_conntrack_net अणु
	/* only used when new connection is allocated: */
	atomic_t count;
	अचिन्हित पूर्णांक expect_count;
	u8 sysctl_स्वतः_assign_helper;
	bool स्वतः_assign_helper_warned;

	/* only used from work queues, configuration plane, and so on: */
	अचिन्हित पूर्णांक users4;
	अचिन्हित पूर्णांक users6;
	अचिन्हित पूर्णांक users_bridge;
#अगर_घोषित CONFIG_SYSCTL
	काष्ठा ctl_table_header	*sysctl_header;
#पूर्ण_अगर
#अगर_घोषित CONFIG_NF_CONNTRACK_EVENTS
	काष्ठा delayed_work ecache_dwork;
	काष्ठा netns_ct *ct_net;
#पूर्ण_अगर
पूर्ण;

#समावेश <linux/types.h>
#समावेश <linux/skbuff.h>

#समावेश <net/netfilter/ipv4/nf_conntrack_ipv4.h>
#समावेश <net/netfilter/ipv6/nf_conntrack_ipv6.h>

काष्ठा nf_conn अणु
	/* Usage count in here is 1 क्रम hash table, 1 per skb,
	 * plus 1 क्रम any connection(s) we are `master' क्रम
	 *
	 * Hपूर्णांक, SKB address this काष्ठा and refcnt via skb->_nfct and
	 * helpers nf_conntrack_get() and nf_conntrack_put().
	 * Helper nf_ct_put() equals nf_conntrack_put() by dec refcnt,
	 * beware nf_ct_get() is dअगरferent and करोn't inc refcnt.
	 */
	काष्ठा nf_conntrack ct_general;

	spinlock_t	lock;
	/* jअगरfies32 when this ct is considered dead */
	u32 समयout;

#अगर_घोषित CONFIG_NF_CONNTRACK_ZONES
	काष्ठा nf_conntrack_zone zone;
#पूर्ण_अगर
	/* XXX should I move this to the tail ? - Y.K */
	/* These are my tuples; original and reply */
	काष्ठा nf_conntrack_tuple_hash tuplehash[IP_CT_सूची_MAX];

	/* Have we seen traffic both ways yet? (bitset) */
	अचिन्हित दीर्घ status;

	u16		cpu;
	possible_net_t ct_net;

#अगर IS_ENABLED(CONFIG_NF_NAT)
	काष्ठा hlist_node	nat_bysource;
#पूर्ण_अगर
	/* all members below initialized via स_रखो */
	काष्ठा अणु पूर्ण __nfct_init_offset;

	/* If we were expected by an expectation, this will be it */
	काष्ठा nf_conn *master;

#अगर defined(CONFIG_NF_CONNTRACK_MARK)
	u_पूर्णांक32_t mark;
#पूर्ण_अगर

#अगर_घोषित CONFIG_NF_CONNTRACK_SECMARK
	u_पूर्णांक32_t secmark;
#पूर्ण_अगर

	/* Extensions */
	काष्ठा nf_ct_ext *ext;

	/* Storage reserved क्रम other modules, must be the last member */
	जोड़ nf_conntrack_proto proto;
पूर्ण;

अटल अंतरभूत काष्ठा nf_conn *
nf_ct_tuplehash_to_ctrack(स्थिर काष्ठा nf_conntrack_tuple_hash *hash)
अणु
	वापस container_of(hash, काष्ठा nf_conn,
			    tuplehash[hash->tuple.dst.dir]);
पूर्ण

अटल अंतरभूत u_पूर्णांक16_t nf_ct_l3num(स्थिर काष्ठा nf_conn *ct)
अणु
	वापस ct->tuplehash[IP_CT_सूची_ORIGINAL].tuple.src.l3num;
पूर्ण

अटल अंतरभूत u_पूर्णांक8_t nf_ct_protonum(स्थिर काष्ठा nf_conn *ct)
अणु
	वापस ct->tuplehash[IP_CT_सूची_ORIGINAL].tuple.dst.protonum;
पूर्ण

#घोषणा nf_ct_tuple(ct, dir) (&(ct)->tuplehash[dir].tuple)

/* get master conntrack via master expectation */
#घोषणा master_ct(conntr) (conntr->master)

बाह्य काष्ठा net init_net;

अटल अंतरभूत काष्ठा net *nf_ct_net(स्थिर काष्ठा nf_conn *ct)
अणु
	वापस पढ़ो_pnet(&ct->ct_net);
पूर्ण

/* Alter reply tuple (maybe alter helper). */
व्योम nf_conntrack_alter_reply(काष्ठा nf_conn *ct,
			      स्थिर काष्ठा nf_conntrack_tuple *newreply);

/* Is this tuple taken? (ignoring any beदीर्घing to the given
   conntrack). */
पूर्णांक nf_conntrack_tuple_taken(स्थिर काष्ठा nf_conntrack_tuple *tuple,
			     स्थिर काष्ठा nf_conn *ignored_conntrack);

/* Return conntrack_info and tuple hash क्रम given skb. */
अटल अंतरभूत काष्ठा nf_conn *
nf_ct_get(स्थिर काष्ठा sk_buff *skb, क्रमागत ip_conntrack_info *ctinfo)
अणु
	अचिन्हित दीर्घ nfct = skb_get_nfct(skb);

	*ctinfo = nfct & NFCT_INFOMASK;
	वापस (काष्ठा nf_conn *)(nfct & NFCT_PTRMASK);
पूर्ण

/* decrement reference count on a conntrack */
अटल अंतरभूत व्योम nf_ct_put(काष्ठा nf_conn *ct)
अणु
	WARN_ON(!ct);
	nf_conntrack_put(&ct->ct_general);
पूर्ण

/* Protocol module loading */
पूर्णांक nf_ct_l3proto_try_module_get(अचिन्हित लघु l3proto);
व्योम nf_ct_l3proto_module_put(अचिन्हित लघु l3proto);

/* load module; enable/disable conntrack in this namespace */
पूर्णांक nf_ct_netns_get(काष्ठा net *net, u8 nfproto);
व्योम nf_ct_netns_put(काष्ठा net *net, u8 nfproto);

/*
 * Allocate a hashtable of hlist_head (अगर nulls == 0),
 * or hlist_nulls_head (अगर nulls == 1)
 */
व्योम *nf_ct_alloc_hashtable(अचिन्हित पूर्णांक *sizep, पूर्णांक nulls);

पूर्णांक nf_conntrack_hash_check_insert(काष्ठा nf_conn *ct);
bool nf_ct_delete(काष्ठा nf_conn *ct, u32 pid, पूर्णांक report);

bool nf_ct_get_tuplepr(स्थिर काष्ठा sk_buff *skb, अचिन्हित पूर्णांक nhoff,
		       u_पूर्णांक16_t l3num, काष्ठा net *net,
		       काष्ठा nf_conntrack_tuple *tuple);

व्योम __nf_ct_refresh_acct(काष्ठा nf_conn *ct, क्रमागत ip_conntrack_info ctinfo,
			  स्थिर काष्ठा sk_buff *skb,
			  u32 extra_jअगरfies, bool करो_acct);

/* Refresh conntrack क्रम this many jअगरfies and करो accounting */
अटल अंतरभूत व्योम nf_ct_refresh_acct(काष्ठा nf_conn *ct,
				      क्रमागत ip_conntrack_info ctinfo,
				      स्थिर काष्ठा sk_buff *skb,
				      u32 extra_jअगरfies)
अणु
	__nf_ct_refresh_acct(ct, ctinfo, skb, extra_jअगरfies, true);
पूर्ण

/* Refresh conntrack क्रम this many jअगरfies */
अटल अंतरभूत व्योम nf_ct_refresh(काष्ठा nf_conn *ct,
				 स्थिर काष्ठा sk_buff *skb,
				 u32 extra_jअगरfies)
अणु
	__nf_ct_refresh_acct(ct, 0, skb, extra_jअगरfies, false);
पूर्ण

/* समाप्त conntrack and करो accounting */
bool nf_ct_समाप्त_acct(काष्ठा nf_conn *ct, क्रमागत ip_conntrack_info ctinfo,
		     स्थिर काष्ठा sk_buff *skb);

/* समाप्त conntrack without accounting */
अटल अंतरभूत bool nf_ct_समाप्त(काष्ठा nf_conn *ct)
अणु
	वापस nf_ct_delete(ct, 0, 0);
पूर्ण

/* Set all unconfirmed conntrack as dying */
व्योम nf_ct_unconfirmed_destroy(काष्ठा net *);

/* Iterate over all conntracks: अगर iter वापसs true, it's deleted. */
व्योम nf_ct_iterate_cleanup_net(काष्ठा net *net,
			       पूर्णांक (*iter)(काष्ठा nf_conn *i, व्योम *data),
			       व्योम *data, u32 portid, पूर्णांक report);

/* also set unconfirmed conntracks as dying. Only use in module निकास path. */
व्योम nf_ct_iterate_destroy(पूर्णांक (*iter)(काष्ठा nf_conn *i, व्योम *data),
			   व्योम *data);

काष्ठा nf_conntrack_zone;

व्योम nf_conntrack_मुक्त(काष्ठा nf_conn *ct);
काष्ठा nf_conn *nf_conntrack_alloc(काष्ठा net *net,
				   स्थिर काष्ठा nf_conntrack_zone *zone,
				   स्थिर काष्ठा nf_conntrack_tuple *orig,
				   स्थिर काष्ठा nf_conntrack_tuple *repl,
				   gfp_t gfp);

अटल अंतरभूत पूर्णांक nf_ct_is_ढाँचा(स्थिर काष्ठा nf_conn *ct)
अणु
	वापस test_bit(IPS_TEMPLATE_BIT, &ct->status);
पूर्ण

/* It's confirmed अगर it is, or has been in the hash table. */
अटल अंतरभूत पूर्णांक nf_ct_is_confirmed(स्थिर काष्ठा nf_conn *ct)
अणु
	वापस test_bit(IPS_CONFIRMED_BIT, &ct->status);
पूर्ण

अटल अंतरभूत पूर्णांक nf_ct_is_dying(स्थिर काष्ठा nf_conn *ct)
अणु
	वापस test_bit(IPS_DYING_BIT, &ct->status);
पूर्ण

/* Packet is received from loopback */
अटल अंतरभूत bool nf_is_loopback_packet(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस skb->dev && skb->skb_iअगर && skb->dev->flags & IFF_LOOPBACK;
पूर्ण

#घोषणा nfct_समय_stamp ((u32)(jअगरfies))

/* jअगरfies until ct expires, 0 अगर alपढ़ोy expired */
अटल अंतरभूत अचिन्हित दीर्घ nf_ct_expires(स्थिर काष्ठा nf_conn *ct)
अणु
	s32 समयout = ct->समयout - nfct_समय_stamp;

	वापस समयout > 0 ? समयout : 0;
पूर्ण

अटल अंतरभूत bool nf_ct_is_expired(स्थिर काष्ठा nf_conn *ct)
अणु
	वापस (__s32)(ct->समयout - nfct_समय_stamp) <= 0;
पूर्ण

/* use after obtaining a reference count */
अटल अंतरभूत bool nf_ct_should_gc(स्थिर काष्ठा nf_conn *ct)
अणु
	वापस nf_ct_is_expired(ct) && nf_ct_is_confirmed(ct) &&
	       !nf_ct_is_dying(ct);
पूर्ण

#घोषणा	NF_CT_DAY	(86400 * HZ)

/* Set an arbitrary समयout large enough not to ever expire, this save
 * us a check क्रम the IPS_OFFLOAD_BIT from the packet path via
 * nf_ct_is_expired().
 */
अटल अंतरभूत व्योम nf_ct_offload_समयout(काष्ठा nf_conn *ct)
अणु
	अगर (nf_ct_expires(ct) < NF_CT_DAY / 2)
		ct->समयout = nfct_समय_stamp + NF_CT_DAY;
पूर्ण

काष्ठा kernel_param;

पूर्णांक nf_conntrack_set_hashsize(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp);
पूर्णांक nf_conntrack_hash_resize(अचिन्हित पूर्णांक hashsize);

बाह्य काष्ठा hlist_nulls_head *nf_conntrack_hash;
बाह्य अचिन्हित पूर्णांक nf_conntrack_htable_size;
बाह्य seqcount_spinlock_t nf_conntrack_generation;
बाह्य अचिन्हित पूर्णांक nf_conntrack_max;

/* must be called with rcu पढ़ो lock held */
अटल अंतरभूत व्योम
nf_conntrack_get_ht(काष्ठा hlist_nulls_head **hash, अचिन्हित पूर्णांक *hsize)
अणु
	काष्ठा hlist_nulls_head *hptr;
	अचिन्हित पूर्णांक sequence, hsz;

	करो अणु
		sequence = पढ़ो_seqcount_begin(&nf_conntrack_generation);
		hsz = nf_conntrack_htable_size;
		hptr = nf_conntrack_hash;
	पूर्ण जबतक (पढ़ो_seqcount_retry(&nf_conntrack_generation, sequence));

	*hash = hptr;
	*hsize = hsz;
पूर्ण

काष्ठा nf_conn *nf_ct_पंचांगpl_alloc(काष्ठा net *net,
				 स्थिर काष्ठा nf_conntrack_zone *zone,
				 gfp_t flags);
व्योम nf_ct_पंचांगpl_मुक्त(काष्ठा nf_conn *पंचांगpl);

u32 nf_ct_get_id(स्थिर काष्ठा nf_conn *ct);
u32 nf_conntrack_count(स्थिर काष्ठा net *net);

अटल अंतरभूत व्योम
nf_ct_set(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct, क्रमागत ip_conntrack_info info)
अणु
	skb_set_nfct(skb, (अचिन्हित दीर्घ)ct | info);
पूर्ण

#घोषणा NF_CT_STAT_INC(net, count)	  __this_cpu_inc((net)->ct.stat->count)
#घोषणा NF_CT_STAT_INC_ATOMIC(net, count) this_cpu_inc((net)->ct.stat->count)
#घोषणा NF_CT_STAT_ADD_ATOMIC(net, count, v) this_cpu_add((net)->ct.stat->count, (v))

#घोषणा MODULE_ALIAS_NFCT_HELPER(helper) \
        MODULE_ALIAS("nfct-helper-" helper)

#पूर्ण_अगर /* _NF_CONNTRACK_H */
