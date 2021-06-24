<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2003 - 2009 NetXen, Inc.
 * Copyright (C) 2009 - QLogic Corporation.
 * All rights reserved.
 */

#अगर_अघोषित _NETXEN_NIC_H_
#घोषणा _NETXEN_NIC_H_

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/ioport.h>
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ip.h>
#समावेश <linux/in.h>
#समावेश <linux/tcp.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/firmware.h>

#समावेश <linux/ethtool.h>
#समावेश <linux/mii.h>
#समावेश <linux/समयr.h>

#समावेश <linux/vदो_स्मृति.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/byteorder.h>

#समावेश "netxen_nic_hdr.h"
#समावेश "netxen_nic_hw.h"

#घोषणा _NETXEN_NIC_LINUX_MAJOR 4
#घोषणा _NETXEN_NIC_LINUX_MINOR 0
#घोषणा _NETXEN_NIC_LINUX_SUBVERSION 82
#घोषणा NETXEN_NIC_LINUX_VERSIONID  "4.0.82"

#घोषणा NETXEN_VERSION_CODE(a, b, c)	(((a) << 24) + ((b) << 16) + (c))
#घोषणा _major(v)	(((v) >> 24) & 0xff)
#घोषणा _minor(v)	(((v) >> 16) & 0xff)
#घोषणा _build(v)	((v) & 0xffff)

/* version in image has weird encoding:
 *  7:0  - major
 * 15:8  - minor
 * 31:16 - build (little endian)
 */
#घोषणा NETXEN_DECODE_VERSION(v) \
	NETXEN_VERSION_CODE(((v) & 0xff), (((v) >> 8) & 0xff), ((v) >> 16))

#घोषणा NETXEN_NUM_FLASH_SECTORS (64)
#घोषणा NETXEN_FLASH_SECTOR_SIZE (64 * 1024)
#घोषणा NETXEN_FLASH_TOTAL_SIZE  (NETXEN_NUM_FLASH_SECTORS \
					* NETXEN_FLASH_SECTOR_SIZE)

#घोषणा RCV_DESC_RINGSIZE(rds_ring)	\
	(माप(काष्ठा rcv_desc) * (rds_ring)->num_desc)
#घोषणा RCV_BUFF_RINGSIZE(rds_ring)	\
	(माप(काष्ठा netxen_rx_buffer) * rds_ring->num_desc)
#घोषणा STATUS_DESC_RINGSIZE(sds_ring)	\
	(माप(काष्ठा status_desc) * (sds_ring)->num_desc)
#घोषणा TX_BUFF_RINGSIZE(tx_ring)	\
	(माप(काष्ठा netxen_cmd_buffer) * tx_ring->num_desc)
#घोषणा TX_DESC_RINGSIZE(tx_ring)	\
	(माप(काष्ठा cmd_desc_type0) * tx_ring->num_desc)

#घोषणा find_dअगरf_among(a,b,range) ((a)<(b)?((b)-(a)):((b)+(range)-(a)))

#घोषणा NETXEN_RCV_PRODUCER_OFFSET	0
#घोषणा NETXEN_RCV_PEG_DB_ID		2
#घोषणा NETXEN_HOST_DUMMY_DMA_SIZE 1024
#घोषणा FLASH_SUCCESS 0

#घोषणा ADDR_IN_WINDOW1(off)	\
	((off > NETXEN_CRB_PCIX_HOST2) && (off < NETXEN_CRB_MAX)) ? 1 : 0

#घोषणा ADDR_IN_RANGE(addr, low, high)	\
	(((addr) < (high)) && ((addr) >= (low)))

/*
 * normalize a 64MB crb address to 32MB PCI winकरोw
 * To use NETXEN_CRB_NORMALIZE, winकरोw _must_ be set to 1
 */
#घोषणा NETXEN_CRB_NORMAL(reg)	\
	((reg) - NETXEN_CRB_PCIX_HOST2 + NETXEN_CRB_PCIX_HOST)

#घोषणा NETXEN_CRB_NORMALIZE(adapter, reg) \
	pci_base_offset(adapter, NETXEN_CRB_NORMAL(reg))

#घोषणा DB_NORMALIZE(adapter, off) \
	(adapter->ahw.db_base + (off))

#घोषणा NX_P2_C0		0x24
#घोषणा NX_P2_C1		0x25
#घोषणा NX_P3_A0		0x30
#घोषणा NX_P3_A2		0x30
#घोषणा NX_P3_B0		0x40
#घोषणा NX_P3_B1		0x41
#घोषणा NX_P3_B2		0x42
#घोषणा NX_P3P_A0		0x50

#घोषणा NX_IS_REVISION_P2(REVISION)     (REVISION <= NX_P2_C1)
#घोषणा NX_IS_REVISION_P3(REVISION)     (REVISION >= NX_P3_A0)
#घोषणा NX_IS_REVISION_P3P(REVISION)     (REVISION >= NX_P3P_A0)

#घोषणा FIRST_PAGE_GROUP_START	0
#घोषणा FIRST_PAGE_GROUP_END	0x100000

#घोषणा SECOND_PAGE_GROUP_START	0x6000000
#घोषणा SECOND_PAGE_GROUP_END	0x68BC000

#घोषणा THIRD_PAGE_GROUP_START	0x70E4000
#घोषणा THIRD_PAGE_GROUP_END	0x8000000

#घोषणा FIRST_PAGE_GROUP_SIZE  FIRST_PAGE_GROUP_END - FIRST_PAGE_GROUP_START
#घोषणा SECOND_PAGE_GROUP_SIZE SECOND_PAGE_GROUP_END - SECOND_PAGE_GROUP_START
#घोषणा THIRD_PAGE_GROUP_SIZE  THIRD_PAGE_GROUP_END - THIRD_PAGE_GROUP_START

#घोषणा P2_MAX_MTU                     (8000)
#घोषणा P3_MAX_MTU                     (9600)
#घोषणा NX_ETHERMTU                    1500
#घोषणा NX_MAX_ETHERHDR                32 /* This contains some padding */

#घोषणा NX_P2_RX_BUF_MAX_LEN           1760
#घोषणा NX_P3_RX_BUF_MAX_LEN           (NX_MAX_ETHERHDR + NX_ETHERMTU)
#घोषणा NX_P2_RX_JUMBO_BUF_MAX_LEN     (NX_MAX_ETHERHDR + P2_MAX_MTU)
#घोषणा NX_P3_RX_JUMBO_BUF_MAX_LEN     (NX_MAX_ETHERHDR + P3_MAX_MTU)
#घोषणा NX_CT_DEFAULT_RX_BUF_LEN	2048
#घोषणा NX_LRO_BUFFER_EXTRA		2048

#घोषणा NX_RX_LRO_BUFFER_LENGTH		(8060)

/*
 * Maximum number of ring contexts
 */
#घोषणा MAX_RING_CTX 1

/* Opcodes to be used with the commands */
#घोषणा TX_ETHER_PKT	0x01
#घोषणा TX_TCP_PKT	0x02
#घोषणा TX_UDP_PKT	0x03
#घोषणा TX_IP_PKT	0x04
#घोषणा TX_TCP_LSO	0x05
#घोषणा TX_TCP_LSO6	0x06
#घोषणा TX_IPSEC	0x07
#घोषणा TX_IPSEC_CMD	0x0a
#घोषणा TX_TCPV6_PKT	0x0b
#घोषणा TX_UDPV6_PKT	0x0c

/* The following opcodes are क्रम पूर्णांकernal consumption. */
#घोषणा NETXEN_CONTROL_OP	0x10
#घोषणा PEGNET_REQUEST		0x11

#घोषणा	MAX_NUM_CARDS		4

#घोषणा NETXEN_MAX_FRAGS_PER_TX	14
#घोषणा MAX_TSO_HEADER_DESC	2
#घोषणा MGMT_CMD_DESC_RESV	4
#घोषणा TX_STOP_THRESH		((MAX_SKB_FRAGS >> 2) + MAX_TSO_HEADER_DESC \
							+ MGMT_CMD_DESC_RESV)
#घोषणा NX_MAX_TX_TIMEOUTS	2

/*
 * Following are the states of the Phantom. Phantom will set them and
 * Host will पढ़ो to check अगर the fields are correct.
 */
#घोषणा PHAN_INITIALIZE_START		0xff00
#घोषणा PHAN_INITIALIZE_FAILED		0xffff
#घोषणा PHAN_INITIALIZE_COMPLETE	0xff01

/* Host ग_लिखोs the following to notअगरy that it has करोne the init-handshake */
#घोषणा PHAN_INITIALIZE_ACK	0xf00f

#घोषणा NUM_RCV_DESC_RINGS	3
#घोषणा NUM_STS_DESC_RINGS	4

#घोषणा RCV_RING_NORMAL	0
#घोषणा RCV_RING_JUMBO	1
#घोषणा RCV_RING_LRO	2

#घोषणा MIN_CMD_DESCRIPTORS		64
#घोषणा MIN_RCV_DESCRIPTORS		64
#घोषणा MIN_JUMBO_DESCRIPTORS		32

#घोषणा MAX_CMD_DESCRIPTORS		1024
#घोषणा MAX_RCV_DESCRIPTORS_1G		4096
#घोषणा MAX_RCV_DESCRIPTORS_10G		8192
#घोषणा MAX_JUMBO_RCV_DESCRIPTORS_1G	512
#घोषणा MAX_JUMBO_RCV_DESCRIPTORS_10G	1024
#घोषणा MAX_LRO_RCV_DESCRIPTORS		8

#घोषणा DEFAULT_RCV_DESCRIPTORS_1G	2048
#घोषणा DEFAULT_RCV_DESCRIPTORS_10G	4096

#घोषणा NETXEN_CTX_SIGNATURE	0xdee0
#घोषणा NETXEN_CTX_SIGNATURE_V2	0x0002dee0
#घोषणा NETXEN_CTX_RESET	0xbad0
#घोषणा NETXEN_CTX_D3_RESET	0xacc0
#घोषणा NETXEN_RCV_PRODUCER(ringid)	(ringid)

#घोषणा PHAN_PEG_RCV_INITIALIZED	0xff01
#घोषणा PHAN_PEG_RCV_START_INITIALIZE	0xff00

#घोषणा get_next_index(index, length)	\
	(((index) + 1) & ((length) - 1))

#घोषणा get_index_range(index,length,count)	\
	(((index) + (count)) & ((length) - 1))

#घोषणा MPORT_SINGLE_FUNCTION_MODE 0x1111
#घोषणा MPORT_MULTI_FUNCTION_MODE 0x2222

#घोषणा NX_MAX_PCI_FUNC		8

/*
 * NetXen host-peg संकेत message काष्ठाure
 *
 *	Bit 0-1		: peg_id => 0x2 क्रम tx and 01 क्रम rx
 *	Bit 2		: priv_id => must be 1
 *	Bit 3-17	: count => क्रम करोorbell
 *	Bit 18-27	: ctx_id => Context id
 *	Bit 28-31	: opcode
 */

प्रकार u32 netxen_ctx_msg;

#घोषणा netxen_set_msg_peg_id(config_word, val)	\
	((config_word) &= ~3, (config_word) |= val & 3)
#घोषणा netxen_set_msg_privid(config_word)	\
	((config_word) |= 1 << 2)
#घोषणा netxen_set_msg_count(config_word, val)	\
	((config_word) &= ~(0x7fff<<3), (config_word) |= (val & 0x7fff) << 3)
#घोषणा netxen_set_msg_ctxid(config_word, val)	\
	((config_word) &= ~(0x3ff<<18), (config_word) |= (val & 0x3ff) << 18)
#घोषणा netxen_set_msg_opcode(config_word, val)	\
	((config_word) &= ~(0xf<<28), (config_word) |= (val & 0xf) << 28)

काष्ठा netxen_rcv_ring अणु
	__le64 addr;
	__le32 size;
	__le32 rsrvd;
पूर्ण;

काष्ठा netxen_sts_ring अणु
	__le64 addr;
	__le32 size;
	__le16 msi_index;
	__le16 rsvd;
पूर्ण ;

काष्ठा netxen_ring_ctx अणु

	/* one command ring */
	__le64 cmd_consumer_offset;
	__le64 cmd_ring_addr;
	__le32 cmd_ring_size;
	__le32 rsrvd;

	/* three receive rings */
	काष्ठा netxen_rcv_ring rcv_rings[NUM_RCV_DESC_RINGS];

	__le64 sts_ring_addr;
	__le32 sts_ring_size;

	__le32 ctx_id;

	__le64 rsrvd_2[3];
	__le32 sts_ring_count;
	__le32 rsrvd_3;
	काष्ठा netxen_sts_ring sts_rings[NUM_STS_DESC_RINGS];

पूर्ण __attribute__ ((aligned(64)));

/*
 * Following data काष्ठाures describe the descriptors that will be used.
 * Added fileds of tcpHdrSize and ipHdrSize, The driver needs to करो it only when
 * we are करोing LSO (above the 1500 size packet) only.
 */

/*
 * The size of reference handle been changed to 16 bits to pass the MSS fields
 * क्रम the LSO packet
 */

#घोषणा FLAGS_CHECKSUM_ENABLED	0x01
#घोषणा FLAGS_LSO_ENABLED	0x02
#घोषणा FLAGS_IPSEC_SA_ADD	0x04
#घोषणा FLAGS_IPSEC_SA_DELETE	0x08
#घोषणा FLAGS_VLAN_TAGGED	0x10
#घोषणा FLAGS_VLAN_OOB		0x40

#घोषणा netxen_set_tx_vlan_tci(cmd_desc, v)	\
	(cmd_desc)->vlan_TCI = cpu_to_le16(v);

#घोषणा netxen_set_cmd_desc_port(cmd_desc, var)	\
	((cmd_desc)->port_ctxid |= ((var) & 0x0F))
#घोषणा netxen_set_cmd_desc_ctxid(cmd_desc, var)	\
	((cmd_desc)->port_ctxid |= ((var) << 4 & 0xF0))

#घोषणा netxen_set_tx_port(_desc, _port) \
	(_desc)->port_ctxid = ((_port) & 0xf) | (((_port) << 4) & 0xf0)

#घोषणा netxen_set_tx_flags_opcode(_desc, _flags, _opcode) \
	(_desc)->flags_opcode = \
	cpu_to_le16(((_flags) & 0x7f) | (((_opcode) & 0x3f) << 7))

#घोषणा netxen_set_tx_frags_len(_desc, _frags, _len) \
	(_desc)->nfrags__length = \
	cpu_to_le32(((_frags) & 0xff) | (((_len) & 0xffffff) << 8))

काष्ठा cmd_desc_type0 अणु
	u8 tcp_hdr_offset;	/* For LSO only */
	u8 ip_hdr_offset;	/* For LSO only */
	__le16 flags_opcode;	/* 15:13 unused, 12:7 opcode, 6:0 flags */
	__le32 nfrags__length;	/* 31:8 total len, 7:0 frag count */

	__le64 addr_buffer2;

	__le16 reference_handle;
	__le16 mss;
	u8 port_ctxid;		/* 7:4 ctxid 3:0 port */
	u8 total_hdr_length;	/* LSO only : MAC+IP+TCP Hdr size */
	__le16 conn_id;		/* IPSec offoad only */

	__le64 addr_buffer3;
	__le64 addr_buffer1;

	__le16 buffer_length[4];

	__le64 addr_buffer4;

	__le32 reserved2;
	__le16 reserved;
	__le16 vlan_TCI;

पूर्ण __attribute__ ((aligned(64)));

/* Note: माप(rcv_desc) should always be a multiple of 2 */
काष्ठा rcv_desc अणु
	__le16 reference_handle;
	__le16 reserved;
	__le32 buffer_length;	/* allocated buffer length (usually 2K) */
	__le64 addr_buffer;
पूर्ण;

/* opcode field in status_desc */
#घोषणा NETXEN_NIC_SYN_OFFLOAD  0x03
#घोषणा NETXEN_NIC_RXPKT_DESC  0x04
#घोषणा NETXEN_OLD_RXPKT_DESC  0x3f
#घोषणा NETXEN_NIC_RESPONSE_DESC 0x05
#घोषणा NETXEN_NIC_LRO_DESC  	0x12

/* क्रम status field in status_desc */
#घोषणा STATUS_NEED_CKSUM	(1)
#घोषणा STATUS_CKSUM_OK		(2)

/* owner bits of status_desc */
#घोषणा STATUS_OWNER_HOST	(0x1ULL << 56)
#घोषणा STATUS_OWNER_PHANTOM	(0x2ULL << 56)

/* Status descriptor:
   0-3 port, 4-7 status, 8-11 type, 12-27 total_length
   28-43 reference_handle, 44-47 protocol, 48-52 pkt_offset
   53-55 desc_cnt, 56-57 owner, 58-63 opcode
 */
#घोषणा netxen_get_sts_port(sts_data)	\
	((sts_data) & 0x0F)
#घोषणा netxen_get_sts_status(sts_data)	\
	(((sts_data) >> 4) & 0x0F)
#घोषणा netxen_get_sts_type(sts_data)	\
	(((sts_data) >> 8) & 0x0F)
#घोषणा netxen_get_sts_totallength(sts_data)	\
	(((sts_data) >> 12) & 0xFFFF)
#घोषणा netxen_get_sts_refhandle(sts_data)	\
	(((sts_data) >> 28) & 0xFFFF)
#घोषणा netxen_get_sts_prot(sts_data)	\
	(((sts_data) >> 44) & 0x0F)
#घोषणा netxen_get_sts_pkt_offset(sts_data)	\
	(((sts_data) >> 48) & 0x1F)
#घोषणा netxen_get_sts_desc_cnt(sts_data)	\
	(((sts_data) >> 53) & 0x7)
#घोषणा netxen_get_sts_opcode(sts_data)	\
	(((sts_data) >> 58) & 0x03F)

#घोषणा netxen_get_lro_sts_refhandle(sts_data) 	\
	((sts_data) & 0x0FFFF)
#घोषणा netxen_get_lro_sts_length(sts_data)	\
	(((sts_data) >> 16) & 0x0FFFF)
#घोषणा netxen_get_lro_sts_l2_hdr_offset(sts_data)	\
	(((sts_data) >> 32) & 0x0FF)
#घोषणा netxen_get_lro_sts_l4_hdr_offset(sts_data)	\
	(((sts_data) >> 40) & 0x0FF)
#घोषणा netxen_get_lro_sts_बारtamp(sts_data)	\
	(((sts_data) >> 48) & 0x1)
#घोषणा netxen_get_lro_sts_type(sts_data)	\
	(((sts_data) >> 49) & 0x7)
#घोषणा netxen_get_lro_sts_push_flag(sts_data)		\
	(((sts_data) >> 52) & 0x1)
#घोषणा netxen_get_lro_sts_seq_number(sts_data)		\
	((sts_data) & 0x0FFFFFFFF)
#घोषणा netxen_get_lro_sts_mss(sts_data1)		\
	((sts_data1 >> 32) & 0x0FFFF)


काष्ठा status_desc अणु
	__le64 status_desc_data[2];
पूर्ण __attribute__ ((aligned(16)));

/* UNIFIED ROMIMAGE *************************/
#घोषणा NX_UNI_सूची_SECT_PRODUCT_TBL	0x0
#घोषणा NX_UNI_सूची_SECT_BOOTLD		0x6
#घोषणा NX_UNI_सूची_SECT_FW		0x7

/*Offsets */
#घोषणा NX_UNI_CHIP_REV_OFF		10
#घोषणा NX_UNI_FLAGS_OFF		11
#घोषणा NX_UNI_BIOS_VERSION_OFF 	12
#घोषणा NX_UNI_BOOTLD_IDX_OFF		27
#घोषणा NX_UNI_FIRMWARE_IDX_OFF 	29

काष्ठा uni_table_descअणु
	uपूर्णांक32_t	findex;
	uपूर्णांक32_t	num_entries;
	uपूर्णांक32_t	entry_size;
	uपूर्णांक32_t	reserved[5];
पूर्ण;

काष्ठा uni_data_descअणु
	uपूर्णांक32_t	findex;
	uपूर्णांक32_t	size;
	uपूर्णांक32_t	reserved[5];
पूर्ण;

/* UNIFIED ROMIMAGE *************************/

/* The version of the मुख्य data काष्ठाure */
#घोषणा	NETXEN_BDINFO_VERSION 1

/* Magic number to let user know flash is programmed */
#घोषणा	NETXEN_BDINFO_MAGIC 0x12345678

/* Max number of Gig ports on a Phantom board */
#घोषणा NETXEN_MAX_PORTS 4

#घोषणा NETXEN_BRDTYPE_P1_BD		0x0000
#घोषणा NETXEN_BRDTYPE_P1_SB		0x0001
#घोषणा NETXEN_BRDTYPE_P1_SMAX		0x0002
#घोषणा NETXEN_BRDTYPE_P1_SOCK		0x0003

#घोषणा NETXEN_BRDTYPE_P2_SOCK_31	0x0008
#घोषणा NETXEN_BRDTYPE_P2_SOCK_35	0x0009
#घोषणा NETXEN_BRDTYPE_P2_SB35_4G	0x000a
#घोषणा NETXEN_BRDTYPE_P2_SB31_10G	0x000b
#घोषणा NETXEN_BRDTYPE_P2_SB31_2G	0x000c

#घोषणा NETXEN_BRDTYPE_P2_SB31_10G_IMEZ		0x000d
#घोषणा NETXEN_BRDTYPE_P2_SB31_10G_HMEZ		0x000e
#घोषणा NETXEN_BRDTYPE_P2_SB31_10G_CX4		0x000f

#घोषणा NETXEN_BRDTYPE_P3_REF_QG	0x0021
#घोषणा NETXEN_BRDTYPE_P3_HMEZ		0x0022
#घोषणा NETXEN_BRDTYPE_P3_10G_CX4_LP	0x0023
#घोषणा NETXEN_BRDTYPE_P3_4_GB		0x0024
#घोषणा NETXEN_BRDTYPE_P3_IMEZ		0x0025
#घोषणा NETXEN_BRDTYPE_P3_10G_SFP_PLUS	0x0026
#घोषणा NETXEN_BRDTYPE_P3_10000_BASE_T	0x0027
#घोषणा NETXEN_BRDTYPE_P3_XG_LOM	0x0028
#घोषणा NETXEN_BRDTYPE_P3_4_GB_MM	0x0029
#घोषणा NETXEN_BRDTYPE_P3_10G_SFP_CT	0x002a
#घोषणा NETXEN_BRDTYPE_P3_10G_SFP_QT	0x002b
#घोषणा NETXEN_BRDTYPE_P3_10G_CX4	0x0031
#घोषणा NETXEN_BRDTYPE_P3_10G_XFP	0x0032
#घोषणा NETXEN_BRDTYPE_P3_10G_TP	0x0080

/* Flash memory map */
#घोषणा NETXEN_CRBINIT_START	0	/* crbinit section */
#घोषणा NETXEN_BRDCFG_START	0x4000	/* board config */
#घोषणा NETXEN_INITCODE_START	0x6000	/* pegtune code */
#घोषणा NETXEN_BOOTLD_START	0x10000	/* bootld */
#घोषणा NETXEN_IMAGE_START	0x43000	/* compressed image */
#घोषणा NETXEN_SECONDARY_START	0x200000	/* backup images */
#घोषणा NETXEN_PXE_START	0x3E0000	/* PXE boot rom */
#घोषणा NETXEN_USER_START	0x3E8000	/* Firmware info */
#घोषणा NETXEN_FIXED_START	0x3F0000	/* backup of crbinit */
#घोषणा NETXEN_USER_START_OLD	NETXEN_PXE_START /* very old flash */

#घोषणा NX_OLD_MAC_ADDR_OFFSET	(NETXEN_USER_START)
#घोषणा NX_FW_VERSION_OFFSET	(NETXEN_USER_START+0x408)
#घोषणा NX_FW_SIZE_OFFSET	(NETXEN_USER_START+0x40c)
#घोषणा NX_FW_MAC_ADDR_OFFSET	(NETXEN_USER_START+0x418)
#घोषणा NX_FW_SERIAL_NUM_OFFSET	(NETXEN_USER_START+0x81c)
#घोषणा NX_BIOS_VERSION_OFFSET	(NETXEN_USER_START+0x83c)

#घोषणा NX_HDR_VERSION_OFFSET	(NETXEN_BRDCFG_START)
#घोषणा NX_BRDTYPE_OFFSET	(NETXEN_BRDCFG_START+0x8)
#घोषणा NX_FW_MAGIC_OFFSET	(NETXEN_BRDCFG_START+0x128)

#घोषणा NX_FW_MIN_SIZE		(0x3fffff)
#घोषणा NX_P2_MN_ROMIMAGE	0
#घोषणा NX_P3_CT_ROMIMAGE	1
#घोषणा NX_P3_MN_ROMIMAGE	2
#घोषणा NX_UNIFIED_ROMIMAGE	3
#घोषणा NX_FLASH_ROMIMAGE	4
#घोषणा NX_UNKNOWN_ROMIMAGE	0xff

#घोषणा NX_P2_MN_ROMIMAGE_NAME		"nxromimg.bin"
#घोषणा NX_P3_CT_ROMIMAGE_NAME		"nx3fwct.bin"
#घोषणा NX_P3_MN_ROMIMAGE_NAME		"nx3fwmn.bin"
#घोषणा NX_UNIFIED_ROMIMAGE_NAME	"phanfw.bin"
#घोषणा NX_FLASH_ROMIMAGE_NAME		"flash"

बाह्य अक्षर netxen_nic_driver_name[];

/* Number of status descriptors to handle per पूर्णांकerrupt */
#घोषणा MAX_STATUS_HANDLE	(64)

/*
 * netxen_skb_fragअणुपूर्ण is to contain mapping info क्रम each SG list. This
 * has to be मुक्तd when DMA is complete. This is part of netxen_tx_bufferअणुपूर्ण.
 */
काष्ठा netxen_skb_frag अणु
	u64 dma;
	u64 length;
पूर्ण;

काष्ठा netxen_recv_crb अणु
	u32 crb_rcv_producer[NUM_RCV_DESC_RINGS];
	u32 crb_sts_consumer[NUM_STS_DESC_RINGS];
	u32 sw_पूर्णांक_mask[NUM_STS_DESC_RINGS];
पूर्ण;

/*    Following defines are क्रम the state of the buffers    */
#घोषणा	NETXEN_BUFFER_FREE	0
#घोषणा	NETXEN_BUFFER_BUSY	1

/*
 * There will be one netxen_buffer per skb packet.    These will be
 * used to save the dma info क्रम pci_unmap_page()
 */
काष्ठा netxen_cmd_buffer अणु
	काष्ठा sk_buff *skb;
	काष्ठा netxen_skb_frag frag_array[MAX_SKB_FRAGS + 1];
	u32 frag_count;
पूर्ण;

/* In rx_buffer, we करो not need multiple fragments as is a single buffer */
काष्ठा netxen_rx_buffer अणु
	काष्ठा list_head list;
	काष्ठा sk_buff *skb;
	u64 dma;
	u16 ref_handle;
	u16 state;
पूर्ण;

/* Board types */
#घोषणा	NETXEN_NIC_GBE	0x01
#घोषणा	NETXEN_NIC_XGBE	0x02

/*
 * One hardware_contextअणुपूर्ण per adapter
 * contains पूर्णांकerrupt info as well shared hardware info.
 */
काष्ठा netxen_hardware_context अणु
	व्योम __iomem *pci_base0;
	व्योम __iomem *pci_base1;
	व्योम __iomem *pci_base2;
	व्योम __iomem *db_base;
	व्योम __iomem *ocm_win_crb;

	अचिन्हित दीर्घ db_len;
	अचिन्हित दीर्घ pci_len0;

	u32 ocm_win;
	u32 crb_win;

	rwlock_t crb_lock;
	spinlock_t mem_lock;

	u8 cut_through;
	u8 revision_id;
	u8 pci_func;
	u8 linkup;
	u16 port_type;
	u16 board_type;
पूर्ण;

#घोषणा MINIMUM_ETHERNET_FRAME_SIZE	64	/* With FCS */
#घोषणा ETHERNET_FCS_SIZE		4

काष्ठा netxen_adapter_stats अणु
	u64  xmitcalled;
	u64  xmitfinished;
	u64  rxdropped;
	u64  txdropped;
	u64  csummed;
	u64  rx_pkts;
	u64  lro_pkts;
	u64  rxbytes;
	u64  txbytes;
पूर्ण;

/*
 * Rcv Descriptor Context. One such per Rcv Descriptor. There may
 * be one Rcv Descriptor क्रम normal packets, one क्रम jumbo and may be others.
 */
काष्ठा nx_host_rds_ring अणु
	u32 producer;
	u32 num_desc;
	u32 dma_size;
	u32 skb_size;
	u32 flags;
	व्योम __iomem *crb_rcv_producer;
	काष्ठा rcv_desc *desc_head;
	काष्ठा netxen_rx_buffer *rx_buf_arr;
	काष्ठा list_head मुक्त_list;
	spinlock_t lock;
	dma_addr_t phys_addr;
पूर्ण;

काष्ठा nx_host_sds_ring अणु
	u32 consumer;
	u32 num_desc;
	व्योम __iomem *crb_sts_consumer;
	व्योम __iomem *crb_पूर्णांकr_mask;

	काष्ठा status_desc *desc_head;
	काष्ठा netxen_adapter *adapter;
	काष्ठा napi_काष्ठा napi;
	काष्ठा list_head मुक्त_list[NUM_RCV_DESC_RINGS];

	पूर्णांक irq;

	dma_addr_t phys_addr;
	अक्षर name[IFNAMSIZ+4];
पूर्ण;

काष्ठा nx_host_tx_ring अणु
	u32 producer;
	__le32 *hw_consumer;
	u32 sw_consumer;
	व्योम __iomem *crb_cmd_producer;
	व्योम __iomem *crb_cmd_consumer;
	u32 num_desc;

	काष्ठा netdev_queue *txq;

	काष्ठा netxen_cmd_buffer *cmd_buf_arr;
	काष्ठा cmd_desc_type0 *desc_head;
	dma_addr_t phys_addr;
पूर्ण;

/*
 * Receive context. There is one such काष्ठाure per instance of the
 * receive processing. Any state inक्रमmation that is relevant to
 * the receive, and is must be in this काष्ठाure. The global data may be
 * present अन्यथाwhere.
 */
काष्ठा netxen_recv_context अणु
	u32 state;
	u16 context_id;
	u16 virt_port;

	काष्ठा nx_host_rds_ring *rds_rings;
	काष्ठा nx_host_sds_ring *sds_rings;

	काष्ठा netxen_ring_ctx *hwctx;
	dma_addr_t phys_addr;
पूर्ण;

काष्ठा _cdrp_cmd अणु
	u32 cmd;
	u32 arg1;
	u32 arg2;
	u32 arg3;
पूर्ण;

काष्ठा netxen_cmd_args अणु
	काष्ठा _cdrp_cmd req;
	काष्ठा _cdrp_cmd rsp;
पूर्ण;

/* New HW context creation */

#घोषणा NX_OS_CRB_RETRY_COUNT	4000
#घोषणा NX_CDRP_SIGNATURE_MAKE(pcअगरn, version) \
	(((pcअगरn) & 0xff) | (((version) & 0xff) << 8) | (0xcafe << 16))

#घोषणा NX_CDRP_CLEAR		0x00000000
#घोषणा NX_CDRP_CMD_BIT		0x80000000

/*
 * All responses must have the NX_CDRP_CMD_BIT cleared
 * in the crb NX_CDRP_CRB_OFFSET.
 */
#घोषणा NX_CDRP_FORM_RSP(rsp)	(rsp)
#घोषणा NX_CDRP_IS_RSP(rsp)	(((rsp) & NX_CDRP_CMD_BIT) == 0)

#घोषणा NX_CDRP_RSP_OK		0x00000001
#घोषणा NX_CDRP_RSP_FAIL	0x00000002
#घोषणा NX_CDRP_RSP_TIMEOUT	0x00000003

/*
 * All commands must have the NX_CDRP_CMD_BIT set in
 * the crb NX_CDRP_CRB_OFFSET.
 */
#घोषणा NX_CDRP_FORM_CMD(cmd)	(NX_CDRP_CMD_BIT | (cmd))
#घोषणा NX_CDRP_IS_CMD(cmd)	(((cmd) & NX_CDRP_CMD_BIT) != 0)

#घोषणा NX_CDRP_CMD_SUBMIT_CAPABILITIES     0x00000001
#घोषणा NX_CDRP_CMD_READ_MAX_RDS_PER_CTX    0x00000002
#घोषणा NX_CDRP_CMD_READ_MAX_SDS_PER_CTX    0x00000003
#घोषणा NX_CDRP_CMD_READ_MAX_RULES_PER_CTX  0x00000004
#घोषणा NX_CDRP_CMD_READ_MAX_RX_CTX         0x00000005
#घोषणा NX_CDRP_CMD_READ_MAX_TX_CTX         0x00000006
#घोषणा NX_CDRP_CMD_CREATE_RX_CTX           0x00000007
#घोषणा NX_CDRP_CMD_DESTROY_RX_CTX          0x00000008
#घोषणा NX_CDRP_CMD_CREATE_TX_CTX           0x00000009
#घोषणा NX_CDRP_CMD_DESTROY_TX_CTX          0x0000000a
#घोषणा NX_CDRP_CMD_SETUP_STATISTICS        0x0000000e
#घोषणा NX_CDRP_CMD_GET_STATISTICS          0x0000000f
#घोषणा NX_CDRP_CMD_DELETE_STATISTICS       0x00000010
#घोषणा NX_CDRP_CMD_SET_MTU                 0x00000012
#घोषणा NX_CDRP_CMD_READ_PHY			0x00000013
#घोषणा NX_CDRP_CMD_WRITE_PHY			0x00000014
#घोषणा NX_CDRP_CMD_READ_HW_REG			0x00000015
#घोषणा NX_CDRP_CMD_GET_FLOW_CTL		0x00000016
#घोषणा NX_CDRP_CMD_SET_FLOW_CTL		0x00000017
#घोषणा NX_CDRP_CMD_READ_MAX_MTU		0x00000018
#घोषणा NX_CDRP_CMD_READ_MAX_LRO		0x00000019
#घोषणा NX_CDRP_CMD_CONFIGURE_TOE		0x0000001a
#घोषणा NX_CDRP_CMD_FUNC_ATTRIB			0x0000001b
#घोषणा NX_CDRP_CMD_READ_PEXQ_PARAMETERS	0x0000001c
#घोषणा NX_CDRP_CMD_GET_LIC_CAPABILITIES	0x0000001d
#घोषणा NX_CDRP_CMD_READ_MAX_LRO_PER_BOARD	0x0000001e
#घोषणा NX_CDRP_CMD_CONFIG_GBE_PORT		0x0000001f
#घोषणा NX_CDRP_CMD_MAX				0x00000020

#घोषणा NX_RCODE_SUCCESS		0
#घोषणा NX_RCODE_NO_HOST_MEM		1
#घोषणा NX_RCODE_NO_HOST_RESOURCE	2
#घोषणा NX_RCODE_NO_CARD_CRB		3
#घोषणा NX_RCODE_NO_CARD_MEM		4
#घोषणा NX_RCODE_NO_CARD_RESOURCE	5
#घोषणा NX_RCODE_INVALID_ARGS		6
#घोषणा NX_RCODE_INVALID_ACTION		7
#घोषणा NX_RCODE_INVALID_STATE		8
#घोषणा NX_RCODE_NOT_SUPPORTED		9
#घोषणा NX_RCODE_NOT_PERMITTED		10
#घोषणा NX_RCODE_NOT_READY		11
#घोषणा NX_RCODE_DOES_NOT_EXIST		12
#घोषणा NX_RCODE_ALREADY_EXISTS		13
#घोषणा NX_RCODE_BAD_SIGNATURE		14
#घोषणा NX_RCODE_CMD_NOT_IMPL		15
#घोषणा NX_RCODE_CMD_INVALID		16
#घोषणा NX_RCODE_TIMEOUT		17
#घोषणा NX_RCODE_CMD_FAILED		18
#घोषणा NX_RCODE_MAX_EXCEEDED		19
#घोषणा NX_RCODE_MAX			20

#घोषणा NX_DESTROY_CTX_RESET		0
#घोषणा NX_DESTROY_CTX_D3_RESET		1
#घोषणा NX_DESTROY_CTX_MAX		2

/*
 * Capabilities
 */
#घोषणा NX_CAP_BIT(class, bit)		(1 << bit)
#घोषणा NX_CAP0_LEGACY_CONTEXT		NX_CAP_BIT(0, 0)
#घोषणा NX_CAP0_MULTI_CONTEXT		NX_CAP_BIT(0, 1)
#घोषणा NX_CAP0_LEGACY_MN		NX_CAP_BIT(0, 2)
#घोषणा NX_CAP0_LEGACY_MS		NX_CAP_BIT(0, 3)
#घोषणा NX_CAP0_CUT_THROUGH		NX_CAP_BIT(0, 4)
#घोषणा NX_CAP0_LRO			NX_CAP_BIT(0, 5)
#घोषणा NX_CAP0_LSO			NX_CAP_BIT(0, 6)
#घोषणा NX_CAP0_JUMBO_CONTIGUOUS	NX_CAP_BIT(0, 7)
#घोषणा NX_CAP0_LRO_CONTIGUOUS		NX_CAP_BIT(0, 8)
#घोषणा NX_CAP0_HW_LRO			NX_CAP_BIT(0, 10)
#घोषणा NX_CAP0_HW_LRO_MSS		NX_CAP_BIT(0, 21)

/*
 * Context state
 */
#घोषणा NX_HOST_CTX_STATE_FREED		0
#घोषणा NX_HOST_CTX_STATE_ALLOCATED	1
#घोषणा NX_HOST_CTX_STATE_ACTIVE	2
#घोषणा NX_HOST_CTX_STATE_DISABLED	3
#घोषणा NX_HOST_CTX_STATE_QUIESCED	4
#घोषणा NX_HOST_CTX_STATE_MAX		5

/*
 * Rx context
 */

प्रकार काष्ठा अणु
	__le64 host_phys_addr;	/* Ring base addr */
	__le32 ring_size;		/* Ring entries */
	__le16 msi_index;
	__le16 rsvd;		/* Padding */
पूर्ण nx_hostrq_sds_ring_t;

प्रकार काष्ठा अणु
	__le64 host_phys_addr;	/* Ring base addr */
	__le64 buff_size;		/* Packet buffer size */
	__le32 ring_size;		/* Ring entries */
	__le32 ring_kind;		/* Class of ring */
पूर्ण nx_hostrq_rds_ring_t;

प्रकार काष्ठा अणु
	__le64 host_rsp_dma_addr;	/* Response dma'd here */
	__le32 capabilities[4];	/* Flag bit vector */
	__le32 host_पूर्णांक_crb_mode;	/* Interrupt crb usage */
	__le32 host_rds_crb_mode;	/* RDS crb usage */
	/* These ring offsets are relative to data[0] below */
	__le32 rds_ring_offset;	/* Offset to RDS config */
	__le32 sds_ring_offset;	/* Offset to SDS config */
	__le16 num_rds_rings;	/* Count of RDS rings */
	__le16 num_sds_rings;	/* Count of SDS rings */
	__le16 rsvd1;		/* Padding */
	__le16 rsvd2;		/* Padding */
	u8  reserved[128]; 	/* reserve space क्रम future expansion*/
	/* MUST BE 64-bit aligned.
	   The following is packed:
	   - N hostrq_rds_rings
	   - N hostrq_sds_rings */
	अक्षर data[0];
पूर्ण nx_hostrq_rx_ctx_t;

प्रकार काष्ठा अणु
	__le32 host_producer_crb;	/* Crb to use */
	__le32 rsvd1;		/* Padding */
पूर्ण nx_cardrsp_rds_ring_t;

प्रकार काष्ठा अणु
	__le32 host_consumer_crb;	/* Crb to use */
	__le32 पूर्णांकerrupt_crb;	/* Crb to use */
पूर्ण nx_cardrsp_sds_ring_t;

प्रकार काष्ठा अणु
	/* These ring offsets are relative to data[0] below */
	__le32 rds_ring_offset;	/* Offset to RDS config */
	__le32 sds_ring_offset;	/* Offset to SDS config */
	__le32 host_ctx_state;	/* Starting State */
	__le32 num_fn_per_port;	/* How many PCI fn share the port */
	__le16 num_rds_rings;	/* Count of RDS rings */
	__le16 num_sds_rings;	/* Count of SDS rings */
	__le16 context_id;		/* Handle क्रम context */
	u8  phys_port;		/* Physical id of port */
	u8  virt_port;		/* Virtual/Logical id of port */
	u8  reserved[128];	/* save space क्रम future expansion */
	/*  MUST BE 64-bit aligned.
	   The following is packed:
	   - N cardrsp_rds_rings
	   - N cardrs_sds_rings */
	अक्षर data[0];
पूर्ण nx_cardrsp_rx_ctx_t;

#घोषणा SIZखातापूर्ण_HOSTRQ_RX(HOSTRQ_RX, rds_rings, sds_rings)	\
	(माप(HOSTRQ_RX) + 					\
	(rds_rings)*(माप(nx_hostrq_rds_ring_t)) +		\
	(sds_rings)*(माप(nx_hostrq_sds_ring_t)))

#घोषणा SIZखातापूर्ण_CARDRSP_RX(CARDRSP_RX, rds_rings, sds_rings) 	\
	(माप(CARDRSP_RX) + 					\
	(rds_rings)*(माप(nx_cardrsp_rds_ring_t)) + 		\
	(sds_rings)*(माप(nx_cardrsp_sds_ring_t)))

/*
 * Tx context
 */

प्रकार काष्ठा अणु
	__le64 host_phys_addr;	/* Ring base addr */
	__le32 ring_size;		/* Ring entries */
	__le32 rsvd;		/* Padding */
पूर्ण nx_hostrq_cds_ring_t;

प्रकार काष्ठा अणु
	__le64 host_rsp_dma_addr;	/* Response dma'd here */
	__le64 cmd_cons_dma_addr;	/*  */
	__le64 dummy_dma_addr;	/*  */
	__le32 capabilities[4];	/* Flag bit vector */
	__le32 host_पूर्णांक_crb_mode;	/* Interrupt crb usage */
	__le32 rsvd1;		/* Padding */
	__le16 rsvd2;		/* Padding */
	__le16 पूर्णांकerrupt_ctl;
	__le16 msi_index;
	__le16 rsvd3;		/* Padding */
	nx_hostrq_cds_ring_t cds_ring;	/* Desc of cds ring */
	u8  reserved[128];	/* future expansion */
पूर्ण nx_hostrq_tx_ctx_t;

प्रकार काष्ठा अणु
	__le32 host_producer_crb;	/* Crb to use */
	__le32 पूर्णांकerrupt_crb;	/* Crb to use */
पूर्ण nx_cardrsp_cds_ring_t;

प्रकार काष्ठा अणु
	__le32 host_ctx_state;	/* Starting state */
	__le16 context_id;		/* Handle क्रम context */
	u8  phys_port;		/* Physical id of port */
	u8  virt_port;		/* Virtual/Logical id of port */
	nx_cardrsp_cds_ring_t cds_ring;	/* Card cds settings */
	u8  reserved[128];	/* future expansion */
पूर्ण nx_cardrsp_tx_ctx_t;

#घोषणा SIZखातापूर्ण_HOSTRQ_TX(HOSTRQ_TX)	(माप(HOSTRQ_TX))
#घोषणा SIZखातापूर्ण_CARDRSP_TX(CARDRSP_TX)	(माप(CARDRSP_TX))

/* CRB */

#घोषणा NX_HOST_RDS_CRB_MODE_UNIQUE	0
#घोषणा NX_HOST_RDS_CRB_MODE_SHARED	1
#घोषणा NX_HOST_RDS_CRB_MODE_CUSTOM	2
#घोषणा NX_HOST_RDS_CRB_MODE_MAX	3

#घोषणा NX_HOST_INT_CRB_MODE_UNIQUE	0
#घोषणा NX_HOST_INT_CRB_MODE_SHARED	1
#घोषणा NX_HOST_INT_CRB_MODE_NORX	2
#घोषणा NX_HOST_INT_CRB_MODE_NOTX	3
#घोषणा NX_HOST_INT_CRB_MODE_NORXTX	4


/* MAC */

#घोषणा MC_COUNT_P2	16
#घोषणा MC_COUNT_P3	38

#घोषणा NETXEN_MAC_NOOP	0
#घोषणा NETXEN_MAC_ADD	1
#घोषणा NETXEN_MAC_DEL	2

प्रकार काष्ठा nx_mac_list_s अणु
	काष्ठा list_head list;
	uपूर्णांक8_t mac_addr[ETH_ALEN+2];
पूर्ण nx_mac_list_t;

काष्ठा nx_ip_list अणु
	काष्ठा list_head list;
	__be32 ip_addr;
	bool master;
पूर्ण;

/*
 * Interrupt coalescing शेषs. The शेषs are क्रम 1500 MTU. It is
 * adjusted based on configured MTU.
 */
#घोषणा NETXEN_DEFAULT_INTR_COALESCE_RX_TIME_US	3
#घोषणा NETXEN_DEFAULT_INTR_COALESCE_RX_PACKETS	256
#घोषणा NETXEN_DEFAULT_INTR_COALESCE_TX_PACKETS	64
#घोषणा NETXEN_DEFAULT_INTR_COALESCE_TX_TIME_US	4

#घोषणा NETXEN_NIC_INTR_DEFAULT			0x04

प्रकार जोड़ अणु
	काष्ठा अणु
		uपूर्णांक16_t	rx_packets;
		uपूर्णांक16_t	rx_समय_us;
		uपूर्णांक16_t	tx_packets;
		uपूर्णांक16_t	tx_समय_us;
	पूर्ण data;
	uपूर्णांक64_t		word;
पूर्ण nx_nic_पूर्णांकr_coalesce_data_t;

प्रकार काष्ठा अणु
	uपूर्णांक16_t			stats_समय_us;
	uपूर्णांक16_t			rate_sample_समय;
	uपूर्णांक16_t			flags;
	uपूर्णांक16_t			rsvd_1;
	uपूर्णांक32_t			low_threshold;
	uपूर्णांक32_t			high_threshold;
	nx_nic_पूर्णांकr_coalesce_data_t	normal;
	nx_nic_पूर्णांकr_coalesce_data_t	low;
	nx_nic_पूर्णांकr_coalesce_data_t	high;
	nx_nic_पूर्णांकr_coalesce_data_t	irq;
पूर्ण nx_nic_पूर्णांकr_coalesce_t;

#घोषणा NX_HOST_REQUEST		0x13
#घोषणा NX_NIC_REQUEST		0x14

#घोषणा NX_MAC_EVENT		0x1

#घोषणा NX_IP_UP		2
#घोषणा NX_IP_DOWN		3

/*
 * Driver --> Firmware
 */
#घोषणा NX_NIC_H2C_OPCODE_START				0
#घोषणा NX_NIC_H2C_OPCODE_CONFIG_RSS			1
#घोषणा NX_NIC_H2C_OPCODE_CONFIG_RSS_TBL		2
#घोषणा NX_NIC_H2C_OPCODE_CONFIG_INTR_COALESCE		3
#घोषणा NX_NIC_H2C_OPCODE_CONFIG_LED			4
#घोषणा NX_NIC_H2C_OPCODE_CONFIG_PROMISCUOUS		5
#घोषणा NX_NIC_H2C_OPCODE_CONFIG_L2_MAC			6
#घोषणा NX_NIC_H2C_OPCODE_LRO_REQUEST			7
#घोषणा NX_NIC_H2C_OPCODE_GET_SNMP_STATS		8
#घोषणा NX_NIC_H2C_OPCODE_PROXY_START_REQUEST		9
#घोषणा NX_NIC_H2C_OPCODE_PROXY_STOP_REQUEST		10
#घोषणा NX_NIC_H2C_OPCODE_PROXY_SET_MTU			11
#घोषणा NX_NIC_H2C_OPCODE_PROXY_SET_VPORT_MISS_MODE	12
#घोषणा NX_NIC_H2C_OPCODE_GET_FINGER_PRINT_REQUEST	13
#घोषणा NX_NIC_H2C_OPCODE_INSTALL_LICENSE_REQUEST	14
#घोषणा NX_NIC_H2C_OPCODE_GET_LICENSE_CAPABILITY_REQUEST	15
#घोषणा NX_NIC_H2C_OPCODE_GET_NET_STATS			16
#घोषणा NX_NIC_H2C_OPCODE_PROXY_UPDATE_P2V		17
#घोषणा NX_NIC_H2C_OPCODE_CONFIG_IPADDR			18
#घोषणा NX_NIC_H2C_OPCODE_CONFIG_LOOPBACK		19
#घोषणा NX_NIC_H2C_OPCODE_PROXY_STOP_DONE		20
#घोषणा NX_NIC_H2C_OPCODE_GET_LINKEVENT			21
#घोषणा NX_NIC_C2C_OPCODE				22
#घोषणा NX_NIC_H2C_OPCODE_CONFIG_BRIDGING               23
#घोषणा NX_NIC_H2C_OPCODE_CONFIG_HW_LRO			24
#घोषणा NX_NIC_H2C_OPCODE_LAST				25

/*
 * Firmware --> Driver
 */

#घोषणा NX_NIC_C2H_OPCODE_START				128
#घोषणा NX_NIC_C2H_OPCODE_CONFIG_RSS_RESPONSE		129
#घोषणा NX_NIC_C2H_OPCODE_CONFIG_RSS_TBL_RESPONSE	130
#घोषणा NX_NIC_C2H_OPCODE_CONFIG_MAC_RESPONSE		131
#घोषणा NX_NIC_C2H_OPCODE_CONFIG_PROMISCUOUS_RESPONSE	132
#घोषणा NX_NIC_C2H_OPCODE_CONFIG_L2_MAC_RESPONSE	133
#घोषणा NX_NIC_C2H_OPCODE_LRO_DELETE_RESPONSE		134
#घोषणा NX_NIC_C2H_OPCODE_LRO_ADD_FAILURE_RESPONSE	135
#घोषणा NX_NIC_C2H_OPCODE_GET_SNMP_STATS		136
#घोषणा NX_NIC_C2H_OPCODE_GET_FINGER_PRINT_REPLY	137
#घोषणा NX_NIC_C2H_OPCODE_INSTALL_LICENSE_REPLY		138
#घोषणा NX_NIC_C2H_OPCODE_GET_LICENSE_CAPABILITIES_REPLY 139
#घोषणा NX_NIC_C2H_OPCODE_GET_NET_STATS_RESPONSE	140
#घोषणा NX_NIC_C2H_OPCODE_GET_LINKEVENT_RESPONSE	141
#घोषणा NX_NIC_C2H_OPCODE_LAST				142

#घोषणा VPORT_MISS_MODE_DROP		0 /* drop all unmatched */
#घोषणा VPORT_MISS_MODE_ACCEPT_ALL	1 /* accept all packets */
#घोषणा VPORT_MISS_MODE_ACCEPT_MULTI	2 /* accept unmatched multicast */

#घोषणा NX_NIC_LRO_REQUEST_FIRST		0
#घोषणा NX_NIC_LRO_REQUEST_ADD_FLOW		1
#घोषणा NX_NIC_LRO_REQUEST_DELETE_FLOW		2
#घोषणा NX_NIC_LRO_REQUEST_TIMER		3
#घोषणा NX_NIC_LRO_REQUEST_CLEANUP		4
#घोषणा NX_NIC_LRO_REQUEST_ADD_FLOW_SCHEDULED	5
#घोषणा NX_TOE_LRO_REQUEST_ADD_FLOW		6
#घोषणा NX_TOE_LRO_REQUEST_ADD_FLOW_RESPONSE	7
#घोषणा NX_TOE_LRO_REQUEST_DELETE_FLOW		8
#घोषणा NX_TOE_LRO_REQUEST_DELETE_FLOW_RESPONSE	9
#घोषणा NX_TOE_LRO_REQUEST_TIMER		10
#घोषणा NX_NIC_LRO_REQUEST_LAST			11

#घोषणा NX_FW_CAPABILITY_LINK_NOTIFICATION	(1 << 5)
#घोषणा NX_FW_CAPABILITY_SWITCHING		(1 << 6)
#घोषणा NX_FW_CAPABILITY_PEXQ			(1 << 7)
#घोषणा NX_FW_CAPABILITY_BDG			(1 << 8)
#घोषणा NX_FW_CAPABILITY_FVLANTX		(1 << 9)
#घोषणा NX_FW_CAPABILITY_HW_LRO			(1 << 10)
#घोषणा NX_FW_CAPABILITY_GBE_LINK_CFG		(1 << 11)
#घोषणा NX_FW_CAPABILITY_MORE_CAPS		(1 << 31)
#घोषणा NX_FW_CAPABILITY_2_LRO_MAX_TCP_SEG	(1 << 2)

/* module types */
#घोषणा LINKEVENT_MODULE_NOT_PRESENT			1
#घोषणा LINKEVENT_MODULE_OPTICAL_UNKNOWN		2
#घोषणा LINKEVENT_MODULE_OPTICAL_SRLR			3
#घोषणा LINKEVENT_MODULE_OPTICAL_LRM			4
#घोषणा LINKEVENT_MODULE_OPTICAL_SFP_1G			5
#घोषणा LINKEVENT_MODULE_TWINAX_UNSUPPORTED_CABLE	6
#घोषणा LINKEVENT_MODULE_TWINAX_UNSUPPORTED_CABLELEN	7
#घोषणा LINKEVENT_MODULE_TWINAX				8

#घोषणा LINKSPEED_10GBPS	10000
#घोषणा LINKSPEED_1GBPS		1000
#घोषणा LINKSPEED_100MBPS	100
#घोषणा LINKSPEED_10MBPS	10

#घोषणा LINKSPEED_ENCODED_10MBPS	0
#घोषणा LINKSPEED_ENCODED_100MBPS	1
#घोषणा LINKSPEED_ENCODED_1GBPS		2

#घोषणा LINKEVENT_AUTONEG_DISABLED	0
#घोषणा LINKEVENT_AUTONEG_ENABLED	1

#घोषणा LINKEVENT_HALF_DUPLEX		0
#घोषणा LINKEVENT_FULL_DUPLEX		1

#घोषणा LINKEVENT_LINKSPEED_MBPS	0
#घोषणा LINKEVENT_LINKSPEED_ENCODED	1

#घोषणा AUTO_FW_RESET_ENABLED	0xEF10AF12
#घोषणा AUTO_FW_RESET_DISABLED	0xDCBAAF12

/* firmware response header:
 *	63:58 - message type
 *	57:56 - owner
 *	55:53 - desc count
 *	52:48 - reserved
 *	47:40 - completion id
 *	39:32 - opcode
 *	31:16 - error code
 *	15:00 - reserved
 */
#घोषणा netxen_get_nic_msgtype(msg_hdr)	\
	((msg_hdr >> 58) & 0x3F)
#घोषणा netxen_get_nic_msg_compid(msg_hdr)	\
	((msg_hdr >> 40) & 0xFF)
#घोषणा netxen_get_nic_msg_opcode(msg_hdr)	\
	((msg_hdr >> 32) & 0xFF)
#घोषणा netxen_get_nic_msg_errcode(msg_hdr)	\
	((msg_hdr >> 16) & 0xFFFF)

प्रकार काष्ठा अणु
	जोड़ अणु
		काष्ठा अणु
			u64 hdr;
			u64 body[7];
		पूर्ण;
		u64 words[8];
	पूर्ण;
पूर्ण nx_fw_msg_t;

प्रकार काष्ठा अणु
	__le64 qhdr;
	__le64 req_hdr;
	__le64 words[6];
पूर्ण nx_nic_req_t;

प्रकार काष्ठा अणु
	u8 op;
	u8 tag;
	u8 mac_addr[6];
पूर्ण nx_mac_req_t;

#घोषणा MAX_PENDING_DESC_BLOCK_SIZE	64

#घोषणा NETXEN_NIC_MSI_ENABLED		0x02
#घोषणा NETXEN_NIC_MSIX_ENABLED		0x04
#घोषणा NETXEN_NIC_LRO_ENABLED		0x08
#घोषणा NETXEN_NIC_LRO_DISABLED		0x00
#घोषणा NETXEN_NIC_BRIDGE_ENABLED       0X10
#घोषणा NETXEN_NIC_DIAG_ENABLED		0x20
#घोषणा NETXEN_FW_RESET_OWNER           0x40
#घोषणा NETXEN_FW_MSS_CAP	        0x80
#घोषणा NETXEN_IS_MSI_FAMILY(adapter) \
	((adapter)->flags & (NETXEN_NIC_MSI_ENABLED | NETXEN_NIC_MSIX_ENABLED))

#घोषणा MSIX_ENTRIES_PER_ADAPTER	NUM_STS_DESC_RINGS
#घोषणा NETXEN_MSIX_TBL_SPACE		8192
#घोषणा NETXEN_PCI_REG_MSIX_TBL		0x44

#घोषणा NETXEN_DB_MAPSIZE_BYTES    	0x1000

#घोषणा NETXEN_ADAPTER_UP_MAGIC 777
#घोषणा NETXEN_NIC_PEG_TUNE 0

#घोषणा __NX_FW_ATTACHED		0
#घोषणा __NX_DEV_UP			1
#घोषणा __NX_RESETTING			2

/* Mini Coredump FW supported version */
#घोषणा NX_MD_SUPPORT_MAJOR		4
#घोषणा NX_MD_SUPPORT_MINOR		0
#घोषणा NX_MD_SUPPORT_SUBVERSION	579

#घोषणा LSW(x)  ((uपूर्णांक16_t)(x))
#घोषणा LSD(x)  ((uपूर्णांक32_t)((uपूर्णांक64_t)(x)))
#घोषणा MSD(x)  ((uपूर्णांक32_t)((((uपूर्णांक64_t)(x)) >> 16) >> 16))

/* Mini Coredump mask level */
#घोषणा	NX_DUMP_MASK_MIN	0x03
#घोषणा	NX_DUMP_MASK_DEF	0x1f
#घोषणा	NX_DUMP_MASK_MAX	0xff

/* Mini Coredump CDRP commands */
#घोषणा NX_CDRP_CMD_TEMP_SIZE           0x0000002f
#घोषणा NX_CDRP_CMD_GET_TEMP_HDR        0x00000030


#घोषणा NX_DUMP_STATE_ARRAY_LEN		16
#घोषणा NX_DUMP_CAP_SIZE_ARRAY_LEN	8

/* Mini Coredump sysfs entries flags*/
#घोषणा NX_FORCE_FW_DUMP_KEY		0xdeadfeed
#घोषणा NX_ENABLE_FW_DUMP               0xaddfeed
#घोषणा NX_DISABLE_FW_DUMP              0xbadfeed
#घोषणा NX_FORCE_FW_RESET               0xdeaddead


/* Flash पढ़ो/ग_लिखो address */
#घोषणा NX_FW_DUMP_REG1         0x00130060
#घोषणा NX_FW_DUMP_REG2         0x001e0000
#घोषणा NX_FLASH_SEM2_LK        0x0013C010
#घोषणा NX_FLASH_SEM2_ULK       0x0013C014
#घोषणा NX_FLASH_LOCK_ID        0x001B2100
#घोषणा FLASH_ROM_WINDOW        0x42110030
#घोषणा FLASH_ROM_DATA          0x42150000

/* Mini Coredump रेजिस्टर पढ़ो/ग_लिखो routine */
#घोषणा NX_RD_DUMP_REG(addr, bar0, data) करो अणु                   \
	ग_लिखोl((addr & 0xFFFF0000), (व्योम __iomem *) (bar0 +            \
		NX_FW_DUMP_REG1));                                      \
	पढ़ोl((व्योम __iomem *) (bar0 + NX_FW_DUMP_REG1));               \
	*data = पढ़ोl((व्योम __iomem *) (bar0 + NX_FW_DUMP_REG2 +        \
		LSW(addr)));                                            \
पूर्ण जबतक (0)

#घोषणा NX_WR_DUMP_REG(addr, bar0, data) करो अणु                   \
	ग_लिखोl((addr & 0xFFFF0000), (व्योम __iomem *) (bar0 +            \
		NX_FW_DUMP_REG1));                                      \
	पढ़ोl((व्योम __iomem *) (bar0 + NX_FW_DUMP_REG1));                \
	ग_लिखोl(data, (व्योम __iomem *) (bar0 + NX_FW_DUMP_REG2 + LSW(addr)));\
	पढ़ोl((व्योम __iomem *) (bar0 + NX_FW_DUMP_REG2 + LSW(addr)));  \
पूर्ण जबतक (0)


/*
Entry Type Defines
*/

#घोषणा RDNOP	0
#घोषणा RDCRB	1
#घोषणा RDMUX	2
#घोषणा QUEUE	3
#घोषणा BOARD	4
#घोषणा RDSRE	5
#घोषणा RDOCM	6
#घोषणा PREGS	7
#घोषणा L1DTG	8
#घोषणा L1ITG	9
#घोषणा CACHE	10

#घोषणा L1DAT	11
#घोषणा L1INS	12
#घोषणा RDSTK	13
#घोषणा RDCON	14

#घोषणा L2DTG	21
#घोषणा L2ITG	22
#घोषणा L2DAT	23
#घोषणा L2INS	24
#घोषणा RDOC3	25

#घोषणा MEMBK	32

#घोषणा RDROM	71
#घोषणा RDMEM	72
#घोषणा RDMN	73

#घोषणा INFOR	81
#घोषणा CNTRL	98

#घोषणा TLHDR	99
#घोषणा RDEND	255

#घोषणा PRIMQ	103
#घोषणा SQG2Q	104
#घोषणा SQG3Q	105

/*
* Opcodes क्रम Control Entries.
* These Flags are bit fields.
*/
#घोषणा NX_DUMP_WCRB		0x01
#घोषणा NX_DUMP_RWCRB		0x02
#घोषणा NX_DUMP_ANDCRB		0x04
#घोषणा NX_DUMP_ORCRB		0x08
#घोषणा NX_DUMP_POLLCRB		0x10
#घोषणा NX_DUMP_RD_SAVE		0x20
#घोषणा NX_DUMP_WRT_SAVED	0x40
#घोषणा NX_DUMP_MOD_SAVE_ST	0x80

/* Driver Flags */
#घोषणा NX_DUMP_SKIP		0x80	/*  driver skipped this entry  */
#घोषणा NX_DUMP_SIZE_ERR 0x40	/*entry size vs capture size mismatch*/

#घोषणा NX_PCI_READ_32(ADDR)			पढ़ोl((ADDR))
#घोषणा NX_PCI_WRITE_32(DATA, ADDR)	ग_लिखोl(DATA, (ADDR))



काष्ठा netxen_minidump अणु
	u32 pos;			/* position in the dump buffer */
	u8  fw_supports_md;		/* FW supports Mini cordump */
	u8  has_valid_dump;		/* indicates valid dump */
	u8  md_capture_mask;		/* driver capture mask */
	u8  md_enabled;			/* Turn Mini Coredump on/off */
	u32 md_dump_size;		/* Total FW Mini Coredump size */
	u32 md_capture_size;		/* FW dump capture size */
	u32 md_ढाँचा_size;		/* FW ढाँचा size */
	u32 md_ढाँचा_ver;		/* FW ढाँचा version */
	u64 md_बारtamp;		/* FW Mini dump बारtamp */
	व्योम *md_ढाँचा;		/* FW ढाँचा will be stored */
	व्योम *md_capture_buff;		/* FW dump will be stored */
पूर्ण;



काष्ठा netxen_minidump_ढाँचा_hdr अणु
	u32 entry_type;
	u32 first_entry_offset;
	u32 size_of_ढाँचा;
	u32 capture_mask;
	u32 num_of_entries;
	u32 version;
	u32 driver_बारtamp;
	u32 checksum;
	u32 driver_capture_mask;
	u32 driver_info_word2;
	u32 driver_info_word3;
	u32 driver_info_word4;
	u32 saved_state_array[NX_DUMP_STATE_ARRAY_LEN];
	u32 capture_size_array[NX_DUMP_CAP_SIZE_ARRAY_LEN];
	u32 rsvd[];
पूर्ण;

/* Common Entry Header:  Common to All Entry Types */
/*
 * Driver Code is क्रम driver to ग_लिखो some info about the entry.
 * Currently not used.
 */

काष्ठा netxen_common_entry_hdr अणु
	u32 entry_type;
	u32 entry_size;
	u32 entry_capture_size;
	जोड़ अणु
		काष्ठा अणु
			u8 entry_capture_mask;
			u8 entry_code;
			u8 driver_code;
			u8 driver_flags;
		पूर्ण;
		u32 entry_ctrl_word;
	पूर्ण;
पूर्ण;


/* Generic Entry Including Header */
काष्ठा netxen_minidump_entry अणु
	काष्ठा netxen_common_entry_hdr hdr;
	u32 entry_data00;
	u32 entry_data01;
	u32 entry_data02;
	u32 entry_data03;
	u32 entry_data04;
	u32 entry_data05;
	u32 entry_data06;
	u32 entry_data07;
पूर्ण;

/* Read ROM Header */
काष्ठा netxen_minidump_entry_rdrom अणु
	काष्ठा netxen_common_entry_hdr h;
	जोड़ अणु
		काष्ठा अणु
			u32 select_addr_reg;
		पूर्ण;
		u32 rsvd_0;
	पूर्ण;
	जोड़ अणु
		काष्ठा अणु
			u8 addr_stride;
			u8 addr_cnt;
			u16 data_size;
		पूर्ण;
		u32 rsvd_1;
	पूर्ण;
	जोड़ अणु
		काष्ठा अणु
			u32 op_count;
		पूर्ण;
		u32 rsvd_2;
	पूर्ण;
	जोड़ अणु
		काष्ठा अणु
			u32 पढ़ो_addr_reg;
		पूर्ण;
		u32 rsvd_3;
	पूर्ण;
	जोड़ अणु
		काष्ठा अणु
			u32 ग_लिखो_mask;
		पूर्ण;
		u32 rsvd_4;
	पूर्ण;
	जोड़ अणु
		काष्ठा अणु
			u32 पढ़ो_mask;
		पूर्ण;
		u32 rsvd_5;
	पूर्ण;
	u32 पढ़ो_addr;
	u32 पढ़ो_data_size;
पूर्ण;


/* Read CRB and Control Entry Header */
काष्ठा netxen_minidump_entry_crb अणु
	काष्ठा netxen_common_entry_hdr h;
	u32 addr;
	जोड़ अणु
		काष्ठा अणु
			u8 addr_stride;
			u8 state_index_a;
			u16 poll_समयout;
			पूर्ण;
		u32 addr_cntrl;
	पूर्ण;
	u32 data_size;
	u32 op_count;
	जोड़ अणु
		काष्ठा अणु
			u8 opcode;
			u8 state_index_v;
			u8 shl;
			u8 shr;
			पूर्ण;
		u32 control_value;
	पूर्ण;
	u32 value_1;
	u32 value_2;
	u32 value_3;
पूर्ण;

/* Read Memory and MN Header */
काष्ठा netxen_minidump_entry_rdmem अणु
	काष्ठा netxen_common_entry_hdr h;
	जोड़ अणु
		काष्ठा अणु
			u32 select_addr_reg;
		पूर्ण;
		u32 rsvd_0;
	पूर्ण;
	जोड़ अणु
		काष्ठा अणु
			u8 addr_stride;
			u8 addr_cnt;
			u16 data_size;
		पूर्ण;
		u32 rsvd_1;
	पूर्ण;
	जोड़ अणु
		काष्ठा अणु
			u32 op_count;
		पूर्ण;
		u32 rsvd_2;
	पूर्ण;
	जोड़ अणु
		काष्ठा अणु
			u32 पढ़ो_addr_reg;
		पूर्ण;
		u32 rsvd_3;
	पूर्ण;
	जोड़ अणु
		काष्ठा अणु
			u32 cntrl_addr_reg;
		पूर्ण;
		u32 rsvd_4;
	पूर्ण;
	जोड़ अणु
		काष्ठा अणु
			u8 wr_byte0;
			u8 wr_byte1;
			u8 poll_mask;
			u8 poll_cnt;
		पूर्ण;
		u32 rsvd_5;
	पूर्ण;
	u32 पढ़ो_addr;
	u32 पढ़ो_data_size;
पूर्ण;

/* Read Cache L1 and L2 Header */
काष्ठा netxen_minidump_entry_cache अणु
	काष्ठा netxen_common_entry_hdr h;
	u32 tag_reg_addr;
	जोड़ अणु
		काष्ठा अणु
			u16 tag_value_stride;
			u16 init_tag_value;
		पूर्ण;
		u32 select_addr_cntrl;
	पूर्ण;
	u32 data_size;
	u32 op_count;
	u32 control_addr;
	जोड़ अणु
		काष्ठा अणु
			u16 ग_लिखो_value;
			u8 poll_mask;
			u8 poll_रुको;
		पूर्ण;
		u32 control_value;
	पूर्ण;
	u32 पढ़ो_addr;
	जोड़ अणु
		काष्ठा अणु
			u8 पढ़ो_addr_stride;
			u8 पढ़ो_addr_cnt;
			u16 rsvd_1;
		पूर्ण;
		u32 पढ़ो_addr_cntrl;
	पूर्ण;
पूर्ण;

/* Read OCM Header */
काष्ठा netxen_minidump_entry_rकरोcm अणु
	काष्ठा netxen_common_entry_hdr h;
	u32 rsvd_0;
	जोड़ अणु
		काष्ठा अणु
			u32 rsvd_1;
		पूर्ण;
		u32 select_addr_cntrl;
	पूर्ण;
	u32 data_size;
	u32 op_count;
	u32 rsvd_2;
	u32 rsvd_3;
	u32 पढ़ो_addr;
	जोड़ अणु
		काष्ठा अणु
			u32 पढ़ो_addr_stride;
		पूर्ण;
		u32 पढ़ो_addr_cntrl;
	पूर्ण;
पूर्ण;

/* Read MUX Header */
काष्ठा netxen_minidump_entry_mux अणु
	काष्ठा netxen_common_entry_hdr h;
	u32 select_addr;
	जोड़ अणु
		काष्ठा अणु
			u32 rsvd_0;
		पूर्ण;
		u32 select_addr_cntrl;
	पूर्ण;
	u32 data_size;
	u32 op_count;
	u32 select_value;
	u32 select_value_stride;
	u32 पढ़ो_addr;
	u32 rsvd_1;
पूर्ण;

/* Read Queue Header */
काष्ठा netxen_minidump_entry_queue अणु
	काष्ठा netxen_common_entry_hdr h;
	u32 select_addr;
	जोड़ अणु
		काष्ठा अणु
			u16 queue_id_stride;
			u16 rsvd_0;
		पूर्ण;
		u32 select_addr_cntrl;
	पूर्ण;
	u32 data_size;
	u32 op_count;
	u32 rsvd_1;
	u32 rsvd_2;
	u32 पढ़ो_addr;
	जोड़ अणु
		काष्ठा अणु
			u8 पढ़ो_addr_stride;
			u8 पढ़ो_addr_cnt;
			u16 rsvd_3;
		पूर्ण;
		u32 पढ़ो_addr_cntrl;
	पूर्ण;
पूर्ण;

काष्ठा netxen_dummy_dma अणु
	व्योम *addr;
	dma_addr_t phys_addr;
पूर्ण;

काष्ठा netxen_adapter अणु
	काष्ठा netxen_hardware_context ahw;

	काष्ठा net_device *netdev;
	काष्ठा pci_dev *pdev;
	काष्ठा list_head mac_list;
	काष्ठा list_head ip_list;

	spinlock_t tx_clean_lock;

	u16 num_txd;
	u16 num_rxd;
	u16 num_jumbo_rxd;
	u16 num_lro_rxd;

	u8 max_rds_rings;
	u8 max_sds_rings;
	u8 driver_mismatch;
	u8 msix_supported;
	u8 __pad;
	u8 pci_using_dac;
	u8 portnum;
	u8 physical_port;

	u8 mc_enabled;
	u8 max_mc_count;
	u8 rss_supported;
	u8 link_changed;
	u8 fw_रुको_cnt;
	u8 fw_fail_cnt;
	u8 tx_समयo_cnt;
	u8 need_fw_reset;

	u8 has_link_events;
	u8 fw_type;
	u16 tx_context_id;
	u16 mtu;
	u16 is_up;

	u16 link_speed;
	u16 link_duplex;
	u16 link_स्वतःneg;
	u16 module_type;

	u32 capabilities;
	u32 flags;
	u32 irq;
	u32 temp;

	u32 पूर्णांक_vec_bit;
	u32 heartbit;

	u8 mac_addr[ETH_ALEN];

	काष्ठा netxen_adapter_stats stats;

	काष्ठा netxen_recv_context recv_ctx;
	काष्ठा nx_host_tx_ring *tx_ring;

	पूर्णांक (*macaddr_set) (काष्ठा netxen_adapter *, u8 *);
	पूर्णांक (*set_mtu) (काष्ठा netxen_adapter *, पूर्णांक);
	पूर्णांक (*set_promisc) (काष्ठा netxen_adapter *, u32);
	व्योम (*set_multi) (काष्ठा net_device *);
	पूर्णांक (*phy_पढ़ो) (काष्ठा netxen_adapter *, u32 reg, u32 *);
	पूर्णांक (*phy_ग_लिखो) (काष्ठा netxen_adapter *, u32 reg, u32 val);
	पूर्णांक (*init_port) (काष्ठा netxen_adapter *, पूर्णांक);
	पूर्णांक (*stop_port) (काष्ठा netxen_adapter *);

	u32 (*crb_पढ़ो)(काष्ठा netxen_adapter *, uदीर्घ);
	पूर्णांक (*crb_ग_लिखो)(काष्ठा netxen_adapter *, uदीर्घ, u32);

	पूर्णांक (*pci_mem_पढ़ो)(काष्ठा netxen_adapter *, u64, u64 *);
	पूर्णांक (*pci_mem_ग_लिखो)(काष्ठा netxen_adapter *, u64, u64);

	पूर्णांक (*pci_set_winकरोw)(काष्ठा netxen_adapter *, u64, u32 *);

	u32 (*io_पढ़ो)(काष्ठा netxen_adapter *, व्योम __iomem *);
	व्योम (*io_ग_लिखो)(काष्ठा netxen_adapter *, व्योम __iomem *, u32);

	व्योम __iomem	*tgt_mask_reg;
	व्योम __iomem	*pci_पूर्णांक_reg;
	व्योम __iomem	*tgt_status_reg;
	व्योम __iomem	*crb_पूर्णांक_state_reg;
	व्योम __iomem	*isr_पूर्णांक_vec;

	काष्ठा msix_entry msix_entries[MSIX_ENTRIES_PER_ADAPTER];

	काष्ठा netxen_dummy_dma dummy_dma;

	काष्ठा delayed_work fw_work;

	काष्ठा work_काष्ठा  tx_समयout_task;

	nx_nic_पूर्णांकr_coalesce_t coal;

	अचिन्हित दीर्घ state;
	__le32 file_prd_off;	/*File fw product offset*/
	u32 fw_version;
	स्थिर काष्ठा firmware *fw;
	काष्ठा netxen_minidump mdump;   /* mdump ptr */
	पूर्णांक fw_mdump_rdy;	/* क्रम mdump पढ़ोy */
पूर्ण;

पूर्णांक nx_fw_cmd_query_phy(काष्ठा netxen_adapter *adapter, u32 reg, u32 *val);
पूर्णांक nx_fw_cmd_set_phy(काष्ठा netxen_adapter *adapter, u32 reg, u32 val);

#घोषणा NXRD32(adapter, off) \
	(adapter->crb_पढ़ो(adapter, off))
#घोषणा NXWR32(adapter, off, val) \
	(adapter->crb_ग_लिखो(adapter, off, val))
#घोषणा NXRDIO(adapter, addr) \
	(adapter->io_पढ़ो(adapter, addr))
#घोषणा NXWRIO(adapter, addr, val) \
	(adapter->io_ग_लिखो(adapter, addr, val))

पूर्णांक netxen_pcie_sem_lock(काष्ठा netxen_adapter *, पूर्णांक, u32);
व्योम netxen_pcie_sem_unlock(काष्ठा netxen_adapter *, पूर्णांक);

#घोषणा netxen_rom_lock(a)	\
	netxen_pcie_sem_lock((a), 2, NETXEN_ROM_LOCK_ID)
#घोषणा netxen_rom_unlock(a)	\
	netxen_pcie_sem_unlock((a), 2)
#घोषणा netxen_phy_lock(a)	\
	netxen_pcie_sem_lock((a), 3, NETXEN_PHY_LOCK_ID)
#घोषणा netxen_phy_unlock(a)	\
	netxen_pcie_sem_unlock((a), 3)
#घोषणा netxen_api_lock(a)	\
	netxen_pcie_sem_lock((a), 5, 0)
#घोषणा netxen_api_unlock(a)	\
	netxen_pcie_sem_unlock((a), 5)
#घोषणा netxen_sw_lock(a)	\
	netxen_pcie_sem_lock((a), 6, 0)
#घोषणा netxen_sw_unlock(a)	\
	netxen_pcie_sem_unlock((a), 6)
#घोषणा crb_win_lock(a)	\
	netxen_pcie_sem_lock((a), 7, NETXEN_CRB_WIN_LOCK_ID)
#घोषणा crb_win_unlock(a)	\
	netxen_pcie_sem_unlock((a), 7)

पूर्णांक netxen_nic_get_board_info(काष्ठा netxen_adapter *adapter);
पूर्णांक netxen_nic_wol_supported(काष्ठा netxen_adapter *adapter);

/* Functions from netxen_nic_init.c */
पूर्णांक netxen_init_dummy_dma(काष्ठा netxen_adapter *adapter);
व्योम netxen_मुक्त_dummy_dma(काष्ठा netxen_adapter *adapter);

पूर्णांक netxen_check_flash_fw_compatibility(काष्ठा netxen_adapter *adapter);
पूर्णांक netxen_phantom_init(काष्ठा netxen_adapter *adapter, पूर्णांक pegtune_val);
पूर्णांक netxen_load_firmware(काष्ठा netxen_adapter *adapter);
पूर्णांक netxen_need_fw_reset(काष्ठा netxen_adapter *adapter);
व्योम netxen_request_firmware(काष्ठा netxen_adapter *adapter);
व्योम netxen_release_firmware(काष्ठा netxen_adapter *adapter);
पूर्णांक netxen_pinit_from_rom(काष्ठा netxen_adapter *adapter);

पूर्णांक netxen_rom_fast_पढ़ो(काष्ठा netxen_adapter *adapter, पूर्णांक addr, पूर्णांक *valp);
पूर्णांक netxen_rom_fast_पढ़ो_words(काष्ठा netxen_adapter *adapter, पूर्णांक addr,
				u8 *bytes, माप_प्रकार size);
पूर्णांक netxen_rom_fast_ग_लिखो_words(काष्ठा netxen_adapter *adapter, पूर्णांक addr,
				u8 *bytes, माप_प्रकार size);
पूर्णांक netxen_flash_unlock(काष्ठा netxen_adapter *adapter);
पूर्णांक netxen_backup_crbinit(काष्ठा netxen_adapter *adapter);
पूर्णांक netxen_flash_erase_secondary(काष्ठा netxen_adapter *adapter);
पूर्णांक netxen_flash_erase_primary(काष्ठा netxen_adapter *adapter);
व्योम netxen_halt_pegs(काष्ठा netxen_adapter *adapter);

पूर्णांक netxen_rom_se(काष्ठा netxen_adapter *adapter, पूर्णांक addr);

पूर्णांक netxen_alloc_sw_resources(काष्ठा netxen_adapter *adapter);
व्योम netxen_मुक्त_sw_resources(काष्ठा netxen_adapter *adapter);

व्योम netxen_setup_hwops(काष्ठा netxen_adapter *adapter);
व्योम __iomem *netxen_get_ioaddr(काष्ठा netxen_adapter *, u32);

पूर्णांक netxen_alloc_hw_resources(काष्ठा netxen_adapter *adapter);
व्योम netxen_मुक्त_hw_resources(काष्ठा netxen_adapter *adapter);

व्योम netxen_release_rx_buffers(काष्ठा netxen_adapter *adapter);
व्योम netxen_release_tx_buffers(काष्ठा netxen_adapter *adapter);

पूर्णांक netxen_init_firmware(काष्ठा netxen_adapter *adapter);
व्योम netxen_nic_clear_stats(काष्ठा netxen_adapter *adapter);
व्योम netxen_watchकरोg_task(काष्ठा work_काष्ठा *work);
व्योम netxen_post_rx_buffers(काष्ठा netxen_adapter *adapter, u32 ringid,
		काष्ठा nx_host_rds_ring *rds_ring);
पूर्णांक netxen_process_cmd_ring(काष्ठा netxen_adapter *adapter);
पूर्णांक netxen_process_rcv_ring(काष्ठा nx_host_sds_ring *sds_ring, पूर्णांक max);

व्योम netxen_p3_मुक्त_mac_list(काष्ठा netxen_adapter *adapter);
पूर्णांक netxen_config_पूर्णांकr_coalesce(काष्ठा netxen_adapter *adapter);
पूर्णांक netxen_config_rss(काष्ठा netxen_adapter *adapter, पूर्णांक enable);
पूर्णांक netxen_config_ipaddr(काष्ठा netxen_adapter *adapter, __be32 ip, पूर्णांक cmd);
पूर्णांक netxen_linkevent_request(काष्ठा netxen_adapter *adapter, पूर्णांक enable);
व्योम netxen_advert_link_change(काष्ठा netxen_adapter *adapter, पूर्णांक linkup);
व्योम netxen_pci_camqm_पढ़ो_2M(काष्ठा netxen_adapter *, u64, u64 *);
व्योम netxen_pci_camqm_ग_लिखो_2M(काष्ठा netxen_adapter *, u64, u64);

पूर्णांक nx_fw_cmd_set_gbe_port(काष्ठा netxen_adapter *adapter,
				u32 speed, u32 duplex, u32 स्वतःneg);
पूर्णांक nx_fw_cmd_set_mtu(काष्ठा netxen_adapter *adapter, पूर्णांक mtu);
पूर्णांक netxen_nic_change_mtu(काष्ठा net_device *netdev, पूर्णांक new_mtu);
पूर्णांक netxen_config_hw_lro(काष्ठा netxen_adapter *adapter, पूर्णांक enable);
पूर्णांक netxen_config_bridged_mode(काष्ठा netxen_adapter *adapter, पूर्णांक enable);
पूर्णांक netxen_send_lro_cleanup(काष्ठा netxen_adapter *adapter);
पूर्णांक netxen_setup_minidump(काष्ठा netxen_adapter *adapter);
व्योम netxen_dump_fw(काष्ठा netxen_adapter *adapter);
व्योम netxen_nic_update_cmd_producer(काष्ठा netxen_adapter *adapter,
		काष्ठा nx_host_tx_ring *tx_ring);

/* Functions from netxen_nic_मुख्य.c */
पूर्णांक netxen_nic_reset_context(काष्ठा netxen_adapter *);

पूर्णांक nx_dev_request_reset(काष्ठा netxen_adapter *adapter);

/*
 * NetXen Board inक्रमmation
 */

#घोषणा NETXEN_MAX_SHORT_NAME 32
काष्ठा netxen_brdinfo अणु
	पूर्णांक brdtype;	/* type of board */
	दीर्घ ports;		/* max no of physical ports */
	अक्षर लघु_name[NETXEN_MAX_SHORT_NAME];
पूर्ण;

काष्ठा netxen_dimm_cfg अणु
	u8 presence;
	u8 mem_type;
	u8 dimm_type;
	u32 size;
पूर्ण;

अटल स्थिर काष्ठा netxen_brdinfo netxen_boards[] = अणु
	अणुNETXEN_BRDTYPE_P2_SB31_10G_CX4, 1, "XGb CX4"पूर्ण,
	अणुNETXEN_BRDTYPE_P2_SB31_10G_HMEZ, 1, "XGb HMEZ"पूर्ण,
	अणुNETXEN_BRDTYPE_P2_SB31_10G_IMEZ, 2, "XGb IMEZ"पूर्ण,
	अणुNETXEN_BRDTYPE_P2_SB31_10G, 1, "XGb XFP"पूर्ण,
	अणुNETXEN_BRDTYPE_P2_SB35_4G, 4, "Quad Gb"पूर्ण,
	अणुNETXEN_BRDTYPE_P2_SB31_2G, 2, "Dual Gb"पूर्ण,
	अणुNETXEN_BRDTYPE_P3_REF_QG,  4, "Reference Quad Gig "पूर्ण,
	अणुNETXEN_BRDTYPE_P3_HMEZ,    2, "Dual XGb HMEZ"पूर्ण,
	अणुNETXEN_BRDTYPE_P3_10G_CX4_LP,   2, "Dual XGb CX4 LP"पूर्ण,
	अणुNETXEN_BRDTYPE_P3_4_GB,    4, "Quad Gig LP"पूर्ण,
	अणुNETXEN_BRDTYPE_P3_IMEZ,    2, "Dual XGb IMEZ"पूर्ण,
	अणुNETXEN_BRDTYPE_P3_10G_SFP_PLUS, 2, "Dual XGb SFP+ LP"पूर्ण,
	अणुNETXEN_BRDTYPE_P3_10000_BASE_T, 1, "XGB 10G BaseT LP"पूर्ण,
	अणुNETXEN_BRDTYPE_P3_XG_LOM,  2, "Dual XGb LOM"पूर्ण,
	अणुNETXEN_BRDTYPE_P3_4_GB_MM, 4, "NX3031 Gigabit Ethernet"पूर्ण,
	अणुNETXEN_BRDTYPE_P3_10G_SFP_CT, 2, "NX3031 10 Gigabit Ethernet"पूर्ण,
	अणुNETXEN_BRDTYPE_P3_10G_SFP_QT, 2, "Quanta Dual XGb SFP+"पूर्ण,
	अणुNETXEN_BRDTYPE_P3_10G_CX4, 2, "Reference Dual CX4 Option"पूर्ण,
	अणुNETXEN_BRDTYPE_P3_10G_XFP, 1, "Reference Single XFP Option"पूर्ण
पूर्ण;

#घोषणा NUM_SUPPORTED_BOARDS ARRAY_SIZE(netxen_boards)

अटल अंतरभूत पूर्णांक netxen_nic_get_brd_name_by_type(u32 type, अक्षर *name)
अणु
	पूर्णांक i, found = 0;
	क्रम (i = 0; i < NUM_SUPPORTED_BOARDS; ++i) अणु
		अगर (netxen_boards[i].brdtype == type) अणु
			म_नकल(name, netxen_boards[i].लघु_name);
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found) अणु
		म_नकल(name, "Unknown");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत u32 netxen_tx_avail(काष्ठा nx_host_tx_ring *tx_ring)
अणु
	smp_mb();
	वापस find_dअगरf_among(tx_ring->producer,
			tx_ring->sw_consumer, tx_ring->num_desc);

पूर्ण

पूर्णांक netxen_get_flash_mac_addr(काष्ठा netxen_adapter *adapter, u64 *mac);
पूर्णांक netxen_p3_get_mac_addr(काष्ठा netxen_adapter *adapter, u64 *mac);
व्योम netxen_change_ringparam(काष्ठा netxen_adapter *adapter);
पूर्णांक netxen_rom_fast_पढ़ो(काष्ठा netxen_adapter *adapter, पूर्णांक addr, पूर्णांक *valp);

बाह्य स्थिर काष्ठा ethtool_ops netxen_nic_ethtool_ops;

#पूर्ण_अगर				/* __NETXEN_NIC_H_ */
