<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2011 - 2012 Cavium, Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/phy.h>
#समावेश <linux/of.h>

#घोषणा PHY_ID_BCM8706	0x0143bdc1
#घोषणा PHY_ID_BCM8727	0x0143bff0

#घोषणा BCM87XX_PMD_RX_SIGNAL_DETECT	(MII_ADDR_C45 | 0x1000a)
#घोषणा BCM87XX_10GBASER_PCS_STATUS	(MII_ADDR_C45 | 0x30020)
#घोषणा BCM87XX_XGXS_LANE_STATUS	(MII_ADDR_C45 | 0x40018)

#घोषणा BCM87XX_LASI_CONTROL (MII_ADDR_C45 | 0x39002)
#घोषणा BCM87XX_LASI_STATUS (MII_ADDR_C45 | 0x39005)

#अगर IS_ENABLED(CONFIG_OF_MDIO)
/* Set and/or override some configuration रेजिस्टरs based on the
 * broadcom,c45-reg-init property stored in the of_node क्रम the phydev.
 *
 * broadcom,c45-reg-init = <devid reg mask value>,...;
 *
 * There may be one or more sets of <devid reg mask value>:
 *
 * devid: which sub-device to use.
 * reg: the रेजिस्टर.
 * mask: अगर non-zero, ANDed with existing रेजिस्टर value.
 * value: ORed with the masked value and written to the regiser.
 *
 */
अटल पूर्णांक bcm87xx_of_reg_init(काष्ठा phy_device *phydev)
अणु
	स्थिर __be32 *paddr;
	स्थिर __be32 *paddr_end;
	पूर्णांक len, ret;

	अगर (!phydev->mdio.dev.of_node)
		वापस 0;

	paddr = of_get_property(phydev->mdio.dev.of_node,
				"broadcom,c45-reg-init", &len);
	अगर (!paddr)
		वापस 0;

	paddr_end = paddr + (len /= माप(*paddr));

	ret = 0;

	जबतक (paddr + 3 < paddr_end) अणु
		u16 devid	= be32_to_cpup(paddr++);
		u16 reg		= be32_to_cpup(paddr++);
		u16 mask	= be32_to_cpup(paddr++);
		u16 val_bits	= be32_to_cpup(paddr++);
		पूर्णांक val;
		u32 regnum = mdiobus_c45_addr(devid, reg);
		val = 0;
		अगर (mask) अणु
			val = phy_पढ़ो(phydev, regnum);
			अगर (val < 0) अणु
				ret = val;
				जाओ err;
			पूर्ण
			val &= mask;
		पूर्ण
		val |= val_bits;

		ret = phy_ग_लिखो(phydev, regnum, val);
		अगर (ret < 0)
			जाओ err;
	पूर्ण
err:
	वापस ret;
पूर्ण
#अन्यथा
अटल पूर्णांक bcm87xx_of_reg_init(काष्ठा phy_device *phydev)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_OF_MDIO */

अटल पूर्णांक bcm87xx_get_features(काष्ठा phy_device *phydev)
अणु
	linkmode_set_bit(ETHTOOL_LINK_MODE_10000baseR_FEC_BIT,
			 phydev->supported);
	वापस 0;
पूर्ण

अटल पूर्णांक bcm87xx_config_init(काष्ठा phy_device *phydev)
अणु
	वापस bcm87xx_of_reg_init(phydev);
पूर्ण

अटल पूर्णांक bcm87xx_config_aneg(काष्ठा phy_device *phydev)
अणु
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक bcm87xx_पढ़ो_status(काष्ठा phy_device *phydev)
अणु
	पूर्णांक rx_संकेत_detect;
	पूर्णांक pcs_status;
	पूर्णांक xgxs_lane_status;

	rx_संकेत_detect = phy_पढ़ो(phydev, BCM87XX_PMD_RX_SIGNAL_DETECT);
	अगर (rx_संकेत_detect < 0)
		वापस rx_संकेत_detect;

	अगर ((rx_संकेत_detect & 1) == 0)
		जाओ no_link;

	pcs_status = phy_पढ़ो(phydev, BCM87XX_10GBASER_PCS_STATUS);
	अगर (pcs_status < 0)
		वापस pcs_status;

	अगर ((pcs_status & 1) == 0)
		जाओ no_link;

	xgxs_lane_status = phy_पढ़ो(phydev, BCM87XX_XGXS_LANE_STATUS);
	अगर (xgxs_lane_status < 0)
		वापस xgxs_lane_status;

	अगर ((xgxs_lane_status & 0x1000) == 0)
		जाओ no_link;

	phydev->speed = 10000;
	phydev->link = 1;
	phydev->duplex = 1;
	वापस 0;

no_link:
	phydev->link = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक bcm87xx_config_पूर्णांकr(काष्ठा phy_device *phydev)
अणु
	पूर्णांक reg, err;

	reg = phy_पढ़ो(phydev, BCM87XX_LASI_CONTROL);

	अगर (reg < 0)
		वापस reg;

	अगर (phydev->पूर्णांकerrupts == PHY_INTERRUPT_ENABLED) अणु
		err = phy_पढ़ो(phydev, BCM87XX_LASI_STATUS);
		अगर (err)
			वापस err;

		reg |= 1;
		err = phy_ग_लिखो(phydev, BCM87XX_LASI_CONTROL, reg);
	पूर्ण अन्यथा अणु
		reg &= ~1;
		err = phy_ग_लिखो(phydev, BCM87XX_LASI_CONTROL, reg);
		अगर (err)
			वापस err;

		err = phy_पढ़ो(phydev, BCM87XX_LASI_STATUS);
	पूर्ण

	वापस err;
पूर्ण

अटल irqवापस_t bcm87xx_handle_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक irq_status;

	irq_status = phy_पढ़ो(phydev, BCM87XX_LASI_STATUS);
	अगर (irq_status < 0) अणु
		phy_error(phydev);
		वापस IRQ_NONE;
	पूर्ण

	अगर (irq_status == 0)
		वापस IRQ_NONE;

	phy_trigger_machine(phydev);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक bcm8706_match_phy_device(काष्ठा phy_device *phydev)
अणु
	वापस phydev->c45_ids.device_ids[4] == PHY_ID_BCM8706;
पूर्ण

अटल पूर्णांक bcm8727_match_phy_device(काष्ठा phy_device *phydev)
अणु
	वापस phydev->c45_ids.device_ids[4] == PHY_ID_BCM8727;
पूर्ण

अटल काष्ठा phy_driver bcm87xx_driver[] = अणु
अणु
	.phy_id		= PHY_ID_BCM8706,
	.phy_id_mask	= 0xffffffff,
	.name		= "Broadcom BCM8706",
	.get_features	= bcm87xx_get_features,
	.config_init	= bcm87xx_config_init,
	.config_aneg	= bcm87xx_config_aneg,
	.पढ़ो_status	= bcm87xx_पढ़ो_status,
	.config_पूर्णांकr	= bcm87xx_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = bcm87xx_handle_पूर्णांकerrupt,
	.match_phy_device = bcm8706_match_phy_device,
पूर्ण, अणु
	.phy_id		= PHY_ID_BCM8727,
	.phy_id_mask	= 0xffffffff,
	.name		= "Broadcom BCM8727",
	.get_features	= bcm87xx_get_features,
	.config_init	= bcm87xx_config_init,
	.config_aneg	= bcm87xx_config_aneg,
	.पढ़ो_status	= bcm87xx_पढ़ो_status,
	.config_पूर्णांकr	= bcm87xx_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = bcm87xx_handle_पूर्णांकerrupt,
	.match_phy_device = bcm8727_match_phy_device,
पूर्ण पूर्ण;

module_phy_driver(bcm87xx_driver);

MODULE_LICENSE("GPL v2");
