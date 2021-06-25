<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2017 Broadcom. All Rights Reserved.
 * The term "Broadcom" refers to Broadcom Limited and/or its subsidiaries.
 *
 * Contact Inक्रमmation:
 * linux-drivers@broadcom.com
 */

#अगर_अघोषित BEISCSI_CMDS_H
#घोषणा BEISCSI_CMDS_H

/**
 * The driver sends configuration and managements command requests to the
 * firmware in the BE. These requests are communicated to the processor
 * using Work Request Blocks (WRBs) submitted to the MCC-WRB ring or via one
 * WRB inside a MAILBOX.
 * The commands are serviced by the ARM processor in the OneConnect's MPU.
 */
काष्ठा be_sge अणु
	__le32 pa_lo;
	__le32 pa_hi;
	__le32 len;
पूर्ण;

काष्ठा be_mcc_wrb अणु
	u32 emb_sgecnt_special;	/* dword 0 */
	/* bits 0 - embedded    */
	/* bits 1 - 2 reserved	*/
	/* bits 3 - 7 sge count	*/
	/* bits 8 - 23 reserved	*/
	/* bits 24 - 31 special	*/
#घोषणा MCC_WRB_EMBEDDED_MASK 1
#घोषणा MCC_WRB_SGE_CNT_SHIFT 3
#घोषणा MCC_WRB_SGE_CNT_MASK 0x1F
	u32 payload_length;	/* dword 1 */
	u32 tag0;		/* dword 2 */
	u32 tag1;		/* dword 3 */
	u32 rsvd;		/* dword 4 */
	जोड़ अणु
#घोषणा EMBED_MBX_MAX_PAYLOAD_SIZE  220
		u8 embedded_payload[236];	/* used by embedded cmds */
		काष्ठा be_sge sgl[19];	/* used by non-embedded cmds */
	पूर्ण payload;
पूर्ण;

#घोषणा CQE_FLAGS_VALID_MASK (1 << 31)
#घोषणा CQE_FLAGS_ASYNC_MASK (1 << 30)
#घोषणा CQE_FLAGS_COMPLETED_MASK	(1 << 28)
#घोषणा CQE_FLAGS_CONSUMED_MASK		(1 << 27)

/* Completion Status */
#घोषणा MCC_STATUS_SUCCESS 0x0
#घोषणा MCC_STATUS_FAILED 0x1
#घोषणा MCC_STATUS_ILLEGAL_REQUEST 0x2
#घोषणा MCC_STATUS_ILLEGAL_FIELD 0x3
#घोषणा MCC_STATUS_INSUFFICIENT_BUFFER 0x4
#घोषणा MCC_STATUS_INVALID_LENGTH 0x74

#घोषणा CQE_STATUS_COMPL_MASK	0xFFFF
#घोषणा CQE_STATUS_COMPL_SHIFT	0		/* bits 0 - 15 */
#घोषणा CQE_STATUS_EXTD_MASK	0xFFFF
#घोषणा CQE_STATUS_EXTD_SHIFT	16		/* bits 31 - 16 */
#घोषणा CQE_STATUS_ADDL_MASK	0xFF00
#घोषणा CQE_STATUS_ADDL_SHIFT	8
#घोषणा CQE_STATUS_MASK		0xFF
#घोषणा CQE_STATUS_WRB_MASK	0xFF0000
#घोषणा CQE_STATUS_WRB_SHIFT	16

#घोषणा BEISCSI_HOST_MBX_TIMEOUT (110 * 1000)
#घोषणा BEISCSI_FW_MBX_TIMEOUT	100

/* MBOX Command VER */
#घोषणा MBX_CMD_VER1	0x01
#घोषणा MBX_CMD_VER2	0x02

काष्ठा be_mcc_compl अणु
	u32 status;		/* dword 0 */
	u32 tag0;		/* dword 1 */
	u32 tag1;		/* dword 2 */
	u32 flags;		/* dword 3 */
पूर्ण;

/********* Mailbox करोor bell *************/
/**
 * Used क्रम driver communication with the FW.
 * The software must ग_लिखो this रेजिस्टर twice to post any command. First,
 * it ग_लिखोs the रेजिस्टर with hi=1 and the upper bits of the physical address
 * क्रम the MAILBOX काष्ठाure. Software must poll the पढ़ोy bit until this
 * is acknowledged. Then, sotware ग_लिखोs the रेजिस्टर with hi=0 with the lower
 * bits in the address. It must poll the पढ़ोy bit until the command is
 * complete. Upon completion, the MAILBOX will contain a valid completion
 * queue entry.
 */
#घोषणा MPU_MAILBOX_DB_OFFSET	0x160
#घोषणा MPU_MAILBOX_DB_RDY_MASK	0x1	/* bit 0 */
#घोषणा MPU_MAILBOX_DB_HI_MASK	0x2	/* bit 1 */

/********** MPU semphore: used क्रम SH & BE ******************/
#घोषणा SLIPORT_SOFTRESET_OFFSET		0x5c	/* CSR BAR offset */
#घोषणा SLIPORT_SEMAPHORE_OFFSET_BEx		0xac	/* CSR BAR offset */
#घोषणा SLIPORT_SEMAPHORE_OFFSET_SH		0x94	/* PCI-CFG offset */
#घोषणा POST_STAGE_MASK				0x0000FFFF
#घोषणा POST_ERROR_BIT				0x80000000
#घोषणा POST_ERR_RECOVERY_CODE_MASK		0xF000

/* Soft Reset रेजिस्टर masks */
#घोषणा SLIPORT_SOFTRESET_SR_MASK		0x00000080	/* SR bit */

/* MPU semphore POST stage values */
#घोषणा POST_STAGE_AWAITING_HOST_RDY	0x1 /* FW aरुकोing goahead from host */
#घोषणा POST_STAGE_HOST_RDY		0x2 /* Host has given go-ahed to FW */
#घोषणा POST_STAGE_BE_RESET		0x3 /* Host wants to reset chip */
#घोषणा POST_STAGE_ARMFW_RDY		0xC000 /* FW is करोne with POST */
#घोषणा POST_STAGE_RECOVERABLE_ERR	0xE000 /* Recoverable err detected */

/********** MCC करोor bell ************/
#घोषणा DB_MCCQ_OFFSET 0x140
#घोषणा DB_MCCQ_RING_ID_MASK 0xFFFF		/* bits 0 - 15 */
/* Number of entries posted */
#घोषणा DB_MCCQ_NUM_POSTED_SHIFT 16		/* bits 16 - 29 */

/**
 * When the async bit of mcc_compl is set, the last 4 bytes of
 * mcc_compl is पूर्णांकerpreted as follows:
 */
#घोषणा ASYNC_TRAILER_EVENT_CODE_SHIFT	8	/* bits 8 - 15 */
#घोषणा ASYNC_TRAILER_EVENT_CODE_MASK	0xFF
#घोषणा ASYNC_EVENT_CODE_LINK_STATE	0x1
#घोषणा ASYNC_EVENT_CODE_ISCSI		0x4
#घोषणा ASYNC_EVENT_CODE_SLI		0x11

#घोषणा ASYNC_TRAILER_EVENT_TYPE_SHIFT	16	/* bits 16 - 23 */
#घोषणा ASYNC_TRAILER_EVENT_TYPE_MASK	0xFF

/* iSCSI events */
#घोषणा ASYNC_EVENT_NEW_ISCSI_TGT_DISC	0x4
#घोषणा ASYNC_EVENT_NEW_ISCSI_CONN	0x5
#घोषणा ASYNC_EVENT_NEW_TCP_CONN	0x7

/* SLI events */
#घोषणा ASYNC_SLI_EVENT_TYPE_MISCONFIGURED	0x9
#घोषणा ASYNC_SLI_LINK_EFFECT_VALID(le)		(le & 0x80)
#घोषणा ASYNC_SLI_LINK_EFFECT_SEV(le)		((le >> 1)  & 0x03)
#घोषणा ASYNC_SLI_LINK_EFFECT_STATE(le)		(le & 0x01)

काष्ठा be_async_event_trailer अणु
	u32 code;
पूर्ण;

क्रमागत अणु
	ASYNC_EVENT_LINK_DOWN = 0x0,
	ASYNC_EVENT_LINK_UP = 0x1,
पूर्ण;

/**
 * When the event code of an async trailer is link-state, the mcc_compl
 * must be पूर्णांकerpreted as follows
 */
काष्ठा be_async_event_link_state अणु
	u8 physical_port;
	u8 port_link_status;
/**
 * ASYNC_EVENT_LINK_DOWN		0x0
 * ASYNC_EVENT_LINK_UP			0x1
 * ASYNC_EVENT_LINK_LOGICAL_DOWN	0x2
 * ASYNC_EVENT_LINK_LOGICAL_UP		0x3
 */
#घोषणा BE_ASYNC_LINK_UP_MASK		0x01
	u8 port_duplex;
	u8 port_speed;
/* BE2ISCSI_LINK_SPEED_ZERO	0x00 - no link */
#घोषणा BE2ISCSI_LINK_SPEED_10MBPS	0x01
#घोषणा BE2ISCSI_LINK_SPEED_100MBPS	0x02
#घोषणा BE2ISCSI_LINK_SPEED_1GBPS	0x03
#घोषणा BE2ISCSI_LINK_SPEED_10GBPS	0x04
#घोषणा BE2ISCSI_LINK_SPEED_25GBPS	0x06
#घोषणा BE2ISCSI_LINK_SPEED_40GBPS	0x07
	u8 port_fault;
	u8 event_reason;
	u16 qos_link_speed;
	u32 event_tag;
	काष्ठा be_async_event_trailer trailer;
पूर्ण __packed;

/**
 * When async-trailer is SLI event, mcc_compl is पूर्णांकerpreted as
 */
काष्ठा be_async_event_sli अणु
	u32 event_data1;
	u32 event_data2;
	u32 reserved;
	u32 trailer;
पूर्ण __packed;

काष्ठा be_mcc_mailbox अणु
	काष्ठा be_mcc_wrb wrb;
	काष्ठा be_mcc_compl compl;
पूर्ण;

/* Type of subप्रणालीs supported by FW */
#घोषणा CMD_SUBSYSTEM_COMMON    0x1
#घोषणा CMD_SUBSYSTEM_ISCSI     0x2
#घोषणा CMD_SUBSYSTEM_ETH       0x3
#घोषणा CMD_SUBSYSTEM_ISCSI_INI 0x6
#घोषणा CMD_COMMON_TCP_UPLOAD   0x1

/**
 * List of common opcodes subप्रणाली  CMD_SUBSYSTEM_COMMON
 * These opcodes are unique क्रम each subप्रणाली defined above
 */
#घोषणा OPCODE_COMMON_CQ_CREATE				12
#घोषणा OPCODE_COMMON_EQ_CREATE				13
#घोषणा OPCODE_COMMON_MCC_CREATE			21
#घोषणा OPCODE_COMMON_MCC_CREATE_EXT			90
#घोषणा OPCODE_COMMON_ADD_TEMPLATE_HEADER_BUFFERS	24
#घोषणा OPCODE_COMMON_REMOVE_TEMPLATE_HEADER_BUFFERS	25
#घोषणा OPCODE_COMMON_GET_CNTL_ATTRIBUTES		32
#घोषणा OPCODE_COMMON_GET_FW_VERSION			35
#घोषणा OPCODE_COMMON_MODIFY_EQ_DELAY			41
#घोषणा OPCODE_COMMON_FIRMWARE_CONFIG			42
#घोषणा OPCODE_COMMON_MCC_DESTROY			53
#घोषणा OPCODE_COMMON_CQ_DESTROY			54
#घोषणा OPCODE_COMMON_EQ_DESTROY			55
#घोषणा OPCODE_COMMON_QUERY_FIRMWARE_CONFIG		58
#घोषणा OPCODE_COMMON_FUNCTION_RESET			61
#घोषणा OPCODE_COMMON_GET_PORT_NAME			77
#घोषणा OPCODE_COMMON_SET_HOST_DATA			93
#घोषणा OPCODE_COMMON_SET_FEATURES			191

/**
 * LIST of opcodes that are common between Initiator and Target
 * used by CMD_SUBSYSTEM_ISCSI
 * These opcodes are unique क्रम each subप्रणाली defined above
 */
#घोषणा OPCODE_COMMON_ISCSI_CFG_POST_SGL_PAGES		2
#घोषणा OPCODE_COMMON_ISCSI_CFG_REMOVE_SGL_PAGES        3
#घोषणा OPCODE_COMMON_ISCSI_NTWK_GET_NIC_CONFIG		7
#घोषणा OPCODE_COMMON_ISCSI_NTWK_SET_VLAN		14
#घोषणा OPCODE_COMMON_ISCSI_NTWK_CONFIG_STATELESS_IP_ADDR	17
#घोषणा OPCODE_COMMON_ISCSI_NTWK_REL_STATELESS_IP_ADDR	18
#घोषणा OPCODE_COMMON_ISCSI_NTWK_MODIFY_IP_ADDR		21
#घोषणा OPCODE_COMMON_ISCSI_NTWK_GET_DEFAULT_GATEWAY	22
#घोषणा OPCODE_COMMON_ISCSI_NTWK_MODIFY_DEFAULT_GATEWAY 23
#घोषणा OPCODE_COMMON_ISCSI_NTWK_GET_ALL_IF_ID		24
#घोषणा OPCODE_COMMON_ISCSI_NTWK_GET_IF_INFO		25
#घोषणा OPCODE_COMMON_ISCSI_SET_FRAGNUM_BITS_FOR_SGL_CRA 61
#घोषणा OPCODE_COMMON_ISCSI_DEFQ_CREATE                 64
#घोषणा OPCODE_COMMON_ISCSI_DEFQ_DESTROY		65
#घोषणा OPCODE_COMMON_ISCSI_WRBQ_CREATE			66
#घोषणा OPCODE_COMMON_ISCSI_WRBQ_DESTROY		67

काष्ठा be_cmd_req_hdr अणु
	u8 opcode;		/* dword 0 */
	u8 subप्रणाली;		/* dword 0 */
	u8 port_number;		/* dword 0 */
	u8 करोमुख्य;		/* dword 0 */
	u32 समयout;		/* dword 1 */
	u32 request_length;	/* dword 2 */
	u8 version;		/* dword 3 */
	u8 rsvd0[3];		/* dword 3 */
पूर्ण;

काष्ठा be_cmd_resp_hdr अणु
	u32 info;		/* dword 0 */
	u32 status;		/* dword 1 */
	u32 response_length;	/* dword 2 */
	u32 actual_resp_len;	/* dword 3 */
पूर्ण;

काष्ठा phys_addr अणु
	u32 lo;
	u32 hi;
पूर्ण;

काष्ठा virt_addr अणु
	u32 lo;
	u32 hi;
पूर्ण;
/**************************
 * BE Command definitions *
 **************************/

/**
 * Pseuकरो amap definition in which each bit of the actual काष्ठाure is defined
 * as a byte - used to calculate offset/shअगरt/mask of each field
 */
काष्ठा amap_eq_context अणु
	u8 cidx[13];		/* dword 0 */
	u8 rsvd0[3];		/* dword 0 */
	u8 epidx[13];		/* dword 0 */
	u8 valid;		/* dword 0 */
	u8 rsvd1;		/* dword 0 */
	u8 size;		/* dword 0 */
	u8 pidx[13];		/* dword 1 */
	u8 rsvd2[3];		/* dword 1 */
	u8 pd[10];		/* dword 1 */
	u8 count[3];		/* dword 1 */
	u8 solevent;		/* dword 1 */
	u8 stalled;		/* dword 1 */
	u8 armed;		/* dword 1 */
	u8 rsvd3[4];		/* dword 2 */
	u8 func[8];		/* dword 2 */
	u8 rsvd4;		/* dword 2 */
	u8 delaymult[10];	/* dword 2 */
	u8 rsvd5[2];		/* dword 2 */
	u8 phase[2];		/* dword 2 */
	u8 nodelay;		/* dword 2 */
	u8 rsvd6[4];		/* dword 2 */
	u8 rsvd7[32];		/* dword 3 */
पूर्ण __packed;

काष्ठा be_cmd_req_eq_create अणु
	काष्ठा be_cmd_req_hdr hdr;	/* dw[4] */
	u16 num_pages;		/* sword */
	u16 rsvd0;		/* sword */
	u8 context[माप(काष्ठा amap_eq_context) / 8];	/* dw[4] */
	काष्ठा phys_addr pages[8];
पूर्ण __packed;

काष्ठा be_cmd_resp_eq_create अणु
	काष्ठा be_cmd_resp_hdr resp_hdr;
	u16 eq_id;		/* sword */
	u16 rsvd0;		/* sword */
पूर्ण __packed;

काष्ठा be_set_eqd अणु
	u32 eq_id;
	u32 phase;
	u32 delay_multiplier;
पूर्ण __packed;

काष्ठा mgmt_chap_क्रमmat अणु
	u32 flags;
	u8  पूर्णांकr_chap_name[256];
	u8  पूर्णांकr_secret[16];
	u8  target_chap_name[256];
	u8  target_secret[16];
	u16 पूर्णांकr_chap_name_length;
	u16 पूर्णांकr_secret_length;
	u16 target_chap_name_length;
	u16 target_secret_length;
पूर्ण __packed;

काष्ठा mgmt_auth_method_क्रमmat अणु
	u8	auth_method_type;
	u8	padding[3];
	काष्ठा	mgmt_chap_क्रमmat chap;
पूर्ण __packed;

काष्ठा be_cmd_req_logout_fw_sess अणु
	काष्ठा be_cmd_req_hdr hdr;	/* dw[4] */
	uपूर्णांक32_t session_handle;
पूर्ण __packed;

काष्ठा be_cmd_resp_logout_fw_sess अणु
	काष्ठा be_cmd_resp_hdr hdr;	/* dw[4] */
	uपूर्णांक32_t session_status;
#घोषणा BE_SESS_STATUS_CLOSE		0x20
पूर्ण __packed;

काष्ठा mgmt_conn_login_options अणु
	u8 flags;
	u8 header_digest;
	u8 data_digest;
	u8 rsvd0;
	u32 max_recv_datasegment_len_ini;
	u32 max_recv_datasegment_len_tgt;
	u32 tcp_mss;
	u32 tcp_winकरोw_size;
	काष्ठा	mgmt_auth_method_क्रमmat auth_data;
पूर्ण __packed;

काष्ठा ip_addr_क्रमmat अणु
	u16 size_of_काष्ठाure;
	u8 reserved;
	u8 ip_type;
#घोषणा BEISCSI_IP_TYPE_V4		0x1
#घोषणा BEISCSI_IP_TYPE_STATIC_V4	0x3
#घोषणा BEISCSI_IP_TYPE_DHCP_V4		0x5
/* type v4 values < type v6 values */
#घोषणा BEISCSI_IP_TYPE_V6		0x10
#घोषणा BEISCSI_IP_TYPE_ROUTABLE_V6	0x30
#घोषणा BEISCSI_IP_TYPE_LINK_LOCAL_V6	0x50
#घोषणा BEISCSI_IP_TYPE_AUTO_V6		0x90
	u8 addr[16];
	u32 rsvd0;
पूर्ण __packed;

काष्ठा mgmt_conn_info अणु
	u32	connection_handle;
	u32	connection_status;
	u16	src_port;
	u16	dest_port;
	u16	dest_port_redirected;
	u16	cid;
	u32	estimated_throughput;
	काष्ठा	ip_addr_क्रमmat	src_ipaddr;
	काष्ठा	ip_addr_क्रमmat	dest_ipaddr;
	काष्ठा	ip_addr_क्रमmat	dest_ipaddr_redirected;
	काष्ठा	mgmt_conn_login_options	negotiated_login_options;
पूर्ण __packed;

काष्ठा mgmt_session_login_options अणु
	u8	flags;
	u8	error_recovery_level;
	u16	rsvd0;
	u32	first_burst_length;
	u32	max_burst_length;
	u16	max_connections;
	u16	max_outstanding_r2t;
	u16	शेष_समय2रुको;
	u16	शेष_समय2retain;
पूर्ण __packed;

काष्ठा mgmt_session_info अणु
	u32	session_handle;
	u32	status;
	u8	isid[6];
	u16	tsih;
	u32	session_flags;
	u16	conn_count;
	u16	pad;
	u8	target_name[224];
	u8	initiator_iscsiname[224];
	काष्ठा	mgmt_session_login_options negotiated_login_options;
	काष्ठा	mgmt_conn_info	conn_list[1];
पूर्ण __packed;

काष्ठा be_cmd_get_session_req अणु
	काष्ठा be_cmd_req_hdr hdr;
	u32 session_handle;
पूर्ण __packed;

काष्ठा be_cmd_get_session_resp अणु
	काष्ठा be_cmd_resp_hdr hdr;
	काष्ठा mgmt_session_info session_info;
पूर्ण __packed;

काष्ठा mac_addr अणु
	u16 size_of_काष्ठाure;
	u8 addr[ETH_ALEN];
पूर्ण __packed;

काष्ठा be_cmd_get_boot_target_req अणु
	काष्ठा be_cmd_req_hdr hdr;
पूर्ण __packed;

काष्ठा be_cmd_get_boot_target_resp अणु
	काष्ठा be_cmd_resp_hdr hdr;
	u32 boot_session_count;
	u32 boot_session_handle;
/**
 * FW वापसs 0xffffffff अगर it couldn't establish connection with
 * configured boot target.
 */
#घोषणा BE_BOOT_INVALID_SHANDLE	0xffffffff
पूर्ण;

काष्ठा be_cmd_reखोलो_session_req अणु
	काष्ठा be_cmd_req_hdr hdr;
#घोषणा BE_REOPEN_ALL_SESSIONS  0x00
#घोषणा BE_REOPEN_BOOT_SESSIONS 0x01
#घोषणा BE_REOPEN_A_SESSION     0x02
	u16 reखोलो_type;
	u16 rsvd;
	u32 session_handle;
पूर्ण __packed;

काष्ठा be_cmd_reखोलो_session_resp अणु
	काष्ठा be_cmd_resp_hdr hdr;
	u32 rsvd;
	u32 session_handle;
पूर्ण __packed;


काष्ठा be_cmd_mac_query_req अणु
	काष्ठा be_cmd_req_hdr hdr;
	u8 type;
	u8 permanent;
	u16 अगर_id;
पूर्ण __packed;

काष्ठा be_cmd_get_mac_resp अणु
	काष्ठा be_cmd_resp_hdr hdr;
	काष्ठा mac_addr mac;
पूर्ण;

काष्ठा be_ip_addr_subnet_क्रमmat अणु
	u16 size_of_काष्ठाure;
	u8 ip_type;
	u8 ipv6_prefix_length;
	u8 addr[16];
	u8 subnet_mask[16];
	u32 rsvd0;
पूर्ण __packed;

काष्ठा be_cmd_get_अगर_info_req अणु
	काष्ठा be_cmd_req_hdr hdr;
	u32 पूर्णांकerface_hndl;
	u32 ip_type;
पूर्ण __packed;

काष्ठा be_cmd_get_अगर_info_resp अणु
	काष्ठा be_cmd_req_hdr hdr;
	u32 पूर्णांकerface_hndl;
	u32 vlan_priority;
	u32 ip_addr_count;
	u32 dhcp_state;
	काष्ठा be_ip_addr_subnet_क्रमmat ip_addr;
पूर्ण __packed;

काष्ठा be_ip_addr_record अणु
	u32 action;
	u32 पूर्णांकerface_hndl;
	काष्ठा be_ip_addr_subnet_क्रमmat ip_addr;
	u32 status;
पूर्ण __packed;

काष्ठा be_ip_addr_record_params अणु
	u32 record_entry_count;
	काष्ठा be_ip_addr_record ip_record;
पूर्ण __packed;

काष्ठा be_cmd_set_ip_addr_req अणु
	काष्ठा be_cmd_req_hdr hdr;
	काष्ठा be_ip_addr_record_params ip_params;
पूर्ण __packed;


काष्ठा be_cmd_set_dhcp_req अणु
	काष्ठा be_cmd_req_hdr hdr;
	u32 पूर्णांकerface_hndl;
	u32 ip_type;
	u32 flags;
	u32 retry_count;
पूर्ण __packed;

काष्ठा be_cmd_rel_dhcp_req अणु
	काष्ठा be_cmd_req_hdr hdr;
	u32 पूर्णांकerface_hndl;
	u32 ip_type;
पूर्ण __packed;

काष्ठा be_cmd_set_def_gateway_req अणु
	काष्ठा be_cmd_req_hdr hdr;
	u32 action;
	काष्ठा ip_addr_क्रमmat ip_addr;
पूर्ण __packed;

काष्ठा be_cmd_get_def_gateway_req अणु
	काष्ठा be_cmd_req_hdr hdr;
	u32 ip_type;
पूर्ण __packed;

काष्ठा be_cmd_get_def_gateway_resp अणु
	काष्ठा be_cmd_req_hdr hdr;
	काष्ठा ip_addr_क्रमmat ip_addr;
पूर्ण __packed;

#घोषणा BEISCSI_VLAN_DISABLE	0xFFFF
काष्ठा be_cmd_set_vlan_req अणु
	काष्ठा be_cmd_req_hdr hdr;
	u32 पूर्णांकerface_hndl;
	u32 vlan_priority;
पूर्ण __packed;
/******************** Create CQ ***************************/
/**
 * Pseuकरो amap definition in which each bit of the actual काष्ठाure is defined
 * as a byte - used to calculate offset/shअगरt/mask of each field
 */
काष्ठा amap_cq_context अणु
	u8 cidx[11];		/* dword 0 */
	u8 rsvd0;		/* dword 0 */
	u8 coalescwm[2];	/* dword 0 */
	u8 nodelay;		/* dword 0 */
	u8 epidx[11];		/* dword 0 */
	u8 rsvd1;		/* dword 0 */
	u8 count[2];		/* dword 0 */
	u8 valid;		/* dword 0 */
	u8 solevent;		/* dword 0 */
	u8 eventable;		/* dword 0 */
	u8 pidx[11];		/* dword 1 */
	u8 rsvd2;		/* dword 1 */
	u8 pd[10];		/* dword 1 */
	u8 eqid[8];		/* dword 1 */
	u8 stalled;		/* dword 1 */
	u8 armed;		/* dword 1 */
	u8 rsvd3[4];		/* dword 2 */
	u8 func[8];		/* dword 2 */
	u8 rsvd4[20];		/* dword 2 */
	u8 rsvd5[32];		/* dword 3 */
पूर्ण __packed;

काष्ठा amap_cq_context_v2 अणु
	u8 rsvd0[12];   /* dword 0 */
	u8 coalescwm[2];    /* dword 0 */
	u8 nodelay;     /* dword 0 */
	u8 rsvd1[12];   /* dword 0 */
	u8 count[2];    /* dword 0 */
	u8 valid;       /* dword 0 */
	u8 rsvd2;       /* dword 0 */
	u8 eventable;   /* dword 0 */
	u8 eqid[16];    /* dword 1 */
	u8 rsvd3[15];   /* dword 1 */
	u8 armed;       /* dword 1 */
	u8 cqecount[16];/* dword 2 */
	u8 rsvd4[16];   /* dword 2 */
	u8 rsvd5[32];   /* dword 3 */
पूर्ण;

काष्ठा be_cmd_req_cq_create अणु
	काष्ठा be_cmd_req_hdr hdr;
	u16 num_pages;
	u8 page_size;
	u8 rsvd0;
	u8 context[माप(काष्ठा amap_cq_context) / 8];
	काष्ठा phys_addr pages[4];
पूर्ण __packed;

काष्ठा be_cmd_resp_cq_create अणु
	काष्ठा be_cmd_resp_hdr hdr;
	u16 cq_id;
	u16 rsvd0;
पूर्ण __packed;

/******************** Create MCCQ ***************************/
/**
 * Pseuकरो amap definition in which each bit of the actual काष्ठाure is defined
 * as a byte - used to calculate offset/shअगरt/mask of each field
 */
काष्ठा amap_mcc_context अणु
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

काष्ठा be_cmd_req_mcc_create_ext अणु
	काष्ठा be_cmd_req_hdr hdr;
	u16 num_pages;
	u16 rsvd0;
	u32 async_evt_biपंचांगap;
	u8 context[माप(काष्ठा amap_mcc_context) / 8];
	काष्ठा phys_addr pages[8];
पूर्ण __packed;

काष्ठा be_cmd_resp_mcc_create अणु
	काष्ठा be_cmd_resp_hdr hdr;
	u16 id;
	u16 rsvd0;
पूर्ण __packed;

/******************** Q Destroy  ***************************/
/* Type of Queue to be destroyed */
क्रमागत अणु
	QTYPE_EQ = 1,
	QTYPE_CQ,
	QTYPE_MCCQ,
	QTYPE_WRBQ,
	QTYPE_DPDUQ,
	QTYPE_SGL
पूर्ण;

काष्ठा be_cmd_req_q_destroy अणु
	काष्ठा be_cmd_req_hdr hdr;
	u16 id;
	u16 bypass_flush;	/* valid only क्रम rx q destroy */
पूर्ण __packed;

काष्ठा macaddr अणु
	u8 byte[ETH_ALEN];
पूर्ण;

काष्ठा be_cmd_req_mcast_mac_config अणु
	काष्ठा be_cmd_req_hdr hdr;
	u16 num_mac;
	u8 promiscuous;
	u8 पूर्णांकerface_id;
	काष्ठा macaddr mac[32];
पूर्ण __packed;

अटल अंतरभूत व्योम *embedded_payload(काष्ठा be_mcc_wrb *wrb)
अणु
	वापस wrb->payload.embedded_payload;
पूर्ण

अटल अंतरभूत काष्ठा be_sge *nonembedded_sgl(काष्ठा be_mcc_wrb *wrb)
अणु
	वापस &wrb->payload.sgl[0];
पूर्ण

/******************** Modअगरy EQ Delay *******************/
काष्ठा be_cmd_req_modअगरy_eq_delay अणु
	काष्ठा be_cmd_req_hdr hdr;
	__le32 num_eq;
	काष्ठा अणु
		__le32 eq_id;
		__le32 phase;
		__le32 delay_multiplier;
	पूर्ण delay[MAX_CPUS];
पूर्ण __packed;

/******************** Get MAC ADDR *******************/

काष्ठा be_cmd_get_nic_conf_resp अणु
	काष्ठा be_cmd_resp_hdr hdr;
	u32 nic_port_count;
	u32 speed;
	u32 max_speed;
	u32 link_state;
	u32 max_frame_size;
	u16 size_of_काष्ठाure;
	u8 mac_address[ETH_ALEN];
पूर्ण __packed;

/******************** Get HBA NAME *******************/

काष्ठा be_cmd_hba_name अणु
	काष्ठा be_cmd_req_hdr hdr;
	u16 flags;
	u16 rsvd0;
	u8 initiator_name[ISCSI_NAME_LEN];
#घोषणा BE_INI_ALIAS_LEN 32
	u8 initiator_alias[BE_INI_ALIAS_LEN];
पूर्ण __packed;

/******************** COMMON SET HOST DATA *******************/
#घोषणा BE_CMD_SET_HOST_PARAM_ID	0x2
#घोषणा BE_CMD_MAX_DRV_VERSION		0x30
काष्ठा be_sethost_req अणु
	u32 param_id;
	u32 param_len;
	u32 param_data[32];
पूर्ण;

काष्ठा be_sethost_resp अणु
	u32 rsvd0;
पूर्ण;

काष्ठा be_cmd_set_host_data अणु
	जोड़ अणु
		काष्ठा be_cmd_req_hdr req_hdr;
		काष्ठा be_cmd_resp_hdr resp_hdr;
	पूर्ण h;
	जोड़ अणु
		काष्ठा be_sethost_req req;
		काष्ठा be_sethost_resp resp;
	पूर्ण param;
पूर्ण __packed;

/******************** COMMON SET Features *******************/
#घोषणा BE_CMD_SET_FEATURE_UER	0x10
#घोषणा BE_CMD_UER_SUPP_BIT	0x1
काष्ठा be_uer_req अणु
	u32 uer;
	u32 rsvd;
पूर्ण;

काष्ठा be_uer_resp अणु
	u32 uer;
	u16 ue2rp;
	u16 ue2sr;
पूर्ण;

काष्ठा be_cmd_set_features अणु
	जोड़ अणु
		काष्ठा be_cmd_req_hdr req_hdr;
		काष्ठा be_cmd_resp_hdr resp_hdr;
	पूर्ण h;
	u32 feature;
	u32 param_len;
	जोड़ अणु
		काष्ठा be_uer_req req;
		काष्ठा be_uer_resp resp;
		u32 rsvd[2];
	पूर्ण param;
पूर्ण __packed;

पूर्णांक beiscsi_cmd_function_reset(काष्ठा beiscsi_hba *phba);

पूर्णांक beiscsi_cmd_special_wrb(काष्ठा be_ctrl_info *ctrl, u32 load);

पूर्णांक beiscsi_check_fw_rdy(काष्ठा beiscsi_hba *phba);

पूर्णांक beiscsi_init_sliport(काष्ठा beiscsi_hba *phba);

पूर्णांक beiscsi_cmd_iscsi_cleanup(काष्ठा beiscsi_hba *phba, अचिन्हित लघु ulp_num);

पूर्णांक beiscsi_detect_ue(काष्ठा beiscsi_hba *phba);

पूर्णांक beiscsi_detect_tpe(काष्ठा beiscsi_hba *phba);

पूर्णांक beiscsi_cmd_eq_create(काष्ठा be_ctrl_info *ctrl,
			  काष्ठा be_queue_info *eq, पूर्णांक eq_delay);

पूर्णांक beiscsi_cmd_cq_create(काष्ठा be_ctrl_info *ctrl,
			  काष्ठा be_queue_info *cq, काष्ठा be_queue_info *eq,
			  bool sol_evts, bool no_delay,
			  पूर्णांक num_cqe_dma_coalesce);

पूर्णांक beiscsi_cmd_q_destroy(काष्ठा be_ctrl_info *ctrl, काष्ठा be_queue_info *q,
			  पूर्णांक type);
पूर्णांक beiscsi_cmd_mccq_create(काष्ठा beiscsi_hba *phba,
			काष्ठा be_queue_info *mccq,
			काष्ठा be_queue_info *cq);

व्योम मुक्त_mcc_wrb(काष्ठा be_ctrl_info *ctrl, अचिन्हित पूर्णांक tag);

पूर्णांक beiscsi_modअगरy_eq_delay(काष्ठा beiscsi_hba *phba, काष्ठा be_set_eqd *,
			    पूर्णांक num);
पूर्णांक beiscsi_mccq_compl_रुको(काष्ठा beiscsi_hba *phba,
			    अचिन्हित पूर्णांक tag,
			    काष्ठा be_mcc_wrb **wrb,
			    काष्ठा be_dma_mem *mbx_cmd_mem);
पूर्णांक __beiscsi_mcc_compl_status(काष्ठा beiscsi_hba *phba,
			       अचिन्हित पूर्णांक tag,
			       काष्ठा be_mcc_wrb **wrb,
			       काष्ठा be_dma_mem *mbx_cmd_mem);
काष्ठा be_mcc_wrb *wrb_from_mbox(काष्ठा be_dma_mem *mbox_mem);
व्योम be_mcc_notअगरy(काष्ठा beiscsi_hba *phba, अचिन्हित पूर्णांक tag);
काष्ठा be_mcc_wrb *alloc_mcc_wrb(काष्ठा beiscsi_hba *phba,
				 अचिन्हित पूर्णांक *ref_tag);
व्योम beiscsi_process_async_event(काष्ठा beiscsi_hba *phba,
				काष्ठा be_mcc_compl *compl);
पूर्णांक beiscsi_process_mcc_compl(काष्ठा be_ctrl_info *ctrl,
			      काष्ठा be_mcc_compl *compl);

पूर्णांक be_cmd_create_शेष_pdu_queue(काष्ठा be_ctrl_info *ctrl,
				    काष्ठा be_queue_info *cq,
				    काष्ठा be_queue_info *dq, पूर्णांक length,
				    पूर्णांक entry_size, uपूर्णांक8_t is_header,
				    uपूर्णांक8_t ulp_num);

पूर्णांक be_cmd_iscsi_post_ढाँचा_hdr(काष्ठा be_ctrl_info *ctrl,
				    काष्ठा be_dma_mem *q_mem);

पूर्णांक be_cmd_iscsi_हटाओ_ढाँचा_hdr(काष्ठा be_ctrl_info *ctrl);

पूर्णांक be_cmd_iscsi_post_sgl_pages(काष्ठा be_ctrl_info *ctrl,
				काष्ठा be_dma_mem *q_mem, u32 page_offset,
				u32 num_pages);

पूर्णांक be_cmd_wrbq_create(काष्ठा be_ctrl_info *ctrl, काष्ठा be_dma_mem *q_mem,
		       काष्ठा be_queue_info *wrbq,
		       काष्ठा hwi_wrb_context *pwrb_context,
		       uपूर्णांक8_t ulp_num);

/* Configuration Functions */
पूर्णांक be_cmd_set_vlan(काष्ठा beiscsi_hba *phba, uपूर्णांक16_t vlan_tag);

पूर्णांक beiscsi_check_supported_fw(काष्ठा be_ctrl_info *ctrl,
			       काष्ठा beiscsi_hba *phba);

पूर्णांक beiscsi_get_fw_config(काष्ठा be_ctrl_info *ctrl, काष्ठा beiscsi_hba *phba);

पूर्णांक beiscsi_get_port_name(काष्ठा be_ctrl_info *ctrl, काष्ठा beiscsi_hba *phba);

पूर्णांक beiscsi_set_uer_feature(काष्ठा beiscsi_hba *phba);
पूर्णांक beiscsi_set_host_data(काष्ठा beiscsi_hba *phba);

काष्ठा be_शेष_pdu_context अणु
	u32 dw[4];
पूर्ण __packed;

काष्ठा amap_be_शेष_pdu_context अणु
	u8 dbuf_cindex[13];	/* dword 0 */
	u8 rsvd0[3];		/* dword 0 */
	u8 ring_size[4];	/* dword 0 */
	u8 ring_state[4];	/* dword 0 */
	u8 rsvd1[8];		/* dword 0 */
	u8 dbuf_pindex[13];	/* dword 1 */
	u8 rsvd2;		/* dword 1 */
	u8 pci_func_id[8];	/* dword 1 */
	u8 rx_pdid[9];		/* dword 1 */
	u8 rx_pdid_valid;	/* dword 1 */
	u8 शेष_buffer_size[16];	/* dword 2 */
	u8 cq_id_recv[10];	/* dword 2 */
	u8 rx_pdid_not_valid;	/* dword 2 */
	u8 rsvd3[5];		/* dword 2 */
	u8 rsvd4[32];		/* dword 3 */
पूर्ण __packed;

काष्ठा amap_शेष_pdu_context_ext अणु
	u8 rsvd0[16];   /* dword 0 */
	u8 ring_size[4];    /* dword 0 */
	u8 rsvd1[12];   /* dword 0 */
	u8 rsvd2[22];   /* dword 1 */
	u8 rx_pdid[9];  /* dword 1 */
	u8 rx_pdid_valid;   /* dword 1 */
	u8 शेष_buffer_size[16]; /* dword 2 */
	u8 cq_id_recv[16];  /* dword 2 */
	u8 rsvd3[32];   /* dword 3 */
पूर्ण __packed;

काष्ठा be_defq_create_req अणु
	काष्ठा be_cmd_req_hdr hdr;
	u16 num_pages;
	u8 ulp_num;
#घोषणा BEISCSI_DUAL_ULP_AWARE_BIT	0	/* Byte 3 - Bit 0 */
#घोषणा BEISCSI_BIND_Q_TO_ULP_BIT	1	/* Byte 3 - Bit 1 */
	u8 dua_feature;
	काष्ठा be_शेष_pdu_context context;
	काष्ठा phys_addr pages[8];
पूर्ण __packed;

काष्ठा be_defq_create_resp अणु
	काष्ठा be_cmd_req_hdr hdr;
	u16 id;
	u8 rsvd0;
	u8 ulp_num;
	u32 करोorbell_offset;
	u16 रेजिस्टर_set;
	u16 करोorbell_क्रमmat;
पूर्ण __packed;

काष्ठा be_post_ढाँचा_pages_req अणु
	काष्ठा be_cmd_req_hdr hdr;
	u16 num_pages;
#घोषणा BEISCSI_TEMPLATE_HDR_TYPE_ISCSI	0x1
	u16 type;
	काष्ठा phys_addr scratch_pa;
	काष्ठा virt_addr scratch_va;
	काष्ठा virt_addr pages_va;
	काष्ठा phys_addr pages[16];
पूर्ण __packed;

काष्ठा be_हटाओ_ढाँचा_pages_req अणु
	काष्ठा be_cmd_req_hdr hdr;
	u16 type;
	u16 rsvd0;
पूर्ण __packed;

काष्ठा be_post_sgl_pages_req अणु
	काष्ठा be_cmd_req_hdr hdr;
	u16 num_pages;
	u16 page_offset;
	u32 rsvd0;
	काष्ठा phys_addr pages[26];
	u32 rsvd1;
पूर्ण __packed;

काष्ठा be_wrbq_create_req अणु
	काष्ठा be_cmd_req_hdr hdr;
	u16 num_pages;
	u8 ulp_num;
	u8 dua_feature;
	काष्ठा phys_addr pages[8];
पूर्ण __packed;

काष्ठा be_wrbq_create_resp अणु
	काष्ठा be_cmd_resp_hdr resp_hdr;
	u16 cid;
	u8 rsvd0;
	u8 ulp_num;
	u32 करोorbell_offset;
	u16 रेजिस्टर_set;
	u16 करोorbell_क्रमmat;
पूर्ण __packed;

#घोषणा SOL_CID_MASK		0x0000FFC0
#घोषणा SOL_CODE_MASK		0x0000003F
#घोषणा SOL_WRB_INDEX_MASK	0x00FF0000
#घोषणा SOL_CMD_WND_MASK	0xFF000000
#घोषणा SOL_RES_CNT_MASK	0x7FFFFFFF
#घोषणा SOL_EXP_CMD_SN_MASK	0xFFFFFFFF
#घोषणा SOL_HW_STS_MASK		0x000000FF
#घोषणा SOL_STS_MASK		0x0000FF00
#घोषणा SOL_RESP_MASK		0x00FF0000
#घोषणा SOL_FLAGS_MASK		0x7F000000
#घोषणा SOL_S_MASK		0x80000000

काष्ठा sol_cqe अणु
	u32 dw[4];
पूर्ण;

काष्ठा amap_sol_cqe अणु
	u8 hw_sts[8];		/* dword 0 */
	u8 i_sts[8];		/* dword 0 */
	u8 i_resp[8];		/* dword 0 */
	u8 i_flags[7];		/* dword 0 */
	u8 s;			/* dword 0 */
	u8 i_exp_cmd_sn[32];	/* dword 1 */
	u8 code[6];		/* dword 2 */
	u8 cid[10];		/* dword 2 */
	u8 wrb_index[8];	/* dword 2 */
	u8 i_cmd_wnd[8];	/* dword 2 */
	u8 i_res_cnt[31];	/* dword 3 */
	u8 valid;		/* dword 3 */
पूर्ण __packed;

#घोषणा SOL_ICD_INDEX_MASK	0x0003FFC0
काष्ठा amap_sol_cqe_ring अणु
	u8 hw_sts[8];		/* dword 0 */
	u8 i_sts[8];		/* dword 0 */
	u8 i_resp[8];		/* dword 0 */
	u8 i_flags[7];		/* dword 0 */
	u8 s;			/* dword 0 */
	u8 i_exp_cmd_sn[32];	/* dword 1 */
	u8 code[6];		/* dword 2 */
	u8 icd_index[12];	/* dword 2 */
	u8 rsvd[6];		/* dword 2 */
	u8 i_cmd_wnd[8];	/* dword 2 */
	u8 i_res_cnt[31];	/* dword 3 */
	u8 valid;		/* dword 3 */
पूर्ण __packed;

काष्ठा amap_sol_cqe_v2 अणु
	u8 hw_sts[8];   /* dword 0 */
	u8 i_sts[8];    /* dword 0 */
	u8 wrb_index[16];   /* dword 0 */
	u8 i_exp_cmd_sn[32];    /* dword 1 */
	u8 code[6]; /* dword 2 */
	u8 cmd_cmpl;    /* dword 2 */
	u8 rsvd0;   /* dword 2 */
	u8 i_cmd_wnd[8];    /* dword 2 */
	u8 cid[13]; /* dword 2 */
	u8 u;   /* dword 2 */
	u8 o;   /* dword 2 */
	u8 s;   /* dword 2 */
	u8 i_res_cnt[31];   /* dword 3 */
	u8 valid;   /* dword 3 */
पूर्ण __packed;

काष्ठा common_sol_cqe अणु
	u32 exp_cmdsn;
	u32 res_cnt;
	u16 wrb_index;
	u16 cid;
	u8 hw_sts;
	u8 cmd_wnd;
	u8 res_flag; /* the s feild of काष्ठाure */
	u8 i_resp; /* क्रम skh अगर cmd_complete is set then i_sts is response */
	u8 i_flags; /* क्रम skh or the u and o feilds */
	u8 i_sts; /* क्रम skh अगर cmd_complete is not-set then i_sts is status */
पूर्ण;

/*** iSCSI ack/driver message completions ***/
काष्ठा amap_it_dmsg_cqe अणु
	u8 ack_num[32]; /* DWORD 0 */
	u8 pdu_bytes_rcvd[32];  /* DWORD 1 */
	u8 code[6]; /* DWORD 2 */
	u8 cid[10]; /* DWORD 2 */
	u8 wrb_idx[8];  /* DWORD 2 */
	u8 rsvd0[8];    /* DWORD 2*/
	u8 rsvd1[31];   /* DWORD 3*/
	u8 valid;   /* DWORD 3 */
पूर्ण __packed;

काष्ठा amap_it_dmsg_cqe_v2 अणु
	u8 ack_num[32]; /* DWORD 0 */
	u8 pdu_bytes_rcvd[32];  /* DWORD 1 */
	u8 code[6]; /* DWORD 2 */
	u8 rsvd0[10];   /* DWORD 2 */
	u8 wrb_idx[16]; /* DWORD 2 */
	u8 rsvd1[16];   /* DWORD 3 */
	u8 cid[13]; /* DWORD 3 */
	u8 rsvd2[2];    /* DWORD 3 */
	u8 valid;   /* DWORD 3 */
पूर्ण __packed;


/**
 * Post WRB Queue Doorbell Register used by the host Storage
 * stack to notअगरy the
 * controller of a posted Work Request Block
 */
#घोषणा DB_WRB_POST_CID_MASK		0xFFFF	/* bits 0 - 16 */
#घोषणा DB_DEF_PDU_WRB_INDEX_MASK	0xFF	/* bits 0 - 9 */

#घोषणा DB_DEF_PDU_WRB_INDEX_SHIFT	16
#घोषणा DB_DEF_PDU_NUM_POSTED_SHIFT	24

काष्ठा fragnum_bits_क्रम_sgl_cra_in अणु
	काष्ठा be_cmd_req_hdr hdr;
	u32 num_bits;
पूर्ण __packed;

काष्ठा iscsi_cleanup_req अणु
	काष्ठा be_cmd_req_hdr hdr;
	u16 chute;
	u8 hdr_ring_id;
	u8 data_ring_id;
पूर्ण __packed;

काष्ठा iscsi_cleanup_req_v1 अणु
	काष्ठा be_cmd_req_hdr hdr;
	u16 chute;
	u16 rsvd1;
	u16 hdr_ring_id;
	u16 rsvd2;
	u16 data_ring_id;
	u16 rsvd3;
पूर्ण __packed;

काष्ठा eq_delay अणु
	u32 eq_id;
	u32 phase;
	u32 delay_multiplier;
पूर्ण __packed;

काष्ठा be_eq_delay_params_in अणु
	काष्ठा be_cmd_req_hdr hdr;
	u32 num_eq;
	काष्ठा eq_delay delay[8];
पूर्ण __packed;

काष्ठा tcp_connect_and_offload_in अणु
	काष्ठा be_cmd_req_hdr hdr;
	काष्ठा ip_addr_क्रमmat ip_address;
	u16 tcp_port;
	u16 cid;
	u16 cq_id;
	u16 defq_id;
	काष्ठा phys_addr dataout_ढाँचा_pa;
	u16 hdr_ring_id;
	u16 data_ring_id;
	u8 करो_offload;
	u8 rsvd0[3];
पूर्ण __packed;

काष्ठा tcp_connect_and_offload_in_v1 अणु
	काष्ठा be_cmd_req_hdr hdr;
	काष्ठा ip_addr_क्रमmat ip_address;
	u16 tcp_port;
	u16 cid;
	u16 cq_id;
	u16 defq_id;
	काष्ठा phys_addr dataout_ढाँचा_pa;
	u16 hdr_ring_id;
	u16 data_ring_id;
	u8 करो_offload;
	u8 अगरd_state;
	u8 rsvd0[2];
	u16 tcp_winकरोw_size;
	u8 tcp_winकरोw_scale_count;
	u8 rsvd1;
	u32 tcp_mss:24;
	u8 rsvd2;
पूर्ण __packed;

काष्ठा tcp_connect_and_offload_out अणु
	काष्ठा be_cmd_resp_hdr hdr;
	u32 connection_handle;
	u16 cid;
	u16 rsvd0;

पूर्ण __packed;

#घोषणा DB_DEF_PDU_RING_ID_MASK	0x3FFF	/* bits 0 - 13 */
#घोषणा DB_DEF_PDU_CQPROC_MASK		0x3FFF	/* bits 16 - 29 */
#घोषणा DB_DEF_PDU_REARM_SHIFT		14
#घोषणा DB_DEF_PDU_EVENT_SHIFT		15
#घोषणा DB_DEF_PDU_CQPROC_SHIFT		16

काष्ठा be_invalidate_connection_params_in अणु
	काष्ठा be_cmd_req_hdr hdr;
	u32 session_handle;
	u16 cid;
	u16 unused;
#घोषणा BE_CLEANUP_TYPE_INVALIDATE	0x8001
#घोषणा BE_CLEANUP_TYPE_ISSUE_TCP_RST	0x8002
	u16 cleanup_type;
	u16 save_cfg;
पूर्ण __packed;

काष्ठा be_invalidate_connection_params_out अणु
	u32 session_handle;
	u16 cid;
	u16 unused;
पूर्ण __packed;

जोड़ be_invalidate_connection_params अणु
	काष्ठा be_invalidate_connection_params_in req;
	काष्ठा be_invalidate_connection_params_out resp;
पूर्ण __packed;

काष्ठा be_tcp_upload_params_in अणु
	काष्ठा be_cmd_req_hdr hdr;
	u16 id;
#घोषणा BE_UPLOAD_TYPE_GRACEFUL		1
/* पातive upload with reset */
#घोषणा BE_UPLOAD_TYPE_ABORT_RESET	2
/* पातive upload without reset */
#घोषणा BE_UPLOAD_TYPE_ABORT		3
/* पातive upload with reset, sequence number by driver */
#घोषणा BE_UPLOAD_TYPE_ABORT_WITH_SEQ	4
	u16 upload_type;
	u32 reset_seq;
पूर्ण __packed;

काष्ठा be_tcp_upload_params_out अणु
	u32 dw[32];
पूर्ण __packed;

जोड़ be_tcp_upload_params अणु
	काष्ठा be_tcp_upload_params_in request;
	काष्ठा be_tcp_upload_params_out response;
पूर्ण __packed;

काष्ठा be_ulp_fw_cfg अणु
#घोषणा BEISCSI_ULP_ISCSI_INI_MODE	0x10
	u32 ulp_mode;
	u32 etx_base;
	u32 etx_count;
	u32 sq_base;
	u32 sq_count;
	u32 rq_base;
	u32 rq_count;
	u32 dq_base;
	u32 dq_count;
	u32 lro_base;
	u32 lro_count;
	u32 icd_base;
	u32 icd_count;
पूर्ण;

काष्ठा be_ulp_chain_icd अणु
	u32 chain_base;
	u32 chain_count;
पूर्ण;

काष्ठा be_fw_cfg अणु
	काष्ठा be_cmd_req_hdr hdr;
	u32 be_config_number;
	u32 asic_revision;
	u32 phys_port;
#घोषणा BEISCSI_FUNC_ISCSI_INI_MODE	0x10
#घोषणा BEISCSI_FUNC_DUA_MODE	0x800
	u32 function_mode;
	काष्ठा be_ulp_fw_cfg ulp[2];
	u32 function_caps;
	u32 cqid_base;
	u32 cqid_count;
	u32 eqid_base;
	u32 eqid_count;
	काष्ठा be_ulp_chain_icd chain_icd[2];
पूर्ण __packed;

काष्ठा be_cmd_get_all_अगर_id_req अणु
	काष्ठा be_cmd_req_hdr hdr;
	u32 अगर_count;
	u32 अगर_hndl_list[1];
पूर्ण __packed;

काष्ठा be_cmd_get_port_name अणु
	जोड़ अणु
		काष्ठा be_cmd_req_hdr req_hdr;
		काष्ठा be_cmd_resp_hdr resp_hdr;
	पूर्ण h;
	जोड़ अणु
		काष्ठा अणु
			u32 reserved;
		पूर्ण req;
		काष्ठा अणु
			u32 port_names;
		पूर्ण resp;
	पूर्ण p;
पूर्ण __packed;

#घोषणा ISCSI_OPCODE_SCSI_DATA_OUT		5
#घोषणा OPCODE_COMMON_NTWK_LINK_STATUS_QUERY 5
#घोषणा OPCODE_COMMON_MODIFY_EQ_DELAY		41
#घोषणा OPCODE_COMMON_ISCSI_CLEANUP		59
#घोषणा	OPCODE_COMMON_TCP_UPLOAD		56
#घोषणा OPCODE_COMMON_ISCSI_TCP_CONNECT_AND_OFFLOAD 70
#घोषणा OPCODE_COMMON_ISCSI_ERROR_RECOVERY_INVALIDATE_COMMANDS 1
#घोषणा OPCODE_ISCSI_INI_CFG_GET_HBA_NAME	6
#घोषणा OPCODE_ISCSI_INI_CFG_SET_HBA_NAME	7
#घोषणा OPCODE_ISCSI_INI_SESSION_GET_A_SESSION  14
#घोषणा OPCODE_ISCSI_INI_SESSION_LOGOUT_TARGET	 24
#घोषणा OPCODE_ISCSI_INI_DRIVER_REOPEN_ALL_SESSIONS 36
#घोषणा OPCODE_ISCSI_INI_DRIVER_OFFLOAD_SESSION 41
#घोषणा OPCODE_ISCSI_INI_DRIVER_INVALIDATE_CONNECTION 42
#घोषणा OPCODE_ISCSI_INI_BOOT_GET_BOOT_TARGET	52
#घोषणा OPCODE_COMMON_WRITE_FLASH		96
#घोषणा OPCODE_COMMON_READ_FLASH		97

#घोषणा CMD_ISCSI_COMMAND_INVALIDATE		1

#घोषणा INI_WR_CMD			1	/* Initiator ग_लिखो command */
#घोषणा INI_TMF_CMD			2	/* Initiator TMF command */
#घोषणा INI_NOPOUT_CMD			3	/* Initiator; Send a NOP-OUT */
#घोषणा INI_RD_CMD			5	/* Initiator requesting to send
						 * a पढ़ो command
						 */
#घोषणा TGT_CTX_UPDT_CMD		7	/* Target context update */
#घोषणा TGT_DM_CMD			11	/* Indicates that the bhs
						 * prepared by driver should not
						 * be touched.
						 */

/* Returns the number of items in the field array. */
#घोषणा BE_NUMBER_OF_FIELD(_type_, _field_)	\
	(माप_field(_type_, _field_)/माप((((_type_ *)0)->_field_[0])))\

/**
 * Dअगरferent types of iSCSI completions to host driver क्रम both initiator
 * and taget mode
 * of operation.
 */
#घोषणा SOL_CMD_COMPLETE		1	/* Solicited command completed
						 * normally
						 */
#घोषणा SOL_CMD_KILLED_DATA_DIGEST_ERR  2	/* Solicited command got
						 * invalidated पूर्णांकernally due
						 * to Data Digest error
						 */
#घोषणा CXN_KILLED_PDU_SIZE_EXCEEDS_DSL 3	/* Connection got invalidated
						 * पूर्णांकernally
						 * due to a received PDU
						 * size > DSL
						 */
#घोषणा CXN_KILLED_BURST_LEN_MISMATCH   4	/* Connection got invalidated
						 * पूर्णांकernally due ti received
						 * PDU sequence size >
						 * FBL/MBL.
						 */
#घोषणा CXN_KILLED_AHS_RCVD		5	/* Connection got invalidated
						 * पूर्णांकernally due to a received
						 * PDU Hdr that has
						 * AHS */
#घोषणा CXN_KILLED_HDR_DIGEST_ERR	6	/* Connection got invalidated
						 * पूर्णांकernally due to Hdr Digest
						 * error
						 */
#घोषणा CXN_KILLED_UNKNOWN_HDR		7	/* Connection got invalidated
						 *  पूर्णांकernally
						 * due to a bad opcode in the
						 * pdu hdr
						 */
#घोषणा CXN_KILLED_STALE_ITT_TTT_RCVD	8	/* Connection got invalidated
						 * पूर्णांकernally due to a received
						 * ITT/TTT that करोes not beदीर्घ
						 * to this Connection
						 */
#घोषणा CXN_KILLED_INVALID_ITT_TTT_RCVD 9	/* Connection got invalidated
						 * पूर्णांकernally due to received
						 * ITT/TTT value > Max
						 * Supported ITTs/TTTs
						 */
#घोषणा CXN_KILLED_RST_RCVD		10	/* Connection got invalidated
						 * पूर्णांकernally due to an
						 * incoming TCP RST
						 */
#घोषणा CXN_KILLED_TIMED_OUT		11	/* Connection got invalidated
						 * पूर्णांकernally due to समयout on
						 * tcp segment 12 retransmit
						 * attempts failed
						 */
#घोषणा CXN_KILLED_RST_SENT		12	/* Connection got invalidated
						 * पूर्णांकernally due to TCP RST
						 * sent by the Tx side
						 */
#घोषणा CXN_KILLED_FIN_RCVD		13	/* Connection got invalidated
						 * पूर्णांकernally due to an
						 * incoming TCP FIN.
						 */
#घोषणा CXN_KILLED_BAD_UNSOL_PDU_RCVD	14	/* Connection got invalidated
						 * पूर्णांकernally due to bad
						 * unsolicited PDU Unsolicited
						 * PDUs are PDUs with
						 * ITT=0xffffffff
						 */
#घोषणा CXN_KILLED_BAD_WRB_INDEX_ERROR	15	/* Connection got invalidated
						 * पूर्णांकernally due to bad WRB
						 * index.
						 */
#घोषणा CXN_KILLED_OVER_RUN_RESIDUAL	16	/* Command got invalidated
						 * पूर्णांकernally due to received
						 * command has residual
						 * over run bytes.
						 */
#घोषणा CXN_KILLED_UNDER_RUN_RESIDUAL	17	/* Command got invalidated
						 * पूर्णांकernally due to received
						 * command has residual under
						 * run bytes.
						 */
#घोषणा CMD_KILLED_INVALID_STATSN_RCVD	18	/* Command got invalidated
						 * पूर्णांकernally due to a received
						 * PDU has an invalid StatusSN
						 */
#घोषणा CMD_KILLED_INVALID_R2T_RCVD	19	/* Command got invalidated
						 * पूर्णांकernally due to a received
						 * an R2T with some invalid
						 * fields in it
						 */
#घोषणा CMD_CXN_KILLED_LUN_INVALID	20	/* Command got invalidated
						 * पूर्णांकernally due to received
						 * PDU has an invalid LUN.
						 */
#घोषणा CMD_CXN_KILLED_ICD_INVALID	21	/* Command got invalidated
						 * पूर्णांकernally due to the
						 * corresponding ICD not in a
						 * valid state
						 */
#घोषणा CMD_CXN_KILLED_ITT_INVALID	22	/* Command got invalidated due
						 *  to received PDU has an
						 *  invalid ITT.
						 */
#घोषणा CMD_CXN_KILLED_SEQ_OUTOFORDER	23	/* Command got invalidated due
						 * to received sequence buffer
						 * offset is out of order.
						 */
#घोषणा CMD_CXN_KILLED_INVALID_DATASN_RCVD 24	/* Command got invalidated
						 * पूर्णांकernally due to a
						 * received PDU has an invalid
						 * DataSN
						 */
#घोषणा CXN_INVALIDATE_NOTIFY		25	/* Connection invalidation
						 * completion notअगरy.
						 */
#घोषणा CXN_INVALIDATE_INDEX_NOTIFY	26	/* Connection invalidation
						 * completion
						 * with data PDU index.
						 */
#घोषणा CMD_INVALIDATED_NOTIFY		27	/* Command invalidation
						 * completionnotअगरअगरy.
						 */
#घोषणा UNSOL_HDR_NOTIFY		28	/* Unsolicited header notअगरy.*/
#घोषणा UNSOL_DATA_NOTIFY		29	/* Unsolicited data notअगरy.*/
#घोषणा UNSOL_DATA_DIGEST_ERROR_NOTIFY	30	/* Unsolicited data digest
						 * error notअगरy.
						 */
#घोषणा DRIVERMSG_NOTIFY		31	/* TCP acknowledge based
						 * notअगरication.
						 */
#घोषणा CXN_KILLED_CMND_DATA_NOT_ON_SAME_CONN 32 /* Connection got invalidated
						  * पूर्णांकernally due to command
						  * and data are not on same
						  * connection.
						  */
#घोषणा SOL_CMD_KILLED_DIF_ERR		33	/* Solicited command got
						 *  invalidated पूर्णांकernally due
						 *  to DIF error
						 */
#घोषणा CXN_KILLED_SYN_RCVD		34	/* Connection got invalidated
						 * पूर्णांकernally due to incoming
						 * TCP SYN
						 */
#घोषणा CXN_KILLED_IMM_DATA_RCVD	35	/* Connection got invalidated
						 * पूर्णांकernally due to an
						 * incoming Unsolicited PDU
						 * that has immediate data on
						 * the cxn
						 */

व्योम be_wrb_hdr_prepare(काष्ठा be_mcc_wrb *wrb, u32 payload_len,
			bool embedded, u8 sge_cnt);

व्योम be_cmd_hdr_prepare(काष्ठा be_cmd_req_hdr *req_hdr,
			u8 subप्रणाली, u8 opcode, u32 cmd_len);
#पूर्ण_अगर /* !BEISCSI_CMDS_H */
