<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * drivers/net/phy/davicom.c
 *
 * Driver क्रम Davicom PHYs
 *
 * Author: Andy Fleming
 *
 * Copyright (c) 2004 Freescale Semiconductor, Inc.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/unistd.h>
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
#समावेश <linux/phy.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <linux/uaccess.h>

#घोषणा MII_DM9161_SCR		0x10
#घोषणा MII_DM9161_SCR_INIT	0x0610
#घोषणा MII_DM9161_SCR_RMII	0x0100

/* DM9161 Interrupt Register */
#घोषणा MII_DM9161_INTR	0x15
#घोषणा MII_DM9161_INTR_PEND		0x8000
#घोषणा MII_DM9161_INTR_DPLX_MASK	0x0800
#घोषणा MII_DM9161_INTR_SPD_MASK	0x0400
#घोषणा MII_DM9161_INTR_LINK_MASK	0x0200
#घोषणा MII_DM9161_INTR_MASK		0x0100
#घोषणा MII_DM9161_INTR_DPLX_CHANGE	0x0010
#घोषणा MII_DM9161_INTR_SPD_CHANGE	0x0008
#घोषणा MII_DM9161_INTR_LINK_CHANGE	0x0004
#घोषणा MII_DM9161_INTR_INIT 		0x0000
#घोषणा MII_DM9161_INTR_STOP	\
(MII_DM9161_INTR_DPLX_MASK | MII_DM9161_INTR_SPD_MASK \
 | MII_DM9161_INTR_LINK_MASK | MII_DM9161_INTR_MASK)
#घोषणा MII_DM9161_INTR_CHANGE	\
	(MII_DM9161_INTR_DPLX_CHANGE | \
	 MII_DM9161_INTR_SPD_CHANGE | \
	 MII_DM9161_INTR_LINK_CHANGE)

/* DM9161 10BT Configuration/Status */
#घोषणा MII_DM9161_10BTCSR	0x12
#घोषणा MII_DM9161_10BTCSR_INIT	0x7800

MODULE_DESCRIPTION("Davicom PHY driver");
MODULE_AUTHOR("Andy Fleming");
MODULE_LICENSE("GPL");


अटल पूर्णांक dm9161_ack_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err = phy_पढ़ो(phydev, MII_DM9161_INTR);

	वापस (err < 0) ? err : 0;
पूर्ण

#घोषणा DM9161_DELAY 1
अटल पूर्णांक dm9161_config_पूर्णांकr(काष्ठा phy_device *phydev)
अणु
	पूर्णांक temp, err;

	temp = phy_पढ़ो(phydev, MII_DM9161_INTR);

	अगर (temp < 0)
		वापस temp;

	अगर (phydev->पूर्णांकerrupts == PHY_INTERRUPT_ENABLED) अणु
		err = dm9161_ack_पूर्णांकerrupt(phydev);
		अगर (err)
			वापस err;

		temp &= ~(MII_DM9161_INTR_STOP);
		err = phy_ग_लिखो(phydev, MII_DM9161_INTR, temp);
	पूर्ण अन्यथा अणु
		temp |= MII_DM9161_INTR_STOP;
		err = phy_ग_लिखो(phydev, MII_DM9161_INTR, temp);
		अगर (err)
			वापस err;

		err = dm9161_ack_पूर्णांकerrupt(phydev);
	पूर्ण

	वापस err;
पूर्ण

अटल irqवापस_t dm9161_handle_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक irq_status;

	irq_status = phy_पढ़ो(phydev, MII_DM9161_INTR);
	अगर (irq_status < 0) अणु
		phy_error(phydev);
		वापस IRQ_NONE;
	पूर्ण

	अगर (!(irq_status & MII_DM9161_INTR_CHANGE))
		वापस IRQ_NONE;

	phy_trigger_machine(phydev);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक dm9161_config_aneg(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	/* Isolate the PHY */
	err = phy_ग_लिखो(phydev, MII_BMCR, BMCR_ISOLATE);

	अगर (err < 0)
		वापस err;

	/* Configure the new settings */
	err = genphy_config_aneg(phydev);

	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक dm9161_config_init(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err, temp;

	/* Isolate the PHY */
	err = phy_ग_लिखो(phydev, MII_BMCR, BMCR_ISOLATE);

	अगर (err < 0)
		वापस err;

	चयन (phydev->पूर्णांकerface) अणु
	हाल PHY_INTERFACE_MODE_MII:
		temp = MII_DM9161_SCR_INIT;
		अवरोध;
	हाल PHY_INTERFACE_MODE_RMII:
		temp =  MII_DM9161_SCR_INIT | MII_DM9161_SCR_RMII;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Do not bypass the scrambler/descrambler */
	err = phy_ग_लिखो(phydev, MII_DM9161_SCR, temp);
	अगर (err < 0)
		वापस err;

	/* Clear 10BTCSR to शेष */
	err = phy_ग_लिखो(phydev, MII_DM9161_10BTCSR, MII_DM9161_10BTCSR_INIT);

	अगर (err < 0)
		वापस err;

	/* Reconnect the PHY, and enable Autonegotiation */
	वापस phy_ग_लिखो(phydev, MII_BMCR, BMCR_ANENABLE);
पूर्ण

अटल काष्ठा phy_driver dm91xx_driver[] = अणु
अणु
	.phy_id		= 0x0181b880,
	.name		= "Davicom DM9161E",
	.phy_id_mask	= 0x0ffffff0,
	/* PHY_BASIC_FEATURES */
	.config_init	= dm9161_config_init,
	.config_aneg	= dm9161_config_aneg,
	.config_पूर्णांकr	= dm9161_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = dm9161_handle_पूर्णांकerrupt,
पूर्ण, अणु
	.phy_id		= 0x0181b8b0,
	.name		= "Davicom DM9161B/C",
	.phy_id_mask	= 0x0ffffff0,
	/* PHY_BASIC_FEATURES */
	.config_init	= dm9161_config_init,
	.config_aneg	= dm9161_config_aneg,
	.config_पूर्णांकr	= dm9161_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = dm9161_handle_पूर्णांकerrupt,
पूर्ण, अणु
	.phy_id		= 0x0181b8a0,
	.name		= "Davicom DM9161A",
	.phy_id_mask	= 0x0ffffff0,
	/* PHY_BASIC_FEATURES */
	.config_init	= dm9161_config_init,
	.config_aneg	= dm9161_config_aneg,
	.config_पूर्णांकr	= dm9161_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = dm9161_handle_पूर्णांकerrupt,
पूर्ण, अणु
	.phy_id		= 0x00181b80,
	.name		= "Davicom DM9131",
	.phy_id_mask	= 0x0ffffff0,
	/* PHY_BASIC_FEATURES */
	.config_पूर्णांकr	= dm9161_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = dm9161_handle_पूर्णांकerrupt,
पूर्ण पूर्ण;

module_phy_driver(dm91xx_driver);

अटल काष्ठा mdio_device_id __maybe_unused davicom_tbl[] = अणु
	अणु 0x0181b880, 0x0ffffff0 पूर्ण,
	अणु 0x0181b8b0, 0x0ffffff0 पूर्ण,
	अणु 0x0181b8a0, 0x0ffffff0 पूर्ण,
	अणु 0x00181b80, 0x0ffffff0 पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(mdio, davicom_tbl);
