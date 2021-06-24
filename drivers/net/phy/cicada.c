<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * drivers/net/phy/cicada.c
 *
 * Driver क्रम Cicada PHYs
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

#समावेश <linux/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <linux/uaccess.h>

/* Cicada Extended Control Register 1 */
#घोषणा MII_CIS8201_EXT_CON1           0x17
#घोषणा MII_CIS8201_EXTCON1_INIT       0x0000

/* Cicada Interrupt Mask Register */
#घोषणा MII_CIS8201_IMASK		0x19
#घोषणा MII_CIS8201_IMASK_IEN		0x8000
#घोषणा MII_CIS8201_IMASK_SPEED	0x4000
#घोषणा MII_CIS8201_IMASK_LINK		0x2000
#घोषणा MII_CIS8201_IMASK_DUPLEX	0x1000
#घोषणा MII_CIS8201_IMASK_MASK		0xf000

/* Cicada Interrupt Status Register */
#घोषणा MII_CIS8201_ISTAT		0x1a
#घोषणा MII_CIS8201_ISTAT_STATUS	0x8000
#घोषणा MII_CIS8201_ISTAT_SPEED	0x4000
#घोषणा MII_CIS8201_ISTAT_LINK		0x2000
#घोषणा MII_CIS8201_ISTAT_DUPLEX	0x1000

/* Cicada Auxiliary Control/Status Register */
#घोषणा MII_CIS8201_AUX_CONSTAT        0x1c
#घोषणा MII_CIS8201_AUXCONSTAT_INIT    0x0004
#घोषणा MII_CIS8201_AUXCONSTAT_DUPLEX  0x0020
#घोषणा MII_CIS8201_AUXCONSTAT_SPEED   0x0018
#घोषणा MII_CIS8201_AUXCONSTAT_GBIT    0x0010
#घोषणा MII_CIS8201_AUXCONSTAT_100     0x0008

MODULE_DESCRIPTION("Cicadia PHY driver");
MODULE_AUTHOR("Andy Fleming");
MODULE_LICENSE("GPL");

अटल पूर्णांक cis820x_config_init(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	err = phy_ग_लिखो(phydev, MII_CIS8201_AUX_CONSTAT,
			MII_CIS8201_AUXCONSTAT_INIT);

	अगर (err < 0)
		वापस err;

	err = phy_ग_लिखो(phydev, MII_CIS8201_EXT_CON1,
			MII_CIS8201_EXTCON1_INIT);

	वापस err;
पूर्ण

अटल पूर्णांक cis820x_ack_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err = phy_पढ़ो(phydev, MII_CIS8201_ISTAT);

	वापस (err < 0) ? err : 0;
पूर्ण

अटल पूर्णांक cis820x_config_पूर्णांकr(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	अगर (phydev->पूर्णांकerrupts == PHY_INTERRUPT_ENABLED) अणु
		err = cis820x_ack_पूर्णांकerrupt(phydev);
		अगर (err)
			वापस err;

		err = phy_ग_लिखो(phydev, MII_CIS8201_IMASK,
				MII_CIS8201_IMASK_MASK);
	पूर्ण अन्यथा अणु
		err = phy_ग_लिखो(phydev, MII_CIS8201_IMASK, 0);
		अगर (err)
			वापस err;

		err = cis820x_ack_पूर्णांकerrupt(phydev);
	पूर्ण

	वापस err;
पूर्ण

अटल irqवापस_t cis820x_handle_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक irq_status;

	irq_status = phy_पढ़ो(phydev, MII_CIS8201_ISTAT);
	अगर (irq_status < 0) अणु
		phy_error(phydev);
		वापस IRQ_NONE;
	पूर्ण

	अगर (!(irq_status & MII_CIS8201_IMASK_MASK))
		वापस IRQ_NONE;

	phy_trigger_machine(phydev);

	वापस IRQ_HANDLED;
पूर्ण

/* Cicada 8201, a.k.a Vitesse VSC8201 */
अटल काष्ठा phy_driver cis820x_driver[] = अणु
अणु
	.phy_id		= 0x000fc410,
	.name		= "Cicada Cis8201",
	.phy_id_mask	= 0x000ffff0,
	/* PHY_GBIT_FEATURES */
	.config_init	= &cis820x_config_init,
	.config_पूर्णांकr	= &cis820x_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = &cis820x_handle_पूर्णांकerrupt,
पूर्ण, अणु
	.phy_id		= 0x000fc440,
	.name		= "Cicada Cis8204",
	.phy_id_mask	= 0x000fffc0,
	/* PHY_GBIT_FEATURES */
	.config_init	= &cis820x_config_init,
	.config_पूर्णांकr	= &cis820x_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = &cis820x_handle_पूर्णांकerrupt,
पूर्ण पूर्ण;

module_phy_driver(cis820x_driver);

अटल काष्ठा mdio_device_id __maybe_unused cicada_tbl[] = अणु
	अणु 0x000fc410, 0x000ffff0 पूर्ण,
	अणु 0x000fc440, 0x000fffc0 पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(mdio, cicada_tbl);
