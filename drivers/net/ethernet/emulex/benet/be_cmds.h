<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2005 - 2016 Broadcom
 * All rights reserved.
 *
 * Contact Inक्रमmation:
 * linux-drivers@emulex.com
 *
 * Emulex
 * 3333 Susan Street
 * Costa Mesa, CA 92626
 */

/*
 * The driver sends configuration and managements command requests to the
 * firmware in the BE. These requests are communicated to the processor
 * using Work Request Blocks (WRBs) submitted to the MCC-WRB ring or via one
 * WRB inside a MAILBOX.
 * The commands are serviced by the ARM processor in the BladeEngine's MPU.
 */

काष्ठा be_sge अणु
	u32 pa_lo;
	u32 pa_hi;
	u32 len;
पूर्ण;

#घोषणा MCC_WRB_EMBEDDED_MASK	1 	/* bit 0 of dword 0*/
#घोषणा MCC_WRB_SGE_CNT_SHIFT	3	/* bits 3 - 7 of dword 0 */
#घोषणा MCC_WRB_SGE_CNT_MASK	0x1F	/* bits 3 - 7 of dword 0 */
काष्ठा be_mcc_wrb अणु
	u32 embedded;		/* dword 0 */
	u32 payload_length;	/* dword 1 */
	u32 tag0;		/* dword 2 */
	u32 tag1;		/* dword 3 */
	u32 rsvd;		/* dword 4 */
	जोड़ अणु
		u8 embedded_payload[236]; /* used by embedded cmds */
		काष्ठा be_sge sgl[19];    /* used by non-embedded cmds */
	पूर्ण payload;
पूर्ण;

#घोषणा CQE_FLAGS_VALID_MASK		BIT(31)
#घोषणा CQE_FLAGS_ASYNC_MASK		BIT(30)
#घोषणा CQE_FLAGS_COMPLETED_MASK	BIT(28)
#घोषणा CQE_FLAGS_CONSUMED_MASK		BIT(27)

/* Completion Status */
क्रमागत mcc_base_status अणु
	MCC_STATUS_SUCCESS = 0,
	MCC_STATUS_FAILED = 1,
	MCC_STATUS_ILLEGAL_REQUEST = 2,
	MCC_STATUS_ILLEGAL_FIELD = 3,
	MCC_STATUS_INSUFFICIENT_BUFFER = 4,
	MCC_STATUS_UNAUTHORIZED_REQUEST = 5,
	MCC_STATUS_NOT_SUPPORTED = 66,
	MCC_STATUS_FEATURE_NOT_SUPPORTED = 68,
	MCC_STATUS_INVALID_LENGTH = 116
पूर्ण;

/* Additional status */
क्रमागत mcc_addl_status अणु
	MCC_ADDL_STATUS_INSUFFICIENT_RESOURCES = 0x16,
	MCC_ADDL_STATUS_FLASH_IMAGE_CRC_MISMATCH = 0x4d,
	MCC_ADDL_STATUS_TOO_MANY_INTERFACES = 0x4a,
	MCC_ADDL_STATUS_INSUFFICIENT_VLANS = 0xab,
	MCC_ADDL_STATUS_INVALID_SIGNATURE = 0x56,
	MCC_ADDL_STATUS_MISSING_SIGNATURE = 0x57,
	MCC_ADDL_STATUS_INSUFFICIENT_PRIVILEGES = 0x60
पूर्ण;

#घोषणा CQE_BASE_STATUS_MASK		0xFFFF
#घोषणा CQE_BASE_STATUS_SHIFT		0	/* bits 0 - 15 */
#घोषणा CQE_ADDL_STATUS_MASK		0xFF
#घोषणा CQE_ADDL_STATUS_SHIFT		16	/* bits 16 - 31 */

#घोषणा base_status(status)		\
		((क्रमागत mcc_base_status)	\
			(status > 0 ? (status & CQE_BASE_STATUS_MASK) : 0))
#घोषणा addl_status(status)		\
		((क्रमागत mcc_addl_status)	\
			(status > 0 ? (status >> CQE_ADDL_STATUS_SHIFT) & \
					CQE_ADDL_STATUS_MASK : 0))

काष्ठा be_mcc_compl अणु
	u32 status;		/* dword 0 */
	u32 tag0;		/* dword 1 */
	u32 tag1;		/* dword 2 */
	u32 flags;		/* dword 3 */
पूर्ण;

/* When the async bit of mcc_compl flags is set, flags
 * is पूर्णांकerpreted as follows:
 */
#घोषणा ASYNC_EVENT_CODE_SHIFT		8	/* bits 8 - 15 */
#घोषणा ASYNC_EVENT_CODE_MASK		0xFF
#घोषणा ASYNC_EVENT_TYPE_SHIFT		16
#घोषणा ASYNC_EVENT_TYPE_MASK		0xFF
#घोषणा ASYNC_EVENT_CODE_LINK_STATE	0x1
#घोषणा ASYNC_EVENT_CODE_GRP_5		0x5
#घोषणा ASYNC_EVENT_QOS_SPEED		0x1
#घोषणा ASYNC_EVENT_COS_PRIORITY	0x2
#घोषणा ASYNC_EVENT_PVID_STATE		0x3
#घोषणा ASYNC_EVENT_CODE_QNQ		0x6
#घोषणा ASYNC_DEBUG_EVENT_TYPE_QNQ	1
#घोषणा ASYNC_EVENT_CODE_SLIPORT	0x11
#घोषणा ASYNC_EVENT_PORT_MISCONFIG	0x9
#घोषणा ASYNC_EVENT_FW_CONTROL		0x5

क्रमागत अणु
	LINK_DOWN	= 0x0,
	LINK_UP		= 0x1
पूर्ण;
#घोषणा LINK_STATUS_MASK			0x1
#घोषणा LOGICAL_LINK_STATUS_MASK		0x2

/* When the event code of compl->flags is link-state, the mcc_compl
 * must be पूर्णांकerpreted as follows
 */
काष्ठा be_async_event_link_state अणु
	u8 physical_port;
	u8 port_link_status;
	u8 port_duplex;
	u8 port_speed;
	u8 port_fault;
	u8 rsvd0[7];
	u32 flags;
पूर्ण __packed;

/* When the event code of compl->flags is GRP-5 and event_type is QOS_SPEED
 * the mcc_compl must be पूर्णांकerpreted as follows
 */
काष्ठा be_async_event_grp5_qos_link_speed अणु
	u8 physical_port;
	u8 rsvd[5];
	u16 qos_link_speed;
	u32 event_tag;
	u32 flags;
पूर्ण __packed;

/* When the event code of compl->flags is GRP5 and event type is
 * CoS-Priority, the mcc_compl must be पूर्णांकerpreted as follows
 */
काष्ठा be_async_event_grp5_cos_priority अणु
	u8 physical_port;
	u8 available_priority_bmap;
	u8 reco_शेष_priority;
	u8 valid;
	u8 rsvd0;
	u8 event_tag;
	u32 flags;
पूर्ण __packed;

/* When the event code of compl->flags is GRP5 and event type is
 * PVID state, the mcc_compl must be पूर्णांकerpreted as follows
 */
काष्ठा be_async_event_grp5_pvid_state अणु
	u8 enabled;
	u8 rsvd0;
	u16 tag;
	u32 event_tag;
	u32 rsvd1;
	u32 flags;
पूर्ण __packed;

/* async event indicating outer VLAN tag in QnQ */
काष्ठा be_async_event_qnq अणु
	u8 valid;	/* Indicates अगर outer VLAN is valid */
	u8 rsvd0;
	u16 vlan_tag;
	u32 event_tag;
	u8 rsvd1[4];
	u32 flags;
पूर्ण __packed;

क्रमागत अणु
	BE_PHY_FUNCTIONAL	= 0,
	BE_PHY_NOT_PRESENT	= 1,
	BE_PHY_DIFF_MEDIA	= 2,
	BE_PHY_INCOMPATIBLE	= 3,
	BE_PHY_UNQUALIFIED	= 4,
	BE_PHY_UNCERTIFIED	= 5
पूर्ण;

#घोषणा PHY_STATE_MSG_SEVERITY		0x6
#घोषणा PHY_STATE_OPER			0x1
#घोषणा PHY_STATE_INFO_VALID		0x80
#घोषणा	PHY_STATE_OPER_MSG_NONE		0x2
#घोषणा DEFAULT_MSG_SEVERITY		0x1

#घोषणा be_phy_state_unknown(phy_state) (phy_state > BE_PHY_UNCERTIFIED)
#घोषणा be_phy_unqualअगरied(phy_state)				\
			(phy_state == BE_PHY_UNQUALIFIED ||	\
			 phy_state == BE_PHY_UNCERTIFIED)
#घोषणा be_phy_misconfigured(phy_state)				\
			(phy_state == BE_PHY_INCOMPATIBLE ||	\
			 phy_state == BE_PHY_UNQUALIFIED ||	\
			 phy_state == BE_PHY_UNCERTIFIED)

बाह्य स्थिर  अक्षर * स्थिर be_misconfig_evt_port_state[];

/* async event indicating misconfigured port */
काष्ठा be_async_event_misconfig_port अणु
 /* DATA_WORD1:
  * phy state of port 0: bits 7 - 0
  * phy state of port 1: bits 15 - 8
  * phy state of port 2: bits 23 - 16
  * phy state of port 3: bits 31 - 24
  */
	u32 event_data_word1;
 /* DATA_WORD2:
  * phy state info of port 0: bits 7 - 0
  * phy state info of port 1: bits 15 - 8
  * phy state info of port 2: bits 23 - 16
  * phy state info of port 3: bits 31 - 24
  *
  * PHY STATE INFO:
  * Link operability	 :bit 0
  * Message severity	 :bit 2 - 1
  * Rsvd			 :bits 6 - 3
  * phy state info valid	 :bit 7
  */
	u32 event_data_word2;
	u32 rsvd0;
	u32 flags;
पूर्ण __packed;

#घोषणा BMC_FILT_BROADCAST_ARP				BIT(0)
#घोषणा BMC_FILT_BROADCAST_DHCP_CLIENT			BIT(1)
#घोषणा BMC_FILT_BROADCAST_DHCP_SERVER			BIT(2)
#घोषणा BMC_FILT_BROADCAST_NET_BIOS			BIT(3)
#घोषणा BMC_FILT_BROADCAST				BIT(7)
#घोषणा BMC_FILT_MULTICAST_IPV6_NEIGH_ADVER		BIT(8)
#घोषणा BMC_FILT_MULTICAST_IPV6_RA			BIT(9)
#घोषणा BMC_FILT_MULTICAST_IPV6_RAS			BIT(10)
#घोषणा BMC_FILT_MULTICAST				BIT(15)
काष्ठा be_async_fw_control अणु
	u32 event_data_word1;
	u32 event_data_word2;
	u32 evt_tag;
	u32 event_data_word4;
पूर्ण __packed;

काष्ठा be_mcc_mailbox अणु
	काष्ठा be_mcc_wrb wrb;
	काष्ठा be_mcc_compl compl;
पूर्ण;

#घोषणा CMD_SUBSYSTEM_COMMON	0x1
#घोषणा CMD_SUBSYSTEM_ETH 	0x3
#घोषणा CMD_SUBSYSTEM_LOWLEVEL  0xb

#घोषणा OPCODE_COMMON_NTWK_MAC_QUERY			1
#घोषणा OPCODE_COMMON_NTWK_MAC_SET			2
#घोषणा OPCODE_COMMON_NTWK_MULTICAST_SET		3
#घोषणा OPCODE_COMMON_NTWK_VLAN_CONFIG  		4
#घोषणा OPCODE_COMMON_NTWK_LINK_STATUS_QUERY		5
#घोषणा OPCODE_COMMON_READ_FLASHROM			6
#घोषणा OPCODE_COMMON_WRITE_FLASHROM			7
#घोषणा OPCODE_COMMON_CQ_CREATE				12
#घोषणा OPCODE_COMMON_EQ_CREATE				13
#घोषणा OPCODE_COMMON_MCC_CREATE			21
#घोषणा OPCODE_COMMON_SET_QOS				28
#घोषणा OPCODE_COMMON_MCC_CREATE_EXT			90
#घोषणा OPCODE_COMMON_SEEPROM_READ			30
#घोषणा OPCODE_COMMON_GET_CNTL_ATTRIBUTES               32
#घोषणा OPCODE_COMMON_NTWK_RX_FILTER    		34
#घोषणा OPCODE_COMMON_GET_FW_VERSION			35
#घोषणा OPCODE_COMMON_SET_FLOW_CONTROL			36
#घोषणा OPCODE_COMMON_GET_FLOW_CONTROL			37
#घोषणा OPCODE_COMMON_SET_FRAME_SIZE			39
#घोषणा OPCODE_COMMON_MODIFY_EQ_DELAY			41
#घोषणा OPCODE_COMMON_FIRMWARE_CONFIG			42
#घोषणा OPCODE_COMMON_NTWK_INTERFACE_CREATE 		50
#घोषणा OPCODE_COMMON_NTWK_INTERFACE_DESTROY 		51
#घोषणा OPCODE_COMMON_MCC_DESTROY        		53
#घोषणा OPCODE_COMMON_CQ_DESTROY        		54
#घोषणा OPCODE_COMMON_EQ_DESTROY        		55
#घोषणा OPCODE_COMMON_QUERY_FIRMWARE_CONFIG		58
#घोषणा OPCODE_COMMON_NTWK_PMAC_ADD			59
#घोषणा OPCODE_COMMON_NTWK_PMAC_DEL			60
#घोषणा OPCODE_COMMON_FUNCTION_RESET			61
#घोषणा OPCODE_COMMON_MANAGE_FAT			68
#घोषणा OPCODE_COMMON_ENABLE_DISABLE_BEACON		69
#घोषणा OPCODE_COMMON_GET_BEACON_STATE			70
#घोषणा OPCODE_COMMON_READ_TRANSRECV_DATA		73
#घोषणा OPCODE_COMMON_GET_PORT_NAME			77
#घोषणा OPCODE_COMMON_SET_LOGICAL_LINK_CONFIG		80
#घोषणा OPCODE_COMMON_SET_INTERRUPT_ENABLE		89
#घोषणा OPCODE_COMMON_SET_FN_PRIVILEGES			100
#घोषणा OPCODE_COMMON_GET_PHY_DETAILS			102
#घोषणा OPCODE_COMMON_SET_DRIVER_FUNCTION_CAP		103
#घोषणा OPCODE_COMMON_GET_CNTL_ADDITIONAL_ATTRIBUTES	121
#घोषणा OPCODE_COMMON_GET_EXT_FAT_CAPABILITIES		125
#घोषणा OPCODE_COMMON_SET_EXT_FAT_CAPABILITIES		126
#घोषणा OPCODE_COMMON_GET_MAC_LIST			147
#घोषणा OPCODE_COMMON_SET_MAC_LIST			148
#घोषणा OPCODE_COMMON_GET_HSW_CONFIG			152
#घोषणा OPCODE_COMMON_GET_FUNC_CONFIG			160
#घोषणा OPCODE_COMMON_GET_PROखाता_CONFIG		164
#घोषणा OPCODE_COMMON_SET_PROखाता_CONFIG		165
#घोषणा OPCODE_COMMON_GET_ACTIVE_PROखाता		167
#घोषणा OPCODE_COMMON_SET_HSW_CONFIG			153
#घोषणा OPCODE_COMMON_GET_FN_PRIVILEGES			170
#घोषणा OPCODE_COMMON_READ_OBJECT			171
#घोषणा OPCODE_COMMON_WRITE_OBJECT			172
#घोषणा OPCODE_COMMON_DELETE_OBJECT			174
#घोषणा OPCODE_COMMON_SET_FEATURES			191
#घोषणा OPCODE_COMMON_MANAGE_IFACE_FILTERS		193
#घोषणा OPCODE_COMMON_GET_IFACE_LIST			194
#घोषणा OPCODE_COMMON_ENABLE_DISABLE_VF			196

#घोषणा OPCODE_ETH_RSS_CONFIG				1
#घोषणा OPCODE_ETH_ACPI_CONFIG				2
#घोषणा OPCODE_ETH_PROMISCUOUS				3
#घोषणा OPCODE_ETH_GET_STATISTICS			4
#घोषणा OPCODE_ETH_TX_CREATE				7
#घोषणा OPCODE_ETH_RX_CREATE            		8
#घोषणा OPCODE_ETH_TX_DESTROY           		9
#घोषणा OPCODE_ETH_RX_DESTROY           		10
#घोषणा OPCODE_ETH_ACPI_WOL_MAGIC_CONFIG		12
#घोषणा OPCODE_ETH_GET_PPORT_STATS			18

#घोषणा OPCODE_LOWLEVEL_HOST_DDR_DMA                    17
#घोषणा OPCODE_LOWLEVEL_LOOPBACK_TEST                   18
#घोषणा OPCODE_LOWLEVEL_SET_LOOPBACK_MODE		19

काष्ठा be_cmd_req_hdr अणु
	u8 opcode;		/* dword 0 */
	u8 subप्रणाली;		/* dword 0 */
	u8 port_number;		/* dword 0 */
	u8 करोमुख्य;		/* dword 0 */
	u32 समयout;		/* dword 1 */
	u32 request_length;	/* dword 2 */
	u8 version;		/* dword 3 */
	u8 rsvd[3];		/* dword 3 */
पूर्ण;

#घोषणा RESP_HDR_INFO_OPCODE_SHIFT	0	/* bits 0 - 7 */
#घोषणा RESP_HDR_INFO_SUBSYS_SHIFT	8 	/* bits 8 - 15 */
काष्ठा be_cmd_resp_hdr अणु
	u8 opcode;		/* dword 0 */
	u8 subप्रणाली;		/* dword 0 */
	u8 rsvd[2];		/* dword 0 */
	u8 base_status;		/* dword 1 */
	u8 addl_status;		/* dword 1 */
	u8 rsvd1[2];		/* dword 1 */
	u32 response_length;	/* dword 2 */
	u32 actual_resp_len;	/* dword 3 */
पूर्ण;

काष्ठा phys_addr अणु
	u32 lo;
	u32 hi;
पूर्ण;

/**************************
 * BE Command definitions *
 **************************/

/* Pseuकरो amap definition in which each bit of the actual काष्ठाure is defined
 * as a byte: used to calculate offset/shअगरt/mask of each field */
काष्ठा amap_eq_context अणु
	u8 cidx[13];		/* dword 0*/
	u8 rsvd0[3];		/* dword 0*/
	u8 epidx[13];		/* dword 0*/
	u8 valid;		/* dword 0*/
	u8 rsvd1;		/* dword 0*/
	u8 size;		/* dword 0*/
	u8 pidx[13];		/* dword 1*/
	u8 rsvd2[3];		/* dword 1*/
	u8 pd[10];		/* dword 1*/
	u8 count[3];		/* dword 1*/
	u8 solevent;		/* dword 1*/
	u8 stalled;		/* dword 1*/
	u8 armed;		/* dword 1*/
	u8 rsvd3[4];		/* dword 2*/
	u8 func[8];		/* dword 2*/
	u8 rsvd4;		/* dword 2*/
	u8 delaymult[10];	/* dword 2*/
	u8 rsvd5[2];		/* dword 2*/
	u8 phase[2];		/* dword 2*/
	u8 nodelay;		/* dword 2*/
	u8 rsvd6[4];		/* dword 2*/
	u8 rsvd7[32];		/* dword 3*/
पूर्ण __packed;

काष्ठा be_cmd_req_eq_create अणु
	काष्ठा be_cmd_req_hdr hdr;
	u16 num_pages;		/* sword */
	u16 rsvd0;		/* sword */
	u8 context[माप(काष्ठा amap_eq_context) / 8];
	काष्ठा phys_addr pages[8];
पूर्ण __packed;

काष्ठा be_cmd_resp_eq_create अणु
	काष्ठा be_cmd_resp_hdr resp_hdr;
	u16 eq_id;		/* sword */
	u16 msix_idx;		/* available only in v2 */
पूर्ण __packed;

/******************** Mac query ***************************/
क्रमागत अणु
	MAC_ADDRESS_TYPE_STORAGE = 0x0,
	MAC_ADDRESS_TYPE_NETWORK = 0x1,
	MAC_ADDRESS_TYPE_PD = 0x2,
	MAC_ADDRESS_TYPE_MANAGEMENT = 0x3
पूर्ण;

काष्ठा mac_addr अणु
	u16 size_of_काष्ठा;
	u8 addr[ETH_ALEN];
पूर्ण __packed;

काष्ठा be_cmd_req_mac_query अणु
	काष्ठा be_cmd_req_hdr hdr;
	u8 type;
	u8 permanent;
	u16 अगर_id;
	u32 pmac_id;
पूर्ण __packed;

काष्ठा be_cmd_resp_mac_query अणु
	काष्ठा be_cmd_resp_hdr hdr;
	काष्ठा mac_addr mac;
पूर्ण;

/******************** PMac Add ***************************/
काष्ठा be_cmd_req_pmac_add अणु
	काष्ठा be_cmd_req_hdr hdr;
	u32 अगर_id;
	u8 mac_address[ETH_ALEN];
	u8 rsvd0[2];
पूर्ण __packed;

काष्ठा be_cmd_resp_pmac_add अणु
	काष्ठा be_cmd_resp_hdr hdr;
	u32 pmac_id;
पूर्ण;

/******************** PMac Del ***************************/
काष्ठा be_cmd_req_pmac_del अणु
	काष्ठा be_cmd_req_hdr hdr;
	u32 अगर_id;
	u32 pmac_id;
पूर्ण;

/******************** Create CQ ***************************/
/* Pseuकरो amap definition in which each bit of the actual काष्ठाure is defined
 * as a byte: used to calculate offset/shअगरt/mask of each field */
काष्ठा amap_cq_context_be अणु
	u8 cidx[11];		/* dword 0*/
	u8 rsvd0;		/* dword 0*/
	u8 coalescwm[2];	/* dword 0*/
	u8 nodelay;		/* dword 0*/
	u8 epidx[11];		/* dword 0*/
	u8 rsvd1;		/* dword 0*/
	u8 count[2];		/* dword 0*/
	u8 valid;		/* dword 0*/
	u8 solevent;		/* dword 0*/
	u8 eventable;		/* dword 0*/
	u8 pidx[11];		/* dword 1*/
	u8 rsvd2;		/* dword 1*/
	u8 pd[10];		/* dword 1*/
	u8 eqid[8];		/* dword 1*/
	u8 stalled;		/* dword 1*/
	u8 armed;		/* dword 1*/
	u8 rsvd3[4];		/* dword 2*/
	u8 func[8];		/* dword 2*/
	u8 rsvd4[20];		/* dword 2*/
	u8 rsvd5[32];		/* dword 3*/
पूर्ण __packed;

काष्ठा amap_cq_context_v2 अणु
	u8 rsvd0[12];		/* dword 0*/
	u8 coalescwm[2];	/* dword 0*/
	u8 nodelay;		/* dword 0*/
	u8 rsvd1[12];		/* dword 0*/
	u8 count[2];		/* dword 0*/
	u8 valid;		/* dword 0*/
	u8 rsvd2;		/* dword 0*/
	u8 eventable;		/* dword 0*/
	u8 eqid[16];		/* dword 1*/
	u8 rsvd3[15];		/* dword 1*/
	u8 armed;		/* dword 1*/
	u8 rsvd4[32];		/* dword 2*/
	u8 rsvd5[32];		/* dword 3*/
पूर्ण __packed;

काष्ठा be_cmd_req_cq_create अणु
	काष्ठा be_cmd_req_hdr hdr;
	u16 num_pages;
	u8 page_size;
	u8 rsvd0;
	u8 context[माप(काष्ठा amap_cq_context_be) / 8];
	काष्ठा phys_addr pages[8];
पूर्ण __packed;


काष्ठा be_cmd_resp_cq_create अणु
	काष्ठा be_cmd_resp_hdr hdr;
	u16 cq_id;
	u16 rsvd0;
पूर्ण __packed;

काष्ठा be_cmd_req_get_fat अणु
	काष्ठा be_cmd_req_hdr hdr;
	u32 fat_operation;
	u32 पढ़ो_log_offset;
	u32 पढ़ो_log_length;
	u32 data_buffer_size;
	u32 data_buffer[1];
पूर्ण __packed;

काष्ठा be_cmd_resp_get_fat अणु
	काष्ठा be_cmd_resp_hdr hdr;
	u32 log_size;
	u32 पढ़ो_log_length;
	u32 rsvd[2];
	u32 data_buffer[1];
पूर्ण __packed;


/******************** Create MCCQ ***************************/
/* Pseuकरो amap definition in which each bit of the actual काष्ठाure is defined
 * as a byte: used to calculate offset/shअगरt/mask of each field */
काष्ठा amap_mcc_context_be अणु
	u8 con_index[14];
	u8 rsvd0[2];
	u8 ring_size[4];
	u8 fetch_wrb;
	u8 fetch_r2t;
	u8 cq_id[10];
	u8 prod_index[14];
	u8 fid[8];
	u8 pdid[9];
	u8 valid;
	u8 rsvd1[32];
	u8 rsvd2[32];
पूर्ण __packed;

काष्ठा amap_mcc_context_v1 अणु
	u8 async_cq_id[16];
	u8 ring_size[4];
	u8 rsvd0[12];
	u8 rsvd1[31];
	u8 valid;
	u8 async_cq_valid[1];
	u8 rsvd2[31];
	u8 rsvd3[32];
पूर्ण __packed;

काष्ठा be_cmd_req_mcc_create अणु
	काष्ठा be_cmd_req_hdr hdr;
	u16 num_pages;
	u16 cq_id;
	u8 context[माप(काष्ठा amap_mcc_context_be) / 8];
	काष्ठा phys_addr pages[8];
पूर्ण __packed;

काष्ठा be_cmd_req_mcc_ext_create अणु
	काष्ठा be_cmd_req_hdr hdr;
	u16 num_pages;
	u16 cq_id;
	u32 async_event_biपंचांगap[1];
	u8 context[माप(काष्ठा amap_mcc_context_v1) / 8];
	काष्ठा phys_addr pages[8];
पूर्ण __packed;

काष्ठा be_cmd_resp_mcc_create अणु
	काष्ठा be_cmd_resp_hdr hdr;
	u16 id;
	u16 rsvd0;
पूर्ण __packed;

/******************** Create TxQ ***************************/
#घोषणा BE_ETH_TX_RING_TYPE_STANDARD    	2
#घोषणा BE_ULP1_NUM				1

काष्ठा be_cmd_req_eth_tx_create अणु
	काष्ठा be_cmd_req_hdr hdr;
	u8 num_pages;
	u8 ulp_num;
	u16 type;
	u16 अगर_id;
	u8 queue_size;
	u8 rsvd0;
	u32 rsvd1;
	u16 cq_id;
	u16 rsvd2;
	u32 rsvd3[13];
	काष्ठा phys_addr pages[8];
पूर्ण __packed;

काष्ठा be_cmd_resp_eth_tx_create अणु
	काष्ठा be_cmd_resp_hdr hdr;
	u16 cid;
	u16 rid;
	u32 db_offset;
	u32 rsvd0[4];
पूर्ण __packed;

/******************** Create RxQ ***************************/
काष्ठा be_cmd_req_eth_rx_create अणु
	काष्ठा be_cmd_req_hdr hdr;
	u16 cq_id;
	u8 frag_size;
	u8 num_pages;
	काष्ठा phys_addr pages[2];
	u32 पूर्णांकerface_id;
	u16 max_frame_size;
	u16 rsvd0;
	u32 rss_queue;
पूर्ण __packed;

काष्ठा be_cmd_resp_eth_rx_create अणु
	काष्ठा be_cmd_resp_hdr hdr;
	u16 id;
	u8 rss_id;
	u8 rsvd0;
पूर्ण __packed;

/******************** Q Destroy  ***************************/
/* Type of Queue to be destroyed */
क्रमागत अणु
	QTYPE_EQ = 1,
	QTYPE_CQ,
	QTYPE_TXQ,
	QTYPE_RXQ,
	QTYPE_MCCQ
पूर्ण;

काष्ठा be_cmd_req_q_destroy अणु
	काष्ठा be_cmd_req_hdr hdr;
	u16 id;
	u16 bypass_flush;	/* valid only क्रम rx q destroy */
पूर्ण __packed;

/************ I/f Create (it's actually I/f Config Create)**********/

/* Capability flags क्रम the i/f */
क्रमागत be_अगर_flags अणु
	BE_IF_FLAGS_RSS = 0x4,
	BE_IF_FLAGS_PROMISCUOUS = 0x8,
	BE_IF_FLAGS_BROADCAST = 0x10,
	BE_IF_FLAGS_UNTAGGED = 0x20,
	BE_IF_FLAGS_ULP = 0x40,
	BE_IF_FLAGS_VLAN_PROMISCUOUS = 0x80,
	BE_IF_FLAGS_VLAN = 0x100,
	BE_IF_FLAGS_MCAST_PROMISCUOUS = 0x200,
	BE_IF_FLAGS_PASS_L2_ERRORS = 0x400,
	BE_IF_FLAGS_PASS_L3L4_ERRORS = 0x800,
	BE_IF_FLAGS_MULTICAST = 0x1000,
	BE_IF_FLAGS_DEFQ_RSS = 0x1000000
पूर्ण;

#घोषणा BE_IF_CAP_FLAGS_WANT (BE_IF_FLAGS_RSS | BE_IF_FLAGS_PROMISCUOUS |\
			 BE_IF_FLAGS_BROADCAST | BE_IF_FLAGS_VLAN_PROMISCUOUS |\
			 BE_IF_FLAGS_VLAN | BE_IF_FLAGS_MCAST_PROMISCUOUS |\
			 BE_IF_FLAGS_PASS_L3L4_ERRORS | BE_IF_FLAGS_MULTICAST |\
			 BE_IF_FLAGS_UNTAGGED | BE_IF_FLAGS_DEFQ_RSS)

#घोषणा BE_IF_FLAGS_ALL_PROMISCUOUS	(BE_IF_FLAGS_PROMISCUOUS | \
					 BE_IF_FLAGS_VLAN_PROMISCUOUS |\
					 BE_IF_FLAGS_MCAST_PROMISCUOUS)

#घोषणा BE_IF_FILT_FLAGS_BASIC (BE_IF_FLAGS_BROADCAST | \
				BE_IF_FLAGS_PASS_L3L4_ERRORS | \
				BE_IF_FLAGS_UNTAGGED)

#घोषणा BE_IF_ALL_FILT_FLAGS	(BE_IF_FILT_FLAGS_BASIC | \
				 BE_IF_FLAGS_MULTICAST | \
				 BE_IF_FLAGS_ALL_PROMISCUOUS)

/* An RX पूर्णांकerface is an object with one or more MAC addresses and
 * filtering capabilities. */
काष्ठा be_cmd_req_अगर_create अणु
	काष्ठा be_cmd_req_hdr hdr;
	u32 version;		/* ignore currently */
	u32 capability_flags;
	u32 enable_flags;
	u8 mac_addr[ETH_ALEN];
	u8 rsvd0;
	u8 pmac_invalid; /* अगर set, करोn't attach the mac addr to the i/f */
	u32 vlan_tag;	 /* not used currently */
पूर्ण __packed;

काष्ठा be_cmd_resp_अगर_create अणु
	काष्ठा be_cmd_resp_hdr hdr;
	u32 पूर्णांकerface_id;
	u32 pmac_id;
पूर्ण;

/****** I/f Destroy(it's actually I/f Config Destroy )**********/
काष्ठा be_cmd_req_अगर_destroy अणु
	काष्ठा be_cmd_req_hdr hdr;
	u32 पूर्णांकerface_id;
पूर्ण;

/*************** HW Stats Get **********************************/
काष्ठा be_port_rxf_stats_v0 अणु
	u32 rx_bytes_lsd;	/* dword 0*/
	u32 rx_bytes_msd;	/* dword 1*/
	u32 rx_total_frames;	/* dword 2*/
	u32 rx_unicast_frames;	/* dword 3*/
	u32 rx_multicast_frames;	/* dword 4*/
	u32 rx_broadcast_frames;	/* dword 5*/
	u32 rx_crc_errors;	/* dword 6*/
	u32 rx_alignment_symbol_errors;	/* dword 7*/
	u32 rx_छोड़ो_frames;	/* dword 8*/
	u32 rx_control_frames;	/* dword 9*/
	u32 rx_in_range_errors;	/* dword 10*/
	u32 rx_out_range_errors;	/* dword 11*/
	u32 rx_frame_too_दीर्घ;	/* dword 12*/
	u32 rx_address_filtered;	/* dword 13*/
	u32 rx_vlan_filtered;	/* dword 14*/
	u32 rx_dropped_too_small;	/* dword 15*/
	u32 rx_dropped_too_लघु;	/* dword 16*/
	u32 rx_dropped_header_too_small;	/* dword 17*/
	u32 rx_dropped_tcp_length;	/* dword 18*/
	u32 rx_dropped_runt;	/* dword 19*/
	u32 rx_64_byte_packets;	/* dword 20*/
	u32 rx_65_127_byte_packets;	/* dword 21*/
	u32 rx_128_256_byte_packets;	/* dword 22*/
	u32 rx_256_511_byte_packets;	/* dword 23*/
	u32 rx_512_1023_byte_packets;	/* dword 24*/
	u32 rx_1024_1518_byte_packets;	/* dword 25*/
	u32 rx_1519_2047_byte_packets;	/* dword 26*/
	u32 rx_2048_4095_byte_packets;	/* dword 27*/
	u32 rx_4096_8191_byte_packets;	/* dword 28*/
	u32 rx_8192_9216_byte_packets;	/* dword 29*/
	u32 rx_ip_checksum_errs;	/* dword 30*/
	u32 rx_tcp_checksum_errs;	/* dword 31*/
	u32 rx_udp_checksum_errs;	/* dword 32*/
	u32 rx_non_rss_packets;	/* dword 33*/
	u32 rx_ipv4_packets;	/* dword 34*/
	u32 rx_ipv6_packets;	/* dword 35*/
	u32 rx_ipv4_bytes_lsd;	/* dword 36*/
	u32 rx_ipv4_bytes_msd;	/* dword 37*/
	u32 rx_ipv6_bytes_lsd;	/* dword 38*/
	u32 rx_ipv6_bytes_msd;	/* dword 39*/
	u32 rx_chute1_packets;	/* dword 40*/
	u32 rx_chute2_packets;	/* dword 41*/
	u32 rx_chute3_packets;	/* dword 42*/
	u32 rx_management_packets;	/* dword 43*/
	u32 rx_चयनed_unicast_packets;	/* dword 44*/
	u32 rx_चयनed_multicast_packets;	/* dword 45*/
	u32 rx_चयनed_broadcast_packets;	/* dword 46*/
	u32 tx_bytes_lsd;	/* dword 47*/
	u32 tx_bytes_msd;	/* dword 48*/
	u32 tx_unicastframes;	/* dword 49*/
	u32 tx_multicastframes;	/* dword 50*/
	u32 tx_broadcastframes;	/* dword 51*/
	u32 tx_छोड़ोframes;	/* dword 52*/
	u32 tx_controlframes;	/* dword 53*/
	u32 tx_64_byte_packets;	/* dword 54*/
	u32 tx_65_127_byte_packets;	/* dword 55*/
	u32 tx_128_256_byte_packets;	/* dword 56*/
	u32 tx_256_511_byte_packets;	/* dword 57*/
	u32 tx_512_1023_byte_packets;	/* dword 58*/
	u32 tx_1024_1518_byte_packets;	/* dword 59*/
	u32 tx_1519_2047_byte_packets;	/* dword 60*/
	u32 tx_2048_4095_byte_packets;	/* dword 61*/
	u32 tx_4096_8191_byte_packets;	/* dword 62*/
	u32 tx_8192_9216_byte_packets;	/* dword 63*/
	u32 rx_fअगरo_overflow;	/* dword 64*/
	u32 rx_input_fअगरo_overflow;	/* dword 65*/
पूर्ण;

काष्ठा be_rxf_stats_v0 अणु
	काष्ठा be_port_rxf_stats_v0 port[2];
	u32 rx_drops_no_pbuf;	/* dword 132*/
	u32 rx_drops_no_txpb;	/* dword 133*/
	u32 rx_drops_no_erx_descr;	/* dword 134*/
	u32 rx_drops_no_tpre_descr;	/* dword 135*/
	u32 management_rx_port_packets;	/* dword 136*/
	u32 management_rx_port_bytes;	/* dword 137*/
	u32 management_rx_port_छोड़ो_frames;	/* dword 138*/
	u32 management_rx_port_errors;	/* dword 139*/
	u32 management_tx_port_packets;	/* dword 140*/
	u32 management_tx_port_bytes;	/* dword 141*/
	u32 management_tx_port_छोड़ो;	/* dword 142*/
	u32 management_rx_port_rxfअगरo_overflow;	/* dword 143*/
	u32 rx_drops_too_many_frags;	/* dword 144*/
	u32 rx_drops_invalid_ring;	/* dword 145*/
	u32 क्रमwarded_packets;	/* dword 146*/
	u32 rx_drops_mtu;	/* dword 147*/
	u32 rsvd0[7];
	u32 port0_jabber_events;
	u32 port1_jabber_events;
	u32 rsvd1[6];
पूर्ण;

काष्ठा be_erx_stats_v0 अणु
	u32 rx_drops_no_fragments[44];     /* dwordS 0 to 43*/
	u32 rsvd[4];
पूर्ण;

काष्ठा be_pmem_stats अणु
	u32 eth_red_drops;
	u32 rsvd[5];
पूर्ण;

काष्ठा be_hw_stats_v0 अणु
	काष्ठा be_rxf_stats_v0 rxf;
	u32 rsvd[48];
	काष्ठा be_erx_stats_v0 erx;
	काष्ठा be_pmem_stats pmem;
पूर्ण;

काष्ठा be_cmd_req_get_stats_v0 अणु
	काष्ठा be_cmd_req_hdr hdr;
	u8 rsvd[माप(काष्ठा be_hw_stats_v0)];
पूर्ण;

काष्ठा be_cmd_resp_get_stats_v0 अणु
	काष्ठा be_cmd_resp_hdr hdr;
	काष्ठा be_hw_stats_v0 hw_stats;
पूर्ण;

काष्ठा lancer_pport_stats अणु
	u32 tx_packets_lo;
	u32 tx_packets_hi;
	u32 tx_unicast_packets_lo;
	u32 tx_unicast_packets_hi;
	u32 tx_multicast_packets_lo;
	u32 tx_multicast_packets_hi;
	u32 tx_broadcast_packets_lo;
	u32 tx_broadcast_packets_hi;
	u32 tx_bytes_lo;
	u32 tx_bytes_hi;
	u32 tx_unicast_bytes_lo;
	u32 tx_unicast_bytes_hi;
	u32 tx_multicast_bytes_lo;
	u32 tx_multicast_bytes_hi;
	u32 tx_broadcast_bytes_lo;
	u32 tx_broadcast_bytes_hi;
	u32 tx_discards_lo;
	u32 tx_discards_hi;
	u32 tx_errors_lo;
	u32 tx_errors_hi;
	u32 tx_छोड़ो_frames_lo;
	u32 tx_छोड़ो_frames_hi;
	u32 tx_छोड़ो_on_frames_lo;
	u32 tx_छोड़ो_on_frames_hi;
	u32 tx_छोड़ो_off_frames_lo;
	u32 tx_छोड़ो_off_frames_hi;
	u32 tx_पूर्णांकernal_mac_errors_lo;
	u32 tx_पूर्णांकernal_mac_errors_hi;
	u32 tx_control_frames_lo;
	u32 tx_control_frames_hi;
	u32 tx_packets_64_bytes_lo;
	u32 tx_packets_64_bytes_hi;
	u32 tx_packets_65_to_127_bytes_lo;
	u32 tx_packets_65_to_127_bytes_hi;
	u32 tx_packets_128_to_255_bytes_lo;
	u32 tx_packets_128_to_255_bytes_hi;
	u32 tx_packets_256_to_511_bytes_lo;
	u32 tx_packets_256_to_511_bytes_hi;
	u32 tx_packets_512_to_1023_bytes_lo;
	u32 tx_packets_512_to_1023_bytes_hi;
	u32 tx_packets_1024_to_1518_bytes_lo;
	u32 tx_packets_1024_to_1518_bytes_hi;
	u32 tx_packets_1519_to_2047_bytes_lo;
	u32 tx_packets_1519_to_2047_bytes_hi;
	u32 tx_packets_2048_to_4095_bytes_lo;
	u32 tx_packets_2048_to_4095_bytes_hi;
	u32 tx_packets_4096_to_8191_bytes_lo;
	u32 tx_packets_4096_to_8191_bytes_hi;
	u32 tx_packets_8192_to_9216_bytes_lo;
	u32 tx_packets_8192_to_9216_bytes_hi;
	u32 tx_lso_packets_lo;
	u32 tx_lso_packets_hi;
	u32 rx_packets_lo;
	u32 rx_packets_hi;
	u32 rx_unicast_packets_lo;
	u32 rx_unicast_packets_hi;
	u32 rx_multicast_packets_lo;
	u32 rx_multicast_packets_hi;
	u32 rx_broadcast_packets_lo;
	u32 rx_broadcast_packets_hi;
	u32 rx_bytes_lo;
	u32 rx_bytes_hi;
	u32 rx_unicast_bytes_lo;
	u32 rx_unicast_bytes_hi;
	u32 rx_multicast_bytes_lo;
	u32 rx_multicast_bytes_hi;
	u32 rx_broadcast_bytes_lo;
	u32 rx_broadcast_bytes_hi;
	u32 rx_unknown_protos;
	u32 rsvd_69; /* Word 69 is reserved */
	u32 rx_discards_lo;
	u32 rx_discards_hi;
	u32 rx_errors_lo;
	u32 rx_errors_hi;
	u32 rx_crc_errors_lo;
	u32 rx_crc_errors_hi;
	u32 rx_alignment_errors_lo;
	u32 rx_alignment_errors_hi;
	u32 rx_symbol_errors_lo;
	u32 rx_symbol_errors_hi;
	u32 rx_छोड़ो_frames_lo;
	u32 rx_छोड़ो_frames_hi;
	u32 rx_छोड़ो_on_frames_lo;
	u32 rx_छोड़ो_on_frames_hi;
	u32 rx_छोड़ो_off_frames_lo;
	u32 rx_छोड़ो_off_frames_hi;
	u32 rx_frames_too_दीर्घ_lo;
	u32 rx_frames_too_दीर्घ_hi;
	u32 rx_पूर्णांकernal_mac_errors_lo;
	u32 rx_पूर्णांकernal_mac_errors_hi;
	u32 rx_undersize_packets;
	u32 rx_oversize_packets;
	u32 rx_fragment_packets;
	u32 rx_jabbers;
	u32 rx_control_frames_lo;
	u32 rx_control_frames_hi;
	u32 rx_control_frames_unknown_opcode_lo;
	u32 rx_control_frames_unknown_opcode_hi;
	u32 rx_in_range_errors;
	u32 rx_out_of_range_errors;
	u32 rx_address_filtered;
	u32 rx_vlan_filtered;
	u32 rx_dropped_too_small;
	u32 rx_dropped_too_लघु;
	u32 rx_dropped_header_too_small;
	u32 rx_dropped_invalid_tcp_length;
	u32 rx_dropped_runt;
	u32 rx_ip_checksum_errors;
	u32 rx_tcp_checksum_errors;
	u32 rx_udp_checksum_errors;
	u32 rx_non_rss_packets;
	u32 rsvd_111;
	u32 rx_ipv4_packets_lo;
	u32 rx_ipv4_packets_hi;
	u32 rx_ipv6_packets_lo;
	u32 rx_ipv6_packets_hi;
	u32 rx_ipv4_bytes_lo;
	u32 rx_ipv4_bytes_hi;
	u32 rx_ipv6_bytes_lo;
	u32 rx_ipv6_bytes_hi;
	u32 rx_nic_packets_lo;
	u32 rx_nic_packets_hi;
	u32 rx_tcp_packets_lo;
	u32 rx_tcp_packets_hi;
	u32 rx_iscsi_packets_lo;
	u32 rx_iscsi_packets_hi;
	u32 rx_management_packets_lo;
	u32 rx_management_packets_hi;
	u32 rx_चयनed_unicast_packets_lo;
	u32 rx_चयनed_unicast_packets_hi;
	u32 rx_चयनed_multicast_packets_lo;
	u32 rx_चयनed_multicast_packets_hi;
	u32 rx_चयनed_broadcast_packets_lo;
	u32 rx_चयनed_broadcast_packets_hi;
	u32 num_क्रमwards_lo;
	u32 num_क्रमwards_hi;
	u32 rx_fअगरo_overflow;
	u32 rx_input_fअगरo_overflow;
	u32 rx_drops_too_many_frags_lo;
	u32 rx_drops_too_many_frags_hi;
	u32 rx_drops_invalid_queue;
	u32 rsvd_141;
	u32 rx_drops_mtu_lo;
	u32 rx_drops_mtu_hi;
	u32 rx_packets_64_bytes_lo;
	u32 rx_packets_64_bytes_hi;
	u32 rx_packets_65_to_127_bytes_lo;
	u32 rx_packets_65_to_127_bytes_hi;
	u32 rx_packets_128_to_255_bytes_lo;
	u32 rx_packets_128_to_255_bytes_hi;
	u32 rx_packets_256_to_511_bytes_lo;
	u32 rx_packets_256_to_511_bytes_hi;
	u32 rx_packets_512_to_1023_bytes_lo;
	u32 rx_packets_512_to_1023_bytes_hi;
	u32 rx_packets_1024_to_1518_bytes_lo;
	u32 rx_packets_1024_to_1518_bytes_hi;
	u32 rx_packets_1519_to_2047_bytes_lo;
	u32 rx_packets_1519_to_2047_bytes_hi;
	u32 rx_packets_2048_to_4095_bytes_lo;
	u32 rx_packets_2048_to_4095_bytes_hi;
	u32 rx_packets_4096_to_8191_bytes_lo;
	u32 rx_packets_4096_to_8191_bytes_hi;
	u32 rx_packets_8192_to_9216_bytes_lo;
	u32 rx_packets_8192_to_9216_bytes_hi;
पूर्ण;

काष्ठा pport_stats_params अणु
	u16 pport_num;
	u8 rsvd;
	u8 reset_stats;
पूर्ण;

काष्ठा lancer_cmd_req_pport_stats अणु
	काष्ठा be_cmd_req_hdr hdr;
	जोड़ अणु
		काष्ठा pport_stats_params params;
		u8 rsvd[माप(काष्ठा lancer_pport_stats)];
	पूर्ण cmd_params;
पूर्ण;

काष्ठा lancer_cmd_resp_pport_stats अणु
	काष्ठा be_cmd_resp_hdr hdr;
	काष्ठा lancer_pport_stats pport_stats;
पूर्ण;

अटल अंतरभूत काष्ठा lancer_pport_stats*
	pport_stats_from_cmd(काष्ठा be_adapter *adapter)
अणु
	काष्ठा lancer_cmd_resp_pport_stats *cmd = adapter->stats_cmd.va;
	वापस &cmd->pport_stats;
पूर्ण

काष्ठा be_cmd_req_get_cntl_addnl_attribs अणु
	काष्ठा be_cmd_req_hdr hdr;
	u8 rsvd[8];
पूर्ण;

काष्ठा be_cmd_resp_get_cntl_addnl_attribs अणु
	काष्ठा be_cmd_resp_hdr hdr;
	u16 ipl_file_number;
	u8 ipl_file_version;
	u8 rsvd0;
	u8 on_die_temperature; /* in degrees centigrade*/
	u8 rsvd1[3];
पूर्ण;

काष्ठा be_cmd_req_vlan_config अणु
	काष्ठा be_cmd_req_hdr hdr;
	u8 पूर्णांकerface_id;
	u8 promiscuous;
	u8 untagged;
	u8 num_vlan;
	u16 normal_vlan[64];
पूर्ण __packed;

/******************* RX FILTER ******************************/
#घोषणा BE_MAX_MC		64 /* set mcast promisc अगर > 64 */
काष्ठा macaddr अणु
	u8 byte[ETH_ALEN];
पूर्ण;

काष्ठा be_cmd_req_rx_filter अणु
	काष्ठा be_cmd_req_hdr hdr;
	u32 global_flags_mask;
	u32 global_flags;
	u32 अगर_flags_mask;
	u32 अगर_flags;
	u32 अगर_id;
	u32 mcast_num;
	काष्ठा macaddr mcast_mac[BE_MAX_MC];
पूर्ण;

/******************** Link Status Query *******************/
काष्ठा be_cmd_req_link_status अणु
	काष्ठा be_cmd_req_hdr hdr;
	u32 rsvd;
पूर्ण;

क्रमागत अणु
	PHY_LINK_DUPLEX_NONE = 0x0,
	PHY_LINK_DUPLEX_HALF = 0x1,
	PHY_LINK_DUPLEX_FULL = 0x2
पूर्ण;

क्रमागत अणु
	PHY_LINK_SPEED_ZERO = 0x0, 	/* => No link */
	PHY_LINK_SPEED_10MBPS = 0x1,
	PHY_LINK_SPEED_100MBPS = 0x2,
	PHY_LINK_SPEED_1GBPS = 0x3,
	PHY_LINK_SPEED_10GBPS = 0x4,
	PHY_LINK_SPEED_20GBPS = 0x5,
	PHY_LINK_SPEED_25GBPS = 0x6,
	PHY_LINK_SPEED_40GBPS = 0x7
पूर्ण;

काष्ठा be_cmd_resp_link_status अणु
	काष्ठा be_cmd_resp_hdr hdr;
	u8 physical_port;
	u8 mac_duplex;
	u8 mac_speed;
	u8 mac_fault;
	u8 mgmt_mac_duplex;
	u8 mgmt_mac_speed;
	u16 link_speed;
	u8 logical_link_status;
	u8 rsvd1[3];
पूर्ण __packed;

/******************** Port Identअगरication ***************************/
/*    Identअगरies the type of port attached to NIC     */
काष्ठा be_cmd_req_port_type अणु
	काष्ठा be_cmd_req_hdr hdr;
	__le32 page_num;
	__le32 port;
पूर्ण;

क्रमागत अणु
	TR_PAGE_A0 = 0xa0,
	TR_PAGE_A2 = 0xa2
पूर्ण;

/* From SFF-8436 QSFP+ spec */
#घोषणा	QSFP_PLUS_CABLE_TYPE_OFFSET	0x83
#घोषणा	QSFP_PLUS_CR4_CABLE		0x8
#घोषणा	QSFP_PLUS_SR4_CABLE		0x4
#घोषणा	QSFP_PLUS_LR4_CABLE		0x2

/* From SFF-8472 spec */
#घोषणा	SFP_PLUS_SFF_8472_COMP		0x5E
#घोषणा	SFP_PLUS_CABLE_TYPE_OFFSET	0x8
#घोषणा	SFP_PLUS_COPPER_CABLE		0x4
#घोषणा SFP_VENDOR_NAME_OFFSET		0x14
#घोषणा SFP_VENDOR_PN_OFFSET		0x28

#घोषणा PAGE_DATA_LEN   256
काष्ठा be_cmd_resp_port_type अणु
	काष्ठा be_cmd_resp_hdr hdr;
	u32 page_num;
	u32 port;
	u8  page_data[PAGE_DATA_LEN];
पूर्ण;

/******************** Get FW Version *******************/
काष्ठा be_cmd_req_get_fw_version अणु
	काष्ठा be_cmd_req_hdr hdr;
	u8 rsvd0[FW_VER_LEN];
	u8 rsvd1[FW_VER_LEN];
पूर्ण __packed;

काष्ठा be_cmd_resp_get_fw_version अणु
	काष्ठा be_cmd_resp_hdr hdr;
	u8 firmware_version_string[FW_VER_LEN];
	u8 fw_on_flash_version_string[FW_VER_LEN];
पूर्ण __packed;

/******************** Set Flow Contrl *******************/
काष्ठा be_cmd_req_set_flow_control अणु
	काष्ठा be_cmd_req_hdr hdr;
	u16 tx_flow_control;
	u16 rx_flow_control;
पूर्ण __packed;

/******************** Get Flow Contrl *******************/
काष्ठा be_cmd_req_get_flow_control अणु
	काष्ठा be_cmd_req_hdr hdr;
	u32 rsvd;
पूर्ण;

काष्ठा be_cmd_resp_get_flow_control अणु
	काष्ठा be_cmd_resp_hdr hdr;
	u16 tx_flow_control;
	u16 rx_flow_control;
पूर्ण __packed;

/******************** Modअगरy EQ Delay *******************/
काष्ठा be_set_eqd अणु
	u32 eq_id;
	u32 phase;
	u32 delay_multiplier;
पूर्ण;

काष्ठा be_cmd_req_modअगरy_eq_delay अणु
	काष्ठा be_cmd_req_hdr hdr;
	u32 num_eq;
	काष्ठा be_set_eqd set_eqd[MAX_EVT_QS];
पूर्ण __packed;

/******************** Get FW Config *******************/
/* The HW can come up in either of the following multi-channel modes
 * based on the skew/IPL.
 */
#घोषणा RDMA_ENABLED				0x4
#घोषणा QNQ_MODE				0x400
#घोषणा VNIC_MODE				0x20000
#घोषणा UMC_ENABLED				0x1000000
काष्ठा be_cmd_req_query_fw_cfg अणु
	काष्ठा be_cmd_req_hdr hdr;
	u32 rsvd[31];
पूर्ण;

काष्ठा be_cmd_resp_query_fw_cfg अणु
	काष्ठा be_cmd_resp_hdr hdr;
	u32 be_config_number;
	u32 asic_revision;
	u32 phys_port;
	u32 function_mode;
	u32 rsvd[26];
	u32 function_caps;
पूर्ण;

/******************** RSS Config ****************************************/
/* RSS type		Input parameters used to compute RX hash
 * RSS_ENABLE_IPV4	SRC IPv4, DST IPv4
 * RSS_ENABLE_TCP_IPV4	SRC IPv4, DST IPv4, TCP SRC PORT, TCP DST PORT
 * RSS_ENABLE_IPV6	SRC IPv6, DST IPv6
 * RSS_ENABLE_TCP_IPV6	SRC IPv6, DST IPv6, TCP SRC PORT, TCP DST PORT
 * RSS_ENABLE_UDP_IPV4	SRC IPv4, DST IPv4, UDP SRC PORT, UDP DST PORT
 * RSS_ENABLE_UDP_IPV6	SRC IPv6, DST IPv6, UDP SRC PORT, UDP DST PORT
 *
 * When multiple RSS types are enabled, HW picks the best hash policy
 * based on the type of the received packet.
 */
#घोषणा RSS_ENABLE_NONE				0x0
#घोषणा RSS_ENABLE_IPV4				0x1
#घोषणा RSS_ENABLE_TCP_IPV4			0x2
#घोषणा RSS_ENABLE_IPV6				0x4
#घोषणा RSS_ENABLE_TCP_IPV6			0x8
#घोषणा RSS_ENABLE_UDP_IPV4			0x10
#घोषणा RSS_ENABLE_UDP_IPV6			0x20

#घोषणा L3_RSS_FLAGS				(RXH_IP_DST | RXH_IP_SRC)
#घोषणा L4_RSS_FLAGS				(RXH_L4_B_0_1 | RXH_L4_B_2_3)

काष्ठा be_cmd_req_rss_config अणु
	काष्ठा be_cmd_req_hdr hdr;
	u32 अगर_id;
	u16 enable_rss;
	u16 cpu_table_size_log2;
	u32 hash[10];
	u8 cpu_table[128];
	u8 flush;
	u8 rsvd0[3];
पूर्ण;

/******************** Port Beacon ***************************/

#घोषणा BEACON_STATE_ENABLED		0x1
#घोषणा BEACON_STATE_DISABLED		0x0

काष्ठा be_cmd_req_enable_disable_beacon अणु
	काष्ठा be_cmd_req_hdr hdr;
	u8  port_num;
	u8  beacon_state;
	u8  beacon_duration;
	u8  status_duration;
पूर्ण __packed;

काष्ठा be_cmd_req_get_beacon_state अणु
	काष्ठा be_cmd_req_hdr hdr;
	u8  port_num;
	u8  rsvd0;
	u16 rsvd1;
पूर्ण __packed;

काष्ठा be_cmd_resp_get_beacon_state अणु
	काष्ठा be_cmd_resp_hdr resp_hdr;
	u8 beacon_state;
	u8 rsvd0[3];
पूर्ण __packed;

/* Flashrom related descriptors */
#घोषणा MAX_FLASH_COMP			32

/* Optypes of each component in the UFI */
क्रमागत अणु
	OPTYPE_ISCSI_ACTIVE = 0,
	OPTYPE_REDBOOT = 1,
	OPTYPE_BIOS = 2,
	OPTYPE_PXE_BIOS = 3,
	OPTYPE_OFFSET_SPECIFIED = 7,
	OPTYPE_FCOE_BIOS = 8,
	OPTYPE_ISCSI_BACKUP = 9,
	OPTYPE_FCOE_FW_ACTIVE = 10,
	OPTYPE_FCOE_FW_BACKUP = 11,
	OPTYPE_NCSI_FW = 13,
	OPTYPE_REDBOOT_सूची = 18,
	OPTYPE_REDBOOT_CONFIG = 19,
	OPTYPE_SH_PHY_FW = 21,
	OPTYPE_FLASHISM_JUMPVECTOR = 22,
	OPTYPE_UFI_सूची = 23,
	OPTYPE_PHY_FW = 99
पूर्ण;

/* Maximum sizes of components in BE2 FW UFI */
क्रमागत अणु
	BE2_BIOS_COMP_MAX_SIZE = 0x40000,
	BE2_REDBOOT_COMP_MAX_SIZE = 0x40000,
	BE2_COMP_MAX_SIZE = 0x140000
पूर्ण;

/* Maximum sizes of components in BE3 FW UFI */
क्रमागत अणु
	BE3_NCSI_COMP_MAX_SIZE = 0x40000,
	BE3_PHY_FW_COMP_MAX_SIZE = 0x40000,
	BE3_BIOS_COMP_MAX_SIZE = 0x80000,
	BE3_REDBOOT_COMP_MAX_SIZE = 0x100000,
	BE3_COMP_MAX_SIZE = 0x200000
पूर्ण;

/* Offsets क्रम components in BE2 FW UFI */
क्रमागत अणु
	BE2_REDBOOT_START = 0x8000,
	BE2_FCOE_BIOS_START = 0x80000,
	BE2_ISCSI_PRIMARY_IMAGE_START = 0x100000,
	BE2_ISCSI_BACKUP_IMAGE_START = 0x240000,
	BE2_FCOE_PRIMARY_IMAGE_START = 0x380000,
	BE2_FCOE_BACKUP_IMAGE_START = 0x4c0000,
	BE2_ISCSI_BIOS_START = 0x700000,
	BE2_PXE_BIOS_START = 0x780000
पूर्ण;

/* Offsets क्रम components in BE3 FW UFI */
क्रमागत अणु
	BE3_REDBOOT_START = 0x40000,
	BE3_PHY_FW_START = 0x140000,
	BE3_ISCSI_PRIMARY_IMAGE_START = 0x200000,
	BE3_ISCSI_BACKUP_IMAGE_START = 0x400000,
	BE3_FCOE_PRIMARY_IMAGE_START = 0x600000,
	BE3_FCOE_BACKUP_IMAGE_START = 0x800000,
	BE3_ISCSI_BIOS_START = 0xc00000,
	BE3_PXE_BIOS_START = 0xc80000,
	BE3_FCOE_BIOS_START = 0xd00000,
	BE3_NCSI_START = 0xf40000
पूर्ण;

/* Component entry types */
क्रमागत अणु
	IMAGE_NCSI = 0x10,
	IMAGE_OPTION_ROM_PXE = 0x20,
	IMAGE_OPTION_ROM_FCOE = 0x21,
	IMAGE_OPTION_ROM_ISCSI = 0x22,
	IMAGE_FLASHISM_JUMPVECTOR = 0x30,
	IMAGE_FIRMWARE_ISCSI = 0xa0,
	IMAGE_FIRMWARE_FCOE = 0xa2,
	IMAGE_FIRMWARE_BACKUP_ISCSI = 0xb0,
	IMAGE_FIRMWARE_BACKUP_FCOE = 0xb2,
	IMAGE_FIRMWARE_PHY = 0xc0,
	IMAGE_REDBOOT_सूची = 0xd0,
	IMAGE_REDBOOT_CONFIG = 0xd1,
	IMAGE_UFI_सूची = 0xd2,
	IMAGE_BOOT_CODE = 0xe2
पूर्ण;

काष्ठा controller_id अणु
	u32 venकरोr;
	u32 device;
	u32 subvenकरोr;
	u32 subdevice;
पूर्ण;

काष्ठा flash_comp अणु
	अचिन्हित दीर्घ offset;
	पूर्णांक optype;
	पूर्णांक size;
	पूर्णांक img_type;
पूर्ण;

काष्ठा image_hdr अणु
	u32 imageid;
	u32 imageoffset;
	u32 imagelength;
	u32 image_checksum;
	u8 image_version[32];
पूर्ण;

काष्ठा flash_file_hdr_g2 अणु
	u8 sign[32];
	u32 cksum;
	u32 antiकरोte;
	काष्ठा controller_id cont_id;
	u32 file_len;
	u32 chunk_num;
	u32 total_chunks;
	u32 num_imgs;
	u8 build[24];
पूर्ण;

/* First letter of the build version of the image */
#घोषणा BLD_STR_UFI_TYPE_BE2	'2'
#घोषणा BLD_STR_UFI_TYPE_BE3	'3'
#घोषणा BLD_STR_UFI_TYPE_SH	'4'

काष्ठा flash_file_hdr_g3 अणु
	u8 sign[52];
	u8 ufi_version[4];
	u32 file_len;
	u32 cksum;
	u32 antiकरोte;
	u32 num_imgs;
	u8 build[24];
	u8 asic_type_rev;
	u8 rsvd[31];
पूर्ण;

काष्ठा flash_section_hdr अणु
	u32 क्रमmat_rev;
	u32 cksum;
	u32 antiकरोte;
	u32 num_images;
	u8 id_string[128];
	u32 rsvd[4];
पूर्ण __packed;

काष्ठा flash_section_hdr_g2 अणु
	u32 क्रमmat_rev;
	u32 cksum;
	u32 antiकरोte;
	u32 build_num;
	u8 id_string[128];
	u32 rsvd[8];
पूर्ण __packed;

काष्ठा flash_section_entry अणु
	u32 type;
	u32 offset;
	u32 pad_size;
	u32 image_size;
	u32 cksum;
	u32 entry_poपूर्णांक;
	u16 optype;
	u16 rsvd0;
	u32 rsvd1;
	u8 ver_data[32];
पूर्ण __packed;

काष्ठा flash_section_info अणु
	u8 cookie[32];
	काष्ठा flash_section_hdr fsec_hdr;
	काष्ठा flash_section_entry fsec_entry[32];
पूर्ण __packed;

काष्ठा flash_section_info_g2 अणु
	u8 cookie[32];
	काष्ठा flash_section_hdr_g2 fsec_hdr;
	काष्ठा flash_section_entry fsec_entry[32];
पूर्ण __packed;

/****************** Firmware Flash ******************/
#घोषणा FLASHROM_OPER_FLASH		1
#घोषणा FLASHROM_OPER_SAVE		2
#घोषणा FLASHROM_OPER_REPORT		4
#घोषणा FLASHROM_OPER_PHY_FLASH		9
#घोषणा FLASHROM_OPER_PHY_SAVE		10

काष्ठा flashrom_params अणु
	u32 op_code;
	u32 op_type;
	u32 data_buf_size;
	u32 offset;
पूर्ण;

काष्ठा be_cmd_ग_लिखो_flashrom अणु
	काष्ठा be_cmd_req_hdr hdr;
	काष्ठा flashrom_params params;
	u8 data_buf[32768];
	u8 rsvd[4];
पूर्ण __packed;

/* cmd to पढ़ो flash crc */
काष्ठा be_cmd_पढ़ो_flash_crc अणु
	काष्ठा be_cmd_req_hdr hdr;
	काष्ठा flashrom_params params;
	u8 crc[4];
	u8 rsvd[4];
पूर्ण __packed;

/**************** Lancer Firmware Flash ************/
#घोषणा LANCER_FW_DOWNLOAD_CHUNK      (32 * 1024)
#घोषणा LANCER_FW_DOWNLOAD_LOCATION   "/prg"

काष्ठा amap_lancer_ग_लिखो_obj_context अणु
	u8 ग_लिखो_length[24];
	u8 reserved1[7];
	u8 eof;
पूर्ण __packed;

काष्ठा lancer_cmd_req_ग_लिखो_object अणु
	काष्ठा be_cmd_req_hdr hdr;
	u8 context[माप(काष्ठा amap_lancer_ग_लिखो_obj_context) / 8];
	u32 ग_लिखो_offset;
	u8 object_name[104];
	u32 descriptor_count;
	u32 buf_len;
	u32 addr_low;
	u32 addr_high;
पूर्ण;

#घोषणा LANCER_NO_RESET_NEEDED		0x00
#घोषणा LANCER_FW_RESET_NEEDED		0x02
काष्ठा lancer_cmd_resp_ग_लिखो_object अणु
	u8 opcode;
	u8 subप्रणाली;
	u8 rsvd1[2];
	u8 status;
	u8 additional_status;
	u8 rsvd2[2];
	u32 resp_len;
	u32 actual_resp_len;
	u32 actual_ग_लिखो_len;
	u8 change_status;
	u8 rsvd3[3];
पूर्ण;

/************************ Lancer Read FW info **************/
#घोषणा LANCER_READ_खाता_CHUNK			(32*1024)
#घोषणा LANCER_READ_खाता_खातापूर्ण_MASK		0x80000000

#घोषणा LANCER_FW_DUMP_खाता			"/dbg/dump.bin"
#घोषणा LANCER_VPD_PF_खाता			"/vpd/ntr_pf.vpd"
#घोषणा LANCER_VPD_VF_खाता			"/vpd/ntr_vf.vpd"

काष्ठा lancer_cmd_req_पढ़ो_object अणु
	काष्ठा be_cmd_req_hdr hdr;
	u32 desired_पढ़ो_len;
	u32 पढ़ो_offset;
	u8 object_name[104];
	u32 descriptor_count;
	u32 buf_len;
	u32 addr_low;
	u32 addr_high;
पूर्ण;

काष्ठा lancer_cmd_resp_पढ़ो_object अणु
	u8 opcode;
	u8 subप्रणाली;
	u8 rsvd1[2];
	u8 status;
	u8 additional_status;
	u8 rsvd2[2];
	u32 resp_len;
	u32 actual_resp_len;
	u32 actual_पढ़ो_len;
	u32 eof;
पूर्ण;

काष्ठा lancer_cmd_req_delete_object अणु
	काष्ठा be_cmd_req_hdr hdr;
	u32 rsvd1;
	u32 rsvd2;
	u8 object_name[104];
पूर्ण;

/************************ WOL *******************************/
काष्ठा be_cmd_req_acpi_wol_magic_configअणु
	काष्ठा be_cmd_req_hdr hdr;
	u32 rsvd0[145];
	u8 magic_mac[6];
	u8 rsvd2[2];
पूर्ण __packed;

काष्ठा be_cmd_req_acpi_wol_magic_config_v1 अणु
	काष्ठा be_cmd_req_hdr hdr;
	u8 rsvd0[2];
	u8 query_options;
	u8 rsvd1[5];
	u32 rsvd2[288];
	u8 magic_mac[6];
	u8 rsvd3[22];
पूर्ण __packed;

काष्ठा be_cmd_resp_acpi_wol_magic_config_v1 अणु
	काष्ठा be_cmd_resp_hdr hdr;
	u8 rsvd0[2];
	u8 wol_settings;
	u8 rsvd1[5];
	u32 rsvd2[288];
	u8 magic_mac[6];
	u8 rsvd3[22];
पूर्ण __packed;

#घोषणा BE_GET_WOL_CAP			2

#घोषणा BE_WOL_CAP			0x1
#घोषणा BE_PME_D0_CAP			0x8
#घोषणा BE_PME_D1_CAP			0x10
#घोषणा BE_PME_D2_CAP			0x20
#घोषणा BE_PME_D3HOT_CAP		0x40
#घोषणा BE_PME_D3COLD_CAP		0x80

/********************** LoopBack test *********************/
#घोषणा SET_LB_MODE_TIMEOUT		12000

काष्ठा be_cmd_req_loopback_test अणु
	काष्ठा be_cmd_req_hdr hdr;
	u32 loopback_type;
	u32 num_pkts;
	u64 pattern;
	u32 src_port;
	u32 dest_port;
	u32 pkt_size;
पूर्ण;

काष्ठा be_cmd_resp_loopback_test अणु
	काष्ठा be_cmd_resp_hdr resp_hdr;
	u32    status;
	u32    num_txfer;
	u32    num_rx;
	u32    miscomp_off;
	u32    ticks_compl;
पूर्ण;

काष्ठा be_cmd_req_set_lmode अणु
	काष्ठा be_cmd_req_hdr hdr;
	u8 src_port;
	u8 dest_port;
	u8 loopback_type;
	u8 loopback_state;
पूर्ण;

/********************** DDR DMA test *********************/
काष्ठा be_cmd_req_ddrdma_test अणु
	काष्ठा be_cmd_req_hdr hdr;
	u64 pattern;
	u32 byte_count;
	u32 rsvd0;
	u8  snd_buff[4096];
	u8  rsvd1[4096];
पूर्ण;

काष्ठा be_cmd_resp_ddrdma_test अणु
	काष्ठा be_cmd_resp_hdr hdr;
	u64 pattern;
	u32 byte_cnt;
	u32 snd_err;
	u8  rsvd0[4096];
	u8  rcv_buff[4096];
पूर्ण;

/*********************** SEEPROM Read ***********************/

#घोषणा BE_READ_SEEPROM_LEN 1024
काष्ठा be_cmd_req_seeprom_पढ़ो अणु
	काष्ठा be_cmd_req_hdr hdr;
	u8 rsvd0[BE_READ_SEEPROM_LEN];
पूर्ण;

काष्ठा be_cmd_resp_seeprom_पढ़ो अणु
	काष्ठा be_cmd_req_hdr hdr;
	u8 seeprom_data[BE_READ_SEEPROM_LEN];
पूर्ण;

क्रमागत अणु
	PHY_TYPE_CX4_10GB = 0,
	PHY_TYPE_XFP_10GB,
	PHY_TYPE_SFP_1GB,
	PHY_TYPE_SFP_PLUS_10GB,
	PHY_TYPE_KR_10GB,
	PHY_TYPE_KX4_10GB,
	PHY_TYPE_BASET_10GB,
	PHY_TYPE_BASET_1GB,
	PHY_TYPE_BASEX_1GB,
	PHY_TYPE_SGMII,
	PHY_TYPE_QSFP,
	PHY_TYPE_KR4_40GB,
	PHY_TYPE_KR2_20GB,
	PHY_TYPE_TN_8022,
	PHY_TYPE_DISABLED = 255
पूर्ण;

#घोषणा BE_SUPPORTED_SPEED_NONE		0
#घोषणा BE_SUPPORTED_SPEED_10MBPS	1
#घोषणा BE_SUPPORTED_SPEED_100MBPS	2
#घोषणा BE_SUPPORTED_SPEED_1GBPS	4
#घोषणा BE_SUPPORTED_SPEED_10GBPS	8
#घोषणा BE_SUPPORTED_SPEED_20GBPS	0x10
#घोषणा BE_SUPPORTED_SPEED_40GBPS	0x20

#घोषणा BE_AN_EN			0x2
#घोषणा BE_PAUSE_SYM_EN			0x80

/* MAC speed valid values */
#घोषणा SPEED_DEFAULT  0x0
#घोषणा SPEED_FORCED_10GB  0x1
#घोषणा SPEED_FORCED_1GB  0x2
#घोषणा SPEED_AUTONEG_10GB  0x3
#घोषणा SPEED_AUTONEG_1GB  0x4
#घोषणा SPEED_AUTONEG_100MB  0x5
#घोषणा SPEED_AUTONEG_10GB_1GB 0x6
#घोषणा SPEED_AUTONEG_10GB_1GB_100MB 0x7
#घोषणा SPEED_AUTONEG_1GB_100MB  0x8
#घोषणा SPEED_AUTONEG_10MB  0x9
#घोषणा SPEED_AUTONEG_1GB_100MB_10MB 0xa
#घोषणा SPEED_AUTONEG_100MB_10MB 0xb
#घोषणा SPEED_FORCED_100MB  0xc
#घोषणा SPEED_FORCED_10MB  0xd

काष्ठा be_cmd_req_get_phy_info अणु
	काष्ठा be_cmd_req_hdr hdr;
	u8 rsvd0[24];
पूर्ण;

काष्ठा be_phy_info अणु
	u16 phy_type;
	u16 पूर्णांकerface_type;
	u32 misc_params;
	u16 ext_phy_details;
	u16 rsvd;
	u16 स्वतः_speeds_supported;
	u16 fixed_speeds_supported;
	u32 future_use[2];
पूर्ण;

काष्ठा be_cmd_resp_get_phy_info अणु
	काष्ठा be_cmd_req_hdr hdr;
	काष्ठा be_phy_info phy_info;
पूर्ण;

/*********************** Set QOS ***********************/

#घोषणा BE_QOS_BITS_NIC				1

काष्ठा be_cmd_req_set_qos अणु
	काष्ठा be_cmd_req_hdr hdr;
	u32 valid_bits;
	u32 max_bps_nic;
	u32 rsvd[7];
पूर्ण;

/*********************** Controller Attributes ***********************/
काष्ठा mgmt_hba_attribs अणु
	u32 rsvd0[24];
	u8 controller_model_number[32];
	u32 rsvd1[16];
	u32 controller_serial_number[8];
	u32 rsvd2[55];
	u8 rsvd3[3];
	u8 phy_port;
	u32 rsvd4[15];
	u8 rsvd5[2];
	u8 pci_funcnum;
	u8 rsvd6;
	u32 rsvd7[6];
पूर्ण __packed;

काष्ठा mgmt_controller_attrib अणु
	काष्ठा mgmt_hba_attribs hba_attribs;
	u32 rsvd0[10];
पूर्ण __packed;

काष्ठा be_cmd_req_cntl_attribs अणु
	काष्ठा be_cmd_req_hdr hdr;
पूर्ण;

काष्ठा be_cmd_resp_cntl_attribs अणु
	काष्ठा be_cmd_resp_hdr hdr;
	काष्ठा mgmt_controller_attrib attribs;
पूर्ण;

/*********************** Set driver function ***********************/
#घोषणा CAPABILITY_SW_TIMESTAMPS	2
#घोषणा CAPABILITY_BE3_NATIVE_ERX_API	4

काष्ठा be_cmd_req_set_func_cap अणु
	काष्ठा be_cmd_req_hdr hdr;
	u32 valid_cap_flags;
	u32 cap_flags;
	u8 rsvd[212];
पूर्ण;

काष्ठा be_cmd_resp_set_func_cap अणु
	काष्ठा be_cmd_resp_hdr hdr;
	u32 valid_cap_flags;
	u32 cap_flags;
	u8 rsvd[212];
पूर्ण;

/*********************** Function Privileges ***********************/
क्रमागत अणु
	BE_PRIV_DEFAULT = 0x1,
	BE_PRIV_LNKQUERY = 0x2,
	BE_PRIV_LNKSTATS = 0x4,
	BE_PRIV_LNKMGMT = 0x8,
	BE_PRIV_LNKDIAG = 0x10,
	BE_PRIV_UTILQUERY = 0x20,
	BE_PRIV_FILTMGMT = 0x40,
	BE_PRIV_IFACEMGMT = 0x80,
	BE_PRIV_VHADM = 0x100,
	BE_PRIV_DEVCFG = 0x200,
	BE_PRIV_DEVSEC = 0x400
पूर्ण;
#घोषणा MAX_PRIVILEGES		(BE_PRIV_VHADM | BE_PRIV_DEVCFG | \
				 BE_PRIV_DEVSEC)
#घोषणा MIN_PRIVILEGES		BE_PRIV_DEFAULT

काष्ठा be_cmd_priv_map अणु
	u8 opcode;
	u8 subप्रणाली;
	u32 priv_mask;
पूर्ण;

काष्ठा be_cmd_req_get_fn_privileges अणु
	काष्ठा be_cmd_req_hdr hdr;
	u32 rsvd;
पूर्ण;

काष्ठा be_cmd_resp_get_fn_privileges अणु
	काष्ठा be_cmd_resp_hdr hdr;
	u32 privilege_mask;
पूर्ण;

काष्ठा be_cmd_req_set_fn_privileges अणु
	काष्ठा be_cmd_req_hdr hdr;
	u32 privileges;		/* Used by BE3, SH-R */
	u32 privileges_lancer;	/* Used by Lancer */
पूर्ण;

/******************** GET/SET_MACLIST  **************************/
#घोषणा BE_MAX_MAC			64
काष्ठा be_cmd_req_get_mac_list अणु
	काष्ठा be_cmd_req_hdr hdr;
	u8 mac_type;
	u8 perm_override;
	u16 अगरace_id;
	u32 mac_id;
	u32 rsvd[3];
पूर्ण __packed;

काष्ठा get_list_macaddr अणु
	u16 mac_addr_size;
	जोड़ अणु
		u8 macaddr[6];
		काष्ठा अणु
			u8 rsvd[2];
			u32 mac_id;
		पूर्ण __packed s_mac_id;
	पूर्ण __packed mac_addr_id;
पूर्ण __packed;

काष्ठा be_cmd_resp_get_mac_list अणु
	काष्ठा be_cmd_resp_hdr hdr;
	काष्ठा get_list_macaddr fd_macaddr; /* Factory शेष mac */
	काष्ठा get_list_macaddr macid_macaddr; /* soft mac */
	u8 true_mac_count;
	u8 pseuकरो_mac_count;
	u8 mac_list_size;
	u8 rsvd;
	/* perm override mac */
	काष्ठा get_list_macaddr macaddr_list[BE_MAX_MAC];
पूर्ण __packed;

काष्ठा be_cmd_req_set_mac_list अणु
	काष्ठा be_cmd_req_hdr hdr;
	u8 mac_count;
	u8 rsvd1;
	u16 rsvd2;
	काष्ठा macaddr mac[BE_MAX_MAC];
पूर्ण __packed;

/*********************** HSW Config ***********************/
#घोषणा PORT_FWD_TYPE_VEPA		0x3
#घोषणा PORT_FWD_TYPE_VEB		0x2
#घोषणा PORT_FWD_TYPE_PASSTHRU		0x1

#घोषणा ENABLE_MAC_SPOOFCHK		0x2
#घोषणा DISABLE_MAC_SPOOFCHK		0x3

काष्ठा amap_set_hsw_context अणु
	u8 पूर्णांकerface_id[16];
	u8 rsvd0[8];
	u8 mac_spoofchk[2];
	u8 rsvd1[4];
	u8 pvid_valid;
	u8 pport;
	u8 rsvd2[6];
	u8 port_fwd_type[3];
	u8 rsvd3[5];
	u8 vlan_spoofchk[2];
	u8 pvid[16];
	u8 rsvd4[32];
	u8 rsvd5[32];
	u8 rsvd6[32];
पूर्ण __packed;

काष्ठा be_cmd_req_set_hsw_config अणु
	काष्ठा be_cmd_req_hdr hdr;
	u8 context[माप(काष्ठा amap_set_hsw_context) / 8];
पूर्ण __packed;

काष्ठा amap_get_hsw_req_context अणु
	u8 पूर्णांकerface_id[16];
	u8 rsvd0[14];
	u8 pvid_valid;
	u8 pport;
पूर्ण __packed;

काष्ठा amap_get_hsw_resp_context अणु
	u8 rsvd0[6];
	u8 port_fwd_type[3];
	u8 rsvd1[5];
	u8 spoofchk;
	u8 rsvd2;
	u8 pvid[16];
	u8 rsvd3[32];
	u8 rsvd4[32];
	u8 rsvd5[32];
पूर्ण __packed;

काष्ठा be_cmd_req_get_hsw_config अणु
	काष्ठा be_cmd_req_hdr hdr;
	u8 context[माप(काष्ठा amap_get_hsw_req_context) / 8];
पूर्ण __packed;

काष्ठा be_cmd_resp_get_hsw_config अणु
	काष्ठा be_cmd_resp_hdr hdr;
	u8 context[माप(काष्ठा amap_get_hsw_resp_context) / 8];
	u32 rsvd;
पूर्ण;

/******************* get port names ***************/
काष्ठा be_cmd_req_get_port_name अणु
	काष्ठा be_cmd_req_hdr hdr;
	u32 rsvd0;
पूर्ण;

काष्ठा be_cmd_resp_get_port_name अणु
	काष्ठा be_cmd_req_hdr hdr;
	u8 port_name[4];
पूर्ण;

/*************** HW Stats Get v1 **********************************/
#घोषणा BE_TXP_SW_SZ			48
काष्ठा be_port_rxf_stats_v1 अणु
	u32 rsvd0[12];
	u32 rx_crc_errors;
	u32 rx_alignment_symbol_errors;
	u32 rx_छोड़ो_frames;
	u32 rx_priority_छोड़ो_frames;
	u32 rx_control_frames;
	u32 rx_in_range_errors;
	u32 rx_out_range_errors;
	u32 rx_frame_too_दीर्घ;
	u32 rx_address_filtered;
	u32 rx_dropped_too_small;
	u32 rx_dropped_too_लघु;
	u32 rx_dropped_header_too_small;
	u32 rx_dropped_tcp_length;
	u32 rx_dropped_runt;
	u32 rsvd1[10];
	u32 rx_ip_checksum_errs;
	u32 rx_tcp_checksum_errs;
	u32 rx_udp_checksum_errs;
	u32 rsvd2[7];
	u32 rx_चयनed_unicast_packets;
	u32 rx_चयनed_multicast_packets;
	u32 rx_चयनed_broadcast_packets;
	u32 rsvd3[3];
	u32 tx_छोड़ोframes;
	u32 tx_priority_छोड़ोframes;
	u32 tx_controlframes;
	u32 rsvd4[10];
	u32 rxpp_fअगरo_overflow_drop;
	u32 rx_input_fअगरo_overflow_drop;
	u32 pmem_fअगरo_overflow_drop;
	u32 jabber_events;
	u32 rsvd5[3];
पूर्ण;


काष्ठा be_rxf_stats_v1 अणु
	काष्ठा be_port_rxf_stats_v1 port[4];
	u32 rsvd0[2];
	u32 rx_drops_no_pbuf;
	u32 rx_drops_no_txpb;
	u32 rx_drops_no_erx_descr;
	u32 rx_drops_no_tpre_descr;
	u32 rsvd1[6];
	u32 rx_drops_too_many_frags;
	u32 rx_drops_invalid_ring;
	u32 क्रमwarded_packets;
	u32 rx_drops_mtu;
	u32 rsvd2[14];
पूर्ण;

काष्ठा be_erx_stats_v1 अणु
	u32 rx_drops_no_fragments[68];     /* dwordS 0 to 67*/
	u32 rsvd[4];
पूर्ण;

काष्ठा be_port_rxf_stats_v2 अणु
	u32 rsvd0[10];
	u32 roce_bytes_received_lsd;
	u32 roce_bytes_received_msd;
	u32 rsvd1[5];
	u32 roce_frames_received;
	u32 rx_crc_errors;
	u32 rx_alignment_symbol_errors;
	u32 rx_छोड़ो_frames;
	u32 rx_priority_छोड़ो_frames;
	u32 rx_control_frames;
	u32 rx_in_range_errors;
	u32 rx_out_range_errors;
	u32 rx_frame_too_दीर्घ;
	u32 rx_address_filtered;
	u32 rx_dropped_too_small;
	u32 rx_dropped_too_लघु;
	u32 rx_dropped_header_too_small;
	u32 rx_dropped_tcp_length;
	u32 rx_dropped_runt;
	u32 rsvd2[10];
	u32 rx_ip_checksum_errs;
	u32 rx_tcp_checksum_errs;
	u32 rx_udp_checksum_errs;
	u32 rsvd3[7];
	u32 rx_चयनed_unicast_packets;
	u32 rx_चयनed_multicast_packets;
	u32 rx_चयनed_broadcast_packets;
	u32 rsvd4[3];
	u32 tx_छोड़ोframes;
	u32 tx_priority_छोड़ोframes;
	u32 tx_controlframes;
	u32 rsvd5[10];
	u32 rxpp_fअगरo_overflow_drop;
	u32 rx_input_fअगरo_overflow_drop;
	u32 pmem_fअगरo_overflow_drop;
	u32 jabber_events;
	u32 rsvd6[3];
	u32 rx_drops_payload_size;
	u32 rx_drops_clipped_header;
	u32 rx_drops_crc;
	u32 roce_drops_payload_len;
	u32 roce_drops_crc;
	u32 rsvd7[19];
पूर्ण;

काष्ठा be_rxf_stats_v2 अणु
	काष्ठा be_port_rxf_stats_v2 port[4];
	u32 rsvd0[2];
	u32 rx_drops_no_pbuf;
	u32 rx_drops_no_txpb;
	u32 rx_drops_no_erx_descr;
	u32 rx_drops_no_tpre_descr;
	u32 rsvd1[6];
	u32 rx_drops_too_many_frags;
	u32 rx_drops_invalid_ring;
	u32 क्रमwarded_packets;
	u32 rx_drops_mtu;
	u32 rsvd2[35];
पूर्ण;

काष्ठा be_hw_stats_v1 अणु
	काष्ठा be_rxf_stats_v1 rxf;
	u32 rsvd0[BE_TXP_SW_SZ];
	काष्ठा be_erx_stats_v1 erx;
	काष्ठा be_pmem_stats pmem;
	u32 rsvd1[18];
पूर्ण;

काष्ठा be_cmd_req_get_stats_v1 अणु
	काष्ठा be_cmd_req_hdr hdr;
	u8 rsvd[माप(काष्ठा be_hw_stats_v1)];
पूर्ण;

काष्ठा be_cmd_resp_get_stats_v1 अणु
	काष्ठा be_cmd_resp_hdr hdr;
	काष्ठा be_hw_stats_v1 hw_stats;
पूर्ण;

काष्ठा be_erx_stats_v2 अणु
	u32 rx_drops_no_fragments[136];     /* dwordS 0 to 135*/
	u32 rsvd[3];
पूर्ण;

काष्ठा be_hw_stats_v2 अणु
	काष्ठा be_rxf_stats_v2 rxf;
	u32 rsvd0[BE_TXP_SW_SZ];
	काष्ठा be_erx_stats_v2 erx;
	काष्ठा be_pmem_stats pmem;
	u32 rsvd1[18];
पूर्ण;

काष्ठा be_cmd_req_get_stats_v2 अणु
	काष्ठा be_cmd_req_hdr hdr;
	u8 rsvd[माप(काष्ठा be_hw_stats_v2)];
पूर्ण;

काष्ठा be_cmd_resp_get_stats_v2 अणु
	काष्ठा be_cmd_resp_hdr hdr;
	काष्ठा be_hw_stats_v2 hw_stats;
पूर्ण;

/************** get fat capabilites *******************/
#घोषणा MAX_MODULES 27
#घोषणा MAX_MODES 4
#घोषणा MODE_UART 0
#घोषणा FW_LOG_LEVEL_DEFAULT 48
#घोषणा FW_LOG_LEVEL_FATAL 64

काष्ठा ext_fat_mode अणु
	u8 mode;
	u8 rsvd0;
	u16 port_mask;
	u32 dbg_lvl;
	u64 fun_mask;
पूर्ण __packed;

काष्ठा ext_fat_modules अणु
	u8 modules_str[32];
	u32 modules_id;
	u32 num_modes;
	काष्ठा ext_fat_mode trace_lvl[MAX_MODES];
पूर्ण __packed;

काष्ठा be_fat_conf_params अणु
	u32 max_log_entries;
	u32 log_entry_size;
	u8 log_type;
	u8 max_log_funs;
	u8 max_log_ports;
	u8 rsvd0;
	u32 supp_modes;
	u32 num_modules;
	काष्ठा ext_fat_modules module[MAX_MODULES];
पूर्ण __packed;

काष्ठा be_cmd_req_get_ext_fat_caps अणु
	काष्ठा be_cmd_req_hdr hdr;
	u32 parameter_type;
पूर्ण;

काष्ठा be_cmd_resp_get_ext_fat_caps अणु
	काष्ठा be_cmd_resp_hdr hdr;
	काष्ठा be_fat_conf_params get_params;
पूर्ण;

काष्ठा be_cmd_req_set_ext_fat_caps अणु
	काष्ठा be_cmd_req_hdr hdr;
	काष्ठा be_fat_conf_params set_params;
पूर्ण;

#घोषणा RESOURCE_DESC_SIZE_V0			72
#घोषणा RESOURCE_DESC_SIZE_V1			88
#घोषणा PCIE_RESOURCE_DESC_TYPE_V0		0x40
#घोषणा NIC_RESOURCE_DESC_TYPE_V0		0x41
#घोषणा PCIE_RESOURCE_DESC_TYPE_V1		0x50
#घोषणा NIC_RESOURCE_DESC_TYPE_V1		0x51
#घोषणा PORT_RESOURCE_DESC_TYPE_V1		0x55
#घोषणा MAX_RESOURCE_DESC			264

#घोषणा IF_CAPS_FLAGS_VALID_SHIFT		0	/* IF caps valid */
#घोषणा VFT_SHIFT				3	/* VF ढाँचा */
#घोषणा IMM_SHIFT				6	/* Immediate */
#घोषणा NOSV_SHIFT				7	/* No save */

#घोषणा MISSION_NIC				1
#घोषणा MISSION_RDMA				8

काष्ठा be_res_desc_hdr अणु
	u8 desc_type;
	u8 desc_len;
पूर्ण __packed;

काष्ठा be_port_res_desc अणु
	काष्ठा be_res_desc_hdr hdr;
	u8 rsvd0;
	u8 flags;
	u8 link_num;
	u8 mc_type;
	u16 rsvd1;

#घोषणा NV_TYPE_MASK				0x3	/* bits 0-1 */
#घोषणा NV_TYPE_DISABLED			1
#घोषणा NV_TYPE_VXLAN				3
#घोषणा SOCVID_SHIFT				2	/* Strip outer vlan */
#घोषणा RCVID_SHIFT				4	/* Report vlan */
#घोषणा PF_NUM_IGNORE				255
	u8 nv_flags;
	u8 rsvd2;
	__le16 nv_port;					/* vxlan/gre port */
	u32 rsvd3[19];
पूर्ण __packed;

काष्ठा be_pcie_res_desc अणु
	काष्ठा be_res_desc_hdr hdr;
	u8 rsvd0;
	u8 flags;
	u16 rsvd1;
	u8 pf_num;
	u8 rsvd2;
	u32 rsvd3;
	u8 sriov_state;
	u8 pf_state;
	u8 pf_type;
	u8 rsvd4;
	u16 num_vfs;
	u16 rsvd5;
	u32 rsvd6[17];
पूर्ण __packed;

काष्ठा be_nic_res_desc अणु
	काष्ठा be_res_desc_hdr hdr;
	u8 rsvd1;

#घोषणा QUN_SHIFT				4 /* QoS is in असलolute units */
	u8 flags;
	u8 vf_num;
	u8 rsvd2;
	u8 pf_num;
	u8 rsvd3;
	u16 unicast_mac_count;
	u8 rsvd4[6];
	u16 mcc_count;
	u16 vlan_count;
	u16 mcast_mac_count;
	u16 txq_count;
	u16 rq_count;
	u16 rssq_count;
	u16 lro_count;
	u16 cq_count;
	u16 toe_conn_count;
	u16 eq_count;
	u16 vlan_id;
	u16 अगरace_count;
	u32 cap_flags;
	u8 link_param;
	u8 rsvd6;
	u16 channel_id_param;
	u32 bw_min;
	u32 bw_max;
	u8 acpi_params;
	u8 wol_param;
	u16 rsvd7;
	u16 tunnel_अगरace_count;
	u16 direct_tenant_अगरace_count;
	u32 rsvd8[6];
पूर्ण __packed;

/************ Multi-Channel type ***********/
क्रमागत mc_type अणु
	MC_NONE = 0x01,
	UMC = 0x02,
	FLEX10 = 0x03,
	vNIC1 = 0x04,
	nPAR = 0x05,
	UFP = 0x06,
	vNIC2 = 0x07
पूर्ण;

/* Is BE in a multi-channel mode */
अटल अंतरभूत bool be_is_mc(काष्ठा be_adapter *adapter)
अणु
	वापस adapter->mc_type > MC_NONE;
पूर्ण

काष्ठा be_cmd_req_get_func_config अणु
	काष्ठा be_cmd_req_hdr hdr;
पूर्ण;

काष्ठा be_cmd_resp_get_func_config अणु
	काष्ठा be_cmd_resp_hdr hdr;
	u32 desc_count;
	u8 func_param[MAX_RESOURCE_DESC * RESOURCE_DESC_SIZE_V1];
पूर्ण;

क्रमागत अणु
	RESOURCE_LIMITS,
	RESOURCE_MODIFIABLE
पूर्ण;

काष्ठा be_cmd_req_get_profile_config अणु
	काष्ठा be_cmd_req_hdr hdr;
	u8 rsvd;
#घोषणा ACTIVE_PROखाता_TYPE			0x2
#घोषणा SAVED_PROखाता_TYPE			0x0
#घोषणा QUERY_MODIFIABLE_FIELDS_TYPE		BIT(3)
	u8 type;
	u16 rsvd1;
पूर्ण;

काष्ठा be_cmd_resp_get_profile_config अणु
	काष्ठा be_cmd_resp_hdr hdr;
	__le16 desc_count;
	u16 rsvd;
	u8 func_param[MAX_RESOURCE_DESC * RESOURCE_DESC_SIZE_V1];
पूर्ण;

#घोषणा FIELD_MODIFIABLE			0xFFFF
काष्ठा be_cmd_req_set_profile_config अणु
	काष्ठा be_cmd_req_hdr hdr;
	u32 rsvd;
	u32 desc_count;
	u8 desc[2 * RESOURCE_DESC_SIZE_V1];
पूर्ण __packed;

काष्ठा be_cmd_req_get_active_profile अणु
	काष्ठा be_cmd_req_hdr hdr;
	u32 rsvd;
पूर्ण __packed;

काष्ठा be_cmd_resp_get_active_profile अणु
	काष्ठा be_cmd_resp_hdr hdr;
	u16 active_profile_id;
	u16 next_profile_id;
पूर्ण __packed;

काष्ठा be_cmd_enable_disable_vf अणु
	काष्ठा be_cmd_req_hdr hdr;
	u8 enable;
	u8 rsvd[3];
पूर्ण;

काष्ठा be_cmd_req_पूर्णांकr_set अणु
	काष्ठा be_cmd_req_hdr hdr;
	u8 पूर्णांकr_enabled;
	u8 rsvd[3];
पूर्ण;

अटल अंतरभूत bool check_privilege(काष्ठा be_adapter *adapter, u32 flags)
अणु
	वापस flags & adapter->cmd_privileges ? true : false;
पूर्ण

/************** Get IFACE LIST *******************/
काष्ठा be_अगर_desc अणु
	u32 अगर_id;
	u32 cap_flags;
	u32 en_flags;
पूर्ण;

काष्ठा be_cmd_req_get_अगरace_list अणु
	काष्ठा be_cmd_req_hdr hdr;
पूर्ण;

काष्ठा be_cmd_resp_get_अगरace_list अणु
	काष्ठा be_cmd_req_hdr hdr;
	u32 अगर_cnt;
	काष्ठा be_अगर_desc अगर_desc;
पूर्ण;

/************** Set Features *******************/
#घोषणा	BE_FEATURE_UE_RECOVERY		0x10
#घोषणा	BE_UE_RECOVERY_UER_MASK		0x1

काष्ठा be_req_ue_recovery अणु
	u32	uer;
	u32	rsvd;
पूर्ण;

काष्ठा be_cmd_req_set_features अणु
	काष्ठा be_cmd_req_hdr hdr;
	u32 features;
	u32 parameter_len;
	जोड़ अणु
		काष्ठा be_req_ue_recovery req;
		u32 rsvd[2];
	पूर्ण parameter;
पूर्ण;

काष्ठा be_resp_ue_recovery अणु
	u32 uer;
	u16 ue2rp;
	u16 ue2sr;
पूर्ण;

काष्ठा be_cmd_resp_set_features अणु
	काष्ठा be_cmd_resp_hdr hdr;
	u32 features;
	u32 parameter_len;
	जोड़ अणु
		काष्ठा be_resp_ue_recovery resp;
		u32 rsvd[2];
	पूर्ण parameter;
पूर्ण;

/*************** Set logical link ********************/
#घोषणा PLINK_ENABLE            BIT(0)
#घोषणा PLINK_TRACK             BIT(8)
काष्ठा be_cmd_req_set_ll_link अणु
	काष्ठा be_cmd_req_hdr hdr;
	u32 link_config; /* Bit 0: UP_DOWN, Bit 9: PLINK */
पूर्ण;

/************** Manage IFACE Filters *******************/
#घोषणा OP_CONVERT_NORMAL_TO_TUNNEL		0
#घोषणा OP_CONVERT_TUNNEL_TO_NORMAL		1

काष्ठा be_cmd_req_manage_अगरace_filters अणु
	काष्ठा be_cmd_req_hdr hdr;
	u8  op;
	u8  rsvd0;
	u8  flags;
	u8  rsvd1;
	u32 tunnel_अगरace_id;
	u32 target_अगरace_id;
	u8  mac[6];
	u16 vlan_tag;
	u32 tenant_id;
	u32 filter_id;
	u32 cap_flags;
	u32 cap_control_flags;
पूर्ण __packed;

u16 be_POST_stage_get(काष्ठा be_adapter *adapter);
पूर्णांक be_pci_fnum_get(काष्ठा be_adapter *adapter);
पूर्णांक be_fw_रुको_पढ़ोy(काष्ठा be_adapter *adapter);
पूर्णांक be_cmd_mac_addr_query(काष्ठा be_adapter *adapter, u8 *mac_addr,
			  bool permanent, u32 अगर_handle, u32 pmac_id);
पूर्णांक be_cmd_pmac_add(काष्ठा be_adapter *adapter, u8 *mac_addr, u32 अगर_id,
		    u32 *pmac_id, u32 करोमुख्य);
पूर्णांक be_cmd_pmac_del(काष्ठा be_adapter *adapter, u32 अगर_id, पूर्णांक pmac_id,
		    u32 करोमुख्य);
पूर्णांक be_cmd_अगर_create(काष्ठा be_adapter *adapter, u32 cap_flags, u32 en_flags,
		     u32 *अगर_handle, u32 करोमुख्य);
पूर्णांक be_cmd_अगर_destroy(काष्ठा be_adapter *adapter, पूर्णांक अगर_handle, u32 करोमुख्य);
पूर्णांक be_cmd_eq_create(काष्ठा be_adapter *adapter, काष्ठा be_eq_obj *eqo);
पूर्णांक be_cmd_cq_create(काष्ठा be_adapter *adapter, काष्ठा be_queue_info *cq,
		     काष्ठा be_queue_info *eq, bool no_delay,
		     पूर्णांक num_cqe_dma_coalesce);
पूर्णांक be_cmd_mccq_create(काष्ठा be_adapter *adapter, काष्ठा be_queue_info *mccq,
		       काष्ठा be_queue_info *cq);
पूर्णांक be_cmd_txq_create(काष्ठा be_adapter *adapter, काष्ठा be_tx_obj *txo);
पूर्णांक be_cmd_rxq_create(काष्ठा be_adapter *adapter, काष्ठा be_queue_info *rxq,
		      u16 cq_id, u16 frag_size, u32 अगर_id, u32 rss, u8 *rss_id);
पूर्णांक be_cmd_q_destroy(काष्ठा be_adapter *adapter, काष्ठा be_queue_info *q,
		     पूर्णांक type);
पूर्णांक be_cmd_rxq_destroy(काष्ठा be_adapter *adapter, काष्ठा be_queue_info *q);
पूर्णांक be_cmd_link_status_query(काष्ठा be_adapter *adapter, u16 *link_speed,
			     u8 *link_status, u32 करोm);
पूर्णांक be_cmd_reset(काष्ठा be_adapter *adapter);
पूर्णांक be_cmd_get_stats(काष्ठा be_adapter *adapter, काष्ठा be_dma_mem *nonemb_cmd);
पूर्णांक lancer_cmd_get_pport_stats(काष्ठा be_adapter *adapter,
			       काष्ठा be_dma_mem *nonemb_cmd);
पूर्णांक be_cmd_get_fw_ver(काष्ठा be_adapter *adapter);
पूर्णांक be_cmd_modअगरy_eqd(काष्ठा be_adapter *adapter, काष्ठा be_set_eqd *, पूर्णांक num);
पूर्णांक be_cmd_vlan_config(काष्ठा be_adapter *adapter, u32 अगर_id, u16 *vtag_array,
		       u32 num, u32 करोमुख्य);
पूर्णांक be_cmd_rx_filter(काष्ठा be_adapter *adapter, u32 flags, u32 status);
पूर्णांक be_cmd_set_flow_control(काष्ठा be_adapter *adapter, u32 tx_fc, u32 rx_fc);
पूर्णांक be_cmd_get_flow_control(काष्ठा be_adapter *adapter, u32 *tx_fc, u32 *rx_fc);
पूर्णांक be_cmd_query_fw_cfg(काष्ठा be_adapter *adapter);
पूर्णांक be_cmd_reset_function(काष्ठा be_adapter *adapter);
पूर्णांक be_cmd_rss_config(काष्ठा be_adapter *adapter, u8 *rsstable,
		      u32 rss_hash_opts, u16 table_size, स्थिर u8 *rss_hkey);
पूर्णांक be_process_mcc(काष्ठा be_adapter *adapter);
पूर्णांक be_cmd_set_beacon_state(काष्ठा be_adapter *adapter, u8 port_num, u8 beacon,
			    u8 status, u8 state);
पूर्णांक be_cmd_get_beacon_state(काष्ठा be_adapter *adapter, u8 port_num,
			    u32 *state);
पूर्णांक be_cmd_पढ़ो_port_transceiver_data(काष्ठा be_adapter *adapter,
				      u8 page_num, u8 *data);
पूर्णांक be_cmd_query_cable_type(काष्ठा be_adapter *adapter);
पूर्णांक be_cmd_query_sfp_info(काष्ठा be_adapter *adapter);
पूर्णांक lancer_cmd_पढ़ो_object(काष्ठा be_adapter *adapter, काष्ठा be_dma_mem *cmd,
			   u32 data_size, u32 data_offset, स्थिर अक्षर *obj_name,
			   u32 *data_पढ़ो, u32 *eof, u8 *addn_status);
पूर्णांक lancer_fw_करोwnload(काष्ठा be_adapter *adapter, स्थिर काष्ठा firmware *fw);
पूर्णांक be_fw_करोwnload(काष्ठा be_adapter *adapter, स्थिर काष्ठा firmware *fw);
पूर्णांक be_cmd_enable_magic_wol(काष्ठा be_adapter *adapter, u8 *mac,
			    काष्ठा be_dma_mem *nonemb_cmd);
पूर्णांक be_cmd_fw_init(काष्ठा be_adapter *adapter);
पूर्णांक be_cmd_fw_clean(काष्ठा be_adapter *adapter);
व्योम be_async_mcc_enable(काष्ठा be_adapter *adapter);
व्योम be_async_mcc_disable(काष्ठा be_adapter *adapter);
पूर्णांक be_cmd_loopback_test(काष्ठा be_adapter *adapter, u32 port_num,
			 u32 loopback_type, u32 pkt_size, u32 num_pkts,
			 u64 pattern);
पूर्णांक be_cmd_ddr_dma_test(काष्ठा be_adapter *adapter, u64 pattern, u32 byte_cnt,
			काष्ठा be_dma_mem *cmd);
पूर्णांक be_cmd_get_seeprom_data(काष्ठा be_adapter *adapter,
			    काष्ठा be_dma_mem *nonemb_cmd);
पूर्णांक be_cmd_set_loopback(काष्ठा be_adapter *adapter, u8 port_num,
			u8 loopback_type, u8 enable);
पूर्णांक be_cmd_get_phy_info(काष्ठा be_adapter *adapter);
पूर्णांक be_cmd_config_qos(काष्ठा be_adapter *adapter, u32 max_rate,
		      u16 link_speed, u8 करोमुख्य);
व्योम be_detect_error(काष्ठा be_adapter *adapter);
पूर्णांक be_cmd_get_die_temperature(काष्ठा be_adapter *adapter);
पूर्णांक be_cmd_get_cntl_attributes(काष्ठा be_adapter *adapter);
पूर्णांक be_cmd_get_fat_dump_len(काष्ठा be_adapter *adapter, u32 *dump_size);
पूर्णांक be_cmd_get_fat_dump(काष्ठा be_adapter *adapter, u32 buf_len, व्योम *buf);
पूर्णांक be_cmd_req_native_mode(काष्ठा be_adapter *adapter);
पूर्णांक be_cmd_get_fn_privileges(काष्ठा be_adapter *adapter, u32 *privilege,
			     u32 करोमुख्य);
पूर्णांक be_cmd_set_fn_privileges(काष्ठा be_adapter *adapter, u32 privileges,
			     u32 vf_num);
पूर्णांक be_cmd_get_mac_from_list(काष्ठा be_adapter *adapter, u8 *mac,
			     bool *pmac_id_active, u32 *pmac_id,
			     u32 अगर_handle, u8 करोमुख्य);
पूर्णांक be_cmd_get_active_mac(काष्ठा be_adapter *adapter, u32 pmac_id, u8 *mac,
			  u32 अगर_handle, bool active, u32 करोमुख्य);
पूर्णांक be_cmd_get_perm_mac(काष्ठा be_adapter *adapter, u8 *mac);
पूर्णांक be_cmd_set_mac_list(काष्ठा be_adapter *adapter, u8 *mac_array, u8 mac_count,
			u32 करोमुख्य);
पूर्णांक be_cmd_set_mac(काष्ठा be_adapter *adapter, u8 *mac, पूर्णांक अगर_id, u32 करोm);
पूर्णांक be_cmd_set_hsw_config(काष्ठा be_adapter *adapter, u16 pvid, u32 करोमुख्य,
			  u16 पूर्णांकf_id, u16 hsw_mode, u8 spoofchk);
पूर्णांक be_cmd_get_hsw_config(काष्ठा be_adapter *adapter, u16 *pvid, u32 करोमुख्य,
			  u16 पूर्णांकf_id, u8 *mode, bool *spoofchk);
पूर्णांक be_cmd_get_acpi_wol_cap(काष्ठा be_adapter *adapter);
पूर्णांक be_cmd_set_fw_log_level(काष्ठा be_adapter *adapter, u32 level);
पूर्णांक be_cmd_get_fw_log_level(काष्ठा be_adapter *adapter);
पूर्णांक be_cmd_get_ext_fat_capabilites(काष्ठा be_adapter *adapter,
				   काष्ठा be_dma_mem *cmd);
पूर्णांक be_cmd_set_ext_fat_capabilites(काष्ठा be_adapter *adapter,
				   काष्ठा be_dma_mem *cmd,
				   काष्ठा be_fat_conf_params *cfgs);
पूर्णांक lancer_physdev_ctrl(काष्ठा be_adapter *adapter, u32 mask);
पूर्णांक lancer_initiate_dump(काष्ठा be_adapter *adapter);
पूर्णांक lancer_delete_dump(काष्ठा be_adapter *adapter);
bool dump_present(काष्ठा be_adapter *adapter);
पूर्णांक lancer_test_and_set_rdy_state(काष्ठा be_adapter *adapter);
पूर्णांक be_cmd_query_port_name(काष्ठा be_adapter *adapter);
पूर्णांक be_cmd_get_func_config(काष्ठा be_adapter *adapter,
			   काष्ठा be_resources *res);
पूर्णांक be_cmd_get_profile_config(काष्ठा be_adapter *adapter,
			      काष्ठा be_resources *res,
			      काष्ठा be_port_resources *port_res,
			      u8 profile_type, u8 query, u8 करोमुख्य);
पूर्णांक be_cmd_get_active_profile(काष्ठा be_adapter *adapter, u16 *profile);
पूर्णांक be_cmd_get_अगर_id(काष्ठा be_adapter *adapter, काष्ठा be_vf_cfg *vf_cfg,
		     पूर्णांक vf_num);
पूर्णांक be_cmd_enable_vf(काष्ठा be_adapter *adapter, u8 करोमुख्य);
पूर्णांक be_cmd_पूर्णांकr_set(काष्ठा be_adapter *adapter, bool पूर्णांकr_enable);
पूर्णांक be_cmd_set_logical_link_config(काष्ठा be_adapter *adapter,
					  पूर्णांक link_state, u8 करोमुख्य);
पूर्णांक be_cmd_set_vxlan_port(काष्ठा be_adapter *adapter, __be16 port);
पूर्णांक be_cmd_manage_अगरace(काष्ठा be_adapter *adapter, u32 अगरace, u8 op);
पूर्णांक be_cmd_set_sriov_config(काष्ठा be_adapter *adapter,
			    काष्ठा be_resources res, u16 num_vfs,
			    काष्ठा be_resources *vft_res);
पूर्णांक be_cmd_set_features(काष्ठा be_adapter *adapter);
