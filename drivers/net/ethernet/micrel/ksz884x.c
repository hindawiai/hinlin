<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/net/ethernet/micrel/ksx884x.c - Micrel KSZ8841/2 PCI Ethernet driver
 *
 * Copyright (c) 2009-2010 Micrel, Inc.
 * 	Tristram Ha <Tristram.Ha@micrel.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/ioport.h>
#समावेश <linux/pci.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/mii.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/crc32.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>


/* DMA Registers */

#घोषणा KS_DMA_TX_CTRL			0x0000
#घोषणा DMA_TX_ENABLE			0x00000001
#घोषणा DMA_TX_CRC_ENABLE		0x00000002
#घोषणा DMA_TX_PAD_ENABLE		0x00000004
#घोषणा DMA_TX_LOOPBACK			0x00000100
#घोषणा DMA_TX_FLOW_ENABLE		0x00000200
#घोषणा DMA_TX_CSUM_IP			0x00010000
#घोषणा DMA_TX_CSUM_TCP			0x00020000
#घोषणा DMA_TX_CSUM_UDP			0x00040000
#घोषणा DMA_TX_BURST_SIZE		0x3F000000

#घोषणा KS_DMA_RX_CTRL			0x0004
#घोषणा DMA_RX_ENABLE			0x00000001
#घोषणा KS884X_DMA_RX_MULTICAST		0x00000002
#घोषणा DMA_RX_PROMISCUOUS		0x00000004
#घोषणा DMA_RX_ERROR			0x00000008
#घोषणा DMA_RX_UNICAST			0x00000010
#घोषणा DMA_RX_ALL_MULTICAST		0x00000020
#घोषणा DMA_RX_BROADCAST		0x00000040
#घोषणा DMA_RX_FLOW_ENABLE		0x00000200
#घोषणा DMA_RX_CSUM_IP			0x00010000
#घोषणा DMA_RX_CSUM_TCP			0x00020000
#घोषणा DMA_RX_CSUM_UDP			0x00040000
#घोषणा DMA_RX_BURST_SIZE		0x3F000000

#घोषणा DMA_BURST_SHIFT			24
#घोषणा DMA_BURST_DEFAULT		8

#घोषणा KS_DMA_TX_START			0x0008
#घोषणा KS_DMA_RX_START			0x000C
#घोषणा DMA_START			0x00000001

#घोषणा KS_DMA_TX_ADDR			0x0010
#घोषणा KS_DMA_RX_ADDR			0x0014

#घोषणा DMA_ADDR_LIST_MASK		0xFFFFFFFC
#घोषणा DMA_ADDR_LIST_SHIFT		2

/* MTR0 */
#घोषणा KS884X_MULTICAST_0_OFFSET	0x0020
#घोषणा KS884X_MULTICAST_1_OFFSET	0x0021
#घोषणा KS884X_MULTICAST_2_OFFSET	0x0022
#घोषणा KS884x_MULTICAST_3_OFFSET	0x0023
/* MTR1 */
#घोषणा KS884X_MULTICAST_4_OFFSET	0x0024
#घोषणा KS884X_MULTICAST_5_OFFSET	0x0025
#घोषणा KS884X_MULTICAST_6_OFFSET	0x0026
#घोषणा KS884X_MULTICAST_7_OFFSET	0x0027

/* Interrupt Registers */

/* INTEN */
#घोषणा KS884X_INTERRUPTS_ENABLE	0x0028
/* INTST */
#घोषणा KS884X_INTERRUPTS_STATUS	0x002C

#घोषणा KS884X_INT_RX_STOPPED		0x02000000
#घोषणा KS884X_INT_TX_STOPPED		0x04000000
#घोषणा KS884X_INT_RX_OVERRUN		0x08000000
#घोषणा KS884X_INT_TX_EMPTY		0x10000000
#घोषणा KS884X_INT_RX			0x20000000
#घोषणा KS884X_INT_TX			0x40000000
#घोषणा KS884X_INT_PHY			0x80000000

#घोषणा KS884X_INT_RX_MASK		\
	(KS884X_INT_RX | KS884X_INT_RX_OVERRUN)
#घोषणा KS884X_INT_TX_MASK		\
	(KS884X_INT_TX | KS884X_INT_TX_EMPTY)
#घोषणा KS884X_INT_MASK	(KS884X_INT_RX | KS884X_INT_TX | KS884X_INT_PHY)

/* MAC Additional Station Address */

/* MAAL0 */
#घोषणा KS_ADD_ADDR_0_LO		0x0080
/* MAAH0 */
#घोषणा KS_ADD_ADDR_0_HI		0x0084
/* MAAL1 */
#घोषणा KS_ADD_ADDR_1_LO		0x0088
/* MAAH1 */
#घोषणा KS_ADD_ADDR_1_HI		0x008C
/* MAAL2 */
#घोषणा KS_ADD_ADDR_2_LO		0x0090
/* MAAH2 */
#घोषणा KS_ADD_ADDR_2_HI		0x0094
/* MAAL3 */
#घोषणा KS_ADD_ADDR_3_LO		0x0098
/* MAAH3 */
#घोषणा KS_ADD_ADDR_3_HI		0x009C
/* MAAL4 */
#घोषणा KS_ADD_ADDR_4_LO		0x00A0
/* MAAH4 */
#घोषणा KS_ADD_ADDR_4_HI		0x00A4
/* MAAL5 */
#घोषणा KS_ADD_ADDR_5_LO		0x00A8
/* MAAH5 */
#घोषणा KS_ADD_ADDR_5_HI		0x00AC
/* MAAL6 */
#घोषणा KS_ADD_ADDR_6_LO		0x00B0
/* MAAH6 */
#घोषणा KS_ADD_ADDR_6_HI		0x00B4
/* MAAL7 */
#घोषणा KS_ADD_ADDR_7_LO		0x00B8
/* MAAH7 */
#घोषणा KS_ADD_ADDR_7_HI		0x00BC
/* MAAL8 */
#घोषणा KS_ADD_ADDR_8_LO		0x00C0
/* MAAH8 */
#घोषणा KS_ADD_ADDR_8_HI		0x00C4
/* MAAL9 */
#घोषणा KS_ADD_ADDR_9_LO		0x00C8
/* MAAH9 */
#घोषणा KS_ADD_ADDR_9_HI		0x00CC
/* MAAL10 */
#घोषणा KS_ADD_ADDR_A_LO		0x00D0
/* MAAH10 */
#घोषणा KS_ADD_ADDR_A_HI		0x00D4
/* MAAL11 */
#घोषणा KS_ADD_ADDR_B_LO		0x00D8
/* MAAH11 */
#घोषणा KS_ADD_ADDR_B_HI		0x00DC
/* MAAL12 */
#घोषणा KS_ADD_ADDR_C_LO		0x00E0
/* MAAH12 */
#घोषणा KS_ADD_ADDR_C_HI		0x00E4
/* MAAL13 */
#घोषणा KS_ADD_ADDR_D_LO		0x00E8
/* MAAH13 */
#घोषणा KS_ADD_ADDR_D_HI		0x00EC
/* MAAL14 */
#घोषणा KS_ADD_ADDR_E_LO		0x00F0
/* MAAH14 */
#घोषणा KS_ADD_ADDR_E_HI		0x00F4
/* MAAL15 */
#घोषणा KS_ADD_ADDR_F_LO		0x00F8
/* MAAH15 */
#घोषणा KS_ADD_ADDR_F_HI		0x00FC

#घोषणा ADD_ADDR_HI_MASK		0x0000FFFF
#घोषणा ADD_ADDR_ENABLE			0x80000000
#घोषणा ADD_ADDR_INCR			8

/* Miscellaneous Registers */

/* MARL */
#घोषणा KS884X_ADDR_0_OFFSET		0x0200
#घोषणा KS884X_ADDR_1_OFFSET		0x0201
/* MARM */
#घोषणा KS884X_ADDR_2_OFFSET		0x0202
#घोषणा KS884X_ADDR_3_OFFSET		0x0203
/* MARH */
#घोषणा KS884X_ADDR_4_OFFSET		0x0204
#घोषणा KS884X_ADDR_5_OFFSET		0x0205

/* OBCR */
#घोषणा KS884X_BUS_CTRL_OFFSET		0x0210

#घोषणा BUS_SPEED_125_MHZ		0x0000
#घोषणा BUS_SPEED_62_5_MHZ		0x0001
#घोषणा BUS_SPEED_41_66_MHZ		0x0002
#घोषणा BUS_SPEED_25_MHZ		0x0003

/* EEPCR */
#घोषणा KS884X_EEPROM_CTRL_OFFSET	0x0212

#घोषणा EEPROM_CHIP_SELECT		0x0001
#घोषणा EEPROM_SERIAL_CLOCK		0x0002
#घोषणा EEPROM_DATA_OUT			0x0004
#घोषणा EEPROM_DATA_IN			0x0008
#घोषणा EEPROM_ACCESS_ENABLE		0x0010

/* MBIR */
#घोषणा KS884X_MEM_INFO_OFFSET		0x0214

#घोषणा RX_MEM_TEST_FAILED		0x0008
#घोषणा RX_MEM_TEST_FINISHED		0x0010
#घोषणा TX_MEM_TEST_FAILED		0x0800
#घोषणा TX_MEM_TEST_FINISHED		0x1000

/* GCR */
#घोषणा KS884X_GLOBAL_CTRL_OFFSET	0x0216
#घोषणा GLOBAL_SOFTWARE_RESET		0x0001

#घोषणा KS8841_POWER_MANAGE_OFFSET	0x0218

/* WFCR */
#घोषणा KS8841_WOL_CTRL_OFFSET		0x021A
#घोषणा KS8841_WOL_MAGIC_ENABLE		0x0080
#घोषणा KS8841_WOL_FRAME3_ENABLE	0x0008
#घोषणा KS8841_WOL_FRAME2_ENABLE	0x0004
#घोषणा KS8841_WOL_FRAME1_ENABLE	0x0002
#घोषणा KS8841_WOL_FRAME0_ENABLE	0x0001

/* WF0 */
#घोषणा KS8841_WOL_FRAME_CRC_OFFSET	0x0220
#घोषणा KS8841_WOL_FRAME_BYTE0_OFFSET	0x0224
#घोषणा KS8841_WOL_FRAME_BYTE2_OFFSET	0x0228

/* IACR */
#घोषणा KS884X_IACR_P			0x04A0
#घोषणा KS884X_IACR_OFFSET		KS884X_IACR_P

/* IADR1 */
#घोषणा KS884X_IADR1_P			0x04A2
#घोषणा KS884X_IADR2_P			0x04A4
#घोषणा KS884X_IADR3_P			0x04A6
#घोषणा KS884X_IADR4_P			0x04A8
#घोषणा KS884X_IADR5_P			0x04AA

#घोषणा KS884X_ACC_CTRL_SEL_OFFSET	KS884X_IACR_P
#घोषणा KS884X_ACC_CTRL_INDEX_OFFSET	(KS884X_ACC_CTRL_SEL_OFFSET + 1)

#घोषणा KS884X_ACC_DATA_0_OFFSET	KS884X_IADR4_P
#घोषणा KS884X_ACC_DATA_1_OFFSET	(KS884X_ACC_DATA_0_OFFSET + 1)
#घोषणा KS884X_ACC_DATA_2_OFFSET	KS884X_IADR5_P
#घोषणा KS884X_ACC_DATA_3_OFFSET	(KS884X_ACC_DATA_2_OFFSET + 1)
#घोषणा KS884X_ACC_DATA_4_OFFSET	KS884X_IADR2_P
#घोषणा KS884X_ACC_DATA_5_OFFSET	(KS884X_ACC_DATA_4_OFFSET + 1)
#घोषणा KS884X_ACC_DATA_6_OFFSET	KS884X_IADR3_P
#घोषणा KS884X_ACC_DATA_7_OFFSET	(KS884X_ACC_DATA_6_OFFSET + 1)
#घोषणा KS884X_ACC_DATA_8_OFFSET	KS884X_IADR1_P

/* P1MBCR */
#घोषणा KS884X_P1MBCR_P			0x04D0
#घोषणा KS884X_P1MBSR_P			0x04D2
#घोषणा KS884X_PHY1ILR_P		0x04D4
#घोषणा KS884X_PHY1IHR_P		0x04D6
#घोषणा KS884X_P1ANAR_P			0x04D8
#घोषणा KS884X_P1ANLPR_P		0x04DA

/* P2MBCR */
#घोषणा KS884X_P2MBCR_P			0x04E0
#घोषणा KS884X_P2MBSR_P			0x04E2
#घोषणा KS884X_PHY2ILR_P		0x04E4
#घोषणा KS884X_PHY2IHR_P		0x04E6
#घोषणा KS884X_P2ANAR_P			0x04E8
#घोषणा KS884X_P2ANLPR_P		0x04EA

#घोषणा KS884X_PHY_1_CTRL_OFFSET	KS884X_P1MBCR_P
#घोषणा PHY_CTRL_INTERVAL		(KS884X_P2MBCR_P - KS884X_P1MBCR_P)

#घोषणा KS884X_PHY_CTRL_OFFSET		0x00

/* Mode Control Register */
#घोषणा PHY_REG_CTRL			0

#घोषणा PHY_RESET			0x8000
#घोषणा PHY_LOOPBACK			0x4000
#घोषणा PHY_SPEED_100MBIT		0x2000
#घोषणा PHY_AUTO_NEG_ENABLE		0x1000
#घोषणा PHY_POWER_DOWN			0x0800
#घोषणा PHY_MII_DISABLE			0x0400
#घोषणा PHY_AUTO_NEG_RESTART		0x0200
#घोषणा PHY_FULL_DUPLEX			0x0100
#घोषणा PHY_COLLISION_TEST		0x0080
#घोषणा PHY_HP_MDIX			0x0020
#घोषणा PHY_FORCE_MDIX			0x0010
#घोषणा PHY_AUTO_MDIX_DISABLE		0x0008
#घोषणा PHY_REMOTE_FAULT_DISABLE	0x0004
#घोषणा PHY_TRANSMIT_DISABLE		0x0002
#घोषणा PHY_LED_DISABLE			0x0001

#घोषणा KS884X_PHY_STATUS_OFFSET	0x02

/* Mode Status Register */
#घोषणा PHY_REG_STATUS			1

#घोषणा PHY_100BT4_CAPABLE		0x8000
#घोषणा PHY_100BTX_FD_CAPABLE		0x4000
#घोषणा PHY_100BTX_CAPABLE		0x2000
#घोषणा PHY_10BT_FD_CAPABLE		0x1000
#घोषणा PHY_10BT_CAPABLE		0x0800
#घोषणा PHY_MII_SUPPRESS_CAPABLE	0x0040
#घोषणा PHY_AUTO_NEG_ACKNOWLEDGE	0x0020
#घोषणा PHY_REMOTE_FAULT		0x0010
#घोषणा PHY_AUTO_NEG_CAPABLE		0x0008
#घोषणा PHY_LINK_STATUS			0x0004
#घोषणा PHY_JABBER_DETECT		0x0002
#घोषणा PHY_EXTENDED_CAPABILITY		0x0001

#घोषणा KS884X_PHY_ID_1_OFFSET		0x04
#घोषणा KS884X_PHY_ID_2_OFFSET		0x06

/* PHY Identअगरier Registers */
#घोषणा PHY_REG_ID_1			2
#घोषणा PHY_REG_ID_2			3

#घोषणा KS884X_PHY_AUTO_NEG_OFFSET	0x08

/* Auto-Negotiation Advertisement Register */
#घोषणा PHY_REG_AUTO_NEGOTIATION	4

#घोषणा PHY_AUTO_NEG_NEXT_PAGE		0x8000
#घोषणा PHY_AUTO_NEG_REMOTE_FAULT	0x2000
/* Not supported. */
#घोषणा PHY_AUTO_NEG_ASYM_PAUSE		0x0800
#घोषणा PHY_AUTO_NEG_SYM_PAUSE		0x0400
#घोषणा PHY_AUTO_NEG_100BT4		0x0200
#घोषणा PHY_AUTO_NEG_100BTX_FD		0x0100
#घोषणा PHY_AUTO_NEG_100BTX		0x0080
#घोषणा PHY_AUTO_NEG_10BT_FD		0x0040
#घोषणा PHY_AUTO_NEG_10BT		0x0020
#घोषणा PHY_AUTO_NEG_SELECTOR		0x001F
#घोषणा PHY_AUTO_NEG_802_3		0x0001

#घोषणा PHY_AUTO_NEG_PAUSE  (PHY_AUTO_NEG_SYM_PAUSE | PHY_AUTO_NEG_ASYM_PAUSE)

#घोषणा KS884X_PHY_REMOTE_CAP_OFFSET	0x0A

/* Auto-Negotiation Link Partner Ability Register */
#घोषणा PHY_REG_REMOTE_CAPABILITY	5

#घोषणा PHY_REMOTE_NEXT_PAGE		0x8000
#घोषणा PHY_REMOTE_ACKNOWLEDGE		0x4000
#घोषणा PHY_REMOTE_REMOTE_FAULT		0x2000
#घोषणा PHY_REMOTE_SYM_PAUSE		0x0400
#घोषणा PHY_REMOTE_100BTX_FD		0x0100
#घोषणा PHY_REMOTE_100BTX		0x0080
#घोषणा PHY_REMOTE_10BT_FD		0x0040
#घोषणा PHY_REMOTE_10BT			0x0020

/* P1VCT */
#घोषणा KS884X_P1VCT_P			0x04F0
#घोषणा KS884X_P1PHYCTRL_P		0x04F2

/* P2VCT */
#घोषणा KS884X_P2VCT_P			0x04F4
#घोषणा KS884X_P2PHYCTRL_P		0x04F6

#घोषणा KS884X_PHY_SPECIAL_OFFSET	KS884X_P1VCT_P
#घोषणा PHY_SPECIAL_INTERVAL		(KS884X_P2VCT_P - KS884X_P1VCT_P)

#घोषणा KS884X_PHY_LINK_MD_OFFSET	0x00

#घोषणा PHY_START_CABLE_DIAG		0x8000
#घोषणा PHY_CABLE_DIAG_RESULT		0x6000
#घोषणा PHY_CABLE_STAT_NORMAL		0x0000
#घोषणा PHY_CABLE_STAT_OPEN		0x2000
#घोषणा PHY_CABLE_STAT_SHORT		0x4000
#घोषणा PHY_CABLE_STAT_FAILED		0x6000
#घोषणा PHY_CABLE_10M_SHORT		0x1000
#घोषणा PHY_CABLE_FAULT_COUNTER		0x01FF

#घोषणा KS884X_PHY_PHY_CTRL_OFFSET	0x02

#घोषणा PHY_STAT_REVERSED_POLARITY	0x0020
#घोषणा PHY_STAT_MDIX			0x0010
#घोषणा PHY_FORCE_LINK			0x0008
#घोषणा PHY_POWER_SAVING_DISABLE	0x0004
#घोषणा PHY_REMOTE_LOOPBACK		0x0002

/* SIDER */
#घोषणा KS884X_SIDER_P			0x0400
#घोषणा KS884X_CHIP_ID_OFFSET		KS884X_SIDER_P
#घोषणा KS884X_FAMILY_ID_OFFSET		(KS884X_CHIP_ID_OFFSET + 1)

#घोषणा REG_FAMILY_ID			0x88

#घोषणा REG_CHIP_ID_41			0x8810
#घोषणा REG_CHIP_ID_42			0x8800

#घोषणा KS884X_CHIP_ID_MASK_41		0xFF10
#घोषणा KS884X_CHIP_ID_MASK		0xFFF0
#घोषणा KS884X_CHIP_ID_SHIFT		4
#घोषणा KS884X_REVISION_MASK		0x000E
#घोषणा KS884X_REVISION_SHIFT		1
#घोषणा KS8842_START			0x0001

#घोषणा CHIP_IP_41_M			0x8810
#घोषणा CHIP_IP_42_M			0x8800
#घोषणा CHIP_IP_61_M			0x8890
#घोषणा CHIP_IP_62_M			0x8880

#घोषणा CHIP_IP_41_P			0x8850
#घोषणा CHIP_IP_42_P			0x8840
#घोषणा CHIP_IP_61_P			0x88D0
#घोषणा CHIP_IP_62_P			0x88C0

/* SGCR1 */
#घोषणा KS8842_SGCR1_P			0x0402
#घोषणा KS8842_SWITCH_CTRL_1_OFFSET	KS8842_SGCR1_P

#घोषणा SWITCH_PASS_ALL			0x8000
#घोषणा SWITCH_TX_FLOW_CTRL		0x2000
#घोषणा SWITCH_RX_FLOW_CTRL		0x1000
#घोषणा SWITCH_CHECK_LENGTH		0x0800
#घोषणा SWITCH_AGING_ENABLE		0x0400
#घोषणा SWITCH_FAST_AGING		0x0200
#घोषणा SWITCH_AGGR_BACKOFF		0x0100
#घोषणा SWITCH_PASS_PAUSE		0x0008
#घोषणा SWITCH_LINK_AUTO_AGING		0x0001

/* SGCR2 */
#घोषणा KS8842_SGCR2_P			0x0404
#घोषणा KS8842_SWITCH_CTRL_2_OFFSET	KS8842_SGCR2_P

#घोषणा SWITCH_VLAN_ENABLE		0x8000
#घोषणा SWITCH_IGMP_SNOOP		0x4000
#घोषणा IPV6_MLD_SNOOP_ENABLE		0x2000
#घोषणा IPV6_MLD_SNOOP_OPTION		0x1000
#घोषणा PRIORITY_SCHEME_SELECT		0x0800
#घोषणा SWITCH_MIRROR_RX_TX		0x0100
#घोषणा UNICAST_VLAN_BOUNDARY		0x0080
#घोषणा MULTICAST_STORM_DISABLE		0x0040
#घोषणा SWITCH_BACK_PRESSURE		0x0020
#घोषणा FAIR_FLOW_CTRL			0x0010
#घोषणा NO_EXC_COLLISION_DROP		0x0008
#घोषणा SWITCH_HUGE_PACKET		0x0004
#घोषणा SWITCH_LEGAL_PACKET		0x0002
#घोषणा SWITCH_BUF_RESERVE		0x0001

/* SGCR3 */
#घोषणा KS8842_SGCR3_P			0x0406
#घोषणा KS8842_SWITCH_CTRL_3_OFFSET	KS8842_SGCR3_P

#घोषणा BROADCAST_STORM_RATE_LO		0xFF00
#घोषणा SWITCH_REPEATER			0x0080
#घोषणा SWITCH_HALF_DUPLEX		0x0040
#घोषणा SWITCH_FLOW_CTRL		0x0020
#घोषणा SWITCH_10_MBIT			0x0010
#घोषणा SWITCH_REPLACE_शून्य_VID		0x0008
#घोषणा BROADCAST_STORM_RATE_HI		0x0007

#घोषणा BROADCAST_STORM_RATE		0x07FF

/* SGCR4 */
#घोषणा KS8842_SGCR4_P			0x0408

/* SGCR5 */
#घोषणा KS8842_SGCR5_P			0x040A
#घोषणा KS8842_SWITCH_CTRL_5_OFFSET	KS8842_SGCR5_P

#घोषणा LED_MODE			0x8200
#घोषणा LED_SPEED_DUPLEX_ACT		0x0000
#घोषणा LED_SPEED_DUPLEX_LINK_ACT	0x8000
#घोषणा LED_DUPLEX_10_100		0x0200

/* SGCR6 */
#घोषणा KS8842_SGCR6_P			0x0410
#घोषणा KS8842_SWITCH_CTRL_6_OFFSET	KS8842_SGCR6_P

#घोषणा KS8842_PRIORITY_MASK		3
#घोषणा KS8842_PRIORITY_SHIFT		2

/* SGCR7 */
#घोषणा KS8842_SGCR7_P			0x0412
#घोषणा KS8842_SWITCH_CTRL_7_OFFSET	KS8842_SGCR7_P

#घोषणा SWITCH_UNK_DEF_PORT_ENABLE	0x0008
#घोषणा SWITCH_UNK_DEF_PORT_3		0x0004
#घोषणा SWITCH_UNK_DEF_PORT_2		0x0002
#घोषणा SWITCH_UNK_DEF_PORT_1		0x0001

/* MACAR1 */
#घोषणा KS8842_MACAR1_P			0x0470
#घोषणा KS8842_MACAR2_P			0x0472
#घोषणा KS8842_MACAR3_P			0x0474
#घोषणा KS8842_MAC_ADDR_1_OFFSET	KS8842_MACAR1_P
#घोषणा KS8842_MAC_ADDR_0_OFFSET	(KS8842_MAC_ADDR_1_OFFSET + 1)
#घोषणा KS8842_MAC_ADDR_3_OFFSET	KS8842_MACAR2_P
#घोषणा KS8842_MAC_ADDR_2_OFFSET	(KS8842_MAC_ADDR_3_OFFSET + 1)
#घोषणा KS8842_MAC_ADDR_5_OFFSET	KS8842_MACAR3_P
#घोषणा KS8842_MAC_ADDR_4_OFFSET	(KS8842_MAC_ADDR_5_OFFSET + 1)

/* TOSR1 */
#घोषणा KS8842_TOSR1_P			0x0480
#घोषणा KS8842_TOSR2_P			0x0482
#घोषणा KS8842_TOSR3_P			0x0484
#घोषणा KS8842_TOSR4_P			0x0486
#घोषणा KS8842_TOSR5_P			0x0488
#घोषणा KS8842_TOSR6_P			0x048A
#घोषणा KS8842_TOSR7_P			0x0490
#घोषणा KS8842_TOSR8_P			0x0492
#घोषणा KS8842_TOS_1_OFFSET		KS8842_TOSR1_P
#घोषणा KS8842_TOS_2_OFFSET		KS8842_TOSR2_P
#घोषणा KS8842_TOS_3_OFFSET		KS8842_TOSR3_P
#घोषणा KS8842_TOS_4_OFFSET		KS8842_TOSR4_P
#घोषणा KS8842_TOS_5_OFFSET		KS8842_TOSR5_P
#घोषणा KS8842_TOS_6_OFFSET		KS8842_TOSR6_P

#घोषणा KS8842_TOS_7_OFFSET		KS8842_TOSR7_P
#घोषणा KS8842_TOS_8_OFFSET		KS8842_TOSR8_P

/* P1CR1 */
#घोषणा KS8842_P1CR1_P			0x0500
#घोषणा KS8842_P1CR2_P			0x0502
#घोषणा KS8842_P1VIDR_P			0x0504
#घोषणा KS8842_P1CR3_P			0x0506
#घोषणा KS8842_P1IRCR_P			0x0508
#घोषणा KS8842_P1ERCR_P			0x050A
#घोषणा KS884X_P1SCSLMD_P		0x0510
#घोषणा KS884X_P1CR4_P			0x0512
#घोषणा KS884X_P1SR_P			0x0514

/* P2CR1 */
#घोषणा KS8842_P2CR1_P			0x0520
#घोषणा KS8842_P2CR2_P			0x0522
#घोषणा KS8842_P2VIDR_P			0x0524
#घोषणा KS8842_P2CR3_P			0x0526
#घोषणा KS8842_P2IRCR_P			0x0528
#घोषणा KS8842_P2ERCR_P			0x052A
#घोषणा KS884X_P2SCSLMD_P		0x0530
#घोषणा KS884X_P2CR4_P			0x0532
#घोषणा KS884X_P2SR_P			0x0534

/* P3CR1 */
#घोषणा KS8842_P3CR1_P			0x0540
#घोषणा KS8842_P3CR2_P			0x0542
#घोषणा KS8842_P3VIDR_P			0x0544
#घोषणा KS8842_P3CR3_P			0x0546
#घोषणा KS8842_P3IRCR_P			0x0548
#घोषणा KS8842_P3ERCR_P			0x054A

#घोषणा KS8842_PORT_1_CTRL_1		KS8842_P1CR1_P
#घोषणा KS8842_PORT_2_CTRL_1		KS8842_P2CR1_P
#घोषणा KS8842_PORT_3_CTRL_1		KS8842_P3CR1_P

#घोषणा PORT_CTRL_ADDR(port, addr)		\
	(addr = KS8842_PORT_1_CTRL_1 + (port) *	\
		(KS8842_PORT_2_CTRL_1 - KS8842_PORT_1_CTRL_1))

#घोषणा KS8842_PORT_CTRL_1_OFFSET	0x00

#घोषणा PORT_BROADCAST_STORM		0x0080
#घोषणा PORT_DIFFSERV_ENABLE		0x0040
#घोषणा PORT_802_1P_ENABLE		0x0020
#घोषणा PORT_BASED_PRIORITY_MASK	0x0018
#घोषणा PORT_BASED_PRIORITY_BASE	0x0003
#घोषणा PORT_BASED_PRIORITY_SHIFT	3
#घोषणा PORT_BASED_PRIORITY_0		0x0000
#घोषणा PORT_BASED_PRIORITY_1		0x0008
#घोषणा PORT_BASED_PRIORITY_2		0x0010
#घोषणा PORT_BASED_PRIORITY_3		0x0018
#घोषणा PORT_INSERT_TAG			0x0004
#घोषणा PORT_REMOVE_TAG			0x0002
#घोषणा PORT_PRIO_QUEUE_ENABLE		0x0001

#घोषणा KS8842_PORT_CTRL_2_OFFSET	0x02

#घोषणा PORT_INGRESS_VLAN_FILTER	0x4000
#घोषणा PORT_DISCARD_NON_VID		0x2000
#घोषणा PORT_FORCE_FLOW_CTRL		0x1000
#घोषणा PORT_BACK_PRESSURE		0x0800
#घोषणा PORT_TX_ENABLE			0x0400
#घोषणा PORT_RX_ENABLE			0x0200
#घोषणा PORT_LEARN_DISABLE		0x0100
#घोषणा PORT_MIRROR_SNIFFER		0x0080
#घोषणा PORT_MIRROR_RX			0x0040
#घोषणा PORT_MIRROR_TX			0x0020
#घोषणा PORT_USER_PRIORITY_CEILING	0x0008
#घोषणा PORT_VLAN_MEMBERSHIP		0x0007

#घोषणा KS8842_PORT_CTRL_VID_OFFSET	0x04

#घोषणा PORT_DEFAULT_VID		0x0001

#घोषणा KS8842_PORT_CTRL_3_OFFSET	0x06

#घोषणा PORT_INGRESS_LIMIT_MODE		0x000C
#घोषणा PORT_INGRESS_ALL		0x0000
#घोषणा PORT_INGRESS_UNICAST		0x0004
#घोषणा PORT_INGRESS_MULTICAST		0x0008
#घोषणा PORT_INGRESS_BROADCAST		0x000C
#घोषणा PORT_COUNT_IFG			0x0002
#घोषणा PORT_COUNT_PREAMBLE		0x0001

#घोषणा KS8842_PORT_IN_RATE_OFFSET	0x08
#घोषणा KS8842_PORT_OUT_RATE_OFFSET	0x0A

#घोषणा PORT_PRIORITY_RATE		0x0F
#घोषणा PORT_PRIORITY_RATE_SHIFT	4

#घोषणा KS884X_PORT_LINK_MD		0x10

#घोषणा PORT_CABLE_10M_SHORT		0x8000
#घोषणा PORT_CABLE_DIAG_RESULT		0x6000
#घोषणा PORT_CABLE_STAT_NORMAL		0x0000
#घोषणा PORT_CABLE_STAT_OPEN		0x2000
#घोषणा PORT_CABLE_STAT_SHORT		0x4000
#घोषणा PORT_CABLE_STAT_FAILED		0x6000
#घोषणा PORT_START_CABLE_DIAG		0x1000
#घोषणा PORT_FORCE_LINK			0x0800
#घोषणा PORT_POWER_SAVING_DISABLE	0x0400
#घोषणा PORT_PHY_REMOTE_LOOPBACK	0x0200
#घोषणा PORT_CABLE_FAULT_COUNTER	0x01FF

#घोषणा KS884X_PORT_CTRL_4_OFFSET	0x12

#घोषणा PORT_LED_OFF			0x8000
#घोषणा PORT_TX_DISABLE			0x4000
#घोषणा PORT_AUTO_NEG_RESTART		0x2000
#घोषणा PORT_REMOTE_FAULT_DISABLE	0x1000
#घोषणा PORT_POWER_DOWN			0x0800
#घोषणा PORT_AUTO_MDIX_DISABLE		0x0400
#घोषणा PORT_FORCE_MDIX			0x0200
#घोषणा PORT_LOOPBACK			0x0100
#घोषणा PORT_AUTO_NEG_ENABLE		0x0080
#घोषणा PORT_FORCE_100_MBIT		0x0040
#घोषणा PORT_FORCE_FULL_DUPLEX		0x0020
#घोषणा PORT_AUTO_NEG_SYM_PAUSE		0x0010
#घोषणा PORT_AUTO_NEG_100BTX_FD		0x0008
#घोषणा PORT_AUTO_NEG_100BTX		0x0004
#घोषणा PORT_AUTO_NEG_10BT_FD		0x0002
#घोषणा PORT_AUTO_NEG_10BT		0x0001

#घोषणा KS884X_PORT_STATUS_OFFSET	0x14

#घोषणा PORT_HP_MDIX			0x8000
#घोषणा PORT_REVERSED_POLARITY		0x2000
#घोषणा PORT_RX_FLOW_CTRL		0x0800
#घोषणा PORT_TX_FLOW_CTRL		0x1000
#घोषणा PORT_STATUS_SPEED_100MBIT	0x0400
#घोषणा PORT_STATUS_FULL_DUPLEX		0x0200
#घोषणा PORT_REMOTE_FAULT		0x0100
#घोषणा PORT_MDIX_STATUS		0x0080
#घोषणा PORT_AUTO_NEG_COMPLETE		0x0040
#घोषणा PORT_STATUS_LINK_GOOD		0x0020
#घोषणा PORT_REMOTE_SYM_PAUSE		0x0010
#घोषणा PORT_REMOTE_100BTX_FD		0x0008
#घोषणा PORT_REMOTE_100BTX		0x0004
#घोषणा PORT_REMOTE_10BT_FD		0x0002
#घोषणा PORT_REMOTE_10BT		0x0001

/*
#घोषणा STATIC_MAC_TABLE_ADDR		00-0000FFFF-FFFFFFFF
#घोषणा STATIC_MAC_TABLE_FWD_PORTS	00-00070000-00000000
#घोषणा STATIC_MAC_TABLE_VALID		00-00080000-00000000
#घोषणा STATIC_MAC_TABLE_OVERRIDE	00-00100000-00000000
#घोषणा STATIC_MAC_TABLE_USE_FID	00-00200000-00000000
#घोषणा STATIC_MAC_TABLE_FID		00-03C00000-00000000
*/

#घोषणा STATIC_MAC_TABLE_ADDR		0x0000FFFF
#घोषणा STATIC_MAC_TABLE_FWD_PORTS	0x00070000
#घोषणा STATIC_MAC_TABLE_VALID		0x00080000
#घोषणा STATIC_MAC_TABLE_OVERRIDE	0x00100000
#घोषणा STATIC_MAC_TABLE_USE_FID	0x00200000
#घोषणा STATIC_MAC_TABLE_FID		0x03C00000

#घोषणा STATIC_MAC_FWD_PORTS_SHIFT	16
#घोषणा STATIC_MAC_FID_SHIFT		22

/*
#घोषणा VLAN_TABLE_VID			00-00000000-00000FFF
#घोषणा VLAN_TABLE_FID			00-00000000-0000F000
#घोषणा VLAN_TABLE_MEMBERSHIP		00-00000000-00070000
#घोषणा VLAN_TABLE_VALID		00-00000000-00080000
*/

#घोषणा VLAN_TABLE_VID			0x00000FFF
#घोषणा VLAN_TABLE_FID			0x0000F000
#घोषणा VLAN_TABLE_MEMBERSHIP		0x00070000
#घोषणा VLAN_TABLE_VALID		0x00080000

#घोषणा VLAN_TABLE_FID_SHIFT		12
#घोषणा VLAN_TABLE_MEMBERSHIP_SHIFT	16

/*
#घोषणा DYNAMIC_MAC_TABLE_ADDR		00-0000FFFF-FFFFFFFF
#घोषणा DYNAMIC_MAC_TABLE_FID		00-000F0000-00000000
#घोषणा DYNAMIC_MAC_TABLE_SRC_PORT	00-00300000-00000000
#घोषणा DYNAMIC_MAC_TABLE_TIMESTAMP	00-00C00000-00000000
#घोषणा DYNAMIC_MAC_TABLE_ENTRIES	03-FF000000-00000000
#घोषणा DYNAMIC_MAC_TABLE_MAC_EMPTY	04-00000000-00000000
#घोषणा DYNAMIC_MAC_TABLE_RESERVED	78-00000000-00000000
#घोषणा DYNAMIC_MAC_TABLE_NOT_READY	80-00000000-00000000
*/

#घोषणा DYNAMIC_MAC_TABLE_ADDR		0x0000FFFF
#घोषणा DYNAMIC_MAC_TABLE_FID		0x000F0000
#घोषणा DYNAMIC_MAC_TABLE_SRC_PORT	0x00300000
#घोषणा DYNAMIC_MAC_TABLE_TIMESTAMP	0x00C00000
#घोषणा DYNAMIC_MAC_TABLE_ENTRIES	0xFF000000

#घोषणा DYNAMIC_MAC_TABLE_ENTRIES_H	0x03
#घोषणा DYNAMIC_MAC_TABLE_MAC_EMPTY	0x04
#घोषणा DYNAMIC_MAC_TABLE_RESERVED	0x78
#घोषणा DYNAMIC_MAC_TABLE_NOT_READY	0x80

#घोषणा DYNAMIC_MAC_FID_SHIFT		16
#घोषणा DYNAMIC_MAC_SRC_PORT_SHIFT	20
#घोषणा DYNAMIC_MAC_TIMESTAMP_SHIFT	22
#घोषणा DYNAMIC_MAC_ENTRIES_SHIFT	24
#घोषणा DYNAMIC_MAC_ENTRIES_H_SHIFT	8

/*
#घोषणा MIB_COUNTER_VALUE		00-00000000-3FFFFFFF
#घोषणा MIB_COUNTER_VALID		00-00000000-40000000
#घोषणा MIB_COUNTER_OVERFLOW		00-00000000-80000000
*/

#घोषणा MIB_COUNTER_VALUE		0x3FFFFFFF
#घोषणा MIB_COUNTER_VALID		0x40000000
#घोषणा MIB_COUNTER_OVERFLOW		0x80000000

#घोषणा MIB_PACKET_DROPPED		0x0000FFFF

#घोषणा KS_MIB_PACKET_DROPPED_TX_0	0x100
#घोषणा KS_MIB_PACKET_DROPPED_TX_1	0x101
#घोषणा KS_MIB_PACKET_DROPPED_TX	0x102
#घोषणा KS_MIB_PACKET_DROPPED_RX_0	0x103
#घोषणा KS_MIB_PACKET_DROPPED_RX_1	0x104
#घोषणा KS_MIB_PACKET_DROPPED_RX	0x105

/* Change शेष LED mode. */
#घोषणा SET_DEFAULT_LED			LED_SPEED_DUPLEX_ACT

#घोषणा MAC_ADDR_ORDER(i)		(ETH_ALEN - 1 - (i))

#घोषणा MAX_ETHERNET_BODY_SIZE		1500
#घोषणा ETHERNET_HEADER_SIZE		(14 + VLAN_HLEN)

#घोषणा MAX_ETHERNET_PACKET_SIZE	\
	(MAX_ETHERNET_BODY_SIZE + ETHERNET_HEADER_SIZE)

#घोषणा REGULAR_RX_BUF_SIZE		(MAX_ETHERNET_PACKET_SIZE + 4)
#घोषणा MAX_RX_BUF_SIZE			(1912 + 4)

#घोषणा ADDITIONAL_ENTRIES		16
#घोषणा MAX_MULTICAST_LIST		32

#घोषणा HW_MULTICAST_SIZE		8

#घोषणा HW_TO_DEV_PORT(port)		(port - 1)

क्रमागत अणु
	media_connected,
	media_disconnected
पूर्ण;

क्रमागत अणु
	OID_COUNTER_UNKOWN,

	OID_COUNTER_FIRST,

	/* total transmit errors */
	OID_COUNTER_XMIT_ERROR,

	/* total receive errors */
	OID_COUNTER_RCV_ERROR,

	OID_COUNTER_LAST
पूर्ण;

/*
 * Hardware descriptor definitions
 */

#घोषणा DESC_ALIGNMENT			16
#घोषणा BUFFER_ALIGNMENT		8

#घोषणा NUM_OF_RX_DESC			64
#घोषणा NUM_OF_TX_DESC			64

#घोषणा KS_DESC_RX_FRAME_LEN		0x000007FF
#घोषणा KS_DESC_RX_FRAME_TYPE		0x00008000
#घोषणा KS_DESC_RX_ERROR_CRC		0x00010000
#घोषणा KS_DESC_RX_ERROR_RUNT		0x00020000
#घोषणा KS_DESC_RX_ERROR_TOO_LONG	0x00040000
#घोषणा KS_DESC_RX_ERROR_PHY		0x00080000
#घोषणा KS884X_DESC_RX_PORT_MASK	0x00300000
#घोषणा KS_DESC_RX_MULTICAST		0x01000000
#घोषणा KS_DESC_RX_ERROR		0x02000000
#घोषणा KS_DESC_RX_ERROR_CSUM_UDP	0x04000000
#घोषणा KS_DESC_RX_ERROR_CSUM_TCP	0x08000000
#घोषणा KS_DESC_RX_ERROR_CSUM_IP	0x10000000
#घोषणा KS_DESC_RX_LAST			0x20000000
#घोषणा KS_DESC_RX_FIRST		0x40000000
#घोषणा KS_DESC_RX_ERROR_COND		\
	(KS_DESC_RX_ERROR_CRC |		\
	KS_DESC_RX_ERROR_RUNT |		\
	KS_DESC_RX_ERROR_PHY |		\
	KS_DESC_RX_ERROR_TOO_LONG)

#घोषणा KS_DESC_HW_OWNED		0x80000000

#घोषणा KS_DESC_BUF_SIZE		0x000007FF
#घोषणा KS884X_DESC_TX_PORT_MASK	0x00300000
#घोषणा KS_DESC_END_OF_RING		0x02000000
#घोषणा KS_DESC_TX_CSUM_GEN_UDP		0x04000000
#घोषणा KS_DESC_TX_CSUM_GEN_TCP		0x08000000
#घोषणा KS_DESC_TX_CSUM_GEN_IP		0x10000000
#घोषणा KS_DESC_TX_LAST			0x20000000
#घोषणा KS_DESC_TX_FIRST		0x40000000
#घोषणा KS_DESC_TX_INTERRUPT		0x80000000

#घोषणा KS_DESC_PORT_SHIFT		20

#घोषणा KS_DESC_RX_MASK			(KS_DESC_BUF_SIZE)

#घोषणा KS_DESC_TX_MASK			\
	(KS_DESC_TX_INTERRUPT |		\
	KS_DESC_TX_FIRST |		\
	KS_DESC_TX_LAST |		\
	KS_DESC_TX_CSUM_GEN_IP |	\
	KS_DESC_TX_CSUM_GEN_TCP |	\
	KS_DESC_TX_CSUM_GEN_UDP |	\
	KS_DESC_BUF_SIZE)

काष्ठा ksz_desc_rx_stat अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
	u32 hw_owned:1;
	u32 first_desc:1;
	u32 last_desc:1;
	u32 csum_err_ip:1;
	u32 csum_err_tcp:1;
	u32 csum_err_udp:1;
	u32 error:1;
	u32 multicast:1;
	u32 src_port:4;
	u32 err_phy:1;
	u32 err_too_दीर्घ:1;
	u32 err_runt:1;
	u32 err_crc:1;
	u32 frame_type:1;
	u32 reserved1:4;
	u32 frame_len:11;
#अन्यथा
	u32 frame_len:11;
	u32 reserved1:4;
	u32 frame_type:1;
	u32 err_crc:1;
	u32 err_runt:1;
	u32 err_too_दीर्घ:1;
	u32 err_phy:1;
	u32 src_port:4;
	u32 multicast:1;
	u32 error:1;
	u32 csum_err_udp:1;
	u32 csum_err_tcp:1;
	u32 csum_err_ip:1;
	u32 last_desc:1;
	u32 first_desc:1;
	u32 hw_owned:1;
#पूर्ण_अगर
पूर्ण;

काष्ठा ksz_desc_tx_stat अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
	u32 hw_owned:1;
	u32 reserved1:31;
#अन्यथा
	u32 reserved1:31;
	u32 hw_owned:1;
#पूर्ण_अगर
पूर्ण;

काष्ठा ksz_desc_rx_buf अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
	u32 reserved4:6;
	u32 end_of_ring:1;
	u32 reserved3:14;
	u32 buf_size:11;
#अन्यथा
	u32 buf_size:11;
	u32 reserved3:14;
	u32 end_of_ring:1;
	u32 reserved4:6;
#पूर्ण_अगर
पूर्ण;

काष्ठा ksz_desc_tx_buf अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
	u32 पूर्णांकr:1;
	u32 first_seg:1;
	u32 last_seg:1;
	u32 csum_gen_ip:1;
	u32 csum_gen_tcp:1;
	u32 csum_gen_udp:1;
	u32 end_of_ring:1;
	u32 reserved4:1;
	u32 dest_port:4;
	u32 reserved3:9;
	u32 buf_size:11;
#अन्यथा
	u32 buf_size:11;
	u32 reserved3:9;
	u32 dest_port:4;
	u32 reserved4:1;
	u32 end_of_ring:1;
	u32 csum_gen_udp:1;
	u32 csum_gen_tcp:1;
	u32 csum_gen_ip:1;
	u32 last_seg:1;
	u32 first_seg:1;
	u32 पूर्णांकr:1;
#पूर्ण_अगर
पूर्ण;

जोड़ desc_stat अणु
	काष्ठा ksz_desc_rx_stat rx;
	काष्ठा ksz_desc_tx_stat tx;
	u32 data;
पूर्ण;

जोड़ desc_buf अणु
	काष्ठा ksz_desc_rx_buf rx;
	काष्ठा ksz_desc_tx_buf tx;
	u32 data;
पूर्ण;

/**
 * काष्ठा ksz_hw_desc - Hardware descriptor data काष्ठाure
 * @ctrl:	Descriptor control value.
 * @buf:	Descriptor buffer value.
 * @addr:	Physical address of memory buffer.
 * @next:	Poपूर्णांकer to next hardware descriptor.
 */
काष्ठा ksz_hw_desc अणु
	जोड़ desc_stat ctrl;
	जोड़ desc_buf buf;
	u32 addr;
	u32 next;
पूर्ण;

/**
 * काष्ठा ksz_sw_desc - Software descriptor data काष्ठाure
 * @ctrl:	Descriptor control value.
 * @buf:	Descriptor buffer value.
 * @buf_size:	Current buffers size value in hardware descriptor.
 */
काष्ठा ksz_sw_desc अणु
	जोड़ desc_stat ctrl;
	जोड़ desc_buf buf;
	u32 buf_size;
पूर्ण;

/**
 * काष्ठा ksz_dma_buf - OS dependent DMA buffer data काष्ठाure
 * @skb:	Associated socket buffer.
 * @dma:	Associated physical DMA address.
 * @len:	Actual len used.
 */
काष्ठा ksz_dma_buf अणु
	काष्ठा sk_buff *skb;
	dma_addr_t dma;
	पूर्णांक len;
पूर्ण;

/**
 * काष्ठा ksz_desc - Descriptor काष्ठाure
 * @phw:	Hardware descriptor poपूर्णांकer to uncached physical memory.
 * @sw:		Cached memory to hold hardware descriptor values क्रम
 * 		manipulation.
 * @dma_buf:	Operating प्रणाली dependent data काष्ठाure to hold physical
 * 		memory buffer allocation inक्रमmation.
 */
काष्ठा ksz_desc अणु
	काष्ठा ksz_hw_desc *phw;
	काष्ठा ksz_sw_desc sw;
	काष्ठा ksz_dma_buf dma_buf;
पूर्ण;

#घोषणा DMA_BUFFER(desc)  ((काष्ठा ksz_dma_buf *)(&(desc)->dma_buf))

/**
 * काष्ठा ksz_desc_info - Descriptor inक्रमmation data काष्ठाure
 * @ring:	First descriptor in the ring.
 * @cur:	Current descriptor being manipulated.
 * @ring_virt:	First hardware descriptor in the ring.
 * @ring_phys:	The physical address of the first descriptor of the ring.
 * @size:	Size of hardware descriptor.
 * @alloc:	Number of descriptors allocated.
 * @avail:	Number of descriptors available क्रम use.
 * @last:	Index क्रम last descriptor released to hardware.
 * @next:	Index क्रम next descriptor available क्रम use.
 * @mask:	Mask क्रम index wrapping.
 */
काष्ठा ksz_desc_info अणु
	काष्ठा ksz_desc *ring;
	काष्ठा ksz_desc *cur;
	काष्ठा ksz_hw_desc *ring_virt;
	u32 ring_phys;
	पूर्णांक size;
	पूर्णांक alloc;
	पूर्णांक avail;
	पूर्णांक last;
	पूर्णांक next;
	पूर्णांक mask;
पूर्ण;

/*
 * KSZ8842 चयन definitions
 */

क्रमागत अणु
	TABLE_STATIC_MAC = 0,
	TABLE_VLAN,
	TABLE_DYNAMIC_MAC,
	TABLE_MIB
पूर्ण;

#घोषणा LEARNED_MAC_TABLE_ENTRIES	1024
#घोषणा STATIC_MAC_TABLE_ENTRIES	8

/**
 * काष्ठा ksz_mac_table - Static MAC table data काष्ठाure
 * @mac_addr:	MAC address to filter.
 * @vid:	VID value.
 * @fid:	FID value.
 * @ports:	Port membership.
 * @override:	Override setting.
 * @use_fid:	FID use setting.
 * @valid:	Valid setting indicating the entry is being used.
 */
काष्ठा ksz_mac_table अणु
	u8 mac_addr[ETH_ALEN];
	u16 vid;
	u8 fid;
	u8 ports;
	u8 override:1;
	u8 use_fid:1;
	u8 valid:1;
पूर्ण;

#घोषणा VLAN_TABLE_ENTRIES		16

/**
 * काष्ठा ksz_vlan_table - VLAN table data काष्ठाure
 * @vid:	VID value.
 * @fid:	FID value.
 * @member:	Port membership.
 */
काष्ठा ksz_vlan_table अणु
	u16 vid;
	u8 fid;
	u8 member;
पूर्ण;

#घोषणा DIFFSERV_ENTRIES		64
#घोषणा PRIO_802_1P_ENTRIES		8
#घोषणा PRIO_QUEUES			4

#घोषणा SWITCH_PORT_NUM			2
#घोषणा TOTAL_PORT_NUM			(SWITCH_PORT_NUM + 1)
#घोषणा HOST_MASK			(1 << SWITCH_PORT_NUM)
#घोषणा PORT_MASK			7

#घोषणा MAIN_PORT			0
#घोषणा OTHER_PORT			1
#घोषणा HOST_PORT			SWITCH_PORT_NUM

#घोषणा PORT_COUNTER_NUM		0x20
#घोषणा TOTAL_PORT_COUNTER_NUM		(PORT_COUNTER_NUM + 2)

#घोषणा MIB_COUNTER_RX_LO_PRIORITY	0x00
#घोषणा MIB_COUNTER_RX_HI_PRIORITY	0x01
#घोषणा MIB_COUNTER_RX_UNDERSIZE	0x02
#घोषणा MIB_COUNTER_RX_FRAGMENT		0x03
#घोषणा MIB_COUNTER_RX_OVERSIZE		0x04
#घोषणा MIB_COUNTER_RX_JABBER		0x05
#घोषणा MIB_COUNTER_RX_SYMBOL_ERR	0x06
#घोषणा MIB_COUNTER_RX_CRC_ERR		0x07
#घोषणा MIB_COUNTER_RX_ALIGNMENT_ERR	0x08
#घोषणा MIB_COUNTER_RX_CTRL_8808	0x09
#घोषणा MIB_COUNTER_RX_PAUSE		0x0A
#घोषणा MIB_COUNTER_RX_BROADCAST	0x0B
#घोषणा MIB_COUNTER_RX_MULTICAST	0x0C
#घोषणा MIB_COUNTER_RX_UNICAST		0x0D
#घोषणा MIB_COUNTER_RX_OCTET_64		0x0E
#घोषणा MIB_COUNTER_RX_OCTET_65_127	0x0F
#घोषणा MIB_COUNTER_RX_OCTET_128_255	0x10
#घोषणा MIB_COUNTER_RX_OCTET_256_511	0x11
#घोषणा MIB_COUNTER_RX_OCTET_512_1023	0x12
#घोषणा MIB_COUNTER_RX_OCTET_1024_1522	0x13
#घोषणा MIB_COUNTER_TX_LO_PRIORITY	0x14
#घोषणा MIB_COUNTER_TX_HI_PRIORITY	0x15
#घोषणा MIB_COUNTER_TX_LATE_COLLISION	0x16
#घोषणा MIB_COUNTER_TX_PAUSE		0x17
#घोषणा MIB_COUNTER_TX_BROADCAST	0x18
#घोषणा MIB_COUNTER_TX_MULTICAST	0x19
#घोषणा MIB_COUNTER_TX_UNICAST		0x1A
#घोषणा MIB_COUNTER_TX_DEFERRED		0x1B
#घोषणा MIB_COUNTER_TX_TOTAL_COLLISION	0x1C
#घोषणा MIB_COUNTER_TX_EXCESS_COLLISION	0x1D
#घोषणा MIB_COUNTER_TX_SINGLE_COLLISION	0x1E
#घोषणा MIB_COUNTER_TX_MULTI_COLLISION	0x1F

#घोषणा MIB_COUNTER_RX_DROPPED_PACKET	0x20
#घोषणा MIB_COUNTER_TX_DROPPED_PACKET	0x21

/**
 * काष्ठा ksz_port_mib - Port MIB data काष्ठाure
 * @cnt_ptr:	Current poपूर्णांकer to MIB counter index.
 * @link_करोwn:	Indication the link has just gone करोwn.
 * @state:	Connection status of the port.
 * @mib_start:	The starting counter index.  Some ports करो not start at 0.
 * @counter:	64-bit MIB counter value.
 * @dropped:	Temporary buffer to remember last पढ़ो packet dropped values.
 *
 * MIB counters needs to be पढ़ो periodically so that counters करो not get
 * overflowed and give incorrect values.  A right balance is needed to
 * satisfy this condition and not waste too much CPU समय.
 *
 * It is poपूर्णांकless to पढ़ो MIB counters when the port is disconnected.  The
 * @state provides the connection status so that MIB counters are पढ़ो only
 * when the port is connected.  The @link_करोwn indicates the port is just
 * disconnected so that all MIB counters are पढ़ो one last समय to update the
 * inक्रमmation.
 */
काष्ठा ksz_port_mib अणु
	u8 cnt_ptr;
	u8 link_करोwn;
	u8 state;
	u8 mib_start;

	u64 counter[TOTAL_PORT_COUNTER_NUM];
	u32 dropped[2];
पूर्ण;

/**
 * काष्ठा ksz_port_cfg - Port configuration data काष्ठाure
 * @vid:	VID value.
 * @member:	Port membership.
 * @port_prio:	Port priority.
 * @rx_rate:	Receive priority rate.
 * @tx_rate:	Transmit priority rate.
 * @stp_state:	Current Spanning Tree Protocol state.
 */
काष्ठा ksz_port_cfg अणु
	u16 vid;
	u8 member;
	u8 port_prio;
	u32 rx_rate[PRIO_QUEUES];
	u32 tx_rate[PRIO_QUEUES];
	पूर्णांक stp_state;
पूर्ण;

/**
 * काष्ठा ksz_चयन - KSZ8842 चयन data काष्ठाure
 * @mac_table:	MAC table entries inक्रमmation.
 * @vlan_table:	VLAN table entries inक्रमmation.
 * @port_cfg:	Port configuration inक्रमmation.
 * @dअगरfserv:	DअगरfServ priority settings.  Possible values from 6-bit of ToS
 * 		(bit7 ~ bit2) field.
 * @p_802_1p:	802.1P priority settings.  Possible values from 3-bit of 802.1p
 * 		Tag priority field.
 * @br_addr:	Bridge address.  Used क्रम STP.
 * @other_addr:	Other MAC address.  Used क्रम multiple network device mode.
 * @broad_per:	Broadcast storm percentage.
 * @member:	Current port membership.  Used क्रम STP.
 */
काष्ठा ksz_चयन अणु
	काष्ठा ksz_mac_table mac_table[STATIC_MAC_TABLE_ENTRIES];
	काष्ठा ksz_vlan_table vlan_table[VLAN_TABLE_ENTRIES];
	काष्ठा ksz_port_cfg port_cfg[TOTAL_PORT_NUM];

	u8 dअगरfserv[DIFFSERV_ENTRIES];
	u8 p_802_1p[PRIO_802_1P_ENTRIES];

	u8 br_addr[ETH_ALEN];
	u8 other_addr[ETH_ALEN];

	u8 broad_per;
	u8 member;
पूर्ण;

#घोषणा TX_RATE_UNIT			10000

/**
 * काष्ठा ksz_port_info - Port inक्रमmation data काष्ठाure
 * @state:	Connection status of the port.
 * @tx_rate:	Transmit rate भागided by 10000 to get Mbit.
 * @duplex:	Duplex mode.
 * @advertised:	Advertised स्वतः-negotiation setting.  Used to determine link.
 * @partner:	Auto-negotiation partner setting.  Used to determine link.
 * @port_id:	Port index to access actual hardware रेजिस्टर.
 * @pdev:	Poपूर्णांकer to OS dependent network device.
 */
काष्ठा ksz_port_info अणु
	uपूर्णांक state;
	uपूर्णांक tx_rate;
	u8 duplex;
	u8 advertised;
	u8 partner;
	u8 port_id;
	व्योम *pdev;
पूर्ण;

#घोषणा MAX_TX_HELD_SIZE		52000

/* Hardware features and bug fixes. */
#घोषणा LINK_INT_WORKING		(1 << 0)
#घोषणा SMALL_PACKET_TX_BUG		(1 << 1)
#घोषणा HALF_DUPLEX_SIGNAL_BUG		(1 << 2)
#घोषणा RX_HUGE_FRAME			(1 << 4)
#घोषणा STP_SUPPORT			(1 << 8)

/* Software overrides. */
#घोषणा PAUSE_FLOW_CTRL			(1 << 0)
#घोषणा FAST_AGING			(1 << 1)

/**
 * काष्ठा ksz_hw - KSZ884X hardware data काष्ठाure
 * @io:			Virtual address asचिन्हित.
 * @ksz_चयन:		Poपूर्णांकer to KSZ8842 चयन.
 * @port_info:		Port inक्रमmation.
 * @port_mib:		Port MIB inक्रमmation.
 * @dev_count:		Number of network devices this hardware supports.
 * @dst_ports:		Destination ports in चयन क्रम transmission.
 * @id:			Hardware ID.  Used क्रम display only.
 * @mib_cnt:		Number of MIB counters this hardware has.
 * @mib_port_cnt:	Number of ports with MIB counters.
 * @tx_cfg:		Cached transmit control settings.
 * @rx_cfg:		Cached receive control settings.
 * @पूर्णांकr_mask:		Current पूर्णांकerrupt mask.
 * @पूर्णांकr_set:		Current पूर्णांकerrup set.
 * @पूर्णांकr_blocked:	Interrupt blocked.
 * @rx_desc_info:	Receive descriptor inक्रमmation.
 * @tx_desc_info:	Transmit descriptor inक्रमmation.
 * @tx_पूर्णांक_cnt:		Transmit पूर्णांकerrupt count.  Used क्रम TX optimization.
 * @tx_पूर्णांक_mask:	Transmit पूर्णांकerrupt mask.  Used क्रम TX optimization.
 * @tx_size:		Transmit data size.  Used क्रम TX optimization.
 * 			The maximum is defined by MAX_TX_HELD_SIZE.
 * @perm_addr:		Permanent MAC address.
 * @override_addr:	Overridden MAC address.
 * @address:		Additional MAC address entries.
 * @addr_list_size:	Additional MAC address list size.
 * @mac_override:	Indication of MAC address overridden.
 * @promiscuous:	Counter to keep track of promiscuous mode set.
 * @all_multi:		Counter to keep track of all multicast mode set.
 * @multi_list:		Multicast address entries.
 * @multi_bits:		Cached multicast hash table settings.
 * @multi_list_size:	Multicast address list size.
 * @enabled:		Indication of hardware enabled.
 * @rx_stop:		Indication of receive process stop.
 * @reserved2:		none
 * @features:		Hardware features to enable.
 * @overrides:		Hardware features to override.
 * @parent:		Poपूर्णांकer to parent, network device निजी काष्ठाure.
 */
काष्ठा ksz_hw अणु
	व्योम __iomem *io;

	काष्ठा ksz_चयन *ksz_चयन;
	काष्ठा ksz_port_info port_info[SWITCH_PORT_NUM];
	काष्ठा ksz_port_mib port_mib[TOTAL_PORT_NUM];
	पूर्णांक dev_count;
	पूर्णांक dst_ports;
	पूर्णांक id;
	पूर्णांक mib_cnt;
	पूर्णांक mib_port_cnt;

	u32 tx_cfg;
	u32 rx_cfg;
	u32 पूर्णांकr_mask;
	u32 पूर्णांकr_set;
	uपूर्णांक पूर्णांकr_blocked;

	काष्ठा ksz_desc_info rx_desc_info;
	काष्ठा ksz_desc_info tx_desc_info;

	पूर्णांक tx_पूर्णांक_cnt;
	पूर्णांक tx_पूर्णांक_mask;
	पूर्णांक tx_size;

	u8 perm_addr[ETH_ALEN];
	u8 override_addr[ETH_ALEN];
	u8 address[ADDITIONAL_ENTRIES][ETH_ALEN];
	u8 addr_list_size;
	u8 mac_override;
	u8 promiscuous;
	u8 all_multi;
	u8 multi_list[MAX_MULTICAST_LIST][ETH_ALEN];
	u8 multi_bits[HW_MULTICAST_SIZE];
	u8 multi_list_size;

	u8 enabled;
	u8 rx_stop;
	u8 reserved2[1];

	uपूर्णांक features;
	uपूर्णांक overrides;

	व्योम *parent;
पूर्ण;

क्रमागत अणु
	PHY_NO_FLOW_CTRL,
	PHY_FLOW_CTRL,
	PHY_TX_ONLY,
	PHY_RX_ONLY
पूर्ण;

/**
 * काष्ठा ksz_port - Virtual port data काष्ठाure
 * @duplex:		Duplex mode setting.  1 क्रम half duplex, 2 क्रम full
 * 			duplex, and 0 क्रम स्वतः, which normally results in full
 * 			duplex.
 * @speed:		Speed setting.  10 क्रम 10 Mbit, 100 क्रम 100 Mbit, and
 * 			0 क्रम स्वतः, which normally results in 100 Mbit.
 * @क्रमce_link:		Force link setting.  0 क्रम स्वतः-negotiation, and 1 क्रम
 * 			क्रमce.
 * @flow_ctrl:		Flow control setting.  PHY_NO_FLOW_CTRL क्रम no flow
 * 			control, and PHY_FLOW_CTRL क्रम flow control.
 * 			PHY_TX_ONLY and PHY_RX_ONLY are not supported क्रम 100
 * 			Mbit PHY.
 * @first_port:		Index of first port this port supports.
 * @mib_port_cnt:	Number of ports with MIB counters.
 * @port_cnt:		Number of ports this port supports.
 * @counter:		Port statistics counter.
 * @hw:			Poपूर्णांकer to hardware काष्ठाure.
 * @linked:		Poपूर्णांकer to port inक्रमmation linked to this port.
 */
काष्ठा ksz_port अणु
	u8 duplex;
	u8 speed;
	u8 क्रमce_link;
	u8 flow_ctrl;

	पूर्णांक first_port;
	पूर्णांक mib_port_cnt;
	पूर्णांक port_cnt;
	u64 counter[OID_COUNTER_LAST];

	काष्ठा ksz_hw *hw;
	काष्ठा ksz_port_info *linked;
पूर्ण;

/**
 * काष्ठा ksz_समयr_info - Timer inक्रमmation data काष्ठाure
 * @समयr:	Kernel समयr.
 * @cnt:	Running समयr counter.
 * @max:	Number of बार to run समयr; -1 क्रम infinity.
 * @period:	Timer period in jअगरfies.
 */
काष्ठा ksz_समयr_info अणु
	काष्ठा समयr_list समयr;
	पूर्णांक cnt;
	पूर्णांक max;
	पूर्णांक period;
पूर्ण;

/**
 * काष्ठा ksz_shared_mem - OS dependent shared memory data काष्ठाure
 * @dma_addr:	Physical DMA address allocated.
 * @alloc_size:	Allocation size.
 * @phys:	Actual physical address used.
 * @alloc_virt:	Virtual address allocated.
 * @virt:	Actual भव address used.
 */
काष्ठा ksz_shared_mem अणु
	dma_addr_t dma_addr;
	uपूर्णांक alloc_size;
	uपूर्णांक phys;
	u8 *alloc_virt;
	u8 *virt;
पूर्ण;

/**
 * काष्ठा ksz_counter_info - OS dependent counter inक्रमmation data काष्ठाure
 * @counter:	Wait queue to wakeup after counters are पढ़ो.
 * @समय:	Next समय in jअगरfies to पढ़ो counter.
 * @पढ़ो:	Indication of counters पढ़ो in full or not.
 */
काष्ठा ksz_counter_info अणु
	रुको_queue_head_t counter;
	अचिन्हित दीर्घ समय;
	पूर्णांक पढ़ो;
पूर्ण;

/**
 * काष्ठा dev_info - Network device inक्रमmation data काष्ठाure
 * @dev:		Poपूर्णांकer to network device.
 * @pdev:		Poपूर्णांकer to PCI device.
 * @hw:			Hardware काष्ठाure.
 * @desc_pool:		Physical memory used क्रम descriptor pool.
 * @hwlock:		Spinlock to prevent hardware from accessing.
 * @lock:		Mutex lock to prevent device from accessing.
 * @dev_rcv:		Receive process function used.
 * @last_skb:		Socket buffer allocated क्रम descriptor rx fragments.
 * @skb_index:		Buffer index क्रम receiving fragments.
 * @skb_len:		Buffer length क्रम receiving fragments.
 * @mib_पढ़ो:		Workqueue to पढ़ो MIB counters.
 * @mib_समयr_info:	Timer to पढ़ो MIB counters.
 * @counter:		Used क्रम MIB पढ़ोing.
 * @mtu:		Current MTU used.  The शेष is REGULAR_RX_BUF_SIZE;
 * 			the maximum is MAX_RX_BUF_SIZE.
 * @खोलोed:		Counter to keep track of device खोलो.
 * @rx_tasklet:		Receive processing tasklet.
 * @tx_tasklet:		Transmit processing tasklet.
 * @wol_enable:		Wake-on-LAN enable set by ethtool.
 * @wol_support:	Wake-on-LAN support used by ethtool.
 * @pme_रुको:		Used क्रम KSZ8841 घातer management.
 */
काष्ठा dev_info अणु
	काष्ठा net_device *dev;
	काष्ठा pci_dev *pdev;

	काष्ठा ksz_hw hw;
	काष्ठा ksz_shared_mem desc_pool;

	spinlock_t hwlock;
	काष्ठा mutex lock;

	पूर्णांक (*dev_rcv)(काष्ठा dev_info *);

	काष्ठा sk_buff *last_skb;
	पूर्णांक skb_index;
	पूर्णांक skb_len;

	काष्ठा work_काष्ठा mib_पढ़ो;
	काष्ठा ksz_समयr_info mib_समयr_info;
	काष्ठा ksz_counter_info counter[TOTAL_PORT_NUM];

	पूर्णांक mtu;
	पूर्णांक खोलोed;

	काष्ठा tasklet_काष्ठा rx_tasklet;
	काष्ठा tasklet_काष्ठा tx_tasklet;

	पूर्णांक wol_enable;
	पूर्णांक wol_support;
	अचिन्हित दीर्घ pme_रुको;
पूर्ण;

/**
 * काष्ठा dev_priv - Network device निजी data काष्ठाure
 * @adapter:		Adapter device inक्रमmation.
 * @port:		Port inक्रमmation.
 * @monitor_समयr_info:	Timer to monitor ports.
 * @proc_sem:		Semaphore क्रम proc accessing.
 * @id:			Device ID.
 * @mii_अगर:		MII पूर्णांकerface inक्रमmation.
 * @advertising:	Temporary variable to store advertised settings.
 * @msg_enable:		The message flags controlling driver output.
 * @media_state:	The connection status of the device.
 * @multicast:		The all multicast state of the device.
 * @promiscuous:	The promiscuous state of the device.
 */
काष्ठा dev_priv अणु
	काष्ठा dev_info *adapter;
	काष्ठा ksz_port port;
	काष्ठा ksz_समयr_info monitor_समयr_info;

	काष्ठा semaphore proc_sem;
	पूर्णांक id;

	काष्ठा mii_अगर_info mii_अगर;
	u32 advertising;

	u32 msg_enable;
	पूर्णांक media_state;
	पूर्णांक multicast;
	पूर्णांक promiscuous;
पूर्ण;

#घोषणा DRV_NAME		"KSZ884X PCI"
#घोषणा DEVICE_NAME		"KSZ884x PCI"
#घोषणा DRV_VERSION		"1.0.0"
#घोषणा DRV_RELDATE		"Feb 8, 2010"

अटल अक्षर version[] =
	"Micrel " DEVICE_NAME " " DRV_VERSION " (" DRV_RELDATE ")";

अटल u8 DEFAULT_MAC_ADDRESS[] = अणु 0x00, 0x10, 0xA1, 0x88, 0x42, 0x01 पूर्ण;

/*
 * Interrupt processing primary routines
 */

अटल अंतरभूत व्योम hw_ack_पूर्णांकr(काष्ठा ksz_hw *hw, uपूर्णांक पूर्णांकerrupt)
अणु
	ग_लिखोl(पूर्णांकerrupt, hw->io + KS884X_INTERRUPTS_STATUS);
पूर्ण

अटल अंतरभूत व्योम hw_dis_पूर्णांकr(काष्ठा ksz_hw *hw)
अणु
	hw->पूर्णांकr_blocked = hw->पूर्णांकr_mask;
	ग_लिखोl(0, hw->io + KS884X_INTERRUPTS_ENABLE);
	hw->पूर्णांकr_set = पढ़ोl(hw->io + KS884X_INTERRUPTS_ENABLE);
पूर्ण

अटल अंतरभूत व्योम hw_set_पूर्णांकr(काष्ठा ksz_hw *hw, uपूर्णांक पूर्णांकerrupt)
अणु
	hw->पूर्णांकr_set = पूर्णांकerrupt;
	ग_लिखोl(पूर्णांकerrupt, hw->io + KS884X_INTERRUPTS_ENABLE);
पूर्ण

अटल अंतरभूत व्योम hw_ena_पूर्णांकr(काष्ठा ksz_hw *hw)
अणु
	hw->पूर्णांकr_blocked = 0;
	hw_set_पूर्णांकr(hw, hw->पूर्णांकr_mask);
पूर्ण

अटल अंतरभूत व्योम hw_dis_पूर्णांकr_bit(काष्ठा ksz_hw *hw, uपूर्णांक bit)
अणु
	hw->पूर्णांकr_mask &= ~(bit);
पूर्ण

अटल अंतरभूत व्योम hw_turn_off_पूर्णांकr(काष्ठा ksz_hw *hw, uपूर्णांक पूर्णांकerrupt)
अणु
	u32 पढ़ो_पूर्णांकr;

	पढ़ो_पूर्णांकr = पढ़ोl(hw->io + KS884X_INTERRUPTS_ENABLE);
	hw->पूर्णांकr_set = पढ़ो_पूर्णांकr & ~पूर्णांकerrupt;
	ग_लिखोl(hw->पूर्णांकr_set, hw->io + KS884X_INTERRUPTS_ENABLE);
	hw_dis_पूर्णांकr_bit(hw, पूर्णांकerrupt);
पूर्ण

/**
 * hw_turn_on_पूर्णांकr - turn on specअगरied पूर्णांकerrupts
 * @hw: 	The hardware instance.
 * @bit:	The पूर्णांकerrupt bits to be on.
 *
 * This routine turns on the specअगरied पूर्णांकerrupts in the पूर्णांकerrupt mask so that
 * those पूर्णांकerrupts will be enabled.
 */
अटल व्योम hw_turn_on_पूर्णांकr(काष्ठा ksz_hw *hw, u32 bit)
अणु
	hw->पूर्णांकr_mask |= bit;

	अगर (!hw->पूर्णांकr_blocked)
		hw_set_पूर्णांकr(hw, hw->पूर्णांकr_mask);
पूर्ण

अटल अंतरभूत व्योम hw_ena_पूर्णांकr_bit(काष्ठा ksz_hw *hw, uपूर्णांक पूर्णांकerrupt)
अणु
	u32 पढ़ो_पूर्णांकr;

	पढ़ो_पूर्णांकr = पढ़ोl(hw->io + KS884X_INTERRUPTS_ENABLE);
	hw->पूर्णांकr_set = पढ़ो_पूर्णांकr | पूर्णांकerrupt;
	ग_लिखोl(hw->पूर्णांकr_set, hw->io + KS884X_INTERRUPTS_ENABLE);
पूर्ण

अटल अंतरभूत व्योम hw_पढ़ो_पूर्णांकr(काष्ठा ksz_hw *hw, uपूर्णांक *status)
अणु
	*status = पढ़ोl(hw->io + KS884X_INTERRUPTS_STATUS);
	*status = *status & hw->पूर्णांकr_set;
पूर्ण

अटल अंतरभूत व्योम hw_restore_पूर्णांकr(काष्ठा ksz_hw *hw, uपूर्णांक पूर्णांकerrupt)
अणु
	अगर (पूर्णांकerrupt)
		hw_ena_पूर्णांकr(hw);
पूर्ण

/**
 * hw_block_पूर्णांकr - block hardware पूर्णांकerrupts
 * @hw: The hardware instance.
 *
 * This function blocks all पूर्णांकerrupts of the hardware and वापसs the current
 * पूर्णांकerrupt enable mask so that पूर्णांकerrupts can be restored later.
 *
 * Return the current पूर्णांकerrupt enable mask.
 */
अटल uपूर्णांक hw_block_पूर्णांकr(काष्ठा ksz_hw *hw)
अणु
	uपूर्णांक पूर्णांकerrupt = 0;

	अगर (!hw->पूर्णांकr_blocked) अणु
		hw_dis_पूर्णांकr(hw);
		पूर्णांकerrupt = hw->पूर्णांकr_blocked;
	पूर्ण
	वापस पूर्णांकerrupt;
पूर्ण

/*
 * Hardware descriptor routines
 */

अटल अंतरभूत व्योम reset_desc(काष्ठा ksz_desc *desc, जोड़ desc_stat status)
अणु
	status.rx.hw_owned = 0;
	desc->phw->ctrl.data = cpu_to_le32(status.data);
पूर्ण

अटल अंतरभूत व्योम release_desc(काष्ठा ksz_desc *desc)
अणु
	desc->sw.ctrl.tx.hw_owned = 1;
	अगर (desc->sw.buf_size != desc->sw.buf.data) अणु
		desc->sw.buf_size = desc->sw.buf.data;
		desc->phw->buf.data = cpu_to_le32(desc->sw.buf.data);
	पूर्ण
	desc->phw->ctrl.data = cpu_to_le32(desc->sw.ctrl.data);
पूर्ण

अटल व्योम get_rx_pkt(काष्ठा ksz_desc_info *info, काष्ठा ksz_desc **desc)
अणु
	*desc = &info->ring[info->last];
	info->last++;
	info->last &= info->mask;
	info->avail--;
	(*desc)->sw.buf.data &= ~KS_DESC_RX_MASK;
पूर्ण

अटल अंतरभूत व्योम set_rx_buf(काष्ठा ksz_desc *desc, u32 addr)
अणु
	desc->phw->addr = cpu_to_le32(addr);
पूर्ण

अटल अंतरभूत व्योम set_rx_len(काष्ठा ksz_desc *desc, u32 len)
अणु
	desc->sw.buf.rx.buf_size = len;
पूर्ण

अटल अंतरभूत व्योम get_tx_pkt(काष्ठा ksz_desc_info *info,
	काष्ठा ksz_desc **desc)
अणु
	*desc = &info->ring[info->next];
	info->next++;
	info->next &= info->mask;
	info->avail--;
	(*desc)->sw.buf.data &= ~KS_DESC_TX_MASK;
पूर्ण

अटल अंतरभूत व्योम set_tx_buf(काष्ठा ksz_desc *desc, u32 addr)
अणु
	desc->phw->addr = cpu_to_le32(addr);
पूर्ण

अटल अंतरभूत व्योम set_tx_len(काष्ठा ksz_desc *desc, u32 len)
अणु
	desc->sw.buf.tx.buf_size = len;
पूर्ण

/* Switch functions */

#घोषणा TABLE_READ			0x10
#घोषणा TABLE_SEL_SHIFT			2

#घोषणा HW_DELAY(hw, reg)			\
	करो अणु					\
		पढ़ोw(hw->io + reg);		\
	पूर्ण जबतक (0)

/**
 * sw_r_table - पढ़ो 4 bytes of data from चयन table
 * @hw:		The hardware instance.
 * @table:	The table selector.
 * @addr:	The address of the table entry.
 * @data:	Buffer to store the पढ़ो data.
 *
 * This routine पढ़ोs 4 bytes of data from the table of the चयन.
 * Hardware पूर्णांकerrupts are disabled to minimize corruption of पढ़ो data.
 */
अटल व्योम sw_r_table(काष्ठा ksz_hw *hw, पूर्णांक table, u16 addr, u32 *data)
अणु
	u16 ctrl_addr;
	uपूर्णांक पूर्णांकerrupt;

	ctrl_addr = (((table << TABLE_SEL_SHIFT) | TABLE_READ) << 8) | addr;

	पूर्णांकerrupt = hw_block_पूर्णांकr(hw);

	ग_लिखोw(ctrl_addr, hw->io + KS884X_IACR_OFFSET);
	HW_DELAY(hw, KS884X_IACR_OFFSET);
	*data = पढ़ोl(hw->io + KS884X_ACC_DATA_0_OFFSET);

	hw_restore_पूर्णांकr(hw, पूर्णांकerrupt);
पूर्ण

/**
 * sw_w_table_64 - ग_लिखो 8 bytes of data to the चयन table
 * @hw:		The hardware instance.
 * @table:	The table selector.
 * @addr:	The address of the table entry.
 * @data_hi:	The high part of data to be written (bit63 ~ bit32).
 * @data_lo:	The low part of data to be written (bit31 ~ bit0).
 *
 * This routine ग_लिखोs 8 bytes of data to the table of the चयन.
 * Hardware पूर्णांकerrupts are disabled to minimize corruption of written data.
 */
अटल व्योम sw_w_table_64(काष्ठा ksz_hw *hw, पूर्णांक table, u16 addr, u32 data_hi,
	u32 data_lo)
अणु
	u16 ctrl_addr;
	uपूर्णांक पूर्णांकerrupt;

	ctrl_addr = ((table << TABLE_SEL_SHIFT) << 8) | addr;

	पूर्णांकerrupt = hw_block_पूर्णांकr(hw);

	ग_लिखोl(data_hi, hw->io + KS884X_ACC_DATA_4_OFFSET);
	ग_लिखोl(data_lo, hw->io + KS884X_ACC_DATA_0_OFFSET);

	ग_लिखोw(ctrl_addr, hw->io + KS884X_IACR_OFFSET);
	HW_DELAY(hw, KS884X_IACR_OFFSET);

	hw_restore_पूर्णांकr(hw, पूर्णांकerrupt);
पूर्ण

/**
 * sw_w_sta_mac_table - ग_लिखो to the अटल MAC table
 * @hw: 	The hardware instance.
 * @addr:	The address of the table entry.
 * @mac_addr:	The MAC address.
 * @ports:	The port members.
 * @override:	The flag to override the port receive/transmit settings.
 * @valid:	The flag to indicate entry is valid.
 * @use_fid:	The flag to indicate the FID is valid.
 * @fid:	The FID value.
 *
 * This routine ग_लिखोs an entry of the अटल MAC table of the चयन.  It
 * calls sw_w_table_64() to ग_लिखो the data.
 */
अटल व्योम sw_w_sta_mac_table(काष्ठा ksz_hw *hw, u16 addr, u8 *mac_addr,
	u8 ports, पूर्णांक override, पूर्णांक valid, पूर्णांक use_fid, u8 fid)
अणु
	u32 data_hi;
	u32 data_lo;

	data_lo = ((u32) mac_addr[2] << 24) |
		((u32) mac_addr[3] << 16) |
		((u32) mac_addr[4] << 8) | mac_addr[5];
	data_hi = ((u32) mac_addr[0] << 8) | mac_addr[1];
	data_hi |= (u32) ports << STATIC_MAC_FWD_PORTS_SHIFT;

	अगर (override)
		data_hi |= STATIC_MAC_TABLE_OVERRIDE;
	अगर (use_fid) अणु
		data_hi |= STATIC_MAC_TABLE_USE_FID;
		data_hi |= (u32) fid << STATIC_MAC_FID_SHIFT;
	पूर्ण
	अगर (valid)
		data_hi |= STATIC_MAC_TABLE_VALID;

	sw_w_table_64(hw, TABLE_STATIC_MAC, addr, data_hi, data_lo);
पूर्ण

/**
 * sw_r_vlan_table - पढ़ो from the VLAN table
 * @hw: 	The hardware instance.
 * @addr:	The address of the table entry.
 * @vid:	Buffer to store the VID.
 * @fid:	Buffer to store the VID.
 * @member:	Buffer to store the port membership.
 *
 * This function पढ़ोs an entry of the VLAN table of the चयन.  It calls
 * sw_r_table() to get the data.
 *
 * Return 0 अगर the entry is valid; otherwise -1.
 */
अटल पूर्णांक sw_r_vlan_table(काष्ठा ksz_hw *hw, u16 addr, u16 *vid, u8 *fid,
	u8 *member)
अणु
	u32 data;

	sw_r_table(hw, TABLE_VLAN, addr, &data);
	अगर (data & VLAN_TABLE_VALID) अणु
		*vid = (u16)(data & VLAN_TABLE_VID);
		*fid = (u8)((data & VLAN_TABLE_FID) >> VLAN_TABLE_FID_SHIFT);
		*member = (u8)((data & VLAN_TABLE_MEMBERSHIP) >>
			VLAN_TABLE_MEMBERSHIP_SHIFT);
		वापस 0;
	पूर्ण
	वापस -1;
पूर्ण

/**
 * port_r_mib_cnt - पढ़ो MIB counter
 * @hw: 	The hardware instance.
 * @port:	The port index.
 * @addr:	The address of the counter.
 * @cnt:	Buffer to store the counter.
 *
 * This routine पढ़ोs a MIB counter of the port.
 * Hardware पूर्णांकerrupts are disabled to minimize corruption of पढ़ो data.
 */
अटल व्योम port_r_mib_cnt(काष्ठा ksz_hw *hw, पूर्णांक port, u16 addr, u64 *cnt)
अणु
	u32 data;
	u16 ctrl_addr;
	uपूर्णांक पूर्णांकerrupt;
	पूर्णांक समयout;

	ctrl_addr = addr + PORT_COUNTER_NUM * port;

	पूर्णांकerrupt = hw_block_पूर्णांकr(hw);

	ctrl_addr |= (((TABLE_MIB << TABLE_SEL_SHIFT) | TABLE_READ) << 8);
	ग_लिखोw(ctrl_addr, hw->io + KS884X_IACR_OFFSET);
	HW_DELAY(hw, KS884X_IACR_OFFSET);

	क्रम (समयout = 100; समयout > 0; समयout--) अणु
		data = पढ़ोl(hw->io + KS884X_ACC_DATA_0_OFFSET);

		अगर (data & MIB_COUNTER_VALID) अणु
			अगर (data & MIB_COUNTER_OVERFLOW)
				*cnt += MIB_COUNTER_VALUE + 1;
			*cnt += data & MIB_COUNTER_VALUE;
			अवरोध;
		पूर्ण
	पूर्ण

	hw_restore_पूर्णांकr(hw, पूर्णांकerrupt);
पूर्ण

/**
 * port_r_mib_pkt - पढ़ो dropped packet counts
 * @hw: 	The hardware instance.
 * @port:	The port index.
 * @last:	last one
 * @cnt:	Buffer to store the receive and transmit dropped packet counts.
 *
 * This routine पढ़ोs the dropped packet counts of the port.
 * Hardware पूर्णांकerrupts are disabled to minimize corruption of पढ़ो data.
 */
अटल व्योम port_r_mib_pkt(काष्ठा ksz_hw *hw, पूर्णांक port, u32 *last, u64 *cnt)
अणु
	u32 cur;
	u32 data;
	u16 ctrl_addr;
	uपूर्णांक पूर्णांकerrupt;
	पूर्णांक index;

	index = KS_MIB_PACKET_DROPPED_RX_0 + port;
	करो अणु
		पूर्णांकerrupt = hw_block_पूर्णांकr(hw);

		ctrl_addr = (u16) index;
		ctrl_addr |= (((TABLE_MIB << TABLE_SEL_SHIFT) | TABLE_READ)
			<< 8);
		ग_लिखोw(ctrl_addr, hw->io + KS884X_IACR_OFFSET);
		HW_DELAY(hw, KS884X_IACR_OFFSET);
		data = पढ़ोl(hw->io + KS884X_ACC_DATA_0_OFFSET);

		hw_restore_पूर्णांकr(hw, पूर्णांकerrupt);

		data &= MIB_PACKET_DROPPED;
		cur = *last;
		अगर (data != cur) अणु
			*last = data;
			अगर (data < cur)
				data += MIB_PACKET_DROPPED + 1;
			data -= cur;
			*cnt += data;
		पूर्ण
		++last;
		++cnt;
		index -= KS_MIB_PACKET_DROPPED_TX -
			KS_MIB_PACKET_DROPPED_TX_0 + 1;
	पूर्ण जबतक (index >= KS_MIB_PACKET_DROPPED_TX_0 + port);
पूर्ण

/**
 * port_r_cnt - पढ़ो MIB counters periodically
 * @hw: 	The hardware instance.
 * @port:	The port index.
 *
 * This routine is used to पढ़ो the counters of the port periodically to aव्योम
 * counter overflow.  The hardware should be acquired first beक्रमe calling this
 * routine.
 *
 * Return non-zero when not all counters not पढ़ो.
 */
अटल पूर्णांक port_r_cnt(काष्ठा ksz_hw *hw, पूर्णांक port)
अणु
	काष्ठा ksz_port_mib *mib = &hw->port_mib[port];

	अगर (mib->mib_start < PORT_COUNTER_NUM)
		जबतक (mib->cnt_ptr < PORT_COUNTER_NUM) अणु
			port_r_mib_cnt(hw, port, mib->cnt_ptr,
				&mib->counter[mib->cnt_ptr]);
			++mib->cnt_ptr;
		पूर्ण
	अगर (hw->mib_cnt > PORT_COUNTER_NUM)
		port_r_mib_pkt(hw, port, mib->dropped,
			&mib->counter[PORT_COUNTER_NUM]);
	mib->cnt_ptr = 0;
	वापस 0;
पूर्ण

/**
 * port_init_cnt - initialize MIB counter values
 * @hw: 	The hardware instance.
 * @port:	The port index.
 *
 * This routine is used to initialize all counters to zero अगर the hardware
 * cannot करो it after reset.
 */
अटल व्योम port_init_cnt(काष्ठा ksz_hw *hw, पूर्णांक port)
अणु
	काष्ठा ksz_port_mib *mib = &hw->port_mib[port];

	mib->cnt_ptr = 0;
	अगर (mib->mib_start < PORT_COUNTER_NUM)
		करो अणु
			port_r_mib_cnt(hw, port, mib->cnt_ptr,
				&mib->counter[mib->cnt_ptr]);
			++mib->cnt_ptr;
		पूर्ण जबतक (mib->cnt_ptr < PORT_COUNTER_NUM);
	अगर (hw->mib_cnt > PORT_COUNTER_NUM)
		port_r_mib_pkt(hw, port, mib->dropped,
			&mib->counter[PORT_COUNTER_NUM]);
	स_रखो((व्योम *) mib->counter, 0, माप(u64) * TOTAL_PORT_COUNTER_NUM);
	mib->cnt_ptr = 0;
पूर्ण

/*
 * Port functions
 */

/**
 * port_chk - check port रेजिस्टर bits
 * @hw: 	The hardware instance.
 * @port:	The port index.
 * @offset:	The offset of the port रेजिस्टर.
 * @bits:	The data bits to check.
 *
 * This function checks whether the specअगरied bits of the port रेजिस्टर are set
 * or not.
 *
 * Return 0 अगर the bits are not set.
 */
अटल पूर्णांक port_chk(काष्ठा ksz_hw *hw, पूर्णांक port, पूर्णांक offset, u16 bits)
अणु
	u32 addr;
	u16 data;

	PORT_CTRL_ADDR(port, addr);
	addr += offset;
	data = पढ़ोw(hw->io + addr);
	वापस (data & bits) == bits;
पूर्ण

/**
 * port_cfg - set port रेजिस्टर bits
 * @hw: 	The hardware instance.
 * @port:	The port index.
 * @offset:	The offset of the port रेजिस्टर.
 * @bits:	The data bits to set.
 * @set:	The flag indicating whether the bits are to be set or not.
 *
 * This routine sets or resets the specअगरied bits of the port रेजिस्टर.
 */
अटल व्योम port_cfg(काष्ठा ksz_hw *hw, पूर्णांक port, पूर्णांक offset, u16 bits,
	पूर्णांक set)
अणु
	u32 addr;
	u16 data;

	PORT_CTRL_ADDR(port, addr);
	addr += offset;
	data = पढ़ोw(hw->io + addr);
	अगर (set)
		data |= bits;
	अन्यथा
		data &= ~bits;
	ग_लिखोw(data, hw->io + addr);
पूर्ण

/**
 * port_chk_shअगरt - check port bit
 * @hw: 	The hardware instance.
 * @port:	The port index.
 * @addr:	The offset of the रेजिस्टर.
 * @shअगरt:	Number of bits to shअगरt.
 *
 * This function checks whether the specअगरied port is set in the रेजिस्टर or
 * not.
 *
 * Return 0 अगर the port is not set.
 */
अटल पूर्णांक port_chk_shअगरt(काष्ठा ksz_hw *hw, पूर्णांक port, u32 addr, पूर्णांक shअगरt)
अणु
	u16 data;
	u16 bit = 1 << port;

	data = पढ़ोw(hw->io + addr);
	data >>= shअगरt;
	वापस (data & bit) == bit;
पूर्ण

/**
 * port_cfg_shअगरt - set port bit
 * @hw: 	The hardware instance.
 * @port:	The port index.
 * @addr:	The offset of the रेजिस्टर.
 * @shअगरt:	Number of bits to shअगरt.
 * @set:	The flag indicating whether the port is to be set or not.
 *
 * This routine sets or resets the specअगरied port in the रेजिस्टर.
 */
अटल व्योम port_cfg_shअगरt(काष्ठा ksz_hw *hw, पूर्णांक port, u32 addr, पूर्णांक shअगरt,
	पूर्णांक set)
अणु
	u16 data;
	u16 bits = 1 << port;

	data = पढ़ोw(hw->io + addr);
	bits <<= shअगरt;
	अगर (set)
		data |= bits;
	अन्यथा
		data &= ~bits;
	ग_लिखोw(data, hw->io + addr);
पूर्ण

/**
 * port_r8 - पढ़ो byte from port रेजिस्टर
 * @hw: 	The hardware instance.
 * @port:	The port index.
 * @offset:	The offset of the port रेजिस्टर.
 * @data:	Buffer to store the data.
 *
 * This routine पढ़ोs a byte from the port रेजिस्टर.
 */
अटल व्योम port_r8(काष्ठा ksz_hw *hw, पूर्णांक port, पूर्णांक offset, u8 *data)
अणु
	u32 addr;

	PORT_CTRL_ADDR(port, addr);
	addr += offset;
	*data = पढ़ोb(hw->io + addr);
पूर्ण

/**
 * port_r16 - पढ़ो word from port रेजिस्टर.
 * @hw: 	The hardware instance.
 * @port:	The port index.
 * @offset:	The offset of the port रेजिस्टर.
 * @data:	Buffer to store the data.
 *
 * This routine पढ़ोs a word from the port रेजिस्टर.
 */
अटल व्योम port_r16(काष्ठा ksz_hw *hw, पूर्णांक port, पूर्णांक offset, u16 *data)
अणु
	u32 addr;

	PORT_CTRL_ADDR(port, addr);
	addr += offset;
	*data = पढ़ोw(hw->io + addr);
पूर्ण

/**
 * port_w16 - ग_लिखो word to port रेजिस्टर.
 * @hw: 	The hardware instance.
 * @port:	The port index.
 * @offset:	The offset of the port रेजिस्टर.
 * @data:	Data to ग_लिखो.
 *
 * This routine ग_लिखोs a word to the port रेजिस्टर.
 */
अटल व्योम port_w16(काष्ठा ksz_hw *hw, पूर्णांक port, पूर्णांक offset, u16 data)
अणु
	u32 addr;

	PORT_CTRL_ADDR(port, addr);
	addr += offset;
	ग_लिखोw(data, hw->io + addr);
पूर्ण

/**
 * sw_chk - check चयन रेजिस्टर bits
 * @hw: 	The hardware instance.
 * @addr:	The address of the चयन रेजिस्टर.
 * @bits:	The data bits to check.
 *
 * This function checks whether the specअगरied bits of the चयन रेजिस्टर are
 * set or not.
 *
 * Return 0 अगर the bits are not set.
 */
अटल पूर्णांक sw_chk(काष्ठा ksz_hw *hw, u32 addr, u16 bits)
अणु
	u16 data;

	data = पढ़ोw(hw->io + addr);
	वापस (data & bits) == bits;
पूर्ण

/**
 * sw_cfg - set चयन रेजिस्टर bits
 * @hw: 	The hardware instance.
 * @addr:	The address of the चयन रेजिस्टर.
 * @bits:	The data bits to set.
 * @set:	The flag indicating whether the bits are to be set or not.
 *
 * This function sets or resets the specअगरied bits of the चयन रेजिस्टर.
 */
अटल व्योम sw_cfg(काष्ठा ksz_hw *hw, u32 addr, u16 bits, पूर्णांक set)
अणु
	u16 data;

	data = पढ़ोw(hw->io + addr);
	अगर (set)
		data |= bits;
	अन्यथा
		data &= ~bits;
	ग_लिखोw(data, hw->io + addr);
पूर्ण

/* Bandwidth */

अटल अंतरभूत व्योम port_cfg_broad_storm(काष्ठा ksz_hw *hw, पूर्णांक p, पूर्णांक set)
अणु
	port_cfg(hw, p,
		KS8842_PORT_CTRL_1_OFFSET, PORT_BROADCAST_STORM, set);
पूर्ण

अटल अंतरभूत पूर्णांक port_chk_broad_storm(काष्ठा ksz_hw *hw, पूर्णांक p)
अणु
	वापस port_chk(hw, p,
		KS8842_PORT_CTRL_1_OFFSET, PORT_BROADCAST_STORM);
पूर्ण

/* Driver set चयन broadcast storm protection at 10% rate. */
#घोषणा BROADCAST_STORM_PROTECTION_RATE	10

/* 148,800 frames * 67 ms / 100 */
#घोषणा BROADCAST_STORM_VALUE		9969

/**
 * sw_cfg_broad_storm - configure broadcast storm threshold
 * @hw: 	The hardware instance.
 * @percent:	Broadcast storm threshold in percent of transmit rate.
 *
 * This routine configures the broadcast storm threshold of the चयन.
 */
अटल व्योम sw_cfg_broad_storm(काष्ठा ksz_hw *hw, u8 percent)
अणु
	u16 data;
	u32 value = ((u32) BROADCAST_STORM_VALUE * (u32) percent / 100);

	अगर (value > BROADCAST_STORM_RATE)
		value = BROADCAST_STORM_RATE;

	data = पढ़ोw(hw->io + KS8842_SWITCH_CTRL_3_OFFSET);
	data &= ~(BROADCAST_STORM_RATE_LO | BROADCAST_STORM_RATE_HI);
	data |= ((value & 0x00FF) << 8) | ((value & 0xFF00) >> 8);
	ग_लिखोw(data, hw->io + KS8842_SWITCH_CTRL_3_OFFSET);
पूर्ण

/**
 * sw_get_board_storm - get broadcast storm threshold
 * @hw: 	The hardware instance.
 * @percent:	Buffer to store the broadcast storm threshold percentage.
 *
 * This routine retrieves the broadcast storm threshold of the चयन.
 */
अटल व्योम sw_get_broad_storm(काष्ठा ksz_hw *hw, u8 *percent)
अणु
	पूर्णांक num;
	u16 data;

	data = पढ़ोw(hw->io + KS8842_SWITCH_CTRL_3_OFFSET);
	num = (data & BROADCAST_STORM_RATE_HI);
	num <<= 8;
	num |= (data & BROADCAST_STORM_RATE_LO) >> 8;
	num = DIV_ROUND_CLOSEST(num * 100, BROADCAST_STORM_VALUE);
	*percent = (u8) num;
पूर्ण

/**
 * sw_dis_broad_storm - disable broadstorm
 * @hw: 	The hardware instance.
 * @port:	The port index.
 *
 * This routine disables the broadcast storm limit function of the चयन.
 */
अटल व्योम sw_dis_broad_storm(काष्ठा ksz_hw *hw, पूर्णांक port)
अणु
	port_cfg_broad_storm(hw, port, 0);
पूर्ण

/**
 * sw_ena_broad_storm - enable broadcast storm
 * @hw: 	The hardware instance.
 * @port:	The port index.
 *
 * This routine enables the broadcast storm limit function of the चयन.
 */
अटल व्योम sw_ena_broad_storm(काष्ठा ksz_hw *hw, पूर्णांक port)
अणु
	sw_cfg_broad_storm(hw, hw->ksz_चयन->broad_per);
	port_cfg_broad_storm(hw, port, 1);
पूर्ण

/**
 * sw_init_broad_storm - initialize broadcast storm
 * @hw: 	The hardware instance.
 *
 * This routine initializes the broadcast storm limit function of the चयन.
 */
अटल व्योम sw_init_broad_storm(काष्ठा ksz_hw *hw)
अणु
	पूर्णांक port;

	hw->ksz_चयन->broad_per = 1;
	sw_cfg_broad_storm(hw, hw->ksz_चयन->broad_per);
	क्रम (port = 0; port < TOTAL_PORT_NUM; port++)
		sw_dis_broad_storm(hw, port);
	sw_cfg(hw, KS8842_SWITCH_CTRL_2_OFFSET, MULTICAST_STORM_DISABLE, 1);
पूर्ण

/**
 * hw_cfg_broad_storm - configure broadcast storm
 * @hw: 	The hardware instance.
 * @percent:	Broadcast storm threshold in percent of transmit rate.
 *
 * This routine configures the broadcast storm threshold of the चयन.
 * It is called by user functions.  The hardware should be acquired first.
 */
अटल व्योम hw_cfg_broad_storm(काष्ठा ksz_hw *hw, u8 percent)
अणु
	अगर (percent > 100)
		percent = 100;

	sw_cfg_broad_storm(hw, percent);
	sw_get_broad_storm(hw, &percent);
	hw->ksz_चयन->broad_per = percent;
पूर्ण

/**
 * sw_dis_prio_rate - disable चयन priority rate
 * @hw: 	The hardware instance.
 * @port:	The port index.
 *
 * This routine disables the priority rate function of the चयन.
 */
अटल व्योम sw_dis_prio_rate(काष्ठा ksz_hw *hw, पूर्णांक port)
अणु
	u32 addr;

	PORT_CTRL_ADDR(port, addr);
	addr += KS8842_PORT_IN_RATE_OFFSET;
	ग_लिखोl(0, hw->io + addr);
पूर्ण

/**
 * sw_init_prio_rate - initialize चयन prioirty rate
 * @hw: 	The hardware instance.
 *
 * This routine initializes the priority rate function of the चयन.
 */
अटल व्योम sw_init_prio_rate(काष्ठा ksz_hw *hw)
अणु
	पूर्णांक port;
	पूर्णांक prio;
	काष्ठा ksz_चयन *sw = hw->ksz_चयन;

	क्रम (port = 0; port < TOTAL_PORT_NUM; port++) अणु
		क्रम (prio = 0; prio < PRIO_QUEUES; prio++) अणु
			sw->port_cfg[port].rx_rate[prio] =
			sw->port_cfg[port].tx_rate[prio] = 0;
		पूर्ण
		sw_dis_prio_rate(hw, port);
	पूर्ण
पूर्ण

/* Communication */

अटल अंतरभूत व्योम port_cfg_back_pressure(काष्ठा ksz_hw *hw, पूर्णांक p, पूर्णांक set)
अणु
	port_cfg(hw, p,
		KS8842_PORT_CTRL_2_OFFSET, PORT_BACK_PRESSURE, set);
पूर्ण

अटल अंतरभूत व्योम port_cfg_क्रमce_flow_ctrl(काष्ठा ksz_hw *hw, पूर्णांक p, पूर्णांक set)
अणु
	port_cfg(hw, p,
		KS8842_PORT_CTRL_2_OFFSET, PORT_FORCE_FLOW_CTRL, set);
पूर्ण

अटल अंतरभूत पूर्णांक port_chk_back_pressure(काष्ठा ksz_hw *hw, पूर्णांक p)
अणु
	वापस port_chk(hw, p,
		KS8842_PORT_CTRL_2_OFFSET, PORT_BACK_PRESSURE);
पूर्ण

अटल अंतरभूत पूर्णांक port_chk_क्रमce_flow_ctrl(काष्ठा ksz_hw *hw, पूर्णांक p)
अणु
	वापस port_chk(hw, p,
		KS8842_PORT_CTRL_2_OFFSET, PORT_FORCE_FLOW_CTRL);
पूर्ण

/* Spanning Tree */

अटल अंतरभूत व्योम port_cfg_rx(काष्ठा ksz_hw *hw, पूर्णांक p, पूर्णांक set)
अणु
	port_cfg(hw, p,
		KS8842_PORT_CTRL_2_OFFSET, PORT_RX_ENABLE, set);
पूर्ण

अटल अंतरभूत व्योम port_cfg_tx(काष्ठा ksz_hw *hw, पूर्णांक p, पूर्णांक set)
अणु
	port_cfg(hw, p,
		KS8842_PORT_CTRL_2_OFFSET, PORT_TX_ENABLE, set);
पूर्ण

अटल अंतरभूत व्योम sw_cfg_fast_aging(काष्ठा ksz_hw *hw, पूर्णांक set)
अणु
	sw_cfg(hw, KS8842_SWITCH_CTRL_1_OFFSET, SWITCH_FAST_AGING, set);
पूर्ण

अटल अंतरभूत व्योम sw_flush_dyn_mac_table(काष्ठा ksz_hw *hw)
अणु
	अगर (!(hw->overrides & FAST_AGING)) अणु
		sw_cfg_fast_aging(hw, 1);
		mdelay(1);
		sw_cfg_fast_aging(hw, 0);
	पूर्ण
पूर्ण

/* VLAN */

अटल अंतरभूत व्योम port_cfg_ins_tag(काष्ठा ksz_hw *hw, पूर्णांक p, पूर्णांक insert)
अणु
	port_cfg(hw, p,
		KS8842_PORT_CTRL_1_OFFSET, PORT_INSERT_TAG, insert);
पूर्ण

अटल अंतरभूत व्योम port_cfg_rmv_tag(काष्ठा ksz_hw *hw, पूर्णांक p, पूर्णांक हटाओ)
अणु
	port_cfg(hw, p,
		KS8842_PORT_CTRL_1_OFFSET, PORT_REMOVE_TAG, हटाओ);
पूर्ण

अटल अंतरभूत पूर्णांक port_chk_ins_tag(काष्ठा ksz_hw *hw, पूर्णांक p)
अणु
	वापस port_chk(hw, p,
		KS8842_PORT_CTRL_1_OFFSET, PORT_INSERT_TAG);
पूर्ण

अटल अंतरभूत पूर्णांक port_chk_rmv_tag(काष्ठा ksz_hw *hw, पूर्णांक p)
अणु
	वापस port_chk(hw, p,
		KS8842_PORT_CTRL_1_OFFSET, PORT_REMOVE_TAG);
पूर्ण

अटल अंतरभूत व्योम port_cfg_dis_non_vid(काष्ठा ksz_hw *hw, पूर्णांक p, पूर्णांक set)
अणु
	port_cfg(hw, p,
		KS8842_PORT_CTRL_2_OFFSET, PORT_DISCARD_NON_VID, set);
पूर्ण

अटल अंतरभूत व्योम port_cfg_in_filter(काष्ठा ksz_hw *hw, पूर्णांक p, पूर्णांक set)
अणु
	port_cfg(hw, p,
		KS8842_PORT_CTRL_2_OFFSET, PORT_INGRESS_VLAN_FILTER, set);
पूर्ण

अटल अंतरभूत पूर्णांक port_chk_dis_non_vid(काष्ठा ksz_hw *hw, पूर्णांक p)
अणु
	वापस port_chk(hw, p,
		KS8842_PORT_CTRL_2_OFFSET, PORT_DISCARD_NON_VID);
पूर्ण

अटल अंतरभूत पूर्णांक port_chk_in_filter(काष्ठा ksz_hw *hw, पूर्णांक p)
अणु
	वापस port_chk(hw, p,
		KS8842_PORT_CTRL_2_OFFSET, PORT_INGRESS_VLAN_FILTER);
पूर्ण

/* Mirroring */

अटल अंतरभूत व्योम port_cfg_mirror_snअगरfer(काष्ठा ksz_hw *hw, पूर्णांक p, पूर्णांक set)
अणु
	port_cfg(hw, p,
		KS8842_PORT_CTRL_2_OFFSET, PORT_MIRROR_SNIFFER, set);
पूर्ण

अटल अंतरभूत व्योम port_cfg_mirror_rx(काष्ठा ksz_hw *hw, पूर्णांक p, पूर्णांक set)
अणु
	port_cfg(hw, p,
		KS8842_PORT_CTRL_2_OFFSET, PORT_MIRROR_RX, set);
पूर्ण

अटल अंतरभूत व्योम port_cfg_mirror_tx(काष्ठा ksz_hw *hw, पूर्णांक p, पूर्णांक set)
अणु
	port_cfg(hw, p,
		KS8842_PORT_CTRL_2_OFFSET, PORT_MIRROR_TX, set);
पूर्ण

अटल अंतरभूत व्योम sw_cfg_mirror_rx_tx(काष्ठा ksz_hw *hw, पूर्णांक set)
अणु
	sw_cfg(hw, KS8842_SWITCH_CTRL_2_OFFSET, SWITCH_MIRROR_RX_TX, set);
पूर्ण

अटल व्योम sw_init_mirror(काष्ठा ksz_hw *hw)
अणु
	पूर्णांक port;

	क्रम (port = 0; port < TOTAL_PORT_NUM; port++) अणु
		port_cfg_mirror_snअगरfer(hw, port, 0);
		port_cfg_mirror_rx(hw, port, 0);
		port_cfg_mirror_tx(hw, port, 0);
	पूर्ण
	sw_cfg_mirror_rx_tx(hw, 0);
पूर्ण

अटल अंतरभूत व्योम sw_cfg_unk_def_deliver(काष्ठा ksz_hw *hw, पूर्णांक set)
अणु
	sw_cfg(hw, KS8842_SWITCH_CTRL_7_OFFSET,
		SWITCH_UNK_DEF_PORT_ENABLE, set);
पूर्ण

अटल अंतरभूत पूर्णांक sw_cfg_chk_unk_def_deliver(काष्ठा ksz_hw *hw)
अणु
	वापस sw_chk(hw, KS8842_SWITCH_CTRL_7_OFFSET,
		SWITCH_UNK_DEF_PORT_ENABLE);
पूर्ण

अटल अंतरभूत व्योम sw_cfg_unk_def_port(काष्ठा ksz_hw *hw, पूर्णांक port, पूर्णांक set)
अणु
	port_cfg_shअगरt(hw, port, KS8842_SWITCH_CTRL_7_OFFSET, 0, set);
पूर्ण

अटल अंतरभूत पूर्णांक sw_chk_unk_def_port(काष्ठा ksz_hw *hw, पूर्णांक port)
अणु
	वापस port_chk_shअगरt(hw, port, KS8842_SWITCH_CTRL_7_OFFSET, 0);
पूर्ण

/* Priority */

अटल अंतरभूत व्योम port_cfg_dअगरfserv(काष्ठा ksz_hw *hw, पूर्णांक p, पूर्णांक set)
अणु
	port_cfg(hw, p,
		KS8842_PORT_CTRL_1_OFFSET, PORT_DIFFSERV_ENABLE, set);
पूर्ण

अटल अंतरभूत व्योम port_cfg_802_1p(काष्ठा ksz_hw *hw, पूर्णांक p, पूर्णांक set)
अणु
	port_cfg(hw, p,
		KS8842_PORT_CTRL_1_OFFSET, PORT_802_1P_ENABLE, set);
पूर्ण

अटल अंतरभूत व्योम port_cfg_replace_vid(काष्ठा ksz_hw *hw, पूर्णांक p, पूर्णांक set)
अणु
	port_cfg(hw, p,
		KS8842_PORT_CTRL_2_OFFSET, PORT_USER_PRIORITY_CEILING, set);
पूर्ण

अटल अंतरभूत व्योम port_cfg_prio(काष्ठा ksz_hw *hw, पूर्णांक p, पूर्णांक set)
अणु
	port_cfg(hw, p,
		KS8842_PORT_CTRL_1_OFFSET, PORT_PRIO_QUEUE_ENABLE, set);
पूर्ण

अटल अंतरभूत पूर्णांक port_chk_dअगरfserv(काष्ठा ksz_hw *hw, पूर्णांक p)
अणु
	वापस port_chk(hw, p,
		KS8842_PORT_CTRL_1_OFFSET, PORT_DIFFSERV_ENABLE);
पूर्ण

अटल अंतरभूत पूर्णांक port_chk_802_1p(काष्ठा ksz_hw *hw, पूर्णांक p)
अणु
	वापस port_chk(hw, p,
		KS8842_PORT_CTRL_1_OFFSET, PORT_802_1P_ENABLE);
पूर्ण

अटल अंतरभूत पूर्णांक port_chk_replace_vid(काष्ठा ksz_hw *hw, पूर्णांक p)
अणु
	वापस port_chk(hw, p,
		KS8842_PORT_CTRL_2_OFFSET, PORT_USER_PRIORITY_CEILING);
पूर्ण

अटल अंतरभूत पूर्णांक port_chk_prio(काष्ठा ksz_hw *hw, पूर्णांक p)
अणु
	वापस port_chk(hw, p,
		KS8842_PORT_CTRL_1_OFFSET, PORT_PRIO_QUEUE_ENABLE);
पूर्ण

/**
 * sw_dis_dअगरfserv - disable चयन DअगरfServ priority
 * @hw: 	The hardware instance.
 * @port:	The port index.
 *
 * This routine disables the DअगरfServ priority function of the चयन.
 */
अटल व्योम sw_dis_dअगरfserv(काष्ठा ksz_hw *hw, पूर्णांक port)
अणु
	port_cfg_dअगरfserv(hw, port, 0);
पूर्ण

/**
 * sw_dis_802_1p - disable चयन 802.1p priority
 * @hw: 	The hardware instance.
 * @port:	The port index.
 *
 * This routine disables the 802.1p priority function of the चयन.
 */
अटल व्योम sw_dis_802_1p(काष्ठा ksz_hw *hw, पूर्णांक port)
अणु
	port_cfg_802_1p(hw, port, 0);
पूर्ण

/**
 * sw_cfg_replace_null_vid -
 * @hw: 	The hardware instance.
 * @set:	The flag to disable or enable.
 *
 */
अटल व्योम sw_cfg_replace_null_vid(काष्ठा ksz_hw *hw, पूर्णांक set)
अणु
	sw_cfg(hw, KS8842_SWITCH_CTRL_3_OFFSET, SWITCH_REPLACE_शून्य_VID, set);
पूर्ण

/**
 * sw_cfg_replace_vid - enable चयन 802.10 priority re-mapping
 * @hw: 	The hardware instance.
 * @port:	The port index.
 * @set:	The flag to disable or enable.
 *
 * This routine enables the 802.1p priority re-mapping function of the चयन.
 * That allows 802.1p priority field to be replaced with the port's शेष
 * tag's priority value if the ingress packet's 802.1p priority has a higher
 * priority than port's default tag's priority.
 */
अटल व्योम sw_cfg_replace_vid(काष्ठा ksz_hw *hw, पूर्णांक port, पूर्णांक set)
अणु
	port_cfg_replace_vid(hw, port, set);
पूर्ण

/**
 * sw_cfg_port_based - configure चयन port based priority
 * @hw: 	The hardware instance.
 * @port:	The port index.
 * @prio:	The priority to set.
 *
 * This routine configures the port based priority of the चयन.
 */
अटल व्योम sw_cfg_port_based(काष्ठा ksz_hw *hw, पूर्णांक port, u8 prio)
अणु
	u16 data;

	अगर (prio > PORT_BASED_PRIORITY_BASE)
		prio = PORT_BASED_PRIORITY_BASE;

	hw->ksz_चयन->port_cfg[port].port_prio = prio;

	port_r16(hw, port, KS8842_PORT_CTRL_1_OFFSET, &data);
	data &= ~PORT_BASED_PRIORITY_MASK;
	data |= prio << PORT_BASED_PRIORITY_SHIFT;
	port_w16(hw, port, KS8842_PORT_CTRL_1_OFFSET, data);
पूर्ण

/**
 * sw_dis_multi_queue - disable transmit multiple queues
 * @hw: 	The hardware instance.
 * @port:	The port index.
 *
 * This routine disables the transmit multiple queues selection of the चयन
 * port.  Only single transmit queue on the port.
 */
अटल व्योम sw_dis_multi_queue(काष्ठा ksz_hw *hw, पूर्णांक port)
अणु
	port_cfg_prio(hw, port, 0);
पूर्ण

/**
 * sw_init_prio - initialize चयन priority
 * @hw: 	The hardware instance.
 *
 * This routine initializes the चयन QoS priority functions.
 */
अटल व्योम sw_init_prio(काष्ठा ksz_hw *hw)
अणु
	पूर्णांक port;
	पूर्णांक tos;
	काष्ठा ksz_चयन *sw = hw->ksz_चयन;

	/*
	 * Init all the 802.1p tag priority value to be asचिन्हित to dअगरferent
	 * priority queue.
	 */
	sw->p_802_1p[0] = 0;
	sw->p_802_1p[1] = 0;
	sw->p_802_1p[2] = 1;
	sw->p_802_1p[3] = 1;
	sw->p_802_1p[4] = 2;
	sw->p_802_1p[5] = 2;
	sw->p_802_1p[6] = 3;
	sw->p_802_1p[7] = 3;

	/*
	 * Init all the DअगरfServ priority value to be asचिन्हित to priority
	 * queue 0.
	 */
	क्रम (tos = 0; tos < DIFFSERV_ENTRIES; tos++)
		sw->dअगरfserv[tos] = 0;

	/* All QoS functions disabled. */
	क्रम (port = 0; port < TOTAL_PORT_NUM; port++) अणु
		sw_dis_multi_queue(hw, port);
		sw_dis_dअगरfserv(hw, port);
		sw_dis_802_1p(hw, port);
		sw_cfg_replace_vid(hw, port, 0);

		sw->port_cfg[port].port_prio = 0;
		sw_cfg_port_based(hw, port, sw->port_cfg[port].port_prio);
	पूर्ण
	sw_cfg_replace_null_vid(hw, 0);
पूर्ण

/**
 * port_get_def_vid - get port शेष VID.
 * @hw: 	The hardware instance.
 * @port:	The port index.
 * @vid:	Buffer to store the VID.
 *
 * This routine retrieves the शेष VID of the port.
 */
अटल व्योम port_get_def_vid(काष्ठा ksz_hw *hw, पूर्णांक port, u16 *vid)
अणु
	u32 addr;

	PORT_CTRL_ADDR(port, addr);
	addr += KS8842_PORT_CTRL_VID_OFFSET;
	*vid = पढ़ोw(hw->io + addr);
पूर्ण

/**
 * sw_init_vlan - initialize चयन VLAN
 * @hw: 	The hardware instance.
 *
 * This routine initializes the VLAN function of the चयन.
 */
अटल व्योम sw_init_vlan(काष्ठा ksz_hw *hw)
अणु
	पूर्णांक port;
	पूर्णांक entry;
	काष्ठा ksz_चयन *sw = hw->ksz_चयन;

	/* Read 16 VLAN entries from device's VLAN table. */
	क्रम (entry = 0; entry < VLAN_TABLE_ENTRIES; entry++) अणु
		sw_r_vlan_table(hw, entry,
			&sw->vlan_table[entry].vid,
			&sw->vlan_table[entry].fid,
			&sw->vlan_table[entry].member);
	पूर्ण

	क्रम (port = 0; port < TOTAL_PORT_NUM; port++) अणु
		port_get_def_vid(hw, port, &sw->port_cfg[port].vid);
		sw->port_cfg[port].member = PORT_MASK;
	पूर्ण
पूर्ण

/**
 * sw_cfg_port_base_vlan - configure port-based VLAN membership
 * @hw: 	The hardware instance.
 * @port:	The port index.
 * @member:	The port-based VLAN membership.
 *
 * This routine configures the port-based VLAN membership of the port.
 */
अटल व्योम sw_cfg_port_base_vlan(काष्ठा ksz_hw *hw, पूर्णांक port, u8 member)
अणु
	u32 addr;
	u8 data;

	PORT_CTRL_ADDR(port, addr);
	addr += KS8842_PORT_CTRL_2_OFFSET;

	data = पढ़ोb(hw->io + addr);
	data &= ~PORT_VLAN_MEMBERSHIP;
	data |= (member & PORT_MASK);
	ग_लिखोb(data, hw->io + addr);

	hw->ksz_चयन->port_cfg[port].member = member;
पूर्ण

/**
 * sw_get_addr - get the चयन MAC address.
 * @hw: 	The hardware instance.
 * @mac_addr:	Buffer to store the MAC address.
 *
 * This function retrieves the MAC address of the चयन.
 */
अटल अंतरभूत व्योम sw_get_addr(काष्ठा ksz_hw *hw, u8 *mac_addr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 6; i += 2) अणु
		mac_addr[i] = पढ़ोb(hw->io + KS8842_MAC_ADDR_0_OFFSET + i);
		mac_addr[1 + i] = पढ़ोb(hw->io + KS8842_MAC_ADDR_1_OFFSET + i);
	पूर्ण
पूर्ण

/**
 * sw_set_addr - configure चयन MAC address
 * @hw: 	The hardware instance.
 * @mac_addr:	The MAC address.
 *
 * This function configures the MAC address of the चयन.
 */
अटल व्योम sw_set_addr(काष्ठा ksz_hw *hw, u8 *mac_addr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 6; i += 2) अणु
		ग_लिखोb(mac_addr[i], hw->io + KS8842_MAC_ADDR_0_OFFSET + i);
		ग_लिखोb(mac_addr[1 + i], hw->io + KS8842_MAC_ADDR_1_OFFSET + i);
	पूर्ण
पूर्ण

/**
 * sw_set_global_ctrl - set चयन global control
 * @hw: 	The hardware instance.
 *
 * This routine sets the global control of the चयन function.
 */
अटल व्योम sw_set_global_ctrl(काष्ठा ksz_hw *hw)
अणु
	u16 data;

	/* Enable चयन MII flow control. */
	data = पढ़ोw(hw->io + KS8842_SWITCH_CTRL_3_OFFSET);
	data |= SWITCH_FLOW_CTRL;
	ग_लिखोw(data, hw->io + KS8842_SWITCH_CTRL_3_OFFSET);

	data = पढ़ोw(hw->io + KS8842_SWITCH_CTRL_1_OFFSET);

	/* Enable aggressive back off algorithm in half duplex mode. */
	data |= SWITCH_AGGR_BACKOFF;

	/* Enable स्वतःmatic fast aging when link changed detected. */
	data |= SWITCH_AGING_ENABLE;
	data |= SWITCH_LINK_AUTO_AGING;

	अगर (hw->overrides & FAST_AGING)
		data |= SWITCH_FAST_AGING;
	अन्यथा
		data &= ~SWITCH_FAST_AGING;
	ग_लिखोw(data, hw->io + KS8842_SWITCH_CTRL_1_OFFSET);

	data = पढ़ोw(hw->io + KS8842_SWITCH_CTRL_2_OFFSET);

	/* Enable no excessive collision drop. */
	data |= NO_EXC_COLLISION_DROP;
	ग_लिखोw(data, hw->io + KS8842_SWITCH_CTRL_2_OFFSET);
पूर्ण

क्रमागत अणु
	STP_STATE_DISABLED = 0,
	STP_STATE_LISTENING,
	STP_STATE_LEARNING,
	STP_STATE_FORWARDING,
	STP_STATE_BLOCKED,
	STP_STATE_SIMPLE
पूर्ण;

/**
 * port_set_stp_state - configure port spanning tree state
 * @hw: 	The hardware instance.
 * @port:	The port index.
 * @state:	The spanning tree state.
 *
 * This routine configures the spanning tree state of the port.
 */
अटल व्योम port_set_stp_state(काष्ठा ksz_hw *hw, पूर्णांक port, पूर्णांक state)
अणु
	u16 data;

	port_r16(hw, port, KS8842_PORT_CTRL_2_OFFSET, &data);
	चयन (state) अणु
	हाल STP_STATE_DISABLED:
		data &= ~(PORT_TX_ENABLE | PORT_RX_ENABLE);
		data |= PORT_LEARN_DISABLE;
		अवरोध;
	हाल STP_STATE_LISTENING:
/*
 * No need to turn on transmit because of port direct mode.
 * Turning on receive is required अगर अटल MAC table is not setup.
 */
		data &= ~PORT_TX_ENABLE;
		data |= PORT_RX_ENABLE;
		data |= PORT_LEARN_DISABLE;
		अवरोध;
	हाल STP_STATE_LEARNING:
		data &= ~PORT_TX_ENABLE;
		data |= PORT_RX_ENABLE;
		data &= ~PORT_LEARN_DISABLE;
		अवरोध;
	हाल STP_STATE_FORWARDING:
		data |= (PORT_TX_ENABLE | PORT_RX_ENABLE);
		data &= ~PORT_LEARN_DISABLE;
		अवरोध;
	हाल STP_STATE_BLOCKED:
/*
 * Need to setup अटल MAC table with override to keep receiving BPDU
 * messages.  See sw_init_stp routine.
 */
		data &= ~(PORT_TX_ENABLE | PORT_RX_ENABLE);
		data |= PORT_LEARN_DISABLE;
		अवरोध;
	हाल STP_STATE_SIMPLE:
		data |= (PORT_TX_ENABLE | PORT_RX_ENABLE);
		data |= PORT_LEARN_DISABLE;
		अवरोध;
	पूर्ण
	port_w16(hw, port, KS8842_PORT_CTRL_2_OFFSET, data);
	hw->ksz_चयन->port_cfg[port].stp_state = state;
पूर्ण

#घोषणा STP_ENTRY			0
#घोषणा BROADCAST_ENTRY			1
#घोषणा BRIDGE_ADDR_ENTRY		2
#घोषणा IPV6_ADDR_ENTRY			3

/**
 * sw_clr_sta_mac_table - clear अटल MAC table
 * @hw: 	The hardware instance.
 *
 * This routine clears the अटल MAC table.
 */
अटल व्योम sw_clr_sta_mac_table(काष्ठा ksz_hw *hw)
अणु
	काष्ठा ksz_mac_table *entry;
	पूर्णांक i;

	क्रम (i = 0; i < STATIC_MAC_TABLE_ENTRIES; i++) अणु
		entry = &hw->ksz_चयन->mac_table[i];
		sw_w_sta_mac_table(hw, i,
			entry->mac_addr, entry->ports,
			entry->override, 0,
			entry->use_fid, entry->fid);
	पूर्ण
पूर्ण

/**
 * sw_init_stp - initialize चयन spanning tree support
 * @hw: 	The hardware instance.
 *
 * This routine initializes the spanning tree support of the चयन.
 */
अटल व्योम sw_init_stp(काष्ठा ksz_hw *hw)
अणु
	काष्ठा ksz_mac_table *entry;

	entry = &hw->ksz_चयन->mac_table[STP_ENTRY];
	entry->mac_addr[0] = 0x01;
	entry->mac_addr[1] = 0x80;
	entry->mac_addr[2] = 0xC2;
	entry->mac_addr[3] = 0x00;
	entry->mac_addr[4] = 0x00;
	entry->mac_addr[5] = 0x00;
	entry->ports = HOST_MASK;
	entry->override = 1;
	entry->valid = 1;
	sw_w_sta_mac_table(hw, STP_ENTRY,
		entry->mac_addr, entry->ports,
		entry->override, entry->valid,
		entry->use_fid, entry->fid);
पूर्ण

/**
 * sw_block_addr - block certain packets from the host port
 * @hw: 	The hardware instance.
 *
 * This routine blocks certain packets from reaching to the host port.
 */
अटल व्योम sw_block_addr(काष्ठा ksz_hw *hw)
अणु
	काष्ठा ksz_mac_table *entry;
	पूर्णांक i;

	क्रम (i = BROADCAST_ENTRY; i <= IPV6_ADDR_ENTRY; i++) अणु
		entry = &hw->ksz_चयन->mac_table[i];
		entry->valid = 0;
		sw_w_sta_mac_table(hw, i,
			entry->mac_addr, entry->ports,
			entry->override, entry->valid,
			entry->use_fid, entry->fid);
	पूर्ण
पूर्ण

#घोषणा PHY_LINK_SUPPORT		\
	(PHY_AUTO_NEG_ASYM_PAUSE |	\
	PHY_AUTO_NEG_SYM_PAUSE |	\
	PHY_AUTO_NEG_100BT4 |		\
	PHY_AUTO_NEG_100BTX_FD |	\
	PHY_AUTO_NEG_100BTX |		\
	PHY_AUTO_NEG_10BT_FD |		\
	PHY_AUTO_NEG_10BT)

अटल अंतरभूत व्योम hw_r_phy_ctrl(काष्ठा ksz_hw *hw, पूर्णांक phy, u16 *data)
अणु
	*data = पढ़ोw(hw->io + phy + KS884X_PHY_CTRL_OFFSET);
पूर्ण

अटल अंतरभूत व्योम hw_w_phy_ctrl(काष्ठा ksz_hw *hw, पूर्णांक phy, u16 data)
अणु
	ग_लिखोw(data, hw->io + phy + KS884X_PHY_CTRL_OFFSET);
पूर्ण

अटल अंतरभूत व्योम hw_r_phy_link_stat(काष्ठा ksz_hw *hw, पूर्णांक phy, u16 *data)
अणु
	*data = पढ़ोw(hw->io + phy + KS884X_PHY_STATUS_OFFSET);
पूर्ण

अटल अंतरभूत व्योम hw_r_phy_स्वतः_neg(काष्ठा ksz_hw *hw, पूर्णांक phy, u16 *data)
अणु
	*data = पढ़ोw(hw->io + phy + KS884X_PHY_AUTO_NEG_OFFSET);
पूर्ण

अटल अंतरभूत व्योम hw_w_phy_स्वतः_neg(काष्ठा ksz_hw *hw, पूर्णांक phy, u16 data)
अणु
	ग_लिखोw(data, hw->io + phy + KS884X_PHY_AUTO_NEG_OFFSET);
पूर्ण

अटल अंतरभूत व्योम hw_r_phy_rem_cap(काष्ठा ksz_hw *hw, पूर्णांक phy, u16 *data)
अणु
	*data = पढ़ोw(hw->io + phy + KS884X_PHY_REMOTE_CAP_OFFSET);
पूर्ण

अटल अंतरभूत व्योम hw_r_phy_crossover(काष्ठा ksz_hw *hw, पूर्णांक phy, u16 *data)
अणु
	*data = पढ़ोw(hw->io + phy + KS884X_PHY_CTRL_OFFSET);
पूर्ण

अटल अंतरभूत व्योम hw_w_phy_crossover(काष्ठा ksz_hw *hw, पूर्णांक phy, u16 data)
अणु
	ग_लिखोw(data, hw->io + phy + KS884X_PHY_CTRL_OFFSET);
पूर्ण

अटल अंतरभूत व्योम hw_r_phy_polarity(काष्ठा ksz_hw *hw, पूर्णांक phy, u16 *data)
अणु
	*data = पढ़ोw(hw->io + phy + KS884X_PHY_PHY_CTRL_OFFSET);
पूर्ण

अटल अंतरभूत व्योम hw_w_phy_polarity(काष्ठा ksz_hw *hw, पूर्णांक phy, u16 data)
अणु
	ग_लिखोw(data, hw->io + phy + KS884X_PHY_PHY_CTRL_OFFSET);
पूर्ण

अटल अंतरभूत व्योम hw_r_phy_link_md(काष्ठा ksz_hw *hw, पूर्णांक phy, u16 *data)
अणु
	*data = पढ़ोw(hw->io + phy + KS884X_PHY_LINK_MD_OFFSET);
पूर्ण

अटल अंतरभूत व्योम hw_w_phy_link_md(काष्ठा ksz_hw *hw, पूर्णांक phy, u16 data)
अणु
	ग_लिखोw(data, hw->io + phy + KS884X_PHY_LINK_MD_OFFSET);
पूर्ण

/**
 * hw_r_phy - पढ़ो data from PHY रेजिस्टर
 * @hw: 	The hardware instance.
 * @port:	Port to पढ़ो.
 * @reg:	PHY रेजिस्टर to पढ़ो.
 * @val:	Buffer to store the पढ़ो data.
 *
 * This routine पढ़ोs data from the PHY रेजिस्टर.
 */
अटल व्योम hw_r_phy(काष्ठा ksz_hw *hw, पूर्णांक port, u16 reg, u16 *val)
अणु
	पूर्णांक phy;

	phy = KS884X_PHY_1_CTRL_OFFSET + port * PHY_CTRL_INTERVAL + reg;
	*val = पढ़ोw(hw->io + phy);
पूर्ण

/**
 * port_w_phy - ग_लिखो data to PHY रेजिस्टर
 * @hw: 	The hardware instance.
 * @port:	Port to ग_लिखो.
 * @reg:	PHY रेजिस्टर to ग_लिखो.
 * @val:	Word data to ग_लिखो.
 *
 * This routine ग_लिखोs data to the PHY रेजिस्टर.
 */
अटल व्योम hw_w_phy(काष्ठा ksz_hw *hw, पूर्णांक port, u16 reg, u16 val)
अणु
	पूर्णांक phy;

	phy = KS884X_PHY_1_CTRL_OFFSET + port * PHY_CTRL_INTERVAL + reg;
	ग_लिखोw(val, hw->io + phy);
पूर्ण

/*
 * EEPROM access functions
 */

#घोषणा AT93C_CODE			0
#घोषणा AT93C_WR_OFF			0x00
#घोषणा AT93C_WR_ALL			0x10
#घोषणा AT93C_ER_ALL			0x20
#घोषणा AT93C_WR_ON			0x30

#घोषणा AT93C_WRITE			1
#घोषणा AT93C_READ			2
#घोषणा AT93C_ERASE			3

#घोषणा EEPROM_DELAY			4

अटल अंतरभूत व्योम drop_gpio(काष्ठा ksz_hw *hw, u8 gpio)
अणु
	u16 data;

	data = पढ़ोw(hw->io + KS884X_EEPROM_CTRL_OFFSET);
	data &= ~gpio;
	ग_लिखोw(data, hw->io + KS884X_EEPROM_CTRL_OFFSET);
पूर्ण

अटल अंतरभूत व्योम उठाओ_gpio(काष्ठा ksz_hw *hw, u8 gpio)
अणु
	u16 data;

	data = पढ़ोw(hw->io + KS884X_EEPROM_CTRL_OFFSET);
	data |= gpio;
	ग_लिखोw(data, hw->io + KS884X_EEPROM_CTRL_OFFSET);
पूर्ण

अटल अंतरभूत u8 state_gpio(काष्ठा ksz_hw *hw, u8 gpio)
अणु
	u16 data;

	data = पढ़ोw(hw->io + KS884X_EEPROM_CTRL_OFFSET);
	वापस (u8)(data & gpio);
पूर्ण

अटल व्योम eeprom_clk(काष्ठा ksz_hw *hw)
अणु
	उठाओ_gpio(hw, EEPROM_SERIAL_CLOCK);
	udelay(EEPROM_DELAY);
	drop_gpio(hw, EEPROM_SERIAL_CLOCK);
	udelay(EEPROM_DELAY);
पूर्ण

अटल u16 spi_r(काष्ठा ksz_hw *hw)
अणु
	पूर्णांक i;
	u16 temp = 0;

	क्रम (i = 15; i >= 0; i--) अणु
		उठाओ_gpio(hw, EEPROM_SERIAL_CLOCK);
		udelay(EEPROM_DELAY);

		temp |= (state_gpio(hw, EEPROM_DATA_IN)) ? 1 << i : 0;

		drop_gpio(hw, EEPROM_SERIAL_CLOCK);
		udelay(EEPROM_DELAY);
	पूर्ण
	वापस temp;
पूर्ण

अटल व्योम spi_w(काष्ठा ksz_hw *hw, u16 data)
अणु
	पूर्णांक i;

	क्रम (i = 15; i >= 0; i--) अणु
		(data & (0x01 << i)) ? उठाओ_gpio(hw, EEPROM_DATA_OUT) :
			drop_gpio(hw, EEPROM_DATA_OUT);
		eeprom_clk(hw);
	पूर्ण
पूर्ण

अटल व्योम spi_reg(काष्ठा ksz_hw *hw, u8 data, u8 reg)
अणु
	पूर्णांक i;

	/* Initial start bit */
	उठाओ_gpio(hw, EEPROM_DATA_OUT);
	eeprom_clk(hw);

	/* AT93C operation */
	क्रम (i = 1; i >= 0; i--) अणु
		(data & (0x01 << i)) ? उठाओ_gpio(hw, EEPROM_DATA_OUT) :
			drop_gpio(hw, EEPROM_DATA_OUT);
		eeprom_clk(hw);
	पूर्ण

	/* Address location */
	क्रम (i = 5; i >= 0; i--) अणु
		(reg & (0x01 << i)) ? उठाओ_gpio(hw, EEPROM_DATA_OUT) :
			drop_gpio(hw, EEPROM_DATA_OUT);
		eeprom_clk(hw);
	पूर्ण
पूर्ण

#घोषणा EEPROM_DATA_RESERVED		0
#घोषणा EEPROM_DATA_MAC_ADDR_0		1
#घोषणा EEPROM_DATA_MAC_ADDR_1		2
#घोषणा EEPROM_DATA_MAC_ADDR_2		3
#घोषणा EEPROM_DATA_SUBSYS_ID		4
#घोषणा EEPROM_DATA_SUBSYS_VEN_ID	5
#घोषणा EEPROM_DATA_PM_CAP		6

/* User defined EEPROM data */
#घोषणा EEPROM_DATA_OTHER_MAC_ADDR	9

/**
 * eeprom_पढ़ो - पढ़ो from AT93C46 EEPROM
 * @hw: 	The hardware instance.
 * @reg:	The रेजिस्टर offset.
 *
 * This function पढ़ोs a word from the AT93C46 EEPROM.
 *
 * Return the data value.
 */
अटल u16 eeprom_पढ़ो(काष्ठा ksz_hw *hw, u8 reg)
अणु
	u16 data;

	उठाओ_gpio(hw, EEPROM_ACCESS_ENABLE | EEPROM_CHIP_SELECT);

	spi_reg(hw, AT93C_READ, reg);
	data = spi_r(hw);

	drop_gpio(hw, EEPROM_ACCESS_ENABLE | EEPROM_CHIP_SELECT);

	वापस data;
पूर्ण

/**
 * eeprom_ग_लिखो - ग_लिखो to AT93C46 EEPROM
 * @hw: 	The hardware instance.
 * @reg:	The रेजिस्टर offset.
 * @data:	The data value.
 *
 * This procedure ग_लिखोs a word to the AT93C46 EEPROM.
 */
अटल व्योम eeprom_ग_लिखो(काष्ठा ksz_hw *hw, u8 reg, u16 data)
अणु
	पूर्णांक समयout;

	उठाओ_gpio(hw, EEPROM_ACCESS_ENABLE | EEPROM_CHIP_SELECT);

	/* Enable ग_लिखो. */
	spi_reg(hw, AT93C_CODE, AT93C_WR_ON);
	drop_gpio(hw, EEPROM_CHIP_SELECT);
	udelay(1);

	/* Erase the रेजिस्टर. */
	उठाओ_gpio(hw, EEPROM_CHIP_SELECT);
	spi_reg(hw, AT93C_ERASE, reg);
	drop_gpio(hw, EEPROM_CHIP_SELECT);
	udelay(1);

	/* Check operation complete. */
	उठाओ_gpio(hw, EEPROM_CHIP_SELECT);
	समयout = 8;
	mdelay(2);
	करो अणु
		mdelay(1);
	पूर्ण जबतक (!state_gpio(hw, EEPROM_DATA_IN) && --समयout);
	drop_gpio(hw, EEPROM_CHIP_SELECT);
	udelay(1);

	/* Write the रेजिस्टर. */
	उठाओ_gpio(hw, EEPROM_CHIP_SELECT);
	spi_reg(hw, AT93C_WRITE, reg);
	spi_w(hw, data);
	drop_gpio(hw, EEPROM_CHIP_SELECT);
	udelay(1);

	/* Check operation complete. */
	उठाओ_gpio(hw, EEPROM_CHIP_SELECT);
	समयout = 8;
	mdelay(2);
	करो अणु
		mdelay(1);
	पूर्ण जबतक (!state_gpio(hw, EEPROM_DATA_IN) && --समयout);
	drop_gpio(hw, EEPROM_CHIP_SELECT);
	udelay(1);

	/* Disable ग_लिखो. */
	उठाओ_gpio(hw, EEPROM_CHIP_SELECT);
	spi_reg(hw, AT93C_CODE, AT93C_WR_OFF);

	drop_gpio(hw, EEPROM_ACCESS_ENABLE | EEPROM_CHIP_SELECT);
पूर्ण

/*
 * Link detection routines
 */

अटल u16 advertised_flow_ctrl(काष्ठा ksz_port *port, u16 ctrl)
अणु
	ctrl &= ~PORT_AUTO_NEG_SYM_PAUSE;
	चयन (port->flow_ctrl) अणु
	हाल PHY_FLOW_CTRL:
		ctrl |= PORT_AUTO_NEG_SYM_PAUSE;
		अवरोध;
	/* Not supported. */
	हाल PHY_TX_ONLY:
	हाल PHY_RX_ONLY:
	शेष:
		अवरोध;
	पूर्ण
	वापस ctrl;
पूर्ण

अटल व्योम set_flow_ctrl(काष्ठा ksz_hw *hw, पूर्णांक rx, पूर्णांक tx)
अणु
	u32 rx_cfg;
	u32 tx_cfg;

	rx_cfg = hw->rx_cfg;
	tx_cfg = hw->tx_cfg;
	अगर (rx)
		hw->rx_cfg |= DMA_RX_FLOW_ENABLE;
	अन्यथा
		hw->rx_cfg &= ~DMA_RX_FLOW_ENABLE;
	अगर (tx)
		hw->tx_cfg |= DMA_TX_FLOW_ENABLE;
	अन्यथा
		hw->tx_cfg &= ~DMA_TX_FLOW_ENABLE;
	अगर (hw->enabled) अणु
		अगर (rx_cfg != hw->rx_cfg)
			ग_लिखोl(hw->rx_cfg, hw->io + KS_DMA_RX_CTRL);
		अगर (tx_cfg != hw->tx_cfg)
			ग_लिखोl(hw->tx_cfg, hw->io + KS_DMA_TX_CTRL);
	पूर्ण
पूर्ण

अटल व्योम determine_flow_ctrl(काष्ठा ksz_hw *hw, काष्ठा ksz_port *port,
	u16 local, u16 remote)
अणु
	पूर्णांक rx;
	पूर्णांक tx;

	अगर (hw->overrides & PAUSE_FLOW_CTRL)
		वापस;

	rx = tx = 0;
	अगर (port->क्रमce_link)
		rx = tx = 1;
	अगर (remote & PHY_AUTO_NEG_SYM_PAUSE) अणु
		अगर (local & PHY_AUTO_NEG_SYM_PAUSE) अणु
			rx = tx = 1;
		पूर्ण अन्यथा अगर ((remote & PHY_AUTO_NEG_ASYM_PAUSE) &&
				(local & PHY_AUTO_NEG_PAUSE) ==
				PHY_AUTO_NEG_ASYM_PAUSE) अणु
			tx = 1;
		पूर्ण
	पूर्ण अन्यथा अगर (remote & PHY_AUTO_NEG_ASYM_PAUSE) अणु
		अगर ((local & PHY_AUTO_NEG_PAUSE) == PHY_AUTO_NEG_PAUSE)
			rx = 1;
	पूर्ण
	अगर (!hw->ksz_चयन)
		set_flow_ctrl(hw, rx, tx);
पूर्ण

अटल अंतरभूत व्योम port_cfg_change(काष्ठा ksz_hw *hw, काष्ठा ksz_port *port,
	काष्ठा ksz_port_info *info, u16 link_status)
अणु
	अगर ((hw->features & HALF_DUPLEX_SIGNAL_BUG) &&
			!(hw->overrides & PAUSE_FLOW_CTRL)) अणु
		u32 cfg = hw->tx_cfg;

		/* Disable flow control in the half duplex mode. */
		अगर (1 == info->duplex)
			hw->tx_cfg &= ~DMA_TX_FLOW_ENABLE;
		अगर (hw->enabled && cfg != hw->tx_cfg)
			ग_लिखोl(hw->tx_cfg, hw->io + KS_DMA_TX_CTRL);
	पूर्ण
पूर्ण

/**
 * port_get_link_speed - get current link status
 * @port: 	The port instance.
 *
 * This routine पढ़ोs PHY रेजिस्टरs to determine the current link status of the
 * चयन ports.
 */
अटल व्योम port_get_link_speed(काष्ठा ksz_port *port)
अणु
	uपूर्णांक पूर्णांकerrupt;
	काष्ठा ksz_port_info *info;
	काष्ठा ksz_port_info *linked = शून्य;
	काष्ठा ksz_hw *hw = port->hw;
	u16 data;
	u16 status;
	u8 local;
	u8 remote;
	पूर्णांक i;
	पूर्णांक p;
	पूर्णांक change = 0;

	पूर्णांकerrupt = hw_block_पूर्णांकr(hw);

	क्रम (i = 0, p = port->first_port; i < port->port_cnt; i++, p++) अणु
		info = &hw->port_info[p];
		port_r16(hw, p, KS884X_PORT_CTRL_4_OFFSET, &data);
		port_r16(hw, p, KS884X_PORT_STATUS_OFFSET, &status);

		/*
		 * Link status is changing all the समय even when there is no
		 * cable connection!
		 */
		remote = status & (PORT_AUTO_NEG_COMPLETE |
			PORT_STATUS_LINK_GOOD);
		local = (u8) data;

		/* No change to status. */
		अगर (local == info->advertised && remote == info->partner)
			जारी;

		info->advertised = local;
		info->partner = remote;
		अगर (status & PORT_STATUS_LINK_GOOD) अणु

			/* Remember the first linked port. */
			अगर (!linked)
				linked = info;

			info->tx_rate = 10 * TX_RATE_UNIT;
			अगर (status & PORT_STATUS_SPEED_100MBIT)
				info->tx_rate = 100 * TX_RATE_UNIT;

			info->duplex = 1;
			अगर (status & PORT_STATUS_FULL_DUPLEX)
				info->duplex = 2;

			अगर (media_connected != info->state) अणु
				hw_r_phy(hw, p, KS884X_PHY_AUTO_NEG_OFFSET,
					&data);
				hw_r_phy(hw, p, KS884X_PHY_REMOTE_CAP_OFFSET,
					&status);
				determine_flow_ctrl(hw, port, data, status);
				अगर (hw->ksz_चयन) अणु
					port_cfg_back_pressure(hw, p,
						(1 == info->duplex));
				पूर्ण
				change |= 1 << i;
				port_cfg_change(hw, port, info, status);
			पूर्ण
			info->state = media_connected;
		पूर्ण अन्यथा अणु
			अगर (media_disconnected != info->state) अणु
				change |= 1 << i;

				/* Indicate the link just goes करोwn. */
				hw->port_mib[p].link_करोwn = 1;
			पूर्ण
			info->state = media_disconnected;
		पूर्ण
		hw->port_mib[p].state = (u8) info->state;
	पूर्ण

	अगर (linked && media_disconnected == port->linked->state)
		port->linked = linked;

	hw_restore_पूर्णांकr(hw, पूर्णांकerrupt);
पूर्ण

#घोषणा PHY_RESET_TIMEOUT		10

/**
 * port_set_link_speed - set port speed
 * @port: 	The port instance.
 *
 * This routine sets the link speed of the चयन ports.
 */
अटल व्योम port_set_link_speed(काष्ठा ksz_port *port)
अणु
	काष्ठा ksz_hw *hw = port->hw;
	u16 data;
	u16 cfg;
	u8 status;
	पूर्णांक i;
	पूर्णांक p;

	क्रम (i = 0, p = port->first_port; i < port->port_cnt; i++, p++) अणु
		port_r16(hw, p, KS884X_PORT_CTRL_4_OFFSET, &data);
		port_r8(hw, p, KS884X_PORT_STATUS_OFFSET, &status);

		cfg = 0;
		अगर (status & PORT_STATUS_LINK_GOOD)
			cfg = data;

		data |= PORT_AUTO_NEG_ENABLE;
		data = advertised_flow_ctrl(port, data);

		data |= PORT_AUTO_NEG_100BTX_FD | PORT_AUTO_NEG_100BTX |
			PORT_AUTO_NEG_10BT_FD | PORT_AUTO_NEG_10BT;

		/* Check अगर manual configuration is specअगरied by the user. */
		अगर (port->speed || port->duplex) अणु
			अगर (10 == port->speed)
				data &= ~(PORT_AUTO_NEG_100BTX_FD |
					PORT_AUTO_NEG_100BTX);
			अन्यथा अगर (100 == port->speed)
				data &= ~(PORT_AUTO_NEG_10BT_FD |
					PORT_AUTO_NEG_10BT);
			अगर (1 == port->duplex)
				data &= ~(PORT_AUTO_NEG_100BTX_FD |
					PORT_AUTO_NEG_10BT_FD);
			अन्यथा अगर (2 == port->duplex)
				data &= ~(PORT_AUTO_NEG_100BTX |
					PORT_AUTO_NEG_10BT);
		पूर्ण
		अगर (data != cfg) अणु
			data |= PORT_AUTO_NEG_RESTART;
			port_w16(hw, p, KS884X_PORT_CTRL_4_OFFSET, data);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * port_क्रमce_link_speed - क्रमce port speed
 * @port: 	The port instance.
 *
 * This routine क्रमces the link speed of the चयन ports.
 */
अटल व्योम port_क्रमce_link_speed(काष्ठा ksz_port *port)
अणु
	काष्ठा ksz_hw *hw = port->hw;
	u16 data;
	पूर्णांक i;
	पूर्णांक phy;
	पूर्णांक p;

	क्रम (i = 0, p = port->first_port; i < port->port_cnt; i++, p++) अणु
		phy = KS884X_PHY_1_CTRL_OFFSET + p * PHY_CTRL_INTERVAL;
		hw_r_phy_ctrl(hw, phy, &data);

		data &= ~PHY_AUTO_NEG_ENABLE;

		अगर (10 == port->speed)
			data &= ~PHY_SPEED_100MBIT;
		अन्यथा अगर (100 == port->speed)
			data |= PHY_SPEED_100MBIT;
		अगर (1 == port->duplex)
			data &= ~PHY_FULL_DUPLEX;
		अन्यथा अगर (2 == port->duplex)
			data |= PHY_FULL_DUPLEX;
		hw_w_phy_ctrl(hw, phy, data);
	पूर्ण
पूर्ण

अटल व्योम port_set_घातer_saving(काष्ठा ksz_port *port, पूर्णांक enable)
अणु
	काष्ठा ksz_hw *hw = port->hw;
	पूर्णांक i;
	पूर्णांक p;

	क्रम (i = 0, p = port->first_port; i < port->port_cnt; i++, p++)
		port_cfg(hw, p,
			KS884X_PORT_CTRL_4_OFFSET, PORT_POWER_DOWN, enable);
पूर्ण

/*
 * KSZ8841 घातer management functions
 */

/**
 * hw_chk_wol_pme_status - check PMEN pin
 * @hw: 	The hardware instance.
 *
 * This function is used to check PMEN pin is निश्चितed.
 *
 * Return 1 अगर PMEN pin is निश्चितed; otherwise, 0.
 */
अटल पूर्णांक hw_chk_wol_pme_status(काष्ठा ksz_hw *hw)
अणु
	काष्ठा dev_info *hw_priv = container_of(hw, काष्ठा dev_info, hw);
	काष्ठा pci_dev *pdev = hw_priv->pdev;
	u16 data;

	अगर (!pdev->pm_cap)
		वापस 0;
	pci_पढ़ो_config_word(pdev, pdev->pm_cap + PCI_PM_CTRL, &data);
	वापस (data & PCI_PM_CTRL_PME_STATUS) == PCI_PM_CTRL_PME_STATUS;
पूर्ण

/**
 * hw_clr_wol_pme_status - clear PMEN pin
 * @hw: 	The hardware instance.
 *
 * This routine is used to clear PME_Status to deनिश्चित PMEN pin.
 */
अटल व्योम hw_clr_wol_pme_status(काष्ठा ksz_hw *hw)
अणु
	काष्ठा dev_info *hw_priv = container_of(hw, काष्ठा dev_info, hw);
	काष्ठा pci_dev *pdev = hw_priv->pdev;
	u16 data;

	अगर (!pdev->pm_cap)
		वापस;

	/* Clear PME_Status to deनिश्चित PMEN pin. */
	pci_पढ़ो_config_word(pdev, pdev->pm_cap + PCI_PM_CTRL, &data);
	data |= PCI_PM_CTRL_PME_STATUS;
	pci_ग_लिखो_config_word(pdev, pdev->pm_cap + PCI_PM_CTRL, data);
पूर्ण

/**
 * hw_cfg_wol_pme - enable or disable Wake-on-LAN
 * @hw: 	The hardware instance.
 * @set:	The flag indicating whether to enable or disable.
 *
 * This routine is used to enable or disable Wake-on-LAN.
 */
अटल व्योम hw_cfg_wol_pme(काष्ठा ksz_hw *hw, पूर्णांक set)
अणु
	काष्ठा dev_info *hw_priv = container_of(hw, काष्ठा dev_info, hw);
	काष्ठा pci_dev *pdev = hw_priv->pdev;
	u16 data;

	अगर (!pdev->pm_cap)
		वापस;
	pci_पढ़ो_config_word(pdev, pdev->pm_cap + PCI_PM_CTRL, &data);
	data &= ~PCI_PM_CTRL_STATE_MASK;
	अगर (set)
		data |= PCI_PM_CTRL_PME_ENABLE | PCI_D3hot;
	अन्यथा
		data &= ~PCI_PM_CTRL_PME_ENABLE;
	pci_ग_लिखो_config_word(pdev, pdev->pm_cap + PCI_PM_CTRL, data);
पूर्ण

/**
 * hw_cfg_wol - configure Wake-on-LAN features
 * @hw: 	The hardware instance.
 * @frame:	The pattern frame bit.
 * @set:	The flag indicating whether to enable or disable.
 *
 * This routine is used to enable or disable certain Wake-on-LAN features.
 */
अटल व्योम hw_cfg_wol(काष्ठा ksz_hw *hw, u16 frame, पूर्णांक set)
अणु
	u16 data;

	data = पढ़ोw(hw->io + KS8841_WOL_CTRL_OFFSET);
	अगर (set)
		data |= frame;
	अन्यथा
		data &= ~frame;
	ग_लिखोw(data, hw->io + KS8841_WOL_CTRL_OFFSET);
पूर्ण

/**
 * hw_set_wol_frame - program Wake-on-LAN pattern
 * @hw: 	The hardware instance.
 * @i:		The frame index.
 * @mask_size:	The size of the mask.
 * @mask:	Mask to ignore certain bytes in the pattern.
 * @frame_size:	The size of the frame.
 * @pattern:	The frame data.
 *
 * This routine is used to program Wake-on-LAN pattern.
 */
अटल व्योम hw_set_wol_frame(काष्ठा ksz_hw *hw, पूर्णांक i, uपूर्णांक mask_size,
	स्थिर u8 *mask, uपूर्णांक frame_size, स्थिर u8 *pattern)
अणु
	पूर्णांक bits;
	पूर्णांक from;
	पूर्णांक len;
	पूर्णांक to;
	u32 crc;
	u8 data[64];
	u8 val = 0;

	अगर (frame_size > mask_size * 8)
		frame_size = mask_size * 8;
	अगर (frame_size > 64)
		frame_size = 64;

	i *= 0x10;
	ग_लिखोl(0, hw->io + KS8841_WOL_FRAME_BYTE0_OFFSET + i);
	ग_लिखोl(0, hw->io + KS8841_WOL_FRAME_BYTE2_OFFSET + i);

	bits = len = from = to = 0;
	करो अणु
		अगर (bits) अणु
			अगर ((val & 1))
				data[to++] = pattern[from];
			val >>= 1;
			++from;
			--bits;
		पूर्ण अन्यथा अणु
			val = mask[len];
			ग_लिखोb(val, hw->io + KS8841_WOL_FRAME_BYTE0_OFFSET + i
				+ len);
			++len;
			अगर (val)
				bits = 8;
			अन्यथा
				from += 8;
		पूर्ण
	पूर्ण जबतक (from < (पूर्णांक) frame_size);
	अगर (val) अणु
		bits = mask[len - 1];
		val <<= (from % 8);
		bits &= ~val;
		ग_लिखोb(bits, hw->io + KS8841_WOL_FRAME_BYTE0_OFFSET + i + len -
			1);
	पूर्ण
	crc = ether_crc(to, data);
	ग_लिखोl(crc, hw->io + KS8841_WOL_FRAME_CRC_OFFSET + i);
पूर्ण

/**
 * hw_add_wol_arp - add ARP pattern
 * @hw: 	The hardware instance.
 * @ip_addr:	The IPv4 address asचिन्हित to the device.
 *
 * This routine is used to add ARP pattern क्रम waking up the host.
 */
अटल व्योम hw_add_wol_arp(काष्ठा ksz_hw *hw, स्थिर u8 *ip_addr)
अणु
	अटल स्थिर u8 mask[6] = अणु 0x3F, 0xF0, 0x3F, 0x00, 0xC0, 0x03 पूर्ण;
	u8 pattern[42] = अणु
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x08, 0x06,
		0x00, 0x01, 0x08, 0x00, 0x06, 0x04, 0x00, 0x01,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00 पूर्ण;

	स_नकल(&pattern[38], ip_addr, 4);
	hw_set_wol_frame(hw, 3, 6, mask, 42, pattern);
पूर्ण

/**
 * hw_add_wol_bcast - add broadcast pattern
 * @hw: 	The hardware instance.
 *
 * This routine is used to add broadcast pattern क्रम waking up the host.
 */
अटल व्योम hw_add_wol_bcast(काष्ठा ksz_hw *hw)
अणु
	अटल स्थिर u8 mask[] = अणु 0x3F पूर्ण;
	अटल स्थिर u8 pattern[] = अणु 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF पूर्ण;

	hw_set_wol_frame(hw, 2, 1, mask, ETH_ALEN, pattern);
पूर्ण

/**
 * hw_add_wol_mcast - add multicast pattern
 * @hw: 	The hardware instance.
 *
 * This routine is used to add multicast pattern क्रम waking up the host.
 *
 * It is assumed the multicast packet is the ICMPv6 neighbor solicitation used
 * by IPv6 ping command.  Note that multicast packets are filtred through the
 * multicast hash table, so not all multicast packets can wake up the host.
 */
अटल व्योम hw_add_wol_mcast(काष्ठा ksz_hw *hw)
अणु
	अटल स्थिर u8 mask[] = अणु 0x3F पूर्ण;
	u8 pattern[] = अणु 0x33, 0x33, 0xFF, 0x00, 0x00, 0x00 पूर्ण;

	स_नकल(&pattern[3], &hw->override_addr[3], 3);
	hw_set_wol_frame(hw, 1, 1, mask, 6, pattern);
पूर्ण

/**
 * hw_add_wol_ucast - add unicast pattern
 * @hw: 	The hardware instance.
 *
 * This routine is used to add unicast pattern to wakeup the host.
 *
 * It is assumed the unicast packet is directed to the device, as the hardware
 * can only receive them in normal हाल.
 */
अटल व्योम hw_add_wol_ucast(काष्ठा ksz_hw *hw)
अणु
	अटल स्थिर u8 mask[] = अणु 0x3F पूर्ण;

	hw_set_wol_frame(hw, 0, 1, mask, ETH_ALEN, hw->override_addr);
पूर्ण

/**
 * hw_enable_wol - enable Wake-on-LAN
 * @hw: 	The hardware instance.
 * @wol_enable:	The Wake-on-LAN settings.
 * @net_addr:	The IPv4 address asचिन्हित to the device.
 *
 * This routine is used to enable Wake-on-LAN depending on driver settings.
 */
अटल व्योम hw_enable_wol(काष्ठा ksz_hw *hw, u32 wol_enable, स्थिर u8 *net_addr)
अणु
	hw_cfg_wol(hw, KS8841_WOL_MAGIC_ENABLE, (wol_enable & WAKE_MAGIC));
	hw_cfg_wol(hw, KS8841_WOL_FRAME0_ENABLE, (wol_enable & WAKE_UCAST));
	hw_add_wol_ucast(hw);
	hw_cfg_wol(hw, KS8841_WOL_FRAME1_ENABLE, (wol_enable & WAKE_MCAST));
	hw_add_wol_mcast(hw);
	hw_cfg_wol(hw, KS8841_WOL_FRAME2_ENABLE, (wol_enable & WAKE_BCAST));
	hw_cfg_wol(hw, KS8841_WOL_FRAME3_ENABLE, (wol_enable & WAKE_ARP));
	hw_add_wol_arp(hw, net_addr);
पूर्ण

/**
 * hw_init - check driver is correct क्रम the hardware
 * @hw: 	The hardware instance.
 *
 * This function checks the hardware is correct क्रम this driver and sets the
 * hardware up क्रम proper initialization.
 *
 * Return number of ports or 0 अगर not right.
 */
अटल पूर्णांक hw_init(काष्ठा ksz_hw *hw)
अणु
	पूर्णांक rc = 0;
	u16 data;
	u16 revision;

	/* Set bus speed to 125MHz. */
	ग_लिखोw(BUS_SPEED_125_MHZ, hw->io + KS884X_BUS_CTRL_OFFSET);

	/* Check KSZ884x chip ID. */
	data = पढ़ोw(hw->io + KS884X_CHIP_ID_OFFSET);

	revision = (data & KS884X_REVISION_MASK) >> KS884X_REVISION_SHIFT;
	data &= KS884X_CHIP_ID_MASK_41;
	अगर (REG_CHIP_ID_41 == data)
		rc = 1;
	अन्यथा अगर (REG_CHIP_ID_42 == data)
		rc = 2;
	अन्यथा
		वापस 0;

	/* Setup hardware features or bug workarounds. */
	अगर (revision <= 1) अणु
		hw->features |= SMALL_PACKET_TX_BUG;
		अगर (1 == rc)
			hw->features |= HALF_DUPLEX_SIGNAL_BUG;
	पूर्ण
	वापस rc;
पूर्ण

/**
 * hw_reset - reset the hardware
 * @hw: 	The hardware instance.
 *
 * This routine resets the hardware.
 */
अटल व्योम hw_reset(काष्ठा ksz_hw *hw)
अणु
	ग_लिखोw(GLOBAL_SOFTWARE_RESET, hw->io + KS884X_GLOBAL_CTRL_OFFSET);

	/* Wait क्रम device to reset. */
	mdelay(10);

	/* Write 0 to clear device reset. */
	ग_लिखोw(0, hw->io + KS884X_GLOBAL_CTRL_OFFSET);
पूर्ण

/**
 * hw_setup - setup the hardware
 * @hw: 	The hardware instance.
 *
 * This routine setup the hardware क्रम proper operation.
 */
अटल व्योम hw_setup(काष्ठा ksz_hw *hw)
अणु
#अगर SET_DEFAULT_LED
	u16 data;

	/* Change शेष LED mode. */
	data = पढ़ोw(hw->io + KS8842_SWITCH_CTRL_5_OFFSET);
	data &= ~LED_MODE;
	data |= SET_DEFAULT_LED;
	ग_लिखोw(data, hw->io + KS8842_SWITCH_CTRL_5_OFFSET);
#पूर्ण_अगर

	/* Setup transmit control. */
	hw->tx_cfg = (DMA_TX_PAD_ENABLE | DMA_TX_CRC_ENABLE |
		(DMA_BURST_DEFAULT << DMA_BURST_SHIFT) | DMA_TX_ENABLE);

	/* Setup receive control. */
	hw->rx_cfg = (DMA_RX_BROADCAST | DMA_RX_UNICAST |
		(DMA_BURST_DEFAULT << DMA_BURST_SHIFT) | DMA_RX_ENABLE);
	hw->rx_cfg |= KS884X_DMA_RX_MULTICAST;

	/* Hardware cannot handle UDP packet in IP fragments. */
	hw->rx_cfg |= (DMA_RX_CSUM_TCP | DMA_RX_CSUM_IP);

	अगर (hw->all_multi)
		hw->rx_cfg |= DMA_RX_ALL_MULTICAST;
	अगर (hw->promiscuous)
		hw->rx_cfg |= DMA_RX_PROMISCUOUS;
पूर्ण

/**
 * hw_setup_पूर्णांकr - setup पूर्णांकerrupt mask
 * @hw: 	The hardware instance.
 *
 * This routine setup the पूर्णांकerrupt mask क्रम proper operation.
 */
अटल व्योम hw_setup_पूर्णांकr(काष्ठा ksz_hw *hw)
अणु
	hw->पूर्णांकr_mask = KS884X_INT_MASK | KS884X_INT_RX_OVERRUN;
पूर्ण

अटल व्योम ksz_check_desc_num(काष्ठा ksz_desc_info *info)
अणु
#घोषणा MIN_DESC_SHIFT  2

	पूर्णांक alloc = info->alloc;
	पूर्णांक shअगरt;

	shअगरt = 0;
	जबतक (!(alloc & 1)) अणु
		shअगरt++;
		alloc >>= 1;
	पूर्ण
	अगर (alloc != 1 || shअगरt < MIN_DESC_SHIFT) अणु
		pr_alert("Hardware descriptor numbers not right!\n");
		जबतक (alloc) अणु
			shअगरt++;
			alloc >>= 1;
		पूर्ण
		अगर (shअगरt < MIN_DESC_SHIFT)
			shअगरt = MIN_DESC_SHIFT;
		alloc = 1 << shअगरt;
		info->alloc = alloc;
	पूर्ण
	info->mask = info->alloc - 1;
पूर्ण

अटल व्योम hw_init_desc(काष्ठा ksz_desc_info *desc_info, पूर्णांक transmit)
अणु
	पूर्णांक i;
	u32 phys = desc_info->ring_phys;
	काष्ठा ksz_hw_desc *desc = desc_info->ring_virt;
	काष्ठा ksz_desc *cur = desc_info->ring;
	काष्ठा ksz_desc *previous = शून्य;

	क्रम (i = 0; i < desc_info->alloc; i++) अणु
		cur->phw = desc++;
		phys += desc_info->size;
		previous = cur++;
		previous->phw->next = cpu_to_le32(phys);
	पूर्ण
	previous->phw->next = cpu_to_le32(desc_info->ring_phys);
	previous->sw.buf.rx.end_of_ring = 1;
	previous->phw->buf.data = cpu_to_le32(previous->sw.buf.data);

	desc_info->avail = desc_info->alloc;
	desc_info->last = desc_info->next = 0;

	desc_info->cur = desc_info->ring;
पूर्ण

/**
 * hw_set_desc_base - set descriptor base addresses
 * @hw: 	The hardware instance.
 * @tx_addr:	The transmit descriptor base.
 * @rx_addr:	The receive descriptor base.
 *
 * This routine programs the descriptor base addresses after reset.
 */
अटल व्योम hw_set_desc_base(काष्ठा ksz_hw *hw, u32 tx_addr, u32 rx_addr)
अणु
	/* Set base address of Tx/Rx descriptors. */
	ग_लिखोl(tx_addr, hw->io + KS_DMA_TX_ADDR);
	ग_लिखोl(rx_addr, hw->io + KS_DMA_RX_ADDR);
पूर्ण

अटल व्योम hw_reset_pkts(काष्ठा ksz_desc_info *info)
अणु
	info->cur = info->ring;
	info->avail = info->alloc;
	info->last = info->next = 0;
पूर्ण

अटल अंतरभूत व्योम hw_resume_rx(काष्ठा ksz_hw *hw)
अणु
	ग_लिखोl(DMA_START, hw->io + KS_DMA_RX_START);
पूर्ण

/**
 * hw_start_rx - start receiving
 * @hw: 	The hardware instance.
 *
 * This routine starts the receive function of the hardware.
 */
अटल व्योम hw_start_rx(काष्ठा ksz_hw *hw)
अणु
	ग_लिखोl(hw->rx_cfg, hw->io + KS_DMA_RX_CTRL);

	/* Notअगरy when the receive stops. */
	hw->पूर्णांकr_mask |= KS884X_INT_RX_STOPPED;

	ग_लिखोl(DMA_START, hw->io + KS_DMA_RX_START);
	hw_ack_पूर्णांकr(hw, KS884X_INT_RX_STOPPED);
	hw->rx_stop++;

	/* Variable overflows. */
	अगर (0 == hw->rx_stop)
		hw->rx_stop = 2;
पूर्ण

/**
 * hw_stop_rx - stop receiving
 * @hw: 	The hardware instance.
 *
 * This routine stops the receive function of the hardware.
 */
अटल व्योम hw_stop_rx(काष्ठा ksz_hw *hw)
अणु
	hw->rx_stop = 0;
	hw_turn_off_पूर्णांकr(hw, KS884X_INT_RX_STOPPED);
	ग_लिखोl((hw->rx_cfg & ~DMA_RX_ENABLE), hw->io + KS_DMA_RX_CTRL);
पूर्ण

/**
 * hw_start_tx - start transmitting
 * @hw: 	The hardware instance.
 *
 * This routine starts the transmit function of the hardware.
 */
अटल व्योम hw_start_tx(काष्ठा ksz_hw *hw)
अणु
	ग_लिखोl(hw->tx_cfg, hw->io + KS_DMA_TX_CTRL);
पूर्ण

/**
 * hw_stop_tx - stop transmitting
 * @hw: 	The hardware instance.
 *
 * This routine stops the transmit function of the hardware.
 */
अटल व्योम hw_stop_tx(काष्ठा ksz_hw *hw)
अणु
	ग_लिखोl((hw->tx_cfg & ~DMA_TX_ENABLE), hw->io + KS_DMA_TX_CTRL);
पूर्ण

/**
 * hw_disable - disable hardware
 * @hw: 	The hardware instance.
 *
 * This routine disables the hardware.
 */
अटल व्योम hw_disable(काष्ठा ksz_hw *hw)
अणु
	hw_stop_rx(hw);
	hw_stop_tx(hw);
	hw->enabled = 0;
पूर्ण

/**
 * hw_enable - enable hardware
 * @hw: 	The hardware instance.
 *
 * This routine enables the hardware.
 */
अटल व्योम hw_enable(काष्ठा ksz_hw *hw)
अणु
	hw_start_tx(hw);
	hw_start_rx(hw);
	hw->enabled = 1;
पूर्ण

/**
 * hw_alloc_pkt - allocate enough descriptors क्रम transmission
 * @hw: 	The hardware instance.
 * @length:	The length of the packet.
 * @physical:	Number of descriptors required.
 *
 * This function allocates descriptors क्रम transmission.
 *
 * Return 0 अगर not successful; 1 क्रम buffer copy; or number of descriptors.
 */
अटल पूर्णांक hw_alloc_pkt(काष्ठा ksz_hw *hw, पूर्णांक length, पूर्णांक physical)
अणु
	/* Always leave one descriptor मुक्त. */
	अगर (hw->tx_desc_info.avail <= 1)
		वापस 0;

	/* Allocate a descriptor क्रम transmission and mark it current. */
	get_tx_pkt(&hw->tx_desc_info, &hw->tx_desc_info.cur);
	hw->tx_desc_info.cur->sw.buf.tx.first_seg = 1;

	/* Keep track of number of transmit descriptors used so far. */
	++hw->tx_पूर्णांक_cnt;
	hw->tx_size += length;

	/* Cannot hold on too much data. */
	अगर (hw->tx_size >= MAX_TX_HELD_SIZE)
		hw->tx_पूर्णांक_cnt = hw->tx_पूर्णांक_mask + 1;

	अगर (physical > hw->tx_desc_info.avail)
		वापस 1;

	वापस hw->tx_desc_info.avail;
पूर्ण

/**
 * hw_send_pkt - mark packet क्रम transmission
 * @hw: 	The hardware instance.
 *
 * This routine marks the packet क्रम transmission in PCI version.
 */
अटल व्योम hw_send_pkt(काष्ठा ksz_hw *hw)
अणु
	काष्ठा ksz_desc *cur = hw->tx_desc_info.cur;

	cur->sw.buf.tx.last_seg = 1;

	/* Interrupt only after specअगरied number of descriptors used. */
	अगर (hw->tx_पूर्णांक_cnt > hw->tx_पूर्णांक_mask) अणु
		cur->sw.buf.tx.पूर्णांकr = 1;
		hw->tx_पूर्णांक_cnt = 0;
		hw->tx_size = 0;
	पूर्ण

	/* KSZ8842 supports port directed transmission. */
	cur->sw.buf.tx.dest_port = hw->dst_ports;

	release_desc(cur);

	ग_लिखोl(0, hw->io + KS_DMA_TX_START);
पूर्ण

अटल पूर्णांक empty_addr(u8 *addr)
अणु
	u32 *addr1 = (u32 *) addr;
	u16 *addr2 = (u16 *) &addr[4];

	वापस 0 == *addr1 && 0 == *addr2;
पूर्ण

/**
 * hw_set_addr - set MAC address
 * @hw: 	The hardware instance.
 *
 * This routine programs the MAC address of the hardware when the address is
 * overridden.
 */
अटल व्योम hw_set_addr(काष्ठा ksz_hw *hw)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ETH_ALEN; i++)
		ग_लिखोb(hw->override_addr[MAC_ADDR_ORDER(i)],
			hw->io + KS884X_ADDR_0_OFFSET + i);

	sw_set_addr(hw, hw->override_addr);
पूर्ण

/**
 * hw_पढ़ो_addr - पढ़ो MAC address
 * @hw: 	The hardware instance.
 *
 * This routine retrieves the MAC address of the hardware.
 */
अटल व्योम hw_पढ़ो_addr(काष्ठा ksz_hw *hw)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ETH_ALEN; i++)
		hw->perm_addr[MAC_ADDR_ORDER(i)] = पढ़ोb(hw->io +
			KS884X_ADDR_0_OFFSET + i);

	अगर (!hw->mac_override) अणु
		स_नकल(hw->override_addr, hw->perm_addr, ETH_ALEN);
		अगर (empty_addr(hw->override_addr)) अणु
			स_नकल(hw->perm_addr, DEFAULT_MAC_ADDRESS, ETH_ALEN);
			स_नकल(hw->override_addr, DEFAULT_MAC_ADDRESS,
			       ETH_ALEN);
			hw->override_addr[5] += hw->id;
			hw_set_addr(hw);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम hw_ena_add_addr(काष्ठा ksz_hw *hw, पूर्णांक index, u8 *mac_addr)
अणु
	पूर्णांक i;
	u32 mac_addr_lo;
	u32 mac_addr_hi;

	mac_addr_hi = 0;
	क्रम (i = 0; i < 2; i++) अणु
		mac_addr_hi <<= 8;
		mac_addr_hi |= mac_addr[i];
	पूर्ण
	mac_addr_hi |= ADD_ADDR_ENABLE;
	mac_addr_lo = 0;
	क्रम (i = 2; i < 6; i++) अणु
		mac_addr_lo <<= 8;
		mac_addr_lo |= mac_addr[i];
	पूर्ण
	index *= ADD_ADDR_INCR;

	ग_लिखोl(mac_addr_lo, hw->io + index + KS_ADD_ADDR_0_LO);
	ग_लिखोl(mac_addr_hi, hw->io + index + KS_ADD_ADDR_0_HI);
पूर्ण

अटल व्योम hw_set_add_addr(काष्ठा ksz_hw *hw)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ADDITIONAL_ENTRIES; i++) अणु
		अगर (empty_addr(hw->address[i]))
			ग_लिखोl(0, hw->io + ADD_ADDR_INCR * i +
				KS_ADD_ADDR_0_HI);
		अन्यथा
			hw_ena_add_addr(hw, i, hw->address[i]);
	पूर्ण
पूर्ण

अटल पूर्णांक hw_add_addr(काष्ठा ksz_hw *hw, u8 *mac_addr)
अणु
	पूर्णांक i;
	पूर्णांक j = ADDITIONAL_ENTRIES;

	अगर (ether_addr_equal(hw->override_addr, mac_addr))
		वापस 0;
	क्रम (i = 0; i < hw->addr_list_size; i++) अणु
		अगर (ether_addr_equal(hw->address[i], mac_addr))
			वापस 0;
		अगर (ADDITIONAL_ENTRIES == j && empty_addr(hw->address[i]))
			j = i;
	पूर्ण
	अगर (j < ADDITIONAL_ENTRIES) अणु
		स_नकल(hw->address[j], mac_addr, ETH_ALEN);
		hw_ena_add_addr(hw, j, hw->address[j]);
		वापस 0;
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक hw_del_addr(काष्ठा ksz_hw *hw, u8 *mac_addr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < hw->addr_list_size; i++) अणु
		अगर (ether_addr_equal(hw->address[i], mac_addr)) अणु
			eth_zero_addr(hw->address[i]);
			ग_लिखोl(0, hw->io + ADD_ADDR_INCR * i +
				KS_ADD_ADDR_0_HI);
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -1;
पूर्ण

/**
 * hw_clr_multicast - clear multicast addresses
 * @hw: 	The hardware instance.
 *
 * This routine हटाओs all multicast addresses set in the hardware.
 */
अटल व्योम hw_clr_multicast(काष्ठा ksz_hw *hw)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < HW_MULTICAST_SIZE; i++) अणु
		hw->multi_bits[i] = 0;

		ग_लिखोb(0, hw->io + KS884X_MULTICAST_0_OFFSET + i);
	पूर्ण
पूर्ण

/**
 * hw_set_grp_addr - set multicast addresses
 * @hw: 	The hardware instance.
 *
 * This routine programs multicast addresses क्रम the hardware to accept those
 * addresses.
 */
अटल व्योम hw_set_grp_addr(काष्ठा ksz_hw *hw)
अणु
	पूर्णांक i;
	पूर्णांक index;
	पूर्णांक position;
	पूर्णांक value;

	स_रखो(hw->multi_bits, 0, माप(u8) * HW_MULTICAST_SIZE);

	क्रम (i = 0; i < hw->multi_list_size; i++) अणु
		position = (ether_crc(6, hw->multi_list[i]) >> 26) & 0x3f;
		index = position >> 3;
		value = 1 << (position & 7);
		hw->multi_bits[index] |= (u8) value;
	पूर्ण

	क्रम (i = 0; i < HW_MULTICAST_SIZE; i++)
		ग_लिखोb(hw->multi_bits[i], hw->io + KS884X_MULTICAST_0_OFFSET +
			i);
पूर्ण

/**
 * hw_set_multicast - enable or disable all multicast receiving
 * @hw: 	The hardware instance.
 * @multicast:	To turn on or off the all multicast feature.
 *
 * This routine enables/disables the hardware to accept all multicast packets.
 */
अटल व्योम hw_set_multicast(काष्ठा ksz_hw *hw, u8 multicast)
अणु
	/* Stop receiving क्रम reconfiguration. */
	hw_stop_rx(hw);

	अगर (multicast)
		hw->rx_cfg |= DMA_RX_ALL_MULTICAST;
	अन्यथा
		hw->rx_cfg &= ~DMA_RX_ALL_MULTICAST;

	अगर (hw->enabled)
		hw_start_rx(hw);
पूर्ण

/**
 * hw_set_promiscuous - enable or disable promiscuous receiving
 * @hw: 	The hardware instance.
 * @prom:	To turn on or off the promiscuous feature.
 *
 * This routine enables/disables the hardware to accept all packets.
 */
अटल व्योम hw_set_promiscuous(काष्ठा ksz_hw *hw, u8 prom)
अणु
	/* Stop receiving क्रम reconfiguration. */
	hw_stop_rx(hw);

	अगर (prom)
		hw->rx_cfg |= DMA_RX_PROMISCUOUS;
	अन्यथा
		hw->rx_cfg &= ~DMA_RX_PROMISCUOUS;

	अगर (hw->enabled)
		hw_start_rx(hw);
पूर्ण

/**
 * sw_enable - enable the चयन
 * @hw: 	The hardware instance.
 * @enable:	The flag to enable or disable the चयन
 *
 * This routine is used to enable/disable the चयन in KSZ8842.
 */
अटल व्योम sw_enable(काष्ठा ksz_hw *hw, पूर्णांक enable)
अणु
	पूर्णांक port;

	क्रम (port = 0; port < SWITCH_PORT_NUM; port++) अणु
		अगर (hw->dev_count > 1) अणु
			/* Set port-base vlan membership with host port. */
			sw_cfg_port_base_vlan(hw, port,
				HOST_MASK | (1 << port));
			port_set_stp_state(hw, port, STP_STATE_DISABLED);
		पूर्ण अन्यथा अणु
			sw_cfg_port_base_vlan(hw, port, PORT_MASK);
			port_set_stp_state(hw, port, STP_STATE_FORWARDING);
		पूर्ण
	पूर्ण
	अगर (hw->dev_count > 1)
		port_set_stp_state(hw, SWITCH_PORT_NUM, STP_STATE_SIMPLE);
	अन्यथा
		port_set_stp_state(hw, SWITCH_PORT_NUM, STP_STATE_FORWARDING);

	अगर (enable)
		enable = KS8842_START;
	ग_लिखोw(enable, hw->io + KS884X_CHIP_ID_OFFSET);
पूर्ण

/**
 * sw_setup - setup the चयन
 * @hw: 	The hardware instance.
 *
 * This routine setup the hardware चयन engine क्रम शेष operation.
 */
अटल व्योम sw_setup(काष्ठा ksz_hw *hw)
अणु
	पूर्णांक port;

	sw_set_global_ctrl(hw);

	/* Enable चयन broadcast storm protection at 10% percent rate. */
	sw_init_broad_storm(hw);
	hw_cfg_broad_storm(hw, BROADCAST_STORM_PROTECTION_RATE);
	क्रम (port = 0; port < SWITCH_PORT_NUM; port++)
		sw_ena_broad_storm(hw, port);

	sw_init_prio(hw);

	sw_init_mirror(hw);

	sw_init_prio_rate(hw);

	sw_init_vlan(hw);

	अगर (hw->features & STP_SUPPORT)
		sw_init_stp(hw);
	अगर (!sw_chk(hw, KS8842_SWITCH_CTRL_1_OFFSET,
			SWITCH_TX_FLOW_CTRL | SWITCH_RX_FLOW_CTRL))
		hw->overrides |= PAUSE_FLOW_CTRL;
	sw_enable(hw, 1);
पूर्ण

/**
 * ksz_start_समयr - start kernel समयr
 * @info:	Kernel समयr inक्रमmation.
 * @समय:	The समय tick.
 *
 * This routine starts the kernel समयr after the specअगरied समय tick.
 */
अटल व्योम ksz_start_समयr(काष्ठा ksz_समयr_info *info, पूर्णांक समय)
अणु
	info->cnt = 0;
	info->समयr.expires = jअगरfies + समय;
	add_समयr(&info->समयr);

	/* infinity */
	info->max = -1;
पूर्ण

/**
 * ksz_stop_समयr - stop kernel समयr
 * @info:	Kernel समयr inक्रमmation.
 *
 * This routine stops the kernel समयr.
 */
अटल व्योम ksz_stop_समयr(काष्ठा ksz_समयr_info *info)
अणु
	अगर (info->max) अणु
		info->max = 0;
		del_समयr_sync(&info->समयr);
	पूर्ण
पूर्ण

अटल व्योम ksz_init_समयr(काष्ठा ksz_समयr_info *info, पूर्णांक period,
	व्योम (*function)(काष्ठा समयr_list *))
अणु
	info->max = 0;
	info->period = period;
	समयr_setup(&info->समयr, function, 0);
पूर्ण

अटल व्योम ksz_update_समयr(काष्ठा ksz_समयr_info *info)
अणु
	++info->cnt;
	अगर (info->max > 0) अणु
		अगर (info->cnt < info->max) अणु
			info->समयr.expires = jअगरfies + info->period;
			add_समयr(&info->समयr);
		पूर्ण अन्यथा
			info->max = 0;
	पूर्ण अन्यथा अगर (info->max < 0) अणु
		info->समयr.expires = jअगरfies + info->period;
		add_समयr(&info->समयr);
	पूर्ण
पूर्ण

/**
 * ksz_alloc_soft_desc - allocate software descriptors
 * @desc_info:	Descriptor inक्रमmation काष्ठाure.
 * @transmit:	Indication that descriptors are क्रम transmit.
 *
 * This local function allocates software descriptors क्रम manipulation in
 * memory.
 *
 * Return 0 अगर successful.
 */
अटल पूर्णांक ksz_alloc_soft_desc(काष्ठा ksz_desc_info *desc_info, पूर्णांक transmit)
अणु
	desc_info->ring = kसुस्मृति(desc_info->alloc, माप(काष्ठा ksz_desc),
				  GFP_KERNEL);
	अगर (!desc_info->ring)
		वापस 1;
	hw_init_desc(desc_info, transmit);
	वापस 0;
पूर्ण

/**
 * ksz_alloc_desc - allocate hardware descriptors
 * @adapter:	Adapter inक्रमmation काष्ठाure.
 *
 * This local function allocates hardware descriptors क्रम receiving and
 * transmitting.
 *
 * Return 0 अगर successful.
 */
अटल पूर्णांक ksz_alloc_desc(काष्ठा dev_info *adapter)
अणु
	काष्ठा ksz_hw *hw = &adapter->hw;
	पूर्णांक offset;

	/* Allocate memory क्रम RX & TX descriptors. */
	adapter->desc_pool.alloc_size =
		hw->rx_desc_info.size * hw->rx_desc_info.alloc +
		hw->tx_desc_info.size * hw->tx_desc_info.alloc +
		DESC_ALIGNMENT;

	adapter->desc_pool.alloc_virt =
		dma_alloc_coherent(&adapter->pdev->dev,
				   adapter->desc_pool.alloc_size,
				   &adapter->desc_pool.dma_addr, GFP_KERNEL);
	अगर (adapter->desc_pool.alloc_virt == शून्य) अणु
		adapter->desc_pool.alloc_size = 0;
		वापस 1;
	पूर्ण

	/* Align to the next cache line boundary. */
	offset = (((uदीर्घ) adapter->desc_pool.alloc_virt % DESC_ALIGNMENT) ?
		(DESC_ALIGNMENT -
		((uदीर्घ) adapter->desc_pool.alloc_virt % DESC_ALIGNMENT)) : 0);
	adapter->desc_pool.virt = adapter->desc_pool.alloc_virt + offset;
	adapter->desc_pool.phys = adapter->desc_pool.dma_addr + offset;

	/* Allocate receive/transmit descriptors. */
	hw->rx_desc_info.ring_virt = (काष्ठा ksz_hw_desc *)
		adapter->desc_pool.virt;
	hw->rx_desc_info.ring_phys = adapter->desc_pool.phys;
	offset = hw->rx_desc_info.alloc * hw->rx_desc_info.size;
	hw->tx_desc_info.ring_virt = (काष्ठा ksz_hw_desc *)
		(adapter->desc_pool.virt + offset);
	hw->tx_desc_info.ring_phys = adapter->desc_pool.phys + offset;

	अगर (ksz_alloc_soft_desc(&hw->rx_desc_info, 0))
		वापस 1;
	अगर (ksz_alloc_soft_desc(&hw->tx_desc_info, 1))
		वापस 1;

	वापस 0;
पूर्ण

/**
 * मुक्त_dma_buf - release DMA buffer resources
 * @adapter:	Adapter inक्रमmation काष्ठाure.
 * @dma_buf:	poपूर्णांकer to buf
 * @direction:	to or from device
 *
 * This routine is just a helper function to release the DMA buffer resources.
 */
अटल व्योम मुक्त_dma_buf(काष्ठा dev_info *adapter, काष्ठा ksz_dma_buf *dma_buf,
	पूर्णांक direction)
अणु
	dma_unmap_single(&adapter->pdev->dev, dma_buf->dma, dma_buf->len,
			 direction);
	dev_kमुक्त_skb(dma_buf->skb);
	dma_buf->skb = शून्य;
	dma_buf->dma = 0;
पूर्ण

/**
 * ksz_init_rx_buffers - initialize receive descriptors
 * @adapter:	Adapter inक्रमmation काष्ठाure.
 *
 * This routine initializes DMA buffers क्रम receiving.
 */
अटल व्योम ksz_init_rx_buffers(काष्ठा dev_info *adapter)
अणु
	पूर्णांक i;
	काष्ठा ksz_desc *desc;
	काष्ठा ksz_dma_buf *dma_buf;
	काष्ठा ksz_hw *hw = &adapter->hw;
	काष्ठा ksz_desc_info *info = &hw->rx_desc_info;

	क्रम (i = 0; i < hw->rx_desc_info.alloc; i++) अणु
		get_rx_pkt(info, &desc);

		dma_buf = DMA_BUFFER(desc);
		अगर (dma_buf->skb && dma_buf->len != adapter->mtu)
			मुक्त_dma_buf(adapter, dma_buf, DMA_FROM_DEVICE);
		dma_buf->len = adapter->mtu;
		अगर (!dma_buf->skb)
			dma_buf->skb = alloc_skb(dma_buf->len, GFP_ATOMIC);
		अगर (dma_buf->skb && !dma_buf->dma)
			dma_buf->dma = dma_map_single(&adapter->pdev->dev,
						skb_tail_poपूर्णांकer(dma_buf->skb),
						dma_buf->len,
						DMA_FROM_DEVICE);

		/* Set descriptor. */
		set_rx_buf(desc, dma_buf->dma);
		set_rx_len(desc, dma_buf->len);
		release_desc(desc);
	पूर्ण
पूर्ण

/**
 * ksz_alloc_mem - allocate memory क्रम hardware descriptors
 * @adapter:	Adapter inक्रमmation काष्ठाure.
 *
 * This function allocates memory क्रम use by hardware descriptors क्रम receiving
 * and transmitting.
 *
 * Return 0 अगर successful.
 */
अटल पूर्णांक ksz_alloc_mem(काष्ठा dev_info *adapter)
अणु
	काष्ठा ksz_hw *hw = &adapter->hw;

	/* Determine the number of receive and transmit descriptors. */
	hw->rx_desc_info.alloc = NUM_OF_RX_DESC;
	hw->tx_desc_info.alloc = NUM_OF_TX_DESC;

	/* Determine how many descriptors to skip transmit पूर्णांकerrupt. */
	hw->tx_पूर्णांक_cnt = 0;
	hw->tx_पूर्णांक_mask = NUM_OF_TX_DESC / 4;
	अगर (hw->tx_पूर्णांक_mask > 8)
		hw->tx_पूर्णांक_mask = 8;
	जबतक (hw->tx_पूर्णांक_mask) अणु
		hw->tx_पूर्णांक_cnt++;
		hw->tx_पूर्णांक_mask >>= 1;
	पूर्ण
	अगर (hw->tx_पूर्णांक_cnt) अणु
		hw->tx_पूर्णांक_mask = (1 << (hw->tx_पूर्णांक_cnt - 1)) - 1;
		hw->tx_पूर्णांक_cnt = 0;
	पूर्ण

	/* Determine the descriptor size. */
	hw->rx_desc_info.size =
		(((माप(काष्ठा ksz_hw_desc) + DESC_ALIGNMENT - 1) /
		DESC_ALIGNMENT) * DESC_ALIGNMENT);
	hw->tx_desc_info.size =
		(((माप(काष्ठा ksz_hw_desc) + DESC_ALIGNMENT - 1) /
		DESC_ALIGNMENT) * DESC_ALIGNMENT);
	अगर (hw->rx_desc_info.size != माप(काष्ठा ksz_hw_desc))
		pr_alert("Hardware descriptor size not right!\n");
	ksz_check_desc_num(&hw->rx_desc_info);
	ksz_check_desc_num(&hw->tx_desc_info);

	/* Allocate descriptors. */
	अगर (ksz_alloc_desc(adapter))
		वापस 1;

	वापस 0;
पूर्ण

/**
 * ksz_मुक्त_desc - मुक्त software and hardware descriptors
 * @adapter:	Adapter inक्रमmation काष्ठाure.
 *
 * This local routine मुक्तs the software and hardware descriptors allocated by
 * ksz_alloc_desc().
 */
अटल व्योम ksz_मुक्त_desc(काष्ठा dev_info *adapter)
अणु
	काष्ठा ksz_hw *hw = &adapter->hw;

	/* Reset descriptor. */
	hw->rx_desc_info.ring_virt = शून्य;
	hw->tx_desc_info.ring_virt = शून्य;
	hw->rx_desc_info.ring_phys = 0;
	hw->tx_desc_info.ring_phys = 0;

	/* Free memory. */
	अगर (adapter->desc_pool.alloc_virt)
		dma_मुक्त_coherent(&adapter->pdev->dev,
				  adapter->desc_pool.alloc_size,
				  adapter->desc_pool.alloc_virt,
				  adapter->desc_pool.dma_addr);

	/* Reset resource pool. */
	adapter->desc_pool.alloc_size = 0;
	adapter->desc_pool.alloc_virt = शून्य;

	kमुक्त(hw->rx_desc_info.ring);
	hw->rx_desc_info.ring = शून्य;
	kमुक्त(hw->tx_desc_info.ring);
	hw->tx_desc_info.ring = शून्य;
पूर्ण

/**
 * ksz_मुक्त_buffers - मुक्त buffers used in the descriptors
 * @adapter:	Adapter inक्रमmation काष्ठाure.
 * @desc_info:	Descriptor inक्रमmation काष्ठाure.
 * @direction:	to or from device
 *
 * This local routine मुक्तs buffers used in the DMA buffers.
 */
अटल व्योम ksz_मुक्त_buffers(काष्ठा dev_info *adapter,
	काष्ठा ksz_desc_info *desc_info, पूर्णांक direction)
अणु
	पूर्णांक i;
	काष्ठा ksz_dma_buf *dma_buf;
	काष्ठा ksz_desc *desc = desc_info->ring;

	क्रम (i = 0; i < desc_info->alloc; i++) अणु
		dma_buf = DMA_BUFFER(desc);
		अगर (dma_buf->skb)
			मुक्त_dma_buf(adapter, dma_buf, direction);
		desc++;
	पूर्ण
पूर्ण

/**
 * ksz_मुक्त_mem - मुक्त all resources used by descriptors
 * @adapter:	Adapter inक्रमmation काष्ठाure.
 *
 * This local routine मुक्तs all the resources allocated by ksz_alloc_mem().
 */
अटल व्योम ksz_मुक्त_mem(काष्ठा dev_info *adapter)
अणु
	/* Free transmit buffers. */
	ksz_मुक्त_buffers(adapter, &adapter->hw.tx_desc_info, DMA_TO_DEVICE);

	/* Free receive buffers. */
	ksz_मुक्त_buffers(adapter, &adapter->hw.rx_desc_info, DMA_FROM_DEVICE);

	/* Free descriptors. */
	ksz_मुक्त_desc(adapter);
पूर्ण

अटल व्योम get_mib_counters(काष्ठा ksz_hw *hw, पूर्णांक first, पूर्णांक cnt,
	u64 *counter)
अणु
	पूर्णांक i;
	पूर्णांक mib;
	पूर्णांक port;
	काष्ठा ksz_port_mib *port_mib;

	स_रखो(counter, 0, माप(u64) * TOTAL_PORT_COUNTER_NUM);
	क्रम (i = 0, port = first; i < cnt; i++, port++) अणु
		port_mib = &hw->port_mib[port];
		क्रम (mib = port_mib->mib_start; mib < hw->mib_cnt; mib++)
			counter[mib] += port_mib->counter[mib];
	पूर्ण
पूर्ण

/**
 * send_packet - send packet
 * @skb:	Socket buffer.
 * @dev:	Network device.
 *
 * This routine is used to send a packet out to the network.
 */
अटल व्योम send_packet(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा ksz_desc *desc;
	काष्ठा ksz_desc *first;
	काष्ठा dev_priv *priv = netdev_priv(dev);
	काष्ठा dev_info *hw_priv = priv->adapter;
	काष्ठा ksz_hw *hw = &hw_priv->hw;
	काष्ठा ksz_desc_info *info = &hw->tx_desc_info;
	काष्ठा ksz_dma_buf *dma_buf;
	पूर्णांक len;
	पूर्णांक last_frag = skb_shinfo(skb)->nr_frags;

	/*
	 * KSZ8842 with multiple device पूर्णांकerfaces needs to be told which port
	 * to send.
	 */
	अगर (hw->dev_count > 1)
		hw->dst_ports = 1 << priv->port.first_port;

	/* Hardware will pad the length to 60. */
	len = skb->len;

	/* Remember the very first descriptor. */
	first = info->cur;
	desc = first;

	dma_buf = DMA_BUFFER(desc);
	अगर (last_frag) अणु
		पूर्णांक frag;
		skb_frag_t *this_frag;

		dma_buf->len = skb_headlen(skb);

		dma_buf->dma = dma_map_single(&hw_priv->pdev->dev, skb->data,
					      dma_buf->len, DMA_TO_DEVICE);
		set_tx_buf(desc, dma_buf->dma);
		set_tx_len(desc, dma_buf->len);

		frag = 0;
		करो अणु
			this_frag = &skb_shinfo(skb)->frags[frag];

			/* Get a new descriptor. */
			get_tx_pkt(info, &desc);

			/* Keep track of descriptors used so far. */
			++hw->tx_पूर्णांक_cnt;

			dma_buf = DMA_BUFFER(desc);
			dma_buf->len = skb_frag_size(this_frag);

			dma_buf->dma = dma_map_single(&hw_priv->pdev->dev,
						      skb_frag_address(this_frag),
						      dma_buf->len,
						      DMA_TO_DEVICE);
			set_tx_buf(desc, dma_buf->dma);
			set_tx_len(desc, dma_buf->len);

			frag++;
			अगर (frag == last_frag)
				अवरोध;

			/* Do not release the last descriptor here. */
			release_desc(desc);
		पूर्ण जबतक (1);

		/* current poपूर्णांकs to the last descriptor. */
		info->cur = desc;

		/* Release the first descriptor. */
		release_desc(first);
	पूर्ण अन्यथा अणु
		dma_buf->len = len;

		dma_buf->dma = dma_map_single(&hw_priv->pdev->dev, skb->data,
					      dma_buf->len, DMA_TO_DEVICE);
		set_tx_buf(desc, dma_buf->dma);
		set_tx_len(desc, dma_buf->len);
	पूर्ण

	अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		(desc)->sw.buf.tx.csum_gen_tcp = 1;
		(desc)->sw.buf.tx.csum_gen_udp = 1;
	पूर्ण

	/*
	 * The last descriptor holds the packet so that it can be वापसed to
	 * network subप्रणाली after all descriptors are transmitted.
	 */
	dma_buf->skb = skb;

	hw_send_pkt(hw);

	/* Update transmit statistics. */
	dev->stats.tx_packets++;
	dev->stats.tx_bytes += len;
पूर्ण

/**
 * transmit_cleanup - clean up transmit descriptors
 * @hw_priv:	Network device.
 * @normal:	अवरोध अगर owned
 *
 * This routine is called to clean up the transmitted buffers.
 */
अटल व्योम transmit_cleanup(काष्ठा dev_info *hw_priv, पूर्णांक normal)
अणु
	पूर्णांक last;
	जोड़ desc_stat status;
	काष्ठा ksz_hw *hw = &hw_priv->hw;
	काष्ठा ksz_desc_info *info = &hw->tx_desc_info;
	काष्ठा ksz_desc *desc;
	काष्ठा ksz_dma_buf *dma_buf;
	काष्ठा net_device *dev = शून्य;

	spin_lock_irq(&hw_priv->hwlock);
	last = info->last;

	जबतक (info->avail < info->alloc) अणु
		/* Get next descriptor which is not hardware owned. */
		desc = &info->ring[last];
		status.data = le32_to_cpu(desc->phw->ctrl.data);
		अगर (status.tx.hw_owned) अणु
			अगर (normal)
				अवरोध;
			अन्यथा
				reset_desc(desc, status);
		पूर्ण

		dma_buf = DMA_BUFFER(desc);
		dma_unmap_single(&hw_priv->pdev->dev, dma_buf->dma,
				 dma_buf->len, DMA_TO_DEVICE);

		/* This descriptor contains the last buffer in the packet. */
		अगर (dma_buf->skb) अणु
			dev = dma_buf->skb->dev;

			/* Release the packet back to network subप्रणाली. */
			dev_kमुक्त_skb_irq(dma_buf->skb);
			dma_buf->skb = शून्य;
		पूर्ण

		/* Free the transmitted descriptor. */
		last++;
		last &= info->mask;
		info->avail++;
	पूर्ण
	info->last = last;
	spin_unlock_irq(&hw_priv->hwlock);

	/* Notअगरy the network subप्रणाली that the packet has been sent. */
	अगर (dev)
		netअगर_trans_update(dev);
पूर्ण

/**
 * transmit_करोne - transmit करोne processing
 * @hw_priv:	Network device.
 *
 * This routine is called when the transmit पूर्णांकerrupt is triggered, indicating
 * either a packet is sent successfully or there are transmit errors.
 */
अटल व्योम tx_करोne(काष्ठा dev_info *hw_priv)
अणु
	काष्ठा ksz_hw *hw = &hw_priv->hw;
	पूर्णांक port;

	transmit_cleanup(hw_priv, 1);

	क्रम (port = 0; port < hw->dev_count; port++) अणु
		काष्ठा net_device *dev = hw->port_info[port].pdev;

		अगर (netअगर_running(dev) && netअगर_queue_stopped(dev))
			netअगर_wake_queue(dev);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम copy_old_skb(काष्ठा sk_buff *old, काष्ठा sk_buff *skb)
अणु
	skb->dev = old->dev;
	skb->protocol = old->protocol;
	skb->ip_summed = old->ip_summed;
	skb->csum = old->csum;
	skb_set_network_header(skb, ETH_HLEN);

	dev_consume_skb_any(old);
पूर्ण

/**
 * netdev_tx - send out packet
 * @skb:	Socket buffer.
 * @dev:	Network device.
 *
 * This function is used by the upper network layer to send out a packet.
 *
 * Return 0 अगर successful; otherwise an error code indicating failure.
 */
अटल netdev_tx_t netdev_tx(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा dev_priv *priv = netdev_priv(dev);
	काष्ठा dev_info *hw_priv = priv->adapter;
	काष्ठा ksz_hw *hw = &hw_priv->hw;
	पूर्णांक left;
	पूर्णांक num = 1;
	पूर्णांक rc = 0;

	अगर (hw->features & SMALL_PACKET_TX_BUG) अणु
		काष्ठा sk_buff *org_skb = skb;

		अगर (skb->len <= 48) अणु
			अगर (skb_end_poपूर्णांकer(skb) - skb->data >= 50) अणु
				स_रखो(&skb->data[skb->len], 0, 50 - skb->len);
				skb->len = 50;
			पूर्ण अन्यथा अणु
				skb = netdev_alloc_skb(dev, 50);
				अगर (!skb)
					वापस NETDEV_TX_BUSY;
				स_नकल(skb->data, org_skb->data, org_skb->len);
				स_रखो(&skb->data[org_skb->len], 0,
					50 - org_skb->len);
				skb->len = 50;
				copy_old_skb(org_skb, skb);
			पूर्ण
		पूर्ण
	पूर्ण

	spin_lock_irq(&hw_priv->hwlock);

	num = skb_shinfo(skb)->nr_frags + 1;
	left = hw_alloc_pkt(hw, skb->len, num);
	अगर (left) अणु
		अगर (left < num ||
		    (CHECKSUM_PARTIAL == skb->ip_summed &&
		     skb->protocol == htons(ETH_P_IPV6))) अणु
			काष्ठा sk_buff *org_skb = skb;

			skb = netdev_alloc_skb(dev, org_skb->len);
			अगर (!skb) अणु
				rc = NETDEV_TX_BUSY;
				जाओ unlock;
			पूर्ण
			skb_copy_and_csum_dev(org_skb, skb->data);
			org_skb->ip_summed = CHECKSUM_NONE;
			skb->len = org_skb->len;
			copy_old_skb(org_skb, skb);
		पूर्ण
		send_packet(skb, dev);
		अगर (left <= num)
			netअगर_stop_queue(dev);
	पूर्ण अन्यथा अणु
		/* Stop the transmit queue until packet is allocated. */
		netअगर_stop_queue(dev);
		rc = NETDEV_TX_BUSY;
	पूर्ण
unlock:
	spin_unlock_irq(&hw_priv->hwlock);

	वापस rc;
पूर्ण

/**
 * netdev_tx_समयout - transmit समयout processing
 * @dev:	Network device.
 * @txqueue:	index of hanging queue
 *
 * This routine is called when the transmit समयr expires.  That indicates the
 * hardware is not running correctly because transmit पूर्णांकerrupts are not
 * triggered to मुक्त up resources so that the transmit routine can जारी
 * sending out packets.  The hardware is reset to correct the problem.
 */
अटल व्योम netdev_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	अटल अचिन्हित दीर्घ last_reset;

	काष्ठा dev_priv *priv = netdev_priv(dev);
	काष्ठा dev_info *hw_priv = priv->adapter;
	काष्ठा ksz_hw *hw = &hw_priv->hw;
	पूर्णांक port;

	अगर (hw->dev_count > 1) अणु
		/*
		 * Only reset the hardware अगर समय between calls is दीर्घ
		 * enough.
		 */
		अगर (समय_beक्रमe_eq(jअगरfies, last_reset + dev->watchकरोg_समयo))
			hw_priv = शून्य;
	पूर्ण

	last_reset = jअगरfies;
	अगर (hw_priv) अणु
		hw_dis_पूर्णांकr(hw);
		hw_disable(hw);

		transmit_cleanup(hw_priv, 0);
		hw_reset_pkts(&hw->rx_desc_info);
		hw_reset_pkts(&hw->tx_desc_info);
		ksz_init_rx_buffers(hw_priv);

		hw_reset(hw);

		hw_set_desc_base(hw,
			hw->tx_desc_info.ring_phys,
			hw->rx_desc_info.ring_phys);
		hw_set_addr(hw);
		अगर (hw->all_multi)
			hw_set_multicast(hw, hw->all_multi);
		अन्यथा अगर (hw->multi_list_size)
			hw_set_grp_addr(hw);

		अगर (hw->dev_count > 1) अणु
			hw_set_add_addr(hw);
			क्रम (port = 0; port < SWITCH_PORT_NUM; port++) अणु
				काष्ठा net_device *port_dev;

				port_set_stp_state(hw, port,
					STP_STATE_DISABLED);

				port_dev = hw->port_info[port].pdev;
				अगर (netअगर_running(port_dev))
					port_set_stp_state(hw, port,
						STP_STATE_SIMPLE);
			पूर्ण
		पूर्ण

		hw_enable(hw);
		hw_ena_पूर्णांकr(hw);
	पूर्ण

	netअगर_trans_update(dev);
	netअगर_wake_queue(dev);
पूर्ण

अटल अंतरभूत व्योम csum_verअगरied(काष्ठा sk_buff *skb)
अणु
	अचिन्हित लघु protocol;
	काष्ठा iphdr *iph;

	protocol = skb->protocol;
	skb_reset_network_header(skb);
	iph = (काष्ठा iphdr *) skb_network_header(skb);
	अगर (protocol == htons(ETH_P_8021Q)) अणु
		protocol = iph->tot_len;
		skb_set_network_header(skb, VLAN_HLEN);
		iph = (काष्ठा iphdr *) skb_network_header(skb);
	पूर्ण
	अगर (protocol == htons(ETH_P_IP)) अणु
		अगर (iph->protocol == IPPROTO_TCP)
			skb->ip_summed = CHECKSUM_UNNECESSARY;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक rx_proc(काष्ठा net_device *dev, काष्ठा ksz_hw* hw,
	काष्ठा ksz_desc *desc, जोड़ desc_stat status)
अणु
	पूर्णांक packet_len;
	काष्ठा dev_priv *priv = netdev_priv(dev);
	काष्ठा dev_info *hw_priv = priv->adapter;
	काष्ठा ksz_dma_buf *dma_buf;
	काष्ठा sk_buff *skb;

	/* Received length includes 4-byte CRC. */
	packet_len = status.rx.frame_len - 4;

	dma_buf = DMA_BUFFER(desc);
	dma_sync_single_क्रम_cpu(&hw_priv->pdev->dev, dma_buf->dma,
				packet_len + 4, DMA_FROM_DEVICE);

	करो अणु
		/* skb->data != skb->head */
		skb = netdev_alloc_skb(dev, packet_len + 2);
		अगर (!skb) अणु
			dev->stats.rx_dropped++;
			वापस -ENOMEM;
		पूर्ण

		/*
		 * Align socket buffer in 4-byte boundary क्रम better
		 * perक्रमmance.
		 */
		skb_reserve(skb, 2);

		skb_put_data(skb, dma_buf->skb->data, packet_len);
	पूर्ण जबतक (0);

	skb->protocol = eth_type_trans(skb, dev);

	अगर (hw->rx_cfg & (DMA_RX_CSUM_UDP | DMA_RX_CSUM_TCP))
		csum_verअगरied(skb);

	/* Update receive statistics. */
	dev->stats.rx_packets++;
	dev->stats.rx_bytes += packet_len;

	/* Notअगरy upper layer क्रम received packet. */
	netअगर_rx(skb);

	वापस 0;
पूर्ण

अटल पूर्णांक dev_rcv_packets(काष्ठा dev_info *hw_priv)
अणु
	पूर्णांक next;
	जोड़ desc_stat status;
	काष्ठा ksz_hw *hw = &hw_priv->hw;
	काष्ठा net_device *dev = hw->port_info[0].pdev;
	काष्ठा ksz_desc_info *info = &hw->rx_desc_info;
	पूर्णांक left = info->alloc;
	काष्ठा ksz_desc *desc;
	पूर्णांक received = 0;

	next = info->next;
	जबतक (left--) अणु
		/* Get next descriptor which is not hardware owned. */
		desc = &info->ring[next];
		status.data = le32_to_cpu(desc->phw->ctrl.data);
		अगर (status.rx.hw_owned)
			अवरोध;

		/* Status valid only when last descriptor bit is set. */
		अगर (status.rx.last_desc && status.rx.first_desc) अणु
			अगर (rx_proc(dev, hw, desc, status))
				जाओ release_packet;
			received++;
		पूर्ण

release_packet:
		release_desc(desc);
		next++;
		next &= info->mask;
	पूर्ण
	info->next = next;

	वापस received;
पूर्ण

अटल पूर्णांक port_rcv_packets(काष्ठा dev_info *hw_priv)
अणु
	पूर्णांक next;
	जोड़ desc_stat status;
	काष्ठा ksz_hw *hw = &hw_priv->hw;
	काष्ठा net_device *dev = hw->port_info[0].pdev;
	काष्ठा ksz_desc_info *info = &hw->rx_desc_info;
	पूर्णांक left = info->alloc;
	काष्ठा ksz_desc *desc;
	पूर्णांक received = 0;

	next = info->next;
	जबतक (left--) अणु
		/* Get next descriptor which is not hardware owned. */
		desc = &info->ring[next];
		status.data = le32_to_cpu(desc->phw->ctrl.data);
		अगर (status.rx.hw_owned)
			अवरोध;

		अगर (hw->dev_count > 1) अणु
			/* Get received port number. */
			पूर्णांक p = HW_TO_DEV_PORT(status.rx.src_port);

			dev = hw->port_info[p].pdev;
			अगर (!netअगर_running(dev))
				जाओ release_packet;
		पूर्ण

		/* Status valid only when last descriptor bit is set. */
		अगर (status.rx.last_desc && status.rx.first_desc) अणु
			अगर (rx_proc(dev, hw, desc, status))
				जाओ release_packet;
			received++;
		पूर्ण

release_packet:
		release_desc(desc);
		next++;
		next &= info->mask;
	पूर्ण
	info->next = next;

	वापस received;
पूर्ण

अटल पूर्णांक dev_rcv_special(काष्ठा dev_info *hw_priv)
अणु
	पूर्णांक next;
	जोड़ desc_stat status;
	काष्ठा ksz_hw *hw = &hw_priv->hw;
	काष्ठा net_device *dev = hw->port_info[0].pdev;
	काष्ठा ksz_desc_info *info = &hw->rx_desc_info;
	पूर्णांक left = info->alloc;
	काष्ठा ksz_desc *desc;
	पूर्णांक received = 0;

	next = info->next;
	जबतक (left--) अणु
		/* Get next descriptor which is not hardware owned. */
		desc = &info->ring[next];
		status.data = le32_to_cpu(desc->phw->ctrl.data);
		अगर (status.rx.hw_owned)
			अवरोध;

		अगर (hw->dev_count > 1) अणु
			/* Get received port number. */
			पूर्णांक p = HW_TO_DEV_PORT(status.rx.src_port);

			dev = hw->port_info[p].pdev;
			अगर (!netअगर_running(dev))
				जाओ release_packet;
		पूर्ण

		/* Status valid only when last descriptor bit is set. */
		अगर (status.rx.last_desc && status.rx.first_desc) अणु
			/*
			 * Receive without error.  With receive errors
			 * disabled, packets with receive errors will be
			 * dropped, so no need to check the error bit.
			 */
			अगर (!status.rx.error || (status.data &
					KS_DESC_RX_ERROR_COND) ==
					KS_DESC_RX_ERROR_TOO_LONG) अणु
				अगर (rx_proc(dev, hw, desc, status))
					जाओ release_packet;
				received++;
			पूर्ण अन्यथा अणु
				काष्ठा dev_priv *priv = netdev_priv(dev);

				/* Update receive error statistics. */
				priv->port.counter[OID_COUNTER_RCV_ERROR]++;
			पूर्ण
		पूर्ण

release_packet:
		release_desc(desc);
		next++;
		next &= info->mask;
	पूर्ण
	info->next = next;

	वापस received;
पूर्ण

अटल व्योम rx_proc_task(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा dev_info *hw_priv = from_tasklet(hw_priv, t, rx_tasklet);
	काष्ठा ksz_hw *hw = &hw_priv->hw;

	अगर (!hw->enabled)
		वापस;
	अगर (unlikely(!hw_priv->dev_rcv(hw_priv))) अणु

		/* In हाल receive process is suspended because of overrun. */
		hw_resume_rx(hw);

		/* tasklets are पूर्णांकerruptible. */
		spin_lock_irq(&hw_priv->hwlock);
		hw_turn_on_पूर्णांकr(hw, KS884X_INT_RX_MASK);
		spin_unlock_irq(&hw_priv->hwlock);
	पूर्ण अन्यथा अणु
		hw_ack_पूर्णांकr(hw, KS884X_INT_RX);
		tasklet_schedule(&hw_priv->rx_tasklet);
	पूर्ण
पूर्ण

अटल व्योम tx_proc_task(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा dev_info *hw_priv = from_tasklet(hw_priv, t, tx_tasklet);
	काष्ठा ksz_hw *hw = &hw_priv->hw;

	hw_ack_पूर्णांकr(hw, KS884X_INT_TX_MASK);

	tx_करोne(hw_priv);

	/* tasklets are पूर्णांकerruptible. */
	spin_lock_irq(&hw_priv->hwlock);
	hw_turn_on_पूर्णांकr(hw, KS884X_INT_TX);
	spin_unlock_irq(&hw_priv->hwlock);
पूर्ण

अटल अंतरभूत व्योम handle_rx_stop(काष्ठा ksz_hw *hw)
अणु
	/* Receive just has been stopped. */
	अगर (0 == hw->rx_stop)
		hw->पूर्णांकr_mask &= ~KS884X_INT_RX_STOPPED;
	अन्यथा अगर (hw->rx_stop > 1) अणु
		अगर (hw->enabled && (hw->rx_cfg & DMA_RX_ENABLE)) अणु
			hw_start_rx(hw);
		पूर्ण अन्यथा अणु
			hw->पूर्णांकr_mask &= ~KS884X_INT_RX_STOPPED;
			hw->rx_stop = 0;
		पूर्ण
	पूर्ण अन्यथा
		/* Receive just has been started. */
		hw->rx_stop++;
पूर्ण

/**
 * netdev_पूर्णांकr - पूर्णांकerrupt handling
 * @irq:	Interrupt number.
 * @dev_id:	Network device.
 *
 * This function is called by upper network layer to संकेत पूर्णांकerrupt.
 *
 * Return IRQ_HANDLED अगर पूर्णांकerrupt is handled.
 */
अटल irqवापस_t netdev_पूर्णांकr(पूर्णांक irq, व्योम *dev_id)
अणु
	uपूर्णांक पूर्णांक_enable = 0;
	काष्ठा net_device *dev = (काष्ठा net_device *) dev_id;
	काष्ठा dev_priv *priv = netdev_priv(dev);
	काष्ठा dev_info *hw_priv = priv->adapter;
	काष्ठा ksz_hw *hw = &hw_priv->hw;

	spin_lock(&hw_priv->hwlock);

	hw_पढ़ो_पूर्णांकr(hw, &पूर्णांक_enable);

	/* Not our पूर्णांकerrupt! */
	अगर (!पूर्णांक_enable) अणु
		spin_unlock(&hw_priv->hwlock);
		वापस IRQ_NONE;
	पूर्ण

	करो अणु
		hw_ack_पूर्णांकr(hw, पूर्णांक_enable);
		पूर्णांक_enable &= hw->पूर्णांकr_mask;

		अगर (unlikely(पूर्णांक_enable & KS884X_INT_TX_MASK)) अणु
			hw_dis_पूर्णांकr_bit(hw, KS884X_INT_TX_MASK);
			tasklet_schedule(&hw_priv->tx_tasklet);
		पूर्ण

		अगर (likely(पूर्णांक_enable & KS884X_INT_RX)) अणु
			hw_dis_पूर्णांकr_bit(hw, KS884X_INT_RX);
			tasklet_schedule(&hw_priv->rx_tasklet);
		पूर्ण

		अगर (unlikely(पूर्णांक_enable & KS884X_INT_RX_OVERRUN)) अणु
			dev->stats.rx_fअगरo_errors++;
			hw_resume_rx(hw);
		पूर्ण

		अगर (unlikely(पूर्णांक_enable & KS884X_INT_PHY)) अणु
			काष्ठा ksz_port *port = &priv->port;

			hw->features |= LINK_INT_WORKING;
			port_get_link_speed(port);
		पूर्ण

		अगर (unlikely(पूर्णांक_enable & KS884X_INT_RX_STOPPED)) अणु
			handle_rx_stop(hw);
			अवरोध;
		पूर्ण

		अगर (unlikely(पूर्णांक_enable & KS884X_INT_TX_STOPPED)) अणु
			u32 data;

			hw->पूर्णांकr_mask &= ~KS884X_INT_TX_STOPPED;
			pr_info("Tx stopped\n");
			data = पढ़ोl(hw->io + KS_DMA_TX_CTRL);
			अगर (!(data & DMA_TX_ENABLE))
				pr_info("Tx disabled\n");
			अवरोध;
		पूर्ण
	पूर्ण जबतक (0);

	hw_ena_पूर्णांकr(hw);

	spin_unlock(&hw_priv->hwlock);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Linux network device functions
 */

अटल अचिन्हित दीर्घ next_jअगरfies;

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम netdev_netpoll(काष्ठा net_device *dev)
अणु
	काष्ठा dev_priv *priv = netdev_priv(dev);
	काष्ठा dev_info *hw_priv = priv->adapter;

	hw_dis_पूर्णांकr(&hw_priv->hw);
	netdev_पूर्णांकr(dev->irq, dev);
पूर्ण
#पूर्ण_अगर

अटल व्योम bridge_change(काष्ठा ksz_hw *hw)
अणु
	पूर्णांक port;
	u8  member;
	काष्ठा ksz_चयन *sw = hw->ksz_चयन;

	/* No ports in क्रमwarding state. */
	अगर (!sw->member) अणु
		port_set_stp_state(hw, SWITCH_PORT_NUM, STP_STATE_SIMPLE);
		sw_block_addr(hw);
	पूर्ण
	क्रम (port = 0; port < SWITCH_PORT_NUM; port++) अणु
		अगर (STP_STATE_FORWARDING == sw->port_cfg[port].stp_state)
			member = HOST_MASK | sw->member;
		अन्यथा
			member = HOST_MASK | (1 << port);
		अगर (member != sw->port_cfg[port].member)
			sw_cfg_port_base_vlan(hw, port, member);
	पूर्ण
पूर्ण

/**
 * netdev_बंद - बंद network device
 * @dev:	Network device.
 *
 * This function process the बंद operation of network device.  This is caused
 * by the user command "ifconfig ethX down."
 *
 * Return 0 अगर successful; otherwise an error code indicating failure.
 */
अटल पूर्णांक netdev_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा dev_priv *priv = netdev_priv(dev);
	काष्ठा dev_info *hw_priv = priv->adapter;
	काष्ठा ksz_port *port = &priv->port;
	काष्ठा ksz_hw *hw = &hw_priv->hw;
	पूर्णांक pi;

	netअगर_stop_queue(dev);

	ksz_stop_समयr(&priv->monitor_समयr_info);

	/* Need to shut the port manually in multiple device पूर्णांकerfaces mode. */
	अगर (hw->dev_count > 1) अणु
		port_set_stp_state(hw, port->first_port, STP_STATE_DISABLED);

		/* Port is बंदd.  Need to change bridge setting. */
		अगर (hw->features & STP_SUPPORT) अणु
			pi = 1 << port->first_port;
			अगर (hw->ksz_चयन->member & pi) अणु
				hw->ksz_चयन->member &= ~pi;
				bridge_change(hw);
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (port->first_port > 0)
		hw_del_addr(hw, dev->dev_addr);
	अगर (!hw_priv->wol_enable)
		port_set_घातer_saving(port, true);

	अगर (priv->multicast)
		--hw->all_multi;
	अगर (priv->promiscuous)
		--hw->promiscuous;

	hw_priv->खोलोed--;
	अगर (!(hw_priv->खोलोed)) अणु
		ksz_stop_समयr(&hw_priv->mib_समयr_info);
		flush_work(&hw_priv->mib_पढ़ो);

		hw_dis_पूर्णांकr(hw);
		hw_disable(hw);
		hw_clr_multicast(hw);

		/* Delay क्रम receive task to stop scheduling itself. */
		msleep(2000 / HZ);

		tasklet_समाप्त(&hw_priv->rx_tasklet);
		tasklet_समाप्त(&hw_priv->tx_tasklet);
		मुक्त_irq(dev->irq, hw_priv->dev);

		transmit_cleanup(hw_priv, 0);
		hw_reset_pkts(&hw->rx_desc_info);
		hw_reset_pkts(&hw->tx_desc_info);

		/* Clean out अटल MAC table when the चयन is shutकरोwn. */
		अगर (hw->features & STP_SUPPORT)
			sw_clr_sta_mac_table(hw);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hw_cfg_huge_frame(काष्ठा dev_info *hw_priv, काष्ठा ksz_hw *hw)
अणु
	अगर (hw->ksz_चयन) अणु
		u32 data;

		data = पढ़ोw(hw->io + KS8842_SWITCH_CTRL_2_OFFSET);
		अगर (hw->features & RX_HUGE_FRAME)
			data |= SWITCH_HUGE_PACKET;
		अन्यथा
			data &= ~SWITCH_HUGE_PACKET;
		ग_लिखोw(data, hw->io + KS8842_SWITCH_CTRL_2_OFFSET);
	पूर्ण
	अगर (hw->features & RX_HUGE_FRAME) अणु
		hw->rx_cfg |= DMA_RX_ERROR;
		hw_priv->dev_rcv = dev_rcv_special;
	पूर्ण अन्यथा अणु
		hw->rx_cfg &= ~DMA_RX_ERROR;
		अगर (hw->dev_count > 1)
			hw_priv->dev_rcv = port_rcv_packets;
		अन्यथा
			hw_priv->dev_rcv = dev_rcv_packets;
	पूर्ण
पूर्ण

अटल पूर्णांक prepare_hardware(काष्ठा net_device *dev)
अणु
	काष्ठा dev_priv *priv = netdev_priv(dev);
	काष्ठा dev_info *hw_priv = priv->adapter;
	काष्ठा ksz_hw *hw = &hw_priv->hw;
	पूर्णांक rc = 0;

	/* Remember the network device that requests पूर्णांकerrupts. */
	hw_priv->dev = dev;
	rc = request_irq(dev->irq, netdev_पूर्णांकr, IRQF_SHARED, dev->name, dev);
	अगर (rc)
		वापस rc;
	tasklet_setup(&hw_priv->rx_tasklet, rx_proc_task);
	tasklet_setup(&hw_priv->tx_tasklet, tx_proc_task);

	hw->promiscuous = 0;
	hw->all_multi = 0;
	hw->multi_list_size = 0;

	hw_reset(hw);

	hw_set_desc_base(hw,
		hw->tx_desc_info.ring_phys, hw->rx_desc_info.ring_phys);
	hw_set_addr(hw);
	hw_cfg_huge_frame(hw_priv, hw);
	ksz_init_rx_buffers(hw_priv);
	वापस 0;
पूर्ण

अटल व्योम set_media_state(काष्ठा net_device *dev, पूर्णांक media_state)
अणु
	काष्ठा dev_priv *priv = netdev_priv(dev);

	अगर (media_state == priv->media_state)
		netअगर_carrier_on(dev);
	अन्यथा
		netअगर_carrier_off(dev);
	netअगर_info(priv, link, dev, "link %s\n",
		   media_state == priv->media_state ? "on" : "off");
पूर्ण

/**
 * netdev_खोलो - खोलो network device
 * @dev:	Network device.
 *
 * This function process the खोलो operation of network device.  This is caused
 * by the user command "ifconfig ethX up."
 *
 * Return 0 अगर successful; otherwise an error code indicating failure.
 */
अटल पूर्णांक netdev_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा dev_priv *priv = netdev_priv(dev);
	काष्ठा dev_info *hw_priv = priv->adapter;
	काष्ठा ksz_hw *hw = &hw_priv->hw;
	काष्ठा ksz_port *port = &priv->port;
	पूर्णांक i;
	पूर्णांक p;
	पूर्णांक rc = 0;

	priv->multicast = 0;
	priv->promiscuous = 0;

	/* Reset device statistics. */
	स_रखो(&dev->stats, 0, माप(काष्ठा net_device_stats));
	स_रखो((व्योम *) port->counter, 0,
		(माप(u64) * OID_COUNTER_LAST));

	अगर (!(hw_priv->खोलोed)) अणु
		rc = prepare_hardware(dev);
		अगर (rc)
			वापस rc;
		क्रम (i = 0; i < hw->mib_port_cnt; i++) अणु
			अगर (next_jअगरfies < jअगरfies)
				next_jअगरfies = jअगरfies + HZ * 2;
			अन्यथा
				next_jअगरfies += HZ * 1;
			hw_priv->counter[i].समय = next_jअगरfies;
			hw->port_mib[i].state = media_disconnected;
			port_init_cnt(hw, i);
		पूर्ण
		अगर (hw->ksz_चयन)
			hw->port_mib[HOST_PORT].state = media_connected;
		अन्यथा अणु
			hw_add_wol_bcast(hw);
			hw_cfg_wol_pme(hw, 0);
			hw_clr_wol_pme_status(&hw_priv->hw);
		पूर्ण
	पूर्ण
	port_set_घातer_saving(port, false);

	क्रम (i = 0, p = port->first_port; i < port->port_cnt; i++, p++) अणु
		/*
		 * Initialize to invalid value so that link detection
		 * is करोne.
		 */
		hw->port_info[p].partner = 0xFF;
		hw->port_info[p].state = media_disconnected;
	पूर्ण

	/* Need to खोलो the port in multiple device पूर्णांकerfaces mode. */
	अगर (hw->dev_count > 1) अणु
		port_set_stp_state(hw, port->first_port, STP_STATE_SIMPLE);
		अगर (port->first_port > 0)
			hw_add_addr(hw, dev->dev_addr);
	पूर्ण

	port_get_link_speed(port);
	अगर (port->क्रमce_link)
		port_क्रमce_link_speed(port);
	अन्यथा
		port_set_link_speed(port);

	अगर (!(hw_priv->खोलोed)) अणु
		hw_setup_पूर्णांकr(hw);
		hw_enable(hw);
		hw_ena_पूर्णांकr(hw);

		अगर (hw->mib_port_cnt)
			ksz_start_समयr(&hw_priv->mib_समयr_info,
				hw_priv->mib_समयr_info.period);
	पूर्ण

	hw_priv->खोलोed++;

	ksz_start_समयr(&priv->monitor_समयr_info,
		priv->monitor_समयr_info.period);

	priv->media_state = port->linked->state;

	set_media_state(dev, media_connected);
	netअगर_start_queue(dev);

	वापस 0;
पूर्ण

/* RX errors = rx_errors */
/* RX dropped = rx_dropped */
/* RX overruns = rx_fअगरo_errors */
/* RX frame = rx_crc_errors + rx_frame_errors + rx_length_errors */
/* TX errors = tx_errors */
/* TX dropped = tx_dropped */
/* TX overruns = tx_fअगरo_errors */
/* TX carrier = tx_पातed_errors + tx_carrier_errors + tx_winकरोw_errors */
/* collisions = collisions */

/**
 * netdev_query_statistics - query network device statistics
 * @dev:	Network device.
 *
 * This function वापसs the statistics of the network device.  The device
 * needs not be खोलोed.
 *
 * Return network device statistics.
 */
अटल काष्ठा net_device_stats *netdev_query_statistics(काष्ठा net_device *dev)
अणु
	काष्ठा dev_priv *priv = netdev_priv(dev);
	काष्ठा ksz_port *port = &priv->port;
	काष्ठा ksz_hw *hw = &priv->adapter->hw;
	काष्ठा ksz_port_mib *mib;
	पूर्णांक i;
	पूर्णांक p;

	dev->stats.rx_errors = port->counter[OID_COUNTER_RCV_ERROR];
	dev->stats.tx_errors = port->counter[OID_COUNTER_XMIT_ERROR];

	/* Reset to zero to add count later. */
	dev->stats.multicast = 0;
	dev->stats.collisions = 0;
	dev->stats.rx_length_errors = 0;
	dev->stats.rx_crc_errors = 0;
	dev->stats.rx_frame_errors = 0;
	dev->stats.tx_winकरोw_errors = 0;

	क्रम (i = 0, p = port->first_port; i < port->mib_port_cnt; i++, p++) अणु
		mib = &hw->port_mib[p];

		dev->stats.multicast += (अचिन्हित दीर्घ)
			mib->counter[MIB_COUNTER_RX_MULTICAST];

		dev->stats.collisions += (अचिन्हित दीर्घ)
			mib->counter[MIB_COUNTER_TX_TOTAL_COLLISION];

		dev->stats.rx_length_errors += (अचिन्हित दीर्घ)(
			mib->counter[MIB_COUNTER_RX_UNDERSIZE] +
			mib->counter[MIB_COUNTER_RX_FRAGMENT] +
			mib->counter[MIB_COUNTER_RX_OVERSIZE] +
			mib->counter[MIB_COUNTER_RX_JABBER]);
		dev->stats.rx_crc_errors += (अचिन्हित दीर्घ)
			mib->counter[MIB_COUNTER_RX_CRC_ERR];
		dev->stats.rx_frame_errors += (अचिन्हित दीर्घ)(
			mib->counter[MIB_COUNTER_RX_ALIGNMENT_ERR] +
			mib->counter[MIB_COUNTER_RX_SYMBOL_ERR]);

		dev->stats.tx_winकरोw_errors += (अचिन्हित दीर्घ)
			mib->counter[MIB_COUNTER_TX_LATE_COLLISION];
	पूर्ण

	वापस &dev->stats;
पूर्ण

/**
 * netdev_set_mac_address - set network device MAC address
 * @dev:	Network device.
 * @addr:	Buffer of MAC address.
 *
 * This function is used to set the MAC address of the network device.
 *
 * Return 0 to indicate success.
 */
अटल पूर्णांक netdev_set_mac_address(काष्ठा net_device *dev, व्योम *addr)
अणु
	काष्ठा dev_priv *priv = netdev_priv(dev);
	काष्ठा dev_info *hw_priv = priv->adapter;
	काष्ठा ksz_hw *hw = &hw_priv->hw;
	काष्ठा sockaddr *mac = addr;
	uपूर्णांक पूर्णांकerrupt;

	अगर (priv->port.first_port > 0)
		hw_del_addr(hw, dev->dev_addr);
	अन्यथा अणु
		hw->mac_override = 1;
		स_नकल(hw->override_addr, mac->sa_data, ETH_ALEN);
	पूर्ण

	स_नकल(dev->dev_addr, mac->sa_data, ETH_ALEN);

	पूर्णांकerrupt = hw_block_पूर्णांकr(hw);

	अगर (priv->port.first_port > 0)
		hw_add_addr(hw, dev->dev_addr);
	अन्यथा
		hw_set_addr(hw);
	hw_restore_पूर्णांकr(hw, पूर्णांकerrupt);

	वापस 0;
पूर्ण

अटल व्योम dev_set_promiscuous(काष्ठा net_device *dev, काष्ठा dev_priv *priv,
	काष्ठा ksz_hw *hw, पूर्णांक promiscuous)
अणु
	अगर (promiscuous != priv->promiscuous) अणु
		u8 prev_state = hw->promiscuous;

		अगर (promiscuous)
			++hw->promiscuous;
		अन्यथा
			--hw->promiscuous;
		priv->promiscuous = promiscuous;

		/* Turn on/off promiscuous mode. */
		अगर (hw->promiscuous <= 1 && prev_state <= 1)
			hw_set_promiscuous(hw, hw->promiscuous);

		/*
		 * Port is not in promiscuous mode, meaning it is released
		 * from the bridge.
		 */
		अगर ((hw->features & STP_SUPPORT) && !promiscuous &&
		    netअगर_is_bridge_port(dev)) अणु
			काष्ठा ksz_चयन *sw = hw->ksz_चयन;
			पूर्णांक port = priv->port.first_port;

			port_set_stp_state(hw, port, STP_STATE_DISABLED);
			port = 1 << port;
			अगर (sw->member & port) अणु
				sw->member &= ~port;
				bridge_change(hw);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम dev_set_multicast(काष्ठा dev_priv *priv, काष्ठा ksz_hw *hw,
	पूर्णांक multicast)
अणु
	अगर (multicast != priv->multicast) अणु
		u8 all_multi = hw->all_multi;

		अगर (multicast)
			++hw->all_multi;
		अन्यथा
			--hw->all_multi;
		priv->multicast = multicast;

		/* Turn on/off all multicast mode. */
		अगर (hw->all_multi <= 1 && all_multi <= 1)
			hw_set_multicast(hw, hw->all_multi);
	पूर्ण
पूर्ण

/**
 * netdev_set_rx_mode
 * @dev:	Network device.
 *
 * This routine is used to set multicast addresses or put the network device
 * पूर्णांकo promiscuous mode.
 */
अटल व्योम netdev_set_rx_mode(काष्ठा net_device *dev)
अणु
	काष्ठा dev_priv *priv = netdev_priv(dev);
	काष्ठा dev_info *hw_priv = priv->adapter;
	काष्ठा ksz_hw *hw = &hw_priv->hw;
	काष्ठा netdev_hw_addr *ha;
	पूर्णांक multicast = (dev->flags & IFF_ALLMULTI);

	dev_set_promiscuous(dev, priv, hw, (dev->flags & IFF_PROMISC));

	अगर (hw_priv->hw.dev_count > 1)
		multicast |= (dev->flags & IFF_MULTICAST);
	dev_set_multicast(priv, hw, multicast);

	/* Cannot use dअगरferent hashes in multiple device पूर्णांकerfaces mode. */
	अगर (hw_priv->hw.dev_count > 1)
		वापस;

	अगर ((dev->flags & IFF_MULTICAST) && !netdev_mc_empty(dev)) अणु
		पूर्णांक i = 0;

		/* List too big to support so turn on all multicast mode. */
		अगर (netdev_mc_count(dev) > MAX_MULTICAST_LIST) अणु
			अगर (MAX_MULTICAST_LIST != hw->multi_list_size) अणु
				hw->multi_list_size = MAX_MULTICAST_LIST;
				++hw->all_multi;
				hw_set_multicast(hw, hw->all_multi);
			पूर्ण
			वापस;
		पूर्ण

		netdev_क्रम_each_mc_addr(ha, dev) अणु
			अगर (i >= MAX_MULTICAST_LIST)
				अवरोध;
			स_नकल(hw->multi_list[i++], ha->addr, ETH_ALEN);
		पूर्ण
		hw->multi_list_size = (u8) i;
		hw_set_grp_addr(hw);
	पूर्ण अन्यथा अणु
		अगर (MAX_MULTICAST_LIST == hw->multi_list_size) अणु
			--hw->all_multi;
			hw_set_multicast(hw, hw->all_multi);
		पूर्ण
		hw->multi_list_size = 0;
		hw_clr_multicast(hw);
	पूर्ण
पूर्ण

अटल पूर्णांक netdev_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	काष्ठा dev_priv *priv = netdev_priv(dev);
	काष्ठा dev_info *hw_priv = priv->adapter;
	काष्ठा ksz_hw *hw = &hw_priv->hw;
	पूर्णांक hw_mtu;

	अगर (netअगर_running(dev))
		वापस -EBUSY;

	/* Cannot use dअगरferent MTU in multiple device पूर्णांकerfaces mode. */
	अगर (hw->dev_count > 1)
		अगर (dev != hw_priv->dev)
			वापस 0;

	hw_mtu = new_mtu + ETHERNET_HEADER_SIZE + 4;
	अगर (hw_mtu > REGULAR_RX_BUF_SIZE) अणु
		hw->features |= RX_HUGE_FRAME;
		hw_mtu = MAX_RX_BUF_SIZE;
	पूर्ण अन्यथा अणु
		hw->features &= ~RX_HUGE_FRAME;
		hw_mtu = REGULAR_RX_BUF_SIZE;
	पूर्ण
	hw_mtu = (hw_mtu + 3) & ~3;
	hw_priv->mtu = hw_mtu;
	dev->mtu = new_mtu;

	वापस 0;
पूर्ण

/**
 * netdev_ioctl - I/O control processing
 * @dev:	Network device.
 * @अगरr:	Interface request काष्ठाure.
 * @cmd:	I/O control code.
 *
 * This function is used to process I/O control calls.
 *
 * Return 0 to indicate success.
 */
अटल पूर्णांक netdev_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा dev_priv *priv = netdev_priv(dev);
	काष्ठा dev_info *hw_priv = priv->adapter;
	काष्ठा ksz_hw *hw = &hw_priv->hw;
	काष्ठा ksz_port *port = &priv->port;
	पूर्णांक result = 0;
	काष्ठा mii_ioctl_data *data = अगर_mii(अगरr);

	अगर (करोwn_पूर्णांकerruptible(&priv->proc_sem))
		वापस -ERESTARTSYS;

	चयन (cmd) अणु
	/* Get address of MII PHY in use. */
	हाल SIOCGMIIPHY:
		data->phy_id = priv->id;
		fallthrough;

	/* Read MII PHY रेजिस्टर. */
	हाल SIOCGMIIREG:
		अगर (data->phy_id != priv->id || data->reg_num >= 6)
			result = -EIO;
		अन्यथा
			hw_r_phy(hw, port->linked->port_id, data->reg_num,
				&data->val_out);
		अवरोध;

	/* Write MII PHY रेजिस्टर. */
	हाल SIOCSMIIREG:
		अगर (!capable(CAP_NET_ADMIN))
			result = -EPERM;
		अन्यथा अगर (data->phy_id != priv->id || data->reg_num >= 6)
			result = -EIO;
		अन्यथा
			hw_w_phy(hw, port->linked->port_id, data->reg_num,
				data->val_in);
		अवरोध;

	शेष:
		result = -EOPNOTSUPP;
	पूर्ण

	up(&priv->proc_sem);

	वापस result;
पूर्ण

/*
 * MII support
 */

/**
 * mdio_पढ़ो - पढ़ो PHY रेजिस्टर
 * @dev:	Network device.
 * @phy_id:	The PHY id.
 * @reg_num:	The रेजिस्टर number.
 *
 * This function वापसs the PHY रेजिस्टर value.
 *
 * Return the रेजिस्टर value.
 */
अटल पूर्णांक mdio_पढ़ो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक reg_num)
अणु
	काष्ठा dev_priv *priv = netdev_priv(dev);
	काष्ठा ksz_port *port = &priv->port;
	काष्ठा ksz_hw *hw = port->hw;
	u16 val_out;

	hw_r_phy(hw, port->linked->port_id, reg_num << 1, &val_out);
	वापस val_out;
पूर्ण

/**
 * mdio_ग_लिखो - set PHY रेजिस्टर
 * @dev:	Network device.
 * @phy_id:	The PHY id.
 * @reg_num:	The रेजिस्टर number.
 * @val:	The रेजिस्टर value.
 *
 * This procedure sets the PHY रेजिस्टर value.
 */
अटल व्योम mdio_ग_लिखो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक reg_num, पूर्णांक val)
अणु
	काष्ठा dev_priv *priv = netdev_priv(dev);
	काष्ठा ksz_port *port = &priv->port;
	काष्ठा ksz_hw *hw = port->hw;
	पूर्णांक i;
	पूर्णांक pi;

	क्रम (i = 0, pi = port->first_port; i < port->port_cnt; i++, pi++)
		hw_w_phy(hw, pi, reg_num << 1, val);
पूर्ण

/*
 * ethtool support
 */

#घोषणा EEPROM_SIZE			0x40

अटल u16 eeprom_data[EEPROM_SIZE] = अणु 0 पूर्ण;

#घोषणा ADVERTISED_ALL			\
	(ADVERTISED_10baseT_Half |	\
	ADVERTISED_10baseT_Full |	\
	ADVERTISED_100baseT_Half |	\
	ADVERTISED_100baseT_Full)

/* These functions use the MII functions in mii.c. */

/**
 * netdev_get_link_ksettings - get network device settings
 * @dev:	Network device.
 * @cmd:	Ethtool command.
 *
 * This function queries the PHY and वापसs its state in the ethtool command.
 *
 * Return 0 अगर successful; otherwise an error code.
 */
अटल पूर्णांक netdev_get_link_ksettings(काष्ठा net_device *dev,
				     काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा dev_priv *priv = netdev_priv(dev);
	काष्ठा dev_info *hw_priv = priv->adapter;

	mutex_lock(&hw_priv->lock);
	mii_ethtool_get_link_ksettings(&priv->mii_अगर, cmd);
	ethtool_link_ksettings_add_link_mode(cmd, advertising, TP);
	mutex_unlock(&hw_priv->lock);

	/* Save advertised settings क्रम workaround in next function. */
	ethtool_convert_link_mode_to_legacy_u32(&priv->advertising,
						cmd->link_modes.advertising);

	वापस 0;
पूर्ण

/**
 * netdev_set_link_ksettings - set network device settings
 * @dev:	Network device.
 * @cmd:	Ethtool command.
 *
 * This function sets the PHY according to the ethtool command.
 *
 * Return 0 अगर successful; otherwise an error code.
 */
अटल पूर्णांक netdev_set_link_ksettings(काष्ठा net_device *dev,
				     स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा dev_priv *priv = netdev_priv(dev);
	काष्ठा dev_info *hw_priv = priv->adapter;
	काष्ठा ksz_port *port = &priv->port;
	काष्ठा ethtool_link_ksettings copy_cmd;
	u32 speed = cmd->base.speed;
	u32 advertising;
	पूर्णांक rc;

	ethtool_convert_link_mode_to_legacy_u32(&advertising,
						cmd->link_modes.advertising);

	/*
	 * ethtool utility करोes not change advertised setting अगर स्वतः
	 * negotiation is not specअगरied explicitly.
	 */
	अगर (cmd->base.स्वतःneg && priv->advertising == advertising) अणु
		advertising |= ADVERTISED_ALL;
		अगर (10 == speed)
			advertising &=
				~(ADVERTISED_100baseT_Full |
				ADVERTISED_100baseT_Half);
		अन्यथा अगर (100 == speed)
			advertising &=
				~(ADVERTISED_10baseT_Full |
				ADVERTISED_10baseT_Half);
		अगर (0 == cmd->base.duplex)
			advertising &=
				~(ADVERTISED_100baseT_Full |
				ADVERTISED_10baseT_Full);
		अन्यथा अगर (1 == cmd->base.duplex)
			advertising &=
				~(ADVERTISED_100baseT_Half |
				ADVERTISED_10baseT_Half);
	पूर्ण
	mutex_lock(&hw_priv->lock);
	अगर (cmd->base.स्वतःneg &&
	    (advertising & ADVERTISED_ALL) == ADVERTISED_ALL) अणु
		port->duplex = 0;
		port->speed = 0;
		port->क्रमce_link = 0;
	पूर्ण अन्यथा अणु
		port->duplex = cmd->base.duplex + 1;
		अगर (1000 != speed)
			port->speed = speed;
		अगर (cmd->base.स्वतःneg)
			port->क्रमce_link = 0;
		अन्यथा
			port->क्रमce_link = 1;
	पूर्ण

	स_नकल(&copy_cmd, cmd, माप(copy_cmd));
	ethtool_convert_legacy_u32_to_link_mode(copy_cmd.link_modes.advertising,
						advertising);
	rc = mii_ethtool_set_link_ksettings(
		&priv->mii_अगर,
		(स्थिर काष्ठा ethtool_link_ksettings *)&copy_cmd);
	mutex_unlock(&hw_priv->lock);
	वापस rc;
पूर्ण

/**
 * netdev_nway_reset - restart स्वतः-negotiation
 * @dev:	Network device.
 *
 * This function restarts the PHY क्रम स्वतः-negotiation.
 *
 * Return 0 अगर successful; otherwise an error code.
 */
अटल पूर्णांक netdev_nway_reset(काष्ठा net_device *dev)
अणु
	काष्ठा dev_priv *priv = netdev_priv(dev);
	काष्ठा dev_info *hw_priv = priv->adapter;
	पूर्णांक rc;

	mutex_lock(&hw_priv->lock);
	rc = mii_nway_restart(&priv->mii_अगर);
	mutex_unlock(&hw_priv->lock);
	वापस rc;
पूर्ण

/**
 * netdev_get_link - get network device link status
 * @dev:	Network device.
 *
 * This function माला_लो the link status from the PHY.
 *
 * Return true अगर PHY is linked and false otherwise.
 */
अटल u32 netdev_get_link(काष्ठा net_device *dev)
अणु
	काष्ठा dev_priv *priv = netdev_priv(dev);
	पूर्णांक rc;

	rc = mii_link_ok(&priv->mii_अगर);
	वापस rc;
पूर्ण

/**
 * netdev_get_drvinfo - get network driver inक्रमmation
 * @dev:	Network device.
 * @info:	Ethtool driver info data काष्ठाure.
 *
 * This procedure वापसs the driver inक्रमmation.
 */
अटल व्योम netdev_get_drvinfo(काष्ठा net_device *dev,
	काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा dev_priv *priv = netdev_priv(dev);
	काष्ठा dev_info *hw_priv = priv->adapter;

	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	strlcpy(info->version, DRV_VERSION, माप(info->version));
	strlcpy(info->bus_info, pci_name(hw_priv->pdev),
		माप(info->bus_info));
पूर्ण

अटल काष्ठा hw_regs अणु
	पूर्णांक start;
	पूर्णांक end;
पूर्ण hw_regs_range[] = अणु
	अणु KS_DMA_TX_CTRL,	KS884X_INTERRUPTS_STATUS पूर्ण,
	अणु KS_ADD_ADDR_0_LO,	KS_ADD_ADDR_F_HI पूर्ण,
	अणु KS884X_ADDR_0_OFFSET,	KS8841_WOL_FRAME_BYTE2_OFFSET पूर्ण,
	अणु KS884X_SIDER_P,	KS8842_SGCR7_P पूर्ण,
	अणु KS8842_MACAR1_P,	KS8842_TOSR8_P पूर्ण,
	अणु KS884X_P1MBCR_P,	KS8842_P3ERCR_P पूर्ण,
	अणु 0, 0 पूर्ण
पूर्ण;

/**
 * netdev_get_regs_len - get length of रेजिस्टर dump
 * @dev:	Network device.
 *
 * This function वापसs the length of the रेजिस्टर dump.
 *
 * Return length of the रेजिस्टर dump.
 */
अटल पूर्णांक netdev_get_regs_len(काष्ठा net_device *dev)
अणु
	काष्ठा hw_regs *range = hw_regs_range;
	पूर्णांक regs_len = 0x10 * माप(u32);

	जबतक (range->end > range->start) अणु
		regs_len += (range->end - range->start + 3) / 4 * 4;
		range++;
	पूर्ण
	वापस regs_len;
पूर्ण

/**
 * netdev_get_regs - get रेजिस्टर dump
 * @dev:	Network device.
 * @regs:	Ethtool रेजिस्टरs data काष्ठाure.
 * @ptr:	Buffer to store the रेजिस्टर values.
 *
 * This procedure dumps the रेजिस्टर values in the provided buffer.
 */
अटल व्योम netdev_get_regs(काष्ठा net_device *dev, काष्ठा ethtool_regs *regs,
	व्योम *ptr)
अणु
	काष्ठा dev_priv *priv = netdev_priv(dev);
	काष्ठा dev_info *hw_priv = priv->adapter;
	काष्ठा ksz_hw *hw = &hw_priv->hw;
	पूर्णांक *buf = (पूर्णांक *) ptr;
	काष्ठा hw_regs *range = hw_regs_range;
	पूर्णांक len;

	mutex_lock(&hw_priv->lock);
	regs->version = 0;
	क्रम (len = 0; len < 0x40; len += 4) अणु
		pci_पढ़ो_config_dword(hw_priv->pdev, len, buf);
		buf++;
	पूर्ण
	जबतक (range->end > range->start) अणु
		क्रम (len = range->start; len < range->end; len += 4) अणु
			*buf = पढ़ोl(hw->io + len);
			buf++;
		पूर्ण
		range++;
	पूर्ण
	mutex_unlock(&hw_priv->lock);
पूर्ण

#घोषणा WOL_SUPPORT			\
	(WAKE_PHY | WAKE_MAGIC |	\
	WAKE_UCAST | WAKE_MCAST |	\
	WAKE_BCAST | WAKE_ARP)

/**
 * netdev_get_wol - get Wake-on-LAN support
 * @dev:	Network device.
 * @wol:	Ethtool Wake-on-LAN data काष्ठाure.
 *
 * This procedure वापसs Wake-on-LAN support.
 */
अटल व्योम netdev_get_wol(काष्ठा net_device *dev,
	काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा dev_priv *priv = netdev_priv(dev);
	काष्ठा dev_info *hw_priv = priv->adapter;

	wol->supported = hw_priv->wol_support;
	wol->wolopts = hw_priv->wol_enable;
	स_रखो(&wol->sopass, 0, माप(wol->sopass));
पूर्ण

/**
 * netdev_set_wol - set Wake-on-LAN support
 * @dev:	Network device.
 * @wol:	Ethtool Wake-on-LAN data काष्ठाure.
 *
 * This function sets Wake-on-LAN support.
 *
 * Return 0 अगर successful; otherwise an error code.
 */
अटल पूर्णांक netdev_set_wol(काष्ठा net_device *dev,
	काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा dev_priv *priv = netdev_priv(dev);
	काष्ठा dev_info *hw_priv = priv->adapter;

	/* Need to find a way to retrieve the device IP address. */
	अटल स्थिर u8 net_addr[] = अणु 192, 168, 1, 1 पूर्ण;

	अगर (wol->wolopts & ~hw_priv->wol_support)
		वापस -EINVAL;

	hw_priv->wol_enable = wol->wolopts;

	/* Link wakeup cannot really be disabled. */
	अगर (wol->wolopts)
		hw_priv->wol_enable |= WAKE_PHY;
	hw_enable_wol(&hw_priv->hw, hw_priv->wol_enable, net_addr);
	वापस 0;
पूर्ण

/**
 * netdev_get_msglevel - get debug message level
 * @dev:	Network device.
 *
 * This function वापसs current debug message level.
 *
 * Return current debug message flags.
 */
अटल u32 netdev_get_msglevel(काष्ठा net_device *dev)
अणु
	काष्ठा dev_priv *priv = netdev_priv(dev);

	वापस priv->msg_enable;
पूर्ण

/**
 * netdev_set_msglevel - set debug message level
 * @dev:	Network device.
 * @value:	Debug message flags.
 *
 * This procedure sets debug message level.
 */
अटल व्योम netdev_set_msglevel(काष्ठा net_device *dev, u32 value)
अणु
	काष्ठा dev_priv *priv = netdev_priv(dev);

	priv->msg_enable = value;
पूर्ण

/**
 * netdev_get_eeprom_len - get EEPROM length
 * @dev:	Network device.
 *
 * This function वापसs the length of the EEPROM.
 *
 * Return length of the EEPROM.
 */
अटल पूर्णांक netdev_get_eeprom_len(काष्ठा net_device *dev)
अणु
	वापस EEPROM_SIZE * 2;
पूर्ण

#घोषणा EEPROM_MAGIC			0x10A18842

/**
 * netdev_get_eeprom - get EEPROM data
 * @dev:	Network device.
 * @eeprom:	Ethtool EEPROM data काष्ठाure.
 * @data:	Buffer to store the EEPROM data.
 *
 * This function dumps the EEPROM data in the provided buffer.
 *
 * Return 0 अगर successful; otherwise an error code.
 */
अटल पूर्णांक netdev_get_eeprom(काष्ठा net_device *dev,
	काष्ठा ethtool_eeprom *eeprom, u8 *data)
अणु
	काष्ठा dev_priv *priv = netdev_priv(dev);
	काष्ठा dev_info *hw_priv = priv->adapter;
	u8 *eeprom_byte = (u8 *) eeprom_data;
	पूर्णांक i;
	पूर्णांक len;

	len = (eeprom->offset + eeprom->len + 1) / 2;
	क्रम (i = eeprom->offset / 2; i < len; i++)
		eeprom_data[i] = eeprom_पढ़ो(&hw_priv->hw, i);
	eeprom->magic = EEPROM_MAGIC;
	स_नकल(data, &eeprom_byte[eeprom->offset], eeprom->len);

	वापस 0;
पूर्ण

/**
 * netdev_set_eeprom - ग_लिखो EEPROM data
 * @dev:	Network device.
 * @eeprom:	Ethtool EEPROM data काष्ठाure.
 * @data:	Data buffer.
 *
 * This function modअगरies the EEPROM data one byte at a समय.
 *
 * Return 0 अगर successful; otherwise an error code.
 */
अटल पूर्णांक netdev_set_eeprom(काष्ठा net_device *dev,
	काष्ठा ethtool_eeprom *eeprom, u8 *data)
अणु
	काष्ठा dev_priv *priv = netdev_priv(dev);
	काष्ठा dev_info *hw_priv = priv->adapter;
	u16 eeprom_word[EEPROM_SIZE];
	u8 *eeprom_byte = (u8 *) eeprom_word;
	पूर्णांक i;
	पूर्णांक len;

	अगर (eeprom->magic != EEPROM_MAGIC)
		वापस -EINVAL;

	len = (eeprom->offset + eeprom->len + 1) / 2;
	क्रम (i = eeprom->offset / 2; i < len; i++)
		eeprom_data[i] = eeprom_पढ़ो(&hw_priv->hw, i);
	स_नकल(eeprom_word, eeprom_data, EEPROM_SIZE * 2);
	स_नकल(&eeprom_byte[eeprom->offset], data, eeprom->len);
	क्रम (i = 0; i < EEPROM_SIZE; i++)
		अगर (eeprom_word[i] != eeprom_data[i]) अणु
			eeprom_data[i] = eeprom_word[i];
			eeprom_ग_लिखो(&hw_priv->hw, i, eeprom_data[i]);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * netdev_get_छोड़ोparam - get flow control parameters
 * @dev:	Network device.
 * @छोड़ो:	Ethtool PAUSE settings data काष्ठाure.
 *
 * This procedure वापसs the PAUSE control flow settings.
 */
अटल व्योम netdev_get_छोड़ोparam(काष्ठा net_device *dev,
	काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा dev_priv *priv = netdev_priv(dev);
	काष्ठा dev_info *hw_priv = priv->adapter;
	काष्ठा ksz_hw *hw = &hw_priv->hw;

	छोड़ो->स्वतःneg = (hw->overrides & PAUSE_FLOW_CTRL) ? 0 : 1;
	अगर (!hw->ksz_चयन) अणु
		छोड़ो->rx_छोड़ो =
			(hw->rx_cfg & DMA_RX_FLOW_ENABLE) ? 1 : 0;
		छोड़ो->tx_छोड़ो =
			(hw->tx_cfg & DMA_TX_FLOW_ENABLE) ? 1 : 0;
	पूर्ण अन्यथा अणु
		छोड़ो->rx_छोड़ो =
			(sw_chk(hw, KS8842_SWITCH_CTRL_1_OFFSET,
				SWITCH_RX_FLOW_CTRL)) ? 1 : 0;
		छोड़ो->tx_छोड़ो =
			(sw_chk(hw, KS8842_SWITCH_CTRL_1_OFFSET,
				SWITCH_TX_FLOW_CTRL)) ? 1 : 0;
	पूर्ण
पूर्ण

/**
 * netdev_set_छोड़ोparam - set flow control parameters
 * @dev:	Network device.
 * @छोड़ो:	Ethtool PAUSE settings data काष्ठाure.
 *
 * This function sets the PAUSE control flow settings.
 * Not implemented yet.
 *
 * Return 0 अगर successful; otherwise an error code.
 */
अटल पूर्णांक netdev_set_छोड़ोparam(काष्ठा net_device *dev,
	काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा dev_priv *priv = netdev_priv(dev);
	काष्ठा dev_info *hw_priv = priv->adapter;
	काष्ठा ksz_hw *hw = &hw_priv->hw;
	काष्ठा ksz_port *port = &priv->port;

	mutex_lock(&hw_priv->lock);
	अगर (छोड़ो->स्वतःneg) अणु
		अगर (!छोड़ो->rx_छोड़ो && !छोड़ो->tx_छोड़ो)
			port->flow_ctrl = PHY_NO_FLOW_CTRL;
		अन्यथा
			port->flow_ctrl = PHY_FLOW_CTRL;
		hw->overrides &= ~PAUSE_FLOW_CTRL;
		port->क्रमce_link = 0;
		अगर (hw->ksz_चयन) अणु
			sw_cfg(hw, KS8842_SWITCH_CTRL_1_OFFSET,
				SWITCH_RX_FLOW_CTRL, 1);
			sw_cfg(hw, KS8842_SWITCH_CTRL_1_OFFSET,
				SWITCH_TX_FLOW_CTRL, 1);
		पूर्ण
		port_set_link_speed(port);
	पूर्ण अन्यथा अणु
		hw->overrides |= PAUSE_FLOW_CTRL;
		अगर (hw->ksz_चयन) अणु
			sw_cfg(hw, KS8842_SWITCH_CTRL_1_OFFSET,
				SWITCH_RX_FLOW_CTRL, छोड़ो->rx_छोड़ो);
			sw_cfg(hw, KS8842_SWITCH_CTRL_1_OFFSET,
				SWITCH_TX_FLOW_CTRL, छोड़ो->tx_छोड़ो);
		पूर्ण अन्यथा
			set_flow_ctrl(hw, छोड़ो->rx_छोड़ो, छोड़ो->tx_छोड़ो);
	पूर्ण
	mutex_unlock(&hw_priv->lock);

	वापस 0;
पूर्ण

/**
 * netdev_get_ringparam - get tx/rx ring parameters
 * @dev:	Network device.
 * @ring:	Ethtool RING settings data काष्ठाure.
 *
 * This procedure वापसs the TX/RX ring settings.
 */
अटल व्योम netdev_get_ringparam(काष्ठा net_device *dev,
	काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा dev_priv *priv = netdev_priv(dev);
	काष्ठा dev_info *hw_priv = priv->adapter;
	काष्ठा ksz_hw *hw = &hw_priv->hw;

	ring->tx_max_pending = (1 << 9);
	ring->tx_pending = hw->tx_desc_info.alloc;
	ring->rx_max_pending = (1 << 9);
	ring->rx_pending = hw->rx_desc_info.alloc;
पूर्ण

#घोषणा STATS_LEN			(TOTAL_PORT_COUNTER_NUM)

अटल काष्ठा अणु
	अक्षर string[ETH_GSTRING_LEN];
पूर्ण ethtool_stats_keys[STATS_LEN] = अणु
	अणु "rx_lo_priority_octets" पूर्ण,
	अणु "rx_hi_priority_octets" पूर्ण,
	अणु "rx_undersize_packets" पूर्ण,
	अणु "rx_fragments" पूर्ण,
	अणु "rx_oversize_packets" पूर्ण,
	अणु "rx_jabbers" पूर्ण,
	अणु "rx_symbol_errors" पूर्ण,
	अणु "rx_crc_errors" पूर्ण,
	अणु "rx_align_errors" पूर्ण,
	अणु "rx_mac_ctrl_packets" पूर्ण,
	अणु "rx_pause_packets" पूर्ण,
	अणु "rx_bcast_packets" पूर्ण,
	अणु "rx_mcast_packets" पूर्ण,
	अणु "rx_ucast_packets" पूर्ण,
	अणु "rx_64_or_less_octet_packets" पूर्ण,
	अणु "rx_65_to_127_octet_packets" पूर्ण,
	अणु "rx_128_to_255_octet_packets" पूर्ण,
	अणु "rx_256_to_511_octet_packets" पूर्ण,
	अणु "rx_512_to_1023_octet_packets" पूर्ण,
	अणु "rx_1024_to_1522_octet_packets" पूर्ण,

	अणु "tx_lo_priority_octets" पूर्ण,
	अणु "tx_hi_priority_octets" पूर्ण,
	अणु "tx_late_collisions" पूर्ण,
	अणु "tx_pause_packets" पूर्ण,
	अणु "tx_bcast_packets" पूर्ण,
	अणु "tx_mcast_packets" पूर्ण,
	अणु "tx_ucast_packets" पूर्ण,
	अणु "tx_deferred" पूर्ण,
	अणु "tx_total_collisions" पूर्ण,
	अणु "tx_excessive_collisions" पूर्ण,
	अणु "tx_single_collisions" पूर्ण,
	अणु "tx_mult_collisions" पूर्ण,

	अणु "rx_discards" पूर्ण,
	अणु "tx_discards" पूर्ण,
पूर्ण;

/**
 * netdev_get_strings - get statistics identity strings
 * @dev:	Network device.
 * @stringset:	String set identअगरier.
 * @buf:	Buffer to store the strings.
 *
 * This procedure वापसs the strings used to identअगरy the statistics.
 */
अटल व्योम netdev_get_strings(काष्ठा net_device *dev, u32 stringset, u8 *buf)
अणु
	काष्ठा dev_priv *priv = netdev_priv(dev);
	काष्ठा dev_info *hw_priv = priv->adapter;
	काष्ठा ksz_hw *hw = &hw_priv->hw;

	अगर (ETH_SS_STATS == stringset)
		स_नकल(buf, &ethtool_stats_keys,
			ETH_GSTRING_LEN * hw->mib_cnt);
पूर्ण

/**
 * netdev_get_sset_count - get statistics size
 * @dev:	Network device.
 * @sset:	The statistics set number.
 *
 * This function वापसs the size of the statistics to be reported.
 *
 * Return size of the statistics to be reported.
 */
अटल पूर्णांक netdev_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	काष्ठा dev_priv *priv = netdev_priv(dev);
	काष्ठा dev_info *hw_priv = priv->adapter;
	काष्ठा ksz_hw *hw = &hw_priv->hw;

	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस hw->mib_cnt;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

/**
 * netdev_get_ethtool_stats - get network device statistics
 * @dev:	Network device.
 * @stats:	Ethtool statistics data काष्ठाure.
 * @data:	Buffer to store the statistics.
 *
 * This procedure वापसs the statistics.
 */
अटल व्योम netdev_get_ethtool_stats(काष्ठा net_device *dev,
	काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा dev_priv *priv = netdev_priv(dev);
	काष्ठा dev_info *hw_priv = priv->adapter;
	काष्ठा ksz_hw *hw = &hw_priv->hw;
	काष्ठा ksz_port *port = &priv->port;
	पूर्णांक n_stats = stats->n_stats;
	पूर्णांक i;
	पूर्णांक n;
	पूर्णांक p;
	u64 counter[TOTAL_PORT_COUNTER_NUM];

	mutex_lock(&hw_priv->lock);
	n = SWITCH_PORT_NUM;
	क्रम (i = 0, p = port->first_port; i < port->mib_port_cnt; i++, p++) अणु
		अगर (media_connected == hw->port_mib[p].state) अणु
			hw_priv->counter[p].पढ़ो = 1;

			/* Remember first port that requests पढ़ो. */
			अगर (n == SWITCH_PORT_NUM)
				n = p;
		पूर्ण
	पूर्ण
	mutex_unlock(&hw_priv->lock);

	अगर (n < SWITCH_PORT_NUM)
		schedule_work(&hw_priv->mib_पढ़ो);

	अगर (1 == port->mib_port_cnt && n < SWITCH_PORT_NUM) अणु
		p = n;
		रुको_event_पूर्णांकerruptible_समयout(
			hw_priv->counter[p].counter,
			2 == hw_priv->counter[p].पढ़ो,
			HZ * 1);
	पूर्ण अन्यथा
		क्रम (i = 0, p = n; i < port->mib_port_cnt - n; i++, p++) अणु
			अगर (0 == i) अणु
				रुको_event_पूर्णांकerruptible_समयout(
					hw_priv->counter[p].counter,
					2 == hw_priv->counter[p].पढ़ो,
					HZ * 2);
			पूर्ण अन्यथा अगर (hw->port_mib[p].cnt_ptr) अणु
				रुको_event_पूर्णांकerruptible_समयout(
					hw_priv->counter[p].counter,
					2 == hw_priv->counter[p].पढ़ो,
					HZ * 1);
			पूर्ण
		पूर्ण

	get_mib_counters(hw, port->first_port, port->mib_port_cnt, counter);
	n = hw->mib_cnt;
	अगर (n > n_stats)
		n = n_stats;
	n_stats -= n;
	क्रम (i = 0; i < n; i++)
		*data++ = counter[i];
पूर्ण

/**
 * netdev_set_features - set receive checksum support
 * @dev:	Network device.
 * @features:	New device features (offloads).
 *
 * This function sets receive checksum support setting.
 *
 * Return 0 अगर successful; otherwise an error code.
 */
अटल पूर्णांक netdev_set_features(काष्ठा net_device *dev,
	netdev_features_t features)
अणु
	काष्ठा dev_priv *priv = netdev_priv(dev);
	काष्ठा dev_info *hw_priv = priv->adapter;
	काष्ठा ksz_hw *hw = &hw_priv->hw;

	mutex_lock(&hw_priv->lock);

	/* see note in hw_setup() */
	अगर (features & NETIF_F_RXCSUM)
		hw->rx_cfg |= DMA_RX_CSUM_TCP | DMA_RX_CSUM_IP;
	अन्यथा
		hw->rx_cfg &= ~(DMA_RX_CSUM_TCP | DMA_RX_CSUM_IP);

	अगर (hw->enabled)
		ग_लिखोl(hw->rx_cfg, hw->io + KS_DMA_RX_CTRL);

	mutex_unlock(&hw_priv->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops netdev_ethtool_ops = अणु
	.nway_reset		= netdev_nway_reset,
	.get_link		= netdev_get_link,
	.get_drvinfo		= netdev_get_drvinfo,
	.get_regs_len		= netdev_get_regs_len,
	.get_regs		= netdev_get_regs,
	.get_wol		= netdev_get_wol,
	.set_wol		= netdev_set_wol,
	.get_msglevel		= netdev_get_msglevel,
	.set_msglevel		= netdev_set_msglevel,
	.get_eeprom_len		= netdev_get_eeprom_len,
	.get_eeprom		= netdev_get_eeprom,
	.set_eeprom		= netdev_set_eeprom,
	.get_छोड़ोparam		= netdev_get_छोड़ोparam,
	.set_छोड़ोparam		= netdev_set_छोड़ोparam,
	.get_ringparam		= netdev_get_ringparam,
	.get_strings		= netdev_get_strings,
	.get_sset_count		= netdev_get_sset_count,
	.get_ethtool_stats	= netdev_get_ethtool_stats,
	.get_link_ksettings	= netdev_get_link_ksettings,
	.set_link_ksettings	= netdev_set_link_ksettings,
पूर्ण;

/*
 * Hardware monitoring
 */

अटल व्योम update_link(काष्ठा net_device *dev, काष्ठा dev_priv *priv,
	काष्ठा ksz_port *port)
अणु
	अगर (priv->media_state != port->linked->state) अणु
		priv->media_state = port->linked->state;
		अगर (netअगर_running(dev))
			set_media_state(dev, media_connected);
	पूर्ण
पूर्ण

अटल व्योम mib_पढ़ो_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dev_info *hw_priv =
		container_of(work, काष्ठा dev_info, mib_पढ़ो);
	काष्ठा ksz_hw *hw = &hw_priv->hw;
	काष्ठा ksz_port_mib *mib;
	पूर्णांक i;

	next_jअगरfies = jअगरfies;
	क्रम (i = 0; i < hw->mib_port_cnt; i++) अणु
		mib = &hw->port_mib[i];

		/* Reading MIB counters or requested to पढ़ो. */
		अगर (mib->cnt_ptr || 1 == hw_priv->counter[i].पढ़ो) अणु

			/* Need to process receive पूर्णांकerrupt. */
			अगर (port_r_cnt(hw, i))
				अवरोध;
			hw_priv->counter[i].पढ़ो = 0;

			/* Finish पढ़ोing counters. */
			अगर (0 == mib->cnt_ptr) अणु
				hw_priv->counter[i].पढ़ो = 2;
				wake_up_पूर्णांकerruptible(
					&hw_priv->counter[i].counter);
			पूर्ण
		पूर्ण अन्यथा अगर (समय_after_eq(jअगरfies, hw_priv->counter[i].समय)) अणु
			/* Only पढ़ो MIB counters when the port is connected. */
			अगर (media_connected == mib->state)
				hw_priv->counter[i].पढ़ो = 1;
			next_jअगरfies += HZ * 1 * hw->mib_port_cnt;
			hw_priv->counter[i].समय = next_jअगरfies;

		/* Port is just disconnected. */
		पूर्ण अन्यथा अगर (mib->link_करोwn) अणु
			mib->link_करोwn = 0;

			/* Read counters one last समय after link is lost. */
			hw_priv->counter[i].पढ़ो = 1;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम mib_monitor(काष्ठा समयr_list *t)
अणु
	काष्ठा dev_info *hw_priv = from_समयr(hw_priv, t, mib_समयr_info.समयr);

	mib_पढ़ो_work(&hw_priv->mib_पढ़ो);

	/* This is used to verअगरy Wake-on-LAN is working. */
	अगर (hw_priv->pme_रुको) अणु
		अगर (समय_is_beक्रमe_eq_jअगरfies(hw_priv->pme_रुको)) अणु
			hw_clr_wol_pme_status(&hw_priv->hw);
			hw_priv->pme_रुको = 0;
		पूर्ण
	पूर्ण अन्यथा अगर (hw_chk_wol_pme_status(&hw_priv->hw)) अणु

		/* PME is निश्चितed.  Wait 2 seconds to clear it. */
		hw_priv->pme_रुको = jअगरfies + HZ * 2;
	पूर्ण

	ksz_update_समयr(&hw_priv->mib_समयr_info);
पूर्ण

/**
 * dev_monitor - periodic monitoring
 * @t:	समयr list containing a network device poपूर्णांकer.
 *
 * This routine is run in a kernel समयr to monitor the network device.
 */
अटल व्योम dev_monitor(काष्ठा समयr_list *t)
अणु
	काष्ठा dev_priv *priv = from_समयr(priv, t, monitor_समयr_info.समयr);
	काष्ठा net_device *dev = priv->mii_अगर.dev;
	काष्ठा dev_info *hw_priv = priv->adapter;
	काष्ठा ksz_hw *hw = &hw_priv->hw;
	काष्ठा ksz_port *port = &priv->port;

	अगर (!(hw->features & LINK_INT_WORKING))
		port_get_link_speed(port);
	update_link(dev, priv, port);

	ksz_update_समयr(&priv->monitor_समयr_info);
पूर्ण

/*
 * Linux network device पूर्णांकerface functions
 */

/* Driver exported variables */

अटल पूर्णांक msg_enable;

अटल अक्षर *macaddr = ":";
अटल अक्षर *mac1addr = ":";

/*
 * This enables multiple network device mode क्रम KSZ8842, which contains a
 * चयन with two physical ports.  Some users like to take control of the
 * ports क्रम running Spanning Tree Protocol.  The driver will create an
 * additional eth? device क्रम the other port.
 *
 * Some limitations are the network devices cannot have dअगरferent MTU and
 * multicast hash tables.
 */
अटल पूर्णांक multi_dev;

/*
 * As most users select multiple network device mode to use Spanning Tree
 * Protocol, this enables a feature in which most unicast and multicast packets
 * are क्रमwarded inside the चयन and not passed to the host.  Only packets
 * that need the host's attention are passed to it.  This prevents the host
 * wasting CPU समय to examine each and every incoming packets and करो the
 * क्रमwarding itself.
 *
 * As the hack requires the निजी bridge header, the driver cannot compile
 * with just the kernel headers.
 *
 * Enabling STP support also turns on multiple network device mode.
 */
अटल पूर्णांक stp;

/*
 * This enables fast aging in the KSZ8842 चयन.  Not sure what situation
 * needs that.  However, fast aging is used to flush the dynamic MAC table when
 * STP support is enabled.
 */
अटल पूर्णांक fast_aging;

/**
 * netdev_init - initialize network device.
 * @dev:	Network device.
 *
 * This function initializes the network device.
 *
 * Return 0 अगर successful; otherwise an error code indicating failure.
 */
अटल पूर्णांक __init netdev_init(काष्ठा net_device *dev)
अणु
	काष्ठा dev_priv *priv = netdev_priv(dev);

	/* 500 ms समयout */
	ksz_init_समयr(&priv->monitor_समयr_info, 500 * HZ / 1000,
		dev_monitor);

	/* 500 ms समयout */
	dev->watchकरोg_समयo = HZ / 2;

	dev->hw_features = NETIF_F_IP_CSUM | NETIF_F_SG | NETIF_F_RXCSUM;

	/*
	 * Hardware करोes not really support IPv6 checksum generation, but
	 * driver actually runs faster with this on.
	 */
	dev->hw_features |= NETIF_F_IPV6_CSUM;

	dev->features |= dev->hw_features;

	sema_init(&priv->proc_sem, 1);

	priv->mii_अगर.phy_id_mask = 0x1;
	priv->mii_अगर.reg_num_mask = 0x7;
	priv->mii_अगर.dev = dev;
	priv->mii_अगर.mdio_पढ़ो = mdio_पढ़ो;
	priv->mii_अगर.mdio_ग_लिखो = mdio_ग_लिखो;
	priv->mii_अगर.phy_id = priv->port.first_port + 1;

	priv->msg_enable = netअगर_msg_init(msg_enable,
		(NETIF_MSG_DRV | NETIF_MSG_PROBE | NETIF_MSG_LINK));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops netdev_ops = अणु
	.nकरो_init		= netdev_init,
	.nकरो_खोलो		= netdev_खोलो,
	.nकरो_stop		= netdev_बंद,
	.nकरो_get_stats		= netdev_query_statistics,
	.nकरो_start_xmit		= netdev_tx,
	.nकरो_tx_समयout		= netdev_tx_समयout,
	.nकरो_change_mtu		= netdev_change_mtu,
	.nकरो_set_features	= netdev_set_features,
	.nकरो_set_mac_address	= netdev_set_mac_address,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_करो_ioctl		= netdev_ioctl,
	.nकरो_set_rx_mode	= netdev_set_rx_mode,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= netdev_netpoll,
#पूर्ण_अगर
पूर्ण;

अटल व्योम netdev_मुक्त(काष्ठा net_device *dev)
अणु
	अगर (dev->watchकरोg_समयo)
		unरेजिस्टर_netdev(dev);

	मुक्त_netdev(dev);
पूर्ण

काष्ठा platक्रमm_info अणु
	काष्ठा dev_info dev_info;
	काष्ठा net_device *netdev[SWITCH_PORT_NUM];
पूर्ण;

अटल पूर्णांक net_device_present;

अटल व्योम get_mac_addr(काष्ठा dev_info *hw_priv, u8 *macaddr, पूर्णांक port)
अणु
	पूर्णांक i;
	पूर्णांक j;
	पूर्णांक got_num;
	पूर्णांक num;

	i = j = num = got_num = 0;
	जबतक (j < ETH_ALEN) अणु
		अगर (macaddr[i]) अणु
			पूर्णांक digit;

			got_num = 1;
			digit = hex_to_bin(macaddr[i]);
			अगर (digit >= 0)
				num = num * 16 + digit;
			अन्यथा अगर (':' == macaddr[i])
				got_num = 2;
			अन्यथा
				अवरोध;
		पूर्ण अन्यथा अगर (got_num)
			got_num = 2;
		अन्यथा
			अवरोध;
		अगर (2 == got_num) अणु
			अगर (MAIN_PORT == port) अणु
				hw_priv->hw.override_addr[j++] = (u8) num;
				hw_priv->hw.override_addr[5] +=
					hw_priv->hw.id;
			पूर्ण अन्यथा अणु
				hw_priv->hw.ksz_चयन->other_addr[j++] =
					(u8) num;
				hw_priv->hw.ksz_चयन->other_addr[5] +=
					hw_priv->hw.id;
			पूर्ण
			num = got_num = 0;
		पूर्ण
		i++;
	पूर्ण
	अगर (ETH_ALEN == j) अणु
		अगर (MAIN_PORT == port)
			hw_priv->hw.mac_override = 1;
	पूर्ण
पूर्ण

#घोषणा KS884X_DMA_MASK			(~0x0UL)

अटल व्योम पढ़ो_other_addr(काष्ठा ksz_hw *hw)
अणु
	पूर्णांक i;
	u16 data[3];
	काष्ठा ksz_चयन *sw = hw->ksz_चयन;

	क्रम (i = 0; i < 3; i++)
		data[i] = eeprom_पढ़ो(hw, i + EEPROM_DATA_OTHER_MAC_ADDR);
	अगर ((data[0] || data[1] || data[2]) && data[0] != 0xffff) अणु
		sw->other_addr[5] = (u8) data[0];
		sw->other_addr[4] = (u8)(data[0] >> 8);
		sw->other_addr[3] = (u8) data[1];
		sw->other_addr[2] = (u8)(data[1] >> 8);
		sw->other_addr[1] = (u8) data[2];
		sw->other_addr[0] = (u8)(data[2] >> 8);
	पूर्ण
पूर्ण

#अगर_अघोषित PCI_VENDOR_ID_MICREL_KS
#घोषणा PCI_VENDOR_ID_MICREL_KS		0x16c6
#पूर्ण_अगर

अटल पूर्णांक pcidev_init(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा net_device *dev;
	काष्ठा dev_priv *priv;
	काष्ठा dev_info *hw_priv;
	काष्ठा ksz_hw *hw;
	काष्ठा platक्रमm_info *info;
	काष्ठा ksz_port *port;
	अचिन्हित दीर्घ reg_base;
	अचिन्हित दीर्घ reg_len;
	पूर्णांक cnt;
	पूर्णांक i;
	पूर्णांक mib_port_count;
	पूर्णांक pi;
	पूर्णांक port_count;
	पूर्णांक result;
	अक्षर banner[माप(version)];
	काष्ठा ksz_चयन *sw = शून्य;

	result = pci_enable_device(pdev);
	अगर (result)
		वापस result;

	result = -ENODEV;

	अगर (dma_set_mask(&pdev->dev, DMA_BIT_MASK(32)) ||
	    dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(32)))
		वापस result;

	reg_base = pci_resource_start(pdev, 0);
	reg_len = pci_resource_len(pdev, 0);
	अगर ((pci_resource_flags(pdev, 0) & IORESOURCE_IO) != 0)
		वापस result;

	अगर (!request_mem_region(reg_base, reg_len, DRV_NAME))
		वापस result;
	pci_set_master(pdev);

	result = -ENOMEM;

	info = kzalloc(माप(काष्ठा platक्रमm_info), GFP_KERNEL);
	अगर (!info)
		जाओ pcidev_init_dev_err;

	hw_priv = &info->dev_info;
	hw_priv->pdev = pdev;

	hw = &hw_priv->hw;

	hw->io = ioremap(reg_base, reg_len);
	अगर (!hw->io)
		जाओ pcidev_init_io_err;

	cnt = hw_init(hw);
	अगर (!cnt) अणु
		अगर (msg_enable & NETIF_MSG_PROBE)
			pr_alert("chip not detected\n");
		result = -ENODEV;
		जाओ pcidev_init_alloc_err;
	पूर्ण

	snम_लिखो(banner, माप(banner), "%s", version);
	banner[13] = cnt + '0';		/* Replace x in "Micrel KSZ884x" */
	dev_info(&hw_priv->pdev->dev, "%s\n", banner);
	dev_dbg(&hw_priv->pdev->dev, "Mem = %p; IRQ = %d\n", hw->io, pdev->irq);

	/* Assume device is KSZ8841. */
	hw->dev_count = 1;
	port_count = 1;
	mib_port_count = 1;
	hw->addr_list_size = 0;
	hw->mib_cnt = PORT_COUNTER_NUM;
	hw->mib_port_cnt = 1;

	/* KSZ8842 has a चयन with multiple ports. */
	अगर (2 == cnt) अणु
		अगर (fast_aging)
			hw->overrides |= FAST_AGING;

		hw->mib_cnt = TOTAL_PORT_COUNTER_NUM;

		/* Multiple network device पूर्णांकerfaces are required. */
		अगर (multi_dev) अणु
			hw->dev_count = SWITCH_PORT_NUM;
			hw->addr_list_size = SWITCH_PORT_NUM - 1;
		पूर्ण

		/* Single network device has multiple ports. */
		अगर (1 == hw->dev_count) अणु
			port_count = SWITCH_PORT_NUM;
			mib_port_count = SWITCH_PORT_NUM;
		पूर्ण
		hw->mib_port_cnt = TOTAL_PORT_NUM;
		hw->ksz_चयन = kzalloc(माप(काष्ठा ksz_चयन), GFP_KERNEL);
		अगर (!hw->ksz_चयन)
			जाओ pcidev_init_alloc_err;

		sw = hw->ksz_चयन;
	पूर्ण
	क्रम (i = 0; i < hw->mib_port_cnt; i++)
		hw->port_mib[i].mib_start = 0;

	hw->parent = hw_priv;

	/* Default MTU is 1500. */
	hw_priv->mtu = (REGULAR_RX_BUF_SIZE + 3) & ~3;

	अगर (ksz_alloc_mem(hw_priv))
		जाओ pcidev_init_mem_err;

	hw_priv->hw.id = net_device_present;

	spin_lock_init(&hw_priv->hwlock);
	mutex_init(&hw_priv->lock);

	क्रम (i = 0; i < TOTAL_PORT_NUM; i++)
		init_रुकोqueue_head(&hw_priv->counter[i].counter);

	अगर (macaddr[0] != ':')
		get_mac_addr(hw_priv, macaddr, MAIN_PORT);

	/* Read MAC address and initialize override address अगर not overridden. */
	hw_पढ़ो_addr(hw);

	/* Multiple device पूर्णांकerfaces mode requires a second MAC address. */
	अगर (hw->dev_count > 1) अणु
		स_नकल(sw->other_addr, hw->override_addr, ETH_ALEN);
		पढ़ो_other_addr(hw);
		अगर (mac1addr[0] != ':')
			get_mac_addr(hw_priv, mac1addr, OTHER_PORT);
	पूर्ण

	hw_setup(hw);
	अगर (hw->ksz_चयन)
		sw_setup(hw);
	अन्यथा अणु
		hw_priv->wol_support = WOL_SUPPORT;
		hw_priv->wol_enable = 0;
	पूर्ण

	INIT_WORK(&hw_priv->mib_पढ़ो, mib_पढ़ो_work);

	/* 500 ms समयout */
	ksz_init_समयr(&hw_priv->mib_समयr_info, 500 * HZ / 1000,
		mib_monitor);

	क्रम (i = 0; i < hw->dev_count; i++) अणु
		dev = alloc_etherdev(माप(काष्ठा dev_priv));
		अगर (!dev)
			जाओ pcidev_init_reg_err;
		SET_NETDEV_DEV(dev, &pdev->dev);
		info->netdev[i] = dev;

		priv = netdev_priv(dev);
		priv->adapter = hw_priv;
		priv->id = net_device_present++;

		port = &priv->port;
		port->port_cnt = port_count;
		port->mib_port_cnt = mib_port_count;
		port->first_port = i;
		port->flow_ctrl = PHY_FLOW_CTRL;

		port->hw = hw;
		port->linked = &hw->port_info[port->first_port];

		क्रम (cnt = 0, pi = i; cnt < port_count; cnt++, pi++) अणु
			hw->port_info[pi].port_id = pi;
			hw->port_info[pi].pdev = dev;
			hw->port_info[pi].state = media_disconnected;
		पूर्ण

		dev->mem_start = (अचिन्हित दीर्घ) hw->io;
		dev->mem_end = dev->mem_start + reg_len - 1;
		dev->irq = pdev->irq;
		अगर (MAIN_PORT == i)
			स_नकल(dev->dev_addr, hw_priv->hw.override_addr,
			       ETH_ALEN);
		अन्यथा अणु
			स_नकल(dev->dev_addr, sw->other_addr, ETH_ALEN);
			अगर (ether_addr_equal(sw->other_addr, hw->override_addr))
				dev->dev_addr[5] += port->first_port;
		पूर्ण

		dev->netdev_ops = &netdev_ops;
		dev->ethtool_ops = &netdev_ethtool_ops;

		/* MTU range: 60 - 1894 */
		dev->min_mtu = ETH_ZLEN;
		dev->max_mtu = MAX_RX_BUF_SIZE -
			       (ETH_HLEN + ETH_FCS_LEN + VLAN_HLEN);

		अगर (रेजिस्टर_netdev(dev))
			जाओ pcidev_init_reg_err;
		port_set_घातer_saving(port, true);
	पूर्ण

	pci_dev_get(hw_priv->pdev);
	pci_set_drvdata(pdev, info);
	वापस 0;

pcidev_init_reg_err:
	क्रम (i = 0; i < hw->dev_count; i++) अणु
		अगर (info->netdev[i]) अणु
			netdev_मुक्त(info->netdev[i]);
			info->netdev[i] = शून्य;
		पूर्ण
	पूर्ण

pcidev_init_mem_err:
	ksz_मुक्त_mem(hw_priv);
	kमुक्त(hw->ksz_चयन);

pcidev_init_alloc_err:
	iounmap(hw->io);

pcidev_init_io_err:
	kमुक्त(info);

pcidev_init_dev_err:
	release_mem_region(reg_base, reg_len);

	वापस result;
पूर्ण

अटल व्योम pcidev_निकास(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक i;
	काष्ठा platक्रमm_info *info = pci_get_drvdata(pdev);
	काष्ठा dev_info *hw_priv = &info->dev_info;

	release_mem_region(pci_resource_start(pdev, 0),
		pci_resource_len(pdev, 0));
	क्रम (i = 0; i < hw_priv->hw.dev_count; i++) अणु
		अगर (info->netdev[i])
			netdev_मुक्त(info->netdev[i]);
	पूर्ण
	अगर (hw_priv->hw.io)
		iounmap(hw_priv->hw.io);
	ksz_मुक्त_mem(hw_priv);
	kमुक्त(hw_priv->hw.ksz_चयन);
	pci_dev_put(hw_priv->pdev);
	kमुक्त(info);
पूर्ण

अटल पूर्णांक __maybe_unused pcidev_resume(काष्ठा device *dev_d)
अणु
	पूर्णांक i;
	काष्ठा platक्रमm_info *info = dev_get_drvdata(dev_d);
	काष्ठा dev_info *hw_priv = &info->dev_info;
	काष्ठा ksz_hw *hw = &hw_priv->hw;

	device_wakeup_disable(dev_d);

	अगर (hw_priv->wol_enable)
		hw_cfg_wol_pme(hw, 0);
	क्रम (i = 0; i < hw->dev_count; i++) अणु
		अगर (info->netdev[i]) अणु
			काष्ठा net_device *dev = info->netdev[i];

			अगर (netअगर_running(dev)) अणु
				netdev_खोलो(dev);
				netअगर_device_attach(dev);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused pcidev_suspend(काष्ठा device *dev_d)
अणु
	पूर्णांक i;
	काष्ठा platक्रमm_info *info = dev_get_drvdata(dev_d);
	काष्ठा dev_info *hw_priv = &info->dev_info;
	काष्ठा ksz_hw *hw = &hw_priv->hw;

	/* Need to find a way to retrieve the device IP address. */
	अटल स्थिर u8 net_addr[] = अणु 192, 168, 1, 1 पूर्ण;

	क्रम (i = 0; i < hw->dev_count; i++) अणु
		अगर (info->netdev[i]) अणु
			काष्ठा net_device *dev = info->netdev[i];

			अगर (netअगर_running(dev)) अणु
				netअगर_device_detach(dev);
				netdev_बंद(dev);
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (hw_priv->wol_enable) अणु
		hw_enable_wol(hw, hw_priv->wol_enable, net_addr);
		hw_cfg_wol_pme(hw, 1);
	पूर्ण

	device_wakeup_enable(dev_d);
	वापस 0;
पूर्ण

अटल अक्षर pcidev_name[] = "ksz884xp";

अटल स्थिर काष्ठा pci_device_id pcidev_table[] = अणु
	अणु PCI_VENDOR_ID_MICREL_KS, 0x8841,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_MICREL_KS, 0x8842,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, pcidev_table);

अटल SIMPLE_DEV_PM_OPS(pcidev_pm_ops, pcidev_suspend, pcidev_resume);

अटल काष्ठा pci_driver pci_device_driver = अणु
	.driver.pm	= &pcidev_pm_ops,
	.name		= pcidev_name,
	.id_table	= pcidev_table,
	.probe		= pcidev_init,
	.हटाओ		= pcidev_निकास
पूर्ण;

module_pci_driver(pci_device_driver);

MODULE_DESCRIPTION("KSZ8841/2 PCI network driver");
MODULE_AUTHOR("Tristram Ha <Tristram.Ha@micrel.com>");
MODULE_LICENSE("GPL");

module_param_named(message, msg_enable, पूर्णांक, 0);
MODULE_PARM_DESC(message, "Message verbosity level (0=none, 31=all)");

module_param(macaddr, अक्षरp, 0);
module_param(mac1addr, अक्षरp, 0);
module_param(fast_aging, पूर्णांक, 0);
module_param(multi_dev, पूर्णांक, 0);
module_param(stp, पूर्णांक, 0);
MODULE_PARM_DESC(macaddr, "MAC address");
MODULE_PARM_DESC(mac1addr, "Second MAC address");
MODULE_PARM_DESC(fast_aging, "Fast aging");
MODULE_PARM_DESC(multi_dev, "Multiple device interfaces");
MODULE_PARM_DESC(stp, "STP support");
