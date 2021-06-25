<शैली गुरु>
/* Broadcom NetXtreme-C/E network driver.
 *
 * Copyright (c) 2017 Broadcom Limited
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 */

#अगर_अघोषित BNXT_TC_H
#घोषणा BNXT_TC_H

#अगर_घोषित CONFIG_BNXT_FLOWER_OFFLOAD

#समावेश <net/ip_tunnels.h>

/* Structs used क्रम storing the filter/actions of the TC cmd.
 */
काष्ठा bnxt_tc_l2_key अणु
	u8		dmac[ETH_ALEN];
	u8		smac[ETH_ALEN];
	__be16		inner_vlan_tpid;
	__be16		inner_vlan_tci;
	__be16		ether_type;
	u8		num_vlans;
	u8		dir;
#घोषणा BNXT_सूची_RX	1
#घोषणा BNXT_सूची_TX	0
पूर्ण;

काष्ठा bnxt_tc_l3_key अणु
	जोड़ अणु
		काष्ठा अणु
			काष्ठा in_addr daddr;
			काष्ठा in_addr saddr;
		पूर्ण ipv4;
		काष्ठा अणु
			काष्ठा in6_addr daddr;
			काष्ठा in6_addr saddr;
		पूर्ण ipv6;
	पूर्ण;
पूर्ण;

काष्ठा bnxt_tc_l4_key अणु
	u8  ip_proto;
	जोड़ अणु
		काष्ठा अणु
			__be16 sport;
			__be16 dport;
		पूर्ण ports;
		काष्ठा अणु
			u8 type;
			u8 code;
		पूर्ण icmp;
	पूर्ण;
पूर्ण;

काष्ठा bnxt_tc_tunnel_key अणु
	काष्ठा bnxt_tc_l2_key	l2;
	काष्ठा bnxt_tc_l3_key	l3;
	काष्ठा bnxt_tc_l4_key	l4;
	__be32			id;
पूर्ण;

#घोषणा bnxt_eth_addr_key_mask_invalid(eth_addr, eth_addr_mask)		\
	((is_wildcard(&(eth_addr)[0], ETH_ALEN) &&			\
	 is_wildcard(&(eth_addr)[ETH_ALEN / 2], ETH_ALEN)) ||		\
	(is_wildcard(&(eth_addr_mask)[0], ETH_ALEN) &&			\
	 is_wildcard(&(eth_addr_mask)[ETH_ALEN / 2], ETH_ALEN)))

काष्ठा bnxt_tc_actions अणु
	u32				flags;
#घोषणा BNXT_TC_ACTION_FLAG_FWD			BIT(0)
#घोषणा BNXT_TC_ACTION_FLAG_FWD_VXLAN		BIT(1)
#घोषणा BNXT_TC_ACTION_FLAG_PUSH_VLAN		BIT(3)
#घोषणा BNXT_TC_ACTION_FLAG_POP_VLAN		BIT(4)
#घोषणा BNXT_TC_ACTION_FLAG_DROP		BIT(5)
#घोषणा BNXT_TC_ACTION_FLAG_TUNNEL_ENCAP	BIT(6)
#घोषणा BNXT_TC_ACTION_FLAG_TUNNEL_DECAP	BIT(7)
#घोषणा BNXT_TC_ACTION_FLAG_L2_REWRITE		BIT(8)
#घोषणा BNXT_TC_ACTION_FLAG_NAT_XLATE		BIT(9)

	u16				dst_fid;
	काष्ठा net_device		*dst_dev;
	__be16				push_vlan_tpid;
	__be16				push_vlan_tci;

	/* tunnel encap */
	काष्ठा ip_tunnel_key		tun_encap_key;
#घोषणा	PEDIT_OFFSET_SMAC_LAST_4_BYTES		0x8
	__be16				l2_reग_लिखो_dmac[3];
	__be16				l2_reग_लिखो_smac[3];
	काष्ठा अणु
		bool src_xlate;  /* true => translate src,
				  * false => translate dst
				  * Mutually exclusive, i.e cannot set both
				  */
		bool l3_is_ipv4; /* false means L3 is ipv6 */
		काष्ठा bnxt_tc_l3_key l3;
		काष्ठा bnxt_tc_l4_key l4;
	पूर्ण nat;
पूर्ण;

काष्ठा bnxt_tc_flow अणु
	u32				flags;
#घोषणा BNXT_TC_FLOW_FLAGS_ETH_ADDRS		BIT(1)
#घोषणा BNXT_TC_FLOW_FLAGS_IPV4_ADDRS		BIT(2)
#घोषणा BNXT_TC_FLOW_FLAGS_IPV6_ADDRS		BIT(3)
#घोषणा BNXT_TC_FLOW_FLAGS_PORTS		BIT(4)
#घोषणा BNXT_TC_FLOW_FLAGS_ICMP			BIT(5)
#घोषणा BNXT_TC_FLOW_FLAGS_TUNL_ETH_ADDRS	BIT(6)
#घोषणा BNXT_TC_FLOW_FLAGS_TUNL_IPV4_ADDRS	BIT(7)
#घोषणा BNXT_TC_FLOW_FLAGS_TUNL_IPV6_ADDRS	BIT(8)
#घोषणा BNXT_TC_FLOW_FLAGS_TUNL_PORTS		BIT(9)
#घोषणा BNXT_TC_FLOW_FLAGS_TUNL_ID		BIT(10)
#घोषणा BNXT_TC_FLOW_FLAGS_TUNNEL	(BNXT_TC_FLOW_FLAGS_TUNL_ETH_ADDRS | \
					 BNXT_TC_FLOW_FLAGS_TUNL_IPV4_ADDRS | \
					 BNXT_TC_FLOW_FLAGS_TUNL_IPV6_ADDRS |\
					 BNXT_TC_FLOW_FLAGS_TUNL_PORTS |\
					 BNXT_TC_FLOW_FLAGS_TUNL_ID)

	/* flow applicable to pkts ingressing on this fid */
	u16				src_fid;
	काष्ठा bnxt_tc_l2_key		l2_key;
	काष्ठा bnxt_tc_l2_key		l2_mask;
	काष्ठा bnxt_tc_l3_key		l3_key;
	काष्ठा bnxt_tc_l3_key		l3_mask;
	काष्ठा bnxt_tc_l4_key		l4_key;
	काष्ठा bnxt_tc_l4_key		l4_mask;
	काष्ठा ip_tunnel_key		tun_key;
	काष्ठा ip_tunnel_key		tun_mask;

	काष्ठा bnxt_tc_actions		actions;

	/* updated stats accounting क्रम hw-counter wrap-around */
	काष्ठा bnxt_tc_flow_stats	stats;
	/* previous snap-shot of stats */
	काष्ठा bnxt_tc_flow_stats	prev_stats;
	अचिन्हित दीर्घ			lastused; /* jअगरfies */
	/* क्रम calculating delta from prev_stats and
	 * updating prev_stats atomically.
	 */
	spinlock_t			stats_lock;
पूर्ण;

/* Tunnel encap/decap hash table
 * This table is used to मुख्यtain a list of flows that use
 * the same tunnel encap/decap params (ip_daddrs, vni, udp_dport)
 * and the FW वापसed handle.
 * A separate table is मुख्यtained क्रम encap and decap
 */
काष्ठा bnxt_tc_tunnel_node अणु
	काष्ठा ip_tunnel_key		key;
	काष्ठा rhash_head		node;

	/* tunnel l2 info */
	काष्ठा bnxt_tc_l2_key		l2_info;

#घोषणा	INVALID_TUNNEL_HANDLE		cpu_to_le32(0xffffffff)
	/* tunnel handle वापसed by FW */
	__le32				tunnel_handle;

	u32				refcount;
	काष्ठा rcu_head			rcu;
पूर्ण;

/* L2 hash table
 * The same data-काष्ठा is used क्रम L2-flow table and L2-tunnel table.
 * The L2 part of a flow or tunnel is stored in a hash table.
 * A flow that shares the same L2 key/mask with an
 * alपढ़ोy existing flow/tunnel must refer to it's flow handle or
 * decap_filter_id respectively.
 */
काष्ठा bnxt_tc_l2_node अणु
	/* hash key: first 16b of key */
#घोषणा BNXT_TC_L2_KEY_LEN			16
	काष्ठा bnxt_tc_l2_key	key;
	काष्ठा rhash_head	node;

	/* a linked list of flows that share the same l2 key */
	काष्ठा list_head	common_l2_flows;

	/* number of flows/tunnels sharing the l2 key */
	u16			refcount;

	काष्ठा rcu_head		rcu;
पूर्ण;

काष्ठा bnxt_tc_flow_node अणु
	/* hash key: provided by TC */
	अचिन्हित दीर्घ			cookie;
	काष्ठा rhash_head		node;

	काष्ठा bnxt_tc_flow		flow;

	__le64				ext_flow_handle;
	__le16				flow_handle;
	__le32				flow_id;

	/* L2 node in l2 hashtable that shares flow's l2 key */
	काष्ठा bnxt_tc_l2_node		*l2_node;
	/* क्रम the shared_flows list मुख्यtained in l2_node */
	काष्ठा list_head		l2_list_node;

	/* tunnel encap related */
	काष्ठा bnxt_tc_tunnel_node	*encap_node;

	/* tunnel decap related */
	काष्ठा bnxt_tc_tunnel_node	*decap_node;
	/* L2 node in tunnel-l2 hashtable that shares flow's tunnel l2 key */
	काष्ठा bnxt_tc_l2_node		*decap_l2_node;
	/* क्रम the shared_flows list मुख्यtained in tunnel decap l2_node */
	काष्ठा list_head		decap_l2_list_node;

	काष्ठा rcu_head			rcu;
पूर्ण;

पूर्णांक bnxt_tc_setup_flower(काष्ठा bnxt *bp, u16 src_fid,
			 काष्ठा flow_cls_offload *cls_flower);
पूर्णांक bnxt_init_tc(काष्ठा bnxt *bp);
व्योम bnxt_shutकरोwn_tc(काष्ठा bnxt *bp);
व्योम bnxt_tc_flow_stats_work(काष्ठा bnxt *bp);

अटल अंतरभूत bool bnxt_tc_flower_enabled(काष्ठा bnxt *bp)
अणु
	वापस bp->tc_info && bp->tc_info->enabled;
पूर्ण

#अन्यथा /* CONFIG_BNXT_FLOWER_OFFLOAD */

अटल अंतरभूत पूर्णांक bnxt_tc_setup_flower(काष्ठा bnxt *bp, u16 src_fid,
				       काष्ठा flow_cls_offload *cls_flower)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक bnxt_init_tc(काष्ठा bnxt *bp)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम bnxt_shutकरोwn_tc(काष्ठा bnxt *bp)
अणु
पूर्ण

अटल अंतरभूत व्योम bnxt_tc_flow_stats_work(काष्ठा bnxt *bp)
अणु
पूर्ण

अटल अंतरभूत bool bnxt_tc_flower_enabled(काष्ठा bnxt *bp)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर /* CONFIG_BNXT_FLOWER_OFFLOAD */
#पूर्ण_अगर /* BNXT_TC_H */
