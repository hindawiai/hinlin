<शैली गुरु>
/**********************************************************************
 * Author: Cavium, Inc.
 *
 * Contact: support@cavium.com
 *          Please include "LiquidIO" in the subject.
 *
 * Copyright (c) 2003-2016 Cavium, Inc.
 *
 * This file is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License, Version 2, as
 * published by the Free Software Foundation.
 *
 * This file is distributed in the hope that it will be useful, but
 * AS-IS and WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE, TITLE, or
 * NONINFRINGEMENT.  See the GNU General Public License क्रम more details.
 ***********************************************************************/
/*!  \पile  liquidio_common.h
 *   \मrief Common: Structures and macros used in PCI-NIC package by core and
 *   host driver.
 */

#अगर_अघोषित __LIQUIDIO_COMMON_H__
#घोषणा __LIQUIDIO_COMMON_H__

#समावेश "octeon_config.h"

#घोषणा LIQUIDIO_BASE_MAJOR_VERSION 1
#घोषणा LIQUIDIO_BASE_MINOR_VERSION 7
#घोषणा LIQUIDIO_BASE_MICRO_VERSION 2
#घोषणा LIQUIDIO_BASE_VERSION   __stringअगरy(LIQUIDIO_BASE_MAJOR_VERSION) "." \
				__stringअगरy(LIQUIDIO_BASE_MINOR_VERSION)

काष्ठा lio_version अणु
	u16  major;
	u16  minor;
	u16  micro;
	u16  reserved;
पूर्ण;

#घोषणा CONTROL_IQ 0
/** Tag types used by Octeon cores in its work. */
क्रमागत octeon_tag_type अणु
	ORDERED_TAG = 0,
	ATOMIC_TAG = 1,
	शून्य_TAG = 2,
	शून्य_शून्य_TAG = 3
पूर्ण;

/* pre-defined host->NIC tag values */
#घोषणा LIO_CONTROL  (0x11111110)
#घोषणा LIO_DATA(i)  (0x11111111 + (i))

/* Opcodes used by host driver/apps to perक्रमm operations on the core.
 * These are used to identअगरy the major subप्रणाली that the operation
 * is क्रम.
 */
#घोषणा OPCODE_CORE 0           /* used क्रम generic core operations */
#घोषणा OPCODE_NIC  1           /* used क्रम NIC operations */
/* Subcodes are used by host driver/apps to identअगरy the sub-operation
 * क्रम the core. They only need to by unique क्रम a given subप्रणाली.
 */
#घोषणा OPCODE_SUBCODE(op, sub)       ((((op) & 0x0f) << 8) | ((sub) & 0x7f))

/** OPCODE_CORE subcodes. For future use. */

/** OPCODE_NIC subcodes */

/* This subcode is sent by core PCI driver to indicate cores are पढ़ोy. */
#घोषणा OPCODE_NIC_CORE_DRV_ACTIVE     0x01
#घोषणा OPCODE_NIC_NW_DATA             0x02     /* network packet data */
#घोषणा OPCODE_NIC_CMD                 0x03
#घोषणा OPCODE_NIC_INFO                0x04
#घोषणा OPCODE_NIC_PORT_STATS          0x05
#घोषणा OPCODE_NIC_MDIO45              0x06
#घोषणा OPCODE_NIC_TIMESTAMP           0x07
#घोषणा OPCODE_NIC_INTRMOD_CFG         0x08
#घोषणा OPCODE_NIC_IF_CFG              0x09
#घोषणा OPCODE_NIC_VF_DRV_NOTICE       0x0A
#घोषणा OPCODE_NIC_INTRMOD_PARAMS      0x0B
#घोषणा OPCODE_NIC_QCOUNT_UPDATE       0x12
#घोषणा OPCODE_NIC_SET_TRUSTED_VF	0x13
#घोषणा OPCODE_NIC_SYNC_OCTEON_TIME	0x14
#घोषणा VF_DRV_LOADED                  1
#घोषणा VF_DRV_REMOVED                -1
#घोषणा VF_DRV_MACADDR_CHANGED         2

#घोषणा OPCODE_NIC_VF_REP_PKT          0x15
#घोषणा OPCODE_NIC_VF_REP_CMD          0x16
#घोषणा OPCODE_NIC_UBOOT_CTL           0x17

#घोषणा CORE_DRV_TEST_SCATTER_OP    0xFFF5

/* Application codes advertised by the core driver initialization packet. */
#घोषणा CVM_DRV_APP_START           0x0
#घोषणा CVM_DRV_NO_APP              0
#घोषणा CVM_DRV_APP_COUNT           0x2
#घोषणा CVM_DRV_BASE_APP            (CVM_DRV_APP_START + 0x0)
#घोषणा CVM_DRV_NIC_APP             (CVM_DRV_APP_START + 0x1)
#घोषणा CVM_DRV_INVALID_APP         (CVM_DRV_APP_START + 0x2)
#घोषणा CVM_DRV_APP_END             (CVM_DRV_INVALID_APP - 1)

#घोषणा BYTES_PER_DHLEN_UNIT        8
#घोषणा MAX_REG_CNT                 2000000U
#घोषणा INTRNAMSIZ                  32
#घोषणा IRQ_NAME_OFF(i)             ((i) * INTRNAMSIZ)
#घोषणा MAX_IOQ_INTERRUPTS_PER_PF   (64 * 2)
#घोषणा MAX_IOQ_INTERRUPTS_PER_VF   (8 * 2)

#घोषणा SCR2_BIT_FW_LOADED	    63

/* App specअगरic capabilities from firmware to pf driver */
#घोषणा LIQUIDIO_TIME_SYNC_CAP 0x1
#घोषणा LIQUIDIO_SWITCHDEV_CAP 0x2
#घोषणा LIQUIDIO_SPOOFCHK_CAP  0x4

/* error status वापस from firmware */
#घोषणा OCTEON_REQUEST_NO_PERMISSION 0xc

अटल अंतरभूत u32 incr_index(u32 index, u32 count, u32 max)
अणु
	अगर ((index + count) >= max)
		index = index + count - max;
	अन्यथा
		index += count;

	वापस index;
पूर्ण

#घोषणा OCT_BOARD_NAME 32
#घोषणा OCT_SERIAL_LEN 64

/* Structure used by core driver to send indication that the Octeon
 * application is पढ़ोy.
 */
काष्ठा octeon_core_setup अणु
	u64 corefreq;

	अक्षर boardname[OCT_BOARD_NAME];

	अक्षर board_serial_number[OCT_SERIAL_LEN];

	u64 board_rev_major;

	u64 board_rev_minor;

पूर्ण;

/*---------------------------  SCATTER GATHER ENTRY  -----------------------*/

/* The Scatter-Gather List Entry. The scatter or gather component used with
 * a Octeon input inकाष्ठाion has this क्रमmat.
 */
काष्ठा octeon_sg_entry अणु
	/** The first 64 bit gives the size of data in each dptr.*/
	जोड़ अणु
		u16 size[4];
		u64 size64;
	पूर्ण u;

	/** The 4 dptr poपूर्णांकers क्रम this entry. */
	u64 ptr[4];

पूर्ण;

#घोषणा OCT_SG_ENTRY_SIZE    (माप(काष्ठा octeon_sg_entry))

/* \मrief Add size to gather list
 * @param sg_entry scatter/gather entry
 * @param size size to add
 * @param pos position to add it.
 */
अटल अंतरभूत व्योम add_sg_size(काष्ठा octeon_sg_entry *sg_entry,
			       u16 size,
			       u32 pos)
अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
	sg_entry->u.size[pos] = size;
#अन्यथा
	sg_entry->u.size[3 - pos] = size;
#पूर्ण_अगर
पूर्ण

/*------------------------- End Scatter/Gather ---------------------------*/

#घोषणा   OCTNET_FRM_LENGTH_SIZE      8

#घोषणा   OCTNET_FRM_PTP_HEADER_SIZE  8

#घोषणा   OCTNET_FRM_HEADER_SIZE     22 /* VLAN + Ethernet */

#घोषणा   OCTNET_MIN_FRM_SIZE        64

#घोषणा   OCTNET_MAX_FRM_SIZE        (16000 + OCTNET_FRM_HEADER_SIZE)

#घोषणा   OCTNET_DEFAULT_MTU         (1500)
#घोषणा   OCTNET_DEFAULT_FRM_SIZE  (OCTNET_DEFAULT_MTU + OCTNET_FRM_HEADER_SIZE)

/** NIC Commands are sent using this Octeon Input Queue */
#घोषणा   OCTNET_CMD_Q                0

/* NIC Command types */
#घोषणा   OCTNET_CMD_CHANGE_MTU       0x1
#घोषणा   OCTNET_CMD_CHANGE_MACADDR   0x2
#घोषणा   OCTNET_CMD_CHANGE_DEVFLAGS  0x3
#घोषणा   OCTNET_CMD_RX_CTL           0x4

#घोषणा	  OCTNET_CMD_SET_MULTI_LIST   0x5
#घोषणा   OCTNET_CMD_CLEAR_STATS      0x6

/* command क्रम setting the speed, duplex & स्वतःneg */
#घोषणा   OCTNET_CMD_SET_SETTINGS     0x7
#घोषणा   OCTNET_CMD_SET_FLOW_CTL     0x8

#घोषणा   OCTNET_CMD_MDIO_READ_WRITE  0x9
#घोषणा   OCTNET_CMD_GPIO_ACCESS      0xA
#घोषणा   OCTNET_CMD_LRO_ENABLE       0xB
#घोषणा   OCTNET_CMD_LRO_DISABLE      0xC
#घोषणा   OCTNET_CMD_SET_RSS          0xD
#घोषणा   OCTNET_CMD_WRITE_SA         0xE
#घोषणा   OCTNET_CMD_DELETE_SA        0xF
#घोषणा   OCTNET_CMD_UPDATE_SA        0x12

#घोषणा   OCTNET_CMD_TNL_RX_CSUM_CTL 0x10
#घोषणा   OCTNET_CMD_TNL_TX_CSUM_CTL 0x11
#घोषणा   OCTNET_CMD_IPSECV2_AH_ESP_CTL 0x13
#घोषणा   OCTNET_CMD_VERBOSE_ENABLE   0x14
#घोषणा   OCTNET_CMD_VERBOSE_DISABLE  0x15

#घोषणा   OCTNET_CMD_VLAN_FILTER_CTL 0x16
#घोषणा   OCTNET_CMD_ADD_VLAN_FILTER  0x17
#घोषणा   OCTNET_CMD_DEL_VLAN_FILTER  0x18
#घोषणा   OCTNET_CMD_VXLAN_PORT_CONFIG 0x19

#घोषणा   OCTNET_CMD_ID_ACTIVE         0x1a

#घोषणा   OCTNET_CMD_SET_UC_LIST       0x1b
#घोषणा   OCTNET_CMD_SET_VF_LINKSTATE  0x1c

#घोषणा   OCTNET_CMD_QUEUE_COUNT_CTL	0x1f

#घोषणा   OCTNET_CMD_GROUP1             1
#घोषणा   OCTNET_CMD_SET_VF_SPOOFCHK    0x1
#घोषणा   OCTNET_GROUP1_LAST_CMD        OCTNET_CMD_SET_VF_SPOOFCHK

#घोषणा   OCTNET_CMD_VXLAN_PORT_ADD    0x0
#घोषणा   OCTNET_CMD_VXLAN_PORT_DEL    0x1
#घोषणा   OCTNET_CMD_RXCSUM_ENABLE     0x0
#घोषणा   OCTNET_CMD_RXCSUM_DISABLE    0x1
#घोषणा   OCTNET_CMD_TXCSUM_ENABLE     0x0
#घोषणा   OCTNET_CMD_TXCSUM_DISABLE    0x1
#घोषणा   OCTNET_CMD_VLAN_FILTER_ENABLE 0x1
#घोषणा   OCTNET_CMD_VLAN_FILTER_DISABLE 0x0

#घोषणा   OCTNET_CMD_FAIL 0x1

#घोषणा   SEAPI_CMD_FEC_SET             0x0
#घोषणा   SEAPI_CMD_FEC_SET_DISABLE       0x0
#घोषणा   SEAPI_CMD_FEC_SET_RS            0x1
#घोषणा   SEAPI_CMD_FEC_GET             0x1

#घोषणा   SEAPI_CMD_SPEED_SET           0x2
#घोषणा   SEAPI_CMD_SPEED_GET           0x3

#घोषणा OPCODE_NIC_VF_PORT_STATS        0x22

#घोषणा   LIO_CMD_WAIT_TM 100

/* RX(packets coming from wire) Checksum verअगरication flags */
/* TCP/UDP csum */
#घोषणा   CNNIC_L4SUM_VERIFIED             0x1
#घोषणा   CNNIC_IPSUM_VERIFIED             0x2
#घोषणा   CNNIC_TUN_CSUM_VERIFIED          0x4
#घोषणा   CNNIC_CSUM_VERIFIED (CNNIC_IPSUM_VERIFIED | CNNIC_L4SUM_VERIFIED)

/*LROIPV4 and LROIPV6 Flags*/
#घोषणा   OCTNIC_LROIPV4    0x1
#घोषणा   OCTNIC_LROIPV6    0x2

/* Interface flags communicated between host driver and core app. */
क्रमागत octnet_अगरflags अणु
	OCTNET_IFFLAG_PROMISC   = 0x01,
	OCTNET_IFFLAG_ALLMULTI  = 0x02,
	OCTNET_IFFLAG_MULTICAST = 0x04,
	OCTNET_IFFLAG_BROADCAST = 0x08,
	OCTNET_IFFLAG_UNICAST   = 0x10
पूर्ण;

/*   wqe
 *  ---------------  0
 * |  wqe  word0-3 |
 *  ---------------  32
 * |    PCI IH     |
 *  ---------------  40
 * |     RPTR      |
 *  ---------------  48
 * |    PCI IRH    |
 *  ---------------  56
 * |  OCT_NET_CMD  |
 *  ---------------  64
 * | Addtl 8-BData |
 * |               |
 *  ---------------
 */

जोड़ octnet_cmd अणु
	u64 u64;

	काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		u64 cmd:5;

		u64 more:6; /* How many udd words follow the command */

		u64 cmdgroup:8;
		u64 reserved:21;

		u64 param1:16;

		u64 param2:8;

#अन्यथा

		u64 param2:8;

		u64 param1:16;

		u64 reserved:21;
		u64 cmdgroup:8;

		u64 more:6;

		u64 cmd:5;

#पूर्ण_अगर
	पूर्ण s;

पूर्ण;

#घोषणा   OCTNET_CMD_SIZE     (माप(जोड़ octnet_cmd))

/*pkiih3 + irh + ossp[0] + ossp[1] + rdp + rptr = 40 bytes */
#घोषणा LIO_SOFTCMDRESP_IH2       40
#घोषणा LIO_SOFTCMDRESP_IH3       (40 + 8)

#घोषणा LIO_PCICMD_O2             24
#घोषणा LIO_PCICMD_O3             (24 + 8)

/* Inकाष्ठाion Header(DPI) - क्रम OCTEON-III models */
काष्ठा  octeon_instr_ih3 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD

	/** Reserved3 */
	u64     reserved3:1;

	/** Gather indicator 1=gather*/
	u64     gather:1;

	/** Data length OR no. of entries in gather list */
	u64     dlengsz:14;

	/** Front Data size */
	u64     fsz:6;

	/** Reserved2 */
	u64     reserved2:4;

	/** PKI port kind - PKIND */
	u64     pkind:6;

	/** Reserved1 */
	u64     reserved1:32;

#अन्यथा
	/** Reserved1 */
	u64     reserved1:32;

	/** PKI port kind - PKIND */
	u64     pkind:6;

	/** Reserved2 */
	u64     reserved2:4;

	/** Front Data size */
	u64     fsz:6;

	/** Data length OR no. of entries in gather list */
	u64     dlengsz:14;

	/** Gather indicator 1=gather*/
	u64     gather:1;

	/** Reserved3 */
	u64     reserved3:1;

#पूर्ण_अगर
पूर्ण;

/* Optional PKI Inकाष्ठाion Header(PKI IH) - क्रम OCTEON-III models */
/** BIG ENDIAN क्रमmat.   */
काष्ठा  octeon_instr_pki_ih3 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD

	/** Wider bit */
	u64     w:1;

	/** Raw mode indicator 1 = RAW */
	u64     raw:1;

	/** Use Tag */
	u64     utag:1;

	/** Use QPG */
	u64     uqpg:1;

	/** Reserved2 */
	u64     reserved2:1;

	/** Parse Mode */
	u64     pm:3;

	/** Skip Length */
	u64     sl:8;

	/** Use Tag Type */
	u64     utt:1;

	/** Tag type */
	u64     tagtype:2;

	/** Reserved1 */
	u64     reserved1:2;

	/** QPG Value */
	u64     qpg:11;

	/** Tag Value */
	u64     tag:32;

#अन्यथा

	/** Tag Value */
	u64     tag:32;

	/** QPG Value */
	u64     qpg:11;

	/** Reserved1 */
	u64     reserved1:2;

	/** Tag type */
	u64     tagtype:2;

	/** Use Tag Type */
	u64     utt:1;

	/** Skip Length */
	u64     sl:8;

	/** Parse Mode */
	u64     pm:3;

	/** Reserved2 */
	u64     reserved2:1;

	/** Use QPG */
	u64     uqpg:1;

	/** Use Tag */
	u64     utag:1;

	/** Raw mode indicator 1 = RAW */
	u64     raw:1;

	/** Wider bit */
	u64     w:1;
#पूर्ण_अगर

पूर्ण;

/** Inकाष्ठाion Header */
काष्ठा octeon_instr_ih2 अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
	/** Raw mode indicator 1 = RAW */
	u64 raw:1;

	/** Gather indicator 1=gather*/
	u64 gather:1;

	/** Data length OR no. of entries in gather list */
	u64 dlengsz:14;

	/** Front Data size */
	u64 fsz:6;

	/** Packet Order / Work Unit selection (1 of 8)*/
	u64 qos:3;

	/** Core group selection (1 of 16) */
	u64 grp:4;

	/** Short Raw Packet Indicator 1=लघु raw pkt */
	u64 rs:1;

	/** Tag type */
	u64 tagtype:2;

	/** Tag Value */
	u64 tag:32;
#अन्यथा
	/** Tag Value */
	u64 tag:32;

	/** Tag type */
	u64 tagtype:2;

	/** Short Raw Packet Indicator 1=लघु raw pkt */
	u64 rs:1;

	/** Core group selection (1 of 16) */
	u64 grp:4;

	/** Packet Order / Work Unit selection (1 of 8)*/
	u64 qos:3;

	/** Front Data size */
	u64 fsz:6;

	/** Data length OR no. of entries in gather list */
	u64 dlengsz:14;

	/** Gather indicator 1=gather*/
	u64 gather:1;

	/** Raw mode indicator 1 = RAW */
	u64 raw:1;
#पूर्ण_अगर
पूर्ण;

/** Input Request Header */
काष्ठा octeon_instr_irh अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
	u64 opcode:4;
	u64 rflag:1;
	u64 subcode:7;
	u64 vlan:12;
	u64 priority:3;
	u64 reserved:5;
	u64 ossp:32;             /* opcode/subcode specअगरic parameters */
#अन्यथा
	u64 ossp:32;             /* opcode/subcode specअगरic parameters */
	u64 reserved:5;
	u64 priority:3;
	u64 vlan:12;
	u64 subcode:7;
	u64 rflag:1;
	u64 opcode:4;
#पूर्ण_अगर
पूर्ण;

/** Return Data Parameters */
काष्ठा octeon_instr_rdp अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
	u64 reserved:49;
	u64 pcie_port:3;
	u64 rlen:12;
#अन्यथा
	u64 rlen:12;
	u64 pcie_port:3;
	u64 reserved:49;
#पूर्ण_अगर
पूर्ण;

/** Receive Header */
जोड़ octeon_rh अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
	u64 u64;
	काष्ठा अणु
		u64 opcode:4;
		u64 subcode:8;
		u64 len:3;     /** additional 64-bit words */
		u64 reserved:17;
		u64 ossp:32;   /** opcode/subcode specअगरic parameters */
	पूर्ण r;
	काष्ठा अणु
		u64 opcode:4;
		u64 subcode:8;
		u64 len:3;     /** additional 64-bit words */
		u64 extra:28;
		u64 vlan:12;
		u64 priority:3;
		u64 csum_verअगरied:3;     /** checksum verअगरied. */
		u64 has_hwtstamp:1;      /** Has hardware बारtamp. 1 = yes. */
		u64 encap_on:1;
		u64 has_hash:1;          /** Has hash (rth or rss). 1 = yes. */
	पूर्ण r_dh;
	काष्ठा अणु
		u64 opcode:4;
		u64 subcode:8;
		u64 len:3;     /** additional 64-bit words */
		u64 reserved:11;
		u64 num_gmx_ports:8;
		u64 max_nic_ports:10;
		u64 app_cap_flags:4;
		u64 app_mode:8;
		u64 pkind:8;
	पूर्ण r_core_drv_init;
	काष्ठा अणु
		u64 opcode:4;
		u64 subcode:8;
		u64 len:3;       /** additional 64-bit words */
		u64 reserved:8;
		u64 extra:25;
		u64 gmxport:16;
	पूर्ण r_nic_info;
#अन्यथा
	u64 u64;
	काष्ठा अणु
		u64 ossp:32;  /** opcode/subcode specअगरic parameters */
		u64 reserved:17;
		u64 len:3;    /** additional 64-bit words */
		u64 subcode:8;
		u64 opcode:4;
	पूर्ण r;
	काष्ठा अणु
		u64 has_hash:1;          /** Has hash (rth or rss). 1 = yes. */
		u64 encap_on:1;
		u64 has_hwtstamp:1;      /** 1 = has hwtstamp */
		u64 csum_verअगरied:3;     /** checksum verअगरied. */
		u64 priority:3;
		u64 vlan:12;
		u64 extra:28;
		u64 len:3;    /** additional 64-bit words */
		u64 subcode:8;
		u64 opcode:4;
	पूर्ण r_dh;
	काष्ठा अणु
		u64 pkind:8;
		u64 app_mode:8;
		u64 app_cap_flags:4;
		u64 max_nic_ports:10;
		u64 num_gmx_ports:8;
		u64 reserved:11;
		u64 len:3;       /** additional 64-bit words */
		u64 subcode:8;
		u64 opcode:4;
	पूर्ण r_core_drv_init;
	काष्ठा अणु
		u64 gmxport:16;
		u64 extra:25;
		u64 reserved:8;
		u64 len:3;       /** additional 64-bit words */
		u64 subcode:8;
		u64 opcode:4;
	पूर्ण r_nic_info;
#पूर्ण_अगर
पूर्ण;

#घोषणा  OCT_RH_SIZE   (माप(जोड़  octeon_rh))

जोड़ octnic_packet_params अणु
	u32 u32;
	काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		u32 reserved:24;
		u32 ip_csum:1;		/* Perक्रमm IP header checksum(s) */
		/* Perक्रमm Outer transport header checksum */
		u32 transport_csum:1;
		/* Find tunnel, and perक्रमm transport csum. */
		u32 tnl_csum:1;
		u32 tsflag:1;		/* Timestamp this packet */
		u32 ipsec_ops:4;	/* IPsec operation */
#अन्यथा
		u32 ipsec_ops:4;
		u32 tsflag:1;
		u32 tnl_csum:1;
		u32 transport_csum:1;
		u32 ip_csum:1;
		u32 reserved:24;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

/** Status of a RGMII Link on Octeon as seen by core driver. */
जोड़ oct_link_status अणु
	u64 u64;

	काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		u64 duplex:8;
		u64 mtu:16;
		u64 speed:16;
		u64 link_up:1;
		u64 स्वतःneg:1;
		u64 अगर_mode:5;
		u64 छोड़ो:1;
		u64 flashing:1;
		u64 phy_type:5;
		u64 reserved:10;
#अन्यथा
		u64 reserved:10;
		u64 phy_type:5;
		u64 flashing:1;
		u64 छोड़ो:1;
		u64 अगर_mode:5;
		u64 स्वतःneg:1;
		u64 link_up:1;
		u64 speed:16;
		u64 mtu:16;
		u64 duplex:8;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

क्रमागत lio_phy_type अणु
	LIO_PHY_PORT_TP = 0x0,
	LIO_PHY_PORT_FIBRE = 0x1,
	LIO_PHY_PORT_UNKNOWN,
पूर्ण;

/** The txpciq info passed to host from the firmware */

जोड़ oct_txpciq अणु
	u64 u64;

	काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		u64 q_no:8;
		u64 port:8;
		u64 pkind:6;
		u64 use_qpg:1;
		u64 qpg:11;
		u64 reserved0:10;
		u64 ctrl_qpg:11;
		u64 reserved:9;
#अन्यथा
		u64 reserved:9;
		u64 ctrl_qpg:11;
		u64 reserved0:10;
		u64 qpg:11;
		u64 use_qpg:1;
		u64 pkind:6;
		u64 port:8;
		u64 q_no:8;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

/** The rxpciq info passed to host from the firmware */

जोड़ oct_rxpciq अणु
	u64 u64;

	काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		u64 q_no:8;
		u64 reserved:56;
#अन्यथा
		u64 reserved:56;
		u64 q_no:8;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

/** Inक्रमmation क्रम a OCTEON ethernet पूर्णांकerface shared between core & host. */
काष्ठा oct_link_info अणु
	जोड़ oct_link_status link;
	u64 hw_addr;

#अगर_घोषित __BIG_ENDIAN_BITFIELD
	u64 gmxport:16;
	u64 macaddr_is_admin_asgnd:1;
	u64 rsvd:13;
	u64 macaddr_spoofchk:1;
	u64 rsvd1:17;
	u64 num_txpciq:8;
	u64 num_rxpciq:8;
#अन्यथा
	u64 num_rxpciq:8;
	u64 num_txpciq:8;
	u64 rsvd1:17;
	u64 macaddr_spoofchk:1;
	u64 rsvd:13;
	u64 macaddr_is_admin_asgnd:1;
	u64 gmxport:16;
#पूर्ण_अगर

	जोड़ oct_txpciq txpciq[MAX_IOQS_PER_NICIF];
	जोड़ oct_rxpciq rxpciq[MAX_IOQS_PER_NICIF];
पूर्ण;

#घोषणा OCT_LINK_INFO_SIZE   (माप(काष्ठा oct_link_info))

काष्ठा liquidio_अगर_cfg_info अणु
	u64 iqmask; /** mask क्रम IQs enabled क्रम  the port */
	u64 oqmask; /** mask क्रम OQs enabled क्रम the port */
	काष्ठा oct_link_info linfo; /** initial link inक्रमmation */
	अक्षर   liquidio_firmware_version[32];
पूर्ण;

/** Stats क्रम each NIC port in RX direction. */
काष्ठा nic_rx_stats अणु
	/* link-level stats */
	u64 total_rcvd;		/* Received packets */
	u64 bytes_rcvd;		/* Octets of received packets */
	u64 total_bcst;		/* Number of non-dropped L2 broadcast packets */
	u64 total_mcst;		/* Number of non-dropped L2 multicast packets */
	u64 runts;		/* Packets लघुer than allowed */
	u64 ctl_rcvd;		/* Received PAUSE packets */
	u64 fअगरo_err;		/* Packets dropped due to RX FIFO full */
	u64 dmac_drop;		/* Packets dropped by the DMAC filter */
	u64 fcs_err;		/* Sum of fragment, overrun, and FCS errors */
	u64 jabber_err;		/* Packets larger than allowed */
	u64 l2_err;		/* Sum of DMA, parity, PCAM access, no memory,
				 * buffer overflow, malक्रमmed L2 header or
				 * length, oversize errors
				 **/
	u64 frame_err;		/* Sum of IPv4 and L4 checksum errors */
	u64 red_drops;		/* Packets dropped by RED due to buffer
				 * exhaustion
				 **/

	/* firmware stats */
	u64 fw_total_rcvd;
	u64 fw_total_fwd;
	u64 fw_total_fwd_bytes;
	u64 fw_total_mcast;
	u64 fw_total_bcast;

	u64 fw_err_pko;
	u64 fw_err_link;
	u64 fw_err_drop;
	u64 fw_rx_vxlan;
	u64 fw_rx_vxlan_err;

	/* LRO */
	u64 fw_lro_pkts;   /* Number of packets that are LROed      */
	u64 fw_lro_octs;   /* Number of octets that are LROed       */
	u64 fw_total_lro;  /* Number of LRO packets क्रमmed          */
	u64 fw_lro_पातs; /* Number of बार LRO of packet पातed */
	u64 fw_lro_पातs_port;
	u64 fw_lro_पातs_seq;
	u64 fw_lro_पातs_tsval;
	u64 fw_lro_पातs_समयr;	/* Timer setting error */
	/* पूर्णांकrmod: packet क्रमward rate */
	u64 fwd_rate;
पूर्ण;

/** Stats क्रम each NIC port in RX direction. */
काष्ठा nic_tx_stats अणु
	/* link-level stats */
	u64 total_pkts_sent;		/* Total frames sent on the पूर्णांकerface */
	u64 total_bytes_sent;		/* Total octets sent on the पूर्णांकerface */
	u64 mcast_pkts_sent;		/* Packets sent to the multicast DMAC */
	u64 bcast_pkts_sent;		/* Packets sent to a broadcast DMAC */
	u64 ctl_sent;			/* Control/PAUSE packets sent */
	u64 one_collision_sent;		/* Packets sent that experienced a
					 * single collision beक्रमe successful
					 * transmission
					 **/
	u64 multi_collision_sent;	/* Packets sent that experienced
					 * multiple collisions beक्रमe successful
					 * transmission
					 **/
	u64 max_collision_fail;		/* Packets dropped due to excessive
					 * collisions
					 **/
	u64 max_deferral_fail;		/* Packets not sent due to max
					 * deferrals
					 **/
	u64 fअगरo_err;			/* Packets sent that experienced a
					 * transmit underflow and were
					 * truncated
					 **/
	u64 runts;			/* Packets sent with an octet count
					 * lessthan 64
					 **/
	u64 total_collisions;		/* Packets dropped due to excessive
					 * collisions
					 **/

	/* firmware stats */
	u64 fw_total_sent;
	u64 fw_total_fwd;
	u64 fw_total_fwd_bytes;
	u64 fw_total_mcast_sent;
	u64 fw_total_bcast_sent;
	u64 fw_err_pko;
	u64 fw_err_link;
	u64 fw_err_drop;
	u64 fw_err_tso;
	u64 fw_tso;		/* number of tso requests */
	u64 fw_tso_fwd;		/* number of packets segmented in tso */
	u64 fw_tx_vxlan;
	u64 fw_err_pki;
पूर्ण;

काष्ठा oct_link_stats अणु
	काष्ठा nic_rx_stats fromwire;
	काष्ठा nic_tx_stats fromhost;

पूर्ण;

अटल अंतरभूत पूर्णांक opcode_slow_path(जोड़ octeon_rh *rh)
अणु
	u16 subcode1, subcode2;

	subcode1 = OPCODE_SUBCODE((rh)->r.opcode, (rh)->r.subcode);
	subcode2 = OPCODE_SUBCODE(OPCODE_NIC, OPCODE_NIC_NW_DATA);

	वापस (subcode2 != subcode1);
पूर्ण

#घोषणा LIO68XX_LED_CTRL_ADDR     0x3501
#घोषणा LIO68XX_LED_CTRL_CFGON    0x1f
#घोषणा LIO68XX_LED_CTRL_CFGOFF   0x100
#घोषणा LIO68XX_LED_BEACON_ADDR   0x3508
#घोषणा LIO68XX_LED_BEACON_CFGON  0x47fd
#घोषणा LIO68XX_LED_BEACON_CFGOFF 0x11fc
#घोषणा VITESSE_PHY_GPIO_DRIVEON  0x1
#घोषणा VITESSE_PHY_GPIO_CFG      0x8
#घोषणा VITESSE_PHY_GPIO_DRIVखातापूर्णF 0x4
#घोषणा VITESSE_PHY_GPIO_HIGH     0x2
#घोषणा VITESSE_PHY_GPIO_LOW      0x3
#घोषणा LED_IDENTIFICATION_ON     0x1
#घोषणा LED_IDENTIFICATION_OFF    0x0
#घोषणा LIO23XX_COPPERHEAD_LED_GPIO 0x2

काष्ठा oct_mdio_cmd अणु
	u64 op;
	u64 mdio_addr;
	u64 value1;
	u64 value2;
	u64 value3;
पूर्ण;

#घोषणा OCT_LINK_STATS_SIZE   (माप(काष्ठा oct_link_stats))

काष्ठा oct_पूर्णांकrmod_cfg अणु
	u64 rx_enable;
	u64 tx_enable;
	u64 check_पूर्णांकrvl;
	u64 maxpkt_ratethr;
	u64 minpkt_ratethr;
	u64 rx_maxcnt_trigger;
	u64 rx_mincnt_trigger;
	u64 rx_maxपंचांगr_trigger;
	u64 rx_mपूर्णांकmr_trigger;
	u64 tx_mincnt_trigger;
	u64 tx_maxcnt_trigger;
	u64 rx_frames;
	u64 tx_frames;
	u64 rx_usecs;
पूर्ण;

#घोषणा BASE_QUEUE_NOT_REQUESTED 65535

जोड़ oct_nic_अगर_cfg अणु
	u64 u64;
	काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		u64 base_queue:16;
		u64 num_iqueues:16;
		u64 num_oqueues:16;
		u64 gmx_port_id:8;
		u64 vf_id:8;
#अन्यथा
		u64 vf_id:8;
		u64 gmx_port_id:8;
		u64 num_oqueues:16;
		u64 num_iqueues:16;
		u64 base_queue:16;
#पूर्ण_अगर
	पूर्ण s;
पूर्ण;

काष्ठा lio_trusted_vf अणु
	uपूर्णांक64_t active: 1;
	uपूर्णांक64_t id : 8;
	uपूर्णांक64_t reserved: 55;
पूर्ण;

काष्ठा lio_समय अणु
	s64 sec;   /* seconds */
	s64 nsec;  /* nanoseconds */
पूर्ण;

काष्ठा lio_vf_rep_stats अणु
	u64 tx_packets;
	u64 tx_bytes;
	u64 tx_dropped;

	u64 rx_packets;
	u64 rx_bytes;
	u64 rx_dropped;
पूर्ण;

क्रमागत lio_vf_rep_req_type अणु
	LIO_VF_REP_REQ_NONE,
	LIO_VF_REP_REQ_STATE,
	LIO_VF_REP_REQ_MTU,
	LIO_VF_REP_REQ_STATS,
	LIO_VF_REP_REQ_DEVNAME
पूर्ण;

क्रमागत अणु
	LIO_VF_REP_STATE_DOWN,
	LIO_VF_REP_STATE_UP
पूर्ण;

#घोषणा LIO_IF_NAME_SIZE 16
काष्ठा lio_vf_rep_req अणु
	u8 req_type;
	u8 अगरidx;
	u8 rsvd[6];

	जोड़ अणु
		काष्ठा lio_vf_rep_name अणु
			अक्षर name[LIO_IF_NAME_SIZE];
		पूर्ण rep_name;

		काष्ठा lio_vf_rep_mtu अणु
			u32 mtu;
			u32 rsvd;
		पूर्ण rep_mtu;

		काष्ठा lio_vf_rep_state अणु
			u8 state;
			u8 rsvd[7];
		पूर्ण rep_state;
	पूर्ण;
पूर्ण;

काष्ठा lio_vf_rep_resp अणु
	u64 rh;
	u8  status;
	u8  rsvd[7];
पूर्ण;
#पूर्ण_अगर
