<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause) */
/* Copyright (C) 2017-2018 Netronome Systems, Inc. */

#अगर_अघोषित __NFP_FLOWER_H__
#घोषणा __NFP_FLOWER_H__ 1

#समावेश "cmsg.h"
#समावेश "../nfp_net.h"

#समावेश <linux/circ_buf.h>
#समावेश <linux/hashtable.h>
#समावेश <linux/rhashtable.h>
#समावेश <linux/समय64.h>
#समावेश <linux/types.h>
#समावेश <net/pkt_cls.h>
#समावेश <net/tcp.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/idr.h>

काष्ठा nfp_fl_pre_lag;
काष्ठा net_device;
काष्ठा nfp_app;

#घोषणा NFP_FL_STAT_ID_MU_NUM		GENMASK(31, 22)
#घोषणा NFP_FL_STAT_ID_STAT		GENMASK(21, 0)

#घोषणा NFP_FL_STATS_ELEM_RS		माप_field(काष्ठा nfp_fl_stats_id, \
						     init_unalloc)
#घोषणा NFP_FLOWER_MASK_ENTRY_RS	256
#घोषणा NFP_FLOWER_MASK_ELEMENT_RS	1
#घोषणा NFP_FLOWER_MASK_HASH_BITS	10

#घोषणा NFP_FLOWER_KEY_MAX_LW		32

#घोषणा NFP_FL_META_FLAG_MANAGE_MASK	BIT(7)

#घोषणा NFP_FL_MASK_REUSE_TIME_NS	40000
#घोषणा NFP_FL_MASK_ID_LOCATION		1

/* Extra features biपंचांगap. */
#घोषणा NFP_FL_FEATS_GENEVE		BIT(0)
#घोषणा NFP_FL_NBI_MTU_SETTING		BIT(1)
#घोषणा NFP_FL_FEATS_GENEVE_OPT		BIT(2)
#घोषणा NFP_FL_FEATS_VLAN_PCP		BIT(3)
#घोषणा NFP_FL_FEATS_VF_RLIM		BIT(4)
#घोषणा NFP_FL_FEATS_FLOW_MOD		BIT(5)
#घोषणा NFP_FL_FEATS_PRE_TUN_RULES	BIT(6)
#घोषणा NFP_FL_FEATS_IPV6_TUN		BIT(7)
#घोषणा NFP_FL_FEATS_VLAN_QINQ		BIT(8)
#घोषणा NFP_FL_FEATS_QOS_PPS		BIT(9)
#घोषणा NFP_FL_FEATS_HOST_ACK		BIT(31)

#घोषणा NFP_FL_ENABLE_FLOW_MERGE	BIT(0)
#घोषणा NFP_FL_ENABLE_LAG		BIT(1)

#घोषणा NFP_FL_FEATS_HOST \
	(NFP_FL_FEATS_GENEVE | \
	NFP_FL_NBI_MTU_SETTING | \
	NFP_FL_FEATS_GENEVE_OPT | \
	NFP_FL_FEATS_VLAN_PCP | \
	NFP_FL_FEATS_VF_RLIM | \
	NFP_FL_FEATS_FLOW_MOD | \
	NFP_FL_FEATS_PRE_TUN_RULES | \
	NFP_FL_FEATS_IPV6_TUN | \
	NFP_FL_FEATS_VLAN_QINQ | \
	NFP_FL_FEATS_QOS_PPS)

काष्ठा nfp_fl_mask_id अणु
	काष्ठा circ_buf mask_id_मुक्त_list;
	kसमय_प्रकार *last_used;
	u8 init_unallocated;
पूर्ण;

काष्ठा nfp_fl_stats_id अणु
	काष्ठा circ_buf मुक्त_list;
	u32 init_unalloc;
	u8 repeated_em_count;
पूर्ण;

/**
 * काष्ठा nfp_fl_tunnel_offloads - priv data क्रम tunnel offloads
 * @offloaded_macs:	Hashtable of the offloaded MAC addresses
 * @ipv4_off_list:	List of IPv4 addresses to offload
 * @ipv6_off_list:	List of IPv6 addresses to offload
 * @neigh_off_list_v4:	List of IPv4 neighbour offloads
 * @neigh_off_list_v6:	List of IPv6 neighbour offloads
 * @ipv4_off_lock:	Lock क्रम the IPv4 address list
 * @ipv6_off_lock:	Lock क्रम the IPv6 address list
 * @neigh_off_lock_v4:	Lock क्रम the IPv4 neighbour address list
 * @neigh_off_lock_v6:	Lock क्रम the IPv6 neighbour address list
 * @mac_off_ids:	IDA to manage id assignment क्रम offloaded MACs
 * @neigh_nb:		Notअगरier to monitor neighbour state
 */
काष्ठा nfp_fl_tunnel_offloads अणु
	काष्ठा rhashtable offloaded_macs;
	काष्ठा list_head ipv4_off_list;
	काष्ठा list_head ipv6_off_list;
	काष्ठा list_head neigh_off_list_v4;
	काष्ठा list_head neigh_off_list_v6;
	काष्ठा mutex ipv4_off_lock;
	काष्ठा mutex ipv6_off_lock;
	spinlock_t neigh_off_lock_v4;
	spinlock_t neigh_off_lock_v6;
	काष्ठा ida mac_off_ids;
	काष्ठा notअगरier_block neigh_nb;
पूर्ण;

/**
 * काष्ठा nfp_mtu_conf - manage MTU setting
 * @portnum:		NFP port number of repr with requested MTU change
 * @requested_val:	MTU value requested क्रम repr
 * @ack:		Received ack that MTU has been correctly set
 * @रुको_q:		Wait queue क्रम MTU acknowledgements
 * @lock:		Lock क्रम setting/पढ़ोing MTU variables
 */
काष्ठा nfp_mtu_conf अणु
	u32 portnum;
	अचिन्हित पूर्णांक requested_val;
	bool ack;
	रुको_queue_head_t रुको_q;
	spinlock_t lock;
पूर्ण;

/**
 * काष्ठा nfp_fl_lag - Flower APP priv data क्रम link aggregation
 * @work:		Work queue क्रम writing configs to the HW
 * @lock:		Lock to protect lag_group_list
 * @group_list:		List of all master/slave groups offloaded
 * @ida_handle:		IDA to handle group ids
 * @pkt_num:		Incremented क्रम each config packet sent
 * @batch_ver:		Incremented क्रम each batch of config packets
 * @global_inst:	Instance allocator क्रम groups
 * @rst_cfg:		Marker to reset HW LAG config
 * @retrans_skbs:	Cmsgs that could not be processed by HW and require
 *			retransmission
 */
काष्ठा nfp_fl_lag अणु
	काष्ठा delayed_work work;
	काष्ठा mutex lock;
	काष्ठा list_head group_list;
	काष्ठा ida ida_handle;
	अचिन्हित पूर्णांक pkt_num;
	अचिन्हित पूर्णांक batch_ver;
	u8 global_inst;
	bool rst_cfg;
	काष्ठा sk_buff_head retrans_skbs;
पूर्ण;

/**
 * काष्ठा nfp_fl_पूर्णांकernal_ports - Flower APP priv data क्रम additional ports
 * @port_ids:	Assignment of ids to any additional ports
 * @lock:	Lock क्रम extra ports list
 */
काष्ठा nfp_fl_पूर्णांकernal_ports अणु
	काष्ठा idr port_ids;
	spinlock_t lock;
पूर्ण;

/**
 * काष्ठा nfp_flower_priv - Flower APP per-vNIC priv data
 * @app:		Back poपूर्णांकer to app
 * @nn:			Poपूर्णांकer to vNIC
 * @mask_id_seed:	Seed used क्रम mask hash table
 * @flower_version:	HW version of flower
 * @flower_ext_feats:	Biपंचांगap of extra features the HW supports
 * @flower_en_feats:	Biपंचांगap of features enabled by HW
 * @stats_ids:		List of मुक्त stats ids
 * @mask_ids:		List of मुक्त mask ids
 * @mask_table:		Hash table used to store masks
 * @stats_ring_size:	Maximum number of allowed stats ids
 * @flow_table:		Hash table used to store flower rules
 * @stats:		Stored stats updates क्रम flower rules
 * @stats_lock:		Lock क्रम flower rule stats updates
 * @stats_ctx_table:	Hash table to map stats contexts to its flow rule
 * @cmsg_work:		Workqueue क्रम control messages processing
 * @cmsg_skbs_high:	List of higher priority skbs क्रम control message
 *			processing
 * @cmsg_skbs_low:	List of lower priority skbs क्रम control message
 *			processing
 * @tun:		Tunnel offload data
 * @reअगरy_replies:	atomically stores the number of replies received
 *			from firmware क्रम repr reअगरy
 * @reअगरy_रुको_queue:	रुको queue क्रम repr reअगरy response counting
 * @mtu_conf:		Configuration of repr MTU value
 * @nfp_lag:		Link aggregation data block
 * @indr_block_cb_priv:	List of priv data passed to indirect block cbs
 * @non_repr_priv:	List of offloaded non-repr ports and their priv data
 * @active_mem_unit:	Current active memory unit क्रम flower rules
 * @total_mem_units:	Total number of available memory units क्रम flower rules
 * @पूर्णांकernal_ports:	Internal port ids used in offloaded rules
 * @qos_stats_work:	Workqueue क्रम qos stats processing
 * @qos_rate_limiters:	Current active qos rate limiters
 * @qos_stats_lock:	Lock on qos stats updates
 * @pre_tun_rule_cnt:	Number of pre-tunnel rules offloaded
 * @merge_table:	Hash table to store merged flows
 */
काष्ठा nfp_flower_priv अणु
	काष्ठा nfp_app *app;
	काष्ठा nfp_net *nn;
	u32 mask_id_seed;
	u64 flower_version;
	u64 flower_ext_feats;
	u8 flower_en_feats;
	काष्ठा nfp_fl_stats_id stats_ids;
	काष्ठा nfp_fl_mask_id mask_ids;
	DECLARE_HASHTABLE(mask_table, NFP_FLOWER_MASK_HASH_BITS);
	u32 stats_ring_size;
	काष्ठा rhashtable flow_table;
	काष्ठा nfp_fl_stats *stats;
	spinlock_t stats_lock; /* lock stats */
	काष्ठा rhashtable stats_ctx_table;
	काष्ठा work_काष्ठा cmsg_work;
	काष्ठा sk_buff_head cmsg_skbs_high;
	काष्ठा sk_buff_head cmsg_skbs_low;
	काष्ठा nfp_fl_tunnel_offloads tun;
	atomic_t reअगरy_replies;
	रुको_queue_head_t reअगरy_रुको_queue;
	काष्ठा nfp_mtu_conf mtu_conf;
	काष्ठा nfp_fl_lag nfp_lag;
	काष्ठा list_head indr_block_cb_priv;
	काष्ठा list_head non_repr_priv;
	अचिन्हित पूर्णांक active_mem_unit;
	अचिन्हित पूर्णांक total_mem_units;
	काष्ठा nfp_fl_पूर्णांकernal_ports पूर्णांकernal_ports;
	काष्ठा delayed_work qos_stats_work;
	अचिन्हित पूर्णांक qos_rate_limiters;
	spinlock_t qos_stats_lock; /* Protect the qos stats */
	पूर्णांक pre_tun_rule_cnt;
	काष्ठा rhashtable merge_table;
पूर्ण;

/**
 * काष्ठा nfp_fl_qos - Flower APP priv data क्रम quality of service
 * @netdev_port_id:	NFP port number of repr with qos info
 * @curr_stats:		Currently stored stats updates क्रम qos info
 * @prev_stats:		Previously stored updates क्रम qos info
 * @last_update:	Stored समय when last stats were updated
 */
काष्ठा nfp_fl_qos अणु
	u32 netdev_port_id;
	काष्ठा nfp_stat_pair curr_stats;
	काष्ठा nfp_stat_pair prev_stats;
	u64 last_update;
पूर्ण;

/**
 * काष्ठा nfp_flower_repr_priv - Flower APP per-repr priv data
 * @nfp_repr:		Back poपूर्णांकer to nfp_repr
 * @lag_port_flags:	Extended port flags to record lag state of repr
 * @mac_offloaded:	Flag indicating a MAC address is offloaded क्रम repr
 * @offloaded_mac_addr:	MAC address that has been offloaded क्रम repr
 * @block_shared:	Flag indicating अगर offload applies to shared blocks
 * @mac_list:		List entry of reprs that share the same offloaded MAC
 * @qos_table:		Stored info on filters implementing qos
 * @on_bridge:		Indicates अगर the repr is attached to a bridge
 */
काष्ठा nfp_flower_repr_priv अणु
	काष्ठा nfp_repr *nfp_repr;
	अचिन्हित दीर्घ lag_port_flags;
	bool mac_offloaded;
	u8 offloaded_mac_addr[ETH_ALEN];
	bool block_shared;
	काष्ठा list_head mac_list;
	काष्ठा nfp_fl_qos qos_table;
	bool on_bridge;
पूर्ण;

/**
 * काष्ठा nfp_flower_non_repr_priv - Priv data क्रम non-repr offloaded ports
 * @list:		List entry of offloaded reprs
 * @netdev:		Poपूर्णांकer to non-repr net_device
 * @ref_count:		Number of references held क्रम this priv data
 * @mac_offloaded:	Flag indicating a MAC address is offloaded क्रम device
 * @offloaded_mac_addr:	MAC address that has been offloaded क्रम dev
 */
काष्ठा nfp_flower_non_repr_priv अणु
	काष्ठा list_head list;
	काष्ठा net_device *netdev;
	पूर्णांक ref_count;
	bool mac_offloaded;
	u8 offloaded_mac_addr[ETH_ALEN];
पूर्ण;

काष्ठा nfp_fl_key_ls अणु
	u32 key_layer_two;
	u8 key_layer;
	पूर्णांक key_size;
पूर्ण;

काष्ठा nfp_fl_rule_metadata अणु
	u8 key_len;
	u8 mask_len;
	u8 act_len;
	u8 flags;
	__be32 host_ctx_id;
	__be64 host_cookie __packed;
	__be64 flow_version __packed;
	__be32 लघुcut;
पूर्ण;

काष्ठा nfp_fl_stats अणु
	u64 pkts;
	u64 bytes;
	u64 used;
पूर्ण;

/**
 * काष्ठा nfp_ipv6_addr_entry - cached IPv6 addresses
 * @ipv6_addr:	IP address
 * @ref_count:	number of rules currently using this IP
 * @list:	list poपूर्णांकer
 */
काष्ठा nfp_ipv6_addr_entry अणु
	काष्ठा in6_addr ipv6_addr;
	पूर्णांक ref_count;
	काष्ठा list_head list;
पूर्ण;

काष्ठा nfp_fl_payload अणु
	काष्ठा nfp_fl_rule_metadata meta;
	अचिन्हित दीर्घ tc_flower_cookie;
	काष्ठा rhash_head fl_node;
	काष्ठा rcu_head rcu;
	__be32 nfp_tun_ipv4_addr;
	काष्ठा nfp_ipv6_addr_entry *nfp_tun_ipv6;
	काष्ठा net_device *ingress_dev;
	अक्षर *unmasked_data;
	अक्षर *mask_data;
	अक्षर *action_data;
	काष्ठा list_head linked_flows;
	bool in_hw;
	काष्ठा अणु
		काष्ठा net_device *dev;
		__be16 vlan_tci;
		__be16 port_idx;
	पूर्ण pre_tun_rule;
पूर्ण;

काष्ठा nfp_fl_payload_link अणु
	/* A link contains a poपूर्णांकer to a merge flow and an associated sub_flow.
	 * Each merge flow will feature in 2 links to its underlying sub_flows.
	 * A sub_flow will have at least 1 link to a merge flow or more अगर it
	 * has been used to create multiple merge flows.
	 *
	 * For a merge flow, 'linked_flows' in its nfp_fl_payload काष्ठा lists
	 * all links to sub_flows (sub_flow.flow) via merge.list.
	 * For a sub_flow, 'linked_flows' gives all links to merge flows it has
	 * क्रमmed (merge_flow.flow) via sub_flow.list.
	 */
	काष्ठा अणु
		काष्ठा list_head list;
		काष्ठा nfp_fl_payload *flow;
	पूर्ण merge_flow, sub_flow;
पूर्ण;

बाह्य स्थिर काष्ठा rhashtable_params nfp_flower_table_params;
बाह्य स्थिर काष्ठा rhashtable_params merge_table_params;

काष्ठा nfp_merge_info अणु
	u64 parent_ctx;
	काष्ठा rhash_head ht_node;
पूर्ण;

काष्ठा nfp_fl_stats_frame अणु
	__be32 stats_con_id;
	__be32 pkt_count;
	__be64 byte_count;
	__be64 stats_cookie;
पूर्ण;

अटल अंतरभूत bool
nfp_flower_पूर्णांकernal_port_can_offload(काष्ठा nfp_app *app,
				     काष्ठा net_device *netdev)
अणु
	काष्ठा nfp_flower_priv *app_priv = app->priv;

	अगर (!(app_priv->flower_en_feats & NFP_FL_ENABLE_FLOW_MERGE))
		वापस false;
	अगर (!netdev->rtnl_link_ops)
		वापस false;
	अगर (!म_भेद(netdev->rtnl_link_ops->kind, "openvswitch"))
		वापस true;

	वापस false;
पूर्ण

/* The address of the merged flow acts as its cookie.
 * Cookies supplied to us by TC flower are also addresses to allocated
 * memory and thus this scheme should not generate any collisions.
 */
अटल अंतरभूत bool nfp_flower_is_merge_flow(काष्ठा nfp_fl_payload *flow_pay)
अणु
	वापस flow_pay->tc_flower_cookie == (अचिन्हित दीर्घ)flow_pay;
पूर्ण

अटल अंतरभूत bool nfp_flower_is_supported_bridge(काष्ठा net_device *netdev)
अणु
	वापस netअगर_is_ovs_master(netdev);
पूर्ण

पूर्णांक nfp_flower_metadata_init(काष्ठा nfp_app *app, u64 host_ctx_count,
			     अचिन्हित पूर्णांक host_ctx_split);
व्योम nfp_flower_metadata_cleanup(काष्ठा nfp_app *app);

पूर्णांक nfp_flower_setup_tc(काष्ठा nfp_app *app, काष्ठा net_device *netdev,
			क्रमागत tc_setup_type type, व्योम *type_data);
पूर्णांक nfp_flower_merge_offloaded_flows(काष्ठा nfp_app *app,
				     काष्ठा nfp_fl_payload *sub_flow1,
				     काष्ठा nfp_fl_payload *sub_flow2);
पूर्णांक nfp_flower_compile_flow_match(काष्ठा nfp_app *app,
				  काष्ठा flow_cls_offload *flow,
				  काष्ठा nfp_fl_key_ls *key_ls,
				  काष्ठा net_device *netdev,
				  काष्ठा nfp_fl_payload *nfp_flow,
				  क्रमागत nfp_flower_tun_type tun_type,
				  काष्ठा netlink_ext_ack *extack);
पूर्णांक nfp_flower_compile_action(काष्ठा nfp_app *app,
			      काष्ठा flow_cls_offload *flow,
			      काष्ठा net_device *netdev,
			      काष्ठा nfp_fl_payload *nfp_flow,
			      काष्ठा netlink_ext_ack *extack);
पूर्णांक nfp_compile_flow_metadata(काष्ठा nfp_app *app,
			      काष्ठा flow_cls_offload *flow,
			      काष्ठा nfp_fl_payload *nfp_flow,
			      काष्ठा net_device *netdev,
			      काष्ठा netlink_ext_ack *extack);
व्योम __nfp_modअगरy_flow_metadata(काष्ठा nfp_flower_priv *priv,
				काष्ठा nfp_fl_payload *nfp_flow);
पूर्णांक nfp_modअगरy_flow_metadata(काष्ठा nfp_app *app,
			     काष्ठा nfp_fl_payload *nfp_flow);

काष्ठा nfp_fl_payload *
nfp_flower_search_fl_table(काष्ठा nfp_app *app, अचिन्हित दीर्घ tc_flower_cookie,
			   काष्ठा net_device *netdev);
काष्ठा nfp_fl_payload *
nfp_flower_get_fl_payload_from_ctx(काष्ठा nfp_app *app, u32 ctx_id);
काष्ठा nfp_fl_payload *
nfp_flower_हटाओ_fl_table(काष्ठा nfp_app *app, अचिन्हित दीर्घ tc_flower_cookie);

व्योम nfp_flower_rx_flow_stats(काष्ठा nfp_app *app, काष्ठा sk_buff *skb);

पूर्णांक nfp_tunnel_config_start(काष्ठा nfp_app *app);
व्योम nfp_tunnel_config_stop(काष्ठा nfp_app *app);
पूर्णांक nfp_tunnel_mac_event_handler(काष्ठा nfp_app *app,
				 काष्ठा net_device *netdev,
				 अचिन्हित दीर्घ event, व्योम *ptr);
व्योम nfp_tunnel_del_ipv4_off(काष्ठा nfp_app *app, __be32 ipv4);
व्योम nfp_tunnel_add_ipv4_off(काष्ठा nfp_app *app, __be32 ipv4);
व्योम
nfp_tunnel_put_ipv6_off(काष्ठा nfp_app *app, काष्ठा nfp_ipv6_addr_entry *entry);
काष्ठा nfp_ipv6_addr_entry *
nfp_tunnel_add_ipv6_off(काष्ठा nfp_app *app, काष्ठा in6_addr *ipv6);
व्योम nfp_tunnel_request_route_v4(काष्ठा nfp_app *app, काष्ठा sk_buff *skb);
व्योम nfp_tunnel_request_route_v6(काष्ठा nfp_app *app, काष्ठा sk_buff *skb);
व्योम nfp_tunnel_keep_alive(काष्ठा nfp_app *app, काष्ठा sk_buff *skb);
व्योम nfp_tunnel_keep_alive_v6(काष्ठा nfp_app *app, काष्ठा sk_buff *skb);
व्योम nfp_flower_lag_init(काष्ठा nfp_fl_lag *lag);
व्योम nfp_flower_lag_cleanup(काष्ठा nfp_fl_lag *lag);
पूर्णांक nfp_flower_lag_reset(काष्ठा nfp_fl_lag *lag);
पूर्णांक nfp_flower_lag_netdev_event(काष्ठा nfp_flower_priv *priv,
				काष्ठा net_device *netdev,
				अचिन्हित दीर्घ event, व्योम *ptr);
bool nfp_flower_lag_unprocessed_msg(काष्ठा nfp_app *app, काष्ठा sk_buff *skb);
पूर्णांक nfp_flower_lag_populate_pre_action(काष्ठा nfp_app *app,
				       काष्ठा net_device *master,
				       काष्ठा nfp_fl_pre_lag *pre_act,
				       काष्ठा netlink_ext_ack *extack);
पूर्णांक nfp_flower_lag_get_output_id(काष्ठा nfp_app *app,
				 काष्ठा net_device *master);
व्योम nfp_flower_qos_init(काष्ठा nfp_app *app);
व्योम nfp_flower_qos_cleanup(काष्ठा nfp_app *app);
पूर्णांक nfp_flower_setup_qos_offload(काष्ठा nfp_app *app, काष्ठा net_device *netdev,
				 काष्ठा tc_cls_matchall_offload *flow);
व्योम nfp_flower_stats_rlim_reply(काष्ठा nfp_app *app, काष्ठा sk_buff *skb);
पूर्णांक nfp_flower_indr_setup_tc_cb(काष्ठा net_device *netdev, काष्ठा Qdisc *sch, व्योम *cb_priv,
				क्रमागत tc_setup_type type, व्योम *type_data,
				व्योम *data,
				व्योम (*cleanup)(काष्ठा flow_block_cb *block_cb));
व्योम nfp_flower_setup_indr_tc_release(व्योम *cb_priv);

व्योम
__nfp_flower_non_repr_priv_get(काष्ठा nfp_flower_non_repr_priv *non_repr_priv);
काष्ठा nfp_flower_non_repr_priv *
nfp_flower_non_repr_priv_get(काष्ठा nfp_app *app, काष्ठा net_device *netdev);
व्योम
__nfp_flower_non_repr_priv_put(काष्ठा nfp_flower_non_repr_priv *non_repr_priv);
व्योम
nfp_flower_non_repr_priv_put(काष्ठा nfp_app *app, काष्ठा net_device *netdev);
u32 nfp_flower_get_port_id_from_netdev(काष्ठा nfp_app *app,
				       काष्ठा net_device *netdev);
पूर्णांक nfp_flower_xmit_pre_tun_flow(काष्ठा nfp_app *app,
				 काष्ठा nfp_fl_payload *flow);
पूर्णांक nfp_flower_xmit_pre_tun_del_flow(काष्ठा nfp_app *app,
				     काष्ठा nfp_fl_payload *flow);
#पूर्ण_अगर
