<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause) */
/* Copyright (C) 2017-2018 Netronome Systems, Inc. */

#अगर_अघोषित NFP_FLOWER_CMSG_H
#घोषणा NFP_FLOWER_CMSG_H

#समावेश <linux/bitfield.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/types.h>
#समावेश <net/geneve.h>
#समावेश <net/gre.h>
#समावेश <net/vxlan.h>

#समावेश "../nfp_app.h"
#समावेश "../nfpcore/nfp_cpp.h"

#घोषणा NFP_FLOWER_LAYER_EXT_META	BIT(0)
#घोषणा NFP_FLOWER_LAYER_PORT		BIT(1)
#घोषणा NFP_FLOWER_LAYER_MAC		BIT(2)
#घोषणा NFP_FLOWER_LAYER_TP		BIT(3)
#घोषणा NFP_FLOWER_LAYER_IPV4		BIT(4)
#घोषणा NFP_FLOWER_LAYER_IPV6		BIT(5)
#घोषणा NFP_FLOWER_LAYER_CT		BIT(6)
#घोषणा NFP_FLOWER_LAYER_VXLAN		BIT(7)

#घोषणा NFP_FLOWER_LAYER2_GRE		BIT(0)
#घोषणा NFP_FLOWER_LAYER2_QINQ		BIT(4)
#घोषणा NFP_FLOWER_LAYER2_GENEVE	BIT(5)
#घोषणा NFP_FLOWER_LAYER2_GENEVE_OP	BIT(6)
#घोषणा NFP_FLOWER_LAYER2_TUN_IPV6	BIT(7)

#घोषणा NFP_FLOWER_MASK_VLAN_PRIO	GENMASK(15, 13)
#घोषणा NFP_FLOWER_MASK_VLAN_PRESENT	BIT(12)
#घोषणा NFP_FLOWER_MASK_VLAN_VID	GENMASK(11, 0)

#घोषणा NFP_FLOWER_MASK_MPLS_LB		GENMASK(31, 12)
#घोषणा NFP_FLOWER_MASK_MPLS_TC		GENMASK(11, 9)
#घोषणा NFP_FLOWER_MASK_MPLS_BOS	BIT(8)
#घोषणा NFP_FLOWER_MASK_MPLS_Q		BIT(0)

#घोषणा NFP_FL_IP_FRAG_FIRST		BIT(7)
#घोषणा NFP_FL_IP_FRAGMENTED		BIT(6)

/* GRE Tunnel flags */
#घोषणा NFP_FL_GRE_FLAG_KEY		BIT(2)

/* Compressed HW representation of TCP Flags */
#घोषणा NFP_FL_TCP_FLAG_URG		BIT(4)
#घोषणा NFP_FL_TCP_FLAG_PSH		BIT(3)
#घोषणा NFP_FL_TCP_FLAG_RST		BIT(2)
#घोषणा NFP_FL_TCP_FLAG_SYN		BIT(1)
#घोषणा NFP_FL_TCP_FLAG_FIN		BIT(0)

#घोषणा NFP_FL_SC_ACT_DROP		0x80000000
#घोषणा NFP_FL_SC_ACT_USER		0x7D000000
#घोषणा NFP_FL_SC_ACT_POPV		0x6A000000
#घोषणा NFP_FL_SC_ACT_शून्य		0x00000000

/* The maximum action list size (in bytes) supported by the NFP.
 */
#घोषणा NFP_FL_MAX_A_SIZ		1216
#घोषणा NFP_FL_LW_SIZ			2

/* Maximum allowed geneve options */
#घोषणा NFP_FL_MAX_GENEVE_OPT_ACT	32
#घोषणा NFP_FL_MAX_GENEVE_OPT_CNT	64
#घोषणा NFP_FL_MAX_GENEVE_OPT_KEY	32
#घोषणा NFP_FL_MAX_GENEVE_OPT_KEY_V6	8

/* Action opcodes */
#घोषणा NFP_FL_ACTION_OPCODE_OUTPUT		0
#घोषणा NFP_FL_ACTION_OPCODE_PUSH_VLAN		1
#घोषणा NFP_FL_ACTION_OPCODE_POP_VLAN		2
#घोषणा NFP_FL_ACTION_OPCODE_PUSH_MPLS		3
#घोषणा NFP_FL_ACTION_OPCODE_POP_MPLS		4
#घोषणा NFP_FL_ACTION_OPCODE_SET_TUNNEL		6
#घोषणा NFP_FL_ACTION_OPCODE_SET_ETHERNET	7
#घोषणा NFP_FL_ACTION_OPCODE_SET_MPLS		8
#घोषणा NFP_FL_ACTION_OPCODE_SET_IPV4_ADDRS	9
#घोषणा NFP_FL_ACTION_OPCODE_SET_IPV4_TTL_TOS	10
#घोषणा NFP_FL_ACTION_OPCODE_SET_IPV6_SRC	11
#घोषणा NFP_FL_ACTION_OPCODE_SET_IPV6_DST	12
#घोषणा NFP_FL_ACTION_OPCODE_SET_IPV6_TC_HL_FL	13
#घोषणा NFP_FL_ACTION_OPCODE_SET_UDP		14
#घोषणा NFP_FL_ACTION_OPCODE_SET_TCP		15
#घोषणा NFP_FL_ACTION_OPCODE_PRE_LAG		16
#घोषणा NFP_FL_ACTION_OPCODE_PRE_TUNNEL		17
#घोषणा NFP_FL_ACTION_OPCODE_PUSH_GENEVE	26
#घोषणा NFP_FL_ACTION_OPCODE_NUM		32

#घोषणा NFP_FL_OUT_FLAGS_LAST		BIT(15)
#घोषणा NFP_FL_OUT_FLAGS_USE_TUN	BIT(4)
#घोषणा NFP_FL_OUT_FLAGS_TYPE_IDX	GENMASK(2, 0)

#घोषणा NFP_FL_PUSH_VLAN_PRIO		GENMASK(15, 13)
#घोषणा NFP_FL_PUSH_VLAN_VID		GENMASK(11, 0)

#घोषणा IPV6_FLOW_LABEL_MASK		cpu_to_be32(0x000fffff)

/* LAG ports */
#घोषणा NFP_FL_LAG_OUT			0xC0DE0000

/* Tunnel ports */
#घोषणा NFP_FL_PORT_TYPE_TUN		0x50000000
#घोषणा NFP_FL_TUNNEL_TYPE		GENMASK(7, 4)
#घोषणा NFP_FL_PRE_TUN_INDEX		GENMASK(2, 0)

#घोषणा NFP_FLOWER_WORKQ_MAX_SKBS	30000

/* Cmesg reply (empirical) समयout*/
#घोषणा NFP_FL_REPLY_TIMEOUT		msecs_to_jअगरfies(40)

#घोषणा nfp_flower_cmsg_warn(app, fmt, args...)                         \
	करो अणु                                                            \
		अगर (net_ratelimit())                                    \
			nfp_warn((app)->cpp, fmt, ## args);             \
	पूर्ण जबतक (0)

क्रमागत nfp_flower_tun_type अणु
	NFP_FL_TUNNEL_NONE =	0,
	NFP_FL_TUNNEL_GRE =	1,
	NFP_FL_TUNNEL_VXLAN =	2,
	NFP_FL_TUNNEL_GENEVE =	4,
पूर्ण;

काष्ठा nfp_fl_act_head अणु
	u8 jump_id;
	u8 len_lw;
पूर्ण;

काष्ठा nfp_fl_set_eth अणु
	काष्ठा nfp_fl_act_head head;
	__be16 reserved;
	u8 eth_addr_mask[ETH_ALEN * 2];
	u8 eth_addr_val[ETH_ALEN * 2];
पूर्ण;

काष्ठा nfp_fl_set_ip4_addrs अणु
	काष्ठा nfp_fl_act_head head;
	__be16 reserved;
	__be32 ipv4_src_mask;
	__be32 ipv4_src;
	__be32 ipv4_dst_mask;
	__be32 ipv4_dst;
पूर्ण;

काष्ठा nfp_fl_set_ip4_ttl_tos अणु
	काष्ठा nfp_fl_act_head head;
	u8 ipv4_ttl_mask;
	u8 ipv4_tos_mask;
	u8 ipv4_ttl;
	u8 ipv4_tos;
	__be16 reserved;
पूर्ण;

काष्ठा nfp_fl_set_ipv6_tc_hl_fl अणु
	काष्ठा nfp_fl_act_head head;
	u8 ipv6_tc_mask;
	u8 ipv6_hop_limit_mask;
	__be16 reserved;
	u8 ipv6_tc;
	u8 ipv6_hop_limit;
	__be32 ipv6_label_mask;
	__be32 ipv6_label;
पूर्ण;

काष्ठा nfp_fl_set_ipv6_addr अणु
	काष्ठा nfp_fl_act_head head;
	__be16 reserved;
	काष्ठा अणु
		__be32 mask;
		__be32 exact;
	पूर्ण ipv6[4];
पूर्ण;

काष्ठा nfp_fl_set_tport अणु
	काष्ठा nfp_fl_act_head head;
	__be16 reserved;
	u8 tp_port_mask[4];
	u8 tp_port_val[4];
पूर्ण;

काष्ठा nfp_fl_output अणु
	काष्ठा nfp_fl_act_head head;
	__be16 flags;
	__be32 port;
पूर्ण;

काष्ठा nfp_fl_push_vlan अणु
	काष्ठा nfp_fl_act_head head;
	__be16 reserved;
	__be16 vlan_tpid;
	__be16 vlan_tci;
पूर्ण;

काष्ठा nfp_fl_pop_vlan अणु
	काष्ठा nfp_fl_act_head head;
	__be16 reserved;
पूर्ण;

काष्ठा nfp_fl_pre_lag अणु
	काष्ठा nfp_fl_act_head head;
	__be16 group_id;
	u8 lag_version[3];
	u8 instance;
पूर्ण;

#घोषणा NFP_FL_PRE_LAG_VER_OFF	8

काष्ठा nfp_fl_pre_tunnel अणु
	काष्ठा nfp_fl_act_head head;
	__be16 flags;
	जोड़ अणु
		__be32 ipv4_dst;
		काष्ठा in6_addr ipv6_dst;
	पूर्ण;
पूर्ण;

#घोषणा NFP_FL_PRE_TUN_IPV6	BIT(0)

काष्ठा nfp_fl_set_tun अणु
	काष्ठा nfp_fl_act_head head;
	__be16 reserved;
	__be64 tun_id __packed;
	__be32 tun_type_index;
	__be16 tun_flags;
	u8 ttl;
	u8 tos;
	__be16 outer_vlan_tpid;
	__be16 outer_vlan_tci;
	u8 tun_len;
	u8 res2;
	__be16 tun_proto;
पूर्ण;

काष्ठा nfp_fl_push_geneve अणु
	काष्ठा nfp_fl_act_head head;
	__be16 reserved;
	__be16 class;
	u8 type;
	u8 length;
	u8 opt_data[];
पूर्ण;

काष्ठा nfp_fl_push_mpls अणु
	काष्ठा nfp_fl_act_head head;
	__be16 ethtype;
	__be32 lse;
पूर्ण;

काष्ठा nfp_fl_pop_mpls अणु
	काष्ठा nfp_fl_act_head head;
	__be16 ethtype;
पूर्ण;

काष्ठा nfp_fl_set_mpls अणु
	काष्ठा nfp_fl_act_head head;
	__be16 reserved;
	__be32 lse_mask;
	__be32 lse;
पूर्ण;

/* Metadata with L2 (1W/4B)
 * ----------------------------------------------------------------
 *    3                   2                   1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |    key_type   |    mask_id    | PCP |p|   vlan outermost VID  |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *                                 ^                               ^
 *                           NOTE: |             TCI               |
 *                                 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */
काष्ठा nfp_flower_meta_tci अणु
	u8 nfp_flow_key_layer;
	u8 mask_id;
	__be16 tci;
पूर्ण;

/* Extended metadata क्रम additional key_layers (1W/4B)
 * ----------------------------------------------------------------
 *    3                   2                   1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                      nfp_flow_key_layer2                      |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */
काष्ठा nfp_flower_ext_meta अणु
	__be32 nfp_flow_key_layer2;
पूर्ण;

/* Port details (1W/4B)
 * ----------------------------------------------------------------
 *    3                   2                   1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                         port_ingress                          |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */
काष्ठा nfp_flower_in_port अणु
	__be32 in_port;
पूर्ण;

/* L2 details (4W/16B)
 *    3                   2                   1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                     mac_addr_dst, 31 - 0                      |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |      mac_addr_dst, 47 - 32    |     mac_addr_src, 15 - 0      |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                     mac_addr_src, 47 - 16                     |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |       mpls outermost label            |  TC |B|   reserved  |q|
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */
काष्ठा nfp_flower_mac_mpls अणु
	u8 mac_dst[6];
	u8 mac_src[6];
	__be32 mpls_lse;
पूर्ण;

/* VLAN details (2W/8B)
 *    3                   2                   1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |           outer_tpid          |           outer_tci           |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |           inner_tpid          |           inner_tci           |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */
काष्ठा nfp_flower_vlan अणु
	__be16 outer_tpid;
	__be16 outer_tci;
	__be16 inner_tpid;
	__be16 inner_tci;
पूर्ण;

/* L4 ports (क्रम UDP, TCP, SCTP) (1W/4B)
 *    3                   2                   1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |            port_src           |           port_dst            |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */
काष्ठा nfp_flower_tp_ports अणु
	__be16 port_src;
	__be16 port_dst;
पूर्ण;

काष्ठा nfp_flower_ip_ext अणु
	u8 tos;
	u8 proto;
	u8 ttl;
	u8 flags;
पूर्ण;

/* L3 IPv4 details (3W/12B)
 *    3                   2                   1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |    DSCP   |ECN|   protocol    |      ttl      |     flags     |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                        ipv4_addr_src                          |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                        ipv4_addr_dst                          |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */
काष्ठा nfp_flower_ipv4 अणु
	काष्ठा nfp_flower_ip_ext ip_ext;
	__be32 ipv4_src;
	__be32 ipv4_dst;
पूर्ण;

/* L3 IPv6 details (10W/40B)
 *    3                   2                   1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |    DSCP   |ECN|   protocol    |      ttl      |     flags     |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |   ipv6_exthdr   | res |            ipv6_flow_label            |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                  ipv6_addr_src,   31 - 0                      |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                  ipv6_addr_src,  63 - 32                      |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                  ipv6_addr_src,  95 - 64                      |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                  ipv6_addr_src, 127 - 96                      |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                  ipv6_addr_dst,   31 - 0                      |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                  ipv6_addr_dst,  63 - 32                      |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                  ipv6_addr_dst,  95 - 64                      |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                  ipv6_addr_dst, 127 - 96                      |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */
काष्ठा nfp_flower_ipv6 अणु
	काष्ठा nfp_flower_ip_ext ip_ext;
	__be32 ipv6_flow_label_exthdr;
	काष्ठा in6_addr ipv6_src;
	काष्ठा in6_addr ipv6_dst;
पूर्ण;

काष्ठा nfp_flower_tun_ipv4 अणु
	__be32 src;
	__be32 dst;
पूर्ण;

काष्ठा nfp_flower_tun_ipv6 अणु
	काष्ठा in6_addr src;
	काष्ठा in6_addr dst;
पूर्ण;

काष्ठा nfp_flower_tun_ip_ext अणु
	u8 tos;
	u8 ttl;
पूर्ण;

/* Flow Frame IPv4 UDP TUNNEL --> Tunnel details (4W/16B)
 * -----------------------------------------------------------------
 *    3                   2                   1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                         ipv4_addr_src                         |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                         ipv4_addr_dst                         |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |           Reserved            |      tos      |      ttl      |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                            Reserved                           |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                     VNI                       |   Reserved    |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */
काष्ठा nfp_flower_ipv4_udp_tun अणु
	काष्ठा nfp_flower_tun_ipv4 ipv4;
	__be16 reserved1;
	काष्ठा nfp_flower_tun_ip_ext ip_ext;
	__be32 reserved2;
	__be32 tun_id;
पूर्ण;

/* Flow Frame IPv6 UDP TUNNEL --> Tunnel details (11W/44B)
 * -----------------------------------------------------------------
 *    3                   2                   1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                  ipv6_addr_src,   31 - 0                      |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                  ipv6_addr_src,  63 - 32                      |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                  ipv6_addr_src,  95 - 64                      |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                  ipv6_addr_src, 127 - 96                      |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                  ipv6_addr_dst,   31 - 0                      |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                  ipv6_addr_dst,  63 - 32                      |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                  ipv6_addr_dst,  95 - 64                      |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                  ipv6_addr_dst, 127 - 96                      |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |           Reserved            |      tos      |      ttl      |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                            Reserved                           |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                     VNI                       |   Reserved    |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */
काष्ठा nfp_flower_ipv6_udp_tun अणु
	काष्ठा nfp_flower_tun_ipv6 ipv6;
	__be16 reserved1;
	काष्ठा nfp_flower_tun_ip_ext ip_ext;
	__be32 reserved2;
	__be32 tun_id;
पूर्ण;

/* Flow Frame GRE TUNNEL --> Tunnel details (6W/24B)
 * -----------------------------------------------------------------
 *    3                   2                   1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                         ipv4_addr_src                         |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                         ipv4_addr_dst                         |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |           tun_flags           |       tos     |       ttl     |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |            Reserved           |           Ethertype           |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                              Key                              |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                           Reserved                            |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */

काष्ठा nfp_flower_ipv4_gre_tun अणु
	काष्ठा nfp_flower_tun_ipv4 ipv4;
	__be16 tun_flags;
	काष्ठा nfp_flower_tun_ip_ext ip_ext;
	__be16 reserved1;
	__be16 ethertype;
	__be32 tun_key;
	__be32 reserved2;
पूर्ण;

/* Flow Frame GRE TUNNEL V6 --> Tunnel details (12W/48B)
 * -----------------------------------------------------------------
 *    3                   2                   1
 *  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                  ipv6_addr_src,   31 - 0                      |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                  ipv6_addr_src,  63 - 32                      |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                  ipv6_addr_src,  95 - 64                      |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                  ipv6_addr_src, 127 - 96                      |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                  ipv6_addr_dst,   31 - 0                      |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                  ipv6_addr_dst,  63 - 32                      |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                  ipv6_addr_dst,  95 - 64                      |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                  ipv6_addr_dst, 127 - 96                      |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |           tun_flags           |       tos     |       ttl     |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |            Reserved           |           Ethertype           |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                              Key                              |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                           Reserved                            |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */
काष्ठा nfp_flower_ipv6_gre_tun अणु
	काष्ठा nfp_flower_tun_ipv6 ipv6;
	__be16 tun_flags;
	काष्ठा nfp_flower_tun_ip_ext ip_ext;
	__be16 reserved1;
	__be16 ethertype;
	__be32 tun_key;
	__be32 reserved2;
पूर्ण;

काष्ठा nfp_flower_geneve_options अणु
	u8 data[NFP_FL_MAX_GENEVE_OPT_KEY];
पूर्ण;

#घोषणा NFP_FL_TUN_VNI_OFFSET 8

/* The base header क्रम a control message packet.
 * Defines an 8-bit version, and an 8-bit type, padded
 * to a 32-bit word. Rest of the packet is type-specअगरic.
 */
काष्ठा nfp_flower_cmsg_hdr अणु
	__be16 pad;
	u8 type;
	u8 version;
पूर्ण;

#घोषणा NFP_FLOWER_CMSG_HLEN		माप(काष्ठा nfp_flower_cmsg_hdr)
#घोषणा NFP_FLOWER_CMSG_VER1		1

/* Types defined क्रम port related control messages  */
क्रमागत nfp_flower_cmsg_type_port अणु
	NFP_FLOWER_CMSG_TYPE_FLOW_ADD =		0,
	NFP_FLOWER_CMSG_TYPE_FLOW_MOD =		1,
	NFP_FLOWER_CMSG_TYPE_FLOW_DEL =		2,
	NFP_FLOWER_CMSG_TYPE_LAG_CONFIG =	4,
	NFP_FLOWER_CMSG_TYPE_PORT_REIFY =	6,
	NFP_FLOWER_CMSG_TYPE_MAC_REPR =		7,
	NFP_FLOWER_CMSG_TYPE_PORT_MOD =		8,
	NFP_FLOWER_CMSG_TYPE_MERGE_HINT =	9,
	NFP_FLOWER_CMSG_TYPE_NO_NEIGH =		10,
	NFP_FLOWER_CMSG_TYPE_TUN_MAC =		11,
	NFP_FLOWER_CMSG_TYPE_ACTIVE_TUNS =	12,
	NFP_FLOWER_CMSG_TYPE_TUN_NEIGH =	13,
	NFP_FLOWER_CMSG_TYPE_TUN_IPS =		14,
	NFP_FLOWER_CMSG_TYPE_FLOW_STATS =	15,
	NFP_FLOWER_CMSG_TYPE_PORT_ECHO =	16,
	NFP_FLOWER_CMSG_TYPE_QOS_MOD =		18,
	NFP_FLOWER_CMSG_TYPE_QOS_DEL =		19,
	NFP_FLOWER_CMSG_TYPE_QOS_STATS =	20,
	NFP_FLOWER_CMSG_TYPE_PRE_TUN_RULE =	21,
	NFP_FLOWER_CMSG_TYPE_TUN_IPS_V6 =	22,
	NFP_FLOWER_CMSG_TYPE_NO_NEIGH_V6 =	23,
	NFP_FLOWER_CMSG_TYPE_TUN_NEIGH_V6 =	24,
	NFP_FLOWER_CMSG_TYPE_ACTIVE_TUNS_V6 =	25,
	NFP_FLOWER_CMSG_TYPE_MAX =		32,
पूर्ण;

/* NFP_FLOWER_CMSG_TYPE_MAC_REPR */
काष्ठा nfp_flower_cmsg_mac_repr अणु
	u8 reserved[3];
	u8 num_ports;
	काष्ठा अणु
		u8 idx;
		u8 info;
		u8 nbi_port;
		u8 phys_port;
	पूर्ण ports[];
पूर्ण;

#घोषणा NFP_FLOWER_CMSG_MAC_REPR_NBI		GENMASK(1, 0)

/* NFP_FLOWER_CMSG_TYPE_PORT_MOD */
काष्ठा nfp_flower_cmsg_porपंचांगod अणु
	__be32 portnum;
	u8 reserved;
	u8 info;
	__be16 mtu;
पूर्ण;

#घोषणा NFP_FLOWER_CMSG_PORTMOD_INFO_LINK	BIT(0)
#घोषणा NFP_FLOWER_CMSG_PORTMOD_MTU_CHANGE_ONLY	BIT(1)

/* NFP_FLOWER_CMSG_TYPE_PORT_REIFY */
काष्ठा nfp_flower_cmsg_portreअगरy अणु
	__be32 portnum;
	u16 reserved;
	__be16 info;
पूर्ण;

#घोषणा NFP_FLOWER_CMSG_PORTREIFY_INFO_EXIST	BIT(0)

/* NFP_FLOWER_CMSG_TYPE_FLOW_MERGE_HINT */
काष्ठा nfp_flower_cmsg_merge_hपूर्णांक अणु
	u8 reserved[3];
	u8 count;
	काष्ठा अणु
		__be32 host_ctx;
		__be64 host_cookie;
	पूर्ण __packed flow[];
पूर्ण;

क्रमागत nfp_flower_cmsg_port_type अणु
	NFP_FLOWER_CMSG_PORT_TYPE_UNSPEC =	0x0,
	NFP_FLOWER_CMSG_PORT_TYPE_PHYS_PORT =	0x1,
	NFP_FLOWER_CMSG_PORT_TYPE_PCIE_PORT =	0x2,
	NFP_FLOWER_CMSG_PORT_TYPE_OTHER_PORT =  0x3,
पूर्ण;

क्रमागत nfp_flower_cmsg_port_vnic_type अणु
	NFP_FLOWER_CMSG_PORT_VNIC_TYPE_VF =	0x0,
	NFP_FLOWER_CMSG_PORT_VNIC_TYPE_PF =	0x1,
	NFP_FLOWER_CMSG_PORT_VNIC_TYPE_CTRL =	0x2,
पूर्ण;

#घोषणा NFP_FLOWER_CMSG_PORT_TYPE		GENMASK(31, 28)
#घोषणा NFP_FLOWER_CMSG_PORT_SYS_ID		GENMASK(27, 24)
#घोषणा NFP_FLOWER_CMSG_PORT_NFP_ID		GENMASK(23, 22)
#घोषणा NFP_FLOWER_CMSG_PORT_PCI		GENMASK(15, 14)
#घोषणा NFP_FLOWER_CMSG_PORT_VNIC_TYPE		GENMASK(13, 12)
#घोषणा NFP_FLOWER_CMSG_PORT_VNIC		GENMASK(11, 6)
#घोषणा NFP_FLOWER_CMSG_PORT_PCIE_Q		GENMASK(5, 0)
#घोषणा NFP_FLOWER_CMSG_PORT_PHYS_PORT_NUM	GENMASK(7, 0)

अटल अंतरभूत u32 nfp_flower_पूर्णांकernal_port_get_port_id(u8 पूर्णांकernal_port)
अणु
	वापस FIELD_PREP(NFP_FLOWER_CMSG_PORT_PHYS_PORT_NUM, पूर्णांकernal_port) |
		FIELD_PREP(NFP_FLOWER_CMSG_PORT_TYPE,
			   NFP_FLOWER_CMSG_PORT_TYPE_OTHER_PORT);
पूर्ण

अटल अंतरभूत u32 nfp_flower_cmsg_phys_port(u8 phys_port)
अणु
	वापस FIELD_PREP(NFP_FLOWER_CMSG_PORT_PHYS_PORT_NUM, phys_port) |
		FIELD_PREP(NFP_FLOWER_CMSG_PORT_TYPE,
			   NFP_FLOWER_CMSG_PORT_TYPE_PHYS_PORT);
पूर्ण

अटल अंतरभूत u32
nfp_flower_cmsg_pcie_port(u8 nfp_pcie, क्रमागत nfp_flower_cmsg_port_vnic_type type,
			  u8 vnic, u8 q)
अणु
	वापस FIELD_PREP(NFP_FLOWER_CMSG_PORT_PCI, nfp_pcie) |
		FIELD_PREP(NFP_FLOWER_CMSG_PORT_VNIC_TYPE, type) |
		FIELD_PREP(NFP_FLOWER_CMSG_PORT_VNIC, vnic) |
		FIELD_PREP(NFP_FLOWER_CMSG_PORT_PCIE_Q, q) |
		FIELD_PREP(NFP_FLOWER_CMSG_PORT_TYPE,
			   NFP_FLOWER_CMSG_PORT_TYPE_PCIE_PORT);
पूर्ण

अटल अंतरभूत व्योम *nfp_flower_cmsg_get_data(काष्ठा sk_buff *skb)
अणु
	वापस (अचिन्हित अक्षर *)skb->data + NFP_FLOWER_CMSG_HLEN;
पूर्ण

अटल अंतरभूत पूर्णांक nfp_flower_cmsg_get_data_len(काष्ठा sk_buff *skb)
अणु
	वापस skb->len - NFP_FLOWER_CMSG_HLEN;
पूर्ण

अटल अंतरभूत bool
nfp_fl_netdev_is_tunnel_type(काष्ठा net_device *netdev,
			     क्रमागत nfp_flower_tun_type tun_type)
अणु
	अगर (netअगर_is_vxlan(netdev))
		वापस tun_type == NFP_FL_TUNNEL_VXLAN;
	अगर (netअगर_is_gretap(netdev))
		वापस tun_type == NFP_FL_TUNNEL_GRE;
	अगर (netअगर_is_geneve(netdev))
		वापस tun_type == NFP_FL_TUNNEL_GENEVE;

	वापस false;
पूर्ण

अटल अंतरभूत bool nfp_fl_is_netdev_to_offload(काष्ठा net_device *netdev)
अणु
	अगर (!netdev->rtnl_link_ops)
		वापस false;
	अगर (!म_भेद(netdev->rtnl_link_ops->kind, "openvswitch"))
		वापस true;
	अगर (netअगर_is_vxlan(netdev))
		वापस true;
	अगर (netअगर_is_geneve(netdev))
		वापस true;
	अगर (netअगर_is_gretap(netdev))
		वापस true;

	वापस false;
पूर्ण

काष्ठा sk_buff *
nfp_flower_cmsg_mac_repr_start(काष्ठा nfp_app *app, अचिन्हित पूर्णांक num_ports);
व्योम
nfp_flower_cmsg_mac_repr_add(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक idx,
			     अचिन्हित पूर्णांक nbi, अचिन्हित पूर्णांक nbi_port,
			     अचिन्हित पूर्णांक phys_port);
पूर्णांक nfp_flower_cmsg_porपंचांगod(काष्ठा nfp_repr *repr, bool carrier_ok,
			    अचिन्हित पूर्णांक mtu, bool mtu_only);
पूर्णांक nfp_flower_cmsg_portreअगरy(काष्ठा nfp_repr *repr, bool exists);
व्योम nfp_flower_cmsg_process_rx(काष्ठा work_काष्ठा *work);
व्योम nfp_flower_cmsg_rx(काष्ठा nfp_app *app, काष्ठा sk_buff *skb);
काष्ठा sk_buff *
nfp_flower_cmsg_alloc(काष्ठा nfp_app *app, अचिन्हित पूर्णांक size,
		      क्रमागत nfp_flower_cmsg_type_port type, gfp_t flag);

#पूर्ण_अगर
