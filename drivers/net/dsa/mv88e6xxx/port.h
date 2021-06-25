<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Marvell 88E6xxx Switch Port Registers support
 *
 * Copyright (c) 2008 Marvell Semiconductor
 *
 * Copyright (c) 2016-2017 Savoir-faire Linux Inc.
 *	Vivien Didelot <vivien.didelot@savoirfairelinux.com>
 */

#अगर_अघोषित _MV88E6XXX_PORT_H
#घोषणा _MV88E6XXX_PORT_H

#समावेश "chip.h"

/* Offset 0x00: Port Status Register */
#घोषणा MV88E6XXX_PORT_STS			0x00
#घोषणा MV88E6XXX_PORT_STS_PAUSE_EN		0x8000
#घोषणा MV88E6XXX_PORT_STS_MY_PAUSE		0x4000
#घोषणा MV88E6XXX_PORT_STS_HD_FLOW		0x2000
#घोषणा MV88E6XXX_PORT_STS_PHY_DETECT		0x1000
#घोषणा MV88E6250_PORT_STS_LINK				0x1000
#घोषणा MV88E6250_PORT_STS_PORTMODE_MASK		0x0f00
#घोषणा MV88E6250_PORT_STS_PORTMODE_PHY_10_HALF		0x0800
#घोषणा MV88E6250_PORT_STS_PORTMODE_PHY_100_HALF	0x0900
#घोषणा MV88E6250_PORT_STS_PORTMODE_PHY_10_FULL		0x0a00
#घोषणा MV88E6250_PORT_STS_PORTMODE_PHY_100_FULL	0x0b00
#घोषणा MV88E6250_PORT_STS_PORTMODE_MII_10_HALF		0x0c00
#घोषणा MV88E6250_PORT_STS_PORTMODE_MII_100_HALF	0x0d00
#घोषणा MV88E6250_PORT_STS_PORTMODE_MII_10_FULL		0x0e00
#घोषणा MV88E6250_PORT_STS_PORTMODE_MII_100_FULL	0x0f00
#घोषणा MV88E6XXX_PORT_STS_LINK			0x0800
#घोषणा MV88E6XXX_PORT_STS_DUPLEX		0x0400
#घोषणा MV88E6XXX_PORT_STS_SPEED_MASK		0x0300
#घोषणा MV88E6XXX_PORT_STS_SPEED_10		0x0000
#घोषणा MV88E6XXX_PORT_STS_SPEED_100		0x0100
#घोषणा MV88E6XXX_PORT_STS_SPEED_1000		0x0200
#घोषणा MV88E6XXX_PORT_STS_SPEED_10000		0x0300
#घोषणा MV88E6352_PORT_STS_EEE			0x0040
#घोषणा MV88E6165_PORT_STS_AM_DIS		0x0040
#घोषणा MV88E6185_PORT_STS_MGMII		0x0040
#घोषणा MV88E6XXX_PORT_STS_TX_PAUSED		0x0020
#घोषणा MV88E6XXX_PORT_STS_FLOW_CTL		0x0010
#घोषणा MV88E6XXX_PORT_STS_CMODE_MASK		0x000f
#घोषणा MV88E6XXX_PORT_STS_CMODE_RGMII		0x0007
#घोषणा MV88E6XXX_PORT_STS_CMODE_100BASEX	0x0008
#घोषणा MV88E6XXX_PORT_STS_CMODE_1000BASEX	0x0009
#घोषणा MV88E6XXX_PORT_STS_CMODE_SGMII		0x000a
#घोषणा MV88E6XXX_PORT_STS_CMODE_2500BASEX	0x000b
#घोषणा MV88E6XXX_PORT_STS_CMODE_XAUI		0x000c
#घोषणा MV88E6XXX_PORT_STS_CMODE_RXAUI		0x000d
#घोषणा MV88E6393X_PORT_STS_CMODE_5GBASER	0x000c
#घोषणा MV88E6393X_PORT_STS_CMODE_10GBASER	0x000d
#घोषणा MV88E6393X_PORT_STS_CMODE_USXGMII	0x000e
#घोषणा MV88E6185_PORT_STS_CDUPLEX		0x0008
#घोषणा MV88E6185_PORT_STS_CMODE_MASK		0x0007
#घोषणा MV88E6185_PORT_STS_CMODE_GMII_FD	0x0000
#घोषणा MV88E6185_PORT_STS_CMODE_MII_100_FD_PS	0x0001
#घोषणा MV88E6185_PORT_STS_CMODE_MII_100	0x0002
#घोषणा MV88E6185_PORT_STS_CMODE_MII_10		0x0003
#घोषणा MV88E6185_PORT_STS_CMODE_SERDES		0x0004
#घोषणा MV88E6185_PORT_STS_CMODE_1000BASE_X	0x0005
#घोषणा MV88E6185_PORT_STS_CMODE_PHY		0x0006
#घोषणा MV88E6185_PORT_STS_CMODE_DISABLED	0x0007

/* Offset 0x01: MAC (or PCS or Physical) Control Register */
#घोषणा MV88E6XXX_PORT_MAC_CTL				0x01
#घोषणा MV88E6XXX_PORT_MAC_CTL_RGMII_DELAY_RXCLK	0x8000
#घोषणा MV88E6XXX_PORT_MAC_CTL_RGMII_DELAY_TXCLK	0x4000
#घोषणा MV88E6185_PORT_MAC_CTL_SYNC_OK			0x4000
#घोषणा MV88E6390_PORT_MAC_CTL_FORCE_SPEED		0x2000
#घोषणा MV88E6390_PORT_MAC_CTL_ALTSPEED			0x1000
#घोषणा MV88E6352_PORT_MAC_CTL_200BASE			0x1000
#घोषणा MV88E6XXX_PORT_MAC_CTL_EEE			0x0200
#घोषणा MV88E6XXX_PORT_MAC_CTL_FORCE_EEE		0x0100
#घोषणा MV88E6185_PORT_MAC_CTL_AN_EN			0x0400
#घोषणा MV88E6185_PORT_MAC_CTL_AN_RESTART		0x0200
#घोषणा MV88E6185_PORT_MAC_CTL_AN_DONE			0x0100
#घोषणा MV88E6XXX_PORT_MAC_CTL_FC			0x0080
#घोषणा MV88E6XXX_PORT_MAC_CTL_FORCE_FC			0x0040
#घोषणा MV88E6XXX_PORT_MAC_CTL_LINK_UP			0x0020
#घोषणा MV88E6XXX_PORT_MAC_CTL_FORCE_LINK		0x0010
#घोषणा MV88E6XXX_PORT_MAC_CTL_DUPLEX_FULL		0x0008
#घोषणा MV88E6XXX_PORT_MAC_CTL_FORCE_DUPLEX		0x0004
#घोषणा MV88E6XXX_PORT_MAC_CTL_SPEED_MASK		0x0003
#घोषणा MV88E6XXX_PORT_MAC_CTL_SPEED_10			0x0000
#घोषणा MV88E6XXX_PORT_MAC_CTL_SPEED_100		0x0001
#घोषणा MV88E6065_PORT_MAC_CTL_SPEED_200		0x0002
#घोषणा MV88E6XXX_PORT_MAC_CTL_SPEED_1000		0x0002
#घोषणा MV88E6390_PORT_MAC_CTL_SPEED_10000		0x0003
#घोषणा MV88E6XXX_PORT_MAC_CTL_SPEED_UNFORCED		0x0003

/* Offset 0x02: Jamming Control Register */
#घोषणा MV88E6097_PORT_JAM_CTL			0x02
#घोषणा MV88E6097_PORT_JAM_CTL_LIMIT_OUT_MASK	0xff00
#घोषणा MV88E6097_PORT_JAM_CTL_LIMIT_IN_MASK	0x00ff

/* Offset 0x02: Flow Control Register */
#घोषणा MV88E6390_PORT_FLOW_CTL			0x02
#घोषणा MV88E6390_PORT_FLOW_CTL_UPDATE		0x8000
#घोषणा MV88E6390_PORT_FLOW_CTL_PTR_MASK	0x7f00
#घोषणा MV88E6390_PORT_FLOW_CTL_LIMIT_IN	0x0000
#घोषणा MV88E6390_PORT_FLOW_CTL_LIMIT_OUT	0x0100
#घोषणा MV88E6390_PORT_FLOW_CTL_DATA_MASK	0x00ff

/* Offset 0x03: Switch Identअगरier Register */
#घोषणा MV88E6XXX_PORT_SWITCH_ID		0x03
#घोषणा MV88E6XXX_PORT_SWITCH_ID_PROD_MASK	0xfff0
#घोषणा MV88E6XXX_PORT_SWITCH_ID_PROD_6085	0x04a0
#घोषणा MV88E6XXX_PORT_SWITCH_ID_PROD_6095	0x0950
#घोषणा MV88E6XXX_PORT_SWITCH_ID_PROD_6097	0x0990
#घोषणा MV88E6XXX_PORT_SWITCH_ID_PROD_6190X	0x0a00
#घोषणा MV88E6XXX_PORT_SWITCH_ID_PROD_6390X	0x0a10
#घोषणा MV88E6XXX_PORT_SWITCH_ID_PROD_6131	0x1060
#घोषणा MV88E6XXX_PORT_SWITCH_ID_PROD_6320	0x1150
#घोषणा MV88E6XXX_PORT_SWITCH_ID_PROD_6123	0x1210
#घोषणा MV88E6XXX_PORT_SWITCH_ID_PROD_6161	0x1610
#घोषणा MV88E6XXX_PORT_SWITCH_ID_PROD_6165	0x1650
#घोषणा MV88E6XXX_PORT_SWITCH_ID_PROD_6171	0x1710
#घोषणा MV88E6XXX_PORT_SWITCH_ID_PROD_6172	0x1720
#घोषणा MV88E6XXX_PORT_SWITCH_ID_PROD_6175	0x1750
#घोषणा MV88E6XXX_PORT_SWITCH_ID_PROD_6176	0x1760
#घोषणा MV88E6XXX_PORT_SWITCH_ID_PROD_6190	0x1900
#घोषणा MV88E6XXX_PORT_SWITCH_ID_PROD_6191	0x1910
#घोषणा MV88E6XXX_PORT_SWITCH_ID_PROD_6191X	0x1920
#घोषणा MV88E6XXX_PORT_SWITCH_ID_PROD_6193X	0x1930
#घोषणा MV88E6XXX_PORT_SWITCH_ID_PROD_6185	0x1a70
#घोषणा MV88E6XXX_PORT_SWITCH_ID_PROD_6220	0x2200
#घोषणा MV88E6XXX_PORT_SWITCH_ID_PROD_6240	0x2400
#घोषणा MV88E6XXX_PORT_SWITCH_ID_PROD_6250	0x2500
#घोषणा MV88E6XXX_PORT_SWITCH_ID_PROD_6290	0x2900
#घोषणा MV88E6XXX_PORT_SWITCH_ID_PROD_6321	0x3100
#घोषणा MV88E6XXX_PORT_SWITCH_ID_PROD_6141	0x3400
#घोषणा MV88E6XXX_PORT_SWITCH_ID_PROD_6341	0x3410
#घोषणा MV88E6XXX_PORT_SWITCH_ID_PROD_6352	0x3520
#घोषणा MV88E6XXX_PORT_SWITCH_ID_PROD_6350	0x3710
#घोषणा MV88E6XXX_PORT_SWITCH_ID_PROD_6351	0x3750
#घोषणा MV88E6XXX_PORT_SWITCH_ID_PROD_6390	0x3900
#घोषणा MV88E6XXX_PORT_SWITCH_ID_PROD_6393X	0x3930
#घोषणा MV88E6XXX_PORT_SWITCH_ID_REV_MASK	0x000f

/* Offset 0x04: Port Control Register */
#घोषणा MV88E6XXX_PORT_CTL0					0x04
#घोषणा MV88E6XXX_PORT_CTL0_USE_CORE_TAG			0x8000
#घोषणा MV88E6XXX_PORT_CTL0_DROP_ON_LOCK			0x4000
#घोषणा MV88E6XXX_PORT_CTL0_EGRESS_MODE_MASK			0x3000
#घोषणा MV88E6XXX_PORT_CTL0_EGRESS_MODE_UNMODIFIED		0x0000
#घोषणा MV88E6XXX_PORT_CTL0_EGRESS_MODE_UNTAGGED		0x1000
#घोषणा MV88E6XXX_PORT_CTL0_EGRESS_MODE_TAGGED			0x2000
#घोषणा MV88E6XXX_PORT_CTL0_EGRESS_MODE_ETHER_TYPE_DSA		0x3000
#घोषणा MV88E6XXX_PORT_CTL0_HEADER				0x0800
#घोषणा MV88E6XXX_PORT_CTL0_IGMP_MLD_SNOOP			0x0400
#घोषणा MV88E6XXX_PORT_CTL0_DOUBLE_TAG				0x0200
#घोषणा MV88E6XXX_PORT_CTL0_FRAME_MODE_MASK			0x0300
#घोषणा MV88E6XXX_PORT_CTL0_FRAME_MODE_NORMAL			0x0000
#घोषणा MV88E6XXX_PORT_CTL0_FRAME_MODE_DSA			0x0100
#घोषणा MV88E6XXX_PORT_CTL0_FRAME_MODE_PROVIDER			0x0200
#घोषणा MV88E6XXX_PORT_CTL0_FRAME_MODE_ETHER_TYPE_DSA		0x0300
#घोषणा MV88E6XXX_PORT_CTL0_DSA_TAG				0x0100
#घोषणा MV88E6XXX_PORT_CTL0_VLAN_TUNNEL				0x0080
#घोषणा MV88E6XXX_PORT_CTL0_TAG_IF_BOTH				0x0040
#घोषणा MV88E6185_PORT_CTL0_USE_IP				0x0020
#घोषणा MV88E6185_PORT_CTL0_USE_TAG				0x0010
#घोषणा MV88E6185_PORT_CTL0_FORWARD_UNKNOWN			0x0004
#घोषणा MV88E6352_PORT_CTL0_EGRESS_FLOODS_UC			0x0004
#घोषणा MV88E6352_PORT_CTL0_EGRESS_FLOODS_MC			0x0008
#घोषणा MV88E6XXX_PORT_CTL0_STATE_MASK				0x0003
#घोषणा MV88E6XXX_PORT_CTL0_STATE_DISABLED			0x0000
#घोषणा MV88E6XXX_PORT_CTL0_STATE_BLOCKING			0x0001
#घोषणा MV88E6XXX_PORT_CTL0_STATE_LEARNING			0x0002
#घोषणा MV88E6XXX_PORT_CTL0_STATE_FORWARDING			0x0003

/* Offset 0x05: Port Control 1 */
#घोषणा MV88E6XXX_PORT_CTL1			0x05
#घोषणा MV88E6XXX_PORT_CTL1_MESSAGE_PORT	0x8000
#घोषणा MV88E6XXX_PORT_CTL1_TRUNK_PORT		0x4000
#घोषणा MV88E6XXX_PORT_CTL1_TRUNK_ID_MASK	0x0f00
#घोषणा MV88E6XXX_PORT_CTL1_TRUNK_ID_SHIFT	8
#घोषणा MV88E6XXX_PORT_CTL1_FID_11_4_MASK	0x00ff

/* Offset 0x06: Port Based VLAN Map */
#घोषणा MV88E6XXX_PORT_BASE_VLAN		0x06
#घोषणा MV88E6XXX_PORT_BASE_VLAN_FID_3_0_MASK	0xf000

/* Offset 0x07: Default Port VLAN ID & Priority */
#घोषणा MV88E6XXX_PORT_DEFAULT_VLAN		0x07
#घोषणा MV88E6XXX_PORT_DEFAULT_VLAN_MASK	0x0fff

/* Offset 0x08: Port Control 2 Register */
#घोषणा MV88E6XXX_PORT_CTL2				0x08
#घोषणा MV88E6XXX_PORT_CTL2_IGNORE_FCS			0x8000
#घोषणा MV88E6XXX_PORT_CTL2_VTU_PRI_OVERRIDE		0x4000
#घोषणा MV88E6XXX_PORT_CTL2_SA_PRIO_OVERRIDE		0x2000
#घोषणा MV88E6XXX_PORT_CTL2_DA_PRIO_OVERRIDE		0x1000
#घोषणा MV88E6XXX_PORT_CTL2_JUMBO_MODE_MASK		0x3000
#घोषणा MV88E6XXX_PORT_CTL2_JUMBO_MODE_1522		0x0000
#घोषणा MV88E6XXX_PORT_CTL2_JUMBO_MODE_2048		0x1000
#घोषणा MV88E6XXX_PORT_CTL2_JUMBO_MODE_10240		0x2000
#घोषणा MV88E6XXX_PORT_CTL2_8021Q_MODE_MASK		0x0c00
#घोषणा MV88E6XXX_PORT_CTL2_8021Q_MODE_DISABLED		0x0000
#घोषणा MV88E6XXX_PORT_CTL2_8021Q_MODE_FALLBACK		0x0400
#घोषणा MV88E6XXX_PORT_CTL2_8021Q_MODE_CHECK		0x0800
#घोषणा MV88E6XXX_PORT_CTL2_8021Q_MODE_SECURE		0x0c00
#घोषणा MV88E6XXX_PORT_CTL2_DISCARD_TAGGED		0x0200
#घोषणा MV88E6XXX_PORT_CTL2_DISCARD_UNTAGGED		0x0100
#घोषणा MV88E6XXX_PORT_CTL2_MAP_DA			0x0080
#घोषणा MV88E6XXX_PORT_CTL2_DEFAULT_FORWARD		0x0040
#घोषणा MV88E6XXX_PORT_CTL2_EGRESS_MONITOR		0x0020
#घोषणा MV88E6XXX_PORT_CTL2_INGRESS_MONITOR		0x0010
#घोषणा MV88E6095_PORT_CTL2_CPU_PORT_MASK		0x000f

/* Offset 0x09: Egress Rate Control */
#घोषणा MV88E6XXX_PORT_EGRESS_RATE_CTL1		0x09

/* Offset 0x0A: Egress Rate Control 2 */
#घोषणा MV88E6XXX_PORT_EGRESS_RATE_CTL2		0x0a

/* Offset 0x0B: Port Association Vector */
#घोषणा MV88E6XXX_PORT_ASSOC_VECTOR			0x0b
#घोषणा MV88E6XXX_PORT_ASSOC_VECTOR_HOLD_AT_1		0x8000
#घोषणा MV88E6XXX_PORT_ASSOC_VECTOR_INT_AGE_OUT		0x4000
#घोषणा MV88E6XXX_PORT_ASSOC_VECTOR_LOCKED_PORT		0x2000
#घोषणा MV88E6XXX_PORT_ASSOC_VECTOR_IGNORE_WRONG	0x1000
#घोषणा MV88E6XXX_PORT_ASSOC_VECTOR_REFRESH_LOCKED	0x0800

/* Offset 0x0C: Port ATU Control */
#घोषणा MV88E6XXX_PORT_ATU_CTL		0x0c

/* Offset 0x0D: Priority Override Register */
#घोषणा MV88E6XXX_PORT_PRI_OVERRIDE	0x0d

/* Offset 0x0E: Policy Control Register */
#घोषणा MV88E6XXX_PORT_POLICY_CTL		0x0e
#घोषणा MV88E6XXX_PORT_POLICY_CTL_DA_MASK	0xc000
#घोषणा MV88E6XXX_PORT_POLICY_CTL_SA_MASK	0x3000
#घोषणा MV88E6XXX_PORT_POLICY_CTL_VTU_MASK	0x0c00
#घोषणा MV88E6XXX_PORT_POLICY_CTL_ETYPE_MASK	0x0300
#घोषणा MV88E6XXX_PORT_POLICY_CTL_PPPOE_MASK	0x00c0
#घोषणा MV88E6XXX_PORT_POLICY_CTL_VBAS_MASK	0x0030
#घोषणा MV88E6XXX_PORT_POLICY_CTL_OPT82_MASK	0x000c
#घोषणा MV88E6XXX_PORT_POLICY_CTL_UDP_MASK	0x0003
#घोषणा MV88E6XXX_PORT_POLICY_CTL_NORMAL	0x0000
#घोषणा MV88E6XXX_PORT_POLICY_CTL_MIRROR	0x0001
#घोषणा MV88E6XXX_PORT_POLICY_CTL_TRAP		0x0002
#घोषणा MV88E6XXX_PORT_POLICY_CTL_DISCARD	0x0003

/* Offset 0x0E: Policy & MGMT Control Register (FAMILY_6393X) */
#घोषणा MV88E6393X_PORT_POLICY_MGMT_CTL				0x0e
#घोषणा MV88E6393X_PORT_POLICY_MGMT_CTL_UPDATE			0x8000
#घोषणा MV88E6393X_PORT_POLICY_MGMT_CTL_PTR_MASK		0x3f00
#घोषणा MV88E6393X_PORT_POLICY_MGMT_CTL_DATA_MASK		0x00ff
#घोषणा MV88E6393X_PORT_POLICY_MGMT_CTL_PTR_01C280000000XLO	0x2000
#घोषणा MV88E6393X_PORT_POLICY_MGMT_CTL_PTR_01C280000000XHI	0x2100
#घोषणा MV88E6393X_PORT_POLICY_MGMT_CTL_PTR_01C280000002XLO	0x2400
#घोषणा MV88E6393X_PORT_POLICY_MGMT_CTL_PTR_01C280000002XHI	0x2500
#घोषणा MV88E6393X_PORT_POLICY_MGMT_CTL_PTR_INGRESS_DEST	0x3000
#घोषणा MV88E6393X_PORT_POLICY_MGMT_CTL_PTR_CPU_DEST		0x3800
#घोषणा MV88E6393X_PORT_POLICY_MGMT_CTL_CPU_DEST_MGMTPRI	0x00e0

/* Offset 0x0F: Port Special Ether Type */
#घोषणा MV88E6XXX_PORT_ETH_TYPE		0x0f
#घोषणा MV88E6XXX_PORT_ETH_TYPE_DEFAULT	0x9100

/* Offset 0x10: InDiscards Low Counter */
#घोषणा MV88E6XXX_PORT_IN_DISCARD_LO	0x10

/* Offset 0x10: Extended Port Control Command */
#घोषणा MV88E6393X_PORT_EPC_CMD		0x10
#घोषणा MV88E6393X_PORT_EPC_CMD_BUSY	0x8000
#घोषणा MV88E6393X_PORT_EPC_CMD_WRITE	0x0300
#घोषणा MV88E6393X_PORT_EPC_INDEX_PORT_ETYPE	0x02

/* Offset 0x11: Extended Port Control Data */
#घोषणा MV88E6393X_PORT_EPC_DATA	0x11

/* Offset 0x11: InDiscards High Counter */
#घोषणा MV88E6XXX_PORT_IN_DISCARD_HI	0x11

/* Offset 0x12: InFiltered Counter */
#घोषणा MV88E6XXX_PORT_IN_FILTERED	0x12

/* Offset 0x13: OutFiltered Counter */
#घोषणा MV88E6XXX_PORT_OUT_FILTERED	0x13

/* Offset 0x18: IEEE Priority Mapping Table */
#घोषणा MV88E6390_PORT_IEEE_PRIO_MAP_TABLE			0x18
#घोषणा MV88E6390_PORT_IEEE_PRIO_MAP_TABLE_UPDATE		0x8000
#घोषणा MV88E6390_PORT_IEEE_PRIO_MAP_TABLE_MASK			0x7000
#घोषणा MV88E6390_PORT_IEEE_PRIO_MAP_TABLE_INGRESS_PCP		0x0000
#घोषणा MV88E6390_PORT_IEEE_PRIO_MAP_TABLE_EGRESS_GREEN_PCP	0x1000
#घोषणा MV88E6390_PORT_IEEE_PRIO_MAP_TABLE_EGRESS_YELLOW_PCP	0x2000
#घोषणा MV88E6390_PORT_IEEE_PRIO_MAP_TABLE_EGRESS_AVB_PCP	0x3000
#घोषणा MV88E6390_PORT_IEEE_PRIO_MAP_TABLE_EGRESS_GREEN_DSCP	0x5000
#घोषणा MV88E6390_PORT_IEEE_PRIO_MAP_TABLE_EGRESS_YELLOW_DSCP	0x6000
#घोषणा MV88E6390_PORT_IEEE_PRIO_MAP_TABLE_EGRESS_AVB_DSCP	0x7000
#घोषणा MV88E6390_PORT_IEEE_PRIO_MAP_TABLE_PTR_MASK		0x0e00
#घोषणा MV88E6390_PORT_IEEE_PRIO_MAP_TABLE_DATA_MASK		0x01ff

/* Offset 0x18: Port IEEE Priority Remapping Registers (0-3) */
#घोषणा MV88E6095_PORT_IEEE_PRIO_REMAP_0123	0x18

/* Offset 0x19: Port IEEE Priority Remapping Registers (4-7) */
#घोषणा MV88E6095_PORT_IEEE_PRIO_REMAP_4567	0x19

/* Offset 0x1a: Magic unकरोcumented errata रेजिस्टर */
#घोषणा MV88E6XXX_PORT_RESERVED_1A		0x1a
#घोषणा MV88E6XXX_PORT_RESERVED_1A_BUSY		0x8000
#घोषणा MV88E6XXX_PORT_RESERVED_1A_WRITE	0x4000
#घोषणा MV88E6XXX_PORT_RESERVED_1A_READ		0x0000
#घोषणा MV88E6XXX_PORT_RESERVED_1A_PORT_SHIFT	5
#घोषणा MV88E6XXX_PORT_RESERVED_1A_BLOCK_SHIFT	10
#घोषणा MV88E6XXX_PORT_RESERVED_1A_CTRL_PORT	0x04
#घोषणा MV88E6XXX_PORT_RESERVED_1A_DATA_PORT	0x05
#घोषणा MV88E6341_PORT_RESERVED_1A_FORCE_CMODE	0x8000
#घोषणा MV88E6341_PORT_RESERVED_1A_SGMII_AN	0x2000

पूर्णांक mv88e6xxx_port_पढ़ो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, पूर्णांक reg,
			u16 *val);
पूर्णांक mv88e6xxx_port_ग_लिखो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, पूर्णांक reg,
			 u16 val);
पूर्णांक mv88e6xxx_port_रुको_bit(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, पूर्णांक reg,
			    पूर्णांक bit, पूर्णांक val);

पूर्णांक mv88e6185_port_set_छोड़ो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
			     पूर्णांक छोड़ो);
पूर्णांक mv88e6352_port_set_rgmii_delay(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				   phy_पूर्णांकerface_t mode);
पूर्णांक mv88e6390_port_set_rgmii_delay(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				   phy_पूर्णांकerface_t mode);

पूर्णांक mv88e6xxx_port_set_link(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, पूर्णांक link);

पूर्णांक mv88e6xxx_port_sync_link(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, अचिन्हित पूर्णांक mode, bool isup);
पूर्णांक mv88e6185_port_sync_link(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, अचिन्हित पूर्णांक mode, bool isup);

पूर्णांक mv88e6065_port_set_speed_duplex(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				    पूर्णांक speed, पूर्णांक duplex);
पूर्णांक mv88e6185_port_set_speed_duplex(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				    पूर्णांक speed, पूर्णांक duplex);
पूर्णांक mv88e6250_port_set_speed_duplex(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				    पूर्णांक speed, पूर्णांक duplex);
पूर्णांक mv88e6341_port_set_speed_duplex(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				    पूर्णांक speed, पूर्णांक duplex);
पूर्णांक mv88e6352_port_set_speed_duplex(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				    पूर्णांक speed, पूर्णांक duplex);
पूर्णांक mv88e6390_port_set_speed_duplex(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				    पूर्णांक speed, पूर्णांक duplex);
पूर्णांक mv88e6390x_port_set_speed_duplex(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				     पूर्णांक speed, पूर्णांक duplex);
पूर्णांक mv88e6393x_port_set_speed_duplex(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				     पूर्णांक speed, पूर्णांक duplex);

phy_पूर्णांकerface_t mv88e6341_port_max_speed_mode(पूर्णांक port);
phy_पूर्णांकerface_t mv88e6390_port_max_speed_mode(पूर्णांक port);
phy_पूर्णांकerface_t mv88e6390x_port_max_speed_mode(पूर्णांक port);
phy_पूर्णांकerface_t mv88e6393x_port_max_speed_mode(पूर्णांक port);

पूर्णांक mv88e6xxx_port_set_state(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, u8 state);

पूर्णांक mv88e6xxx_port_set_vlan_map(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, u16 map);

पूर्णांक mv88e6xxx_port_get_fid(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, u16 *fid);
पूर्णांक mv88e6xxx_port_set_fid(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, u16 fid);

पूर्णांक mv88e6xxx_port_get_pvid(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, u16 *pvid);
पूर्णांक mv88e6xxx_port_set_pvid(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, u16 pvid);

पूर्णांक mv88e6xxx_port_set_8021q_mode(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				  u16 mode);
पूर्णांक mv88e6095_port_tag_remap(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port);
पूर्णांक mv88e6390_port_tag_remap(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port);
पूर्णांक mv88e6xxx_port_set_egress_mode(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				   क्रमागत mv88e6xxx_egress_mode mode);
पूर्णांक mv88e6085_port_set_frame_mode(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				  क्रमागत mv88e6xxx_frame_mode mode);
पूर्णांक mv88e6351_port_set_frame_mode(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				  क्रमागत mv88e6xxx_frame_mode mode);
पूर्णांक mv88e6185_port_set_क्रमward_unknown(काष्ठा mv88e6xxx_chip *chip,
				       पूर्णांक port, bool unicast);
पूर्णांक mv88e6185_port_set_शेष_क्रमward(काष्ठा mv88e6xxx_chip *chip,
				       पूर्णांक port, bool multicast);
पूर्णांक mv88e6352_port_set_ucast_flood(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				   bool unicast);
पूर्णांक mv88e6352_port_set_mcast_flood(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				   bool multicast);
पूर्णांक mv88e6352_port_set_policy(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
			      क्रमागत mv88e6xxx_policy_mapping mapping,
			      क्रमागत mv88e6xxx_policy_action action);
पूर्णांक mv88e6393x_port_set_policy(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
			       क्रमागत mv88e6xxx_policy_mapping mapping,
			       क्रमागत mv88e6xxx_policy_action action);
पूर्णांक mv88e6351_port_set_ether_type(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				  u16 etype);
पूर्णांक mv88e6393x_set_egress_port(काष्ठा mv88e6xxx_chip *chip,
			       क्रमागत mv88e6xxx_egress_direction direction,
			       पूर्णांक port);
पूर्णांक mv88e6393x_port_set_upstream_port(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				      पूर्णांक upstream_port);
पूर्णांक mv88e6393x_port_mgmt_rsvd2cpu(काष्ठा mv88e6xxx_chip *chip);
पूर्णांक mv88e6393x_port_set_ether_type(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				   u16 etype);
पूर्णांक mv88e6xxx_port_set_message_port(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				    bool message_port);
पूर्णांक mv88e6xxx_port_set_trunk(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
			     bool trunk, u8 id);
पूर्णांक mv88e6165_port_set_jumbo_size(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				  माप_प्रकार size);
पूर्णांक mv88e6095_port_egress_rate_limiting(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port);
पूर्णांक mv88e6097_port_egress_rate_limiting(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port);
पूर्णांक mv88e6xxx_port_set_assoc_vector(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				    u16 pav);
पूर्णांक mv88e6097_port_छोड़ो_limit(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, u8 in,
			       u8 out);
पूर्णांक mv88e6390_port_छोड़ो_limit(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, u8 in,
			       u8 out);
पूर्णांक mv88e6341_port_set_cmode(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
			     phy_पूर्णांकerface_t mode);
पूर्णांक mv88e6390_port_set_cmode(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
			     phy_पूर्णांकerface_t mode);
पूर्णांक mv88e6390x_port_set_cmode(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
			      phy_पूर्णांकerface_t mode);
पूर्णांक mv88e6393x_port_set_cmode(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
			      phy_पूर्णांकerface_t mode);
पूर्णांक mv88e6185_port_get_cmode(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, u8 *cmode);
पूर्णांक mv88e6352_port_get_cmode(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, u8 *cmode);
पूर्णांक mv88e6xxx_port_set_map_da(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port);
पूर्णांक mv88e6095_port_set_upstream_port(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				     पूर्णांक upstream_port);
पूर्णांक mv88e6xxx_port_set_mirror(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
			      क्रमागत mv88e6xxx_egress_direction direction,
			      bool mirror);

पूर्णांक mv88e6xxx_port_disable_learn_limit(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port);
पूर्णांक mv88e6xxx_port_disable_pri_override(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port);

पूर्णांक mv88e6xxx_port_hidden_ग_लिखो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक block,
				पूर्णांक port, पूर्णांक reg, u16 val);
पूर्णांक mv88e6xxx_port_hidden_रुको(काष्ठा mv88e6xxx_chip *chip);
पूर्णांक mv88e6xxx_port_hidden_पढ़ो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक block, पूर्णांक port,
			       पूर्णांक reg, u16 *val);

#पूर्ण_अगर /* _MV88E6XXX_PORT_H */
