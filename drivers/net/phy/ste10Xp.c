<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * drivers/net/phy/ste10Xp.c
 *
 * Driver क्रम STMicroelectronics STe10Xp PHYs
 *
 * Author: Giuseppe Cavallaro <peppe.cavallaro@st.com>
 *
 * Copyright (c) 2008 STMicroelectronics Limited
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/mii.h>
#समावेश <linux/phy.h>

#घोषणा MII_XCIIS   	0x11	/* Configuration Info IRQ & Status Reg */
#घोषणा MII_XIE     	0x12	/* Interrupt Enable Register */
#घोषणा MII_XIE_DEFAULT_MASK 0x0070 /* ANE complete, Remote Fault, Link Down */

#घोषणा STE101P_PHY_ID		0x00061c50
#घोषणा STE100P_PHY_ID       	0x1c040011

अटल पूर्णांक ste10Xp_config_init(काष्ठा phy_device *phydev)
अणु
	पूर्णांक value, err;

	/* Software Reset PHY */
	value = phy_पढ़ो(phydev, MII_BMCR);
	अगर (value < 0)
		वापस value;

	value |= BMCR_RESET;
	err = phy_ग_लिखो(phydev, MII_BMCR, value);
	अगर (err < 0)
		वापस err;

	करो अणु
		value = phy_पढ़ो(phydev, MII_BMCR);
	पूर्ण जबतक (value & BMCR_RESET);

	वापस 0;
पूर्ण

अटल पूर्णांक ste10Xp_ack_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err = phy_पढ़ो(phydev, MII_XCIIS);

	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक ste10Xp_config_पूर्णांकr(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	अगर (phydev->पूर्णांकerrupts == PHY_INTERRUPT_ENABLED) अणु
		/* clear any pending पूर्णांकerrupts */
		err = ste10Xp_ack_पूर्णांकerrupt(phydev);
		अगर (err)
			वापस err;

		/* Enable all STe101P पूर्णांकerrupts (PR12) */
		err = phy_ग_लिखो(phydev, MII_XIE, MII_XIE_DEFAULT_MASK);
	पूर्ण अन्यथा अणु
		err = phy_ग_लिखो(phydev, MII_XIE, 0);
		अगर (err)
			वापस err;

		err = ste10Xp_ack_पूर्णांकerrupt(phydev);
	पूर्ण

	वापस err;
पूर्ण

अटल irqवापस_t ste10Xp_handle_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक irq_status;

	irq_status = phy_पढ़ो(phydev, MII_XCIIS);
	अगर (irq_status < 0) अणु
		phy_error(phydev);
		वापस IRQ_NONE;
	पूर्ण

	अगर (!(irq_status & MII_XIE_DEFAULT_MASK))
		वापस IRQ_NONE;

	phy_trigger_machine(phydev);

	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा phy_driver ste10xp_pdriver[] = अणु
अणु
	.phy_id = STE101P_PHY_ID,
	.phy_id_mask = 0xfffffff0,
	.name = "STe101p",
	/* PHY_BASIC_FEATURES */
	.config_init = ste10Xp_config_init,
	.config_पूर्णांकr = ste10Xp_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = ste10Xp_handle_पूर्णांकerrupt,
	.suspend = genphy_suspend,
	.resume = genphy_resume,
पूर्ण, अणु
	.phy_id = STE100P_PHY_ID,
	.phy_id_mask = 0xffffffff,
	.name = "STe100p",
	/* PHY_BASIC_FEATURES */
	.config_init = ste10Xp_config_init,
	.config_पूर्णांकr = ste10Xp_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = ste10Xp_handle_पूर्णांकerrupt,
	.suspend = genphy_suspend,
	.resume = genphy_resume,
पूर्ण पूर्ण;

module_phy_driver(ste10xp_pdriver);

अटल काष्ठा mdio_device_id __maybe_unused ste10Xp_tbl[] = अणु
	अणु STE101P_PHY_ID, 0xfffffff0 पूर्ण,
	अणु STE100P_PHY_ID, 0xffffffff पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(mdio, ste10Xp_tbl);

MODULE_DESCRIPTION("STMicroelectronics STe10Xp PHY driver");
MODULE_AUTHOR("Giuseppe Cavallaro <peppe.cavallaro@st.com>");
MODULE_LICENSE("GPL");
