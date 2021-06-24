<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET  is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		Definitions क्रम the Forwarding Inक्रमmation Base.
 *
 * Authors:	A.N.Kuznetsov, <kuznet@ms2.inr.ac.ru>
 */

#अगर_अघोषित _NET_IP_FIB_H
#घोषणा _NET_IP_FIB_H

#समावेश <net/flow.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/rcupdate.h>
#समावेश <net/fib_notअगरier.h>
#समावेश <net/fib_rules.h>
#समावेश <net/inetpeer.h>
#समावेश <linux/percpu.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/refcount.h>

काष्ठा fib_config अणु
	u8			fc_dst_len;
	u8			fc_tos;
	u8			fc_protocol;
	u8			fc_scope;
	u8			fc_type;
	u8			fc_gw_family;
	/* 2 bytes unused */
	u32			fc_table;
	__be32			fc_dst;
	जोड़ अणु
		__be32		fc_gw4;
		काष्ठा in6_addr	fc_gw6;
	पूर्ण;
	पूर्णांक			fc_oअगर;
	u32			fc_flags;
	u32			fc_priority;
	__be32			fc_prefsrc;
	u32			fc_nh_id;
	काष्ठा nlattr		*fc_mx;
	काष्ठा rtnexthop	*fc_mp;
	पूर्णांक			fc_mx_len;
	पूर्णांक			fc_mp_len;
	u32			fc_flow;
	u32			fc_nlflags;
	काष्ठा nl_info		fc_nlinfo;
	काष्ठा nlattr		*fc_encap;
	u16			fc_encap_type;
पूर्ण;

काष्ठा fib_info;
काष्ठा rtable;

काष्ठा fib_nh_exception अणु
	काष्ठा fib_nh_exception __rcu	*fnhe_next;
	पूर्णांक				fnhe_genid;
	__be32				fnhe_daddr;
	u32				fnhe_pmtu;
	bool				fnhe_mtu_locked;
	__be32				fnhe_gw;
	अचिन्हित दीर्घ			fnhe_expires;
	काष्ठा rtable __rcu		*fnhe_rth_input;
	काष्ठा rtable __rcu		*fnhe_rth_output;
	अचिन्हित दीर्घ			fnhe_stamp;
	काष्ठा rcu_head			rcu;
पूर्ण;

काष्ठा fnhe_hash_bucket अणु
	काष्ठा fib_nh_exception __rcu	*chain;
पूर्ण;

#घोषणा FNHE_HASH_SHIFT		11
#घोषणा FNHE_HASH_SIZE		(1 << FNHE_HASH_SHIFT)
#घोषणा FNHE_RECLAIM_DEPTH	5

काष्ठा fib_nh_common अणु
	काष्ठा net_device	*nhc_dev;
	पूर्णांक			nhc_oअगर;
	अचिन्हित अक्षर		nhc_scope;
	u8			nhc_family;
	u8			nhc_gw_family;
	अचिन्हित अक्षर		nhc_flags;
	काष्ठा lwtunnel_state	*nhc_lwtstate;

	जोड़ अणु
		__be32          ipv4;
		काष्ठा in6_addr ipv6;
	पूर्ण nhc_gw;

	पूर्णांक			nhc_weight;
	atomic_t		nhc_upper_bound;

	/* v4 specअगरic, but allows fib6_nh with v4 routes */
	काष्ठा rtable __rcu * __percpu *nhc_pcpu_rth_output;
	काष्ठा rtable __rcu     *nhc_rth_input;
	काष्ठा fnhe_hash_bucket	__rcu *nhc_exceptions;
पूर्ण;

काष्ठा fib_nh अणु
	काष्ठा fib_nh_common	nh_common;
	काष्ठा hlist_node	nh_hash;
	काष्ठा fib_info		*nh_parent;
#अगर_घोषित CONFIG_IP_ROUTE_CLASSID
	__u32			nh_tclassid;
#पूर्ण_अगर
	__be32			nh_saddr;
	पूर्णांक			nh_saddr_genid;
#घोषणा fib_nh_family		nh_common.nhc_family
#घोषणा fib_nh_dev		nh_common.nhc_dev
#घोषणा fib_nh_oअगर		nh_common.nhc_oअगर
#घोषणा fib_nh_flags		nh_common.nhc_flags
#घोषणा fib_nh_lws		nh_common.nhc_lwtstate
#घोषणा fib_nh_scope		nh_common.nhc_scope
#घोषणा fib_nh_gw_family	nh_common.nhc_gw_family
#घोषणा fib_nh_gw4		nh_common.nhc_gw.ipv4
#घोषणा fib_nh_gw6		nh_common.nhc_gw.ipv6
#घोषणा fib_nh_weight		nh_common.nhc_weight
#घोषणा fib_nh_upper_bound	nh_common.nhc_upper_bound
पूर्ण;

/*
 * This काष्ठाure contains data shared by many of routes.
 */

काष्ठा nexthop;

काष्ठा fib_info अणु
	काष्ठा hlist_node	fib_hash;
	काष्ठा hlist_node	fib_lhash;
	काष्ठा list_head	nh_list;
	काष्ठा net		*fib_net;
	पूर्णांक			fib_treeref;
	refcount_t		fib_clntref;
	अचिन्हित पूर्णांक		fib_flags;
	अचिन्हित अक्षर		fib_dead;
	अचिन्हित अक्षर		fib_protocol;
	अचिन्हित अक्षर		fib_scope;
	अचिन्हित अक्षर		fib_type;
	__be32			fib_prefsrc;
	u32			fib_tb_id;
	u32			fib_priority;
	काष्ठा dst_metrics	*fib_metrics;
#घोषणा fib_mtu fib_metrics->metrics[RTAX_MTU-1]
#घोषणा fib_winकरोw fib_metrics->metrics[RTAX_WINDOW-1]
#घोषणा fib_rtt fib_metrics->metrics[RTAX_RTT-1]
#घोषणा fib_advmss fib_metrics->metrics[RTAX_ADVMSS-1]
	पूर्णांक			fib_nhs;
	bool			fib_nh_is_v6;
	bool			nh_updated;
	काष्ठा nexthop		*nh;
	काष्ठा rcu_head		rcu;
	काष्ठा fib_nh		fib_nh[];
पूर्ण;


#अगर_घोषित CONFIG_IP_MULTIPLE_TABLES
काष्ठा fib_rule;
#पूर्ण_अगर

काष्ठा fib_table;
काष्ठा fib_result अणु
	__be32			prefix;
	अचिन्हित अक्षर		prefixlen;
	अचिन्हित अक्षर		nh_sel;
	अचिन्हित अक्षर		type;
	अचिन्हित अक्षर		scope;
	u32			tclassid;
	काष्ठा fib_nh_common	*nhc;
	काष्ठा fib_info		*fi;
	काष्ठा fib_table	*table;
	काष्ठा hlist_head	*fa_head;
पूर्ण;

काष्ठा fib_result_nl अणु
	__be32		fl_addr;   /* To be looked up*/
	u32		fl_mark;
	अचिन्हित अक्षर	fl_tos;
	अचिन्हित अक्षर   fl_scope;
	अचिन्हित अक्षर   tb_id_in;

	अचिन्हित अक्षर   tb_id;      /* Results */
	अचिन्हित अक्षर	prefixlen;
	अचिन्हित अक्षर	nh_sel;
	अचिन्हित अक्षर	type;
	अचिन्हित अक्षर	scope;
	पूर्णांक             err;
पूर्ण;

#अगर_घोषित CONFIG_IP_MULTIPLE_TABLES
#घोषणा FIB_TABLE_HASHSZ 256
#अन्यथा
#घोषणा FIB_TABLE_HASHSZ 2
#पूर्ण_अगर

__be32 fib_info_update_nhc_saddr(काष्ठा net *net, काष्ठा fib_nh_common *nhc,
				 अचिन्हित अक्षर scope);
__be32 fib_result_prefsrc(काष्ठा net *net, काष्ठा fib_result *res);

#घोषणा FIB_RES_NHC(res)		((res).nhc)
#घोषणा FIB_RES_DEV(res)	(FIB_RES_NHC(res)->nhc_dev)
#घोषणा FIB_RES_OIF(res)	(FIB_RES_NHC(res)->nhc_oअगर)

काष्ठा fib_rt_info अणु
	काष्ठा fib_info		*fi;
	u32			tb_id;
	__be32			dst;
	पूर्णांक			dst_len;
	u8			tos;
	u8			type;
	u8			offload:1,
				trap:1,
				offload_failed:1,
				unused:5;
पूर्ण;

काष्ठा fib_entry_notअगरier_info अणु
	काष्ठा fib_notअगरier_info info; /* must be first */
	u32 dst;
	पूर्णांक dst_len;
	काष्ठा fib_info *fi;
	u8 tos;
	u8 type;
	u32 tb_id;
पूर्ण;

काष्ठा fib_nh_notअगरier_info अणु
	काष्ठा fib_notअगरier_info info; /* must be first */
	काष्ठा fib_nh *fib_nh;
पूर्ण;

पूर्णांक call_fib4_notअगरier(काष्ठा notअगरier_block *nb,
		       क्रमागत fib_event_type event_type,
		       काष्ठा fib_notअगरier_info *info);
पूर्णांक call_fib4_notअगरiers(काष्ठा net *net, क्रमागत fib_event_type event_type,
			काष्ठा fib_notअगरier_info *info);

पूर्णांक __net_init fib4_notअगरier_init(काष्ठा net *net);
व्योम __net_निकास fib4_notअगरier_निकास(काष्ठा net *net);

व्योम fib_info_notअगरy_update(काष्ठा net *net, काष्ठा nl_info *info);
पूर्णांक fib_notअगरy(काष्ठा net *net, काष्ठा notअगरier_block *nb,
	       काष्ठा netlink_ext_ack *extack);

काष्ठा fib_table अणु
	काष्ठा hlist_node	tb_hlist;
	u32			tb_id;
	पूर्णांक			tb_num_शेष;
	काष्ठा rcu_head		rcu;
	अचिन्हित दीर्घ 		*tb_data;
	अचिन्हित दीर्घ		__data[];
पूर्ण;

काष्ठा fib_dump_filter अणु
	u32			table_id;
	/* filter_set is an optimization that an entry is set */
	bool			filter_set;
	bool			dump_routes;
	bool			dump_exceptions;
	अचिन्हित अक्षर		protocol;
	अचिन्हित अक्षर		rt_type;
	अचिन्हित पूर्णांक		flags;
	काष्ठा net_device	*dev;
पूर्ण;

पूर्णांक fib_table_lookup(काष्ठा fib_table *tb, स्थिर काष्ठा flowi4 *flp,
		     काष्ठा fib_result *res, पूर्णांक fib_flags);
पूर्णांक fib_table_insert(काष्ठा net *, काष्ठा fib_table *, काष्ठा fib_config *,
		     काष्ठा netlink_ext_ack *extack);
पूर्णांक fib_table_delete(काष्ठा net *, काष्ठा fib_table *, काष्ठा fib_config *,
		     काष्ठा netlink_ext_ack *extack);
पूर्णांक fib_table_dump(काष्ठा fib_table *table, काष्ठा sk_buff *skb,
		   काष्ठा netlink_callback *cb, काष्ठा fib_dump_filter *filter);
पूर्णांक fib_table_flush(काष्ठा net *net, काष्ठा fib_table *table, bool flush_all);
काष्ठा fib_table *fib_trie_unmerge(काष्ठा fib_table *मुख्य_tb);
व्योम fib_table_flush_बाह्यal(काष्ठा fib_table *table);
व्योम fib_मुक्त_table(काष्ठा fib_table *tb);

#अगर_अघोषित CONFIG_IP_MULTIPLE_TABLES

#घोषणा TABLE_LOCAL_INDEX	(RT_TABLE_LOCAL & (FIB_TABLE_HASHSZ - 1))
#घोषणा TABLE_MAIN_INDEX	(RT_TABLE_MAIN  & (FIB_TABLE_HASHSZ - 1))

अटल अंतरभूत काष्ठा fib_table *fib_get_table(काष्ठा net *net, u32 id)
अणु
	काष्ठा hlist_node *tb_hlist;
	काष्ठा hlist_head *ptr;

	ptr = id == RT_TABLE_LOCAL ?
		&net->ipv4.fib_table_hash[TABLE_LOCAL_INDEX] :
		&net->ipv4.fib_table_hash[TABLE_MAIN_INDEX];

	tb_hlist = rcu_dereference_rtnl(hlist_first_rcu(ptr));

	वापस hlist_entry(tb_hlist, काष्ठा fib_table, tb_hlist);
पूर्ण

अटल अंतरभूत काष्ठा fib_table *fib_new_table(काष्ठा net *net, u32 id)
अणु
	वापस fib_get_table(net, id);
पूर्ण

अटल अंतरभूत पूर्णांक fib_lookup(काष्ठा net *net, स्थिर काष्ठा flowi4 *flp,
			     काष्ठा fib_result *res, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा fib_table *tb;
	पूर्णांक err = -ENETUNREACH;

	rcu_पढ़ो_lock();

	tb = fib_get_table(net, RT_TABLE_MAIN);
	अगर (tb)
		err = fib_table_lookup(tb, flp, res, flags | FIB_LOOKUP_NOREF);

	अगर (err == -EAGAIN)
		err = -ENETUNREACH;

	rcu_पढ़ो_unlock();

	वापस err;
पूर्ण

अटल अंतरभूत bool fib4_has_custom_rules(स्थिर काष्ठा net *net)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool fib4_rule_शेष(स्थिर काष्ठा fib_rule *rule)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत पूर्णांक fib4_rules_dump(काष्ठा net *net, काष्ठा notअगरier_block *nb,
				  काष्ठा netlink_ext_ack *extack)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक fib4_rules_seq_पढ़ो(काष्ठा net *net)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत bool fib4_rules_early_flow_dissect(काष्ठा net *net,
						 काष्ठा sk_buff *skb,
						 काष्ठा flowi4 *fl4,
						 काष्ठा flow_keys *flkeys)
अणु
	वापस false;
पूर्ण
#अन्यथा /* CONFIG_IP_MULTIPLE_TABLES */
पूर्णांक __net_init fib4_rules_init(काष्ठा net *net);
व्योम __net_निकास fib4_rules_निकास(काष्ठा net *net);

काष्ठा fib_table *fib_new_table(काष्ठा net *net, u32 id);
काष्ठा fib_table *fib_get_table(काष्ठा net *net, u32 id);

पूर्णांक __fib_lookup(काष्ठा net *net, काष्ठा flowi4 *flp,
		 काष्ठा fib_result *res, अचिन्हित पूर्णांक flags);

अटल अंतरभूत पूर्णांक fib_lookup(काष्ठा net *net, काष्ठा flowi4 *flp,
			     काष्ठा fib_result *res, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा fib_table *tb;
	पूर्णांक err = -ENETUNREACH;

	flags |= FIB_LOOKUP_NOREF;
	अगर (net->ipv4.fib_has_custom_rules)
		वापस __fib_lookup(net, flp, res, flags);

	rcu_पढ़ो_lock();

	res->tclassid = 0;

	tb = rcu_dereference_rtnl(net->ipv4.fib_मुख्य);
	अगर (tb)
		err = fib_table_lookup(tb, flp, res, flags);

	अगर (!err)
		जाओ out;

	tb = rcu_dereference_rtnl(net->ipv4.fib_शेष);
	अगर (tb)
		err = fib_table_lookup(tb, flp, res, flags);

out:
	अगर (err == -EAGAIN)
		err = -ENETUNREACH;

	rcu_पढ़ो_unlock();

	वापस err;
पूर्ण

अटल अंतरभूत bool fib4_has_custom_rules(स्थिर काष्ठा net *net)
अणु
	वापस net->ipv4.fib_has_custom_rules;
पूर्ण

bool fib4_rule_शेष(स्थिर काष्ठा fib_rule *rule);
पूर्णांक fib4_rules_dump(काष्ठा net *net, काष्ठा notअगरier_block *nb,
		    काष्ठा netlink_ext_ack *extack);
अचिन्हित पूर्णांक fib4_rules_seq_पढ़ो(काष्ठा net *net);

अटल अंतरभूत bool fib4_rules_early_flow_dissect(काष्ठा net *net,
						 काष्ठा sk_buff *skb,
						 काष्ठा flowi4 *fl4,
						 काष्ठा flow_keys *flkeys)
अणु
	अचिन्हित पूर्णांक flag = FLOW_DISSECTOR_F_STOP_AT_ENCAP;

	अगर (!net->ipv4.fib_rules_require_fldissect)
		वापस false;

	skb_flow_dissect_flow_keys(skb, flkeys, flag);
	fl4->fl4_sport = flkeys->ports.src;
	fl4->fl4_dport = flkeys->ports.dst;
	fl4->flowi4_proto = flkeys->basic.ip_proto;

	वापस true;
पूर्ण

#पूर्ण_अगर /* CONFIG_IP_MULTIPLE_TABLES */

/* Exported by fib_frontend.c */
बाह्य स्थिर काष्ठा nla_policy rपंचांग_ipv4_policy[];
व्योम ip_fib_init(व्योम);
पूर्णांक fib_gw_from_via(काष्ठा fib_config *cfg, काष्ठा nlattr *nla,
		    काष्ठा netlink_ext_ack *extack);
__be32 fib_compute_spec_dst(काष्ठा sk_buff *skb);
bool fib_info_nh_uses_dev(काष्ठा fib_info *fi, स्थिर काष्ठा net_device *dev);
पूर्णांक fib_validate_source(काष्ठा sk_buff *skb, __be32 src, __be32 dst,
			u8 tos, पूर्णांक oअगर, काष्ठा net_device *dev,
			काष्ठा in_device *idev, u32 *itag);
#अगर_घोषित CONFIG_IP_ROUTE_CLASSID
अटल अंतरभूत पूर्णांक fib_num_tclassid_users(काष्ठा net *net)
अणु
	वापस net->ipv4.fib_num_tclassid_users;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक fib_num_tclassid_users(काष्ठा net *net)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर
पूर्णांक fib_unmerge(काष्ठा net *net);

अटल अंतरभूत bool nhc_l3mdev_matches_dev(स्थिर काष्ठा fib_nh_common *nhc,
स्थिर काष्ठा net_device *dev)
अणु
	अगर (nhc->nhc_dev == dev ||
	    l3mdev_master_अगरindex_rcu(nhc->nhc_dev) == dev->अगरindex)
		वापस true;

	वापस false;
पूर्ण

/* Exported by fib_semantics.c */
पूर्णांक ip_fib_check_शेष(__be32 gw, काष्ठा net_device *dev);
पूर्णांक fib_sync_करोwn_dev(काष्ठा net_device *dev, अचिन्हित दीर्घ event, bool क्रमce);
पूर्णांक fib_sync_करोwn_addr(काष्ठा net_device *dev, __be32 local);
पूर्णांक fib_sync_up(काष्ठा net_device *dev, अचिन्हित अक्षर nh_flags);
व्योम fib_sync_mtu(काष्ठा net_device *dev, u32 orig_mtu);
व्योम fib_nhc_update_mtu(काष्ठा fib_nh_common *nhc, u32 new, u32 orig);

#अगर_घोषित CONFIG_IP_ROUTE_MULTIPATH
पूर्णांक fib_multipath_hash(स्थिर काष्ठा net *net, स्थिर काष्ठा flowi4 *fl4,
		       स्थिर काष्ठा sk_buff *skb, काष्ठा flow_keys *flkeys);
#पूर्ण_अगर
पूर्णांक fib_check_nh(काष्ठा net *net, काष्ठा fib_nh *nh, u32 table, u8 scope,
		 काष्ठा netlink_ext_ack *extack);
व्योम fib_select_multipath(काष्ठा fib_result *res, पूर्णांक hash);
व्योम fib_select_path(काष्ठा net *net, काष्ठा fib_result *res,
		     काष्ठा flowi4 *fl4, स्थिर काष्ठा sk_buff *skb);

पूर्णांक fib_nh_init(काष्ठा net *net, काष्ठा fib_nh *fib_nh,
		काष्ठा fib_config *cfg, पूर्णांक nh_weight,
		काष्ठा netlink_ext_ack *extack);
व्योम fib_nh_release(काष्ठा net *net, काष्ठा fib_nh *fib_nh);
पूर्णांक fib_nh_common_init(काष्ठा net *net, काष्ठा fib_nh_common *nhc,
		       काष्ठा nlattr *fc_encap, u16 fc_encap_type,
		       व्योम *cfg, gfp_t gfp_flags,
		       काष्ठा netlink_ext_ack *extack);
व्योम fib_nh_common_release(काष्ठा fib_nh_common *nhc);

/* Exported by fib_trie.c */
व्योम fib_alias_hw_flags_set(काष्ठा net *net, स्थिर काष्ठा fib_rt_info *fri);
व्योम fib_trie_init(व्योम);
काष्ठा fib_table *fib_trie_table(u32 id, काष्ठा fib_table *alias);
bool fib_lookup_good_nhc(स्थिर काष्ठा fib_nh_common *nhc, पूर्णांक fib_flags,
			 स्थिर काष्ठा flowi4 *flp);

अटल अंतरभूत व्योम fib_combine_itag(u32 *itag, स्थिर काष्ठा fib_result *res)
अणु
#अगर_घोषित CONFIG_IP_ROUTE_CLASSID
	काष्ठा fib_nh_common *nhc = res->nhc;
#अगर_घोषित CONFIG_IP_MULTIPLE_TABLES
	u32 rtag;
#पूर्ण_अगर
	अगर (nhc->nhc_family == AF_INET) अणु
		काष्ठा fib_nh *nh;

		nh = container_of(nhc, काष्ठा fib_nh, nh_common);
		*itag = nh->nh_tclassid << 16;
	पूर्ण अन्यथा अणु
		*itag = 0;
	पूर्ण

#अगर_घोषित CONFIG_IP_MULTIPLE_TABLES
	rtag = res->tclassid;
	अगर (*itag == 0)
		*itag = (rtag<<16);
	*itag |= (rtag>>16);
#पूर्ण_अगर
#पूर्ण_अगर
पूर्ण

व्योम fib_flush(काष्ठा net *net);
व्योम मुक्त_fib_info(काष्ठा fib_info *fi);

अटल अंतरभूत व्योम fib_info_hold(काष्ठा fib_info *fi)
अणु
	refcount_inc(&fi->fib_clntref);
पूर्ण

अटल अंतरभूत व्योम fib_info_put(काष्ठा fib_info *fi)
अणु
	अगर (refcount_dec_and_test(&fi->fib_clntref))
		मुक्त_fib_info(fi);
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
पूर्णांक __net_init fib_proc_init(काष्ठा net *net);
व्योम __net_निकास fib_proc_निकास(काष्ठा net *net);
#अन्यथा
अटल अंतरभूत पूर्णांक fib_proc_init(काष्ठा net *net)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम fib_proc_निकास(काष्ठा net *net)
अणु
पूर्ण
#पूर्ण_अगर

u32 ip_mtu_from_fib_result(काष्ठा fib_result *res, __be32 daddr);

पूर्णांक ip_valid_fib_dump_req(काष्ठा net *net, स्थिर काष्ठा nlmsghdr *nlh,
			  काष्ठा fib_dump_filter *filter,
			  काष्ठा netlink_callback *cb);

पूर्णांक fib_nexthop_info(काष्ठा sk_buff *skb, स्थिर काष्ठा fib_nh_common *nh,
		     u8 rt_family, अचिन्हित अक्षर *flags, bool skip_oअगर);
पूर्णांक fib_add_nexthop(काष्ठा sk_buff *skb, स्थिर काष्ठा fib_nh_common *nh,
		    पूर्णांक nh_weight, u8 rt_family);
#पूर्ण_अगर  /* _NET_FIB_H */
