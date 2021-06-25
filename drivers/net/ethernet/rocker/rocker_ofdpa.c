<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * drivers/net/ethernet/rocker/rocker_ofdpa.c - Rocker चयन OF-DPA-like
 *					        implementation
 * Copyright (c) 2014 Scott Feldman <sfeldma@gmail.com>
 * Copyright (c) 2014-2016 Jiri Pirko <jiri@mellanox.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/hashtable.h>
#समावेश <linux/crc32.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/अगर_bridge.h>
#समावेश <net/neighbour.h>
#समावेश <net/चयनdev.h>
#समावेश <net/ip_fib.h>
#समावेश <net/nexthop.h>
#समावेश <net/arp.h>

#समावेश "rocker.h"
#समावेश "rocker_tlv.h"

काष्ठा ofdpa_flow_tbl_key अणु
	u32 priority;
	क्रमागत rocker_of_dpa_table_id tbl_id;
	जोड़ अणु
		काष्ठा अणु
			u32 in_pport;
			u32 in_pport_mask;
			क्रमागत rocker_of_dpa_table_id जाओ_tbl;
		पूर्ण ig_port;
		काष्ठा अणु
			u32 in_pport;
			__be16 vlan_id;
			__be16 vlan_id_mask;
			क्रमागत rocker_of_dpa_table_id जाओ_tbl;
			bool untagged;
			__be16 new_vlan_id;
		पूर्ण vlan;
		काष्ठा अणु
			u32 in_pport;
			u32 in_pport_mask;
			__be16 eth_type;
			u8 eth_dst[ETH_ALEN];
			u8 eth_dst_mask[ETH_ALEN];
			__be16 vlan_id;
			__be16 vlan_id_mask;
			क्रमागत rocker_of_dpa_table_id जाओ_tbl;
			bool copy_to_cpu;
		पूर्ण term_mac;
		काष्ठा अणु
			__be16 eth_type;
			__be32 dst4;
			__be32 dst4_mask;
			क्रमागत rocker_of_dpa_table_id जाओ_tbl;
			u32 group_id;
		पूर्ण ucast_routing;
		काष्ठा अणु
			u8 eth_dst[ETH_ALEN];
			u8 eth_dst_mask[ETH_ALEN];
			पूर्णांक has_eth_dst;
			पूर्णांक has_eth_dst_mask;
			__be16 vlan_id;
			u32 tunnel_id;
			क्रमागत rocker_of_dpa_table_id जाओ_tbl;
			u32 group_id;
			bool copy_to_cpu;
		पूर्ण bridge;
		काष्ठा अणु
			u32 in_pport;
			u32 in_pport_mask;
			u8 eth_src[ETH_ALEN];
			u8 eth_src_mask[ETH_ALEN];
			u8 eth_dst[ETH_ALEN];
			u8 eth_dst_mask[ETH_ALEN];
			__be16 eth_type;
			__be16 vlan_id;
			__be16 vlan_id_mask;
			u8 ip_proto;
			u8 ip_proto_mask;
			u8 ip_tos;
			u8 ip_tos_mask;
			u32 group_id;
		पूर्ण acl;
	पूर्ण;
पूर्ण;

काष्ठा ofdpa_flow_tbl_entry अणु
	काष्ठा hlist_node entry;
	u32 cmd;
	u64 cookie;
	काष्ठा ofdpa_flow_tbl_key key;
	माप_प्रकार key_len;
	u32 key_crc32; /* key */
	काष्ठा fib_info *fi;
पूर्ण;

काष्ठा ofdpa_group_tbl_entry अणु
	काष्ठा hlist_node entry;
	u32 cmd;
	u32 group_id; /* key */
	u16 group_count;
	u32 *group_ids;
	जोड़ अणु
		काष्ठा अणु
			u8 pop_vlan;
		पूर्ण l2_पूर्णांकerface;
		काष्ठा अणु
			u8 eth_src[ETH_ALEN];
			u8 eth_dst[ETH_ALEN];
			__be16 vlan_id;
			u32 group_id;
		पूर्ण l2_reग_लिखो;
		काष्ठा अणु
			u8 eth_src[ETH_ALEN];
			u8 eth_dst[ETH_ALEN];
			__be16 vlan_id;
			bool ttl_check;
			u32 group_id;
		पूर्ण l3_unicast;
	पूर्ण;
पूर्ण;

काष्ठा ofdpa_fdb_tbl_entry अणु
	काष्ठा hlist_node entry;
	u32 key_crc32; /* key */
	bool learned;
	अचिन्हित दीर्घ touched;
	काष्ठा ofdpa_fdb_tbl_key अणु
		काष्ठा ofdpa_port *ofdpa_port;
		u8 addr[ETH_ALEN];
		__be16 vlan_id;
	पूर्ण key;
पूर्ण;

काष्ठा ofdpa_पूर्णांकernal_vlan_tbl_entry अणु
	काष्ठा hlist_node entry;
	पूर्णांक अगरindex; /* key */
	u32 ref_count;
	__be16 vlan_id;
पूर्ण;

काष्ठा ofdpa_neigh_tbl_entry अणु
	काष्ठा hlist_node entry;
	__be32 ip_addr; /* key */
	काष्ठा net_device *dev;
	u32 ref_count;
	u32 index;
	u8 eth_dst[ETH_ALEN];
	bool ttl_check;
पूर्ण;

क्रमागत अणु
	OFDPA_CTRL_LINK_LOCAL_MCAST,
	OFDPA_CTRL_LOCAL_ARP,
	OFDPA_CTRL_IPV4_MCAST,
	OFDPA_CTRL_IPV6_MCAST,
	OFDPA_CTRL_DFLT_BRIDGING,
	OFDPA_CTRL_DFLT_OVS,
	OFDPA_CTRL_MAX,
पूर्ण;

#घोषणा OFDPA_INTERNAL_VLAN_ID_BASE	0x0f00
#घोषणा OFDPA_N_INTERNAL_VLANS		255
#घोषणा OFDPA_VLAN_BITMAP_LEN		BITS_TO_LONGS(VLAN_N_VID)
#घोषणा OFDPA_INTERNAL_VLAN_BITMAP_LEN	BITS_TO_LONGS(OFDPA_N_INTERNAL_VLANS)
#घोषणा OFDPA_UNTAGGED_VID 0

काष्ठा ofdpa अणु
	काष्ठा rocker *rocker;
	DECLARE_HASHTABLE(flow_tbl, 16);
	spinlock_t flow_tbl_lock;		/* क्रम flow tbl accesses */
	u64 flow_tbl_next_cookie;
	DECLARE_HASHTABLE(group_tbl, 16);
	spinlock_t group_tbl_lock;		/* क्रम group tbl accesses */
	काष्ठा समयr_list fdb_cleanup_समयr;
	DECLARE_HASHTABLE(fdb_tbl, 16);
	spinlock_t fdb_tbl_lock;		/* क्रम fdb tbl accesses */
	अचिन्हित दीर्घ पूर्णांकernal_vlan_biपंचांगap[OFDPA_INTERNAL_VLAN_BITMAP_LEN];
	DECLARE_HASHTABLE(पूर्णांकernal_vlan_tbl, 8);
	spinlock_t पूर्णांकernal_vlan_tbl_lock;	/* क्रम vlan tbl accesses */
	DECLARE_HASHTABLE(neigh_tbl, 16);
	spinlock_t neigh_tbl_lock;		/* क्रम neigh tbl accesses */
	u32 neigh_tbl_next_index;
	अचिन्हित दीर्घ ageing_समय;
	bool fib_पातed;
पूर्ण;

काष्ठा ofdpa_port अणु
	काष्ठा ofdpa *ofdpa;
	काष्ठा rocker_port *rocker_port;
	काष्ठा net_device *dev;
	u32 pport;
	काष्ठा net_device *bridge_dev;
	__be16 पूर्णांकernal_vlan_id;
	पूर्णांक stp_state;
	u32 brport_flags;
	अचिन्हित दीर्घ ageing_समय;
	bool ctrls[OFDPA_CTRL_MAX];
	अचिन्हित दीर्घ vlan_biपंचांगap[OFDPA_VLAN_BITMAP_LEN];
पूर्ण;

अटल स्थिर u8 zero_mac[ETH_ALEN]   = अणु 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 पूर्ण;
अटल स्थिर u8 ff_mac[ETH_ALEN]     = अणु 0xff, 0xff, 0xff, 0xff, 0xff, 0xff पूर्ण;
अटल स्थिर u8 ll_mac[ETH_ALEN]     = अणु 0x01, 0x80, 0xc2, 0x00, 0x00, 0x00 पूर्ण;
अटल स्थिर u8 ll_mask[ETH_ALEN]    = अणु 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0 पूर्ण;
अटल स्थिर u8 mcast_mac[ETH_ALEN]  = अणु 0x01, 0x00, 0x00, 0x00, 0x00, 0x00 पूर्ण;
अटल स्थिर u8 ipv4_mcast[ETH_ALEN] = अणु 0x01, 0x00, 0x5e, 0x00, 0x00, 0x00 पूर्ण;
अटल स्थिर u8 ipv4_mask[ETH_ALEN]  = अणु 0xff, 0xff, 0xff, 0x80, 0x00, 0x00 पूर्ण;
अटल स्थिर u8 ipv6_mcast[ETH_ALEN] = अणु 0x33, 0x33, 0x00, 0x00, 0x00, 0x00 पूर्ण;
अटल स्थिर u8 ipv6_mask[ETH_ALEN]  = अणु 0xff, 0xff, 0x00, 0x00, 0x00, 0x00 पूर्ण;

/* Rocker priority levels क्रम flow table entries.  Higher
 * priority match takes precedence over lower priority match.
 */

क्रमागत अणु
	OFDPA_PRIORITY_UNKNOWN = 0,
	OFDPA_PRIORITY_IG_PORT = 1,
	OFDPA_PRIORITY_VLAN = 1,
	OFDPA_PRIORITY_TERM_MAC_UCAST = 0,
	OFDPA_PRIORITY_TERM_MAC_MCAST = 1,
	OFDPA_PRIORITY_BRIDGING_VLAN_DFLT_EXACT = 1,
	OFDPA_PRIORITY_BRIDGING_VLAN_DFLT_WILD = 2,
	OFDPA_PRIORITY_BRIDGING_VLAN = 3,
	OFDPA_PRIORITY_BRIDGING_TEन_अंकT_DFLT_EXACT = 1,
	OFDPA_PRIORITY_BRIDGING_TEन_अंकT_DFLT_WILD = 2,
	OFDPA_PRIORITY_BRIDGING_TEन_अंकT = 3,
	OFDPA_PRIORITY_ACL_CTRL = 3,
	OFDPA_PRIORITY_ACL_NORMAL = 2,
	OFDPA_PRIORITY_ACL_DFLT = 1,
पूर्ण;

अटल bool ofdpa_vlan_id_is_पूर्णांकernal(__be16 vlan_id)
अणु
	u16 start = OFDPA_INTERNAL_VLAN_ID_BASE;
	u16 end = 0xffe;
	u16 _vlan_id = ntohs(vlan_id);

	वापस (_vlan_id >= start && _vlan_id <= end);
पूर्ण

अटल __be16 ofdpa_port_vid_to_vlan(स्थिर काष्ठा ofdpa_port *ofdpa_port,
				     u16 vid, bool *pop_vlan)
अणु
	__be16 vlan_id;

	अगर (pop_vlan)
		*pop_vlan = false;
	vlan_id = htons(vid);
	अगर (!vlan_id) अणु
		vlan_id = ofdpa_port->पूर्णांकernal_vlan_id;
		अगर (pop_vlan)
			*pop_vlan = true;
	पूर्ण

	वापस vlan_id;
पूर्ण

अटल u16 ofdpa_port_vlan_to_vid(स्थिर काष्ठा ofdpa_port *ofdpa_port,
				  __be16 vlan_id)
अणु
	अगर (ofdpa_vlan_id_is_पूर्णांकernal(vlan_id))
		वापस 0;

	वापस ntohs(vlan_id);
पूर्ण

अटल bool ofdpa_port_is_slave(स्थिर काष्ठा ofdpa_port *ofdpa_port,
				स्थिर अक्षर *kind)
अणु
	वापस ofdpa_port->bridge_dev &&
		!म_भेद(ofdpa_port->bridge_dev->rtnl_link_ops->kind, kind);
पूर्ण

अटल bool ofdpa_port_is_bridged(स्थिर काष्ठा ofdpa_port *ofdpa_port)
अणु
	वापस ofdpa_port_is_slave(ofdpa_port, "bridge");
पूर्ण

अटल bool ofdpa_port_is_ovsed(स्थिर काष्ठा ofdpa_port *ofdpa_port)
अणु
	वापस ofdpa_port_is_slave(ofdpa_port, "openvswitch");
पूर्ण

#घोषणा OFDPA_OP_FLAG_REMOVE		BIT(0)
#घोषणा OFDPA_OP_FLAG_NOWAIT		BIT(1)
#घोषणा OFDPA_OP_FLAG_LEARNED		BIT(2)
#घोषणा OFDPA_OP_FLAG_REFRESH		BIT(3)

अटल bool ofdpa_flags_noरुको(पूर्णांक flags)
अणु
	वापस flags & OFDPA_OP_FLAG_NOWAIT;
पूर्ण

/*************************************************************
 * Flow, group, FDB, पूर्णांकernal VLAN and neigh command prepares
 *************************************************************/

अटल पूर्णांक
ofdpa_cmd_flow_tbl_add_ig_port(काष्ठा rocker_desc_info *desc_info,
			       स्थिर काष्ठा ofdpa_flow_tbl_entry *entry)
अणु
	अगर (rocker_tlv_put_u32(desc_info, ROCKER_TLV_OF_DPA_IN_PPORT,
			       entry->key.ig_port.in_pport))
		वापस -EMSGSIZE;
	अगर (rocker_tlv_put_u32(desc_info, ROCKER_TLV_OF_DPA_IN_PPORT_MASK,
			       entry->key.ig_port.in_pport_mask))
		वापस -EMSGSIZE;
	अगर (rocker_tlv_put_u16(desc_info, ROCKER_TLV_OF_DPA_GOTO_TABLE_ID,
			       entry->key.ig_port.जाओ_tbl))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक
ofdpa_cmd_flow_tbl_add_vlan(काष्ठा rocker_desc_info *desc_info,
			    स्थिर काष्ठा ofdpa_flow_tbl_entry *entry)
अणु
	अगर (rocker_tlv_put_u32(desc_info, ROCKER_TLV_OF_DPA_IN_PPORT,
			       entry->key.vlan.in_pport))
		वापस -EMSGSIZE;
	अगर (rocker_tlv_put_be16(desc_info, ROCKER_TLV_OF_DPA_VLAN_ID,
				entry->key.vlan.vlan_id))
		वापस -EMSGSIZE;
	अगर (rocker_tlv_put_be16(desc_info, ROCKER_TLV_OF_DPA_VLAN_ID_MASK,
				entry->key.vlan.vlan_id_mask))
		वापस -EMSGSIZE;
	अगर (rocker_tlv_put_u16(desc_info, ROCKER_TLV_OF_DPA_GOTO_TABLE_ID,
			       entry->key.vlan.जाओ_tbl))
		वापस -EMSGSIZE;
	अगर (entry->key.vlan.untagged &&
	    rocker_tlv_put_be16(desc_info, ROCKER_TLV_OF_DPA_NEW_VLAN_ID,
				entry->key.vlan.new_vlan_id))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक
ofdpa_cmd_flow_tbl_add_term_mac(काष्ठा rocker_desc_info *desc_info,
				स्थिर काष्ठा ofdpa_flow_tbl_entry *entry)
अणु
	अगर (rocker_tlv_put_u32(desc_info, ROCKER_TLV_OF_DPA_IN_PPORT,
			       entry->key.term_mac.in_pport))
		वापस -EMSGSIZE;
	अगर (rocker_tlv_put_u32(desc_info, ROCKER_TLV_OF_DPA_IN_PPORT_MASK,
			       entry->key.term_mac.in_pport_mask))
		वापस -EMSGSIZE;
	अगर (rocker_tlv_put_be16(desc_info, ROCKER_TLV_OF_DPA_ETHERTYPE,
				entry->key.term_mac.eth_type))
		वापस -EMSGSIZE;
	अगर (rocker_tlv_put(desc_info, ROCKER_TLV_OF_DPA_DST_MAC,
			   ETH_ALEN, entry->key.term_mac.eth_dst))
		वापस -EMSGSIZE;
	अगर (rocker_tlv_put(desc_info, ROCKER_TLV_OF_DPA_DST_MAC_MASK,
			   ETH_ALEN, entry->key.term_mac.eth_dst_mask))
		वापस -EMSGSIZE;
	अगर (rocker_tlv_put_be16(desc_info, ROCKER_TLV_OF_DPA_VLAN_ID,
				entry->key.term_mac.vlan_id))
		वापस -EMSGSIZE;
	अगर (rocker_tlv_put_be16(desc_info, ROCKER_TLV_OF_DPA_VLAN_ID_MASK,
				entry->key.term_mac.vlan_id_mask))
		वापस -EMSGSIZE;
	अगर (rocker_tlv_put_u16(desc_info, ROCKER_TLV_OF_DPA_GOTO_TABLE_ID,
			       entry->key.term_mac.जाओ_tbl))
		वापस -EMSGSIZE;
	अगर (entry->key.term_mac.copy_to_cpu &&
	    rocker_tlv_put_u8(desc_info, ROCKER_TLV_OF_DPA_COPY_CPU_ACTION,
			      entry->key.term_mac.copy_to_cpu))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक
ofdpa_cmd_flow_tbl_add_ucast_routing(काष्ठा rocker_desc_info *desc_info,
				     स्थिर काष्ठा ofdpa_flow_tbl_entry *entry)
अणु
	अगर (rocker_tlv_put_be16(desc_info, ROCKER_TLV_OF_DPA_ETHERTYPE,
				entry->key.ucast_routing.eth_type))
		वापस -EMSGSIZE;
	अगर (rocker_tlv_put_be32(desc_info, ROCKER_TLV_OF_DPA_DST_IP,
				entry->key.ucast_routing.dst4))
		वापस -EMSGSIZE;
	अगर (rocker_tlv_put_be32(desc_info, ROCKER_TLV_OF_DPA_DST_IP_MASK,
				entry->key.ucast_routing.dst4_mask))
		वापस -EMSGSIZE;
	अगर (rocker_tlv_put_u16(desc_info, ROCKER_TLV_OF_DPA_GOTO_TABLE_ID,
			       entry->key.ucast_routing.जाओ_tbl))
		वापस -EMSGSIZE;
	अगर (rocker_tlv_put_u32(desc_info, ROCKER_TLV_OF_DPA_GROUP_ID,
			       entry->key.ucast_routing.group_id))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक
ofdpa_cmd_flow_tbl_add_bridge(काष्ठा rocker_desc_info *desc_info,
			      स्थिर काष्ठा ofdpa_flow_tbl_entry *entry)
अणु
	अगर (entry->key.bridge.has_eth_dst &&
	    rocker_tlv_put(desc_info, ROCKER_TLV_OF_DPA_DST_MAC,
			   ETH_ALEN, entry->key.bridge.eth_dst))
		वापस -EMSGSIZE;
	अगर (entry->key.bridge.has_eth_dst_mask &&
	    rocker_tlv_put(desc_info, ROCKER_TLV_OF_DPA_DST_MAC_MASK,
			   ETH_ALEN, entry->key.bridge.eth_dst_mask))
		वापस -EMSGSIZE;
	अगर (entry->key.bridge.vlan_id &&
	    rocker_tlv_put_be16(desc_info, ROCKER_TLV_OF_DPA_VLAN_ID,
				entry->key.bridge.vlan_id))
		वापस -EMSGSIZE;
	अगर (entry->key.bridge.tunnel_id &&
	    rocker_tlv_put_u32(desc_info, ROCKER_TLV_OF_DPA_TUNNEL_ID,
			       entry->key.bridge.tunnel_id))
		वापस -EMSGSIZE;
	अगर (rocker_tlv_put_u16(desc_info, ROCKER_TLV_OF_DPA_GOTO_TABLE_ID,
			       entry->key.bridge.जाओ_tbl))
		वापस -EMSGSIZE;
	अगर (rocker_tlv_put_u32(desc_info, ROCKER_TLV_OF_DPA_GROUP_ID,
			       entry->key.bridge.group_id))
		वापस -EMSGSIZE;
	अगर (entry->key.bridge.copy_to_cpu &&
	    rocker_tlv_put_u8(desc_info, ROCKER_TLV_OF_DPA_COPY_CPU_ACTION,
			      entry->key.bridge.copy_to_cpu))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक
ofdpa_cmd_flow_tbl_add_acl(काष्ठा rocker_desc_info *desc_info,
			   स्थिर काष्ठा ofdpa_flow_tbl_entry *entry)
अणु
	अगर (rocker_tlv_put_u32(desc_info, ROCKER_TLV_OF_DPA_IN_PPORT,
			       entry->key.acl.in_pport))
		वापस -EMSGSIZE;
	अगर (rocker_tlv_put_u32(desc_info, ROCKER_TLV_OF_DPA_IN_PPORT_MASK,
			       entry->key.acl.in_pport_mask))
		वापस -EMSGSIZE;
	अगर (rocker_tlv_put(desc_info, ROCKER_TLV_OF_DPA_SRC_MAC,
			   ETH_ALEN, entry->key.acl.eth_src))
		वापस -EMSGSIZE;
	अगर (rocker_tlv_put(desc_info, ROCKER_TLV_OF_DPA_SRC_MAC_MASK,
			   ETH_ALEN, entry->key.acl.eth_src_mask))
		वापस -EMSGSIZE;
	अगर (rocker_tlv_put(desc_info, ROCKER_TLV_OF_DPA_DST_MAC,
			   ETH_ALEN, entry->key.acl.eth_dst))
		वापस -EMSGSIZE;
	अगर (rocker_tlv_put(desc_info, ROCKER_TLV_OF_DPA_DST_MAC_MASK,
			   ETH_ALEN, entry->key.acl.eth_dst_mask))
		वापस -EMSGSIZE;
	अगर (rocker_tlv_put_be16(desc_info, ROCKER_TLV_OF_DPA_ETHERTYPE,
				entry->key.acl.eth_type))
		वापस -EMSGSIZE;
	अगर (rocker_tlv_put_be16(desc_info, ROCKER_TLV_OF_DPA_VLAN_ID,
				entry->key.acl.vlan_id))
		वापस -EMSGSIZE;
	अगर (rocker_tlv_put_be16(desc_info, ROCKER_TLV_OF_DPA_VLAN_ID_MASK,
				entry->key.acl.vlan_id_mask))
		वापस -EMSGSIZE;

	चयन (ntohs(entry->key.acl.eth_type)) अणु
	हाल ETH_P_IP:
	हाल ETH_P_IPV6:
		अगर (rocker_tlv_put_u8(desc_info, ROCKER_TLV_OF_DPA_IP_PROTO,
				      entry->key.acl.ip_proto))
			वापस -EMSGSIZE;
		अगर (rocker_tlv_put_u8(desc_info,
				      ROCKER_TLV_OF_DPA_IP_PROTO_MASK,
				      entry->key.acl.ip_proto_mask))
			वापस -EMSGSIZE;
		अगर (rocker_tlv_put_u8(desc_info, ROCKER_TLV_OF_DPA_IP_DSCP,
				      entry->key.acl.ip_tos & 0x3f))
			वापस -EMSGSIZE;
		अगर (rocker_tlv_put_u8(desc_info,
				      ROCKER_TLV_OF_DPA_IP_DSCP_MASK,
				      entry->key.acl.ip_tos_mask & 0x3f))
			वापस -EMSGSIZE;
		अगर (rocker_tlv_put_u8(desc_info, ROCKER_TLV_OF_DPA_IP_ECN,
				      (entry->key.acl.ip_tos & 0xc0) >> 6))
			वापस -EMSGSIZE;
		अगर (rocker_tlv_put_u8(desc_info,
				      ROCKER_TLV_OF_DPA_IP_ECN_MASK,
				      (entry->key.acl.ip_tos_mask & 0xc0) >> 6))
			वापस -EMSGSIZE;
		अवरोध;
	पूर्ण

	अगर (entry->key.acl.group_id != ROCKER_GROUP_NONE &&
	    rocker_tlv_put_u32(desc_info, ROCKER_TLV_OF_DPA_GROUP_ID,
			       entry->key.acl.group_id))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक ofdpa_cmd_flow_tbl_add(स्थिर काष्ठा rocker_port *rocker_port,
				  काष्ठा rocker_desc_info *desc_info,
				  व्योम *priv)
अणु
	स्थिर काष्ठा ofdpa_flow_tbl_entry *entry = priv;
	काष्ठा rocker_tlv *cmd_info;
	पूर्णांक err = 0;

	अगर (rocker_tlv_put_u16(desc_info, ROCKER_TLV_CMD_TYPE, entry->cmd))
		वापस -EMSGSIZE;
	cmd_info = rocker_tlv_nest_start(desc_info, ROCKER_TLV_CMD_INFO);
	अगर (!cmd_info)
		वापस -EMSGSIZE;
	अगर (rocker_tlv_put_u16(desc_info, ROCKER_TLV_OF_DPA_TABLE_ID,
			       entry->key.tbl_id))
		वापस -EMSGSIZE;
	अगर (rocker_tlv_put_u32(desc_info, ROCKER_TLV_OF_DPA_PRIORITY,
			       entry->key.priority))
		वापस -EMSGSIZE;
	अगर (rocker_tlv_put_u32(desc_info, ROCKER_TLV_OF_DPA_HARDTIME, 0))
		वापस -EMSGSIZE;
	अगर (rocker_tlv_put_u64(desc_info, ROCKER_TLV_OF_DPA_COOKIE,
			       entry->cookie))
		वापस -EMSGSIZE;

	चयन (entry->key.tbl_id) अणु
	हाल ROCKER_OF_DPA_TABLE_ID_INGRESS_PORT:
		err = ofdpa_cmd_flow_tbl_add_ig_port(desc_info, entry);
		अवरोध;
	हाल ROCKER_OF_DPA_TABLE_ID_VLAN:
		err = ofdpa_cmd_flow_tbl_add_vlan(desc_info, entry);
		अवरोध;
	हाल ROCKER_OF_DPA_TABLE_ID_TERMINATION_MAC:
		err = ofdpa_cmd_flow_tbl_add_term_mac(desc_info, entry);
		अवरोध;
	हाल ROCKER_OF_DPA_TABLE_ID_UNICAST_ROUTING:
		err = ofdpa_cmd_flow_tbl_add_ucast_routing(desc_info, entry);
		अवरोध;
	हाल ROCKER_OF_DPA_TABLE_ID_BRIDGING:
		err = ofdpa_cmd_flow_tbl_add_bridge(desc_info, entry);
		अवरोध;
	हाल ROCKER_OF_DPA_TABLE_ID_ACL_POLICY:
		err = ofdpa_cmd_flow_tbl_add_acl(desc_info, entry);
		अवरोध;
	शेष:
		err = -ENOTSUPP;
		अवरोध;
	पूर्ण

	अगर (err)
		वापस err;

	rocker_tlv_nest_end(desc_info, cmd_info);

	वापस 0;
पूर्ण

अटल पूर्णांक ofdpa_cmd_flow_tbl_del(स्थिर काष्ठा rocker_port *rocker_port,
				  काष्ठा rocker_desc_info *desc_info,
				  व्योम *priv)
अणु
	स्थिर काष्ठा ofdpa_flow_tbl_entry *entry = priv;
	काष्ठा rocker_tlv *cmd_info;

	अगर (rocker_tlv_put_u16(desc_info, ROCKER_TLV_CMD_TYPE, entry->cmd))
		वापस -EMSGSIZE;
	cmd_info = rocker_tlv_nest_start(desc_info, ROCKER_TLV_CMD_INFO);
	अगर (!cmd_info)
		वापस -EMSGSIZE;
	अगर (rocker_tlv_put_u64(desc_info, ROCKER_TLV_OF_DPA_COOKIE,
			       entry->cookie))
		वापस -EMSGSIZE;
	rocker_tlv_nest_end(desc_info, cmd_info);

	वापस 0;
पूर्ण

अटल पूर्णांक
ofdpa_cmd_group_tbl_add_l2_पूर्णांकerface(काष्ठा rocker_desc_info *desc_info,
				     काष्ठा ofdpa_group_tbl_entry *entry)
अणु
	अगर (rocker_tlv_put_u32(desc_info, ROCKER_TLV_OF_DPA_OUT_PPORT,
			       ROCKER_GROUP_PORT_GET(entry->group_id)))
		वापस -EMSGSIZE;
	अगर (rocker_tlv_put_u8(desc_info, ROCKER_TLV_OF_DPA_POP_VLAN,
			      entry->l2_पूर्णांकerface.pop_vlan))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक
ofdpa_cmd_group_tbl_add_l2_reग_लिखो(काष्ठा rocker_desc_info *desc_info,
				   स्थिर काष्ठा ofdpa_group_tbl_entry *entry)
अणु
	अगर (rocker_tlv_put_u32(desc_info, ROCKER_TLV_OF_DPA_GROUP_ID_LOWER,
			       entry->l2_reग_लिखो.group_id))
		वापस -EMSGSIZE;
	अगर (!is_zero_ether_addr(entry->l2_reग_लिखो.eth_src) &&
	    rocker_tlv_put(desc_info, ROCKER_TLV_OF_DPA_SRC_MAC,
			   ETH_ALEN, entry->l2_reग_लिखो.eth_src))
		वापस -EMSGSIZE;
	अगर (!is_zero_ether_addr(entry->l2_reग_लिखो.eth_dst) &&
	    rocker_tlv_put(desc_info, ROCKER_TLV_OF_DPA_DST_MAC,
			   ETH_ALEN, entry->l2_reग_लिखो.eth_dst))
		वापस -EMSGSIZE;
	अगर (entry->l2_reग_लिखो.vlan_id &&
	    rocker_tlv_put_be16(desc_info, ROCKER_TLV_OF_DPA_VLAN_ID,
				entry->l2_reग_लिखो.vlan_id))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक
ofdpa_cmd_group_tbl_add_group_ids(काष्ठा rocker_desc_info *desc_info,
				  स्थिर काष्ठा ofdpa_group_tbl_entry *entry)
अणु
	पूर्णांक i;
	काष्ठा rocker_tlv *group_ids;

	अगर (rocker_tlv_put_u16(desc_info, ROCKER_TLV_OF_DPA_GROUP_COUNT,
			       entry->group_count))
		वापस -EMSGSIZE;

	group_ids = rocker_tlv_nest_start(desc_info,
					  ROCKER_TLV_OF_DPA_GROUP_IDS);
	अगर (!group_ids)
		वापस -EMSGSIZE;

	क्रम (i = 0; i < entry->group_count; i++)
		/* Note TLV array is 1-based */
		अगर (rocker_tlv_put_u32(desc_info, i + 1, entry->group_ids[i]))
			वापस -EMSGSIZE;

	rocker_tlv_nest_end(desc_info, group_ids);

	वापस 0;
पूर्ण

अटल पूर्णांक
ofdpa_cmd_group_tbl_add_l3_unicast(काष्ठा rocker_desc_info *desc_info,
				   स्थिर काष्ठा ofdpa_group_tbl_entry *entry)
अणु
	अगर (!is_zero_ether_addr(entry->l3_unicast.eth_src) &&
	    rocker_tlv_put(desc_info, ROCKER_TLV_OF_DPA_SRC_MAC,
			   ETH_ALEN, entry->l3_unicast.eth_src))
		वापस -EMSGSIZE;
	अगर (!is_zero_ether_addr(entry->l3_unicast.eth_dst) &&
	    rocker_tlv_put(desc_info, ROCKER_TLV_OF_DPA_DST_MAC,
			   ETH_ALEN, entry->l3_unicast.eth_dst))
		वापस -EMSGSIZE;
	अगर (entry->l3_unicast.vlan_id &&
	    rocker_tlv_put_be16(desc_info, ROCKER_TLV_OF_DPA_VLAN_ID,
				entry->l3_unicast.vlan_id))
		वापस -EMSGSIZE;
	अगर (rocker_tlv_put_u8(desc_info, ROCKER_TLV_OF_DPA_TTL_CHECK,
			      entry->l3_unicast.ttl_check))
		वापस -EMSGSIZE;
	अगर (rocker_tlv_put_u32(desc_info, ROCKER_TLV_OF_DPA_GROUP_ID_LOWER,
			       entry->l3_unicast.group_id))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक ofdpa_cmd_group_tbl_add(स्थिर काष्ठा rocker_port *rocker_port,
				   काष्ठा rocker_desc_info *desc_info,
				   व्योम *priv)
अणु
	काष्ठा ofdpa_group_tbl_entry *entry = priv;
	काष्ठा rocker_tlv *cmd_info;
	पूर्णांक err = 0;

	अगर (rocker_tlv_put_u16(desc_info, ROCKER_TLV_CMD_TYPE, entry->cmd))
		वापस -EMSGSIZE;
	cmd_info = rocker_tlv_nest_start(desc_info, ROCKER_TLV_CMD_INFO);
	अगर (!cmd_info)
		वापस -EMSGSIZE;

	अगर (rocker_tlv_put_u32(desc_info, ROCKER_TLV_OF_DPA_GROUP_ID,
			       entry->group_id))
		वापस -EMSGSIZE;

	चयन (ROCKER_GROUP_TYPE_GET(entry->group_id)) अणु
	हाल ROCKER_OF_DPA_GROUP_TYPE_L2_INTERFACE:
		err = ofdpa_cmd_group_tbl_add_l2_पूर्णांकerface(desc_info, entry);
		अवरोध;
	हाल ROCKER_OF_DPA_GROUP_TYPE_L2_REWRITE:
		err = ofdpa_cmd_group_tbl_add_l2_reग_लिखो(desc_info, entry);
		अवरोध;
	हाल ROCKER_OF_DPA_GROUP_TYPE_L2_FLOOD:
	हाल ROCKER_OF_DPA_GROUP_TYPE_L2_MCAST:
		err = ofdpa_cmd_group_tbl_add_group_ids(desc_info, entry);
		अवरोध;
	हाल ROCKER_OF_DPA_GROUP_TYPE_L3_UCAST:
		err = ofdpa_cmd_group_tbl_add_l3_unicast(desc_info, entry);
		अवरोध;
	शेष:
		err = -ENOTSUPP;
		अवरोध;
	पूर्ण

	अगर (err)
		वापस err;

	rocker_tlv_nest_end(desc_info, cmd_info);

	वापस 0;
पूर्ण

अटल पूर्णांक ofdpa_cmd_group_tbl_del(स्थिर काष्ठा rocker_port *rocker_port,
				   काष्ठा rocker_desc_info *desc_info,
				   व्योम *priv)
अणु
	स्थिर काष्ठा ofdpa_group_tbl_entry *entry = priv;
	काष्ठा rocker_tlv *cmd_info;

	अगर (rocker_tlv_put_u16(desc_info, ROCKER_TLV_CMD_TYPE, entry->cmd))
		वापस -EMSGSIZE;
	cmd_info = rocker_tlv_nest_start(desc_info, ROCKER_TLV_CMD_INFO);
	अगर (!cmd_info)
		वापस -EMSGSIZE;
	अगर (rocker_tlv_put_u32(desc_info, ROCKER_TLV_OF_DPA_GROUP_ID,
			       entry->group_id))
		वापस -EMSGSIZE;
	rocker_tlv_nest_end(desc_info, cmd_info);

	वापस 0;
पूर्ण

/***************************************************
 * Flow, group, FDB, पूर्णांकernal VLAN and neigh tables
 ***************************************************/

अटल काष्ठा ofdpa_flow_tbl_entry *
ofdpa_flow_tbl_find(स्थिर काष्ठा ofdpa *ofdpa,
		    स्थिर काष्ठा ofdpa_flow_tbl_entry *match)
अणु
	काष्ठा ofdpa_flow_tbl_entry *found;
	माप_प्रकार key_len = match->key_len ? match->key_len : माप(found->key);

	hash_क्रम_each_possible(ofdpa->flow_tbl, found,
			       entry, match->key_crc32) अणु
		अगर (स_भेद(&found->key, &match->key, key_len) == 0)
			वापस found;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक ofdpa_flow_tbl_add(काष्ठा ofdpa_port *ofdpa_port,
			      पूर्णांक flags, काष्ठा ofdpa_flow_tbl_entry *match)
अणु
	काष्ठा ofdpa *ofdpa = ofdpa_port->ofdpa;
	काष्ठा ofdpa_flow_tbl_entry *found;
	माप_प्रकार key_len = match->key_len ? match->key_len : माप(found->key);
	अचिन्हित दीर्घ lock_flags;

	match->key_crc32 = crc32(~0, &match->key, key_len);

	spin_lock_irqsave(&ofdpa->flow_tbl_lock, lock_flags);

	found = ofdpa_flow_tbl_find(ofdpa, match);

	अगर (found) अणु
		match->cookie = found->cookie;
		hash_del(&found->entry);
		kमुक्त(found);
		found = match;
		found->cmd = ROCKER_TLV_CMD_TYPE_OF_DPA_FLOW_MOD;
	पूर्ण अन्यथा अणु
		found = match;
		found->cookie = ofdpa->flow_tbl_next_cookie++;
		found->cmd = ROCKER_TLV_CMD_TYPE_OF_DPA_FLOW_ADD;
	पूर्ण

	hash_add(ofdpa->flow_tbl, &found->entry, found->key_crc32);
	spin_unlock_irqrestore(&ofdpa->flow_tbl_lock, lock_flags);

	वापस rocker_cmd_exec(ofdpa_port->rocker_port,
			       ofdpa_flags_noरुको(flags),
			       ofdpa_cmd_flow_tbl_add,
			       found, शून्य, शून्य);
पूर्ण

अटल पूर्णांक ofdpa_flow_tbl_del(काष्ठा ofdpa_port *ofdpa_port,
			      पूर्णांक flags, काष्ठा ofdpa_flow_tbl_entry *match)
अणु
	काष्ठा ofdpa *ofdpa = ofdpa_port->ofdpa;
	काष्ठा ofdpa_flow_tbl_entry *found;
	माप_प्रकार key_len = match->key_len ? match->key_len : माप(found->key);
	अचिन्हित दीर्घ lock_flags;
	पूर्णांक err = 0;

	match->key_crc32 = crc32(~0, &match->key, key_len);

	spin_lock_irqsave(&ofdpa->flow_tbl_lock, lock_flags);

	found = ofdpa_flow_tbl_find(ofdpa, match);

	अगर (found) अणु
		hash_del(&found->entry);
		found->cmd = ROCKER_TLV_CMD_TYPE_OF_DPA_FLOW_DEL;
	पूर्ण

	spin_unlock_irqrestore(&ofdpa->flow_tbl_lock, lock_flags);

	kमुक्त(match);

	अगर (found) अणु
		err = rocker_cmd_exec(ofdpa_port->rocker_port,
				      ofdpa_flags_noरुको(flags),
				      ofdpa_cmd_flow_tbl_del,
				      found, शून्य, शून्य);
		kमुक्त(found);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक ofdpa_flow_tbl_करो(काष्ठा ofdpa_port *ofdpa_port, पूर्णांक flags,
			     काष्ठा ofdpa_flow_tbl_entry *entry)
अणु
	अगर (flags & OFDPA_OP_FLAG_REMOVE)
		वापस ofdpa_flow_tbl_del(ofdpa_port, flags, entry);
	अन्यथा
		वापस ofdpa_flow_tbl_add(ofdpa_port, flags, entry);
पूर्ण

अटल पूर्णांक ofdpa_flow_tbl_ig_port(काष्ठा ofdpa_port *ofdpa_port, पूर्णांक flags,
				  u32 in_pport, u32 in_pport_mask,
				  क्रमागत rocker_of_dpa_table_id जाओ_tbl)
अणु
	काष्ठा ofdpa_flow_tbl_entry *entry;

	entry = kzalloc(माप(*entry), GFP_KERNEL);
	अगर (!entry)
		वापस -ENOMEM;

	entry->key.priority = OFDPA_PRIORITY_IG_PORT;
	entry->key.tbl_id = ROCKER_OF_DPA_TABLE_ID_INGRESS_PORT;
	entry->key.ig_port.in_pport = in_pport;
	entry->key.ig_port.in_pport_mask = in_pport_mask;
	entry->key.ig_port.जाओ_tbl = जाओ_tbl;

	वापस ofdpa_flow_tbl_करो(ofdpa_port, flags, entry);
पूर्ण

अटल पूर्णांक ofdpa_flow_tbl_vlan(काष्ठा ofdpa_port *ofdpa_port,
			       पूर्णांक flags,
			       u32 in_pport, __be16 vlan_id,
			       __be16 vlan_id_mask,
			       क्रमागत rocker_of_dpa_table_id जाओ_tbl,
			       bool untagged, __be16 new_vlan_id)
अणु
	काष्ठा ofdpa_flow_tbl_entry *entry;

	entry = kzalloc(माप(*entry), GFP_KERNEL);
	अगर (!entry)
		वापस -ENOMEM;

	entry->key.priority = OFDPA_PRIORITY_VLAN;
	entry->key.tbl_id = ROCKER_OF_DPA_TABLE_ID_VLAN;
	entry->key.vlan.in_pport = in_pport;
	entry->key.vlan.vlan_id = vlan_id;
	entry->key.vlan.vlan_id_mask = vlan_id_mask;
	entry->key.vlan.जाओ_tbl = जाओ_tbl;

	entry->key.vlan.untagged = untagged;
	entry->key.vlan.new_vlan_id = new_vlan_id;

	वापस ofdpa_flow_tbl_करो(ofdpa_port, flags, entry);
पूर्ण

अटल पूर्णांक ofdpa_flow_tbl_term_mac(काष्ठा ofdpa_port *ofdpa_port,
				   u32 in_pport, u32 in_pport_mask,
				   __be16 eth_type, स्थिर u8 *eth_dst,
				   स्थिर u8 *eth_dst_mask, __be16 vlan_id,
				   __be16 vlan_id_mask, bool copy_to_cpu,
				   पूर्णांक flags)
अणु
	काष्ठा ofdpa_flow_tbl_entry *entry;

	entry = kzalloc(माप(*entry), GFP_KERNEL);
	अगर (!entry)
		वापस -ENOMEM;

	अगर (is_multicast_ether_addr(eth_dst)) अणु
		entry->key.priority = OFDPA_PRIORITY_TERM_MAC_MCAST;
		entry->key.term_mac.जाओ_tbl =
			 ROCKER_OF_DPA_TABLE_ID_MULTICAST_ROUTING;
	पूर्ण अन्यथा अणु
		entry->key.priority = OFDPA_PRIORITY_TERM_MAC_UCAST;
		entry->key.term_mac.जाओ_tbl =
			 ROCKER_OF_DPA_TABLE_ID_UNICAST_ROUTING;
	पूर्ण

	entry->key.tbl_id = ROCKER_OF_DPA_TABLE_ID_TERMINATION_MAC;
	entry->key.term_mac.in_pport = in_pport;
	entry->key.term_mac.in_pport_mask = in_pport_mask;
	entry->key.term_mac.eth_type = eth_type;
	ether_addr_copy(entry->key.term_mac.eth_dst, eth_dst);
	ether_addr_copy(entry->key.term_mac.eth_dst_mask, eth_dst_mask);
	entry->key.term_mac.vlan_id = vlan_id;
	entry->key.term_mac.vlan_id_mask = vlan_id_mask;
	entry->key.term_mac.copy_to_cpu = copy_to_cpu;

	वापस ofdpa_flow_tbl_करो(ofdpa_port, flags, entry);
पूर्ण

अटल पूर्णांक ofdpa_flow_tbl_bridge(काष्ठा ofdpa_port *ofdpa_port,
				 पूर्णांक flags, स्थिर u8 *eth_dst,
				 स्थिर u8 *eth_dst_mask,  __be16 vlan_id,
				 u32 tunnel_id,
				 क्रमागत rocker_of_dpa_table_id जाओ_tbl,
				 u32 group_id, bool copy_to_cpu)
अणु
	काष्ठा ofdpa_flow_tbl_entry *entry;
	u32 priority;
	bool vlan_bridging = !!vlan_id;
	bool dflt = !eth_dst || eth_dst_mask;
	bool wild = false;

	entry = kzalloc(माप(*entry), GFP_ATOMIC);
	अगर (!entry)
		वापस -ENOMEM;

	entry->key.tbl_id = ROCKER_OF_DPA_TABLE_ID_BRIDGING;

	अगर (eth_dst) अणु
		entry->key.bridge.has_eth_dst = 1;
		ether_addr_copy(entry->key.bridge.eth_dst, eth_dst);
	पूर्ण
	अगर (eth_dst_mask) अणु
		entry->key.bridge.has_eth_dst_mask = 1;
		ether_addr_copy(entry->key.bridge.eth_dst_mask, eth_dst_mask);
		अगर (!ether_addr_equal(eth_dst_mask, ff_mac))
			wild = true;
	पूर्ण

	priority = OFDPA_PRIORITY_UNKNOWN;
	अगर (vlan_bridging && dflt && wild)
		priority = OFDPA_PRIORITY_BRIDGING_VLAN_DFLT_WILD;
	अन्यथा अगर (vlan_bridging && dflt && !wild)
		priority = OFDPA_PRIORITY_BRIDGING_VLAN_DFLT_EXACT;
	अन्यथा अगर (vlan_bridging && !dflt)
		priority = OFDPA_PRIORITY_BRIDGING_VLAN;
	अन्यथा अगर (!vlan_bridging && dflt && wild)
		priority = OFDPA_PRIORITY_BRIDGING_TEन_अंकT_DFLT_WILD;
	अन्यथा अगर (!vlan_bridging && dflt && !wild)
		priority = OFDPA_PRIORITY_BRIDGING_TEन_अंकT_DFLT_EXACT;
	अन्यथा अगर (!vlan_bridging && !dflt)
		priority = OFDPA_PRIORITY_BRIDGING_TEन_अंकT;

	entry->key.priority = priority;
	entry->key.bridge.vlan_id = vlan_id;
	entry->key.bridge.tunnel_id = tunnel_id;
	entry->key.bridge.जाओ_tbl = जाओ_tbl;
	entry->key.bridge.group_id = group_id;
	entry->key.bridge.copy_to_cpu = copy_to_cpu;

	वापस ofdpa_flow_tbl_करो(ofdpa_port, flags, entry);
पूर्ण

अटल पूर्णांक ofdpa_flow_tbl_ucast4_routing(काष्ठा ofdpa_port *ofdpa_port,
					 __be16 eth_type, __be32 dst,
					 __be32 dst_mask, u32 priority,
					 क्रमागत rocker_of_dpa_table_id जाओ_tbl,
					 u32 group_id, काष्ठा fib_info *fi,
					 पूर्णांक flags)
अणु
	काष्ठा ofdpa_flow_tbl_entry *entry;

	entry = kzalloc(माप(*entry), GFP_KERNEL);
	अगर (!entry)
		वापस -ENOMEM;

	entry->key.tbl_id = ROCKER_OF_DPA_TABLE_ID_UNICAST_ROUTING;
	entry->key.priority = priority;
	entry->key.ucast_routing.eth_type = eth_type;
	entry->key.ucast_routing.dst4 = dst;
	entry->key.ucast_routing.dst4_mask = dst_mask;
	entry->key.ucast_routing.जाओ_tbl = जाओ_tbl;
	entry->key.ucast_routing.group_id = group_id;
	entry->key_len = दुरत्व(काष्ठा ofdpa_flow_tbl_key,
				  ucast_routing.group_id);
	entry->fi = fi;

	वापस ofdpa_flow_tbl_करो(ofdpa_port, flags, entry);
पूर्ण

अटल पूर्णांक ofdpa_flow_tbl_acl(काष्ठा ofdpa_port *ofdpa_port, पूर्णांक flags,
			      u32 in_pport, u32 in_pport_mask,
			      स्थिर u8 *eth_src, स्थिर u8 *eth_src_mask,
			      स्थिर u8 *eth_dst, स्थिर u8 *eth_dst_mask,
			      __be16 eth_type, __be16 vlan_id,
			      __be16 vlan_id_mask, u8 ip_proto,
			      u8 ip_proto_mask, u8 ip_tos, u8 ip_tos_mask,
			      u32 group_id)
अणु
	u32 priority;
	काष्ठा ofdpa_flow_tbl_entry *entry;

	entry = kzalloc(माप(*entry), GFP_KERNEL);
	अगर (!entry)
		वापस -ENOMEM;

	priority = OFDPA_PRIORITY_ACL_NORMAL;
	अगर (eth_dst && eth_dst_mask) अणु
		अगर (ether_addr_equal(eth_dst_mask, mcast_mac))
			priority = OFDPA_PRIORITY_ACL_DFLT;
		अन्यथा अगर (is_link_local_ether_addr(eth_dst))
			priority = OFDPA_PRIORITY_ACL_CTRL;
	पूर्ण

	entry->key.priority = priority;
	entry->key.tbl_id = ROCKER_OF_DPA_TABLE_ID_ACL_POLICY;
	entry->key.acl.in_pport = in_pport;
	entry->key.acl.in_pport_mask = in_pport_mask;

	अगर (eth_src)
		ether_addr_copy(entry->key.acl.eth_src, eth_src);
	अगर (eth_src_mask)
		ether_addr_copy(entry->key.acl.eth_src_mask, eth_src_mask);
	अगर (eth_dst)
		ether_addr_copy(entry->key.acl.eth_dst, eth_dst);
	अगर (eth_dst_mask)
		ether_addr_copy(entry->key.acl.eth_dst_mask, eth_dst_mask);

	entry->key.acl.eth_type = eth_type;
	entry->key.acl.vlan_id = vlan_id;
	entry->key.acl.vlan_id_mask = vlan_id_mask;
	entry->key.acl.ip_proto = ip_proto;
	entry->key.acl.ip_proto_mask = ip_proto_mask;
	entry->key.acl.ip_tos = ip_tos;
	entry->key.acl.ip_tos_mask = ip_tos_mask;
	entry->key.acl.group_id = group_id;

	वापस ofdpa_flow_tbl_करो(ofdpa_port, flags, entry);
पूर्ण

अटल काष्ठा ofdpa_group_tbl_entry *
ofdpa_group_tbl_find(स्थिर काष्ठा ofdpa *ofdpa,
		     स्थिर काष्ठा ofdpa_group_tbl_entry *match)
अणु
	काष्ठा ofdpa_group_tbl_entry *found;

	hash_क्रम_each_possible(ofdpa->group_tbl, found,
			       entry, match->group_id) अणु
		अगर (found->group_id == match->group_id)
			वापस found;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम ofdpa_group_tbl_entry_मुक्त(काष्ठा ofdpa_group_tbl_entry *entry)
अणु
	चयन (ROCKER_GROUP_TYPE_GET(entry->group_id)) अणु
	हाल ROCKER_OF_DPA_GROUP_TYPE_L2_FLOOD:
	हाल ROCKER_OF_DPA_GROUP_TYPE_L2_MCAST:
		kमुक्त(entry->group_ids);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	kमुक्त(entry);
पूर्ण

अटल पूर्णांक ofdpa_group_tbl_add(काष्ठा ofdpa_port *ofdpa_port, पूर्णांक flags,
			       काष्ठा ofdpa_group_tbl_entry *match)
अणु
	काष्ठा ofdpa *ofdpa = ofdpa_port->ofdpa;
	काष्ठा ofdpa_group_tbl_entry *found;
	अचिन्हित दीर्घ lock_flags;

	spin_lock_irqsave(&ofdpa->group_tbl_lock, lock_flags);

	found = ofdpa_group_tbl_find(ofdpa, match);

	अगर (found) अणु
		hash_del(&found->entry);
		ofdpa_group_tbl_entry_मुक्त(found);
		found = match;
		found->cmd = ROCKER_TLV_CMD_TYPE_OF_DPA_GROUP_MOD;
	पूर्ण अन्यथा अणु
		found = match;
		found->cmd = ROCKER_TLV_CMD_TYPE_OF_DPA_GROUP_ADD;
	पूर्ण

	hash_add(ofdpa->group_tbl, &found->entry, found->group_id);

	spin_unlock_irqrestore(&ofdpa->group_tbl_lock, lock_flags);

	वापस rocker_cmd_exec(ofdpa_port->rocker_port,
			       ofdpa_flags_noरुको(flags),
			       ofdpa_cmd_group_tbl_add,
			       found, शून्य, शून्य);
पूर्ण

अटल पूर्णांक ofdpa_group_tbl_del(काष्ठा ofdpa_port *ofdpa_port, पूर्णांक flags,
			       काष्ठा ofdpa_group_tbl_entry *match)
अणु
	काष्ठा ofdpa *ofdpa = ofdpa_port->ofdpa;
	काष्ठा ofdpa_group_tbl_entry *found;
	अचिन्हित दीर्घ lock_flags;
	पूर्णांक err = 0;

	spin_lock_irqsave(&ofdpa->group_tbl_lock, lock_flags);

	found = ofdpa_group_tbl_find(ofdpa, match);

	अगर (found) अणु
		hash_del(&found->entry);
		found->cmd = ROCKER_TLV_CMD_TYPE_OF_DPA_GROUP_DEL;
	पूर्ण

	spin_unlock_irqrestore(&ofdpa->group_tbl_lock, lock_flags);

	ofdpa_group_tbl_entry_मुक्त(match);

	अगर (found) अणु
		err = rocker_cmd_exec(ofdpa_port->rocker_port,
				      ofdpa_flags_noरुको(flags),
				      ofdpa_cmd_group_tbl_del,
				      found, शून्य, शून्य);
		ofdpa_group_tbl_entry_मुक्त(found);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक ofdpa_group_tbl_करो(काष्ठा ofdpa_port *ofdpa_port, पूर्णांक flags,
			      काष्ठा ofdpa_group_tbl_entry *entry)
अणु
	अगर (flags & OFDPA_OP_FLAG_REMOVE)
		वापस ofdpa_group_tbl_del(ofdpa_port, flags, entry);
	अन्यथा
		वापस ofdpa_group_tbl_add(ofdpa_port, flags, entry);
पूर्ण

अटल पूर्णांक ofdpa_group_l2_पूर्णांकerface(काष्ठा ofdpa_port *ofdpa_port,
				    पूर्णांक flags, __be16 vlan_id,
				    u32 out_pport, पूर्णांक pop_vlan)
अणु
	काष्ठा ofdpa_group_tbl_entry *entry;

	entry = kzalloc(माप(*entry), GFP_KERNEL);
	अगर (!entry)
		वापस -ENOMEM;

	entry->group_id = ROCKER_GROUP_L2_INTERFACE(vlan_id, out_pport);
	entry->l2_पूर्णांकerface.pop_vlan = pop_vlan;

	वापस ofdpa_group_tbl_करो(ofdpa_port, flags, entry);
पूर्ण

अटल पूर्णांक ofdpa_group_l2_fan_out(काष्ठा ofdpa_port *ofdpa_port,
				  पूर्णांक flags, u8 group_count,
				  स्थिर u32 *group_ids, u32 group_id)
अणु
	काष्ठा ofdpa_group_tbl_entry *entry;

	entry = kzalloc(माप(*entry), GFP_KERNEL);
	अगर (!entry)
		वापस -ENOMEM;

	entry->group_id = group_id;
	entry->group_count = group_count;

	entry->group_ids = kसुस्मृति(group_count, माप(u32), GFP_KERNEL);
	अगर (!entry->group_ids) अणु
		kमुक्त(entry);
		वापस -ENOMEM;
	पूर्ण
	स_नकल(entry->group_ids, group_ids, group_count * माप(u32));

	वापस ofdpa_group_tbl_करो(ofdpa_port, flags, entry);
पूर्ण

अटल पूर्णांक ofdpa_group_l2_flood(काष्ठा ofdpa_port *ofdpa_port,
				पूर्णांक flags, __be16 vlan_id,
				u8 group_count,	स्थिर u32 *group_ids,
				u32 group_id)
अणु
	वापस ofdpa_group_l2_fan_out(ofdpa_port, flags,
				      group_count, group_ids,
				      group_id);
पूर्ण

अटल पूर्णांक ofdpa_group_l3_unicast(काष्ठा ofdpa_port *ofdpa_port, पूर्णांक flags,
				  u32 index, स्थिर u8 *src_mac, स्थिर u8 *dst_mac,
				  __be16 vlan_id, bool ttl_check, u32 pport)
अणु
	काष्ठा ofdpa_group_tbl_entry *entry;

	entry = kzalloc(माप(*entry), GFP_KERNEL);
	अगर (!entry)
		वापस -ENOMEM;

	entry->group_id = ROCKER_GROUP_L3_UNICAST(index);
	अगर (src_mac)
		ether_addr_copy(entry->l3_unicast.eth_src, src_mac);
	अगर (dst_mac)
		ether_addr_copy(entry->l3_unicast.eth_dst, dst_mac);
	entry->l3_unicast.vlan_id = vlan_id;
	entry->l3_unicast.ttl_check = ttl_check;
	entry->l3_unicast.group_id = ROCKER_GROUP_L2_INTERFACE(vlan_id, pport);

	वापस ofdpa_group_tbl_करो(ofdpa_port, flags, entry);
पूर्ण

अटल काष्ठा ofdpa_neigh_tbl_entry *
ofdpa_neigh_tbl_find(स्थिर काष्ठा ofdpa *ofdpa, __be32 ip_addr)
अणु
	काष्ठा ofdpa_neigh_tbl_entry *found;

	hash_क्रम_each_possible(ofdpa->neigh_tbl, found,
			       entry, be32_to_cpu(ip_addr))
		अगर (found->ip_addr == ip_addr)
			वापस found;

	वापस शून्य;
पूर्ण

अटल व्योम ofdpa_neigh_add(काष्ठा ofdpa *ofdpa,
			    काष्ठा ofdpa_neigh_tbl_entry *entry)
अणु
	entry->index = ofdpa->neigh_tbl_next_index++;
	entry->ref_count++;
	hash_add(ofdpa->neigh_tbl, &entry->entry,
		 be32_to_cpu(entry->ip_addr));
पूर्ण

अटल व्योम ofdpa_neigh_del(काष्ठा ofdpa_neigh_tbl_entry *entry)
अणु
	अगर (--entry->ref_count == 0) अणु
		hash_del(&entry->entry);
		kमुक्त(entry);
	पूर्ण
पूर्ण

अटल व्योम ofdpa_neigh_update(काष्ठा ofdpa_neigh_tbl_entry *entry,
			       स्थिर u8 *eth_dst, bool ttl_check)
अणु
	अगर (eth_dst) अणु
		ether_addr_copy(entry->eth_dst, eth_dst);
		entry->ttl_check = ttl_check;
	पूर्ण अन्यथा अणु
		entry->ref_count++;
	पूर्ण
पूर्ण

अटल पूर्णांक ofdpa_port_ipv4_neigh(काष्ठा ofdpa_port *ofdpa_port,
				 पूर्णांक flags, __be32 ip_addr, स्थिर u8 *eth_dst)
अणु
	काष्ठा ofdpa *ofdpa = ofdpa_port->ofdpa;
	काष्ठा ofdpa_neigh_tbl_entry *entry;
	काष्ठा ofdpa_neigh_tbl_entry *found;
	अचिन्हित दीर्घ lock_flags;
	__be16 eth_type = htons(ETH_P_IP);
	क्रमागत rocker_of_dpa_table_id जाओ_tbl =
			ROCKER_OF_DPA_TABLE_ID_ACL_POLICY;
	u32 group_id;
	u32 priority = 0;
	bool adding = !(flags & OFDPA_OP_FLAG_REMOVE);
	bool updating;
	bool removing;
	पूर्णांक err = 0;

	entry = kzalloc(माप(*entry), GFP_KERNEL);
	अगर (!entry)
		वापस -ENOMEM;

	spin_lock_irqsave(&ofdpa->neigh_tbl_lock, lock_flags);

	found = ofdpa_neigh_tbl_find(ofdpa, ip_addr);

	updating = found && adding;
	removing = found && !adding;
	adding = !found && adding;

	अगर (adding) अणु
		entry->ip_addr = ip_addr;
		entry->dev = ofdpa_port->dev;
		ether_addr_copy(entry->eth_dst, eth_dst);
		entry->ttl_check = true;
		ofdpa_neigh_add(ofdpa, entry);
	पूर्ण अन्यथा अगर (removing) अणु
		स_नकल(entry, found, माप(*entry));
		ofdpa_neigh_del(found);
	पूर्ण अन्यथा अगर (updating) अणु
		ofdpa_neigh_update(found, eth_dst, true);
		स_नकल(entry, found, माप(*entry));
	पूर्ण अन्यथा अणु
		err = -ENOENT;
	पूर्ण

	spin_unlock_irqrestore(&ofdpa->neigh_tbl_lock, lock_flags);

	अगर (err)
		जाओ err_out;

	/* For each active neighbor, we have an L3 unicast group and
	 * a /32 route to the neighbor, which uses the L3 unicast
	 * group.  The L3 unicast group can also be referred to by
	 * other routes' nexthops.
	 */

	err = ofdpa_group_l3_unicast(ofdpa_port, flags,
				     entry->index,
				     ofdpa_port->dev->dev_addr,
				     entry->eth_dst,
				     ofdpa_port->पूर्णांकernal_vlan_id,
				     entry->ttl_check,
				     ofdpa_port->pport);
	अगर (err) अणु
		netdev_err(ofdpa_port->dev, "Error (%d) L3 unicast group index %d\n",
			   err, entry->index);
		जाओ err_out;
	पूर्ण

	अगर (adding || removing) अणु
		group_id = ROCKER_GROUP_L3_UNICAST(entry->index);
		err = ofdpa_flow_tbl_ucast4_routing(ofdpa_port,
						    eth_type, ip_addr,
						    inet_make_mask(32),
						    priority, जाओ_tbl,
						    group_id, शून्य, flags);

		अगर (err)
			netdev_err(ofdpa_port->dev, "Error (%d) /32 unicast route %pI4 group 0x%08x\n",
				   err, &entry->ip_addr, group_id);
	पूर्ण

err_out:
	अगर (!adding)
		kमुक्त(entry);

	वापस err;
पूर्ण

अटल पूर्णांक ofdpa_port_ipv4_resolve(काष्ठा ofdpa_port *ofdpa_port,
				   __be32 ip_addr)
अणु
	काष्ठा net_device *dev = ofdpa_port->dev;
	काष्ठा neighbour *n = __ipv4_neigh_lookup(dev, (__क्रमce u32)ip_addr);
	पूर्णांक err = 0;

	अगर (!n) अणु
		n = neigh_create(&arp_tbl, &ip_addr, dev);
		अगर (IS_ERR(n))
			वापस PTR_ERR(n);
	पूर्ण

	/* If the neigh is alपढ़ोy resolved, then go ahead and
	 * install the entry, otherwise start the ARP process to
	 * resolve the neigh.
	 */

	अगर (n->nud_state & NUD_VALID)
		err = ofdpa_port_ipv4_neigh(ofdpa_port, 0,
					    ip_addr, n->ha);
	अन्यथा
		neigh_event_send(n, शून्य);

	neigh_release(n);
	वापस err;
पूर्ण

अटल पूर्णांक ofdpa_port_ipv4_nh(काष्ठा ofdpa_port *ofdpa_port,
			      पूर्णांक flags, __be32 ip_addr, u32 *index)
अणु
	काष्ठा ofdpa *ofdpa = ofdpa_port->ofdpa;
	काष्ठा ofdpa_neigh_tbl_entry *entry;
	काष्ठा ofdpa_neigh_tbl_entry *found;
	अचिन्हित दीर्घ lock_flags;
	bool adding = !(flags & OFDPA_OP_FLAG_REMOVE);
	bool updating;
	bool removing;
	bool resolved = true;
	पूर्णांक err = 0;

	entry = kzalloc(माप(*entry), GFP_KERNEL);
	अगर (!entry)
		वापस -ENOMEM;

	spin_lock_irqsave(&ofdpa->neigh_tbl_lock, lock_flags);

	found = ofdpa_neigh_tbl_find(ofdpa, ip_addr);

	updating = found && adding;
	removing = found && !adding;
	adding = !found && adding;

	अगर (adding) अणु
		entry->ip_addr = ip_addr;
		entry->dev = ofdpa_port->dev;
		ofdpa_neigh_add(ofdpa, entry);
		*index = entry->index;
		resolved = false;
	पूर्ण अन्यथा अगर (removing) अणु
		*index = found->index;
		ofdpa_neigh_del(found);
	पूर्ण अन्यथा अगर (updating) अणु
		ofdpa_neigh_update(found, शून्य, false);
		resolved = !is_zero_ether_addr(found->eth_dst);
		*index = found->index;
	पूर्ण अन्यथा अणु
		err = -ENOENT;
	पूर्ण

	spin_unlock_irqrestore(&ofdpa->neigh_tbl_lock, lock_flags);

	अगर (!adding)
		kमुक्त(entry);

	अगर (err)
		वापस err;

	/* Resolved means neigh ip_addr is resolved to neigh mac. */

	अगर (!resolved)
		err = ofdpa_port_ipv4_resolve(ofdpa_port, ip_addr);

	वापस err;
पूर्ण

अटल काष्ठा ofdpa_port *ofdpa_port_get(स्थिर काष्ठा ofdpa *ofdpa,
					 पूर्णांक port_index)
अणु
	काष्ठा rocker_port *rocker_port;

	rocker_port = ofdpa->rocker->ports[port_index];
	वापस rocker_port ? rocker_port->wpriv : शून्य;
पूर्ण

अटल पूर्णांक ofdpa_port_vlan_flood_group(काष्ठा ofdpa_port *ofdpa_port,
				       पूर्णांक flags, __be16 vlan_id)
अणु
	काष्ठा ofdpa_port *p;
	स्थिर काष्ठा ofdpa *ofdpa = ofdpa_port->ofdpa;
	अचिन्हित पूर्णांक port_count = ofdpa->rocker->port_count;
	u32 group_id = ROCKER_GROUP_L2_FLOOD(vlan_id, 0);
	u32 *group_ids;
	u8 group_count = 0;
	पूर्णांक err = 0;
	पूर्णांक i;

	group_ids = kसुस्मृति(port_count, माप(u32), GFP_KERNEL);
	अगर (!group_ids)
		वापस -ENOMEM;

	/* Adjust the flood group क्रम this VLAN.  The flood group
	 * references an L2 पूर्णांकerface group क्रम each port in this
	 * VLAN.
	 */

	क्रम (i = 0; i < port_count; i++) अणु
		p = ofdpa_port_get(ofdpa, i);
		अगर (!p)
			जारी;
		अगर (!ofdpa_port_is_bridged(p))
			जारी;
		अगर (test_bit(ntohs(vlan_id), p->vlan_biपंचांगap)) अणु
			group_ids[group_count++] =
				ROCKER_GROUP_L2_INTERFACE(vlan_id, p->pport);
		पूर्ण
	पूर्ण

	/* If there are no bridged ports in this VLAN, we're करोne */
	अगर (group_count == 0)
		जाओ no_ports_in_vlan;

	err = ofdpa_group_l2_flood(ofdpa_port, flags, vlan_id,
				   group_count, group_ids, group_id);
	अगर (err)
		netdev_err(ofdpa_port->dev, "Error (%d) port VLAN l2 flood group\n", err);

no_ports_in_vlan:
	kमुक्त(group_ids);
	वापस err;
पूर्ण

अटल पूर्णांक ofdpa_port_vlan_l2_groups(काष्ठा ofdpa_port *ofdpa_port, पूर्णांक flags,
				     __be16 vlan_id, bool pop_vlan)
अणु
	स्थिर काष्ठा ofdpa *ofdpa = ofdpa_port->ofdpa;
	अचिन्हित पूर्णांक port_count = ofdpa->rocker->port_count;
	काष्ठा ofdpa_port *p;
	bool adding = !(flags & OFDPA_OP_FLAG_REMOVE);
	u32 out_pport;
	पूर्णांक ref = 0;
	पूर्णांक err;
	पूर्णांक i;

	/* An L2 पूर्णांकerface group क्रम this port in this VLAN, but
	 * only when port STP state is LEARNING|FORWARDING.
	 */

	अगर (ofdpa_port->stp_state == BR_STATE_LEARNING ||
	    ofdpa_port->stp_state == BR_STATE_FORWARDING) अणु
		out_pport = ofdpa_port->pport;
		err = ofdpa_group_l2_पूर्णांकerface(ofdpa_port, flags,
					       vlan_id, out_pport, pop_vlan);
		अगर (err) अणु
			netdev_err(ofdpa_port->dev, "Error (%d) port VLAN l2 group for pport %d\n",
				   err, out_pport);
			वापस err;
		पूर्ण
	पूर्ण

	/* An L2 पूर्णांकerface group क्रम this VLAN to CPU port.
	 * Add when first port joins this VLAN and destroy when
	 * last port leaves this VLAN.
	 */

	क्रम (i = 0; i < port_count; i++) अणु
		p = ofdpa_port_get(ofdpa, i);
		अगर (p && test_bit(ntohs(vlan_id), p->vlan_biपंचांगap))
			ref++;
	पूर्ण

	अगर ((!adding || ref != 1) && (adding || ref != 0))
		वापस 0;

	out_pport = 0;
	err = ofdpa_group_l2_पूर्णांकerface(ofdpa_port, flags,
				       vlan_id, out_pport, pop_vlan);
	अगर (err) अणु
		netdev_err(ofdpa_port->dev, "Error (%d) port VLAN l2 group for CPU port\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा ofdpa_ctrl अणु
	स्थिर u8 *eth_dst;
	स्थिर u8 *eth_dst_mask;
	__be16 eth_type;
	bool acl;
	bool bridge;
	bool term;
	bool copy_to_cpu;
पूर्ण ofdpa_ctrls[] = अणु
	[OFDPA_CTRL_LINK_LOCAL_MCAST] = अणु
		/* pass link local multicast pkts up to CPU क्रम filtering */
		.eth_dst = ll_mac,
		.eth_dst_mask = ll_mask,
		.acl = true,
	पूर्ण,
	[OFDPA_CTRL_LOCAL_ARP] = अणु
		/* pass local ARP pkts up to CPU */
		.eth_dst = zero_mac,
		.eth_dst_mask = zero_mac,
		.eth_type = htons(ETH_P_ARP),
		.acl = true,
	पूर्ण,
	[OFDPA_CTRL_IPV4_MCAST] = अणु
		/* pass IPv4 mcast pkts up to CPU, RFC 1112 */
		.eth_dst = ipv4_mcast,
		.eth_dst_mask = ipv4_mask,
		.eth_type = htons(ETH_P_IP),
		.term  = true,
		.copy_to_cpu = true,
	पूर्ण,
	[OFDPA_CTRL_IPV6_MCAST] = अणु
		/* pass IPv6 mcast pkts up to CPU, RFC 2464 */
		.eth_dst = ipv6_mcast,
		.eth_dst_mask = ipv6_mask,
		.eth_type = htons(ETH_P_IPV6),
		.term  = true,
		.copy_to_cpu = true,
	पूर्ण,
	[OFDPA_CTRL_DFLT_BRIDGING] = अणु
		/* flood any pkts on vlan */
		.bridge = true,
		.copy_to_cpu = true,
	पूर्ण,
	[OFDPA_CTRL_DFLT_OVS] = अणु
		/* pass all pkts up to CPU */
		.eth_dst = zero_mac,
		.eth_dst_mask = zero_mac,
		.acl = true,
	पूर्ण,
पूर्ण;

अटल पूर्णांक ofdpa_port_ctrl_vlan_acl(काष्ठा ofdpa_port *ofdpa_port, पूर्णांक flags,
				    स्थिर काष्ठा ofdpa_ctrl *ctrl, __be16 vlan_id)
अणु
	u32 in_pport = ofdpa_port->pport;
	u32 in_pport_mask = 0xffffffff;
	u32 out_pport = 0;
	स्थिर u8 *eth_src = शून्य;
	स्थिर u8 *eth_src_mask = शून्य;
	__be16 vlan_id_mask = htons(0xffff);
	u8 ip_proto = 0;
	u8 ip_proto_mask = 0;
	u8 ip_tos = 0;
	u8 ip_tos_mask = 0;
	u32 group_id = ROCKER_GROUP_L2_INTERFACE(vlan_id, out_pport);
	पूर्णांक err;

	err = ofdpa_flow_tbl_acl(ofdpa_port, flags,
				 in_pport, in_pport_mask,
				 eth_src, eth_src_mask,
				 ctrl->eth_dst, ctrl->eth_dst_mask,
				 ctrl->eth_type,
				 vlan_id, vlan_id_mask,
				 ip_proto, ip_proto_mask,
				 ip_tos, ip_tos_mask,
				 group_id);

	अगर (err)
		netdev_err(ofdpa_port->dev, "Error (%d) ctrl ACL\n", err);

	वापस err;
पूर्ण

अटल पूर्णांक ofdpa_port_ctrl_vlan_bridge(काष्ठा ofdpa_port *ofdpa_port,
				       पूर्णांक flags, स्थिर काष्ठा ofdpa_ctrl *ctrl,
				       __be16 vlan_id)
अणु
	क्रमागत rocker_of_dpa_table_id जाओ_tbl =
			ROCKER_OF_DPA_TABLE_ID_ACL_POLICY;
	u32 group_id = ROCKER_GROUP_L2_FLOOD(vlan_id, 0);
	u32 tunnel_id = 0;
	पूर्णांक err;

	अगर (!ofdpa_port_is_bridged(ofdpa_port))
		वापस 0;

	err = ofdpa_flow_tbl_bridge(ofdpa_port, flags,
				    ctrl->eth_dst, ctrl->eth_dst_mask,
				    vlan_id, tunnel_id,
				    जाओ_tbl, group_id, ctrl->copy_to_cpu);

	अगर (err)
		netdev_err(ofdpa_port->dev, "Error (%d) ctrl FLOOD\n", err);

	वापस err;
पूर्ण

अटल पूर्णांक ofdpa_port_ctrl_vlan_term(काष्ठा ofdpa_port *ofdpa_port, पूर्णांक flags,
				     स्थिर काष्ठा ofdpa_ctrl *ctrl, __be16 vlan_id)
अणु
	u32 in_pport_mask = 0xffffffff;
	__be16 vlan_id_mask = htons(0xffff);
	पूर्णांक err;

	अगर (ntohs(vlan_id) == 0)
		vlan_id = ofdpa_port->पूर्णांकernal_vlan_id;

	err = ofdpa_flow_tbl_term_mac(ofdpa_port, ofdpa_port->pport, in_pport_mask,
				      ctrl->eth_type, ctrl->eth_dst,
				      ctrl->eth_dst_mask, vlan_id,
				      vlan_id_mask, ctrl->copy_to_cpu,
				      flags);

	अगर (err)
		netdev_err(ofdpa_port->dev, "Error (%d) ctrl term\n", err);

	वापस err;
पूर्ण

अटल पूर्णांक ofdpa_port_ctrl_vlan(काष्ठा ofdpa_port *ofdpa_port, पूर्णांक flags,
				स्थिर काष्ठा ofdpa_ctrl *ctrl, __be16 vlan_id)
अणु
	अगर (ctrl->acl)
		वापस ofdpa_port_ctrl_vlan_acl(ofdpa_port, flags,
						ctrl, vlan_id);
	अगर (ctrl->bridge)
		वापस ofdpa_port_ctrl_vlan_bridge(ofdpa_port, flags,
						   ctrl, vlan_id);

	अगर (ctrl->term)
		वापस ofdpa_port_ctrl_vlan_term(ofdpa_port, flags,
						 ctrl, vlan_id);

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक ofdpa_port_ctrl_vlan_add(काष्ठा ofdpa_port *ofdpa_port, पूर्णांक flags,
				    __be16 vlan_id)
अणु
	पूर्णांक err = 0;
	पूर्णांक i;

	क्रम (i = 0; i < OFDPA_CTRL_MAX; i++) अणु
		अगर (ofdpa_port->ctrls[i]) अणु
			err = ofdpa_port_ctrl_vlan(ofdpa_port, flags,
						   &ofdpa_ctrls[i], vlan_id);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक ofdpa_port_ctrl(काष्ठा ofdpa_port *ofdpa_port, पूर्णांक flags,
			   स्थिर काष्ठा ofdpa_ctrl *ctrl)
अणु
	u16 vid;
	पूर्णांक err = 0;

	क्रम (vid = 1; vid < VLAN_N_VID; vid++) अणु
		अगर (!test_bit(vid, ofdpa_port->vlan_biपंचांगap))
			जारी;
		err = ofdpa_port_ctrl_vlan(ofdpa_port, flags,
					   ctrl, htons(vid));
		अगर (err)
			अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक ofdpa_port_vlan(काष्ठा ofdpa_port *ofdpa_port, पूर्णांक flags,
			   u16 vid)
अणु
	क्रमागत rocker_of_dpa_table_id जाओ_tbl =
			ROCKER_OF_DPA_TABLE_ID_TERMINATION_MAC;
	u32 in_pport = ofdpa_port->pport;
	__be16 vlan_id = htons(vid);
	__be16 vlan_id_mask = htons(0xffff);
	__be16 पूर्णांकernal_vlan_id;
	bool untagged;
	bool adding = !(flags & OFDPA_OP_FLAG_REMOVE);
	पूर्णांक err;

	पूर्णांकernal_vlan_id = ofdpa_port_vid_to_vlan(ofdpa_port, vid, &untagged);

	अगर (adding &&
	    test_bit(ntohs(पूर्णांकernal_vlan_id), ofdpa_port->vlan_biपंचांगap))
		वापस 0; /* alपढ़ोy added */
	अन्यथा अगर (!adding &&
		 !test_bit(ntohs(पूर्णांकernal_vlan_id), ofdpa_port->vlan_biपंचांगap))
		वापस 0; /* alपढ़ोy हटाओd */

	change_bit(ntohs(पूर्णांकernal_vlan_id), ofdpa_port->vlan_biपंचांगap);

	अगर (adding) अणु
		err = ofdpa_port_ctrl_vlan_add(ofdpa_port, flags,
					       पूर्णांकernal_vlan_id);
		अगर (err) अणु
			netdev_err(ofdpa_port->dev, "Error (%d) port ctrl vlan add\n", err);
			जाओ err_vlan_add;
		पूर्ण
	पूर्ण

	err = ofdpa_port_vlan_l2_groups(ofdpa_port, flags,
					पूर्णांकernal_vlan_id, untagged);
	अगर (err) अणु
		netdev_err(ofdpa_port->dev, "Error (%d) port VLAN l2 groups\n", err);
		जाओ err_vlan_l2_groups;
	पूर्ण

	err = ofdpa_port_vlan_flood_group(ofdpa_port, flags,
					  पूर्णांकernal_vlan_id);
	अगर (err) अणु
		netdev_err(ofdpa_port->dev, "Error (%d) port VLAN l2 flood group\n", err);
		जाओ err_flood_group;
	पूर्ण

	err = ofdpa_flow_tbl_vlan(ofdpa_port, flags,
				  in_pport, vlan_id, vlan_id_mask,
				  जाओ_tbl, untagged, पूर्णांकernal_vlan_id);
	अगर (err)
		netdev_err(ofdpa_port->dev, "Error (%d) port VLAN table\n", err);

	वापस 0;

err_vlan_add:
err_vlan_l2_groups:
err_flood_group:
	change_bit(ntohs(पूर्णांकernal_vlan_id), ofdpa_port->vlan_biपंचांगap);
	वापस err;
पूर्ण

अटल पूर्णांक ofdpa_port_ig_tbl(काष्ठा ofdpa_port *ofdpa_port, पूर्णांक flags)
अणु
	क्रमागत rocker_of_dpa_table_id जाओ_tbl;
	u32 in_pport;
	u32 in_pport_mask;
	पूर्णांक err;

	/* Normal Ethernet Frames.  Matches pkts from any local physical
	 * ports.  Goto VLAN tbl.
	 */

	in_pport = 0;
	in_pport_mask = 0xffff0000;
	जाओ_tbl = ROCKER_OF_DPA_TABLE_ID_VLAN;

	err = ofdpa_flow_tbl_ig_port(ofdpa_port, flags,
				     in_pport, in_pport_mask,
				     जाओ_tbl);
	अगर (err)
		netdev_err(ofdpa_port->dev, "Error (%d) ingress port table entry\n", err);

	वापस err;
पूर्ण

काष्ठा ofdpa_fdb_learn_work अणु
	काष्ठा work_काष्ठा work;
	काष्ठा ofdpa_port *ofdpa_port;
	पूर्णांक flags;
	u8 addr[ETH_ALEN];
	u16 vid;
पूर्ण;

अटल व्योम ofdpa_port_fdb_learn_work(काष्ठा work_काष्ठा *work)
अणु
	स्थिर काष्ठा ofdpa_fdb_learn_work *lw =
		container_of(work, काष्ठा ofdpa_fdb_learn_work, work);
	bool removing = (lw->flags & OFDPA_OP_FLAG_REMOVE);
	bool learned = (lw->flags & OFDPA_OP_FLAG_LEARNED);
	काष्ठा चयनdev_notअगरier_fdb_info info;

	info.addr = lw->addr;
	info.vid = lw->vid;

	rtnl_lock();
	अगर (learned && removing)
		call_चयनdev_notअगरiers(SWITCHDEV_FDB_DEL_TO_BRIDGE,
					 lw->ofdpa_port->dev, &info.info, शून्य);
	अन्यथा अगर (learned && !removing)
		call_चयनdev_notअगरiers(SWITCHDEV_FDB_ADD_TO_BRIDGE,
					 lw->ofdpa_port->dev, &info.info, शून्य);
	rtnl_unlock();

	kमुक्त(work);
पूर्ण

अटल पूर्णांक ofdpa_port_fdb_learn(काष्ठा ofdpa_port *ofdpa_port,
				पूर्णांक flags, स्थिर u8 *addr, __be16 vlan_id)
अणु
	काष्ठा ofdpa_fdb_learn_work *lw;
	क्रमागत rocker_of_dpa_table_id जाओ_tbl =
			ROCKER_OF_DPA_TABLE_ID_ACL_POLICY;
	u32 out_pport = ofdpa_port->pport;
	u32 tunnel_id = 0;
	u32 group_id = ROCKER_GROUP_NONE;
	bool copy_to_cpu = false;
	पूर्णांक err;

	अगर (ofdpa_port_is_bridged(ofdpa_port))
		group_id = ROCKER_GROUP_L2_INTERFACE(vlan_id, out_pport);

	अगर (!(flags & OFDPA_OP_FLAG_REFRESH)) अणु
		err = ofdpa_flow_tbl_bridge(ofdpa_port, flags, addr,
					    शून्य, vlan_id, tunnel_id, जाओ_tbl,
					    group_id, copy_to_cpu);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (!ofdpa_port_is_bridged(ofdpa_port))
		वापस 0;

	lw = kzalloc(माप(*lw), GFP_ATOMIC);
	अगर (!lw)
		वापस -ENOMEM;

	INIT_WORK(&lw->work, ofdpa_port_fdb_learn_work);

	lw->ofdpa_port = ofdpa_port;
	lw->flags = flags;
	ether_addr_copy(lw->addr, addr);
	lw->vid = ofdpa_port_vlan_to_vid(ofdpa_port, vlan_id);

	schedule_work(&lw->work);
	वापस 0;
पूर्ण

अटल काष्ठा ofdpa_fdb_tbl_entry *
ofdpa_fdb_tbl_find(स्थिर काष्ठा ofdpa *ofdpa,
		   स्थिर काष्ठा ofdpa_fdb_tbl_entry *match)
अणु
	काष्ठा ofdpa_fdb_tbl_entry *found;

	hash_क्रम_each_possible(ofdpa->fdb_tbl, found, entry, match->key_crc32)
		अगर (स_भेद(&found->key, &match->key, माप(found->key)) == 0)
			वापस found;

	वापस शून्य;
पूर्ण

अटल पूर्णांक ofdpa_port_fdb(काष्ठा ofdpa_port *ofdpa_port,
			  स्थिर अचिन्हित अक्षर *addr,
			  __be16 vlan_id, पूर्णांक flags)
अणु
	काष्ठा ofdpa *ofdpa = ofdpa_port->ofdpa;
	काष्ठा ofdpa_fdb_tbl_entry *fdb;
	काष्ठा ofdpa_fdb_tbl_entry *found;
	bool removing = (flags & OFDPA_OP_FLAG_REMOVE);
	अचिन्हित दीर्घ lock_flags;

	fdb = kzalloc(माप(*fdb), GFP_KERNEL);
	अगर (!fdb)
		वापस -ENOMEM;

	fdb->learned = (flags & OFDPA_OP_FLAG_LEARNED);
	fdb->touched = jअगरfies;
	fdb->key.ofdpa_port = ofdpa_port;
	ether_addr_copy(fdb->key.addr, addr);
	fdb->key.vlan_id = vlan_id;
	fdb->key_crc32 = crc32(~0, &fdb->key, माप(fdb->key));

	spin_lock_irqsave(&ofdpa->fdb_tbl_lock, lock_flags);

	found = ofdpa_fdb_tbl_find(ofdpa, fdb);

	अगर (found) अणु
		found->touched = jअगरfies;
		अगर (removing) अणु
			kमुक्त(fdb);
			hash_del(&found->entry);
		पूर्ण
	पूर्ण अन्यथा अगर (!removing) अणु
		hash_add(ofdpa->fdb_tbl, &fdb->entry,
			 fdb->key_crc32);
	पूर्ण

	spin_unlock_irqrestore(&ofdpa->fdb_tbl_lock, lock_flags);

	/* Check अगर adding and alपढ़ोy exists, or removing and can't find */
	अगर (!found != !removing) अणु
		kमुक्त(fdb);
		अगर (!found && removing)
			वापस 0;
		/* Refreshing existing to update aging समयrs */
		flags |= OFDPA_OP_FLAG_REFRESH;
	पूर्ण

	वापस ofdpa_port_fdb_learn(ofdpa_port, flags, addr, vlan_id);
पूर्ण

अटल पूर्णांक ofdpa_port_fdb_flush(काष्ठा ofdpa_port *ofdpa_port, पूर्णांक flags)
अणु
	काष्ठा ofdpa *ofdpa = ofdpa_port->ofdpa;
	काष्ठा ofdpa_fdb_tbl_entry *found;
	अचिन्हित दीर्घ lock_flags;
	काष्ठा hlist_node *पंचांगp;
	पूर्णांक bkt;
	पूर्णांक err = 0;

	अगर (ofdpa_port->stp_state == BR_STATE_LEARNING ||
	    ofdpa_port->stp_state == BR_STATE_FORWARDING)
		वापस 0;

	flags |= OFDPA_OP_FLAG_NOWAIT | OFDPA_OP_FLAG_REMOVE;

	spin_lock_irqsave(&ofdpa->fdb_tbl_lock, lock_flags);

	hash_क्रम_each_safe(ofdpa->fdb_tbl, bkt, पंचांगp, found, entry) अणु
		अगर (found->key.ofdpa_port != ofdpa_port)
			जारी;
		अगर (!found->learned)
			जारी;
		err = ofdpa_port_fdb_learn(ofdpa_port, flags,
					   found->key.addr,
					   found->key.vlan_id);
		अगर (err)
			जाओ err_out;
		hash_del(&found->entry);
	पूर्ण

err_out:
	spin_unlock_irqrestore(&ofdpa->fdb_tbl_lock, lock_flags);

	वापस err;
पूर्ण

अटल व्योम ofdpa_fdb_cleanup(काष्ठा समयr_list *t)
अणु
	काष्ठा ofdpa *ofdpa = from_समयr(ofdpa, t, fdb_cleanup_समयr);
	काष्ठा ofdpa_port *ofdpa_port;
	काष्ठा ofdpa_fdb_tbl_entry *entry;
	काष्ठा hlist_node *पंचांगp;
	अचिन्हित दीर्घ next_समयr = jअगरfies + ofdpa->ageing_समय;
	अचिन्हित दीर्घ expires;
	अचिन्हित दीर्घ lock_flags;
	पूर्णांक flags = OFDPA_OP_FLAG_NOWAIT | OFDPA_OP_FLAG_REMOVE |
		    OFDPA_OP_FLAG_LEARNED;
	पूर्णांक bkt;

	spin_lock_irqsave(&ofdpa->fdb_tbl_lock, lock_flags);

	hash_क्रम_each_safe(ofdpa->fdb_tbl, bkt, पंचांगp, entry, entry) अणु
		अगर (!entry->learned)
			जारी;
		ofdpa_port = entry->key.ofdpa_port;
		expires = entry->touched + ofdpa_port->ageing_समय;
		अगर (समय_beक्रमe_eq(expires, jअगरfies)) अणु
			ofdpa_port_fdb_learn(ofdpa_port, flags,
					     entry->key.addr,
					     entry->key.vlan_id);
			hash_del(&entry->entry);
		पूर्ण अन्यथा अगर (समय_beक्रमe(expires, next_समयr)) अणु
			next_समयr = expires;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&ofdpa->fdb_tbl_lock, lock_flags);

	mod_समयr(&ofdpa->fdb_cleanup_समयr, round_jअगरfies_up(next_समयr));
पूर्ण

अटल पूर्णांक ofdpa_port_router_mac(काष्ठा ofdpa_port *ofdpa_port,
				 पूर्णांक flags, __be16 vlan_id)
अणु
	u32 in_pport_mask = 0xffffffff;
	__be16 eth_type;
	स्थिर u8 *dst_mac_mask = ff_mac;
	__be16 vlan_id_mask = htons(0xffff);
	bool copy_to_cpu = false;
	पूर्णांक err;

	अगर (ntohs(vlan_id) == 0)
		vlan_id = ofdpa_port->पूर्णांकernal_vlan_id;

	eth_type = htons(ETH_P_IP);
	err = ofdpa_flow_tbl_term_mac(ofdpa_port, ofdpa_port->pport,
				      in_pport_mask, eth_type,
				      ofdpa_port->dev->dev_addr,
				      dst_mac_mask, vlan_id, vlan_id_mask,
				      copy_to_cpu, flags);
	अगर (err)
		वापस err;

	eth_type = htons(ETH_P_IPV6);
	err = ofdpa_flow_tbl_term_mac(ofdpa_port, ofdpa_port->pport,
				      in_pport_mask, eth_type,
				      ofdpa_port->dev->dev_addr,
				      dst_mac_mask, vlan_id, vlan_id_mask,
				      copy_to_cpu, flags);

	वापस err;
पूर्ण

अटल पूर्णांक ofdpa_port_fwding(काष्ठा ofdpa_port *ofdpa_port, पूर्णांक flags)
अणु
	bool pop_vlan;
	u32 out_pport;
	__be16 vlan_id;
	u16 vid;
	पूर्णांक err;

	/* Port will be क्रमwarding-enabled अगर its STP state is LEARNING
	 * or FORWARDING.  Traffic from CPU can still egress, regardless of
	 * port STP state.  Use L2 पूर्णांकerface group on port VLANs as a way
	 * to toggle port क्रमwarding: अगर क्रमwarding is disabled, L2
	 * पूर्णांकerface group will not exist.
	 */

	अगर (ofdpa_port->stp_state != BR_STATE_LEARNING &&
	    ofdpa_port->stp_state != BR_STATE_FORWARDING)
		flags |= OFDPA_OP_FLAG_REMOVE;

	out_pport = ofdpa_port->pport;
	क्रम (vid = 1; vid < VLAN_N_VID; vid++) अणु
		अगर (!test_bit(vid, ofdpa_port->vlan_biपंचांगap))
			जारी;
		vlan_id = htons(vid);
		pop_vlan = ofdpa_vlan_id_is_पूर्णांकernal(vlan_id);
		err = ofdpa_group_l2_पूर्णांकerface(ofdpa_port, flags,
					       vlan_id, out_pport, pop_vlan);
		अगर (err) अणु
			netdev_err(ofdpa_port->dev, "Error (%d) port VLAN l2 group for pport %d\n",
				   err, out_pport);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ofdpa_port_stp_update(काष्ठा ofdpa_port *ofdpa_port,
				 पूर्णांक flags, u8 state)
अणु
	bool want[OFDPA_CTRL_MAX] = अणु 0, पूर्ण;
	bool prev_ctrls[OFDPA_CTRL_MAX];
	u8 prev_state;
	पूर्णांक err;
	पूर्णांक i;

	स_नकल(prev_ctrls, ofdpa_port->ctrls, माप(prev_ctrls));
	prev_state = ofdpa_port->stp_state;

	अगर (ofdpa_port->stp_state == state)
		वापस 0;

	ofdpa_port->stp_state = state;

	चयन (state) अणु
	हाल BR_STATE_DISABLED:
		/* port is completely disabled */
		अवरोध;
	हाल BR_STATE_LISTENING:
	हाल BR_STATE_BLOCKING:
		want[OFDPA_CTRL_LINK_LOCAL_MCAST] = true;
		अवरोध;
	हाल BR_STATE_LEARNING:
	हाल BR_STATE_FORWARDING:
		अगर (!ofdpa_port_is_ovsed(ofdpa_port))
			want[OFDPA_CTRL_LINK_LOCAL_MCAST] = true;
		want[OFDPA_CTRL_IPV4_MCAST] = true;
		want[OFDPA_CTRL_IPV6_MCAST] = true;
		अगर (ofdpa_port_is_bridged(ofdpa_port))
			want[OFDPA_CTRL_DFLT_BRIDGING] = true;
		अन्यथा अगर (ofdpa_port_is_ovsed(ofdpa_port))
			want[OFDPA_CTRL_DFLT_OVS] = true;
		अन्यथा
			want[OFDPA_CTRL_LOCAL_ARP] = true;
		अवरोध;
	पूर्ण

	क्रम (i = 0; i < OFDPA_CTRL_MAX; i++) अणु
		अगर (want[i] != ofdpa_port->ctrls[i]) अणु
			पूर्णांक ctrl_flags = flags |
					 (want[i] ? 0 : OFDPA_OP_FLAG_REMOVE);
			err = ofdpa_port_ctrl(ofdpa_port, ctrl_flags,
					      &ofdpa_ctrls[i]);
			अगर (err)
				जाओ err_port_ctrl;
			ofdpa_port->ctrls[i] = want[i];
		पूर्ण
	पूर्ण

	err = ofdpa_port_fdb_flush(ofdpa_port, flags);
	अगर (err)
		जाओ err_fdb_flush;

	err = ofdpa_port_fwding(ofdpa_port, flags);
	अगर (err)
		जाओ err_port_fwding;

	वापस 0;

err_port_ctrl:
err_fdb_flush:
err_port_fwding:
	स_नकल(ofdpa_port->ctrls, prev_ctrls, माप(prev_ctrls));
	ofdpa_port->stp_state = prev_state;
	वापस err;
पूर्ण

अटल पूर्णांक ofdpa_port_fwd_enable(काष्ठा ofdpa_port *ofdpa_port, पूर्णांक flags)
अणु
	अगर (ofdpa_port_is_bridged(ofdpa_port))
		/* bridge STP will enable port */
		वापस 0;

	/* port is not bridged, so simulate going to FORWARDING state */
	वापस ofdpa_port_stp_update(ofdpa_port, flags,
				     BR_STATE_FORWARDING);
पूर्ण

अटल पूर्णांक ofdpa_port_fwd_disable(काष्ठा ofdpa_port *ofdpa_port, पूर्णांक flags)
अणु
	अगर (ofdpa_port_is_bridged(ofdpa_port))
		/* bridge STP will disable port */
		वापस 0;

	/* port is not bridged, so simulate going to DISABLED state */
	वापस ofdpa_port_stp_update(ofdpa_port, flags,
				     BR_STATE_DISABLED);
पूर्ण

अटल पूर्णांक ofdpa_port_vlan_add(काष्ठा ofdpa_port *ofdpa_port,
			       u16 vid, u16 flags)
अणु
	पूर्णांक err;

	/* XXX deal with flags क्रम PVID and untagged */

	err = ofdpa_port_vlan(ofdpa_port, 0, vid);
	अगर (err)
		वापस err;

	err = ofdpa_port_router_mac(ofdpa_port, 0, htons(vid));
	अगर (err)
		ofdpa_port_vlan(ofdpa_port,
				OFDPA_OP_FLAG_REMOVE, vid);

	वापस err;
पूर्ण

अटल पूर्णांक ofdpa_port_vlan_del(काष्ठा ofdpa_port *ofdpa_port,
			       u16 vid, u16 flags)
अणु
	पूर्णांक err;

	err = ofdpa_port_router_mac(ofdpa_port, OFDPA_OP_FLAG_REMOVE,
				    htons(vid));
	अगर (err)
		वापस err;

	वापस ofdpa_port_vlan(ofdpa_port, OFDPA_OP_FLAG_REMOVE,
			       vid);
पूर्ण

अटल काष्ठा ofdpa_पूर्णांकernal_vlan_tbl_entry *
ofdpa_पूर्णांकernal_vlan_tbl_find(स्थिर काष्ठा ofdpa *ofdpa, पूर्णांक अगरindex)
अणु
	काष्ठा ofdpa_पूर्णांकernal_vlan_tbl_entry *found;

	hash_क्रम_each_possible(ofdpa->पूर्णांकernal_vlan_tbl, found,
			       entry, अगरindex) अणु
		अगर (found->अगरindex == अगरindex)
			वापस found;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल __be16 ofdpa_port_पूर्णांकernal_vlan_id_get(काष्ठा ofdpa_port *ofdpa_port,
					      पूर्णांक अगरindex)
अणु
	काष्ठा ofdpa *ofdpa = ofdpa_port->ofdpa;
	काष्ठा ofdpa_पूर्णांकernal_vlan_tbl_entry *entry;
	काष्ठा ofdpa_पूर्णांकernal_vlan_tbl_entry *found;
	अचिन्हित दीर्घ lock_flags;
	पूर्णांक i;

	entry = kzalloc(माप(*entry), GFP_KERNEL);
	अगर (!entry)
		वापस 0;

	entry->अगरindex = अगरindex;

	spin_lock_irqsave(&ofdpa->पूर्णांकernal_vlan_tbl_lock, lock_flags);

	found = ofdpa_पूर्णांकernal_vlan_tbl_find(ofdpa, अगरindex);
	अगर (found) अणु
		kमुक्त(entry);
		जाओ found;
	पूर्ण

	found = entry;
	hash_add(ofdpa->पूर्णांकernal_vlan_tbl, &found->entry, found->अगरindex);

	क्रम (i = 0; i < OFDPA_N_INTERNAL_VLANS; i++) अणु
		अगर (test_and_set_bit(i, ofdpa->पूर्णांकernal_vlan_biपंचांगap))
			जारी;
		found->vlan_id = htons(OFDPA_INTERNAL_VLAN_ID_BASE + i);
		जाओ found;
	पूर्ण

	netdev_err(ofdpa_port->dev, "Out of internal VLAN IDs\n");

found:
	found->ref_count++;
	spin_unlock_irqrestore(&ofdpa->पूर्णांकernal_vlan_tbl_lock, lock_flags);

	वापस found->vlan_id;
पूर्ण

अटल पूर्णांक ofdpa_port_fib_ipv4(काष्ठा ofdpa_port *ofdpa_port,  __be32 dst,
			       पूर्णांक dst_len, काष्ठा fib_info *fi, u32 tb_id,
			       पूर्णांक flags)
अणु
	स्थिर काष्ठा fib_nh *nh;
	__be16 eth_type = htons(ETH_P_IP);
	__be32 dst_mask = inet_make_mask(dst_len);
	__be16 पूर्णांकernal_vlan_id = ofdpa_port->पूर्णांकernal_vlan_id;
	u32 priority = fi->fib_priority;
	क्रमागत rocker_of_dpa_table_id जाओ_tbl =
		ROCKER_OF_DPA_TABLE_ID_ACL_POLICY;
	u32 group_id;
	bool nh_on_port;
	bool has_gw;
	u32 index;
	पूर्णांक err;

	/* XXX support ECMP */

	nh = fib_info_nh(fi, 0);
	nh_on_port = (nh->fib_nh_dev == ofdpa_port->dev);
	has_gw = !!nh->fib_nh_gw4;

	अगर (has_gw && nh_on_port) अणु
		err = ofdpa_port_ipv4_nh(ofdpa_port, flags,
					 nh->fib_nh_gw4, &index);
		अगर (err)
			वापस err;

		group_id = ROCKER_GROUP_L3_UNICAST(index);
	पूर्ण अन्यथा अणु
		/* Send to CPU क्रम processing */
		group_id = ROCKER_GROUP_L2_INTERFACE(पूर्णांकernal_vlan_id, 0);
	पूर्ण

	err = ofdpa_flow_tbl_ucast4_routing(ofdpa_port, eth_type, dst,
					    dst_mask, priority, जाओ_tbl,
					    group_id, fi, flags);
	अगर (err)
		netdev_err(ofdpa_port->dev, "Error (%d) IPv4 route %pI4\n",
			   err, &dst);

	वापस err;
पूर्ण

अटल व्योम
ofdpa_port_पूर्णांकernal_vlan_id_put(स्थिर काष्ठा ofdpa_port *ofdpa_port,
				पूर्णांक अगरindex)
अणु
	काष्ठा ofdpa *ofdpa = ofdpa_port->ofdpa;
	काष्ठा ofdpa_पूर्णांकernal_vlan_tbl_entry *found;
	अचिन्हित दीर्घ lock_flags;
	अचिन्हित दीर्घ bit;

	spin_lock_irqsave(&ofdpa->पूर्णांकernal_vlan_tbl_lock, lock_flags);

	found = ofdpa_पूर्णांकernal_vlan_tbl_find(ofdpa, अगरindex);
	अगर (!found) अणु
		netdev_err(ofdpa_port->dev,
			   "ifindex (%d) not found in internal VLAN tbl\n",
			   अगरindex);
		जाओ not_found;
	पूर्ण

	अगर (--found->ref_count <= 0) अणु
		bit = ntohs(found->vlan_id) - OFDPA_INTERNAL_VLAN_ID_BASE;
		clear_bit(bit, ofdpa->पूर्णांकernal_vlan_biपंचांगap);
		hash_del(&found->entry);
		kमुक्त(found);
	पूर्ण

not_found:
	spin_unlock_irqrestore(&ofdpa->पूर्णांकernal_vlan_tbl_lock, lock_flags);
पूर्ण

/**********************************
 * Rocker world ops implementation
 **********************************/

अटल पूर्णांक ofdpa_init(काष्ठा rocker *rocker)
अणु
	काष्ठा ofdpa *ofdpa = rocker->wpriv;

	ofdpa->rocker = rocker;

	hash_init(ofdpa->flow_tbl);
	spin_lock_init(&ofdpa->flow_tbl_lock);

	hash_init(ofdpa->group_tbl);
	spin_lock_init(&ofdpa->group_tbl_lock);

	hash_init(ofdpa->fdb_tbl);
	spin_lock_init(&ofdpa->fdb_tbl_lock);

	hash_init(ofdpa->पूर्णांकernal_vlan_tbl);
	spin_lock_init(&ofdpa->पूर्णांकernal_vlan_tbl_lock);

	hash_init(ofdpa->neigh_tbl);
	spin_lock_init(&ofdpa->neigh_tbl_lock);

	समयr_setup(&ofdpa->fdb_cleanup_समयr, ofdpa_fdb_cleanup, 0);
	mod_समयr(&ofdpa->fdb_cleanup_समयr, jअगरfies);

	ofdpa->ageing_समय = BR_DEFAULT_AGEING_TIME;

	वापस 0;
पूर्ण

अटल व्योम ofdpa_fini(काष्ठा rocker *rocker)
अणु
	काष्ठा ofdpa *ofdpa = rocker->wpriv;

	अचिन्हित दीर्घ flags;
	काष्ठा ofdpa_flow_tbl_entry *flow_entry;
	काष्ठा ofdpa_group_tbl_entry *group_entry;
	काष्ठा ofdpa_fdb_tbl_entry *fdb_entry;
	काष्ठा ofdpa_पूर्णांकernal_vlan_tbl_entry *पूर्णांकernal_vlan_entry;
	काष्ठा ofdpa_neigh_tbl_entry *neigh_entry;
	काष्ठा hlist_node *पंचांगp;
	पूर्णांक bkt;

	del_समयr_sync(&ofdpa->fdb_cleanup_समयr);
	flush_workqueue(rocker->rocker_owq);

	spin_lock_irqsave(&ofdpa->flow_tbl_lock, flags);
	hash_क्रम_each_safe(ofdpa->flow_tbl, bkt, पंचांगp, flow_entry, entry)
		hash_del(&flow_entry->entry);
	spin_unlock_irqrestore(&ofdpa->flow_tbl_lock, flags);

	spin_lock_irqsave(&ofdpa->group_tbl_lock, flags);
	hash_क्रम_each_safe(ofdpa->group_tbl, bkt, पंचांगp, group_entry, entry)
		hash_del(&group_entry->entry);
	spin_unlock_irqrestore(&ofdpa->group_tbl_lock, flags);

	spin_lock_irqsave(&ofdpa->fdb_tbl_lock, flags);
	hash_क्रम_each_safe(ofdpa->fdb_tbl, bkt, पंचांगp, fdb_entry, entry)
		hash_del(&fdb_entry->entry);
	spin_unlock_irqrestore(&ofdpa->fdb_tbl_lock, flags);

	spin_lock_irqsave(&ofdpa->पूर्णांकernal_vlan_tbl_lock, flags);
	hash_क्रम_each_safe(ofdpa->पूर्णांकernal_vlan_tbl, bkt,
			   पंचांगp, पूर्णांकernal_vlan_entry, entry)
		hash_del(&पूर्णांकernal_vlan_entry->entry);
	spin_unlock_irqrestore(&ofdpa->पूर्णांकernal_vlan_tbl_lock, flags);

	spin_lock_irqsave(&ofdpa->neigh_tbl_lock, flags);
	hash_क्रम_each_safe(ofdpa->neigh_tbl, bkt, पंचांगp, neigh_entry, entry)
		hash_del(&neigh_entry->entry);
	spin_unlock_irqrestore(&ofdpa->neigh_tbl_lock, flags);
पूर्ण

अटल पूर्णांक ofdpa_port_pre_init(काष्ठा rocker_port *rocker_port)
अणु
	काष्ठा ofdpa_port *ofdpa_port = rocker_port->wpriv;

	ofdpa_port->ofdpa = rocker_port->rocker->wpriv;
	ofdpa_port->rocker_port = rocker_port;
	ofdpa_port->dev = rocker_port->dev;
	ofdpa_port->pport = rocker_port->pport;
	ofdpa_port->brport_flags = BR_LEARNING;
	ofdpa_port->ageing_समय = BR_DEFAULT_AGEING_TIME;
	वापस 0;
पूर्ण

अटल पूर्णांक ofdpa_port_init(काष्ठा rocker_port *rocker_port)
अणु
	काष्ठा ofdpa_port *ofdpa_port = rocker_port->wpriv;
	पूर्णांक err;

	rocker_port_set_learning(rocker_port,
				 !!(ofdpa_port->brport_flags & BR_LEARNING));

	err = ofdpa_port_ig_tbl(ofdpa_port, 0);
	अगर (err) अणु
		netdev_err(ofdpa_port->dev, "install ig port table failed\n");
		वापस err;
	पूर्ण

	ofdpa_port->पूर्णांकernal_vlan_id =
		ofdpa_port_पूर्णांकernal_vlan_id_get(ofdpa_port,
						ofdpa_port->dev->अगरindex);

	err = ofdpa_port_vlan_add(ofdpa_port, OFDPA_UNTAGGED_VID, 0);
	अगर (err) अणु
		netdev_err(ofdpa_port->dev, "install untagged VLAN failed\n");
		जाओ err_untagged_vlan;
	पूर्ण
	वापस 0;

err_untagged_vlan:
	ofdpa_port_ig_tbl(ofdpa_port, OFDPA_OP_FLAG_REMOVE);
	वापस err;
पूर्ण

अटल व्योम ofdpa_port_fini(काष्ठा rocker_port *rocker_port)
अणु
	काष्ठा ofdpa_port *ofdpa_port = rocker_port->wpriv;

	ofdpa_port_ig_tbl(ofdpa_port, OFDPA_OP_FLAG_REMOVE);
पूर्ण

अटल पूर्णांक ofdpa_port_खोलो(काष्ठा rocker_port *rocker_port)
अणु
	काष्ठा ofdpa_port *ofdpa_port = rocker_port->wpriv;

	वापस ofdpa_port_fwd_enable(ofdpa_port, 0);
पूर्ण

अटल व्योम ofdpa_port_stop(काष्ठा rocker_port *rocker_port)
अणु
	काष्ठा ofdpa_port *ofdpa_port = rocker_port->wpriv;

	ofdpa_port_fwd_disable(ofdpa_port, OFDPA_OP_FLAG_NOWAIT);
पूर्ण

अटल पूर्णांक ofdpa_port_attr_stp_state_set(काष्ठा rocker_port *rocker_port,
					 u8 state)
अणु
	काष्ठा ofdpa_port *ofdpa_port = rocker_port->wpriv;

	वापस ofdpa_port_stp_update(ofdpa_port, 0, state);
पूर्ण

अटल पूर्णांक ofdpa_port_attr_bridge_flags_set(काष्ठा rocker_port *rocker_port,
					    अचिन्हित दीर्घ brport_flags)
अणु
	काष्ठा ofdpa_port *ofdpa_port = rocker_port->wpriv;
	अचिन्हित दीर्घ orig_flags;
	पूर्णांक err = 0;

	orig_flags = ofdpa_port->brport_flags;
	ofdpa_port->brport_flags = brport_flags;

	अगर ((orig_flags ^ ofdpa_port->brport_flags) & BR_LEARNING)
		err = rocker_port_set_learning(ofdpa_port->rocker_port,
					       !!(ofdpa_port->brport_flags & BR_LEARNING));

	वापस err;
पूर्ण

अटल पूर्णांक
ofdpa_port_attr_bridge_flags_support_get(स्थिर काष्ठा rocker_port *
					 rocker_port,
					 अचिन्हित दीर्घ *
					 p_brport_flags_support)
अणु
	*p_brport_flags_support = BR_LEARNING;
	वापस 0;
पूर्ण

अटल पूर्णांक
ofdpa_port_attr_bridge_ageing_समय_set(काष्ठा rocker_port *rocker_port,
				       u32 ageing_समय)
अणु
	काष्ठा ofdpa_port *ofdpa_port = rocker_port->wpriv;
	काष्ठा ofdpa *ofdpa = ofdpa_port->ofdpa;

	ofdpa_port->ageing_समय = घड़ी_प्रकार_to_jअगरfies(ageing_समय);
	अगर (ofdpa_port->ageing_समय < ofdpa->ageing_समय)
		ofdpa->ageing_समय = ofdpa_port->ageing_समय;
	mod_समयr(&ofdpa_port->ofdpa->fdb_cleanup_समयr, jअगरfies);

	वापस 0;
पूर्ण

अटल पूर्णांक ofdpa_port_obj_vlan_add(काष्ठा rocker_port *rocker_port,
				   स्थिर काष्ठा चयनdev_obj_port_vlan *vlan)
अणु
	काष्ठा ofdpa_port *ofdpa_port = rocker_port->wpriv;

	वापस ofdpa_port_vlan_add(ofdpa_port, vlan->vid, vlan->flags);
पूर्ण

अटल पूर्णांक ofdpa_port_obj_vlan_del(काष्ठा rocker_port *rocker_port,
				   स्थिर काष्ठा चयनdev_obj_port_vlan *vlan)
अणु
	काष्ठा ofdpa_port *ofdpa_port = rocker_port->wpriv;

	वापस ofdpa_port_vlan_del(ofdpa_port, vlan->vid, vlan->flags);
पूर्ण

अटल पूर्णांक ofdpa_port_obj_fdb_add(काष्ठा rocker_port *rocker_port,
				  u16 vid, स्थिर अचिन्हित अक्षर *addr)
अणु
	काष्ठा ofdpa_port *ofdpa_port = rocker_port->wpriv;
	__be16 vlan_id = ofdpa_port_vid_to_vlan(ofdpa_port, vid, शून्य);

	अगर (!ofdpa_port_is_bridged(ofdpa_port))
		वापस -EINVAL;

	वापस ofdpa_port_fdb(ofdpa_port, addr, vlan_id, 0);
पूर्ण

अटल पूर्णांक ofdpa_port_obj_fdb_del(काष्ठा rocker_port *rocker_port,
				  u16 vid, स्थिर अचिन्हित अक्षर *addr)
अणु
	काष्ठा ofdpa_port *ofdpa_port = rocker_port->wpriv;
	__be16 vlan_id = ofdpa_port_vid_to_vlan(ofdpa_port, vid, शून्य);
	पूर्णांक flags = OFDPA_OP_FLAG_REMOVE;

	अगर (!ofdpa_port_is_bridged(ofdpa_port))
		वापस -EINVAL;

	वापस ofdpa_port_fdb(ofdpa_port, addr, vlan_id, flags);
पूर्ण

अटल पूर्णांक ofdpa_port_bridge_join(काष्ठा ofdpa_port *ofdpa_port,
				  काष्ठा net_device *bridge)
अणु
	पूर्णांक err;

	/* Port is joining bridge, so the पूर्णांकernal VLAN क्रम the
	 * port is going to change to the bridge पूर्णांकernal VLAN.
	 * Let's हटाओ untagged VLAN (vid=0) from port and
	 * re-add once पूर्णांकernal VLAN has changed.
	 */

	err = ofdpa_port_vlan_del(ofdpa_port, OFDPA_UNTAGGED_VID, 0);
	अगर (err)
		वापस err;

	ofdpa_port_पूर्णांकernal_vlan_id_put(ofdpa_port,
					ofdpa_port->dev->अगरindex);
	ofdpa_port->पूर्णांकernal_vlan_id =
		ofdpa_port_पूर्णांकernal_vlan_id_get(ofdpa_port, bridge->अगरindex);

	ofdpa_port->bridge_dev = bridge;

	वापस ofdpa_port_vlan_add(ofdpa_port, OFDPA_UNTAGGED_VID, 0);
पूर्ण

अटल पूर्णांक ofdpa_port_bridge_leave(काष्ठा ofdpa_port *ofdpa_port)
अणु
	पूर्णांक err;

	err = ofdpa_port_vlan_del(ofdpa_port, OFDPA_UNTAGGED_VID, 0);
	अगर (err)
		वापस err;

	ofdpa_port_पूर्णांकernal_vlan_id_put(ofdpa_port,
					ofdpa_port->bridge_dev->अगरindex);
	ofdpa_port->पूर्णांकernal_vlan_id =
		ofdpa_port_पूर्णांकernal_vlan_id_get(ofdpa_port,
						ofdpa_port->dev->अगरindex);

	ofdpa_port->bridge_dev = शून्य;

	err = ofdpa_port_vlan_add(ofdpa_port, OFDPA_UNTAGGED_VID, 0);
	अगर (err)
		वापस err;

	अगर (ofdpa_port->dev->flags & IFF_UP)
		err = ofdpa_port_fwd_enable(ofdpa_port, 0);

	वापस err;
पूर्ण

अटल पूर्णांक ofdpa_port_ovs_changed(काष्ठा ofdpa_port *ofdpa_port,
				  काष्ठा net_device *master)
अणु
	पूर्णांक err;

	ofdpa_port->bridge_dev = master;

	err = ofdpa_port_fwd_disable(ofdpa_port, 0);
	अगर (err)
		वापस err;
	err = ofdpa_port_fwd_enable(ofdpa_port, 0);

	वापस err;
पूर्ण

अटल पूर्णांक ofdpa_port_master_linked(काष्ठा rocker_port *rocker_port,
				    काष्ठा net_device *master)
अणु
	काष्ठा ofdpa_port *ofdpa_port = rocker_port->wpriv;
	पूर्णांक err = 0;

	अगर (netअगर_is_bridge_master(master))
		err = ofdpa_port_bridge_join(ofdpa_port, master);
	अन्यथा अगर (netअगर_is_ovs_master(master))
		err = ofdpa_port_ovs_changed(ofdpa_port, master);
	वापस err;
पूर्ण

अटल पूर्णांक ofdpa_port_master_unlinked(काष्ठा rocker_port *rocker_port,
				      काष्ठा net_device *master)
अणु
	काष्ठा ofdpa_port *ofdpa_port = rocker_port->wpriv;
	पूर्णांक err = 0;

	अगर (ofdpa_port_is_bridged(ofdpa_port))
		err = ofdpa_port_bridge_leave(ofdpa_port);
	अन्यथा अगर (ofdpa_port_is_ovsed(ofdpa_port))
		err = ofdpa_port_ovs_changed(ofdpa_port, शून्य);
	वापस err;
पूर्ण

अटल पूर्णांक ofdpa_port_neigh_update(काष्ठा rocker_port *rocker_port,
				   काष्ठा neighbour *n)
अणु
	काष्ठा ofdpa_port *ofdpa_port = rocker_port->wpriv;
	पूर्णांक flags = (n->nud_state & NUD_VALID ? 0 : OFDPA_OP_FLAG_REMOVE) |
						    OFDPA_OP_FLAG_NOWAIT;
	__be32 ip_addr = *(__be32 *) n->primary_key;

	वापस ofdpa_port_ipv4_neigh(ofdpa_port, flags, ip_addr, n->ha);
पूर्ण

अटल पूर्णांक ofdpa_port_neigh_destroy(काष्ठा rocker_port *rocker_port,
				    काष्ठा neighbour *n)
अणु
	काष्ठा ofdpa_port *ofdpa_port = rocker_port->wpriv;
	पूर्णांक flags = OFDPA_OP_FLAG_REMOVE | OFDPA_OP_FLAG_NOWAIT;
	__be32 ip_addr = *(__be32 *) n->primary_key;

	वापस ofdpa_port_ipv4_neigh(ofdpa_port, flags, ip_addr, n->ha);
पूर्ण

अटल पूर्णांक ofdpa_port_ev_mac_vlan_seen(काष्ठा rocker_port *rocker_port,
				       स्थिर अचिन्हित अक्षर *addr,
				       __be16 vlan_id)
अणु
	काष्ठा ofdpa_port *ofdpa_port = rocker_port->wpriv;
	पूर्णांक flags = OFDPA_OP_FLAG_NOWAIT | OFDPA_OP_FLAG_LEARNED;

	अगर (ofdpa_port->stp_state != BR_STATE_LEARNING &&
	    ofdpa_port->stp_state != BR_STATE_FORWARDING)
		वापस 0;

	वापस ofdpa_port_fdb(ofdpa_port, addr, vlan_id, flags);
पूर्ण

अटल काष्ठा ofdpa_port *ofdpa_port_dev_lower_find(काष्ठा net_device *dev,
						    काष्ठा rocker *rocker)
अणु
	काष्ठा rocker_port *rocker_port;

	rocker_port = rocker_port_dev_lower_find(dev, rocker);
	वापस rocker_port ? rocker_port->wpriv : शून्य;
पूर्ण

अटल पूर्णांक ofdpa_fib4_add(काष्ठा rocker *rocker,
			  स्थिर काष्ठा fib_entry_notअगरier_info *fen_info)
अणु
	काष्ठा ofdpa *ofdpa = rocker->wpriv;
	काष्ठा ofdpa_port *ofdpa_port;
	काष्ठा fib_nh *nh;
	पूर्णांक err;

	अगर (ofdpa->fib_पातed)
		वापस 0;
	nh = fib_info_nh(fen_info->fi, 0);
	ofdpa_port = ofdpa_port_dev_lower_find(nh->fib_nh_dev, rocker);
	अगर (!ofdpa_port)
		वापस 0;
	err = ofdpa_port_fib_ipv4(ofdpa_port, htonl(fen_info->dst),
				  fen_info->dst_len, fen_info->fi,
				  fen_info->tb_id, 0);
	अगर (err)
		वापस err;
	nh->fib_nh_flags |= RTNH_F_OFFLOAD;
	वापस 0;
पूर्ण

अटल पूर्णांक ofdpa_fib4_del(काष्ठा rocker *rocker,
			  स्थिर काष्ठा fib_entry_notअगरier_info *fen_info)
अणु
	काष्ठा ofdpa *ofdpa = rocker->wpriv;
	काष्ठा ofdpa_port *ofdpa_port;
	काष्ठा fib_nh *nh;

	अगर (ofdpa->fib_पातed)
		वापस 0;
	nh = fib_info_nh(fen_info->fi, 0);
	ofdpa_port = ofdpa_port_dev_lower_find(nh->fib_nh_dev, rocker);
	अगर (!ofdpa_port)
		वापस 0;
	nh->fib_nh_flags &= ~RTNH_F_OFFLOAD;
	वापस ofdpa_port_fib_ipv4(ofdpa_port, htonl(fen_info->dst),
				   fen_info->dst_len, fen_info->fi,
				   fen_info->tb_id, OFDPA_OP_FLAG_REMOVE);
पूर्ण

अटल व्योम ofdpa_fib4_पात(काष्ठा rocker *rocker)
अणु
	काष्ठा ofdpa *ofdpa = rocker->wpriv;
	काष्ठा ofdpa_port *ofdpa_port;
	काष्ठा ofdpa_flow_tbl_entry *flow_entry;
	काष्ठा hlist_node *पंचांगp;
	अचिन्हित दीर्घ flags;
	पूर्णांक bkt;

	अगर (ofdpa->fib_पातed)
		वापस;

	spin_lock_irqsave(&ofdpa->flow_tbl_lock, flags);
	hash_क्रम_each_safe(ofdpa->flow_tbl, bkt, पंचांगp, flow_entry, entry) अणु
		काष्ठा fib_nh *nh;

		अगर (flow_entry->key.tbl_id !=
		    ROCKER_OF_DPA_TABLE_ID_UNICAST_ROUTING)
			जारी;
		nh = fib_info_nh(flow_entry->fi, 0);
		ofdpa_port = ofdpa_port_dev_lower_find(nh->fib_nh_dev, rocker);
		अगर (!ofdpa_port)
			जारी;
		nh->fib_nh_flags &= ~RTNH_F_OFFLOAD;
		ofdpa_flow_tbl_del(ofdpa_port, OFDPA_OP_FLAG_REMOVE,
				   flow_entry);
	पूर्ण
	spin_unlock_irqrestore(&ofdpa->flow_tbl_lock, flags);
	ofdpa->fib_पातed = true;
पूर्ण

काष्ठा rocker_world_ops rocker_ofdpa_ops = अणु
	.kind = "ofdpa",
	.priv_size = माप(काष्ठा ofdpa),
	.port_priv_size = माप(काष्ठा ofdpa_port),
	.mode = ROCKER_PORT_MODE_OF_DPA,
	.init = ofdpa_init,
	.fini = ofdpa_fini,
	.port_pre_init = ofdpa_port_pre_init,
	.port_init = ofdpa_port_init,
	.port_fini = ofdpa_port_fini,
	.port_खोलो = ofdpa_port_खोलो,
	.port_stop = ofdpa_port_stop,
	.port_attr_stp_state_set = ofdpa_port_attr_stp_state_set,
	.port_attr_bridge_flags_set = ofdpa_port_attr_bridge_flags_set,
	.port_attr_bridge_flags_support_get = ofdpa_port_attr_bridge_flags_support_get,
	.port_attr_bridge_ageing_समय_set = ofdpa_port_attr_bridge_ageing_समय_set,
	.port_obj_vlan_add = ofdpa_port_obj_vlan_add,
	.port_obj_vlan_del = ofdpa_port_obj_vlan_del,
	.port_obj_fdb_add = ofdpa_port_obj_fdb_add,
	.port_obj_fdb_del = ofdpa_port_obj_fdb_del,
	.port_master_linked = ofdpa_port_master_linked,
	.port_master_unlinked = ofdpa_port_master_unlinked,
	.port_neigh_update = ofdpa_port_neigh_update,
	.port_neigh_destroy = ofdpa_port_neigh_destroy,
	.port_ev_mac_vlan_seen = ofdpa_port_ev_mac_vlan_seen,
	.fib4_add = ofdpa_fib4_add,
	.fib4_del = ofdpa_fib4_del,
	.fib4_पात = ofdpa_fib4_पात,
पूर्ण;
