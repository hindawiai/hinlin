<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * drivers/net/phy/et1011c.c
 *
 * Driver क्रम LSI ET1011C PHYs
 *
 * Author: Chaithrika U S
 *
 * Copyright (c) 2008 Texas Instruments
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
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/irq.h>

#घोषणा ET1011C_STATUS_REG	(0x1A)
#घोषणा ET1011C_CONFIG_REG	(0x16)
#घोषणा ET1011C_SPEED_MASK		(0x0300)
#घोषणा ET1011C_GIGABIT_SPEED		(0x0200)
#घोषणा ET1011C_TX_FIFO_MASK		(0x3000)
#घोषणा ET1011C_TX_FIFO_DEPTH_8		(0x0000)
#घोषणा ET1011C_TX_FIFO_DEPTH_16	(0x1000)
#घोषणा ET1011C_INTERFACE_MASK		(0x0007)
#घोषणा ET1011C_GMII_INTERFACE		(0x0002)
#घोषणा ET1011C_SYS_CLK_EN		(0x01 << 4)


MODULE_DESCRIPTION("LSI ET1011C PHY driver");
MODULE_AUTHOR("Chaithrika U S");
MODULE_LICENSE("GPL");

अटल पूर्णांक et1011c_config_aneg(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ctl = 0;
	ctl = phy_पढ़ो(phydev, MII_BMCR);
	अगर (ctl < 0)
		वापस ctl;
	ctl &= ~(BMCR_FULLDPLX | BMCR_SPEED100 | BMCR_SPEED1000 |
		 BMCR_ANENABLE);
	/* First clear the PHY */
	phy_ग_लिखो(phydev, MII_BMCR, ctl | BMCR_RESET);

	वापस genphy_config_aneg(phydev);
पूर्ण

अटल पूर्णांक et1011c_पढ़ो_status(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;
	u32 val;
	अटल पूर्णांक speed;
	ret = genphy_पढ़ो_status(phydev);

	अगर (speed != phydev->speed) अणु
		speed = phydev->speed;
		val = phy_पढ़ो(phydev, ET1011C_STATUS_REG);
		अगर ((val & ET1011C_SPEED_MASK) ==
					ET1011C_GIGABIT_SPEED) अणु
			val = phy_पढ़ो(phydev, ET1011C_CONFIG_REG);
			val &= ~ET1011C_TX_FIFO_MASK;
			phy_ग_लिखो(phydev, ET1011C_CONFIG_REG, val\
					| ET1011C_GMII_INTERFACE\
					| ET1011C_SYS_CLK_EN\
					| ET1011C_TX_FIFO_DEPTH_16);

		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल काष्ठा phy_driver et1011c_driver[] = अणु अणु
	.phy_id		= 0x0282f014,
	.name		= "ET1011C",
	.phy_id_mask	= 0xfffffff0,
	/* PHY_GBIT_FEATURES */
	.config_aneg	= et1011c_config_aneg,
	.पढ़ो_status	= et1011c_पढ़ो_status,
पूर्ण पूर्ण;

module_phy_driver(et1011c_driver);

अटल काष्ठा mdio_device_id __maybe_unused et1011c_tbl[] = अणु
	अणु 0x0282f014, 0xfffffff0 पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(mdio, et1011c_tbl);
