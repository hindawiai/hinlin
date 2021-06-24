<शैली गुरु>
/*
 * Linux driver क्रम VMware's vmxnet3 ethernet NIC.
 *
 * Copyright (C) 2008-2020, VMware, Inc. All Rights Reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; version 2 of the License and no later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or
 * NON INFRINGEMENT.  See the GNU General Public License क्रम more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin St, Fअगरth Floor, Boston, MA 02110-1301 USA.
 *
 * The full GNU General Public License is included in this distribution in
 * the file called "COPYING".
 *
 * Maपूर्णांकained by: pv-drivers@vmware.com
 *
 */

#अगर_अघोषित _VMXNET3_DEFS_H_
#घोषणा _VMXNET3_DEFS_H_

#समावेश "upt1_defs.h"

/* all रेजिस्टरs are 32 bit wide */
/* BAR 1 */
क्रमागत अणु
	VMXNET3_REG_VRRS	= 0x0,	/* Vmxnet3 Revision Report Selection */
	VMXNET3_REG_UVRS	= 0x8,	/* UPT Version Report Selection */
	VMXNET3_REG_DSAL	= 0x10,	/* Driver Shared Address Low */
	VMXNET3_REG_DSAH	= 0x18,	/* Driver Shared Address High */
	VMXNET3_REG_CMD		= 0x20,	/* Command */
	VMXNET3_REG_MACL	= 0x28,	/* MAC Address Low */
	VMXNET3_REG_MACH	= 0x30,	/* MAC Address High */
	VMXNET3_REG_ICR		= 0x38,	/* Interrupt Cause Register */
	VMXNET3_REG_ECR		= 0x40	/* Event Cause Register */
पूर्ण;

/* BAR 0 */
क्रमागत अणु
	VMXNET3_REG_IMR		= 0x0,	 /* Interrupt Mask Register */
	VMXNET3_REG_TXPROD	= 0x600, /* Tx Producer Index */
	VMXNET3_REG_RXPROD	= 0x800, /* Rx Producer Index क्रम ring 1 */
	VMXNET3_REG_RXPROD2	= 0xA00	 /* Rx Producer Index क्रम ring 2 */
पूर्ण;

#घोषणा VMXNET3_PT_REG_SIZE     4096	/* BAR 0 */
#घोषणा VMXNET3_VD_REG_SIZE     4096	/* BAR 1 */

#घोषणा VMXNET3_REG_ALIGN       8	/* All रेजिस्टरs are 8-byte aligned. */
#घोषणा VMXNET3_REG_ALIGN_MASK  0x7

/* I/O Mapped access to रेजिस्टरs */
#घोषणा VMXNET3_IO_TYPE_PT              0
#घोषणा VMXNET3_IO_TYPE_VD              1
#घोषणा VMXNET3_IO_ADDR(type, reg)      (((type) << 24) | ((reg) & 0xFFFFFF))
#घोषणा VMXNET3_IO_TYPE(addr)           ((addr) >> 24)
#घोषणा VMXNET3_IO_REG(addr)            ((addr) & 0xFFFFFF)

क्रमागत अणु
	VMXNET3_CMD_FIRST_SET = 0xCAFE0000,
	VMXNET3_CMD_ACTIVATE_DEV = VMXNET3_CMD_FIRST_SET,
	VMXNET3_CMD_QUIESCE_DEV,
	VMXNET3_CMD_RESET_DEV,
	VMXNET3_CMD_UPDATE_RX_MODE,
	VMXNET3_CMD_UPDATE_MAC_FILTERS,
	VMXNET3_CMD_UPDATE_VLAN_FILTERS,
	VMXNET3_CMD_UPDATE_RSSIDT,
	VMXNET3_CMD_UPDATE_IML,
	VMXNET3_CMD_UPDATE_PMCFG,
	VMXNET3_CMD_UPDATE_FEATURE,
	VMXNET3_CMD_RESERVED1,
	VMXNET3_CMD_LOAD_PLUGIN,
	VMXNET3_CMD_RESERVED2,
	VMXNET3_CMD_RESERVED3,
	VMXNET3_CMD_SET_COALESCE,
	VMXNET3_CMD_REGISTER_MEMREGS,
	VMXNET3_CMD_SET_RSS_FIELDS,

	VMXNET3_CMD_FIRST_GET = 0xF00D0000,
	VMXNET3_CMD_GET_QUEUE_STATUS = VMXNET3_CMD_FIRST_GET,
	VMXNET3_CMD_GET_STATS,
	VMXNET3_CMD_GET_LINK,
	VMXNET3_CMD_GET_PERM_MAC_LO,
	VMXNET3_CMD_GET_PERM_MAC_HI,
	VMXNET3_CMD_GET_DID_LO,
	VMXNET3_CMD_GET_DID_HI,
	VMXNET3_CMD_GET_DEV_EXTRA_INFO,
	VMXNET3_CMD_GET_CONF_INTR,
	VMXNET3_CMD_GET_RESERVED1,
	VMXNET3_CMD_GET_TXDATA_DESC_SIZE,
	VMXNET3_CMD_GET_COALESCE,
	VMXNET3_CMD_GET_RSS_FIELDS,
पूर्ण;

/*
 *	Little Endian layout of bitfields -
 *	Byte 0 :	7.....len.....0
 *	Byte 1 :	oco gen 13.len.8
 *	Byte 2 : 	5.msscof.0 ext1  dtype
 *	Byte 3 : 	13...msscof...6
 *
 *	Big Endian layout of bitfields -
 *	Byte 0:		13...msscof...6
 *	Byte 1 : 	5.msscof.0 ext1  dtype
 *	Byte 2 :	oco gen 13.len.8
 *	Byte 3 :	7.....len.....0
 *
 *	Thus, le32_to_cpu on the dword will allow the big endian driver to पढ़ो
 *	the bit fields correctly. And cpu_to_le32 will convert bitfields
 *	bit fields written by big endian driver to क्रमmat required by device.
 */

काष्ठा Vmxnet3_TxDesc अणु
	__le64 addr;

#अगर_घोषित __BIG_ENDIAN_BITFIELD
	u32 msscof:14;  /* MSS, checksum offset, flags */
	u32 ext1:1;
	u32 dtype:1;    /* descriptor type */
	u32 oco:1;
	u32 gen:1;      /* generation bit */
	u32 len:14;
#अन्यथा
	u32 len:14;
	u32 gen:1;      /* generation bit */
	u32 oco:1;
	u32 dtype:1;    /* descriptor type */
	u32 ext1:1;
	u32 msscof:14;  /* MSS, checksum offset, flags */
#पूर्ण_अगर  /* __BIG_ENDIAN_BITFIELD */

#अगर_घोषित __BIG_ENDIAN_BITFIELD
	u32 tci:16;     /* Tag to Insert */
	u32 ti:1;       /* VLAN Tag Insertion */
	u32 ext2:1;
	u32 cq:1;       /* completion request */
	u32 eop:1;      /* End Of Packet */
	u32 om:2;       /* offload mode */
	u32 hlen:10;    /* header len */
#अन्यथा
	u32 hlen:10;    /* header len */
	u32 om:2;       /* offload mode */
	u32 eop:1;      /* End Of Packet */
	u32 cq:1;       /* completion request */
	u32 ext2:1;
	u32 ti:1;       /* VLAN Tag Insertion */
	u32 tci:16;     /* Tag to Insert */
#पूर्ण_अगर  /* __BIG_ENDIAN_BITFIELD */
पूर्ण;

/* TxDesc.OM values */
#घोषणा VMXNET3_OM_NONE         0
#घोषणा VMXNET3_OM_ENCAP        1
#घोषणा VMXNET3_OM_CSUM         2
#घोषणा VMXNET3_OM_TSO          3

/* fields in TxDesc we access w/o using bit fields */
#घोषणा VMXNET3_TXD_EOP_SHIFT	12
#घोषणा VMXNET3_TXD_CQ_SHIFT	13
#घोषणा VMXNET3_TXD_GEN_SHIFT	14
#घोषणा VMXNET3_TXD_EOP_DWORD_SHIFT 3
#घोषणा VMXNET3_TXD_GEN_DWORD_SHIFT 2

#घोषणा VMXNET3_TXD_CQ		(1 << VMXNET3_TXD_CQ_SHIFT)
#घोषणा VMXNET3_TXD_EOP		(1 << VMXNET3_TXD_EOP_SHIFT)
#घोषणा VMXNET3_TXD_GEN		(1 << VMXNET3_TXD_GEN_SHIFT)

#घोषणा VMXNET3_HDR_COPY_SIZE   128


काष्ठा Vmxnet3_TxDataDesc अणु
	u8		data[VMXNET3_HDR_COPY_SIZE];
पूर्ण;

प्रकार u8 Vmxnet3_RxDataDesc;

#घोषणा VMXNET3_TCD_GEN_SHIFT	31
#घोषणा VMXNET3_TCD_GEN_SIZE	1
#घोषणा VMXNET3_TCD_TXIDX_SHIFT	0
#घोषणा VMXNET3_TCD_TXIDX_SIZE	12
#घोषणा VMXNET3_TCD_GEN_DWORD_SHIFT	3

काष्ठा Vmxnet3_TxCompDesc अणु
	u32		txdIdx:12;    /* Index of the EOP TxDesc */
	u32		ext1:20;

	__le32		ext2;
	__le32		ext3;

	u32		rsvd:24;
	u32		type:7;       /* completion type */
	u32		gen:1;        /* generation bit */
पूर्ण;

काष्ठा Vmxnet3_RxDesc अणु
	__le64		addr;

#अगर_घोषित __BIG_ENDIAN_BITFIELD
	u32		gen:1;        /* Generation bit */
	u32		rsvd:15;
	u32		dtype:1;      /* Descriptor type */
	u32		btype:1;      /* Buffer Type */
	u32		len:14;
#अन्यथा
	u32		len:14;
	u32		btype:1;      /* Buffer Type */
	u32		dtype:1;      /* Descriptor type */
	u32		rsvd:15;
	u32		gen:1;        /* Generation bit */
#पूर्ण_अगर
	u32		ext1;
पूर्ण;

/* values of RXD.BTYPE */
#घोषणा VMXNET3_RXD_BTYPE_HEAD   0    /* head only */
#घोषणा VMXNET3_RXD_BTYPE_BODY   1    /* body only */

/* fields in RxDesc we access w/o using bit fields */
#घोषणा VMXNET3_RXD_BTYPE_SHIFT  14
#घोषणा VMXNET3_RXD_GEN_SHIFT    31

#घोषणा VMXNET3_RCD_HDR_INNER_SHIFT  13

काष्ठा Vmxnet3_RxCompDesc अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
	u32		ext2:1;
	u32		cnc:1;        /* Checksum Not Calculated */
	u32		rssType:4;    /* RSS hash type used */
	u32		rqID:10;      /* rx queue/ring ID */
	u32		sop:1;        /* Start of Packet */
	u32		eop:1;        /* End of Packet */
	u32		ext1:2;
	u32		rxdIdx:12;    /* Index of the RxDesc */
#अन्यथा
	u32		rxdIdx:12;    /* Index of the RxDesc */
	u32		ext1:2;
	u32		eop:1;        /* End of Packet */
	u32		sop:1;        /* Start of Packet */
	u32		rqID:10;      /* rx queue/ring ID */
	u32		rssType:4;    /* RSS hash type used */
	u32		cnc:1;        /* Checksum Not Calculated */
	u32		ext2:1;
#पूर्ण_अगर  /* __BIG_ENDIAN_BITFIELD */

	__le32		rssHash;      /* RSS hash value */

#अगर_घोषित __BIG_ENDIAN_BITFIELD
	u32		tci:16;       /* Tag stripped */
	u32		ts:1;         /* Tag is stripped */
	u32		err:1;        /* Error */
	u32		len:14;       /* data length */
#अन्यथा
	u32		len:14;       /* data length */
	u32		err:1;        /* Error */
	u32		ts:1;         /* Tag is stripped */
	u32		tci:16;       /* Tag stripped */
#पूर्ण_अगर  /* __BIG_ENDIAN_BITFIELD */


#अगर_घोषित __BIG_ENDIAN_BITFIELD
	u32		gen:1;        /* generation bit */
	u32		type:7;       /* completion type */
	u32		fcs:1;        /* Frame CRC correct */
	u32		frg:1;        /* IP Fragment */
	u32		v4:1;         /* IPv4 */
	u32		v6:1;         /* IPv6 */
	u32		ipc:1;        /* IP Checksum Correct */
	u32		tcp:1;        /* TCP packet */
	u32		udp:1;        /* UDP packet */
	u32		tuc:1;        /* TCP/UDP Checksum Correct */
	u32		csum:16;
#अन्यथा
	u32		csum:16;
	u32		tuc:1;        /* TCP/UDP Checksum Correct */
	u32		udp:1;        /* UDP packet */
	u32		tcp:1;        /* TCP packet */
	u32		ipc:1;        /* IP Checksum Correct */
	u32		v6:1;         /* IPv6 */
	u32		v4:1;         /* IPv4 */
	u32		frg:1;        /* IP Fragment */
	u32		fcs:1;        /* Frame CRC correct */
	u32		type:7;       /* completion type */
	u32		gen:1;        /* generation bit */
#पूर्ण_अगर  /* __BIG_ENDIAN_BITFIELD */
पूर्ण;

काष्ठा Vmxnet3_RxCompDescExt अणु
	__le32		dword1;
	u8		segCnt;       /* Number of aggregated packets */
	u8		dupAckCnt;    /* Number of duplicate Acks */
	__le16		tsDelta;      /* TCP बारtamp dअगरference */
	__le32		dword2;
#अगर_घोषित __BIG_ENDIAN_BITFIELD
	u32		gen:1;        /* generation bit */
	u32		type:7;       /* completion type */
	u32		fcs:1;        /* Frame CRC correct */
	u32		frg:1;        /* IP Fragment */
	u32		v4:1;         /* IPv4 */
	u32		v6:1;         /* IPv6 */
	u32		ipc:1;        /* IP Checksum Correct */
	u32		tcp:1;        /* TCP packet */
	u32		udp:1;        /* UDP packet */
	u32		tuc:1;        /* TCP/UDP Checksum Correct */
	u32		mss:16;
#अन्यथा
	u32		mss:16;
	u32		tuc:1;        /* TCP/UDP Checksum Correct */
	u32		udp:1;        /* UDP packet */
	u32		tcp:1;        /* TCP packet */
	u32		ipc:1;        /* IP Checksum Correct */
	u32		v6:1;         /* IPv6 */
	u32		v4:1;         /* IPv4 */
	u32		frg:1;        /* IP Fragment */
	u32		fcs:1;        /* Frame CRC correct */
	u32		type:7;       /* completion type */
	u32		gen:1;        /* generation bit */
#पूर्ण_अगर  /* __BIG_ENDIAN_BITFIELD */
पूर्ण;


/* fields in RxCompDesc we access via Vmxnet3_GenericDesc.dword[3] */
#घोषणा VMXNET3_RCD_TUC_SHIFT	16
#घोषणा VMXNET3_RCD_IPC_SHIFT	19

/* fields in RxCompDesc we access via Vmxnet3_GenericDesc.qword[1] */
#घोषणा VMXNET3_RCD_TYPE_SHIFT	56
#घोषणा VMXNET3_RCD_GEN_SHIFT	63

/* csum OK क्रम TCP/UDP pkts over IP */
#घोषणा VMXNET3_RCD_CSUM_OK (1 << VMXNET3_RCD_TUC_SHIFT | \
			     1 << VMXNET3_RCD_IPC_SHIFT)
#घोषणा VMXNET3_TXD_GEN_SIZE 1
#घोषणा VMXNET3_TXD_EOP_SIZE 1

/* value of RxCompDesc.rssType */
क्रमागत अणु
	VMXNET3_RCD_RSS_TYPE_NONE     = 0,
	VMXNET3_RCD_RSS_TYPE_IPV4     = 1,
	VMXNET3_RCD_RSS_TYPE_TCPIPV4  = 2,
	VMXNET3_RCD_RSS_TYPE_IPV6     = 3,
	VMXNET3_RCD_RSS_TYPE_TCPIPV6  = 4,
पूर्ण;


/* a जोड़ क्रम accessing all cmd/completion descriptors */
जोड़ Vmxnet3_GenericDesc अणु
	__le64				qword[2];
	__le32				dword[4];
	__le16				word[8];
	काष्ठा Vmxnet3_TxDesc		txd;
	काष्ठा Vmxnet3_RxDesc		rxd;
	काष्ठा Vmxnet3_TxCompDesc	tcd;
	काष्ठा Vmxnet3_RxCompDesc	rcd;
	काष्ठा Vmxnet3_RxCompDescExt 	rcdExt;
पूर्ण;

#घोषणा VMXNET3_INIT_GEN       1

/* Max size of a single tx buffer */
#घोषणा VMXNET3_MAX_TX_BUF_SIZE  (1 << 14)

/* # of tx desc needed क्रम a tx buffer size */
#घोषणा VMXNET3_TXD_NEEDED(size) (((size) + VMXNET3_MAX_TX_BUF_SIZE - 1) / \
				  VMXNET3_MAX_TX_BUF_SIZE)

/* max # of tx descs क्रम a non-tso pkt */
#घोषणा VMXNET3_MAX_TXD_PER_PKT 16

/* Max size of a single rx buffer */
#घोषणा VMXNET3_MAX_RX_BUF_SIZE  ((1 << 14) - 1)
/* Minimum size of a type 0 buffer */
#घोषणा VMXNET3_MIN_T0_BUF_SIZE  128
#घोषणा VMXNET3_MAX_CSUM_OFFSET  1024

/* Ring base address alignment */
#घोषणा VMXNET3_RING_BA_ALIGN   512
#घोषणा VMXNET3_RING_BA_MASK    (VMXNET3_RING_BA_ALIGN - 1)

/* Ring size must be a multiple of 32 */
#घोषणा VMXNET3_RING_SIZE_ALIGN 32
#घोषणा VMXNET3_RING_SIZE_MASK  (VMXNET3_RING_SIZE_ALIGN - 1)

/* Tx Data Ring buffer size must be a multiple of 64 */
#घोषणा VMXNET3_TXDATA_DESC_SIZE_ALIGN 64
#घोषणा VMXNET3_TXDATA_DESC_SIZE_MASK  (VMXNET3_TXDATA_DESC_SIZE_ALIGN - 1)

/* Rx Data Ring buffer size must be a multiple of 64 */
#घोषणा VMXNET3_RXDATA_DESC_SIZE_ALIGN 64
#घोषणा VMXNET3_RXDATA_DESC_SIZE_MASK  (VMXNET3_RXDATA_DESC_SIZE_ALIGN - 1)

/* Max ring size */
#घोषणा VMXNET3_TX_RING_MAX_SIZE   4096
#घोषणा VMXNET3_TC_RING_MAX_SIZE   4096
#घोषणा VMXNET3_RX_RING_MAX_SIZE   4096
#घोषणा VMXNET3_RX_RING2_MAX_SIZE  4096
#घोषणा VMXNET3_RC_RING_MAX_SIZE   8192

#घोषणा VMXNET3_TXDATA_DESC_MIN_SIZE 128
#घोषणा VMXNET3_TXDATA_DESC_MAX_SIZE 2048

#घोषणा VMXNET3_RXDATA_DESC_MAX_SIZE 2048

/* a list of reasons क्रम queue stop */

क्रमागत अणु
 VMXNET3_ERR_NOEOP        = 0x80000000,  /* cannot find the EOP desc of a pkt */
 VMXNET3_ERR_TXD_REUSE    = 0x80000001,  /* reuse TxDesc beक्रमe tx completion */
 VMXNET3_ERR_BIG_PKT      = 0x80000002,  /* too many TxDesc क्रम a pkt */
 VMXNET3_ERR_DESC_NOT_SPT = 0x80000003,  /* descriptor type not supported */
 VMXNET3_ERR_SMALL_BUF    = 0x80000004,  /* type 0 buffer too small */
 VMXNET3_ERR_STRESS       = 0x80000005,  /* stress option firing in vmkernel */
 VMXNET3_ERR_SWITCH       = 0x80000006,  /* mode चयन failure */
 VMXNET3_ERR_TXD_INVALID  = 0x80000007,  /* invalid TxDesc */
पूर्ण;

/* completion descriptor types */
#घोषणा VMXNET3_CDTYPE_TXCOMP      0    /* Tx Completion Descriptor */
#घोषणा VMXNET3_CDTYPE_RXCOMP      3    /* Rx Completion Descriptor */
#घोषणा VMXNET3_CDTYPE_RXCOMP_LRO  4    /* Rx Completion Descriptor क्रम LRO */

क्रमागत अणु
	VMXNET3_GOS_BITS_UNK    = 0,   /* unknown */
	VMXNET3_GOS_BITS_32     = 1,
	VMXNET3_GOS_BITS_64     = 2,
पूर्ण;

#घोषणा VMXNET3_GOS_TYPE_LINUX	1


काष्ठा Vmxnet3_GOSInfo अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
	u32		gosMisc:10;    /* other info about gos */
	u32		gosVer:16;     /* gos version */
	u32		gosType:4;     /* which guest */
	u32		gosBits:2;    /* 32-bit or 64-bit? */
#अन्यथा
	u32		gosBits:2;     /* 32-bit or 64-bit? */
	u32		gosType:4;     /* which guest */
	u32		gosVer:16;     /* gos version */
	u32		gosMisc:10;    /* other info about gos */
#पूर्ण_अगर  /* __BIG_ENDIAN_BITFIELD */
पूर्ण;

काष्ठा Vmxnet3_DriverInfo अणु
	__le32				version;
	काष्ठा Vmxnet3_GOSInfo		gos;
	__le32				vmxnet3RevSpt;
	__le32				uptVerSpt;
पूर्ण;


#घोषणा VMXNET3_REV1_MAGIC  3133079265u

/*
 * QueueDescPA must be 128 bytes aligned. It poपूर्णांकs to an array of
 * Vmxnet3_TxQueueDesc followed by an array of Vmxnet3_RxQueueDesc.
 * The number of Vmxnet3_TxQueueDesc/Vmxnet3_RxQueueDesc are specअगरied by
 * Vmxnet3_MiscConf.numTxQueues/numRxQueues, respectively.
 */
#घोषणा VMXNET3_QUEUE_DESC_ALIGN  128


काष्ठा Vmxnet3_MiscConf अणु
	काष्ठा Vmxnet3_DriverInfo driverInfo;
	__le64		uptFeatures;
	__le64		ddPA;         /* driver data PA */
	__le64		queueDescPA;  /* queue descriptor table PA */
	__le32		ddLen;        /* driver data len */
	__le32		queueDescLen; /* queue desc. table len in bytes */
	__le32		mtu;
	__le16		maxNumRxSG;
	u8		numTxQueues;
	u8		numRxQueues;
	__le32		reserved[4];
पूर्ण;


काष्ठा Vmxnet3_TxQueueConf अणु
	__le64		txRingBasePA;
	__le64		dataRingBasePA;
	__le64		compRingBasePA;
	__le64		ddPA;         /* driver data */
	__le64		reserved;
	__le32		txRingSize;   /* # of tx desc */
	__le32		dataRingSize; /* # of data desc */
	__le32		compRingSize; /* # of comp desc */
	__le32		ddLen;        /* size of driver data */
	u8		पूर्णांकrIdx;
	u8		_pad1[1];
	__le16		txDataRingDescSize;
	u8		_pad2[4];
पूर्ण;


काष्ठा Vmxnet3_RxQueueConf अणु
	__le64		rxRingBasePA[2];
	__le64		compRingBasePA;
	__le64		ddPA;            /* driver data */
	__le64		rxDataRingBasePA;
	__le32		rxRingSize[2];   /* # of rx desc */
	__le32		compRingSize;    /* # of rx comp desc */
	__le32		ddLen;           /* size of driver data */
	u8		पूर्णांकrIdx;
	u8		_pad1[1];
	__le16		rxDataRingDescSize;  /* size of rx data ring buffer */
	u8		_pad2[4];
पूर्ण;


क्रमागत vmxnet3_पूर्णांकr_mask_mode अणु
	VMXNET3_IMM_AUTO   = 0,
	VMXNET3_IMM_ACTIVE = 1,
	VMXNET3_IMM_LAZY   = 2
पूर्ण;

क्रमागत vmxnet3_पूर्णांकr_type अणु
	VMXNET3_IT_AUTO = 0,
	VMXNET3_IT_INTX = 1,
	VMXNET3_IT_MSI  = 2,
	VMXNET3_IT_MSIX = 3
पूर्ण;

#घोषणा VMXNET3_MAX_TX_QUEUES  8
#घोषणा VMXNET3_MAX_RX_QUEUES  16
/* addition 1 क्रम events */
#घोषणा VMXNET3_MAX_INTRS      25

/* value of पूर्णांकrCtrl */
#घोषणा VMXNET3_IC_DISABLE_ALL  0x1   /* bit 0 */


काष्ठा Vmxnet3_IntrConf अणु
	bool		स्वतःMask;
	u8		numIntrs;      /* # of पूर्णांकerrupts */
	u8		eventIntrIdx;
	u8		modLevels[VMXNET3_MAX_INTRS];	/* moderation level क्रम
							 * each पूर्णांकr */
	__le32		पूर्णांकrCtrl;
	__le32		reserved[2];
पूर्ण;

/* one bit per VLAN ID, the size is in the units of u32	*/
#घोषणा VMXNET3_VFT_SIZE  (4096 / (माप(u32) * 8))


काष्ठा Vmxnet3_QueueStatus अणु
	bool		stopped;
	u8		_pad[3];
	__le32		error;
पूर्ण;


काष्ठा Vmxnet3_TxQueueCtrl अणु
	__le32		txNumDeferred;
	__le32		txThreshold;
	__le64		reserved;
पूर्ण;


काष्ठा Vmxnet3_RxQueueCtrl अणु
	bool		updateRxProd;
	u8		_pad[7];
	__le64		reserved;
पूर्ण;

क्रमागत अणु
	VMXNET3_RXM_UCAST     = 0x01,  /* unicast only */
	VMXNET3_RXM_MCAST     = 0x02,  /* multicast passing the filters */
	VMXNET3_RXM_BCAST     = 0x04,  /* broadcast only */
	VMXNET3_RXM_ALL_MULTI = 0x08,  /* all multicast */
	VMXNET3_RXM_PROMISC   = 0x10  /* promiscuous */
पूर्ण;

काष्ठा Vmxnet3_RxFilterConf अणु
	__le32		rxMode;       /* VMXNET3_RXM_xxx */
	__le16		mfTableLen;   /* size of the multicast filter table */
	__le16		_pad1;
	__le64		mfTablePA;    /* PA of the multicast filters table */
	__le32		vfTable[VMXNET3_VFT_SIZE]; /* vlan filter */
पूर्ण;


#घोषणा VMXNET3_PM_MAX_FILTERS        6
#घोषणा VMXNET3_PM_MAX_PATTERN_SIZE   128
#घोषणा VMXNET3_PM_MAX_MASK_SIZE      (VMXNET3_PM_MAX_PATTERN_SIZE / 8)

#घोषणा VMXNET3_PM_WAKEUP_MAGIC       cpu_to_le16(0x01)  /* wake up on magic pkts */
#घोषणा VMXNET3_PM_WAKEUP_FILTER      cpu_to_le16(0x02)  /* wake up on pkts matching
							  * filters */


काष्ठा Vmxnet3_PM_PktFilter अणु
	u8		maskSize;
	u8		patternSize;
	u8		mask[VMXNET3_PM_MAX_MASK_SIZE];
	u8		pattern[VMXNET3_PM_MAX_PATTERN_SIZE];
	u8		pad[6];
पूर्ण;


काष्ठा Vmxnet3_PMConf अणु
	__le16		wakeUpEvents;  /* VMXNET3_PM_WAKEUP_xxx */
	u8		numFilters;
	u8		pad[5];
	काष्ठा Vmxnet3_PM_PktFilter filters[VMXNET3_PM_MAX_FILTERS];
पूर्ण;


काष्ठा Vmxnet3_VariableLenConfDesc अणु
	__le32		confVer;
	__le32		confLen;
	__le64		confPA;
पूर्ण;


काष्ठा Vmxnet3_TxQueueDesc अणु
	काष्ठा Vmxnet3_TxQueueCtrl		ctrl;
	काष्ठा Vmxnet3_TxQueueConf		conf;

	/* Driver पढ़ो after a GET command */
	काष्ठा Vmxnet3_QueueStatus		status;
	काष्ठा UPT1_TxStats			stats;
	u8					_pad[88]; /* 128 aligned */
पूर्ण;


काष्ठा Vmxnet3_RxQueueDesc अणु
	काष्ठा Vmxnet3_RxQueueCtrl		ctrl;
	काष्ठा Vmxnet3_RxQueueConf		conf;
	/* Driver पढ़ो after a GET commad */
	काष्ठा Vmxnet3_QueueStatus		status;
	काष्ठा UPT1_RxStats			stats;
	u8				      __pad[88]; /* 128 aligned */
पूर्ण;

काष्ठा Vmxnet3_SetPolling अणु
	u8					enablePolling;
पूर्ण;

#घोषणा VMXNET3_COAL_STATIC_MAX_DEPTH		128
#घोषणा VMXNET3_COAL_RBC_MIN_RATE		100
#घोषणा VMXNET3_COAL_RBC_MAX_RATE		100000

क्रमागत Vmxnet3_CoalesceMode अणु
	VMXNET3_COALESCE_DISABLED   = 0,
	VMXNET3_COALESCE_ADAPT      = 1,
	VMXNET3_COALESCE_STATIC     = 2,
	VMXNET3_COALESCE_RBC        = 3
पूर्ण;

काष्ठा Vmxnet3_CoalesceRbc अणु
	u32					rbc_rate;
पूर्ण;

काष्ठा Vmxnet3_CoalesceStatic अणु
	u32					tx_depth;
	u32					tx_comp_depth;
	u32					rx_depth;
पूर्ण;

काष्ठा Vmxnet3_CoalesceScheme अणु
	क्रमागत Vmxnet3_CoalesceMode		coalMode;
	जोड़ अणु
		काष्ठा Vmxnet3_CoalesceRbc	coalRbc;
		काष्ठा Vmxnet3_CoalesceStatic	coalStatic;
	पूर्ण coalPara;
पूर्ण;

काष्ठा Vmxnet3_MemoryRegion अणु
	__le64					startPA;
	__le32					length;
	__le16					txQueueBits;
	__le16					rxQueueBits;
पूर्ण;

#घोषणा MAX_MEMORY_REGION_PER_QUEUE 16
#घोषणा MAX_MEMORY_REGION_PER_DEVICE 256

काष्ठा Vmxnet3_MemRegs अणु
	__le16					numRegs;
	__le16					pad[3];
	काष्ठा Vmxnet3_MemoryRegion		memRegs[1];
पूर्ण;

क्रमागत Vmxnet3_RSSField अणु
	VMXNET3_RSS_FIELDS_TCPIP4 = 0x0001,
	VMXNET3_RSS_FIELDS_TCPIP6 = 0x0002,
	VMXNET3_RSS_FIELDS_UDPIP4 = 0x0004,
	VMXNET3_RSS_FIELDS_UDPIP6 = 0x0008,
	VMXNET3_RSS_FIELDS_ESPIP4 = 0x0010,
	VMXNET3_RSS_FIELDS_ESPIP6 = 0x0020,
पूर्ण;

/* If the command data <= 16 bytes, use the shared memory directly.
 * otherwise, use variable length configuration descriptor.
 */
जोड़ Vmxnet3_CmdInfo अणु
	काष्ठा Vmxnet3_VariableLenConfDesc	varConf;
	काष्ठा Vmxnet3_SetPolling		setPolling;
	क्रमागत   Vmxnet3_RSSField                 setRssFields;
	__le64					data[2];
पूर्ण;

काष्ठा Vmxnet3_DSDevRead अणु
	/* पढ़ो-only region क्रम device, पढ़ो by dev in response to a SET cmd */
	काष्ठा Vmxnet3_MiscConf			misc;
	काष्ठा Vmxnet3_IntrConf			पूर्णांकrConf;
	काष्ठा Vmxnet3_RxFilterConf		rxFilterConf;
	काष्ठा Vmxnet3_VariableLenConfDesc	rssConfDesc;
	काष्ठा Vmxnet3_VariableLenConfDesc	pmConfDesc;
	काष्ठा Vmxnet3_VariableLenConfDesc	pluginConfDesc;
पूर्ण;

/* All काष्ठाures in DriverShared are padded to multiples of 8 bytes */
काष्ठा Vmxnet3_DriverShared अणु
	__le32				magic;
	/* make devRead start at 64bit boundaries */
	__le32				pad;
	काष्ठा Vmxnet3_DSDevRead	devRead;
	__le32				ecr;
	__le32				reserved;
	जोड़ अणु
		__le32			reserved1[4];
		जोड़ Vmxnet3_CmdInfo	cmdInfo; /* only valid in the context of
						  * executing the relevant
						  * command
						  */
	पूर्ण cu;
पूर्ण;


#घोषणा VMXNET3_ECR_RQERR       (1 << 0)
#घोषणा VMXNET3_ECR_TQERR       (1 << 1)
#घोषणा VMXNET3_ECR_LINK        (1 << 2)
#घोषणा VMXNET3_ECR_DIC         (1 << 3)
#घोषणा VMXNET3_ECR_DEBUG       (1 << 4)

/* flip the gen bit of a ring */
#घोषणा VMXNET3_FLIP_RING_GEN(gen) ((gen) = (gen) ^ 0x1)

/* only use this अगर moving the idx won't affect the gen bit */
#घोषणा VMXNET3_INC_RING_IDX_ONLY(idx, ring_size) \
	करो अणु\
		(idx)++;\
		अगर (unlikely((idx) == (ring_size))) अणु\
			(idx) = 0;\
		पूर्ण \
	पूर्ण जबतक (0)

#घोषणा VMXNET3_SET_VFTABLE_ENTRY(vfTable, vid) \
	(vfTable[vid >> 5] |= (1 << (vid & 31)))
#घोषणा VMXNET3_CLEAR_VFTABLE_ENTRY(vfTable, vid) \
	(vfTable[vid >> 5] &= ~(1 << (vid & 31)))

#घोषणा VMXNET3_VFTABLE_ENTRY_IS_SET(vfTable, vid) \
	((vfTable[vid >> 5] & (1 << (vid & 31))) != 0)

#घोषणा VMXNET3_MAX_MTU     9000
#घोषणा VMXNET3_MIN_MTU     60

#घोषणा VMXNET3_LINK_UP         (10000 << 16 | 1)    /* 10 Gbps, up */
#घोषणा VMXNET3_LINK_DOWN       0

#पूर्ण_अगर /* _VMXNET3_DEFS_H_ */
