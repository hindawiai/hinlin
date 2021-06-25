<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Generic nexthop implementation
 *
 * Copyright (c) 2017-19 Cumulus Networks
 * Copyright (c) 2017-19 David Ahern <dsa@cumulusnetworks.com>
 */

#अगर_अघोषित __LINUX_NEXTHOP_H
#घोषणा __LINUX_NEXTHOP_H

#समावेश <linux/netdevice.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/route.h>
#समावेश <linux/types.h>
#समावेश <net/ip_fib.h>
#समावेश <net/ip6_fib.h>
#समावेश <net/netlink.h>

#घोषणा NEXTHOP_VALID_USER_FLAGS RTNH_F_ONLINK

काष्ठा nexthop;

काष्ठा nh_config अणु
	u32		nh_id;

	u8		nh_family;
	u8		nh_protocol;
	u8		nh_blackhole;
	u8		nh_fdb;
	u32		nh_flags;

	पूर्णांक		nh_अगरindex;
	काष्ठा net_device *dev;

	जोड़ अणु
		__be32		ipv4;
		काष्ठा in6_addr	ipv6;
	पूर्ण gw;

	काष्ठा nlattr	*nh_grp;
	u16		nh_grp_type;
	u16		nh_grp_res_num_buckets;
	अचिन्हित दीर्घ	nh_grp_res_idle_समयr;
	अचिन्हित दीर्घ	nh_grp_res_unbalanced_समयr;
	bool		nh_grp_res_has_num_buckets;
	bool		nh_grp_res_has_idle_समयr;
	bool		nh_grp_res_has_unbalanced_समयr;

	काष्ठा nlattr	*nh_encap;
	u16		nh_encap_type;

	u32		nlflags;
	काष्ठा nl_info	nlinfo;
पूर्ण;

काष्ठा nh_info अणु
	काष्ठा hlist_node	dev_hash;    /* entry on netns devhash */
	काष्ठा nexthop		*nh_parent;

	u8			family;
	bool			reject_nh;
	bool			fdb_nh;

	जोड़ अणु
		काष्ठा fib_nh_common	fib_nhc;
		काष्ठा fib_nh		fib_nh;
		काष्ठा fib6_nh		fib6_nh;
	पूर्ण;
पूर्ण;

काष्ठा nh_res_bucket अणु
	काष्ठा nh_grp_entry __rcu *nh_entry;
	atomic_दीर्घ_t		used_समय;
	अचिन्हित दीर्घ		migrated_समय;
	bool			occupied;
	u8			nh_flags;
पूर्ण;

काष्ठा nh_res_table अणु
	काष्ठा net		*net;
	u32			nhg_id;
	काष्ठा delayed_work	upkeep_dw;

	/* List of NHGEs that have too few buckets ("uw" क्रम underweight).
	 * Reclaimed buckets will be given to entries in this list.
	 */
	काष्ठा list_head	uw_nh_entries;
	अचिन्हित दीर्घ		unbalanced_since;

	u32			idle_समयr;
	u32			unbalanced_समयr;

	u16			num_nh_buckets;
	काष्ठा nh_res_bucket	nh_buckets[];
पूर्ण;

काष्ठा nh_grp_entry अणु
	काष्ठा nexthop	*nh;
	u8		weight;

	जोड़ अणु
		काष्ठा अणु
			atomic_t	upper_bound;
		पूर्ण hthr;
		काष्ठा अणु
			/* Member on uw_nh_entries. */
			काष्ठा list_head	uw_nh_entry;

			u16			count_buckets;
			u16			wants_buckets;
		पूर्ण res;
	पूर्ण;

	काष्ठा list_head nh_list;
	काष्ठा nexthop	*nh_parent;  /* nexthop of group with this entry */
पूर्ण;

काष्ठा nh_group अणु
	काष्ठा nh_group		*spare; /* spare group क्रम removals */
	u16			num_nh;
	bool			is_multipath;
	bool			hash_threshold;
	bool			resilient;
	bool			fdb_nh;
	bool			has_v4;

	काष्ठा nh_res_table __rcu *res_table;
	काष्ठा nh_grp_entry	nh_entries[];
पूर्ण;

काष्ठा nexthop अणु
	काष्ठा rb_node		rb_node;    /* entry on netns rbtree */
	काष्ठा list_head	fi_list;    /* v4 entries using nh */
	काष्ठा list_head	f6i_list;   /* v6 entries using nh */
	काष्ठा list_head        fdb_list;   /* fdb entries using this nh */
	काष्ठा list_head	grp_list;   /* nh group entries using this nh */
	काष्ठा net		*net;

	u32			id;

	u8			protocol;   /* app managing this nh */
	u8			nh_flags;
	bool			is_group;

	refcount_t		refcnt;
	काष्ठा rcu_head		rcu;

	जोड़ अणु
		काष्ठा nh_info	__rcu *nh_info;
		काष्ठा nh_group __rcu *nh_grp;
	पूर्ण;
पूर्ण;

क्रमागत nexthop_event_type अणु
	NEXTHOP_EVENT_DEL,
	NEXTHOP_EVENT_REPLACE,
	NEXTHOP_EVENT_RES_TABLE_PRE_REPLACE,
	NEXTHOP_EVENT_BUCKET_REPLACE,
पूर्ण;

क्रमागत nh_notअगरier_info_type अणु
	NH_NOTIFIER_INFO_TYPE_SINGLE,
	NH_NOTIFIER_INFO_TYPE_GRP,
	NH_NOTIFIER_INFO_TYPE_RES_TABLE,
	NH_NOTIFIER_INFO_TYPE_RES_BUCKET,
पूर्ण;

काष्ठा nh_notअगरier_single_info अणु
	काष्ठा net_device *dev;
	u8 gw_family;
	जोड़ अणु
		__be32 ipv4;
		काष्ठा in6_addr ipv6;
	पूर्ण;
	u8 is_reject:1,
	   is_fdb:1,
	   has_encap:1;
पूर्ण;

काष्ठा nh_notअगरier_grp_entry_info अणु
	u8 weight;
	u32 id;
	काष्ठा nh_notअगरier_single_info nh;
पूर्ण;

काष्ठा nh_notअगरier_grp_info अणु
	u16 num_nh;
	bool is_fdb;
	काष्ठा nh_notअगरier_grp_entry_info nh_entries[];
पूर्ण;

काष्ठा nh_notअगरier_res_bucket_info अणु
	u16 bucket_index;
	अचिन्हित पूर्णांक idle_समयr_ms;
	bool क्रमce;
	काष्ठा nh_notअगरier_single_info old_nh;
	काष्ठा nh_notअगरier_single_info new_nh;
पूर्ण;

काष्ठा nh_notअगरier_res_table_info अणु
	u16 num_nh_buckets;
	काष्ठा nh_notअगरier_single_info nhs[];
पूर्ण;

काष्ठा nh_notअगरier_info अणु
	काष्ठा net *net;
	काष्ठा netlink_ext_ack *extack;
	u32 id;
	क्रमागत nh_notअगरier_info_type type;
	जोड़ अणु
		काष्ठा nh_notअगरier_single_info *nh;
		काष्ठा nh_notअगरier_grp_info *nh_grp;
		काष्ठा nh_notअगरier_res_table_info *nh_res_table;
		काष्ठा nh_notअगरier_res_bucket_info *nh_res_bucket;
	पूर्ण;
पूर्ण;

पूर्णांक रेजिस्टर_nexthop_notअगरier(काष्ठा net *net, काष्ठा notअगरier_block *nb,
			      काष्ठा netlink_ext_ack *extack);
पूर्णांक unरेजिस्टर_nexthop_notअगरier(काष्ठा net *net, काष्ठा notअगरier_block *nb);
व्योम nexthop_set_hw_flags(काष्ठा net *net, u32 id, bool offload, bool trap);
व्योम nexthop_bucket_set_hw_flags(काष्ठा net *net, u32 id, u16 bucket_index,
				 bool offload, bool trap);
व्योम nexthop_res_grp_activity_update(काष्ठा net *net, u32 id, u16 num_buckets,
				     अचिन्हित दीर्घ *activity);

/* caller is holding rcu or rtnl; no reference taken to nexthop */
काष्ठा nexthop *nexthop_find_by_id(काष्ठा net *net, u32 id);
व्योम nexthop_मुक्त_rcu(काष्ठा rcu_head *head);

अटल अंतरभूत bool nexthop_get(काष्ठा nexthop *nh)
अणु
	वापस refcount_inc_not_zero(&nh->refcnt);
पूर्ण

अटल अंतरभूत व्योम nexthop_put(काष्ठा nexthop *nh)
अणु
	अगर (refcount_dec_and_test(&nh->refcnt))
		call_rcu(&nh->rcu, nexthop_मुक्त_rcu);
पूर्ण

अटल अंतरभूत bool nexthop_cmp(स्थिर काष्ठा nexthop *nh1,
			       स्थिर काष्ठा nexthop *nh2)
अणु
	वापस nh1 == nh2;
पूर्ण

अटल अंतरभूत bool nexthop_is_fdb(स्थिर काष्ठा nexthop *nh)
अणु
	अगर (nh->is_group) अणु
		स्थिर काष्ठा nh_group *nh_grp;

		nh_grp = rcu_dereference_rtnl(nh->nh_grp);
		वापस nh_grp->fdb_nh;
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा nh_info *nhi;

		nhi = rcu_dereference_rtnl(nh->nh_info);
		वापस nhi->fdb_nh;
	पूर्ण
पूर्ण

अटल अंतरभूत bool nexthop_has_v4(स्थिर काष्ठा nexthop *nh)
अणु
	अगर (nh->is_group) अणु
		काष्ठा nh_group *nh_grp;

		nh_grp = rcu_dereference_rtnl(nh->nh_grp);
		वापस nh_grp->has_v4;
	पूर्ण
	वापस false;
पूर्ण

अटल अंतरभूत bool nexthop_is_multipath(स्थिर काष्ठा nexthop *nh)
अणु
	अगर (nh->is_group) अणु
		काष्ठा nh_group *nh_grp;

		nh_grp = rcu_dereference_rtnl(nh->nh_grp);
		वापस nh_grp->is_multipath;
	पूर्ण
	वापस false;
पूर्ण

काष्ठा nexthop *nexthop_select_path(काष्ठा nexthop *nh, पूर्णांक hash);

अटल अंतरभूत अचिन्हित पूर्णांक nexthop_num_path(स्थिर काष्ठा nexthop *nh)
अणु
	अचिन्हित पूर्णांक rc = 1;

	अगर (nh->is_group) अणु
		काष्ठा nh_group *nh_grp;

		nh_grp = rcu_dereference_rtnl(nh->nh_grp);
		अगर (nh_grp->is_multipath)
			rc = nh_grp->num_nh;
	पूर्ण

	वापस rc;
पूर्ण

अटल अंतरभूत
काष्ठा nexthop *nexthop_mpath_select(स्थिर काष्ठा nh_group *nhg, पूर्णांक nhsel)
अणु
	/* क्रम_nexthops macros in fib_semantics.c grअसल a poपूर्णांकer to
	 * the nexthop beक्रमe checking nhsel
	 */
	अगर (nhsel >= nhg->num_nh)
		वापस शून्य;

	वापस nhg->nh_entries[nhsel].nh;
पूर्ण

अटल अंतरभूत
पूर्णांक nexthop_mpath_fill_node(काष्ठा sk_buff *skb, काष्ठा nexthop *nh,
			    u8 rt_family)
अणु
	काष्ठा nh_group *nhg = rtnl_dereference(nh->nh_grp);
	पूर्णांक i;

	क्रम (i = 0; i < nhg->num_nh; i++) अणु
		काष्ठा nexthop *nhe = nhg->nh_entries[i].nh;
		काष्ठा nh_info *nhi = rcu_dereference_rtnl(nhe->nh_info);
		काष्ठा fib_nh_common *nhc = &nhi->fib_nhc;
		पूर्णांक weight = nhg->nh_entries[i].weight;

		अगर (fib_add_nexthop(skb, nhc, weight, rt_family) < 0)
			वापस -EMSGSIZE;
	पूर्ण

	वापस 0;
पूर्ण

/* called with rcu lock */
अटल अंतरभूत bool nexthop_is_blackhole(स्थिर काष्ठा nexthop *nh)
अणु
	स्थिर काष्ठा nh_info *nhi;

	अगर (nh->is_group) अणु
		काष्ठा nh_group *nh_grp;

		nh_grp = rcu_dereference_rtnl(nh->nh_grp);
		अगर (nh_grp->num_nh > 1)
			वापस false;

		nh = nh_grp->nh_entries[0].nh;
	पूर्ण

	nhi = rcu_dereference_rtnl(nh->nh_info);
	वापस nhi->reject_nh;
पूर्ण

अटल अंतरभूत व्योम nexthop_path_fib_result(काष्ठा fib_result *res, पूर्णांक hash)
अणु
	काष्ठा nh_info *nhi;
	काष्ठा nexthop *nh;

	nh = nexthop_select_path(res->fi->nh, hash);
	nhi = rcu_dereference(nh->nh_info);
	res->nhc = &nhi->fib_nhc;
पूर्ण

/* called with rcu पढ़ो lock or rtnl held */
अटल अंतरभूत
काष्ठा fib_nh_common *nexthop_fib_nhc(काष्ठा nexthop *nh, पूर्णांक nhsel)
अणु
	काष्ठा nh_info *nhi;

	BUILD_BUG_ON(दुरत्व(काष्ठा fib_nh, nh_common) != 0);
	BUILD_BUG_ON(दुरत्व(काष्ठा fib6_nh, nh_common) != 0);

	अगर (nh->is_group) अणु
		काष्ठा nh_group *nh_grp;

		nh_grp = rcu_dereference_rtnl(nh->nh_grp);
		अगर (nh_grp->is_multipath) अणु
			nh = nexthop_mpath_select(nh_grp, nhsel);
			अगर (!nh)
				वापस शून्य;
		पूर्ण
	पूर्ण

	nhi = rcu_dereference_rtnl(nh->nh_info);
	वापस &nhi->fib_nhc;
पूर्ण

/* called from fib_table_lookup with rcu_lock */
अटल अंतरभूत
काष्ठा fib_nh_common *nexthop_get_nhc_lookup(स्थिर काष्ठा nexthop *nh,
					     पूर्णांक fib_flags,
					     स्थिर काष्ठा flowi4 *flp,
					     पूर्णांक *nhsel)
अणु
	काष्ठा nh_info *nhi;

	अगर (nh->is_group) अणु
		काष्ठा nh_group *nhg = rcu_dereference(nh->nh_grp);
		पूर्णांक i;

		क्रम (i = 0; i < nhg->num_nh; i++) अणु
			काष्ठा nexthop *nhe = nhg->nh_entries[i].nh;

			nhi = rcu_dereference(nhe->nh_info);
			अगर (fib_lookup_good_nhc(&nhi->fib_nhc, fib_flags, flp)) अणु
				*nhsel = i;
				वापस &nhi->fib_nhc;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		nhi = rcu_dereference(nh->nh_info);
		अगर (fib_lookup_good_nhc(&nhi->fib_nhc, fib_flags, flp)) अणु
			*nhsel = 0;
			वापस &nhi->fib_nhc;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल अंतरभूत bool nexthop_uses_dev(स्थिर काष्ठा nexthop *nh,
				    स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा nh_info *nhi;

	अगर (nh->is_group) अणु
		काष्ठा nh_group *nhg = rcu_dereference(nh->nh_grp);
		पूर्णांक i;

		क्रम (i = 0; i < nhg->num_nh; i++) अणु
			काष्ठा nexthop *nhe = nhg->nh_entries[i].nh;

			nhi = rcu_dereference(nhe->nh_info);
			अगर (nhc_l3mdev_matches_dev(&nhi->fib_nhc, dev))
				वापस true;
		पूर्ण
	पूर्ण अन्यथा अणु
		nhi = rcu_dereference(nh->nh_info);
		अगर (nhc_l3mdev_matches_dev(&nhi->fib_nhc, dev))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक fib_info_num_path(स्थिर काष्ठा fib_info *fi)
अणु
	अगर (unlikely(fi->nh))
		वापस nexthop_num_path(fi->nh);

	वापस fi->fib_nhs;
पूर्ण

पूर्णांक fib_check_nexthop(काष्ठा nexthop *nh, u8 scope,
		      काष्ठा netlink_ext_ack *extack);

अटल अंतरभूत काष्ठा fib_nh_common *fib_info_nhc(काष्ठा fib_info *fi, पूर्णांक nhsel)
अणु
	अगर (unlikely(fi->nh))
		वापस nexthop_fib_nhc(fi->nh, nhsel);

	वापस &fi->fib_nh[nhsel].nh_common;
पूर्ण

/* only used when fib_nh is built पूर्णांकo fib_info */
अटल अंतरभूत काष्ठा fib_nh *fib_info_nh(काष्ठा fib_info *fi, पूर्णांक nhsel)
अणु
	WARN_ON(fi->nh);

	वापस &fi->fib_nh[nhsel];
पूर्ण

/*
 * IPv6 variants
 */
पूर्णांक fib6_check_nexthop(काष्ठा nexthop *nh, काष्ठा fib6_config *cfg,
		       काष्ठा netlink_ext_ack *extack);

/* Caller should either hold rcu_पढ़ो_lock(), or RTNL. */
अटल अंतरभूत काष्ठा fib6_nh *nexthop_fib6_nh(काष्ठा nexthop *nh)
अणु
	काष्ठा nh_info *nhi;

	अगर (nh->is_group) अणु
		काष्ठा nh_group *nh_grp;

		nh_grp = rcu_dereference_rtnl(nh->nh_grp);
		nh = nexthop_mpath_select(nh_grp, 0);
		अगर (!nh)
			वापस शून्य;
	पूर्ण

	nhi = rcu_dereference_rtnl(nh->nh_info);
	अगर (nhi->family == AF_INET6)
		वापस &nhi->fib6_nh;

	वापस शून्य;
पूर्ण

/* Variant of nexthop_fib6_nh().
 * Caller should either hold rcu_पढ़ो_lock_bh(), or RTNL.
 */
अटल अंतरभूत काष्ठा fib6_nh *nexthop_fib6_nh_bh(काष्ठा nexthop *nh)
अणु
	काष्ठा nh_info *nhi;

	अगर (nh->is_group) अणु
		काष्ठा nh_group *nh_grp;

		nh_grp = rcu_dereference_bh_rtnl(nh->nh_grp);
		nh = nexthop_mpath_select(nh_grp, 0);
		अगर (!nh)
			वापस शून्य;
	पूर्ण

	nhi = rcu_dereference_bh_rtnl(nh->nh_info);
	अगर (nhi->family == AF_INET6)
		वापस &nhi->fib6_nh;

	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा net_device *fib6_info_nh_dev(काष्ठा fib6_info *f6i)
अणु
	काष्ठा fib6_nh *fib6_nh;

	fib6_nh = f6i->nh ? nexthop_fib6_nh(f6i->nh) : f6i->fib6_nh;
	वापस fib6_nh->fib_nh_dev;
पूर्ण

अटल अंतरभूत व्योम nexthop_path_fib6_result(काष्ठा fib6_result *res, पूर्णांक hash)
अणु
	काष्ठा nexthop *nh = res->f6i->nh;
	काष्ठा nh_info *nhi;

	nh = nexthop_select_path(nh, hash);

	nhi = rcu_dereference_rtnl(nh->nh_info);
	अगर (nhi->reject_nh) अणु
		res->fib6_type = RTN_BLACKHOLE;
		res->fib6_flags |= RTF_REJECT;
		res->nh = nexthop_fib6_nh(nh);
	पूर्ण अन्यथा अणु
		res->nh = &nhi->fib6_nh;
	पूर्ण
पूर्ण

पूर्णांक nexthop_क्रम_each_fib6_nh(काष्ठा nexthop *nh,
			     पूर्णांक (*cb)(काष्ठा fib6_nh *nh, व्योम *arg),
			     व्योम *arg);

अटल अंतरभूत पूर्णांक nexthop_get_family(काष्ठा nexthop *nh)
अणु
	काष्ठा nh_info *nhi = rcu_dereference_rtnl(nh->nh_info);

	वापस nhi->family;
पूर्ण

अटल अंतरभूत
काष्ठा fib_nh_common *nexthop_fdb_nhc(काष्ठा nexthop *nh)
अणु
	काष्ठा nh_info *nhi = rcu_dereference_rtnl(nh->nh_info);

	वापस &nhi->fib_nhc;
पूर्ण

अटल अंतरभूत काष्ठा fib_nh_common *nexthop_path_fdb_result(काष्ठा nexthop *nh,
							    पूर्णांक hash)
अणु
	काष्ठा nh_info *nhi;
	काष्ठा nexthop *nhp;

	nhp = nexthop_select_path(nh, hash);
	अगर (unlikely(!nhp))
		वापस शून्य;
	nhi = rcu_dereference(nhp->nh_info);
	वापस &nhi->fib_nhc;
पूर्ण
#पूर्ण_अगर
