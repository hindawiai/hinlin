<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR Linux-OpenIB) OR BSD-2-Clause */
/* Copyright (c) 2017-2020 Pensanकरो Systems, Inc.  All rights reserved. */

#अगर_अघोषित _IONIC_IF_H_
#घोषणा _IONIC_IF_H_

#घोषणा IONIC_DEV_INFO_SIGNATURE		0x44455649      /* 'DEVI' */
#घोषणा IONIC_DEV_INFO_VERSION			1
#घोषणा IONIC_IFNAMSIZ				16

/**
 * क्रमागत ionic_cmd_opcode - Device commands
 */
क्रमागत ionic_cmd_opcode अणु
	IONIC_CMD_NOP				= 0,

	/* Device commands */
	IONIC_CMD_IDENTIFY			= 1,
	IONIC_CMD_INIT				= 2,
	IONIC_CMD_RESET				= 3,
	IONIC_CMD_GETATTR			= 4,
	IONIC_CMD_SETATTR			= 5,

	/* Port commands */
	IONIC_CMD_PORT_IDENTIFY			= 10,
	IONIC_CMD_PORT_INIT			= 11,
	IONIC_CMD_PORT_RESET			= 12,
	IONIC_CMD_PORT_GETATTR			= 13,
	IONIC_CMD_PORT_SETATTR			= 14,

	/* LIF commands */
	IONIC_CMD_LIF_IDENTIFY			= 20,
	IONIC_CMD_LIF_INIT			= 21,
	IONIC_CMD_LIF_RESET			= 22,
	IONIC_CMD_LIF_GETATTR			= 23,
	IONIC_CMD_LIF_SETATTR			= 24,
	IONIC_CMD_LIF_SETPHC			= 25,

	IONIC_CMD_RX_MODE_SET			= 30,
	IONIC_CMD_RX_FILTER_ADD			= 31,
	IONIC_CMD_RX_FILTER_DEL			= 32,

	/* Queue commands */
	IONIC_CMD_Q_IDENTIFY			= 39,
	IONIC_CMD_Q_INIT			= 40,
	IONIC_CMD_Q_CONTROL			= 41,

	/* RDMA commands */
	IONIC_CMD_RDMA_RESET_LIF		= 50,
	IONIC_CMD_RDMA_CREATE_EQ		= 51,
	IONIC_CMD_RDMA_CREATE_CQ		= 52,
	IONIC_CMD_RDMA_CREATE_ADMINQ		= 53,

	/* SR/IOV commands */
	IONIC_CMD_VF_GETATTR			= 60,
	IONIC_CMD_VF_SETATTR			= 61,

	/* QoS commands */
	IONIC_CMD_QOS_CLASS_IDENTIFY		= 240,
	IONIC_CMD_QOS_CLASS_INIT		= 241,
	IONIC_CMD_QOS_CLASS_RESET		= 242,
	IONIC_CMD_QOS_CLASS_UPDATE		= 243,
	IONIC_CMD_QOS_CLEAR_STATS		= 244,
	IONIC_CMD_QOS_RESET			= 245,

	/* Firmware commands */
	IONIC_CMD_FW_DOWNLOAD                   = 252,
	IONIC_CMD_FW_CONTROL                    = 253,
	IONIC_CMD_FW_DOWNLOAD_V1		= 254,
	IONIC_CMD_FW_CONTROL_V1		        = 255,
पूर्ण;

/**
 * क्रमागत ionic_status_code - Device command वापस codes
 */
क्रमागत ionic_status_code अणु
	IONIC_RC_SUCCESS	= 0,	/* Success */
	IONIC_RC_EVERSION	= 1,	/* Incorrect version क्रम request */
	IONIC_RC_EOPCODE	= 2,	/* Invalid cmd opcode */
	IONIC_RC_EIO		= 3,	/* I/O error */
	IONIC_RC_EPERM		= 4,	/* Permission denied */
	IONIC_RC_EQID		= 5,	/* Bad qid */
	IONIC_RC_EQTYPE		= 6,	/* Bad qtype */
	IONIC_RC_ENOENT		= 7,	/* No such element */
	IONIC_RC_EINTR		= 8,	/* operation पूर्णांकerrupted */
	IONIC_RC_EAGAIN		= 9,	/* Try again */
	IONIC_RC_ENOMEM		= 10,	/* Out of memory */
	IONIC_RC_EFAULT		= 11,	/* Bad address */
	IONIC_RC_EBUSY		= 12,	/* Device or resource busy */
	IONIC_RC_EEXIST		= 13,	/* object alपढ़ोy exists */
	IONIC_RC_EINVAL		= 14,	/* Invalid argument */
	IONIC_RC_ENOSPC		= 15,	/* No space left or alloc failure */
	IONIC_RC_दुस्फल		= 16,	/* Parameter out of range */
	IONIC_RC_BAD_ADDR	= 17,	/* Descriptor contains a bad ptr */
	IONIC_RC_DEV_CMD	= 18,	/* Device cmd attempted on AdminQ */
	IONIC_RC_ENOSUPP	= 19,	/* Operation not supported */
	IONIC_RC_ERROR		= 29,	/* Generic error */
	IONIC_RC_ERDMA		= 30,	/* Generic RDMA error */
	IONIC_RC_EVFID		= 31,	/* VF ID करोes not exist */
	IONIC_RC_EBAD_FW	= 32,	/* FW file is invalid or corrupted */
पूर्ण;

क्रमागत ionic_notअगरyq_opcode अणु
	IONIC_EVENT_LINK_CHANGE		= 1,
	IONIC_EVENT_RESET		= 2,
	IONIC_EVENT_HEARTBEAT		= 3,
	IONIC_EVENT_LOG			= 4,
	IONIC_EVENT_XCVR		= 5,
पूर्ण;

/**
 * काष्ठा ionic_admin_cmd - General admin command क्रमmat
 * @opcode:     Opcode क्रम the command
 * @lअगर_index:  LIF index
 * @cmd_data:   Opcode-specअगरic command bytes
 */
काष्ठा ionic_admin_cmd अणु
	u8     opcode;
	u8     rsvd;
	__le16 lअगर_index;
	u8     cmd_data[60];
पूर्ण;

/**
 * काष्ठा ionic_admin_comp - General admin command completion क्रमmat
 * @status:     Status of the command (क्रमागत ionic_status_code)
 * @comp_index: Index in the descriptor ring क्रम which this is the completion
 * @cmd_data:   Command-specअगरic bytes
 * @color:      Color bit (Always 0 क्रम commands issued to the
 *              Device Cmd Registers)
 */
काष्ठा ionic_admin_comp अणु
	u8     status;
	u8     rsvd;
	__le16 comp_index;
	u8     cmd_data[11];
	u8     color;
#घोषणा IONIC_COMP_COLOR_MASK  0x80
पूर्ण;

अटल अंतरभूत u8 color_match(u8 color, u8 करोne_color)
अणु
	वापस (!!(color & IONIC_COMP_COLOR_MASK)) == करोne_color;
पूर्ण

/**
 * काष्ठा ionic_nop_cmd - NOP command
 * @opcode: opcode
 */
काष्ठा ionic_nop_cmd अणु
	u8 opcode;
	u8 rsvd[63];
पूर्ण;

/**
 * काष्ठा ionic_nop_comp - NOP command completion
 * @status: Status of the command (क्रमागत ionic_status_code)
 */
काष्ठा ionic_nop_comp अणु
	u8 status;
	u8 rsvd[15];
पूर्ण;

/**
 * काष्ठा ionic_dev_init_cmd - Device init command
 * @opcode:    opcode
 * @type:      Device type
 */
काष्ठा ionic_dev_init_cmd अणु
	u8     opcode;
	u8     type;
	u8     rsvd[62];
पूर्ण;

/**
 * काष्ठा ionic_dev_init_comp - Device init command completion
 * @status: Status of the command (क्रमागत ionic_status_code)
 */
काष्ठा ionic_dev_init_comp अणु
	u8 status;
	u8 rsvd[15];
पूर्ण;

/**
 * काष्ठा ionic_dev_reset_cmd - Device reset command
 * @opcode: opcode
 */
काष्ठा ionic_dev_reset_cmd अणु
	u8 opcode;
	u8 rsvd[63];
पूर्ण;

/**
 * काष्ठा ionic_dev_reset_comp - Reset command completion
 * @status: Status of the command (क्रमागत ionic_status_code)
 */
काष्ठा ionic_dev_reset_comp अणु
	u8 status;
	u8 rsvd[15];
पूर्ण;

#घोषणा IONIC_IDENTITY_VERSION_1	1

/**
 * काष्ठा ionic_dev_identअगरy_cmd - Driver/device identअगरy command
 * @opcode:  opcode
 * @ver:     Highest version of identअगरy supported by driver
 */
काष्ठा ionic_dev_identअगरy_cmd अणु
	u8 opcode;
	u8 ver;
	u8 rsvd[62];
पूर्ण;

/**
 * काष्ठा ionic_dev_identअगरy_comp - Driver/device identअगरy command completion
 * @status: Status of the command (क्रमागत ionic_status_code)
 * @ver:    Version of identअगरy वापसed by device
 */
काष्ठा ionic_dev_identअगरy_comp अणु
	u8 status;
	u8 ver;
	u8 rsvd[14];
पूर्ण;

क्रमागत ionic_os_type अणु
	IONIC_OS_TYPE_LINUX   = 1,
	IONIC_OS_TYPE_WIN     = 2,
	IONIC_OS_TYPE_DPDK    = 3,
	IONIC_OS_TYPE_FREEBSD = 4,
	IONIC_OS_TYPE_IPXE    = 5,
	IONIC_OS_TYPE_ESXI    = 6,
पूर्ण;

/**
 * जोड़ ionic_drv_identity - driver identity inक्रमmation
 * @os_type:          OS type (see क्रमागत ionic_os_type)
 * @os_dist:          OS distribution, numeric क्रमmat
 * @os_dist_str:      OS distribution, string क्रमmat
 * @kernel_ver:       Kernel version, numeric क्रमmat
 * @kernel_ver_str:   Kernel version, string क्रमmat
 * @driver_ver_str:   Driver version, string क्रमmat
 */
जोड़ ionic_drv_identity अणु
	काष्ठा अणु
		__le32 os_type;
		__le32 os_dist;
		अक्षर   os_dist_str[128];
		__le32 kernel_ver;
		अक्षर   kernel_ver_str[32];
		अक्षर   driver_ver_str[32];
	पूर्ण;
	__le32 words[478];
पूर्ण;

/**
 * जोड़ ionic_dev_identity - device identity inक्रमmation
 * @version:          Version of device identअगरy
 * @type:             Identअगरy type (0 क्रम now)
 * @nports:           Number of ports provisioned
 * @nlअगरs:            Number of LIFs provisioned
 * @nपूर्णांकrs:           Number of पूर्णांकerrupts provisioned
 * @ndbpgs_per_lअगर:   Number of करोorbell pages per LIF
 * @पूर्णांकr_coal_mult:   Interrupt coalescing multiplication factor
 *                    Scale user-supplied पूर्णांकerrupt coalescing
 *                    value in usecs to device units using:
 *                    device units = usecs * mult / भाग
 * @पूर्णांकr_coal_भाग:    Interrupt coalescing भागision factor
 *                    Scale user-supplied पूर्णांकerrupt coalescing
 *                    value in usecs to device units using:
 *                    device units = usecs * mult / भाग
 * @eq_count:         Number of shared event queues
 * @hwstamp_mask:     Biपंचांगask क्रम subtraction of hardware tick values.
 * @hwstamp_mult:     Hardware tick to nanosecond multiplier.
 * @hwstamp_shअगरt:    Hardware tick to nanosecond भागisor (घातer of two).
 */
जोड़ ionic_dev_identity अणु
	काष्ठा अणु
		u8     version;
		u8     type;
		u8     rsvd[2];
		u8     nports;
		u8     rsvd2[3];
		__le32 nlअगरs;
		__le32 nपूर्णांकrs;
		__le32 ndbpgs_per_lअगर;
		__le32 पूर्णांकr_coal_mult;
		__le32 पूर्णांकr_coal_भाग;
		__le32 eq_count;
		__le64 hwstamp_mask;
		__le32 hwstamp_mult;
		__le32 hwstamp_shअगरt;
	पूर्ण;
	__le32 words[478];
पूर्ण;

क्रमागत ionic_lअगर_type अणु
	IONIC_LIF_TYPE_CLASSIC = 0,
	IONIC_LIF_TYPE_MACVLAN = 1,
	IONIC_LIF_TYPE_NETQUEUE = 2,
पूर्ण;

/**
 * काष्ठा ionic_lअगर_identअगरy_cmd - LIF identअगरy command
 * @opcode:  opcode
 * @type:    LIF type (क्रमागत ionic_lअगर_type)
 * @ver:     Version of identअगरy वापसed by device
 */
काष्ठा ionic_lअगर_identअगरy_cmd अणु
	u8 opcode;
	u8 type;
	u8 ver;
	u8 rsvd[61];
पूर्ण;

/**
 * काष्ठा ionic_lअगर_identअगरy_comp - LIF identअगरy command completion
 * @status:  Status of the command (क्रमागत ionic_status_code)
 * @ver:     Version of identअगरy वापसed by device
 */
काष्ठा ionic_lअगर_identअगरy_comp अणु
	u8 status;
	u8 ver;
	u8 rsvd2[14];
पूर्ण;

/**
 * क्रमागत ionic_lअगर_capability - LIF capabilities
 * @IONIC_LIF_CAP_ETH:     LIF supports Ethernet
 * @IONIC_LIF_CAP_RDMA:    LIF supports RDMA
 */
क्रमागत ionic_lअगर_capability अणु
	IONIC_LIF_CAP_ETH        = BIT(0),
	IONIC_LIF_CAP_RDMA       = BIT(1),
पूर्ण;

/**
 * क्रमागत ionic_logical_qtype - Logical Queue Types
 * @IONIC_QTYPE_ADMINQ:    Administrative Queue
 * @IONIC_QTYPE_NOTIFYQ:   Notअगरy Queue
 * @IONIC_QTYPE_RXQ:       Receive Queue
 * @IONIC_QTYPE_TXQ:       Transmit Queue
 * @IONIC_QTYPE_EQ:        Event Queue
 * @IONIC_QTYPE_MAX:       Max queue type supported
 */
क्रमागत ionic_logical_qtype अणु
	IONIC_QTYPE_ADMINQ  = 0,
	IONIC_QTYPE_NOTIFYQ = 1,
	IONIC_QTYPE_RXQ     = 2,
	IONIC_QTYPE_TXQ     = 3,
	IONIC_QTYPE_EQ      = 4,
	IONIC_QTYPE_MAX     = 16,
पूर्ण;

/**
 * क्रमागत ionic_q_feature - Common Features क्रम most queue types
 *
 * Common features use bits 0-15. Per-queue-type features use higher bits.
 *
 * @IONIC_QIDENT_F_CQ:      Queue has completion ring
 * @IONIC_QIDENT_F_SG:      Queue has scatter/gather ring
 * @IONIC_QIDENT_F_EQ:      Queue can use event queue
 * @IONIC_QIDENT_F_CMB:     Queue is in cmb bar
 * @IONIC_Q_F_2X_DESC:      Double मुख्य descriptor size
 * @IONIC_Q_F_2X_CQ_DESC:   Double cq descriptor size
 * @IONIC_Q_F_2X_SG_DESC:   Double sg descriptor size
 * @IONIC_Q_F_4X_DESC:      Quadruple मुख्य descriptor size
 * @IONIC_Q_F_4X_CQ_DESC:   Quadruple cq descriptor size
 * @IONIC_Q_F_4X_SG_DESC:   Quadruple sg descriptor size
 */
क्रमागत ionic_q_feature अणु
	IONIC_QIDENT_F_CQ		= BIT_ULL(0),
	IONIC_QIDENT_F_SG		= BIT_ULL(1),
	IONIC_QIDENT_F_EQ		= BIT_ULL(2),
	IONIC_QIDENT_F_CMB		= BIT_ULL(3),
	IONIC_Q_F_2X_DESC		= BIT_ULL(4),
	IONIC_Q_F_2X_CQ_DESC		= BIT_ULL(5),
	IONIC_Q_F_2X_SG_DESC		= BIT_ULL(6),
	IONIC_Q_F_4X_DESC		= BIT_ULL(7),
	IONIC_Q_F_4X_CQ_DESC		= BIT_ULL(8),
	IONIC_Q_F_4X_SG_DESC		= BIT_ULL(9),
पूर्ण;

/**
 * क्रमागत ionic_rxq_feature - RXQ-specअगरic Features
 *
 * Per-queue-type features use bits 16 and higher.
 *
 * @IONIC_RXQ_F_HWSTAMP:   Queue supports Hardware Timestamping
 */
क्रमागत ionic_rxq_feature अणु
	IONIC_RXQ_F_HWSTAMP		= BIT_ULL(16),
पूर्ण;

/**
 * क्रमागत ionic_txq_feature - TXQ-specअगरic Features
 *
 * Per-queue-type features use bits 16 and higher.
 *
 * @IONIC_TXQ_F_HWSTAMP:   Queue supports Hardware Timestamping
 */
क्रमागत ionic_txq_feature अणु
	IONIC_TXQ_F_HWSTAMP		= BIT(16),
पूर्ण;

/**
 * काष्ठा ionic_hwstamp_bits - Hardware बारtamp decoding bits
 * @IONIC_HWSTAMP_INVALID:          Invalid hardware बारtamp value
 * @IONIC_HWSTAMP_CQ_NEGOFFSET:     Timestamp field negative offset
 *                                  from the base cq descriptor.
 */
क्रमागत ionic_hwstamp_bits अणु
	IONIC_HWSTAMP_INVALID	    = ~0ull,
	IONIC_HWSTAMP_CQ_NEGOFFSET  = 8,
पूर्ण;

/**
 * काष्ठा ionic_lअगर_logical_qtype - Descriptor of logical to HW queue type
 * @qtype:          Hardware Queue Type
 * @qid_count:      Number of Queue IDs of the logical type
 * @qid_base:       Minimum Queue ID of the logical type
 */
काष्ठा ionic_lअगर_logical_qtype अणु
	u8     qtype;
	u8     rsvd[3];
	__le32 qid_count;
	__le32 qid_base;
पूर्ण;

/**
 * क्रमागत ionic_lअगर_state - LIF state
 * @IONIC_LIF_DISABLE:     LIF disabled
 * @IONIC_LIF_ENABLE:      LIF enabled
 * @IONIC_LIF_QUIESCE:     LIF Quiesced
 */
क्रमागत ionic_lअगर_state अणु
	IONIC_LIF_QUIESCE	= 0,
	IONIC_LIF_ENABLE	= 1,
	IONIC_LIF_DISABLE	= 2,
पूर्ण;

/**
 * जोड़ ionic_lअगर_config - LIF configuration
 * @state:          LIF state (क्रमागत ionic_lअगर_state)
 * @name:           LIF name
 * @mtu:            MTU
 * @mac:            Station MAC address
 * @vlan:           Default Vlan ID
 * @features:       Features (क्रमागत ionic_eth_hw_features)
 * @queue_count:    Queue counts per queue-type
 */
जोड़ ionic_lअगर_config अणु
	काष्ठा अणु
		u8     state;
		u8     rsvd[3];
		अक्षर   name[IONIC_IFNAMSIZ];
		__le32 mtu;
		u8     mac[6];
		__le16 vlan;
		__le64 features;
		__le32 queue_count[IONIC_QTYPE_MAX];
	पूर्ण __packed;
	__le32 words[64];
पूर्ण;

/**
 * काष्ठा ionic_lअगर_identity - LIF identity inक्रमmation (type-specअगरic)
 *
 * @capabilities:        LIF capabilities
 *
 * @eth:                    Ethernet identअगरy काष्ठाure
 *     @version:            Ethernet identअगरy काष्ठाure version
 *     @max_ucast_filters:  Number of perfect unicast addresses supported
 *     @max_mcast_filters:  Number of perfect multicast addresses supported
 *     @min_frame_size:     Minimum size of frames to be sent
 *     @max_frame_size:     Maximum size of frames to be sent
 *     @hwstamp_tx_modes:   Biपंचांगask of BIT_ULL(क्रमागत ionic_txstamp_mode)
 *     @hwstamp_rx_filters: Biपंचांगask of क्रमागत ionic_pkt_class
 *     @config:             LIF config काष्ठा with features, mtu, mac, q counts
 *
 * @rdma:                RDMA identअगरy काष्ठाure
 *     @version:         RDMA version of opcodes and queue descriptors
 *     @qp_opcodes:      Number of RDMA queue pair opcodes supported
 *     @admin_opcodes:   Number of RDMA admin opcodes supported
 *     @npts_per_lअगर:    Page table size per LIF
 *     @nmrs_per_lअगर:    Number of memory regions per LIF
 *     @nahs_per_lअगर:    Number of address handles per LIF
 *     @max_stride:      Max work request stride
 *     @cl_stride:       Cache line stride
 *     @pte_stride:      Page table entry stride
 *     @rrq_stride:      Remote RQ work request stride
 *     @rsq_stride:      Remote SQ work request stride
 *     @dcqcn_profiles:  Number of DCQCN profiles
 *     @aq_qtype:        RDMA Admin Qtype
 *     @sq_qtype:        RDMA Send Qtype
 *     @rq_qtype:        RDMA Receive Qtype
 *     @cq_qtype:        RDMA Completion Qtype
 *     @eq_qtype:        RDMA Event Qtype
 */
जोड़ ionic_lअगर_identity अणु
	काष्ठा अणु
		__le64 capabilities;

		काष्ठा अणु
			u8 version;
			u8 rsvd[3];
			__le32 max_ucast_filters;
			__le32 max_mcast_filters;
			__le16 rss_ind_tbl_sz;
			__le32 min_frame_size;
			__le32 max_frame_size;
			u8 rsvd2[2];
			__le64 hwstamp_tx_modes;
			__le64 hwstamp_rx_filters;
			u8 rsvd3[88];
			जोड़ ionic_lअगर_config config;
		पूर्ण __packed eth;

		काष्ठा अणु
			u8 version;
			u8 qp_opcodes;
			u8 admin_opcodes;
			u8 rsvd;
			__le32 npts_per_lअगर;
			__le32 nmrs_per_lअगर;
			__le32 nahs_per_lअगर;
			u8 max_stride;
			u8 cl_stride;
			u8 pte_stride;
			u8 rrq_stride;
			u8 rsq_stride;
			u8 dcqcn_profiles;
			u8 rsvd_dimensions[10];
			काष्ठा ionic_lअगर_logical_qtype aq_qtype;
			काष्ठा ionic_lअगर_logical_qtype sq_qtype;
			काष्ठा ionic_lअगर_logical_qtype rq_qtype;
			काष्ठा ionic_lअगर_logical_qtype cq_qtype;
			काष्ठा ionic_lअगर_logical_qtype eq_qtype;
		पूर्ण __packed rdma;
	पूर्ण __packed;
	__le32 words[478];
पूर्ण;

/**
 * काष्ठा ionic_lअगर_init_cmd - LIF init command
 * @opcode:       Opcode
 * @type:         LIF type (क्रमागत ionic_lअगर_type)
 * @index:        LIF index
 * @info_pa:      Destination address क्रम LIF info (काष्ठा ionic_lअगर_info)
 */
काष्ठा ionic_lअगर_init_cmd अणु
	u8     opcode;
	u8     type;
	__le16 index;
	__le32 rsvd;
	__le64 info_pa;
	u8     rsvd2[48];
पूर्ण;

/**
 * काष्ठा ionic_lअगर_init_comp - LIF init command completion
 * @status:	Status of the command (क्रमागत ionic_status_code)
 * @hw_index:	Hardware index of the initialized LIF
 */
काष्ठा ionic_lअगर_init_comp अणु
	u8 status;
	u8 rsvd;
	__le16 hw_index;
	u8 rsvd2[12];
पूर्ण;

/**
 * काष्ठा ionic_q_identअगरy_cmd - queue identअगरy command
 * @opcode:     opcode
 * @lअगर_type:   LIF type (क्रमागत ionic_lअगर_type)
 * @type:       Logical queue type (क्रमागत ionic_logical_qtype)
 * @ver:        Highest queue type version that the driver supports
 */
काष्ठा ionic_q_identअगरy_cmd अणु
	u8     opcode;
	u8     rsvd;
	__le16 lअगर_type;
	u8     type;
	u8     ver;
	u8     rsvd2[58];
पूर्ण;

/**
 * काष्ठा ionic_q_identअगरy_comp - queue identअगरy command completion
 * @status:     Status of the command (क्रमागत ionic_status_code)
 * @comp_index: Index in the descriptor ring क्रम which this is the completion
 * @ver:        Queue type version that can be used with FW
 */
काष्ठा ionic_q_identअगरy_comp अणु
	u8     status;
	u8     rsvd;
	__le16 comp_index;
	u8     ver;
	u8     rsvd2[11];
पूर्ण;

/**
 * जोड़ ionic_q_identity - queue identity inक्रमmation
 *     @version:        Queue type version that can be used with FW
 *     @supported:      Bitfield of queue versions, first bit = ver 0
 *     @features:       Queue features (क्रमागत ionic_q_feature, etc)
 *     @desc_sz:        Descriptor size
 *     @comp_sz:        Completion descriptor size
 *     @sg_desc_sz:     Scatter/Gather descriptor size
 *     @max_sg_elems:   Maximum number of Scatter/Gather elements
 *     @sg_desc_stride: Number of Scatter/Gather elements per descriptor
 */
जोड़ ionic_q_identity अणु
	काष्ठा अणु
		u8      version;
		u8      supported;
		u8      rsvd[6];
		__le64  features;
		__le16  desc_sz;
		__le16  comp_sz;
		__le16  sg_desc_sz;
		__le16  max_sg_elems;
		__le16  sg_desc_stride;
	पूर्ण;
	__le32 words[478];
पूर्ण;

/**
 * काष्ठा ionic_q_init_cmd - Queue init command
 * @opcode:       opcode
 * @type:         Logical queue type
 * @ver:          Queue type version
 * @lअगर_index:    LIF index
 * @index:        (LIF, qtype) relative admin queue index
 * @पूर्णांकr_index:   Interrupt control रेजिस्टर index, or Event queue index
 * @pid:          Process ID
 * @flags:
 *    IRQ:        Interrupt requested on completion
 *    ENA:        Enable the queue.  If ENA=0 the queue is initialized
 *                but reमुख्यs disabled, to be later enabled with the
 *                Queue Enable command.  If ENA=1, then queue is
 *                initialized and then enabled.
 *    SG:         Enable Scatter-Gather on the queue.
 *                in number of descs.  The actual ring size is
 *                (1 << ring_size).  For example, to
 *                select a ring size of 64 descriptors ग_लिखो
 *                ring_size = 6.  The minimum ring_size value is 2
 *                क्रम a ring size of 4 descriptors.  The maximum
 *                ring_size value is 16 क्रम a ring size of 64k
 *                descriptors.  Values of ring_size <2 and >16 are
 *                reserved.
 *    EQ:         Enable the Event Queue
 * @cos:          Class of service क्रम this queue
 * @ring_size:    Queue ring size, encoded as a log2(size)
 * @ring_base:    Queue ring base address
 * @cq_ring_base: Completion queue ring base address
 * @sg_ring_base: Scatter/Gather ring base address
 * @features:     Mask of queue features to enable, अगर not in the flags above.
 */
काष्ठा ionic_q_init_cmd अणु
	u8     opcode;
	u8     rsvd;
	__le16 lअगर_index;
	u8     type;
	u8     ver;
	u8     rsvd1[2];
	__le32 index;
	__le16 pid;
	__le16 पूर्णांकr_index;
	__le16 flags;
#घोषणा IONIC_QINIT_F_IRQ	0x01	/* Request पूर्णांकerrupt on completion */
#घोषणा IONIC_QINIT_F_ENA	0x02	/* Enable the queue */
#घोषणा IONIC_QINIT_F_SG	0x04	/* Enable scatter/gather on the queue */
#घोषणा IONIC_QINIT_F_EQ	0x08	/* Enable event queue */
#घोषणा IONIC_QINIT_F_CMB	0x10	/* Enable cmb-based queue */
#घोषणा IONIC_QINIT_F_DEBUG	0x80	/* Enable queue debugging */
	u8     cos;
	u8     ring_size;
	__le64 ring_base;
	__le64 cq_ring_base;
	__le64 sg_ring_base;
	u8     rsvd2[12];
	__le64 features;
पूर्ण __packed;

/**
 * काष्ठा ionic_q_init_comp - Queue init command completion
 * @status:     Status of the command (क्रमागत ionic_status_code)
 * @comp_index: Index in the descriptor ring क्रम which this is the completion
 * @hw_index:   Hardware Queue ID
 * @hw_type:    Hardware Queue type
 * @color:      Color
 */
काष्ठा ionic_q_init_comp अणु
	u8     status;
	u8     rsvd;
	__le16 comp_index;
	__le32 hw_index;
	u8     hw_type;
	u8     rsvd2[6];
	u8     color;
पूर्ण;

/* the device's पूर्णांकernal addressing uses up to 52 bits */
#घोषणा IONIC_ADDR_LEN		52
#घोषणा IONIC_ADDR_MASK		(BIT_ULL(IONIC_ADDR_LEN) - 1)

क्रमागत ionic_txq_desc_opcode अणु
	IONIC_TXQ_DESC_OPCODE_CSUM_NONE = 0,
	IONIC_TXQ_DESC_OPCODE_CSUM_PARTIAL = 1,
	IONIC_TXQ_DESC_OPCODE_CSUM_HW = 2,
	IONIC_TXQ_DESC_OPCODE_TSO = 3,
पूर्ण;

/**
 * काष्ठा ionic_txq_desc - Ethernet Tx queue descriptor क्रमmat
 * @cmd:          Tx operation, see IONIC_TXQ_DESC_OPCODE_*:
 *
 *                   IONIC_TXQ_DESC_OPCODE_CSUM_NONE:
 *                      Non-offload send.  No segmentation,
 *                      fragmentation or checksum calc/insertion is
 *                      perक्रमmed by device; packet is prepared
 *                      to send by software stack and requires
 *                      no further manipulation from device.
 *
 *                   IONIC_TXQ_DESC_OPCODE_CSUM_PARTIAL:
 *                      Offload 16-bit L4 checksum
 *                      calculation/insertion.  The device will
 *                      calculate the L4 checksum value and
 *                      insert the result in the packet's L4
 *                      header checksum field.  The L4 checksum
 *                      is calculated starting at @csum_start bytes
 *                      पूर्णांकo the packet to the end of the packet.
 *                      The checksum insertion position is given
 *                      in @csum_offset, which is the offset from
 *                      @csum_start to the checksum field in the L4
 *                      header.  This feature is only applicable to
 *                      protocols such as TCP, UDP and ICMP where a
 *                      standard (i.e. the 'IP-style' checksum)
 *                      one's complement 16-bit checksum is used,
 *                      using an IP pseuकरो-header to seed the
 *                      calculation.  Software will preload the L4
 *                      checksum field with the IP pseuकरो-header
 *                      checksum.
 *
 *                      For tunnel encapsulation, @csum_start and
 *                      @csum_offset refer to the inner L4
 *                      header.  Supported tunnels encapsulations
 *                      are: IPIP, GRE, and UDP.  If the @encap
 *                      is clear, no further processing by the
 *                      device is required; software will
 *                      calculate the outer header checksums.  If
 *                      the @encap is set, the device will
 *                      offload the outer header checksums using
 *                      LCO (local checksum offload) (see
 *                      Documentation/networking/checksum-offloads.rst
 *                      क्रम more info).
 *
 *                   IONIC_TXQ_DESC_OPCODE_CSUM_HW:
 *                      Offload 16-bit checksum computation to hardware.
 *                      If @csum_l3 is set then the packet's L3 checksum is
 *                      updated. Similarly, अगर @csum_l4 is set the the L4
 *                      checksum is updated. If @encap is set then encap header
 *                      checksums are also updated.
 *
 *                   IONIC_TXQ_DESC_OPCODE_TSO:
 *                      Device perक्रमms TCP segmentation offload
 *                      (TSO).  @hdr_len is the number of bytes
 *                      to the end of TCP header (the offset to
 *                      the TCP payload).  @mss is the desired
 *                      MSS, the TCP payload length क्रम each
 *                      segment.  The device will calculate/
 *                      insert IP (IPv4 only) and TCP checksums
 *                      क्रम each segment.  In the first data
 *                      buffer containing the header ढाँचा,
 *                      the driver will set IPv4 checksum to 0
 *                      and preload TCP checksum with the IP
 *                      pseuकरो header calculated with IP length = 0.
 *
 *                      Supported tunnel encapsulations are IPIP,
 *                      layer-3 GRE, and UDP. @hdr_len includes
 *                      both outer and inner headers.  The driver
 *                      will set IPv4 checksum to zero and
 *                      preload TCP checksum with IP pseuकरो
 *                      header on the inner header.
 *
 *                      TCP ECN offload is supported.  The device
 *                      will set CWR flag in the first segment अगर
 *                      CWR is set in the ढाँचा header, and
 *                      clear CWR in reमुख्यing segments.
 * @flags:
 *                vlan:
 *                    Insert an L2 VLAN header using @vlan_tci
 *                encap:
 *                    Calculate encap header checksum
 *                csum_l3:
 *                    Compute L3 header checksum
 *                csum_l4:
 *                    Compute L4 header checksum
 *                tso_sot:
 *                    TSO start
 *                tso_eot:
 *                    TSO end
 * @num_sg_elems: Number of scatter-gather elements in SG
 *                descriptor
 * @addr:         First data buffer's DMA address
 *                (Subsequent data buffers are on txq_sg_desc)
 * @len:          First data buffer's length, in bytes
 * @vlan_tci:     VLAN tag to insert in the packet (अगर requested
 *                by @V-bit).  Includes .1p and .1q tags
 * @hdr_len:      Length of packet headers, including
 *                encapsulating outer header, अगर applicable
 *                Valid क्रम opcodes IONIC_TXQ_DESC_OPCODE_CALC_CSUM and
 *                IONIC_TXQ_DESC_OPCODE_TSO.  Should be set to zero क्रम
 *                all other modes.  For
 *                IONIC_TXQ_DESC_OPCODE_CALC_CSUM, @hdr_len is length
 *                of headers up to inner-most L4 header.  For
 *                IONIC_TXQ_DESC_OPCODE_TSO, @hdr_len is up to
 *                inner-most L4 payload, so inclusive of
 *                inner-most L4 header.
 * @mss:          Desired MSS value क्रम TSO; only applicable क्रम
 *                IONIC_TXQ_DESC_OPCODE_TSO
 * @csum_start:   Offset from packet to first byte checked in L4 checksum
 * @csum_offset:  Offset from csum_start to L4 checksum field
 */
काष्ठा ionic_txq_desc अणु
	__le64  cmd;
#घोषणा IONIC_TXQ_DESC_OPCODE_MASK		0xf
#घोषणा IONIC_TXQ_DESC_OPCODE_SHIFT		4
#घोषणा IONIC_TXQ_DESC_FLAGS_MASK		0xf
#घोषणा IONIC_TXQ_DESC_FLAGS_SHIFT		0
#घोषणा IONIC_TXQ_DESC_NSGE_MASK		0xf
#घोषणा IONIC_TXQ_DESC_NSGE_SHIFT		8
#घोषणा IONIC_TXQ_DESC_ADDR_MASK		(BIT_ULL(IONIC_ADDR_LEN) - 1)
#घोषणा IONIC_TXQ_DESC_ADDR_SHIFT		12

/* common flags */
#घोषणा IONIC_TXQ_DESC_FLAG_VLAN		0x1
#घोषणा IONIC_TXQ_DESC_FLAG_ENCAP		0x2

/* flags क्रम csum_hw opcode */
#घोषणा IONIC_TXQ_DESC_FLAG_CSUM_L3		0x4
#घोषणा IONIC_TXQ_DESC_FLAG_CSUM_L4		0x8

/* flags क्रम tso opcode */
#घोषणा IONIC_TXQ_DESC_FLAG_TSO_SOT		0x4
#घोषणा IONIC_TXQ_DESC_FLAG_TSO_EOT		0x8

	__le16  len;
	जोड़ अणु
		__le16  vlan_tci;
		__le16  hword0;
	पूर्ण;
	जोड़ अणु
		__le16  csum_start;
		__le16  hdr_len;
		__le16  hword1;
	पूर्ण;
	जोड़ अणु
		__le16  csum_offset;
		__le16  mss;
		__le16  hword2;
	पूर्ण;
पूर्ण;

अटल अंतरभूत u64 encode_txq_desc_cmd(u8 opcode, u8 flags,
				      u8 nsge, u64 addr)
अणु
	u64 cmd;

	cmd = (opcode & IONIC_TXQ_DESC_OPCODE_MASK) << IONIC_TXQ_DESC_OPCODE_SHIFT;
	cmd |= (flags & IONIC_TXQ_DESC_FLAGS_MASK) << IONIC_TXQ_DESC_FLAGS_SHIFT;
	cmd |= (nsge & IONIC_TXQ_DESC_NSGE_MASK) << IONIC_TXQ_DESC_NSGE_SHIFT;
	cmd |= (addr & IONIC_TXQ_DESC_ADDR_MASK) << IONIC_TXQ_DESC_ADDR_SHIFT;

	वापस cmd;
पूर्ण;

अटल अंतरभूत व्योम decode_txq_desc_cmd(u64 cmd, u8 *opcode, u8 *flags,
				       u8 *nsge, u64 *addr)
अणु
	*opcode = (cmd >> IONIC_TXQ_DESC_OPCODE_SHIFT) & IONIC_TXQ_DESC_OPCODE_MASK;
	*flags = (cmd >> IONIC_TXQ_DESC_FLAGS_SHIFT) & IONIC_TXQ_DESC_FLAGS_MASK;
	*nsge = (cmd >> IONIC_TXQ_DESC_NSGE_SHIFT) & IONIC_TXQ_DESC_NSGE_MASK;
	*addr = (cmd >> IONIC_TXQ_DESC_ADDR_SHIFT) & IONIC_TXQ_DESC_ADDR_MASK;
पूर्ण;

/**
 * काष्ठा ionic_txq_sg_elem - Transmit scatter-gather (SG) descriptor element
 * @addr:      DMA address of SG element data buffer
 * @len:       Length of SG element data buffer, in bytes
 */
काष्ठा ionic_txq_sg_elem अणु
	__le64 addr;
	__le16 len;
	__le16 rsvd[3];
पूर्ण;

/**
 * काष्ठा ionic_txq_sg_desc - Transmit scatter-gather (SG) list
 * @elems:     Scatter-gather elements
 */
काष्ठा ionic_txq_sg_desc अणु
#घोषणा IONIC_TX_MAX_SG_ELEMS		8
#घोषणा IONIC_TX_SG_DESC_STRIDE		8
	काष्ठा ionic_txq_sg_elem elems[IONIC_TX_MAX_SG_ELEMS];
पूर्ण;

काष्ठा ionic_txq_sg_desc_v1 अणु
#घोषणा IONIC_TX_MAX_SG_ELEMS_V1		15
#घोषणा IONIC_TX_SG_DESC_STRIDE_V1		16
	काष्ठा ionic_txq_sg_elem elems[IONIC_TX_SG_DESC_STRIDE_V1];
पूर्ण;

/**
 * काष्ठा ionic_txq_comp - Ethernet transmit queue completion descriptor
 * @status:     Status of the command (क्रमागत ionic_status_code)
 * @comp_index: Index in the descriptor ring क्रम which this is the completion
 * @color:      Color bit
 */
काष्ठा ionic_txq_comp अणु
	u8     status;
	u8     rsvd;
	__le16 comp_index;
	u8     rsvd2[11];
	u8     color;
पूर्ण;

क्रमागत ionic_rxq_desc_opcode अणु
	IONIC_RXQ_DESC_OPCODE_SIMPLE = 0,
	IONIC_RXQ_DESC_OPCODE_SG = 1,
पूर्ण;

/**
 * काष्ठा ionic_rxq_desc - Ethernet Rx queue descriptor क्रमmat
 * @opcode:       Rx operation, see IONIC_RXQ_DESC_OPCODE_*:
 *
 *                   IONIC_RXQ_DESC_OPCODE_SIMPLE:
 *                      Receive full packet पूर्णांकo data buffer
 *                      starting at @addr.  Results of
 *                      receive, including actual bytes received,
 *                      are recorded in Rx completion descriptor.
 *
 * @len:          Data buffer's length, in bytes
 * @addr:         Data buffer's DMA address
 */
काष्ठा ionic_rxq_desc अणु
	u8     opcode;
	u8     rsvd[5];
	__le16 len;
	__le64 addr;
पूर्ण;

/**
 * काष्ठा ionic_rxq_sg_elem - Receive scatter-gather (SG) descriptor element
 * @addr:      DMA address of SG element data buffer
 * @len:       Length of SG element data buffer, in bytes
 */
काष्ठा ionic_rxq_sg_elem अणु
	__le64 addr;
	__le16 len;
	__le16 rsvd[3];
पूर्ण;

/**
 * काष्ठा ionic_rxq_sg_desc - Receive scatter-gather (SG) list
 * @elems:     Scatter-gather elements
 */
काष्ठा ionic_rxq_sg_desc अणु
#घोषणा IONIC_RX_MAX_SG_ELEMS		8
#घोषणा IONIC_RX_SG_DESC_STRIDE		8
	काष्ठा ionic_rxq_sg_elem elems[IONIC_RX_SG_DESC_STRIDE];
पूर्ण;

/**
 * काष्ठा ionic_rxq_comp - Ethernet receive queue completion descriptor
 * @status:       Status of the command (क्रमागत ionic_status_code)
 * @num_sg_elems: Number of SG elements used by this descriptor
 * @comp_index:   Index in the descriptor ring क्रम which this is the completion
 * @rss_hash:     32-bit RSS hash
 * @csum:         16-bit sum of the packet's L2 payload
 *                If the packet's L2 payload is odd length, an extra
 *                zero-value byte is included in the @csum calculation but
 *                not included in @len.
 * @vlan_tci:     VLAN tag stripped from the packet.  Valid अगर @VLAN is
 *                set.  Includes .1p and .1q tags.
 * @len:          Received packet length, in bytes.  Excludes FCS.
 * @csum_calc     L2 payload checksum is computed or not
 * @csum_flags:   See IONIC_RXQ_COMP_CSUM_F_*:
 *
 *                  IONIC_RXQ_COMP_CSUM_F_TCP_OK:
 *                    The TCP checksum calculated by the device
 *                    matched the checksum in the receive packet's
 *                    TCP header.
 *
 *                  IONIC_RXQ_COMP_CSUM_F_TCP_BAD:
 *                    The TCP checksum calculated by the device did
 *                    not match the checksum in the receive packet's
 *                    TCP header.
 *
 *                  IONIC_RXQ_COMP_CSUM_F_UDP_OK:
 *                    The UDP checksum calculated by the device
 *                    matched the checksum in the receive packet's
 *                    UDP header
 *
 *                  IONIC_RXQ_COMP_CSUM_F_UDP_BAD:
 *                    The UDP checksum calculated by the device did
 *                    not match the checksum in the receive packet's
 *                    UDP header.
 *
 *                  IONIC_RXQ_COMP_CSUM_F_IP_OK:
 *                    The IPv4 checksum calculated by the device
 *                    matched the checksum in the receive packet's
 *                    first IPv4 header.  If the receive packet
 *                    contains both a tunnel IPv4 header and a
 *                    transport IPv4 header, the device validates the
 *                    checksum क्रम the both IPv4 headers.
 *
 *                  IONIC_RXQ_COMP_CSUM_F_IP_BAD:
 *                    The IPv4 checksum calculated by the device did
 *                    not match the checksum in the receive packet's
 *                    first IPv4 header. If the receive packet
 *                    contains both a tunnel IPv4 header and a
 *                    transport IPv4 header, the device validates the
 *                    checksum क्रम both IP headers.
 *
 *                  IONIC_RXQ_COMP_CSUM_F_VLAN:
 *                    The VLAN header was stripped and placed in @vlan_tci.
 *
 *                  IONIC_RXQ_COMP_CSUM_F_CALC:
 *                    The checksum was calculated by the device.
 *
 * @pkt_type_color: Packet type and color bit; see IONIC_RXQ_COMP_PKT_TYPE_MASK
 */
काष्ठा ionic_rxq_comp अणु
	u8     status;
	u8     num_sg_elems;
	__le16 comp_index;
	__le32 rss_hash;
	__le16 csum;
	__le16 vlan_tci;
	__le16 len;
	u8     csum_flags;
#घोषणा IONIC_RXQ_COMP_CSUM_F_TCP_OK	0x01
#घोषणा IONIC_RXQ_COMP_CSUM_F_TCP_BAD	0x02
#घोषणा IONIC_RXQ_COMP_CSUM_F_UDP_OK	0x04
#घोषणा IONIC_RXQ_COMP_CSUM_F_UDP_BAD	0x08
#घोषणा IONIC_RXQ_COMP_CSUM_F_IP_OK	0x10
#घोषणा IONIC_RXQ_COMP_CSUM_F_IP_BAD	0x20
#घोषणा IONIC_RXQ_COMP_CSUM_F_VLAN	0x40
#घोषणा IONIC_RXQ_COMP_CSUM_F_CALC	0x80
	u8     pkt_type_color;
#घोषणा IONIC_RXQ_COMP_PKT_TYPE_MASK	0x7f
पूर्ण;

क्रमागत ionic_pkt_type अणु
	IONIC_PKT_TYPE_NON_IP		= 0x00,
	IONIC_PKT_TYPE_IPV4		= 0x01,
	IONIC_PKT_TYPE_IPV4_TCP		= 0x03,
	IONIC_PKT_TYPE_IPV4_UDP		= 0x05,
	IONIC_PKT_TYPE_IPV6		= 0x08,
	IONIC_PKT_TYPE_IPV6_TCP		= 0x18,
	IONIC_PKT_TYPE_IPV6_UDP		= 0x28,
	/* below types are only used अगर encap offloads are enabled on lअगर */
	IONIC_PKT_TYPE_ENCAP_NON_IP	= 0x40,
	IONIC_PKT_TYPE_ENCAP_IPV4	= 0x41,
	IONIC_PKT_TYPE_ENCAP_IPV4_TCP	= 0x43,
	IONIC_PKT_TYPE_ENCAP_IPV4_UDP	= 0x45,
	IONIC_PKT_TYPE_ENCAP_IPV6	= 0x48,
	IONIC_PKT_TYPE_ENCAP_IPV6_TCP	= 0x58,
	IONIC_PKT_TYPE_ENCAP_IPV6_UDP	= 0x68,
पूर्ण;

क्रमागत ionic_eth_hw_features अणु
	IONIC_ETH_HW_VLAN_TX_TAG	= BIT(0),
	IONIC_ETH_HW_VLAN_RX_STRIP	= BIT(1),
	IONIC_ETH_HW_VLAN_RX_FILTER	= BIT(2),
	IONIC_ETH_HW_RX_HASH		= BIT(3),
	IONIC_ETH_HW_RX_CSUM		= BIT(4),
	IONIC_ETH_HW_TX_SG		= BIT(5),
	IONIC_ETH_HW_RX_SG		= BIT(6),
	IONIC_ETH_HW_TX_CSUM		= BIT(7),
	IONIC_ETH_HW_TSO		= BIT(8),
	IONIC_ETH_HW_TSO_IPV6		= BIT(9),
	IONIC_ETH_HW_TSO_ECN		= BIT(10),
	IONIC_ETH_HW_TSO_GRE		= BIT(11),
	IONIC_ETH_HW_TSO_GRE_CSUM	= BIT(12),
	IONIC_ETH_HW_TSO_IPXIP4		= BIT(13),
	IONIC_ETH_HW_TSO_IPXIP6		= BIT(14),
	IONIC_ETH_HW_TSO_UDP		= BIT(15),
	IONIC_ETH_HW_TSO_UDP_CSUM	= BIT(16),
	IONIC_ETH_HW_RX_CSUM_GENEVE	= BIT(17),
	IONIC_ETH_HW_TX_CSUM_GENEVE	= BIT(18),
	IONIC_ETH_HW_TSO_GENEVE		= BIT(19),
	IONIC_ETH_HW_TIMESTAMP		= BIT(20),
पूर्ण;

/**
 * क्रमागत ionic_pkt_class - Packet classअगरication mask.
 *
 * Used with rx steering filter, packets indicated by the mask can be steered
 * toward a specअगरic receive queue.
 *
 * @IONIC_PKT_CLS_NTP_ALL:          All NTP packets.
 * @IONIC_PKT_CLS_PTP1_SYNC:        PTPv1 sync
 * @IONIC_PKT_CLS_PTP1_DREQ:        PTPv1 delay-request
 * @IONIC_PKT_CLS_PTP1_ALL:         PTPv1 all packets
 * @IONIC_PKT_CLS_PTP2_L4_SYNC:     PTPv2-UDP sync
 * @IONIC_PKT_CLS_PTP2_L4_DREQ:     PTPv2-UDP delay-request
 * @IONIC_PKT_CLS_PTP2_L4_ALL:      PTPv2-UDP all packets
 * @IONIC_PKT_CLS_PTP2_L2_SYNC:     PTPv2-ETH sync
 * @IONIC_PKT_CLS_PTP2_L2_DREQ:     PTPv2-ETH delay-request
 * @IONIC_PKT_CLS_PTP2_L2_ALL:      PTPv2-ETH all packets
 * @IONIC_PKT_CLS_PTP2_SYNC:        PTPv2 sync
 * @IONIC_PKT_CLS_PTP2_DREQ:        PTPv2 delay-request
 * @IONIC_PKT_CLS_PTP2_ALL:         PTPv2 all packets
 * @IONIC_PKT_CLS_PTP_SYNC:         PTP sync
 * @IONIC_PKT_CLS_PTP_DREQ:         PTP delay-request
 * @IONIC_PKT_CLS_PTP_ALL:          PTP all packets
 */
क्रमागत ionic_pkt_class अणु
	IONIC_PKT_CLS_NTP_ALL		= BIT(0),

	IONIC_PKT_CLS_PTP1_SYNC		= BIT(1),
	IONIC_PKT_CLS_PTP1_DREQ		= BIT(2),
	IONIC_PKT_CLS_PTP1_ALL		= BIT(3) |
		IONIC_PKT_CLS_PTP1_SYNC | IONIC_PKT_CLS_PTP1_DREQ,

	IONIC_PKT_CLS_PTP2_L4_SYNC	= BIT(4),
	IONIC_PKT_CLS_PTP2_L4_DREQ	= BIT(5),
	IONIC_PKT_CLS_PTP2_L4_ALL	= BIT(6) |
		IONIC_PKT_CLS_PTP2_L4_SYNC | IONIC_PKT_CLS_PTP2_L4_DREQ,

	IONIC_PKT_CLS_PTP2_L2_SYNC	= BIT(7),
	IONIC_PKT_CLS_PTP2_L2_DREQ	= BIT(8),
	IONIC_PKT_CLS_PTP2_L2_ALL	= BIT(9) |
		IONIC_PKT_CLS_PTP2_L2_SYNC | IONIC_PKT_CLS_PTP2_L2_DREQ,

	IONIC_PKT_CLS_PTP2_SYNC		=
		IONIC_PKT_CLS_PTP2_L4_SYNC | IONIC_PKT_CLS_PTP2_L2_SYNC,
	IONIC_PKT_CLS_PTP2_DREQ		=
		IONIC_PKT_CLS_PTP2_L4_DREQ | IONIC_PKT_CLS_PTP2_L2_DREQ,
	IONIC_PKT_CLS_PTP2_ALL		=
		IONIC_PKT_CLS_PTP2_L4_ALL | IONIC_PKT_CLS_PTP2_L2_ALL,

	IONIC_PKT_CLS_PTP_SYNC		=
		IONIC_PKT_CLS_PTP1_SYNC | IONIC_PKT_CLS_PTP2_SYNC,
	IONIC_PKT_CLS_PTP_DREQ		=
		IONIC_PKT_CLS_PTP1_DREQ | IONIC_PKT_CLS_PTP2_DREQ,
	IONIC_PKT_CLS_PTP_ALL		=
		IONIC_PKT_CLS_PTP1_ALL | IONIC_PKT_CLS_PTP2_ALL,
पूर्ण;

/**
 * काष्ठा ionic_q_control_cmd - Queue control command
 * @opcode:     opcode
 * @type:       Queue type
 * @lअगर_index:  LIF index
 * @index:      Queue index
 * @oper:       Operation (क्रमागत ionic_q_control_oper)
 */
काष्ठा ionic_q_control_cmd अणु
	u8     opcode;
	u8     type;
	__le16 lअगर_index;
	__le32 index;
	u8     oper;
	u8     rsvd[55];
पूर्ण;

प्रकार काष्ठा ionic_admin_comp ionic_q_control_comp;

क्रमागत q_control_oper अणु
	IONIC_Q_DISABLE		= 0,
	IONIC_Q_ENABLE		= 1,
	IONIC_Q_HANG_RESET	= 2,
पूर्ण;

/**
 * क्रमागत ionic_phy_type - Physical connection type
 * @IONIC_PHY_TYPE_NONE:    No PHY installed
 * @IONIC_PHY_TYPE_COPPER:  Copper PHY
 * @IONIC_PHY_TYPE_FIBER:   Fiber PHY
 */
क्रमागत ionic_phy_type अणु
	IONIC_PHY_TYPE_NONE	= 0,
	IONIC_PHY_TYPE_COPPER	= 1,
	IONIC_PHY_TYPE_FIBER	= 2,
पूर्ण;

/**
 * क्रमागत ionic_xcvr_state - Transceiver status
 * @IONIC_XCVR_STATE_REMOVED:        Transceiver हटाओd
 * @IONIC_XCVR_STATE_INSERTED:       Transceiver inserted
 * @IONIC_XCVR_STATE_PENDING:        Transceiver pending
 * @IONIC_XCVR_STATE_SPROM_READ:     Transceiver data पढ़ो
 * @IONIC_XCVR_STATE_SPROM_READ_ERR: Transceiver data पढ़ो error
 */
क्रमागत ionic_xcvr_state अणु
	IONIC_XCVR_STATE_REMOVED	 = 0,
	IONIC_XCVR_STATE_INSERTED	 = 1,
	IONIC_XCVR_STATE_PENDING	 = 2,
	IONIC_XCVR_STATE_SPROM_READ	 = 3,
	IONIC_XCVR_STATE_SPROM_READ_ERR	 = 4,
पूर्ण;

/**
 * क्रमागत ionic_xcvr_pid - Supported link modes
 */
क्रमागत ionic_xcvr_pid अणु
	IONIC_XCVR_PID_UNKNOWN           = 0,

	/* CU */
	IONIC_XCVR_PID_QSFP_100G_CR4     = 1,
	IONIC_XCVR_PID_QSFP_40GBASE_CR4  = 2,
	IONIC_XCVR_PID_SFP_25GBASE_CR_S  = 3,
	IONIC_XCVR_PID_SFP_25GBASE_CR_L  = 4,
	IONIC_XCVR_PID_SFP_25GBASE_CR_N  = 5,

	/* Fiber */
	IONIC_XCVR_PID_QSFP_100G_AOC    = 50,
	IONIC_XCVR_PID_QSFP_100G_ACC    = 51,
	IONIC_XCVR_PID_QSFP_100G_SR4    = 52,
	IONIC_XCVR_PID_QSFP_100G_LR4    = 53,
	IONIC_XCVR_PID_QSFP_100G_ER4    = 54,
	IONIC_XCVR_PID_QSFP_40GBASE_ER4 = 55,
	IONIC_XCVR_PID_QSFP_40GBASE_SR4 = 56,
	IONIC_XCVR_PID_QSFP_40GBASE_LR4 = 57,
	IONIC_XCVR_PID_QSFP_40GBASE_AOC = 58,
	IONIC_XCVR_PID_SFP_25GBASE_SR   = 59,
	IONIC_XCVR_PID_SFP_25GBASE_LR   = 60,
	IONIC_XCVR_PID_SFP_25GBASE_ER   = 61,
	IONIC_XCVR_PID_SFP_25GBASE_AOC  = 62,
	IONIC_XCVR_PID_SFP_10GBASE_SR   = 63,
	IONIC_XCVR_PID_SFP_10GBASE_LR   = 64,
	IONIC_XCVR_PID_SFP_10GBASE_LRM  = 65,
	IONIC_XCVR_PID_SFP_10GBASE_ER   = 66,
	IONIC_XCVR_PID_SFP_10GBASE_AOC  = 67,
	IONIC_XCVR_PID_SFP_10GBASE_CU   = 68,
	IONIC_XCVR_PID_QSFP_100G_CWDM4  = 69,
	IONIC_XCVR_PID_QSFP_100G_PSM4   = 70,
	IONIC_XCVR_PID_SFP_25GBASE_ACC  = 71,
	IONIC_XCVR_PID_SFP_10GBASE_T    = 72,
	IONIC_XCVR_PID_SFP_1000BASE_T   = 73,
पूर्ण;

/**
 * क्रमागत ionic_port_type - Port types
 * @IONIC_PORT_TYPE_NONE:           Port type not configured
 * @IONIC_PORT_TYPE_ETH:            Port carries ethernet traffic (inband)
 * @IONIC_PORT_TYPE_MGMT:           Port carries mgmt traffic (out-of-band)
 */
क्रमागत ionic_port_type अणु
	IONIC_PORT_TYPE_NONE = 0,
	IONIC_PORT_TYPE_ETH  = 1,
	IONIC_PORT_TYPE_MGMT = 2,
पूर्ण;

/**
 * क्रमागत ionic_port_admin_state - Port config state
 * @IONIC_PORT_ADMIN_STATE_NONE:    Port admin state not configured
 * @IONIC_PORT_ADMIN_STATE_DOWN:    Port admin disabled
 * @IONIC_PORT_ADMIN_STATE_UP:      Port admin enabled
 */
क्रमागत ionic_port_admin_state अणु
	IONIC_PORT_ADMIN_STATE_NONE = 0,
	IONIC_PORT_ADMIN_STATE_DOWN = 1,
	IONIC_PORT_ADMIN_STATE_UP   = 2,
पूर्ण;

/**
 * क्रमागत ionic_port_oper_status - Port operational status
 * @IONIC_PORT_OPER_STATUS_NONE:    Port disabled
 * @IONIC_PORT_OPER_STATUS_UP:      Port link status up
 * @IONIC_PORT_OPER_STATUS_DOWN:    Port link status करोwn
 */
क्रमागत ionic_port_oper_status अणु
	IONIC_PORT_OPER_STATUS_NONE  = 0,
	IONIC_PORT_OPER_STATUS_UP    = 1,
	IONIC_PORT_OPER_STATUS_DOWN  = 2,
पूर्ण;

/**
 * क्रमागत ionic_port_fec_type - Ethernet Forward error correction (FEC) modes
 * @IONIC_PORT_FEC_TYPE_NONE:       FEC Disabled
 * @IONIC_PORT_FEC_TYPE_FC:         FireCode FEC
 * @IONIC_PORT_FEC_TYPE_RS:         ReedSolomon FEC
 */
क्रमागत ionic_port_fec_type अणु
	IONIC_PORT_FEC_TYPE_NONE = 0,
	IONIC_PORT_FEC_TYPE_FC   = 1,
	IONIC_PORT_FEC_TYPE_RS   = 2,
पूर्ण;

/**
 * क्रमागत ionic_port_छोड़ो_type - Ethernet छोड़ो (flow control) modes
 * @IONIC_PORT_PAUSE_TYPE_NONE:     Disable Pause
 * @IONIC_PORT_PAUSE_TYPE_LINK:     Link level छोड़ो
 * @IONIC_PORT_PAUSE_TYPE_PFC:      Priority-Flow Control
 */
क्रमागत ionic_port_छोड़ो_type अणु
	IONIC_PORT_PAUSE_TYPE_NONE = 0,
	IONIC_PORT_PAUSE_TYPE_LINK = 1,
	IONIC_PORT_PAUSE_TYPE_PFC  = 2,
पूर्ण;

/**
 * क्रमागत ionic_port_loopback_mode - Loopback modes
 * @IONIC_PORT_LOOPBACK_MODE_NONE:  Disable loopback
 * @IONIC_PORT_LOOPBACK_MODE_MAC:   MAC loopback
 * @IONIC_PORT_LOOPBACK_MODE_PHY:   PHY/SerDes loopback
 */
क्रमागत ionic_port_loopback_mode अणु
	IONIC_PORT_LOOPBACK_MODE_NONE = 0,
	IONIC_PORT_LOOPBACK_MODE_MAC  = 1,
	IONIC_PORT_LOOPBACK_MODE_PHY  = 2,
पूर्ण;

/**
 * काष्ठा ionic_xcvr_status - Transceiver Status inक्रमmation
 * @state:    Transceiver status (क्रमागत ionic_xcvr_state)
 * @phy:      Physical connection type (क्रमागत ionic_phy_type)
 * @pid:      Transceiver link mode (क्रमागत ionic_xcvr_pid)
 * @sprom:    Transceiver sprom contents
 */
काष्ठा ionic_xcvr_status अणु
	u8     state;
	u8     phy;
	__le16 pid;
	u8     sprom[256];
पूर्ण;

/**
 * जोड़ ionic_port_config - Port configuration
 * @speed:              port speed (in Mbps)
 * @mtu:                mtu
 * @state:              port admin state (क्रमागत ionic_port_admin_state)
 * @an_enable:          स्वतःneg enable
 * @fec_type:           fec type (क्रमागत ionic_port_fec_type)
 * @छोड़ो_type:         छोड़ो type (क्रमागत ionic_port_छोड़ो_type)
 * @loopback_mode:      loopback mode (क्रमागत ionic_port_loopback_mode)
 */
जोड़ ionic_port_config अणु
	काष्ठा अणु
#घोषणा IONIC_SPEED_100G	100000	/* 100G in Mbps */
#घोषणा IONIC_SPEED_50G		50000	/* 50G in Mbps */
#घोषणा IONIC_SPEED_40G		40000	/* 40G in Mbps */
#घोषणा IONIC_SPEED_25G		25000	/* 25G in Mbps */
#घोषणा IONIC_SPEED_10G		10000	/* 10G in Mbps */
#घोषणा IONIC_SPEED_1G		1000	/* 1G in Mbps */
		__le32 speed;
		__le32 mtu;
		u8     state;
		u8     an_enable;
		u8     fec_type;
#घोषणा IONIC_PAUSE_TYPE_MASK		0x0f
#घोषणा IONIC_PAUSE_FLAGS_MASK		0xf0
#घोषणा IONIC_PAUSE_F_TX		0x10
#घोषणा IONIC_PAUSE_F_RX		0x20
		u8     छोड़ो_type;
		u8     loopback_mode;
	पूर्ण;
	__le32 words[64];
पूर्ण;

/**
 * काष्ठा ionic_port_status - Port Status inक्रमmation
 * @status:             link status (क्रमागत ionic_port_oper_status)
 * @id:                 port id
 * @speed:              link speed (in Mbps)
 * @link_करोwn_count:    number of बार link went from from up to करोwn
 * @fec_type:           fec type (क्रमागत ionic_port_fec_type)
 * @xcvr:               tranceiver status
 */
काष्ठा ionic_port_status अणु
	__le32 id;
	__le32 speed;
	u8     status;
	__le16 link_करोwn_count;
	u8     fec_type;
	u8     rsvd[48];
	काष्ठा ionic_xcvr_status  xcvr;
पूर्ण __packed;

/**
 * काष्ठा ionic_port_identअगरy_cmd - Port identअगरy command
 * @opcode:     opcode
 * @index:      port index
 * @ver:        Highest version of identअगरy supported by driver
 */
काष्ठा ionic_port_identअगरy_cmd अणु
	u8 opcode;
	u8 index;
	u8 ver;
	u8 rsvd[61];
पूर्ण;

/**
 * काष्ठा ionic_port_identअगरy_comp - Port identअगरy command completion
 * @status: Status of the command (क्रमागत ionic_status_code)
 * @ver:    Version of identअगरy वापसed by device
 */
काष्ठा ionic_port_identअगरy_comp अणु
	u8 status;
	u8 ver;
	u8 rsvd[14];
पूर्ण;

/**
 * काष्ठा ionic_port_init_cmd - Port initialization command
 * @opcode:     opcode
 * @index:      port index
 * @info_pa:    destination address क्रम port info (काष्ठा ionic_port_info)
 */
काष्ठा ionic_port_init_cmd अणु
	u8     opcode;
	u8     index;
	u8     rsvd[6];
	__le64 info_pa;
	u8     rsvd2[48];
पूर्ण;

/**
 * काष्ठा ionic_port_init_comp - Port initialization command completion
 * @status: Status of the command (क्रमागत ionic_status_code)
 */
काष्ठा ionic_port_init_comp अणु
	u8 status;
	u8 rsvd[15];
पूर्ण;

/**
 * काष्ठा ionic_port_reset_cmd - Port reset command
 * @opcode:     opcode
 * @index:      port index
 */
काष्ठा ionic_port_reset_cmd अणु
	u8 opcode;
	u8 index;
	u8 rsvd[62];
पूर्ण;

/**
 * काष्ठा ionic_port_reset_comp - Port reset command completion
 * @status: Status of the command (क्रमागत ionic_status_code)
 */
काष्ठा ionic_port_reset_comp अणु
	u8 status;
	u8 rsvd[15];
पूर्ण;

/**
 * क्रमागत ionic_stats_ctl_cmd - List of commands क्रम stats control
 * @IONIC_STATS_CTL_RESET:      Reset statistics
 */
क्रमागत ionic_stats_ctl_cmd अणु
	IONIC_STATS_CTL_RESET		= 0,
पूर्ण;

/**
 * क्रमागत ionic_txstamp_mode - List of TX Timestamping Modes
 * @IONIC_TXSTAMP_OFF:           Disable TX hardware समयtamping.
 * @IONIC_TXSTAMP_ON:            Enable local TX hardware समयtamping.
 * @IONIC_TXSTAMP_ONESTEP_SYNC:  Modअगरy TX PTP Sync packets.
 * @IONIC_TXSTAMP_ONESTEP_P2P:   Modअगरy TX PTP Sync and PDelayResp.
 */
क्रमागत ionic_txstamp_mode अणु
	IONIC_TXSTAMP_OFF		= 0,
	IONIC_TXSTAMP_ON		= 1,
	IONIC_TXSTAMP_ONESTEP_SYNC	= 2,
	IONIC_TXSTAMP_ONESTEP_P2P	= 3,
पूर्ण;

/**
 * क्रमागत ionic_port_attr - List of device attributes
 * @IONIC_PORT_ATTR_STATE:      Port state attribute
 * @IONIC_PORT_ATTR_SPEED:      Port speed attribute
 * @IONIC_PORT_ATTR_MTU:        Port MTU attribute
 * @IONIC_PORT_ATTR_AUTONEG:    Port स्वतःnegotiation attribute
 * @IONIC_PORT_ATTR_FEC:        Port FEC attribute
 * @IONIC_PORT_ATTR_PAUSE:      Port छोड़ो attribute
 * @IONIC_PORT_ATTR_LOOPBACK:   Port loopback attribute
 * @IONIC_PORT_ATTR_STATS_CTRL: Port statistics control attribute
 */
क्रमागत ionic_port_attr अणु
	IONIC_PORT_ATTR_STATE		= 0,
	IONIC_PORT_ATTR_SPEED		= 1,
	IONIC_PORT_ATTR_MTU		= 2,
	IONIC_PORT_ATTR_AUTONEG		= 3,
	IONIC_PORT_ATTR_FEC		= 4,
	IONIC_PORT_ATTR_PAUSE		= 5,
	IONIC_PORT_ATTR_LOOPBACK	= 6,
	IONIC_PORT_ATTR_STATS_CTRL	= 7,
पूर्ण;

/**
 * काष्ठा ionic_port_setattr_cmd - Set port attributes on the NIC
 * @opcode:         Opcode
 * @index:          Port index
 * @attr:           Attribute type (क्रमागत ionic_port_attr)
 * @state:          Port state
 * @speed:          Port speed
 * @mtu:            Port MTU
 * @an_enable:      Port स्वतःnegotiation setting
 * @fec_type:       Port FEC type setting
 * @छोड़ो_type:     Port छोड़ो type setting
 * @loopback_mode:  Port loopback mode
 * @stats_ctl:      Port stats setting
 */
काष्ठा ionic_port_setattr_cmd अणु
	u8     opcode;
	u8     index;
	u8     attr;
	u8     rsvd;
	जोड़ अणु
		u8      state;
		__le32  speed;
		__le32  mtu;
		u8      an_enable;
		u8      fec_type;
		u8      छोड़ो_type;
		u8      loopback_mode;
		u8      stats_ctl;
		u8      rsvd2[60];
	पूर्ण;
पूर्ण;

/**
 * काष्ठा ionic_port_setattr_comp - Port set attr command completion
 * @status:     Status of the command (क्रमागत ionic_status_code)
 * @color:      Color bit
 */
काष्ठा ionic_port_setattr_comp अणु
	u8     status;
	u8     rsvd[14];
	u8     color;
पूर्ण;

/**
 * काष्ठा ionic_port_getattr_cmd - Get port attributes from the NIC
 * @opcode:     Opcode
 * @index:      port index
 * @attr:       Attribute type (क्रमागत ionic_port_attr)
 */
काष्ठा ionic_port_getattr_cmd अणु
	u8     opcode;
	u8     index;
	u8     attr;
	u8     rsvd[61];
पूर्ण;

/**
 * काष्ठा ionic_port_getattr_comp - Port get attr command completion
 * @status:         Status of the command (क्रमागत ionic_status_code)
 * @state:          Port state
 * @speed:          Port speed
 * @mtu:            Port MTU
 * @an_enable:      Port स्वतःnegotiation setting
 * @fec_type:       Port FEC type setting
 * @छोड़ो_type:     Port छोड़ो type setting
 * @loopback_mode:  Port loopback mode
 * @color:          Color bit
 */
काष्ठा ionic_port_getattr_comp अणु
	u8     status;
	u8     rsvd[3];
	जोड़ अणु
		u8      state;
		__le32  speed;
		__le32  mtu;
		u8      an_enable;
		u8      fec_type;
		u8      छोड़ो_type;
		u8      loopback_mode;
		u8      rsvd2[11];
	पूर्ण __packed;
	u8     color;
पूर्ण;

/**
 * काष्ठा ionic_lअगर_status - LIF status रेजिस्टर
 * @eid:             most recent NotअगरyQ event id
 * @port_num:        port the LIF is connected to
 * @link_status:     port status (क्रमागत ionic_port_oper_status)
 * @link_speed:      speed of link in Mbps
 * @link_करोwn_count: number of बार link went from up to करोwn
 */
काष्ठा ionic_lअगर_status अणु
	__le64 eid;
	u8     port_num;
	u8     rsvd;
	__le16 link_status;
	__le32 link_speed;		/* units of 1Mbps: eg 10000 = 10Gbps */
	__le16 link_करोwn_count;
	u8      rsvd2[46];
पूर्ण;

/**
 * काष्ठा ionic_lअगर_reset_cmd - LIF reset command
 * @opcode:    opcode
 * @index:     LIF index
 */
काष्ठा ionic_lअगर_reset_cmd अणु
	u8     opcode;
	u8     rsvd;
	__le16 index;
	__le32 rsvd2[15];
पूर्ण;

प्रकार काष्ठा ionic_admin_comp ionic_lअगर_reset_comp;

क्रमागत ionic_dev_state अणु
	IONIC_DEV_DISABLE	= 0,
	IONIC_DEV_ENABLE	= 1,
	IONIC_DEV_HANG_RESET	= 2,
पूर्ण;

/**
 * क्रमागत ionic_dev_attr - List of device attributes
 * @IONIC_DEV_ATTR_STATE:     Device state attribute
 * @IONIC_DEV_ATTR_NAME:      Device name attribute
 * @IONIC_DEV_ATTR_FEATURES:  Device feature attributes
 */
क्रमागत ionic_dev_attr अणु
	IONIC_DEV_ATTR_STATE    = 0,
	IONIC_DEV_ATTR_NAME     = 1,
	IONIC_DEV_ATTR_FEATURES = 2,
पूर्ण;

/**
 * काष्ठा ionic_dev_setattr_cmd - Set Device attributes on the NIC
 * @opcode:     Opcode
 * @attr:       Attribute type (क्रमागत ionic_dev_attr)
 * @state:      Device state (क्रमागत ionic_dev_state)
 * @name:       The bus info, e.g. PCI slot-device-function, 0 terminated
 * @features:   Device features
 */
काष्ठा ionic_dev_setattr_cmd अणु
	u8     opcode;
	u8     attr;
	__le16 rsvd;
	जोड़ अणु
		u8      state;
		अक्षर    name[IONIC_IFNAMSIZ];
		__le64  features;
		u8      rsvd2[60];
	पूर्ण __packed;
पूर्ण;

/**
 * काष्ठा ionic_dev_setattr_comp - Device set attr command completion
 * @status:     Status of the command (क्रमागत ionic_status_code)
 * @features:   Device features
 * @color:      Color bit
 */
काष्ठा ionic_dev_setattr_comp अणु
	u8     status;
	u8     rsvd[3];
	जोड़ अणु
		__le64  features;
		u8      rsvd2[11];
	पूर्ण __packed;
	u8     color;
पूर्ण;

/**
 * काष्ठा ionic_dev_getattr_cmd - Get Device attributes from the NIC
 * @opcode:     opcode
 * @attr:       Attribute type (क्रमागत ionic_dev_attr)
 */
काष्ठा ionic_dev_getattr_cmd अणु
	u8     opcode;
	u8     attr;
	u8     rsvd[62];
पूर्ण;

/**
 * काष्ठा ionic_dev_setattr_comp - Device set attr command completion
 * @status:     Status of the command (क्रमागत ionic_status_code)
 * @features:   Device features
 * @color:      Color bit
 */
काष्ठा ionic_dev_getattr_comp अणु
	u8     status;
	u8     rsvd[3];
	जोड़ अणु
		__le64  features;
		u8      rsvd2[11];
	पूर्ण __packed;
	u8     color;
पूर्ण;

/**
 * RSS parameters
 */
#घोषणा IONIC_RSS_HASH_KEY_SIZE		40

क्रमागत ionic_rss_hash_types अणु
	IONIC_RSS_TYPE_IPV4	= BIT(0),
	IONIC_RSS_TYPE_IPV4_TCP	= BIT(1),
	IONIC_RSS_TYPE_IPV4_UDP	= BIT(2),
	IONIC_RSS_TYPE_IPV6	= BIT(3),
	IONIC_RSS_TYPE_IPV6_TCP	= BIT(4),
	IONIC_RSS_TYPE_IPV6_UDP	= BIT(5),
पूर्ण;

/**
 * क्रमागत ionic_lअगर_attr - List of LIF attributes
 * @IONIC_LIF_ATTR_STATE:       LIF state attribute
 * @IONIC_LIF_ATTR_NAME:        LIF name attribute
 * @IONIC_LIF_ATTR_MTU:         LIF MTU attribute
 * @IONIC_LIF_ATTR_MAC:         LIF MAC attribute
 * @IONIC_LIF_ATTR_FEATURES:    LIF features attribute
 * @IONIC_LIF_ATTR_RSS:         LIF RSS attribute
 * @IONIC_LIF_ATTR_STATS_CTRL:  LIF statistics control attribute
 * @IONIC_LIF_ATTR_TXSTAMP:     LIF TX बारtamping mode
 */
क्रमागत ionic_lअगर_attr अणु
	IONIC_LIF_ATTR_STATE        = 0,
	IONIC_LIF_ATTR_NAME         = 1,
	IONIC_LIF_ATTR_MTU          = 2,
	IONIC_LIF_ATTR_MAC          = 3,
	IONIC_LIF_ATTR_FEATURES     = 4,
	IONIC_LIF_ATTR_RSS          = 5,
	IONIC_LIF_ATTR_STATS_CTRL   = 6,
	IONIC_LIF_ATTR_TXSTAMP      = 7,
पूर्ण;

/**
 * काष्ठा ionic_lअगर_setattr_cmd - Set LIF attributes on the NIC
 * @opcode:     Opcode
 * @attr:       Attribute type (क्रमागत ionic_lअगर_attr)
 * @index:      LIF index
 * @state:      LIF state (क्रमागत ionic_lअगर_state)
 * @name:       The netdev name string, 0 terminated
 * @mtu:        Mtu
 * @mac:        Station mac
 * @features:   Features (क्रमागत ionic_eth_hw_features)
 * @rss:        RSS properties
 *              @types:     The hash types to enable (see rss_hash_types)
 *              @key:       The hash secret key
 *              @addr:      Address क्रम the indirection table shared memory
 * @stats_ctl:  stats control commands (क्रमागत ionic_stats_ctl_cmd)
 * @txstamp:    TX Timestamping Mode (क्रमागत ionic_txstamp_mode)
 */
काष्ठा ionic_lअगर_setattr_cmd अणु
	u8     opcode;
	u8     attr;
	__le16 index;
	जोड़ अणु
		u8      state;
		अक्षर    name[IONIC_IFNAMSIZ];
		__le32  mtu;
		u8      mac[6];
		__le64  features;
		काष्ठा अणु
			__le16 types;
			u8     key[IONIC_RSS_HASH_KEY_SIZE];
			u8     rsvd[6];
			__le64 addr;
		पूर्ण rss;
		u8      stats_ctl;
		__le16 txstamp_mode;
		u8      rsvd[60];
	पूर्ण __packed;
पूर्ण;

/**
 * काष्ठा ionic_lअगर_setattr_comp - LIF set attr command completion
 * @status:     Status of the command (क्रमागत ionic_status_code)
 * @comp_index: Index in the descriptor ring क्रम which this is the completion
 * @features:   features (क्रमागत ionic_eth_hw_features)
 * @color:      Color bit
 */
काष्ठा ionic_lअगर_setattr_comp अणु
	u8     status;
	u8     rsvd;
	__le16 comp_index;
	जोड़ अणु
		__le64  features;
		u8      rsvd2[11];
	पूर्ण __packed;
	u8     color;
पूर्ण;

/**
 * काष्ठा ionic_lअगर_getattr_cmd - Get LIF attributes from the NIC
 * @opcode:     Opcode
 * @attr:       Attribute type (क्रमागत ionic_lअगर_attr)
 * @index:      LIF index
 */
काष्ठा ionic_lअगर_getattr_cmd अणु
	u8     opcode;
	u8     attr;
	__le16 index;
	u8     rsvd[60];
पूर्ण;

/**
 * काष्ठा ionic_lअगर_getattr_comp - LIF get attr command completion
 * @status:     Status of the command (क्रमागत ionic_status_code)
 * @comp_index: Index in the descriptor ring क्रम which this is the completion
 * @state:      LIF state (क्रमागत ionic_lअगर_state)
 * @name:       The netdev name string, 0 terminated
 * @mtu:        Mtu
 * @mac:        Station mac
 * @features:   Features (क्रमागत ionic_eth_hw_features)
 * @txstamp:    TX Timestamping Mode (क्रमागत ionic_txstamp_mode)
 * @color:      Color bit
 */
काष्ठा ionic_lअगर_getattr_comp अणु
	u8     status;
	u8     rsvd;
	__le16 comp_index;
	जोड़ अणु
		u8      state;
		__le32  mtu;
		u8      mac[6];
		__le64  features;
		__le16  txstamp_mode;
		u8      rsvd2[11];
	पूर्ण __packed;
	u8     color;
पूर्ण;

/**
 * काष्ठा ionic_lअगर_setphc_cmd - Set LIF PTP Hardware Clock
 * @opcode:     Opcode
 * @lअगर_index:  LIF index
 * @tick:       Hardware stamp tick of an instant in समय.
 * @nsec:       Nanosecond stamp of the same instant.
 * @frac:       Fractional nanoseconds at the same instant.
 * @mult:       Cycle to nanosecond multiplier.
 * @shअगरt:      Cycle to nanosecond भागisor (घातer of two).
 */
काष्ठा ionic_lअगर_setphc_cmd अणु
	u8	opcode;
	u8	rsvd1;
	__le16  lअगर_index;
	u8      rsvd2[4];
	__le64	tick;
	__le64	nsec;
	__le64	frac;
	__le32	mult;
	__le32	shअगरt;
	u8     rsvd3[24];
पूर्ण;

क्रमागत ionic_rx_mode अणु
	IONIC_RX_MODE_F_UNICAST		= BIT(0),
	IONIC_RX_MODE_F_MULTICAST	= BIT(1),
	IONIC_RX_MODE_F_BROADCAST	= BIT(2),
	IONIC_RX_MODE_F_PROMISC		= BIT(3),
	IONIC_RX_MODE_F_ALLMULTI	= BIT(4),
	IONIC_RX_MODE_F_RDMA_SNIFFER	= BIT(5),
पूर्ण;

/**
 * काष्ठा ionic_rx_mode_set_cmd - Set LIF's Rx mode command
 * @opcode:     opcode
 * @lअगर_index:  LIF index
 * @rx_mode:    Rx mode flags:
 *                  IONIC_RX_MODE_F_UNICAST: Accept known unicast packets
 *                  IONIC_RX_MODE_F_MULTICAST: Accept known multicast packets
 *                  IONIC_RX_MODE_F_BROADCAST: Accept broadcast packets
 *                  IONIC_RX_MODE_F_PROMISC: Accept any packets
 *                  IONIC_RX_MODE_F_ALLMULTI: Accept any multicast packets
 *                  IONIC_RX_MODE_F_RDMA_SNIFFER: Snअगरf RDMA packets
 */
काष्ठा ionic_rx_mode_set_cmd अणु
	u8     opcode;
	u8     rsvd;
	__le16 lअगर_index;
	__le16 rx_mode;
	__le16 rsvd2[29];
पूर्ण;

प्रकार काष्ठा ionic_admin_comp ionic_rx_mode_set_comp;

क्रमागत ionic_rx_filter_match_type अणु
	IONIC_RX_FILTER_MATCH_VLAN	= 0x0,
	IONIC_RX_FILTER_MATCH_MAC	= 0x1,
	IONIC_RX_FILTER_MATCH_MAC_VLAN	= 0x2,
	IONIC_RX_FILTER_STEER_PKTCLASS	= 0x10,
पूर्ण;

/**
 * काष्ठा ionic_rx_filter_add_cmd - Add LIF Rx filter command
 * @opcode:     opcode
 * @qtype:      Queue type
 * @lअगर_index:  LIF index
 * @qid:        Queue ID
 * @match:      Rx filter match type (see IONIC_RX_FILTER_MATCH_xxx)
 * @vlan:       VLAN filter
 *              @vlan:  VLAN ID
 * @mac:        MAC filter
 *              @addr:  MAC address (network-byte order)
 * @mac_vlan:   MACVLAN filter
 *              @vlan:  VLAN ID
 *              @addr:  MAC address (network-byte order)
 * @pkt_class:  Packet classअगरication filter
 */
काष्ठा ionic_rx_filter_add_cmd अणु
	u8     opcode;
	u8     qtype;
	__le16 lअगर_index;
	__le32 qid;
	__le16 match;
	जोड़ अणु
		काष्ठा अणु
			__le16 vlan;
		पूर्ण vlan;
		काष्ठा अणु
			u8     addr[6];
		पूर्ण mac;
		काष्ठा अणु
			__le16 vlan;
			u8     addr[6];
		पूर्ण mac_vlan;
		__le64 pkt_class;
		u8 rsvd[54];
	पूर्ण __packed;
पूर्ण;

/**
 * काष्ठा ionic_rx_filter_add_comp - Add LIF Rx filter command completion
 * @status:     Status of the command (क्रमागत ionic_status_code)
 * @comp_index: Index in the descriptor ring क्रम which this is the completion
 * @filter_id:  Filter ID
 * @color:      Color bit
 */
काष्ठा ionic_rx_filter_add_comp अणु
	u8     status;
	u8     rsvd;
	__le16 comp_index;
	__le32 filter_id;
	u8     rsvd2[7];
	u8     color;
पूर्ण;

/**
 * काष्ठा ionic_rx_filter_del_cmd - Delete LIF Rx filter command
 * @opcode:     opcode
 * @lअगर_index:  LIF index
 * @filter_id:  Filter ID
 */
काष्ठा ionic_rx_filter_del_cmd अणु
	u8     opcode;
	u8     rsvd;
	__le16 lअगर_index;
	__le32 filter_id;
	u8     rsvd2[56];
पूर्ण;

प्रकार काष्ठा ionic_admin_comp ionic_rx_filter_del_comp;

क्रमागत ionic_vf_attr अणु
	IONIC_VF_ATTR_SPOOFCHK	= 1,
	IONIC_VF_ATTR_TRUST	= 2,
	IONIC_VF_ATTR_MAC	= 3,
	IONIC_VF_ATTR_LINKSTATE	= 4,
	IONIC_VF_ATTR_VLAN	= 5,
	IONIC_VF_ATTR_RATE	= 6,
	IONIC_VF_ATTR_STATSADDR	= 7,
पूर्ण;

/**
 * क्रमागत ionic_vf_link_status - Virtual Function link status
 * @IONIC_VF_LINK_STATUS_AUTO:   Use link state of the uplink
 * @IONIC_VF_LINK_STATUS_UP:     Link always up
 * @IONIC_VF_LINK_STATUS_DOWN:   Link always करोwn
 */
क्रमागत ionic_vf_link_status अणु
	IONIC_VF_LINK_STATUS_AUTO = 0,
	IONIC_VF_LINK_STATUS_UP   = 1,
	IONIC_VF_LINK_STATUS_DOWN = 2,
पूर्ण;

/**
 * काष्ठा ionic_vf_setattr_cmd - Set VF attributes on the NIC
 * @opcode:     Opcode
 * @attr:       Attribute type (क्रमागत ionic_vf_attr)
 * @vf_index:   VF index
 *	@macaddr:	mac address
 *	@vlanid:	vlan ID
 *	@maxrate:	max Tx rate in Mbps
 *	@spoofchk:	enable address spoof checking
 *	@trust:		enable VF trust
 *	@linkstate:	set link up or करोwn
 *	@stats_pa:	set DMA address क्रम VF stats
 */
काष्ठा ionic_vf_setattr_cmd अणु
	u8     opcode;
	u8     attr;
	__le16 vf_index;
	जोड़ अणु
		u8     macaddr[6];
		__le16 vlanid;
		__le32 maxrate;
		u8     spoofchk;
		u8     trust;
		u8     linkstate;
		__le64 stats_pa;
		u8     pad[60];
	पूर्ण __packed;
पूर्ण;

काष्ठा ionic_vf_setattr_comp अणु
	u8     status;
	u8     attr;
	__le16 vf_index;
	__le16 comp_index;
	u8     rsvd[9];
	u8     color;
पूर्ण;

/**
 * काष्ठा ionic_vf_getattr_cmd - Get VF attributes from the NIC
 * @opcode:     Opcode
 * @attr:       Attribute type (क्रमागत ionic_vf_attr)
 * @vf_index:   VF index
 */
काष्ठा ionic_vf_getattr_cmd अणु
	u8     opcode;
	u8     attr;
	__le16 vf_index;
	u8     rsvd[60];
पूर्ण;

काष्ठा ionic_vf_getattr_comp अणु
	u8     status;
	u8     attr;
	__le16 vf_index;
	जोड़ अणु
		u8     macaddr[6];
		__le16 vlanid;
		__le32 maxrate;
		u8     spoofchk;
		u8     trust;
		u8     linkstate;
		__le64 stats_pa;
		u8     pad[11];
	पूर्ण __packed;
	u8     color;
पूर्ण;

/**
 * काष्ठा ionic_qos_identअगरy_cmd - QoS identअगरy command
 * @opcode:  opcode
 * @ver:     Highest version of identअगरy supported by driver
 *
 */
काष्ठा ionic_qos_identअगरy_cmd अणु
	u8 opcode;
	u8 ver;
	u8 rsvd[62];
पूर्ण;

/**
 * काष्ठा ionic_qos_identअगरy_comp - QoS identअगरy command completion
 * @status: Status of the command (क्रमागत ionic_status_code)
 * @ver:    Version of identअगरy वापसed by device
 */
काष्ठा ionic_qos_identअगरy_comp अणु
	u8 status;
	u8 ver;
	u8 rsvd[14];
पूर्ण;

#घोषणा IONIC_QOS_TC_MAX		8
#घोषणा IONIC_QOS_ALL_TC		0xFF
/* Capri max supported, should be नामd. */
#घोषणा IONIC_QOS_CLASS_MAX		7
#घोषणा IONIC_QOS_PCP_MAX		8
#घोषणा IONIC_QOS_CLASS_NAME_SZ	32
#घोषणा IONIC_QOS_DSCP_MAX		64
#घोषणा IONIC_QOS_ALL_PCP		0xFF
#घोषणा IONIC_DSCP_BLOCK_SIZE		8

/**
 * क्रमागत ionic_qos_class
 */
क्रमागत ionic_qos_class अणु
	IONIC_QOS_CLASS_DEFAULT		= 0,
	IONIC_QOS_CLASS_USER_DEFINED_1	= 1,
	IONIC_QOS_CLASS_USER_DEFINED_2	= 2,
	IONIC_QOS_CLASS_USER_DEFINED_3	= 3,
	IONIC_QOS_CLASS_USER_DEFINED_4	= 4,
	IONIC_QOS_CLASS_USER_DEFINED_5	= 5,
	IONIC_QOS_CLASS_USER_DEFINED_6	= 6,
पूर्ण;

/**
 * क्रमागत ionic_qos_class_type - Traffic classअगरication criteria
 * @IONIC_QOS_CLASS_TYPE_NONE:    No QoS
 * @IONIC_QOS_CLASS_TYPE_PCP:     Dot1Q PCP
 * @IONIC_QOS_CLASS_TYPE_DSCP:    IP DSCP
 */
क्रमागत ionic_qos_class_type अणु
	IONIC_QOS_CLASS_TYPE_NONE	= 0,
	IONIC_QOS_CLASS_TYPE_PCP	= 1,
	IONIC_QOS_CLASS_TYPE_DSCP	= 2,
पूर्ण;

/**
 * क्रमागत ionic_qos_sched_type - QoS class scheduling type
 * @IONIC_QOS_SCHED_TYPE_STRICT:  Strict priority
 * @IONIC_QOS_SCHED_TYPE_DWRR:    Deficit weighted round-robin
 */
क्रमागत ionic_qos_sched_type अणु
	IONIC_QOS_SCHED_TYPE_STRICT	= 0,
	IONIC_QOS_SCHED_TYPE_DWRR	= 1,
पूर्ण;

/**
 * जोड़ ionic_qos_config - QoS configuration काष्ठाure
 * @flags:		Configuration flags
 *	IONIC_QOS_CONFIG_F_ENABLE		enable
 *	IONIC_QOS_CONFIG_F_NO_DROP		drop/nodrop
 *	IONIC_QOS_CONFIG_F_RW_DOT1Q_PCP		enable करोt1q pcp reग_लिखो
 *	IONIC_QOS_CONFIG_F_RW_IP_DSCP		enable ip dscp reग_लिखो
 *	IONIC_QOS_CONFIG_F_NON_DISRUPTIVE	Non-disruptive TC update
 * @sched_type:		QoS class scheduling type (क्रमागत ionic_qos_sched_type)
 * @class_type:		QoS class type (क्रमागत ionic_qos_class_type)
 * @छोड़ो_type:		QoS छोड़ो type (क्रमागत ionic_qos_छोड़ो_type)
 * @name:		QoS class name
 * @mtu:		MTU of the class
 * @pfc_cos:		Priority-Flow Control class of service
 * @dwrr_weight:	QoS class scheduling weight
 * @strict_rlmt:	Rate limit क्रम strict priority scheduling
 * @rw_करोt1q_pcp:	Reग_लिखो करोt1q pcp to value (valid अगरf F_RW_DOT1Q_PCP)
 * @rw_ip_dscp:		Reग_लिखो ip dscp to value (valid अगरf F_RW_IP_DSCP)
 * @करोt1q_pcp:		Dot1q pcp value
 * @ndscp:		Number of valid dscp values in the ip_dscp field
 * @ip_dscp:		IP dscp values
 */
जोड़ ionic_qos_config अणु
	काष्ठा अणु
#घोषणा IONIC_QOS_CONFIG_F_ENABLE		BIT(0)
#घोषणा IONIC_QOS_CONFIG_F_NO_DROP		BIT(1)
/* Used to reग_लिखो PCP or DSCP value. */
#घोषणा IONIC_QOS_CONFIG_F_RW_DOT1Q_PCP		BIT(2)
#घोषणा IONIC_QOS_CONFIG_F_RW_IP_DSCP		BIT(3)
/* Non-disruptive TC update */
#घोषणा IONIC_QOS_CONFIG_F_NON_DISRUPTIVE	BIT(4)
		u8      flags;
		u8      sched_type;
		u8      class_type;
		u8      छोड़ो_type;
		अक्षर    name[IONIC_QOS_CLASS_NAME_SZ];
		__le32  mtu;
		/* flow control */
		u8      pfc_cos;
		/* scheduler */
		जोड़ अणु
			u8      dwrr_weight;
			__le64  strict_rlmt;
		पूर्ण;
		/* marking */
		/* Used to reग_लिखो PCP or DSCP value. */
		जोड़ अणु
			u8      rw_करोt1q_pcp;
			u8      rw_ip_dscp;
		पूर्ण;
		/* classअगरication */
		जोड़ अणु
			u8      करोt1q_pcp;
			काष्ठा अणु
				u8      ndscp;
				u8      ip_dscp[IONIC_QOS_DSCP_MAX];
			पूर्ण;
		पूर्ण;
	पूर्ण;
	__le32  words[64];
पूर्ण;

/**
 * जोड़ ionic_qos_identity - QoS identity काष्ठाure
 * @version:	Version of the identअगरy काष्ठाure
 * @type:	QoS प्रणाली type
 * @nclasses:	Number of usable QoS classes
 * @config:	Current configuration of classes
 */
जोड़ ionic_qos_identity अणु
	काष्ठा अणु
		u8     version;
		u8     type;
		u8     rsvd[62];
		जोड़ ionic_qos_config config[IONIC_QOS_CLASS_MAX];
	पूर्ण;
	__le32 words[478];
पूर्ण;

/**
 * काष्ठा ionic_qos_init_cmd - QoS config init command
 * @opcode:	Opcode
 * @group:	QoS class id
 * @info_pa:	destination address क्रम qos info
 */
काष्ठा ionic_qos_init_cmd अणु
	u8     opcode;
	u8     group;
	u8     rsvd[6];
	__le64 info_pa;
	u8     rsvd1[48];
पूर्ण;

प्रकार काष्ठा ionic_admin_comp ionic_qos_init_comp;

/**
 * काष्ठा ionic_qos_reset_cmd - QoS config reset command
 * @opcode:	Opcode
 * @group:	QoS class id
 */
काष्ठा ionic_qos_reset_cmd अणु
	u8    opcode;
	u8    group;
	u8    rsvd[62];
पूर्ण;

/**
 * काष्ठा ionic_qos_clear_port_stats_cmd - Qos config reset command
 * @opcode:	Opcode
 */
काष्ठा ionic_qos_clear_stats_cmd अणु
	u8    opcode;
	u8    group_biपंचांगap;
	u8    rsvd[62];
पूर्ण;

प्रकार काष्ठा ionic_admin_comp ionic_qos_reset_comp;

/**
 * काष्ठा ionic_fw_करोwnload_cmd - Firmware करोwnload command
 * @opcode:	opcode
 * @addr:	dma address of the firmware buffer
 * @offset:	offset of the firmware buffer within the full image
 * @length:	number of valid bytes in the firmware buffer
 */
काष्ठा ionic_fw_करोwnload_cmd अणु
	u8     opcode;
	u8     rsvd[3];
	__le32 offset;
	__le64 addr;
	__le32 length;
पूर्ण;

प्रकार काष्ठा ionic_admin_comp ionic_fw_करोwnload_comp;

/**
 * क्रमागत ionic_fw_control_oper - FW control operations
 * @IONIC_FW_RESET:		Reset firmware
 * @IONIC_FW_INSTALL:		Install firmware
 * @IONIC_FW_ACTIVATE:		Activate firmware
 * @IONIC_FW_INSTALL_ASYNC:	Install firmware asynchronously
 * @IONIC_FW_INSTALL_STATUS:	Firmware installation status
 * @IONIC_FW_ACTIVATE_ASYNC:	Activate firmware asynchronously
 * @IONIC_FW_ACTIVATE_STATUS:	Firmware activate status
 */
क्रमागत ionic_fw_control_oper अणु
	IONIC_FW_RESET			= 0,
	IONIC_FW_INSTALL		= 1,
	IONIC_FW_ACTIVATE		= 2,
	IONIC_FW_INSTALL_ASYNC		= 3,
	IONIC_FW_INSTALL_STATUS		= 4,
	IONIC_FW_ACTIVATE_ASYNC		= 5,
	IONIC_FW_ACTIVATE_STATUS	= 6,
	IONIC_FW_UPDATE_CLEANUP		= 7,
पूर्ण;

/**
 * काष्ठा ionic_fw_control_cmd - Firmware control command
 * @opcode:    opcode
 * @oper:      firmware control operation (क्रमागत ionic_fw_control_oper)
 * @slot:      slot to activate
 */
काष्ठा ionic_fw_control_cmd अणु
	u8  opcode;
	u8  rsvd[3];
	u8  oper;
	u8  slot;
	u8  rsvd1[58];
पूर्ण;

/**
 * काष्ठा ionic_fw_control_comp - Firmware control copletion
 * @status:     Status of the command (क्रमागत ionic_status_code)
 * @comp_index: Index in the descriptor ring क्रम which this is the completion
 * @slot:       Slot where the firmware was installed
 * @color:      Color bit
 */
काष्ठा ionic_fw_control_comp अणु
	u8     status;
	u8     rsvd;
	__le16 comp_index;
	u8     slot;
	u8     rsvd1[10];
	u8     color;
पूर्ण;

/******************************************************************
 ******************* RDMA Commands ********************************
 ******************************************************************/

/**
 * काष्ठा ionic_rdma_reset_cmd - Reset RDMA LIF cmd
 * @opcode:        opcode
 * @lअगर_index:     LIF index
 *
 * There is no RDMA specअगरic dev command completion काष्ठा.  Completion uses
 * the common काष्ठा ionic_admin_comp.  Only the status is indicated.
 * Nonzero status means the LIF करोes not support RDMA.
 **/
काष्ठा ionic_rdma_reset_cmd अणु
	u8     opcode;
	u8     rsvd;
	__le16 lअगर_index;
	u8     rsvd2[60];
पूर्ण;

/**
 * काष्ठा ionic_rdma_queue_cmd - Create RDMA Queue command
 * @opcode:        opcode, 52, 53
 * @lअगर_index:     LIF index
 * @qid_ver:       (qid | (RDMA version << 24))
 * @cid:           पूर्णांकr, eq_id, or cq_id
 * @dbid:          करोorbell page id
 * @depth_log2:    log base two of queue depth
 * @stride_log2:   log base two of queue stride
 * @dma_addr:      address of the queue memory
 *
 * The same command काष्ठा is used to create an RDMA event queue, completion
 * queue, or RDMA admin queue.  The cid is an पूर्णांकerrupt number क्रम an event
 * queue, an event queue id क्रम a completion queue, or a completion queue id
 * क्रम an RDMA admin queue.
 *
 * The queue created via a dev command must be contiguous in dma space.
 *
 * The dev commands are पूर्णांकended only to be used during driver initialization,
 * to create queues supporting the RDMA admin queue.  Other queues, and other
 * types of RDMA resources like memory regions, will be created and रेजिस्टरed
 * via the RDMA admin queue, and will support a more complete पूर्णांकerface
 * providing scatter gather lists क्रम larger, scattered queue buffers and
 * memory registration.
 *
 * There is no RDMA specअगरic dev command completion काष्ठा.  Completion uses
 * the common काष्ठा ionic_admin_comp.  Only the status is indicated.
 **/
काष्ठा ionic_rdma_queue_cmd अणु
	u8     opcode;
	u8     rsvd;
	__le16 lअगर_index;
	__le32 qid_ver;
	__le32 cid;
	__le16 dbid;
	u8     depth_log2;
	u8     stride_log2;
	__le64 dma_addr;
	u8     rsvd2[40];
पूर्ण;

/******************************************************************
 ******************* Notअगरy Events ********************************
 ******************************************************************/

/**
 * काष्ठा ionic_notअगरyq_event - Generic event reporting काष्ठाure
 * @eid:   event number
 * @ecode: event code
 * @data:  unspecअगरied data about the event
 *
 * This is the generic event report काष्ठा from which the other
 * actual events will be क्रमmed.
 */
काष्ठा ionic_notअगरyq_event अणु
	__le64 eid;
	__le16 ecode;
	u8     data[54];
पूर्ण;

/**
 * काष्ठा ionic_link_change_event - Link change event notअगरication
 * @eid:		event number
 * @ecode:		event code = IONIC_EVENT_LINK_CHANGE
 * @link_status:	link up/करोwn, with error bits (क्रमागत ionic_port_status)
 * @link_speed:		speed of the network link
 *
 * Sent when the network link state changes between UP and DOWN
 */
काष्ठा ionic_link_change_event अणु
	__le64 eid;
	__le16 ecode;
	__le16 link_status;
	__le32 link_speed;	/* units of 1Mbps: e.g. 10000 = 10Gbps */
	u8     rsvd[48];
पूर्ण;

/**
 * काष्ठा ionic_reset_event - Reset event notअगरication
 * @eid:		event number
 * @ecode:		event code = IONIC_EVENT_RESET
 * @reset_code:		reset type
 * @state:		0=pending, 1=complete, 2=error
 *
 * Sent when the NIC or some subप्रणाली is going to be or
 * has been reset.
 */
काष्ठा ionic_reset_event अणु
	__le64 eid;
	__le16 ecode;
	u8     reset_code;
	u8     state;
	u8     rsvd[52];
पूर्ण;

/**
 * काष्ठा ionic_heartbeat_event - Sent periodically by NIC to indicate health
 * @eid:	event number
 * @ecode:	event code = IONIC_EVENT_HEARTBEAT
 */
काष्ठा ionic_heartbeat_event अणु
	__le64 eid;
	__le16 ecode;
	u8     rsvd[54];
पूर्ण;

/**
 * काष्ठा ionic_log_event - Sent to notअगरy the driver of an पूर्णांकernal error
 * @eid:	event number
 * @ecode:	event code = IONIC_EVENT_LOG
 * @data:	log data
 */
काष्ठा ionic_log_event अणु
	__le64 eid;
	__le16 ecode;
	u8     data[54];
पूर्ण;

/**
 * काष्ठा ionic_xcvr_event - Transceiver change event
 * @eid:	event number
 * @ecode:	event code = IONIC_EVENT_XCVR
 */
काष्ठा ionic_xcvr_event अणु
	__le64 eid;
	__le16 ecode;
	u8     rsvd[54];
पूर्ण;

/**
 * काष्ठा ionic_port_stats - Port statistics काष्ठाure
 */
काष्ठा ionic_port_stats अणु
	__le64 frames_rx_ok;
	__le64 frames_rx_all;
	__le64 frames_rx_bad_fcs;
	__le64 frames_rx_bad_all;
	__le64 octets_rx_ok;
	__le64 octets_rx_all;
	__le64 frames_rx_unicast;
	__le64 frames_rx_multicast;
	__le64 frames_rx_broadcast;
	__le64 frames_rx_छोड़ो;
	__le64 frames_rx_bad_length;
	__le64 frames_rx_undersized;
	__le64 frames_rx_oversized;
	__le64 frames_rx_fragments;
	__le64 frames_rx_jabber;
	__le64 frames_rx_priछोड़ो;
	__le64 frames_rx_stomped_crc;
	__le64 frames_rx_too_दीर्घ;
	__le64 frames_rx_vlan_good;
	__le64 frames_rx_dropped;
	__le64 frames_rx_less_than_64b;
	__le64 frames_rx_64b;
	__le64 frames_rx_65b_127b;
	__le64 frames_rx_128b_255b;
	__le64 frames_rx_256b_511b;
	__le64 frames_rx_512b_1023b;
	__le64 frames_rx_1024b_1518b;
	__le64 frames_rx_1519b_2047b;
	__le64 frames_rx_2048b_4095b;
	__le64 frames_rx_4096b_8191b;
	__le64 frames_rx_8192b_9215b;
	__le64 frames_rx_other;
	__le64 frames_tx_ok;
	__le64 frames_tx_all;
	__le64 frames_tx_bad;
	__le64 octets_tx_ok;
	__le64 octets_tx_total;
	__le64 frames_tx_unicast;
	__le64 frames_tx_multicast;
	__le64 frames_tx_broadcast;
	__le64 frames_tx_छोड़ो;
	__le64 frames_tx_priछोड़ो;
	__le64 frames_tx_vlan;
	__le64 frames_tx_less_than_64b;
	__le64 frames_tx_64b;
	__le64 frames_tx_65b_127b;
	__le64 frames_tx_128b_255b;
	__le64 frames_tx_256b_511b;
	__le64 frames_tx_512b_1023b;
	__le64 frames_tx_1024b_1518b;
	__le64 frames_tx_1519b_2047b;
	__le64 frames_tx_2048b_4095b;
	__le64 frames_tx_4096b_8191b;
	__le64 frames_tx_8192b_9215b;
	__le64 frames_tx_other;
	__le64 frames_tx_pri_0;
	__le64 frames_tx_pri_1;
	__le64 frames_tx_pri_2;
	__le64 frames_tx_pri_3;
	__le64 frames_tx_pri_4;
	__le64 frames_tx_pri_5;
	__le64 frames_tx_pri_6;
	__le64 frames_tx_pri_7;
	__le64 frames_rx_pri_0;
	__le64 frames_rx_pri_1;
	__le64 frames_rx_pri_2;
	__le64 frames_rx_pri_3;
	__le64 frames_rx_pri_4;
	__le64 frames_rx_pri_5;
	__le64 frames_rx_pri_6;
	__le64 frames_rx_pri_7;
	__le64 tx_priछोड़ो_0_1us_count;
	__le64 tx_priछोड़ो_1_1us_count;
	__le64 tx_priछोड़ो_2_1us_count;
	__le64 tx_priछोड़ो_3_1us_count;
	__le64 tx_priछोड़ो_4_1us_count;
	__le64 tx_priछोड़ो_5_1us_count;
	__le64 tx_priछोड़ो_6_1us_count;
	__le64 tx_priछोड़ो_7_1us_count;
	__le64 rx_priछोड़ो_0_1us_count;
	__le64 rx_priछोड़ो_1_1us_count;
	__le64 rx_priछोड़ो_2_1us_count;
	__le64 rx_priछोड़ो_3_1us_count;
	__le64 rx_priछोड़ो_4_1us_count;
	__le64 rx_priछोड़ो_5_1us_count;
	__le64 rx_priछोड़ो_6_1us_count;
	__le64 rx_priछोड़ो_7_1us_count;
	__le64 rx_छोड़ो_1us_count;
	__le64 frames_tx_truncated;
पूर्ण;

काष्ठा ionic_mgmt_port_stats अणु
	__le64 frames_rx_ok;
	__le64 frames_rx_all;
	__le64 frames_rx_bad_fcs;
	__le64 frames_rx_bad_all;
	__le64 octets_rx_ok;
	__le64 octets_rx_all;
	__le64 frames_rx_unicast;
	__le64 frames_rx_multicast;
	__le64 frames_rx_broadcast;
	__le64 frames_rx_छोड़ो;
	__le64 frames_rx_bad_length;
	__le64 frames_rx_undersized;
	__le64 frames_rx_oversized;
	__le64 frames_rx_fragments;
	__le64 frames_rx_jabber;
	__le64 frames_rx_64b;
	__le64 frames_rx_65b_127b;
	__le64 frames_rx_128b_255b;
	__le64 frames_rx_256b_511b;
	__le64 frames_rx_512b_1023b;
	__le64 frames_rx_1024b_1518b;
	__le64 frames_rx_gt_1518b;
	__le64 frames_rx_fअगरo_full;
	__le64 frames_tx_ok;
	__le64 frames_tx_all;
	__le64 frames_tx_bad;
	__le64 octets_tx_ok;
	__le64 octets_tx_total;
	__le64 frames_tx_unicast;
	__le64 frames_tx_multicast;
	__le64 frames_tx_broadcast;
	__le64 frames_tx_छोड़ो;
पूर्ण;

क्रमागत ionic_pb_buffer_drop_stats अणु
	IONIC_BUFFER_INTRINSIC_DROP = 0,
	IONIC_BUFFER_DISCARDED,
	IONIC_BUFFER_ADMITTED,
	IONIC_BUFFER_OUT_OF_CELLS_DROP,
	IONIC_BUFFER_OUT_OF_CELLS_DROP_2,
	IONIC_BUFFER_OUT_OF_CREDIT_DROP,
	IONIC_BUFFER_TRUNCATION_DROP,
	IONIC_BUFFER_PORT_DISABLED_DROP,
	IONIC_BUFFER_COPY_TO_CPU_TAIL_DROP,
	IONIC_BUFFER_SPAN_TAIL_DROP,
	IONIC_BUFFER_MIN_SIZE_VIOLATION_DROP,
	IONIC_BUFFER_ENQUEUE_ERROR_DROP,
	IONIC_BUFFER_INVALID_PORT_DROP,
	IONIC_BUFFER_INVALID_OUTPUT_QUEUE_DROP,
	IONIC_BUFFER_DROP_MAX,
पूर्ण;

क्रमागत ionic_oflow_drop_stats अणु
	IONIC_OFLOW_OCCUPANCY_DROP,
	IONIC_OFLOW_EMERGENCY_STOP_DROP,
	IONIC_OFLOW_WRITE_BUFFER_ACK_FILL_UP_DROP,
	IONIC_OFLOW_WRITE_BUFFER_ACK_FULL_DROP,
	IONIC_OFLOW_WRITE_BUFFER_FULL_DROP,
	IONIC_OFLOW_CONTROL_FIFO_FULL_DROP,
	IONIC_OFLOW_DROP_MAX,
पूर्ण;

/**
 * काष्ठा port_pb_stats - packet buffers प्रणाली stats
 * uses ionic_pb_buffer_drop_stats क्रम drop_counts[]
 */
काष्ठा ionic_port_pb_stats अणु
	__le64 sop_count_in;
	__le64 eop_count_in;
	__le64 sop_count_out;
	__le64 eop_count_out;
	__le64 drop_counts[IONIC_BUFFER_DROP_MAX];
	__le64 input_queue_buffer_occupancy[IONIC_QOS_TC_MAX];
	__le64 input_queue_port_monitor[IONIC_QOS_TC_MAX];
	__le64 output_queue_port_monitor[IONIC_QOS_TC_MAX];
	__le64 oflow_drop_counts[IONIC_OFLOW_DROP_MAX];
	__le64 input_queue_good_pkts_in[IONIC_QOS_TC_MAX];
	__le64 input_queue_good_pkts_out[IONIC_QOS_TC_MAX];
	__le64 input_queue_err_pkts_in[IONIC_QOS_TC_MAX];
	__le64 input_queue_fअगरo_depth[IONIC_QOS_TC_MAX];
	__le64 input_queue_max_fअगरo_depth[IONIC_QOS_TC_MAX];
	__le64 input_queue_peak_occupancy[IONIC_QOS_TC_MAX];
	__le64 output_queue_buffer_occupancy[IONIC_QOS_TC_MAX];
पूर्ण;

/**
 * काष्ठा ionic_port_identity - port identity काष्ठाure
 * @version:        identity काष्ठाure version
 * @type:           type of port (क्रमागत ionic_port_type)
 * @num_lanes:      number of lanes क्रम the port
 * @स्वतःneg:        स्वतःneg supported
 * @min_frame_size: minimum frame size supported
 * @max_frame_size: maximum frame size supported
 * @fec_type:       supported fec types
 * @छोड़ो_type:     supported छोड़ो types
 * @loopback_mode:  supported loopback mode
 * @speeds:         supported speeds
 * @config:         current port configuration
 */
जोड़ ionic_port_identity अणु
	काष्ठा अणु
		u8     version;
		u8     type;
		u8     num_lanes;
		u8     स्वतःneg;
		__le32 min_frame_size;
		__le32 max_frame_size;
		u8     fec_type[4];
		u8     छोड़ो_type[2];
		u8     loopback_mode[2];
		__le32 speeds[16];
		u8     rsvd2[44];
		जोड़ ionic_port_config config;
	पूर्ण;
	__le32 words[478];
पूर्ण;

/**
 * काष्ठा ionic_port_info - port info काष्ठाure
 * @config:          Port configuration data
 * @status:          Port status data
 * @stats:           Port statistics data
 * @mgmt_stats:      Port management statistics data
 * @port_pb_drop_stats:   uplink pb drop stats
 */
काष्ठा ionic_port_info अणु
	जोड़ ionic_port_config config;
	काष्ठा ionic_port_status status;
	जोड़ अणु
		काष्ठा ionic_port_stats      stats;
		काष्ठा ionic_mgmt_port_stats mgmt_stats;
	पूर्ण;
	/* room क्रम pb_stats to start at 2k offset */
	u8                          rsvd[760];
	काष्ठा ionic_port_pb_stats  pb_stats;
पूर्ण;

/**
 * काष्ठा ionic_lअगर_stats - LIF statistics काष्ठाure
 */
काष्ठा ionic_lअगर_stats अणु
	/* RX */
	__le64 rx_ucast_bytes;
	__le64 rx_ucast_packets;
	__le64 rx_mcast_bytes;
	__le64 rx_mcast_packets;
	__le64 rx_bcast_bytes;
	__le64 rx_bcast_packets;
	__le64 rsvd0;
	__le64 rsvd1;
	/* RX drops */
	__le64 rx_ucast_drop_bytes;
	__le64 rx_ucast_drop_packets;
	__le64 rx_mcast_drop_bytes;
	__le64 rx_mcast_drop_packets;
	__le64 rx_bcast_drop_bytes;
	__le64 rx_bcast_drop_packets;
	__le64 rx_dma_error;
	__le64 rsvd2;
	/* TX */
	__le64 tx_ucast_bytes;
	__le64 tx_ucast_packets;
	__le64 tx_mcast_bytes;
	__le64 tx_mcast_packets;
	__le64 tx_bcast_bytes;
	__le64 tx_bcast_packets;
	__le64 rsvd3;
	__le64 rsvd4;
	/* TX drops */
	__le64 tx_ucast_drop_bytes;
	__le64 tx_ucast_drop_packets;
	__le64 tx_mcast_drop_bytes;
	__le64 tx_mcast_drop_packets;
	__le64 tx_bcast_drop_bytes;
	__le64 tx_bcast_drop_packets;
	__le64 tx_dma_error;
	__le64 rsvd5;
	/* Rx Queue/Ring drops */
	__le64 rx_queue_disabled;
	__le64 rx_queue_empty;
	__le64 rx_queue_error;
	__le64 rx_desc_fetch_error;
	__le64 rx_desc_data_error;
	__le64 rsvd6;
	__le64 rsvd7;
	__le64 rsvd8;
	/* Tx Queue/Ring drops */
	__le64 tx_queue_disabled;
	__le64 tx_queue_error;
	__le64 tx_desc_fetch_error;
	__le64 tx_desc_data_error;
	__le64 tx_queue_empty;
	__le64 rsvd10;
	__le64 rsvd11;
	__le64 rsvd12;

	/* RDMA/ROCE TX */
	__le64 tx_rdma_ucast_bytes;
	__le64 tx_rdma_ucast_packets;
	__le64 tx_rdma_mcast_bytes;
	__le64 tx_rdma_mcast_packets;
	__le64 tx_rdma_cnp_packets;
	__le64 rsvd13;
	__le64 rsvd14;
	__le64 rsvd15;

	/* RDMA/ROCE RX */
	__le64 rx_rdma_ucast_bytes;
	__le64 rx_rdma_ucast_packets;
	__le64 rx_rdma_mcast_bytes;
	__le64 rx_rdma_mcast_packets;
	__le64 rx_rdma_cnp_packets;
	__le64 rx_rdma_ecn_packets;
	__le64 rsvd16;
	__le64 rsvd17;

	__le64 rsvd18;
	__le64 rsvd19;
	__le64 rsvd20;
	__le64 rsvd21;
	__le64 rsvd22;
	__le64 rsvd23;
	__le64 rsvd24;
	__le64 rsvd25;

	__le64 rsvd26;
	__le64 rsvd27;
	__le64 rsvd28;
	__le64 rsvd29;
	__le64 rsvd30;
	__le64 rsvd31;
	__le64 rsvd32;
	__le64 rsvd33;

	__le64 rsvd34;
	__le64 rsvd35;
	__le64 rsvd36;
	__le64 rsvd37;
	__le64 rsvd38;
	__le64 rsvd39;
	__le64 rsvd40;
	__le64 rsvd41;

	__le64 rsvd42;
	__le64 rsvd43;
	__le64 rsvd44;
	__le64 rsvd45;
	__le64 rsvd46;
	__le64 rsvd47;
	__le64 rsvd48;
	__le64 rsvd49;

	/* RDMA/ROCE REQ Error/Debugs (768 - 895) */
	__le64 rdma_req_rx_pkt_seq_err;
	__le64 rdma_req_rx_rnr_retry_err;
	__le64 rdma_req_rx_remote_access_err;
	__le64 rdma_req_rx_remote_inv_req_err;
	__le64 rdma_req_rx_remote_oper_err;
	__le64 rdma_req_rx_implied_nak_seq_err;
	__le64 rdma_req_rx_cqe_err;
	__le64 rdma_req_rx_cqe_flush_err;

	__le64 rdma_req_rx_dup_responses;
	__le64 rdma_req_rx_invalid_packets;
	__le64 rdma_req_tx_local_access_err;
	__le64 rdma_req_tx_local_oper_err;
	__le64 rdma_req_tx_memory_mgmt_err;
	__le64 rsvd52;
	__le64 rsvd53;
	__le64 rsvd54;

	/* RDMA/ROCE RESP Error/Debugs (896 - 1023) */
	__le64 rdma_resp_rx_dup_requests;
	__le64 rdma_resp_rx_out_of_buffer;
	__le64 rdma_resp_rx_out_of_seq_pkts;
	__le64 rdma_resp_rx_cqe_err;
	__le64 rdma_resp_rx_cqe_flush_err;
	__le64 rdma_resp_rx_local_len_err;
	__le64 rdma_resp_rx_inv_request_err;
	__le64 rdma_resp_rx_local_qp_oper_err;

	__le64 rdma_resp_rx_out_of_atomic_resource;
	__le64 rdma_resp_tx_pkt_seq_err;
	__le64 rdma_resp_tx_remote_inv_req_err;
	__le64 rdma_resp_tx_remote_access_err;
	__le64 rdma_resp_tx_remote_oper_err;
	__le64 rdma_resp_tx_rnr_retry_err;
	__le64 rsvd57;
	__le64 rsvd58;
पूर्ण;

/**
 * काष्ठा ionic_lअगर_info - LIF info काष्ठाure
 * @config:	LIF configuration काष्ठाure
 * @status:	LIF status काष्ठाure
 * @stats:	LIF statistics काष्ठाure
 */
काष्ठा ionic_lअगर_info अणु
	जोड़ ionic_lअगर_config config;
	काष्ठा ionic_lअगर_status status;
	काष्ठा ionic_lअगर_stats stats;
पूर्ण;

जोड़ ionic_dev_cmd अणु
	u32 words[16];
	काष्ठा ionic_admin_cmd cmd;
	काष्ठा ionic_nop_cmd nop;

	काष्ठा ionic_dev_identअगरy_cmd identअगरy;
	काष्ठा ionic_dev_init_cmd init;
	काष्ठा ionic_dev_reset_cmd reset;
	काष्ठा ionic_dev_getattr_cmd getattr;
	काष्ठा ionic_dev_setattr_cmd setattr;

	काष्ठा ionic_port_identअगरy_cmd port_identअगरy;
	काष्ठा ionic_port_init_cmd port_init;
	काष्ठा ionic_port_reset_cmd port_reset;
	काष्ठा ionic_port_getattr_cmd port_getattr;
	काष्ठा ionic_port_setattr_cmd port_setattr;

	काष्ठा ionic_vf_setattr_cmd vf_setattr;
	काष्ठा ionic_vf_getattr_cmd vf_getattr;

	काष्ठा ionic_lअगर_identअगरy_cmd lअगर_identअगरy;
	काष्ठा ionic_lअगर_init_cmd lअगर_init;
	काष्ठा ionic_lअगर_reset_cmd lअगर_reset;

	काष्ठा ionic_qos_identअगरy_cmd qos_identअगरy;
	काष्ठा ionic_qos_init_cmd qos_init;
	काष्ठा ionic_qos_reset_cmd qos_reset;
	काष्ठा ionic_qos_clear_stats_cmd qos_clear_stats;

	काष्ठा ionic_q_identअगरy_cmd q_identअगरy;
	काष्ठा ionic_q_init_cmd q_init;
	काष्ठा ionic_q_control_cmd q_control;

	काष्ठा ionic_fw_करोwnload_cmd fw_करोwnload;
	काष्ठा ionic_fw_control_cmd fw_control;
पूर्ण;

जोड़ ionic_dev_cmd_comp अणु
	u32 words[4];
	u8 status;
	काष्ठा ionic_admin_comp comp;
	काष्ठा ionic_nop_comp nop;

	काष्ठा ionic_dev_identअगरy_comp identअगरy;
	काष्ठा ionic_dev_init_comp init;
	काष्ठा ionic_dev_reset_comp reset;
	काष्ठा ionic_dev_getattr_comp getattr;
	काष्ठा ionic_dev_setattr_comp setattr;

	काष्ठा ionic_port_identअगरy_comp port_identअगरy;
	काष्ठा ionic_port_init_comp port_init;
	काष्ठा ionic_port_reset_comp port_reset;
	काष्ठा ionic_port_getattr_comp port_getattr;
	काष्ठा ionic_port_setattr_comp port_setattr;

	काष्ठा ionic_vf_setattr_comp vf_setattr;
	काष्ठा ionic_vf_getattr_comp vf_getattr;

	काष्ठा ionic_lअगर_identअगरy_comp lअगर_identअगरy;
	काष्ठा ionic_lअगर_init_comp lअगर_init;
	ionic_lअगर_reset_comp lअगर_reset;

	काष्ठा ionic_qos_identअगरy_comp qos_identअगरy;
	ionic_qos_init_comp qos_init;
	ionic_qos_reset_comp qos_reset;

	काष्ठा ionic_q_identअगरy_comp q_identअगरy;
	काष्ठा ionic_q_init_comp q_init;

	ionic_fw_करोwnload_comp fw_करोwnload;
	काष्ठा ionic_fw_control_comp fw_control;
पूर्ण;

/**
 * काष्ठा ionic_hwstamp_regs - Hardware current बारtamp रेजिस्टरs
 * @tick_low:        Low 32 bits of hardware बारtamp
 * @tick_high:       High 32 bits of hardware बारtamp
 */
काष्ठा ionic_hwstamp_regs अणु
	u32    tick_low;
	u32    tick_high;
पूर्ण;

/**
 * जोड़ ionic_dev_info_regs - Device info रेजिस्टर क्रमmat (पढ़ो-only)
 * @signature:       Signature value of 0x44455649 ('DEVI')
 * @version:         Current version of info
 * @asic_type:       Asic type
 * @asic_rev:        Asic revision
 * @fw_status:       Firmware status
 * @fw_heartbeat:    Firmware heartbeat counter
 * @serial_num:      Serial number
 * @fw_version:      Firmware version
 * @hwstamp_regs:    Hardware current बारtamp रेजिस्टरs
 */
जोड़ ionic_dev_info_regs अणु
#घोषणा IONIC_DEVINFO_FWVERS_BUFLEN 32
#घोषणा IONIC_DEVINFO_SERIAL_BUFLEN 32
	काष्ठा अणु
		u32    signature;
		u8     version;
		u8     asic_type;
		u8     asic_rev;
#घोषणा IONIC_FW_STS_F_RUNNING	0x1
		u8     fw_status;
		u32    fw_heartbeat;
		अक्षर   fw_version[IONIC_DEVINFO_FWVERS_BUFLEN];
		अक्षर   serial_num[IONIC_DEVINFO_SERIAL_BUFLEN];
		u8     rsvd_pad1024[948];
		काष्ठा ionic_hwstamp_regs hwstamp;
	पूर्ण;
	u32 words[512];
पूर्ण;

/**
 * जोड़ ionic_dev_cmd_regs - Device command रेजिस्टर क्रमmat (पढ़ो-ग_लिखो)
 * @करोorbell:        Device Cmd Doorbell, ग_लिखो-only
 *                   Write a 1 to संकेत device to process cmd,
 *                   poll करोne क्रम completion.
 * @करोne:            Done indicator, bit 0 == 1 when command is complete
 * @cmd:             Opcode-specअगरic command bytes
 * @comp:            Opcode-specअगरic response bytes
 * @data:            Opcode-specअगरic side-data
 */
जोड़ ionic_dev_cmd_regs अणु
	काष्ठा अणु
		u32                   करोorbell;
		u32                   करोne;
		जोड़ ionic_dev_cmd         cmd;
		जोड़ ionic_dev_cmd_comp    comp;
		u8                    rsvd[48];
		u32                   data[478];
	पूर्ण __packed;
	u32 words[512];
पूर्ण;

/**
 * जोड़ ionic_dev_regs - Device रेजिस्टर क्रमmat क्रम bar 0 page 0
 * @info:            Device info रेजिस्टरs
 * @devcmd:          Device command रेजिस्टरs
 */
जोड़ ionic_dev_regs अणु
	काष्ठा अणु
		जोड़ ionic_dev_info_regs info;
		जोड़ ionic_dev_cmd_regs  devcmd;
	पूर्ण __packed;
	__le32 words[1024];
पूर्ण;

जोड़ ionic_adminq_cmd अणु
	काष्ठा ionic_admin_cmd cmd;
	काष्ठा ionic_nop_cmd nop;
	काष्ठा ionic_q_identअगरy_cmd q_identअगरy;
	काष्ठा ionic_q_init_cmd q_init;
	काष्ठा ionic_q_control_cmd q_control;
	काष्ठा ionic_lअगर_setattr_cmd lअगर_setattr;
	काष्ठा ionic_lअगर_getattr_cmd lअगर_getattr;
	काष्ठा ionic_lअगर_setphc_cmd lअगर_setphc;
	काष्ठा ionic_rx_mode_set_cmd rx_mode_set;
	काष्ठा ionic_rx_filter_add_cmd rx_filter_add;
	काष्ठा ionic_rx_filter_del_cmd rx_filter_del;
	काष्ठा ionic_rdma_reset_cmd rdma_reset;
	काष्ठा ionic_rdma_queue_cmd rdma_queue;
	काष्ठा ionic_fw_करोwnload_cmd fw_करोwnload;
	काष्ठा ionic_fw_control_cmd fw_control;
पूर्ण;

जोड़ ionic_adminq_comp अणु
	काष्ठा ionic_admin_comp comp;
	काष्ठा ionic_nop_comp nop;
	काष्ठा ionic_q_identअगरy_comp q_identअगरy;
	काष्ठा ionic_q_init_comp q_init;
	काष्ठा ionic_lअगर_setattr_comp lअगर_setattr;
	काष्ठा ionic_lअगर_getattr_comp lअगर_getattr;
	काष्ठा ionic_admin_comp lअगर_setphc;
	काष्ठा ionic_rx_filter_add_comp rx_filter_add;
	काष्ठा ionic_fw_control_comp fw_control;
पूर्ण;

#घोषणा IONIC_BARS_MAX			6
#घोषणा IONIC_PCI_BAR_DBELL		1

/* BAR0 */
#घोषणा IONIC_BAR0_SIZE				0x8000

#घोषणा IONIC_BAR0_DEV_INFO_REGS_OFFSET		0x0000
#घोषणा IONIC_BAR0_DEV_CMD_REGS_OFFSET		0x0800
#घोषणा IONIC_BAR0_DEV_CMD_DATA_REGS_OFFSET	0x0c00
#घोषणा IONIC_BAR0_INTR_STATUS_OFFSET		0x1000
#घोषणा IONIC_BAR0_INTR_CTRL_OFFSET		0x2000
#घोषणा IONIC_DEV_CMD_DONE			0x00000001

#घोषणा IONIC_ASIC_TYPE_CAPRI			0

/**
 * काष्ठा ionic_करोorbell - Doorbell रेजिस्टर layout
 * @p_index: Producer index
 * @ring:    Selects the specअगरic ring of the queue to update
 *           Type-specअगरic meaning:
 *              ring=0: Default producer/consumer queue
 *              ring=1: (CQ, EQ) Re-Arm queue.  RDMA CQs
 *              send events to EQs when armed.  EQs send
 *              पूर्णांकerrupts when armed.
 * @qid_lo:  Queue destination क्रम the producer index and flags (low bits)
 * @qid_hi:  Queue destination क्रम the producer index and flags (high bits)
 */
काष्ठा ionic_करोorbell अणु
	__le16 p_index;
	u8     ring;
	u8     qid_lo;
	__le16 qid_hi;
	u16    rsvd2;
पूर्ण;

काष्ठा ionic_पूर्णांकr_status अणु
	u32 status[2];
पूर्ण;

काष्ठा ionic_notअगरyq_cmd अणु
	__le32 data;	/* Not used but needed क्रम qcq काष्ठाure */
पूर्ण;

जोड़ ionic_notअगरyq_comp अणु
	काष्ठा ionic_notअगरyq_event event;
	काष्ठा ionic_link_change_event link_change;
	काष्ठा ionic_reset_event reset;
	काष्ठा ionic_heartbeat_event heartbeat;
	काष्ठा ionic_log_event log;
पूर्ण;

/* Deprecate */
काष्ठा ionic_identity अणु
	जोड़ ionic_drv_identity drv;
	जोड़ ionic_dev_identity dev;
	जोड़ ionic_lअगर_identity lअगर;
	जोड़ ionic_port_identity port;
	जोड़ ionic_qos_identity qos;
	जोड़ ionic_q_identity txq;
पूर्ण;

#पूर्ण_अगर /* _IONIC_IF_H_ */
