<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * ipv6 in net namespaces
 */

#समावेश <net/inet_frag.h>

#अगर_अघोषित __NETNS_IPV6_H__
#घोषणा __NETNS_IPV6_H__
#समावेश <net/dst_ops.h>
#समावेश <uapi/linux/icmpv6.h>

काष्ठा ctl_table_header;

काष्ठा netns_sysctl_ipv6 अणु
#अगर_घोषित CONFIG_SYSCTL
	काष्ठा ctl_table_header *hdr;
	काष्ठा ctl_table_header *route_hdr;
	काष्ठा ctl_table_header *icmp_hdr;
	काष्ठा ctl_table_header *frags_hdr;
	काष्ठा ctl_table_header *xfrm6_hdr;
#पूर्ण_अगर
	पूर्णांक flush_delay;
	पूर्णांक ip6_rt_max_size;
	पूर्णांक ip6_rt_gc_min_पूर्णांकerval;
	पूर्णांक ip6_rt_gc_समयout;
	पूर्णांक ip6_rt_gc_पूर्णांकerval;
	पूर्णांक ip6_rt_gc_elasticity;
	पूर्णांक ip6_rt_mtu_expires;
	पूर्णांक ip6_rt_min_advmss;
	u8 bindv6only;
	u8 multipath_hash_policy;
	u8 flowlabel_consistency;
	u8 स्वतः_flowlabels;
	पूर्णांक icmpv6_समय;
	u8 icmpv6_echo_ignore_all;
	u8 icmpv6_echo_ignore_multicast;
	u8 icmpv6_echo_ignore_anycast;
	DECLARE_BITMAP(icmpv6_ratemask, ICMPV6_MSG_MAX + 1);
	अचिन्हित दीर्घ *icmpv6_ratemask_ptr;
	u8 anycast_src_echo_reply;
	u8 ip_nonlocal_bind;
	u8 fwmark_reflect;
	u8 flowlabel_state_ranges;
	पूर्णांक idgen_retries;
	पूर्णांक idgen_delay;
	पूर्णांक flowlabel_reflect;
	पूर्णांक max_dst_opts_cnt;
	पूर्णांक max_hbh_opts_cnt;
	पूर्णांक max_dst_opts_len;
	पूर्णांक max_hbh_opts_len;
	पूर्णांक seg6_flowlabel;
	bool skip_notअगरy_on_dev_करोwn;
	u8 fib_notअगरy_on_flag_change;
पूर्ण;

काष्ठा netns_ipv6 अणु
	/* Keep ip6_dst_ops at the beginning of netns_sysctl_ipv6 */
	काष्ठा dst_ops		ip6_dst_ops;

	काष्ठा netns_sysctl_ipv6 sysctl;
	काष्ठा ipv6_devconf	*devconf_all;
	काष्ठा ipv6_devconf	*devconf_dflt;
	काष्ठा inet_peer_base	*peers;
	काष्ठा fqdir		*fqdir;
	काष्ठा fib6_info	*fib6_null_entry;
	काष्ठा rt6_info		*ip6_null_entry;
	काष्ठा rt6_statistics   *rt6_stats;
	काष्ठा समयr_list       ip6_fib_समयr;
	काष्ठा hlist_head       *fib_table_hash;
	काष्ठा fib6_table       *fib6_मुख्य_tbl;
	काष्ठा list_head	fib6_walkers;
	rwlock_t		fib6_walker_lock;
	spinlock_t		fib6_gc_lock;
	अचिन्हित पूर्णांक		 ip6_rt_gc_expire;
	अचिन्हित दीर्घ		 ip6_rt_last_gc;
#अगर_घोषित CONFIG_IPV6_MULTIPLE_TABLES
	अचिन्हित पूर्णांक		fib6_rules_require_fldissect;
	bool			fib6_has_custom_rules;
#अगर_घोषित CONFIG_IPV6_SUBTREES
	अचिन्हित पूर्णांक		fib6_routes_require_src;
#पूर्ण_अगर
	काष्ठा rt6_info         *ip6_prohibit_entry;
	काष्ठा rt6_info         *ip6_blk_hole_entry;
	काष्ठा fib6_table       *fib6_local_tbl;
	काष्ठा fib_rules_ops    *fib6_rules_ops;
#पूर्ण_अगर
	काष्ठा sock * __percpu	*icmp_sk;
	काष्ठा sock             *ndisc_sk;
	काष्ठा sock             *tcp_sk;
	काष्ठा sock             *igmp_sk;
	काष्ठा sock		*mc_स्वतःjoin_sk;
#अगर_घोषित CONFIG_IPV6_MROUTE
#अगर_अघोषित CONFIG_IPV6_MROUTE_MULTIPLE_TABLES
	काष्ठा mr_table		*mrt6;
#अन्यथा
	काष्ठा list_head	mr6_tables;
	काष्ठा fib_rules_ops	*mr6_rules_ops;
#पूर्ण_अगर
#पूर्ण_अगर
	atomic_t		dev_addr_genid;
	atomic_t		fib6_sernum;
	काष्ठा seg6_pernet_data *seg6_data;
	काष्ठा fib_notअगरier_ops	*notअगरier_ops;
	काष्ठा fib_notअगरier_ops	*ip6mr_notअगरier_ops;
	अचिन्हित पूर्णांक ipmr_seq; /* रक्षित by rtnl_mutex */
	काष्ठा अणु
		काष्ठा hlist_head head;
		spinlock_t	lock;
		u32		seq;
	पूर्ण ip6addrlbl_table;
पूर्ण;

#अगर IS_ENABLED(CONFIG_NF_DEFRAG_IPV6)
काष्ठा netns_nf_frag अणु
	काष्ठा fqdir	*fqdir;
पूर्ण;
#पूर्ण_अगर

#पूर्ण_अगर
