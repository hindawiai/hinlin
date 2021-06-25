<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright(c) 2008 - 2009 Atheros Corporation. All rights reserved.
 *
 * Derived from Intel e1000 driver
 * Copyright(c) 1999 - 2005 Intel Corporation. All rights reserved.
 */

#अगर_अघोषित _ATL1C_H_
#घोषणा _ATL1C_H_

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ioport.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/delay.h>
#समावेश <linux/sched.h>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/udp.h>
#समावेश <linux/mii.h>
#समावेश <linux/पन.स>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/tcp.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/workqueue.h>
#समावेश <net/checksum.h>
#समावेश <net/ip6_checksum.h>

#समावेश "atl1c_hw.h"

/* Wake Up Filter Control */
#घोषणा AT_WUFC_LNKC 0x00000001 /* Link Status Change Wakeup Enable */
#घोषणा AT_WUFC_MAG  0x00000002 /* Magic Packet Wakeup Enable */
#घोषणा AT_WUFC_EX   0x00000004 /* Directed Exact Wakeup Enable */
#घोषणा AT_WUFC_MC   0x00000008 /* Multicast Wakeup Enable */
#घोषणा AT_WUFC_BC   0x00000010 /* Broadcast Wakeup Enable */

#घोषणा AT_VLAN_TO_TAG(_vlan, _tag)	   \
	_tag =  ((((_vlan) >> 8) & 0xFF)  |\
		 (((_vlan) & 0xFF) << 8))

#घोषणा AT_TAG_TO_VLAN(_tag, _vlan) 	 \
	_vlan = ((((_tag) >> 8) & 0xFF) |\
		(((_tag) & 0xFF) << 8))

#घोषणा SPEED_0		   0xffff
#घोषणा HALF_DUPLEX        1
#घोषणा FULL_DUPLEX        2

#घोषणा AT_RX_BUF_SIZE		(ETH_FRAME_LEN + VLAN_HLEN + ETH_FCS_LEN)
#घोषणा MAX_JUMBO_FRAME_SIZE	(6*1024)

#घोषणा AT_MAX_RECEIVE_QUEUE    4
#घोषणा AT_DEF_RECEIVE_QUEUE	1
#घोषणा AT_MAX_TRANSMIT_QUEUE	2

#घोषणा AT_DMA_HI_ADDR_MASK     0xffffffff00000000ULL
#घोषणा AT_DMA_LO_ADDR_MASK     0x00000000ffffffffULL

#घोषणा AT_TX_WATCHDOG  (5 * HZ)
#घोषणा AT_MAX_INT_WORK		5
#घोषणा AT_TWSI_EEPROM_TIMEOUT 	100
#घोषणा AT_HW_MAX_IDLE_DELAY 	10
#घोषणा AT_SUSPEND_LINK_TIMEOUT 100

#घोषणा AT_ASPM_L0S_TIMER	6
#घोषणा AT_ASPM_L1_TIMER	12
#घोषणा AT_LCKDET_TIMER		12

#घोषणा ATL1C_PCIE_L0S_L1_DISABLE 	0x01
#घोषणा ATL1C_PCIE_PHY_RESET		0x02

#घोषणा ATL1C_ASPM_L0s_ENABLE		0x0001
#घोषणा ATL1C_ASPM_L1_ENABLE		0x0002

#घोषणा AT_REGS_LEN	(74 * माप(u32))
#घोषणा AT_EEPROM_LEN 	512

#घोषणा ATL1C_GET_DESC(R, i, type)	(&(((type *)((R)->desc))[i]))
#घोषणा ATL1C_RFD_DESC(R, i)	ATL1C_GET_DESC(R, i, काष्ठा atl1c_rx_मुक्त_desc)
#घोषणा ATL1C_TPD_DESC(R, i)	ATL1C_GET_DESC(R, i, काष्ठा atl1c_tpd_desc)
#घोषणा ATL1C_RRD_DESC(R, i)	ATL1C_GET_DESC(R, i, काष्ठा atl1c_recv_ret_status)

/* tpd word 1 bit 0:7 General Checksum task offload */
#घोषणा TPD_L4HDR_OFFSET_MASK	0x00FF
#घोषणा TPD_L4HDR_OFFSET_SHIFT	0

/* tpd word 1 bit 0:7 Large Send task offload (IPv4/IPV6) */
#घोषणा TPD_TCPHDR_OFFSET_MASK	0x00FF
#घोषणा TPD_TCPHDR_OFFSET_SHIFT	0

/* tpd word 1 bit 0:7 Custom Checksum task offload */
#घोषणा TPD_PLOADOFFSET_MASK	0x00FF
#घोषणा TPD_PLOADOFFSET_SHIFT	0

/* tpd word 1 bit 8:17 */
#घोषणा TPD_CCSUM_EN_MASK	0x0001
#घोषणा TPD_CCSUM_EN_SHIFT	8
#घोषणा TPD_IP_CSUM_MASK	0x0001
#घोषणा TPD_IP_CSUM_SHIFT	9
#घोषणा TPD_TCP_CSUM_MASK	0x0001
#घोषणा TPD_TCP_CSUM_SHIFT	10
#घोषणा TPD_UDP_CSUM_MASK	0x0001
#घोषणा TPD_UDP_CSUM_SHIFT	11
#घोषणा TPD_LSO_EN_MASK		0x0001	/* TCP Large Send Offload */
#घोषणा TPD_LSO_EN_SHIFT	12
#घोषणा TPD_LSO_VER_MASK	0x0001
#घोषणा TPD_LSO_VER_SHIFT	13 	/* 0 : ipv4; 1 : ipv4/ipv6 */
#घोषणा TPD_CON_VTAG_MASK	0x0001
#घोषणा TPD_CON_VTAG_SHIFT	14
#घोषणा TPD_INS_VTAG_MASK	0x0001
#घोषणा TPD_INS_VTAG_SHIFT	15
#घोषणा TPD_IPV4_PACKET_MASK	0x0001  /* valid when LSO VER  is 1 */
#घोषणा TPD_IPV4_PACKET_SHIFT	16
#घोषणा TPD_ETH_TYPE_MASK	0x0001
#घोषणा TPD_ETH_TYPE_SHIFT	17	/* 0 : 802.3 frame; 1 : Ethernet */

/* tpd word 18:25 Custom Checksum task offload */
#घोषणा TPD_CCSUM_OFFSET_MASK	0x00FF
#घोषणा TPD_CCSUM_OFFSET_SHIFT	18
#घोषणा TPD_CCSUM_EPAD_MASK	0x0001
#घोषणा TPD_CCSUM_EPAD_SHIFT	30

/* tpd word 18:30 Large Send task offload (IPv4/IPV6) */
#घोषणा TPD_MSS_MASK            0x1FFF
#घोषणा TPD_MSS_SHIFT		18

#घोषणा TPD_EOP_MASK		0x0001
#घोषणा TPD_EOP_SHIFT		31

काष्ठा atl1c_tpd_desc अणु
	__le16	buffer_len; /* include 4-byte CRC */
	__le16	vlan_tag;
	__le32	word1;
	__le64	buffer_addr;
पूर्ण;

काष्ठा atl1c_tpd_ext_desc अणु
	u32 reservd_0;
	__le32 word1;
	__le32 pkt_len;
	u32 reservd_1;
पूर्ण;
/* rrs word 0 bit 0:31 */
#घोषणा RRS_RX_CSUM_MASK	0xFFFF
#घोषणा RRS_RX_CSUM_SHIFT	0
#घोषणा RRS_RX_RFD_CNT_MASK	0x000F
#घोषणा RRS_RX_RFD_CNT_SHIFT	16
#घोषणा RRS_RX_RFD_INDEX_MASK	0x0FFF
#घोषणा RRS_RX_RFD_INDEX_SHIFT	20

/* rrs flag bit 0:16 */
#घोषणा RRS_HEAD_LEN_MASK	0x00FF
#घोषणा RRS_HEAD_LEN_SHIFT	0
#घोषणा RRS_HDS_TYPE_MASK	0x0003
#घोषणा RRS_HDS_TYPE_SHIFT	8
#घोषणा RRS_CPU_NUM_MASK	0x0003
#घोषणा	RRS_CPU_NUM_SHIFT	10
#घोषणा RRS_HASH_FLG_MASK	0x000F
#घोषणा RRS_HASH_FLG_SHIFT	12

#घोषणा RRS_HDS_TYPE_HEAD	1
#घोषणा RRS_HDS_TYPE_DATA	2

#घोषणा RRS_IS_NO_HDS_TYPE(flag) \
	((((flag) >> (RRS_HDS_TYPE_SHIFT)) & RRS_HDS_TYPE_MASK) == 0)

#घोषणा RRS_IS_HDS_HEAD(flag) \
	((((flag) >> (RRS_HDS_TYPE_SHIFT)) & RRS_HDS_TYPE_MASK) == \
			RRS_HDS_TYPE_HEAD)

#घोषणा RRS_IS_HDS_DATA(flag) \
	((((flag) >> (RRS_HDS_TYPE_SHIFT)) & RRS_HDS_TYPE_MASK) == \
			RRS_HDS_TYPE_DATA)

/* rrs word 3 bit 0:31 */
#घोषणा RRS_PKT_SIZE_MASK	0x3FFF
#घोषणा RRS_PKT_SIZE_SHIFT	0
#घोषणा RRS_ERR_L4_CSUM_MASK	0x0001
#घोषणा RRS_ERR_L4_CSUM_SHIFT	14
#घोषणा RRS_ERR_IP_CSUM_MASK	0x0001
#घोषणा RRS_ERR_IP_CSUM_SHIFT	15
#घोषणा RRS_VLAN_INS_MASK	0x0001
#घोषणा RRS_VLAN_INS_SHIFT	16
#घोषणा RRS_PROT_ID_MASK	0x0007
#घोषणा RRS_PROT_ID_SHIFT	17
#घोषणा RRS_RX_ERR_SUM_MASK	0x0001
#घोषणा RRS_RX_ERR_SUM_SHIFT	20
#घोषणा RRS_RX_ERR_CRC_MASK	0x0001
#घोषणा RRS_RX_ERR_CRC_SHIFT	21
#घोषणा RRS_RX_ERR_FAE_MASK	0x0001
#घोषणा RRS_RX_ERR_FAE_SHIFT	22
#घोषणा RRS_RX_ERR_TRUNC_MASK	0x0001
#घोषणा RRS_RX_ERR_TRUNC_SHIFT	23
#घोषणा RRS_RX_ERR_RUNC_MASK	0x0001
#घोषणा RRS_RX_ERR_RUNC_SHIFT	24
#घोषणा RRS_RX_ERR_ICMP_MASK	0x0001
#घोषणा RRS_RX_ERR_ICMP_SHIFT	25
#घोषणा RRS_PACKET_BCAST_MASK	0x0001
#घोषणा RRS_PACKET_BCAST_SHIFT	26
#घोषणा RRS_PACKET_MCAST_MASK	0x0001
#घोषणा RRS_PACKET_MCAST_SHIFT	27
#घोषणा RRS_PACKET_TYPE_MASK	0x0001
#घोषणा RRS_PACKET_TYPE_SHIFT	28
#घोषणा RRS_FIFO_FULL_MASK	0x0001
#घोषणा RRS_FIFO_FULL_SHIFT	29
#घोषणा RRS_802_3_LEN_ERR_MASK 	0x0001
#घोषणा RRS_802_3_LEN_ERR_SHIFT 30
#घोषणा RRS_RXD_UPDATED_MASK	0x0001
#घोषणा RRS_RXD_UPDATED_SHIFT	31

#घोषणा RRS_ERR_L4_CSUM         0x00004000
#घोषणा RRS_ERR_IP_CSUM         0x00008000
#घोषणा RRS_VLAN_INS            0x00010000
#घोषणा RRS_RX_ERR_SUM          0x00100000
#घोषणा RRS_RX_ERR_CRC          0x00200000
#घोषणा RRS_802_3_LEN_ERR	0x40000000
#घोषणा RRS_RXD_UPDATED		0x80000000

#घोषणा RRS_PACKET_TYPE_802_3  	1
#घोषणा RRS_PACKET_TYPE_ETH	0
#घोषणा RRS_PACKET_IS_ETH(word) \
	((((word) >> RRS_PACKET_TYPE_SHIFT) & RRS_PACKET_TYPE_MASK) == \
			RRS_PACKET_TYPE_ETH)
#घोषणा RRS_RXD_IS_VALID(word) \
	((((word) >> RRS_RXD_UPDATED_SHIFT) & RRS_RXD_UPDATED_MASK) == 1)

#घोषणा RRS_PACKET_PROT_IS_IPV4_ONLY(word) \
	((((word) >> RRS_PROT_ID_SHIFT) & RRS_PROT_ID_MASK) == 1)
#घोषणा RRS_PACKET_PROT_IS_IPV6_ONLY(word) \
	((((word) >> RRS_PROT_ID_SHIFT) & RRS_PROT_ID_MASK) == 6)

काष्ठा atl1c_recv_ret_status अणु
	__le32  word0;
	__le32	rss_hash;
	__le16	vlan_tag;
	__le16	flag;
	__le32	word3;
पूर्ण;

/* RFD descriptor */
काष्ठा atl1c_rx_मुक्त_desc अणु
	__le64	buffer_addr;
पूर्ण;

/* DMA Order Settings */
क्रमागत atl1c_dma_order अणु
	atl1c_dma_ord_in = 1,
	atl1c_dma_ord_enh = 2,
	atl1c_dma_ord_out = 4
पूर्ण;

क्रमागत atl1c_dma_rcb अणु
	atl1c_rcb_64 = 0,
	atl1c_rcb_128 = 1
पूर्ण;

क्रमागत atl1c_mac_speed अणु
	atl1c_mac_speed_0 = 0,
	atl1c_mac_speed_10_100 = 1,
	atl1c_mac_speed_1000 = 2
पूर्ण;

क्रमागत atl1c_dma_req_block अणु
	atl1c_dma_req_128 = 0,
	atl1c_dma_req_256 = 1,
	atl1c_dma_req_512 = 2,
	atl1c_dma_req_1024 = 3,
	atl1c_dma_req_2048 = 4,
	atl1c_dma_req_4096 = 5
पूर्ण;


क्रमागत atl1c_nic_type अणु
	athr_l1c = 0,
	athr_l2c = 1,
	athr_l2c_b,
	athr_l2c_b2,
	athr_l1d,
	athr_l1d_2,
पूर्ण;

क्रमागत atl1c_trans_queue अणु
	atl1c_trans_normal = 0,
	atl1c_trans_high = 1
पूर्ण;

काष्ठा atl1c_hw_stats अणु
	/* rx */
	अचिन्हित दीर्घ rx_ok;		/* The number of good packet received. */
	अचिन्हित दीर्घ rx_bcast;		/* The number of good broadcast packet received. */
	अचिन्हित दीर्घ rx_mcast;		/* The number of good multicast packet received. */
	अचिन्हित दीर्घ rx_छोड़ो;		/* The number of Pause packet received. */
	अचिन्हित दीर्घ rx_ctrl;		/* The number of Control packet received other than Pause frame. */
	अचिन्हित दीर्घ rx_fcs_err;	/* The number of packets with bad FCS. */
	अचिन्हित दीर्घ rx_len_err;	/* The number of packets with mismatch of length field and actual size. */
	अचिन्हित दीर्घ rx_byte_cnt;	/* The number of bytes of good packet received. FCS is NOT included. */
	अचिन्हित दीर्घ rx_runt;		/* The number of packets received that are less than 64 byte दीर्घ and with good FCS. */
	अचिन्हित दीर्घ rx_frag;		/* The number of packets received that are less than 64 byte दीर्घ and with bad FCS. */
	अचिन्हित दीर्घ rx_sz_64;		/* The number of good and bad packets received that are 64 byte दीर्घ. */
	अचिन्हित दीर्घ rx_sz_65_127;	/* The number of good and bad packets received that are between 65 and 127-byte दीर्घ. */
	अचिन्हित दीर्घ rx_sz_128_255;	/* The number of good and bad packets received that are between 128 and 255-byte दीर्घ. */
	अचिन्हित दीर्घ rx_sz_256_511;	/* The number of good and bad packets received that are between 256 and 511-byte दीर्घ. */
	अचिन्हित दीर्घ rx_sz_512_1023;	/* The number of good and bad packets received that are between 512 and 1023-byte दीर्घ. */
	अचिन्हित दीर्घ rx_sz_1024_1518;	/* The number of good and bad packets received that are between 1024 and 1518-byte दीर्घ. */
	अचिन्हित दीर्घ rx_sz_1519_max;	/* The number of good and bad packets received that are between 1519-byte and MTU. */
	अचिन्हित दीर्घ rx_sz_ov;		/* The number of good and bad packets received that are more than MTU size truncated by Selene. */
	अचिन्हित दीर्घ rx_rxf_ov;	/* The number of frame dropped due to occurrence of RX FIFO overflow. */
	अचिन्हित दीर्घ rx_rrd_ov;	/* The number of frame dropped due to occurrence of RRD overflow. */
	अचिन्हित दीर्घ rx_align_err;	/* Alignment Error */
	अचिन्हित दीर्घ rx_bcast_byte_cnt; /* The byte count of broadcast packet received, excluding FCS. */
	अचिन्हित दीर्घ rx_mcast_byte_cnt; /* The byte count of multicast packet received, excluding FCS. */
	अचिन्हित दीर्घ rx_err_addr;	/* The number of packets dropped due to address filtering. */

	/* tx */
	अचिन्हित दीर्घ tx_ok;		/* The number of good packet transmitted. */
	अचिन्हित दीर्घ tx_bcast;		/* The number of good broadcast packet transmitted. */
	अचिन्हित दीर्घ tx_mcast;		/* The number of good multicast packet transmitted. */
	अचिन्हित दीर्घ tx_छोड़ो;		/* The number of Pause packet transmitted. */
	अचिन्हित दीर्घ tx_exc_defer;	/* The number of packets transmitted with excessive deferral. */
	अचिन्हित दीर्घ tx_ctrl;		/* The number of packets transmitted is a control frame, excluding Pause frame. */
	अचिन्हित दीर्घ tx_defer;		/* The number of packets transmitted that is deferred. */
	अचिन्हित दीर्घ tx_byte_cnt;	/* The number of bytes of data transmitted. FCS is NOT included. */
	अचिन्हित दीर्घ tx_sz_64;		/* The number of good and bad packets transmitted that are 64 byte दीर्घ. */
	अचिन्हित दीर्घ tx_sz_65_127;	/* The number of good and bad packets transmitted that are between 65 and 127-byte दीर्घ. */
	अचिन्हित दीर्घ tx_sz_128_255;	/* The number of good and bad packets transmitted that are between 128 and 255-byte दीर्घ. */
	अचिन्हित दीर्घ tx_sz_256_511;	/* The number of good and bad packets transmitted that are between 256 and 511-byte दीर्घ. */
	अचिन्हित दीर्घ tx_sz_512_1023;	/* The number of good and bad packets transmitted that are between 512 and 1023-byte दीर्घ. */
	अचिन्हित दीर्घ tx_sz_1024_1518;	/* The number of good and bad packets transmitted that are between 1024 and 1518-byte दीर्घ. */
	अचिन्हित दीर्घ tx_sz_1519_max;	/* The number of good and bad packets transmitted that are between 1519-byte and MTU. */
	अचिन्हित दीर्घ tx_1_col;		/* The number of packets subsequently transmitted successfully with a single prior collision. */
	अचिन्हित दीर्घ tx_2_col;		/* The number of packets subsequently transmitted successfully with multiple prior collisions. */
	अचिन्हित दीर्घ tx_late_col;	/* The number of packets transmitted with late collisions. */
	अचिन्हित दीर्घ tx_पात_col;	/* The number of transmit packets पातed due to excessive collisions. */
	अचिन्हित दीर्घ tx_underrun;	/* The number of transmit packets पातed due to transmit FIFO underrun, or TRD FIFO underrun */
	अचिन्हित दीर्घ tx_rd_eop;	/* The number of बार that पढ़ो beyond the EOP पूर्णांकo the next frame area when TRD was not written समयly */
	अचिन्हित दीर्घ tx_len_err;	/* The number of transmit packets with length field करोes NOT match the actual frame size. */
	अचिन्हित दीर्घ tx_trunc;		/* The number of transmit packets truncated due to size exceeding MTU. */
	अचिन्हित दीर्घ tx_bcast_byte;	/* The byte count of broadcast packet transmitted, excluding FCS. */
	अचिन्हित दीर्घ tx_mcast_byte;	/* The byte count of multicast packet transmitted, excluding FCS. */
पूर्ण;

काष्ठा atl1c_hw अणु
	u8 __iomem      *hw_addr;            /* inner रेजिस्टर address */
	काष्ठा atl1c_adapter *adapter;
	क्रमागत atl1c_nic_type  nic_type;
	क्रमागत atl1c_dma_order dma_order;
	क्रमागत atl1c_dma_rcb   rcb_value;
	क्रमागत atl1c_dma_req_block dmar_block;

	u16 device_id;
	u16 venकरोr_id;
	u16 subप्रणाली_id;
	u16 subप्रणाली_venकरोr_id;
	u8 revision_id;
	u16 phy_id1;
	u16 phy_id2;

	spinlock_t पूर्णांकr_mask_lock;	/* protect the पूर्णांकr_mask */
	u32 पूर्णांकr_mask;

	u8 preamble_len;
	u16 max_frame_size;
	u16 min_frame_size;

	क्रमागत atl1c_mac_speed mac_speed;
	bool mac_duplex;
	bool hibernate;
	u16 media_type;
#घोषणा MEDIA_TYPE_AUTO_SENSOR  0
#घोषणा MEDIA_TYPE_100M_FULL    1
#घोषणा MEDIA_TYPE_100M_HALF    2
#घोषणा MEDIA_TYPE_10M_FULL     3
#घोषणा MEDIA_TYPE_10M_HALF     4

	u16 स्वतःneg_advertised;
	u16 mii_स्वतःneg_adv_reg;
	u16 mii_1000t_ctrl_reg;

	u16 tx_imt;	/* TX Interrupt Moderator समयr ( 2us resolution) */
	u16 rx_imt;	/* RX Interrupt Moderator समयr ( 2us resolution) */
	u16 ict;        /* Interrupt Clear समयr (2us resolution) */
	u16 ctrl_flags;
#घोषणा ATL1C_INTR_CLEAR_ON_READ	0x0001
#घोषणा ATL1C_INTR_MODRT_ENABLE	 	0x0002
#घोषणा ATL1C_CMB_ENABLE		0x0004
#घोषणा ATL1C_SMB_ENABLE		0x0010
#घोषणा ATL1C_TXQ_MODE_ENHANCE		0x0020
#घोषणा ATL1C_RX_IPV6_CHKSUM		0x0040
#घोषणा ATL1C_ASPM_L0S_SUPPORT		0x0080
#घोषणा ATL1C_ASPM_L1_SUPPORT		0x0100
#घोषणा ATL1C_ASPM_CTRL_MON		0x0200
#घोषणा ATL1C_HIB_DISABLE		0x0400
#घोषणा ATL1C_APS_MODE_ENABLE           0x0800
#घोषणा ATL1C_LINK_EXT_SYNC             0x1000
#घोषणा ATL1C_CLK_GATING_EN             0x2000
#घोषणा ATL1C_FPGA_VERSION              0x8000
	u16 link_cap_flags;
#घोषणा ATL1C_LINK_CAP_1000M		0x0001
	u32 smb_समयr;

	u16 rrd_thresh; /* Threshold of number of RRD produced to trigger
			  पूर्णांकerrupt request */
	u16 tpd_thresh;
	u8 tpd_burst;   /* Number of TPD to prefetch in cache-aligned burst. */
	u8 rfd_burst;
	u32 base_cpu;
	u32 indirect_tab;
	u8 mac_addr[ETH_ALEN];
	u8 perm_mac_addr[ETH_ALEN];

	bool phy_configured;
	bool re_स्वतःneg;
	bool emi_ca;
	bool msi_lnkpatch;	/* link patch क्रम specअगरic platक्रमms */
पूर्ण;

/*
 * atl1c_ring_header represents a single, contiguous block of DMA space
 * mapped क्रम the three descriptor rings (tpd, rfd, rrd) described below
 */
काष्ठा atl1c_ring_header अणु
	व्योम *desc;		/* भव address */
	dma_addr_t dma;		/* physical address*/
	अचिन्हित पूर्णांक size;	/* length in bytes */
पूर्ण;

/*
 * atl1c_buffer is wrapper around a poपूर्णांकer to a socket buffer
 * so a DMA handle can be stored aदीर्घ with the skb
 */
काष्ठा atl1c_buffer अणु
	काष्ठा sk_buff *skb;	/* socket buffer */
	u16 length;		/* rx buffer length */
	u16 flags;		/* inक्रमmation of buffer */
#घोषणा ATL1C_BUFFER_FREE		0x0001
#घोषणा ATL1C_BUFFER_BUSY		0x0002
#घोषणा ATL1C_BUFFER_STATE_MASK		0x0003

#घोषणा ATL1C_PCIMAP_SINGLE		0x0004
#घोषणा ATL1C_PCIMAP_PAGE		0x0008
#घोषणा ATL1C_PCIMAP_TYPE_MASK		0x000C

#घोषणा ATL1C_PCIMAP_TODEVICE		0x0010
#घोषणा ATL1C_PCIMAP_FROMDEVICE		0x0020
#घोषणा ATL1C_PCIMAP_सूचीECTION_MASK	0x0030
	dma_addr_t dma;
पूर्ण;

#घोषणा ATL1C_SET_BUFFER_STATE(buff, state) करो अणु	\
	((buff)->flags) &= ~ATL1C_BUFFER_STATE_MASK;	\
	((buff)->flags) |= (state);			\
	पूर्ण जबतक (0)

#घोषणा ATL1C_SET_PCIMAP_TYPE(buff, type, direction) करो अणु	\
	((buff)->flags) &= ~ATL1C_PCIMAP_TYPE_MASK;		\
	((buff)->flags) |= (type);				\
	((buff)->flags) &= ~ATL1C_PCIMAP_सूचीECTION_MASK;	\
	((buff)->flags) |= (direction);				\
	पूर्ण जबतक (0)

/* transimit packet descriptor (tpd) ring */
काष्ठा atl1c_tpd_ring अणु
	व्योम *desc;		/* descriptor ring भव address */
	dma_addr_t dma;		/* descriptor ring physical address */
	u16 size;		/* descriptor ring length in bytes */
	u16 count;		/* number of descriptors in the ring */
	u16 next_to_use;
	atomic_t next_to_clean;
	काष्ठा atl1c_buffer *buffer_info;
पूर्ण;

/* receive मुक्त descriptor (rfd) ring */
काष्ठा atl1c_rfd_ring अणु
	व्योम *desc;		/* descriptor ring भव address */
	dma_addr_t dma;		/* descriptor ring physical address */
	u16 size;		/* descriptor ring length in bytes */
	u16 count;		/* number of descriptors in the ring */
	u16 next_to_use;
	u16 next_to_clean;
	काष्ठा atl1c_buffer *buffer_info;
पूर्ण;

/* receive वापस descriptor (rrd) ring */
काष्ठा atl1c_rrd_ring अणु
	व्योम *desc;		/* descriptor ring भव address */
	dma_addr_t dma;		/* descriptor ring physical address */
	u16 size;		/* descriptor ring length in bytes */
	u16 count;		/* number of descriptors in the ring */
	u16 next_to_use;
	u16 next_to_clean;
पूर्ण;

/* board specअगरic निजी data काष्ठाure */
काष्ठा atl1c_adapter अणु
	काष्ठा net_device   *netdev;
	काष्ठा pci_dev      *pdev;
	काष्ठा napi_काष्ठा  napi;
	काष्ठा napi_काष्ठा  tx_napi;
	काष्ठा page         *rx_page;
	अचिन्हित पूर्णांक	    rx_page_offset;
	अचिन्हित पूर्णांक	    rx_frag_size;
	काष्ठा atl1c_hw        hw;
	काष्ठा atl1c_hw_stats  hw_stats;
	काष्ठा mii_अगर_info  mii;    /* MII पूर्णांकerface info */
	u16 rx_buffer_len;

	अचिन्हित दीर्घ flags;
#घोषणा __AT_TESTING        0x0001
#घोषणा __AT_RESETTING      0x0002
#घोषणा __AT_DOWN           0x0003
	अचिन्हित दीर्घ work_event;
#घोषणा	ATL1C_WORK_EVENT_RESET		0
#घोषणा	ATL1C_WORK_EVENT_LINK_CHANGE	1
	u32 msg_enable;

	bool have_msi;
	u32 wol;
	u16 link_speed;
	u16 link_duplex;

	spinlock_t mdio_lock;
	atomic_t irq_sem;

	काष्ठा work_काष्ठा common_task;
	काष्ठा समयr_list watchकरोg_समयr;
	काष्ठा समयr_list phy_config_समयr;

	/* All Descriptor memory */
	काष्ठा atl1c_ring_header ring_header;
	काष्ठा atl1c_tpd_ring tpd_ring[AT_MAX_TRANSMIT_QUEUE];
	काष्ठा atl1c_rfd_ring rfd_ring;
	काष्ठा atl1c_rrd_ring rrd_ring;
	u32 bd_number;     /* board number;*/
पूर्ण;

#घोषणा AT_WRITE_REG(a, reg, value) ( \
		ग_लिखोl((value), ((a)->hw_addr + reg)))

#घोषणा AT_WRITE_FLUSH(a) (\
		पढ़ोl((a)->hw_addr))

#घोषणा AT_READ_REG(a, reg, pdata) करो अणु					\
		अगर (unlikely((a)->hibernate)) अणु				\
			पढ़ोl((a)->hw_addr + reg);			\
			*(u32 *)pdata = पढ़ोl((a)->hw_addr + reg);	\
		पूर्ण अन्यथा अणु						\
			*(u32 *)pdata = पढ़ोl((a)->hw_addr + reg);	\
		पूर्ण							\
	पूर्ण जबतक (0)

#घोषणा AT_WRITE_REGB(a, reg, value) (\
		ग_लिखोb((value), ((a)->hw_addr + reg)))

#घोषणा AT_READ_REGB(a, reg) (\
		पढ़ोb((a)->hw_addr + reg))

#घोषणा AT_WRITE_REGW(a, reg, value) (\
		ग_लिखोw((value), ((a)->hw_addr + reg)))

#घोषणा AT_READ_REGW(a, reg, pdata) करो अणु				\
		अगर (unlikely((a)->hibernate)) अणु				\
			पढ़ोw((a)->hw_addr + reg);			\
			*(u16 *)pdata = पढ़ोw((a)->hw_addr + reg);	\
		पूर्ण अन्यथा अणु						\
			*(u16 *)pdata = पढ़ोw((a)->hw_addr + reg);	\
		पूर्ण							\
	पूर्ण जबतक (0)

#घोषणा AT_WRITE_REG_ARRAY(a, reg, offset, value) ( \
		ग_लिखोl((value), (((a)->hw_addr + reg) + ((offset) << 2))))

#घोषणा AT_READ_REG_ARRAY(a, reg, offset) ( \
		पढ़ोl(((a)->hw_addr + reg) + ((offset) << 2)))

बाह्य अक्षर atl1c_driver_name[];

व्योम atl1c_reinit_locked(काष्ठा atl1c_adapter *adapter);
s32 atl1c_reset_hw(काष्ठा atl1c_hw *hw);
व्योम atl1c_set_ethtool_ops(काष्ठा net_device *netdev);
#पूर्ण_अगर /* _ATL1C_H_ */
