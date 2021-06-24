<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 *	Linux ethernet bridge
 *
 *	Authors:
 *	Lennert Buytenhek		<buytenh@gnu.org>
 *
 *	This program is मुक्त software; you can redistribute it and/or
 *	modअगरy it under the terms of the GNU General Public License
 *	as published by the Free Software Foundation; either version
 *	2 of the License, or (at your option) any later version.
 */

#अगर_अघोषित _UAPI_LINUX_IF_BRIDGE_H
#घोषणा _UAPI_LINUX_IF_BRIDGE_H

#समावेश <linux/types.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/in6.h>

#घोषणा SYSFS_BRIDGE_ATTR	"bridge"
#घोषणा SYSFS_BRIDGE_FDB	"brforward"
#घोषणा SYSFS_BRIDGE_PORT_SUBसूची "brif"
#घोषणा SYSFS_BRIDGE_PORT_ATTR	"brport"
#घोषणा SYSFS_BRIDGE_PORT_LINK	"bridge"

#घोषणा BRCTL_VERSION 1

#घोषणा BRCTL_GET_VERSION 0
#घोषणा BRCTL_GET_BRIDGES 1
#घोषणा BRCTL_ADD_BRIDGE 2
#घोषणा BRCTL_DEL_BRIDGE 3
#घोषणा BRCTL_ADD_IF 4
#घोषणा BRCTL_DEL_IF 5
#घोषणा BRCTL_GET_BRIDGE_INFO 6
#घोषणा BRCTL_GET_PORT_LIST 7
#घोषणा BRCTL_SET_BRIDGE_FORWARD_DELAY 8
#घोषणा BRCTL_SET_BRIDGE_HELLO_TIME 9
#घोषणा BRCTL_SET_BRIDGE_MAX_AGE 10
#घोषणा BRCTL_SET_AGEING_TIME 11
#घोषणा BRCTL_SET_GC_INTERVAL 12
#घोषणा BRCTL_GET_PORT_INFO 13
#घोषणा BRCTL_SET_BRIDGE_STP_STATE 14
#घोषणा BRCTL_SET_BRIDGE_PRIORITY 15
#घोषणा BRCTL_SET_PORT_PRIORITY 16
#घोषणा BRCTL_SET_PATH_COST 17
#घोषणा BRCTL_GET_FDB_ENTRIES 18

#घोषणा BR_STATE_DISABLED 0
#घोषणा BR_STATE_LISTENING 1
#घोषणा BR_STATE_LEARNING 2
#घोषणा BR_STATE_FORWARDING 3
#घोषणा BR_STATE_BLOCKING 4

काष्ठा __bridge_info अणु
	__u64 designated_root;
	__u64 bridge_id;
	__u32 root_path_cost;
	__u32 max_age;
	__u32 hello_समय;
	__u32 क्रमward_delay;
	__u32 bridge_max_age;
	__u32 bridge_hello_समय;
	__u32 bridge_क्रमward_delay;
	__u8 topology_change;
	__u8 topology_change_detected;
	__u8 root_port;
	__u8 stp_enabled;
	__u32 ageing_समय;
	__u32 gc_पूर्णांकerval;
	__u32 hello_समयr_value;
	__u32 tcn_समयr_value;
	__u32 topology_change_समयr_value;
	__u32 gc_समयr_value;
पूर्ण;

काष्ठा __port_info अणु
	__u64 designated_root;
	__u64 designated_bridge;
	__u16 port_id;
	__u16 designated_port;
	__u32 path_cost;
	__u32 designated_cost;
	__u8 state;
	__u8 top_change_ack;
	__u8 config_pending;
	__u8 unused0;
	__u32 message_age_समयr_value;
	__u32 क्रमward_delay_समयr_value;
	__u32 hold_समयr_value;
पूर्ण;

काष्ठा __fdb_entry अणु
	__u8 mac_addr[ETH_ALEN];
	__u8 port_no;
	__u8 is_local;
	__u32 ageing_समयr_value;
	__u8 port_hi;
	__u8 pad0;
	__u16 unused;
पूर्ण;

/* Bridge Flags */
#घोषणा BRIDGE_FLAGS_MASTER	1	/* Bridge command to/from master */
#घोषणा BRIDGE_FLAGS_SELF	2	/* Bridge command to/from lowerdev */

#घोषणा BRIDGE_MODE_VEB		0	/* Default loopback mode */
#घोषणा BRIDGE_MODE_VEPA	1	/* 802.1Qbg defined VEPA mode */
#घोषणा BRIDGE_MODE_UNDEF	0xFFFF  /* mode undefined */

/* Bridge management nested attributes
 * [IFLA_AF_SPEC] = अणु
 *     [IFLA_BRIDGE_FLAGS]
 *     [IFLA_BRIDGE_MODE]
 *     [IFLA_BRIDGE_VLAN_INFO]
 * पूर्ण
 */
क्रमागत अणु
	IFLA_BRIDGE_FLAGS,
	IFLA_BRIDGE_MODE,
	IFLA_BRIDGE_VLAN_INFO,
	IFLA_BRIDGE_VLAN_TUNNEL_INFO,
	IFLA_BRIDGE_MRP,
	IFLA_BRIDGE_CFM,
	__IFLA_BRIDGE_MAX,
पूर्ण;
#घोषणा IFLA_BRIDGE_MAX (__IFLA_BRIDGE_MAX - 1)

#घोषणा BRIDGE_VLAN_INFO_MASTER	(1<<0)	/* Operate on Bridge device as well */
#घोषणा BRIDGE_VLAN_INFO_PVID	(1<<1)	/* VLAN is PVID, ingress untagged */
#घोषणा BRIDGE_VLAN_INFO_UNTAGGED	(1<<2)	/* VLAN egresses untagged */
#घोषणा BRIDGE_VLAN_INFO_RANGE_BEGIN	(1<<3) /* VLAN is start of vlan range */
#घोषणा BRIDGE_VLAN_INFO_RANGE_END	(1<<4) /* VLAN is end of vlan range */
#घोषणा BRIDGE_VLAN_INFO_BRENTRY	(1<<5) /* Global bridge VLAN entry */
#घोषणा BRIDGE_VLAN_INFO_ONLY_OPTS	(1<<6) /* Skip create/delete/flags */

काष्ठा bridge_vlan_info अणु
	__u16 flags;
	__u16 vid;
पूर्ण;

क्रमागत अणु
	IFLA_BRIDGE_VLAN_TUNNEL_UNSPEC,
	IFLA_BRIDGE_VLAN_TUNNEL_ID,
	IFLA_BRIDGE_VLAN_TUNNEL_VID,
	IFLA_BRIDGE_VLAN_TUNNEL_FLAGS,
	__IFLA_BRIDGE_VLAN_TUNNEL_MAX,
पूर्ण;

#घोषणा IFLA_BRIDGE_VLAN_TUNNEL_MAX (__IFLA_BRIDGE_VLAN_TUNNEL_MAX - 1)

काष्ठा bridge_vlan_xstats अणु
	__u64 rx_bytes;
	__u64 rx_packets;
	__u64 tx_bytes;
	__u64 tx_packets;
	__u16 vid;
	__u16 flags;
	__u32 pad2;
पूर्ण;

क्रमागत अणु
	IFLA_BRIDGE_MRP_UNSPEC,
	IFLA_BRIDGE_MRP_INSTANCE,
	IFLA_BRIDGE_MRP_PORT_STATE,
	IFLA_BRIDGE_MRP_PORT_ROLE,
	IFLA_BRIDGE_MRP_RING_STATE,
	IFLA_BRIDGE_MRP_RING_ROLE,
	IFLA_BRIDGE_MRP_START_TEST,
	IFLA_BRIDGE_MRP_INFO,
	IFLA_BRIDGE_MRP_IN_ROLE,
	IFLA_BRIDGE_MRP_IN_STATE,
	IFLA_BRIDGE_MRP_START_IN_TEST,
	__IFLA_BRIDGE_MRP_MAX,
पूर्ण;

#घोषणा IFLA_BRIDGE_MRP_MAX (__IFLA_BRIDGE_MRP_MAX - 1)

क्रमागत अणु
	IFLA_BRIDGE_MRP_INSTANCE_UNSPEC,
	IFLA_BRIDGE_MRP_INSTANCE_RING_ID,
	IFLA_BRIDGE_MRP_INSTANCE_P_IFINDEX,
	IFLA_BRIDGE_MRP_INSTANCE_S_IFINDEX,
	IFLA_BRIDGE_MRP_INSTANCE_PRIO,
	__IFLA_BRIDGE_MRP_INSTANCE_MAX,
पूर्ण;

#घोषणा IFLA_BRIDGE_MRP_INSTANCE_MAX (__IFLA_BRIDGE_MRP_INSTANCE_MAX - 1)

क्रमागत अणु
	IFLA_BRIDGE_MRP_PORT_STATE_UNSPEC,
	IFLA_BRIDGE_MRP_PORT_STATE_STATE,
	__IFLA_BRIDGE_MRP_PORT_STATE_MAX,
पूर्ण;

#घोषणा IFLA_BRIDGE_MRP_PORT_STATE_MAX (__IFLA_BRIDGE_MRP_PORT_STATE_MAX - 1)

क्रमागत अणु
	IFLA_BRIDGE_MRP_PORT_ROLE_UNSPEC,
	IFLA_BRIDGE_MRP_PORT_ROLE_ROLE,
	__IFLA_BRIDGE_MRP_PORT_ROLE_MAX,
पूर्ण;

#घोषणा IFLA_BRIDGE_MRP_PORT_ROLE_MAX (__IFLA_BRIDGE_MRP_PORT_ROLE_MAX - 1)

क्रमागत अणु
	IFLA_BRIDGE_MRP_RING_STATE_UNSPEC,
	IFLA_BRIDGE_MRP_RING_STATE_RING_ID,
	IFLA_BRIDGE_MRP_RING_STATE_STATE,
	__IFLA_BRIDGE_MRP_RING_STATE_MAX,
पूर्ण;

#घोषणा IFLA_BRIDGE_MRP_RING_STATE_MAX (__IFLA_BRIDGE_MRP_RING_STATE_MAX - 1)

क्रमागत अणु
	IFLA_BRIDGE_MRP_RING_ROLE_UNSPEC,
	IFLA_BRIDGE_MRP_RING_ROLE_RING_ID,
	IFLA_BRIDGE_MRP_RING_ROLE_ROLE,
	__IFLA_BRIDGE_MRP_RING_ROLE_MAX,
पूर्ण;

#घोषणा IFLA_BRIDGE_MRP_RING_ROLE_MAX (__IFLA_BRIDGE_MRP_RING_ROLE_MAX - 1)

क्रमागत अणु
	IFLA_BRIDGE_MRP_START_TEST_UNSPEC,
	IFLA_BRIDGE_MRP_START_TEST_RING_ID,
	IFLA_BRIDGE_MRP_START_TEST_INTERVAL,
	IFLA_BRIDGE_MRP_START_TEST_MAX_MISS,
	IFLA_BRIDGE_MRP_START_TEST_PERIOD,
	IFLA_BRIDGE_MRP_START_TEST_MONITOR,
	__IFLA_BRIDGE_MRP_START_TEST_MAX,
पूर्ण;

#घोषणा IFLA_BRIDGE_MRP_START_TEST_MAX (__IFLA_BRIDGE_MRP_START_TEST_MAX - 1)

क्रमागत अणु
	IFLA_BRIDGE_MRP_INFO_UNSPEC,
	IFLA_BRIDGE_MRP_INFO_RING_ID,
	IFLA_BRIDGE_MRP_INFO_P_IFINDEX,
	IFLA_BRIDGE_MRP_INFO_S_IFINDEX,
	IFLA_BRIDGE_MRP_INFO_PRIO,
	IFLA_BRIDGE_MRP_INFO_RING_STATE,
	IFLA_BRIDGE_MRP_INFO_RING_ROLE,
	IFLA_BRIDGE_MRP_INFO_TEST_INTERVAL,
	IFLA_BRIDGE_MRP_INFO_TEST_MAX_MISS,
	IFLA_BRIDGE_MRP_INFO_TEST_MONITOR,
	IFLA_BRIDGE_MRP_INFO_I_IFINDEX,
	IFLA_BRIDGE_MRP_INFO_IN_STATE,
	IFLA_BRIDGE_MRP_INFO_IN_ROLE,
	IFLA_BRIDGE_MRP_INFO_IN_TEST_INTERVAL,
	IFLA_BRIDGE_MRP_INFO_IN_TEST_MAX_MISS,
	__IFLA_BRIDGE_MRP_INFO_MAX,
पूर्ण;

#घोषणा IFLA_BRIDGE_MRP_INFO_MAX (__IFLA_BRIDGE_MRP_INFO_MAX - 1)

क्रमागत अणु
	IFLA_BRIDGE_MRP_IN_STATE_UNSPEC,
	IFLA_BRIDGE_MRP_IN_STATE_IN_ID,
	IFLA_BRIDGE_MRP_IN_STATE_STATE,
	__IFLA_BRIDGE_MRP_IN_STATE_MAX,
पूर्ण;

#घोषणा IFLA_BRIDGE_MRP_IN_STATE_MAX (__IFLA_BRIDGE_MRP_IN_STATE_MAX - 1)

क्रमागत अणु
	IFLA_BRIDGE_MRP_IN_ROLE_UNSPEC,
	IFLA_BRIDGE_MRP_IN_ROLE_RING_ID,
	IFLA_BRIDGE_MRP_IN_ROLE_IN_ID,
	IFLA_BRIDGE_MRP_IN_ROLE_ROLE,
	IFLA_BRIDGE_MRP_IN_ROLE_I_IFINDEX,
	__IFLA_BRIDGE_MRP_IN_ROLE_MAX,
पूर्ण;

#घोषणा IFLA_BRIDGE_MRP_IN_ROLE_MAX (__IFLA_BRIDGE_MRP_IN_ROLE_MAX - 1)

क्रमागत अणु
	IFLA_BRIDGE_MRP_START_IN_TEST_UNSPEC,
	IFLA_BRIDGE_MRP_START_IN_TEST_IN_ID,
	IFLA_BRIDGE_MRP_START_IN_TEST_INTERVAL,
	IFLA_BRIDGE_MRP_START_IN_TEST_MAX_MISS,
	IFLA_BRIDGE_MRP_START_IN_TEST_PERIOD,
	__IFLA_BRIDGE_MRP_START_IN_TEST_MAX,
पूर्ण;

#घोषणा IFLA_BRIDGE_MRP_START_IN_TEST_MAX (__IFLA_BRIDGE_MRP_START_IN_TEST_MAX - 1)

काष्ठा br_mrp_instance अणु
	__u32 ring_id;
	__u32 p_अगरindex;
	__u32 s_अगरindex;
	__u16 prio;
पूर्ण;

काष्ठा br_mrp_ring_state अणु
	__u32 ring_id;
	__u32 ring_state;
पूर्ण;

काष्ठा br_mrp_ring_role अणु
	__u32 ring_id;
	__u32 ring_role;
पूर्ण;

काष्ठा br_mrp_start_test अणु
	__u32 ring_id;
	__u32 पूर्णांकerval;
	__u32 max_miss;
	__u32 period;
	__u32 monitor;
पूर्ण;

काष्ठा br_mrp_in_state अणु
	__u32 in_state;
	__u16 in_id;
पूर्ण;

काष्ठा br_mrp_in_role अणु
	__u32 ring_id;
	__u32 in_role;
	__u32 i_अगरindex;
	__u16 in_id;
पूर्ण;

काष्ठा br_mrp_start_in_test अणु
	__u32 पूर्णांकerval;
	__u32 max_miss;
	__u32 period;
	__u16 in_id;
पूर्ण;

क्रमागत अणु
	IFLA_BRIDGE_CFM_UNSPEC,
	IFLA_BRIDGE_CFM_MEP_CREATE,
	IFLA_BRIDGE_CFM_MEP_DELETE,
	IFLA_BRIDGE_CFM_MEP_CONFIG,
	IFLA_BRIDGE_CFM_CC_CONFIG,
	IFLA_BRIDGE_CFM_CC_PEER_MEP_ADD,
	IFLA_BRIDGE_CFM_CC_PEER_MEP_REMOVE,
	IFLA_BRIDGE_CFM_CC_RDI,
	IFLA_BRIDGE_CFM_CC_CCM_TX,
	IFLA_BRIDGE_CFM_MEP_CREATE_INFO,
	IFLA_BRIDGE_CFM_MEP_CONFIG_INFO,
	IFLA_BRIDGE_CFM_CC_CONFIG_INFO,
	IFLA_BRIDGE_CFM_CC_RDI_INFO,
	IFLA_BRIDGE_CFM_CC_CCM_TX_INFO,
	IFLA_BRIDGE_CFM_CC_PEER_MEP_INFO,
	IFLA_BRIDGE_CFM_MEP_STATUS_INFO,
	IFLA_BRIDGE_CFM_CC_PEER_STATUS_INFO,
	__IFLA_BRIDGE_CFM_MAX,
पूर्ण;

#घोषणा IFLA_BRIDGE_CFM_MAX (__IFLA_BRIDGE_CFM_MAX - 1)

क्रमागत अणु
	IFLA_BRIDGE_CFM_MEP_CREATE_UNSPEC,
	IFLA_BRIDGE_CFM_MEP_CREATE_INSTANCE,
	IFLA_BRIDGE_CFM_MEP_CREATE_DOMAIN,
	IFLA_BRIDGE_CFM_MEP_CREATE_सूचीECTION,
	IFLA_BRIDGE_CFM_MEP_CREATE_IFINDEX,
	__IFLA_BRIDGE_CFM_MEP_CREATE_MAX,
पूर्ण;

#घोषणा IFLA_BRIDGE_CFM_MEP_CREATE_MAX (__IFLA_BRIDGE_CFM_MEP_CREATE_MAX - 1)

क्रमागत अणु
	IFLA_BRIDGE_CFM_MEP_DELETE_UNSPEC,
	IFLA_BRIDGE_CFM_MEP_DELETE_INSTANCE,
	__IFLA_BRIDGE_CFM_MEP_DELETE_MAX,
पूर्ण;

#घोषणा IFLA_BRIDGE_CFM_MEP_DELETE_MAX (__IFLA_BRIDGE_CFM_MEP_DELETE_MAX - 1)

क्रमागत अणु
	IFLA_BRIDGE_CFM_MEP_CONFIG_UNSPEC,
	IFLA_BRIDGE_CFM_MEP_CONFIG_INSTANCE,
	IFLA_BRIDGE_CFM_MEP_CONFIG_UNICAST_MAC,
	IFLA_BRIDGE_CFM_MEP_CONFIG_MDLEVEL,
	IFLA_BRIDGE_CFM_MEP_CONFIG_MEPID,
	__IFLA_BRIDGE_CFM_MEP_CONFIG_MAX,
पूर्ण;

#घोषणा IFLA_BRIDGE_CFM_MEP_CONFIG_MAX (__IFLA_BRIDGE_CFM_MEP_CONFIG_MAX - 1)

क्रमागत अणु
	IFLA_BRIDGE_CFM_CC_CONFIG_UNSPEC,
	IFLA_BRIDGE_CFM_CC_CONFIG_INSTANCE,
	IFLA_BRIDGE_CFM_CC_CONFIG_ENABLE,
	IFLA_BRIDGE_CFM_CC_CONFIG_EXP_INTERVAL,
	IFLA_BRIDGE_CFM_CC_CONFIG_EXP_MAID,
	__IFLA_BRIDGE_CFM_CC_CONFIG_MAX,
पूर्ण;

#घोषणा IFLA_BRIDGE_CFM_CC_CONFIG_MAX (__IFLA_BRIDGE_CFM_CC_CONFIG_MAX - 1)

क्रमागत अणु
	IFLA_BRIDGE_CFM_CC_PEER_MEP_UNSPEC,
	IFLA_BRIDGE_CFM_CC_PEER_MEP_INSTANCE,
	IFLA_BRIDGE_CFM_CC_PEER_MEPID,
	__IFLA_BRIDGE_CFM_CC_PEER_MEP_MAX,
पूर्ण;

#घोषणा IFLA_BRIDGE_CFM_CC_PEER_MEP_MAX (__IFLA_BRIDGE_CFM_CC_PEER_MEP_MAX - 1)

क्रमागत अणु
	IFLA_BRIDGE_CFM_CC_RDI_UNSPEC,
	IFLA_BRIDGE_CFM_CC_RDI_INSTANCE,
	IFLA_BRIDGE_CFM_CC_RDI_RDI,
	__IFLA_BRIDGE_CFM_CC_RDI_MAX,
पूर्ण;

#घोषणा IFLA_BRIDGE_CFM_CC_RDI_MAX (__IFLA_BRIDGE_CFM_CC_RDI_MAX - 1)

क्रमागत अणु
	IFLA_BRIDGE_CFM_CC_CCM_TX_UNSPEC,
	IFLA_BRIDGE_CFM_CC_CCM_TX_INSTANCE,
	IFLA_BRIDGE_CFM_CC_CCM_TX_DMAC,
	IFLA_BRIDGE_CFM_CC_CCM_TX_SEQ_NO_UPDATE,
	IFLA_BRIDGE_CFM_CC_CCM_TX_PERIOD,
	IFLA_BRIDGE_CFM_CC_CCM_TX_IF_TLV,
	IFLA_BRIDGE_CFM_CC_CCM_TX_IF_TLV_VALUE,
	IFLA_BRIDGE_CFM_CC_CCM_TX_PORT_TLV,
	IFLA_BRIDGE_CFM_CC_CCM_TX_PORT_TLV_VALUE,
	__IFLA_BRIDGE_CFM_CC_CCM_TX_MAX,
पूर्ण;

#घोषणा IFLA_BRIDGE_CFM_CC_CCM_TX_MAX (__IFLA_BRIDGE_CFM_CC_CCM_TX_MAX - 1)

क्रमागत अणु
	IFLA_BRIDGE_CFM_MEP_STATUS_UNSPEC,
	IFLA_BRIDGE_CFM_MEP_STATUS_INSTANCE,
	IFLA_BRIDGE_CFM_MEP_STATUS_OPCODE_UNEXP_SEEN,
	IFLA_BRIDGE_CFM_MEP_STATUS_VERSION_UNEXP_SEEN,
	IFLA_BRIDGE_CFM_MEP_STATUS_RX_LEVEL_LOW_SEEN,
	__IFLA_BRIDGE_CFM_MEP_STATUS_MAX,
पूर्ण;

#घोषणा IFLA_BRIDGE_CFM_MEP_STATUS_MAX (__IFLA_BRIDGE_CFM_MEP_STATUS_MAX - 1)

क्रमागत अणु
	IFLA_BRIDGE_CFM_CC_PEER_STATUS_UNSPEC,
	IFLA_BRIDGE_CFM_CC_PEER_STATUS_INSTANCE,
	IFLA_BRIDGE_CFM_CC_PEER_STATUS_PEER_MEPID,
	IFLA_BRIDGE_CFM_CC_PEER_STATUS_CCM_DEFECT,
	IFLA_BRIDGE_CFM_CC_PEER_STATUS_RDI,
	IFLA_BRIDGE_CFM_CC_PEER_STATUS_PORT_TLV_VALUE,
	IFLA_BRIDGE_CFM_CC_PEER_STATUS_IF_TLV_VALUE,
	IFLA_BRIDGE_CFM_CC_PEER_STATUS_SEEN,
	IFLA_BRIDGE_CFM_CC_PEER_STATUS_TLV_SEEN,
	IFLA_BRIDGE_CFM_CC_PEER_STATUS_SEQ_UNEXP_SEEN,
	__IFLA_BRIDGE_CFM_CC_PEER_STATUS_MAX,
पूर्ण;

#घोषणा IFLA_BRIDGE_CFM_CC_PEER_STATUS_MAX (__IFLA_BRIDGE_CFM_CC_PEER_STATUS_MAX - 1)

काष्ठा bridge_stp_xstats अणु
	__u64 transition_blk;
	__u64 transition_fwd;
	__u64 rx_bpdu;
	__u64 tx_bpdu;
	__u64 rx_tcn;
	__u64 tx_tcn;
पूर्ण;

/* Bridge vlan RTM header */
काष्ठा br_vlan_msg अणु
	__u8 family;
	__u8 reserved1;
	__u16 reserved2;
	__u32 अगरindex;
पूर्ण;

क्रमागत अणु
	BRIDGE_VLANDB_DUMP_UNSPEC,
	BRIDGE_VLANDB_DUMP_FLAGS,
	__BRIDGE_VLANDB_DUMP_MAX,
पूर्ण;
#घोषणा BRIDGE_VLANDB_DUMP_MAX (__BRIDGE_VLANDB_DUMP_MAX - 1)

/* flags used in BRIDGE_VLANDB_DUMP_FLAGS attribute to affect dumps */
#घोषणा BRIDGE_VLANDB_DUMPF_STATS	(1 << 0) /* Include stats in the dump */

/* Bridge vlan RTM attributes
 * [BRIDGE_VLANDB_ENTRY] = अणु
 *     [BRIDGE_VLANDB_ENTRY_INFO]
 *     ...
 * पूर्ण
 */
क्रमागत अणु
	BRIDGE_VLANDB_UNSPEC,
	BRIDGE_VLANDB_ENTRY,
	__BRIDGE_VLANDB_MAX,
पूर्ण;
#घोषणा BRIDGE_VLANDB_MAX (__BRIDGE_VLANDB_MAX - 1)

क्रमागत अणु
	BRIDGE_VLANDB_ENTRY_UNSPEC,
	BRIDGE_VLANDB_ENTRY_INFO,
	BRIDGE_VLANDB_ENTRY_RANGE,
	BRIDGE_VLANDB_ENTRY_STATE,
	BRIDGE_VLANDB_ENTRY_TUNNEL_INFO,
	BRIDGE_VLANDB_ENTRY_STATS,
	__BRIDGE_VLANDB_ENTRY_MAX,
पूर्ण;
#घोषणा BRIDGE_VLANDB_ENTRY_MAX (__BRIDGE_VLANDB_ENTRY_MAX - 1)

/* [BRIDGE_VLANDB_ENTRY] = अणु
 *     [BRIDGE_VLANDB_ENTRY_TUNNEL_INFO] = अणु
 *         [BRIDGE_VLANDB_TINFO_ID]
 *         ...
 *     पूर्ण
 * पूर्ण
 */
क्रमागत अणु
	BRIDGE_VLANDB_TINFO_UNSPEC,
	BRIDGE_VLANDB_TINFO_ID,
	BRIDGE_VLANDB_TINFO_CMD,
	__BRIDGE_VLANDB_TINFO_MAX,
पूर्ण;
#घोषणा BRIDGE_VLANDB_TINFO_MAX (__BRIDGE_VLANDB_TINFO_MAX - 1)

/* [BRIDGE_VLANDB_ENTRY] = अणु
 *     [BRIDGE_VLANDB_ENTRY_STATS] = अणु
 *         [BRIDGE_VLANDB_STATS_RX_BYTES]
 *         ...
 *     पूर्ण
 *     ...
 * पूर्ण
 */
क्रमागत अणु
	BRIDGE_VLANDB_STATS_UNSPEC,
	BRIDGE_VLANDB_STATS_RX_BYTES,
	BRIDGE_VLANDB_STATS_RX_PACKETS,
	BRIDGE_VLANDB_STATS_TX_BYTES,
	BRIDGE_VLANDB_STATS_TX_PACKETS,
	BRIDGE_VLANDB_STATS_PAD,
	__BRIDGE_VLANDB_STATS_MAX,
पूर्ण;
#घोषणा BRIDGE_VLANDB_STATS_MAX (__BRIDGE_VLANDB_STATS_MAX - 1)

/* Bridge multicast database attributes
 * [MDBA_MDB] = अणु
 *     [MDBA_MDB_ENTRY] = अणु
 *         [MDBA_MDB_ENTRY_INFO] अणु
 *		काष्ठा br_mdb_entry
 *		[MDBA_MDB_EATTR attributes]
 *         पूर्ण
 *     पूर्ण
 * पूर्ण
 * [MDBA_ROUTER] = अणु
 *    [MDBA_ROUTER_PORT] = अणु
 *        u32 अगरindex
 *        [MDBA_ROUTER_PATTR attributes]
 *    पूर्ण
 * पूर्ण
 */
क्रमागत अणु
	MDBA_UNSPEC,
	MDBA_MDB,
	MDBA_ROUTER,
	__MDBA_MAX,
पूर्ण;
#घोषणा MDBA_MAX (__MDBA_MAX - 1)

क्रमागत अणु
	MDBA_MDB_UNSPEC,
	MDBA_MDB_ENTRY,
	__MDBA_MDB_MAX,
पूर्ण;
#घोषणा MDBA_MDB_MAX (__MDBA_MDB_MAX - 1)

क्रमागत अणु
	MDBA_MDB_ENTRY_UNSPEC,
	MDBA_MDB_ENTRY_INFO,
	__MDBA_MDB_ENTRY_MAX,
पूर्ण;
#घोषणा MDBA_MDB_ENTRY_MAX (__MDBA_MDB_ENTRY_MAX - 1)

/* per mdb entry additional attributes */
क्रमागत अणु
	MDBA_MDB_EATTR_UNSPEC,
	MDBA_MDB_EATTR_TIMER,
	MDBA_MDB_EATTR_SRC_LIST,
	MDBA_MDB_EATTR_GROUP_MODE,
	MDBA_MDB_EATTR_SOURCE,
	MDBA_MDB_EATTR_RTPROT,
	__MDBA_MDB_EATTR_MAX
पूर्ण;
#घोषणा MDBA_MDB_EATTR_MAX (__MDBA_MDB_EATTR_MAX - 1)

/* per mdb entry source */
क्रमागत अणु
	MDBA_MDB_SRCLIST_UNSPEC,
	MDBA_MDB_SRCLIST_ENTRY,
	__MDBA_MDB_SRCLIST_MAX
पूर्ण;
#घोषणा MDBA_MDB_SRCLIST_MAX (__MDBA_MDB_SRCLIST_MAX - 1)

/* per mdb entry per source attributes
 * these are embedded in MDBA_MDB_SRCLIST_ENTRY
 */
क्रमागत अणु
	MDBA_MDB_SRCATTR_UNSPEC,
	MDBA_MDB_SRCATTR_ADDRESS,
	MDBA_MDB_SRCATTR_TIMER,
	__MDBA_MDB_SRCATTR_MAX
पूर्ण;
#घोषणा MDBA_MDB_SRCATTR_MAX (__MDBA_MDB_SRCATTR_MAX - 1)

/* multicast router types */
क्रमागत अणु
	MDB_RTR_TYPE_DISABLED,
	MDB_RTR_TYPE_TEMP_QUERY,
	MDB_RTR_TYPE_PERM,
	MDB_RTR_TYPE_TEMP
पूर्ण;

क्रमागत अणु
	MDBA_ROUTER_UNSPEC,
	MDBA_ROUTER_PORT,
	__MDBA_ROUTER_MAX,
पूर्ण;
#घोषणा MDBA_ROUTER_MAX (__MDBA_ROUTER_MAX - 1)

/* router port attributes */
क्रमागत अणु
	MDBA_ROUTER_PATTR_UNSPEC,
	MDBA_ROUTER_PATTR_TIMER,
	MDBA_ROUTER_PATTR_TYPE,
	__MDBA_ROUTER_PATTR_MAX
पूर्ण;
#घोषणा MDBA_ROUTER_PATTR_MAX (__MDBA_ROUTER_PATTR_MAX - 1)

काष्ठा br_port_msg अणु
	__u8  family;
	__u32 अगरindex;
पूर्ण;

काष्ठा br_mdb_entry अणु
	__u32 अगरindex;
#घोषणा MDB_TEMPORARY 0
#घोषणा MDB_PERMANENT 1
	__u8 state;
#घोषणा MDB_FLAGS_OFFLOAD	(1 << 0)
#घोषणा MDB_FLAGS_FAST_LEAVE	(1 << 1)
#घोषणा MDB_FLAGS_STAR_EXCL	(1 << 2)
#घोषणा MDB_FLAGS_BLOCKED	(1 << 3)
	__u8 flags;
	__u16 vid;
	काष्ठा अणु
		जोड़ अणु
			__be32	ip4;
			काष्ठा in6_addr ip6;
			अचिन्हित अक्षर mac_addr[ETH_ALEN];
		पूर्ण u;
		__be16		proto;
	पूर्ण addr;
पूर्ण;

क्रमागत अणु
	MDBA_SET_ENTRY_UNSPEC,
	MDBA_SET_ENTRY,
	MDBA_SET_ENTRY_ATTRS,
	__MDBA_SET_ENTRY_MAX,
पूर्ण;
#घोषणा MDBA_SET_ENTRY_MAX (__MDBA_SET_ENTRY_MAX - 1)

/* [MDBA_SET_ENTRY_ATTRS] = अणु
 *    [MDBE_ATTR_xxx]
 *    ...
 * पूर्ण
 */
क्रमागत अणु
	MDBE_ATTR_UNSPEC,
	MDBE_ATTR_SOURCE,
	__MDBE_ATTR_MAX,
पूर्ण;
#घोषणा MDBE_ATTR_MAX (__MDBE_ATTR_MAX - 1)

/* Embedded inside LINK_XSTATS_TYPE_BRIDGE */
क्रमागत अणु
	BRIDGE_XSTATS_UNSPEC,
	BRIDGE_XSTATS_VLAN,
	BRIDGE_XSTATS_MCAST,
	BRIDGE_XSTATS_PAD,
	BRIDGE_XSTATS_STP,
	__BRIDGE_XSTATS_MAX
पूर्ण;
#घोषणा BRIDGE_XSTATS_MAX (__BRIDGE_XSTATS_MAX - 1)

क्रमागत अणु
	BR_MCAST_सूची_RX,
	BR_MCAST_सूची_TX,
	BR_MCAST_सूची_SIZE
पूर्ण;

/* IGMP/MLD statistics */
काष्ठा br_mcast_stats अणु
	__u64 igmp_v1queries[BR_MCAST_सूची_SIZE];
	__u64 igmp_v2queries[BR_MCAST_सूची_SIZE];
	__u64 igmp_v3queries[BR_MCAST_सूची_SIZE];
	__u64 igmp_leaves[BR_MCAST_सूची_SIZE];
	__u64 igmp_v1reports[BR_MCAST_सूची_SIZE];
	__u64 igmp_v2reports[BR_MCAST_सूची_SIZE];
	__u64 igmp_v3reports[BR_MCAST_सूची_SIZE];
	__u64 igmp_parse_errors;

	__u64 mld_v1queries[BR_MCAST_सूची_SIZE];
	__u64 mld_v2queries[BR_MCAST_सूची_SIZE];
	__u64 mld_leaves[BR_MCAST_सूची_SIZE];
	__u64 mld_v1reports[BR_MCAST_सूची_SIZE];
	__u64 mld_v2reports[BR_MCAST_सूची_SIZE];
	__u64 mld_parse_errors;

	__u64 mcast_bytes[BR_MCAST_सूची_SIZE];
	__u64 mcast_packets[BR_MCAST_सूची_SIZE];
पूर्ण;

/* bridge boolean options
 * BR_BOOLOPT_NO_LL_LEARN - disable learning from link-local packets
 *
 * IMPORTANT: अगर adding a new option करो not क्रमget to handle
 *            it in br_boolopt_toggle/get and bridge sysfs
 */
क्रमागत br_boolopt_id अणु
	BR_BOOLOPT_NO_LL_LEARN,
	BR_BOOLOPT_MAX
पूर्ण;

/* काष्ठा br_boolopt_multi - change multiple bridge boolean options
 *
 * @optval: new option values (bit per option)
 * @opपंचांगask: options to change (bit per option)
 */
काष्ठा br_boolopt_multi अणु
	__u32 optval;
	__u32 opपंचांगask;
पूर्ण;
#पूर्ण_अगर /* _UAPI_LINUX_IF_BRIDGE_H */
