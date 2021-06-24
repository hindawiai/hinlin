<शैली गुरु>
/*
 * B53 रेजिस्टर definitions
 *
 * Copyright (C) 2004 Broadcom Corporation
 * Copyright (C) 2011-2013 Jonas Gorski <jogo@खोलोwrt.org>
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#अगर_अघोषित __B53_REGS_H
#घोषणा __B53_REGS_H

/* Management Port (SMP) Page offsets */
#घोषणा B53_CTRL_PAGE			0x00 /* Control */
#घोषणा B53_STAT_PAGE			0x01 /* Status */
#घोषणा B53_MGMT_PAGE			0x02 /* Management Mode */
#घोषणा B53_MIB_AC_PAGE			0x03 /* MIB Autocast */
#घोषणा B53_ARLCTRL_PAGE		0x04 /* ARL Control */
#घोषणा B53_ARLIO_PAGE			0x05 /* ARL Access */
#घोषणा B53_FRAMEBUF_PAGE		0x06 /* Management frame access */
#घोषणा B53_MEM_ACCESS_PAGE		0x08 /* Memory access */

/* PHY Registers */
#घोषणा B53_PORT_MII_PAGE(i)		(0x10 + (i)) /* Port i MII Registers */
#घोषणा B53_IM_PORT_PAGE		0x18 /* Inverse MII Port (to EMAC) */
#घोषणा B53_ALL_PORT_PAGE		0x19 /* All ports MII (broadcast) */

/* MIB रेजिस्टरs */
#घोषणा B53_MIB_PAGE(i)			(0x20 + (i))

/* Quality of Service (QoS) Registers */
#घोषणा B53_QOS_PAGE			0x30

/* Port VLAN Page */
#घोषणा B53_PVLAN_PAGE			0x31

/* VLAN Registers */
#घोषणा B53_VLAN_PAGE			0x34

/* Jumbo Frame Registers */
#घोषणा B53_JUMBO_PAGE			0x40

/* EEE Control Registers Page */
#घोषणा B53_EEE_PAGE			0x92

/* CFP Configuration Registers Page */
#घोषणा B53_CFP_PAGE			0xa1

/*************************************************************************
 * Control Page रेजिस्टरs
 *************************************************************************/

/* Port Control Register (8 bit) */
#घोषणा B53_PORT_CTRL(i)		(0x00 + (i))
#घोषणा   PORT_CTRL_RX_DISABLE		BIT(0)
#घोषणा   PORT_CTRL_TX_DISABLE		BIT(1)
#घोषणा   PORT_CTRL_RX_BCST_EN		BIT(2) /* Broadcast RX (P8 only) */
#घोषणा   PORT_CTRL_RX_MCST_EN		BIT(3) /* Multicast RX (P8 only) */
#घोषणा   PORT_CTRL_RX_UCST_EN		BIT(4) /* Unicast RX (P8 only) */
#घोषणा	  PORT_CTRL_STP_STATE_S		5
#घोषणा   PORT_CTRL_NO_STP		(0 << PORT_CTRL_STP_STATE_S)
#घोषणा   PORT_CTRL_DIS_STATE		(1 << PORT_CTRL_STP_STATE_S)
#घोषणा   PORT_CTRL_BLOCK_STATE		(2 << PORT_CTRL_STP_STATE_S)
#घोषणा   PORT_CTRL_LISTEN_STATE	(3 << PORT_CTRL_STP_STATE_S)
#घोषणा   PORT_CTRL_LEARN_STATE		(4 << PORT_CTRL_STP_STATE_S)
#घोषणा   PORT_CTRL_FWD_STATE		(5 << PORT_CTRL_STP_STATE_S)
#घोषणा   PORT_CTRL_STP_STATE_MASK	(0x7 << PORT_CTRL_STP_STATE_S)

/* SMP Control Register (8 bit) */
#घोषणा B53_SMP_CTRL			0x0a

/* Switch Mode Control Register (8 bit) */
#घोषणा B53_SWITCH_MODE			0x0b
#घोषणा   SM_SW_FWD_MODE		BIT(0)	/* 1 = Managed Mode */
#घोषणा   SM_SW_FWD_EN			BIT(1)	/* Forwarding Enable */

/* IMP Port state override रेजिस्टर (8 bit) */
#घोषणा B53_PORT_OVERRIDE_CTRL		0x0e
#घोषणा   PORT_OVERRIDE_LINK		BIT(0)
#घोषणा   PORT_OVERRIDE_FULL_DUPLEX	BIT(1) /* 0 = Half Duplex */
#घोषणा   PORT_OVERRIDE_SPEED_S		2
#घोषणा   PORT_OVERRIDE_SPEED_10M	(0 << PORT_OVERRIDE_SPEED_S)
#घोषणा   PORT_OVERRIDE_SPEED_100M	(1 << PORT_OVERRIDE_SPEED_S)
#घोषणा   PORT_OVERRIDE_SPEED_1000M	(2 << PORT_OVERRIDE_SPEED_S)
#घोषणा   PORT_OVERRIDE_RV_MII_25	BIT(4) /* BCM5325 only */
#घोषणा   PORT_OVERRIDE_RX_FLOW		BIT(4)
#घोषणा   PORT_OVERRIDE_TX_FLOW		BIT(5)
#घोषणा   PORT_OVERRIDE_SPEED_2000M	BIT(6) /* BCM5301X only, requires setting 1000M */
#घोषणा   PORT_OVERRIDE_EN		BIT(7) /* Use the रेजिस्टर contents */

/* Power-करोwn mode control */
#घोषणा B53_PD_MODE_CTRL_25		0x0f

/* IP Multicast control (8 bit) */
#घोषणा B53_IP_MULTICAST_CTRL		0x21
#घोषणा  B53_IPMC_FWD_EN		BIT(1)
#घोषणा  B53_UC_FWD_EN			BIT(6)
#घोषणा  B53_MC_FWD_EN			BIT(7)

/* Switch control (8 bit) */
#घोषणा B53_SWITCH_CTRL			0x22
#घोषणा  B53_MII_DUMB_FWDG_EN		BIT(6)

/* (16 bit) */
#घोषणा B53_UC_FLOOD_MASK		0x32
#घोषणा B53_MC_FLOOD_MASK		0x34
#घोषणा B53_IPMC_FLOOD_MASK		0x36
#घोषणा B53_DIS_LEARNING		0x3c

/*
 * Override Ports 0-7 State on devices with xMII पूर्णांकerfaces (8 bit)
 *
 * For port 8 still use B53_PORT_OVERRIDE_CTRL
 * Please note that not all ports are available on every hardware, e.g. BCM5301X
 * करोn't include overriding port 6, BCM63xx also have some limitations.
 */
#घोषणा B53_GMII_PORT_OVERRIDE_CTRL(i)	(0x58 + (i))
#घोषणा   GMII_PO_LINK			BIT(0)
#घोषणा   GMII_PO_FULL_DUPLEX		BIT(1) /* 0 = Half Duplex */
#घोषणा   GMII_PO_SPEED_S		2
#घोषणा   GMII_PO_SPEED_10M		(0 << GMII_PO_SPEED_S)
#घोषणा   GMII_PO_SPEED_100M		(1 << GMII_PO_SPEED_S)
#घोषणा   GMII_PO_SPEED_1000M		(2 << GMII_PO_SPEED_S)
#घोषणा   GMII_PO_RX_FLOW		BIT(4)
#घोषणा   GMII_PO_TX_FLOW		BIT(5)
#घोषणा   GMII_PO_EN			BIT(6) /* Use the रेजिस्टर contents */
#घोषणा   GMII_PO_SPEED_2000M		BIT(7) /* BCM5301X only, requires setting 1000M */

#घोषणा B53_RGMII_CTRL_IMP		0x60
#घोषणा   RGMII_CTRL_ENABLE_GMII	BIT(7)
#घोषणा   RGMII_CTRL_TIMING_SEL		BIT(2)
#घोषणा   RGMII_CTRL_DLL_RXC		BIT(1)
#घोषणा   RGMII_CTRL_DLL_TXC		BIT(0)

#घोषणा B53_RGMII_CTRL_P(i)		(B53_RGMII_CTRL_IMP + (i))

/* Software reset रेजिस्टर (8 bit) */
#घोषणा B53_SOFTRESET			0x79
#घोषणा   SW_RST			BIT(7)
#घोषणा   EN_CH_RST			BIT(6)
#घोषणा   EN_SW_RST			BIT(4)

/* Fast Aging Control रेजिस्टर (8 bit) */
#घोषणा B53_FAST_AGE_CTRL		0x88
#घोषणा   FAST_AGE_STATIC		BIT(0)
#घोषणा   FAST_AGE_DYNAMIC		BIT(1)
#घोषणा   FAST_AGE_PORT			BIT(2)
#घोषणा   FAST_AGE_VLAN			BIT(3)
#घोषणा   FAST_AGE_STP			BIT(4)
#घोषणा   FAST_AGE_MC			BIT(5)
#घोषणा   FAST_AGE_DONE			BIT(7)

/* Fast Aging Port Control रेजिस्टर (8 bit) */
#घोषणा B53_FAST_AGE_PORT_CTRL		0x89

/* Fast Aging VID Control रेजिस्टर (16 bit) */
#घोषणा B53_FAST_AGE_VID_CTRL		0x8a

/*************************************************************************
 * Status Page रेजिस्टरs
 *************************************************************************/

/* Link Status Summary Register (16bit) */
#घोषणा B53_LINK_STAT			0x00

/* Link Status Change Register (16 bit) */
#घोषणा B53_LINK_STAT_CHANGE		0x02

/* Port Speed Summary Register (16 bit क्रम FE, 32 bit क्रम GE) */
#घोषणा B53_SPEED_STAT			0x04
#घोषणा  SPEED_PORT_FE(reg, port)	(((reg) >> (port)) & 1)
#घोषणा  SPEED_PORT_GE(reg, port)	(((reg) >> 2 * (port)) & 3)
#घोषणा  SPEED_STAT_10M			0
#घोषणा  SPEED_STAT_100M		1
#घोषणा  SPEED_STAT_1000M		2

/* Duplex Status Summary (16 bit) */
#घोषणा B53_DUPLEX_STAT_FE		0x06
#घोषणा B53_DUPLEX_STAT_GE		0x08
#घोषणा B53_DUPLEX_STAT_63XX		0x0c

/* Revision ID रेजिस्टर क्रम BCM5325 */
#घोषणा B53_REV_ID_25			0x50

/* Strap Value (48 bit) */
#घोषणा B53_STRAP_VALUE			0x70
#घोषणा   SV_GMII_CTRL_115		BIT(27)

/*************************************************************************
 * Management Mode Page Registers
 *************************************************************************/

/* Global Management Config Register (8 bit) */
#घोषणा B53_GLOBAL_CONFIG		0x00
#घोषणा   GC_RESET_MIB			0x01
#घोषणा   GC_RX_BPDU_EN			0x02
#घोषणा   GC_MIB_AC_HDR_EN		0x10
#घोषणा   GC_MIB_AC_EN			0x20
#घोषणा   GC_FRM_MGMT_PORT_M		0xC0
#घोषणा   GC_FRM_MGMT_PORT_04		0x00
#घोषणा   GC_FRM_MGMT_PORT_MII		0x80

/* Broadcom Header control रेजिस्टर (8 bit) */
#घोषणा B53_BRCM_HDR			0x03
#घोषणा   BRCM_HDR_P8_EN		BIT(0) /* Enable tagging on port 8 */
#घोषणा   BRCM_HDR_P5_EN		BIT(1) /* Enable tagging on port 5 */
#घोषणा   BRCM_HDR_P7_EN		BIT(2) /* Enable tagging on port 7 */

/* Mirror capture control रेजिस्टर (16 bit) */
#घोषणा B53_MIR_CAP_CTL			0x10
#घोषणा  CAP_PORT_MASK			0xf
#घोषणा  BLK_NOT_MIR			BIT(14)
#घोषणा  MIRROR_EN			BIT(15)

/* Ingress mirror control रेजिस्टर (16 bit) */
#घोषणा B53_IG_MIR_CTL			0x12
#घोषणा  MIRROR_MASK			0x1ff
#घोषणा  DIV_EN				BIT(13)
#घोषणा  MIRROR_FILTER_MASK		0x3
#घोषणा  MIRROR_FILTER_SHIFT		14
#घोषणा  MIRROR_ALL			0
#घोषणा  MIRROR_DA			1
#घोषणा  MIRROR_SA			2

/* Ingress mirror भागider रेजिस्टर (16 bit) */
#घोषणा B53_IG_MIR_DIV			0x14
#घोषणा  IN_MIRROR_DIV_MASK		0x3ff

/* Ingress mirror MAC address रेजिस्टर (48 bit) */
#घोषणा B53_IG_MIR_MAC			0x16

/* Egress mirror control रेजिस्टर (16 bit) */
#घोषणा B53_EG_MIR_CTL			0x1C

/* Egress mirror भागider रेजिस्टर (16 bit) */
#घोषणा B53_EG_MIR_DIV			0x1E

/* Egress mirror MAC address रेजिस्टर (48 bit) */
#घोषणा B53_EG_MIR_MAC			0x20

/* Device ID रेजिस्टर (8 or 32 bit) */
#घोषणा B53_DEVICE_ID			0x30

/* Revision ID रेजिस्टर (8 bit) */
#घोषणा B53_REV_ID			0x40

/* Broadcom header RX control (16 bit) */
#घोषणा B53_BRCM_HDR_RX_DIS		0x60

/* Broadcom header TX control (16 bit)	*/
#घोषणा B53_BRCM_HDR_TX_DIS		0x62

/*************************************************************************
 * ARL Access Page Registers
 *************************************************************************/

/* VLAN Table Access Register (8 bit) */
#घोषणा B53_VT_ACCESS			0x80
#घोषणा B53_VT_ACCESS_9798		0x60 /* क्रम BCM5397/BCM5398 */
#घोषणा B53_VT_ACCESS_63XX		0x60 /* क्रम BCM6328/62/68 */
#घोषणा   VTA_CMD_WRITE			0
#घोषणा   VTA_CMD_READ			1
#घोषणा   VTA_CMD_CLEAR			2
#घोषणा   VTA_START_CMD			BIT(7)

/* VLAN Table Index Register (16 bit) */
#घोषणा B53_VT_INDEX			0x81
#घोषणा B53_VT_INDEX_9798		0x61
#घोषणा B53_VT_INDEX_63XX		0x62

/* VLAN Table Entry Register (32 bit) */
#घोषणा B53_VT_ENTRY			0x83
#घोषणा B53_VT_ENTRY_9798		0x63
#घोषणा B53_VT_ENTRY_63XX		0x64
#घोषणा   VTE_MEMBERS			0x1ff
#घोषणा   VTE_UNTAG_S			9
#घोषणा   VTE_UNTAG			(0x1ff << 9)

/*************************************************************************
 * ARL I/O Registers
 *************************************************************************/

/* ARL Table Read/Write Register (8 bit) */
#घोषणा B53_ARLTBL_RW_CTRL		0x00
#घोषणा    ARLTBL_RW			BIT(0)
#घोषणा    ARLTBL_IVL_SVL_SELECT	BIT(6)
#घोषणा    ARLTBL_START_DONE		BIT(7)

/* MAC Address Index Register (48 bit) */
#घोषणा B53_MAC_ADDR_IDX		0x02

/* VLAN ID Index Register (16 bit) */
#घोषणा B53_VLAN_ID_IDX			0x08

/* ARL Table MAC/VID Entry N Registers (64 bit)
 *
 * BCM5325 and BCM5365 share most definitions below
 */
#घोषणा B53_ARLTBL_MAC_VID_ENTRY(n)	((0x10 * (n)) + 0x10)
#घोषणा   ARLTBL_MAC_MASK		0xffffffffffffULL
#घोषणा   ARLTBL_VID_S			48
#घोषणा   ARLTBL_VID_MASK_25		0xff
#घोषणा   ARLTBL_VID_MASK		0xfff
#घोषणा   ARLTBL_DATA_PORT_ID_S_25	48
#घोषणा   ARLTBL_DATA_PORT_ID_MASK_25	0xf
#घोषणा   ARLTBL_AGE_25			BIT(61)
#घोषणा   ARLTBL_STATIC_25		BIT(62)
#घोषणा   ARLTBL_VALID_25		BIT(63)

/* ARL Table Data Entry N Registers (32 bit) */
#घोषणा B53_ARLTBL_DATA_ENTRY(n)	((0x10 * (n)) + 0x18)
#घोषणा   ARLTBL_DATA_PORT_ID_MASK	0x1ff
#घोषणा   ARLTBL_TC(tc)			((3 & tc) << 11)
#घोषणा   ARLTBL_AGE			BIT(14)
#घोषणा   ARLTBL_STATIC			BIT(15)
#घोषणा   ARLTBL_VALID			BIT(16)

/* Maximum number of bin entries in the ARL क्रम all चयनes */
#घोषणा B53_ARLTBL_MAX_BIN_ENTRIES	4

/* ARL Search Control Register (8 bit) */
#घोषणा B53_ARL_SRCH_CTL		0x50
#घोषणा B53_ARL_SRCH_CTL_25		0x20
#घोषणा   ARL_SRCH_VLID			BIT(0)
#घोषणा   ARL_SRCH_STDN			BIT(7)

/* ARL Search Address Register (16 bit) */
#घोषणा B53_ARL_SRCH_ADDR		0x51
#घोषणा B53_ARL_SRCH_ADDR_25		0x22
#घोषणा B53_ARL_SRCH_ADDR_65		0x24
#घोषणा  ARL_ADDR_MASK			GENMASK(14, 0)

/* ARL Search MAC/VID Result (64 bit) */
#घोषणा B53_ARL_SRCH_RSTL_0_MACVID	0x60

/* Single रेजिस्टर search result on 5325 */
#घोषणा B53_ARL_SRCH_RSTL_0_MACVID_25	0x24
/* Single रेजिस्टर search result on 5365 */
#घोषणा B53_ARL_SRCH_RSTL_0_MACVID_65	0x30

/* ARL Search Data Result (32 bit) */
#घोषणा B53_ARL_SRCH_RSTL_0		0x68

#घोषणा B53_ARL_SRCH_RSTL_MACVID(x)	(B53_ARL_SRCH_RSTL_0_MACVID + ((x) * 0x10))
#घोषणा B53_ARL_SRCH_RSTL(x)		(B53_ARL_SRCH_RSTL_0 + ((x) * 0x10))

/*************************************************************************
 * Port VLAN Registers
 *************************************************************************/

/* Port VLAN mask (16 bit) IMP port is always 8, also on 5325 & co */
#घोषणा B53_PVLAN_PORT_MASK(i)		((i) * 2)

/* Join all VLANs रेजिस्टर (16 bit) */
#घोषणा B53_JOIN_ALL_VLAN_EN		0x50

/*************************************************************************
 * 802.1Q Page Registers
 *************************************************************************/

/* Global QoS Control (8 bit) */
#घोषणा B53_QOS_GLOBAL_CTL		0x00

/* Enable 802.1Q क्रम inभागidual Ports (16 bit) */
#घोषणा B53_802_1P_EN			0x04

/*************************************************************************
 * VLAN Page Registers
 *************************************************************************/

/* VLAN Control 0 (8 bit) */
#घोषणा B53_VLAN_CTRL0			0x00
#घोषणा   VC0_8021PF_CTRL_MASK		0x3
#घोषणा   VC0_8021PF_CTRL_NONE		0x0
#घोषणा   VC0_8021PF_CTRL_CHANGE_PRI	0x1
#घोषणा   VC0_8021PF_CTRL_CHANGE_VID	0x2
#घोषणा   VC0_8021PF_CTRL_CHANGE_BOTH	0x3
#घोषणा   VC0_8021QF_CTRL_MASK		0xc
#घोषणा   VC0_8021QF_CTRL_CHANGE_PRI	0x1
#घोषणा   VC0_8021QF_CTRL_CHANGE_VID	0x2
#घोषणा   VC0_8021QF_CTRL_CHANGE_BOTH	0x3
#घोषणा   VC0_RESERVED_1		BIT(1)
#घोषणा   VC0_DROP_VID_MISS		BIT(4)
#घोषणा   VC0_VID_HASH_VID		BIT(5)
#घोषणा   VC0_VID_CHK_EN		BIT(6)	/* Use VID,DA or VID,SA */
#घोषणा   VC0_VLAN_EN			BIT(7)	/* 802.1Q VLAN Enabled */

/* VLAN Control 1 (8 bit) */
#घोषणा B53_VLAN_CTRL1			0x01
#घोषणा   VC1_RX_MCST_TAG_EN		BIT(1)
#घोषणा   VC1_RX_MCST_FWD_EN		BIT(2)
#घोषणा   VC1_RX_MCST_UNTAG_EN		BIT(3)

/* VLAN Control 2 (8 bit) */
#घोषणा B53_VLAN_CTRL2			0x02

/* VLAN Control 3 (8 bit when BCM5325, 16 bit अन्यथा) */
#घोषणा B53_VLAN_CTRL3			0x03
#घोषणा B53_VLAN_CTRL3_63XX		0x04
#घोषणा   VC3_MAXSIZE_1532		BIT(6) /* 5325 only */
#घोषणा   VC3_HIGH_8BIT_EN		BIT(7) /* 5325 only */

/* VLAN Control 4 (8 bit) */
#घोषणा B53_VLAN_CTRL4			0x05
#घोषणा B53_VLAN_CTRL4_25		0x04
#घोषणा B53_VLAN_CTRL4_63XX		0x06
#घोषणा   VC4_ING_VID_CHECK_S		6
#घोषणा   VC4_ING_VID_CHECK_MASK	(0x3 << VC4_ING_VID_CHECK_S)
#घोषणा   VC4_ING_VID_VIO_FWD		0 /* क्रमward, but करो not learn */
#घोषणा   VC4_ING_VID_VIO_DROP		1 /* drop VID violations */
#घोषणा   VC4_NO_ING_VID_CHK		2 /* करो not check */
#घोषणा   VC4_ING_VID_VIO_TO_IMP	3 /* redirect to MII port */

/* VLAN Control 5 (8 bit) */
#घोषणा B53_VLAN_CTRL5			0x06
#घोषणा B53_VLAN_CTRL5_25		0x05
#घोषणा B53_VLAN_CTRL5_63XX		0x07
#घोषणा   VC5_VID_FFF_EN		BIT(2)
#घोषणा   VC5_DROP_VTABLE_MISS		BIT(3)

/* VLAN Control 6 (8 bit) */
#घोषणा B53_VLAN_CTRL6			0x07
#घोषणा B53_VLAN_CTRL6_63XX		0x08

/* VLAN Table Access Register (16 bit) */
#घोषणा B53_VLAN_TABLE_ACCESS_25	0x06	/* BCM5325E/5350 */
#घोषणा B53_VLAN_TABLE_ACCESS_65	0x08	/* BCM5365 */
#घोषणा   VTA_VID_LOW_MASK_25		0xf
#घोषणा   VTA_VID_LOW_MASK_65		0xff
#घोषणा   VTA_VID_HIGH_S_25		4
#घोषणा   VTA_VID_HIGH_S_65		8
#घोषणा   VTA_VID_HIGH_MASK_25		(0xff << VTA_VID_HIGH_S_25E)
#घोषणा   VTA_VID_HIGH_MASK_65		(0xf << VTA_VID_HIGH_S_65)
#घोषणा   VTA_RW_STATE			BIT(12)
#घोषणा   VTA_RW_STATE_RD		0
#घोषणा   VTA_RW_STATE_WR		BIT(12)
#घोषणा   VTA_RW_OP_EN			BIT(13)

/* VLAN Read/Write Registers क्रम (16/32 bit) */
#घोषणा B53_VLAN_WRITE_25		0x08
#घोषणा B53_VLAN_WRITE_65		0x0a
#घोषणा B53_VLAN_READ			0x0c
#घोषणा   VA_MEMBER_MASK		0x3f
#घोषणा   VA_UNTAG_S_25			6
#घोषणा   VA_UNTAG_MASK_25		0x3f
#घोषणा   VA_UNTAG_S_65			7
#घोषणा   VA_UNTAG_MASK_65		0x1f
#घोषणा   VA_VID_HIGH_S			12
#घोषणा   VA_VID_HIGH_MASK		(0xffff << VA_VID_HIGH_S)
#घोषणा   VA_VALID_25			BIT(20)
#घोषणा   VA_VALID_25_R4		BIT(24)
#घोषणा   VA_VALID_65			BIT(14)

/* VLAN Port Default Tag (16 bit) */
#घोषणा B53_VLAN_PORT_DEF_TAG(i)	(0x10 + 2 * (i))

/*************************************************************************
 * Jumbo Frame Page Registers
 *************************************************************************/

/* Jumbo Enable Port Mask (bit i == port i enabled) (32 bit) */
#घोषणा B53_JUMBO_PORT_MASK		0x01
#घोषणा B53_JUMBO_PORT_MASK_63XX	0x04
#घोषणा   JPM_10_100_JUMBO_EN		BIT(24) /* GigE always enabled */

/* Good Frame Max Size without 802.1Q TAG (16 bit) */
#घोषणा B53_JUMBO_MAX_SIZE		0x05
#घोषणा B53_JUMBO_MAX_SIZE_63XX		0x08
#घोषणा   JMS_MIN_SIZE			1518
#घोषणा   JMS_MAX_SIZE			9724

/*************************************************************************
 * EEE Configuration Page Registers
 *************************************************************************/

/* EEE Enable control रेजिस्टर (16 bit) */
#घोषणा B53_EEE_EN_CTRL			0x00

/* EEE LPI निश्चित status रेजिस्टर (16 bit) */
#घोषणा B53_EEE_LPI_ASSERT_STS		0x02

/* EEE LPI indicate status रेजिस्टर (16 bit) */
#घोषणा B53_EEE_LPI_INDICATE		0x4

/* EEE Receiving idle symbols status रेजिस्टर (16 bit) */
#घोषणा B53_EEE_RX_IDLE_SYM_STS		0x6

/* EEE Pipeline समयr रेजिस्टर (32 bit) */
#घोषणा B53_EEE_PIP_TIMER		0xC

/* EEE Sleep समयr Gig रेजिस्टर (32 bit) */
#घोषणा B53_EEE_SLEEP_TIMER_GIG(i)	(0x10 + 4 * (i))

/* EEE Sleep समयr FE रेजिस्टर (32 bit) */
#घोषणा B53_EEE_SLEEP_TIMER_FE(i)	(0x34 + 4 * (i))

/* EEE Minimum LP समयr Gig रेजिस्टर (32 bit) */
#घोषणा B53_EEE_MIN_LP_TIMER_GIG(i)	(0x58 + 4 * (i))

/* EEE Minimum LP समयr FE रेजिस्टर (32 bit) */
#घोषणा B53_EEE_MIN_LP_TIMER_FE(i)	(0x7c + 4 * (i))

/* EEE Wake समयr Gig रेजिस्टर (16 bit) */
#घोषणा B53_EEE_WAKE_TIMER_GIG(i)	(0xa0 + 2 * (i))

/* EEE Wake समयr FE रेजिस्टर (16 bit) */
#घोषणा B53_EEE_WAKE_TIMER_FE(i)	(0xb2 + 2 * (i))


/*************************************************************************
 * CFP Configuration Page Registers
 *************************************************************************/

/* CFP Control Register with ports map (8 bit) */
#घोषणा B53_CFP_CTRL			0x00

#पूर्ण_अगर /* !__B53_REGS_H */
