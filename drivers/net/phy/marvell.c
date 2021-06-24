<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * drivers/net/phy/marvell.c
 *
 * Driver क्रम Marvell PHYs
 *
 * Author: Andy Fleming
 *
 * Copyright (c) 2004 Freescale Semiconductor, Inc.
 *
 * Copyright (c) 2013 Michael Stapelberg <michael@stapelberg.de>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/प्रकार.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/unistd.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/mii.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/ethtool_netlink.h>
#समावेश <linux/phy.h>
#समावेश <linux/marvell_phy.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/of.h>

#समावेश <linux/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <linux/uaccess.h>

#घोषणा MII_MARVELL_PHY_PAGE		22
#घोषणा MII_MARVELL_COPPER_PAGE		0x00
#घोषणा MII_MARVELL_FIBER_PAGE		0x01
#घोषणा MII_MARVELL_MSCR_PAGE		0x02
#घोषणा MII_MARVELL_LED_PAGE		0x03
#घोषणा MII_MARVELL_VCT5_PAGE		0x05
#घोषणा MII_MARVELL_MISC_TEST_PAGE	0x06
#घोषणा MII_MARVELL_VCT7_PAGE		0x07
#घोषणा MII_MARVELL_WOL_PAGE		0x11

#घोषणा MII_M1011_IEVENT		0x13
#घोषणा MII_M1011_IEVENT_CLEAR		0x0000

#घोषणा MII_M1011_IMASK			0x12
#घोषणा MII_M1011_IMASK_INIT		0x6400
#घोषणा MII_M1011_IMASK_CLEAR		0x0000

#घोषणा MII_M1011_PHY_SCR			0x10
#घोषणा MII_M1011_PHY_SCR_DOWNSHIFT_EN		BIT(11)
#घोषणा MII_M1011_PHY_SCR_DOWNSHIFT_MASK	GENMASK(14, 12)
#घोषणा MII_M1011_PHY_SCR_DOWNSHIFT_MAX		8
#घोषणा MII_M1011_PHY_SCR_MDI			(0x0 << 5)
#घोषणा MII_M1011_PHY_SCR_MDI_X			(0x1 << 5)
#घोषणा MII_M1011_PHY_SCR_AUTO_CROSS		(0x3 << 5)

#घोषणा MII_M1011_PHY_SSR			0x11
#घोषणा MII_M1011_PHY_SSR_DOWNSHIFT		BIT(5)

#घोषणा MII_M1111_PHY_LED_CONTROL	0x18
#घोषणा MII_M1111_PHY_LED_सूचीECT	0x4100
#घोषणा MII_M1111_PHY_LED_COMBINE	0x411c
#घोषणा MII_M1111_PHY_EXT_CR		0x14
#घोषणा MII_M1111_PHY_EXT_CR_DOWNSHIFT_MASK	GENMASK(11, 9)
#घोषणा MII_M1111_PHY_EXT_CR_DOWNSHIFT_MAX	8
#घोषणा MII_M1111_PHY_EXT_CR_DOWNSHIFT_EN	BIT(8)
#घोषणा MII_M1111_RGMII_RX_DELAY	BIT(7)
#घोषणा MII_M1111_RGMII_TX_DELAY	BIT(1)
#घोषणा MII_M1111_PHY_EXT_SR		0x1b

#घोषणा MII_M1111_HWCFG_MODE_MASK		0xf
#घोषणा MII_M1111_HWCFG_MODE_FIBER_RGMII	0x3
#घोषणा MII_M1111_HWCFG_MODE_SGMII_NO_CLK	0x4
#घोषणा MII_M1111_HWCFG_MODE_RTBI		0x7
#घोषणा MII_M1111_HWCFG_MODE_COPPER_1000X_AN	0x8
#घोषणा MII_M1111_HWCFG_MODE_COPPER_RTBI	0x9
#घोषणा MII_M1111_HWCFG_MODE_COPPER_RGMII	0xb
#घोषणा MII_M1111_HWCFG_MODE_COPPER_1000X_NOAN	0xc
#घोषणा MII_M1111_HWCFG_SERIAL_AN_BYPASS	BIT(12)
#घोषणा MII_M1111_HWCFG_FIBER_COPPER_RES	BIT(13)
#घोषणा MII_M1111_HWCFG_FIBER_COPPER_AUTO	BIT(15)

#घोषणा MII_88E1121_PHY_MSCR_REG	21
#घोषणा MII_88E1121_PHY_MSCR_RX_DELAY	BIT(5)
#घोषणा MII_88E1121_PHY_MSCR_TX_DELAY	BIT(4)
#घोषणा MII_88E1121_PHY_MSCR_DELAY_MASK	(BIT(5) | BIT(4))

#घोषणा MII_88E1121_MISC_TEST				0x1a
#घोषणा MII_88E1510_MISC_TEST_TEMP_THRESHOLD_MASK	0x1f00
#घोषणा MII_88E1510_MISC_TEST_TEMP_THRESHOLD_SHIFT	8
#घोषणा MII_88E1510_MISC_TEST_TEMP_IRQ_EN		BIT(7)
#घोषणा MII_88E1510_MISC_TEST_TEMP_IRQ			BIT(6)
#घोषणा MII_88E1121_MISC_TEST_TEMP_SENSOR_EN		BIT(5)
#घोषणा MII_88E1121_MISC_TEST_TEMP_MASK			0x1f

#घोषणा MII_88E1510_TEMP_SENSOR		0x1b
#घोषणा MII_88E1510_TEMP_SENSOR_MASK	0xff

#घोषणा MII_88E1540_COPPER_CTRL3	0x1a
#घोषणा MII_88E1540_COPPER_CTRL3_LINK_DOWN_DELAY_MASK	GENMASK(11, 10)
#घोषणा MII_88E1540_COPPER_CTRL3_LINK_DOWN_DELAY_00MS	0
#घोषणा MII_88E1540_COPPER_CTRL3_LINK_DOWN_DELAY_10MS	1
#घोषणा MII_88E1540_COPPER_CTRL3_LINK_DOWN_DELAY_20MS	2
#घोषणा MII_88E1540_COPPER_CTRL3_LINK_DOWN_DELAY_40MS	3
#घोषणा MII_88E1540_COPPER_CTRL3_FAST_LINK_DOWN		BIT(9)

#घोषणा MII_88E6390_MISC_TEST		0x1b
#घोषणा MII_88E6390_MISC_TEST_TEMP_SENSOR_ENABLE_SAMPLE_1S	(0x0 << 14)
#घोषणा MII_88E6390_MISC_TEST_TEMP_SENSOR_ENABLE		(0x1 << 14)
#घोषणा MII_88E6390_MISC_TEST_TEMP_SENSOR_ENABLE_ONESHOT	(0x2 << 14)
#घोषणा MII_88E6390_MISC_TEST_TEMP_SENSOR_DISABLE		(0x3 << 14)
#घोषणा MII_88E6390_MISC_TEST_TEMP_SENSOR_MASK			(0x3 << 14)
#घोषणा MII_88E6393_MISC_TEST_SAMPLES_2048	(0x0 << 11)
#घोषणा MII_88E6393_MISC_TEST_SAMPLES_4096	(0x1 << 11)
#घोषणा MII_88E6393_MISC_TEST_SAMPLES_8192	(0x2 << 11)
#घोषणा MII_88E6393_MISC_TEST_SAMPLES_16384	(0x3 << 11)
#घोषणा MII_88E6393_MISC_TEST_SAMPLES_MASK	(0x3 << 11)
#घोषणा MII_88E6393_MISC_TEST_RATE_2_3MS	(0x5 << 8)
#घोषणा MII_88E6393_MISC_TEST_RATE_6_4MS	(0x6 << 8)
#घोषणा MII_88E6393_MISC_TEST_RATE_11_9MS	(0x7 << 8)
#घोषणा MII_88E6393_MISC_TEST_RATE_MASK		(0x7 << 8)

#घोषणा MII_88E6390_TEMP_SENSOR		0x1c
#घोषणा MII_88E6393_TEMP_SENSOR_THRESHOLD_MASK	0xff00
#घोषणा MII_88E6393_TEMP_SENSOR_THRESHOLD_SHIFT	8
#घोषणा MII_88E6390_TEMP_SENSOR_MASK		0xff
#घोषणा MII_88E6390_TEMP_SENSOR_SAMPLES		10

#घोषणा MII_88E1318S_PHY_MSCR1_REG	16
#घोषणा MII_88E1318S_PHY_MSCR1_PAD_ODD	BIT(6)

/* Copper Specअगरic Interrupt Enable Register */
#घोषणा MII_88E1318S_PHY_CSIER				0x12
/* WOL Event Interrupt Enable */
#घोषणा MII_88E1318S_PHY_CSIER_WOL_EIE			BIT(7)

/* LED Timer Control Register */
#घोषणा MII_88E1318S_PHY_LED_TCR			0x12
#घोषणा MII_88E1318S_PHY_LED_TCR_FORCE_INT		BIT(15)
#घोषणा MII_88E1318S_PHY_LED_TCR_INTn_ENABLE		BIT(7)
#घोषणा MII_88E1318S_PHY_LED_TCR_INT_ACTIVE_LOW		BIT(11)

/* Magic Packet MAC address रेजिस्टरs */
#घोषणा MII_88E1318S_PHY_MAGIC_PACKET_WORD2		0x17
#घोषणा MII_88E1318S_PHY_MAGIC_PACKET_WORD1		0x18
#घोषणा MII_88E1318S_PHY_MAGIC_PACKET_WORD0		0x19

#घोषणा MII_88E1318S_PHY_WOL_CTRL				0x10
#घोषणा MII_88E1318S_PHY_WOL_CTRL_CLEAR_WOL_STATUS		BIT(12)
#घोषणा MII_88E1318S_PHY_WOL_CTRL_MAGIC_PACKET_MATCH_ENABLE	BIT(14)

#घोषणा MII_PHY_LED_CTRL	        16
#घोषणा MII_88E1121_PHY_LED_DEF		0x0030
#घोषणा MII_88E1510_PHY_LED_DEF		0x1177
#घोषणा MII_88E1510_PHY_LED0_LINK_LED1_ACTIVE	0x1040

#घोषणा MII_M1011_PHY_STATUS		0x11
#घोषणा MII_M1011_PHY_STATUS_1000	0x8000
#घोषणा MII_M1011_PHY_STATUS_100	0x4000
#घोषणा MII_M1011_PHY_STATUS_SPD_MASK	0xc000
#घोषणा MII_M1011_PHY_STATUS_FULLDUPLEX	0x2000
#घोषणा MII_M1011_PHY_STATUS_RESOLVED	0x0800
#घोषणा MII_M1011_PHY_STATUS_LINK	0x0400

#घोषणा MII_88E3016_PHY_SPEC_CTRL	0x10
#घोषणा MII_88E3016_DISABLE_SCRAMBLER	0x0200
#घोषणा MII_88E3016_AUTO_MDIX_CROSSOVER	0x0030

#घोषणा MII_88E1510_GEN_CTRL_REG_1		0x14
#घोषणा MII_88E1510_GEN_CTRL_REG_1_MODE_MASK	0x7
#घोषणा MII_88E1510_GEN_CTRL_REG_1_MODE_SGMII	0x1	/* SGMII to copper */
#घोषणा MII_88E1510_GEN_CTRL_REG_1_RESET	0x8000	/* Soft reset */

#घोषणा MII_VCT5_TX_RX_MDI0_COUPLING	0x10
#घोषणा MII_VCT5_TX_RX_MDI1_COUPLING	0x11
#घोषणा MII_VCT5_TX_RX_MDI2_COUPLING	0x12
#घोषणा MII_VCT5_TX_RX_MDI3_COUPLING	0x13
#घोषणा MII_VCT5_TX_RX_AMPLITUDE_MASK	0x7f00
#घोषणा MII_VCT5_TX_RX_AMPLITUDE_SHIFT	8
#घोषणा MII_VCT5_TX_RX_COUPLING_POSITIVE_REFLECTION	BIT(15)

#घोषणा MII_VCT5_CTRL				0x17
#घोषणा MII_VCT5_CTRL_ENABLE				BIT(15)
#घोषणा MII_VCT5_CTRL_COMPLETE				BIT(14)
#घोषणा MII_VCT5_CTRL_TX_SAME_CHANNEL			(0x0 << 11)
#घोषणा MII_VCT5_CTRL_TX0_CHANNEL			(0x4 << 11)
#घोषणा MII_VCT5_CTRL_TX1_CHANNEL			(0x5 << 11)
#घोषणा MII_VCT5_CTRL_TX2_CHANNEL			(0x6 << 11)
#घोषणा MII_VCT5_CTRL_TX3_CHANNEL			(0x7 << 11)
#घोषणा MII_VCT5_CTRL_SAMPLES_2				(0x0 << 8)
#घोषणा MII_VCT5_CTRL_SAMPLES_4				(0x1 << 8)
#घोषणा MII_VCT5_CTRL_SAMPLES_8				(0x2 << 8)
#घोषणा MII_VCT5_CTRL_SAMPLES_16			(0x3 << 8)
#घोषणा MII_VCT5_CTRL_SAMPLES_32			(0x4 << 8)
#घोषणा MII_VCT5_CTRL_SAMPLES_64			(0x5 << 8)
#घोषणा MII_VCT5_CTRL_SAMPLES_128			(0x6 << 8)
#घोषणा MII_VCT5_CTRL_SAMPLES_DEFAULT			(0x6 << 8)
#घोषणा MII_VCT5_CTRL_SAMPLES_256			(0x7 << 8)
#घोषणा MII_VCT5_CTRL_SAMPLES_SHIFT			8
#घोषणा MII_VCT5_CTRL_MODE_MAXIMUM_PEEK			(0x0 << 6)
#घोषणा MII_VCT5_CTRL_MODE_FIRST_LAST_PEEK		(0x1 << 6)
#घोषणा MII_VCT5_CTRL_MODE_OFFSET			(0x2 << 6)
#घोषणा MII_VCT5_CTRL_SAMPLE_POINT			(0x3 << 6)
#घोषणा MII_VCT5_CTRL_PEEK_HYST_DEFAULT			3

#घोषणा MII_VCT5_SAMPLE_POINT_DISTANCE		0x18
#घोषणा MII_VCT5_SAMPLE_POINT_DISTANCE_MAX	511
#घोषणा MII_VCT5_TX_PULSE_CTRL			0x1c
#घोषणा MII_VCT5_TX_PULSE_CTRL_DONT_WAIT_LINK_DOWN	BIT(12)
#घोषणा MII_VCT5_TX_PULSE_CTRL_PULSE_WIDTH_128nS	(0x0 << 10)
#घोषणा MII_VCT5_TX_PULSE_CTRL_PULSE_WIDTH_96nS		(0x1 << 10)
#घोषणा MII_VCT5_TX_PULSE_CTRL_PULSE_WIDTH_64nS		(0x2 << 10)
#घोषणा MII_VCT5_TX_PULSE_CTRL_PULSE_WIDTH_32nS		(0x3 << 10)
#घोषणा MII_VCT5_TX_PULSE_CTRL_PULSE_WIDTH_SHIFT	10
#घोषणा MII_VCT5_TX_PULSE_CTRL_PULSE_AMPLITUDE_1000mV	(0x0 << 8)
#घोषणा MII_VCT5_TX_PULSE_CTRL_PULSE_AMPLITUDE_750mV	(0x1 << 8)
#घोषणा MII_VCT5_TX_PULSE_CTRL_PULSE_AMPLITUDE_500mV	(0x2 << 8)
#घोषणा MII_VCT5_TX_PULSE_CTRL_PULSE_AMPLITUDE_250mV	(0x3 << 8)
#घोषणा MII_VCT5_TX_PULSE_CTRL_PULSE_AMPLITUDE_SHIFT	8
#घोषणा MII_VCT5_TX_PULSE_CTRL_MAX_AMP			BIT(7)
#घोषणा MII_VCT5_TX_PULSE_CTRL_GT_140m_46_86mV		(0x6 << 0)

/* For TDR measurements less than 11 meters, a लघु pulse should be
 * used.
 */
#घोषणा TDR_SHORT_CABLE_LENGTH	11

#घोषणा MII_VCT7_PAIR_0_DISTANCE	0x10
#घोषणा MII_VCT7_PAIR_1_DISTANCE	0x11
#घोषणा MII_VCT7_PAIR_2_DISTANCE	0x12
#घोषणा MII_VCT7_PAIR_3_DISTANCE	0x13

#घोषणा MII_VCT7_RESULTS	0x14
#घोषणा MII_VCT7_RESULTS_PAIR3_MASK	0xf000
#घोषणा MII_VCT7_RESULTS_PAIR2_MASK	0x0f00
#घोषणा MII_VCT7_RESULTS_PAIR1_MASK	0x00f0
#घोषणा MII_VCT7_RESULTS_PAIR0_MASK	0x000f
#घोषणा MII_VCT7_RESULTS_PAIR3_SHIFT	12
#घोषणा MII_VCT7_RESULTS_PAIR2_SHIFT	8
#घोषणा MII_VCT7_RESULTS_PAIR1_SHIFT	4
#घोषणा MII_VCT7_RESULTS_PAIR0_SHIFT	0
#घोषणा MII_VCT7_RESULTS_INVALID	0
#घोषणा MII_VCT7_RESULTS_OK		1
#घोषणा MII_VCT7_RESULTS_OPEN		2
#घोषणा MII_VCT7_RESULTS_SAME_SHORT	3
#घोषणा MII_VCT7_RESULTS_CROSS_SHORT	4
#घोषणा MII_VCT7_RESULTS_BUSY		9

#घोषणा MII_VCT7_CTRL		0x15
#घोषणा MII_VCT7_CTRL_RUN_NOW			BIT(15)
#घोषणा MII_VCT7_CTRL_RUN_ANEG			BIT(14)
#घोषणा MII_VCT7_CTRL_DISABLE_CROSS		BIT(13)
#घोषणा MII_VCT7_CTRL_RUN_AFTER_BREAK_LINK	BIT(12)
#घोषणा MII_VCT7_CTRL_IN_PROGRESS		BIT(11)
#घोषणा MII_VCT7_CTRL_METERS			BIT(10)
#घोषणा MII_VCT7_CTRL_CENTIMETERS		0

#घोषणा LPA_PAUSE_FIBER		0x180
#घोषणा LPA_PAUSE_ASYM_FIBER	0x100

#घोषणा NB_FIBER_STATS	1

MODULE_DESCRIPTION("Marvell PHY driver");
MODULE_AUTHOR("Andy Fleming");
MODULE_LICENSE("GPL");

काष्ठा marvell_hw_stat अणु
	स्थिर अक्षर *string;
	u8 page;
	u8 reg;
	u8 bits;
पूर्ण;

अटल काष्ठा marvell_hw_stat marvell_hw_stats[] = अणु
	अणु "phy_receive_errors_copper", 0, 21, 16पूर्ण,
	अणु "phy_idle_errors", 0, 10, 8 पूर्ण,
	अणु "phy_receive_errors_fiber", 1, 21, 16पूर्ण,
पूर्ण;

काष्ठा marvell_priv अणु
	u64 stats[ARRAY_SIZE(marvell_hw_stats)];
	अक्षर *hwmon_name;
	काष्ठा device *hwmon_dev;
	bool cable_test_tdr;
	u32 first;
	u32 last;
	u32 step;
	s8 pair;
पूर्ण;

अटल पूर्णांक marvell_पढ़ो_page(काष्ठा phy_device *phydev)
अणु
	वापस __phy_पढ़ो(phydev, MII_MARVELL_PHY_PAGE);
पूर्ण

अटल पूर्णांक marvell_ग_लिखो_page(काष्ठा phy_device *phydev, पूर्णांक page)
अणु
	वापस __phy_ग_लिखो(phydev, MII_MARVELL_PHY_PAGE, page);
पूर्ण

अटल पूर्णांक marvell_set_page(काष्ठा phy_device *phydev, पूर्णांक page)
अणु
	वापस phy_ग_लिखो(phydev, MII_MARVELL_PHY_PAGE, page);
पूर्ण

अटल पूर्णांक marvell_ack_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	/* Clear the पूर्णांकerrupts by पढ़ोing the reg */
	err = phy_पढ़ो(phydev, MII_M1011_IEVENT);

	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक marvell_config_पूर्णांकr(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	अगर (phydev->पूर्णांकerrupts == PHY_INTERRUPT_ENABLED) अणु
		err = marvell_ack_पूर्णांकerrupt(phydev);
		अगर (err)
			वापस err;

		err = phy_ग_लिखो(phydev, MII_M1011_IMASK,
				MII_M1011_IMASK_INIT);
	पूर्ण अन्यथा अणु
		err = phy_ग_लिखो(phydev, MII_M1011_IMASK,
				MII_M1011_IMASK_CLEAR);
		अगर (err)
			वापस err;

		err = marvell_ack_पूर्णांकerrupt(phydev);
	पूर्ण

	वापस err;
पूर्ण

अटल irqवापस_t marvell_handle_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक irq_status;

	irq_status = phy_पढ़ो(phydev, MII_M1011_IEVENT);
	अगर (irq_status < 0) अणु
		phy_error(phydev);
		वापस IRQ_NONE;
	पूर्ण

	अगर (!(irq_status & MII_M1011_IMASK_INIT))
		वापस IRQ_NONE;

	phy_trigger_machine(phydev);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक marvell_set_polarity(काष्ठा phy_device *phydev, पूर्णांक polarity)
अणु
	पूर्णांक reg;
	पूर्णांक err;
	पूर्णांक val;

	/* get the current settings */
	reg = phy_पढ़ो(phydev, MII_M1011_PHY_SCR);
	अगर (reg < 0)
		वापस reg;

	val = reg;
	val &= ~MII_M1011_PHY_SCR_AUTO_CROSS;
	चयन (polarity) अणु
	हाल ETH_TP_MDI:
		val |= MII_M1011_PHY_SCR_MDI;
		अवरोध;
	हाल ETH_TP_MDI_X:
		val |= MII_M1011_PHY_SCR_MDI_X;
		अवरोध;
	हाल ETH_TP_MDI_AUTO:
	हाल ETH_TP_MDI_INVALID:
	शेष:
		val |= MII_M1011_PHY_SCR_AUTO_CROSS;
		अवरोध;
	पूर्ण

	अगर (val != reg) अणु
		/* Set the new polarity value in the रेजिस्टर */
		err = phy_ग_लिखो(phydev, MII_M1011_PHY_SCR, val);
		अगर (err)
			वापस err;
	पूर्ण

	वापस val != reg;
पूर्ण

अटल पूर्णांक marvell_config_aneg(काष्ठा phy_device *phydev)
अणु
	पूर्णांक changed = 0;
	पूर्णांक err;

	err = marvell_set_polarity(phydev, phydev->mdix_ctrl);
	अगर (err < 0)
		वापस err;

	changed = err;

	err = phy_ग_लिखो(phydev, MII_M1111_PHY_LED_CONTROL,
			MII_M1111_PHY_LED_सूचीECT);
	अगर (err < 0)
		वापस err;

	err = genphy_config_aneg(phydev);
	अगर (err < 0)
		वापस err;

	अगर (phydev->स्वतःneg != AUTONEG_ENABLE || changed) अणु
		/* A ग_लिखो to speed/duplex bits (that is perक्रमmed by
		 * genphy_config_aneg() call above) must be followed by
		 * a software reset. Otherwise, the ग_लिखो has no effect.
		 */
		err = genphy_soft_reset(phydev);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक m88e1101_config_aneg(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	/* This Marvell PHY has an errata which requires
	 * that certain रेजिस्टरs get written in order
	 * to restart स्वतःnegotiation
	 */
	err = genphy_soft_reset(phydev);
	अगर (err < 0)
		वापस err;

	err = phy_ग_लिखो(phydev, 0x1d, 0x1f);
	अगर (err < 0)
		वापस err;

	err = phy_ग_लिखो(phydev, 0x1e, 0x200c);
	अगर (err < 0)
		वापस err;

	err = phy_ग_लिखो(phydev, 0x1d, 0x5);
	अगर (err < 0)
		वापस err;

	err = phy_ग_लिखो(phydev, 0x1e, 0);
	अगर (err < 0)
		वापस err;

	err = phy_ग_लिखो(phydev, 0x1e, 0x100);
	अगर (err < 0)
		वापस err;

	वापस marvell_config_aneg(phydev);
पूर्ण

#अगर IS_ENABLED(CONFIG_OF_MDIO)
/* Set and/or override some configuration रेजिस्टरs based on the
 * marvell,reg-init property stored in the of_node क्रम the phydev.
 *
 * marvell,reg-init = <reg-page reg mask value>,...;
 *
 * There may be one or more sets of <reg-page reg mask value>:
 *
 * reg-page: which रेजिस्टर bank to use.
 * reg: the रेजिस्टर.
 * mask: अगर non-zero, ANDed with existing रेजिस्टर value.
 * value: ORed with the masked value and written to the regiser.
 *
 */
अटल पूर्णांक marvell_of_reg_init(काष्ठा phy_device *phydev)
अणु
	स्थिर __be32 *paddr;
	पूर्णांक len, i, saved_page, current_page, ret = 0;

	अगर (!phydev->mdio.dev.of_node)
		वापस 0;

	paddr = of_get_property(phydev->mdio.dev.of_node,
				"marvell,reg-init", &len);
	अगर (!paddr || len < (4 * माप(*paddr)))
		वापस 0;

	saved_page = phy_save_page(phydev);
	अगर (saved_page < 0)
		जाओ err;
	current_page = saved_page;

	len /= माप(*paddr);
	क्रम (i = 0; i < len - 3; i += 4) अणु
		u16 page = be32_to_cpup(paddr + i);
		u16 reg = be32_to_cpup(paddr + i + 1);
		u16 mask = be32_to_cpup(paddr + i + 2);
		u16 val_bits = be32_to_cpup(paddr + i + 3);
		पूर्णांक val;

		अगर (page != current_page) अणु
			current_page = page;
			ret = marvell_ग_लिखो_page(phydev, page);
			अगर (ret < 0)
				जाओ err;
		पूर्ण

		val = 0;
		अगर (mask) अणु
			val = __phy_पढ़ो(phydev, reg);
			अगर (val < 0) अणु
				ret = val;
				जाओ err;
			पूर्ण
			val &= mask;
		पूर्ण
		val |= val_bits;

		ret = __phy_ग_लिखो(phydev, reg, val);
		अगर (ret < 0)
			जाओ err;
	पूर्ण
err:
	वापस phy_restore_page(phydev, saved_page, ret);
पूर्ण
#अन्यथा
अटल पूर्णांक marvell_of_reg_init(काष्ठा phy_device *phydev)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_OF_MDIO */

अटल पूर्णांक m88e1121_config_aneg_rgmii_delays(काष्ठा phy_device *phydev)
अणु
	पूर्णांक mscr;

	अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_ID)
		mscr = MII_88E1121_PHY_MSCR_RX_DELAY |
		       MII_88E1121_PHY_MSCR_TX_DELAY;
	अन्यथा अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_RXID)
		mscr = MII_88E1121_PHY_MSCR_RX_DELAY;
	अन्यथा अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_TXID)
		mscr = MII_88E1121_PHY_MSCR_TX_DELAY;
	अन्यथा
		mscr = 0;

	वापस phy_modअगरy_paged(phydev, MII_MARVELL_MSCR_PAGE,
				MII_88E1121_PHY_MSCR_REG,
				MII_88E1121_PHY_MSCR_DELAY_MASK, mscr);
पूर्ण

अटल पूर्णांक m88e1121_config_aneg(काष्ठा phy_device *phydev)
अणु
	पूर्णांक changed = 0;
	पूर्णांक err = 0;

	अगर (phy_पूर्णांकerface_is_rgmii(phydev)) अणु
		err = m88e1121_config_aneg_rgmii_delays(phydev);
		अगर (err < 0)
			वापस err;
	पूर्ण

	err = marvell_set_polarity(phydev, phydev->mdix_ctrl);
	अगर (err < 0)
		वापस err;

	changed = err;

	err = genphy_config_aneg(phydev);
	अगर (err < 0)
		वापस err;

	अगर (phydev->स्वतःneg != AUTONEG_ENABLE || changed) अणु
		/* A software reset is used to ensure a "commit" of the
		 * changes is करोne.
		 */
		err = genphy_soft_reset(phydev);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक m88e1318_config_aneg(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	err = phy_modअगरy_paged(phydev, MII_MARVELL_MSCR_PAGE,
			       MII_88E1318S_PHY_MSCR1_REG,
			       0, MII_88E1318S_PHY_MSCR1_PAD_ODD);
	अगर (err < 0)
		वापस err;

	वापस m88e1121_config_aneg(phydev);
पूर्ण

/**
 * linkmode_adv_to_fiber_adv_t
 * @advertise: the linkmode advertisement settings
 *
 * A small helper function that translates linkmode advertisement
 * settings to phy स्वतःnegotiation advertisements क्रम the MII_ADV
 * रेजिस्टर क्रम fiber link.
 */
अटल अंतरभूत u32 linkmode_adv_to_fiber_adv_t(अचिन्हित दीर्घ *advertise)
अणु
	u32 result = 0;

	अगर (linkmode_test_bit(ETHTOOL_LINK_MODE_1000baseT_Half_BIT, advertise))
		result |= ADVERTISE_1000XHALF;
	अगर (linkmode_test_bit(ETHTOOL_LINK_MODE_1000baseT_Full_BIT, advertise))
		result |= ADVERTISE_1000XFULL;

	अगर (linkmode_test_bit(ETHTOOL_LINK_MODE_Asym_Pause_BIT, advertise) &&
	    linkmode_test_bit(ETHTOOL_LINK_MODE_Pause_BIT, advertise))
		result |= ADVERTISE_1000XPSE_ASYM;
	अन्यथा अगर (linkmode_test_bit(ETHTOOL_LINK_MODE_Pause_BIT, advertise))
		result |= ADVERTISE_1000XPAUSE;

	वापस result;
पूर्ण

/**
 * marvell_config_aneg_fiber - restart स्वतः-negotiation or ग_लिखो BMCR
 * @phydev: target phy_device काष्ठा
 *
 * Description: If स्वतः-negotiation is enabled, we configure the
 *   advertising, and then restart स्वतः-negotiation.  If it is not
 *   enabled, then we ग_लिखो the BMCR. Adapted क्रम fiber link in
 *   some Marvell's devices.
 */
अटल पूर्णांक marvell_config_aneg_fiber(काष्ठा phy_device *phydev)
अणु
	पूर्णांक changed = 0;
	पूर्णांक err;
	u16 adv;

	अगर (phydev->स्वतःneg != AUTONEG_ENABLE)
		वापस genphy_setup_क्रमced(phydev);

	/* Only allow advertising what this PHY supports */
	linkmode_and(phydev->advertising, phydev->advertising,
		     phydev->supported);

	adv = linkmode_adv_to_fiber_adv_t(phydev->advertising);

	/* Setup fiber advertisement */
	err = phy_modअगरy_changed(phydev, MII_ADVERTISE,
				 ADVERTISE_1000XHALF | ADVERTISE_1000XFULL |
				 ADVERTISE_1000XPAUSE | ADVERTISE_1000XPSE_ASYM,
				 adv);
	अगर (err < 0)
		वापस err;
	अगर (err > 0)
		changed = 1;

	वापस genphy_check_and_restart_aneg(phydev, changed);
पूर्ण

अटल पूर्णांक m88e1111_config_aneg(काष्ठा phy_device *phydev)
अणु
	पूर्णांक extsr = phy_पढ़ो(phydev, MII_M1111_PHY_EXT_SR);
	पूर्णांक err;

	अगर (extsr < 0)
		वापस extsr;

	/* If not using SGMII or copper 1000BaseX modes, use normal process.
	 * Steps below are only required क्रम these modes.
	 */
	अगर (phydev->पूर्णांकerface != PHY_INTERFACE_MODE_SGMII &&
	    (extsr & MII_M1111_HWCFG_MODE_MASK) !=
	    MII_M1111_HWCFG_MODE_COPPER_1000X_AN)
		वापस marvell_config_aneg(phydev);

	err = marvell_set_page(phydev, MII_MARVELL_COPPER_PAGE);
	अगर (err < 0)
		जाओ error;

	/* Configure the copper link first */
	err = marvell_config_aneg(phydev);
	अगर (err < 0)
		जाओ error;

	/* Then the fiber link */
	err = marvell_set_page(phydev, MII_MARVELL_FIBER_PAGE);
	अगर (err < 0)
		जाओ error;

	अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_SGMII)
		/* Do not touch the fiber advertisement अगर we're in copper->sgmii mode.
		 * Just ensure that SGMII-side स्वतःnegotiation is enabled.
		 * If we चयनed from some other mode to SGMII it may not be.
		 */
		err = genphy_check_and_restart_aneg(phydev, false);
	अन्यथा
		err = marvell_config_aneg_fiber(phydev);
	अगर (err < 0)
		जाओ error;

	वापस marvell_set_page(phydev, MII_MARVELL_COPPER_PAGE);

error:
	marvell_set_page(phydev, MII_MARVELL_COPPER_PAGE);
	वापस err;
पूर्ण

अटल पूर्णांक m88e1510_config_aneg(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	err = marvell_set_page(phydev, MII_MARVELL_COPPER_PAGE);
	अगर (err < 0)
		जाओ error;

	/* Configure the copper link first */
	err = m88e1318_config_aneg(phydev);
	अगर (err < 0)
		जाओ error;

	/* Do not touch the fiber page अगर we're in copper->sgmii mode */
	अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_SGMII)
		वापस 0;

	/* Then the fiber link */
	err = marvell_set_page(phydev, MII_MARVELL_FIBER_PAGE);
	अगर (err < 0)
		जाओ error;

	err = marvell_config_aneg_fiber(phydev);
	अगर (err < 0)
		जाओ error;

	वापस marvell_set_page(phydev, MII_MARVELL_COPPER_PAGE);

error:
	marvell_set_page(phydev, MII_MARVELL_COPPER_PAGE);
	वापस err;
पूर्ण

अटल व्योम marvell_config_led(काष्ठा phy_device *phydev)
अणु
	u16 def_config;
	पूर्णांक err;

	चयन (MARVELL_PHY_FAMILY_ID(phydev->phy_id)) अणु
	/* Default PHY LED config: LED[0] .. Link, LED[1] .. Activity */
	हाल MARVELL_PHY_FAMILY_ID(MARVELL_PHY_ID_88E1121R):
	हाल MARVELL_PHY_FAMILY_ID(MARVELL_PHY_ID_88E1318S):
		def_config = MII_88E1121_PHY_LED_DEF;
		अवरोध;
	/* Default PHY LED config:
	 * LED[0] .. 1000Mbps Link
	 * LED[1] .. 100Mbps Link
	 * LED[2] .. Blink, Activity
	 */
	हाल MARVELL_PHY_FAMILY_ID(MARVELL_PHY_ID_88E1510):
		अगर (phydev->dev_flags & MARVELL_PHY_LED0_LINK_LED1_ACTIVE)
			def_config = MII_88E1510_PHY_LED0_LINK_LED1_ACTIVE;
		अन्यथा
			def_config = MII_88E1510_PHY_LED_DEF;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	err = phy_ग_लिखो_paged(phydev, MII_MARVELL_LED_PAGE, MII_PHY_LED_CTRL,
			      def_config);
	अगर (err < 0)
		phydev_warn(phydev, "Fail to config marvell phy LED.\n");
पूर्ण

अटल पूर्णांक marvell_config_init(काष्ठा phy_device *phydev)
अणु
	/* Set शेष LED */
	marvell_config_led(phydev);

	/* Set रेजिस्टरs from marvell,reg-init DT property */
	वापस marvell_of_reg_init(phydev);
पूर्ण

अटल पूर्णांक m88e3016_config_init(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	/* Enable Scrambler and Auto-Crossover */
	ret = phy_modअगरy(phydev, MII_88E3016_PHY_SPEC_CTRL,
			 MII_88E3016_DISABLE_SCRAMBLER,
			 MII_88E3016_AUTO_MDIX_CROSSOVER);
	अगर (ret < 0)
		वापस ret;

	वापस marvell_config_init(phydev);
पूर्ण

अटल पूर्णांक m88e1111_config_init_hwcfg_mode(काष्ठा phy_device *phydev,
					   u16 mode,
					   पूर्णांक fibre_copper_स्वतः)
अणु
	अगर (fibre_copper_स्वतः)
		mode |= MII_M1111_HWCFG_FIBER_COPPER_AUTO;

	वापस phy_modअगरy(phydev, MII_M1111_PHY_EXT_SR,
			  MII_M1111_HWCFG_MODE_MASK |
			  MII_M1111_HWCFG_FIBER_COPPER_AUTO |
			  MII_M1111_HWCFG_FIBER_COPPER_RES,
			  mode);
पूर्ण

अटल पूर्णांक m88e1111_config_init_rgmii_delays(काष्ठा phy_device *phydev)
अणु
	पूर्णांक delay;

	अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_ID) अणु
		delay = MII_M1111_RGMII_RX_DELAY | MII_M1111_RGMII_TX_DELAY;
	पूर्ण अन्यथा अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_RXID) अणु
		delay = MII_M1111_RGMII_RX_DELAY;
	पूर्ण अन्यथा अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_TXID) अणु
		delay = MII_M1111_RGMII_TX_DELAY;
	पूर्ण अन्यथा अणु
		delay = 0;
	पूर्ण

	वापस phy_modअगरy(phydev, MII_M1111_PHY_EXT_CR,
			  MII_M1111_RGMII_RX_DELAY | MII_M1111_RGMII_TX_DELAY,
			  delay);
पूर्ण

अटल पूर्णांक m88e1111_config_init_rgmii(काष्ठा phy_device *phydev)
अणु
	पूर्णांक temp;
	पूर्णांक err;

	err = m88e1111_config_init_rgmii_delays(phydev);
	अगर (err < 0)
		वापस err;

	temp = phy_पढ़ो(phydev, MII_M1111_PHY_EXT_SR);
	अगर (temp < 0)
		वापस temp;

	temp &= ~(MII_M1111_HWCFG_MODE_MASK);

	अगर (temp & MII_M1111_HWCFG_FIBER_COPPER_RES)
		temp |= MII_M1111_HWCFG_MODE_FIBER_RGMII;
	अन्यथा
		temp |= MII_M1111_HWCFG_MODE_COPPER_RGMII;

	वापस phy_ग_लिखो(phydev, MII_M1111_PHY_EXT_SR, temp);
पूर्ण

अटल पूर्णांक m88e1111_config_init_sgmii(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	err = m88e1111_config_init_hwcfg_mode(
		phydev,
		MII_M1111_HWCFG_MODE_SGMII_NO_CLK,
		MII_M1111_HWCFG_FIBER_COPPER_AUTO);
	अगर (err < 0)
		वापस err;

	/* make sure copper is selected */
	वापस marvell_set_page(phydev, MII_MARVELL_COPPER_PAGE);
पूर्ण

अटल पूर्णांक m88e1111_config_init_rtbi(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	err = m88e1111_config_init_rgmii_delays(phydev);
	अगर (err < 0)
		वापस err;

	err = m88e1111_config_init_hwcfg_mode(
		phydev,
		MII_M1111_HWCFG_MODE_RTBI,
		MII_M1111_HWCFG_FIBER_COPPER_AUTO);
	अगर (err < 0)
		वापस err;

	/* soft reset */
	err = genphy_soft_reset(phydev);
	अगर (err < 0)
		वापस err;

	वापस m88e1111_config_init_hwcfg_mode(
		phydev,
		MII_M1111_HWCFG_MODE_RTBI,
		MII_M1111_HWCFG_FIBER_COPPER_AUTO);
पूर्ण

अटल पूर्णांक m88e1111_config_init_1000basex(काष्ठा phy_device *phydev)
अणु
	पूर्णांक extsr = phy_पढ़ो(phydev, MII_M1111_PHY_EXT_SR);
	पूर्णांक err, mode;

	अगर (extsr < 0)
		वापस extsr;

	/* If using copper mode, ensure 1000BaseX स्वतः-negotiation is enabled */
	mode = extsr & MII_M1111_HWCFG_MODE_MASK;
	अगर (mode == MII_M1111_HWCFG_MODE_COPPER_1000X_NOAN) अणु
		err = phy_modअगरy(phydev, MII_M1111_PHY_EXT_SR,
				 MII_M1111_HWCFG_MODE_MASK |
				 MII_M1111_HWCFG_SERIAL_AN_BYPASS,
				 MII_M1111_HWCFG_MODE_COPPER_1000X_AN |
				 MII_M1111_HWCFG_SERIAL_AN_BYPASS);
		अगर (err < 0)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक m88e1111_config_init(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	अगर (phy_पूर्णांकerface_is_rgmii(phydev)) अणु
		err = m88e1111_config_init_rgmii(phydev);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_SGMII) अणु
		err = m88e1111_config_init_sgmii(phydev);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RTBI) अणु
		err = m88e1111_config_init_rtbi(phydev);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_1000BASEX) अणु
		err = m88e1111_config_init_1000basex(phydev);
		अगर (err < 0)
			वापस err;
	पूर्ण

	err = marvell_of_reg_init(phydev);
	अगर (err < 0)
		वापस err;

	वापस genphy_soft_reset(phydev);
पूर्ण

अटल पूर्णांक m88e1111_get_करोwnshअगरt(काष्ठा phy_device *phydev, u8 *data)
अणु
	पूर्णांक val, cnt, enable;

	val = phy_पढ़ो(phydev, MII_M1111_PHY_EXT_CR);
	अगर (val < 0)
		वापस val;

	enable = FIELD_GET(MII_M1111_PHY_EXT_CR_DOWNSHIFT_EN, val);
	cnt = FIELD_GET(MII_M1111_PHY_EXT_CR_DOWNSHIFT_MASK, val) + 1;

	*data = enable ? cnt : DOWNSHIFT_DEV_DISABLE;

	वापस 0;
पूर्ण

अटल पूर्णांक m88e1111_set_करोwnshअगरt(काष्ठा phy_device *phydev, u8 cnt)
अणु
	पूर्णांक val, err;

	अगर (cnt > MII_M1111_PHY_EXT_CR_DOWNSHIFT_MAX)
		वापस -E2BIG;

	अगर (!cnt) अणु
		err = phy_clear_bits(phydev, MII_M1111_PHY_EXT_CR,
				     MII_M1111_PHY_EXT_CR_DOWNSHIFT_EN);
	पूर्ण अन्यथा अणु
		val = MII_M1111_PHY_EXT_CR_DOWNSHIFT_EN;
		val |= FIELD_PREP(MII_M1111_PHY_EXT_CR_DOWNSHIFT_MASK, cnt - 1);

		err = phy_modअगरy(phydev, MII_M1111_PHY_EXT_CR,
				 MII_M1111_PHY_EXT_CR_DOWNSHIFT_EN |
				 MII_M1111_PHY_EXT_CR_DOWNSHIFT_MASK,
				 val);
	पूर्ण

	अगर (err < 0)
		वापस err;

	वापस genphy_soft_reset(phydev);
पूर्ण

अटल पूर्णांक m88e1111_get_tunable(काष्ठा phy_device *phydev,
				काष्ठा ethtool_tunable *tuna, व्योम *data)
अणु
	चयन (tuna->id) अणु
	हाल ETHTOOL_PHY_DOWNSHIFT:
		वापस m88e1111_get_करोwnshअगरt(phydev, data);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक m88e1111_set_tunable(काष्ठा phy_device *phydev,
				काष्ठा ethtool_tunable *tuna, स्थिर व्योम *data)
अणु
	चयन (tuna->id) अणु
	हाल ETHTOOL_PHY_DOWNSHIFT:
		वापस m88e1111_set_करोwnshअगरt(phydev, *(स्थिर u8 *)data);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक m88e1011_get_करोwnshअगरt(काष्ठा phy_device *phydev, u8 *data)
अणु
	पूर्णांक val, cnt, enable;

	val = phy_पढ़ो(phydev, MII_M1011_PHY_SCR);
	अगर (val < 0)
		वापस val;

	enable = FIELD_GET(MII_M1011_PHY_SCR_DOWNSHIFT_EN, val);
	cnt = FIELD_GET(MII_M1011_PHY_SCR_DOWNSHIFT_MASK, val) + 1;

	*data = enable ? cnt : DOWNSHIFT_DEV_DISABLE;

	वापस 0;
पूर्ण

अटल पूर्णांक m88e1011_set_करोwnshअगरt(काष्ठा phy_device *phydev, u8 cnt)
अणु
	पूर्णांक val, err;

	अगर (cnt > MII_M1011_PHY_SCR_DOWNSHIFT_MAX)
		वापस -E2BIG;

	अगर (!cnt) अणु
		err = phy_clear_bits(phydev, MII_M1011_PHY_SCR,
				     MII_M1011_PHY_SCR_DOWNSHIFT_EN);
	पूर्ण अन्यथा अणु
		val = MII_M1011_PHY_SCR_DOWNSHIFT_EN;
		val |= FIELD_PREP(MII_M1011_PHY_SCR_DOWNSHIFT_MASK, cnt - 1);

		err = phy_modअगरy(phydev, MII_M1011_PHY_SCR,
				 MII_M1011_PHY_SCR_DOWNSHIFT_EN |
				 MII_M1011_PHY_SCR_DOWNSHIFT_MASK,
				 val);
	पूर्ण

	अगर (err < 0)
		वापस err;

	वापस genphy_soft_reset(phydev);
पूर्ण

अटल पूर्णांक m88e1011_get_tunable(काष्ठा phy_device *phydev,
				काष्ठा ethtool_tunable *tuna, व्योम *data)
अणु
	चयन (tuna->id) अणु
	हाल ETHTOOL_PHY_DOWNSHIFT:
		वापस m88e1011_get_करोwnshअगरt(phydev, data);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक m88e1011_set_tunable(काष्ठा phy_device *phydev,
				काष्ठा ethtool_tunable *tuna, स्थिर व्योम *data)
अणु
	चयन (tuna->id) अणु
	हाल ETHTOOL_PHY_DOWNSHIFT:
		वापस m88e1011_set_करोwnshअगरt(phydev, *(स्थिर u8 *)data);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक m88e1112_config_init(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	err = m88e1011_set_करोwnshअगरt(phydev, 3);
	अगर (err < 0)
		वापस err;

	वापस m88e1111_config_init(phydev);
पूर्ण

अटल पूर्णांक m88e1111gbe_config_init(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	err = m88e1111_set_करोwnshअगरt(phydev, 3);
	अगर (err < 0)
		वापस err;

	वापस m88e1111_config_init(phydev);
पूर्ण

अटल पूर्णांक marvell_1011gbe_config_init(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	err = m88e1011_set_करोwnshअगरt(phydev, 3);
	अगर (err < 0)
		वापस err;

	वापस marvell_config_init(phydev);
पूर्ण
अटल पूर्णांक m88e1116r_config_init(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	err = genphy_soft_reset(phydev);
	अगर (err < 0)
		वापस err;

	msleep(500);

	err = marvell_set_page(phydev, MII_MARVELL_COPPER_PAGE);
	अगर (err < 0)
		वापस err;

	err = marvell_set_polarity(phydev, phydev->mdix_ctrl);
	अगर (err < 0)
		वापस err;

	err = m88e1011_set_करोwnshअगरt(phydev, 8);
	अगर (err < 0)
		वापस err;

	अगर (phy_पूर्णांकerface_is_rgmii(phydev)) अणु
		err = m88e1121_config_aneg_rgmii_delays(phydev);
		अगर (err < 0)
			वापस err;
	पूर्ण

	err = genphy_soft_reset(phydev);
	अगर (err < 0)
		वापस err;

	वापस marvell_config_init(phydev);
पूर्ण

अटल पूर्णांक m88e1318_config_init(काष्ठा phy_device *phydev)
अणु
	अगर (phy_पूर्णांकerrupt_is_valid(phydev)) अणु
		पूर्णांक err = phy_modअगरy_paged(
			phydev, MII_MARVELL_LED_PAGE,
			MII_88E1318S_PHY_LED_TCR,
			MII_88E1318S_PHY_LED_TCR_FORCE_INT,
			MII_88E1318S_PHY_LED_TCR_INTn_ENABLE |
			MII_88E1318S_PHY_LED_TCR_INT_ACTIVE_LOW);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस marvell_config_init(phydev);
पूर्ण

अटल पूर्णांक m88e1510_config_init(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	/* SGMII-to-Copper mode initialization */
	अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_SGMII) अणु
		/* Select page 18 */
		err = marvell_set_page(phydev, 18);
		अगर (err < 0)
			वापस err;

		/* In reg 20, ग_लिखो MODE[2:0] = 0x1 (SGMII to Copper) */
		err = phy_modअगरy(phydev, MII_88E1510_GEN_CTRL_REG_1,
				 MII_88E1510_GEN_CTRL_REG_1_MODE_MASK,
				 MII_88E1510_GEN_CTRL_REG_1_MODE_SGMII);
		अगर (err < 0)
			वापस err;

		/* PHY reset is necessary after changing MODE[2:0] */
		err = phy_set_bits(phydev, MII_88E1510_GEN_CTRL_REG_1,
				   MII_88E1510_GEN_CTRL_REG_1_RESET);
		अगर (err < 0)
			वापस err;

		/* Reset page selection */
		err = marvell_set_page(phydev, MII_MARVELL_COPPER_PAGE);
		अगर (err < 0)
			वापस err;
	पूर्ण
	err = m88e1011_set_करोwnshअगरt(phydev, 3);
	अगर (err < 0)
		वापस err;

	वापस m88e1318_config_init(phydev);
पूर्ण

अटल पूर्णांक m88e1118_config_aneg(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	err = genphy_soft_reset(phydev);
	अगर (err < 0)
		वापस err;

	err = marvell_set_polarity(phydev, phydev->mdix_ctrl);
	अगर (err < 0)
		वापस err;

	err = genphy_config_aneg(phydev);
	वापस 0;
पूर्ण

अटल पूर्णांक m88e1118_config_init(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	/* Change address */
	err = marvell_set_page(phydev, MII_MARVELL_MSCR_PAGE);
	अगर (err < 0)
		वापस err;

	/* Enable 1000 Mbit */
	err = phy_ग_लिखो(phydev, 0x15, 0x1070);
	अगर (err < 0)
		वापस err;

	/* Change address */
	err = marvell_set_page(phydev, MII_MARVELL_LED_PAGE);
	अगर (err < 0)
		वापस err;

	/* Adjust LED Control */
	अगर (phydev->dev_flags & MARVELL_PHY_M1118_DNS323_LEDS)
		err = phy_ग_लिखो(phydev, 0x10, 0x1100);
	अन्यथा
		err = phy_ग_लिखो(phydev, 0x10, 0x021e);
	अगर (err < 0)
		वापस err;

	err = marvell_of_reg_init(phydev);
	अगर (err < 0)
		वापस err;

	/* Reset address */
	err = marvell_set_page(phydev, MII_MARVELL_COPPER_PAGE);
	अगर (err < 0)
		वापस err;

	वापस genphy_soft_reset(phydev);
पूर्ण

अटल पूर्णांक m88e1149_config_init(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	/* Change address */
	err = marvell_set_page(phydev, MII_MARVELL_MSCR_PAGE);
	अगर (err < 0)
		वापस err;

	/* Enable 1000 Mbit */
	err = phy_ग_लिखो(phydev, 0x15, 0x1048);
	अगर (err < 0)
		वापस err;

	err = marvell_of_reg_init(phydev);
	अगर (err < 0)
		वापस err;

	/* Reset address */
	err = marvell_set_page(phydev, MII_MARVELL_COPPER_PAGE);
	अगर (err < 0)
		वापस err;

	वापस genphy_soft_reset(phydev);
पूर्ण

अटल पूर्णांक m88e1145_config_init_rgmii(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	err = m88e1111_config_init_rgmii_delays(phydev);
	अगर (err < 0)
		वापस err;

	अगर (phydev->dev_flags & MARVELL_PHY_M1145_FLAGS_RESISTANCE) अणु
		err = phy_ग_लिखो(phydev, 0x1d, 0x0012);
		अगर (err < 0)
			वापस err;

		err = phy_modअगरy(phydev, 0x1e, 0x0fc0,
				 2 << 9 | /* 36 ohm */
				 2 << 6); /* 39 ohm */
		अगर (err < 0)
			वापस err;

		err = phy_ग_लिखो(phydev, 0x1d, 0x3);
		अगर (err < 0)
			वापस err;

		err = phy_ग_लिखो(phydev, 0x1e, 0x8000);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक m88e1145_config_init_sgmii(काष्ठा phy_device *phydev)
अणु
	वापस m88e1111_config_init_hwcfg_mode(
		phydev, MII_M1111_HWCFG_MODE_SGMII_NO_CLK,
		MII_M1111_HWCFG_FIBER_COPPER_AUTO);
पूर्ण

अटल पूर्णांक m88e1145_config_init(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	/* Take care of errata E0 & E1 */
	err = phy_ग_लिखो(phydev, 0x1d, 0x001b);
	अगर (err < 0)
		वापस err;

	err = phy_ग_लिखो(phydev, 0x1e, 0x418f);
	अगर (err < 0)
		वापस err;

	err = phy_ग_लिखो(phydev, 0x1d, 0x0016);
	अगर (err < 0)
		वापस err;

	err = phy_ग_लिखो(phydev, 0x1e, 0xa2da);
	अगर (err < 0)
		वापस err;

	अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_ID) अणु
		err = m88e1145_config_init_rgmii(phydev);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_SGMII) अणु
		err = m88e1145_config_init_sgmii(phydev);
		अगर (err < 0)
			वापस err;
	पूर्ण
	err = m88e1111_set_करोwnshअगरt(phydev, 3);
	अगर (err < 0)
		वापस err;

	err = marvell_of_reg_init(phydev);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक m88e1540_get_fld(काष्ठा phy_device *phydev, u8 *msecs)
अणु
	पूर्णांक val;

	val = phy_पढ़ो(phydev, MII_88E1540_COPPER_CTRL3);
	अगर (val < 0)
		वापस val;

	अगर (!(val & MII_88E1540_COPPER_CTRL3_FAST_LINK_DOWN)) अणु
		*msecs = ETHTOOL_PHY_FAST_LINK_DOWN_OFF;
		वापस 0;
	पूर्ण

	val = FIELD_GET(MII_88E1540_COPPER_CTRL3_LINK_DOWN_DELAY_MASK, val);

	चयन (val) अणु
	हाल MII_88E1540_COPPER_CTRL3_LINK_DOWN_DELAY_00MS:
		*msecs = 0;
		अवरोध;
	हाल MII_88E1540_COPPER_CTRL3_LINK_DOWN_DELAY_10MS:
		*msecs = 10;
		अवरोध;
	हाल MII_88E1540_COPPER_CTRL3_LINK_DOWN_DELAY_20MS:
		*msecs = 20;
		अवरोध;
	हाल MII_88E1540_COPPER_CTRL3_LINK_DOWN_DELAY_40MS:
		*msecs = 40;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक m88e1540_set_fld(काष्ठा phy_device *phydev, स्थिर u8 *msecs)
अणु
	काष्ठा ethtool_eee eee;
	पूर्णांक val, ret;

	अगर (*msecs == ETHTOOL_PHY_FAST_LINK_DOWN_OFF)
		वापस phy_clear_bits(phydev, MII_88E1540_COPPER_CTRL3,
				      MII_88E1540_COPPER_CTRL3_FAST_LINK_DOWN);

	/* According to the Marvell data sheet EEE must be disabled क्रम
	 * Fast Link Down detection to work properly
	 */
	ret = phy_ethtool_get_eee(phydev, &eee);
	अगर (!ret && eee.eee_enabled) अणु
		phydev_warn(phydev, "Fast Link Down detection requires EEE to be disabled!\n");
		वापस -EBUSY;
	पूर्ण

	अगर (*msecs <= 5)
		val = MII_88E1540_COPPER_CTRL3_LINK_DOWN_DELAY_00MS;
	अन्यथा अगर (*msecs <= 15)
		val = MII_88E1540_COPPER_CTRL3_LINK_DOWN_DELAY_10MS;
	अन्यथा अगर (*msecs <= 30)
		val = MII_88E1540_COPPER_CTRL3_LINK_DOWN_DELAY_20MS;
	अन्यथा
		val = MII_88E1540_COPPER_CTRL3_LINK_DOWN_DELAY_40MS;

	val = FIELD_PREP(MII_88E1540_COPPER_CTRL3_LINK_DOWN_DELAY_MASK, val);

	ret = phy_modअगरy(phydev, MII_88E1540_COPPER_CTRL3,
			 MII_88E1540_COPPER_CTRL3_LINK_DOWN_DELAY_MASK, val);
	अगर (ret)
		वापस ret;

	वापस phy_set_bits(phydev, MII_88E1540_COPPER_CTRL3,
			    MII_88E1540_COPPER_CTRL3_FAST_LINK_DOWN);
पूर्ण

अटल पूर्णांक m88e1540_get_tunable(काष्ठा phy_device *phydev,
				काष्ठा ethtool_tunable *tuna, व्योम *data)
अणु
	चयन (tuna->id) अणु
	हाल ETHTOOL_PHY_FAST_LINK_DOWN:
		वापस m88e1540_get_fld(phydev, data);
	हाल ETHTOOL_PHY_DOWNSHIFT:
		वापस m88e1011_get_करोwnshअगरt(phydev, data);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक m88e1540_set_tunable(काष्ठा phy_device *phydev,
				काष्ठा ethtool_tunable *tuna, स्थिर व्योम *data)
अणु
	चयन (tuna->id) अणु
	हाल ETHTOOL_PHY_FAST_LINK_DOWN:
		वापस m88e1540_set_fld(phydev, data);
	हाल ETHTOOL_PHY_DOWNSHIFT:
		वापस m88e1011_set_करोwnshअगरt(phydev, *(स्थिर u8 *)data);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

/* The VOD can be out of specअगरication on link up. Poke an
 * unकरोcumented रेजिस्टर, in an unकरोcumented page, with a magic value
 * to fix this.
 */
अटल पूर्णांक m88e6390_errata(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	err = phy_ग_लिखो(phydev, MII_BMCR,
			BMCR_ANENABLE | BMCR_SPEED1000 | BMCR_FULLDPLX);
	अगर (err)
		वापस err;

	usleep_range(300, 400);

	err = phy_ग_लिखो_paged(phydev, 0xf8, 0x08, 0x36);
	अगर (err)
		वापस err;

	वापस genphy_soft_reset(phydev);
पूर्ण

अटल पूर्णांक m88e6390_config_aneg(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	err = m88e6390_errata(phydev);
	अगर (err)
		वापस err;

	वापस m88e1510_config_aneg(phydev);
पूर्ण

/**
 * fiber_lpa_mod_linkmode_lpa_t
 * @advertising: the linkmode advertisement settings
 * @lpa: value of the MII_LPA रेजिस्टर क्रम fiber link
 *
 * A small helper function that translates MII_LPA bits to linkmode LP
 * advertisement settings. Other bits in advertising are left
 * unchanged.
 */
अटल व्योम fiber_lpa_mod_linkmode_lpa_t(अचिन्हित दीर्घ *advertising, u32 lpa)
अणु
	linkmode_mod_bit(ETHTOOL_LINK_MODE_1000baseT_Half_BIT,
			 advertising, lpa & LPA_1000XHALF);

	linkmode_mod_bit(ETHTOOL_LINK_MODE_1000baseT_Full_BIT,
			 advertising, lpa & LPA_1000XFULL);
पूर्ण

अटल पूर्णांक marvell_पढ़ो_status_page_an(काष्ठा phy_device *phydev,
				       पूर्णांक fiber, पूर्णांक status)
अणु
	पूर्णांक lpa;
	पूर्णांक err;

	अगर (!(status & MII_M1011_PHY_STATUS_RESOLVED)) अणु
		phydev->link = 0;
		वापस 0;
	पूर्ण

	अगर (status & MII_M1011_PHY_STATUS_FULLDUPLEX)
		phydev->duplex = DUPLEX_FULL;
	अन्यथा
		phydev->duplex = DUPLEX_HALF;

	चयन (status & MII_M1011_PHY_STATUS_SPD_MASK) अणु
	हाल MII_M1011_PHY_STATUS_1000:
		phydev->speed = SPEED_1000;
		अवरोध;

	हाल MII_M1011_PHY_STATUS_100:
		phydev->speed = SPEED_100;
		अवरोध;

	शेष:
		phydev->speed = SPEED_10;
		अवरोध;
	पूर्ण

	अगर (!fiber) अणु
		err = genphy_पढ़ो_lpa(phydev);
		अगर (err < 0)
			वापस err;

		phy_resolve_aneg_छोड़ो(phydev);
	पूर्ण अन्यथा अणु
		lpa = phy_पढ़ो(phydev, MII_LPA);
		अगर (lpa < 0)
			वापस lpa;

		/* The fiber link is only 1000M capable */
		fiber_lpa_mod_linkmode_lpa_t(phydev->lp_advertising, lpa);

		अगर (phydev->duplex == DUPLEX_FULL) अणु
			अगर (!(lpa & LPA_PAUSE_FIBER)) अणु
				phydev->छोड़ो = 0;
				phydev->asym_छोड़ो = 0;
			पूर्ण अन्यथा अगर ((lpa & LPA_PAUSE_ASYM_FIBER)) अणु
				phydev->छोड़ो = 1;
				phydev->asym_छोड़ो = 1;
			पूर्ण अन्यथा अणु
				phydev->छोड़ो = 1;
				phydev->asym_छोड़ो = 0;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* marvell_पढ़ो_status_page
 *
 * Description:
 *   Check the link, then figure out the current state
 *   by comparing what we advertise with what the link partner
 *   advertises.  Start by checking the gigabit possibilities,
 *   then move on to 10/100.
 */
अटल पूर्णांक marvell_पढ़ो_status_page(काष्ठा phy_device *phydev, पूर्णांक page)
अणु
	पूर्णांक status;
	पूर्णांक fiber;
	पूर्णांक err;

	status = phy_पढ़ो(phydev, MII_M1011_PHY_STATUS);
	अगर (status < 0)
		वापस status;

	/* Use the generic रेजिस्टर क्रम copper link status,
	 * and the PHY status रेजिस्टर क्रम fiber link status.
	 */
	अगर (page == MII_MARVELL_FIBER_PAGE) अणु
		phydev->link = !!(status & MII_M1011_PHY_STATUS_LINK);
	पूर्ण अन्यथा अणु
		err = genphy_update_link(phydev);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (page == MII_MARVELL_FIBER_PAGE)
		fiber = 1;
	अन्यथा
		fiber = 0;

	linkmode_zero(phydev->lp_advertising);
	phydev->छोड़ो = 0;
	phydev->asym_छोड़ो = 0;
	phydev->speed = SPEED_UNKNOWN;
	phydev->duplex = DUPLEX_UNKNOWN;
	phydev->port = fiber ? PORT_FIBRE : PORT_TP;

	अगर (phydev->स्वतःneg == AUTONEG_ENABLE)
		err = marvell_पढ़ो_status_page_an(phydev, fiber, status);
	अन्यथा
		err = genphy_पढ़ो_status_fixed(phydev);

	वापस err;
पूर्ण

/* marvell_पढ़ो_status
 *
 * Some Marvell's phys have two modes: fiber and copper.
 * Both need status checked.
 * Description:
 *   First, check the fiber link and status.
 *   If the fiber link is करोwn, check the copper link and status which
 *   will be the शेष value अगर both link are करोwn.
 */
अटल पूर्णांक marvell_पढ़ो_status(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	/* Check the fiber mode first */
	अगर (linkmode_test_bit(ETHTOOL_LINK_MODE_FIBRE_BIT,
			      phydev->supported) &&
	    phydev->पूर्णांकerface != PHY_INTERFACE_MODE_SGMII) अणु
		err = marvell_set_page(phydev, MII_MARVELL_FIBER_PAGE);
		अगर (err < 0)
			जाओ error;

		err = marvell_पढ़ो_status_page(phydev, MII_MARVELL_FIBER_PAGE);
		अगर (err < 0)
			जाओ error;

		/* If the fiber link is up, it is the selected and
		 * used link. In this हाल, we need to stay in the
		 * fiber page. Please to be careful about that, aव्योम
		 * to restore Copper page in other functions which
		 * could अवरोध the behaviour क्रम some fiber phy like
		 * 88E1512.
		 */
		अगर (phydev->link)
			वापस 0;

		/* If fiber link is करोwn, check and save copper mode state */
		err = marvell_set_page(phydev, MII_MARVELL_COPPER_PAGE);
		अगर (err < 0)
			जाओ error;
	पूर्ण

	वापस marvell_पढ़ो_status_page(phydev, MII_MARVELL_COPPER_PAGE);

error:
	marvell_set_page(phydev, MII_MARVELL_COPPER_PAGE);
	वापस err;
पूर्ण

/* marvell_suspend
 *
 * Some Marvell's phys have two modes: fiber and copper.
 * Both need to be suspended
 */
अटल पूर्णांक marvell_suspend(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	/* Suspend the fiber mode first */
	अगर (!linkmode_test_bit(ETHTOOL_LINK_MODE_FIBRE_BIT,
			       phydev->supported)) अणु
		err = marvell_set_page(phydev, MII_MARVELL_FIBER_PAGE);
		अगर (err < 0)
			जाओ error;

		/* With the page set, use the generic suspend */
		err = genphy_suspend(phydev);
		अगर (err < 0)
			जाओ error;

		/* Then, the copper link */
		err = marvell_set_page(phydev, MII_MARVELL_COPPER_PAGE);
		अगर (err < 0)
			जाओ error;
	पूर्ण

	/* With the page set, use the generic suspend */
	वापस genphy_suspend(phydev);

error:
	marvell_set_page(phydev, MII_MARVELL_COPPER_PAGE);
	वापस err;
पूर्ण

/* marvell_resume
 *
 * Some Marvell's phys have two modes: fiber and copper.
 * Both need to be resumed
 */
अटल पूर्णांक marvell_resume(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	/* Resume the fiber mode first */
	अगर (!linkmode_test_bit(ETHTOOL_LINK_MODE_FIBRE_BIT,
			       phydev->supported)) अणु
		err = marvell_set_page(phydev, MII_MARVELL_FIBER_PAGE);
		अगर (err < 0)
			जाओ error;

		/* With the page set, use the generic resume */
		err = genphy_resume(phydev);
		अगर (err < 0)
			जाओ error;

		/* Then, the copper link */
		err = marvell_set_page(phydev, MII_MARVELL_COPPER_PAGE);
		अगर (err < 0)
			जाओ error;
	पूर्ण

	/* With the page set, use the generic resume */
	वापस genphy_resume(phydev);

error:
	marvell_set_page(phydev, MII_MARVELL_COPPER_PAGE);
	वापस err;
पूर्ण

अटल पूर्णांक marvell_aneg_करोne(काष्ठा phy_device *phydev)
अणु
	पूर्णांक retval = phy_पढ़ो(phydev, MII_M1011_PHY_STATUS);

	वापस (retval < 0) ? retval : (retval & MII_M1011_PHY_STATUS_RESOLVED);
पूर्ण

अटल व्योम m88e1318_get_wol(काष्ठा phy_device *phydev,
			     काष्ठा ethtool_wolinfo *wol)
अणु
	पूर्णांक ret;

	wol->supported = WAKE_MAGIC;
	wol->wolopts = 0;

	ret = phy_पढ़ो_paged(phydev, MII_MARVELL_WOL_PAGE,
			     MII_88E1318S_PHY_WOL_CTRL);
	अगर (ret >= 0 && ret & MII_88E1318S_PHY_WOL_CTRL_MAGIC_PACKET_MATCH_ENABLE)
		wol->wolopts |= WAKE_MAGIC;
पूर्ण

अटल पूर्णांक m88e1318_set_wol(काष्ठा phy_device *phydev,
			    काष्ठा ethtool_wolinfo *wol)
अणु
	पूर्णांक err = 0, oldpage;

	oldpage = phy_save_page(phydev);
	अगर (oldpage < 0)
		जाओ error;

	अगर (wol->wolopts & WAKE_MAGIC) अणु
		/* Explicitly चयन to page 0x00, just to be sure */
		err = marvell_ग_लिखो_page(phydev, MII_MARVELL_COPPER_PAGE);
		अगर (err < 0)
			जाओ error;

		/* If WOL event happened once, the LED[2] पूर्णांकerrupt pin
		 * will not be cleared unless we पढ़ोing the पूर्णांकerrupt status
		 * रेजिस्टर. If पूर्णांकerrupts are in use, the normal पूर्णांकerrupt
		 * handling will clear the WOL event. Clear the WOL event
		 * beक्रमe enabling it अगर !phy_पूर्णांकerrupt_is_valid()
		 */
		अगर (!phy_पूर्णांकerrupt_is_valid(phydev))
			__phy_पढ़ो(phydev, MII_M1011_IEVENT);

		/* Enable the WOL पूर्णांकerrupt */
		err = __phy_set_bits(phydev, MII_88E1318S_PHY_CSIER,
				     MII_88E1318S_PHY_CSIER_WOL_EIE);
		अगर (err < 0)
			जाओ error;

		err = marvell_ग_लिखो_page(phydev, MII_MARVELL_LED_PAGE);
		अगर (err < 0)
			जाओ error;

		/* Setup LED[2] as पूर्णांकerrupt pin (active low) */
		err = __phy_modअगरy(phydev, MII_88E1318S_PHY_LED_TCR,
				   MII_88E1318S_PHY_LED_TCR_FORCE_INT,
				   MII_88E1318S_PHY_LED_TCR_INTn_ENABLE |
				   MII_88E1318S_PHY_LED_TCR_INT_ACTIVE_LOW);
		अगर (err < 0)
			जाओ error;

		err = marvell_ग_लिखो_page(phydev, MII_MARVELL_WOL_PAGE);
		अगर (err < 0)
			जाओ error;

		/* Store the device address क्रम the magic packet */
		err = __phy_ग_लिखो(phydev, MII_88E1318S_PHY_MAGIC_PACKET_WORD2,
				((phydev->attached_dev->dev_addr[5] << 8) |
				 phydev->attached_dev->dev_addr[4]));
		अगर (err < 0)
			जाओ error;
		err = __phy_ग_लिखो(phydev, MII_88E1318S_PHY_MAGIC_PACKET_WORD1,
				((phydev->attached_dev->dev_addr[3] << 8) |
				 phydev->attached_dev->dev_addr[2]));
		अगर (err < 0)
			जाओ error;
		err = __phy_ग_लिखो(phydev, MII_88E1318S_PHY_MAGIC_PACKET_WORD0,
				((phydev->attached_dev->dev_addr[1] << 8) |
				 phydev->attached_dev->dev_addr[0]));
		अगर (err < 0)
			जाओ error;

		/* Clear WOL status and enable magic packet matching */
		err = __phy_set_bits(phydev, MII_88E1318S_PHY_WOL_CTRL,
				     MII_88E1318S_PHY_WOL_CTRL_CLEAR_WOL_STATUS |
				     MII_88E1318S_PHY_WOL_CTRL_MAGIC_PACKET_MATCH_ENABLE);
		अगर (err < 0)
			जाओ error;
	पूर्ण अन्यथा अणु
		err = marvell_ग_लिखो_page(phydev, MII_MARVELL_WOL_PAGE);
		अगर (err < 0)
			जाओ error;

		/* Clear WOL status and disable magic packet matching */
		err = __phy_modअगरy(phydev, MII_88E1318S_PHY_WOL_CTRL,
				   MII_88E1318S_PHY_WOL_CTRL_MAGIC_PACKET_MATCH_ENABLE,
				   MII_88E1318S_PHY_WOL_CTRL_CLEAR_WOL_STATUS);
		अगर (err < 0)
			जाओ error;
	पूर्ण

error:
	वापस phy_restore_page(phydev, oldpage, err);
पूर्ण

अटल पूर्णांक marvell_get_sset_count(काष्ठा phy_device *phydev)
अणु
	अगर (linkmode_test_bit(ETHTOOL_LINK_MODE_FIBRE_BIT,
			      phydev->supported))
		वापस ARRAY_SIZE(marvell_hw_stats);
	अन्यथा
		वापस ARRAY_SIZE(marvell_hw_stats) - NB_FIBER_STATS;
पूर्ण

अटल व्योम marvell_get_strings(काष्ठा phy_device *phydev, u8 *data)
अणु
	पूर्णांक count = marvell_get_sset_count(phydev);
	पूर्णांक i;

	क्रम (i = 0; i < count; i++) अणु
		strlcpy(data + i * ETH_GSTRING_LEN,
			marvell_hw_stats[i].string, ETH_GSTRING_LEN);
	पूर्ण
पूर्ण

अटल u64 marvell_get_stat(काष्ठा phy_device *phydev, पूर्णांक i)
अणु
	काष्ठा marvell_hw_stat stat = marvell_hw_stats[i];
	काष्ठा marvell_priv *priv = phydev->priv;
	पूर्णांक val;
	u64 ret;

	val = phy_पढ़ो_paged(phydev, stat.page, stat.reg);
	अगर (val < 0) अणु
		ret = U64_MAX;
	पूर्ण अन्यथा अणु
		val = val & ((1 << stat.bits) - 1);
		priv->stats[i] += val;
		ret = priv->stats[i];
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम marvell_get_stats(काष्ठा phy_device *phydev,
			      काष्ठा ethtool_stats *stats, u64 *data)
अणु
	पूर्णांक count = marvell_get_sset_count(phydev);
	पूर्णांक i;

	क्रम (i = 0; i < count; i++)
		data[i] = marvell_get_stat(phydev, i);
पूर्ण

अटल पूर्णांक marvell_vct5_रुको_complete(काष्ठा phy_device *phydev)
अणु
	पूर्णांक i;
	पूर्णांक val;

	क्रम (i = 0; i < 32; i++) अणु
		val = __phy_पढ़ो(phydev, MII_VCT5_CTRL);
		अगर (val < 0)
			वापस val;

		अगर (val & MII_VCT5_CTRL_COMPLETE)
			वापस 0;
	पूर्ण

	phydev_err(phydev, "Timeout while waiting for cable test to finish\n");
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक marvell_vct5_amplitude(काष्ठा phy_device *phydev, पूर्णांक pair)
अणु
	पूर्णांक amplitude;
	पूर्णांक val;
	पूर्णांक reg;

	reg = MII_VCT5_TX_RX_MDI0_COUPLING + pair;
	val = __phy_पढ़ो(phydev, reg);

	अगर (val < 0)
		वापस 0;

	amplitude = (val & MII_VCT5_TX_RX_AMPLITUDE_MASK) >>
		MII_VCT5_TX_RX_AMPLITUDE_SHIFT;

	अगर (!(val & MII_VCT5_TX_RX_COUPLING_POSITIVE_REFLECTION))
		amplitude = -amplitude;

	वापस 1000 * amplitude / 128;
पूर्ण

अटल u32 marvell_vct5_distance2cm(पूर्णांक distance)
अणु
	वापस distance * 805 / 10;
पूर्ण

अटल u32 marvell_vct5_cm2distance(पूर्णांक cm)
अणु
	वापस cm * 10 / 805;
पूर्ण

अटल पूर्णांक marvell_vct5_amplitude_distance(काष्ठा phy_device *phydev,
					   पूर्णांक distance, पूर्णांक pair)
अणु
	u16 reg;
	पूर्णांक err;
	पूर्णांक mV;
	पूर्णांक i;

	err = __phy_ग_लिखो(phydev, MII_VCT5_SAMPLE_POINT_DISTANCE,
			  distance);
	अगर (err)
		वापस err;

	reg = MII_VCT5_CTRL_ENABLE |
		MII_VCT5_CTRL_TX_SAME_CHANNEL |
		MII_VCT5_CTRL_SAMPLES_DEFAULT |
		MII_VCT5_CTRL_SAMPLE_POINT |
		MII_VCT5_CTRL_PEEK_HYST_DEFAULT;
	err = __phy_ग_लिखो(phydev, MII_VCT5_CTRL, reg);
	अगर (err)
		वापस err;

	err = marvell_vct5_रुको_complete(phydev);
	अगर (err)
		वापस err;

	क्रम (i = 0; i < 4; i++) अणु
		अगर (pair != PHY_PAIR_ALL && i != pair)
			जारी;

		mV = marvell_vct5_amplitude(phydev, i);
		ethnl_cable_test_amplitude(phydev, i, mV);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक marvell_vct5_amplitude_graph(काष्ठा phy_device *phydev)
अणु
	काष्ठा marvell_priv *priv = phydev->priv;
	पूर्णांक distance;
	u16 width;
	पूर्णांक page;
	पूर्णांक err;
	u16 reg;

	अगर (priv->first <= TDR_SHORT_CABLE_LENGTH)
		width = MII_VCT5_TX_PULSE_CTRL_PULSE_WIDTH_32nS;
	अन्यथा
		width = MII_VCT5_TX_PULSE_CTRL_PULSE_WIDTH_128nS;

	reg = MII_VCT5_TX_PULSE_CTRL_GT_140m_46_86mV |
		MII_VCT5_TX_PULSE_CTRL_DONT_WAIT_LINK_DOWN |
		MII_VCT5_TX_PULSE_CTRL_MAX_AMP | width;

	err = phy_ग_लिखो_paged(phydev, MII_MARVELL_VCT5_PAGE,
			      MII_VCT5_TX_PULSE_CTRL, reg);
	अगर (err)
		वापस err;

	/* Reading the TDR data is very MDIO heavy. We need to optimize
	 * access to keep the समय to a minimum. So lock the bus once,
	 * and करोn't release it until complete. We can then aव्योम having
	 * to change the page क्रम every access, greatly speeding things
	 * up.
	 */
	page = phy_select_page(phydev, MII_MARVELL_VCT5_PAGE);
	अगर (page < 0)
		जाओ restore_page;

	क्रम (distance = priv->first;
	     distance <= priv->last;
	     distance += priv->step) अणु
		err = marvell_vct5_amplitude_distance(phydev, distance,
						      priv->pair);
		अगर (err)
			जाओ restore_page;

		अगर (distance > TDR_SHORT_CABLE_LENGTH &&
		    width == MII_VCT5_TX_PULSE_CTRL_PULSE_WIDTH_32nS) अणु
			width = MII_VCT5_TX_PULSE_CTRL_PULSE_WIDTH_128nS;
			reg = MII_VCT5_TX_PULSE_CTRL_GT_140m_46_86mV |
				MII_VCT5_TX_PULSE_CTRL_DONT_WAIT_LINK_DOWN |
				MII_VCT5_TX_PULSE_CTRL_MAX_AMP | width;
			err = __phy_ग_लिखो(phydev, MII_VCT5_TX_PULSE_CTRL, reg);
			अगर (err)
				जाओ restore_page;
		पूर्ण
	पूर्ण

restore_page:
	वापस phy_restore_page(phydev, page, err);
पूर्ण

अटल पूर्णांक marvell_cable_test_start_common(काष्ठा phy_device *phydev)
अणु
	पूर्णांक bmcr, bmsr, ret;

	/* If स्वतः-negotiation is enabled, but not complete, the cable
	 * test never completes. So disable स्वतः-neg.
	 */
	bmcr = phy_पढ़ो(phydev, MII_BMCR);
	अगर (bmcr < 0)
		वापस bmcr;

	bmsr = phy_पढ़ो(phydev, MII_BMSR);

	अगर (bmsr < 0)
		वापस bmsr;

	अगर (bmcr & BMCR_ANENABLE) अणु
		ret =  phy_clear_bits(phydev, MII_BMCR, BMCR_ANENABLE);
		अगर (ret < 0)
			वापस ret;
		ret = genphy_soft_reset(phydev);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* If the link is up, allow it some समय to go करोwn */
	अगर (bmsr & BMSR_LSTATUS)
		msleep(1500);

	वापस 0;
पूर्ण

अटल पूर्णांक marvell_vct7_cable_test_start(काष्ठा phy_device *phydev)
अणु
	काष्ठा marvell_priv *priv = phydev->priv;
	पूर्णांक ret;

	ret = marvell_cable_test_start_common(phydev);
	अगर (ret)
		वापस ret;

	priv->cable_test_tdr = false;

	/* Reset the VCT5 API control to शेषs, otherwise
	 * VCT7 करोes not work correctly.
	 */
	ret = phy_ग_लिखो_paged(phydev, MII_MARVELL_VCT5_PAGE,
			      MII_VCT5_CTRL,
			      MII_VCT5_CTRL_TX_SAME_CHANNEL |
			      MII_VCT5_CTRL_SAMPLES_DEFAULT |
			      MII_VCT5_CTRL_MODE_MAXIMUM_PEEK |
			      MII_VCT5_CTRL_PEEK_HYST_DEFAULT);
	अगर (ret)
		वापस ret;

	ret = phy_ग_लिखो_paged(phydev, MII_MARVELL_VCT5_PAGE,
			      MII_VCT5_SAMPLE_POINT_DISTANCE, 0);
	अगर (ret)
		वापस ret;

	वापस phy_ग_लिखो_paged(phydev, MII_MARVELL_VCT7_PAGE,
			       MII_VCT7_CTRL,
			       MII_VCT7_CTRL_RUN_NOW |
			       MII_VCT7_CTRL_CENTIMETERS);
पूर्ण

अटल पूर्णांक marvell_vct5_cable_test_tdr_start(काष्ठा phy_device *phydev,
					     स्थिर काष्ठा phy_tdr_config *cfg)
अणु
	काष्ठा marvell_priv *priv = phydev->priv;
	पूर्णांक ret;

	priv->cable_test_tdr = true;
	priv->first = marvell_vct5_cm2distance(cfg->first);
	priv->last = marvell_vct5_cm2distance(cfg->last);
	priv->step = marvell_vct5_cm2distance(cfg->step);
	priv->pair = cfg->pair;

	अगर (priv->first > MII_VCT5_SAMPLE_POINT_DISTANCE_MAX)
		वापस -EINVAL;

	अगर (priv->last > MII_VCT5_SAMPLE_POINT_DISTANCE_MAX)
		वापस -EINVAL;

	/* Disable  VCT7 */
	ret = phy_ग_लिखो_paged(phydev, MII_MARVELL_VCT7_PAGE,
			      MII_VCT7_CTRL, 0);
	अगर (ret)
		वापस ret;

	ret = marvell_cable_test_start_common(phydev);
	अगर (ret)
		वापस ret;

	ret = ethnl_cable_test_pulse(phydev, 1000);
	अगर (ret)
		वापस ret;

	वापस ethnl_cable_test_step(phydev,
				     marvell_vct5_distance2cm(priv->first),
				     marvell_vct5_distance2cm(priv->last),
				     marvell_vct5_distance2cm(priv->step));
पूर्ण

अटल पूर्णांक marvell_vct7_distance_to_length(पूर्णांक distance, bool meter)
अणु
	अगर (meter)
		distance *= 100;

	वापस distance;
पूर्ण

अटल bool marvell_vct7_distance_valid(पूर्णांक result)
अणु
	चयन (result) अणु
	हाल MII_VCT7_RESULTS_OPEN:
	हाल MII_VCT7_RESULTS_SAME_SHORT:
	हाल MII_VCT7_RESULTS_CROSS_SHORT:
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक marvell_vct7_report_length(काष्ठा phy_device *phydev,
				      पूर्णांक pair, bool meter)
अणु
	पूर्णांक length;
	पूर्णांक ret;

	ret = phy_पढ़ो_paged(phydev, MII_MARVELL_VCT7_PAGE,
			     MII_VCT7_PAIR_0_DISTANCE + pair);
	अगर (ret < 0)
		वापस ret;

	length = marvell_vct7_distance_to_length(ret, meter);

	ethnl_cable_test_fault_length(phydev, pair, length);

	वापस 0;
पूर्ण

अटल पूर्णांक marvell_vct7_cable_test_report_trans(पूर्णांक result)
अणु
	चयन (result) अणु
	हाल MII_VCT7_RESULTS_OK:
		वापस ETHTOOL_A_CABLE_RESULT_CODE_OK;
	हाल MII_VCT7_RESULTS_OPEN:
		वापस ETHTOOL_A_CABLE_RESULT_CODE_OPEN;
	हाल MII_VCT7_RESULTS_SAME_SHORT:
		वापस ETHTOOL_A_CABLE_RESULT_CODE_SAME_SHORT;
	हाल MII_VCT7_RESULTS_CROSS_SHORT:
		वापस ETHTOOL_A_CABLE_RESULT_CODE_CROSS_SHORT;
	शेष:
		वापस ETHTOOL_A_CABLE_RESULT_CODE_UNSPEC;
	पूर्ण
पूर्ण

अटल पूर्णांक marvell_vct7_cable_test_report(काष्ठा phy_device *phydev)
अणु
	पूर्णांक pair0, pair1, pair2, pair3;
	bool meter;
	पूर्णांक ret;

	ret = phy_पढ़ो_paged(phydev, MII_MARVELL_VCT7_PAGE,
			     MII_VCT7_RESULTS);
	अगर (ret < 0)
		वापस ret;

	pair3 = (ret & MII_VCT7_RESULTS_PAIR3_MASK) >>
		MII_VCT7_RESULTS_PAIR3_SHIFT;
	pair2 = (ret & MII_VCT7_RESULTS_PAIR2_MASK) >>
		MII_VCT7_RESULTS_PAIR2_SHIFT;
	pair1 = (ret & MII_VCT7_RESULTS_PAIR1_MASK) >>
		MII_VCT7_RESULTS_PAIR1_SHIFT;
	pair0 = (ret & MII_VCT7_RESULTS_PAIR0_MASK) >>
		MII_VCT7_RESULTS_PAIR0_SHIFT;

	ethnl_cable_test_result(phydev, ETHTOOL_A_CABLE_PAIR_A,
				marvell_vct7_cable_test_report_trans(pair0));
	ethnl_cable_test_result(phydev, ETHTOOL_A_CABLE_PAIR_B,
				marvell_vct7_cable_test_report_trans(pair1));
	ethnl_cable_test_result(phydev, ETHTOOL_A_CABLE_PAIR_C,
				marvell_vct7_cable_test_report_trans(pair2));
	ethnl_cable_test_result(phydev, ETHTOOL_A_CABLE_PAIR_D,
				marvell_vct7_cable_test_report_trans(pair3));

	ret = phy_पढ़ो_paged(phydev, MII_MARVELL_VCT7_PAGE, MII_VCT7_CTRL);
	अगर (ret < 0)
		वापस ret;

	meter = ret & MII_VCT7_CTRL_METERS;

	अगर (marvell_vct7_distance_valid(pair0))
		marvell_vct7_report_length(phydev, 0, meter);
	अगर (marvell_vct7_distance_valid(pair1))
		marvell_vct7_report_length(phydev, 1, meter);
	अगर (marvell_vct7_distance_valid(pair2))
		marvell_vct7_report_length(phydev, 2, meter);
	अगर (marvell_vct7_distance_valid(pair3))
		marvell_vct7_report_length(phydev, 3, meter);

	वापस 0;
पूर्ण

अटल पूर्णांक marvell_vct7_cable_test_get_status(काष्ठा phy_device *phydev,
					      bool *finished)
अणु
	काष्ठा marvell_priv *priv = phydev->priv;
	पूर्णांक ret;

	अगर (priv->cable_test_tdr) अणु
		ret = marvell_vct5_amplitude_graph(phydev);
		*finished = true;
		वापस ret;
	पूर्ण

	*finished = false;

	ret = phy_पढ़ो_paged(phydev, MII_MARVELL_VCT7_PAGE,
			     MII_VCT7_CTRL);

	अगर (ret < 0)
		वापस ret;

	अगर (!(ret & MII_VCT7_CTRL_IN_PROGRESS)) अणु
		*finished = true;

		वापस marvell_vct7_cable_test_report(phydev);
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_HWMON
काष्ठा marvell_hwmon_ops अणु
	पूर्णांक (*config)(काष्ठा phy_device *phydev);
	पूर्णांक (*get_temp)(काष्ठा phy_device *phydev, दीर्घ *temp);
	पूर्णांक (*get_temp_critical)(काष्ठा phy_device *phydev, दीर्घ *temp);
	पूर्णांक (*set_temp_critical)(काष्ठा phy_device *phydev, दीर्घ temp);
	पूर्णांक (*get_temp_alarm)(काष्ठा phy_device *phydev, दीर्घ *alarm);
पूर्ण;

अटल स्थिर काष्ठा marvell_hwmon_ops *
to_marvell_hwmon_ops(स्थिर काष्ठा phy_device *phydev)
अणु
	वापस phydev->drv->driver_data;
पूर्ण

अटल पूर्णांक m88e1121_get_temp(काष्ठा phy_device *phydev, दीर्घ *temp)
अणु
	पूर्णांक oldpage;
	पूर्णांक ret = 0;
	पूर्णांक val;

	*temp = 0;

	oldpage = phy_select_page(phydev, MII_MARVELL_MISC_TEST_PAGE);
	अगर (oldpage < 0)
		जाओ error;

	/* Enable temperature sensor */
	ret = __phy_पढ़ो(phydev, MII_88E1121_MISC_TEST);
	अगर (ret < 0)
		जाओ error;

	ret = __phy_ग_लिखो(phydev, MII_88E1121_MISC_TEST,
			  ret | MII_88E1121_MISC_TEST_TEMP_SENSOR_EN);
	अगर (ret < 0)
		जाओ error;

	/* Wait क्रम temperature to stabilize */
	usleep_range(10000, 12000);

	val = __phy_पढ़ो(phydev, MII_88E1121_MISC_TEST);
	अगर (val < 0) अणु
		ret = val;
		जाओ error;
	पूर्ण

	/* Disable temperature sensor */
	ret = __phy_ग_लिखो(phydev, MII_88E1121_MISC_TEST,
			  ret & ~MII_88E1121_MISC_TEST_TEMP_SENSOR_EN);
	अगर (ret < 0)
		जाओ error;

	*temp = ((val & MII_88E1121_MISC_TEST_TEMP_MASK) - 5) * 5000;

error:
	वापस phy_restore_page(phydev, oldpage, ret);
पूर्ण

अटल पूर्णांक m88e1510_get_temp(काष्ठा phy_device *phydev, दीर्घ *temp)
अणु
	पूर्णांक ret;

	*temp = 0;

	ret = phy_पढ़ो_paged(phydev, MII_MARVELL_MISC_TEST_PAGE,
			     MII_88E1510_TEMP_SENSOR);
	अगर (ret < 0)
		वापस ret;

	*temp = ((ret & MII_88E1510_TEMP_SENSOR_MASK) - 25) * 1000;

	वापस 0;
पूर्ण

अटल पूर्णांक m88e1510_get_temp_critical(काष्ठा phy_device *phydev, दीर्घ *temp)
अणु
	पूर्णांक ret;

	*temp = 0;

	ret = phy_पढ़ो_paged(phydev, MII_MARVELL_MISC_TEST_PAGE,
			     MII_88E1121_MISC_TEST);
	अगर (ret < 0)
		वापस ret;

	*temp = (((ret & MII_88E1510_MISC_TEST_TEMP_THRESHOLD_MASK) >>
		  MII_88E1510_MISC_TEST_TEMP_THRESHOLD_SHIFT) * 5) - 25;
	/* convert to mC */
	*temp *= 1000;

	वापस 0;
पूर्ण

अटल पूर्णांक m88e1510_set_temp_critical(काष्ठा phy_device *phydev, दीर्घ temp)
अणु
	temp = temp / 1000;
	temp = clamp_val(DIV_ROUND_CLOSEST(temp, 5) + 5, 0, 0x1f);

	वापस phy_modअगरy_paged(phydev, MII_MARVELL_MISC_TEST_PAGE,
				MII_88E1121_MISC_TEST,
				MII_88E1510_MISC_TEST_TEMP_THRESHOLD_MASK,
				temp << MII_88E1510_MISC_TEST_TEMP_THRESHOLD_SHIFT);
पूर्ण

अटल पूर्णांक m88e1510_get_temp_alarm(काष्ठा phy_device *phydev, दीर्घ *alarm)
अणु
	पूर्णांक ret;

	*alarm = false;

	ret = phy_पढ़ो_paged(phydev, MII_MARVELL_MISC_TEST_PAGE,
			     MII_88E1121_MISC_TEST);
	अगर (ret < 0)
		वापस ret;

	*alarm = !!(ret & MII_88E1510_MISC_TEST_TEMP_IRQ);

	वापस 0;
पूर्ण

अटल पूर्णांक m88e6390_get_temp(काष्ठा phy_device *phydev, दीर्घ *temp)
अणु
	पूर्णांक sum = 0;
	पूर्णांक oldpage;
	पूर्णांक ret = 0;
	पूर्णांक i;

	*temp = 0;

	oldpage = phy_select_page(phydev, MII_MARVELL_MISC_TEST_PAGE);
	अगर (oldpage < 0)
		जाओ error;

	/* Enable temperature sensor */
	ret = __phy_पढ़ो(phydev, MII_88E6390_MISC_TEST);
	अगर (ret < 0)
		जाओ error;

	ret &= ~MII_88E6390_MISC_TEST_TEMP_SENSOR_MASK;
	ret |= MII_88E6390_MISC_TEST_TEMP_SENSOR_ENABLE_SAMPLE_1S;

	ret = __phy_ग_लिखो(phydev, MII_88E6390_MISC_TEST, ret);
	अगर (ret < 0)
		जाओ error;

	/* Wait क्रम temperature to stabilize */
	usleep_range(10000, 12000);

	/* Reading the temperature sense has an errata. You need to पढ़ो
	 * a number of बार and take an average.
	 */
	क्रम (i = 0; i < MII_88E6390_TEMP_SENSOR_SAMPLES; i++) अणु
		ret = __phy_पढ़ो(phydev, MII_88E6390_TEMP_SENSOR);
		अगर (ret < 0)
			जाओ error;
		sum += ret & MII_88E6390_TEMP_SENSOR_MASK;
	पूर्ण

	sum /= MII_88E6390_TEMP_SENSOR_SAMPLES;
	*temp = (sum  - 75) * 1000;

	/* Disable temperature sensor */
	ret = __phy_पढ़ो(phydev, MII_88E6390_MISC_TEST);
	अगर (ret < 0)
		जाओ error;

	ret = ret & ~MII_88E6390_MISC_TEST_TEMP_SENSOR_MASK;
	ret |= MII_88E6390_MISC_TEST_TEMP_SENSOR_DISABLE;

	ret = __phy_ग_लिखो(phydev, MII_88E6390_MISC_TEST, ret);

error:
	phy_restore_page(phydev, oldpage, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक m88e6393_get_temp(काष्ठा phy_device *phydev, दीर्घ *temp)
अणु
	पूर्णांक err;

	err = m88e1510_get_temp(phydev, temp);

	/* 88E1510 measures T + 25, जबतक the PHY on 88E6393X चयन
	 * T + 75, so we have to subtract another 50
	 */
	*temp -= 50000;

	वापस err;
पूर्ण

अटल पूर्णांक m88e6393_get_temp_critical(काष्ठा phy_device *phydev, दीर्घ *temp)
अणु
	पूर्णांक ret;

	*temp = 0;

	ret = phy_पढ़ो_paged(phydev, MII_MARVELL_MISC_TEST_PAGE,
			     MII_88E6390_TEMP_SENSOR);
	अगर (ret < 0)
		वापस ret;

	*temp = (((ret & MII_88E6393_TEMP_SENSOR_THRESHOLD_MASK) >>
		  MII_88E6393_TEMP_SENSOR_THRESHOLD_SHIFT) - 75) * 1000;

	वापस 0;
पूर्ण

अटल पूर्णांक m88e6393_set_temp_critical(काष्ठा phy_device *phydev, दीर्घ temp)
अणु
	temp = (temp / 1000) + 75;

	वापस phy_modअगरy_paged(phydev, MII_MARVELL_MISC_TEST_PAGE,
				MII_88E6390_TEMP_SENSOR,
				MII_88E6393_TEMP_SENSOR_THRESHOLD_MASK,
				temp << MII_88E6393_TEMP_SENSOR_THRESHOLD_SHIFT);
पूर्ण

अटल पूर्णांक m88e6393_hwmon_config(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	err = m88e6393_set_temp_critical(phydev, 100000);
	अगर (err)
		वापस err;

	वापस phy_modअगरy_paged(phydev, MII_MARVELL_MISC_TEST_PAGE,
				MII_88E6390_MISC_TEST,
				MII_88E6390_MISC_TEST_TEMP_SENSOR_MASK |
				MII_88E6393_MISC_TEST_SAMPLES_MASK |
				MII_88E6393_MISC_TEST_RATE_MASK,
				MII_88E6390_MISC_TEST_TEMP_SENSOR_ENABLE |
				MII_88E6393_MISC_TEST_SAMPLES_2048 |
				MII_88E6393_MISC_TEST_RATE_2_3MS);
पूर्ण

अटल पूर्णांक marvell_hwmon_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			      u32 attr, पूर्णांक channel, दीर्घ *temp)
अणु
	काष्ठा phy_device *phydev = dev_get_drvdata(dev);
	स्थिर काष्ठा marvell_hwmon_ops *ops = to_marvell_hwmon_ops(phydev);
	पूर्णांक err = -EOPNOTSUPP;

	चयन (attr) अणु
	हाल hwmon_temp_input:
		अगर (ops->get_temp)
			err = ops->get_temp(phydev, temp);
		अवरोध;
	हाल hwmon_temp_crit:
		अगर (ops->get_temp_critical)
			err = ops->get_temp_critical(phydev, temp);
		अवरोध;
	हाल hwmon_temp_max_alarm:
		अगर (ops->get_temp_alarm)
			err = ops->get_temp_alarm(phydev, temp);
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक marvell_hwmon_ग_लिखो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			       u32 attr, पूर्णांक channel, दीर्घ temp)
अणु
	काष्ठा phy_device *phydev = dev_get_drvdata(dev);
	स्थिर काष्ठा marvell_hwmon_ops *ops = to_marvell_hwmon_ops(phydev);
	पूर्णांक err = -EOPNOTSUPP;

	चयन (attr) अणु
	हाल hwmon_temp_crit:
		अगर (ops->set_temp_critical)
			err = ops->set_temp_critical(phydev, temp);
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल umode_t marvell_hwmon_is_visible(स्थिर व्योम *data,
					क्रमागत hwmon_sensor_types type,
					u32 attr, पूर्णांक channel)
अणु
	स्थिर काष्ठा phy_device *phydev = data;
	स्थिर काष्ठा marvell_hwmon_ops *ops = to_marvell_hwmon_ops(phydev);

	अगर (type != hwmon_temp)
		वापस 0;

	चयन (attr) अणु
	हाल hwmon_temp_input:
		वापस ops->get_temp ? 0444 : 0;
	हाल hwmon_temp_max_alarm:
		वापस ops->get_temp_alarm ? 0444 : 0;
	हाल hwmon_temp_crit:
		वापस (ops->get_temp_critical ? 0444 : 0) |
		       (ops->set_temp_critical ? 0200 : 0);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल u32 marvell_hwmon_chip_config[] = अणु
	HWMON_C_REGISTER_TZ,
	0
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info marvell_hwmon_chip = अणु
	.type = hwmon_chip,
	.config = marvell_hwmon_chip_config,
पूर्ण;

/* we can define HWMON_T_CRIT and HWMON_T_MAX_ALARM even though these are not
 * defined क्रम all PHYs, because the hwmon code checks whether the attributes
 * exists via the .is_visible method
 */
अटल u32 marvell_hwmon_temp_config[] = अणु
	HWMON_T_INPUT | HWMON_T_CRIT | HWMON_T_MAX_ALARM,
	0
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info marvell_hwmon_temp = अणु
	.type = hwmon_temp,
	.config = marvell_hwmon_temp_config,
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info *marvell_hwmon_info[] = अणु
	&marvell_hwmon_chip,
	&marvell_hwmon_temp,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hwmon_ops marvell_hwmon_hwmon_ops = अणु
	.is_visible = marvell_hwmon_is_visible,
	.पढ़ो = marvell_hwmon_पढ़ो,
	.ग_लिखो = marvell_hwmon_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info marvell_hwmon_chip_info = अणु
	.ops = &marvell_hwmon_hwmon_ops,
	.info = marvell_hwmon_info,
पूर्ण;

अटल पूर्णांक marvell_hwmon_name(काष्ठा phy_device *phydev)
अणु
	काष्ठा marvell_priv *priv = phydev->priv;
	काष्ठा device *dev = &phydev->mdio.dev;
	स्थिर अक्षर *devname = dev_name(dev);
	माप_प्रकार len = म_माप(devname);
	पूर्णांक i, j;

	priv->hwmon_name = devm_kzalloc(dev, len, GFP_KERNEL);
	अगर (!priv->hwmon_name)
		वापस -ENOMEM;

	क्रम (i = j = 0; i < len && devname[i]; i++) अणु
		अगर (है_अक्षर_अंक(devname[i]))
			priv->hwmon_name[j++] = devname[i];
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक marvell_hwmon_probe(काष्ठा phy_device *phydev)
अणु
	स्थिर काष्ठा marvell_hwmon_ops *ops = to_marvell_hwmon_ops(phydev);
	काष्ठा marvell_priv *priv = phydev->priv;
	काष्ठा device *dev = &phydev->mdio.dev;
	पूर्णांक err;

	अगर (!ops)
		वापस 0;

	err = marvell_hwmon_name(phydev);
	अगर (err)
		वापस err;

	priv->hwmon_dev = devm_hwmon_device_रेजिस्टर_with_info(
		dev, priv->hwmon_name, phydev, &marvell_hwmon_chip_info, शून्य);
	अगर (IS_ERR(priv->hwmon_dev))
		वापस PTR_ERR(priv->hwmon_dev);

	अगर (ops->config)
		err = ops->config(phydev);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा marvell_hwmon_ops m88e1121_hwmon_ops = अणु
	.get_temp = m88e1121_get_temp,
पूर्ण;

अटल स्थिर काष्ठा marvell_hwmon_ops m88e1510_hwmon_ops = अणु
	.get_temp = m88e1510_get_temp,
	.get_temp_critical = m88e1510_get_temp_critical,
	.set_temp_critical = m88e1510_set_temp_critical,
	.get_temp_alarm = m88e1510_get_temp_alarm,
पूर्ण;

अटल स्थिर काष्ठा marvell_hwmon_ops m88e6390_hwmon_ops = अणु
	.get_temp = m88e6390_get_temp,
पूर्ण;

अटल स्थिर काष्ठा marvell_hwmon_ops m88e6393_hwmon_ops = अणु
	.config = m88e6393_hwmon_config,
	.get_temp = m88e6393_get_temp,
	.get_temp_critical = m88e6393_get_temp_critical,
	.set_temp_critical = m88e6393_set_temp_critical,
	.get_temp_alarm = m88e1510_get_temp_alarm,
पूर्ण;

#घोषणा DEF_MARVELL_HWMON_OPS(s) (&(s))

#अन्यथा

#घोषणा DEF_MARVELL_HWMON_OPS(s) शून्य

अटल पूर्णांक marvell_hwmon_probe(काष्ठा phy_device *phydev)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक marvell_probe(काष्ठा phy_device *phydev)
अणु
	काष्ठा marvell_priv *priv;

	priv = devm_kzalloc(&phydev->mdio.dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	phydev->priv = priv;

	वापस marvell_hwmon_probe(phydev);
पूर्ण

अटल काष्ठा phy_driver marvell_drivers[] = अणु
	अणु
		.phy_id = MARVELL_PHY_ID_88E1101,
		.phy_id_mask = MARVELL_PHY_ID_MASK,
		.name = "Marvell 88E1101",
		/* PHY_GBIT_FEATURES */
		.probe = marvell_probe,
		.config_init = marvell_config_init,
		.config_aneg = m88e1101_config_aneg,
		.config_पूर्णांकr = marvell_config_पूर्णांकr,
		.handle_पूर्णांकerrupt = marvell_handle_पूर्णांकerrupt,
		.resume = genphy_resume,
		.suspend = genphy_suspend,
		.पढ़ो_page = marvell_पढ़ो_page,
		.ग_लिखो_page = marvell_ग_लिखो_page,
		.get_sset_count = marvell_get_sset_count,
		.get_strings = marvell_get_strings,
		.get_stats = marvell_get_stats,
	पूर्ण,
	अणु
		.phy_id = MARVELL_PHY_ID_88E1112,
		.phy_id_mask = MARVELL_PHY_ID_MASK,
		.name = "Marvell 88E1112",
		/* PHY_GBIT_FEATURES */
		.probe = marvell_probe,
		.config_init = m88e1112_config_init,
		.config_aneg = marvell_config_aneg,
		.config_पूर्णांकr = marvell_config_पूर्णांकr,
		.handle_पूर्णांकerrupt = marvell_handle_पूर्णांकerrupt,
		.resume = genphy_resume,
		.suspend = genphy_suspend,
		.पढ़ो_page = marvell_पढ़ो_page,
		.ग_लिखो_page = marvell_ग_लिखो_page,
		.get_sset_count = marvell_get_sset_count,
		.get_strings = marvell_get_strings,
		.get_stats = marvell_get_stats,
		.get_tunable = m88e1011_get_tunable,
		.set_tunable = m88e1011_set_tunable,
	पूर्ण,
	अणु
		.phy_id = MARVELL_PHY_ID_88E1111,
		.phy_id_mask = MARVELL_PHY_ID_MASK,
		.name = "Marvell 88E1111",
		/* PHY_GBIT_FEATURES */
		.probe = marvell_probe,
		.config_init = m88e1111gbe_config_init,
		.config_aneg = m88e1111_config_aneg,
		.पढ़ो_status = marvell_पढ़ो_status,
		.config_पूर्णांकr = marvell_config_पूर्णांकr,
		.handle_पूर्णांकerrupt = marvell_handle_पूर्णांकerrupt,
		.resume = genphy_resume,
		.suspend = genphy_suspend,
		.पढ़ो_page = marvell_पढ़ो_page,
		.ग_लिखो_page = marvell_ग_लिखो_page,
		.get_sset_count = marvell_get_sset_count,
		.get_strings = marvell_get_strings,
		.get_stats = marvell_get_stats,
		.get_tunable = m88e1111_get_tunable,
		.set_tunable = m88e1111_set_tunable,
	पूर्ण,
	अणु
		.phy_id = MARVELL_PHY_ID_88E1111_FINISAR,
		.phy_id_mask = MARVELL_PHY_ID_MASK,
		.name = "Marvell 88E1111 (Finisar)",
		/* PHY_GBIT_FEATURES */
		.probe = marvell_probe,
		.config_init = m88e1111gbe_config_init,
		.config_aneg = m88e1111_config_aneg,
		.पढ़ो_status = marvell_पढ़ो_status,
		.config_पूर्णांकr = marvell_config_पूर्णांकr,
		.handle_पूर्णांकerrupt = marvell_handle_पूर्णांकerrupt,
		.resume = genphy_resume,
		.suspend = genphy_suspend,
		.पढ़ो_page = marvell_पढ़ो_page,
		.ग_लिखो_page = marvell_ग_लिखो_page,
		.get_sset_count = marvell_get_sset_count,
		.get_strings = marvell_get_strings,
		.get_stats = marvell_get_stats,
		.get_tunable = m88e1111_get_tunable,
		.set_tunable = m88e1111_set_tunable,
	पूर्ण,
	अणु
		.phy_id = MARVELL_PHY_ID_88E1118,
		.phy_id_mask = MARVELL_PHY_ID_MASK,
		.name = "Marvell 88E1118",
		/* PHY_GBIT_FEATURES */
		.probe = marvell_probe,
		.config_init = m88e1118_config_init,
		.config_aneg = m88e1118_config_aneg,
		.config_पूर्णांकr = marvell_config_पूर्णांकr,
		.handle_पूर्णांकerrupt = marvell_handle_पूर्णांकerrupt,
		.resume = genphy_resume,
		.suspend = genphy_suspend,
		.पढ़ो_page = marvell_पढ़ो_page,
		.ग_लिखो_page = marvell_ग_लिखो_page,
		.get_sset_count = marvell_get_sset_count,
		.get_strings = marvell_get_strings,
		.get_stats = marvell_get_stats,
	पूर्ण,
	अणु
		.phy_id = MARVELL_PHY_ID_88E1121R,
		.phy_id_mask = MARVELL_PHY_ID_MASK,
		.name = "Marvell 88E1121R",
		.driver_data = DEF_MARVELL_HWMON_OPS(m88e1121_hwmon_ops),
		/* PHY_GBIT_FEATURES */
		.probe = marvell_probe,
		.config_init = marvell_1011gbe_config_init,
		.config_aneg = m88e1121_config_aneg,
		.पढ़ो_status = marvell_पढ़ो_status,
		.config_पूर्णांकr = marvell_config_पूर्णांकr,
		.handle_पूर्णांकerrupt = marvell_handle_पूर्णांकerrupt,
		.resume = genphy_resume,
		.suspend = genphy_suspend,
		.पढ़ो_page = marvell_पढ़ो_page,
		.ग_लिखो_page = marvell_ग_लिखो_page,
		.get_sset_count = marvell_get_sset_count,
		.get_strings = marvell_get_strings,
		.get_stats = marvell_get_stats,
		.get_tunable = m88e1011_get_tunable,
		.set_tunable = m88e1011_set_tunable,
	पूर्ण,
	अणु
		.phy_id = MARVELL_PHY_ID_88E1318S,
		.phy_id_mask = MARVELL_PHY_ID_MASK,
		.name = "Marvell 88E1318S",
		/* PHY_GBIT_FEATURES */
		.probe = marvell_probe,
		.config_init = m88e1318_config_init,
		.config_aneg = m88e1318_config_aneg,
		.पढ़ो_status = marvell_पढ़ो_status,
		.config_पूर्णांकr = marvell_config_पूर्णांकr,
		.handle_पूर्णांकerrupt = marvell_handle_पूर्णांकerrupt,
		.get_wol = m88e1318_get_wol,
		.set_wol = m88e1318_set_wol,
		.resume = genphy_resume,
		.suspend = genphy_suspend,
		.पढ़ो_page = marvell_पढ़ो_page,
		.ग_लिखो_page = marvell_ग_लिखो_page,
		.get_sset_count = marvell_get_sset_count,
		.get_strings = marvell_get_strings,
		.get_stats = marvell_get_stats,
	पूर्ण,
	अणु
		.phy_id = MARVELL_PHY_ID_88E1145,
		.phy_id_mask = MARVELL_PHY_ID_MASK,
		.name = "Marvell 88E1145",
		/* PHY_GBIT_FEATURES */
		.probe = marvell_probe,
		.config_init = m88e1145_config_init,
		.config_aneg = m88e1101_config_aneg,
		.config_पूर्णांकr = marvell_config_पूर्णांकr,
		.handle_पूर्णांकerrupt = marvell_handle_पूर्णांकerrupt,
		.resume = genphy_resume,
		.suspend = genphy_suspend,
		.पढ़ो_page = marvell_पढ़ो_page,
		.ग_लिखो_page = marvell_ग_लिखो_page,
		.get_sset_count = marvell_get_sset_count,
		.get_strings = marvell_get_strings,
		.get_stats = marvell_get_stats,
		.get_tunable = m88e1111_get_tunable,
		.set_tunable = m88e1111_set_tunable,
	पूर्ण,
	अणु
		.phy_id = MARVELL_PHY_ID_88E1149R,
		.phy_id_mask = MARVELL_PHY_ID_MASK,
		.name = "Marvell 88E1149R",
		/* PHY_GBIT_FEATURES */
		.probe = marvell_probe,
		.config_init = m88e1149_config_init,
		.config_aneg = m88e1118_config_aneg,
		.config_पूर्णांकr = marvell_config_पूर्णांकr,
		.handle_पूर्णांकerrupt = marvell_handle_पूर्णांकerrupt,
		.resume = genphy_resume,
		.suspend = genphy_suspend,
		.पढ़ो_page = marvell_पढ़ो_page,
		.ग_लिखो_page = marvell_ग_लिखो_page,
		.get_sset_count = marvell_get_sset_count,
		.get_strings = marvell_get_strings,
		.get_stats = marvell_get_stats,
	पूर्ण,
	अणु
		.phy_id = MARVELL_PHY_ID_88E1240,
		.phy_id_mask = MARVELL_PHY_ID_MASK,
		.name = "Marvell 88E1240",
		/* PHY_GBIT_FEATURES */
		.probe = marvell_probe,
		.config_init = m88e1112_config_init,
		.config_aneg = marvell_config_aneg,
		.config_पूर्णांकr = marvell_config_पूर्णांकr,
		.handle_पूर्णांकerrupt = marvell_handle_पूर्णांकerrupt,
		.resume = genphy_resume,
		.suspend = genphy_suspend,
		.पढ़ो_page = marvell_पढ़ो_page,
		.ग_लिखो_page = marvell_ग_लिखो_page,
		.get_sset_count = marvell_get_sset_count,
		.get_strings = marvell_get_strings,
		.get_stats = marvell_get_stats,
		.get_tunable = m88e1011_get_tunable,
		.set_tunable = m88e1011_set_tunable,
	पूर्ण,
	अणु
		.phy_id = MARVELL_PHY_ID_88E1116R,
		.phy_id_mask = MARVELL_PHY_ID_MASK,
		.name = "Marvell 88E1116R",
		/* PHY_GBIT_FEATURES */
		.probe = marvell_probe,
		.config_init = m88e1116r_config_init,
		.config_पूर्णांकr = marvell_config_पूर्णांकr,
		.handle_पूर्णांकerrupt = marvell_handle_पूर्णांकerrupt,
		.resume = genphy_resume,
		.suspend = genphy_suspend,
		.पढ़ो_page = marvell_पढ़ो_page,
		.ग_लिखो_page = marvell_ग_लिखो_page,
		.get_sset_count = marvell_get_sset_count,
		.get_strings = marvell_get_strings,
		.get_stats = marvell_get_stats,
		.get_tunable = m88e1011_get_tunable,
		.set_tunable = m88e1011_set_tunable,
	पूर्ण,
	अणु
		.phy_id = MARVELL_PHY_ID_88E1510,
		.phy_id_mask = MARVELL_PHY_ID_MASK,
		.name = "Marvell 88E1510",
		.driver_data = DEF_MARVELL_HWMON_OPS(m88e1510_hwmon_ops),
		.features = PHY_GBIT_FIBRE_FEATURES,
		.flags = PHY_POLL_CABLE_TEST,
		.probe = marvell_probe,
		.config_init = m88e1510_config_init,
		.config_aneg = m88e1510_config_aneg,
		.पढ़ो_status = marvell_पढ़ो_status,
		.config_पूर्णांकr = marvell_config_पूर्णांकr,
		.handle_पूर्णांकerrupt = marvell_handle_पूर्णांकerrupt,
		.get_wol = m88e1318_get_wol,
		.set_wol = m88e1318_set_wol,
		.resume = marvell_resume,
		.suspend = marvell_suspend,
		.पढ़ो_page = marvell_पढ़ो_page,
		.ग_लिखो_page = marvell_ग_लिखो_page,
		.get_sset_count = marvell_get_sset_count,
		.get_strings = marvell_get_strings,
		.get_stats = marvell_get_stats,
		.set_loopback = genphy_loopback,
		.get_tunable = m88e1011_get_tunable,
		.set_tunable = m88e1011_set_tunable,
		.cable_test_start = marvell_vct7_cable_test_start,
		.cable_test_tdr_start = marvell_vct5_cable_test_tdr_start,
		.cable_test_get_status = marvell_vct7_cable_test_get_status,
	पूर्ण,
	अणु
		.phy_id = MARVELL_PHY_ID_88E1540,
		.phy_id_mask = MARVELL_PHY_ID_MASK,
		.name = "Marvell 88E1540",
		.driver_data = DEF_MARVELL_HWMON_OPS(m88e1510_hwmon_ops),
		/* PHY_GBIT_FEATURES */
		.flags = PHY_POLL_CABLE_TEST,
		.probe = marvell_probe,
		.config_init = marvell_1011gbe_config_init,
		.config_aneg = m88e1510_config_aneg,
		.पढ़ो_status = marvell_पढ़ो_status,
		.config_पूर्णांकr = marvell_config_पूर्णांकr,
		.handle_पूर्णांकerrupt = marvell_handle_पूर्णांकerrupt,
		.resume = genphy_resume,
		.suspend = genphy_suspend,
		.पढ़ो_page = marvell_पढ़ो_page,
		.ग_लिखो_page = marvell_ग_लिखो_page,
		.get_sset_count = marvell_get_sset_count,
		.get_strings = marvell_get_strings,
		.get_stats = marvell_get_stats,
		.get_tunable = m88e1540_get_tunable,
		.set_tunable = m88e1540_set_tunable,
		.cable_test_start = marvell_vct7_cable_test_start,
		.cable_test_tdr_start = marvell_vct5_cable_test_tdr_start,
		.cable_test_get_status = marvell_vct7_cable_test_get_status,
	पूर्ण,
	अणु
		.phy_id = MARVELL_PHY_ID_88E1545,
		.phy_id_mask = MARVELL_PHY_ID_MASK,
		.name = "Marvell 88E1545",
		.driver_data = DEF_MARVELL_HWMON_OPS(m88e1510_hwmon_ops),
		.probe = marvell_probe,
		/* PHY_GBIT_FEATURES */
		.flags = PHY_POLL_CABLE_TEST,
		.config_init = marvell_1011gbe_config_init,
		.config_aneg = m88e1510_config_aneg,
		.पढ़ो_status = marvell_पढ़ो_status,
		.config_पूर्णांकr = marvell_config_पूर्णांकr,
		.handle_पूर्णांकerrupt = marvell_handle_पूर्णांकerrupt,
		.resume = genphy_resume,
		.suspend = genphy_suspend,
		.पढ़ो_page = marvell_पढ़ो_page,
		.ग_लिखो_page = marvell_ग_लिखो_page,
		.get_sset_count = marvell_get_sset_count,
		.get_strings = marvell_get_strings,
		.get_stats = marvell_get_stats,
		.get_tunable = m88e1540_get_tunable,
		.set_tunable = m88e1540_set_tunable,
		.cable_test_start = marvell_vct7_cable_test_start,
		.cable_test_tdr_start = marvell_vct5_cable_test_tdr_start,
		.cable_test_get_status = marvell_vct7_cable_test_get_status,
	पूर्ण,
	अणु
		.phy_id = MARVELL_PHY_ID_88E3016,
		.phy_id_mask = MARVELL_PHY_ID_MASK,
		.name = "Marvell 88E3016",
		/* PHY_BASIC_FEATURES */
		.probe = marvell_probe,
		.config_init = m88e3016_config_init,
		.aneg_करोne = marvell_aneg_करोne,
		.पढ़ो_status = marvell_पढ़ो_status,
		.config_पूर्णांकr = marvell_config_पूर्णांकr,
		.handle_पूर्णांकerrupt = marvell_handle_पूर्णांकerrupt,
		.resume = genphy_resume,
		.suspend = genphy_suspend,
		.पढ़ो_page = marvell_पढ़ो_page,
		.ग_लिखो_page = marvell_ग_लिखो_page,
		.get_sset_count = marvell_get_sset_count,
		.get_strings = marvell_get_strings,
		.get_stats = marvell_get_stats,
	पूर्ण,
	अणु
		.phy_id = MARVELL_PHY_ID_88E6341_FAMILY,
		.phy_id_mask = MARVELL_PHY_ID_MASK,
		.name = "Marvell 88E6341 Family",
		.driver_data = DEF_MARVELL_HWMON_OPS(m88e1510_hwmon_ops),
		/* PHY_GBIT_FEATURES */
		.flags = PHY_POLL_CABLE_TEST,
		.probe = marvell_probe,
		.config_init = marvell_1011gbe_config_init,
		.config_aneg = m88e6390_config_aneg,
		.पढ़ो_status = marvell_पढ़ो_status,
		.config_पूर्णांकr = marvell_config_पूर्णांकr,
		.handle_पूर्णांकerrupt = marvell_handle_पूर्णांकerrupt,
		.resume = genphy_resume,
		.suspend = genphy_suspend,
		.पढ़ो_page = marvell_पढ़ो_page,
		.ग_लिखो_page = marvell_ग_लिखो_page,
		.get_sset_count = marvell_get_sset_count,
		.get_strings = marvell_get_strings,
		.get_stats = marvell_get_stats,
		.get_tunable = m88e1540_get_tunable,
		.set_tunable = m88e1540_set_tunable,
		.cable_test_start = marvell_vct7_cable_test_start,
		.cable_test_tdr_start = marvell_vct5_cable_test_tdr_start,
		.cable_test_get_status = marvell_vct7_cable_test_get_status,
	पूर्ण,
	अणु
		.phy_id = MARVELL_PHY_ID_88E6390_FAMILY,
		.phy_id_mask = MARVELL_PHY_ID_MASK,
		.name = "Marvell 88E6390 Family",
		.driver_data = DEF_MARVELL_HWMON_OPS(m88e6390_hwmon_ops),
		/* PHY_GBIT_FEATURES */
		.flags = PHY_POLL_CABLE_TEST,
		.probe = marvell_probe,
		.config_init = marvell_1011gbe_config_init,
		.config_aneg = m88e6390_config_aneg,
		.पढ़ो_status = marvell_पढ़ो_status,
		.config_पूर्णांकr = marvell_config_पूर्णांकr,
		.handle_पूर्णांकerrupt = marvell_handle_पूर्णांकerrupt,
		.resume = genphy_resume,
		.suspend = genphy_suspend,
		.पढ़ो_page = marvell_पढ़ो_page,
		.ग_लिखो_page = marvell_ग_लिखो_page,
		.get_sset_count = marvell_get_sset_count,
		.get_strings = marvell_get_strings,
		.get_stats = marvell_get_stats,
		.get_tunable = m88e1540_get_tunable,
		.set_tunable = m88e1540_set_tunable,
		.cable_test_start = marvell_vct7_cable_test_start,
		.cable_test_tdr_start = marvell_vct5_cable_test_tdr_start,
		.cable_test_get_status = marvell_vct7_cable_test_get_status,
	पूर्ण,
	अणु
		.phy_id = MARVELL_PHY_ID_88E6393_FAMILY,
		.phy_id_mask = MARVELL_PHY_ID_MASK,
		.name = "Marvell 88E6393 Family",
		.driver_data = DEF_MARVELL_HWMON_OPS(m88e6393_hwmon_ops),
		/* PHY_GBIT_FEATURES */
		.flags = PHY_POLL_CABLE_TEST,
		.probe = marvell_probe,
		.config_init = marvell_1011gbe_config_init,
		.config_aneg = m88e1510_config_aneg,
		.पढ़ो_status = marvell_पढ़ो_status,
		.config_पूर्णांकr = marvell_config_पूर्णांकr,
		.handle_पूर्णांकerrupt = marvell_handle_पूर्णांकerrupt,
		.resume = genphy_resume,
		.suspend = genphy_suspend,
		.पढ़ो_page = marvell_पढ़ो_page,
		.ग_लिखो_page = marvell_ग_लिखो_page,
		.get_sset_count = marvell_get_sset_count,
		.get_strings = marvell_get_strings,
		.get_stats = marvell_get_stats,
		.get_tunable = m88e1540_get_tunable,
		.set_tunable = m88e1540_set_tunable,
		.cable_test_start = marvell_vct7_cable_test_start,
		.cable_test_tdr_start = marvell_vct5_cable_test_tdr_start,
		.cable_test_get_status = marvell_vct7_cable_test_get_status,
	पूर्ण,
	अणु
		.phy_id = MARVELL_PHY_ID_88E1340S,
		.phy_id_mask = MARVELL_PHY_ID_MASK,
		.name = "Marvell 88E1340S",
		.driver_data = DEF_MARVELL_HWMON_OPS(m88e1510_hwmon_ops),
		.probe = marvell_probe,
		/* PHY_GBIT_FEATURES */
		.config_init = marvell_1011gbe_config_init,
		.config_aneg = m88e1510_config_aneg,
		.पढ़ो_status = marvell_पढ़ो_status,
		.config_पूर्णांकr = marvell_config_पूर्णांकr,
		.handle_पूर्णांकerrupt = marvell_handle_पूर्णांकerrupt,
		.resume = genphy_resume,
		.suspend = genphy_suspend,
		.पढ़ो_page = marvell_पढ़ो_page,
		.ग_लिखो_page = marvell_ग_लिखो_page,
		.get_sset_count = marvell_get_sset_count,
		.get_strings = marvell_get_strings,
		.get_stats = marvell_get_stats,
		.get_tunable = m88e1540_get_tunable,
		.set_tunable = m88e1540_set_tunable,
	पूर्ण,
	अणु
		.phy_id = MARVELL_PHY_ID_88E1548P,
		.phy_id_mask = MARVELL_PHY_ID_MASK,
		.name = "Marvell 88E1548P",
		.driver_data = DEF_MARVELL_HWMON_OPS(m88e1510_hwmon_ops),
		.probe = marvell_probe,
		.features = PHY_GBIT_FIBRE_FEATURES,
		.config_init = marvell_1011gbe_config_init,
		.config_aneg = m88e1510_config_aneg,
		.पढ़ो_status = marvell_पढ़ो_status,
		.config_पूर्णांकr = marvell_config_पूर्णांकr,
		.handle_पूर्णांकerrupt = marvell_handle_पूर्णांकerrupt,
		.resume = genphy_resume,
		.suspend = genphy_suspend,
		.पढ़ो_page = marvell_पढ़ो_page,
		.ग_लिखो_page = marvell_ग_लिखो_page,
		.get_sset_count = marvell_get_sset_count,
		.get_strings = marvell_get_strings,
		.get_stats = marvell_get_stats,
		.get_tunable = m88e1540_get_tunable,
		.set_tunable = m88e1540_set_tunable,
	पूर्ण,
पूर्ण;

module_phy_driver(marvell_drivers);

अटल काष्ठा mdio_device_id __maybe_unused marvell_tbl[] = अणु
	अणु MARVELL_PHY_ID_88E1101, MARVELL_PHY_ID_MASK पूर्ण,
	अणु MARVELL_PHY_ID_88E1112, MARVELL_PHY_ID_MASK पूर्ण,
	अणु MARVELL_PHY_ID_88E1111, MARVELL_PHY_ID_MASK पूर्ण,
	अणु MARVELL_PHY_ID_88E1111_FINISAR, MARVELL_PHY_ID_MASK पूर्ण,
	अणु MARVELL_PHY_ID_88E1118, MARVELL_PHY_ID_MASK पूर्ण,
	अणु MARVELL_PHY_ID_88E1121R, MARVELL_PHY_ID_MASK पूर्ण,
	अणु MARVELL_PHY_ID_88E1145, MARVELL_PHY_ID_MASK पूर्ण,
	अणु MARVELL_PHY_ID_88E1149R, MARVELL_PHY_ID_MASK पूर्ण,
	अणु MARVELL_PHY_ID_88E1240, MARVELL_PHY_ID_MASK पूर्ण,
	अणु MARVELL_PHY_ID_88E1318S, MARVELL_PHY_ID_MASK पूर्ण,
	अणु MARVELL_PHY_ID_88E1116R, MARVELL_PHY_ID_MASK पूर्ण,
	अणु MARVELL_PHY_ID_88E1510, MARVELL_PHY_ID_MASK पूर्ण,
	अणु MARVELL_PHY_ID_88E1540, MARVELL_PHY_ID_MASK पूर्ण,
	अणु MARVELL_PHY_ID_88E1545, MARVELL_PHY_ID_MASK पूर्ण,
	अणु MARVELL_PHY_ID_88E3016, MARVELL_PHY_ID_MASK पूर्ण,
	अणु MARVELL_PHY_ID_88E6341_FAMILY, MARVELL_PHY_ID_MASK पूर्ण,
	अणु MARVELL_PHY_ID_88E6390_FAMILY, MARVELL_PHY_ID_MASK पूर्ण,
	अणु MARVELL_PHY_ID_88E6393_FAMILY, MARVELL_PHY_ID_MASK पूर्ण,
	अणु MARVELL_PHY_ID_88E1340S, MARVELL_PHY_ID_MASK पूर्ण,
	अणु MARVELL_PHY_ID_88E1548P, MARVELL_PHY_ID_MASK पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(mdio, marvell_tbl);
