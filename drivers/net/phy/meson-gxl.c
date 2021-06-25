<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Amlogic Meson GXL Internal PHY Driver
 *
 * Copyright (C) 2015 Amlogic, Inc. All rights reserved.
 * Copyright (C) 2016 BayLibre, SAS. All rights reserved.
 * Author: Neil Armstrong <narmstrong@baylibre.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mii.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/phy.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/bitfield.h>

#घोषणा TSTCNTL		20
#घोषणा  TSTCNTL_READ		BIT(15)
#घोषणा  TSTCNTL_WRITE		BIT(14)
#घोषणा  TSTCNTL_REG_BANK_SEL	GENMASK(12, 11)
#घोषणा  TSTCNTL_TEST_MODE	BIT(10)
#घोषणा  TSTCNTL_READ_ADDRESS	GENMASK(9, 5)
#घोषणा  TSTCNTL_WRITE_ADDRESS	GENMASK(4, 0)
#घोषणा TSTREAD1	21
#घोषणा TSTWRITE	23
#घोषणा INTSRC_FLAG	29
#घोषणा  INTSRC_ANEG_PR		BIT(1)
#घोषणा  INTSRC_PARALLEL_FAULT	BIT(2)
#घोषणा  INTSRC_ANEG_LP_ACK	BIT(3)
#घोषणा  INTSRC_LINK_DOWN	BIT(4)
#घोषणा  INTSRC_REMOTE_FAULT	BIT(5)
#घोषणा  INTSRC_ANEG_COMPLETE	BIT(6)
#घोषणा INTSRC_MASK	30

#घोषणा BANK_ANALOG_DSP		0
#घोषणा BANK_WOL		1
#घोषणा BANK_BIST		3

/* WOL Registers */
#घोषणा LPI_STATUS	0xc
#घोषणा  LPI_STATUS_RSV12	BIT(12)

/* BIST Registers */
#घोषणा FR_PLL_CONTROL	0x1b
#घोषणा FR_PLL_DIV0	0x1c
#घोषणा FR_PLL_DIV1	0x1d

अटल पूर्णांक meson_gxl_खोलो_banks(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	/* Enable Analog and DSP रेजिस्टर Bank access by
	 * toggling TSTCNTL_TEST_MODE bit in the TSTCNTL रेजिस्टर
	 */
	ret = phy_ग_लिखो(phydev, TSTCNTL, 0);
	अगर (ret)
		वापस ret;
	ret = phy_ग_लिखो(phydev, TSTCNTL, TSTCNTL_TEST_MODE);
	अगर (ret)
		वापस ret;
	ret = phy_ग_लिखो(phydev, TSTCNTL, 0);
	अगर (ret)
		वापस ret;
	वापस phy_ग_लिखो(phydev, TSTCNTL, TSTCNTL_TEST_MODE);
पूर्ण

अटल व्योम meson_gxl_बंद_banks(काष्ठा phy_device *phydev)
अणु
	phy_ग_लिखो(phydev, TSTCNTL, 0);
पूर्ण

अटल पूर्णांक meson_gxl_पढ़ो_reg(काष्ठा phy_device *phydev,
			      अचिन्हित पूर्णांक bank, अचिन्हित पूर्णांक reg)
अणु
	पूर्णांक ret;

	ret = meson_gxl_खोलो_banks(phydev);
	अगर (ret)
		जाओ out;

	ret = phy_ग_लिखो(phydev, TSTCNTL, TSTCNTL_READ |
			FIELD_PREP(TSTCNTL_REG_BANK_SEL, bank) |
			TSTCNTL_TEST_MODE |
			FIELD_PREP(TSTCNTL_READ_ADDRESS, reg));
	अगर (ret)
		जाओ out;

	ret = phy_पढ़ो(phydev, TSTREAD1);
out:
	/* Close the bank access on our way out */
	meson_gxl_बंद_banks(phydev);
	वापस ret;
पूर्ण

अटल पूर्णांक meson_gxl_ग_लिखो_reg(काष्ठा phy_device *phydev,
			       अचिन्हित पूर्णांक bank, अचिन्हित पूर्णांक reg,
			       uपूर्णांक16_t value)
अणु
	पूर्णांक ret;

	ret = meson_gxl_खोलो_banks(phydev);
	अगर (ret)
		जाओ out;

	ret = phy_ग_लिखो(phydev, TSTWRITE, value);
	अगर (ret)
		जाओ out;

	ret = phy_ग_लिखो(phydev, TSTCNTL, TSTCNTL_WRITE |
			FIELD_PREP(TSTCNTL_REG_BANK_SEL, bank) |
			TSTCNTL_TEST_MODE |
			FIELD_PREP(TSTCNTL_WRITE_ADDRESS, reg));

out:
	/* Close the bank access on our way out */
	meson_gxl_बंद_banks(phydev);
	वापस ret;
पूर्ण

अटल पूर्णांक meson_gxl_config_init(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	/* Enable fractional PLL */
	ret = meson_gxl_ग_लिखो_reg(phydev, BANK_BIST, FR_PLL_CONTROL, 0x5);
	अगर (ret)
		वापस ret;

	/* Program fraction FR_PLL_DIV1 */
	ret = meson_gxl_ग_लिखो_reg(phydev, BANK_BIST, FR_PLL_DIV1, 0x029a);
	अगर (ret)
		वापस ret;

	/* Program fraction FR_PLL_DIV1 */
	ret = meson_gxl_ग_लिखो_reg(phydev, BANK_BIST, FR_PLL_DIV0, 0xaaaa);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

/* This function is provided to cope with the possible failures of this phy
 * during aneg process. When aneg fails, the PHY reports that aneg is करोne
 * but the value found in MII_LPA is wrong:
 *  - Early failures: MII_LPA is just 0x0001. अगर MII_EXPANSION reports that
 *    the link partner (LP) supports aneg but the LP never acked our base
 *    code word, it is likely that we never sent it to begin with.
 *  - Late failures: MII_LPA is filled with a value which seems to make sense
 *    but it actually is not what the LP is advertising. It seems that we
 *    can detect this using a magic bit in the WOL bank (reg 12 - bit 12).
 *    If this particular bit is not set when aneg is reported being करोne,
 *    it means MII_LPA is likely to be wrong.
 *
 * In both हाल, क्रमcing a restart of the aneg process solve the problem.
 * When this failure happens, the first retry is usually successful but,
 * in some हालs, it may take up to 6 retries to get a decent result
 */
अटल पूर्णांक meson_gxl_पढ़ो_status(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret, wol, lpa, exp;

	अगर (phydev->स्वतःneg == AUTONEG_ENABLE) अणु
		ret = genphy_aneg_करोne(phydev);
		अगर (ret < 0)
			वापस ret;
		अन्यथा अगर (!ret)
			जाओ पढ़ो_status_जारी;

		/* Aneg is करोne, let's check everything is fine */
		wol = meson_gxl_पढ़ो_reg(phydev, BANK_WOL, LPI_STATUS);
		अगर (wol < 0)
			वापस wol;

		lpa = phy_पढ़ो(phydev, MII_LPA);
		अगर (lpa < 0)
			वापस lpa;

		exp = phy_पढ़ो(phydev, MII_EXPANSION);
		अगर (exp < 0)
			वापस exp;

		अगर (!(wol & LPI_STATUS_RSV12) ||
		    ((exp & EXPANSION_NWAY) && !(lpa & LPA_LPACK))) अणु
			/* Looks like aneg failed after all */
			phydev_dbg(phydev, "LPA corruption - aneg restart\n");
			वापस genphy_restart_aneg(phydev);
		पूर्ण
	पूर्ण

पढ़ो_status_जारी:
	वापस genphy_पढ़ो_status(phydev);
पूर्ण

अटल पूर्णांक meson_gxl_ack_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret = phy_पढ़ो(phydev, INTSRC_FLAG);

	वापस ret < 0 ? ret : 0;
पूर्ण

अटल पूर्णांक meson_gxl_config_पूर्णांकr(काष्ठा phy_device *phydev)
अणु
	u16 val;
	पूर्णांक ret;

	अगर (phydev->पूर्णांकerrupts == PHY_INTERRUPT_ENABLED) अणु
		/* Ack any pending IRQ */
		ret = meson_gxl_ack_पूर्णांकerrupt(phydev);
		अगर (ret)
			वापस ret;

		val = INTSRC_ANEG_PR
			| INTSRC_PARALLEL_FAULT
			| INTSRC_ANEG_LP_ACK
			| INTSRC_LINK_DOWN
			| INTSRC_REMOTE_FAULT
			| INTSRC_ANEG_COMPLETE;
		ret = phy_ग_लिखो(phydev, INTSRC_MASK, val);
	पूर्ण अन्यथा अणु
		val = 0;
		ret = phy_ग_लिखो(phydev, INTSRC_MASK, val);

		/* Ack any pending IRQ */
		ret = meson_gxl_ack_पूर्णांकerrupt(phydev);
	पूर्ण

	वापस ret;
पूर्ण

अटल irqवापस_t meson_gxl_handle_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक irq_status;

	irq_status = phy_पढ़ो(phydev, INTSRC_FLAG);
	अगर (irq_status < 0) अणु
		phy_error(phydev);
		वापस IRQ_NONE;
	पूर्ण

	अगर (irq_status == 0)
		वापस IRQ_NONE;

	phy_trigger_machine(phydev);

	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा phy_driver meson_gxl_phy[] = अणु
	अणु
		PHY_ID_MATCH_EXACT(0x01814400),
		.name		= "Meson GXL Internal PHY",
		/* PHY_BASIC_FEATURES */
		.flags		= PHY_IS_INTERNAL,
		.soft_reset     = genphy_soft_reset,
		.config_init	= meson_gxl_config_init,
		.पढ़ो_status	= meson_gxl_पढ़ो_status,
		.config_पूर्णांकr	= meson_gxl_config_पूर्णांकr,
		.handle_पूर्णांकerrupt = meson_gxl_handle_पूर्णांकerrupt,
		.suspend        = genphy_suspend,
		.resume         = genphy_resume,
	पूर्ण, अणु
		PHY_ID_MATCH_EXACT(0x01803301),
		.name		= "Meson G12A Internal PHY",
		/* PHY_BASIC_FEATURES */
		.flags		= PHY_IS_INTERNAL,
		.soft_reset     = genphy_soft_reset,
		.config_पूर्णांकr	= meson_gxl_config_पूर्णांकr,
		.handle_पूर्णांकerrupt = meson_gxl_handle_पूर्णांकerrupt,
		.suspend        = genphy_suspend,
		.resume         = genphy_resume,
	पूर्ण,
पूर्ण;

अटल काष्ठा mdio_device_id __maybe_unused meson_gxl_tbl[] = अणु
	अणु PHY_ID_MATCH_VENDOR(0x01814400) पूर्ण,
	अणु PHY_ID_MATCH_VENDOR(0x01803301) पूर्ण,
	अणु पूर्ण
पूर्ण;

module_phy_driver(meson_gxl_phy);

MODULE_DEVICE_TABLE(mdio, meson_gxl_tbl);

MODULE_DESCRIPTION("Amlogic Meson GXL Internal PHY driver");
MODULE_AUTHOR("Baoqi wang");
MODULE_AUTHOR("Neil Armstrong <narmstrong@baylibre.com>");
MODULE_AUTHOR("Jerome Brunet <jbrunet@baylibre.com>");
MODULE_LICENSE("GPL");
