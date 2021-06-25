<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम AMD am79c PHYs
 *
 * Author: Heiko Schocher <hs@denx.de>
 *
 * Copyright (c) 2011 DENX Software Engineering GmbH
 */
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/mii.h>
#समावेश <linux/phy.h>

#घोषणा PHY_ID_AM79C874		0x0022561b

#घोषणा MII_AM79C_IR		17	/* Interrupt Status/Control Register */
#घोषणा MII_AM79C_IR_EN_LINK	0x0400	/* IR enable Linkstate */
#घोषणा MII_AM79C_IR_EN_ANEG	0x0100	/* IR enable Aneg Complete */
#घोषणा MII_AM79C_IR_IMASK_INIT	(MII_AM79C_IR_EN_LINK | MII_AM79C_IR_EN_ANEG)

#घोषणा MII_AM79C_IR_LINK_DOWN	BIT(2)
#घोषणा MII_AM79C_IR_ANEG_DONE	BIT(0)
#घोषणा MII_AM79C_IR_IMASK_STAT	(MII_AM79C_IR_LINK_DOWN | MII_AM79C_IR_ANEG_DONE)

MODULE_DESCRIPTION("AMD PHY driver");
MODULE_AUTHOR("Heiko Schocher <hs@denx.de>");
MODULE_LICENSE("GPL");

अटल पूर्णांक am79c_ack_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	err = phy_पढ़ो(phydev, MII_BMSR);
	अगर (err < 0)
		वापस err;

	err = phy_पढ़ो(phydev, MII_AM79C_IR);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक am79c_config_init(काष्ठा phy_device *phydev)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक am79c_config_पूर्णांकr(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	अगर (phydev->पूर्णांकerrupts == PHY_INTERRUPT_ENABLED) अणु
		err = am79c_ack_पूर्णांकerrupt(phydev);
		अगर (err)
			वापस err;

		err = phy_ग_लिखो(phydev, MII_AM79C_IR, MII_AM79C_IR_IMASK_INIT);
	पूर्ण अन्यथा अणु
		err = phy_ग_लिखो(phydev, MII_AM79C_IR, 0);
		अगर (err)
			वापस err;

		err = am79c_ack_पूर्णांकerrupt(phydev);
	पूर्ण

	वापस err;
पूर्ण

अटल irqवापस_t am79c_handle_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक irq_status;

	irq_status = phy_पढ़ो(phydev, MII_AM79C_IR);
	अगर (irq_status < 0) अणु
		phy_error(phydev);
		वापस IRQ_NONE;
	पूर्ण

	अगर (!(irq_status & MII_AM79C_IR_IMASK_STAT))
		वापस IRQ_NONE;

	phy_trigger_machine(phydev);

	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा phy_driver am79c_driver[] = अणु अणु
	.phy_id		= PHY_ID_AM79C874,
	.name		= "AM79C874",
	.phy_id_mask	= 0xfffffff0,
	/* PHY_BASIC_FEATURES */
	.config_init	= am79c_config_init,
	.config_पूर्णांकr	= am79c_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = am79c_handle_पूर्णांकerrupt,
पूर्ण पूर्ण;

module_phy_driver(am79c_driver);

अटल काष्ठा mdio_device_id __maybe_unused amd_tbl[] = अणु
	अणु PHY_ID_AM79C874, 0xfffffff0 पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(mdio, amd_tbl);
