<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *	Linux INET6 implementation 
 *
 *	Authors:
 *	Pedro Roque		<roque@di.fc.ul.pt>	
 */

#अगर_अघोषित _IP6_FIB_H
#घोषणा _IP6_FIB_H

#समावेश <linux/ipv6_route.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/notअगरier.h>
#समावेश <net/dst.h>
#समावेश <net/flow.h>
#समावेश <net/ip_fib.h>
#समावेश <net/netlink.h>
#समावेश <net/inetpeer.h>
#समावेश <net/fib_notअगरier.h>
#समावेश <linux/indirect_call_wrapper.h>

#अगर_घोषित CONFIG_IPV6_MULTIPLE_TABLES
#घोषणा FIB6_TABLE_HASHSZ 256
#अन्यथा
#घोषणा FIB6_TABLE_HASHSZ 1
#पूर्ण_अगर

#घोषणा RT6_DEBUG 2

#अगर RT6_DEBUG >= 3
#घोषणा RT6_TRACE(x...) pr_debug(x)
#अन्यथा
#घोषणा RT6_TRACE(x...) करो अणु ; पूर्ण जबतक (0)
#पूर्ण_अगर

काष्ठा rt6_info;
काष्ठा fib6_info;

काष्ठा fib6_config अणु
	u32		fc_table;
	u32		fc_metric;
	पूर्णांक		fc_dst_len;
	पूर्णांक		fc_src_len;
	पूर्णांक		fc_अगरindex;
	u32		fc_flags;
	u32		fc_protocol;
	u16		fc_type;        /* only 8 bits are used */
	u16		fc_delete_all_nh : 1,
			fc_ignore_dev_करोwn:1,
			__unused : 14;
	u32		fc_nh_id;

	काष्ठा in6_addr	fc_dst;
	काष्ठा in6_addr	fc_src;
	काष्ठा in6_addr	fc_prefsrc;
	काष्ठा in6_addr	fc_gateway;

	अचिन्हित दीर्घ	fc_expires;
	काष्ठा nlattr	*fc_mx;
	पूर्णांक		fc_mx_len;
	पूर्णांक		fc_mp_len;
	काष्ठा nlattr	*fc_mp;

	काष्ठा nl_info	fc_nlinfo;
	काष्ठा nlattr	*fc_encap;
	u16		fc_encap_type;
	bool		fc_is_fdb;
पूर्ण;

काष्ठा fib6_node अणु
	काष्ठा fib6_node __rcu	*parent;
	काष्ठा fib6_node __rcu	*left;
	काष्ठा fib6_node __rcu	*right;
#अगर_घोषित CONFIG_IPV6_SUBTREES
	काष्ठा fib6_node __rcu	*subtree;
#पूर्ण_अगर
	काष्ठा fib6_info __rcu	*leaf;

	__u16			fn_bit;		/* bit key */
	__u16			fn_flags;
	पूर्णांक			fn_sernum;
	काष्ठा fib6_info __rcu	*rr_ptr;
	काष्ठा rcu_head		rcu;
पूर्ण;

काष्ठा fib6_gc_args अणु
	पूर्णांक			समयout;
	पूर्णांक			more;
पूर्ण;

#अगर_अघोषित CONFIG_IPV6_SUBTREES
#घोषणा FIB6_SUBTREE(fn)	शून्य

अटल अंतरभूत bool fib6_routes_require_src(स्थिर काष्ठा net *net)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम fib6_routes_require_src_inc(काष्ठा net *net) अणुपूर्ण
अटल अंतरभूत व्योम fib6_routes_require_src_dec(काष्ठा net *net) अणुपूर्ण

#अन्यथा

अटल अंतरभूत bool fib6_routes_require_src(स्थिर काष्ठा net *net)
अणु
	वापस net->ipv6.fib6_routes_require_src > 0;
पूर्ण

अटल अंतरभूत व्योम fib6_routes_require_src_inc(काष्ठा net *net)
अणु
	net->ipv6.fib6_routes_require_src++;
पूर्ण

अटल अंतरभूत व्योम fib6_routes_require_src_dec(काष्ठा net *net)
अणु
	net->ipv6.fib6_routes_require_src--;
पूर्ण

#घोषणा FIB6_SUBTREE(fn)	(rcu_dereference_रक्षित((fn)->subtree, 1))
#पूर्ण_अगर

/*
 *	routing inक्रमmation
 *
 */

काष्ठा rt6key अणु
	काष्ठा in6_addr	addr;
	पूर्णांक		plen;
पूर्ण;

काष्ठा fib6_table;

काष्ठा rt6_exception_bucket अणु
	काष्ठा hlist_head	chain;
	पूर्णांक			depth;
पूर्ण;

काष्ठा rt6_exception अणु
	काष्ठा hlist_node	hlist;
	काष्ठा rt6_info		*rt6i;
	अचिन्हित दीर्घ		stamp;
	काष्ठा rcu_head		rcu;
पूर्ण;

#घोषणा FIB6_EXCEPTION_BUCKET_SIZE_SHIFT 10
#घोषणा FIB6_EXCEPTION_BUCKET_SIZE (1 << FIB6_EXCEPTION_BUCKET_SIZE_SHIFT)
#घोषणा FIB6_MAX_DEPTH 5

काष्ठा fib6_nh अणु
	काष्ठा fib_nh_common	nh_common;

#अगर_घोषित CONFIG_IPV6_ROUTER_PREF
	अचिन्हित दीर्घ		last_probe;
#पूर्ण_अगर

	काष्ठा rt6_info * __percpu *rt6i_pcpu;
	काष्ठा rt6_exception_bucket __rcu *rt6i_exception_bucket;
पूर्ण;

काष्ठा fib6_info अणु
	काष्ठा fib6_table		*fib6_table;
	काष्ठा fib6_info __rcu		*fib6_next;
	काष्ठा fib6_node __rcu		*fib6_node;

	/* Multipath routes:
	 * siblings is a list of fib6_info that have the same metric/weight,
	 * destination, but not the same gateway. nsiblings is just a cache
	 * to speed up lookup.
	 */
	जोड़ अणु
		काष्ठा list_head	fib6_siblings;
		काष्ठा list_head	nh_list;
	पूर्ण;
	अचिन्हित पूर्णांक			fib6_nsiblings;

	refcount_t			fib6_ref;
	अचिन्हित दीर्घ			expires;
	काष्ठा dst_metrics		*fib6_metrics;
#घोषणा fib6_pmtu		fib6_metrics->metrics[RTAX_MTU-1]

	काष्ठा rt6key			fib6_dst;
	u32				fib6_flags;
	काष्ठा rt6key			fib6_src;
	काष्ठा rt6key			fib6_prefsrc;

	u32				fib6_metric;
	u8				fib6_protocol;
	u8				fib6_type;
	u8				should_flush:1,
					dst_nocount:1,
					dst_nopolicy:1,
					fib6_destroying:1,
					offload:1,
					trap:1,
					offload_failed:1,
					unused:1;

	काष्ठा rcu_head			rcu;
	काष्ठा nexthop			*nh;
	काष्ठा fib6_nh			fib6_nh[];
पूर्ण;

काष्ठा rt6_info अणु
	काष्ठा dst_entry		dst;
	काष्ठा fib6_info __rcu		*from;
	पूर्णांक				sernum;

	काष्ठा rt6key			rt6i_dst;
	काष्ठा rt6key			rt6i_src;
	काष्ठा in6_addr			rt6i_gateway;
	काष्ठा inet6_dev		*rt6i_idev;
	u32				rt6i_flags;

	काष्ठा list_head		rt6i_uncached;
	काष्ठा uncached_list		*rt6i_uncached_list;

	/* more non-fragment space at head required */
	अचिन्हित लघु			rt6i_nfheader_len;
पूर्ण;

काष्ठा fib6_result अणु
	काष्ठा fib6_nh		*nh;
	काष्ठा fib6_info	*f6i;
	u32			fib6_flags;
	u8			fib6_type;
	काष्ठा rt6_info		*rt6;
पूर्ण;

#घोषणा क्रम_each_fib6_node_rt_rcu(fn)					\
	क्रम (rt = rcu_dereference((fn)->leaf); rt;			\
	     rt = rcu_dereference(rt->fib6_next))

#घोषणा क्रम_each_fib6_walker_rt(w)					\
	क्रम (rt = (w)->leaf; rt;					\
	     rt = rcu_dereference_रक्षित(rt->fib6_next, 1))

अटल अंतरभूत काष्ठा inet6_dev *ip6_dst_idev(काष्ठा dst_entry *dst)
अणु
	वापस ((काष्ठा rt6_info *)dst)->rt6i_idev;
पूर्ण

अटल अंतरभूत bool fib6_requires_src(स्थिर काष्ठा fib6_info *rt)
अणु
	वापस rt->fib6_src.plen > 0;
पूर्ण

अटल अंतरभूत व्योम fib6_clean_expires(काष्ठा fib6_info *f6i)
अणु
	f6i->fib6_flags &= ~RTF_EXPIRES;
	f6i->expires = 0;
पूर्ण

अटल अंतरभूत व्योम fib6_set_expires(काष्ठा fib6_info *f6i,
				    अचिन्हित दीर्घ expires)
अणु
	f6i->expires = expires;
	f6i->fib6_flags |= RTF_EXPIRES;
पूर्ण

अटल अंतरभूत bool fib6_check_expired(स्थिर काष्ठा fib6_info *f6i)
अणु
	अगर (f6i->fib6_flags & RTF_EXPIRES)
		वापस समय_after(jअगरfies, f6i->expires);
	वापस false;
पूर्ण

/* Function to safely get fn->sernum क्रम passed in rt
 * and store result in passed in cookie.
 * Return true अगर we can get cookie safely
 * Return false अगर not
 */
अटल अंतरभूत bool fib6_get_cookie_safe(स्थिर काष्ठा fib6_info *f6i,
					u32 *cookie)
अणु
	काष्ठा fib6_node *fn;
	bool status = false;

	fn = rcu_dereference(f6i->fib6_node);

	अगर (fn) अणु
		*cookie = fn->fn_sernum;
		/* pairs with smp_wmb() in fib6_update_sernum_upto_root() */
		smp_rmb();
		status = true;
	पूर्ण

	वापस status;
पूर्ण

अटल अंतरभूत u32 rt6_get_cookie(स्थिर काष्ठा rt6_info *rt)
अणु
	काष्ठा fib6_info *from;
	u32 cookie = 0;

	अगर (rt->sernum)
		वापस rt->sernum;

	rcu_पढ़ो_lock();

	from = rcu_dereference(rt->from);
	अगर (from)
		fib6_get_cookie_safe(from, &cookie);

	rcu_पढ़ो_unlock();

	वापस cookie;
पूर्ण

अटल अंतरभूत व्योम ip6_rt_put(काष्ठा rt6_info *rt)
अणु
	/* dst_release() accepts a शून्य parameter.
	 * We rely on dst being first काष्ठाure in काष्ठा rt6_info
	 */
	BUILD_BUG_ON(दुरत्व(काष्ठा rt6_info, dst) != 0);
	dst_release(&rt->dst);
पूर्ण

काष्ठा fib6_info *fib6_info_alloc(gfp_t gfp_flags, bool with_fib6_nh);
व्योम fib6_info_destroy_rcu(काष्ठा rcu_head *head);

अटल अंतरभूत व्योम fib6_info_hold(काष्ठा fib6_info *f6i)
अणु
	refcount_inc(&f6i->fib6_ref);
पूर्ण

अटल अंतरभूत bool fib6_info_hold_safe(काष्ठा fib6_info *f6i)
अणु
	वापस refcount_inc_not_zero(&f6i->fib6_ref);
पूर्ण

अटल अंतरभूत व्योम fib6_info_release(काष्ठा fib6_info *f6i)
अणु
	अगर (f6i && refcount_dec_and_test(&f6i->fib6_ref))
		call_rcu(&f6i->rcu, fib6_info_destroy_rcu);
पूर्ण

क्रमागत fib6_walk_state अणु
#अगर_घोषित CONFIG_IPV6_SUBTREES
	FWS_S,
#पूर्ण_अगर
	FWS_L,
	FWS_R,
	FWS_C,
	FWS_U
पूर्ण;

काष्ठा fib6_walker अणु
	काष्ठा list_head lh;
	काष्ठा fib6_node *root, *node;
	काष्ठा fib6_info *leaf;
	क्रमागत fib6_walk_state state;
	अचिन्हित पूर्णांक skip;
	अचिन्हित पूर्णांक count;
	अचिन्हित पूर्णांक skip_in_node;
	पूर्णांक (*func)(काष्ठा fib6_walker *);
	व्योम *args;
पूर्ण;

काष्ठा rt6_statistics अणु
	__u32		fib_nodes;		/* all fib6 nodes */
	__u32		fib_route_nodes;	/* पूर्णांकermediate nodes */
	__u32		fib_rt_entries;		/* rt entries in fib table */
	__u32		fib_rt_cache;		/* cached rt entries in exception table */
	__u32		fib_discarded_routes;	/* total number of routes delete */

	/* The following stats are not रक्षित by any lock */
	atomic_t	fib_rt_alloc;		/* total number of routes alloced */
	atomic_t	fib_rt_uncache;		/* rt entries in uncached list */
पूर्ण;

#घोषणा RTN_TL_ROOT	0x0001
#घोषणा RTN_ROOT	0x0002		/* tree root node		*/
#घोषणा RTN_RTINFO	0x0004		/* node with valid routing info	*/

/*
 *	priority levels (or metrics)
 *
 */


काष्ठा fib6_table अणु
	काष्ठा hlist_node	tb6_hlist;
	u32			tb6_id;
	spinlock_t		tb6_lock;
	काष्ठा fib6_node	tb6_root;
	काष्ठा inet_peer_base	tb6_peers;
	अचिन्हित पूर्णांक		flags;
	अचिन्हित पूर्णांक		fib_seq;
#घोषणा RT6_TABLE_HAS_DFLT_ROUTER	BIT(0)
पूर्ण;

#घोषणा RT6_TABLE_UNSPEC	RT_TABLE_UNSPEC
#घोषणा RT6_TABLE_MAIN		RT_TABLE_MAIN
#घोषणा RT6_TABLE_DFLT		RT6_TABLE_MAIN
#घोषणा RT6_TABLE_INFO		RT6_TABLE_MAIN
#घोषणा RT6_TABLE_PREFIX	RT6_TABLE_MAIN

#अगर_घोषित CONFIG_IPV6_MULTIPLE_TABLES
#घोषणा FIB6_TABLE_MIN		1
#घोषणा FIB6_TABLE_MAX		RT_TABLE_MAX
#घोषणा RT6_TABLE_LOCAL		RT_TABLE_LOCAL
#अन्यथा
#घोषणा FIB6_TABLE_MIN		RT_TABLE_MAIN
#घोषणा FIB6_TABLE_MAX		FIB6_TABLE_MIN
#घोषणा RT6_TABLE_LOCAL		RT6_TABLE_MAIN
#पूर्ण_अगर

प्रकार काष्ठा rt6_info *(*pol_lookup_t)(काष्ठा net *,
					 काष्ठा fib6_table *,
					 काष्ठा flowi6 *,
					 स्थिर काष्ठा sk_buff *, पूर्णांक);

काष्ठा fib6_entry_notअगरier_info अणु
	काष्ठा fib_notअगरier_info info; /* must be first */
	काष्ठा fib6_info *rt;
	अचिन्हित पूर्णांक nsiblings;
पूर्ण;

/*
 *	exported functions
 */

काष्ठा fib6_table *fib6_get_table(काष्ठा net *net, u32 id);
काष्ठा fib6_table *fib6_new_table(काष्ठा net *net, u32 id);
काष्ठा dst_entry *fib6_rule_lookup(काष्ठा net *net, काष्ठा flowi6 *fl6,
				   स्थिर काष्ठा sk_buff *skb,
				   पूर्णांक flags, pol_lookup_t lookup);

/* called with rcu lock held; can वापस error poपूर्णांकer
 * caller needs to select path
 */
पूर्णांक fib6_lookup(काष्ठा net *net, पूर्णांक oअगर, काष्ठा flowi6 *fl6,
		काष्ठा fib6_result *res, पूर्णांक flags);

/* called with rcu lock held; caller needs to select path */
पूर्णांक fib6_table_lookup(काष्ठा net *net, काष्ठा fib6_table *table,
		      पूर्णांक oअगर, काष्ठा flowi6 *fl6, काष्ठा fib6_result *res,
		      पूर्णांक strict);

व्योम fib6_select_path(स्थिर काष्ठा net *net, काष्ठा fib6_result *res,
		      काष्ठा flowi6 *fl6, पूर्णांक oअगर, bool have_oअगर_match,
		      स्थिर काष्ठा sk_buff *skb, पूर्णांक strict);
काष्ठा fib6_node *fib6_node_lookup(काष्ठा fib6_node *root,
				   स्थिर काष्ठा in6_addr *daddr,
				   स्थिर काष्ठा in6_addr *saddr);

काष्ठा fib6_node *fib6_locate(काष्ठा fib6_node *root,
			      स्थिर काष्ठा in6_addr *daddr, पूर्णांक dst_len,
			      स्थिर काष्ठा in6_addr *saddr, पूर्णांक src_len,
			      bool exact_match);

व्योम fib6_clean_all(काष्ठा net *net, पूर्णांक (*func)(काष्ठा fib6_info *, व्योम *arg),
		    व्योम *arg);
व्योम fib6_clean_all_skip_notअगरy(काष्ठा net *net,
				पूर्णांक (*func)(काष्ठा fib6_info *, व्योम *arg),
				व्योम *arg);

पूर्णांक fib6_add(काष्ठा fib6_node *root, काष्ठा fib6_info *rt,
	     काष्ठा nl_info *info, काष्ठा netlink_ext_ack *extack);
पूर्णांक fib6_del(काष्ठा fib6_info *rt, काष्ठा nl_info *info);

अटल अंतरभूत
व्योम rt6_get_prefsrc(स्थिर काष्ठा rt6_info *rt, काष्ठा in6_addr *addr)
अणु
	स्थिर काष्ठा fib6_info *from;

	rcu_पढ़ो_lock();

	from = rcu_dereference(rt->from);
	अगर (from) अणु
		*addr = from->fib6_prefsrc.addr;
	पूर्ण अन्यथा अणु
		काष्ठा in6_addr in6_zero = अणुपूर्ण;

		*addr = in6_zero;
	पूर्ण

	rcu_पढ़ो_unlock();
पूर्ण

पूर्णांक fib6_nh_init(काष्ठा net *net, काष्ठा fib6_nh *fib6_nh,
		 काष्ठा fib6_config *cfg, gfp_t gfp_flags,
		 काष्ठा netlink_ext_ack *extack);
व्योम fib6_nh_release(काष्ठा fib6_nh *fib6_nh);

पूर्णांक call_fib6_entry_notअगरiers(काष्ठा net *net,
			      क्रमागत fib_event_type event_type,
			      काष्ठा fib6_info *rt,
			      काष्ठा netlink_ext_ack *extack);
पूर्णांक call_fib6_multipath_entry_notअगरiers(काष्ठा net *net,
					क्रमागत fib_event_type event_type,
					काष्ठा fib6_info *rt,
					अचिन्हित पूर्णांक nsiblings,
					काष्ठा netlink_ext_ack *extack);
पूर्णांक call_fib6_entry_notअगरiers_replace(काष्ठा net *net, काष्ठा fib6_info *rt);
व्योम fib6_rt_update(काष्ठा net *net, काष्ठा fib6_info *rt,
		    काष्ठा nl_info *info);
व्योम inet6_rt_notअगरy(पूर्णांक event, काष्ठा fib6_info *rt, काष्ठा nl_info *info,
		     अचिन्हित पूर्णांक flags);

व्योम fib6_run_gc(अचिन्हित दीर्घ expires, काष्ठा net *net, bool क्रमce);

व्योम fib6_gc_cleanup(व्योम);

पूर्णांक fib6_init(व्योम);

काष्ठा ipv6_route_iter अणु
	काष्ठा seq_net_निजी p;
	काष्ठा fib6_walker w;
	loff_t skip;
	काष्ठा fib6_table *tbl;
	पूर्णांक sernum;
पूर्ण;

बाह्य स्थिर काष्ठा seq_operations ipv6_route_seq_ops;

पूर्णांक call_fib6_notअगरier(काष्ठा notअगरier_block *nb,
		       क्रमागत fib_event_type event_type,
		       काष्ठा fib_notअगरier_info *info);
पूर्णांक call_fib6_notअगरiers(काष्ठा net *net, क्रमागत fib_event_type event_type,
			काष्ठा fib_notअगरier_info *info);

पूर्णांक __net_init fib6_notअगरier_init(काष्ठा net *net);
व्योम __net_निकास fib6_notअगरier_निकास(काष्ठा net *net);

अचिन्हित पूर्णांक fib6_tables_seq_पढ़ो(काष्ठा net *net);
पूर्णांक fib6_tables_dump(काष्ठा net *net, काष्ठा notअगरier_block *nb,
		     काष्ठा netlink_ext_ack *extack);

व्योम fib6_update_sernum(काष्ठा net *net, काष्ठा fib6_info *rt);
व्योम fib6_update_sernum_upto_root(काष्ठा net *net, काष्ठा fib6_info *rt);
व्योम fib6_update_sernum_stub(काष्ठा net *net, काष्ठा fib6_info *f6i);

व्योम fib6_metric_set(काष्ठा fib6_info *f6i, पूर्णांक metric, u32 val);
अटल अंतरभूत bool fib6_metric_locked(काष्ठा fib6_info *f6i, पूर्णांक metric)
अणु
	वापस !!(f6i->fib6_metrics->metrics[RTAX_LOCK - 1] & (1 << metric));
पूर्ण
व्योम fib6_info_hw_flags_set(काष्ठा net *net, काष्ठा fib6_info *f6i,
			    bool offload, bool trap, bool offload_failed);

#अगर IS_BUILTIN(CONFIG_IPV6) && defined(CONFIG_BPF_SYSCALL)
काष्ठा bpf_iter__ipv6_route अणु
	__bpf_md_ptr(काष्ठा bpf_iter_meta *, meta);
	__bpf_md_ptr(काष्ठा fib6_info *, rt);
पूर्ण;
#पूर्ण_अगर

INसूचीECT_CALLABLE_DECLARE(काष्ठा rt6_info *ip6_pol_route_output(काष्ठा net *net,
					     काष्ठा fib6_table *table,
					     काष्ठा flowi6 *fl6,
					     स्थिर काष्ठा sk_buff *skb,
					     पूर्णांक flags));
INसूचीECT_CALLABLE_DECLARE(काष्ठा rt6_info *ip6_pol_route_input(काष्ठा net *net,
					     काष्ठा fib6_table *table,
					     काष्ठा flowi6 *fl6,
					     स्थिर काष्ठा sk_buff *skb,
					     पूर्णांक flags));
INसूचीECT_CALLABLE_DECLARE(काष्ठा rt6_info *__ip6_route_redirect(काष्ठा net *net,
					     काष्ठा fib6_table *table,
					     काष्ठा flowi6 *fl6,
					     स्थिर काष्ठा sk_buff *skb,
					     पूर्णांक flags));
INसूचीECT_CALLABLE_DECLARE(काष्ठा rt6_info *ip6_pol_route_lookup(काष्ठा net *net,
					     काष्ठा fib6_table *table,
					     काष्ठा flowi6 *fl6,
					     स्थिर काष्ठा sk_buff *skb,
					     पूर्णांक flags));
अटल अंतरभूत काष्ठा rt6_info *pol_lookup_func(pol_lookup_t lookup,
						काष्ठा net *net,
						काष्ठा fib6_table *table,
						काष्ठा flowi6 *fl6,
						स्थिर काष्ठा sk_buff *skb,
						पूर्णांक flags)
अणु
	वापस INसूचीECT_CALL_4(lookup,
			       ip6_pol_route_output,
			       ip6_pol_route_input,
			       ip6_pol_route_lookup,
			       __ip6_route_redirect,
			       net, table, fl6, skb, flags);
पूर्ण

#अगर_घोषित CONFIG_IPV6_MULTIPLE_TABLES
अटल अंतरभूत bool fib6_has_custom_rules(स्थिर काष्ठा net *net)
अणु
	वापस net->ipv6.fib6_has_custom_rules;
पूर्ण

पूर्णांक fib6_rules_init(व्योम);
व्योम fib6_rules_cleanup(व्योम);
bool fib6_rule_शेष(स्थिर काष्ठा fib_rule *rule);
पूर्णांक fib6_rules_dump(काष्ठा net *net, काष्ठा notअगरier_block *nb,
		    काष्ठा netlink_ext_ack *extack);
अचिन्हित पूर्णांक fib6_rules_seq_पढ़ो(काष्ठा net *net);

अटल अंतरभूत bool fib6_rules_early_flow_dissect(काष्ठा net *net,
						 काष्ठा sk_buff *skb,
						 काष्ठा flowi6 *fl6,
						 काष्ठा flow_keys *flkeys)
अणु
	अचिन्हित पूर्णांक flag = FLOW_DISSECTOR_F_STOP_AT_ENCAP;

	अगर (!net->ipv6.fib6_rules_require_fldissect)
		वापस false;

	skb_flow_dissect_flow_keys(skb, flkeys, flag);
	fl6->fl6_sport = flkeys->ports.src;
	fl6->fl6_dport = flkeys->ports.dst;
	fl6->flowi6_proto = flkeys->basic.ip_proto;

	वापस true;
पूर्ण
#अन्यथा
अटल अंतरभूत bool fib6_has_custom_rules(स्थिर काष्ठा net *net)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत पूर्णांक               fib6_rules_init(व्योम)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम              fib6_rules_cleanup(व्योम)
अणु
	वापस ;
पूर्ण
अटल अंतरभूत bool fib6_rule_शेष(स्थिर काष्ठा fib_rule *rule)
अणु
	वापस true;
पूर्ण
अटल अंतरभूत पूर्णांक fib6_rules_dump(काष्ठा net *net, काष्ठा notअगरier_block *nb,
				  काष्ठा netlink_ext_ack *extack)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत अचिन्हित पूर्णांक fib6_rules_seq_पढ़ो(काष्ठा net *net)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत bool fib6_rules_early_flow_dissect(काष्ठा net *net,
						 काष्ठा sk_buff *skb,
						 काष्ठा flowi6 *fl6,
						 काष्ठा flow_keys *flkeys)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर
