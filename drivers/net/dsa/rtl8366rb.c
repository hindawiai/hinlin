<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Realtek SMI subdriver क्रम the Realtek RTL8366RB ethernet चयन
 *
 * This is a sparsely करोcumented chip, the only viable करोcumentation seems
 * to be a patched up code drop from the venकरोr that appear in various
 * GPL source trees.
 *
 * Copyright (C) 2017 Linus Walleij <linus.walleij@linaro.org>
 * Copyright (C) 2009-2010 Gabor Juhos <juhosg@खोलोwrt.org>
 * Copyright (C) 2010 Antti Seppथअlथअ <a.seppala@gmail.com>
 * Copyright (C) 2010 Roman Yeryomin <roman@advem.lv>
 * Copyright (C) 2011 Colin Leitner <colin.leitner@googlemail.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/regmap.h>

#समावेश "realtek-smi-core.h"

#घोषणा RTL8366RB_PORT_NUM_CPU		5
#घोषणा RTL8366RB_NUM_PORTS		6
#घोषणा RTL8366RB_PHY_NO_MAX		4
#घोषणा RTL8366RB_PHY_ADDR_MAX		31

/* Switch Global Configuration रेजिस्टर */
#घोषणा RTL8366RB_SGCR				0x0000
#घोषणा RTL8366RB_SGCR_EN_BC_STORM_CTRL		BIT(0)
#घोषणा RTL8366RB_SGCR_MAX_LENGTH(a)		((a) << 4)
#घोषणा RTL8366RB_SGCR_MAX_LENGTH_MASK		RTL8366RB_SGCR_MAX_LENGTH(0x3)
#घोषणा RTL8366RB_SGCR_MAX_LENGTH_1522		RTL8366RB_SGCR_MAX_LENGTH(0x0)
#घोषणा RTL8366RB_SGCR_MAX_LENGTH_1536		RTL8366RB_SGCR_MAX_LENGTH(0x1)
#घोषणा RTL8366RB_SGCR_MAX_LENGTH_1552		RTL8366RB_SGCR_MAX_LENGTH(0x2)
#घोषणा RTL8366RB_SGCR_MAX_LENGTH_16000		RTL8366RB_SGCR_MAX_LENGTH(0x3)
#घोषणा RTL8366RB_SGCR_EN_VLAN			BIT(13)
#घोषणा RTL8366RB_SGCR_EN_VLAN_4KTB		BIT(14)

/* Port Enable Control रेजिस्टर */
#घोषणा RTL8366RB_PECR				0x0001

/* Switch Security Control रेजिस्टरs */
#घोषणा RTL8366RB_SSCR0				0x0002
#घोषणा RTL8366RB_SSCR1				0x0003
#घोषणा RTL8366RB_SSCR2				0x0004
#घोषणा RTL8366RB_SSCR2_DROP_UNKNOWN_DA		BIT(0)

/* Port Mode Control रेजिस्टरs */
#घोषणा RTL8366RB_PMC0				0x0005
#घोषणा RTL8366RB_PMC0_SPI			BIT(0)
#घोषणा RTL8366RB_PMC0_EN_AUTOLOAD		BIT(1)
#घोषणा RTL8366RB_PMC0_PROBE			BIT(2)
#घोषणा RTL8366RB_PMC0_DIS_BISR			BIT(3)
#घोषणा RTL8366RB_PMC0_ADCTEST			BIT(4)
#घोषणा RTL8366RB_PMC0_SRAM_DIAG		BIT(5)
#घोषणा RTL8366RB_PMC0_EN_SCAN			BIT(6)
#घोषणा RTL8366RB_PMC0_P4_IOMODE_SHIFT		7
#घोषणा RTL8366RB_PMC0_P4_IOMODE_MASK		GENMASK(9, 7)
#घोषणा RTL8366RB_PMC0_P5_IOMODE_SHIFT		10
#घोषणा RTL8366RB_PMC0_P5_IOMODE_MASK		GENMASK(12, 10)
#घोषणा RTL8366RB_PMC0_SDSMODE_SHIFT		13
#घोषणा RTL8366RB_PMC0_SDSMODE_MASK		GENMASK(15, 13)
#घोषणा RTL8366RB_PMC1				0x0006

/* Port Mirror Control Register */
#घोषणा RTL8366RB_PMCR				0x0007
#घोषणा RTL8366RB_PMCR_SOURCE_PORT(a)		(a)
#घोषणा RTL8366RB_PMCR_SOURCE_PORT_MASK		0x000f
#घोषणा RTL8366RB_PMCR_MONITOR_PORT(a)		((a) << 4)
#घोषणा RTL8366RB_PMCR_MONITOR_PORT_MASK	0x00f0
#घोषणा RTL8366RB_PMCR_MIRROR_RX		BIT(8)
#घोषणा RTL8366RB_PMCR_MIRROR_TX		BIT(9)
#घोषणा RTL8366RB_PMCR_MIRROR_SPC		BIT(10)
#घोषणा RTL8366RB_PMCR_MIRROR_ISO		BIT(11)

/* bits 0..7 = port 0, bits 8..15 = port 1 */
#घोषणा RTL8366RB_PAACR0		0x0010
/* bits 0..7 = port 2, bits 8..15 = port 3 */
#घोषणा RTL8366RB_PAACR1		0x0011
/* bits 0..7 = port 4, bits 8..15 = port 5 */
#घोषणा RTL8366RB_PAACR2		0x0012
#घोषणा RTL8366RB_PAACR_SPEED_10M	0
#घोषणा RTL8366RB_PAACR_SPEED_100M	1
#घोषणा RTL8366RB_PAACR_SPEED_1000M	2
#घोषणा RTL8366RB_PAACR_FULL_DUPLEX	BIT(2)
#घोषणा RTL8366RB_PAACR_LINK_UP		BIT(4)
#घोषणा RTL8366RB_PAACR_TX_PAUSE	BIT(5)
#घोषणा RTL8366RB_PAACR_RX_PAUSE	BIT(6)
#घोषणा RTL8366RB_PAACR_AN		BIT(7)

#घोषणा RTL8366RB_PAACR_CPU_PORT	(RTL8366RB_PAACR_SPEED_1000M | \
					 RTL8366RB_PAACR_FULL_DUPLEX | \
					 RTL8366RB_PAACR_LINK_UP | \
					 RTL8366RB_PAACR_TX_PAUSE | \
					 RTL8366RB_PAACR_RX_PAUSE)

/* bits 0..7 = port 0, bits 8..15 = port 1 */
#घोषणा RTL8366RB_PSTAT0		0x0014
/* bits 0..7 = port 2, bits 8..15 = port 3 */
#घोषणा RTL8366RB_PSTAT1		0x0015
/* bits 0..7 = port 4, bits 8..15 = port 5 */
#घोषणा RTL8366RB_PSTAT2		0x0016

#घोषणा RTL8366RB_POWER_SAVING_REG	0x0021

/* CPU port control reg */
#घोषणा RTL8368RB_CPU_CTRL_REG		0x0061
#घोषणा RTL8368RB_CPU_PORTS_MSK		0x00FF
/* Disables inserting custom tag length/type 0x8899 */
#घोषणा RTL8368RB_CPU_NO_TAG		BIT(15)

#घोषणा RTL8366RB_SMAR0			0x0070 /* bits 0..15 */
#घोषणा RTL8366RB_SMAR1			0x0071 /* bits 16..31 */
#घोषणा RTL8366RB_SMAR2			0x0072 /* bits 32..47 */

#घोषणा RTL8366RB_RESET_CTRL_REG		0x0100
#घोषणा RTL8366RB_CHIP_CTRL_RESET_HW		BIT(0)
#घोषणा RTL8366RB_CHIP_CTRL_RESET_SW		BIT(1)

#घोषणा RTL8366RB_CHIP_ID_REG			0x0509
#घोषणा RTL8366RB_CHIP_ID_8366			0x5937
#घोषणा RTL8366RB_CHIP_VERSION_CTRL_REG		0x050A
#घोषणा RTL8366RB_CHIP_VERSION_MASK		0xf

/* PHY रेजिस्टरs control */
#घोषणा RTL8366RB_PHY_ACCESS_CTRL_REG		0x8000
#घोषणा RTL8366RB_PHY_CTRL_READ			BIT(0)
#घोषणा RTL8366RB_PHY_CTRL_WRITE		0
#घोषणा RTL8366RB_PHY_ACCESS_BUSY_REG		0x8001
#घोषणा RTL8366RB_PHY_INT_BUSY			BIT(0)
#घोषणा RTL8366RB_PHY_EXT_BUSY			BIT(4)
#घोषणा RTL8366RB_PHY_ACCESS_DATA_REG		0x8002
#घोषणा RTL8366RB_PHY_EXT_CTRL_REG		0x8010
#घोषणा RTL8366RB_PHY_EXT_WRDATA_REG		0x8011
#घोषणा RTL8366RB_PHY_EXT_RDDATA_REG		0x8012

#घोषणा RTL8366RB_PHY_REG_MASK			0x1f
#घोषणा RTL8366RB_PHY_PAGE_OFFSET		5
#घोषणा RTL8366RB_PHY_PAGE_MASK			(0xf << 5)
#घोषणा RTL8366RB_PHY_NO_OFFSET			9
#घोषणा RTL8366RB_PHY_NO_MASK			(0x1f << 9)

#घोषणा RTL8366RB_VLAN_INGRESS_CTRL2_REG	0x037f

/* LED control रेजिस्टरs */
#घोषणा RTL8366RB_LED_BLINKRATE_REG		0x0430
#घोषणा RTL8366RB_LED_BLINKRATE_MASK		0x0007
#घोषणा RTL8366RB_LED_BLINKRATE_28MS		0x0000
#घोषणा RTL8366RB_LED_BLINKRATE_56MS		0x0001
#घोषणा RTL8366RB_LED_BLINKRATE_84MS		0x0002
#घोषणा RTL8366RB_LED_BLINKRATE_111MS		0x0003
#घोषणा RTL8366RB_LED_BLINKRATE_222MS		0x0004
#घोषणा RTL8366RB_LED_BLINKRATE_446MS		0x0005

#घोषणा RTL8366RB_LED_CTRL_REG			0x0431
#घोषणा RTL8366RB_LED_OFF			0x0
#घोषणा RTL8366RB_LED_DUP_COL			0x1
#घोषणा RTL8366RB_LED_LINK_ACT			0x2
#घोषणा RTL8366RB_LED_SPD1000			0x3
#घोषणा RTL8366RB_LED_SPD100			0x4
#घोषणा RTL8366RB_LED_SPD10			0x5
#घोषणा RTL8366RB_LED_SPD1000_ACT		0x6
#घोषणा RTL8366RB_LED_SPD100_ACT		0x7
#घोषणा RTL8366RB_LED_SPD10_ACT			0x8
#घोषणा RTL8366RB_LED_SPD100_10_ACT		0x9
#घोषणा RTL8366RB_LED_FIBER			0xa
#घोषणा RTL8366RB_LED_AN_FAULT			0xb
#घोषणा RTL8366RB_LED_LINK_RX			0xc
#घोषणा RTL8366RB_LED_LINK_TX			0xd
#घोषणा RTL8366RB_LED_MASTER			0xe
#घोषणा RTL8366RB_LED_FORCE			0xf
#घोषणा RTL8366RB_LED_0_1_CTRL_REG		0x0432
#घोषणा RTL8366RB_LED_1_OFFSET			6
#घोषणा RTL8366RB_LED_2_3_CTRL_REG		0x0433
#घोषणा RTL8366RB_LED_3_OFFSET			6

#घोषणा RTL8366RB_MIB_COUNT			33
#घोषणा RTL8366RB_GLOBAL_MIB_COUNT		1
#घोषणा RTL8366RB_MIB_COUNTER_PORT_OFFSET	0x0050
#घोषणा RTL8366RB_MIB_COUNTER_BASE		0x1000
#घोषणा RTL8366RB_MIB_CTRL_REG			0x13F0
#घोषणा RTL8366RB_MIB_CTRL_USER_MASK		0x0FFC
#घोषणा RTL8366RB_MIB_CTRL_BUSY_MASK		BIT(0)
#घोषणा RTL8366RB_MIB_CTRL_RESET_MASK		BIT(1)
#घोषणा RTL8366RB_MIB_CTRL_PORT_RESET(_p)	BIT(2 + (_p))
#घोषणा RTL8366RB_MIB_CTRL_GLOBAL_RESET		BIT(11)

#घोषणा RTL8366RB_PORT_VLAN_CTRL_BASE		0x0063
#घोषणा RTL8366RB_PORT_VLAN_CTRL_REG(_p)  \
		(RTL8366RB_PORT_VLAN_CTRL_BASE + (_p) / 4)
#घोषणा RTL8366RB_PORT_VLAN_CTRL_MASK		0xf
#घोषणा RTL8366RB_PORT_VLAN_CTRL_SHIFT(_p)	(4 * ((_p) % 4))

#घोषणा RTL8366RB_VLAN_TABLE_READ_BASE		0x018C
#घोषणा RTL8366RB_VLAN_TABLE_WRITE_BASE		0x0185

#घोषणा RTL8366RB_TABLE_ACCESS_CTRL_REG		0x0180
#घोषणा RTL8366RB_TABLE_VLAN_READ_CTRL		0x0E01
#घोषणा RTL8366RB_TABLE_VLAN_WRITE_CTRL		0x0F01

#घोषणा RTL8366RB_VLAN_MC_BASE(_x)		(0x0020 + (_x) * 3)

#घोषणा RTL8366RB_PORT_LINK_STATUS_BASE		0x0014
#घोषणा RTL8366RB_PORT_STATUS_SPEED_MASK	0x0003
#घोषणा RTL8366RB_PORT_STATUS_DUPLEX_MASK	0x0004
#घोषणा RTL8366RB_PORT_STATUS_LINK_MASK		0x0010
#घोषणा RTL8366RB_PORT_STATUS_TXPAUSE_MASK	0x0020
#घोषणा RTL8366RB_PORT_STATUS_RXPAUSE_MASK	0x0040
#घोषणा RTL8366RB_PORT_STATUS_AN_MASK		0x0080

#घोषणा RTL8366RB_NUM_VLANS		16
#घोषणा RTL8366RB_NUM_LEDGROUPS		4
#घोषणा RTL8366RB_NUM_VIDS		4096
#घोषणा RTL8366RB_PRIORITYMAX		7
#घोषणा RTL8366RB_FIDMAX		7

#घोषणा RTL8366RB_PORT_1		BIT(0) /* In userspace port 0 */
#घोषणा RTL8366RB_PORT_2		BIT(1) /* In userspace port 1 */
#घोषणा RTL8366RB_PORT_3		BIT(2) /* In userspace port 2 */
#घोषणा RTL8366RB_PORT_4		BIT(3) /* In userspace port 3 */
#घोषणा RTL8366RB_PORT_5		BIT(4) /* In userspace port 4 */

#घोषणा RTL8366RB_PORT_CPU		BIT(5) /* CPU port */

#घोषणा RTL8366RB_PORT_ALL		(RTL8366RB_PORT_1 |	\
					 RTL8366RB_PORT_2 |	\
					 RTL8366RB_PORT_3 |	\
					 RTL8366RB_PORT_4 |	\
					 RTL8366RB_PORT_5 |	\
					 RTL8366RB_PORT_CPU)

#घोषणा RTL8366RB_PORT_ALL_BUT_CPU	(RTL8366RB_PORT_1 |	\
					 RTL8366RB_PORT_2 |	\
					 RTL8366RB_PORT_3 |	\
					 RTL8366RB_PORT_4 |	\
					 RTL8366RB_PORT_5)

#घोषणा RTL8366RB_PORT_ALL_EXTERNAL	(RTL8366RB_PORT_1 |	\
					 RTL8366RB_PORT_2 |	\
					 RTL8366RB_PORT_3 |	\
					 RTL8366RB_PORT_4)

#घोषणा RTL8366RB_PORT_ALL_INTERNAL	 RTL8366RB_PORT_CPU

/* First configuration word per member config, VID and prio */
#घोषणा RTL8366RB_VLAN_VID_MASK		0xfff
#घोषणा RTL8366RB_VLAN_PRIORITY_SHIFT	12
#घोषणा RTL8366RB_VLAN_PRIORITY_MASK	0x7
/* Second configuration word per member config, member and untagged */
#घोषणा RTL8366RB_VLAN_UNTAG_SHIFT	8
#घोषणा RTL8366RB_VLAN_UNTAG_MASK	0xff
#घोषणा RTL8366RB_VLAN_MEMBER_MASK	0xff
/* Third config word per member config, STAG currently unused */
#घोषणा RTL8366RB_VLAN_STAG_MBR_MASK	0xff
#घोषणा RTL8366RB_VLAN_STAG_MBR_SHIFT	8
#घोषणा RTL8366RB_VLAN_STAG_IDX_MASK	0x7
#घोषणा RTL8366RB_VLAN_STAG_IDX_SHIFT	5
#घोषणा RTL8366RB_VLAN_FID_MASK		0x7

/* Port ingress bandwidth control */
#घोषणा RTL8366RB_IB_BASE		0x0200
#घोषणा RTL8366RB_IB_REG(pnum)		(RTL8366RB_IB_BASE + (pnum))
#घोषणा RTL8366RB_IB_BDTH_MASK		0x3fff
#घोषणा RTL8366RB_IB_PREIFG		BIT(14)

/* Port egress bandwidth control */
#घोषणा RTL8366RB_EB_BASE		0x02d1
#घोषणा RTL8366RB_EB_REG(pnum)		(RTL8366RB_EB_BASE + (pnum))
#घोषणा RTL8366RB_EB_BDTH_MASK		0x3fff
#घोषणा RTL8366RB_EB_PREIFG_REG		0x02f8
#घोषणा RTL8366RB_EB_PREIFG		BIT(9)

#घोषणा RTL8366RB_BDTH_SW_MAX		1048512 /* 1048576? */
#घोषणा RTL8366RB_BDTH_UNIT		64
#घोषणा RTL8366RB_BDTH_REG_DEFAULT	16383

/* QOS */
#घोषणा RTL8366RB_QOS			BIT(15)
/* Include/Exclude Preamble and IFG (20 bytes). 0:Exclude, 1:Include. */
#घोषणा RTL8366RB_QOS_DEFAULT_PREIFG	1

/* Interrupt handling */
#घोषणा RTL8366RB_INTERRUPT_CONTROL_REG	0x0440
#घोषणा RTL8366RB_INTERRUPT_POLARITY	BIT(0)
#घोषणा RTL8366RB_P4_RGMII_LED		BIT(2)
#घोषणा RTL8366RB_INTERRUPT_MASK_REG	0x0441
#घोषणा RTL8366RB_INTERRUPT_LINK_CHGALL	GENMASK(11, 0)
#घोषणा RTL8366RB_INTERRUPT_ACLEXCEED	BIT(8)
#घोषणा RTL8366RB_INTERRUPT_STORMEXCEED	BIT(9)
#घोषणा RTL8366RB_INTERRUPT_P4_FIBER	BIT(12)
#घोषणा RTL8366RB_INTERRUPT_P4_UTP	BIT(13)
#घोषणा RTL8366RB_INTERRUPT_VALID	(RTL8366RB_INTERRUPT_LINK_CHGALL | \
					 RTL8366RB_INTERRUPT_ACLEXCEED | \
					 RTL8366RB_INTERRUPT_STORMEXCEED | \
					 RTL8366RB_INTERRUPT_P4_FIBER | \
					 RTL8366RB_INTERRUPT_P4_UTP)
#घोषणा RTL8366RB_INTERRUPT_STATUS_REG	0x0442
#घोषणा RTL8366RB_NUM_INTERRUPT		14 /* 0..13 */

/* bits 0..5 enable क्रमce when cleared */
#घोषणा RTL8366RB_MAC_FORCE_CTRL_REG	0x0F11

#घोषणा RTL8366RB_OAM_PARSER_REG	0x0F14
#घोषणा RTL8366RB_OAM_MULTIPLEXER_REG	0x0F15

#घोषणा RTL8366RB_GREEN_FEATURE_REG	0x0F51
#घोषणा RTL8366RB_GREEN_FEATURE_MSK	0x0007
#घोषणा RTL8366RB_GREEN_FEATURE_TX	BIT(0)
#घोषणा RTL8366RB_GREEN_FEATURE_RX	BIT(2)

/**
 * काष्ठा rtl8366rb - RTL8366RB-specअगरic data
 * @max_mtu: per-port max MTU setting
 */
काष्ठा rtl8366rb अणु
	अचिन्हित पूर्णांक max_mtu[RTL8366RB_NUM_PORTS];
पूर्ण;

अटल काष्ठा rtl8366_mib_counter rtl8366rb_mib_counters[] = अणु
	अणु 0,  0, 4, "IfInOctets"				पूर्ण,
	अणु 0,  4, 4, "EtherStatsOctets"				पूर्ण,
	अणु 0,  8, 2, "EtherStatsUnderSizePkts"			पूर्ण,
	अणु 0, 10, 2, "EtherFragments"				पूर्ण,
	अणु 0, 12, 2, "EtherStatsPkts64Octets"			पूर्ण,
	अणु 0, 14, 2, "EtherStatsPkts65to127Octets"		पूर्ण,
	अणु 0, 16, 2, "EtherStatsPkts128to255Octets"		पूर्ण,
	अणु 0, 18, 2, "EtherStatsPkts256to511Octets"		पूर्ण,
	अणु 0, 20, 2, "EtherStatsPkts512to1023Octets"		पूर्ण,
	अणु 0, 22, 2, "EtherStatsPkts1024to1518Octets"		पूर्ण,
	अणु 0, 24, 2, "EtherOversizeStats"			पूर्ण,
	अणु 0, 26, 2, "EtherStatsJabbers"				पूर्ण,
	अणु 0, 28, 2, "IfInUcastPkts"				पूर्ण,
	अणु 0, 30, 2, "EtherStatsMulticastPkts"			पूर्ण,
	अणु 0, 32, 2, "EtherStatsBroadcastPkts"			पूर्ण,
	अणु 0, 34, 2, "EtherStatsDropEvents"			पूर्ण,
	अणु 0, 36, 2, "Dot3StatsFCSErrors"			पूर्ण,
	अणु 0, 38, 2, "Dot3StatsSymbolErrors"			पूर्ण,
	अणु 0, 40, 2, "Dot3InPauseFrames"				पूर्ण,
	अणु 0, 42, 2, "Dot3ControlInUnknownOpcodes"		पूर्ण,
	अणु 0, 44, 4, "IfOutOctets"				पूर्ण,
	अणु 0, 48, 2, "Dot3StatsSingleCollisionFrames"		पूर्ण,
	अणु 0, 50, 2, "Dot3StatMultipleCollisionFrames"		पूर्ण,
	अणु 0, 52, 2, "Dot3sDeferredTransmissions"		पूर्ण,
	अणु 0, 54, 2, "Dot3StatsLateCollisions"			पूर्ण,
	अणु 0, 56, 2, "EtherStatsCollisions"			पूर्ण,
	अणु 0, 58, 2, "Dot3StatsExcessiveCollisions"		पूर्ण,
	अणु 0, 60, 2, "Dot3OutPauseFrames"			पूर्ण,
	अणु 0, 62, 2, "Dot1dBasePortDelayExceededDiscards"	पूर्ण,
	अणु 0, 64, 2, "Dot1dTpPortInDiscards"			पूर्ण,
	अणु 0, 66, 2, "IfOutUcastPkts"				पूर्ण,
	अणु 0, 68, 2, "IfOutMulticastPkts"			पूर्ण,
	अणु 0, 70, 2, "IfOutBroadcastPkts"			पूर्ण,
पूर्ण;

अटल पूर्णांक rtl8366rb_get_mib_counter(काष्ठा realtek_smi *smi,
				     पूर्णांक port,
				     काष्ठा rtl8366_mib_counter *mib,
				     u64 *mibvalue)
अणु
	u32 addr, val;
	पूर्णांक ret;
	पूर्णांक i;

	addr = RTL8366RB_MIB_COUNTER_BASE +
		RTL8366RB_MIB_COUNTER_PORT_OFFSET * (port) +
		mib->offset;

	/* Writing access counter address first
	 * then ASIC will prepare 64bits counter रुको क्रम being retrived
	 */
	ret = regmap_ग_लिखो(smi->map, addr, 0); /* Write whatever */
	अगर (ret)
		वापस ret;

	/* Read MIB control रेजिस्टर */
	ret = regmap_पढ़ो(smi->map, RTL8366RB_MIB_CTRL_REG, &val);
	अगर (ret)
		वापस -EIO;

	अगर (val & RTL8366RB_MIB_CTRL_BUSY_MASK)
		वापस -EBUSY;

	अगर (val & RTL8366RB_MIB_CTRL_RESET_MASK)
		वापस -EIO;

	/* Read each inभागidual MIB 16 bits at the समय */
	*mibvalue = 0;
	क्रम (i = mib->length; i > 0; i--) अणु
		ret = regmap_पढ़ो(smi->map, addr + (i - 1), &val);
		अगर (ret)
			वापस ret;
		*mibvalue = (*mibvalue << 16) | (val & 0xFFFF);
	पूर्ण
	वापस 0;
पूर्ण

अटल u32 rtl8366rb_get_irqmask(काष्ठा irq_data *d)
अणु
	पूर्णांक line = irqd_to_hwirq(d);
	u32 val;

	/* For line पूर्णांकerrupts we combine link करोwn in bits
	 * 6..11 with link up in bits 0..5 पूर्णांकo one पूर्णांकerrupt.
	 */
	अगर (line < 12)
		val = BIT(line) | BIT(line + 6);
	अन्यथा
		val = BIT(line);
	वापस val;
पूर्ण

अटल व्योम rtl8366rb_mask_irq(काष्ठा irq_data *d)
अणु
	काष्ठा realtek_smi *smi = irq_data_get_irq_chip_data(d);
	पूर्णांक ret;

	ret = regmap_update_bits(smi->map, RTL8366RB_INTERRUPT_MASK_REG,
				 rtl8366rb_get_irqmask(d), 0);
	अगर (ret)
		dev_err(smi->dev, "could not mask IRQ\n");
पूर्ण

अटल व्योम rtl8366rb_unmask_irq(काष्ठा irq_data *d)
अणु
	काष्ठा realtek_smi *smi = irq_data_get_irq_chip_data(d);
	पूर्णांक ret;

	ret = regmap_update_bits(smi->map, RTL8366RB_INTERRUPT_MASK_REG,
				 rtl8366rb_get_irqmask(d),
				 rtl8366rb_get_irqmask(d));
	अगर (ret)
		dev_err(smi->dev, "could not unmask IRQ\n");
पूर्ण

अटल irqवापस_t rtl8366rb_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा realtek_smi *smi = data;
	u32 stat;
	पूर्णांक ret;

	/* This clears the IRQ status रेजिस्टर */
	ret = regmap_पढ़ो(smi->map, RTL8366RB_INTERRUPT_STATUS_REG,
			  &stat);
	अगर (ret) अणु
		dev_err(smi->dev, "can't read interrupt status\n");
		वापस IRQ_NONE;
	पूर्ण
	stat &= RTL8366RB_INTERRUPT_VALID;
	अगर (!stat)
		वापस IRQ_NONE;
	जबतक (stat) अणु
		पूर्णांक line = __ffs(stat);
		पूर्णांक child_irq;

		stat &= ~BIT(line);
		/* For line पूर्णांकerrupts we combine link करोwn in bits
		 * 6..11 with link up in bits 0..5 पूर्णांकo one पूर्णांकerrupt.
		 */
		अगर (line < 12 && line > 5)
			line -= 5;
		child_irq = irq_find_mapping(smi->irqकरोमुख्य, line);
		handle_nested_irq(child_irq);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा irq_chip rtl8366rb_irq_chip = अणु
	.name = "RTL8366RB",
	.irq_mask = rtl8366rb_mask_irq,
	.irq_unmask = rtl8366rb_unmask_irq,
पूर्ण;

अटल पूर्णांक rtl8366rb_irq_map(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक irq,
			     irq_hw_number_t hwirq)
अणु
	irq_set_chip_data(irq, करोमुख्य->host_data);
	irq_set_chip_and_handler(irq, &rtl8366rb_irq_chip, handle_simple_irq);
	irq_set_nested_thपढ़ो(irq, 1);
	irq_set_noprobe(irq);

	वापस 0;
पूर्ण

अटल व्योम rtl8366rb_irq_unmap(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq)
अणु
	irq_set_nested_thपढ़ो(irq, 0);
	irq_set_chip_and_handler(irq, शून्य, शून्य);
	irq_set_chip_data(irq, शून्य);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops rtl8366rb_irqकरोमुख्य_ops = अणु
	.map = rtl8366rb_irq_map,
	.unmap = rtl8366rb_irq_unmap,
	.xlate  = irq_करोमुख्य_xlate_onecell,
पूर्ण;

अटल पूर्णांक rtl8366rb_setup_cascaded_irq(काष्ठा realtek_smi *smi)
अणु
	काष्ठा device_node *पूर्णांकc;
	अचिन्हित दीर्घ irq_trig;
	पूर्णांक irq;
	पूर्णांक ret;
	u32 val;
	पूर्णांक i;

	पूर्णांकc = of_get_child_by_name(smi->dev->of_node, "interrupt-controller");
	अगर (!पूर्णांकc) अणु
		dev_err(smi->dev, "missing child interrupt-controller node\n");
		वापस -EINVAL;
	पूर्ण
	/* RB8366RB IRQs cascade off this one */
	irq = of_irq_get(पूर्णांकc, 0);
	अगर (irq <= 0) अणु
		dev_err(smi->dev, "failed to get parent IRQ\n");
		ret = irq ? irq : -EINVAL;
		जाओ out_put_node;
	पूर्ण

	/* This clears the IRQ status रेजिस्टर */
	ret = regmap_पढ़ो(smi->map, RTL8366RB_INTERRUPT_STATUS_REG,
			  &val);
	अगर (ret) अणु
		dev_err(smi->dev, "can't read interrupt status\n");
		जाओ out_put_node;
	पूर्ण

	/* Fetch IRQ edge inक्रमmation from the descriptor */
	irq_trig = irqd_get_trigger_type(irq_get_irq_data(irq));
	चयन (irq_trig) अणु
	हाल IRQF_TRIGGER_RISING:
	हाल IRQF_TRIGGER_HIGH:
		dev_info(smi->dev, "active high/rising IRQ\n");
		val = 0;
		अवरोध;
	हाल IRQF_TRIGGER_FALLING:
	हाल IRQF_TRIGGER_LOW:
		dev_info(smi->dev, "active low/falling IRQ\n");
		val = RTL8366RB_INTERRUPT_POLARITY;
		अवरोध;
	पूर्ण
	ret = regmap_update_bits(smi->map, RTL8366RB_INTERRUPT_CONTROL_REG,
				 RTL8366RB_INTERRUPT_POLARITY,
				 val);
	अगर (ret) अणु
		dev_err(smi->dev, "could not configure IRQ polarity\n");
		जाओ out_put_node;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(smi->dev, irq, शून्य,
					rtl8366rb_irq, IRQF_ONESHOT,
					"RTL8366RB", smi);
	अगर (ret) अणु
		dev_err(smi->dev, "unable to request irq: %d\n", ret);
		जाओ out_put_node;
	पूर्ण
	smi->irqकरोमुख्य = irq_करोमुख्य_add_linear(पूर्णांकc,
					       RTL8366RB_NUM_INTERRUPT,
					       &rtl8366rb_irqकरोमुख्य_ops,
					       smi);
	अगर (!smi->irqकरोमुख्य) अणु
		dev_err(smi->dev, "failed to create IRQ domain\n");
		ret = -EINVAL;
		जाओ out_put_node;
	पूर्ण
	क्रम (i = 0; i < smi->num_ports; i++)
		irq_set_parent(irq_create_mapping(smi->irqकरोमुख्य, i), irq);

out_put_node:
	of_node_put(पूर्णांकc);
	वापस ret;
पूर्ण

अटल पूर्णांक rtl8366rb_set_addr(काष्ठा realtek_smi *smi)
अणु
	u8 addr[ETH_ALEN];
	u16 val;
	पूर्णांक ret;

	eth_अक्रमom_addr(addr);

	dev_info(smi->dev, "set MAC: %02X:%02X:%02X:%02X:%02X:%02X\n",
		 addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);
	val = addr[0] << 8 | addr[1];
	ret = regmap_ग_लिखो(smi->map, RTL8366RB_SMAR0, val);
	अगर (ret)
		वापस ret;
	val = addr[2] << 8 | addr[3];
	ret = regmap_ग_लिखो(smi->map, RTL8366RB_SMAR1, val);
	अगर (ret)
		वापस ret;
	val = addr[4] << 8 | addr[5];
	ret = regmap_ग_लिखो(smi->map, RTL8366RB_SMAR2, val);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

/* Found in a venकरोr driver */

/* Struct क्रम handling the jam tables' entries */
काष्ठा rtl8366rb_jam_tbl_entry अणु
	u16 reg;
	u16 val;
पूर्ण;

/* For the "version 0" early silicon, appear in most source releases */
अटल स्थिर काष्ठा rtl8366rb_jam_tbl_entry rtl8366rb_init_jam_ver_0[] = अणु
	अणु0x000B, 0x0001पूर्ण, अणु0x03A6, 0x0100पूर्ण, अणु0x03A7, 0x0001पूर्ण, अणु0x02D1, 0x3FFFपूर्ण,
	अणु0x02D2, 0x3FFFपूर्ण, अणु0x02D3, 0x3FFFपूर्ण, अणु0x02D4, 0x3FFFपूर्ण, अणु0x02D5, 0x3FFFपूर्ण,
	अणु0x02D6, 0x3FFFपूर्ण, अणु0x02D7, 0x3FFFपूर्ण, अणु0x02D8, 0x3FFFपूर्ण, अणु0x022B, 0x0688पूर्ण,
	अणु0x022C, 0x0FACपूर्ण, अणु0x03D0, 0x4688पूर्ण, अणु0x03D1, 0x01F5पूर्ण, अणु0x0000, 0x0830पूर्ण,
	अणु0x02F9, 0x0200पूर्ण, अणु0x02F7, 0x7FFFपूर्ण, अणु0x02F8, 0x03FFपूर्ण, अणु0x0080, 0x03E8पूर्ण,
	अणु0x0081, 0x00CEपूर्ण, अणु0x0082, 0x00DAपूर्ण, अणु0x0083, 0x0230पूर्ण, अणु0xBE0F, 0x2000पूर्ण,
	अणु0x0231, 0x422Aपूर्ण, अणु0x0232, 0x422Aपूर्ण, अणु0x0233, 0x422Aपूर्ण, अणु0x0234, 0x422Aपूर्ण,
	अणु0x0235, 0x422Aपूर्ण, अणु0x0236, 0x422Aपूर्ण, अणु0x0237, 0x422Aपूर्ण, अणु0x0238, 0x422Aपूर्ण,
	अणु0x0239, 0x422Aपूर्ण, अणु0x023A, 0x422Aपूर्ण, अणु0x023B, 0x422Aपूर्ण, अणु0x023C, 0x422Aपूर्ण,
	अणु0x023D, 0x422Aपूर्ण, अणु0x023E, 0x422Aपूर्ण, अणु0x023F, 0x422Aपूर्ण, अणु0x0240, 0x422Aपूर्ण,
	अणु0x0241, 0x422Aपूर्ण, अणु0x0242, 0x422Aपूर्ण, अणु0x0243, 0x422Aपूर्ण, अणु0x0244, 0x422Aपूर्ण,
	अणु0x0245, 0x422Aपूर्ण, अणु0x0246, 0x422Aपूर्ण, अणु0x0247, 0x422Aपूर्ण, अणु0x0248, 0x422Aपूर्ण,
	अणु0x0249, 0x0146पूर्ण, अणु0x024A, 0x0146पूर्ण, अणु0x024B, 0x0146पूर्ण, अणु0xBE03, 0xC961पूर्ण,
	अणु0x024D, 0x0146पूर्ण, अणु0x024E, 0x0146पूर्ण, अणु0x024F, 0x0146पूर्ण, अणु0x0250, 0x0146पूर्ण,
	अणु0xBE64, 0x0226पूर्ण, अणु0x0252, 0x0146पूर्ण, अणु0x0253, 0x0146पूर्ण, अणु0x024C, 0x0146पूर्ण,
	अणु0x0251, 0x0146पूर्ण, अणु0x0254, 0x0146पूर्ण, अणु0xBE62, 0x3FD0पूर्ण, अणु0x0084, 0x0320पूर्ण,
	अणु0x0255, 0x0146पूर्ण, अणु0x0256, 0x0146पूर्ण, अणु0x0257, 0x0146पूर्ण, अणु0x0258, 0x0146पूर्ण,
	अणु0x0259, 0x0146पूर्ण, अणु0x025A, 0x0146पूर्ण, अणु0x025B, 0x0146पूर्ण, अणु0x025C, 0x0146पूर्ण,
	अणु0x025D, 0x0146पूर्ण, अणु0x025E, 0x0146पूर्ण, अणु0x025F, 0x0146पूर्ण, अणु0x0260, 0x0146पूर्ण,
	अणु0x0261, 0xA23Fपूर्ण, अणु0x0262, 0x0294पूर्ण, अणु0x0263, 0xA23Fपूर्ण, अणु0x0264, 0x0294पूर्ण,
	अणु0x0265, 0xA23Fपूर्ण, अणु0x0266, 0x0294पूर्ण, अणु0x0267, 0xA23Fपूर्ण, अणु0x0268, 0x0294पूर्ण,
	अणु0x0269, 0xA23Fपूर्ण, अणु0x026A, 0x0294पूर्ण, अणु0x026B, 0xA23Fपूर्ण, अणु0x026C, 0x0294पूर्ण,
	अणु0x026D, 0xA23Fपूर्ण, अणु0x026E, 0x0294पूर्ण, अणु0x026F, 0xA23Fपूर्ण, अणु0x0270, 0x0294पूर्ण,
	अणु0x02F5, 0x0048पूर्ण, अणु0xBE09, 0x0E00पूर्ण, अणु0xBE1E, 0x0FA0पूर्ण, अणु0xBE14, 0x8448पूर्ण,
	अणु0xBE15, 0x1007पूर्ण, अणु0xBE4A, 0xA284पूर्ण, अणु0xC454, 0x3F0Bपूर्ण, अणु0xC474, 0x3F0Bपूर्ण,
	अणु0xBE48, 0x3672पूर्ण, अणु0xBE4B, 0x17A7पूर्ण, अणु0xBE4C, 0x0B15पूर्ण, अणु0xBE52, 0x0EDDपूर्ण,
	अणु0xBE49, 0x8C00पूर्ण, अणु0xBE5B, 0x785Cपूर्ण, अणु0xBE5C, 0x785Cपूर्ण, अणु0xBE5D, 0x785Cपूर्ण,
	अणु0xBE61, 0x368Aपूर्ण, अणु0xBE63, 0x9B84पूर्ण, अणु0xC456, 0xCC13पूर्ण, अणु0xC476, 0xCC13पूर्ण,
	अणु0xBE65, 0x307Dपूर्ण, अणु0xBE6D, 0x0005पूर्ण, अणु0xBE6E, 0xE120पूर्ण, अणु0xBE2E, 0x7BAFपूर्ण,
पूर्ण;

/* This v1 init sequence is from Belkin F5D8235 U-Boot release */
अटल स्थिर काष्ठा rtl8366rb_jam_tbl_entry rtl8366rb_init_jam_ver_1[] = अणु
	अणु0x0000, 0x0830पूर्ण, अणु0x0001, 0x8000पूर्ण, अणु0x0400, 0x8130पूर्ण, अणु0xBE78, 0x3C3Cपूर्ण,
	अणु0x0431, 0x5432पूर्ण, अणु0xBE37, 0x0CE4पूर्ण, अणु0x02FA, 0xFFDFपूर्ण, अणु0x02FB, 0xFFE0पूर्ण,
	अणु0xC44C, 0x1585पूर्ण, अणु0xC44C, 0x1185पूर्ण, अणु0xC44C, 0x1585पूर्ण, अणु0xC46C, 0x1585पूर्ण,
	अणु0xC46C, 0x1185पूर्ण, अणु0xC46C, 0x1585पूर्ण, अणु0xC451, 0x2135पूर्ण, अणु0xC471, 0x2135पूर्ण,
	अणु0xBE10, 0x8140पूर्ण, अणु0xBE15, 0x0007पूर्ण, अणु0xBE6E, 0xE120पूर्ण, अणु0xBE69, 0xD20Fपूर्ण,
	अणु0xBE6B, 0x0320पूर्ण, अणु0xBE24, 0xB000पूर्ण, अणु0xBE23, 0xFF51पूर्ण, अणु0xBE22, 0xDF20पूर्ण,
	अणु0xBE21, 0x0140पूर्ण, अणु0xBE20, 0x00BBपूर्ण, अणु0xBE24, 0xB800पूर्ण, अणु0xBE24, 0x0000पूर्ण,
	अणु0xBE24, 0x7000पूर्ण, अणु0xBE23, 0xFF51पूर्ण, अणु0xBE22, 0xDF60पूर्ण, अणु0xBE21, 0x0140पूर्ण,
	अणु0xBE20, 0x0077पूर्ण, अणु0xBE24, 0x7800पूर्ण, अणु0xBE24, 0x0000पूर्ण, अणु0xBE2E, 0x7B7Aपूर्ण,
	अणु0xBE36, 0x0CE4पूर्ण, अणु0x02F5, 0x0048पूर्ण, अणु0xBE77, 0x2940पूर्ण, अणु0x000A, 0x83E0पूर्ण,
	अणु0xBE79, 0x3C3Cपूर्ण, अणु0xBE00, 0x1340पूर्ण,
पूर्ण;

/* This v2 init sequence is from Belkin F5D8235 U-Boot release */
अटल स्थिर काष्ठा rtl8366rb_jam_tbl_entry rtl8366rb_init_jam_ver_2[] = अणु
	अणु0x0450, 0x0000पूर्ण, अणु0x0400, 0x8130पूर्ण, अणु0x000A, 0x83EDपूर्ण, अणु0x0431, 0x5432पूर्ण,
	अणु0xC44F, 0x6250पूर्ण, अणु0xC46F, 0x6250पूर्ण, अणु0xC456, 0x0C14पूर्ण, अणु0xC476, 0x0C14पूर्ण,
	अणु0xC44C, 0x1C85पूर्ण, अणु0xC44C, 0x1885पूर्ण, अणु0xC44C, 0x1C85पूर्ण, अणु0xC46C, 0x1C85पूर्ण,
	अणु0xC46C, 0x1885पूर्ण, अणु0xC46C, 0x1C85पूर्ण, अणु0xC44C, 0x0885पूर्ण, अणु0xC44C, 0x0881पूर्ण,
	अणु0xC44C, 0x0885पूर्ण, अणु0xC46C, 0x0885पूर्ण, अणु0xC46C, 0x0881पूर्ण, अणु0xC46C, 0x0885पूर्ण,
	अणु0xBE2E, 0x7BA7पूर्ण, अणु0xBE36, 0x1000पूर्ण, अणु0xBE37, 0x1000पूर्ण, अणु0x8000, 0x0001पूर्ण,
	अणु0xBE69, 0xD50Fपूर्ण, अणु0x8000, 0x0000पूर्ण, अणु0xBE69, 0xD50Fपूर्ण, अणु0xBE6E, 0x0320पूर्ण,
	अणु0xBE77, 0x2940पूर्ण, अणु0xBE78, 0x3C3Cपूर्ण, अणु0xBE79, 0x3C3Cपूर्ण, अणु0xBE6E, 0xE120पूर्ण,
	अणु0x8000, 0x0001पूर्ण, अणु0xBE15, 0x1007पूर्ण, अणु0x8000, 0x0000पूर्ण, अणु0xBE15, 0x1007पूर्ण,
	अणु0xBE14, 0x0448पूर्ण, अणु0xBE1E, 0x00A0पूर्ण, अणु0xBE10, 0x8160पूर्ण, अणु0xBE10, 0x8140पूर्ण,
	अणु0xBE00, 0x1340पूर्ण, अणु0x0F51, 0x0010पूर्ण,
पूर्ण;

/* Appears in a DDWRT code dump */
अटल स्थिर काष्ठा rtl8366rb_jam_tbl_entry rtl8366rb_init_jam_ver_3[] = अणु
	अणु0x0000, 0x0830पूर्ण, अणु0x0400, 0x8130पूर्ण, अणु0x000A, 0x83EDपूर्ण, अणु0x0431, 0x5432पूर्ण,
	अणु0x0F51, 0x0017पूर्ण, अणु0x02F5, 0x0048पूर्ण, अणु0x02FA, 0xFFDFपूर्ण, अणु0x02FB, 0xFFE0पूर्ण,
	अणु0xC456, 0x0C14पूर्ण, अणु0xC476, 0x0C14पूर्ण, अणु0xC454, 0x3F8Bपूर्ण, अणु0xC474, 0x3F8Bपूर्ण,
	अणु0xC450, 0x2071पूर्ण, अणु0xC470, 0x2071पूर्ण, अणु0xC451, 0x226Bपूर्ण, अणु0xC471, 0x226Bपूर्ण,
	अणु0xC452, 0xA293पूर्ण, अणु0xC472, 0xA293पूर्ण, अणु0xC44C, 0x1585पूर्ण, अणु0xC44C, 0x1185पूर्ण,
	अणु0xC44C, 0x1585पूर्ण, अणु0xC46C, 0x1585पूर्ण, अणु0xC46C, 0x1185पूर्ण, अणु0xC46C, 0x1585पूर्ण,
	अणु0xC44C, 0x0185पूर्ण, अणु0xC44C, 0x0181पूर्ण, अणु0xC44C, 0x0185पूर्ण, अणु0xC46C, 0x0185पूर्ण,
	अणु0xC46C, 0x0181पूर्ण, अणु0xC46C, 0x0185पूर्ण, अणु0xBE24, 0xB000पूर्ण, अणु0xBE23, 0xFF51पूर्ण,
	अणु0xBE22, 0xDF20पूर्ण, अणु0xBE21, 0x0140पूर्ण, अणु0xBE20, 0x00BBपूर्ण, अणु0xBE24, 0xB800पूर्ण,
	अणु0xBE24, 0x0000पूर्ण, अणु0xBE24, 0x7000पूर्ण, अणु0xBE23, 0xFF51पूर्ण, अणु0xBE22, 0xDF60पूर्ण,
	अणु0xBE21, 0x0140पूर्ण, अणु0xBE20, 0x0077पूर्ण, अणु0xBE24, 0x7800पूर्ण, अणु0xBE24, 0x0000पूर्ण,
	अणु0xBE2E, 0x7BA7पूर्ण, अणु0xBE36, 0x1000पूर्ण, अणु0xBE37, 0x1000पूर्ण, अणु0x8000, 0x0001पूर्ण,
	अणु0xBE69, 0xD50Fपूर्ण, अणु0x8000, 0x0000पूर्ण, अणु0xBE69, 0xD50Fपूर्ण, अणु0xBE6B, 0x0320पूर्ण,
	अणु0xBE77, 0x2800पूर्ण, अणु0xBE78, 0x3C3Cपूर्ण, अणु0xBE79, 0x3C3Cपूर्ण, अणु0xBE6E, 0xE120पूर्ण,
	अणु0x8000, 0x0001पूर्ण, अणु0xBE10, 0x8140पूर्ण, अणु0x8000, 0x0000पूर्ण, अणु0xBE10, 0x8140पूर्ण,
	अणु0xBE15, 0x1007पूर्ण, अणु0xBE14, 0x0448पूर्ण, अणु0xBE1E, 0x00A0पूर्ण, अणु0xBE10, 0x8160पूर्ण,
	अणु0xBE10, 0x8140पूर्ण, अणु0xBE00, 0x1340पूर्ण, अणु0x0450, 0x0000पूर्ण, अणु0x0401, 0x0000पूर्ण,
पूर्ण;

/* Belkin F5D8235 v1, "belkin,f5d8235-v1" */
अटल स्थिर काष्ठा rtl8366rb_jam_tbl_entry rtl8366rb_init_jam_f5d8235[] = अणु
	अणु0x0242, 0x02BFपूर्ण, अणु0x0245, 0x02BFपूर्ण, अणु0x0248, 0x02BFपूर्ण, अणु0x024B, 0x02BFपूर्ण,
	अणु0x024E, 0x02BFपूर्ण, अणु0x0251, 0x02BFपूर्ण, अणु0x0254, 0x0A3Fपूर्ण, अणु0x0256, 0x0A3Fपूर्ण,
	अणु0x0258, 0x0A3Fपूर्ण, अणु0x025A, 0x0A3Fपूर्ण, अणु0x025C, 0x0A3Fपूर्ण, अणु0x025E, 0x0A3Fपूर्ण,
	अणु0x0263, 0x007Cपूर्ण, अणु0x0100, 0x0004पूर्ण, अणु0xBE5B, 0x3500पूर्ण, अणु0x800E, 0x200Fपूर्ण,
	अणु0xBE1D, 0x0F00पूर्ण, अणु0x8001, 0x5011पूर्ण, अणु0x800A, 0xA2F4पूर्ण, अणु0x800B, 0x17A3पूर्ण,
	अणु0xBE4B, 0x17A3पूर्ण, अणु0xBE41, 0x5011पूर्ण, अणु0xBE17, 0x2100पूर्ण, अणु0x8000, 0x8304पूर्ण,
	अणु0xBE40, 0x8304पूर्ण, अणु0xBE4A, 0xA2F4पूर्ण, अणु0x800C, 0xA8D5पूर्ण, अणु0x8014, 0x5500पूर्ण,
	अणु0x8015, 0x0004पूर्ण, अणु0xBE4C, 0xA8D5पूर्ण, अणु0xBE59, 0x0008पूर्ण, अणु0xBE09, 0x0E00पूर्ण,
	अणु0xBE36, 0x1036पूर्ण, अणु0xBE37, 0x1036पूर्ण, अणु0x800D, 0x00FFपूर्ण, अणु0xBE4D, 0x00FFपूर्ण,
पूर्ण;

/* DGN3500, "netgear,dgn3500", "netgear,dgn3500b" */
अटल स्थिर काष्ठा rtl8366rb_jam_tbl_entry rtl8366rb_init_jam_dgn3500[] = अणु
	अणु0x0000, 0x0830पूर्ण, अणु0x0400, 0x8130पूर्ण, अणु0x000A, 0x83EDपूर्ण, अणु0x0F51, 0x0017पूर्ण,
	अणु0x02F5, 0x0048पूर्ण, अणु0x02FA, 0xFFDFपूर्ण, अणु0x02FB, 0xFFE0पूर्ण, अणु0x0450, 0x0000पूर्ण,
	अणु0x0401, 0x0000पूर्ण, अणु0x0431, 0x0960पूर्ण,
पूर्ण;

/* This jam table activates "green ethernet", which means low घातer mode
 * and is claimed to detect the cable length and not use more घातer than
 * necessary, and the ports should enter घातer saving mode 10 seconds after
 * a cable is disconnected. Seems to always be the same.
 */
अटल स्थिर काष्ठा rtl8366rb_jam_tbl_entry rtl8366rb_green_jam[] = अणु
	अणु0xBE78, 0x323Cपूर्ण, अणु0xBE77, 0x5000पूर्ण, अणु0xBE2E, 0x7BA7पूर्ण,
	अणु0xBE59, 0x3459पूर्ण, अणु0xBE5A, 0x745Aपूर्ण, अणु0xBE5B, 0x785Cपूर्ण,
	अणु0xBE5C, 0x785Cपूर्ण, अणु0xBE6E, 0xE120पूर्ण, अणु0xBE79, 0x323Cपूर्ण,
पूर्ण;

/* Function that jams the tables in the proper रेजिस्टरs */
अटल पूर्णांक rtl8366rb_jam_table(स्थिर काष्ठा rtl8366rb_jam_tbl_entry *jam_table,
			       पूर्णांक jam_size, काष्ठा realtek_smi *smi,
			       bool ग_लिखो_dbg)
अणु
	u32 val;
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < jam_size; i++) अणु
		अगर ((jam_table[i].reg & 0xBE00) == 0xBE00) अणु
			ret = regmap_पढ़ो(smi->map,
					  RTL8366RB_PHY_ACCESS_BUSY_REG,
					  &val);
			अगर (ret)
				वापस ret;
			अगर (!(val & RTL8366RB_PHY_INT_BUSY)) अणु
				ret = regmap_ग_लिखो(smi->map,
						RTL8366RB_PHY_ACCESS_CTRL_REG,
						RTL8366RB_PHY_CTRL_WRITE);
				अगर (ret)
					वापस ret;
			पूर्ण
		पूर्ण
		अगर (ग_लिखो_dbg)
			dev_dbg(smi->dev, "jam %04x into register %04x\n",
				jam_table[i].val,
				jam_table[i].reg);
		ret = regmap_ग_लिखो(smi->map,
				   jam_table[i].reg,
				   jam_table[i].val);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rtl8366rb_setup(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा realtek_smi *smi = ds->priv;
	स्थिर काष्ठा rtl8366rb_jam_tbl_entry *jam_table;
	काष्ठा rtl8366rb *rb;
	u32 chip_ver = 0;
	u32 chip_id = 0;
	पूर्णांक jam_size;
	u32 val;
	पूर्णांक ret;
	पूर्णांक i;

	rb = smi->chip_data;

	ret = regmap_पढ़ो(smi->map, RTL8366RB_CHIP_ID_REG, &chip_id);
	अगर (ret) अणु
		dev_err(smi->dev, "unable to read chip id\n");
		वापस ret;
	पूर्ण

	चयन (chip_id) अणु
	हाल RTL8366RB_CHIP_ID_8366:
		अवरोध;
	शेष:
		dev_err(smi->dev, "unknown chip id (%04x)\n", chip_id);
		वापस -ENODEV;
	पूर्ण

	ret = regmap_पढ़ो(smi->map, RTL8366RB_CHIP_VERSION_CTRL_REG,
			  &chip_ver);
	अगर (ret) अणु
		dev_err(smi->dev, "unable to read chip version\n");
		वापस ret;
	पूर्ण

	dev_info(smi->dev, "RTL%04x ver %u chip found\n",
		 chip_id, chip_ver & RTL8366RB_CHIP_VERSION_MASK);

	/* Do the init dance using the right jam table */
	चयन (chip_ver) अणु
	हाल 0:
		jam_table = rtl8366rb_init_jam_ver_0;
		jam_size = ARRAY_SIZE(rtl8366rb_init_jam_ver_0);
		अवरोध;
	हाल 1:
		jam_table = rtl8366rb_init_jam_ver_1;
		jam_size = ARRAY_SIZE(rtl8366rb_init_jam_ver_1);
		अवरोध;
	हाल 2:
		jam_table = rtl8366rb_init_jam_ver_2;
		jam_size = ARRAY_SIZE(rtl8366rb_init_jam_ver_2);
		अवरोध;
	शेष:
		jam_table = rtl8366rb_init_jam_ver_3;
		jam_size = ARRAY_SIZE(rtl8366rb_init_jam_ver_3);
		अवरोध;
	पूर्ण

	/* Special jam tables क्रम special routers
	 * TODO: are these necessary? Maपूर्णांकainers, please test
	 * without them, using just the off-the-shelf tables.
	 */
	अगर (of_machine_is_compatible("belkin,f5d8235-v1")) अणु
		jam_table = rtl8366rb_init_jam_f5d8235;
		jam_size = ARRAY_SIZE(rtl8366rb_init_jam_f5d8235);
	पूर्ण
	अगर (of_machine_is_compatible("netgear,dgn3500") ||
	    of_machine_is_compatible("netgear,dgn3500b")) अणु
		jam_table = rtl8366rb_init_jam_dgn3500;
		jam_size = ARRAY_SIZE(rtl8366rb_init_jam_dgn3500);
	पूर्ण

	ret = rtl8366rb_jam_table(jam_table, jam_size, smi, true);
	अगर (ret)
		वापस ret;

	/* Set up the "green ethernet" feature */
	ret = rtl8366rb_jam_table(rtl8366rb_green_jam,
				  ARRAY_SIZE(rtl8366rb_green_jam), smi, false);
	अगर (ret)
		वापस ret;

	ret = regmap_ग_लिखो(smi->map,
			   RTL8366RB_GREEN_FEATURE_REG,
			   (chip_ver == 1) ? 0x0007 : 0x0003);
	अगर (ret)
		वापस ret;

	/* Venकरोr driver sets 0x240 in रेजिस्टरs 0xc and 0xd (unकरोcumented) */
	ret = regmap_ग_लिखो(smi->map, 0x0c, 0x240);
	अगर (ret)
		वापस ret;
	ret = regmap_ग_लिखो(smi->map, 0x0d, 0x240);
	अगर (ret)
		वापस ret;

	/* Set some अक्रमom MAC address */
	ret = rtl8366rb_set_addr(smi);
	अगर (ret)
		वापस ret;

	/* Enable CPU port with custom DSA tag 8899.
	 *
	 * If you set RTL8368RB_CPU_NO_TAG (bit 15) in this रेजिस्टरs
	 * the custom tag is turned off.
	 */
	ret = regmap_update_bits(smi->map, RTL8368RB_CPU_CTRL_REG,
				 0xFFFF,
				 BIT(smi->cpu_port));
	अगर (ret)
		वापस ret;

	/* Make sure we शेष-enable the fixed CPU port */
	ret = regmap_update_bits(smi->map, RTL8366RB_PECR,
				 BIT(smi->cpu_port),
				 0);
	अगर (ret)
		वापस ret;

	/* Set maximum packet length to 1536 bytes */
	ret = regmap_update_bits(smi->map, RTL8366RB_SGCR,
				 RTL8366RB_SGCR_MAX_LENGTH_MASK,
				 RTL8366RB_SGCR_MAX_LENGTH_1536);
	अगर (ret)
		वापस ret;
	क्रम (i = 0; i < RTL8366RB_NUM_PORTS; i++)
		/* layer 2 size, see rtl8366rb_change_mtu() */
		rb->max_mtu[i] = 1532;

	/* Enable learning क्रम all ports */
	ret = regmap_ग_लिखो(smi->map, RTL8366RB_SSCR0, 0);
	अगर (ret)
		वापस ret;

	/* Enable स्वतः ageing क्रम all ports */
	ret = regmap_ग_लिखो(smi->map, RTL8366RB_SSCR1, 0);
	अगर (ret)
		वापस ret;

	/* Port 4 setup: this enables Port 4, usually the WAN port,
	 * common PHY IO mode is apparently mode 0, and this is not what
	 * the port is initialized to. There is no explanation of the
	 * IO modes in the Realtek source code, अगर your WAN port is
	 * connected to something exotic such as fiber, then this might
	 * be worth experimenting with.
	 */
	ret = regmap_update_bits(smi->map, RTL8366RB_PMC0,
				 RTL8366RB_PMC0_P4_IOMODE_MASK,
				 0 << RTL8366RB_PMC0_P4_IOMODE_SHIFT);
	अगर (ret)
		वापस ret;

	/* Discard VLAN tagged packets अगर the port is not a member of
	 * the VLAN with which the packets is associated.
	 */
	ret = regmap_ग_लिखो(smi->map, RTL8366RB_VLAN_INGRESS_CTRL2_REG,
			   RTL8366RB_PORT_ALL);
	अगर (ret)
		वापस ret;

	/* Don't drop packets whose DA has not been learned */
	ret = regmap_update_bits(smi->map, RTL8366RB_SSCR2,
				 RTL8366RB_SSCR2_DROP_UNKNOWN_DA, 0);
	अगर (ret)
		वापस ret;

	/* Set blinking, TODO: make this configurable */
	ret = regmap_update_bits(smi->map, RTL8366RB_LED_BLINKRATE_REG,
				 RTL8366RB_LED_BLINKRATE_MASK,
				 RTL8366RB_LED_BLINKRATE_56MS);
	अगर (ret)
		वापस ret;

	/* Set up LED activity:
	 * Each port has 4 LEDs, we configure all ports to the same
	 * behaviour (no inभागidual config) but we can set up each
	 * LED separately.
	 */
	अगर (smi->leds_disabled) अणु
		/* Turn everything off */
		regmap_update_bits(smi->map,
				   RTL8366RB_LED_0_1_CTRL_REG,
				   0x0FFF, 0);
		regmap_update_bits(smi->map,
				   RTL8366RB_LED_2_3_CTRL_REG,
				   0x0FFF, 0);
		regmap_update_bits(smi->map,
				   RTL8366RB_INTERRUPT_CONTROL_REG,
				   RTL8366RB_P4_RGMII_LED,
				   0);
		val = RTL8366RB_LED_OFF;
	पूर्ण अन्यथा अणु
		/* TODO: make this configurable per LED */
		val = RTL8366RB_LED_FORCE;
	पूर्ण
	क्रम (i = 0; i < 4; i++) अणु
		ret = regmap_update_bits(smi->map,
					 RTL8366RB_LED_CTRL_REG,
					 0xf << (i * 4),
					 val << (i * 4));
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = rtl8366_init_vlan(smi);
	अगर (ret)
		वापस ret;

	ret = rtl8366rb_setup_cascaded_irq(smi);
	अगर (ret)
		dev_info(smi->dev, "no interrupt support\n");

	ret = realtek_smi_setup_mdio(smi);
	अगर (ret) अणु
		dev_info(smi->dev, "could not set up MDIO bus\n");
		वापस -ENODEV;
	पूर्ण

	ds->configure_vlan_जबतक_not_filtering = false;

	वापस 0;
पूर्ण

अटल क्रमागत dsa_tag_protocol rtl8366_get_tag_protocol(काष्ठा dsa_चयन *ds,
						      पूर्णांक port,
						      क्रमागत dsa_tag_protocol mp)
अणु
	/* This चयन uses the 4 byte protocol A Realtek DSA tag */
	वापस DSA_TAG_PROTO_RTL4_A;
पूर्ण

अटल व्योम
rtl8366rb_mac_link_up(काष्ठा dsa_चयन *ds, पूर्णांक port, अचिन्हित पूर्णांक mode,
		      phy_पूर्णांकerface_t पूर्णांकerface, काष्ठा phy_device *phydev,
		      पूर्णांक speed, पूर्णांक duplex, bool tx_छोड़ो, bool rx_छोड़ो)
अणु
	काष्ठा realtek_smi *smi = ds->priv;
	पूर्णांक ret;

	अगर (port != smi->cpu_port)
		वापस;

	dev_dbg(smi->dev, "MAC link up on CPU port (%d)\n", port);

	/* Force the fixed CPU port पूर्णांकo 1Gbit mode, no स्वतःnegotiation */
	ret = regmap_update_bits(smi->map, RTL8366RB_MAC_FORCE_CTRL_REG,
				 BIT(port), BIT(port));
	अगर (ret) अणु
		dev_err(smi->dev, "failed to force 1Gbit on CPU port\n");
		वापस;
	पूर्ण

	ret = regmap_update_bits(smi->map, RTL8366RB_PAACR2,
				 0xFF00U,
				 RTL8366RB_PAACR_CPU_PORT << 8);
	अगर (ret) अणु
		dev_err(smi->dev, "failed to set PAACR on CPU port\n");
		वापस;
	पूर्ण

	/* Enable the CPU port */
	ret = regmap_update_bits(smi->map, RTL8366RB_PECR, BIT(port),
				 0);
	अगर (ret) अणु
		dev_err(smi->dev, "failed to enable the CPU port\n");
		वापस;
	पूर्ण
पूर्ण

अटल व्योम
rtl8366rb_mac_link_करोwn(काष्ठा dsa_चयन *ds, पूर्णांक port, अचिन्हित पूर्णांक mode,
			phy_पूर्णांकerface_t पूर्णांकerface)
अणु
	काष्ठा realtek_smi *smi = ds->priv;
	पूर्णांक ret;

	अगर (port != smi->cpu_port)
		वापस;

	dev_dbg(smi->dev, "MAC link down on CPU port (%d)\n", port);

	/* Disable the CPU port */
	ret = regmap_update_bits(smi->map, RTL8366RB_PECR, BIT(port),
				 BIT(port));
	अगर (ret) अणु
		dev_err(smi->dev, "failed to disable the CPU port\n");
		वापस;
	पूर्ण
पूर्ण

अटल व्योम rb8366rb_set_port_led(काष्ठा realtek_smi *smi,
				  पूर्णांक port, bool enable)
अणु
	u16 val = enable ? 0x3f : 0;
	पूर्णांक ret;

	अगर (smi->leds_disabled)
		वापस;

	चयन (port) अणु
	हाल 0:
		ret = regmap_update_bits(smi->map,
					 RTL8366RB_LED_0_1_CTRL_REG,
					 0x3F, val);
		अवरोध;
	हाल 1:
		ret = regmap_update_bits(smi->map,
					 RTL8366RB_LED_0_1_CTRL_REG,
					 0x3F << RTL8366RB_LED_1_OFFSET,
					 val << RTL8366RB_LED_1_OFFSET);
		अवरोध;
	हाल 2:
		ret = regmap_update_bits(smi->map,
					 RTL8366RB_LED_2_3_CTRL_REG,
					 0x3F, val);
		अवरोध;
	हाल 3:
		ret = regmap_update_bits(smi->map,
					 RTL8366RB_LED_2_3_CTRL_REG,
					 0x3F << RTL8366RB_LED_3_OFFSET,
					 val << RTL8366RB_LED_3_OFFSET);
		अवरोध;
	हाल 4:
		ret = regmap_update_bits(smi->map,
					 RTL8366RB_INTERRUPT_CONTROL_REG,
					 RTL8366RB_P4_RGMII_LED,
					 enable ? RTL8366RB_P4_RGMII_LED : 0);
		अवरोध;
	शेष:
		dev_err(smi->dev, "no LED for port %d\n", port);
		वापस;
	पूर्ण
	अगर (ret)
		dev_err(smi->dev, "error updating LED on port %d\n", port);
पूर्ण

अटल पूर्णांक
rtl8366rb_port_enable(काष्ठा dsa_चयन *ds, पूर्णांक port,
		      काष्ठा phy_device *phy)
अणु
	काष्ठा realtek_smi *smi = ds->priv;
	पूर्णांक ret;

	dev_dbg(smi->dev, "enable port %d\n", port);
	ret = regmap_update_bits(smi->map, RTL8366RB_PECR, BIT(port),
				 0);
	अगर (ret)
		वापस ret;

	rb8366rb_set_port_led(smi, port, true);
	वापस 0;
पूर्ण

अटल व्योम
rtl8366rb_port_disable(काष्ठा dsa_चयन *ds, पूर्णांक port)
अणु
	काष्ठा realtek_smi *smi = ds->priv;
	पूर्णांक ret;

	dev_dbg(smi->dev, "disable port %d\n", port);
	ret = regmap_update_bits(smi->map, RTL8366RB_PECR, BIT(port),
				 BIT(port));
	अगर (ret)
		वापस;

	rb8366rb_set_port_led(smi, port, false);
पूर्ण

अटल पूर्णांक rtl8366rb_change_mtu(काष्ठा dsa_चयन *ds, पूर्णांक port, पूर्णांक new_mtu)
अणु
	काष्ठा realtek_smi *smi = ds->priv;
	काष्ठा rtl8366rb *rb;
	अचिन्हित पूर्णांक max_mtu;
	u32 len;
	पूर्णांक i;

	/* Cache the per-port MTU setting */
	rb = smi->chip_data;
	rb->max_mtu[port] = new_mtu;

	/* Roof out the MTU क्रम the entire चयन to the greatest
	 * common denominator: the biggest set क्रम any one port will
	 * be the biggest MTU क्रम the चयन.
	 *
	 * The first setting, 1522 bytes, is max IP packet 1500 bytes,
	 * plus ethernet header, 1518 bytes, plus CPU tag, 4 bytes.
	 * This function should consider the parameter an SDU, so the
	 * MTU passed क्रम this setting is 1518 bytes. The same logic
	 * of subtracting the DSA tag of 4 bytes apply to the other
	 * settings.
	 */
	max_mtu = 1518;
	क्रम (i = 0; i < RTL8366RB_NUM_PORTS; i++) अणु
		अगर (rb->max_mtu[i] > max_mtu)
			max_mtu = rb->max_mtu[i];
	पूर्ण
	अगर (max_mtu <= 1518)
		len = RTL8366RB_SGCR_MAX_LENGTH_1522;
	अन्यथा अगर (max_mtu > 1518 && max_mtu <= 1532)
		len = RTL8366RB_SGCR_MAX_LENGTH_1536;
	अन्यथा अगर (max_mtu > 1532 && max_mtu <= 1548)
		len = RTL8366RB_SGCR_MAX_LENGTH_1552;
	अन्यथा
		len = RTL8366RB_SGCR_MAX_LENGTH_16000;

	वापस regmap_update_bits(smi->map, RTL8366RB_SGCR,
				  RTL8366RB_SGCR_MAX_LENGTH_MASK,
				  len);
पूर्ण

अटल पूर्णांक rtl8366rb_max_mtu(काष्ठा dsa_चयन *ds, पूर्णांक port)
अणु
	/* The max MTU is 16000 bytes, so we subtract the CPU tag
	 * and the max presented to the प्रणाली is 15996 bytes.
	 */
	वापस 15996;
पूर्ण

अटल पूर्णांक rtl8366rb_get_vlan_4k(काष्ठा realtek_smi *smi, u32 vid,
				 काष्ठा rtl8366_vlan_4k *vlan4k)
अणु
	u32 data[3];
	पूर्णांक ret;
	पूर्णांक i;

	स_रखो(vlan4k, '\0', माप(काष्ठा rtl8366_vlan_4k));

	अगर (vid >= RTL8366RB_NUM_VIDS)
		वापस -EINVAL;

	/* ग_लिखो VID */
	ret = regmap_ग_लिखो(smi->map, RTL8366RB_VLAN_TABLE_WRITE_BASE,
			   vid & RTL8366RB_VLAN_VID_MASK);
	अगर (ret)
		वापस ret;

	/* ग_लिखो table access control word */
	ret = regmap_ग_लिखो(smi->map, RTL8366RB_TABLE_ACCESS_CTRL_REG,
			   RTL8366RB_TABLE_VLAN_READ_CTRL);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < 3; i++) अणु
		ret = regmap_पढ़ो(smi->map,
				  RTL8366RB_VLAN_TABLE_READ_BASE + i,
				  &data[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	vlan4k->vid = vid;
	vlan4k->untag = (data[1] >> RTL8366RB_VLAN_UNTAG_SHIFT) &
			RTL8366RB_VLAN_UNTAG_MASK;
	vlan4k->member = data[1] & RTL8366RB_VLAN_MEMBER_MASK;
	vlan4k->fid = data[2] & RTL8366RB_VLAN_FID_MASK;

	वापस 0;
पूर्ण

अटल पूर्णांक rtl8366rb_set_vlan_4k(काष्ठा realtek_smi *smi,
				 स्थिर काष्ठा rtl8366_vlan_4k *vlan4k)
अणु
	u32 data[3];
	पूर्णांक ret;
	पूर्णांक i;

	अगर (vlan4k->vid >= RTL8366RB_NUM_VIDS ||
	    vlan4k->member > RTL8366RB_VLAN_MEMBER_MASK ||
	    vlan4k->untag > RTL8366RB_VLAN_UNTAG_MASK ||
	    vlan4k->fid > RTL8366RB_FIDMAX)
		वापस -EINVAL;

	data[0] = vlan4k->vid & RTL8366RB_VLAN_VID_MASK;
	data[1] = (vlan4k->member & RTL8366RB_VLAN_MEMBER_MASK) |
		  ((vlan4k->untag & RTL8366RB_VLAN_UNTAG_MASK) <<
			RTL8366RB_VLAN_UNTAG_SHIFT);
	data[2] = vlan4k->fid & RTL8366RB_VLAN_FID_MASK;

	क्रम (i = 0; i < 3; i++) अणु
		ret = regmap_ग_लिखो(smi->map,
				   RTL8366RB_VLAN_TABLE_WRITE_BASE + i,
				   data[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* ग_लिखो table access control word */
	ret = regmap_ग_लिखो(smi->map, RTL8366RB_TABLE_ACCESS_CTRL_REG,
			   RTL8366RB_TABLE_VLAN_WRITE_CTRL);

	वापस ret;
पूर्ण

अटल पूर्णांक rtl8366rb_get_vlan_mc(काष्ठा realtek_smi *smi, u32 index,
				 काष्ठा rtl8366_vlan_mc *vlanmc)
अणु
	u32 data[3];
	पूर्णांक ret;
	पूर्णांक i;

	स_रखो(vlanmc, '\0', माप(काष्ठा rtl8366_vlan_mc));

	अगर (index >= RTL8366RB_NUM_VLANS)
		वापस -EINVAL;

	क्रम (i = 0; i < 3; i++) अणु
		ret = regmap_पढ़ो(smi->map,
				  RTL8366RB_VLAN_MC_BASE(index) + i,
				  &data[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	vlanmc->vid = data[0] & RTL8366RB_VLAN_VID_MASK;
	vlanmc->priority = (data[0] >> RTL8366RB_VLAN_PRIORITY_SHIFT) &
		RTL8366RB_VLAN_PRIORITY_MASK;
	vlanmc->untag = (data[1] >> RTL8366RB_VLAN_UNTAG_SHIFT) &
		RTL8366RB_VLAN_UNTAG_MASK;
	vlanmc->member = data[1] & RTL8366RB_VLAN_MEMBER_MASK;
	vlanmc->fid = data[2] & RTL8366RB_VLAN_FID_MASK;

	वापस 0;
पूर्ण

अटल पूर्णांक rtl8366rb_set_vlan_mc(काष्ठा realtek_smi *smi, u32 index,
				 स्थिर काष्ठा rtl8366_vlan_mc *vlanmc)
अणु
	u32 data[3];
	पूर्णांक ret;
	पूर्णांक i;

	अगर (index >= RTL8366RB_NUM_VLANS ||
	    vlanmc->vid >= RTL8366RB_NUM_VIDS ||
	    vlanmc->priority > RTL8366RB_PRIORITYMAX ||
	    vlanmc->member > RTL8366RB_VLAN_MEMBER_MASK ||
	    vlanmc->untag > RTL8366RB_VLAN_UNTAG_MASK ||
	    vlanmc->fid > RTL8366RB_FIDMAX)
		वापस -EINVAL;

	data[0] = (vlanmc->vid & RTL8366RB_VLAN_VID_MASK) |
		  ((vlanmc->priority & RTL8366RB_VLAN_PRIORITY_MASK) <<
			RTL8366RB_VLAN_PRIORITY_SHIFT);
	data[1] = (vlanmc->member & RTL8366RB_VLAN_MEMBER_MASK) |
		  ((vlanmc->untag & RTL8366RB_VLAN_UNTAG_MASK) <<
			RTL8366RB_VLAN_UNTAG_SHIFT);
	data[2] = vlanmc->fid & RTL8366RB_VLAN_FID_MASK;

	क्रम (i = 0; i < 3; i++) अणु
		ret = regmap_ग_लिखो(smi->map,
				   RTL8366RB_VLAN_MC_BASE(index) + i,
				   data[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rtl8366rb_get_mc_index(काष्ठा realtek_smi *smi, पूर्णांक port, पूर्णांक *val)
अणु
	u32 data;
	पूर्णांक ret;

	अगर (port >= smi->num_ports)
		वापस -EINVAL;

	ret = regmap_पढ़ो(smi->map, RTL8366RB_PORT_VLAN_CTRL_REG(port),
			  &data);
	अगर (ret)
		वापस ret;

	*val = (data >> RTL8366RB_PORT_VLAN_CTRL_SHIFT(port)) &
		RTL8366RB_PORT_VLAN_CTRL_MASK;

	वापस 0;
पूर्ण

अटल पूर्णांक rtl8366rb_set_mc_index(काष्ठा realtek_smi *smi, पूर्णांक port, पूर्णांक index)
अणु
	अगर (port >= smi->num_ports || index >= RTL8366RB_NUM_VLANS)
		वापस -EINVAL;

	वापस regmap_update_bits(smi->map, RTL8366RB_PORT_VLAN_CTRL_REG(port),
				RTL8366RB_PORT_VLAN_CTRL_MASK <<
					RTL8366RB_PORT_VLAN_CTRL_SHIFT(port),
				(index & RTL8366RB_PORT_VLAN_CTRL_MASK) <<
					RTL8366RB_PORT_VLAN_CTRL_SHIFT(port));
पूर्ण

अटल bool rtl8366rb_is_vlan_valid(काष्ठा realtek_smi *smi, अचिन्हित पूर्णांक vlan)
अणु
	अचिन्हित पूर्णांक max = RTL8366RB_NUM_VLANS;

	अगर (smi->vlan4k_enabled)
		max = RTL8366RB_NUM_VIDS - 1;

	अगर (vlan == 0 || vlan > max)
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक rtl8366rb_enable_vlan(काष्ठा realtek_smi *smi, bool enable)
अणु
	dev_dbg(smi->dev, "%s VLAN\n", enable ? "enable" : "disable");
	वापस regmap_update_bits(smi->map,
				  RTL8366RB_SGCR, RTL8366RB_SGCR_EN_VLAN,
				  enable ? RTL8366RB_SGCR_EN_VLAN : 0);
पूर्ण

अटल पूर्णांक rtl8366rb_enable_vlan4k(काष्ठा realtek_smi *smi, bool enable)
अणु
	dev_dbg(smi->dev, "%s VLAN 4k\n", enable ? "enable" : "disable");
	वापस regmap_update_bits(smi->map, RTL8366RB_SGCR,
				  RTL8366RB_SGCR_EN_VLAN_4KTB,
				  enable ? RTL8366RB_SGCR_EN_VLAN_4KTB : 0);
पूर्ण

अटल पूर्णांक rtl8366rb_phy_पढ़ो(काष्ठा realtek_smi *smi, पूर्णांक phy, पूर्णांक regnum)
अणु
	u32 val;
	u32 reg;
	पूर्णांक ret;

	अगर (phy > RTL8366RB_PHY_NO_MAX)
		वापस -EINVAL;

	ret = regmap_ग_लिखो(smi->map, RTL8366RB_PHY_ACCESS_CTRL_REG,
			   RTL8366RB_PHY_CTRL_READ);
	अगर (ret)
		वापस ret;

	reg = 0x8000 | (1 << (phy + RTL8366RB_PHY_NO_OFFSET)) | regnum;

	ret = regmap_ग_लिखो(smi->map, reg, 0);
	अगर (ret) अणु
		dev_err(smi->dev,
			"failed to write PHY%d reg %04x @ %04x, ret %d\n",
			phy, regnum, reg, ret);
		वापस ret;
	पूर्ण

	ret = regmap_पढ़ो(smi->map, RTL8366RB_PHY_ACCESS_DATA_REG, &val);
	अगर (ret)
		वापस ret;

	dev_dbg(smi->dev, "read PHY%d register 0x%04x @ %08x, val <- %04x\n",
		phy, regnum, reg, val);

	वापस val;
पूर्ण

अटल पूर्णांक rtl8366rb_phy_ग_लिखो(काष्ठा realtek_smi *smi, पूर्णांक phy, पूर्णांक regnum,
			       u16 val)
अणु
	u32 reg;
	पूर्णांक ret;

	अगर (phy > RTL8366RB_PHY_NO_MAX)
		वापस -EINVAL;

	ret = regmap_ग_लिखो(smi->map, RTL8366RB_PHY_ACCESS_CTRL_REG,
			   RTL8366RB_PHY_CTRL_WRITE);
	अगर (ret)
		वापस ret;

	reg = 0x8000 | (1 << (phy + RTL8366RB_PHY_NO_OFFSET)) | regnum;

	dev_dbg(smi->dev, "write PHY%d register 0x%04x @ %04x, val -> %04x\n",
		phy, regnum, reg, val);

	ret = regmap_ग_लिखो(smi->map, reg, val);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक rtl8366rb_reset_chip(काष्ठा realtek_smi *smi)
अणु
	पूर्णांक समयout = 10;
	u32 val;
	पूर्णांक ret;

	realtek_smi_ग_लिखो_reg_noack(smi, RTL8366RB_RESET_CTRL_REG,
				    RTL8366RB_CHIP_CTRL_RESET_HW);
	करो अणु
		usleep_range(20000, 25000);
		ret = regmap_पढ़ो(smi->map, RTL8366RB_RESET_CTRL_REG, &val);
		अगर (ret)
			वापस ret;

		अगर (!(val & RTL8366RB_CHIP_CTRL_RESET_HW))
			अवरोध;
	पूर्ण जबतक (--समयout);

	अगर (!समयout) अणु
		dev_err(smi->dev, "timeout waiting for the switch to reset\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rtl8366rb_detect(काष्ठा realtek_smi *smi)
अणु
	काष्ठा device *dev = smi->dev;
	पूर्णांक ret;
	u32 val;

	/* Detect device */
	ret = regmap_पढ़ो(smi->map, 0x5c, &val);
	अगर (ret) अणु
		dev_err(dev, "can't get chip ID (%d)\n", ret);
		वापस ret;
	पूर्ण

	चयन (val) अणु
	हाल 0x6027:
		dev_info(dev, "found an RTL8366S switch\n");
		dev_err(dev, "this switch is not yet supported, submit patches!\n");
		वापस -ENODEV;
	हाल 0x5937:
		dev_info(dev, "found an RTL8366RB switch\n");
		smi->cpu_port = RTL8366RB_PORT_NUM_CPU;
		smi->num_ports = RTL8366RB_NUM_PORTS;
		smi->num_vlan_mc = RTL8366RB_NUM_VLANS;
		smi->mib_counters = rtl8366rb_mib_counters;
		smi->num_mib_counters = ARRAY_SIZE(rtl8366rb_mib_counters);
		अवरोध;
	शेष:
		dev_info(dev, "found an Unknown Realtek switch (id=0x%04x)\n",
			 val);
		अवरोध;
	पूर्ण

	ret = rtl8366rb_reset_chip(smi);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dsa_चयन_ops rtl8366rb_चयन_ops = अणु
	.get_tag_protocol = rtl8366_get_tag_protocol,
	.setup = rtl8366rb_setup,
	.phylink_mac_link_up = rtl8366rb_mac_link_up,
	.phylink_mac_link_करोwn = rtl8366rb_mac_link_करोwn,
	.get_strings = rtl8366_get_strings,
	.get_ethtool_stats = rtl8366_get_ethtool_stats,
	.get_sset_count = rtl8366_get_sset_count,
	.port_vlan_filtering = rtl8366_vlan_filtering,
	.port_vlan_add = rtl8366_vlan_add,
	.port_vlan_del = rtl8366_vlan_del,
	.port_enable = rtl8366rb_port_enable,
	.port_disable = rtl8366rb_port_disable,
	.port_change_mtu = rtl8366rb_change_mtu,
	.port_max_mtu = rtl8366rb_max_mtu,
पूर्ण;

अटल स्थिर काष्ठा realtek_smi_ops rtl8366rb_smi_ops = अणु
	.detect		= rtl8366rb_detect,
	.get_vlan_mc	= rtl8366rb_get_vlan_mc,
	.set_vlan_mc	= rtl8366rb_set_vlan_mc,
	.get_vlan_4k	= rtl8366rb_get_vlan_4k,
	.set_vlan_4k	= rtl8366rb_set_vlan_4k,
	.get_mc_index	= rtl8366rb_get_mc_index,
	.set_mc_index	= rtl8366rb_set_mc_index,
	.get_mib_counter = rtl8366rb_get_mib_counter,
	.is_vlan_valid	= rtl8366rb_is_vlan_valid,
	.enable_vlan	= rtl8366rb_enable_vlan,
	.enable_vlan4k	= rtl8366rb_enable_vlan4k,
	.phy_पढ़ो	= rtl8366rb_phy_पढ़ो,
	.phy_ग_लिखो	= rtl8366rb_phy_ग_लिखो,
पूर्ण;

स्थिर काष्ठा realtek_smi_variant rtl8366rb_variant = अणु
	.ds_ops = &rtl8366rb_चयन_ops,
	.ops = &rtl8366rb_smi_ops,
	.clk_delay = 10,
	.cmd_पढ़ो = 0xa9,
	.cmd_ग_लिखो = 0xa8,
	.chip_data_sz = माप(काष्ठा rtl8366rb),
पूर्ण;
EXPORT_SYMBOL_GPL(rtl8366rb_variant);
