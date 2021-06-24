<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *	Linux ethernet bridge
 *
 *	Authors:
 *	Lennert Buytenhek		<buytenh@gnu.org>
 */

#अगर_अघोषित _BR_PRIVATE_H
#घोषणा _BR_PRIVATE_H

#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_bridge.h>
#समावेश <linux/netpoll.h>
#समावेश <linux/u64_stats_sync.h>
#समावेश <net/route.h>
#समावेश <net/ip6_fib.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/rhashtable.h>
#समावेश <linux/refcount.h>

#घोषणा BR_HASH_BITS 8
#घोषणा BR_HASH_SIZE (1 << BR_HASH_BITS)

#घोषणा BR_HOLD_TIME (1*HZ)

#घोषणा BR_PORT_BITS	10
#घोषणा BR_MAX_PORTS	(1<<BR_PORT_BITS)

#घोषणा BR_MULTICAST_DEFAULT_HASH_MAX 4096

#घोषणा BR_VERSION	"2.3"

/* Control of क्रमwarding link local multicast */
#घोषणा BR_GROUPFWD_DEFAULT	0
/* Don't allow क्रमwarding of control protocols like STP, MAC PAUSE and LACP */
क्रमागत अणु
	BR_GROUPFWD_STP		= BIT(0),
	BR_GROUPFWD_MACPAUSE	= BIT(1),
	BR_GROUPFWD_LACP	= BIT(2),
पूर्ण;

#घोषणा BR_GROUPFWD_RESTRICTED (BR_GROUPFWD_STP | BR_GROUPFWD_MACPAUSE | \
				BR_GROUPFWD_LACP)
/* The Nearest Customer Bridge Group Address, 01-80-C2-00-00-[00,0B,0C,0D,0F] */
#घोषणा BR_GROUPFWD_8021AD	0xB801u

/* Path to usermode spanning tree program */
#घोषणा BR_STP_PROG	"/sbin/bridge-stp"

#घोषणा BR_FDB_NOTIFY_SETTABLE_BITS (FDB_NOTIFY_BIT | FDB_NOTIFY_INACTIVE_BIT)

प्रकार काष्ठा bridge_id bridge_id;
प्रकार काष्ठा mac_addr mac_addr;
प्रकार __u16 port_id;

काष्ठा bridge_id अणु
	अचिन्हित अक्षर	prio[2];
	अचिन्हित अक्षर	addr[ETH_ALEN];
पूर्ण;

काष्ठा mac_addr अणु
	अचिन्हित अक्षर	addr[ETH_ALEN];
पूर्ण;

#अगर_घोषित CONFIG_BRIDGE_IGMP_SNOOPING
/* our own querier */
काष्ठा bridge_mcast_own_query अणु
	काष्ठा समयr_list	समयr;
	u32			startup_sent;
पूर्ण;

/* other querier */
काष्ठा bridge_mcast_other_query अणु
	काष्ठा समयr_list		समयr;
	अचिन्हित दीर्घ			delay_समय;
पूर्ण;

/* selected querier */
काष्ठा bridge_mcast_querier अणु
	काष्ठा br_ip addr;
	काष्ठा net_bridge_port __rcu	*port;
पूर्ण;

/* IGMP/MLD statistics */
काष्ठा bridge_mcast_stats अणु
	काष्ठा br_mcast_stats mstats;
	काष्ठा u64_stats_sync syncp;
पूर्ण;
#पूर्ण_अगर

काष्ठा br_tunnel_info अणु
	__be64				tunnel_id;
	काष्ठा metadata_dst __rcu	*tunnel_dst;
पूर्ण;

/* निजी vlan flags */
क्रमागत अणु
	BR_VLFLAG_PER_PORT_STATS = BIT(0),
	BR_VLFLAG_ADDED_BY_SWITCHDEV = BIT(1),
पूर्ण;

/**
 * काष्ठा net_bridge_vlan - per-vlan entry
 *
 * @vnode: rhashtable member
 * @vid: VLAN id
 * @flags: bridge vlan flags
 * @priv_flags: निजी (in-kernel) bridge vlan flags
 * @state: STP state (e.g. blocking, learning, क्रमwarding)
 * @stats: per-cpu VLAN statistics
 * @br: अगर MASTER flag set, this poपूर्णांकs to a bridge काष्ठा
 * @port: अगर MASTER flag unset, this poपूर्णांकs to a port काष्ठा
 * @refcnt: अगर MASTER flag set, this is bumped क्रम each port referencing it
 * @brvlan: अगर MASTER flag unset, this poपूर्णांकs to the global per-VLAN context
 *          क्रम this VLAN entry
 * @vlist: sorted list of VLAN entries
 * @rcu: used क्रम entry deकाष्ठाion
 *
 * This काष्ठाure is shared between the global per-VLAN entries contained in
 * the bridge rhashtable and the local per-port per-VLAN entries contained in
 * the port's rhashtable. The जोड़ entries should be पूर्णांकerpreted depending on
 * the entry flags that are set.
 */
काष्ठा net_bridge_vlan अणु
	काष्ठा rhash_head		vnode;
	काष्ठा rhash_head		tnode;
	u16				vid;
	u16				flags;
	u16				priv_flags;
	u8				state;
	काष्ठा pcpu_sw_netstats __percpu *stats;
	जोड़ अणु
		काष्ठा net_bridge	*br;
		काष्ठा net_bridge_port	*port;
	पूर्ण;
	जोड़ अणु
		refcount_t		refcnt;
		काष्ठा net_bridge_vlan	*brvlan;
	पूर्ण;

	काष्ठा br_tunnel_info		tinfo;

	काष्ठा list_head		vlist;

	काष्ठा rcu_head			rcu;
पूर्ण;

/**
 * काष्ठा net_bridge_vlan_group
 *
 * @vlan_hash: VLAN entry rhashtable
 * @vlan_list: sorted VLAN entry list
 * @num_vlans: number of total VLAN entries
 * @pvid: PVID VLAN id
 * @pvid_state: PVID's STP state (e.g. क्रमwarding, learning, blocking)
 *
 * IMPORTANT: Be careful when checking अगर there're VLAN entries using list
 *            primitives because the bridge can have entries in its list which
 *            are just क्रम global context but not क्रम filtering, i.e. they have
 *            the master flag set but not the brentry flag. If you have to check
 *            अगर there're "real" entries in the bridge please test @num_vlans
 */
काष्ठा net_bridge_vlan_group अणु
	काष्ठा rhashtable		vlan_hash;
	काष्ठा rhashtable		tunnel_hash;
	काष्ठा list_head		vlan_list;
	u16				num_vlans;
	u16				pvid;
	u8				pvid_state;
पूर्ण;

/* bridge fdb flags */
क्रमागत अणु
	BR_FDB_LOCAL,
	BR_FDB_STATIC,
	BR_FDB_STICKY,
	BR_FDB_ADDED_BY_USER,
	BR_FDB_ADDED_BY_EXT_LEARN,
	BR_FDB_OFFLOADED,
	BR_FDB_NOTIFY,
	BR_FDB_NOTIFY_INACTIVE
पूर्ण;

काष्ठा net_bridge_fdb_key अणु
	mac_addr addr;
	u16 vlan_id;
पूर्ण;

काष्ठा net_bridge_fdb_entry अणु
	काष्ठा rhash_head		rhnode;
	काष्ठा net_bridge_port		*dst;

	काष्ठा net_bridge_fdb_key	key;
	काष्ठा hlist_node		fdb_node;
	अचिन्हित दीर्घ			flags;

	/* ग_लिखो-heavy members should not affect lookups */
	अचिन्हित दीर्घ			updated ____cacheline_aligned_in_smp;
	अचिन्हित दीर्घ			used;

	काष्ठा rcu_head			rcu;
पूर्ण;

#घोषणा MDB_PG_FLAGS_PERMANENT	BIT(0)
#घोषणा MDB_PG_FLAGS_OFFLOAD	BIT(1)
#घोषणा MDB_PG_FLAGS_FAST_LEAVE	BIT(2)
#घोषणा MDB_PG_FLAGS_STAR_EXCL	BIT(3)
#घोषणा MDB_PG_FLAGS_BLOCKED	BIT(4)

#घोषणा PG_SRC_ENT_LIMIT	32

#घोषणा BR_SGRP_F_DELETE	BIT(0)
#घोषणा BR_SGRP_F_SEND		BIT(1)
#घोषणा BR_SGRP_F_INSTALLED	BIT(2)

काष्ठा net_bridge_mcast_gc अणु
	काष्ठा hlist_node		gc_node;
	व्योम				(*destroy)(काष्ठा net_bridge_mcast_gc *gc);
पूर्ण;

काष्ठा net_bridge_group_src अणु
	काष्ठा hlist_node		node;

	काष्ठा br_ip			addr;
	काष्ठा net_bridge_port_group	*pg;
	u8				flags;
	u8				src_query_rexmit_cnt;
	काष्ठा समयr_list		समयr;

	काष्ठा net_bridge		*br;
	काष्ठा net_bridge_mcast_gc	mcast_gc;
	काष्ठा rcu_head			rcu;
पूर्ण;

काष्ठा net_bridge_port_group_sg_key अणु
	काष्ठा net_bridge_port		*port;
	काष्ठा br_ip			addr;
पूर्ण;

काष्ठा net_bridge_port_group अणु
	काष्ठा net_bridge_port_group __rcu *next;
	काष्ठा net_bridge_port_group_sg_key key;
	अचिन्हित अक्षर			eth_addr[ETH_ALEN] __aligned(2);
	अचिन्हित अक्षर			flags;
	अचिन्हित अक्षर			filter_mode;
	अचिन्हित अक्षर			grp_query_rexmit_cnt;
	अचिन्हित अक्षर			rt_protocol;

	काष्ठा hlist_head		src_list;
	अचिन्हित पूर्णांक			src_ents;
	काष्ठा समयr_list		समयr;
	काष्ठा समयr_list		rexmit_समयr;
	काष्ठा hlist_node		mglist;
	काष्ठा rb_root			eht_set_tree;
	काष्ठा rb_root			eht_host_tree;

	काष्ठा rhash_head		rhnode;
	काष्ठा net_bridge_mcast_gc	mcast_gc;
	काष्ठा rcu_head			rcu;
पूर्ण;

काष्ठा net_bridge_mdb_entry अणु
	काष्ठा rhash_head		rhnode;
	काष्ठा net_bridge		*br;
	काष्ठा net_bridge_port_group __rcu *ports;
	काष्ठा br_ip			addr;
	bool				host_joined;

	काष्ठा समयr_list		समयr;
	काष्ठा hlist_node		mdb_node;

	काष्ठा net_bridge_mcast_gc	mcast_gc;
	काष्ठा rcu_head			rcu;
पूर्ण;

काष्ठा net_bridge_port अणु
	काष्ठा net_bridge		*br;
	काष्ठा net_device		*dev;
	काष्ठा list_head		list;

	अचिन्हित दीर्घ			flags;
#अगर_घोषित CONFIG_BRIDGE_VLAN_FILTERING
	काष्ठा net_bridge_vlan_group	__rcu *vlgrp;
#पूर्ण_अगर
	काष्ठा net_bridge_port		__rcu *backup_port;

	/* STP */
	u8				priority;
	u8				state;
	u16				port_no;
	अचिन्हित अक्षर			topology_change_ack;
	अचिन्हित अक्षर			config_pending;
	port_id				port_id;
	port_id				designated_port;
	bridge_id			designated_root;
	bridge_id			designated_bridge;
	u32				path_cost;
	u32				designated_cost;
	अचिन्हित दीर्घ			designated_age;

	काष्ठा समयr_list		क्रमward_delay_समयr;
	काष्ठा समयr_list		hold_समयr;
	काष्ठा समयr_list		message_age_समयr;
	काष्ठा kobject			kobj;
	काष्ठा rcu_head			rcu;

#अगर_घोषित CONFIG_BRIDGE_IGMP_SNOOPING
	काष्ठा bridge_mcast_own_query	ip4_own_query;
#अगर IS_ENABLED(CONFIG_IPV6)
	काष्ठा bridge_mcast_own_query	ip6_own_query;
#पूर्ण_अगर /* IS_ENABLED(CONFIG_IPV6) */
	u32				multicast_eht_hosts_limit;
	u32				multicast_eht_hosts_cnt;
	अचिन्हित अक्षर			multicast_router;
	काष्ठा bridge_mcast_stats	__percpu *mcast_stats;
	काष्ठा समयr_list		multicast_router_समयr;
	काष्ठा hlist_head		mglist;
	काष्ठा hlist_node		rlist;
#पूर्ण_अगर

#अगर_घोषित CONFIG_SYSFS
	अक्षर				sysfs_name[IFNAMSIZ];
#पूर्ण_अगर

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	काष्ठा netpoll			*np;
#पूर्ण_अगर
#अगर_घोषित CONFIG_NET_SWITCHDEV
	पूर्णांक				offload_fwd_mark;
#पूर्ण_अगर
	u16				group_fwd_mask;
	u16				backup_redirected_cnt;

	काष्ठा bridge_stp_xstats	stp_xstats;
पूर्ण;

#घोषणा kobj_to_brport(obj)	container_of(obj, काष्ठा net_bridge_port, kobj)

#घोषणा br_स्वतः_port(p) ((p)->flags & BR_AUTO_MASK)
#घोषणा br_promisc_port(p) ((p)->flags & BR_PROMISC)

अटल अंतरभूत काष्ठा net_bridge_port *br_port_get_rcu(स्थिर काष्ठा net_device *dev)
अणु
	वापस rcu_dereference(dev->rx_handler_data);
पूर्ण

अटल अंतरभूत काष्ठा net_bridge_port *br_port_get_rtnl(स्थिर काष्ठा net_device *dev)
अणु
	वापस netअगर_is_bridge_port(dev) ?
		rtnl_dereference(dev->rx_handler_data) : शून्य;
पूर्ण

अटल अंतरभूत काष्ठा net_bridge_port *br_port_get_rtnl_rcu(स्थिर काष्ठा net_device *dev)
अणु
	वापस netअगर_is_bridge_port(dev) ?
		rcu_dereference_rtnl(dev->rx_handler_data) : शून्य;
पूर्ण

क्रमागत net_bridge_opts अणु
	BROPT_VLAN_ENABLED,
	BROPT_VLAN_STATS_ENABLED,
	BROPT_NF_CALL_IPTABLES,
	BROPT_NF_CALL_IP6TABLES,
	BROPT_NF_CALL_ARPTABLES,
	BROPT_GROUP_ADDR_SET,
	BROPT_MULTICAST_ENABLED,
	BROPT_MULTICAST_QUERIER,
	BROPT_MULTICAST_QUERY_USE_IFADDR,
	BROPT_MULTICAST_STATS_ENABLED,
	BROPT_HAS_IPV6_ADDR,
	BROPT_NEIGH_SUPPRESS_ENABLED,
	BROPT_MTU_SET_BY_USER,
	BROPT_VLAN_STATS_PER_PORT,
	BROPT_NO_LL_LEARN,
	BROPT_VLAN_BRIDGE_BINDING,
पूर्ण;

काष्ठा net_bridge अणु
	spinlock_t			lock;
	spinlock_t			hash_lock;
	काष्ठा hlist_head		frame_type_list;
	काष्ठा net_device		*dev;
	अचिन्हित दीर्घ			options;
	/* These fields are accessed on each packet */
#अगर_घोषित CONFIG_BRIDGE_VLAN_FILTERING
	__be16				vlan_proto;
	u16				शेष_pvid;
	काष्ठा net_bridge_vlan_group	__rcu *vlgrp;
#पूर्ण_अगर

	काष्ठा rhashtable		fdb_hash_tbl;
	काष्ठा list_head		port_list;
#अगर IS_ENABLED(CONFIG_BRIDGE_NETFILTER)
	जोड़ अणु
		काष्ठा rtable		fake_rtable;
		काष्ठा rt6_info		fake_rt6_info;
	पूर्ण;
#पूर्ण_अगर
	u16				group_fwd_mask;
	u16				group_fwd_mask_required;

	/* STP */
	bridge_id			designated_root;
	bridge_id			bridge_id;
	अचिन्हित अक्षर			topology_change;
	अचिन्हित अक्षर			topology_change_detected;
	u16				root_port;
	अचिन्हित दीर्घ			max_age;
	अचिन्हित दीर्घ			hello_समय;
	अचिन्हित दीर्घ			क्रमward_delay;
	अचिन्हित दीर्घ			ageing_समय;
	अचिन्हित दीर्घ			bridge_max_age;
	अचिन्हित दीर्घ			bridge_hello_समय;
	अचिन्हित दीर्घ			bridge_क्रमward_delay;
	अचिन्हित दीर्घ			bridge_ageing_समय;
	u32				root_path_cost;

	u8				group_addr[ETH_ALEN];

	क्रमागत अणु
		BR_NO_STP, 		/* no spanning tree */
		BR_KERNEL_STP,		/* old STP in kernel */
		BR_USER_STP,		/* new RSTP in userspace */
	पूर्ण stp_enabled;

#अगर_घोषित CONFIG_BRIDGE_IGMP_SNOOPING

	u32				hash_max;

	u32				multicast_last_member_count;
	u32				multicast_startup_query_count;

	u8				multicast_igmp_version;
	u8				multicast_router;
#अगर IS_ENABLED(CONFIG_IPV6)
	u8				multicast_mld_version;
#पूर्ण_अगर
	spinlock_t			multicast_lock;
	अचिन्हित दीर्घ			multicast_last_member_पूर्णांकerval;
	अचिन्हित दीर्घ			multicast_membership_पूर्णांकerval;
	अचिन्हित दीर्घ			multicast_querier_पूर्णांकerval;
	अचिन्हित दीर्घ			multicast_query_पूर्णांकerval;
	अचिन्हित दीर्घ			multicast_query_response_पूर्णांकerval;
	अचिन्हित दीर्घ			multicast_startup_query_पूर्णांकerval;

	काष्ठा rhashtable		mdb_hash_tbl;
	काष्ठा rhashtable		sg_port_tbl;

	काष्ठा hlist_head		mcast_gc_list;
	काष्ठा hlist_head		mdb_list;
	काष्ठा hlist_head		router_list;

	काष्ठा समयr_list		multicast_router_समयr;
	काष्ठा bridge_mcast_other_query	ip4_other_query;
	काष्ठा bridge_mcast_own_query	ip4_own_query;
	काष्ठा bridge_mcast_querier	ip4_querier;
	काष्ठा bridge_mcast_stats	__percpu *mcast_stats;
#अगर IS_ENABLED(CONFIG_IPV6)
	काष्ठा bridge_mcast_other_query	ip6_other_query;
	काष्ठा bridge_mcast_own_query	ip6_own_query;
	काष्ठा bridge_mcast_querier	ip6_querier;
#पूर्ण_अगर /* IS_ENABLED(CONFIG_IPV6) */
	काष्ठा work_काष्ठा		mcast_gc_work;
#पूर्ण_अगर

	काष्ठा समयr_list		hello_समयr;
	काष्ठा समयr_list		tcn_समयr;
	काष्ठा समयr_list		topology_change_समयr;
	काष्ठा delayed_work		gc_work;
	काष्ठा kobject			*अगरobj;
	u32				स्वतः_cnt;

#अगर_घोषित CONFIG_NET_SWITCHDEV
	पूर्णांक offload_fwd_mark;
#पूर्ण_अगर
	काष्ठा hlist_head		fdb_list;

#अगर IS_ENABLED(CONFIG_BRIDGE_MRP)
	काष्ठा hlist_head		mrp_list;
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_BRIDGE_CFM)
	काष्ठा hlist_head		mep_list;
#पूर्ण_अगर
पूर्ण;

काष्ठा br_input_skb_cb अणु
	काष्ठा net_device *brdev;

	u16 frag_max_size;
#अगर_घोषित CONFIG_BRIDGE_IGMP_SNOOPING
	u8 igmp;
	u8 mrouters_only:1;
#पूर्ण_अगर
	u8 proxyarp_replied:1;
	u8 src_port_isolated:1;
#अगर_घोषित CONFIG_BRIDGE_VLAN_FILTERING
	u8 vlan_filtered:1;
#पूर्ण_अगर
#अगर_घोषित CONFIG_NETFILTER_FAMILY_BRIDGE
	u8 br_netfilter_broute:1;
#पूर्ण_अगर

#अगर_घोषित CONFIG_NET_SWITCHDEV
	पूर्णांक offload_fwd_mark;
#पूर्ण_अगर
पूर्ण;

#घोषणा BR_INPUT_SKB_CB(__skb)	((काष्ठा br_input_skb_cb *)(__skb)->cb)

#अगर_घोषित CONFIG_BRIDGE_IGMP_SNOOPING
# define BR_INPUT_SKB_CB_MROUTERS_ONLY(__skb)	(BR_INPUT_SKB_CB(__skb)->mrouters_only)
#अन्यथा
# define BR_INPUT_SKB_CB_MROUTERS_ONLY(__skb)	(0)
#पूर्ण_अगर

#घोषणा br_prपूर्णांकk(level, br, क्रमmat, args...)	\
	prपूर्णांकk(level "%s: " क्रमmat, (br)->dev->name, ##args)

#घोषणा br_err(__br, क्रमmat, args...)			\
	br_prपूर्णांकk(KERN_ERR, __br, क्रमmat, ##args)
#घोषणा br_warn(__br, क्रमmat, args...)			\
	br_prपूर्णांकk(KERN_WARNING, __br, क्रमmat, ##args)
#घोषणा br_notice(__br, क्रमmat, args...)		\
	br_prपूर्णांकk(KERN_NOTICE, __br, क्रमmat, ##args)
#घोषणा br_info(__br, क्रमmat, args...)			\
	br_prपूर्णांकk(KERN_INFO, __br, क्रमmat, ##args)

#घोषणा br_debug(br, क्रमmat, args...)			\
	pr_debug("%s: " क्रमmat,  (br)->dev->name, ##args)

/* called under bridge lock */
अटल अंतरभूत पूर्णांक br_is_root_bridge(स्थिर काष्ठा net_bridge *br)
अणु
	वापस !स_भेद(&br->bridge_id, &br->designated_root, 8);
पूर्ण

/* check अगर a VLAN entry is global */
अटल अंतरभूत bool br_vlan_is_master(स्थिर काष्ठा net_bridge_vlan *v)
अणु
	वापस v->flags & BRIDGE_VLAN_INFO_MASTER;
पूर्ण

/* check अगर a VLAN entry is used by the bridge */
अटल अंतरभूत bool br_vlan_is_brentry(स्थिर काष्ठा net_bridge_vlan *v)
अणु
	वापस v->flags & BRIDGE_VLAN_INFO_BRENTRY;
पूर्ण

/* check अगर we should use the vlan entry, वापसs false अगर it's only context */
अटल अंतरभूत bool br_vlan_should_use(स्थिर काष्ठा net_bridge_vlan *v)
अणु
	अगर (br_vlan_is_master(v)) अणु
		अगर (br_vlan_is_brentry(v))
			वापस true;
		अन्यथा
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल अंतरभूत bool nbp_state_should_learn(स्थिर काष्ठा net_bridge_port *p)
अणु
	वापस p->state == BR_STATE_LEARNING || p->state == BR_STATE_FORWARDING;
पूर्ण

अटल अंतरभूत bool br_vlan_valid_id(u16 vid, काष्ठा netlink_ext_ack *extack)
अणु
	bool ret = vid > 0 && vid < VLAN_VID_MASK;

	अगर (!ret)
		NL_SET_ERR_MSG_MOD(extack, "Vlan id is invalid");

	वापस ret;
पूर्ण

अटल अंतरभूत bool br_vlan_valid_range(स्थिर काष्ठा bridge_vlan_info *cur,
				       स्थिर काष्ठा bridge_vlan_info *last,
				       काष्ठा netlink_ext_ack *extack)
अणु
	/* pvid flag is not allowed in ranges */
	अगर (cur->flags & BRIDGE_VLAN_INFO_PVID) अणु
		NL_SET_ERR_MSG_MOD(extack, "Pvid isn't allowed in a range");
		वापस false;
	पूर्ण

	/* when cur is the range end, check अगर:
	 *  - it has range start flag
	 *  - range ids are invalid (end is equal to or beक्रमe start)
	 */
	अगर (last) अणु
		अगर (cur->flags & BRIDGE_VLAN_INFO_RANGE_BEGIN) अणु
			NL_SET_ERR_MSG_MOD(extack, "Found a new vlan range start while processing one");
			वापस false;
		पूर्ण अन्यथा अगर (!(cur->flags & BRIDGE_VLAN_INFO_RANGE_END)) अणु
			NL_SET_ERR_MSG_MOD(extack, "Vlan range end flag is missing");
			वापस false;
		पूर्ण अन्यथा अगर (cur->vid <= last->vid) अणु
			NL_SET_ERR_MSG_MOD(extack, "End vlan id is less than or equal to start vlan id");
			वापस false;
		पूर्ण
	पूर्ण

	/* check क्रम required range flags */
	अगर (!(cur->flags & (BRIDGE_VLAN_INFO_RANGE_BEGIN |
			    BRIDGE_VLAN_INFO_RANGE_END))) अणु
		NL_SET_ERR_MSG_MOD(extack, "Both vlan range flags are missing");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल अंतरभूत पूर्णांक br_afspec_cmd_to_rपंचांग(पूर्णांक cmd)
अणु
	चयन (cmd) अणु
	हाल RTM_SETLINK:
		वापस RTM_NEWVLAN;
	हाल RTM_DELLINK:
		वापस RTM_DELVLAN;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक br_opt_get(स्थिर काष्ठा net_bridge *br,
			     क्रमागत net_bridge_opts opt)
अणु
	वापस test_bit(opt, &br->options);
पूर्ण

पूर्णांक br_boolopt_toggle(काष्ठा net_bridge *br, क्रमागत br_boolopt_id opt, bool on,
		      काष्ठा netlink_ext_ack *extack);
पूर्णांक br_boolopt_get(स्थिर काष्ठा net_bridge *br, क्रमागत br_boolopt_id opt);
पूर्णांक br_boolopt_multi_toggle(काष्ठा net_bridge *br,
			    काष्ठा br_boolopt_multi *bm,
			    काष्ठा netlink_ext_ack *extack);
व्योम br_boolopt_multi_get(स्थिर काष्ठा net_bridge *br,
			  काष्ठा br_boolopt_multi *bm);
व्योम br_opt_toggle(काष्ठा net_bridge *br, क्रमागत net_bridge_opts opt, bool on);

/* br_device.c */
व्योम br_dev_setup(काष्ठा net_device *dev);
व्योम br_dev_delete(काष्ठा net_device *dev, काष्ठा list_head *list);
netdev_tx_t br_dev_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev);
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल अंतरभूत व्योम br_netpoll_send_skb(स्थिर काष्ठा net_bridge_port *p,
				       काष्ठा sk_buff *skb)
अणु
	netpoll_send_skb(p->np, skb);
पूर्ण

पूर्णांक br_netpoll_enable(काष्ठा net_bridge_port *p);
व्योम br_netpoll_disable(काष्ठा net_bridge_port *p);
#अन्यथा
अटल अंतरभूत व्योम br_netpoll_send_skb(स्थिर काष्ठा net_bridge_port *p,
				       काष्ठा sk_buff *skb)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक br_netpoll_enable(काष्ठा net_bridge_port *p)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम br_netpoll_disable(काष्ठा net_bridge_port *p)
अणु
पूर्ण
#पूर्ण_अगर

/* br_fdb.c */
पूर्णांक br_fdb_init(व्योम);
व्योम br_fdb_fini(व्योम);
पूर्णांक br_fdb_hash_init(काष्ठा net_bridge *br);
व्योम br_fdb_hash_fini(काष्ठा net_bridge *br);
व्योम br_fdb_flush(काष्ठा net_bridge *br);
व्योम br_fdb_find_delete_local(काष्ठा net_bridge *br,
			      स्थिर काष्ठा net_bridge_port *p,
			      स्थिर अचिन्हित अक्षर *addr, u16 vid);
व्योम br_fdb_changeaddr(काष्ठा net_bridge_port *p, स्थिर अचिन्हित अक्षर *newaddr);
व्योम br_fdb_change_mac_address(काष्ठा net_bridge *br, स्थिर u8 *newaddr);
व्योम br_fdb_cleanup(काष्ठा work_काष्ठा *work);
व्योम br_fdb_delete_by_port(काष्ठा net_bridge *br,
			   स्थिर काष्ठा net_bridge_port *p, u16 vid, पूर्णांक करो_all);
काष्ठा net_bridge_fdb_entry *br_fdb_find_rcu(काष्ठा net_bridge *br,
					     स्थिर अचिन्हित अक्षर *addr,
					     __u16 vid);
पूर्णांक br_fdb_test_addr(काष्ठा net_device *dev, अचिन्हित अक्षर *addr);
पूर्णांक br_fdb_fillbuf(काष्ठा net_bridge *br, व्योम *buf, अचिन्हित दीर्घ count,
		   अचिन्हित दीर्घ off);
पूर्णांक br_fdb_insert(काष्ठा net_bridge *br, काष्ठा net_bridge_port *source,
		  स्थिर अचिन्हित अक्षर *addr, u16 vid);
व्योम br_fdb_update(काष्ठा net_bridge *br, काष्ठा net_bridge_port *source,
		   स्थिर अचिन्हित अक्षर *addr, u16 vid, अचिन्हित दीर्घ flags);

पूर्णांक br_fdb_delete(काष्ठा ndmsg *ndm, काष्ठा nlattr *tb[],
		  काष्ठा net_device *dev, स्थिर अचिन्हित अक्षर *addr, u16 vid);
पूर्णांक br_fdb_add(काष्ठा ndmsg *nlh, काष्ठा nlattr *tb[], काष्ठा net_device *dev,
	       स्थिर अचिन्हित अक्षर *addr, u16 vid, u16 nlh_flags,
	       काष्ठा netlink_ext_ack *extack);
पूर्णांक br_fdb_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb,
		काष्ठा net_device *dev, काष्ठा net_device *fdev, पूर्णांक *idx);
पूर्णांक br_fdb_get(काष्ठा sk_buff *skb, काष्ठा nlattr *tb[], काष्ठा net_device *dev,
	       स्थिर अचिन्हित अक्षर *addr, u16 vid, u32 portid, u32 seq,
	       काष्ठा netlink_ext_ack *extack);
पूर्णांक br_fdb_sync_अटल(काष्ठा net_bridge *br, काष्ठा net_bridge_port *p);
व्योम br_fdb_unsync_अटल(काष्ठा net_bridge *br, काष्ठा net_bridge_port *p);
पूर्णांक br_fdb_बाह्यal_learn_add(काष्ठा net_bridge *br, काष्ठा net_bridge_port *p,
			      स्थिर अचिन्हित अक्षर *addr, u16 vid,
			      bool swdev_notअगरy);
पूर्णांक br_fdb_बाह्यal_learn_del(काष्ठा net_bridge *br, काष्ठा net_bridge_port *p,
			      स्थिर अचिन्हित अक्षर *addr, u16 vid,
			      bool swdev_notअगरy);
व्योम br_fdb_offloaded_set(काष्ठा net_bridge *br, काष्ठा net_bridge_port *p,
			  स्थिर अचिन्हित अक्षर *addr, u16 vid, bool offloaded);

/* br_क्रमward.c */
क्रमागत br_pkt_type अणु
	BR_PKT_UNICAST,
	BR_PKT_MULTICAST,
	BR_PKT_BROADCAST
पूर्ण;
पूर्णांक br_dev_queue_push_xmit(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb);
व्योम br_क्रमward(स्थिर काष्ठा net_bridge_port *to, काष्ठा sk_buff *skb,
		bool local_rcv, bool local_orig);
पूर्णांक br_क्रमward_finish(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb);
व्योम br_flood(काष्ठा net_bridge *br, काष्ठा sk_buff *skb,
	      क्रमागत br_pkt_type pkt_type, bool local_rcv, bool local_orig);

/* वापस true अगर both source port and dest port are isolated */
अटल अंतरभूत bool br_skb_isolated(स्थिर काष्ठा net_bridge_port *to,
				   स्थिर काष्ठा sk_buff *skb)
अणु
	वापस BR_INPUT_SKB_CB(skb)->src_port_isolated &&
	       (to->flags & BR_ISOLATED);
पूर्ण

/* br_अगर.c */
व्योम br_port_carrier_check(काष्ठा net_bridge_port *p, bool *notअगरied);
पूर्णांक br_add_bridge(काष्ठा net *net, स्थिर अक्षर *name);
पूर्णांक br_del_bridge(काष्ठा net *net, स्थिर अक्षर *name);
पूर्णांक br_add_अगर(काष्ठा net_bridge *br, काष्ठा net_device *dev,
	      काष्ठा netlink_ext_ack *extack);
पूर्णांक br_del_अगर(काष्ठा net_bridge *br, काष्ठा net_device *dev);
व्योम br_mtu_स्वतः_adjust(काष्ठा net_bridge *br);
netdev_features_t br_features_recompute(काष्ठा net_bridge *br,
					netdev_features_t features);
व्योम br_port_flags_change(काष्ठा net_bridge_port *port, अचिन्हित दीर्घ mask);
व्योम br_manage_promisc(काष्ठा net_bridge *br);
पूर्णांक nbp_backup_change(काष्ठा net_bridge_port *p, काष्ठा net_device *backup_dev);

/* br_input.c */
पूर्णांक br_handle_frame_finish(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb);
rx_handler_func_t *br_get_rx_handler(स्थिर काष्ठा net_device *dev);

काष्ठा br_frame_type अणु
	__be16			type;
	पूर्णांक			(*frame_handler)(काष्ठा net_bridge_port *port,
						 काष्ठा sk_buff *skb);
	काष्ठा hlist_node	list;
पूर्ण;

व्योम br_add_frame(काष्ठा net_bridge *br, काष्ठा br_frame_type *ft);
व्योम br_del_frame(काष्ठा net_bridge *br, काष्ठा br_frame_type *ft);

अटल अंतरभूत bool br_rx_handler_check_rcu(स्थिर काष्ठा net_device *dev)
अणु
	वापस rcu_dereference(dev->rx_handler) == br_get_rx_handler(dev);
पूर्ण

अटल अंतरभूत bool br_rx_handler_check_rtnl(स्थिर काष्ठा net_device *dev)
अणु
	वापस rcu_dereference_rtnl(dev->rx_handler) == br_get_rx_handler(dev);
पूर्ण

अटल अंतरभूत काष्ठा net_bridge_port *br_port_get_check_rcu(स्थिर काष्ठा net_device *dev)
अणु
	वापस br_rx_handler_check_rcu(dev) ? br_port_get_rcu(dev) : शून्य;
पूर्ण

अटल अंतरभूत काष्ठा net_bridge_port *
br_port_get_check_rtnl(स्थिर काष्ठा net_device *dev)
अणु
	वापस br_rx_handler_check_rtnl(dev) ? br_port_get_rtnl_rcu(dev) : शून्य;
पूर्ण

/* br_ioctl.c */
पूर्णांक br_dev_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd);
पूर्णांक br_ioctl_deviceless_stub(काष्ठा net *net, अचिन्हित पूर्णांक cmd,
			     व्योम __user *arg);

/* br_multicast.c */
#अगर_घोषित CONFIG_BRIDGE_IGMP_SNOOPING
पूर्णांक br_multicast_rcv(काष्ठा net_bridge *br, काष्ठा net_bridge_port *port,
		     काष्ठा sk_buff *skb, u16 vid);
काष्ठा net_bridge_mdb_entry *br_mdb_get(काष्ठा net_bridge *br,
					काष्ठा sk_buff *skb, u16 vid);
पूर्णांक br_multicast_add_port(काष्ठा net_bridge_port *port);
व्योम br_multicast_del_port(काष्ठा net_bridge_port *port);
व्योम br_multicast_enable_port(काष्ठा net_bridge_port *port);
व्योम br_multicast_disable_port(काष्ठा net_bridge_port *port);
व्योम br_multicast_init(काष्ठा net_bridge *br);
व्योम br_multicast_join_snoopers(काष्ठा net_bridge *br);
व्योम br_multicast_leave_snoopers(काष्ठा net_bridge *br);
व्योम br_multicast_खोलो(काष्ठा net_bridge *br);
व्योम br_multicast_stop(काष्ठा net_bridge *br);
व्योम br_multicast_dev_del(काष्ठा net_bridge *br);
व्योम br_multicast_flood(काष्ठा net_bridge_mdb_entry *mdst,
			काष्ठा sk_buff *skb, bool local_rcv, bool local_orig);
पूर्णांक br_multicast_set_router(काष्ठा net_bridge *br, अचिन्हित दीर्घ val);
पूर्णांक br_multicast_set_port_router(काष्ठा net_bridge_port *p, अचिन्हित दीर्घ val);
पूर्णांक br_multicast_toggle(काष्ठा net_bridge *br, अचिन्हित दीर्घ val,
			काष्ठा netlink_ext_ack *extack);
पूर्णांक br_multicast_set_querier(काष्ठा net_bridge *br, अचिन्हित दीर्घ val);
पूर्णांक br_multicast_set_hash_max(काष्ठा net_bridge *br, अचिन्हित दीर्घ val);
पूर्णांक br_multicast_set_igmp_version(काष्ठा net_bridge *br, अचिन्हित दीर्घ val);
#अगर IS_ENABLED(CONFIG_IPV6)
पूर्णांक br_multicast_set_mld_version(काष्ठा net_bridge *br, अचिन्हित दीर्घ val);
#पूर्ण_अगर
काष्ठा net_bridge_mdb_entry *
br_mdb_ip_get(काष्ठा net_bridge *br, काष्ठा br_ip *dst);
काष्ठा net_bridge_mdb_entry *
br_multicast_new_group(काष्ठा net_bridge *br, काष्ठा br_ip *group);
काष्ठा net_bridge_port_group *
br_multicast_new_port_group(काष्ठा net_bridge_port *port, काष्ठा br_ip *group,
			    काष्ठा net_bridge_port_group __rcu *next,
			    अचिन्हित अक्षर flags, स्थिर अचिन्हित अक्षर *src,
			    u8 filter_mode, u8 rt_protocol);
पूर्णांक br_mdb_hash_init(काष्ठा net_bridge *br);
व्योम br_mdb_hash_fini(काष्ठा net_bridge *br);
व्योम br_mdb_notअगरy(काष्ठा net_device *dev, काष्ठा net_bridge_mdb_entry *mp,
		   काष्ठा net_bridge_port_group *pg, पूर्णांक type);
व्योम br_rtr_notअगरy(काष्ठा net_device *dev, काष्ठा net_bridge_port *port,
		   पूर्णांक type);
व्योम br_multicast_del_pg(काष्ठा net_bridge_mdb_entry *mp,
			 काष्ठा net_bridge_port_group *pg,
			 काष्ठा net_bridge_port_group __rcu **pp);
व्योम br_multicast_count(काष्ठा net_bridge *br, स्थिर काष्ठा net_bridge_port *p,
			स्थिर काष्ठा sk_buff *skb, u8 type, u8 dir);
पूर्णांक br_multicast_init_stats(काष्ठा net_bridge *br);
व्योम br_multicast_uninit_stats(काष्ठा net_bridge *br);
व्योम br_multicast_get_stats(स्थिर काष्ठा net_bridge *br,
			    स्थिर काष्ठा net_bridge_port *p,
			    काष्ठा br_mcast_stats *dest);
व्योम br_mdb_init(व्योम);
व्योम br_mdb_uninit(व्योम);
व्योम br_multicast_host_join(काष्ठा net_bridge_mdb_entry *mp, bool notअगरy);
व्योम br_multicast_host_leave(काष्ठा net_bridge_mdb_entry *mp, bool notअगरy);
व्योम br_multicast_star_g_handle_mode(काष्ठा net_bridge_port_group *pg,
				     u8 filter_mode);
व्योम br_multicast_sg_add_exclude_ports(काष्ठा net_bridge_mdb_entry *star_mp,
				       काष्ठा net_bridge_port_group *sg);
काष्ठा net_bridge_group_src *
br_multicast_find_group_src(काष्ठा net_bridge_port_group *pg, काष्ठा br_ip *ip);
व्योम br_multicast_del_group_src(काष्ठा net_bridge_group_src *src,
				bool fastleave);

अटल अंतरभूत bool br_group_is_l2(स्थिर काष्ठा br_ip *group)
अणु
	वापस group->proto == 0;
पूर्ण

#घोषणा mlock_dereference(X, br) \
	rcu_dereference_रक्षित(X, lockdep_is_held(&br->multicast_lock))

अटल अंतरभूत bool br_multicast_is_router(काष्ठा net_bridge *br)
अणु
	वापस br->multicast_router == 2 ||
	       (br->multicast_router == 1 &&
		समयr_pending(&br->multicast_router_समयr));
पूर्ण

अटल अंतरभूत bool
__br_multicast_querier_exists(काष्ठा net_bridge *br,
				काष्ठा bridge_mcast_other_query *querier,
				स्थिर bool is_ipv6)
अणु
	bool own_querier_enabled;

	अगर (br_opt_get(br, BROPT_MULTICAST_QUERIER)) अणु
		अगर (is_ipv6 && !br_opt_get(br, BROPT_HAS_IPV6_ADDR))
			own_querier_enabled = false;
		अन्यथा
			own_querier_enabled = true;
	पूर्ण अन्यथा अणु
		own_querier_enabled = false;
	पूर्ण

	वापस समय_is_beक्रमe_jअगरfies(querier->delay_समय) &&
	       (own_querier_enabled || समयr_pending(&querier->समयr));
पूर्ण

अटल अंतरभूत bool br_multicast_querier_exists(काष्ठा net_bridge *br,
					       काष्ठा ethhdr *eth,
					       स्थिर काष्ठा net_bridge_mdb_entry *mdb)
अणु
	चयन (eth->h_proto) अणु
	हाल (htons(ETH_P_IP)):
		वापस __br_multicast_querier_exists(br,
			&br->ip4_other_query, false);
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल (htons(ETH_P_IPV6)):
		वापस __br_multicast_querier_exists(br,
			&br->ip6_other_query, true);
#पूर्ण_अगर
	शेष:
		वापस !!mdb && br_group_is_l2(&mdb->addr);
	पूर्ण
पूर्ण

अटल अंतरभूत bool br_multicast_is_star_g(स्थिर काष्ठा br_ip *ip)
अणु
	चयन (ip->proto) अणु
	हाल htons(ETH_P_IP):
		वापस ipv4_is_zeronet(ip->src.ip4);
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल htons(ETH_P_IPV6):
		वापस ipv6_addr_any(&ip->src.ip6);
#पूर्ण_अगर
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल अंतरभूत bool br_multicast_should_handle_mode(स्थिर काष्ठा net_bridge *br,
						   __be16 proto)
अणु
	चयन (proto) अणु
	हाल htons(ETH_P_IP):
		वापस !!(br->multicast_igmp_version == 3);
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल htons(ETH_P_IPV6):
		वापस !!(br->multicast_mld_version == 2);
#पूर्ण_अगर
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक br_multicast_igmp_type(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस BR_INPUT_SKB_CB(skb)->igmp;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ br_multicast_lmqt(स्थिर काष्ठा net_bridge *br)
अणु
	वापस br->multicast_last_member_पूर्णांकerval *
	       br->multicast_last_member_count;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ br_multicast_gmi(स्थिर काष्ठा net_bridge *br)
अणु
	/* use the RFC शेष of 2 क्रम QRV */
	वापस 2 * br->multicast_query_पूर्णांकerval +
	       br->multicast_query_response_पूर्णांकerval;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक br_multicast_rcv(काष्ठा net_bridge *br,
				   काष्ठा net_bridge_port *port,
				   काष्ठा sk_buff *skb,
				   u16 vid)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा net_bridge_mdb_entry *br_mdb_get(काष्ठा net_bridge *br,
						      काष्ठा sk_buff *skb, u16 vid)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक br_multicast_add_port(काष्ठा net_bridge_port *port)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम br_multicast_del_port(काष्ठा net_bridge_port *port)
अणु
पूर्ण

अटल अंतरभूत व्योम br_multicast_enable_port(काष्ठा net_bridge_port *port)
अणु
पूर्ण

अटल अंतरभूत व्योम br_multicast_disable_port(काष्ठा net_bridge_port *port)
अणु
पूर्ण

अटल अंतरभूत व्योम br_multicast_init(काष्ठा net_bridge *br)
अणु
पूर्ण

अटल अंतरभूत व्योम br_multicast_join_snoopers(काष्ठा net_bridge *br)
अणु
पूर्ण

अटल अंतरभूत व्योम br_multicast_leave_snoopers(काष्ठा net_bridge *br)
अणु
पूर्ण

अटल अंतरभूत व्योम br_multicast_खोलो(काष्ठा net_bridge *br)
अणु
पूर्ण

अटल अंतरभूत व्योम br_multicast_stop(काष्ठा net_bridge *br)
अणु
पूर्ण

अटल अंतरभूत व्योम br_multicast_dev_del(काष्ठा net_bridge *br)
अणु
पूर्ण

अटल अंतरभूत व्योम br_multicast_flood(काष्ठा net_bridge_mdb_entry *mdst,
				      काष्ठा sk_buff *skb,
				      bool local_rcv, bool local_orig)
अणु
पूर्ण

अटल अंतरभूत bool br_multicast_is_router(काष्ठा net_bridge *br)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool br_multicast_querier_exists(काष्ठा net_bridge *br,
					       काष्ठा ethhdr *eth,
					       स्थिर काष्ठा net_bridge_mdb_entry *mdb)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम br_mdb_init(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम br_mdb_uninit(व्योम)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक br_mdb_hash_init(काष्ठा net_bridge *br)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम br_mdb_hash_fini(काष्ठा net_bridge *br)
अणु
पूर्ण

अटल अंतरभूत व्योम br_multicast_count(काष्ठा net_bridge *br,
				      स्थिर काष्ठा net_bridge_port *p,
				      स्थिर काष्ठा sk_buff *skb,
				      u8 type, u8 dir)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक br_multicast_init_stats(काष्ठा net_bridge *br)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम br_multicast_uninit_stats(काष्ठा net_bridge *br)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक br_multicast_igmp_type(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

/* br_vlan.c */
#अगर_घोषित CONFIG_BRIDGE_VLAN_FILTERING
bool br_allowed_ingress(स्थिर काष्ठा net_bridge *br,
			काष्ठा net_bridge_vlan_group *vg, काष्ठा sk_buff *skb,
			u16 *vid, u8 *state);
bool br_allowed_egress(काष्ठा net_bridge_vlan_group *vg,
		       स्थिर काष्ठा sk_buff *skb);
bool br_should_learn(काष्ठा net_bridge_port *p, काष्ठा sk_buff *skb, u16 *vid);
काष्ठा sk_buff *br_handle_vlan(काष्ठा net_bridge *br,
			       स्थिर काष्ठा net_bridge_port *port,
			       काष्ठा net_bridge_vlan_group *vg,
			       काष्ठा sk_buff *skb);
पूर्णांक br_vlan_add(काष्ठा net_bridge *br, u16 vid, u16 flags,
		bool *changed, काष्ठा netlink_ext_ack *extack);
पूर्णांक br_vlan_delete(काष्ठा net_bridge *br, u16 vid);
व्योम br_vlan_flush(काष्ठा net_bridge *br);
काष्ठा net_bridge_vlan *br_vlan_find(काष्ठा net_bridge_vlan_group *vg, u16 vid);
व्योम br_recalculate_fwd_mask(काष्ठा net_bridge *br);
पूर्णांक br_vlan_filter_toggle(काष्ठा net_bridge *br, अचिन्हित दीर्घ val,
			  काष्ठा netlink_ext_ack *extack);
पूर्णांक __br_vlan_set_proto(काष्ठा net_bridge *br, __be16 proto,
			काष्ठा netlink_ext_ack *extack);
पूर्णांक br_vlan_set_proto(काष्ठा net_bridge *br, अचिन्हित दीर्घ val,
		      काष्ठा netlink_ext_ack *extack);
पूर्णांक br_vlan_set_stats(काष्ठा net_bridge *br, अचिन्हित दीर्घ val);
पूर्णांक br_vlan_set_stats_per_port(काष्ठा net_bridge *br, अचिन्हित दीर्घ val);
पूर्णांक br_vlan_init(काष्ठा net_bridge *br);
पूर्णांक br_vlan_set_शेष_pvid(काष्ठा net_bridge *br, अचिन्हित दीर्घ val,
			     काष्ठा netlink_ext_ack *extack);
पूर्णांक __br_vlan_set_शेष_pvid(काष्ठा net_bridge *br, u16 pvid,
			       काष्ठा netlink_ext_ack *extack);
पूर्णांक nbp_vlan_add(काष्ठा net_bridge_port *port, u16 vid, u16 flags,
		 bool *changed, काष्ठा netlink_ext_ack *extack);
पूर्णांक nbp_vlan_delete(काष्ठा net_bridge_port *port, u16 vid);
व्योम nbp_vlan_flush(काष्ठा net_bridge_port *port);
पूर्णांक nbp_vlan_init(काष्ठा net_bridge_port *port, काष्ठा netlink_ext_ack *extack);
पूर्णांक nbp_get_num_vlan_infos(काष्ठा net_bridge_port *p, u32 filter_mask);
व्योम br_vlan_get_stats(स्थिर काष्ठा net_bridge_vlan *v,
		       काष्ठा pcpu_sw_netstats *stats);
व्योम br_vlan_port_event(काष्ठा net_bridge_port *p, अचिन्हित दीर्घ event);
पूर्णांक br_vlan_bridge_event(काष्ठा net_device *dev, अचिन्हित दीर्घ event,
			 व्योम *ptr);
व्योम br_vlan_rtnl_init(व्योम);
व्योम br_vlan_rtnl_uninit(व्योम);
व्योम br_vlan_notअगरy(स्थिर काष्ठा net_bridge *br,
		    स्थिर काष्ठा net_bridge_port *p,
		    u16 vid, u16 vid_range,
		    पूर्णांक cmd);
bool br_vlan_can_enter_range(स्थिर काष्ठा net_bridge_vlan *v_curr,
			     स्थिर काष्ठा net_bridge_vlan *range_end);

व्योम br_vlan_fill_क्रमward_path_pvid(काष्ठा net_bridge *br,
				    काष्ठा net_device_path_ctx *ctx,
				    काष्ठा net_device_path *path);
पूर्णांक br_vlan_fill_क्रमward_path_mode(काष्ठा net_bridge *br,
				   काष्ठा net_bridge_port *dst,
				   काष्ठा net_device_path *path);

अटल अंतरभूत काष्ठा net_bridge_vlan_group *br_vlan_group(
					स्थिर काष्ठा net_bridge *br)
अणु
	वापस rtnl_dereference(br->vlgrp);
पूर्ण

अटल अंतरभूत काष्ठा net_bridge_vlan_group *nbp_vlan_group(
					स्थिर काष्ठा net_bridge_port *p)
अणु
	वापस rtnl_dereference(p->vlgrp);
पूर्ण

अटल अंतरभूत काष्ठा net_bridge_vlan_group *br_vlan_group_rcu(
					स्थिर काष्ठा net_bridge *br)
अणु
	वापस rcu_dereference(br->vlgrp);
पूर्ण

अटल अंतरभूत काष्ठा net_bridge_vlan_group *nbp_vlan_group_rcu(
					स्थिर काष्ठा net_bridge_port *p)
अणु
	वापस rcu_dereference(p->vlgrp);
पूर्ण

/* Since bridge now depends on 8021Q module, but the समय bridge sees the
 * skb, the vlan tag will always be present अगर the frame was tagged.
 */
अटल अंतरभूत पूर्णांक br_vlan_get_tag(स्थिर काष्ठा sk_buff *skb, u16 *vid)
अणु
	पूर्णांक err = 0;

	अगर (skb_vlan_tag_present(skb)) अणु
		*vid = skb_vlan_tag_get_id(skb);
	पूर्ण अन्यथा अणु
		*vid = 0;
		err = -EINVAL;
	पूर्ण

	वापस err;
पूर्ण

अटल अंतरभूत u16 br_get_pvid(स्थिर काष्ठा net_bridge_vlan_group *vg)
अणु
	अगर (!vg)
		वापस 0;

	smp_rmb();
	वापस vg->pvid;
पूर्ण

अटल अंतरभूत u16 br_vlan_flags(स्थिर काष्ठा net_bridge_vlan *v, u16 pvid)
अणु
	वापस v->vid == pvid ? v->flags | BRIDGE_VLAN_INFO_PVID : v->flags;
पूर्ण
#अन्यथा
अटल अंतरभूत bool br_allowed_ingress(स्थिर काष्ठा net_bridge *br,
				      काष्ठा net_bridge_vlan_group *vg,
				      काष्ठा sk_buff *skb,
				      u16 *vid, u8 *state)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत bool br_allowed_egress(काष्ठा net_bridge_vlan_group *vg,
				     स्थिर काष्ठा sk_buff *skb)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत bool br_should_learn(काष्ठा net_bridge_port *p,
				   काष्ठा sk_buff *skb, u16 *vid)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *br_handle_vlan(काष्ठा net_bridge *br,
					     स्थिर काष्ठा net_bridge_port *port,
					     काष्ठा net_bridge_vlan_group *vg,
					     काष्ठा sk_buff *skb)
अणु
	वापस skb;
पूर्ण

अटल अंतरभूत पूर्णांक br_vlan_add(काष्ठा net_bridge *br, u16 vid, u16 flags,
			      bool *changed, काष्ठा netlink_ext_ack *extack)
अणु
	*changed = false;
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक br_vlan_delete(काष्ठा net_bridge *br, u16 vid)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत व्योम br_vlan_flush(काष्ठा net_bridge *br)
अणु
पूर्ण

अटल अंतरभूत व्योम br_recalculate_fwd_mask(काष्ठा net_bridge *br)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक br_vlan_init(काष्ठा net_bridge *br)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक nbp_vlan_add(काष्ठा net_bridge_port *port, u16 vid, u16 flags,
			       bool *changed, काष्ठा netlink_ext_ack *extack)
अणु
	*changed = false;
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक nbp_vlan_delete(काष्ठा net_bridge_port *port, u16 vid)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत व्योम nbp_vlan_flush(काष्ठा net_bridge_port *port)
अणु
पूर्ण

अटल अंतरभूत काष्ठा net_bridge_vlan *br_vlan_find(काष्ठा net_bridge_vlan_group *vg,
						   u16 vid)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक nbp_vlan_init(काष्ठा net_bridge_port *port,
				काष्ठा netlink_ext_ack *extack)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत u16 br_vlan_get_tag(स्थिर काष्ठा sk_buff *skb, u16 *tag)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत u16 br_get_pvid(स्थिर काष्ठा net_bridge_vlan_group *vg)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक br_vlan_filter_toggle(काष्ठा net_bridge *br,
					अचिन्हित दीर्घ val,
					काष्ठा netlink_ext_ack *extack)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक nbp_get_num_vlan_infos(काष्ठा net_bridge_port *p,
					 u32 filter_mask)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम br_vlan_fill_क्रमward_path_pvid(काष्ठा net_bridge *br,
						  काष्ठा net_device_path_ctx *ctx,
						  काष्ठा net_device_path *path)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक br_vlan_fill_क्रमward_path_mode(काष्ठा net_bridge *br,
						 काष्ठा net_bridge_port *dst,
						 काष्ठा net_device_path *path)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा net_bridge_vlan_group *br_vlan_group(
					स्थिर काष्ठा net_bridge *br)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा net_bridge_vlan_group *nbp_vlan_group(
					स्थिर काष्ठा net_bridge_port *p)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा net_bridge_vlan_group *br_vlan_group_rcu(
					स्थिर काष्ठा net_bridge *br)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा net_bridge_vlan_group *nbp_vlan_group_rcu(
					स्थिर काष्ठा net_bridge_port *p)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम br_vlan_get_stats(स्थिर काष्ठा net_bridge_vlan *v,
				     काष्ठा pcpu_sw_netstats *stats)
अणु
पूर्ण

अटल अंतरभूत व्योम br_vlan_port_event(काष्ठा net_bridge_port *p,
				      अचिन्हित दीर्घ event)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक br_vlan_bridge_event(काष्ठा net_device *dev,
				       अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम br_vlan_rtnl_init(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम br_vlan_rtnl_uninit(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम br_vlan_notअगरy(स्थिर काष्ठा net_bridge *br,
				  स्थिर काष्ठा net_bridge_port *p,
				  u16 vid, u16 vid_range,
				  पूर्णांक cmd)
अणु
पूर्ण

अटल अंतरभूत bool br_vlan_can_enter_range(स्थिर काष्ठा net_bridge_vlan *v_curr,
					   स्थिर काष्ठा net_bridge_vlan *range_end)
अणु
	वापस true;
पूर्ण
#पूर्ण_अगर

/* br_vlan_options.c */
#अगर_घोषित CONFIG_BRIDGE_VLAN_FILTERING
bool br_vlan_opts_eq_range(स्थिर काष्ठा net_bridge_vlan *v_curr,
			   स्थिर काष्ठा net_bridge_vlan *range_end);
bool br_vlan_opts_fill(काष्ठा sk_buff *skb, स्थिर काष्ठा net_bridge_vlan *v);
माप_प्रकार br_vlan_opts_nl_size(व्योम);
पूर्णांक br_vlan_process_options(स्थिर काष्ठा net_bridge *br,
			    स्थिर काष्ठा net_bridge_port *p,
			    काष्ठा net_bridge_vlan *range_start,
			    काष्ठा net_bridge_vlan *range_end,
			    काष्ठा nlattr **tb,
			    काष्ठा netlink_ext_ack *extack);

/* vlan state manipulation helpers using *_ONCE to annotate lock-मुक्त access */
अटल अंतरभूत u8 br_vlan_get_state(स्थिर काष्ठा net_bridge_vlan *v)
अणु
	वापस READ_ONCE(v->state);
पूर्ण

अटल अंतरभूत व्योम br_vlan_set_state(काष्ठा net_bridge_vlan *v, u8 state)
अणु
	WRITE_ONCE(v->state, state);
पूर्ण

अटल अंतरभूत u8 br_vlan_get_pvid_state(स्थिर काष्ठा net_bridge_vlan_group *vg)
अणु
	वापस READ_ONCE(vg->pvid_state);
पूर्ण

अटल अंतरभूत व्योम br_vlan_set_pvid_state(काष्ठा net_bridge_vlan_group *vg,
					  u8 state)
अणु
	WRITE_ONCE(vg->pvid_state, state);
पूर्ण

/* learn_allow is true at ingress and false at egress */
अटल अंतरभूत bool br_vlan_state_allowed(u8 state, bool learn_allow)
अणु
	चयन (state) अणु
	हाल BR_STATE_LEARNING:
		वापस learn_allow;
	हाल BR_STATE_FORWARDING:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण
#पूर्ण_अगर

काष्ठा nf_br_ops अणु
	पूर्णांक (*br_dev_xmit_hook)(काष्ठा sk_buff *skb);
पूर्ण;
बाह्य स्थिर काष्ठा nf_br_ops __rcu *nf_br_ops;

/* br_netfilter.c */
#अगर IS_ENABLED(CONFIG_BRIDGE_NETFILTER)
पूर्णांक br_nf_core_init(व्योम);
व्योम br_nf_core_fini(व्योम);
व्योम br_netfilter_rtable_init(काष्ठा net_bridge *);
#अन्यथा
अटल अंतरभूत पूर्णांक br_nf_core_init(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम br_nf_core_fini(व्योम) अणुपूर्ण
#घोषणा br_netfilter_rtable_init(x)
#पूर्ण_अगर

/* br_stp.c */
व्योम br_set_state(काष्ठा net_bridge_port *p, अचिन्हित पूर्णांक state);
काष्ठा net_bridge_port *br_get_port(काष्ठा net_bridge *br, u16 port_no);
व्योम br_init_port(काष्ठा net_bridge_port *p);
व्योम br_become_designated_port(काष्ठा net_bridge_port *p);

व्योम __br_set_क्रमward_delay(काष्ठा net_bridge *br, अचिन्हित दीर्घ t);
पूर्णांक br_set_क्रमward_delay(काष्ठा net_bridge *br, अचिन्हित दीर्घ x);
पूर्णांक br_set_hello_समय(काष्ठा net_bridge *br, अचिन्हित दीर्घ x);
पूर्णांक br_set_max_age(काष्ठा net_bridge *br, अचिन्हित दीर्घ x);
पूर्णांक __set_ageing_समय(काष्ठा net_device *dev, अचिन्हित दीर्घ t);
पूर्णांक br_set_ageing_समय(काष्ठा net_bridge *br, घड़ी_प्रकार ageing_समय);


/* br_stp_अगर.c */
व्योम br_stp_enable_bridge(काष्ठा net_bridge *br);
व्योम br_stp_disable_bridge(काष्ठा net_bridge *br);
पूर्णांक br_stp_set_enabled(काष्ठा net_bridge *br, अचिन्हित दीर्घ val,
		       काष्ठा netlink_ext_ack *extack);
व्योम br_stp_enable_port(काष्ठा net_bridge_port *p);
व्योम br_stp_disable_port(काष्ठा net_bridge_port *p);
bool br_stp_recalculate_bridge_id(काष्ठा net_bridge *br);
व्योम br_stp_change_bridge_id(काष्ठा net_bridge *br, स्थिर अचिन्हित अक्षर *a);
व्योम br_stp_set_bridge_priority(काष्ठा net_bridge *br, u16 newprio);
पूर्णांक br_stp_set_port_priority(काष्ठा net_bridge_port *p, अचिन्हित दीर्घ newprio);
पूर्णांक br_stp_set_path_cost(काष्ठा net_bridge_port *p, अचिन्हित दीर्घ path_cost);
sमाप_प्रकार br_show_bridge_id(अक्षर *buf, स्थिर काष्ठा bridge_id *id);

/* br_stp_bpdu.c */
काष्ठा stp_proto;
व्योम br_stp_rcv(स्थिर काष्ठा stp_proto *proto, काष्ठा sk_buff *skb,
		काष्ठा net_device *dev);

/* br_stp_समयr.c */
व्योम br_stp_समयr_init(काष्ठा net_bridge *br);
व्योम br_stp_port_समयr_init(काष्ठा net_bridge_port *p);
अचिन्हित दीर्घ br_समयr_value(स्थिर काष्ठा समयr_list *समयr);

/* br.c */
#अगर IS_ENABLED(CONFIG_ATM_LANE)
बाह्य पूर्णांक (*br_fdb_test_addr_hook)(काष्ठा net_device *dev, अचिन्हित अक्षर *addr);
#पूर्ण_अगर

/* br_mrp.c */
#अगर IS_ENABLED(CONFIG_BRIDGE_MRP)
पूर्णांक br_mrp_parse(काष्ठा net_bridge *br, काष्ठा net_bridge_port *p,
		 काष्ठा nlattr *attr, पूर्णांक cmd, काष्ठा netlink_ext_ack *extack);
bool br_mrp_enabled(काष्ठा net_bridge *br);
व्योम br_mrp_port_del(काष्ठा net_bridge *br, काष्ठा net_bridge_port *p);
पूर्णांक br_mrp_fill_info(काष्ठा sk_buff *skb, काष्ठा net_bridge *br);
#अन्यथा
अटल अंतरभूत पूर्णांक br_mrp_parse(काष्ठा net_bridge *br, काष्ठा net_bridge_port *p,
			       काष्ठा nlattr *attr, पूर्णांक cmd,
			       काष्ठा netlink_ext_ack *extack)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत bool br_mrp_enabled(काष्ठा net_bridge *br)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम br_mrp_port_del(काष्ठा net_bridge *br,
				   काष्ठा net_bridge_port *p)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक br_mrp_fill_info(काष्ठा sk_buff *skb, काष्ठा net_bridge *br)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर

/* br_cfm.c */
#अगर IS_ENABLED(CONFIG_BRIDGE_CFM)
पूर्णांक br_cfm_parse(काष्ठा net_bridge *br, काष्ठा net_bridge_port *p,
		 काष्ठा nlattr *attr, पूर्णांक cmd, काष्ठा netlink_ext_ack *extack);
bool br_cfm_created(काष्ठा net_bridge *br);
व्योम br_cfm_port_del(काष्ठा net_bridge *br, काष्ठा net_bridge_port *p);
पूर्णांक br_cfm_config_fill_info(काष्ठा sk_buff *skb, काष्ठा net_bridge *br);
पूर्णांक br_cfm_status_fill_info(काष्ठा sk_buff *skb,
			    काष्ठा net_bridge *br,
			    bool getlink);
पूर्णांक br_cfm_mep_count(काष्ठा net_bridge *br, u32 *count);
पूर्णांक br_cfm_peer_mep_count(काष्ठा net_bridge *br, u32 *count);
#अन्यथा
अटल अंतरभूत पूर्णांक br_cfm_parse(काष्ठा net_bridge *br, काष्ठा net_bridge_port *p,
			       काष्ठा nlattr *attr, पूर्णांक cmd,
			       काष्ठा netlink_ext_ack *extack)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत bool br_cfm_created(काष्ठा net_bridge *br)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम br_cfm_port_del(काष्ठा net_bridge *br,
				   काष्ठा net_bridge_port *p)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक br_cfm_config_fill_info(काष्ठा sk_buff *skb, काष्ठा net_bridge *br)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक br_cfm_status_fill_info(काष्ठा sk_buff *skb,
					  काष्ठा net_bridge *br,
					  bool getlink)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक br_cfm_mep_count(काष्ठा net_bridge *br, u32 *count)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक br_cfm_peer_mep_count(काष्ठा net_bridge *br, u32 *count)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
#पूर्ण_अगर

/* br_netlink.c */
बाह्य काष्ठा rtnl_link_ops br_link_ops;
पूर्णांक br_netlink_init(व्योम);
व्योम br_netlink_fini(व्योम);
व्योम br_अगरinfo_notअगरy(पूर्णांक event, स्थिर काष्ठा net_bridge *br,
		      स्थिर काष्ठा net_bridge_port *port);
व्योम br_info_notअगरy(पूर्णांक event, स्थिर काष्ठा net_bridge *br,
		    स्थिर काष्ठा net_bridge_port *port, u32 filter);
पूर्णांक br_setlink(काष्ठा net_device *dev, काष्ठा nlmsghdr *nlmsg, u16 flags,
	       काष्ठा netlink_ext_ack *extack);
पूर्णांक br_dellink(काष्ठा net_device *dev, काष्ठा nlmsghdr *nlmsg, u16 flags);
पूर्णांक br_getlink(काष्ठा sk_buff *skb, u32 pid, u32 seq, काष्ठा net_device *dev,
	       u32 filter_mask, पूर्णांक nlflags);
पूर्णांक br_process_vlan_info(काष्ठा net_bridge *br,
			 काष्ठा net_bridge_port *p, पूर्णांक cmd,
			 काष्ठा bridge_vlan_info *vinfo_curr,
			 काष्ठा bridge_vlan_info **vinfo_last,
			 bool *changed,
			 काष्ठा netlink_ext_ack *extack);

#अगर_घोषित CONFIG_SYSFS
/* br_sysfs_अगर.c */
बाह्य स्थिर काष्ठा sysfs_ops brport_sysfs_ops;
पूर्णांक br_sysfs_addअगर(काष्ठा net_bridge_port *p);
पूर्णांक br_sysfs_नामअगर(काष्ठा net_bridge_port *p);

/* br_sysfs_br.c */
पूर्णांक br_sysfs_addbr(काष्ठा net_device *dev);
व्योम br_sysfs_delbr(काष्ठा net_device *dev);

#अन्यथा

अटल अंतरभूत पूर्णांक br_sysfs_addअगर(काष्ठा net_bridge_port *p) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक br_sysfs_नामअगर(काष्ठा net_bridge_port *p) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक br_sysfs_addbr(काष्ठा net_device *dev) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम br_sysfs_delbr(काष्ठा net_device *dev) अणु वापस; पूर्ण
#पूर्ण_अगर /* CONFIG_SYSFS */

/* br_चयनdev.c */
#अगर_घोषित CONFIG_NET_SWITCHDEV
पूर्णांक nbp_चयनdev_mark_set(काष्ठा net_bridge_port *p);
व्योम nbp_चयनdev_frame_mark(स्थिर काष्ठा net_bridge_port *p,
			      काष्ठा sk_buff *skb);
bool nbp_चयनdev_allowed_egress(स्थिर काष्ठा net_bridge_port *p,
				  स्थिर काष्ठा sk_buff *skb);
पूर्णांक br_चयनdev_set_port_flag(काष्ठा net_bridge_port *p,
			       अचिन्हित दीर्घ flags,
			       अचिन्हित दीर्घ mask,
			       काष्ठा netlink_ext_ack *extack);
व्योम br_चयनdev_fdb_notअगरy(स्थिर काष्ठा net_bridge_fdb_entry *fdb,
			     पूर्णांक type);
पूर्णांक br_चयनdev_port_vlan_add(काष्ठा net_device *dev, u16 vid, u16 flags,
			       काष्ठा netlink_ext_ack *extack);
पूर्णांक br_चयनdev_port_vlan_del(काष्ठा net_device *dev, u16 vid);

अटल अंतरभूत व्योम br_चयनdev_frame_unmark(काष्ठा sk_buff *skb)
अणु
	skb->offload_fwd_mark = 0;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक nbp_चयनdev_mark_set(काष्ठा net_bridge_port *p)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम nbp_चयनdev_frame_mark(स्थिर काष्ठा net_bridge_port *p,
					    काष्ठा sk_buff *skb)
अणु
पूर्ण

अटल अंतरभूत bool nbp_चयनdev_allowed_egress(स्थिर काष्ठा net_bridge_port *p,
						स्थिर काष्ठा sk_buff *skb)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत पूर्णांक br_चयनdev_set_port_flag(काष्ठा net_bridge_port *p,
					     अचिन्हित दीर्घ flags,
					     अचिन्हित दीर्घ mask,
					     काष्ठा netlink_ext_ack *extack)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक br_चयनdev_port_vlan_add(काष्ठा net_device *dev,
					     u16 vid, u16 flags,
					     काष्ठा netlink_ext_ack *extack)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक br_चयनdev_port_vlan_del(काष्ठा net_device *dev, u16 vid)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत व्योम
br_चयनdev_fdb_notअगरy(स्थिर काष्ठा net_bridge_fdb_entry *fdb, पूर्णांक type)
अणु
पूर्ण

अटल अंतरभूत व्योम br_चयनdev_frame_unmark(काष्ठा sk_buff *skb)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_NET_SWITCHDEV */

/* br_arp_nd_proxy.c */
व्योम br_recalculate_neigh_suppress_enabled(काष्ठा net_bridge *br);
व्योम br_करो_proxy_suppress_arp(काष्ठा sk_buff *skb, काष्ठा net_bridge *br,
			      u16 vid, काष्ठा net_bridge_port *p);
व्योम br_करो_suppress_nd(काष्ठा sk_buff *skb, काष्ठा net_bridge *br,
		       u16 vid, काष्ठा net_bridge_port *p, काष्ठा nd_msg *msg);
काष्ठा nd_msg *br_is_nd_neigh_msg(काष्ठा sk_buff *skb, काष्ठा nd_msg *m);
#पूर्ण_अगर
