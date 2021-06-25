<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* Aquantia Corp. Aquantia AQtion USB to 5GbE Controller
 * Copyright (C) 2003-2005 David Hollis <dhollis@davehollis.com>
 * Copyright (C) 2005 Phil Chang <pchang23@sbcglobal.net>
 * Copyright (C) 2002-2003 TiVo Inc.
 * Copyright (C) 2017-2018 ASIX
 * Copyright (C) 2018 Aquantia Corp.
 */

#अगर_अघोषित __LINUX_USBNET_AQC111_H
#घोषणा __LINUX_USBNET_AQC111_H

#घोषणा URB_SIZE	(1024 * 62)

#घोषणा AQ_MCAST_FILTER_SIZE		8
#घोषणा AQ_MAX_MCAST			64

#घोषणा AQ_ACCESS_MAC			0x01
#घोषणा AQ_FLASH_PARAMETERS		0x20
#घोषणा AQ_PHY_POWER			0x31
#घोषणा AQ_WOL_CFG			0x60
#घोषणा AQ_PHY_OPS			0x61

#घोषणा AQ_USB_PHY_SET_TIMEOUT		10000
#घोषणा AQ_USB_SET_TIMEOUT		4000

/* Feature. ********************************************/
#घोषणा AQ_SUPPORT_FEATURE	(NETIF_F_SG | NETIF_F_IP_CSUM |\
				 NETIF_F_IPV6_CSUM | NETIF_F_RXCSUM |\
				 NETIF_F_TSO | NETIF_F_HW_VLAN_CTAG_TX |\
				 NETIF_F_HW_VLAN_CTAG_RX)

#घोषणा AQ_SUPPORT_HW_FEATURE	(NETIF_F_SG | NETIF_F_IP_CSUM |\
				 NETIF_F_IPV6_CSUM | NETIF_F_RXCSUM |\
				 NETIF_F_TSO | NETIF_F_HW_VLAN_CTAG_FILTER)

#घोषणा AQ_SUPPORT_VLAN_FEATURE (NETIF_F_SG | NETIF_F_IP_CSUM |\
				 NETIF_F_IPV6_CSUM | NETIF_F_RXCSUM |\
				 NETIF_F_TSO)

/* SFR Reg. ********************************************/

#घोषणा SFR_GENERAL_STATUS		0x03
#घोषणा SFR_CHIP_STATUS			0x05
#घोषणा SFR_RX_CTL			0x0B
	#घोषणा SFR_RX_CTL_TXPADCRC		0x0400
	#घोषणा SFR_RX_CTL_IPE			0x0200
	#घोषणा SFR_RX_CTL_DROPCRCERR		0x0100
	#घोषणा SFR_RX_CTL_START		0x0080
	#घोषणा SFR_RX_CTL_RF_WAK		0x0040
	#घोषणा SFR_RX_CTL_AP			0x0020
	#घोषणा SFR_RX_CTL_AM			0x0010
	#घोषणा SFR_RX_CTL_AB			0x0008
	#घोषणा SFR_RX_CTL_AMALL		0x0002
	#घोषणा SFR_RX_CTL_PRO			0x0001
	#घोषणा SFR_RX_CTL_STOP			0x0000
#घोषणा SFR_INTER_PACKET_GAP_0		0x0D
#घोषणा SFR_NODE_ID			0x10
#घोषणा SFR_MULTI_FILTER_ARRY		0x16
#घोषणा SFR_MEDIUM_STATUS_MODE		0x22
	#घोषणा SFR_MEDIUM_XGMIIMODE		0x0001
	#घोषणा SFR_MEDIUM_FULL_DUPLEX		0x0002
	#घोषणा SFR_MEDIUM_RXFLOW_CTRLEN	0x0010
	#घोषणा SFR_MEDIUM_TXFLOW_CTRLEN	0x0020
	#घोषणा SFR_MEDIUM_JUMBO_EN		0x0040
	#घोषणा SFR_MEDIUM_RECEIVE_EN		0x0100
#घोषणा SFR_MONITOR_MODE		0x24
	#घोषणा SFR_MONITOR_MODE_EPHYRW		0x01
	#घोषणा SFR_MONITOR_MODE_RWLC		0x02
	#घोषणा SFR_MONITOR_MODE_RWMP		0x04
	#घोषणा SFR_MONITOR_MODE_RWWF		0x08
	#घोषणा SFR_MONITOR_MODE_RW_FLAG	0x10
	#घोषणा SFR_MONITOR_MODE_PMEPOL		0x20
	#घोषणा SFR_MONITOR_MODE_PMETYPE	0x40
#घोषणा SFR_PHYPWR_RSTCTL		0x26
	#घोषणा SFR_PHYPWR_RSTCTL_BZ		0x0010
	#घोषणा SFR_PHYPWR_RSTCTL_IPRL		0x0020
#घोषणा SFR_VLAN_ID_ADDRESS		0x2A
#घोषणा SFR_VLAN_ID_CONTROL		0x2B
	#घोषणा SFR_VLAN_CONTROL_WE		0x0001
	#घोषणा SFR_VLAN_CONTROL_RD		0x0002
	#घोषणा SFR_VLAN_CONTROL_VSO		0x0010
	#घोषणा SFR_VLAN_CONTROL_VFE		0x0020
#घोषणा SFR_VLAN_ID_DATA0		0x2C
#घोषणा SFR_VLAN_ID_DATA1		0x2D
#घोषणा SFR_RX_BULKIN_QCTRL		0x2E
	#घोषणा SFR_RX_BULKIN_QCTRL_TIME	0x01
	#घोषणा SFR_RX_BULKIN_QCTRL_IFG		0x02
	#घोषणा SFR_RX_BULKIN_QCTRL_SIZE	0x04
#घोषणा SFR_RX_BULKIN_QTIMR_LOW		0x2F
#घोषणा SFR_RX_BULKIN_QTIMR_HIGH	0x30
#घोषणा SFR_RX_BULKIN_QSIZE		0x31
#घोषणा SFR_RX_BULKIN_QIFG		0x32
#घोषणा SFR_RXCOE_CTL			0x34
	#घोषणा SFR_RXCOE_IP			0x01
	#घोषणा SFR_RXCOE_TCP			0x02
	#घोषणा SFR_RXCOE_UDP			0x04
	#घोषणा SFR_RXCOE_ICMP			0x08
	#घोषणा SFR_RXCOE_IGMP			0x10
	#घोषणा SFR_RXCOE_TCPV6			0x20
	#घोषणा SFR_RXCOE_UDPV6			0x40
	#घोषणा SFR_RXCOE_ICMV6			0x80
#घोषणा SFR_TXCOE_CTL			0x35
	#घोषणा SFR_TXCOE_IP			0x01
	#घोषणा SFR_TXCOE_TCP			0x02
	#घोषणा SFR_TXCOE_UDP			0x04
	#घोषणा SFR_TXCOE_ICMP			0x08
	#घोषणा SFR_TXCOE_IGMP			0x10
	#घोषणा SFR_TXCOE_TCPV6			0x20
	#घोषणा SFR_TXCOE_UDPV6			0x40
	#घोषणा SFR_TXCOE_ICMV6			0x80
#घोषणा SFR_BM_INT_MASK			0x41
#घोषणा SFR_BMRX_DMA_CONTROL		0x43
	#घोषणा SFR_BMRX_DMA_EN			0x80
#घोषणा SFR_BMTX_DMA_CONTROL		0x46
#घोषणा SFR_PAUSE_WATERLVL_LOW		0x54
#घोषणा SFR_PAUSE_WATERLVL_HIGH		0x55
#घोषणा SFR_ARC_CTRL			0x9E
#घोषणा SFR_SWP_CTRL			0xB1
#घोषणा SFR_TX_PAUSE_RESEND_T		0xB2
#घोषणा SFR_ETH_MAC_PATH		0xB7
	#घोषणा SFR_RX_PATH_READY		0x01
#घोषणा SFR_BULK_OUT_CTRL		0xB9
	#घोषणा SFR_BULK_OUT_FLUSH_EN		0x01
	#घोषणा SFR_BULK_OUT_EFF_EN		0x02

#घोषणा AQ_FW_VER_MAJOR			0xDA
#घोषणा AQ_FW_VER_MINOR			0xDB
#घोषणा AQ_FW_VER_REV			0xDC

/*PHY_OPS**********************************************************************/

#घोषणा AQ_ADV_100M	BIT(0)
#घोषणा AQ_ADV_1G	BIT(1)
#घोषणा AQ_ADV_2G5	BIT(2)
#घोषणा AQ_ADV_5G	BIT(3)
#घोषणा AQ_ADV_MASK	0x0F

#घोषणा AQ_PAUSE	BIT(16)
#घोषणा AQ_ASYM_PAUSE	BIT(17)
#घोषणा AQ_LOW_POWER	BIT(18)
#घोषणा AQ_PHY_POWER_EN	BIT(19)
#घोषणा AQ_WOL		BIT(20)
#घोषणा AQ_DOWNSHIFT	BIT(21)

#घोषणा AQ_DSH_RETRIES_SHIFT	0x18
#घोषणा AQ_DSH_RETRIES_MASK	0xF000000

#घोषणा AQ_WOL_FLAG_MP			0x2

/******************************************************************************/

काष्ठा aqc111_wol_cfg अणु
	u8 hw_addr[6];
	u8 flags;
	u8 rsvd[283];
पूर्ण __packed;

#घोषणा WOL_CFG_SIZE माप(काष्ठा aqc111_wol_cfg)

काष्ठा aqc111_data अणु
	u16 rxctl;
	u8 rx_checksum;
	u8 link_speed;
	u8 link;
	u8 स्वतःneg;
	u32 advertised_speed;
	काष्ठा अणु
		u8 major;
		u8 minor;
		u8 rev;
	पूर्ण fw_ver;
	u32 phy_cfg;
	u8 wol_flags;
पूर्ण;

#घोषणा AQ_LS_MASK		0x8000
#घोषणा AQ_SPEED_MASK		0x7F00
#घोषणा AQ_SPEED_SHIFT		0x0008
#घोषणा AQ_INT_SPEED_5G		0x000F
#घोषणा AQ_INT_SPEED_2_5G	0x0010
#घोषणा AQ_INT_SPEED_1G		0x0011
#घोषणा AQ_INT_SPEED_100M	0x0013

/* TX Descriptor */
#घोषणा AQ_TX_DESC_LEN_MASK	0x1FFFFF
#घोषणा AQ_TX_DESC_DROP_PADD	BIT(28)
#घोषणा AQ_TX_DESC_VLAN		BIT(29)
#घोषणा AQ_TX_DESC_MSS_MASK	0x7FFF
#घोषणा AQ_TX_DESC_MSS_SHIFT	0x20
#घोषणा AQ_TX_DESC_VLAN_MASK	0xFFFF
#घोषणा AQ_TX_DESC_VLAN_SHIFT	0x30

#घोषणा AQ_RX_HW_PAD			0x02

/* RX Packet Descriptor */
#घोषणा AQ_RX_PD_L4_ERR		BIT(0)
#घोषणा AQ_RX_PD_L3_ERR		BIT(1)
#घोषणा AQ_RX_PD_L4_TYPE_MASK	0x1C
#घोषणा AQ_RX_PD_L4_UDP		0x04
#घोषणा AQ_RX_PD_L4_TCP		0x10
#घोषणा AQ_RX_PD_L3_TYPE_MASK	0x60
#घोषणा AQ_RX_PD_L3_IP		0x20
#घोषणा AQ_RX_PD_L3_IP6		0x40

#घोषणा AQ_RX_PD_VLAN		BIT(10)
#घोषणा AQ_RX_PD_RX_OK		BIT(11)
#घोषणा AQ_RX_PD_DROP		BIT(31)
#घोषणा AQ_RX_PD_LEN_MASK	0x7FFF0000
#घोषणा AQ_RX_PD_LEN_SHIFT	0x10
#घोषणा AQ_RX_PD_VLAN_SHIFT	0x20

/* RX Descriptor header */
#घोषणा AQ_RX_DH_PKT_CNT_MASK		0x1FFF
#घोषणा AQ_RX_DH_DESC_OFFSET_MASK	0xFFFFE000
#घोषणा AQ_RX_DH_DESC_OFFSET_SHIFT	0x0D

अटल काष्ठा अणु
	अचिन्हित अक्षर ctrl;
	अचिन्हित अक्षर समयr_l;
	अचिन्हित अक्षर समयr_h;
	अचिन्हित अक्षर size;
	अचिन्हित अक्षर अगरg;
पूर्ण AQC111_BULKIN_SIZE[] = अणु
	/* xHCI & EHCI & OHCI */
	अणु7, 0x00, 0x01, 0x1E, 0xFFपूर्ण,/* 10G, 5G, 2.5G, 1G */
	अणु7, 0xA0, 0x00, 0x14, 0x00पूर्ण,/* 100M */
	/* Jumbo packet */
	अणु7, 0x00, 0x01, 0x18, 0xFFपूर्ण,
पूर्ण;

#पूर्ण_अगर /* __LINUX_USBNET_AQC111_H */
