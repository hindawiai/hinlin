<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Linux network driver क्रम QLogic BR-series Converged Network Adapter.
 */
/*
 * Copyright (c) 2005-2014 Brocade Communications Systems, Inc.
 * Copyright (c) 2014-2015 QLogic Corporation
 * All rights reserved
 * www.qlogic.com
 */

/* BNA Hardware and Firmware Interface */

/* Skipping statistics collection to aव्योम clutter.
 * Command is no दीर्घer needed:
 *	MTU
 *	TxQ Stop
 *	RxQ Stop
 *	RxF Enable/Disable
 *
 * HDS-off request is dynamic
 * keep काष्ठाures as multiple of 32-bit fields क्रम alignment.
 * All values must be written in big-endian.
 */
#अगर_अघोषित __BFI_ENET_H__
#घोषणा __BFI_ENET_H__

#समावेश "bfa_defs.h"
#समावेश "bfi.h"

#घोषणा BFI_ENET_CFG_MAX		32	/* Max resources per PF */

#घोषणा BFI_ENET_TXQ_PRIO_MAX		8
#घोषणा BFI_ENET_RX_QSET_MAX		16
#घोषणा BFI_ENET_TXQ_WI_VECT_MAX	4

#घोषणा BFI_ENET_VLAN_ID_MAX		4096
#घोषणा BFI_ENET_VLAN_BLOCK_SIZE	512	/* in bits */
#घोषणा BFI_ENET_VLAN_BLOCKS_MAX					\
	(BFI_ENET_VLAN_ID_MAX / BFI_ENET_VLAN_BLOCK_SIZE)
#घोषणा BFI_ENET_VLAN_WORD_SIZE		32	/* in bits */
#घोषणा BFI_ENET_VLAN_WORDS_MAX						\
	(BFI_ENET_VLAN_BLOCK_SIZE / BFI_ENET_VLAN_WORD_SIZE)

#घोषणा BFI_ENET_RSS_RIT_MAX		64	/* entries */
#घोषणा BFI_ENET_RSS_KEY_LEN		10	/* 32-bit words */

जोड़ bfi_addr_be_u अणु
	काष्ठा अणु
		u32	addr_hi;	/* Most Signअगरicant 32-bits */
		u32	addr_lo;	/* Least Signअगरicant 32-Bits */
	पूर्ण __packed a32;
पूर्ण __packed;

/*	T X   Q U E U E   D E F I N E S      */
/* TxQ Vector (a.k.a. Tx-Buffer Descriptor) */
/* TxQ Entry Opcodes */
#घोषणा BFI_ENET_TXQ_WI_SEND		(0x402)	/* Single Frame Transmission */
#घोषणा BFI_ENET_TXQ_WI_SEND_LSO	(0x403)	/* Multi-Frame Transmission */
#घोषणा BFI_ENET_TXQ_WI_EXTENSION	(0x104)	/* Extension WI */

/* TxQ Entry Control Flags */
#घोषणा BFI_ENET_TXQ_WI_CF_FCOE_CRC	BIT(8)
#घोषणा BFI_ENET_TXQ_WI_CF_IPID_MODE	BIT(5)
#घोषणा BFI_ENET_TXQ_WI_CF_INS_PRIO	BIT(4)
#घोषणा BFI_ENET_TXQ_WI_CF_INS_VLAN	BIT(3)
#घोषणा BFI_ENET_TXQ_WI_CF_UDP_CKSUM	BIT(2)
#घोषणा BFI_ENET_TXQ_WI_CF_TCP_CKSUM	BIT(1)
#घोषणा BFI_ENET_TXQ_WI_CF_IP_CKSUM	BIT(0)

काष्ठा bfi_enet_txq_wi_base अणु
	u8			reserved;
	u8			num_vectors;	/* number of vectors present */
	u16			opcode;
			/* BFI_ENET_TXQ_WI_SEND or BFI_ENET_TXQ_WI_SEND_LSO */
	u16			flags;		/* OR of all the flags */
	u16			l4_hdr_size_n_offset;
	u16			vlan_tag;
	u16			lso_mss;	/* Only 14 LSB are valid */
	u32			frame_length;	/* Only 24 LSB are valid */
पूर्ण __packed;

काष्ठा bfi_enet_txq_wi_ext अणु
	u16			reserved;
	u16			opcode;		/* BFI_ENET_TXQ_WI_EXTENSION */
	u32			reserved2[3];
पूर्ण __packed;

काष्ठा bfi_enet_txq_wi_vector अणु			/* Tx Buffer Descriptor */
	u16			reserved;
	u16			length;		/* Only 14 LSB are valid */
	जोड़ bfi_addr_be_u	addr;
पूर्ण __packed;

/*  TxQ Entry Structure  */
काष्ठा bfi_enet_txq_entry अणु
	जोड़ अणु
		काष्ठा bfi_enet_txq_wi_base	base;
		काष्ठा bfi_enet_txq_wi_ext	ext;
	पूर्ण __packed wi;
	काष्ठा bfi_enet_txq_wi_vector vector[BFI_ENET_TXQ_WI_VECT_MAX];
पूर्ण __packed;

#घोषणा wi_hdr		wi.base
#घोषणा wi_ext_hdr	wi.ext

#घोषणा BFI_ENET_TXQ_WI_L4_HDR_N_OFFSET(_hdr_size, _offset) \
		(((_hdr_size) << 10) | ((_offset) & 0x3FF))

/*   R X   Q U E U E   D E F I N E S   */
काष्ठा bfi_enet_rxq_entry अणु
	जोड़ bfi_addr_be_u  rx_buffer;
पूर्ण __packed;

/*   R X   C O M P L E T I O N   Q U E U E   D E F I N E S   */
/* CQ Entry Flags */
#घोषणा BFI_ENET_CQ_EF_MAC_ERROR	BIT(0)
#घोषणा BFI_ENET_CQ_EF_FCS_ERROR	BIT(1)
#घोषणा BFI_ENET_CQ_EF_TOO_LONG		BIT(2)
#घोषणा BFI_ENET_CQ_EF_FC_CRC_OK	BIT(3)

#घोषणा BFI_ENET_CQ_EF_RSVD1		BIT(4)
#घोषणा BFI_ENET_CQ_EF_L4_CKSUM_OK	BIT(5)
#घोषणा BFI_ENET_CQ_EF_L3_CKSUM_OK	BIT(6)
#घोषणा BFI_ENET_CQ_EF_HDS_HEADER	BIT(7)

#घोषणा BFI_ENET_CQ_EF_UDP		BIT(8)
#घोषणा BFI_ENET_CQ_EF_TCP		BIT(9)
#घोषणा BFI_ENET_CQ_EF_IP_OPTIONS	BIT(10)
#घोषणा BFI_ENET_CQ_EF_IPV6		BIT(11)

#घोषणा BFI_ENET_CQ_EF_IPV4		BIT(12)
#घोषणा BFI_ENET_CQ_EF_VLAN		BIT(13)
#घोषणा BFI_ENET_CQ_EF_RSS		BIT(14)
#घोषणा BFI_ENET_CQ_EF_RSVD2		BIT(15)

#घोषणा BFI_ENET_CQ_EF_MCAST_MATCH	BIT(16)
#घोषणा BFI_ENET_CQ_EF_MCAST		BIT(17)
#घोषणा BFI_ENET_CQ_EF_BCAST		BIT(18)
#घोषणा BFI_ENET_CQ_EF_REMOTE		BIT(19)

#घोषणा BFI_ENET_CQ_EF_LOCAL		BIT(20)

/* CQ Entry Structure */
काष्ठा bfi_enet_cq_entry अणु
	u32 flags;
	u16	vlan_tag;
	u16	length;
	u32	rss_hash;
	u8	valid;
	u8	reserved1;
	u8	reserved2;
	u8	rxq_id;
पूर्ण __packed;

/*   E N E T   C O N T R O L   P A T H   C O M M A N D S   */
काष्ठा bfi_enet_q अणु
	जोड़ bfi_addr_u	pg_tbl;
	जोड़ bfi_addr_u	first_entry;
	u16		pages;	/* # of pages */
	u16		page_sz;
पूर्ण __packed;

काष्ठा bfi_enet_txq अणु
	काष्ठा bfi_enet_q	q;
	u8			priority;
	u8			rsvd[3];
पूर्ण __packed;

काष्ठा bfi_enet_rxq अणु
	काष्ठा bfi_enet_q	q;
	u16		rx_buffer_size;
	u16		rsvd;
पूर्ण __packed;

काष्ठा bfi_enet_cq अणु
	काष्ठा bfi_enet_q	q;
पूर्ण __packed;

काष्ठा bfi_enet_ib_cfg अणु
	u8		पूर्णांक_pkt_dma;
	u8		पूर्णांक_enabled;
	u8		पूर्णांक_pkt_enabled;
	u8		continuous_coalescing;
	u8		msix;
	u8		rsvd[3];
	u32	coalescing_समयout;
	u32	पूर्णांकer_pkt_समयout;
	u8		पूर्णांकer_pkt_count;
	u8		rsvd1[3];
पूर्ण __packed;

काष्ठा bfi_enet_ib अणु
	जोड़ bfi_addr_u	index_addr;
	जोड़ अणु
		u16	msix_index;
		u16	पूर्णांकx_biपंचांगask;
	पूर्ण __packed पूर्णांकr;
	u16		rsvd;
पूर्ण __packed;

/* ENET command messages */
क्रमागत bfi_enet_h2i_msgs अणु
	/* Rx Commands */
	BFI_ENET_H2I_RX_CFG_SET_REQ = 1,
	BFI_ENET_H2I_RX_CFG_CLR_REQ = 2,

	BFI_ENET_H2I_RIT_CFG_REQ = 3,
	BFI_ENET_H2I_RSS_CFG_REQ = 4,
	BFI_ENET_H2I_RSS_ENABLE_REQ = 5,
	BFI_ENET_H2I_RX_PROMISCUOUS_REQ = 6,
	BFI_ENET_H2I_RX_DEFAULT_REQ = 7,

	BFI_ENET_H2I_MAC_UCAST_SET_REQ = 8,
	BFI_ENET_H2I_MAC_UCAST_CLR_REQ = 9,
	BFI_ENET_H2I_MAC_UCAST_ADD_REQ = 10,
	BFI_ENET_H2I_MAC_UCAST_DEL_REQ = 11,

	BFI_ENET_H2I_MAC_MCAST_ADD_REQ = 12,
	BFI_ENET_H2I_MAC_MCAST_DEL_REQ = 13,
	BFI_ENET_H2I_MAC_MCAST_FILTER_REQ = 14,

	BFI_ENET_H2I_RX_VLAN_SET_REQ = 15,
	BFI_ENET_H2I_RX_VLAN_STRIP_ENABLE_REQ = 16,

	/* Tx Commands */
	BFI_ENET_H2I_TX_CFG_SET_REQ = 17,
	BFI_ENET_H2I_TX_CFG_CLR_REQ = 18,

	/* Port Commands */
	BFI_ENET_H2I_PORT_ADMIN_UP_REQ = 19,
	BFI_ENET_H2I_SET_PAUSE_REQ = 20,
	BFI_ENET_H2I_DIAG_LOOPBACK_REQ = 21,

	/* Get Attributes Command */
	BFI_ENET_H2I_GET_ATTR_REQ = 22,

	/*  Statistics Commands */
	BFI_ENET_H2I_STATS_GET_REQ = 23,
	BFI_ENET_H2I_STATS_CLR_REQ = 24,

	BFI_ENET_H2I_WOL_MAGIC_REQ = 25,
	BFI_ENET_H2I_WOL_FRAME_REQ = 26,

	BFI_ENET_H2I_MAX = 27,
पूर्ण;

क्रमागत bfi_enet_i2h_msgs अणु
	/* Rx Responses */
	BFI_ENET_I2H_RX_CFG_SET_RSP =
		BFA_I2HM(BFI_ENET_H2I_RX_CFG_SET_REQ),
	BFI_ENET_I2H_RX_CFG_CLR_RSP =
		BFA_I2HM(BFI_ENET_H2I_RX_CFG_CLR_REQ),

	BFI_ENET_I2H_RIT_CFG_RSP =
		BFA_I2HM(BFI_ENET_H2I_RIT_CFG_REQ),
	BFI_ENET_I2H_RSS_CFG_RSP =
		BFA_I2HM(BFI_ENET_H2I_RSS_CFG_REQ),
	BFI_ENET_I2H_RSS_ENABLE_RSP =
		BFA_I2HM(BFI_ENET_H2I_RSS_ENABLE_REQ),
	BFI_ENET_I2H_RX_PROMISCUOUS_RSP =
		BFA_I2HM(BFI_ENET_H2I_RX_PROMISCUOUS_REQ),
	BFI_ENET_I2H_RX_DEFAULT_RSP =
		BFA_I2HM(BFI_ENET_H2I_RX_DEFAULT_REQ),

	BFI_ENET_I2H_MAC_UCAST_SET_RSP =
		BFA_I2HM(BFI_ENET_H2I_MAC_UCAST_SET_REQ),
	BFI_ENET_I2H_MAC_UCAST_CLR_RSP =
		BFA_I2HM(BFI_ENET_H2I_MAC_UCAST_CLR_REQ),
	BFI_ENET_I2H_MAC_UCAST_ADD_RSP =
		BFA_I2HM(BFI_ENET_H2I_MAC_UCAST_ADD_REQ),
	BFI_ENET_I2H_MAC_UCAST_DEL_RSP =
		BFA_I2HM(BFI_ENET_H2I_MAC_UCAST_DEL_REQ),

	BFI_ENET_I2H_MAC_MCAST_ADD_RSP =
		BFA_I2HM(BFI_ENET_H2I_MAC_MCAST_ADD_REQ),
	BFI_ENET_I2H_MAC_MCAST_DEL_RSP =
		BFA_I2HM(BFI_ENET_H2I_MAC_MCAST_DEL_REQ),
	BFI_ENET_I2H_MAC_MCAST_FILTER_RSP =
		BFA_I2HM(BFI_ENET_H2I_MAC_MCAST_FILTER_REQ),

	BFI_ENET_I2H_RX_VLAN_SET_RSP =
		BFA_I2HM(BFI_ENET_H2I_RX_VLAN_SET_REQ),

	BFI_ENET_I2H_RX_VLAN_STRIP_ENABLE_RSP =
		BFA_I2HM(BFI_ENET_H2I_RX_VLAN_STRIP_ENABLE_REQ),

	/* Tx Responses */
	BFI_ENET_I2H_TX_CFG_SET_RSP =
		BFA_I2HM(BFI_ENET_H2I_TX_CFG_SET_REQ),
	BFI_ENET_I2H_TX_CFG_CLR_RSP =
		BFA_I2HM(BFI_ENET_H2I_TX_CFG_CLR_REQ),

	/* Port Responses */
	BFI_ENET_I2H_PORT_ADMIN_RSP =
		BFA_I2HM(BFI_ENET_H2I_PORT_ADMIN_UP_REQ),

	BFI_ENET_I2H_SET_PAUSE_RSP =
		BFA_I2HM(BFI_ENET_H2I_SET_PAUSE_REQ),
	BFI_ENET_I2H_DIAG_LOOPBACK_RSP =
		BFA_I2HM(BFI_ENET_H2I_DIAG_LOOPBACK_REQ),

	/*  Attributes Response */
	BFI_ENET_I2H_GET_ATTR_RSP =
		BFA_I2HM(BFI_ENET_H2I_GET_ATTR_REQ),

	/* Statistics Responses */
	BFI_ENET_I2H_STATS_GET_RSP =
		BFA_I2HM(BFI_ENET_H2I_STATS_GET_REQ),
	BFI_ENET_I2H_STATS_CLR_RSP =
		BFA_I2HM(BFI_ENET_H2I_STATS_CLR_REQ),

	BFI_ENET_I2H_WOL_MAGIC_RSP =
		BFA_I2HM(BFI_ENET_H2I_WOL_MAGIC_REQ),
	BFI_ENET_I2H_WOL_FRAME_RSP =
		BFA_I2HM(BFI_ENET_H2I_WOL_FRAME_REQ),

	/* AENs */
	BFI_ENET_I2H_LINK_DOWN_AEN = BFA_I2HM(BFI_ENET_H2I_MAX),
	BFI_ENET_I2H_LINK_UP_AEN = BFA_I2HM(BFI_ENET_H2I_MAX + 1),

	BFI_ENET_I2H_PORT_ENABLE_AEN = BFA_I2HM(BFI_ENET_H2I_MAX + 2),
	BFI_ENET_I2H_PORT_DISABLE_AEN = BFA_I2HM(BFI_ENET_H2I_MAX + 3),

	BFI_ENET_I2H_BW_UPDATE_AEN = BFA_I2HM(BFI_ENET_H2I_MAX + 4),
पूर्ण;

/* The following error codes can be वापसed by the enet commands */
क्रमागत bfi_enet_err अणु
	BFI_ENET_CMD_OK		= 0,
	BFI_ENET_CMD_FAIL	= 1,
	BFI_ENET_CMD_DUP_ENTRY	= 2,	/* !< Duplicate entry in CAM */
	BFI_ENET_CMD_CAM_FULL	= 3,	/* !< CAM is full */
	BFI_ENET_CMD_NOT_OWNER	= 4,	/* !< Not permitted, b'cos not owner */
	BFI_ENET_CMD_NOT_EXEC	= 5,	/* !< Was not sent to f/w at all */
	BFI_ENET_CMD_WAITING	= 6,	/* !< Waiting क्रम completion */
	BFI_ENET_CMD_PORT_DISABLED = 7,	/* !< port in disabled state */
पूर्ण;

/* Generic Request
 *
 * bfi_enet_req is used by:
 *	BFI_ENET_H2I_RX_CFG_CLR_REQ
 *	BFI_ENET_H2I_TX_CFG_CLR_REQ
 */
काष्ठा bfi_enet_req अणु
	काष्ठा bfi_msgq_mhdr mh;
पूर्ण __packed;

/* Enable/Disable Request
 *
 * bfi_enet_enable_req is used by:
 *	BFI_ENET_H2I_RSS_ENABLE_REQ	(enet_id must be zero)
 *	BFI_ENET_H2I_RX_PROMISCUOUS_REQ (enet_id must be zero)
 *	BFI_ENET_H2I_RX_DEFAULT_REQ	(enet_id must be zero)
 *	BFI_ENET_H2I_RX_MAC_MCAST_FILTER_REQ
 *	BFI_ENET_H2I_PORT_ADMIN_UP_REQ	(enet_id must be zero)
 */
काष्ठा bfi_enet_enable_req अणु
	काष्ठा		bfi_msgq_mhdr mh;
	u8		enable;		/* 1 = enable;  0 = disable */
	u8		rsvd[3];
पूर्ण __packed;

/* Generic Response */
काष्ठा bfi_enet_rsp अणु
	काष्ठा bfi_msgq_mhdr mh;
	u8		error;		/*!< अगर error see cmd_offset */
	u8		rsvd;
	u16		cmd_offset;	/*!< offset to invalid parameter */
पूर्ण __packed;

/* GLOBAL CONFIGURATION */

/* bfi_enet_attr_req is used by:
 *	BFI_ENET_H2I_GET_ATTR_REQ
 */
काष्ठा bfi_enet_attr_req अणु
	काष्ठा bfi_msgq_mhdr	mh;
पूर्ण __packed;

/* bfi_enet_attr_rsp is used by:
 *	BFI_ENET_I2H_GET_ATTR_RSP
 */
काष्ठा bfi_enet_attr_rsp अणु
	काष्ठा bfi_msgq_mhdr mh;
	u8		error;		/*!< अगर error see cmd_offset */
	u8		rsvd;
	u16		cmd_offset;	/*!< offset to invalid parameter */
	u32		max_cfg;
	u32		max_ucmac;
	u32		rit_size;
पूर्ण __packed;

/* Tx Configuration
 *
 * bfi_enet_tx_cfg is used by:
 *	BFI_ENET_H2I_TX_CFG_SET_REQ
 */
क्रमागत bfi_enet_tx_vlan_mode अणु
	BFI_ENET_TX_VLAN_NOP	= 0,
	BFI_ENET_TX_VLAN_INS	= 1,
	BFI_ENET_TX_VLAN_WI	= 2,
पूर्ण;

काष्ठा bfi_enet_tx_cfg अणु
	u8		vlan_mode;	/*!< processing mode */
	u8		rsvd;
	u16		vlan_id;
	u8		admit_tagged_frame;
	u8		apply_vlan_filter;
	u8		add_to_vचयन;
	u8		rsvd1[1];
पूर्ण __packed;

काष्ठा bfi_enet_tx_cfg_req अणु
	काष्ठा bfi_msgq_mhdr mh;
	u8			num_queues;	/* # of Tx Queues */
	u8			rsvd[3];

	काष्ठा अणु
		काष्ठा bfi_enet_txq	q;
		काष्ठा bfi_enet_ib	ib;
	पूर्ण __packed q_cfg[BFI_ENET_TXQ_PRIO_MAX];

	काष्ठा bfi_enet_ib_cfg	ib_cfg;

	काष्ठा bfi_enet_tx_cfg	tx_cfg;
पूर्ण;

काष्ठा bfi_enet_tx_cfg_rsp अणु
	काष्ठा		bfi_msgq_mhdr mh;
	u8		error;
	u8		hw_id;		/* For debugging */
	u8		rsvd[2];
	काष्ठा अणु
		u32	q_dbell;	/* PCI base address offset */
		u32	i_dbell;	/* PCI base address offset */
		u8	hw_qid;		/* For debugging */
		u8	rsvd[3];
	पूर्ण __packed q_handles[BFI_ENET_TXQ_PRIO_MAX];
पूर्ण;

/* Rx Configuration
 *
 * bfi_enet_rx_cfg is used by:
 *	BFI_ENET_H2I_RX_CFG_SET_REQ
 */
क्रमागत bfi_enet_rxq_type अणु
	BFI_ENET_RXQ_SINGLE		= 1,
	BFI_ENET_RXQ_LARGE_SMALL	= 2,
	BFI_ENET_RXQ_HDS		= 3,
	BFI_ENET_RXQ_HDS_OPT_BASED	= 4,
पूर्ण;

क्रमागत bfi_enet_hds_type अणु
	BFI_ENET_HDS_FORCED	= 0x01,
	BFI_ENET_HDS_IPV6_UDP	= 0x02,
	BFI_ENET_HDS_IPV6_TCP	= 0x04,
	BFI_ENET_HDS_IPV4_TCP	= 0x08,
	BFI_ENET_HDS_IPV4_UDP	= 0x10,
पूर्ण;

काष्ठा bfi_enet_rx_cfg अणु
	u8		rxq_type;
	u8		rsvd[1];
	u16		frame_size;

	काष्ठा अणु
		u8			max_header_size;
		u8			क्रमce_offset;
		u8			type;
		u8			rsvd1;
	पूर्ण __packed hds;

	u8		multi_buffer;
	u8		strip_vlan;
	u8		drop_untagged;
	u8		rsvd2;
पूर्ण __packed;

/*
 * Multicast frames are received on the ql of q-set index zero.
 * On the completion queue.  RxQ ID = even is क्रम large/data buffer queues
 * and RxQ ID = odd is क्रम small/header buffer queues.
 */
काष्ठा bfi_enet_rx_cfg_req अणु
	काष्ठा bfi_msgq_mhdr mh;
	u8			num_queue_sets;	/* # of Rx Queue Sets */
	u8			rsvd[3];

	काष्ठा अणु
		काष्ठा bfi_enet_rxq	ql;	/* large/data/single buffers */
		काष्ठा bfi_enet_rxq	qs;	/* small/header buffers */
		काष्ठा bfi_enet_cq	cq;
		काष्ठा bfi_enet_ib	ib;
	पूर्ण __packed q_cfg[BFI_ENET_RX_QSET_MAX];

	काष्ठा bfi_enet_ib_cfg	ib_cfg;

	काष्ठा bfi_enet_rx_cfg	rx_cfg;
पूर्ण __packed;

काष्ठा bfi_enet_rx_cfg_rsp अणु
	काष्ठा bfi_msgq_mhdr mh;
	u8		error;
	u8		hw_id;	 /* For debugging */
	u8		rsvd[2];
	काष्ठा अणु
		u32	ql_dbell; /* PCI base address offset */
		u32	qs_dbell; /* PCI base address offset */
		u32	i_dbell;  /* PCI base address offset */
		u8		hw_lqid;  /* For debugging */
		u8		hw_sqid;  /* For debugging */
		u8		hw_cqid;  /* For debugging */
		u8		rsvd;
	पूर्ण __packed q_handles[BFI_ENET_RX_QSET_MAX];
पूर्ण __packed;

/* RIT
 *
 * bfi_enet_rit_req is used by:
 *	BFI_ENET_H2I_RIT_CFG_REQ
 */
काष्ठा bfi_enet_rit_req अणु
	काष्ठा	bfi_msgq_mhdr mh;
	u16	size;			/* number of table-entries used */
	u8	rsvd[2];
	u8	table[BFI_ENET_RSS_RIT_MAX];
पूर्ण __packed;

/* RSS
 *
 * bfi_enet_rss_cfg_req is used by:
 *	BFI_ENET_H2I_RSS_CFG_REQ
 */
क्रमागत bfi_enet_rss_type अणु
	BFI_ENET_RSS_IPV6	= 0x01,
	BFI_ENET_RSS_IPV6_TCP	= 0x02,
	BFI_ENET_RSS_IPV4	= 0x04,
	BFI_ENET_RSS_IPV4_TCP	= 0x08
पूर्ण;

काष्ठा bfi_enet_rss_cfg अणु
	u8	type;
	u8	mask;
	u8	rsvd[2];
	u32	key[BFI_ENET_RSS_KEY_LEN];
पूर्ण __packed;

काष्ठा bfi_enet_rss_cfg_req अणु
	काष्ठा bfi_msgq_mhdr	mh;
	काष्ठा bfi_enet_rss_cfg	cfg;
पूर्ण __packed;

/* MAC Unicast
 *
 * bfi_enet_rx_vlan_req is used by:
 *	BFI_ENET_H2I_MAC_UCAST_SET_REQ
 *	BFI_ENET_H2I_MAC_UCAST_CLR_REQ
 *	BFI_ENET_H2I_MAC_UCAST_ADD_REQ
 *	BFI_ENET_H2I_MAC_UCAST_DEL_REQ
 */
काष्ठा bfi_enet_ucast_req अणु
	काष्ठा bfi_msgq_mhdr	mh;
	u8			mac_addr[ETH_ALEN];
	u8			rsvd[2];
पूर्ण __packed;

/* MAC Unicast + VLAN */
काष्ठा bfi_enet_mac_n_vlan_req अणु
	काष्ठा bfi_msgq_mhdr	mh;
	u16			vlan_id;
	u8			mac_addr[ETH_ALEN];
पूर्ण __packed;

/* MAC Multicast
 *
 * bfi_enet_mac_mfilter_add_req is used by:
 *	BFI_ENET_H2I_MAC_MCAST_ADD_REQ
 */
काष्ठा bfi_enet_mcast_add_req अणु
	काष्ठा bfi_msgq_mhdr	mh;
	u8			mac_addr[ETH_ALEN];
	u8			rsvd[2];
पूर्ण __packed;

/* bfi_enet_mac_mfilter_add_rsp is used by:
 *	BFI_ENET_I2H_MAC_MCAST_ADD_RSP
 */
काष्ठा bfi_enet_mcast_add_rsp अणु
	काष्ठा bfi_msgq_mhdr	mh;
	u8			error;
	u8			rsvd;
	u16			cmd_offset;
	u16			handle;
	u8			rsvd1[2];
पूर्ण __packed;

/* bfi_enet_mac_mfilter_del_req is used by:
 *	BFI_ENET_H2I_MAC_MCAST_DEL_REQ
 */
काष्ठा bfi_enet_mcast_del_req अणु
	काष्ठा bfi_msgq_mhdr	mh;
	u16			handle;
	u8			rsvd[2];
पूर्ण __packed;

/* VLAN
 *
 * bfi_enet_rx_vlan_req is used by:
 *	BFI_ENET_H2I_RX_VLAN_SET_REQ
 */
काष्ठा bfi_enet_rx_vlan_req अणु
	काष्ठा bfi_msgq_mhdr	mh;
	u8			block_idx;
	u8			rsvd[3];
	u32			bit_mask[BFI_ENET_VLAN_WORDS_MAX];
पूर्ण __packed;

/* PAUSE
 *
 * bfi_enet_set_छोड़ो_req is used by:
 *	BFI_ENET_H2I_SET_PAUSE_REQ
 */
काष्ठा bfi_enet_set_छोड़ो_req अणु
	काष्ठा bfi_msgq_mhdr	mh;
	u8			rsvd[2];
	u8			tx_छोड़ो;	/* 1 = enable;  0 = disable */
	u8			rx_छोड़ो;	/* 1 = enable;  0 = disable */
पूर्ण __packed;

/* DIAGNOSTICS
 *
 * bfi_enet_diag_lb_req is used by:
 *      BFI_ENET_H2I_DIAG_LOOPBACK
 */
काष्ठा bfi_enet_diag_lb_req अणु
	काष्ठा bfi_msgq_mhdr	mh;
	u8			rsvd[2];
	u8			mode;		/* cable or Serdes */
	u8			enable;		/* 1 = enable;  0 = disable */
पूर्ण __packed;

/* क्रमागत क्रम Loopback opmodes */
क्रमागत अणु
	BFI_ENET_DIAG_LB_OPMODE_EXT = 0,
	BFI_ENET_DIAG_LB_OPMODE_CBL = 1,
पूर्ण;

/* STATISTICS
 *
 * bfi_enet_stats_req is used by:
 *    BFI_ENET_H2I_STATS_GET_REQ
 *    BFI_ENET_I2H_STATS_CLR_REQ
 */
काष्ठा bfi_enet_stats_req अणु
	काष्ठा bfi_msgq_mhdr	mh;
	u16			stats_mask;
	u8			rsvd[2];
	u32			rx_enet_mask;
	u32			tx_enet_mask;
	जोड़ bfi_addr_u	host_buffer;
पूर्ण __packed;

/* defines क्रम "stats_mask" above. */
#घोषणा BFI_ENET_STATS_MAC    BIT(0)    /* !< MAC Statistics */
#घोषणा BFI_ENET_STATS_BPC    BIT(1)    /* !< Pause Stats from BPC */
#घोषणा BFI_ENET_STATS_RAD    BIT(2)    /* !< Rx Admission Statistics */
#घोषणा BFI_ENET_STATS_RX_FC  BIT(3)    /* !< Rx FC Stats from RxA */
#घोषणा BFI_ENET_STATS_TX_FC  BIT(4)    /* !< Tx FC Stats from TxA */

#घोषणा BFI_ENET_STATS_ALL    0x1f

/* TxF Frame Statistics */
काष्ठा bfi_enet_stats_txf अणु
	u64 ucast_octets;
	u64 ucast;
	u64 ucast_vlan;

	u64 mcast_octets;
	u64 mcast;
	u64 mcast_vlan;

	u64 bcast_octets;
	u64 bcast;
	u64 bcast_vlan;

	u64 errors;
	u64 filter_vlan;      /* frames filtered due to VLAN */
	u64 filter_mac_sa;    /* frames filtered due to SA check */
पूर्ण __packed;

/* RxF Frame Statistics */
काष्ठा bfi_enet_stats_rxf अणु
	u64 ucast_octets;
	u64 ucast;
	u64 ucast_vlan;

	u64 mcast_octets;
	u64 mcast;
	u64 mcast_vlan;

	u64 bcast_octets;
	u64 bcast;
	u64 bcast_vlan;
	u64 frame_drops;
पूर्ण __packed;

/* FC Tx Frame Statistics */
काष्ठा bfi_enet_stats_fc_tx अणु
	u64 txf_ucast_octets;
	u64 txf_ucast;
	u64 txf_ucast_vlan;

	u64 txf_mcast_octets;
	u64 txf_mcast;
	u64 txf_mcast_vlan;

	u64 txf_bcast_octets;
	u64 txf_bcast;
	u64 txf_bcast_vlan;

	u64 txf_parity_errors;
	u64 txf_समयout;
	u64 txf_fid_parity_errors;
पूर्ण __packed;

/* FC Rx Frame Statistics */
काष्ठा bfi_enet_stats_fc_rx अणु
	u64 rxf_ucast_octets;
	u64 rxf_ucast;
	u64 rxf_ucast_vlan;

	u64 rxf_mcast_octets;
	u64 rxf_mcast;
	u64 rxf_mcast_vlan;

	u64 rxf_bcast_octets;
	u64 rxf_bcast;
	u64 rxf_bcast_vlan;
पूर्ण __packed;

/* RAD Frame Statistics */
काष्ठा bfi_enet_stats_rad अणु
	u64 rx_frames;
	u64 rx_octets;
	u64 rx_vlan_frames;

	u64 rx_ucast;
	u64 rx_ucast_octets;
	u64 rx_ucast_vlan;

	u64 rx_mcast;
	u64 rx_mcast_octets;
	u64 rx_mcast_vlan;

	u64 rx_bcast;
	u64 rx_bcast_octets;
	u64 rx_bcast_vlan;

	u64 rx_drops;
पूर्ण __packed;

/* BPC Tx Registers */
काष्ठा bfi_enet_stats_bpc अणु
	/* transmit stats */
	u64 tx_छोड़ो[8];
	u64 tx_zero_छोड़ो[8];	/*!< Pause cancellation */
	/*!<Pause initiation rather than retention */
	u64 tx_first_छोड़ो[8];

	/* receive stats */
	u64 rx_छोड़ो[8];
	u64 rx_zero_छोड़ो[8];	/*!< Pause cancellation */
	/*!<Pause initiation rather than retention */
	u64 rx_first_छोड़ो[8];
पूर्ण __packed;

/* MAC Rx Statistics */
काष्ठा bfi_enet_stats_mac अणु
	u64 stats_clr_cnt;	/* बार this stats cleared */
	u64 frame_64;		/* both rx and tx counter */
	u64 frame_65_127;		/* both rx and tx counter */
	u64 frame_128_255;		/* both rx and tx counter */
	u64 frame_256_511;		/* both rx and tx counter */
	u64 frame_512_1023;	/* both rx and tx counter */
	u64 frame_1024_1518;	/* both rx and tx counter */
	u64 frame_1519_1522;	/* both rx and tx counter */

	/* receive stats */
	u64 rx_bytes;
	u64 rx_packets;
	u64 rx_fcs_error;
	u64 rx_multicast;
	u64 rx_broadcast;
	u64 rx_control_frames;
	u64 rx_छोड़ो;
	u64 rx_unknown_opcode;
	u64 rx_alignment_error;
	u64 rx_frame_length_error;
	u64 rx_code_error;
	u64 rx_carrier_sense_error;
	u64 rx_undersize;
	u64 rx_oversize;
	u64 rx_fragments;
	u64 rx_jabber;
	u64 rx_drop;

	/* transmit stats */
	u64 tx_bytes;
	u64 tx_packets;
	u64 tx_multicast;
	u64 tx_broadcast;
	u64 tx_छोड़ो;
	u64 tx_deferral;
	u64 tx_excessive_deferral;
	u64 tx_single_collision;
	u64 tx_muliple_collision;
	u64 tx_late_collision;
	u64 tx_excessive_collision;
	u64 tx_total_collision;
	u64 tx_छोड़ो_honored;
	u64 tx_drop;
	u64 tx_jabber;
	u64 tx_fcs_error;
	u64 tx_control_frame;
	u64 tx_oversize;
	u64 tx_undersize;
	u64 tx_fragments;
पूर्ण __packed;

/* Complete statistics, DMAed from fw to host followed by
 * BFI_ENET_I2H_STATS_GET_RSP
 */
काष्ठा bfi_enet_stats अणु
	काष्ठा bfi_enet_stats_mac	mac_stats;
	काष्ठा bfi_enet_stats_bpc	bpc_stats;
	काष्ठा bfi_enet_stats_rad	rad_stats;
	काष्ठा bfi_enet_stats_rad	rlb_stats;
	काष्ठा bfi_enet_stats_fc_rx	fc_rx_stats;
	काष्ठा bfi_enet_stats_fc_tx	fc_tx_stats;
	काष्ठा bfi_enet_stats_rxf	rxf_stats[BFI_ENET_CFG_MAX];
	काष्ठा bfi_enet_stats_txf	txf_stats[BFI_ENET_CFG_MAX];
पूर्ण __packed;

#पूर्ण_अगर  /* __BFI_ENET_H__ */
