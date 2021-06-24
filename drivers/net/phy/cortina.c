<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *    Copyright 2017 NXP
 *
 *    CORTINA is a रेजिस्टरed trademark of Cortina Systems, Inc.
 *
 */
#समावेश <linux/module.h>
#समावेश <linux/phy.h>

#घोषणा PHY_ID_CS4340	0x13e51002

#घोषणा VILLA_GLOBAL_CHIP_ID_LSB			0x0
#घोषणा VILLA_GLOBAL_CHIP_ID_MSB			0x1

#घोषणा VILLA_GLOBAL_GPIO_1_INTS			0x017

अटल पूर्णांक cortina_पढ़ो_reg(काष्ठा phy_device *phydev, u16 regnum)
अणु
	वापस mdiobus_c45_पढ़ो(phydev->mdio.bus, phydev->mdio.addr, 0, regnum);
पूर्ण

अटल पूर्णांक cortina_पढ़ो_status(काष्ठा phy_device *phydev)
अणु
	पूर्णांक gpio_पूर्णांक_status, ret = 0;

	gpio_पूर्णांक_status = cortina_पढ़ो_reg(phydev, VILLA_GLOBAL_GPIO_1_INTS);
	अगर (gpio_पूर्णांक_status < 0) अणु
		ret = gpio_पूर्णांक_status;
		जाओ err;
	पूर्ण

	अगर (gpio_पूर्णांक_status & 0x8) अणु
		/* up when edc_convergedS set */
		phydev->speed = SPEED_10000;
		phydev->duplex = DUPLEX_FULL;
		phydev->link = 1;
	पूर्ण अन्यथा अणु
		phydev->link = 0;
	पूर्ण

err:
	वापस ret;
पूर्ण

अटल पूर्णांक cortina_probe(काष्ठा phy_device *phydev)
अणु
	u32 phy_id = 0;
	पूर्णांक id_lsb = 0, id_msb = 0;

	/* Read device id from phy रेजिस्टरs. */
	id_lsb = cortina_पढ़ो_reg(phydev, VILLA_GLOBAL_CHIP_ID_LSB);
	अगर (id_lsb < 0)
		वापस -ENXIO;

	phy_id = id_lsb << 16;

	id_msb = cortina_पढ़ो_reg(phydev, VILLA_GLOBAL_CHIP_ID_MSB);
	अगर (id_msb < 0)
		वापस -ENXIO;

	phy_id |= id_msb;

	/* Make sure the device tree binding matched the driver with the
	 * right device.
	 */
	अगर (phy_id != phydev->drv->phy_id) अणु
		phydev_err(phydev, "Error matching phy with %s driver\n",
			   phydev->drv->name);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा phy_driver cortina_driver[] = अणु
अणु
	.phy_id		= PHY_ID_CS4340,
	.phy_id_mask	= 0xffffffff,
	.name		= "Cortina CS4340",
	.features       = PHY_10GBIT_FEATURES,
	.config_aneg	= gen10g_config_aneg,
	.पढ़ो_status	= cortina_पढ़ो_status,
	.probe		= cortina_probe,
पूर्ण,
पूर्ण;

module_phy_driver(cortina_driver);

अटल काष्ठा mdio_device_id __maybe_unused cortina_tbl[] = अणु
	अणु PHY_ID_CS4340, 0xffffffffपूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(mdio, cortina_tbl);

MODULE_DESCRIPTION("Cortina EDC CDR 10G Ethernet PHY driver");
MODULE_AUTHOR("NXP");
MODULE_LICENSE("GPL");
