<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright 2014-2016 Freescale Semiconductor Inc.
 * Copyright 2017-2021 NXP
 *
 */

#अगर_अघोषित __FSL_DPSW_CMD_H
#घोषणा __FSL_DPSW_CMD_H

#समावेश "dpsw.h"

/* DPSW Version */
#घोषणा DPSW_VER_MAJOR		8
#घोषणा DPSW_VER_MINOR		9

#घोषणा DPSW_CMD_BASE_VERSION	1
#घोषणा DPSW_CMD_VERSION_2	2
#घोषणा DPSW_CMD_ID_OFFSET	4

#घोषणा DPSW_CMD_ID(id)	(((id) << DPSW_CMD_ID_OFFSET) | DPSW_CMD_BASE_VERSION)
#घोषणा DPSW_CMD_V2(id) (((id) << DPSW_CMD_ID_OFFSET) | DPSW_CMD_VERSION_2)

/* Command IDs */
#घोषणा DPSW_CMDID_CLOSE                    DPSW_CMD_ID(0x800)
#घोषणा DPSW_CMDID_OPEN                     DPSW_CMD_ID(0x802)

#घोषणा DPSW_CMDID_GET_API_VERSION          DPSW_CMD_ID(0xa02)

#घोषणा DPSW_CMDID_ENABLE                   DPSW_CMD_ID(0x002)
#घोषणा DPSW_CMDID_DISABLE                  DPSW_CMD_ID(0x003)
#घोषणा DPSW_CMDID_GET_ATTR                 DPSW_CMD_V2(0x004)
#घोषणा DPSW_CMDID_RESET                    DPSW_CMD_ID(0x005)

#घोषणा DPSW_CMDID_SET_IRQ_ENABLE           DPSW_CMD_ID(0x012)

#घोषणा DPSW_CMDID_SET_IRQ_MASK             DPSW_CMD_ID(0x014)

#घोषणा DPSW_CMDID_GET_IRQ_STATUS           DPSW_CMD_ID(0x016)
#घोषणा DPSW_CMDID_CLEAR_IRQ_STATUS         DPSW_CMD_ID(0x017)

#घोषणा DPSW_CMDID_IF_SET_TCI               DPSW_CMD_ID(0x030)
#घोषणा DPSW_CMDID_IF_SET_STP               DPSW_CMD_ID(0x031)

#घोषणा DPSW_CMDID_IF_GET_COUNTER           DPSW_CMD_V2(0x034)

#घोषणा DPSW_CMDID_IF_ENABLE                DPSW_CMD_ID(0x03D)
#घोषणा DPSW_CMDID_IF_DISABLE               DPSW_CMD_ID(0x03E)

#घोषणा DPSW_CMDID_IF_GET_ATTR              DPSW_CMD_ID(0x042)

#घोषणा DPSW_CMDID_IF_SET_MAX_FRAME_LENGTH  DPSW_CMD_ID(0x044)

#घोषणा DPSW_CMDID_IF_GET_LINK_STATE        DPSW_CMD_ID(0x046)

#घोषणा DPSW_CMDID_IF_GET_TCI               DPSW_CMD_ID(0x04A)

#घोषणा DPSW_CMDID_IF_SET_LINK_CFG          DPSW_CMD_ID(0x04C)

#घोषणा DPSW_CMDID_VLAN_ADD                 DPSW_CMD_ID(0x060)
#घोषणा DPSW_CMDID_VLAN_ADD_IF              DPSW_CMD_V2(0x061)
#घोषणा DPSW_CMDID_VLAN_ADD_IF_UNTAGGED     DPSW_CMD_ID(0x062)

#घोषणा DPSW_CMDID_VLAN_REMOVE_IF           DPSW_CMD_ID(0x064)
#घोषणा DPSW_CMDID_VLAN_REMOVE_IF_UNTAGGED  DPSW_CMD_ID(0x065)
#घोषणा DPSW_CMDID_VLAN_REMOVE_IF_FLOODING  DPSW_CMD_ID(0x066)
#घोषणा DPSW_CMDID_VLAN_REMOVE              DPSW_CMD_ID(0x067)

#घोषणा DPSW_CMDID_FDB_ADD                  DPSW_CMD_ID(0x082)
#घोषणा DPSW_CMDID_FDB_REMOVE               DPSW_CMD_ID(0x083)
#घोषणा DPSW_CMDID_FDB_ADD_UNICAST          DPSW_CMD_ID(0x084)
#घोषणा DPSW_CMDID_FDB_REMOVE_UNICAST       DPSW_CMD_ID(0x085)
#घोषणा DPSW_CMDID_FDB_ADD_MULTICAST        DPSW_CMD_ID(0x086)
#घोषणा DPSW_CMDID_FDB_REMOVE_MULTICAST     DPSW_CMD_ID(0x087)
#घोषणा DPSW_CMDID_FDB_DUMP                 DPSW_CMD_ID(0x08A)

#घोषणा DPSW_CMDID_ACL_ADD                  DPSW_CMD_ID(0x090)
#घोषणा DPSW_CMDID_ACL_REMOVE               DPSW_CMD_ID(0x091)
#घोषणा DPSW_CMDID_ACL_ADD_ENTRY            DPSW_CMD_ID(0x092)
#घोषणा DPSW_CMDID_ACL_REMOVE_ENTRY         DPSW_CMD_ID(0x093)
#घोषणा DPSW_CMDID_ACL_ADD_IF               DPSW_CMD_ID(0x094)
#घोषणा DPSW_CMDID_ACL_REMOVE_IF            DPSW_CMD_ID(0x095)

#घोषणा DPSW_CMDID_IF_GET_PORT_MAC_ADDR     DPSW_CMD_ID(0x0A7)

#घोषणा DPSW_CMDID_CTRL_IF_GET_ATTR         DPSW_CMD_ID(0x0A0)
#घोषणा DPSW_CMDID_CTRL_IF_SET_POOLS        DPSW_CMD_ID(0x0A1)
#घोषणा DPSW_CMDID_CTRL_IF_ENABLE           DPSW_CMD_ID(0x0A2)
#घोषणा DPSW_CMDID_CTRL_IF_DISABLE          DPSW_CMD_ID(0x0A3)
#घोषणा DPSW_CMDID_CTRL_IF_SET_QUEUE        DPSW_CMD_ID(0x0A6)

#घोषणा DPSW_CMDID_SET_EGRESS_FLOOD         DPSW_CMD_ID(0x0AC)
#घोषणा DPSW_CMDID_IF_SET_LEARNING_MODE     DPSW_CMD_ID(0x0AD)

/* Macros क्रम accessing command fields smaller than 1byte */
#घोषणा DPSW_MASK(field)        \
	GENMASK(DPSW_##field##_SHIFT + DPSW_##field##_SIZE - 1, \
		DPSW_##field##_SHIFT)
#घोषणा dpsw_set_field(var, field, val) \
	((var) |= (((val) << DPSW_##field##_SHIFT) & DPSW_MASK(field)))
#घोषणा dpsw_get_field(var, field)      \
	(((var) & DPSW_MASK(field)) >> DPSW_##field##_SHIFT)
#घोषणा dpsw_get_bit(var, bit) \
	(((var)  >> (bit)) & GENMASK(0, 0))

#आशय pack(push, 1)
काष्ठा dpsw_cmd_खोलो अणु
	__le32 dpsw_id;
पूर्ण;

#घोषणा DPSW_COMPONENT_TYPE_SHIFT	0
#घोषणा DPSW_COMPONENT_TYPE_SIZE	4

काष्ठा dpsw_cmd_create अणु
	/* cmd word 0 */
	__le16 num_अगरs;
	u8 max_fdbs;
	u8 max_meters_per_अगर;
	/* from LSB: only the first 4 bits */
	u8 component_type;
	u8 pad[3];
	/* cmd word 1 */
	__le16 max_vlans;
	__le16 max_fdb_entries;
	__le16 fdb_aging_समय;
	__le16 max_fdb_mc_groups;
	/* cmd word 2 */
	__le64 options;
पूर्ण;

काष्ठा dpsw_cmd_destroy अणु
	__le32 dpsw_id;
पूर्ण;

#घोषणा DPSW_ENABLE_SHIFT 0
#घोषणा DPSW_ENABLE_SIZE  1

काष्ठा dpsw_rsp_is_enabled अणु
	/* from LSB: enable:1 */
	u8 enabled;
पूर्ण;

काष्ठा dpsw_cmd_set_irq_enable अणु
	u8 enable_state;
	u8 pad[3];
	u8 irq_index;
पूर्ण;

काष्ठा dpsw_cmd_get_irq_enable अणु
	__le32 pad;
	u8 irq_index;
पूर्ण;

काष्ठा dpsw_rsp_get_irq_enable अणु
	u8 enable_state;
पूर्ण;

काष्ठा dpsw_cmd_set_irq_mask अणु
	__le32 mask;
	u8 irq_index;
पूर्ण;

काष्ठा dpsw_cmd_get_irq_mask अणु
	__le32 pad;
	u8 irq_index;
पूर्ण;

काष्ठा dpsw_rsp_get_irq_mask अणु
	__le32 mask;
पूर्ण;

काष्ठा dpsw_cmd_get_irq_status अणु
	__le32 status;
	u8 irq_index;
पूर्ण;

काष्ठा dpsw_rsp_get_irq_status अणु
	__le32 status;
पूर्ण;

काष्ठा dpsw_cmd_clear_irq_status अणु
	__le32 status;
	u8 irq_index;
पूर्ण;

#घोषणा DPSW_COMPONENT_TYPE_SHIFT	0
#घोषणा DPSW_COMPONENT_TYPE_SIZE	4

#घोषणा DPSW_FLOODING_CFG_SHIFT		0
#घोषणा DPSW_FLOODING_CFG_SIZE		4

#घोषणा DPSW_BROADCAST_CFG_SHIFT	4
#घोषणा DPSW_BROADCAST_CFG_SIZE		4

काष्ठा dpsw_rsp_get_attr अणु
	/* cmd word 0 */
	__le16 num_अगरs;
	u8 max_fdbs;
	u8 num_fdbs;
	__le16 max_vlans;
	__le16 num_vlans;
	/* cmd word 1 */
	__le16 max_fdb_entries;
	__le16 fdb_aging_समय;
	__le32 dpsw_id;
	/* cmd word 2 */
	__le16 mem_size;
	__le16 max_fdb_mc_groups;
	u8 max_meters_per_अगर;
	/* from LSB only the first 4 bits */
	u8 component_type;
	/* [0:3] - flooding configuration
	 * [4:7] - broadcast configuration
	 */
	u8 repl_cfg;
	u8 pad;
	/* cmd word 3 */
	__le64 options;
पूर्ण;

#घोषणा DPSW_VLAN_ID_SHIFT	0
#घोषणा DPSW_VLAN_ID_SIZE	12
#घोषणा DPSW_DEI_SHIFT		12
#घोषणा DPSW_DEI_SIZE		1
#घोषणा DPSW_PCP_SHIFT		13
#घोषणा DPSW_PCP_SIZE		3

काष्ठा dpsw_cmd_अगर_set_tci अणु
	__le16 अगर_id;
	/* from LSB: VLAN_ID:12 DEI:1 PCP:3 */
	__le16 conf;
पूर्ण;

काष्ठा dpsw_cmd_अगर_get_tci अणु
	__le16 अगर_id;
पूर्ण;

काष्ठा dpsw_rsp_अगर_get_tci अणु
	__le16 pad;
	__le16 vlan_id;
	u8 dei;
	u8 pcp;
पूर्ण;

#घोषणा DPSW_STATE_SHIFT	0
#घोषणा DPSW_STATE_SIZE		4

काष्ठा dpsw_cmd_अगर_set_stp अणु
	__le16 अगर_id;
	__le16 vlan_id;
	/* only the first LSB 4 bits */
	u8 state;
पूर्ण;

#घोषणा DPSW_COUNTER_TYPE_SHIFT		0
#घोषणा DPSW_COUNTER_TYPE_SIZE		5

काष्ठा dpsw_cmd_अगर_get_counter अणु
	__le16 अगर_id;
	/* from LSB: type:5 */
	u8 type;
पूर्ण;

काष्ठा dpsw_rsp_अगर_get_counter अणु
	__le64 pad;
	__le64 counter;
पूर्ण;

काष्ठा dpsw_cmd_अगर अणु
	__le16 अगर_id;
पूर्ण;

#घोषणा DPSW_ADMIT_UNTAGGED_SHIFT	0
#घोषणा DPSW_ADMIT_UNTAGGED_SIZE	4
#घोषणा DPSW_ENABLED_SHIFT		5
#घोषणा DPSW_ENABLED_SIZE		1
#घोषणा DPSW_ACCEPT_ALL_VLAN_SHIFT	6
#घोषणा DPSW_ACCEPT_ALL_VLAN_SIZE	1

काष्ठा dpsw_rsp_अगर_get_attr अणु
	/* cmd word 0 */
	/* from LSB: admit_untagged:4 enabled:1 accept_all_vlan:1 */
	u8 conf;
	u8 pad1;
	u8 num_tcs;
	u8 pad2;
	__le16 qdid;
	/* cmd word 1 */
	__le32 options;
	__le32 pad3;
	/* cmd word 2 */
	__le32 rate;
पूर्ण;

काष्ठा dpsw_cmd_अगर_set_max_frame_length अणु
	__le16 अगर_id;
	__le16 frame_length;
पूर्ण;

काष्ठा dpsw_cmd_अगर_set_link_cfg अणु
	/* cmd word 0 */
	__le16 अगर_id;
	u8 pad[6];
	/* cmd word 1 */
	__le32 rate;
	__le32 pad1;
	/* cmd word 2 */
	__le64 options;
पूर्ण;

काष्ठा dpsw_cmd_अगर_get_link_state अणु
	__le16 अगर_id;
पूर्ण;

#घोषणा DPSW_UP_SHIFT	0
#घोषणा DPSW_UP_SIZE	1

काष्ठा dpsw_rsp_अगर_get_link_state अणु
	/* cmd word 0 */
	__le32 pad0;
	u8 up;
	u8 pad1[3];
	/* cmd word 1 */
	__le32 rate;
	__le32 pad2;
	/* cmd word 2 */
	__le64 options;
पूर्ण;

काष्ठा dpsw_vlan_add अणु
	__le16 fdb_id;
	__le16 vlan_id;
पूर्ण;

काष्ठा dpsw_cmd_vlan_add_अगर अणु
	/* cmd word 0 */
	__le16 options;
	__le16 vlan_id;
	__le16 fdb_id;
	__le16 pad0;
	/* cmd word 1-4 */
	__le64 अगर_id;
पूर्ण;

काष्ठा dpsw_cmd_vlan_manage_अगर अणु
	/* cmd word 0 */
	__le16 pad0;
	__le16 vlan_id;
	__le32 pad1;
	/* cmd word 1-4 */
	__le64 अगर_id;
पूर्ण;

काष्ठा dpsw_cmd_vlan_हटाओ अणु
	__le16 pad;
	__le16 vlan_id;
पूर्ण;

काष्ठा dpsw_cmd_fdb_add अणु
	__le32 pad;
	__le16 fdb_ageing_समय;
	__le16 num_fdb_entries;
पूर्ण;

काष्ठा dpsw_rsp_fdb_add अणु
	__le16 fdb_id;
पूर्ण;

काष्ठा dpsw_cmd_fdb_हटाओ अणु
	__le16 fdb_id;
पूर्ण;

#घोषणा DPSW_ENTRY_TYPE_SHIFT	0
#घोषणा DPSW_ENTRY_TYPE_SIZE	4

काष्ठा dpsw_cmd_fdb_unicast_op अणु
	/* cmd word 0 */
	__le16 fdb_id;
	u8 mac_addr[6];
	/* cmd word 1 */
	__le16 अगर_egress;
	/* only the first 4 bits from LSB */
	u8 type;
पूर्ण;

काष्ठा dpsw_cmd_fdb_multicast_op अणु
	/* cmd word 0 */
	__le16 fdb_id;
	__le16 num_अगरs;
	/* only the first 4 bits from LSB */
	u8 type;
	u8 pad[3];
	/* cmd word 1 */
	u8 mac_addr[6];
	__le16 pad2;
	/* cmd word 2-5 */
	__le64 अगर_id;
पूर्ण;

काष्ठा dpsw_cmd_fdb_dump अणु
	__le16 fdb_id;
	__le16 pad0;
	__le32 pad1;
	__le64 iova_addr;
	__le32 iova_size;
पूर्ण;

काष्ठा dpsw_rsp_fdb_dump अणु
	__le16 num_entries;
पूर्ण;

काष्ठा dpsw_rsp_ctrl_अगर_get_attr अणु
	__le64 pad;
	__le32 rx_fqid;
	__le32 rx_err_fqid;
	__le32 tx_err_conf_fqid;
पूर्ण;

#घोषणा DPSW_BACKUP_POOL(val, order)	(((val) & 0x1) << (order))
काष्ठा dpsw_cmd_ctrl_अगर_set_pools अणु
	u8 num_dpbp;
	u8 backup_pool_mask;
	__le16 pad;
	__le32 dpbp_id[DPSW_MAX_DPBP];
	__le16 buffer_size[DPSW_MAX_DPBP];
पूर्ण;

#घोषणा DPSW_DEST_TYPE_SHIFT	0
#घोषणा DPSW_DEST_TYPE_SIZE	4

काष्ठा dpsw_cmd_ctrl_अगर_set_queue अणु
	__le32 dest_id;
	u8 dest_priority;
	u8 pad;
	/* from LSB: dest_type:4 */
	u8 dest_type;
	u8 qtype;
	__le64 user_ctx;
	__le32 options;
पूर्ण;

काष्ठा dpsw_rsp_get_api_version अणु
	__le16 version_major;
	__le16 version_minor;
पूर्ण;

काष्ठा dpsw_rsp_अगर_get_mac_addr अणु
	__le16 pad;
	u8 mac_addr[6];
पूर्ण;

काष्ठा dpsw_cmd_set_egress_flood अणु
	__le16 fdb_id;
	u8 flood_type;
	u8 pad[5];
	__le64 अगर_id;
पूर्ण;

#घोषणा DPSW_LEARNING_MODE_SHIFT	0
#घोषणा DPSW_LEARNING_MODE_SIZE		4

काष्ठा dpsw_cmd_अगर_set_learning_mode अणु
	__le16 अगर_id;
	/* only the first 4 bits from LSB */
	u8 mode;
पूर्ण;

काष्ठा dpsw_cmd_acl_add अणु
	__le16 pad;
	__le16 max_entries;
पूर्ण;

काष्ठा dpsw_rsp_acl_add अणु
	__le16 acl_id;
पूर्ण;

काष्ठा dpsw_cmd_acl_हटाओ अणु
	__le16 acl_id;
पूर्ण;

काष्ठा dpsw_cmd_acl_अगर अणु
	__le16 acl_id;
	__le16 num_अगरs;
	__le32 pad;
	__le64 अगर_id;
पूर्ण;

काष्ठा dpsw_prep_acl_entry अणु
	u8 match_l2_dest_mac[6];
	__le16 match_l2_tpid;

	u8 match_l2_source_mac[6];
	__le16 match_l2_vlan_id;

	__le32 match_l3_dest_ip;
	__le32 match_l3_source_ip;

	__le16 match_l4_dest_port;
	__le16 match_l4_source_port;
	__le16 match_l2_ether_type;
	u8 match_l2_pcp_dei;
	u8 match_l3_dscp;

	u8 mask_l2_dest_mac[6];
	__le16 mask_l2_tpid;

	u8 mask_l2_source_mac[6];
	__le16 mask_l2_vlan_id;

	__le32 mask_l3_dest_ip;
	__le32 mask_l3_source_ip;

	__le16 mask_l4_dest_port;
	__le16 mask_l4_source_port;
	__le16 mask_l2_ether_type;
	u8 mask_l2_pcp_dei;
	u8 mask_l3_dscp;

	u8 match_l3_protocol;
	u8 mask_l3_protocol;
पूर्ण;

#घोषणा DPSW_RESULT_ACTION_SHIFT	0
#घोषणा DPSW_RESULT_ACTION_SIZE		4

काष्ठा dpsw_cmd_acl_entry अणु
	__le16 acl_id;
	__le16 result_अगर_id;
	__le32 precedence;
	/* from LSB only the first 4 bits */
	u8 result_action;
	u8 pad[7];
	__le64 pad2[4];
	__le64 key_iova;
पूर्ण;
#आशय pack(pop)
#पूर्ण_अगर /* __FSL_DPSW_CMD_H */
