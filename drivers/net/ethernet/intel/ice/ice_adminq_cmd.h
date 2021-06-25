<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2018, Intel Corporation. */

#अगर_अघोषित _ICE_ADMINQ_CMD_H_
#घोषणा _ICE_ADMINQ_CMD_H_

/* This header file defines the Admin Queue commands, error codes and
 * descriptor क्रमmat. It is shared between Firmware and Software.
 */

#घोषणा ICE_MAX_VSI			768
#घोषणा ICE_AQC_TOPO_MAX_LEVEL_NUM	0x9
#घोषणा ICE_AQ_SET_MAC_FRAME_SIZE_MAX	9728

काष्ठा ice_aqc_generic अणु
	__le32 param0;
	__le32 param1;
	__le32 addr_high;
	__le32 addr_low;
पूर्ण;

/* Get version (direct 0x0001) */
काष्ठा ice_aqc_get_ver अणु
	__le32 rom_ver;
	__le32 fw_build;
	u8 fw_branch;
	u8 fw_major;
	u8 fw_minor;
	u8 fw_patch;
	u8 api_branch;
	u8 api_major;
	u8 api_minor;
	u8 api_patch;
पूर्ण;

/* Send driver version (indirect 0x0002) */
काष्ठा ice_aqc_driver_ver अणु
	u8 major_ver;
	u8 minor_ver;
	u8 build_ver;
	u8 subbuild_ver;
	u8 reserved[4];
	__le32 addr_high;
	__le32 addr_low;
पूर्ण;

/* Queue Shutकरोwn (direct 0x0003) */
काष्ठा ice_aqc_q_shutकरोwn अणु
	u8 driver_unloading;
#घोषणा ICE_AQC_DRIVER_UNLOADING	BIT(0)
	u8 reserved[15];
पूर्ण;

/* Request resource ownership (direct 0x0008)
 * Release resource ownership (direct 0x0009)
 */
काष्ठा ice_aqc_req_res अणु
	__le16 res_id;
#घोषणा ICE_AQC_RES_ID_NVM		1
#घोषणा ICE_AQC_RES_ID_SDP		2
#घोषणा ICE_AQC_RES_ID_CHNG_LOCK	3
#घोषणा ICE_AQC_RES_ID_GLBL_LOCK	4
	__le16 access_type;
#घोषणा ICE_AQC_RES_ACCESS_READ		1
#घोषणा ICE_AQC_RES_ACCESS_WRITE	2

	/* Upon successful completion, FW ग_लिखोs this value and driver is
	 * expected to release resource beक्रमe समयout. This value is provided
	 * in milliseconds.
	 */
	__le32 समयout;
#घोषणा ICE_AQ_RES_NVM_READ_DFLT_TIMEOUT_MS	3000
#घोषणा ICE_AQ_RES_NVM_WRITE_DFLT_TIMEOUT_MS	180000
#घोषणा ICE_AQ_RES_CHNG_LOCK_DFLT_TIMEOUT_MS	1000
#घोषणा ICE_AQ_RES_GLBL_LOCK_DFLT_TIMEOUT_MS	3000
	/* For SDP: pin ID of the SDP */
	__le32 res_number;
	/* Status is only used क्रम ICE_AQC_RES_ID_GLBL_LOCK */
	__le16 status;
#घोषणा ICE_AQ_RES_GLBL_SUCCESS		0
#घोषणा ICE_AQ_RES_GLBL_IN_PROG		1
#घोषणा ICE_AQ_RES_GLBL_DONE		2
	u8 reserved[2];
पूर्ण;

/* Get function capabilities (indirect 0x000A)
 * Get device capabilities (indirect 0x000B)
 */
काष्ठा ice_aqc_list_caps अणु
	u8 cmd_flags;
	u8 pf_index;
	u8 reserved[2];
	__le32 count;
	__le32 addr_high;
	__le32 addr_low;
पूर्ण;

/* Device/Function buffer entry, repeated per reported capability */
काष्ठा ice_aqc_list_caps_elem अणु
	__le16 cap;
#घोषणा ICE_AQC_CAPS_VALID_FUNCTIONS			0x0005
#घोषणा ICE_AQC_CAPS_SRIOV				0x0012
#घोषणा ICE_AQC_CAPS_VF					0x0013
#घोषणा ICE_AQC_CAPS_VSI				0x0017
#घोषणा ICE_AQC_CAPS_DCB				0x0018
#घोषणा ICE_AQC_CAPS_RSS				0x0040
#घोषणा ICE_AQC_CAPS_RXQS				0x0041
#घोषणा ICE_AQC_CAPS_TXQS				0x0042
#घोषणा ICE_AQC_CAPS_MSIX				0x0043
#घोषणा ICE_AQC_CAPS_FD					0x0045
#घोषणा ICE_AQC_CAPS_MAX_MTU				0x0047
#घोषणा ICE_AQC_CAPS_NVM_VER				0x0048
#घोषणा ICE_AQC_CAPS_PENDING_NVM_VER			0x0049
#घोषणा ICE_AQC_CAPS_OROM_VER				0x004A
#घोषणा ICE_AQC_CAPS_PENDING_OROM_VER			0x004B
#घोषणा ICE_AQC_CAPS_NET_VER				0x004C
#घोषणा ICE_AQC_CAPS_PENDING_NET_VER			0x004D
#घोषणा ICE_AQC_CAPS_NVM_MGMT				0x0080

	u8 major_ver;
	u8 minor_ver;
	/* Number of resources described by this capability */
	__le32 number;
	/* Only meaningful क्रम some types of resources */
	__le32 logical_id;
	/* Only meaningful क्रम some types of resources */
	__le32 phys_id;
	__le64 rsvd1;
	__le64 rsvd2;
पूर्ण;

/* Manage MAC address, पढ़ो command - indirect (0x0107)
 * This काष्ठा is also used क्रम the response
 */
काष्ठा ice_aqc_manage_mac_पढ़ो अणु
	__le16 flags; /* Zeroed by device driver */
#घोषणा ICE_AQC_MAN_MAC_LAN_ADDR_VALID		BIT(4)
#घोषणा ICE_AQC_MAN_MAC_SAN_ADDR_VALID		BIT(5)
#घोषणा ICE_AQC_MAN_MAC_PORT_ADDR_VALID		BIT(6)
#घोषणा ICE_AQC_MAN_MAC_WOL_ADDR_VALID		BIT(7)
#घोषणा ICE_AQC_MAN_MAC_READ_S			4
#घोषणा ICE_AQC_MAN_MAC_READ_M			(0xF << ICE_AQC_MAN_MAC_READ_S)
	u8 rsvd[2];
	u8 num_addr; /* Used in response */
	u8 rsvd1[3];
	__le32 addr_high;
	__le32 addr_low;
पूर्ण;

/* Response buffer क्रमmat क्रम manage MAC पढ़ो command */
काष्ठा ice_aqc_manage_mac_पढ़ो_resp अणु
	u8 lport_num;
	u8 addr_type;
#घोषणा ICE_AQC_MAN_MAC_ADDR_TYPE_LAN		0
#घोषणा ICE_AQC_MAN_MAC_ADDR_TYPE_WOL		1
	u8 mac_addr[ETH_ALEN];
पूर्ण;

/* Manage MAC address, ग_लिखो command - direct (0x0108) */
काष्ठा ice_aqc_manage_mac_ग_लिखो अणु
	u8 rsvd;
	u8 flags;
#घोषणा ICE_AQC_MAN_MAC_WR_MC_MAG_EN		BIT(0)
#घोषणा ICE_AQC_MAN_MAC_WR_WOL_LAA_PFR_KEEP	BIT(1)
#घोषणा ICE_AQC_MAN_MAC_WR_S		6
#घोषणा ICE_AQC_MAN_MAC_WR_M		ICE_M(3, ICE_AQC_MAN_MAC_WR_S)
#घोषणा ICE_AQC_MAN_MAC_UPDATE_LAA	0
#घोषणा ICE_AQC_MAN_MAC_UPDATE_LAA_WOL	BIT(ICE_AQC_MAN_MAC_WR_S)
	/* byte stream in network order */
	u8 mac_addr[ETH_ALEN];
	__le32 addr_high;
	__le32 addr_low;
पूर्ण;

/* Clear PXE Command and response (direct 0x0110) */
काष्ठा ice_aqc_clear_pxe अणु
	u8 rx_cnt;
#घोषणा ICE_AQC_CLEAR_PXE_RX_CNT		0x2
	u8 reserved[15];
पूर्ण;

/* Get चयन configuration (0x0200) */
काष्ठा ice_aqc_get_sw_cfg अणु
	/* Reserved क्रम command and copy of request flags क्रम response */
	__le16 flags;
	/* First desc in हाल of command and next_elem in हाल of response
	 * In हाल of response, अगर it is not zero, means all the configuration
	 * was not वापसed and new command shall be sent with this value in
	 * the 'first desc' field
	 */
	__le16 element;
	/* Reserved क्रम command, only used क्रम response */
	__le16 num_elems;
	__le16 rsvd;
	__le32 addr_high;
	__le32 addr_low;
पूर्ण;

/* Each entry in the response buffer is of the following type: */
काष्ठा ice_aqc_get_sw_cfg_resp_elem अणु
	/* VSI/Port Number */
	__le16 vsi_port_num;
#घोषणा ICE_AQC_GET_SW_CONF_RESP_VSI_PORT_NUM_S	0
#घोषणा ICE_AQC_GET_SW_CONF_RESP_VSI_PORT_NUM_M	\
			(0x3FF << ICE_AQC_GET_SW_CONF_RESP_VSI_PORT_NUM_S)
#घोषणा ICE_AQC_GET_SW_CONF_RESP_TYPE_S	14
#घोषणा ICE_AQC_GET_SW_CONF_RESP_TYPE_M	(0x3 << ICE_AQC_GET_SW_CONF_RESP_TYPE_S)
#घोषणा ICE_AQC_GET_SW_CONF_RESP_PHYS_PORT	0
#घोषणा ICE_AQC_GET_SW_CONF_RESP_VIRT_PORT	1
#घोषणा ICE_AQC_GET_SW_CONF_RESP_VSI		2

	/* SWID VSI/Port beदीर्घs to */
	__le16 swid;

	/* Bit 14..0 : PF/VF number VSI beदीर्घs to
	 * Bit 15 : VF indication bit
	 */
	__le16 pf_vf_num;
#घोषणा ICE_AQC_GET_SW_CONF_RESP_FUNC_NUM_S	0
#घोषणा ICE_AQC_GET_SW_CONF_RESP_FUNC_NUM_M	\
				(0x7FFF << ICE_AQC_GET_SW_CONF_RESP_FUNC_NUM_S)
#घोषणा ICE_AQC_GET_SW_CONF_RESP_IS_VF		BIT(15)
पूर्ण;

/* These resource type defines are used क्रम all चयन resource
 * commands where a resource type is required, such as:
 * Get Resource Allocation command (indirect 0x0204)
 * Allocate Resources command (indirect 0x0208)
 * Free Resources command (indirect 0x0209)
 * Get Allocated Resource Descriptors Command (indirect 0x020A)
 */
#घोषणा ICE_AQC_RES_TYPE_VSI_LIST_REP			0x03
#घोषणा ICE_AQC_RES_TYPE_VSI_LIST_PRUNE			0x04
#घोषणा ICE_AQC_RES_TYPE_Fसूची_COUNTER_BLOCK		0x21
#घोषणा ICE_AQC_RES_TYPE_Fसूची_GUARANTEED_ENTRIES	0x22
#घोषणा ICE_AQC_RES_TYPE_Fसूची_SHARED_ENTRIES		0x23
#घोषणा ICE_AQC_RES_TYPE_FD_PROF_BLDR_PROFID		0x58
#घोषणा ICE_AQC_RES_TYPE_FD_PROF_BLDR_TCAM		0x59
#घोषणा ICE_AQC_RES_TYPE_HASH_PROF_BLDR_PROFID		0x60
#घोषणा ICE_AQC_RES_TYPE_HASH_PROF_BLDR_TCAM		0x61

#घोषणा ICE_AQC_RES_TYPE_FLAG_SCAN_BOTTOM		BIT(12)
#घोषणा ICE_AQC_RES_TYPE_FLAG_IGNORE_INDEX		BIT(13)

#घोषणा ICE_AQC_RES_TYPE_FLAG_DEDICATED			0x00

#घोषणा ICE_AQC_RES_TYPE_S	0
#घोषणा ICE_AQC_RES_TYPE_M	(0x07F << ICE_AQC_RES_TYPE_S)

/* Allocate Resources command (indirect 0x0208)
 * Free Resources command (indirect 0x0209)
 */
काष्ठा ice_aqc_alloc_मुक्त_res_cmd अणु
	__le16 num_entries; /* Number of Resource entries */
	u8 reserved[6];
	__le32 addr_high;
	__le32 addr_low;
पूर्ण;

/* Resource descriptor */
काष्ठा ice_aqc_res_elem अणु
	जोड़ अणु
		__le16 sw_resp;
		__le16 flu_resp;
	पूर्ण e;
पूर्ण;

/* Buffer क्रम Allocate/Free Resources commands */
काष्ठा ice_aqc_alloc_मुक्त_res_elem अणु
	__le16 res_type; /* Types defined above cmd 0x0204 */
#घोषणा ICE_AQC_RES_TYPE_SHARED_S	7
#घोषणा ICE_AQC_RES_TYPE_SHARED_M	(0x1 << ICE_AQC_RES_TYPE_SHARED_S)
#घोषणा ICE_AQC_RES_TYPE_VSI_PRUNE_LIST_S	8
#घोषणा ICE_AQC_RES_TYPE_VSI_PRUNE_LIST_M	\
				(0xF << ICE_AQC_RES_TYPE_VSI_PRUNE_LIST_S)
	__le16 num_elems;
	काष्ठा ice_aqc_res_elem elem[];
पूर्ण;

/* Add VSI (indirect 0x0210)
 * Update VSI (indirect 0x0211)
 * Get VSI (indirect 0x0212)
 * Free VSI (indirect 0x0213)
 */
काष्ठा ice_aqc_add_get_update_मुक्त_vsi अणु
	__le16 vsi_num;
#घोषणा ICE_AQ_VSI_NUM_S	0
#घोषणा ICE_AQ_VSI_NUM_M	(0x03FF << ICE_AQ_VSI_NUM_S)
#घोषणा ICE_AQ_VSI_IS_VALID	BIT(15)
	__le16 cmd_flags;
#घोषणा ICE_AQ_VSI_KEEP_ALLOC	0x1
	u8 vf_id;
	u8 reserved;
	__le16 vsi_flags;
#घोषणा ICE_AQ_VSI_TYPE_S	0
#घोषणा ICE_AQ_VSI_TYPE_M	(0x3 << ICE_AQ_VSI_TYPE_S)
#घोषणा ICE_AQ_VSI_TYPE_VF	0x0
#घोषणा ICE_AQ_VSI_TYPE_VMDQ2	0x1
#घोषणा ICE_AQ_VSI_TYPE_PF	0x2
#घोषणा ICE_AQ_VSI_TYPE_EMP_MNG	0x3
	__le32 addr_high;
	__le32 addr_low;
पूर्ण;

/* Response descriptor क्रम:
 * Add VSI (indirect 0x0210)
 * Update VSI (indirect 0x0211)
 * Free VSI (indirect 0x0213)
 */
काष्ठा ice_aqc_add_update_मुक्त_vsi_resp अणु
	__le16 vsi_num;
	__le16 ext_status;
	__le16 vsi_used;
	__le16 vsi_मुक्त;
	__le32 addr_high;
	__le32 addr_low;
पूर्ण;

काष्ठा ice_aqc_vsi_props अणु
	__le16 valid_sections;
#घोषणा ICE_AQ_VSI_PROP_SW_VALID		BIT(0)
#घोषणा ICE_AQ_VSI_PROP_SECURITY_VALID		BIT(1)
#घोषणा ICE_AQ_VSI_PROP_VLAN_VALID		BIT(2)
#घोषणा ICE_AQ_VSI_PROP_OUTER_TAG_VALID		BIT(3)
#घोषणा ICE_AQ_VSI_PROP_INGRESS_UP_VALID	BIT(4)
#घोषणा ICE_AQ_VSI_PROP_EGRESS_UP_VALID		BIT(5)
#घोषणा ICE_AQ_VSI_PROP_RXQ_MAP_VALID		BIT(6)
#घोषणा ICE_AQ_VSI_PROP_Q_OPT_VALID		BIT(7)
#घोषणा ICE_AQ_VSI_PROP_OUTER_UP_VALID		BIT(8)
#घोषणा ICE_AQ_VSI_PROP_FLOW_सूची_VALID		BIT(11)
#घोषणा ICE_AQ_VSI_PROP_PASID_VALID		BIT(12)
	/* चयन section */
	u8 sw_id;
	u8 sw_flags;
#घोषणा ICE_AQ_VSI_SW_FLAG_ALLOW_LB		BIT(5)
#घोषणा ICE_AQ_VSI_SW_FLAG_LOCAL_LB		BIT(6)
#घोषणा ICE_AQ_VSI_SW_FLAG_SRC_PRUNE		BIT(7)
	u8 sw_flags2;
#घोषणा ICE_AQ_VSI_SW_FLAG_RX_PRUNE_EN_S	0
#घोषणा ICE_AQ_VSI_SW_FLAG_RX_PRUNE_EN_M	\
				(0xF << ICE_AQ_VSI_SW_FLAG_RX_PRUNE_EN_S)
#घोषणा ICE_AQ_VSI_SW_FLAG_RX_VLAN_PRUNE_ENA	BIT(0)
#घोषणा ICE_AQ_VSI_SW_FLAG_LAN_ENA		BIT(4)
	u8 veb_stat_id;
#घोषणा ICE_AQ_VSI_SW_VEB_STAT_ID_S		0
#घोषणा ICE_AQ_VSI_SW_VEB_STAT_ID_M	(0x1F << ICE_AQ_VSI_SW_VEB_STAT_ID_S)
#घोषणा ICE_AQ_VSI_SW_VEB_STAT_ID_VALID		BIT(5)
	/* security section */
	u8 sec_flags;
#घोषणा ICE_AQ_VSI_SEC_FLAG_ALLOW_DEST_OVRD	BIT(0)
#घोषणा ICE_AQ_VSI_SEC_FLAG_ENA_MAC_ANTI_SPOOF	BIT(2)
#घोषणा ICE_AQ_VSI_SEC_TX_PRUNE_ENA_S	4
#घोषणा ICE_AQ_VSI_SEC_TX_PRUNE_ENA_M	(0xF << ICE_AQ_VSI_SEC_TX_PRUNE_ENA_S)
#घोषणा ICE_AQ_VSI_SEC_TX_VLAN_PRUNE_ENA	BIT(0)
	u8 sec_reserved;
	/* VLAN section */
	__le16 pvid; /* VLANS include priority bits */
	u8 pvlan_reserved[2];
	u8 vlan_flags;
#घोषणा ICE_AQ_VSI_VLAN_MODE_S	0
#घोषणा ICE_AQ_VSI_VLAN_MODE_M	(0x3 << ICE_AQ_VSI_VLAN_MODE_S)
#घोषणा ICE_AQ_VSI_VLAN_MODE_UNTAGGED	0x1
#घोषणा ICE_AQ_VSI_VLAN_MODE_TAGGED	0x2
#घोषणा ICE_AQ_VSI_VLAN_MODE_ALL	0x3
#घोषणा ICE_AQ_VSI_PVLAN_INSERT_PVID	BIT(2)
#घोषणा ICE_AQ_VSI_VLAN_EMOD_S		3
#घोषणा ICE_AQ_VSI_VLAN_EMOD_M		(0x3 << ICE_AQ_VSI_VLAN_EMOD_S)
#घोषणा ICE_AQ_VSI_VLAN_EMOD_STR_BOTH	(0x0 << ICE_AQ_VSI_VLAN_EMOD_S)
#घोषणा ICE_AQ_VSI_VLAN_EMOD_STR_UP	(0x1 << ICE_AQ_VSI_VLAN_EMOD_S)
#घोषणा ICE_AQ_VSI_VLAN_EMOD_STR	(0x2 << ICE_AQ_VSI_VLAN_EMOD_S)
#घोषणा ICE_AQ_VSI_VLAN_EMOD_NOTHING	(0x3 << ICE_AQ_VSI_VLAN_EMOD_S)
	u8 pvlan_reserved2[3];
	/* ingress egress up sections */
	__le32 ingress_table; /* biपंचांगap, 3 bits per up */
#घोषणा ICE_AQ_VSI_UP_TABLE_UP0_S	0
#घोषणा ICE_AQ_VSI_UP_TABLE_UP0_M	(0x7 << ICE_AQ_VSI_UP_TABLE_UP0_S)
#घोषणा ICE_AQ_VSI_UP_TABLE_UP1_S	3
#घोषणा ICE_AQ_VSI_UP_TABLE_UP1_M	(0x7 << ICE_AQ_VSI_UP_TABLE_UP1_S)
#घोषणा ICE_AQ_VSI_UP_TABLE_UP2_S	6
#घोषणा ICE_AQ_VSI_UP_TABLE_UP2_M	(0x7 << ICE_AQ_VSI_UP_TABLE_UP2_S)
#घोषणा ICE_AQ_VSI_UP_TABLE_UP3_S	9
#घोषणा ICE_AQ_VSI_UP_TABLE_UP3_M	(0x7 << ICE_AQ_VSI_UP_TABLE_UP3_S)
#घोषणा ICE_AQ_VSI_UP_TABLE_UP4_S	12
#घोषणा ICE_AQ_VSI_UP_TABLE_UP4_M	(0x7 << ICE_AQ_VSI_UP_TABLE_UP4_S)
#घोषणा ICE_AQ_VSI_UP_TABLE_UP5_S	15
#घोषणा ICE_AQ_VSI_UP_TABLE_UP5_M	(0x7 << ICE_AQ_VSI_UP_TABLE_UP5_S)
#घोषणा ICE_AQ_VSI_UP_TABLE_UP6_S	18
#घोषणा ICE_AQ_VSI_UP_TABLE_UP6_M	(0x7 << ICE_AQ_VSI_UP_TABLE_UP6_S)
#घोषणा ICE_AQ_VSI_UP_TABLE_UP7_S	21
#घोषणा ICE_AQ_VSI_UP_TABLE_UP7_M	(0x7 << ICE_AQ_VSI_UP_TABLE_UP7_S)
	__le32 egress_table;   /* same defines as क्रम ingress table */
	/* outer tags section */
	__le16 outer_tag;
	u8 outer_tag_flags;
#घोषणा ICE_AQ_VSI_OUTER_TAG_MODE_S	0
#घोषणा ICE_AQ_VSI_OUTER_TAG_MODE_M	(0x3 << ICE_AQ_VSI_OUTER_TAG_MODE_S)
#घोषणा ICE_AQ_VSI_OUTER_TAG_NOTHING	0x0
#घोषणा ICE_AQ_VSI_OUTER_TAG_REMOVE	0x1
#घोषणा ICE_AQ_VSI_OUTER_TAG_COPY	0x2
#घोषणा ICE_AQ_VSI_OUTER_TAG_TYPE_S	2
#घोषणा ICE_AQ_VSI_OUTER_TAG_TYPE_M	(0x3 << ICE_AQ_VSI_OUTER_TAG_TYPE_S)
#घोषणा ICE_AQ_VSI_OUTER_TAG_NONE	0x0
#घोषणा ICE_AQ_VSI_OUTER_TAG_STAG	0x1
#घोषणा ICE_AQ_VSI_OUTER_TAG_VLAN_8100	0x2
#घोषणा ICE_AQ_VSI_OUTER_TAG_VLAN_9100	0x3
#घोषणा ICE_AQ_VSI_OUTER_TAG_INSERT	BIT(4)
#घोषणा ICE_AQ_VSI_OUTER_TAG_ACCEPT_HOST BIT(6)
	u8 outer_tag_reserved;
	/* queue mapping section */
	__le16 mapping_flags;
#घोषणा ICE_AQ_VSI_Q_MAP_CONTIG	0x0
#घोषणा ICE_AQ_VSI_Q_MAP_NONCONTIG	BIT(0)
	__le16 q_mapping[16];
#घोषणा ICE_AQ_VSI_Q_S		0
#घोषणा ICE_AQ_VSI_Q_M		(0x7FF << ICE_AQ_VSI_Q_S)
	__le16 tc_mapping[8];
#घोषणा ICE_AQ_VSI_TC_Q_OFFSET_S	0
#घोषणा ICE_AQ_VSI_TC_Q_OFFSET_M	(0x7FF << ICE_AQ_VSI_TC_Q_OFFSET_S)
#घोषणा ICE_AQ_VSI_TC_Q_NUM_S		11
#घोषणा ICE_AQ_VSI_TC_Q_NUM_M		(0xF << ICE_AQ_VSI_TC_Q_NUM_S)
	/* queueing option section */
	u8 q_opt_rss;
#घोषणा ICE_AQ_VSI_Q_OPT_RSS_LUT_S	0
#घोषणा ICE_AQ_VSI_Q_OPT_RSS_LUT_M	(0x3 << ICE_AQ_VSI_Q_OPT_RSS_LUT_S)
#घोषणा ICE_AQ_VSI_Q_OPT_RSS_LUT_VSI	0x0
#घोषणा ICE_AQ_VSI_Q_OPT_RSS_LUT_PF	0x2
#घोषणा ICE_AQ_VSI_Q_OPT_RSS_LUT_GBL	0x3
#घोषणा ICE_AQ_VSI_Q_OPT_RSS_GBL_LUT_S	2
#घोषणा ICE_AQ_VSI_Q_OPT_RSS_GBL_LUT_M	(0xF << ICE_AQ_VSI_Q_OPT_RSS_GBL_LUT_S)
#घोषणा ICE_AQ_VSI_Q_OPT_RSS_HASH_S	6
#घोषणा ICE_AQ_VSI_Q_OPT_RSS_HASH_M	(0x3 << ICE_AQ_VSI_Q_OPT_RSS_HASH_S)
#घोषणा ICE_AQ_VSI_Q_OPT_RSS_TPLZ	(0x0 << ICE_AQ_VSI_Q_OPT_RSS_HASH_S)
#घोषणा ICE_AQ_VSI_Q_OPT_RSS_SYM_TPLZ	(0x1 << ICE_AQ_VSI_Q_OPT_RSS_HASH_S)
#घोषणा ICE_AQ_VSI_Q_OPT_RSS_XOR	(0x2 << ICE_AQ_VSI_Q_OPT_RSS_HASH_S)
#घोषणा ICE_AQ_VSI_Q_OPT_RSS_JHASH	(0x3 << ICE_AQ_VSI_Q_OPT_RSS_HASH_S)
	u8 q_opt_tc;
#घोषणा ICE_AQ_VSI_Q_OPT_TC_OVR_S	0
#घोषणा ICE_AQ_VSI_Q_OPT_TC_OVR_M	(0x1F << ICE_AQ_VSI_Q_OPT_TC_OVR_S)
#घोषणा ICE_AQ_VSI_Q_OPT_PROF_TC_OVR	BIT(7)
	u8 q_opt_flags;
#घोषणा ICE_AQ_VSI_Q_OPT_PE_FLTR_EN	BIT(0)
	u8 q_opt_reserved[3];
	/* outer up section */
	__le32 outer_up_table; /* same काष्ठाure and defines as ingress tbl */
	/* section 10 */
	__le16 sect_10_reserved;
	/* flow director section */
	__le16 fd_options;
#घोषणा ICE_AQ_VSI_FD_ENABLE		BIT(0)
#घोषणा ICE_AQ_VSI_FD_TX_AUTO_ENABLE	BIT(1)
#घोषणा ICE_AQ_VSI_FD_PROG_ENABLE	BIT(3)
	__le16 max_fd_fltr_dedicated;
	__le16 max_fd_fltr_shared;
	__le16 fd_def_q;
#घोषणा ICE_AQ_VSI_FD_DEF_Q_S		0
#घोषणा ICE_AQ_VSI_FD_DEF_Q_M		(0x7FF << ICE_AQ_VSI_FD_DEF_Q_S)
#घोषणा ICE_AQ_VSI_FD_DEF_GRP_S	12
#घोषणा ICE_AQ_VSI_FD_DEF_GRP_M	(0x7 << ICE_AQ_VSI_FD_DEF_GRP_S)
	__le16 fd_report_opt;
#घोषणा ICE_AQ_VSI_FD_REPORT_Q_S	0
#घोषणा ICE_AQ_VSI_FD_REPORT_Q_M	(0x7FF << ICE_AQ_VSI_FD_REPORT_Q_S)
#घोषणा ICE_AQ_VSI_FD_DEF_PRIORITY_S	12
#घोषणा ICE_AQ_VSI_FD_DEF_PRIORITY_M	(0x7 << ICE_AQ_VSI_FD_DEF_PRIORITY_S)
#घोषणा ICE_AQ_VSI_FD_DEF_DROP		BIT(15)
	/* PASID section */
	__le32 pasid_id;
#घोषणा ICE_AQ_VSI_PASID_ID_S		0
#घोषणा ICE_AQ_VSI_PASID_ID_M		(0xFFFFF << ICE_AQ_VSI_PASID_ID_S)
#घोषणा ICE_AQ_VSI_PASID_ID_VALID	BIT(31)
	u8 reserved[24];
पूर्ण;

#घोषणा ICE_MAX_NUM_RECIPES 64

/* Add/Update/Remove/Get चयन rules (indirect 0x02A0, 0x02A1, 0x02A2, 0x02A3)
 */
काष्ठा ice_aqc_sw_rules अणु
	/* ops: add चयन rules, referring the number of rules.
	 * ops: update चयन rules, referring the number of filters
	 * ops: हटाओ चयन rules, referring the entry index.
	 * ops: get चयन rules, referring to the number of filters.
	 */
	__le16 num_rules_fltr_entry_index;
	u8 reserved[6];
	__le32 addr_high;
	__le32 addr_low;
पूर्ण;

/* Add/Update/Get/Remove lookup Rx/Tx command/response entry
 * This काष्ठाures describes the lookup rules and associated actions. "index"
 * is वापसed as part of a response to a successful Add command, and can be
 * used to identअगरy the rule क्रम Update/Get/Remove commands.
 */
काष्ठा ice_sw_rule_lkup_rx_tx अणु
	__le16 recipe_id;
#घोषणा ICE_SW_RECIPE_LOGICAL_PORT_FWD		10
	/* Source port क्रम LOOKUP_RX and source VSI in हाल of LOOKUP_TX */
	__le16 src;
	__le32 act;

	/* Bit 0:1 - Action type */
#घोषणा ICE_SINGLE_ACT_TYPE_S	0x00
#घोषणा ICE_SINGLE_ACT_TYPE_M	(0x3 << ICE_SINGLE_ACT_TYPE_S)

	/* Bit 2 - Loop back enable
	 * Bit 3 - LAN enable
	 */
#घोषणा ICE_SINGLE_ACT_LB_ENABLE	BIT(2)
#घोषणा ICE_SINGLE_ACT_LAN_ENABLE	BIT(3)

	/* Action type = 0 - Forward to VSI or VSI list */
#घोषणा ICE_SINGLE_ACT_VSI_FORWARDING	0x0

#घोषणा ICE_SINGLE_ACT_VSI_ID_S		4
#घोषणा ICE_SINGLE_ACT_VSI_ID_M		(0x3FF << ICE_SINGLE_ACT_VSI_ID_S)
#घोषणा ICE_SINGLE_ACT_VSI_LIST_ID_S	4
#घोषणा ICE_SINGLE_ACT_VSI_LIST_ID_M	(0x3FF << ICE_SINGLE_ACT_VSI_LIST_ID_S)
	/* This bit needs to be set अगर action is क्रमward to VSI list */
#घोषणा ICE_SINGLE_ACT_VSI_LIST		BIT(14)
#घोषणा ICE_SINGLE_ACT_VALID_BIT	BIT(17)
#घोषणा ICE_SINGLE_ACT_DROP		BIT(18)

	/* Action type = 1 - Forward to Queue of Queue group */
#घोषणा ICE_SINGLE_ACT_TO_Q		0x1
#घोषणा ICE_SINGLE_ACT_Q_INDEX_S	4
#घोषणा ICE_SINGLE_ACT_Q_INDEX_M	(0x7FF << ICE_SINGLE_ACT_Q_INDEX_S)
#घोषणा ICE_SINGLE_ACT_Q_REGION_S	15
#घोषणा ICE_SINGLE_ACT_Q_REGION_M	(0x7 << ICE_SINGLE_ACT_Q_REGION_S)
#घोषणा ICE_SINGLE_ACT_Q_PRIORITY	BIT(18)

	/* Action type = 2 - Prune */
#घोषणा ICE_SINGLE_ACT_PRUNE		0x2
#घोषणा ICE_SINGLE_ACT_EGRESS		BIT(15)
#घोषणा ICE_SINGLE_ACT_INGRESS		BIT(16)
#घोषणा ICE_SINGLE_ACT_PRUNET		BIT(17)
	/* Bit 18 should be set to 0 क्रम this action */

	/* Action type = 2 - Poपूर्णांकer */
#घोषणा ICE_SINGLE_ACT_PTR		0x2
#घोषणा ICE_SINGLE_ACT_PTR_VAL_S	4
#घोषणा ICE_SINGLE_ACT_PTR_VAL_M	(0x1FFF << ICE_SINGLE_ACT_PTR_VAL_S)
	/* Bit 18 should be set to 1 */
#घोषणा ICE_SINGLE_ACT_PTR_BIT		BIT(18)

	/* Action type = 3 - Other actions. Last two bits
	 * are other action identअगरier
	 */
#घोषणा ICE_SINGLE_ACT_OTHER_ACTS		0x3
#घोषणा ICE_SINGLE_OTHER_ACT_IDENTIFIER_S	17
#घोषणा ICE_SINGLE_OTHER_ACT_IDENTIFIER_M	\
				(0x3 << ICE_SINGLE_OTHER_ACT_IDENTIFIER_S)

	/* Bit 17:18 - Defines other actions */
	/* Other action = 0 - Mirror VSI */
#घोषणा ICE_SINGLE_OTHER_ACT_MIRROR		0
#घोषणा ICE_SINGLE_ACT_MIRROR_VSI_ID_S	4
#घोषणा ICE_SINGLE_ACT_MIRROR_VSI_ID_M	\
				(0x3FF << ICE_SINGLE_ACT_MIRROR_VSI_ID_S)

	/* Other action = 3 - Set Stat count */
#घोषणा ICE_SINGLE_OTHER_ACT_STAT_COUNT		3
#घोषणा ICE_SINGLE_ACT_STAT_COUNT_INDEX_S	4
#घोषणा ICE_SINGLE_ACT_STAT_COUNT_INDEX_M	\
				(0x7F << ICE_SINGLE_ACT_STAT_COUNT_INDEX_S)

	__le16 index; /* The index of the rule in the lookup table */
	/* Length and values of the header to be matched per recipe or
	 * lookup-type
	 */
	__le16 hdr_len;
	u8 hdr[];
पूर्ण;

/* Add/Update/Remove large action command/response entry
 * "index" is वापसed as part of a response to a successful Add command, and
 * can be used to identअगरy the action क्रम Update/Get/Remove commands.
 */
काष्ठा ice_sw_rule_lg_act अणु
	__le16 index; /* Index in large action table */
	__le16 size;
	/* Max number of large actions */
#घोषणा ICE_MAX_LG_ACT	4
	/* Bit 0:1 - Action type */
#घोषणा ICE_LG_ACT_TYPE_S	0
#घोषणा ICE_LG_ACT_TYPE_M	(0x7 << ICE_LG_ACT_TYPE_S)

	/* Action type = 0 - Forward to VSI or VSI list */
#घोषणा ICE_LG_ACT_VSI_FORWARDING	0
#घोषणा ICE_LG_ACT_VSI_ID_S		3
#घोषणा ICE_LG_ACT_VSI_ID_M		(0x3FF << ICE_LG_ACT_VSI_ID_S)
#घोषणा ICE_LG_ACT_VSI_LIST_ID_S	3
#घोषणा ICE_LG_ACT_VSI_LIST_ID_M	(0x3FF << ICE_LG_ACT_VSI_LIST_ID_S)
	/* This bit needs to be set अगर action is क्रमward to VSI list */
#घोषणा ICE_LG_ACT_VSI_LIST		BIT(13)

#घोषणा ICE_LG_ACT_VALID_BIT		BIT(16)

	/* Action type = 1 - Forward to Queue of Queue group */
#घोषणा ICE_LG_ACT_TO_Q			0x1
#घोषणा ICE_LG_ACT_Q_INDEX_S		3
#घोषणा ICE_LG_ACT_Q_INDEX_M		(0x7FF << ICE_LG_ACT_Q_INDEX_S)
#घोषणा ICE_LG_ACT_Q_REGION_S		14
#घोषणा ICE_LG_ACT_Q_REGION_M		(0x7 << ICE_LG_ACT_Q_REGION_S)
#घोषणा ICE_LG_ACT_Q_PRIORITY_SET	BIT(17)

	/* Action type = 2 - Prune */
#घोषणा ICE_LG_ACT_PRUNE		0x2
#घोषणा ICE_LG_ACT_EGRESS		BIT(14)
#घोषणा ICE_LG_ACT_INGRESS		BIT(15)
#घोषणा ICE_LG_ACT_PRUNET		BIT(16)

	/* Action type = 3 - Mirror VSI */
#घोषणा ICE_LG_OTHER_ACT_MIRROR		0x3
#घोषणा ICE_LG_ACT_MIRROR_VSI_ID_S	3
#घोषणा ICE_LG_ACT_MIRROR_VSI_ID_M	(0x3FF << ICE_LG_ACT_MIRROR_VSI_ID_S)

	/* Action type = 5 - Generic Value */
#घोषणा ICE_LG_ACT_GENERIC		0x5
#घोषणा ICE_LG_ACT_GENERIC_VALUE_S	3
#घोषणा ICE_LG_ACT_GENERIC_VALUE_M	(0xFFFF << ICE_LG_ACT_GENERIC_VALUE_S)
#घोषणा ICE_LG_ACT_GENERIC_OFFSET_S	19
#घोषणा ICE_LG_ACT_GENERIC_OFFSET_M	(0x7 << ICE_LG_ACT_GENERIC_OFFSET_S)
#घोषणा ICE_LG_ACT_GENERIC_PRIORITY_S	22
#घोषणा ICE_LG_ACT_GENERIC_PRIORITY_M	(0x7 << ICE_LG_ACT_GENERIC_PRIORITY_S)
#घोषणा ICE_LG_ACT_GENERIC_OFF_RX_DESC_PROF_IDX	7

	/* Action = 7 - Set Stat count */
#घोषणा ICE_LG_ACT_STAT_COUNT		0x7
#घोषणा ICE_LG_ACT_STAT_COUNT_S		3
#घोषणा ICE_LG_ACT_STAT_COUNT_M		(0x7F << ICE_LG_ACT_STAT_COUNT_S)
	__le32 act[]; /* array of size क्रम actions */
पूर्ण;

/* Add/Update/Remove VSI list command/response entry
 * "index" is वापसed as part of a response to a successful Add command, and
 * can be used to identअगरy the VSI list क्रम Update/Get/Remove commands.
 */
काष्ठा ice_sw_rule_vsi_list अणु
	__le16 index; /* Index of VSI/Prune list */
	__le16 number_vsi;
	__le16 vsi[]; /* Array of number_vsi VSI numbers */
पूर्ण;

/* Query VSI list command/response entry */
काष्ठा ice_sw_rule_vsi_list_query अणु
	__le16 index;
	DECLARE_BITMAP(vsi_list, ICE_MAX_VSI);
पूर्ण __packed;

/* Add चयन rule response:
 * Content of वापस buffer is same as the input buffer. The status field and
 * LUT index are updated as part of the response
 */
काष्ठा ice_aqc_sw_rules_elem अणु
	__le16 type; /* Switch rule type, one of T_... */
#घोषणा ICE_AQC_SW_RULES_T_LKUP_RX		0x0
#घोषणा ICE_AQC_SW_RULES_T_LKUP_TX		0x1
#घोषणा ICE_AQC_SW_RULES_T_LG_ACT		0x2
#घोषणा ICE_AQC_SW_RULES_T_VSI_LIST_SET		0x3
#घोषणा ICE_AQC_SW_RULES_T_VSI_LIST_CLEAR	0x4
#घोषणा ICE_AQC_SW_RULES_T_PRUNE_LIST_SET	0x5
#घोषणा ICE_AQC_SW_RULES_T_PRUNE_LIST_CLEAR	0x6
	__le16 status;
	जोड़ अणु
		काष्ठा ice_sw_rule_lkup_rx_tx lkup_tx_rx;
		काष्ठा ice_sw_rule_lg_act lg_act;
		काष्ठा ice_sw_rule_vsi_list vsi_list;
		काष्ठा ice_sw_rule_vsi_list_query vsi_list_query;
	पूर्ण __packed pdata;
पूर्ण;

/* Get Default Topology (indirect 0x0400) */
काष्ठा ice_aqc_get_topo अणु
	u8 port_num;
	u8 num_branches;
	__le16 reserved1;
	__le32 reserved2;
	__le32 addr_high;
	__le32 addr_low;
पूर्ण;

/* Update TSE (indirect 0x0403)
 * Get TSE (indirect 0x0404)
 * Add TSE (indirect 0x0401)
 * Delete TSE (indirect 0x040F)
 * Move TSE (indirect 0x0408)
 * Suspend Nodes (indirect 0x0409)
 * Resume Nodes (indirect 0x040A)
 */
काष्ठा ice_aqc_sched_elem_cmd अणु
	__le16 num_elem_req;	/* Used by commands */
	__le16 num_elem_resp;	/* Used by responses */
	__le32 reserved;
	__le32 addr_high;
	__le32 addr_low;
पूर्ण;

काष्ठा ice_aqc_txsched_move_grp_info_hdr अणु
	__le32 src_parent_teid;
	__le32 dest_parent_teid;
	__le16 num_elems;
	__le16 reserved;
पूर्ण;

काष्ठा ice_aqc_move_elem अणु
	काष्ठा ice_aqc_txsched_move_grp_info_hdr hdr;
	__le32 teid[];
पूर्ण;

काष्ठा ice_aqc_elem_info_bw अणु
	__le16 bw_profile_idx;
	__le16 bw_alloc;
पूर्ण;

काष्ठा ice_aqc_txsched_elem अणु
	u8 elem_type; /* Special field, reserved क्रम some aq calls */
#घोषणा ICE_AQC_ELEM_TYPE_UNDEFINED		0x0
#घोषणा ICE_AQC_ELEM_TYPE_ROOT_PORT		0x1
#घोषणा ICE_AQC_ELEM_TYPE_TC			0x2
#घोषणा ICE_AQC_ELEM_TYPE_SE_GENERIC		0x3
#घोषणा ICE_AQC_ELEM_TYPE_ENTRY_POINT		0x4
#घोषणा ICE_AQC_ELEM_TYPE_LEAF			0x5
#घोषणा ICE_AQC_ELEM_TYPE_SE_PADDED		0x6
	u8 valid_sections;
#घोषणा ICE_AQC_ELEM_VALID_GENERIC		BIT(0)
#घोषणा ICE_AQC_ELEM_VALID_CIR			BIT(1)
#घोषणा ICE_AQC_ELEM_VALID_EIR			BIT(2)
#घोषणा ICE_AQC_ELEM_VALID_SHARED		BIT(3)
	u8 generic;
#घोषणा ICE_AQC_ELEM_GENERIC_MODE_M		0x1
#घोषणा ICE_AQC_ELEM_GENERIC_PRIO_S		0x1
#घोषणा ICE_AQC_ELEM_GENERIC_PRIO_M	(0x7 << ICE_AQC_ELEM_GENERIC_PRIO_S)
#घोषणा ICE_AQC_ELEM_GENERIC_SP_S		0x4
#घोषणा ICE_AQC_ELEM_GENERIC_SP_M	(0x1 << ICE_AQC_ELEM_GENERIC_SP_S)
#घोषणा ICE_AQC_ELEM_GENERIC_ADJUST_VAL_S	0x5
#घोषणा ICE_AQC_ELEM_GENERIC_ADJUST_VAL_M	\
	(0x3 << ICE_AQC_ELEM_GENERIC_ADJUST_VAL_S)
	u8 flags; /* Special field, reserved क्रम some aq calls */
#घोषणा ICE_AQC_ELEM_FLAG_SUSPEND_M		0x1
	काष्ठा ice_aqc_elem_info_bw cir_bw;
	काष्ठा ice_aqc_elem_info_bw eir_bw;
	__le16 srl_id;
	__le16 reserved2;
पूर्ण;

काष्ठा ice_aqc_txsched_elem_data अणु
	__le32 parent_teid;
	__le32 node_teid;
	काष्ठा ice_aqc_txsched_elem data;
पूर्ण;

काष्ठा ice_aqc_txsched_topo_grp_info_hdr अणु
	__le32 parent_teid;
	__le16 num_elems;
	__le16 reserved2;
पूर्ण;

काष्ठा ice_aqc_add_elem अणु
	काष्ठा ice_aqc_txsched_topo_grp_info_hdr hdr;
	काष्ठा ice_aqc_txsched_elem_data generic[];
पूर्ण;

काष्ठा ice_aqc_get_topo_elem अणु
	काष्ठा ice_aqc_txsched_topo_grp_info_hdr hdr;
	काष्ठा ice_aqc_txsched_elem_data
		generic[ICE_AQC_TOPO_MAX_LEVEL_NUM];
पूर्ण;

काष्ठा ice_aqc_delete_elem अणु
	काष्ठा ice_aqc_txsched_topo_grp_info_hdr hdr;
	__le32 teid[];
पूर्ण;

/* Query Port ETS (indirect 0x040E)
 *
 * This indirect command is used to query port TC node configuration.
 */
काष्ठा ice_aqc_query_port_ets अणु
	__le32 port_teid;
	__le32 reserved;
	__le32 addr_high;
	__le32 addr_low;
पूर्ण;

काष्ठा ice_aqc_port_ets_elem अणु
	u8 tc_valid_bits;
	u8 reserved[3];
	/* 3 bits क्रम UP per TC 0-7, 4th byte reserved */
	__le32 up2tc;
	u8 tc_bw_share[8];
	__le32 port_eir_prof_id;
	__le32 port_cir_prof_id;
	/* 3 bits per Node priority to TC 0-7, 4th byte reserved */
	__le32 tc_node_prio;
#घोषणा ICE_TC_NODE_PRIO_S	0x4
	u8 reserved1[4];
	__le32 tc_node_teid[8]; /* Used क्रम response, reserved in command */
पूर्ण;

/* Rate limiting profile क्रम
 * Add RL profile (indirect 0x0410)
 * Query RL profile (indirect 0x0411)
 * Remove RL profile (indirect 0x0415)
 * These indirect commands acts on single or multiple
 * RL profiles with specअगरied data.
 */
काष्ठा ice_aqc_rl_profile अणु
	__le16 num_profiles;
	__le16 num_processed; /* Only क्रम response. Reserved in Command. */
	u8 reserved[4];
	__le32 addr_high;
	__le32 addr_low;
पूर्ण;

काष्ठा ice_aqc_rl_profile_elem अणु
	u8 level;
	u8 flags;
#घोषणा ICE_AQC_RL_PROखाता_TYPE_S	0x0
#घोषणा ICE_AQC_RL_PROखाता_TYPE_M	(0x3 << ICE_AQC_RL_PROखाता_TYPE_S)
#घोषणा ICE_AQC_RL_PROखाता_TYPE_CIR	0
#घोषणा ICE_AQC_RL_PROखाता_TYPE_EIR	1
#घोषणा ICE_AQC_RL_PROखाता_TYPE_SRL	2
/* The following flag is used क्रम Query RL Profile Data */
#घोषणा ICE_AQC_RL_PROखाता_INVAL_S	0x7
#घोषणा ICE_AQC_RL_PROखाता_INVAL_M	(0x1 << ICE_AQC_RL_PROखाता_INVAL_S)

	__le16 profile_id;
	__le16 max_burst_size;
	__le16 rl_multiply;
	__le16 wake_up_calc;
	__le16 rl_encode;
पूर्ण;

/* Query Scheduler Resource Allocation (indirect 0x0412)
 * This indirect command retrieves the scheduler resources allocated by
 * EMP Firmware to the given PF.
 */
काष्ठा ice_aqc_query_txsched_res अणु
	u8 reserved[8];
	__le32 addr_high;
	__le32 addr_low;
पूर्ण;

काष्ठा ice_aqc_generic_sched_props अणु
	__le16 phys_levels;
	__le16 logical_levels;
	u8 flattening_biपंचांगap;
	u8 max_device_cgds;
	u8 max_pf_cgds;
	u8 rsvd0;
	__le16 rdma_qsets;
	u8 rsvd1[22];
पूर्ण;

काष्ठा ice_aqc_layer_props अणु
	u8 logical_layer;
	u8 chunk_size;
	__le16 max_device_nodes;
	__le16 max_pf_nodes;
	u8 rsvd0[4];
	__le16 max_sibl_grp_sz;
	__le16 max_cir_rl_profiles;
	__le16 max_eir_rl_profiles;
	__le16 max_srl_profiles;
	u8 rsvd1[14];
पूर्ण;

काष्ठा ice_aqc_query_txsched_res_resp अणु
	काष्ठा ice_aqc_generic_sched_props sched_props;
	काष्ठा ice_aqc_layer_props layer_props[ICE_AQC_TOPO_MAX_LEVEL_NUM];
पूर्ण;

/* Get PHY capabilities (indirect 0x0600) */
काष्ठा ice_aqc_get_phy_caps अणु
	u8 lport_num;
	u8 reserved;
	__le16 param0;
	/* 18.0 - Report qualअगरied modules */
#घोषणा ICE_AQC_GET_PHY_RQM		BIT(0)
	/* 18.1 - 18.3 : Report mode
	 * 000b - Report NVM capabilities
	 * 001b - Report topology capabilities
	 * 010b - Report SW configured
	 * 100b - Report शेष capabilities
	 */
#घोषणा ICE_AQC_REPORT_MODE_S			1
#घोषणा ICE_AQC_REPORT_MODE_M			(7 << ICE_AQC_REPORT_MODE_S)
#घोषणा ICE_AQC_REPORT_TOPO_CAP_NO_MEDIA	0
#घोषणा ICE_AQC_REPORT_TOPO_CAP_MEDIA		BIT(1)
#घोषणा ICE_AQC_REPORT_ACTIVE_CFG		BIT(2)
#घोषणा ICE_AQC_REPORT_DFLT_CFG		BIT(3)
	__le32 reserved1;
	__le32 addr_high;
	__le32 addr_low;
पूर्ण;

/* This is #घोषणा of PHY type (Extended):
 * The first set of defines is क्रम phy_type_low.
 */
#घोषणा ICE_PHY_TYPE_LOW_100BASE_TX		BIT_ULL(0)
#घोषणा ICE_PHY_TYPE_LOW_100M_SGMII		BIT_ULL(1)
#घोषणा ICE_PHY_TYPE_LOW_1000BASE_T		BIT_ULL(2)
#घोषणा ICE_PHY_TYPE_LOW_1000BASE_SX		BIT_ULL(3)
#घोषणा ICE_PHY_TYPE_LOW_1000BASE_LX		BIT_ULL(4)
#घोषणा ICE_PHY_TYPE_LOW_1000BASE_KX		BIT_ULL(5)
#घोषणा ICE_PHY_TYPE_LOW_1G_SGMII		BIT_ULL(6)
#घोषणा ICE_PHY_TYPE_LOW_2500BASE_T		BIT_ULL(7)
#घोषणा ICE_PHY_TYPE_LOW_2500BASE_X		BIT_ULL(8)
#घोषणा ICE_PHY_TYPE_LOW_2500BASE_KX		BIT_ULL(9)
#घोषणा ICE_PHY_TYPE_LOW_5GBASE_T		BIT_ULL(10)
#घोषणा ICE_PHY_TYPE_LOW_5GBASE_KR		BIT_ULL(11)
#घोषणा ICE_PHY_TYPE_LOW_10GBASE_T		BIT_ULL(12)
#घोषणा ICE_PHY_TYPE_LOW_10G_SFI_DA		BIT_ULL(13)
#घोषणा ICE_PHY_TYPE_LOW_10GBASE_SR		BIT_ULL(14)
#घोषणा ICE_PHY_TYPE_LOW_10GBASE_LR		BIT_ULL(15)
#घोषणा ICE_PHY_TYPE_LOW_10GBASE_KR_CR1		BIT_ULL(16)
#घोषणा ICE_PHY_TYPE_LOW_10G_SFI_AOC_ACC	BIT_ULL(17)
#घोषणा ICE_PHY_TYPE_LOW_10G_SFI_C2C		BIT_ULL(18)
#घोषणा ICE_PHY_TYPE_LOW_25GBASE_T		BIT_ULL(19)
#घोषणा ICE_PHY_TYPE_LOW_25GBASE_CR		BIT_ULL(20)
#घोषणा ICE_PHY_TYPE_LOW_25GBASE_CR_S		BIT_ULL(21)
#घोषणा ICE_PHY_TYPE_LOW_25GBASE_CR1		BIT_ULL(22)
#घोषणा ICE_PHY_TYPE_LOW_25GBASE_SR		BIT_ULL(23)
#घोषणा ICE_PHY_TYPE_LOW_25GBASE_LR		BIT_ULL(24)
#घोषणा ICE_PHY_TYPE_LOW_25GBASE_KR		BIT_ULL(25)
#घोषणा ICE_PHY_TYPE_LOW_25GBASE_KR_S		BIT_ULL(26)
#घोषणा ICE_PHY_TYPE_LOW_25GBASE_KR1		BIT_ULL(27)
#घोषणा ICE_PHY_TYPE_LOW_25G_AUI_AOC_ACC	BIT_ULL(28)
#घोषणा ICE_PHY_TYPE_LOW_25G_AUI_C2C		BIT_ULL(29)
#घोषणा ICE_PHY_TYPE_LOW_40GBASE_CR4		BIT_ULL(30)
#घोषणा ICE_PHY_TYPE_LOW_40GBASE_SR4		BIT_ULL(31)
#घोषणा ICE_PHY_TYPE_LOW_40GBASE_LR4		BIT_ULL(32)
#घोषणा ICE_PHY_TYPE_LOW_40GBASE_KR4		BIT_ULL(33)
#घोषणा ICE_PHY_TYPE_LOW_40G_XLAUI_AOC_ACC	BIT_ULL(34)
#घोषणा ICE_PHY_TYPE_LOW_40G_XLAUI		BIT_ULL(35)
#घोषणा ICE_PHY_TYPE_LOW_50GBASE_CR2		BIT_ULL(36)
#घोषणा ICE_PHY_TYPE_LOW_50GBASE_SR2		BIT_ULL(37)
#घोषणा ICE_PHY_TYPE_LOW_50GBASE_LR2		BIT_ULL(38)
#घोषणा ICE_PHY_TYPE_LOW_50GBASE_KR2		BIT_ULL(39)
#घोषणा ICE_PHY_TYPE_LOW_50G_LAUI2_AOC_ACC	BIT_ULL(40)
#घोषणा ICE_PHY_TYPE_LOW_50G_LAUI2		BIT_ULL(41)
#घोषणा ICE_PHY_TYPE_LOW_50G_AUI2_AOC_ACC	BIT_ULL(42)
#घोषणा ICE_PHY_TYPE_LOW_50G_AUI2		BIT_ULL(43)
#घोषणा ICE_PHY_TYPE_LOW_50GBASE_CP		BIT_ULL(44)
#घोषणा ICE_PHY_TYPE_LOW_50GBASE_SR		BIT_ULL(45)
#घोषणा ICE_PHY_TYPE_LOW_50GBASE_FR		BIT_ULL(46)
#घोषणा ICE_PHY_TYPE_LOW_50GBASE_LR		BIT_ULL(47)
#घोषणा ICE_PHY_TYPE_LOW_50GBASE_KR_PAM4	BIT_ULL(48)
#घोषणा ICE_PHY_TYPE_LOW_50G_AUI1_AOC_ACC	BIT_ULL(49)
#घोषणा ICE_PHY_TYPE_LOW_50G_AUI1		BIT_ULL(50)
#घोषणा ICE_PHY_TYPE_LOW_100GBASE_CR4		BIT_ULL(51)
#घोषणा ICE_PHY_TYPE_LOW_100GBASE_SR4		BIT_ULL(52)
#घोषणा ICE_PHY_TYPE_LOW_100GBASE_LR4		BIT_ULL(53)
#घोषणा ICE_PHY_TYPE_LOW_100GBASE_KR4		BIT_ULL(54)
#घोषणा ICE_PHY_TYPE_LOW_100G_CAUI4_AOC_ACC	BIT_ULL(55)
#घोषणा ICE_PHY_TYPE_LOW_100G_CAUI4		BIT_ULL(56)
#घोषणा ICE_PHY_TYPE_LOW_100G_AUI4_AOC_ACC	BIT_ULL(57)
#घोषणा ICE_PHY_TYPE_LOW_100G_AUI4		BIT_ULL(58)
#घोषणा ICE_PHY_TYPE_LOW_100GBASE_CR_PAM4	BIT_ULL(59)
#घोषणा ICE_PHY_TYPE_LOW_100GBASE_KR_PAM4	BIT_ULL(60)
#घोषणा ICE_PHY_TYPE_LOW_100GBASE_CP2		BIT_ULL(61)
#घोषणा ICE_PHY_TYPE_LOW_100GBASE_SR2		BIT_ULL(62)
#घोषणा ICE_PHY_TYPE_LOW_100GBASE_DR		BIT_ULL(63)
#घोषणा ICE_PHY_TYPE_LOW_MAX_INDEX		63
/* The second set of defines is क्रम phy_type_high. */
#घोषणा ICE_PHY_TYPE_HIGH_100GBASE_KR2_PAM4	BIT_ULL(0)
#घोषणा ICE_PHY_TYPE_HIGH_100G_CAUI2_AOC_ACC	BIT_ULL(1)
#घोषणा ICE_PHY_TYPE_HIGH_100G_CAUI2		BIT_ULL(2)
#घोषणा ICE_PHY_TYPE_HIGH_100G_AUI2_AOC_ACC	BIT_ULL(3)
#घोषणा ICE_PHY_TYPE_HIGH_100G_AUI2		BIT_ULL(4)
#घोषणा ICE_PHY_TYPE_HIGH_MAX_INDEX		5

काष्ठा ice_aqc_get_phy_caps_data अणु
	__le64 phy_type_low; /* Use values from ICE_PHY_TYPE_LOW_* */
	__le64 phy_type_high; /* Use values from ICE_PHY_TYPE_HIGH_* */
	u8 caps;
#घोषणा ICE_AQC_PHY_EN_TX_LINK_PAUSE			BIT(0)
#घोषणा ICE_AQC_PHY_EN_RX_LINK_PAUSE			BIT(1)
#घोषणा ICE_AQC_PHY_LOW_POWER_MODE			BIT(2)
#घोषणा ICE_AQC_PHY_EN_LINK				BIT(3)
#घोषणा ICE_AQC_PHY_AN_MODE				BIT(4)
#घोषणा ICE_AQC_GET_PHY_EN_MOD_QUAL			BIT(5)
#घोषणा ICE_AQC_PHY_EN_AUTO_FEC				BIT(7)
#घोषणा ICE_AQC_PHY_CAPS_MASK				ICE_M(0xff, 0)
	u8 low_घातer_ctrl_an;
#घोषणा ICE_AQC_PHY_EN_D3COLD_LOW_POWER_AUTONEG		BIT(0)
#घोषणा ICE_AQC_PHY_AN_EN_CLAUSE28			BIT(1)
#घोषणा ICE_AQC_PHY_AN_EN_CLAUSE73			BIT(2)
#घोषणा ICE_AQC_PHY_AN_EN_CLAUSE37			BIT(3)
	__le16 eee_cap;
#घोषणा ICE_AQC_PHY_EEE_EN_100BASE_TX			BIT(0)
#घोषणा ICE_AQC_PHY_EEE_EN_1000BASE_T			BIT(1)
#घोषणा ICE_AQC_PHY_EEE_EN_10GBASE_T			BIT(2)
#घोषणा ICE_AQC_PHY_EEE_EN_1000BASE_KX			BIT(3)
#घोषणा ICE_AQC_PHY_EEE_EN_10GBASE_KR			BIT(4)
#घोषणा ICE_AQC_PHY_EEE_EN_25GBASE_KR			BIT(5)
#घोषणा ICE_AQC_PHY_EEE_EN_40GBASE_KR4			BIT(6)
	__le16 eeer_value;
	u8 phy_id_oui[4]; /* PHY/Module ID connected on the port */
	u8 phy_fw_ver[8];
	u8 link_fec_options;
#घोषणा ICE_AQC_PHY_FEC_10G_KR_40G_KR4_EN		BIT(0)
#घोषणा ICE_AQC_PHY_FEC_10G_KR_40G_KR4_REQ		BIT(1)
#घोषणा ICE_AQC_PHY_FEC_25G_RS_528_REQ			BIT(2)
#घोषणा ICE_AQC_PHY_FEC_25G_KR_REQ			BIT(3)
#घोषणा ICE_AQC_PHY_FEC_25G_RS_544_REQ			BIT(4)
#घोषणा ICE_AQC_PHY_FEC_25G_RS_CLAUSE91_EN		BIT(6)
#घोषणा ICE_AQC_PHY_FEC_25G_KR_CLAUSE74_EN		BIT(7)
#घोषणा ICE_AQC_PHY_FEC_MASK				ICE_M(0xdf, 0)
	u8 module_compliance_enक्रमcement;
#घोषणा ICE_AQC_MOD_ENFORCE_STRICT_MODE			BIT(0)
	u8 extended_compliance_code;
#घोषणा ICE_MODULE_TYPE_TOTAL_BYTE			3
	u8 module_type[ICE_MODULE_TYPE_TOTAL_BYTE];
#घोषणा ICE_AQC_MOD_TYPE_BYTE0_SFP_PLUS			0xA0
#घोषणा ICE_AQC_MOD_TYPE_BYTE0_QSFP_PLUS		0x80
#घोषणा ICE_AQC_MOD_TYPE_IDENT				1
#घोषणा ICE_AQC_MOD_TYPE_BYTE1_SFP_PLUS_CU_PASSIVE	BIT(0)
#घोषणा ICE_AQC_MOD_TYPE_BYTE1_SFP_PLUS_CU_ACTIVE	BIT(1)
#घोषणा ICE_AQC_MOD_TYPE_BYTE1_10G_BASE_SR		BIT(4)
#घोषणा ICE_AQC_MOD_TYPE_BYTE1_10G_BASE_LR		BIT(5)
#घोषणा ICE_AQC_MOD_TYPE_BYTE1_10G_BASE_LRM		BIT(6)
#घोषणा ICE_AQC_MOD_TYPE_BYTE1_10G_BASE_ER		BIT(7)
#घोषणा ICE_AQC_MOD_TYPE_BYTE2_SFP_PLUS			0xA0
#घोषणा ICE_AQC_MOD_TYPE_BYTE2_QSFP_PLUS		0x86
	u8 qualअगरied_module_count;
	u8 rsvd2[7];	/* Bytes 47:41 reserved */
#घोषणा ICE_AQC_QUAL_MOD_COUNT_MAX			16
	काष्ठा अणु
		u8 v_oui[3];
		u8 rsvd3;
		u8 v_part[16];
		__le32 v_rev;
		__le64 rsvd4;
	पूर्ण qual_modules[ICE_AQC_QUAL_MOD_COUNT_MAX];
पूर्ण;

/* Set PHY capabilities (direct 0x0601)
 * NOTE: This command must be followed by setup link and restart स्वतः-neg
 */
काष्ठा ice_aqc_set_phy_cfg अणु
	u8 lport_num;
	u8 reserved[7];
	__le32 addr_high;
	__le32 addr_low;
पूर्ण;

/* Set PHY config command data काष्ठाure */
काष्ठा ice_aqc_set_phy_cfg_data अणु
	__le64 phy_type_low; /* Use values from ICE_PHY_TYPE_LOW_* */
	__le64 phy_type_high; /* Use values from ICE_PHY_TYPE_HIGH_* */
	u8 caps;
#घोषणा ICE_AQ_PHY_ENA_VALID_MASK	ICE_M(0xef, 0)
#घोषणा ICE_AQ_PHY_ENA_TX_PAUSE_ABILITY	BIT(0)
#घोषणा ICE_AQ_PHY_ENA_RX_PAUSE_ABILITY	BIT(1)
#घोषणा ICE_AQ_PHY_ENA_LOW_POWER	BIT(2)
#घोषणा ICE_AQ_PHY_ENA_LINK		BIT(3)
#घोषणा ICE_AQ_PHY_ENA_AUTO_LINK_UPDT	BIT(5)
#घोषणा ICE_AQ_PHY_ENA_LESM		BIT(6)
#घोषणा ICE_AQ_PHY_ENA_AUTO_FEC		BIT(7)
	u8 low_घातer_ctrl_an;
	__le16 eee_cap; /* Value from ice_aqc_get_phy_caps */
	__le16 eeer_value;
	u8 link_fec_opt; /* Use defines from ice_aqc_get_phy_caps */
	u8 module_compliance_enक्रमcement;
पूर्ण;

/* Set MAC Config command data काष्ठाure (direct 0x0603) */
काष्ठा ice_aqc_set_mac_cfg अणु
	__le16 max_frame_size;
	u8 params;
#घोषणा ICE_AQ_SET_MAC_PACE_S		3
#घोषणा ICE_AQ_SET_MAC_PACE_M		(0xF << ICE_AQ_SET_MAC_PACE_S)
#घोषणा ICE_AQ_SET_MAC_PACE_TYPE_M	BIT(7)
#घोषणा ICE_AQ_SET_MAC_PACE_TYPE_RATE	0
#घोषणा ICE_AQ_SET_MAC_PACE_TYPE_FIXED	ICE_AQ_SET_MAC_PACE_TYPE_M
	u8 tx_पंचांगr_priority;
	__le16 tx_पंचांगr_value;
	__le16 fc_refresh_threshold;
	u8 drop_opts;
#घोषणा ICE_AQ_SET_MAC_AUTO_DROP_MASK		BIT(0)
#घोषणा ICE_AQ_SET_MAC_AUTO_DROP_NONE		0
#घोषणा ICE_AQ_SET_MAC_AUTO_DROP_BLOCKING_PKTS	BIT(0)
	u8 reserved[7];
पूर्ण;

/* Restart AN command data काष्ठाure (direct 0x0605)
 * Also used क्रम response, with only the lport_num field present.
 */
काष्ठा ice_aqc_restart_an अणु
	u8 lport_num;
	u8 reserved;
	u8 cmd_flags;
#घोषणा ICE_AQC_RESTART_AN_LINK_RESTART	BIT(1)
#घोषणा ICE_AQC_RESTART_AN_LINK_ENABLE	BIT(2)
	u8 reserved2[13];
पूर्ण;

/* Get link status (indirect 0x0607), also used क्रम Link Status Event */
काष्ठा ice_aqc_get_link_status अणु
	u8 lport_num;
	u8 reserved;
	__le16 cmd_flags;
#घोषणा ICE_AQ_LSE_M			0x3
#घोषणा ICE_AQ_LSE_NOP			0x0
#घोषणा ICE_AQ_LSE_DIS			0x2
#घोषणा ICE_AQ_LSE_ENA			0x3
	/* only response uses this flag */
#घोषणा ICE_AQ_LSE_IS_ENABLED		0x1
	__le32 reserved2;
	__le32 addr_high;
	__le32 addr_low;
पूर्ण;

/* Get link status response data काष्ठाure, also used क्रम Link Status Event */
काष्ठा ice_aqc_get_link_status_data अणु
	u8 topo_media_conflict;
#घोषणा ICE_AQ_LINK_TOPO_CONFLICT	BIT(0)
#घोषणा ICE_AQ_LINK_MEDIA_CONFLICT	BIT(1)
#घोषणा ICE_AQ_LINK_TOPO_CORRUPT	BIT(2)
#घोषणा ICE_AQ_LINK_TOPO_UNREACH_PRT	BIT(4)
#घोषणा ICE_AQ_LINK_TOPO_UNDRUTIL_PRT	BIT(5)
#घोषणा ICE_AQ_LINK_TOPO_UNDRUTIL_MEDIA	BIT(6)
#घोषणा ICE_AQ_LINK_TOPO_UNSUPP_MEDIA	BIT(7)
	u8 reserved1;
	u8 link_info;
#घोषणा ICE_AQ_LINK_UP			BIT(0)	/* Link Status */
#घोषणा ICE_AQ_LINK_FAULT		BIT(1)
#घोषणा ICE_AQ_LINK_FAULT_TX		BIT(2)
#घोषणा ICE_AQ_LINK_FAULT_RX		BIT(3)
#घोषणा ICE_AQ_LINK_FAULT_REMOTE	BIT(4)
#घोषणा ICE_AQ_LINK_UP_PORT		BIT(5)	/* External Port Link Status */
#घोषणा ICE_AQ_MEDIA_AVAILABLE		BIT(6)
#घोषणा ICE_AQ_SIGNAL_DETECT		BIT(7)
	u8 an_info;
#घोषणा ICE_AQ_AN_COMPLETED		BIT(0)
#घोषणा ICE_AQ_LP_AN_ABILITY		BIT(1)
#घोषणा ICE_AQ_PD_FAULT			BIT(2)	/* Parallel Detection Fault */
#घोषणा ICE_AQ_FEC_EN			BIT(3)
#घोषणा ICE_AQ_PHY_LOW_POWER		BIT(4)	/* Low Power State */
#घोषणा ICE_AQ_LINK_PAUSE_TX		BIT(5)
#घोषणा ICE_AQ_LINK_PAUSE_RX		BIT(6)
#घोषणा ICE_AQ_QUALIFIED_MODULE		BIT(7)
	u8 ext_info;
#घोषणा ICE_AQ_LINK_PHY_TEMP_ALARM	BIT(0)
#घोषणा ICE_AQ_LINK_EXCESSIVE_ERRORS	BIT(1)	/* Excessive Link Errors */
	/* Port Tx Suspended */
#घोषणा ICE_AQ_LINK_TX_S		2
#घोषणा ICE_AQ_LINK_TX_M		(0x03 << ICE_AQ_LINK_TX_S)
#घोषणा ICE_AQ_LINK_TX_ACTIVE		0
#घोषणा ICE_AQ_LINK_TX_DRAINED		1
#घोषणा ICE_AQ_LINK_TX_FLUSHED		3
	u8 reserved2;
	__le16 max_frame_size;
	u8 cfg;
#घोषणा ICE_AQ_LINK_25G_KR_FEC_EN	BIT(0)
#घोषणा ICE_AQ_LINK_25G_RS_528_FEC_EN	BIT(1)
#घोषणा ICE_AQ_LINK_25G_RS_544_FEC_EN	BIT(2)
#घोषणा ICE_AQ_FEC_MASK			ICE_M(0x7, 0)
	/* Pacing Config */
#घोषणा ICE_AQ_CFG_PACING_S		3
#घोषणा ICE_AQ_CFG_PACING_M		(0xF << ICE_AQ_CFG_PACING_S)
#घोषणा ICE_AQ_CFG_PACING_TYPE_M	BIT(7)
#घोषणा ICE_AQ_CFG_PACING_TYPE_AVG	0
#घोषणा ICE_AQ_CFG_PACING_TYPE_FIXED	ICE_AQ_CFG_PACING_TYPE_M
	/* External Device Power Ability */
	u8 घातer_desc;
#घोषणा ICE_AQ_PWR_CLASS_M		0x3
#घोषणा ICE_AQ_LINK_PWR_BASET_LOW_HIGH	0
#घोषणा ICE_AQ_LINK_PWR_BASET_HIGH	1
#घोषणा ICE_AQ_LINK_PWR_QSFP_CLASS_1	0
#घोषणा ICE_AQ_LINK_PWR_QSFP_CLASS_2	1
#घोषणा ICE_AQ_LINK_PWR_QSFP_CLASS_3	2
#घोषणा ICE_AQ_LINK_PWR_QSFP_CLASS_4	3
	__le16 link_speed;
#घोषणा ICE_AQ_LINK_SPEED_M		0x7FF
#घोषणा ICE_AQ_LINK_SPEED_10MB		BIT(0)
#घोषणा ICE_AQ_LINK_SPEED_100MB		BIT(1)
#घोषणा ICE_AQ_LINK_SPEED_1000MB	BIT(2)
#घोषणा ICE_AQ_LINK_SPEED_2500MB	BIT(3)
#घोषणा ICE_AQ_LINK_SPEED_5GB		BIT(4)
#घोषणा ICE_AQ_LINK_SPEED_10GB		BIT(5)
#घोषणा ICE_AQ_LINK_SPEED_20GB		BIT(6)
#घोषणा ICE_AQ_LINK_SPEED_25GB		BIT(7)
#घोषणा ICE_AQ_LINK_SPEED_40GB		BIT(8)
#घोषणा ICE_AQ_LINK_SPEED_50GB		BIT(9)
#घोषणा ICE_AQ_LINK_SPEED_100GB		BIT(10)
#घोषणा ICE_AQ_LINK_SPEED_UNKNOWN	BIT(15)
	__le32 reserved3; /* Aligns next field to 8-byte boundary */
	__le64 phy_type_low; /* Use values from ICE_PHY_TYPE_LOW_* */
	__le64 phy_type_high; /* Use values from ICE_PHY_TYPE_HIGH_* */
पूर्ण;

/* Set event mask command (direct 0x0613) */
काष्ठा ice_aqc_set_event_mask अणु
	u8	lport_num;
	u8	reserved[7];
	__le16	event_mask;
#घोषणा ICE_AQ_LINK_EVENT_UPDOWN		BIT(1)
#घोषणा ICE_AQ_LINK_EVENT_MEDIA_NA		BIT(2)
#घोषणा ICE_AQ_LINK_EVENT_LINK_FAULT		BIT(3)
#घोषणा ICE_AQ_LINK_EVENT_PHY_TEMP_ALARM	BIT(4)
#घोषणा ICE_AQ_LINK_EVENT_EXCESSIVE_ERRORS	BIT(5)
#घोषणा ICE_AQ_LINK_EVENT_SIGNAL_DETECT		BIT(6)
#घोषणा ICE_AQ_LINK_EVENT_AN_COMPLETED		BIT(7)
#घोषणा ICE_AQ_LINK_EVENT_MODULE_QUAL_FAIL	BIT(8)
#घोषणा ICE_AQ_LINK_EVENT_PORT_TX_SUSPENDED	BIT(9)
	u8	reserved1[6];
पूर्ण;

/* Set MAC Loopback command (direct 0x0620) */
काष्ठा ice_aqc_set_mac_lb अणु
	u8 lb_mode;
#घोषणा ICE_AQ_MAC_LB_EN		BIT(0)
#घोषणा ICE_AQ_MAC_LB_OSC_CLK		BIT(1)
	u8 reserved[15];
पूर्ण;

काष्ठा ice_aqc_link_topo_addr अणु
	u8 lport_num;
	u8 lport_num_valid;
#घोषणा ICE_AQC_LINK_TOPO_PORT_NUM_VALID	BIT(0)
	u8 node_type_ctx;
#घोषणा ICE_AQC_LINK_TOPO_NODE_TYPE_S		0
#घोषणा ICE_AQC_LINK_TOPO_NODE_TYPE_M	(0xF << ICE_AQC_LINK_TOPO_NODE_TYPE_S)
#घोषणा ICE_AQC_LINK_TOPO_NODE_TYPE_PHY		0
#घोषणा ICE_AQC_LINK_TOPO_NODE_TYPE_GPIO_CTRL	1
#घोषणा ICE_AQC_LINK_TOPO_NODE_TYPE_MUX_CTRL	2
#घोषणा ICE_AQC_LINK_TOPO_NODE_TYPE_LED_CTRL	3
#घोषणा ICE_AQC_LINK_TOPO_NODE_TYPE_LED		4
#घोषणा ICE_AQC_LINK_TOPO_NODE_TYPE_THERMAL	5
#घोषणा ICE_AQC_LINK_TOPO_NODE_TYPE_CAGE	6
#घोषणा ICE_AQC_LINK_TOPO_NODE_TYPE_MEZZ	7
#घोषणा ICE_AQC_LINK_TOPO_NODE_TYPE_ID_EEPROM	8
#घोषणा ICE_AQC_LINK_TOPO_NODE_CTX_S		4
#घोषणा ICE_AQC_LINK_TOPO_NODE_CTX_M		\
				(0xF << ICE_AQC_LINK_TOPO_NODE_CTX_S)
#घोषणा ICE_AQC_LINK_TOPO_NODE_CTX_GLOBAL	0
#घोषणा ICE_AQC_LINK_TOPO_NODE_CTX_BOARD	1
#घोषणा ICE_AQC_LINK_TOPO_NODE_CTX_PORT		2
#घोषणा ICE_AQC_LINK_TOPO_NODE_CTX_NODE		3
#घोषणा ICE_AQC_LINK_TOPO_NODE_CTX_PROVIDED	4
#घोषणा ICE_AQC_LINK_TOPO_NODE_CTX_OVERRIDE	5
	u8 index;
	__le16 handle;
#घोषणा ICE_AQC_LINK_TOPO_HANDLE_S	0
#घोषणा ICE_AQC_LINK_TOPO_HANDLE_M	(0x3FF << ICE_AQC_LINK_TOPO_HANDLE_S)
/* Used to decode the handle field */
#घोषणा ICE_AQC_LINK_TOPO_HANDLE_BRD_TYPE_M	BIT(9)
#घोषणा ICE_AQC_LINK_TOPO_HANDLE_BRD_TYPE_LOM	BIT(9)
#घोषणा ICE_AQC_LINK_TOPO_HANDLE_BRD_TYPE_MEZZ	0
#घोषणा ICE_AQC_LINK_TOPO_HANDLE_NODE_S		0
/* In हाल of a Mezzanine type */
#घोषणा ICE_AQC_LINK_TOPO_HANDLE_MEZZ_NODE_M	\
				(0x3F << ICE_AQC_LINK_TOPO_HANDLE_NODE_S)
#घोषणा ICE_AQC_LINK_TOPO_HANDLE_MEZZ_S	6
#घोषणा ICE_AQC_LINK_TOPO_HANDLE_MEZZ_M	(0x7 << ICE_AQC_LINK_TOPO_HANDLE_MEZZ_S)
/* In हाल of a LOM type */
#घोषणा ICE_AQC_LINK_TOPO_HANDLE_LOM_NODE_M	\
				(0x1FF << ICE_AQC_LINK_TOPO_HANDLE_NODE_S)
पूर्ण;

/* Get Link Topology Handle (direct, 0x06E0) */
काष्ठा ice_aqc_get_link_topo अणु
	काष्ठा ice_aqc_link_topo_addr addr;
	u8 node_part_num;
	u8 rsvd[9];
पूर्ण;

/* Set Port Identअगरication LED (direct, 0x06E9) */
काष्ठा ice_aqc_set_port_id_led अणु
	u8 lport_num;
	u8 lport_num_valid;
	u8 ident_mode;
#घोषणा ICE_AQC_PORT_IDENT_LED_BLINK	BIT(0)
#घोषणा ICE_AQC_PORT_IDENT_LED_ORIG	0
	u8 rsvd[13];
पूर्ण;

/* Read/Write SFF EEPROM command (indirect 0x06EE) */
काष्ठा ice_aqc_sff_eeprom अणु
	u8 lport_num;
	u8 lport_num_valid;
#घोषणा ICE_AQC_SFF_PORT_NUM_VALID	BIT(0)
	__le16 i2c_bus_addr;
#घोषणा ICE_AQC_SFF_I2CBUS_7BIT_M	0x7F
#घोषणा ICE_AQC_SFF_I2CBUS_10BIT_M	0x3FF
#घोषणा ICE_AQC_SFF_I2CBUS_TYPE_M	BIT(10)
#घोषणा ICE_AQC_SFF_I2CBUS_TYPE_7BIT	0
#घोषणा ICE_AQC_SFF_I2CBUS_TYPE_10BIT	ICE_AQC_SFF_I2CBUS_TYPE_M
#घोषणा ICE_AQC_SFF_SET_EEPROM_PAGE_S	11
#घोषणा ICE_AQC_SFF_SET_EEPROM_PAGE_M	(0x3 << ICE_AQC_SFF_SET_EEPROM_PAGE_S)
#घोषणा ICE_AQC_SFF_NO_PAGE_CHANGE	0
#घोषणा ICE_AQC_SFF_SET_23_ON_MISMATCH	1
#घोषणा ICE_AQC_SFF_SET_22_ON_MISMATCH	2
#घोषणा ICE_AQC_SFF_IS_WRITE		BIT(15)
	__le16 i2c_mem_addr;
	__le16 eeprom_page;
#घोषणा  ICE_AQC_SFF_EEPROM_BANK_S 0
#घोषणा  ICE_AQC_SFF_EEPROM_BANK_M (0xFF << ICE_AQC_SFF_EEPROM_BANK_S)
#घोषणा  ICE_AQC_SFF_EEPROM_PAGE_S 8
#घोषणा  ICE_AQC_SFF_EEPROM_PAGE_M (0xFF << ICE_AQC_SFF_EEPROM_PAGE_S)
	__le32 addr_high;
	__le32 addr_low;
पूर्ण;

/* NVM Read command (indirect 0x0701)
 * NVM Erase commands (direct 0x0702)
 * NVM Update commands (indirect 0x0703)
 */
काष्ठा ice_aqc_nvm अणु
#घोषणा ICE_AQC_NVM_MAX_OFFSET		0xFFFFFF
	__le16 offset_low;
	u8 offset_high;
	u8 cmd_flags;
#घोषणा ICE_AQC_NVM_LAST_CMD		BIT(0)
#घोषणा ICE_AQC_NVM_PCIR_REQ		BIT(0)	/* Used by NVM Update reply */
#घोषणा ICE_AQC_NVM_PRESERVATION_S	1
#घोषणा ICE_AQC_NVM_PRESERVATION_M	(3 << ICE_AQC_NVM_PRESERVATION_S)
#घोषणा ICE_AQC_NVM_NO_PRESERVATION	(0 << ICE_AQC_NVM_PRESERVATION_S)
#घोषणा ICE_AQC_NVM_PRESERVE_ALL	BIT(1)
#घोषणा ICE_AQC_NVM_FACTORY_DEFAULT	(2 << ICE_AQC_NVM_PRESERVATION_S)
#घोषणा ICE_AQC_NVM_PRESERVE_SELECTED	(3 << ICE_AQC_NVM_PRESERVATION_S)
#घोषणा ICE_AQC_NVM_ACTIV_SEL_NVM	BIT(3) /* Write Activate/SR Dump only */
#घोषणा ICE_AQC_NVM_ACTIV_SEL_OROM	BIT(4)
#घोषणा ICE_AQC_NVM_ACTIV_SEL_NETLIST	BIT(5)
#घोषणा ICE_AQC_NVM_SPECIAL_UPDATE	BIT(6)
#घोषणा ICE_AQC_NVM_REVERT_LAST_ACTIV	BIT(6) /* Write Activate only */
#घोषणा ICE_AQC_NVM_ACTIV_SEL_MASK	ICE_M(0x7, 3)
#घोषणा ICE_AQC_NVM_FLASH_ONLY		BIT(7)
	__le16 module_typeid;
	__le16 length;
#घोषणा ICE_AQC_NVM_ERASE_LEN	0xFFFF
	__le32 addr_high;
	__le32 addr_low;
पूर्ण;

#घोषणा ICE_AQC_NVM_START_POINT			0

/* NVM Checksum Command (direct, 0x0706) */
काष्ठा ice_aqc_nvm_checksum अणु
	u8 flags;
#घोषणा ICE_AQC_NVM_CHECKSUM_VERIFY	BIT(0)
#घोषणा ICE_AQC_NVM_CHECKSUM_RECALC	BIT(1)
	u8 rsvd;
	__le16 checksum; /* Used only by response */
#घोषणा ICE_AQC_NVM_CHECKSUM_CORRECT	0xBABA
	u8 rsvd2[12];
पूर्ण;

/* Used क्रम NVM Set Package Data command - 0x070A */
काष्ठा ice_aqc_nvm_pkg_data अणु
	u8 reserved[3];
	u8 cmd_flags;
#घोषणा ICE_AQC_NVM_PKG_DELETE		BIT(0) /* used क्रम command call */
#घोषणा ICE_AQC_NVM_PKG_SKIPPED		BIT(0) /* used क्रम command response */

	u32 reserved1;
	__le32 addr_high;
	__le32 addr_low;
पूर्ण;

/* Used क्रम Pass Component Table command - 0x070B */
काष्ठा ice_aqc_nvm_pass_comp_tbl अणु
	u8 component_response; /* Response only */
#घोषणा ICE_AQ_NVM_PASS_COMP_CAN_BE_UPDATED		0x0
#घोषणा ICE_AQ_NVM_PASS_COMP_CAN_MAY_BE_UPDATEABLE	0x1
#घोषणा ICE_AQ_NVM_PASS_COMP_CAN_NOT_BE_UPDATED		0x2
	u8 component_response_code; /* Response only */
#घोषणा ICE_AQ_NVM_PASS_COMP_CAN_BE_UPDATED_CODE	0x0
#घोषणा ICE_AQ_NVM_PASS_COMP_STAMP_IDENTICAL_CODE	0x1
#घोषणा ICE_AQ_NVM_PASS_COMP_STAMP_LOWER		0x2
#घोषणा ICE_AQ_NVM_PASS_COMP_INVALID_STAMP_CODE		0x3
#घोषणा ICE_AQ_NVM_PASS_COMP_CONFLICT_CODE		0x4
#घोषणा ICE_AQ_NVM_PASS_COMP_PRE_REQ_NOT_MET_CODE	0x5
#घोषणा ICE_AQ_NVM_PASS_COMP_NOT_SUPPORTED_CODE		0x6
#घोषणा ICE_AQ_NVM_PASS_COMP_CANNOT_DOWNGRADE_CODE	0x7
#घोषणा ICE_AQ_NVM_PASS_COMP_INCOMPLETE_IMAGE_CODE	0x8
#घोषणा ICE_AQ_NVM_PASS_COMP_VER_STR_IDENTICAL_CODE	0xA
#घोषणा ICE_AQ_NVM_PASS_COMP_VER_STR_LOWER_CODE		0xB
	u8 reserved;
	u8 transfer_flag;
#घोषणा ICE_AQ_NVM_PASS_COMP_TBL_START			0x1
#घोषणा ICE_AQ_NVM_PASS_COMP_TBL_MIDDLE			0x2
#घोषणा ICE_AQ_NVM_PASS_COMP_TBL_END			0x4
#घोषणा ICE_AQ_NVM_PASS_COMP_TBL_START_AND_END		0x5
	__le32 reserved1;
	__le32 addr_high;
	__le32 addr_low;
पूर्ण;

काष्ठा ice_aqc_nvm_comp_tbl अणु
	__le16 comp_class;
#घोषणा NVM_COMP_CLASS_ALL_FW	0x000A

	__le16 comp_id;
#घोषणा NVM_COMP_ID_OROM	0x5
#घोषणा NVM_COMP_ID_NVM		0x6
#घोषणा NVM_COMP_ID_NETLIST	0x8

	u8 comp_class_idx;
#घोषणा FWU_COMP_CLASS_IDX_NOT_USE 0x0

	__le32 comp_cmp_stamp;
	u8 cvs_type;
#घोषणा NVM_CVS_TYPE_ASCII	0x1

	u8 cvs_len;
	u8 cvs[]; /* Component Version String */
पूर्ण __packed;

/* Send to PF command (indirect 0x0801) ID is only used by PF
 *
 * Send to VF command (indirect 0x0802) ID is only used by PF
 *
 */
काष्ठा ice_aqc_pf_vf_msg अणु
	__le32 id;
	u32 reserved;
	__le32 addr_high;
	__le32 addr_low;
पूर्ण;

/* Get LLDP MIB (indirect 0x0A00)
 * Note: This is also used by the LLDP MIB Change Event (0x0A01)
 * as the क्रमmat is the same.
 */
काष्ठा ice_aqc_lldp_get_mib अणु
	u8 type;
#घोषणा ICE_AQ_LLDP_MIB_TYPE_S			0
#घोषणा ICE_AQ_LLDP_MIB_TYPE_M			(0x3 << ICE_AQ_LLDP_MIB_TYPE_S)
#घोषणा ICE_AQ_LLDP_MIB_LOCAL			0
#घोषणा ICE_AQ_LLDP_MIB_REMOTE			1
#घोषणा ICE_AQ_LLDP_MIB_LOCAL_AND_REMOTE	2
#घोषणा ICE_AQ_LLDP_BRID_TYPE_S			2
#घोषणा ICE_AQ_LLDP_BRID_TYPE_M			(0x3 << ICE_AQ_LLDP_BRID_TYPE_S)
#घोषणा ICE_AQ_LLDP_BRID_TYPE_NEAREST_BRID	0
#घोषणा ICE_AQ_LLDP_BRID_TYPE_NON_TPMR		1
/* Tx छोड़ो flags in the 0xA01 event use ICE_AQ_LLDP_TX_* */
#घोषणा ICE_AQ_LLDP_TX_S			0x4
#घोषणा ICE_AQ_LLDP_TX_M			(0x03 << ICE_AQ_LLDP_TX_S)
#घोषणा ICE_AQ_LLDP_TX_ACTIVE			0
#घोषणा ICE_AQ_LLDP_TX_SUSPENDED		1
#घोषणा ICE_AQ_LLDP_TX_FLUSHED			3
/* The following bytes are reserved क्रम the Get LLDP MIB command (0x0A00)
 * and in the LLDP MIB Change Event (0x0A01). They are valid क्रम the
 * Get LLDP MIB (0x0A00) response only.
 */
	u8 reserved1;
	__le16 local_len;
	__le16 remote_len;
	u8 reserved2[2];
	__le32 addr_high;
	__le32 addr_low;
पूर्ण;

/* Configure LLDP MIB Change Event (direct 0x0A01) */
/* For MIB Change Event use ice_aqc_lldp_get_mib काष्ठाure above */
काष्ठा ice_aqc_lldp_set_mib_change अणु
	u8 command;
#घोषणा ICE_AQ_LLDP_MIB_UPDATE_ENABLE		0x0
#घोषणा ICE_AQ_LLDP_MIB_UPDATE_DIS		0x1
	u8 reserved[15];
पूर्ण;

/* Stop LLDP (direct 0x0A05) */
काष्ठा ice_aqc_lldp_stop अणु
	u8 command;
#घोषणा ICE_AQ_LLDP_AGENT_STATE_MASK	BIT(0)
#घोषणा ICE_AQ_LLDP_AGENT_STOP		0x0
#घोषणा ICE_AQ_LLDP_AGENT_SHUTDOWN	ICE_AQ_LLDP_AGENT_STATE_MASK
#घोषणा ICE_AQ_LLDP_AGENT_PERSIST_DIS	BIT(1)
	u8 reserved[15];
पूर्ण;

/* Start LLDP (direct 0x0A06) */
काष्ठा ice_aqc_lldp_start अणु
	u8 command;
#घोषणा ICE_AQ_LLDP_AGENT_START		BIT(0)
#घोषणा ICE_AQ_LLDP_AGENT_PERSIST_ENA	BIT(1)
	u8 reserved[15];
पूर्ण;

/* Get CEE DCBX Oper Config (0x0A07)
 * The command uses the generic descriptor काष्ठा and
 * वापसs the काष्ठा below as an indirect response.
 */
काष्ठा ice_aqc_get_cee_dcb_cfg_resp अणु
	u8 oper_num_tc;
	u8 oper_prio_tc[4];
	u8 oper_tc_bw[8];
	u8 oper_pfc_en;
	__le16 oper_app_prio;
#घोषणा ICE_AQC_CEE_APP_FCOE_S		0
#घोषणा ICE_AQC_CEE_APP_FCOE_M		(0x7 << ICE_AQC_CEE_APP_FCOE_S)
#घोषणा ICE_AQC_CEE_APP_ISCSI_S		3
#घोषणा ICE_AQC_CEE_APP_ISCSI_M		(0x7 << ICE_AQC_CEE_APP_ISCSI_S)
#घोषणा ICE_AQC_CEE_APP_FIP_S		8
#घोषणा ICE_AQC_CEE_APP_FIP_M		(0x7 << ICE_AQC_CEE_APP_FIP_S)
	__le32 tlv_status;
#घोषणा ICE_AQC_CEE_PG_STATUS_S		0
#घोषणा ICE_AQC_CEE_PG_STATUS_M		(0x7 << ICE_AQC_CEE_PG_STATUS_S)
#घोषणा ICE_AQC_CEE_PFC_STATUS_S	3
#घोषणा ICE_AQC_CEE_PFC_STATUS_M	(0x7 << ICE_AQC_CEE_PFC_STATUS_S)
#घोषणा ICE_AQC_CEE_FCOE_STATUS_S	8
#घोषणा ICE_AQC_CEE_FCOE_STATUS_M	(0x7 << ICE_AQC_CEE_FCOE_STATUS_S)
#घोषणा ICE_AQC_CEE_ISCSI_STATUS_S	11
#घोषणा ICE_AQC_CEE_ISCSI_STATUS_M	(0x7 << ICE_AQC_CEE_ISCSI_STATUS_S)
#घोषणा ICE_AQC_CEE_FIP_STATUS_S	16
#घोषणा ICE_AQC_CEE_FIP_STATUS_M	(0x7 << ICE_AQC_CEE_FIP_STATUS_S)
	u8 reserved[12];
पूर्ण;

/* Set Local LLDP MIB (indirect 0x0A08)
 * Used to replace the local MIB of a given LLDP agent. e.g. DCBX
 */
काष्ठा ice_aqc_lldp_set_local_mib अणु
	u8 type;
#घोषणा SET_LOCAL_MIB_TYPE_DCBX_M		BIT(0)
#घोषणा SET_LOCAL_MIB_TYPE_LOCAL_MIB		0
#घोषणा SET_LOCAL_MIB_TYPE_CEE_M		BIT(1)
#घोषणा SET_LOCAL_MIB_TYPE_CEE_WILLING		0
#घोषणा SET_LOCAL_MIB_TYPE_CEE_NON_WILLING	SET_LOCAL_MIB_TYPE_CEE_M
	u8 reserved0;
	__le16 length;
	u8 reserved1[4];
	__le32 addr_high;
	__le32 addr_low;
पूर्ण;

/* Stop/Start LLDP Agent (direct 0x0A09)
 * Used क्रम stopping/starting specअगरic LLDP agent. e.g. DCBX.
 * The same काष्ठाure is used क्रम the response, with the command field
 * being used as the status field.
 */
काष्ठा ice_aqc_lldp_stop_start_specअगरic_agent अणु
	u8 command;
#घोषणा ICE_AQC_START_STOP_AGENT_M		BIT(0)
#घोषणा ICE_AQC_START_STOP_AGENT_STOP_DCBX	0
#घोषणा ICE_AQC_START_STOP_AGENT_START_DCBX	ICE_AQC_START_STOP_AGENT_M
	u8 reserved[15];
पूर्ण;

/* LLDP Filter Control (direct 0x0A0A) */
काष्ठा ice_aqc_lldp_filter_ctrl अणु
	u8 cmd_flags;
#घोषणा ICE_AQC_LLDP_FILTER_ACTION_ADD		0x0
#घोषणा ICE_AQC_LLDP_FILTER_ACTION_DELETE	0x1
	u8 reserved1;
	__le16 vsi_num;
	u8 reserved2[12];
पूर्ण;

/* Get/Set RSS key (indirect 0x0B04/0x0B02) */
काष्ठा ice_aqc_get_set_rss_key अणु
#घोषणा ICE_AQC_GSET_RSS_KEY_VSI_VALID	BIT(15)
#घोषणा ICE_AQC_GSET_RSS_KEY_VSI_ID_S	0
#घोषणा ICE_AQC_GSET_RSS_KEY_VSI_ID_M	(0x3FF << ICE_AQC_GSET_RSS_KEY_VSI_ID_S)
	__le16 vsi_id;
	u8 reserved[6];
	__le32 addr_high;
	__le32 addr_low;
पूर्ण;

#घोषणा ICE_AQC_GET_SET_RSS_KEY_DATA_RSS_KEY_SIZE	0x28
#घोषणा ICE_AQC_GET_SET_RSS_KEY_DATA_HASH_KEY_SIZE	0xC
#घोषणा ICE_GET_SET_RSS_KEY_EXTEND_KEY_SIZE \
				(ICE_AQC_GET_SET_RSS_KEY_DATA_RSS_KEY_SIZE + \
				 ICE_AQC_GET_SET_RSS_KEY_DATA_HASH_KEY_SIZE)

काष्ठा ice_aqc_get_set_rss_keys अणु
	u8 standard_rss_key[ICE_AQC_GET_SET_RSS_KEY_DATA_RSS_KEY_SIZE];
	u8 extended_hash_key[ICE_AQC_GET_SET_RSS_KEY_DATA_HASH_KEY_SIZE];
पूर्ण;

/* Get/Set RSS LUT (indirect 0x0B05/0x0B03) */
काष्ठा ice_aqc_get_set_rss_lut अणु
#घोषणा ICE_AQC_GSET_RSS_LUT_VSI_VALID	BIT(15)
#घोषणा ICE_AQC_GSET_RSS_LUT_VSI_ID_S	0
#घोषणा ICE_AQC_GSET_RSS_LUT_VSI_ID_M	(0x3FF << ICE_AQC_GSET_RSS_LUT_VSI_ID_S)
	__le16 vsi_id;
#घोषणा ICE_AQC_GSET_RSS_LUT_TABLE_TYPE_S	0
#घोषणा ICE_AQC_GSET_RSS_LUT_TABLE_TYPE_M	\
				(0x3 << ICE_AQC_GSET_RSS_LUT_TABLE_TYPE_S)

#घोषणा ICE_AQC_GSET_RSS_LUT_TABLE_TYPE_VSI	 0
#घोषणा ICE_AQC_GSET_RSS_LUT_TABLE_TYPE_PF	 1
#घोषणा ICE_AQC_GSET_RSS_LUT_TABLE_TYPE_GLOBAL	 2

#घोषणा ICE_AQC_GSET_RSS_LUT_TABLE_SIZE_S	 2
#घोषणा ICE_AQC_GSET_RSS_LUT_TABLE_SIZE_M	 \
				(0x3 << ICE_AQC_GSET_RSS_LUT_TABLE_SIZE_S)

#घोषणा ICE_AQC_GSET_RSS_LUT_TABLE_SIZE_128	 128
#घोषणा ICE_AQC_GSET_RSS_LUT_TABLE_SIZE_128_FLAG 0
#घोषणा ICE_AQC_GSET_RSS_LUT_TABLE_SIZE_512	 512
#घोषणा ICE_AQC_GSET_RSS_LUT_TABLE_SIZE_512_FLAG 1
#घोषणा ICE_AQC_GSET_RSS_LUT_TABLE_SIZE_2K	 2048
#घोषणा ICE_AQC_GSET_RSS_LUT_TABLE_SIZE_2K_FLAG	 2

#घोषणा ICE_AQC_GSET_RSS_LUT_GLOBAL_IDX_S	 4
#घोषणा ICE_AQC_GSET_RSS_LUT_GLOBAL_IDX_M	 \
				(0xF << ICE_AQC_GSET_RSS_LUT_GLOBAL_IDX_S)

	__le16 flags;
	__le32 reserved;
	__le32 addr_high;
	__le32 addr_low;
पूर्ण;

/* Add Tx LAN Queues (indirect 0x0C30) */
काष्ठा ice_aqc_add_txqs अणु
	u8 num_qgrps;
	u8 reserved[3];
	__le32 reserved1;
	__le32 addr_high;
	__le32 addr_low;
पूर्ण;

/* This is the descriptor of each queue entry क्रम the Add Tx LAN Queues
 * command (0x0C30). Only used within काष्ठा ice_aqc_add_tx_qgrp.
 */
काष्ठा ice_aqc_add_txqs_perq अणु
	__le16 txq_id;
	u8 rsvd[2];
	__le32 q_teid;
	u8 txq_ctx[22];
	u8 rsvd2[2];
	काष्ठा ice_aqc_txsched_elem info;
पूर्ण;

/* The क्रमmat of the command buffer क्रम Add Tx LAN Queues (0x0C30)
 * is an array of the following काष्ठाs. Please note that the length of
 * each काष्ठा ice_aqc_add_tx_qgrp is variable due
 * to the variable number of queues in each group!
 */
काष्ठा ice_aqc_add_tx_qgrp अणु
	__le32 parent_teid;
	u8 num_txqs;
	u8 rsvd[3];
	काष्ठा ice_aqc_add_txqs_perq txqs[];
पूर्ण;

/* Disable Tx LAN Queues (indirect 0x0C31) */
काष्ठा ice_aqc_dis_txqs अणु
	u8 cmd_type;
#घोषणा ICE_AQC_Q_DIS_CMD_S		0
#घोषणा ICE_AQC_Q_DIS_CMD_M		(0x3 << ICE_AQC_Q_DIS_CMD_S)
#घोषणा ICE_AQC_Q_DIS_CMD_NO_FUNC_RESET	(0 << ICE_AQC_Q_DIS_CMD_S)
#घोषणा ICE_AQC_Q_DIS_CMD_VM_RESET	BIT(ICE_AQC_Q_DIS_CMD_S)
#घोषणा ICE_AQC_Q_DIS_CMD_VF_RESET	(2 << ICE_AQC_Q_DIS_CMD_S)
#घोषणा ICE_AQC_Q_DIS_CMD_PF_RESET	(3 << ICE_AQC_Q_DIS_CMD_S)
#घोषणा ICE_AQC_Q_DIS_CMD_SUBSEQ_CALL	BIT(2)
#घोषणा ICE_AQC_Q_DIS_CMD_FLUSH_PIPE	BIT(3)
	u8 num_entries;
	__le16 vmvf_and_समयout;
#घोषणा ICE_AQC_Q_DIS_VMVF_NUM_S	0
#घोषणा ICE_AQC_Q_DIS_VMVF_NUM_M	(0x3FF << ICE_AQC_Q_DIS_VMVF_NUM_S)
#घोषणा ICE_AQC_Q_DIS_TIMEOUT_S		10
#घोषणा ICE_AQC_Q_DIS_TIMEOUT_M		(0x3F << ICE_AQC_Q_DIS_TIMEOUT_S)
	__le32 blocked_cgds;
	__le32 addr_high;
	__le32 addr_low;
पूर्ण;

/* The buffer क्रम Disable Tx LAN Queues (indirect 0x0C31)
 * contains the following काष्ठाures, arrayed one after the
 * other.
 * Note: Since the q_id is 16 bits wide, अगर the
 * number of queues is even, then 2 bytes of alignment MUST be
 * added beक्रमe the start of the next group, to allow correct
 * alignment of the parent_teid field.
 */
काष्ठा ice_aqc_dis_txq_item अणु
	__le32 parent_teid;
	u8 num_qs;
	u8 rsvd;
	/* The length of the q_id array varies according to num_qs */
#घोषणा ICE_AQC_Q_DIS_BUF_ELEM_TYPE_S		15
#घोषणा ICE_AQC_Q_DIS_BUF_ELEM_TYPE_LAN_Q	\
			(0 << ICE_AQC_Q_DIS_BUF_ELEM_TYPE_S)
#घोषणा ICE_AQC_Q_DIS_BUF_ELEM_TYPE_RDMA_QSET	\
			(1 << ICE_AQC_Q_DIS_BUF_ELEM_TYPE_S)
	__le16 q_id[];
पूर्ण __packed;

/* Configure Firmware Logging Command (indirect 0xFF09)
 * Logging Inक्रमmation Read Response (indirect 0xFF10)
 * Note: The 0xFF10 command has no input parameters.
 */
काष्ठा ice_aqc_fw_logging अणु
	u8 log_ctrl;
#घोषणा ICE_AQC_FW_LOG_AQ_EN		BIT(0)
#घोषणा ICE_AQC_FW_LOG_UART_EN		BIT(1)
	u8 rsvd0;
	u8 log_ctrl_valid; /* Not used by 0xFF10 Response */
#घोषणा ICE_AQC_FW_LOG_AQ_VALID		BIT(0)
#घोषणा ICE_AQC_FW_LOG_UART_VALID	BIT(1)
	u8 rsvd1[5];
	__le32 addr_high;
	__le32 addr_low;
पूर्ण;

क्रमागत ice_aqc_fw_logging_mod अणु
	ICE_AQC_FW_LOG_ID_GENERAL = 0,
	ICE_AQC_FW_LOG_ID_CTRL,
	ICE_AQC_FW_LOG_ID_LINK,
	ICE_AQC_FW_LOG_ID_LINK_TOPO,
	ICE_AQC_FW_LOG_ID_DNL,
	ICE_AQC_FW_LOG_ID_I2C,
	ICE_AQC_FW_LOG_ID_SDP,
	ICE_AQC_FW_LOG_ID_MDIO,
	ICE_AQC_FW_LOG_ID_ADMINQ,
	ICE_AQC_FW_LOG_ID_HDMA,
	ICE_AQC_FW_LOG_ID_LLDP,
	ICE_AQC_FW_LOG_ID_DCBX,
	ICE_AQC_FW_LOG_ID_DCB,
	ICE_AQC_FW_LOG_ID_NETPROXY,
	ICE_AQC_FW_LOG_ID_NVM,
	ICE_AQC_FW_LOG_ID_AUTH,
	ICE_AQC_FW_LOG_ID_VPD,
	ICE_AQC_FW_LOG_ID_IOSF,
	ICE_AQC_FW_LOG_ID_PARSER,
	ICE_AQC_FW_LOG_ID_SW,
	ICE_AQC_FW_LOG_ID_SCHEDULER,
	ICE_AQC_FW_LOG_ID_TXQ,
	ICE_AQC_FW_LOG_ID_RSVD,
	ICE_AQC_FW_LOG_ID_POST,
	ICE_AQC_FW_LOG_ID_WATCHDOG,
	ICE_AQC_FW_LOG_ID_TASK_DISPATCH,
	ICE_AQC_FW_LOG_ID_MNG,
	ICE_AQC_FW_LOG_ID_MAX,
पूर्ण;

/* Defines क्रम both above FW logging command/response buffers */
#घोषणा ICE_AQC_FW_LOG_ID_S		0
#घोषणा ICE_AQC_FW_LOG_ID_M		(0xFFF << ICE_AQC_FW_LOG_ID_S)

#घोषणा ICE_AQC_FW_LOG_CONF_SUCCESS	0	/* Used by response */
#घोषणा ICE_AQC_FW_LOG_CONF_BAD_INDX	BIT(12)	/* Used by response */

#घोषणा ICE_AQC_FW_LOG_EN_S		12
#घोषणा ICE_AQC_FW_LOG_EN_M		(0xF << ICE_AQC_FW_LOG_EN_S)
#घोषणा ICE_AQC_FW_LOG_INFO_EN		BIT(12)	/* Used by command */
#घोषणा ICE_AQC_FW_LOG_INIT_EN		BIT(13)	/* Used by command */
#घोषणा ICE_AQC_FW_LOG_FLOW_EN		BIT(14)	/* Used by command */
#घोषणा ICE_AQC_FW_LOG_ERR_EN		BIT(15)	/* Used by command */

/* Get/Clear FW Log (indirect 0xFF11) */
काष्ठा ice_aqc_get_clear_fw_log अणु
	u8 flags;
#घोषणा ICE_AQC_FW_LOG_CLEAR		BIT(0)
#घोषणा ICE_AQC_FW_LOG_MORE_DATA_AVAIL	BIT(1)
	u8 rsvd1[7];
	__le32 addr_high;
	__le32 addr_low;
पूर्ण;

/* Download Package (indirect 0x0C40) */
/* Also used क्रम Update Package (indirect 0x0C42) */
काष्ठा ice_aqc_करोwnload_pkg अणु
	u8 flags;
#घोषणा ICE_AQC_DOWNLOAD_PKG_LAST_BUF	0x01
	u8 reserved[3];
	__le32 reserved1;
	__le32 addr_high;
	__le32 addr_low;
पूर्ण;

काष्ठा ice_aqc_करोwnload_pkg_resp अणु
	__le32 error_offset;
	__le32 error_info;
	__le32 addr_high;
	__le32 addr_low;
पूर्ण;

/* Get Package Info List (indirect 0x0C43) */
काष्ठा ice_aqc_get_pkg_info_list अणु
	__le32 reserved1;
	__le32 reserved2;
	__le32 addr_high;
	__le32 addr_low;
पूर्ण;

/* Version क्रमmat क्रम packages */
काष्ठा ice_pkg_ver अणु
	u8 major;
	u8 minor;
	u8 update;
	u8 draft;
पूर्ण;

#घोषणा ICE_PKG_NAME_SIZE	32
#घोषणा ICE_SEG_ID_SIZE		28
#घोषणा ICE_SEG_NAME_SIZE	28

काष्ठा ice_aqc_get_pkg_info अणु
	काष्ठा ice_pkg_ver ver;
	अक्षर name[ICE_SEG_NAME_SIZE];
	__le32 track_id;
	u8 is_in_nvm;
	u8 is_active;
	u8 is_active_at_boot;
	u8 is_modअगरied;
पूर्ण;

/* Get Package Info List response buffer क्रमmat (0x0C43) */
काष्ठा ice_aqc_get_pkg_info_resp अणु
	__le32 count;
	काष्ठा ice_aqc_get_pkg_info pkg_info[];
पूर्ण;

/* Lan Queue Overflow Event (direct, 0x1001) */
काष्ठा ice_aqc_event_lan_overflow अणु
	__le32 prtdcb_ruptq;
	__le32 qtx_ctl;
	u8 reserved[8];
पूर्ण;

/**
 * काष्ठा ice_aq_desc - Admin Queue (AQ) descriptor
 * @flags: ICE_AQ_FLAG_* flags
 * @opcode: AQ command opcode
 * @datalen: length in bytes of indirect/बाह्यal data buffer
 * @retval: वापस value from firmware
 * @cookie_high: opaque data high-half
 * @cookie_low: opaque data low-half
 * @params: command-specअगरic parameters
 *
 * Descriptor क्रमmat क्रम commands the driver posts on the Admin Transmit Queue
 * (ATQ). The firmware ग_लिखोs back onto the command descriptor and वापसs
 * the result of the command. Asynchronous events that are not an immediate
 * result of the command are written to the Admin Receive Queue (ARQ) using
 * the same descriptor क्रमmat. Descriptors are in little-endian notation with
 * 32-bit words.
 */
काष्ठा ice_aq_desc अणु
	__le16 flags;
	__le16 opcode;
	__le16 datalen;
	__le16 retval;
	__le32 cookie_high;
	__le32 cookie_low;
	जोड़ अणु
		u8 raw[16];
		काष्ठा ice_aqc_generic generic;
		काष्ठा ice_aqc_get_ver get_ver;
		काष्ठा ice_aqc_driver_ver driver_ver;
		काष्ठा ice_aqc_q_shutकरोwn q_shutकरोwn;
		काष्ठा ice_aqc_req_res res_owner;
		काष्ठा ice_aqc_manage_mac_पढ़ो mac_पढ़ो;
		काष्ठा ice_aqc_manage_mac_ग_लिखो mac_ग_लिखो;
		काष्ठा ice_aqc_clear_pxe clear_pxe;
		काष्ठा ice_aqc_list_caps get_cap;
		काष्ठा ice_aqc_get_phy_caps get_phy;
		काष्ठा ice_aqc_set_phy_cfg set_phy;
		काष्ठा ice_aqc_restart_an restart_an;
		काष्ठा ice_aqc_sff_eeprom पढ़ो_ग_लिखो_sff_param;
		काष्ठा ice_aqc_set_port_id_led set_port_id_led;
		काष्ठा ice_aqc_get_sw_cfg get_sw_conf;
		काष्ठा ice_aqc_sw_rules sw_rules;
		काष्ठा ice_aqc_get_topo get_topo;
		काष्ठा ice_aqc_sched_elem_cmd sched_elem_cmd;
		काष्ठा ice_aqc_query_txsched_res query_sched_res;
		काष्ठा ice_aqc_query_port_ets port_ets;
		काष्ठा ice_aqc_rl_profile rl_profile;
		काष्ठा ice_aqc_nvm nvm;
		काष्ठा ice_aqc_nvm_checksum nvm_checksum;
		काष्ठा ice_aqc_nvm_pkg_data pkg_data;
		काष्ठा ice_aqc_nvm_pass_comp_tbl pass_comp_tbl;
		काष्ठा ice_aqc_pf_vf_msg virt;
		काष्ठा ice_aqc_lldp_get_mib lldp_get_mib;
		काष्ठा ice_aqc_lldp_set_mib_change lldp_set_event;
		काष्ठा ice_aqc_lldp_stop lldp_stop;
		काष्ठा ice_aqc_lldp_start lldp_start;
		काष्ठा ice_aqc_lldp_set_local_mib lldp_set_mib;
		काष्ठा ice_aqc_lldp_stop_start_specअगरic_agent lldp_agent_ctrl;
		काष्ठा ice_aqc_lldp_filter_ctrl lldp_filter_ctrl;
		काष्ठा ice_aqc_get_set_rss_lut get_set_rss_lut;
		काष्ठा ice_aqc_get_set_rss_key get_set_rss_key;
		काष्ठा ice_aqc_add_txqs add_txqs;
		काष्ठा ice_aqc_dis_txqs dis_txqs;
		काष्ठा ice_aqc_add_get_update_मुक्त_vsi vsi_cmd;
		काष्ठा ice_aqc_add_update_मुक्त_vsi_resp add_update_मुक्त_vsi_res;
		काष्ठा ice_aqc_fw_logging fw_logging;
		काष्ठा ice_aqc_get_clear_fw_log get_clear_fw_log;
		काष्ठा ice_aqc_करोwnload_pkg करोwnload_pkg;
		काष्ठा ice_aqc_set_mac_lb set_mac_lb;
		काष्ठा ice_aqc_alloc_मुक्त_res_cmd sw_res_ctrl;
		काष्ठा ice_aqc_set_mac_cfg set_mac_cfg;
		काष्ठा ice_aqc_set_event_mask set_event_mask;
		काष्ठा ice_aqc_get_link_status get_link_status;
		काष्ठा ice_aqc_event_lan_overflow lan_overflow;
		काष्ठा ice_aqc_get_link_topo get_link_topo;
	पूर्ण params;
पूर्ण;

/* FW defined boundary क्रम a large buffer, 4k >= Large buffer > 512 bytes */
#घोषणा ICE_AQ_LG_BUF	512

#घोषणा ICE_AQ_FLAG_ERR_S	2
#घोषणा ICE_AQ_FLAG_LB_S	9
#घोषणा ICE_AQ_FLAG_RD_S	10
#घोषणा ICE_AQ_FLAG_BUF_S	12
#घोषणा ICE_AQ_FLAG_SI_S	13

#घोषणा ICE_AQ_FLAG_ERR		BIT(ICE_AQ_FLAG_ERR_S) /* 0x4    */
#घोषणा ICE_AQ_FLAG_LB		BIT(ICE_AQ_FLAG_LB_S)  /* 0x200  */
#घोषणा ICE_AQ_FLAG_RD		BIT(ICE_AQ_FLAG_RD_S)  /* 0x400  */
#घोषणा ICE_AQ_FLAG_BUF		BIT(ICE_AQ_FLAG_BUF_S) /* 0x1000 */
#घोषणा ICE_AQ_FLAG_SI		BIT(ICE_AQ_FLAG_SI_S)  /* 0x2000 */

/* error codes */
क्रमागत ice_aq_err अणु
	ICE_AQ_RC_OK		= 0,  /* Success */
	ICE_AQ_RC_EPERM		= 1,  /* Operation not permitted */
	ICE_AQ_RC_ENOENT	= 2,  /* No such element */
	ICE_AQ_RC_ENOMEM	= 9,  /* Out of memory */
	ICE_AQ_RC_EBUSY		= 12, /* Device or resource busy */
	ICE_AQ_RC_EEXIST	= 13, /* Object alपढ़ोy exists */
	ICE_AQ_RC_EINVAL	= 14, /* Invalid argument */
	ICE_AQ_RC_ENOSPC	= 16, /* No space left or allocation failure */
	ICE_AQ_RC_ENOSYS	= 17, /* Function not implemented */
	ICE_AQ_RC_EMODE		= 21, /* Op not allowed in current dev mode */
	ICE_AQ_RC_ENOSEC	= 24, /* Missing security manअगरest */
	ICE_AQ_RC_EBADSIG	= 25, /* Bad RSA signature */
	ICE_AQ_RC_ESVN		= 26, /* SVN number prohibits this package */
	ICE_AQ_RC_EBADMAN	= 27, /* Manअगरest hash mismatch */
	ICE_AQ_RC_EBADBUF	= 28, /* Buffer hash mismatches manअगरest */
पूर्ण;

/* Admin Queue command opcodes */
क्रमागत ice_adminq_opc अणु
	/* AQ commands */
	ice_aqc_opc_get_ver				= 0x0001,
	ice_aqc_opc_driver_ver				= 0x0002,
	ice_aqc_opc_q_shutकरोwn				= 0x0003,

	/* resource ownership */
	ice_aqc_opc_req_res				= 0x0008,
	ice_aqc_opc_release_res				= 0x0009,

	/* device/function capabilities */
	ice_aqc_opc_list_func_caps			= 0x000A,
	ice_aqc_opc_list_dev_caps			= 0x000B,

	/* manage MAC address */
	ice_aqc_opc_manage_mac_पढ़ो			= 0x0107,
	ice_aqc_opc_manage_mac_ग_लिखो			= 0x0108,

	/* PXE */
	ice_aqc_opc_clear_pxe_mode			= 0x0110,

	/* पूर्णांकernal चयन commands */
	ice_aqc_opc_get_sw_cfg				= 0x0200,

	/* Alloc/Free/Get Resources */
	ice_aqc_opc_alloc_res				= 0x0208,
	ice_aqc_opc_मुक्त_res				= 0x0209,

	/* VSI commands */
	ice_aqc_opc_add_vsi				= 0x0210,
	ice_aqc_opc_update_vsi				= 0x0211,
	ice_aqc_opc_मुक्त_vsi				= 0x0213,

	/* चयन rules population commands */
	ice_aqc_opc_add_sw_rules			= 0x02A0,
	ice_aqc_opc_update_sw_rules			= 0x02A1,
	ice_aqc_opc_हटाओ_sw_rules			= 0x02A2,

	ice_aqc_opc_clear_pf_cfg			= 0x02A4,

	/* transmit scheduler commands */
	ice_aqc_opc_get_dflt_topo			= 0x0400,
	ice_aqc_opc_add_sched_elems			= 0x0401,
	ice_aqc_opc_cfg_sched_elems			= 0x0403,
	ice_aqc_opc_get_sched_elems			= 0x0404,
	ice_aqc_opc_move_sched_elems			= 0x0408,
	ice_aqc_opc_suspend_sched_elems			= 0x0409,
	ice_aqc_opc_resume_sched_elems			= 0x040A,
	ice_aqc_opc_query_port_ets			= 0x040E,
	ice_aqc_opc_delete_sched_elems			= 0x040F,
	ice_aqc_opc_add_rl_profiles			= 0x0410,
	ice_aqc_opc_query_sched_res			= 0x0412,
	ice_aqc_opc_हटाओ_rl_profiles			= 0x0415,

	/* PHY commands */
	ice_aqc_opc_get_phy_caps			= 0x0600,
	ice_aqc_opc_set_phy_cfg				= 0x0601,
	ice_aqc_opc_set_mac_cfg				= 0x0603,
	ice_aqc_opc_restart_an				= 0x0605,
	ice_aqc_opc_get_link_status			= 0x0607,
	ice_aqc_opc_set_event_mask			= 0x0613,
	ice_aqc_opc_set_mac_lb				= 0x0620,
	ice_aqc_opc_get_link_topo			= 0x06E0,
	ice_aqc_opc_set_port_id_led			= 0x06E9,
	ice_aqc_opc_sff_eeprom				= 0x06EE,

	/* NVM commands */
	ice_aqc_opc_nvm_पढ़ो				= 0x0701,
	ice_aqc_opc_nvm_erase				= 0x0702,
	ice_aqc_opc_nvm_ग_लिखो				= 0x0703,
	ice_aqc_opc_nvm_checksum			= 0x0706,
	ice_aqc_opc_nvm_ग_लिखो_activate			= 0x0707,
	ice_aqc_opc_nvm_update_empr			= 0x0709,
	ice_aqc_opc_nvm_pkg_data			= 0x070A,
	ice_aqc_opc_nvm_pass_component_tbl		= 0x070B,

	/* PF/VF mailbox commands */
	ice_mbx_opc_send_msg_to_pf			= 0x0801,
	ice_mbx_opc_send_msg_to_vf			= 0x0802,
	/* LLDP commands */
	ice_aqc_opc_lldp_get_mib			= 0x0A00,
	ice_aqc_opc_lldp_set_mib_change			= 0x0A01,
	ice_aqc_opc_lldp_stop				= 0x0A05,
	ice_aqc_opc_lldp_start				= 0x0A06,
	ice_aqc_opc_get_cee_dcb_cfg			= 0x0A07,
	ice_aqc_opc_lldp_set_local_mib			= 0x0A08,
	ice_aqc_opc_lldp_stop_start_specअगरic_agent	= 0x0A09,
	ice_aqc_opc_lldp_filter_ctrl			= 0x0A0A,

	/* RSS commands */
	ice_aqc_opc_set_rss_key				= 0x0B02,
	ice_aqc_opc_set_rss_lut				= 0x0B03,
	ice_aqc_opc_get_rss_key				= 0x0B04,
	ice_aqc_opc_get_rss_lut				= 0x0B05,

	/* Tx queue handling commands/events */
	ice_aqc_opc_add_txqs				= 0x0C30,
	ice_aqc_opc_dis_txqs				= 0x0C31,

	/* package commands */
	ice_aqc_opc_करोwnload_pkg			= 0x0C40,
	ice_aqc_opc_update_pkg				= 0x0C42,
	ice_aqc_opc_get_pkg_info_list			= 0x0C43,

	/* Standalone Commands/Events */
	ice_aqc_opc_event_lan_overflow			= 0x1001,

	/* debug commands */
	ice_aqc_opc_fw_logging				= 0xFF09,
	ice_aqc_opc_fw_logging_info			= 0xFF10,
पूर्ण;

#पूर्ण_अगर /* _ICE_ADMINQ_CMD_H_ */
