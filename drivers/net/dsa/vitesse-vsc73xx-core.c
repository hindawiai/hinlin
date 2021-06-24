<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* DSA driver क्रम:
 * Vitesse VSC7385 SparX-G5 5+1-port Integrated Gigabit Ethernet Switch
 * Vitesse VSC7388 SparX-G8 8-port Integrated Gigabit Ethernet Switch
 * Vitesse VSC7395 SparX-G5e 5+1-port Integrated Gigabit Ethernet Switch
 * Vitesse VSC7398 SparX-G8e 8-port Integrated Gigabit Ethernet Switch
 *
 * These चयनes have a built-in 8051 CPU and can करोwnload and execute a
 * firmware in this CPU. They can also be configured to use an बाह्यal CPU
 * handling the चयन in a memory-mapped manner by connecting to that बाह्यal
 * CPU's memory bus.
 *
 * Copyright (C) 2018 Linus Wallej <linus.walleij@linaro.org>
 * Includes portions of code from the firmware uploader by:
 * Copyright (C) 2009 Gabor Juhos <juhosg@खोलोwrt.org>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/bitops.h>
#समावेश <linux/अगर_bridge.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/अक्रमom.h>
#समावेश <net/dsa.h>

#समावेश "vitesse-vsc73xx.h"

#घोषणा VSC73XX_BLOCK_MAC	0x1 /* Subblocks 0-4, 6 (CPU port) */
#घोषणा VSC73XX_BLOCK_ANALYZER	0x2 /* Only subblock 0 */
#घोषणा VSC73XX_BLOCK_MII	0x3 /* Subblocks 0 and 1 */
#घोषणा VSC73XX_BLOCK_MEMINIT	0x3 /* Only subblock 2 */
#घोषणा VSC73XX_BLOCK_CAPTURE	0x4 /* Only subblock 2 */
#घोषणा VSC73XX_BLOCK_ARBITER	0x5 /* Only subblock 0 */
#घोषणा VSC73XX_BLOCK_SYSTEM	0x7 /* Only subblock 0 */

#घोषणा CPU_PORT	6 /* CPU port */

/* MAC Block रेजिस्टरs */
#घोषणा VSC73XX_MAC_CFG		0x00
#घोषणा VSC73XX_MACHDXGAP	0x02
#घोषणा VSC73XX_FCCONF		0x04
#घोषणा VSC73XX_FCMACHI		0x08
#घोषणा VSC73XX_FCMACLO		0x0c
#घोषणा VSC73XX_MAXLEN		0x10
#घोषणा VSC73XX_ADVPORTM	0x19
#घोषणा VSC73XX_TXUPDCFG	0x24
#घोषणा VSC73XX_TXQ_SELECT_CFG	0x28
#घोषणा VSC73XX_RXOCT		0x50
#घोषणा VSC73XX_TXOCT		0x51
#घोषणा VSC73XX_C_RX0		0x52
#घोषणा VSC73XX_C_RX1		0x53
#घोषणा VSC73XX_C_RX2		0x54
#घोषणा VSC73XX_C_TX0		0x55
#घोषणा VSC73XX_C_TX1		0x56
#घोषणा VSC73XX_C_TX2		0x57
#घोषणा VSC73XX_C_CFG		0x58
#घोषणा VSC73XX_CAT_DROP	0x6e
#घोषणा VSC73XX_CAT_PR_MISC_L2	0x6f
#घोषणा VSC73XX_CAT_PR_USR_PRIO	0x75
#घोषणा VSC73XX_Q_MISC_CONF	0xdf

/* MAC_CFG रेजिस्टर bits */
#घोषणा VSC73XX_MAC_CFG_WEXC_DIS	BIT(31)
#घोषणा VSC73XX_MAC_CFG_PORT_RST	BIT(29)
#घोषणा VSC73XX_MAC_CFG_TX_EN		BIT(28)
#घोषणा VSC73XX_MAC_CFG_SEED_LOAD	BIT(27)
#घोषणा VSC73XX_MAC_CFG_SEED_MASK	GENMASK(26, 19)
#घोषणा VSC73XX_MAC_CFG_SEED_OFFSET	19
#घोषणा VSC73XX_MAC_CFG_FDX		BIT(18)
#घोषणा VSC73XX_MAC_CFG_GIGA_MODE	BIT(17)
#घोषणा VSC73XX_MAC_CFG_RX_EN		BIT(16)
#घोषणा VSC73XX_MAC_CFG_VLAN_DBLAWR	BIT(15)
#घोषणा VSC73XX_MAC_CFG_VLAN_AWR	BIT(14)
#घोषणा VSC73XX_MAC_CFG_100_BASE_T	BIT(13) /* Not in manual */
#घोषणा VSC73XX_MAC_CFG_TX_IPG_MASK	GENMASK(10, 6)
#घोषणा VSC73XX_MAC_CFG_TX_IPG_OFFSET	6
#घोषणा VSC73XX_MAC_CFG_TX_IPG_1000M	(6 << VSC73XX_MAC_CFG_TX_IPG_OFFSET)
#घोषणा VSC73XX_MAC_CFG_TX_IPG_100_10M	(17 << VSC73XX_MAC_CFG_TX_IPG_OFFSET)
#घोषणा VSC73XX_MAC_CFG_MAC_RX_RST	BIT(5)
#घोषणा VSC73XX_MAC_CFG_MAC_TX_RST	BIT(4)
#घोषणा VSC73XX_MAC_CFG_CLK_SEL_MASK	GENMASK(2, 0)
#घोषणा VSC73XX_MAC_CFG_CLK_SEL_OFFSET	0
#घोषणा VSC73XX_MAC_CFG_CLK_SEL_1000M	1
#घोषणा VSC73XX_MAC_CFG_CLK_SEL_100M	2
#घोषणा VSC73XX_MAC_CFG_CLK_SEL_10M	3
#घोषणा VSC73XX_MAC_CFG_CLK_SEL_EXT	4

#घोषणा VSC73XX_MAC_CFG_1000M_F_PHY	(VSC73XX_MAC_CFG_FDX | \
					 VSC73XX_MAC_CFG_GIGA_MODE | \
					 VSC73XX_MAC_CFG_TX_IPG_1000M | \
					 VSC73XX_MAC_CFG_CLK_SEL_EXT)
#घोषणा VSC73XX_MAC_CFG_100_10M_F_PHY	(VSC73XX_MAC_CFG_FDX | \
					 VSC73XX_MAC_CFG_TX_IPG_100_10M | \
					 VSC73XX_MAC_CFG_CLK_SEL_EXT)
#घोषणा VSC73XX_MAC_CFG_100_10M_H_PHY	(VSC73XX_MAC_CFG_TX_IPG_100_10M | \
					 VSC73XX_MAC_CFG_CLK_SEL_EXT)
#घोषणा VSC73XX_MAC_CFG_1000M_F_RGMII	(VSC73XX_MAC_CFG_FDX | \
					 VSC73XX_MAC_CFG_GIGA_MODE | \
					 VSC73XX_MAC_CFG_TX_IPG_1000M | \
					 VSC73XX_MAC_CFG_CLK_SEL_1000M)
#घोषणा VSC73XX_MAC_CFG_RESET		(VSC73XX_MAC_CFG_PORT_RST | \
					 VSC73XX_MAC_CFG_MAC_RX_RST | \
					 VSC73XX_MAC_CFG_MAC_TX_RST)

/* Flow control रेजिस्टर bits */
#घोषणा VSC73XX_FCCONF_ZERO_PAUSE_EN	BIT(17)
#घोषणा VSC73XX_FCCONF_FLOW_CTRL_OBEY	BIT(16)
#घोषणा VSC73XX_FCCONF_PAUSE_VAL_MASK	GENMASK(15, 0)

/* ADVPORTM advanced port setup रेजिस्टर bits */
#घोषणा VSC73XX_ADVPORTM_IFG_PPM	BIT(7)
#घोषणा VSC73XX_ADVPORTM_EXC_COL_CONT	BIT(6)
#घोषणा VSC73XX_ADVPORTM_EXT_PORT	BIT(5)
#घोषणा VSC73XX_ADVPORTM_INV_GTX	BIT(4)
#घोषणा VSC73XX_ADVPORTM_ENA_GTX	BIT(3)
#घोषणा VSC73XX_ADVPORTM_DDR_MODE	BIT(2)
#घोषणा VSC73XX_ADVPORTM_IO_LOOPBACK	BIT(1)
#घोषणा VSC73XX_ADVPORTM_HOST_LOOPBACK	BIT(0)

/* CAT_DROP categorizer frame dropping रेजिस्टर bits */
#घोषणा VSC73XX_CAT_DROP_DROP_MC_SMAC_ENA	BIT(6)
#घोषणा VSC73XX_CAT_DROP_FWD_CTRL_ENA		BIT(4)
#घोषणा VSC73XX_CAT_DROP_FWD_PAUSE_ENA		BIT(3)
#घोषणा VSC73XX_CAT_DROP_UNTAGGED_ENA		BIT(2)
#घोषणा VSC73XX_CAT_DROP_TAGGED_ENA		BIT(1)
#घोषणा VSC73XX_CAT_DROP_शून्य_MAC_ENA		BIT(0)

#घोषणा VSC73XX_Q_MISC_CONF_EXTENT_MEM		BIT(31)
#घोषणा VSC73XX_Q_MISC_CONF_EARLY_TX_MASK	GENMASK(4, 1)
#घोषणा VSC73XX_Q_MISC_CONF_EARLY_TX_512	(1 << 1)
#घोषणा VSC73XX_Q_MISC_CONF_MAC_PAUSE_MODE	BIT(0)

/* Frame analyzer block 2 रेजिस्टरs */
#घोषणा VSC73XX_STORMLIMIT	0x02
#घोषणा VSC73XX_ADVLEARN	0x03
#घोषणा VSC73XX_IFLODMSK	0x04
#घोषणा VSC73XX_VLANMASK	0x05
#घोषणा VSC73XX_MACHDATA	0x06
#घोषणा VSC73XX_MACLDATA	0x07
#घोषणा VSC73XX_ANMOVED		0x08
#घोषणा VSC73XX_ANAGEFIL	0x09
#घोषणा VSC73XX_ANEVENTS	0x0a
#घोषणा VSC73XX_ANCNTMASK	0x0b
#घोषणा VSC73XX_ANCNTVAL	0x0c
#घोषणा VSC73XX_LEARNMASK	0x0d
#घोषणा VSC73XX_UFLODMASK	0x0e
#घोषणा VSC73XX_MFLODMASK	0x0f
#घोषणा VSC73XX_RECVMASK	0x10
#घोषणा VSC73XX_AGGRCTRL	0x20
#घोषणा VSC73XX_AGGRMSKS	0x30 /* Until 0x3f */
#घोषणा VSC73XX_DSTMASKS	0x40 /* Until 0x7f */
#घोषणा VSC73XX_SRCMASKS	0x80 /* Until 0x87 */
#घोषणा VSC73XX_CAPENAB		0xa0
#घोषणा VSC73XX_MACACCESS	0xb0
#घोषणा VSC73XX_IPMCACCESS	0xb1
#घोषणा VSC73XX_MACTINDX	0xc0
#घोषणा VSC73XX_VLANACCESS	0xd0
#घोषणा VSC73XX_VLANTIDX	0xe0
#घोषणा VSC73XX_AGENCTRL	0xf0
#घोषणा VSC73XX_CAPRST		0xff

#घोषणा VSC73XX_MACACCESS_CPU_COPY		BIT(14)
#घोषणा VSC73XX_MACACCESS_FWD_KILL		BIT(13)
#घोषणा VSC73XX_MACACCESS_IGNORE_VLAN		BIT(12)
#घोषणा VSC73XX_MACACCESS_AGED_FLAG		BIT(11)
#घोषणा VSC73XX_MACACCESS_VALID			BIT(10)
#घोषणा VSC73XX_MACACCESS_LOCKED		BIT(9)
#घोषणा VSC73XX_MACACCESS_DEST_IDX_MASK		GENMASK(8, 3)
#घोषणा VSC73XX_MACACCESS_CMD_MASK		GENMASK(2, 0)
#घोषणा VSC73XX_MACACCESS_CMD_IDLE		0
#घोषणा VSC73XX_MACACCESS_CMD_LEARN		1
#घोषणा VSC73XX_MACACCESS_CMD_FORGET		2
#घोषणा VSC73XX_MACACCESS_CMD_AGE_TABLE		3
#घोषणा VSC73XX_MACACCESS_CMD_FLUSH_TABLE	4
#घोषणा VSC73XX_MACACCESS_CMD_CLEAR_TABLE	5
#घोषणा VSC73XX_MACACCESS_CMD_READ_ENTRY	6
#घोषणा VSC73XX_MACACCESS_CMD_WRITE_ENTRY	7

#घोषणा VSC73XX_VLANACCESS_LEARN_DISABLED	BIT(30)
#घोषणा VSC73XX_VLANACCESS_VLAN_MIRROR		BIT(29)
#घोषणा VSC73XX_VLANACCESS_VLAN_SRC_CHECK	BIT(28)
#घोषणा VSC73XX_VLANACCESS_VLAN_PORT_MASK	GENMASK(9, 2)
#घोषणा VSC73XX_VLANACCESS_VLAN_TBL_CMD_MASK	GENMASK(2, 0)
#घोषणा VSC73XX_VLANACCESS_VLAN_TBL_CMD_IDLE	0
#घोषणा VSC73XX_VLANACCESS_VLAN_TBL_CMD_READ_ENTRY	1
#घोषणा VSC73XX_VLANACCESS_VLAN_TBL_CMD_WRITE_ENTRY	2
#घोषणा VSC73XX_VLANACCESS_VLAN_TBL_CMD_CLEAR_TABLE	3

/* MII block 3 रेजिस्टरs */
#घोषणा VSC73XX_MII_STAT	0x0
#घोषणा VSC73XX_MII_CMD		0x1
#घोषणा VSC73XX_MII_DATA	0x2

/* Arbiter block 5 रेजिस्टरs */
#घोषणा VSC73XX_ARBEMPTY		0x0c
#घोषणा VSC73XX_ARBDISC			0x0e
#घोषणा VSC73XX_SBACKWDROP		0x12
#घोषणा VSC73XX_DBACKWDROP		0x13
#घोषणा VSC73XX_ARBBURSTPROB		0x15

/* System block 7 रेजिस्टरs */
#घोषणा VSC73XX_ICPU_SIPAD		0x01
#घोषणा VSC73XX_GMIIDELAY		0x05
#घोषणा VSC73XX_ICPU_CTRL		0x10
#घोषणा VSC73XX_ICPU_ADDR		0x11
#घोषणा VSC73XX_ICPU_SRAM		0x12
#घोषणा VSC73XX_HWSEM			0x13
#घोषणा VSC73XX_GLORESET		0x14
#घोषणा VSC73XX_ICPU_MBOX_VAL		0x15
#घोषणा VSC73XX_ICPU_MBOX_SET		0x16
#घोषणा VSC73XX_ICPU_MBOX_CLR		0x17
#घोषणा VSC73XX_CHIPID			0x18
#घोषणा VSC73XX_GPIO			0x34

#घोषणा VSC73XX_GMIIDELAY_GMII0_GTXDELAY_NONE	0
#घोषणा VSC73XX_GMIIDELAY_GMII0_GTXDELAY_1_4_NS	1
#घोषणा VSC73XX_GMIIDELAY_GMII0_GTXDELAY_1_7_NS	2
#घोषणा VSC73XX_GMIIDELAY_GMII0_GTXDELAY_2_0_NS	3

#घोषणा VSC73XX_GMIIDELAY_GMII0_RXDELAY_NONE	(0 << 4)
#घोषणा VSC73XX_GMIIDELAY_GMII0_RXDELAY_1_4_NS	(1 << 4)
#घोषणा VSC73XX_GMIIDELAY_GMII0_RXDELAY_1_7_NS	(2 << 4)
#घोषणा VSC73XX_GMIIDELAY_GMII0_RXDELAY_2_0_NS	(3 << 4)

#घोषणा VSC73XX_ICPU_CTRL_WATCHDOG_RST	BIT(31)
#घोषणा VSC73XX_ICPU_CTRL_CLK_DIV_MASK	GENMASK(12, 8)
#घोषणा VSC73XX_ICPU_CTRL_SRST_HOLD	BIT(7)
#घोषणा VSC73XX_ICPU_CTRL_ICPU_PI_EN	BIT(6)
#घोषणा VSC73XX_ICPU_CTRL_BOOT_EN	BIT(3)
#घोषणा VSC73XX_ICPU_CTRL_EXT_ACC_EN	BIT(2)
#घोषणा VSC73XX_ICPU_CTRL_CLK_EN	BIT(1)
#घोषणा VSC73XX_ICPU_CTRL_SRST		BIT(0)

#घोषणा VSC73XX_CHIPID_ID_SHIFT		12
#घोषणा VSC73XX_CHIPID_ID_MASK		0xffff
#घोषणा VSC73XX_CHIPID_REV_SHIFT	28
#घोषणा VSC73XX_CHIPID_REV_MASK		0xf
#घोषणा VSC73XX_CHIPID_ID_7385		0x7385
#घोषणा VSC73XX_CHIPID_ID_7388		0x7388
#घोषणा VSC73XX_CHIPID_ID_7395		0x7395
#घोषणा VSC73XX_CHIPID_ID_7398		0x7398

#घोषणा VSC73XX_GLORESET_STROBE		BIT(4)
#घोषणा VSC73XX_GLORESET_ICPU_LOCK	BIT(3)
#घोषणा VSC73XX_GLORESET_MEM_LOCK	BIT(2)
#घोषणा VSC73XX_GLORESET_PHY_RESET	BIT(1)
#घोषणा VSC73XX_GLORESET_MASTER_RESET	BIT(0)

#घोषणा VSC7385_CLOCK_DELAY		((3 << 4) | 3)
#घोषणा VSC7385_CLOCK_DELAY_MASK	((3 << 4) | 3)

#घोषणा VSC73XX_ICPU_CTRL_STOP	(VSC73XX_ICPU_CTRL_SRST_HOLD | \
				 VSC73XX_ICPU_CTRL_BOOT_EN | \
				 VSC73XX_ICPU_CTRL_EXT_ACC_EN)

#घोषणा VSC73XX_ICPU_CTRL_START	(VSC73XX_ICPU_CTRL_CLK_DIV | \
				 VSC73XX_ICPU_CTRL_BOOT_EN | \
				 VSC73XX_ICPU_CTRL_CLK_EN | \
				 VSC73XX_ICPU_CTRL_SRST)

#घोषणा IS_7385(a) ((a)->chipid == VSC73XX_CHIPID_ID_7385)
#घोषणा IS_7388(a) ((a)->chipid == VSC73XX_CHIPID_ID_7388)
#घोषणा IS_7395(a) ((a)->chipid == VSC73XX_CHIPID_ID_7395)
#घोषणा IS_7398(a) ((a)->chipid == VSC73XX_CHIPID_ID_7398)
#घोषणा IS_739X(a) (IS_7395(a) || IS_7398(a))

काष्ठा vsc73xx_counter अणु
	u8 counter;
	स्थिर अक्षर *name;
पूर्ण;

/* Counters are named according to the MIB standards where applicable.
 * Some counters are custom, non-standard. The standard counters are
 * named in accordance with RFC2819, RFC2021 and IEEE Std 802.3-2002 Annex
 * 30A Counters.
 */
अटल स्थिर काष्ठा vsc73xx_counter vsc73xx_rx_counters[] = अणु
	अणु 0, "RxEtherStatsPkts" पूर्ण,
	अणु 1, "RxBroadcast+MulticastPkts" पूर्ण, /* non-standard counter */
	अणु 2, "RxTotalErrorPackets" पूर्ण, /* non-standard counter */
	अणु 3, "RxEtherStatsBroadcastPkts" पूर्ण,
	अणु 4, "RxEtherStatsMulticastPkts" पूर्ण,
	अणु 5, "RxEtherStatsPkts64Octets" पूर्ण,
	अणु 6, "RxEtherStatsPkts65to127Octets" पूर्ण,
	अणु 7, "RxEtherStatsPkts128to255Octets" पूर्ण,
	अणु 8, "RxEtherStatsPkts256to511Octets" पूर्ण,
	अणु 9, "RxEtherStatsPkts512to1023Octets" पूर्ण,
	अणु 10, "RxEtherStatsPkts1024to1518Octets" पूर्ण,
	अणु 11, "RxJumboFrames" पूर्ण, /* non-standard counter */
	अणु 12, "RxaPauseMACControlFramesTransmitted" पूर्ण,
	अणु 13, "RxFIFODrops" पूर्ण, /* non-standard counter */
	अणु 14, "RxBackwardDrops" पूर्ण, /* non-standard counter */
	अणु 15, "RxClassifierDrops" पूर्ण, /* non-standard counter */
	अणु 16, "RxEtherStatsCRCAlignErrors" पूर्ण,
	अणु 17, "RxEtherStatsUndersizePkts" पूर्ण,
	अणु 18, "RxEtherStatsOversizePkts" पूर्ण,
	अणु 19, "RxEtherStatsFragments" पूर्ण,
	अणु 20, "RxEtherStatsJabbers" पूर्ण,
	अणु 21, "RxaMACControlFramesReceived" पूर्ण,
	/* 22-24 are undefined */
	अणु 25, "RxaFramesReceivedOK" पूर्ण,
	अणु 26, "RxQoSClass0" पूर्ण, /* non-standard counter */
	अणु 27, "RxQoSClass1" पूर्ण, /* non-standard counter */
	अणु 28, "RxQoSClass2" पूर्ण, /* non-standard counter */
	अणु 29, "RxQoSClass3" पूर्ण, /* non-standard counter */
पूर्ण;

अटल स्थिर काष्ठा vsc73xx_counter vsc73xx_tx_counters[] = अणु
	अणु 0, "TxEtherStatsPkts" पूर्ण,
	अणु 1, "TxBroadcast+MulticastPkts" पूर्ण, /* non-standard counter */
	अणु 2, "TxTotalErrorPackets" पूर्ण, /* non-standard counter */
	अणु 3, "TxEtherStatsBroadcastPkts" पूर्ण,
	अणु 4, "TxEtherStatsMulticastPkts" पूर्ण,
	अणु 5, "TxEtherStatsPkts64Octets" पूर्ण,
	अणु 6, "TxEtherStatsPkts65to127Octets" पूर्ण,
	अणु 7, "TxEtherStatsPkts128to255Octets" पूर्ण,
	अणु 8, "TxEtherStatsPkts256to511Octets" पूर्ण,
	अणु 9, "TxEtherStatsPkts512to1023Octets" पूर्ण,
	अणु 10, "TxEtherStatsPkts1024to1518Octets" पूर्ण,
	अणु 11, "TxJumboFrames" पूर्ण, /* non-standard counter */
	अणु 12, "TxaPauseMACControlFramesTransmitted" पूर्ण,
	अणु 13, "TxFIFODrops" पूर्ण, /* non-standard counter */
	अणु 14, "TxDrops" पूर्ण, /* non-standard counter */
	अणु 15, "TxEtherStatsCollisions" पूर्ण,
	अणु 16, "TxEtherStatsCRCAlignErrors" पूर्ण,
	अणु 17, "TxEtherStatsUndersizePkts" पूर्ण,
	अणु 18, "TxEtherStatsOversizePkts" पूर्ण,
	अणु 19, "TxEtherStatsFragments" पूर्ण,
	अणु 20, "TxEtherStatsJabbers" पूर्ण,
	/* 21-24 are undefined */
	अणु 25, "TxaFramesReceivedOK" पूर्ण,
	अणु 26, "TxQoSClass0" पूर्ण, /* non-standard counter */
	अणु 27, "TxQoSClass1" पूर्ण, /* non-standard counter */
	अणु 28, "TxQoSClass2" पूर्ण, /* non-standard counter */
	अणु 29, "TxQoSClass3" पूर्ण, /* non-standard counter */
पूर्ण;

पूर्णांक vsc73xx_is_addr_valid(u8 block, u8 subblock)
अणु
	चयन (block) अणु
	हाल VSC73XX_BLOCK_MAC:
		चयन (subblock) अणु
		हाल 0 ... 4:
		हाल 6:
			वापस 1;
		पूर्ण
		अवरोध;

	हाल VSC73XX_BLOCK_ANALYZER:
	हाल VSC73XX_BLOCK_SYSTEM:
		चयन (subblock) अणु
		हाल 0:
			वापस 1;
		पूर्ण
		अवरोध;

	हाल VSC73XX_BLOCK_MII:
	हाल VSC73XX_BLOCK_CAPTURE:
	हाल VSC73XX_BLOCK_ARBITER:
		चयन (subblock) अणु
		हाल 0 ... 1:
			वापस 1;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(vsc73xx_is_addr_valid);

अटल पूर्णांक vsc73xx_पढ़ो(काष्ठा vsc73xx *vsc, u8 block, u8 subblock, u8 reg,
			u32 *val)
अणु
	वापस vsc->ops->पढ़ो(vsc, block, subblock, reg, val);
पूर्ण

अटल पूर्णांक vsc73xx_ग_लिखो(काष्ठा vsc73xx *vsc, u8 block, u8 subblock, u8 reg,
			 u32 val)
अणु
	वापस vsc->ops->ग_लिखो(vsc, block, subblock, reg, val);
पूर्ण

अटल पूर्णांक vsc73xx_update_bits(काष्ठा vsc73xx *vsc, u8 block, u8 subblock,
			       u8 reg, u32 mask, u32 val)
अणु
	u32 पंचांगp, orig;
	पूर्णांक ret;

	/* Same पढ़ो-modअगरy-ग_लिखो algorithm as e.g. regmap */
	ret = vsc73xx_पढ़ो(vsc, block, subblock, reg, &orig);
	अगर (ret)
		वापस ret;
	पंचांगp = orig & ~mask;
	पंचांगp |= val & mask;
	वापस vsc73xx_ग_लिखो(vsc, block, subblock, reg, पंचांगp);
पूर्ण

अटल पूर्णांक vsc73xx_detect(काष्ठा vsc73xx *vsc)
अणु
	bool icpu_si_boot_en;
	bool icpu_pi_en;
	u32 val;
	u32 rev;
	पूर्णांक ret;
	u32 id;

	ret = vsc73xx_पढ़ो(vsc, VSC73XX_BLOCK_SYSTEM, 0,
			   VSC73XX_ICPU_MBOX_VAL, &val);
	अगर (ret) अणु
		dev_err(vsc->dev, "unable to read mailbox (%d)\n", ret);
		वापस ret;
	पूर्ण

	अगर (val == 0xffffffff) अणु
		dev_info(vsc->dev, "chip seems dead.\n");
		वापस -EAGAIN;
	पूर्ण

	ret = vsc73xx_पढ़ो(vsc, VSC73XX_BLOCK_SYSTEM, 0,
			   VSC73XX_CHIPID, &val);
	अगर (ret) अणु
		dev_err(vsc->dev, "unable to read chip id (%d)\n", ret);
		वापस ret;
	पूर्ण

	id = (val >> VSC73XX_CHIPID_ID_SHIFT) &
		VSC73XX_CHIPID_ID_MASK;
	चयन (id) अणु
	हाल VSC73XX_CHIPID_ID_7385:
	हाल VSC73XX_CHIPID_ID_7388:
	हाल VSC73XX_CHIPID_ID_7395:
	हाल VSC73XX_CHIPID_ID_7398:
		अवरोध;
	शेष:
		dev_err(vsc->dev, "unsupported chip, id=%04x\n", id);
		वापस -ENODEV;
	पूर्ण

	vsc->chipid = id;
	rev = (val >> VSC73XX_CHIPID_REV_SHIFT) &
		VSC73XX_CHIPID_REV_MASK;
	dev_info(vsc->dev, "VSC%04X (rev: %d) switch found\n", id, rev);

	ret = vsc73xx_पढ़ो(vsc, VSC73XX_BLOCK_SYSTEM, 0,
			   VSC73XX_ICPU_CTRL, &val);
	अगर (ret) अणु
		dev_err(vsc->dev, "unable to read iCPU control\n");
		वापस ret;
	पूर्ण

	/* The iCPU can always be used but can boot in dअगरferent ways.
	 * If it is initially disabled and has no बाह्यal memory,
	 * we are in control and can करो whatever we like, अन्यथा we
	 * are probably in trouble (we need some way to communicate
	 * with the running firmware) so we bail out क्रम now.
	 */
	icpu_pi_en = !!(val & VSC73XX_ICPU_CTRL_ICPU_PI_EN);
	icpu_si_boot_en = !!(val & VSC73XX_ICPU_CTRL_BOOT_EN);
	अगर (icpu_si_boot_en && icpu_pi_en) अणु
		dev_err(vsc->dev,
			"iCPU enabled boots from SI, has external memory\n");
		dev_err(vsc->dev, "no idea how to deal with this\n");
		वापस -ENODEV;
	पूर्ण
	अगर (icpu_si_boot_en && !icpu_pi_en) अणु
		dev_err(vsc->dev,
			"iCPU enabled boots from PI/SI, no external memory\n");
		वापस -EAGAIN;
	पूर्ण
	अगर (!icpu_si_boot_en && icpu_pi_en) अणु
		dev_err(vsc->dev,
			"iCPU enabled, boots from PI external memory\n");
		dev_err(vsc->dev, "no idea how to deal with this\n");
		वापस -ENODEV;
	पूर्ण
	/* !icpu_si_boot_en && !cpu_pi_en */
	dev_info(vsc->dev, "iCPU disabled, no external memory\n");

	वापस 0;
पूर्ण

अटल पूर्णांक vsc73xx_phy_पढ़ो(काष्ठा dsa_चयन *ds, पूर्णांक phy, पूर्णांक regnum)
अणु
	काष्ठा vsc73xx *vsc = ds->priv;
	u32 cmd;
	u32 val;
	पूर्णांक ret;

	/* Setting bit 26 means "read" */
	cmd = BIT(26) | (phy << 21) | (regnum << 16);
	ret = vsc73xx_ग_लिखो(vsc, VSC73XX_BLOCK_MII, 0, 1, cmd);
	अगर (ret)
		वापस ret;
	msleep(2);
	ret = vsc73xx_पढ़ो(vsc, VSC73XX_BLOCK_MII, 0, 2, &val);
	अगर (ret)
		वापस ret;
	अगर (val & BIT(16)) अणु
		dev_err(vsc->dev, "reading reg %02x from phy%d failed\n",
			regnum, phy);
		वापस -EIO;
	पूर्ण
	val &= 0xFFFFU;

	dev_dbg(vsc->dev, "read reg %02x from phy%d = %04x\n",
		regnum, phy, val);

	वापस val;
पूर्ण

अटल पूर्णांक vsc73xx_phy_ग_लिखो(काष्ठा dsa_चयन *ds, पूर्णांक phy, पूर्णांक regnum,
			     u16 val)
अणु
	काष्ठा vsc73xx *vsc = ds->priv;
	u32 cmd;
	पूर्णांक ret;

	/* It was found through tedious experiments that this router
	 * chip really hates to have it's PHYs reset. They
	 * never recover अगर that happens: स्वतःnegotiation stops
	 * working after a reset. Just filter out this command.
	 * (Resetting the whole chip is OK.)
	 */
	अगर (regnum == 0 && (val & BIT(15))) अणु
		dev_info(vsc->dev, "reset PHY - disallowed\n");
		वापस 0;
	पूर्ण

	cmd = (phy << 21) | (regnum << 16);
	ret = vsc73xx_ग_लिखो(vsc, VSC73XX_BLOCK_MII, 0, 1, cmd);
	अगर (ret)
		वापस ret;

	dev_dbg(vsc->dev, "write %04x to reg %02x in phy%d\n",
		val, regnum, phy);
	वापस 0;
पूर्ण

अटल क्रमागत dsa_tag_protocol vsc73xx_get_tag_protocol(काष्ठा dsa_चयन *ds,
						      पूर्णांक port,
						      क्रमागत dsa_tag_protocol mp)
अणु
	/* The चयन पूर्णांकernally uses a 8 byte header with length,
	 * source port, tag, LPA and priority. This is supposedly
	 * only accessible when operating the चयन using the पूर्णांकernal
	 * CPU or with an बाह्यal CPU mapping the device in, but not
	 * when operating the चयन over SPI and putting frames in/out
	 * on port 6 (the CPU port). So far we must assume that we
	 * cannot access the tag. (See "Internal frame header" section
	 * 3.9.1 in the manual.)
	 */
	वापस DSA_TAG_PROTO_NONE;
पूर्ण

अटल पूर्णांक vsc73xx_setup(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा vsc73xx *vsc = ds->priv;
	पूर्णांक i;

	dev_info(vsc->dev, "set up the switch\n");

	/* Issue RESET */
	vsc73xx_ग_लिखो(vsc, VSC73XX_BLOCK_SYSTEM, 0, VSC73XX_GLORESET,
		      VSC73XX_GLORESET_MASTER_RESET);
	usleep_range(125, 200);

	/* Initialize memory, initialize RAM bank 0..15 except 6 and 7
	 * This sequence appears in the
	 * VSC7385 SparX-G5 datasheet section 6.6.1
	 * VSC7395 SparX-G5e datasheet section 6.6.1
	 * "initialization sequence".
	 * No explanation is given to the 0x1010400 magic number.
	 */
	क्रम (i = 0; i <= 15; i++) अणु
		अगर (i != 6 && i != 7) अणु
			vsc73xx_ग_लिखो(vsc, VSC73XX_BLOCK_MEMINIT,
				      2,
				      0, 0x1010400 + i);
			mdelay(1);
		पूर्ण
	पूर्ण
	mdelay(30);

	/* Clear MAC table */
	vsc73xx_ग_लिखो(vsc, VSC73XX_BLOCK_ANALYZER, 0,
		      VSC73XX_MACACCESS,
		      VSC73XX_MACACCESS_CMD_CLEAR_TABLE);

	/* Clear VLAN table */
	vsc73xx_ग_लिखो(vsc, VSC73XX_BLOCK_ANALYZER, 0,
		      VSC73XX_VLANACCESS,
		      VSC73XX_VLANACCESS_VLAN_TBL_CMD_CLEAR_TABLE);

	msleep(40);

	/* Use 20KiB buffers on all ports on VSC7395
	 * The VSC7385 has 16KiB buffers and that is the
	 * शेष अगर we करोn't set this up explicitly.
	 * Port "31" is "all ports".
	 */
	अगर (IS_739X(vsc))
		vsc73xx_ग_लिखो(vsc, VSC73XX_BLOCK_MAC, 0x1f,
			      VSC73XX_Q_MISC_CONF,
			      VSC73XX_Q_MISC_CONF_EXTENT_MEM);

	/* Put all ports पूर्णांकo reset until enabled */
	क्रम (i = 0; i < 7; i++) अणु
		अगर (i == 5)
			जारी;
		vsc73xx_ग_लिखो(vsc, VSC73XX_BLOCK_MAC, 4,
			      VSC73XX_MAC_CFG, VSC73XX_MAC_CFG_RESET);
	पूर्ण

	/* MII delay, set both GTX and RX delay to 2 ns */
	vsc73xx_ग_लिखो(vsc, VSC73XX_BLOCK_SYSTEM, 0, VSC73XX_GMIIDELAY,
		      VSC73XX_GMIIDELAY_GMII0_GTXDELAY_2_0_NS |
		      VSC73XX_GMIIDELAY_GMII0_RXDELAY_2_0_NS);
	/* Enable reception of frames on all ports */
	vsc73xx_ग_लिखो(vsc, VSC73XX_BLOCK_ANALYZER, 0, VSC73XX_RECVMASK,
		      0x5f);
	/* IP multicast flood mask (table 144) */
	vsc73xx_ग_लिखो(vsc, VSC73XX_BLOCK_ANALYZER, 0, VSC73XX_IFLODMSK,
		      0xff);

	mdelay(50);

	/* Release reset from the पूर्णांकernal PHYs */
	vsc73xx_ग_लिखो(vsc, VSC73XX_BLOCK_SYSTEM, 0, VSC73XX_GLORESET,
		      VSC73XX_GLORESET_PHY_RESET);

	udelay(4);

	वापस 0;
पूर्ण

अटल व्योम vsc73xx_init_port(काष्ठा vsc73xx *vsc, पूर्णांक port)
अणु
	u32 val;

	/* MAC configure, first reset the port and then ग_लिखो शेषs */
	vsc73xx_ग_लिखो(vsc, VSC73XX_BLOCK_MAC,
		      port,
		      VSC73XX_MAC_CFG,
		      VSC73XX_MAC_CFG_RESET);

	/* Take up the port in 1Gbit mode by शेष, this will be
	 * augmented after स्वतः-negotiation on the PHY-facing
	 * ports.
	 */
	अगर (port == CPU_PORT)
		val = VSC73XX_MAC_CFG_1000M_F_RGMII;
	अन्यथा
		val = VSC73XX_MAC_CFG_1000M_F_PHY;

	vsc73xx_ग_लिखो(vsc, VSC73XX_BLOCK_MAC,
		      port,
		      VSC73XX_MAC_CFG,
		      val |
		      VSC73XX_MAC_CFG_TX_EN |
		      VSC73XX_MAC_CFG_RX_EN);

	/* Flow control क्रम the CPU port:
	 * Use a zero delay छोड़ो frame when छोड़ो condition is left
	 * Obey छोड़ो control frames
	 */
	vsc73xx_ग_लिखो(vsc, VSC73XX_BLOCK_MAC,
		      port,
		      VSC73XX_FCCONF,
		      VSC73XX_FCCONF_ZERO_PAUSE_EN |
		      VSC73XX_FCCONF_FLOW_CTRL_OBEY);

	/* Issue छोड़ो control frames on PHY facing ports.
	 * Allow early initiation of MAC transmission अगर the amount
	 * of egress data is below 512 bytes on CPU port.
	 * FIXME: enable 20KiB buffers?
	 */
	अगर (port == CPU_PORT)
		val = VSC73XX_Q_MISC_CONF_EARLY_TX_512;
	अन्यथा
		val = VSC73XX_Q_MISC_CONF_MAC_PAUSE_MODE;
	val |= VSC73XX_Q_MISC_CONF_EXTENT_MEM;
	vsc73xx_ग_लिखो(vsc, VSC73XX_BLOCK_MAC,
		      port,
		      VSC73XX_Q_MISC_CONF,
		      val);

	/* Flow control MAC: a MAC address used in flow control frames */
	val = (vsc->addr[5] << 16) | (vsc->addr[4] << 8) | (vsc->addr[3]);
	vsc73xx_ग_लिखो(vsc, VSC73XX_BLOCK_MAC,
		      port,
		      VSC73XX_FCMACHI,
		      val);
	val = (vsc->addr[2] << 16) | (vsc->addr[1] << 8) | (vsc->addr[0]);
	vsc73xx_ग_लिखो(vsc, VSC73XX_BLOCK_MAC,
		      port,
		      VSC73XX_FCMACLO,
		      val);

	/* Tell the categorizer to क्रमward छोड़ो frames, not control
	 * frame. Do not drop anything.
	 */
	vsc73xx_ग_लिखो(vsc, VSC73XX_BLOCK_MAC,
		      port,
		      VSC73XX_CAT_DROP,
		      VSC73XX_CAT_DROP_FWD_PAUSE_ENA);

	/* Clear all counters */
	vsc73xx_ग_लिखो(vsc, VSC73XX_BLOCK_MAC,
		      port, VSC73XX_C_RX0, 0);
पूर्ण

अटल व्योम vsc73xx_adjust_enable_port(काष्ठा vsc73xx *vsc,
				       पूर्णांक port, काष्ठा phy_device *phydev,
				       u32 initval)
अणु
	u32 val = initval;
	u8 seed;

	/* Reset this port FIXME: अवरोध out subroutine */
	val |= VSC73XX_MAC_CFG_RESET;
	vsc73xx_ग_लिखो(vsc, VSC73XX_BLOCK_MAC, port, VSC73XX_MAC_CFG, val);

	/* Seed the port अक्रमomness with अक्रमomness */
	get_अक्रमom_bytes(&seed, 1);
	val |= seed << VSC73XX_MAC_CFG_SEED_OFFSET;
	val |= VSC73XX_MAC_CFG_SEED_LOAD;
	val |= VSC73XX_MAC_CFG_WEXC_DIS;
	vsc73xx_ग_लिखो(vsc, VSC73XX_BLOCK_MAC, port, VSC73XX_MAC_CFG, val);

	/* Flow control क्रम the PHY facing ports:
	 * Use a zero delay छोड़ो frame when छोड़ो condition is left
	 * Obey छोड़ो control frames
	 * When generating छोड़ो frames, use 0xff as छोड़ो value
	 */
	vsc73xx_ग_लिखो(vsc, VSC73XX_BLOCK_MAC, port, VSC73XX_FCCONF,
		      VSC73XX_FCCONF_ZERO_PAUSE_EN |
		      VSC73XX_FCCONF_FLOW_CTRL_OBEY |
		      0xff);

	/* Disallow backward dropping of frames from this port */
	vsc73xx_update_bits(vsc, VSC73XX_BLOCK_ARBITER, 0,
			    VSC73XX_SBACKWDROP, BIT(port), 0);

	/* Enable TX, RX, deनिश्चित reset, stop loading seed */
	vsc73xx_update_bits(vsc, VSC73XX_BLOCK_MAC, port,
			    VSC73XX_MAC_CFG,
			    VSC73XX_MAC_CFG_RESET | VSC73XX_MAC_CFG_SEED_LOAD |
			    VSC73XX_MAC_CFG_TX_EN | VSC73XX_MAC_CFG_RX_EN,
			    VSC73XX_MAC_CFG_TX_EN | VSC73XX_MAC_CFG_RX_EN);
पूर्ण

अटल व्योम vsc73xx_adjust_link(काष्ठा dsa_चयन *ds, पूर्णांक port,
				काष्ठा phy_device *phydev)
अणु
	काष्ठा vsc73xx *vsc = ds->priv;
	u32 val;

	/* Special handling of the CPU-facing port */
	अगर (port == CPU_PORT) अणु
		/* Other ports are alपढ़ोy initialized but not this one */
		vsc73xx_init_port(vsc, CPU_PORT);
		/* Select the बाह्यal port क्रम this पूर्णांकerface (EXT_PORT)
		 * Enable the GMII GTX बाह्यal घड़ी
		 * Use द्विगुन data rate (DDR mode)
		 */
		vsc73xx_ग_लिखो(vsc, VSC73XX_BLOCK_MAC,
			      CPU_PORT,
			      VSC73XX_ADVPORTM,
			      VSC73XX_ADVPORTM_EXT_PORT |
			      VSC73XX_ADVPORTM_ENA_GTX |
			      VSC73XX_ADVPORTM_DDR_MODE);
	पूर्ण

	/* This is the MAC confiuration that always need to happen
	 * after a PHY or the CPU port comes up or करोwn.
	 */
	अगर (!phydev->link) अणु
		पूर्णांक maxloop = 10;

		dev_dbg(vsc->dev, "port %d: went down\n",
			port);

		/* Disable RX on this port */
		vsc73xx_update_bits(vsc, VSC73XX_BLOCK_MAC, port,
				    VSC73XX_MAC_CFG,
				    VSC73XX_MAC_CFG_RX_EN, 0);

		/* Discard packets */
		vsc73xx_update_bits(vsc, VSC73XX_BLOCK_ARBITER, 0,
				    VSC73XX_ARBDISC, BIT(port), BIT(port));

		/* Wait until queue is empty */
		vsc73xx_पढ़ो(vsc, VSC73XX_BLOCK_ARBITER, 0,
			     VSC73XX_ARBEMPTY, &val);
		जबतक (!(val & BIT(port))) अणु
			msleep(1);
			vsc73xx_पढ़ो(vsc, VSC73XX_BLOCK_ARBITER, 0,
				     VSC73XX_ARBEMPTY, &val);
			अगर (--maxloop == 0) अणु
				dev_err(vsc->dev,
					"timeout waiting for block arbiter\n");
				/* Continue anyway */
				अवरोध;
			पूर्ण
		पूर्ण

		/* Put this port पूर्णांकo reset */
		vsc73xx_ग_लिखो(vsc, VSC73XX_BLOCK_MAC, port, VSC73XX_MAC_CFG,
			      VSC73XX_MAC_CFG_RESET);

		/* Accept packets again */
		vsc73xx_update_bits(vsc, VSC73XX_BLOCK_ARBITER, 0,
				    VSC73XX_ARBDISC, BIT(port), 0);

		/* Allow backward dropping of frames from this port */
		vsc73xx_update_bits(vsc, VSC73XX_BLOCK_ARBITER, 0,
				    VSC73XX_SBACKWDROP, BIT(port), BIT(port));

		/* Receive mask (disable क्रमwarding) */
		vsc73xx_update_bits(vsc, VSC73XX_BLOCK_ANALYZER, 0,
				    VSC73XX_RECVMASK, BIT(port), 0);

		वापस;
	पूर्ण

	/* Figure out what speed was negotiated */
	अगर (phydev->speed == SPEED_1000) अणु
		dev_dbg(vsc->dev, "port %d: 1000 Mbit mode full duplex\n",
			port);

		/* Set up शेष क्रम पूर्णांकernal port or बाह्यal RGMII */
		अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII)
			val = VSC73XX_MAC_CFG_1000M_F_RGMII;
		अन्यथा
			val = VSC73XX_MAC_CFG_1000M_F_PHY;
		vsc73xx_adjust_enable_port(vsc, port, phydev, val);
	पूर्ण अन्यथा अगर (phydev->speed == SPEED_100) अणु
		अगर (phydev->duplex == DUPLEX_FULL) अणु
			val = VSC73XX_MAC_CFG_100_10M_F_PHY;
			dev_dbg(vsc->dev,
				"port %d: 100 Mbit full duplex mode\n",
				port);
		पूर्ण अन्यथा अणु
			val = VSC73XX_MAC_CFG_100_10M_H_PHY;
			dev_dbg(vsc->dev,
				"port %d: 100 Mbit half duplex mode\n",
				port);
		पूर्ण
		vsc73xx_adjust_enable_port(vsc, port, phydev, val);
	पूर्ण अन्यथा अगर (phydev->speed == SPEED_10) अणु
		अगर (phydev->duplex == DUPLEX_FULL) अणु
			val = VSC73XX_MAC_CFG_100_10M_F_PHY;
			dev_dbg(vsc->dev,
				"port %d: 10 Mbit full duplex mode\n",
				port);
		पूर्ण अन्यथा अणु
			val = VSC73XX_MAC_CFG_100_10M_H_PHY;
			dev_dbg(vsc->dev,
				"port %d: 10 Mbit half duplex mode\n",
				port);
		पूर्ण
		vsc73xx_adjust_enable_port(vsc, port, phydev, val);
	पूर्ण अन्यथा अणु
		dev_err(vsc->dev,
			"could not adjust link: unknown speed\n");
	पूर्ण

	/* Enable port (क्रमwarding) in the receieve mask */
	vsc73xx_update_bits(vsc, VSC73XX_BLOCK_ANALYZER, 0,
			    VSC73XX_RECVMASK, BIT(port), BIT(port));
पूर्ण

अटल पूर्णांक vsc73xx_port_enable(काष्ठा dsa_चयन *ds, पूर्णांक port,
			       काष्ठा phy_device *phy)
अणु
	काष्ठा vsc73xx *vsc = ds->priv;

	dev_info(vsc->dev, "enable port %d\n", port);
	vsc73xx_init_port(vsc, port);

	वापस 0;
पूर्ण

अटल व्योम vsc73xx_port_disable(काष्ठा dsa_चयन *ds, पूर्णांक port)
अणु
	काष्ठा vsc73xx *vsc = ds->priv;

	/* Just put the port पूर्णांकo reset */
	vsc73xx_ग_लिखो(vsc, VSC73XX_BLOCK_MAC, port,
		      VSC73XX_MAC_CFG, VSC73XX_MAC_CFG_RESET);
पूर्ण

अटल स्थिर काष्ठा vsc73xx_counter *
vsc73xx_find_counter(काष्ठा vsc73xx *vsc,
		     u8 counter,
		     bool tx)
अणु
	स्थिर काष्ठा vsc73xx_counter *cnts;
	पूर्णांक num_cnts;
	पूर्णांक i;

	अगर (tx) अणु
		cnts = vsc73xx_tx_counters;
		num_cnts = ARRAY_SIZE(vsc73xx_tx_counters);
	पूर्ण अन्यथा अणु
		cnts = vsc73xx_rx_counters;
		num_cnts = ARRAY_SIZE(vsc73xx_rx_counters);
	पूर्ण

	क्रम (i = 0; i < num_cnts; i++) अणु
		स्थिर काष्ठा vsc73xx_counter *cnt;

		cnt = &cnts[i];
		अगर (cnt->counter == counter)
			वापस cnt;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम vsc73xx_get_strings(काष्ठा dsa_चयन *ds, पूर्णांक port, u32 stringset,
				uपूर्णांक8_t *data)
अणु
	स्थिर काष्ठा vsc73xx_counter *cnt;
	काष्ठा vsc73xx *vsc = ds->priv;
	u8 indices[6];
	पूर्णांक i, j;
	u32 val;
	पूर्णांक ret;

	अगर (stringset != ETH_SS_STATS)
		वापस;

	ret = vsc73xx_पढ़ो(vsc, VSC73XX_BLOCK_MAC, port,
			   VSC73XX_C_CFG, &val);
	अगर (ret)
		वापस;

	indices[0] = (val & 0x1f); /* RX counter 0 */
	indices[1] = ((val >> 5) & 0x1f); /* RX counter 1 */
	indices[2] = ((val >> 10) & 0x1f); /* RX counter 2 */
	indices[3] = ((val >> 16) & 0x1f); /* TX counter 0 */
	indices[4] = ((val >> 21) & 0x1f); /* TX counter 1 */
	indices[5] = ((val >> 26) & 0x1f); /* TX counter 2 */

	/* The first counters is the RX octets */
	j = 0;
	म_नकलन(data + j * ETH_GSTRING_LEN,
		"RxEtherStatsOctets", ETH_GSTRING_LEN);
	j++;

	/* Each port supports recording 3 RX counters and 3 TX counters,
	 * figure out what counters we use in this set-up and वापस the
	 * names of them. The hardware शेष counters will be number of
	 * packets on RX/TX, combined broadcast+multicast packets RX/TX and
	 * total error packets RX/TX.
	 */
	क्रम (i = 0; i < 3; i++) अणु
		cnt = vsc73xx_find_counter(vsc, indices[i], false);
		अगर (cnt)
			म_नकलन(data + j * ETH_GSTRING_LEN,
				cnt->name, ETH_GSTRING_LEN);
		j++;
	पूर्ण

	/* TX stats begins with the number of TX octets */
	म_नकलन(data + j * ETH_GSTRING_LEN,
		"TxEtherStatsOctets", ETH_GSTRING_LEN);
	j++;

	क्रम (i = 3; i < 6; i++) अणु
		cnt = vsc73xx_find_counter(vsc, indices[i], true);
		अगर (cnt)
			म_नकलन(data + j * ETH_GSTRING_LEN,
				cnt->name, ETH_GSTRING_LEN);
		j++;
	पूर्ण
पूर्ण

अटल पूर्णांक vsc73xx_get_sset_count(काष्ठा dsa_चयन *ds, पूर्णांक port, पूर्णांक sset)
अणु
	/* We only support SS_STATS */
	अगर (sset != ETH_SS_STATS)
		वापस 0;
	/* RX and TX packets, then 3 RX counters, 3 TX counters */
	वापस 8;
पूर्ण

अटल व्योम vsc73xx_get_ethtool_stats(काष्ठा dsa_चयन *ds, पूर्णांक port,
				      uपूर्णांक64_t *data)
अणु
	काष्ठा vsc73xx *vsc = ds->priv;
	u8 regs[] = अणु
		VSC73XX_RXOCT,
		VSC73XX_C_RX0,
		VSC73XX_C_RX1,
		VSC73XX_C_RX2,
		VSC73XX_TXOCT,
		VSC73XX_C_TX0,
		VSC73XX_C_TX1,
		VSC73XX_C_TX2,
	पूर्ण;
	u32 val;
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(regs); i++) अणु
		ret = vsc73xx_पढ़ो(vsc, VSC73XX_BLOCK_MAC, port,
				   regs[i], &val);
		अगर (ret) अणु
			dev_err(vsc->dev, "error reading counter %d\n", i);
			वापस;
		पूर्ण
		data[i] = val;
	पूर्ण
पूर्ण

अटल पूर्णांक vsc73xx_change_mtu(काष्ठा dsa_चयन *ds, पूर्णांक port, पूर्णांक new_mtu)
अणु
	काष्ठा vsc73xx *vsc = ds->priv;

	वापस vsc73xx_ग_लिखो(vsc, VSC73XX_BLOCK_MAC, port,
			     VSC73XX_MAXLEN, new_mtu);
पूर्ण

/* According to application not "VSC7398 Jumbo Frames" setting
 * up the MTU to 9.6 KB करोes not affect the perक्रमmance on standard
 * frames. It is clear from the application note that
 * "9.6 kilobytes" == 9600 bytes.
 */
अटल पूर्णांक vsc73xx_get_max_mtu(काष्ठा dsa_चयन *ds, पूर्णांक port)
अणु
	वापस 9600;
पूर्ण

अटल स्थिर काष्ठा dsa_चयन_ops vsc73xx_ds_ops = अणु
	.get_tag_protocol = vsc73xx_get_tag_protocol,
	.setup = vsc73xx_setup,
	.phy_पढ़ो = vsc73xx_phy_पढ़ो,
	.phy_ग_लिखो = vsc73xx_phy_ग_लिखो,
	.adjust_link = vsc73xx_adjust_link,
	.get_strings = vsc73xx_get_strings,
	.get_ethtool_stats = vsc73xx_get_ethtool_stats,
	.get_sset_count = vsc73xx_get_sset_count,
	.port_enable = vsc73xx_port_enable,
	.port_disable = vsc73xx_port_disable,
	.port_change_mtu = vsc73xx_change_mtu,
	.port_max_mtu = vsc73xx_get_max_mtu,
पूर्ण;

अटल पूर्णांक vsc73xx_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा vsc73xx *vsc = gpiochip_get_data(chip);
	u32 val;
	पूर्णांक ret;

	ret = vsc73xx_पढ़ो(vsc, VSC73XX_BLOCK_SYSTEM, 0,
			   VSC73XX_GPIO, &val);
	अगर (ret)
		वापस ret;

	वापस !!(val & BIT(offset));
पूर्ण

अटल व्योम vsc73xx_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
			     पूर्णांक val)
अणु
	काष्ठा vsc73xx *vsc = gpiochip_get_data(chip);
	u32 पंचांगp = val ? BIT(offset) : 0;

	vsc73xx_update_bits(vsc, VSC73XX_BLOCK_SYSTEM, 0,
			    VSC73XX_GPIO, BIT(offset), पंचांगp);
पूर्ण

अटल पूर्णांक vsc73xx_gpio_direction_output(काष्ठा gpio_chip *chip,
					 अचिन्हित पूर्णांक offset, पूर्णांक val)
अणु
	काष्ठा vsc73xx *vsc = gpiochip_get_data(chip);
	u32 पंचांगp = val ? BIT(offset) : 0;

	वापस vsc73xx_update_bits(vsc, VSC73XX_BLOCK_SYSTEM, 0,
				   VSC73XX_GPIO, BIT(offset + 4) | BIT(offset),
				   BIT(offset + 4) | पंचांगp);
पूर्ण

अटल पूर्णांक vsc73xx_gpio_direction_input(काष्ठा gpio_chip *chip,
					अचिन्हित पूर्णांक offset)
अणु
	काष्ठा vsc73xx *vsc = gpiochip_get_data(chip);

	वापस  vsc73xx_update_bits(vsc, VSC73XX_BLOCK_SYSTEM, 0,
				    VSC73XX_GPIO, BIT(offset + 4),
				    0);
पूर्ण

अटल पूर्णांक vsc73xx_gpio_get_direction(काष्ठा gpio_chip *chip,
				      अचिन्हित पूर्णांक offset)
अणु
	काष्ठा vsc73xx *vsc = gpiochip_get_data(chip);
	u32 val;
	पूर्णांक ret;

	ret = vsc73xx_पढ़ो(vsc, VSC73XX_BLOCK_SYSTEM, 0,
			   VSC73XX_GPIO, &val);
	अगर (ret)
		वापस ret;

	वापस !(val & BIT(offset + 4));
पूर्ण

अटल पूर्णांक vsc73xx_gpio_probe(काष्ठा vsc73xx *vsc)
अणु
	पूर्णांक ret;

	vsc->gc.label = devm_kaप्र_लिखो(vsc->dev, GFP_KERNEL, "VSC%04x",
				       vsc->chipid);
	vsc->gc.ngpio = 4;
	vsc->gc.owner = THIS_MODULE;
	vsc->gc.parent = vsc->dev;
#अगर IS_ENABLED(CONFIG_OF_GPIO)
	vsc->gc.of_node = vsc->dev->of_node;
#पूर्ण_अगर
	vsc->gc.base = -1;
	vsc->gc.get = vsc73xx_gpio_get;
	vsc->gc.set = vsc73xx_gpio_set;
	vsc->gc.direction_input = vsc73xx_gpio_direction_input;
	vsc->gc.direction_output = vsc73xx_gpio_direction_output;
	vsc->gc.get_direction = vsc73xx_gpio_get_direction;
	vsc->gc.can_sleep = true;
	ret = devm_gpiochip_add_data(vsc->dev, &vsc->gc, vsc);
	अगर (ret) अणु
		dev_err(vsc->dev, "unable to register GPIO chip\n");
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक vsc73xx_probe(काष्ठा vsc73xx *vsc)
अणु
	काष्ठा device *dev = vsc->dev;
	पूर्णांक ret;

	/* Release reset, अगर any */
	vsc->reset = devm_gpiod_get_optional(dev, "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(vsc->reset)) अणु
		dev_err(dev, "failed to get RESET GPIO\n");
		वापस PTR_ERR(vsc->reset);
	पूर्ण
	अगर (vsc->reset)
		/* Wait 20ms according to datasheet table 245 */
		msleep(20);

	ret = vsc73xx_detect(vsc);
	अगर (ret == -EAGAIN) अणु
		dev_err(vsc->dev,
			"Chip seems to be out of control. Assert reset and try again.\n");
		gpiod_set_value_cansleep(vsc->reset, 1);
		/* Reset pulse should be 20ns minimum, according to datasheet
		 * table 245, so 10us should be fine
		 */
		usleep_range(10, 100);
		gpiod_set_value_cansleep(vsc->reset, 0);
		/* Wait 20ms according to datasheet table 245 */
		msleep(20);
		ret = vsc73xx_detect(vsc);
	पूर्ण
	अगर (ret) अणु
		dev_err(dev, "no chip found (%d)\n", ret);
		वापस -ENODEV;
	पूर्ण

	eth_अक्रमom_addr(vsc->addr);
	dev_info(vsc->dev,
		 "MAC for control frames: %02X:%02X:%02X:%02X:%02X:%02X\n",
		 vsc->addr[0], vsc->addr[1], vsc->addr[2],
		 vsc->addr[3], vsc->addr[4], vsc->addr[5]);

	/* The VSC7395 चयन chips have 5+1 ports which means 5
	 * ordinary ports and a sixth CPU port facing the processor
	 * with an RGMII पूर्णांकerface. These ports are numbered 0..4
	 * and 6, so they leave a "hole" in the port map क्रम port 5,
	 * which is invalid.
	 *
	 * The VSC7398 has 8 ports, port 7 is again the CPU port.
	 *
	 * We allocate 8 ports and aव्योम access to the nonexistant
	 * ports.
	 */
	vsc->ds = devm_kzalloc(dev, माप(*vsc->ds), GFP_KERNEL);
	अगर (!vsc->ds)
		वापस -ENOMEM;

	vsc->ds->dev = dev;
	vsc->ds->num_ports = 8;
	vsc->ds->priv = vsc;

	vsc->ds->ops = &vsc73xx_ds_ops;
	ret = dsa_रेजिस्टर_चयन(vsc->ds);
	अगर (ret) अणु
		dev_err(dev, "unable to register switch (%d)\n", ret);
		वापस ret;
	पूर्ण

	ret = vsc73xx_gpio_probe(vsc);
	अगर (ret) अणु
		dsa_unरेजिस्टर_चयन(vsc->ds);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(vsc73xx_probe);

पूर्णांक vsc73xx_हटाओ(काष्ठा vsc73xx *vsc)
अणु
	dsa_unरेजिस्टर_चयन(vsc->ds);
	gpiod_set_value(vsc->reset, 1);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(vsc73xx_हटाओ);

MODULE_AUTHOR("Linus Walleij <linus.walleij@linaro.org>");
MODULE_DESCRIPTION("Vitesse VSC7385/7388/7395/7398 driver");
MODULE_LICENSE("GPL v2");
