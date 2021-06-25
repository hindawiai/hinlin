<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * drivers/net/phy/micrel.c
 *
 * Driver क्रम Micrel PHYs
 *
 * Author: David J. Choi
 *
 * Copyright (c) 2010-2013 Micrel, Inc.
 * Copyright (c) 2014 Johan Hovold <johan@kernel.org>
 *
 * Support : Micrel Phys:
 *		Giga phys: ksz9021, ksz9031, ksz9131
 *		100/10 Phys : ksz8001, ksz8721, ksz8737, ksz8041
 *			   ksz8021, ksz8031, ksz8051,
 *			   ksz8081, ksz8091,
 *			   ksz8061,
 *		Switch : ksz8873, ksz886x
 *			 ksz9477
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/phy.h>
#समावेश <linux/micrel_phy.h>
#समावेश <linux/of.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>

/* Operation Mode Strap Override */
#घोषणा MII_KSZPHY_OMSO				0x16
#घोषणा KSZPHY_OMSO_FACTORY_TEST		BIT(15)
#घोषणा KSZPHY_OMSO_B_CAST_OFF			BIT(9)
#घोषणा KSZPHY_OMSO_न_अंकD_TREE_ON		BIT(5)
#घोषणा KSZPHY_OMSO_RMII_OVERRIDE		BIT(1)
#घोषणा KSZPHY_OMSO_MII_OVERRIDE		BIT(0)

/* general Interrupt control/status reg in venकरोr specअगरic block. */
#घोषणा MII_KSZPHY_INTCS			0x1B
#घोषणा	KSZPHY_INTCS_JABBER			BIT(15)
#घोषणा	KSZPHY_INTCS_RECEIVE_ERR		BIT(14)
#घोषणा	KSZPHY_INTCS_PAGE_RECEIVE		BIT(13)
#घोषणा	KSZPHY_INTCS_PARELLEL			BIT(12)
#घोषणा	KSZPHY_INTCS_LINK_PARTNER_ACK		BIT(11)
#घोषणा	KSZPHY_INTCS_LINK_DOWN			BIT(10)
#घोषणा	KSZPHY_INTCS_REMOTE_FAULT		BIT(9)
#घोषणा	KSZPHY_INTCS_LINK_UP			BIT(8)
#घोषणा	KSZPHY_INTCS_ALL			(KSZPHY_INTCS_LINK_UP |\
						KSZPHY_INTCS_LINK_DOWN)
#घोषणा	KSZPHY_INTCS_LINK_DOWN_STATUS		BIT(2)
#घोषणा	KSZPHY_INTCS_LINK_UP_STATUS		BIT(0)
#घोषणा	KSZPHY_INTCS_STATUS			(KSZPHY_INTCS_LINK_DOWN_STATUS |\
						 KSZPHY_INTCS_LINK_UP_STATUS)

/* PHY Control 1 */
#घोषणा	MII_KSZPHY_CTRL_1			0x1e

/* PHY Control 2 / PHY Control (अगर no PHY Control 1) */
#घोषणा	MII_KSZPHY_CTRL_2			0x1f
#घोषणा	MII_KSZPHY_CTRL				MII_KSZPHY_CTRL_2
/* biपंचांगap of PHY रेजिस्टर to set पूर्णांकerrupt mode */
#घोषणा KSZPHY_CTRL_INT_ACTIVE_HIGH		BIT(9)
#घोषणा KSZPHY_RMII_REF_CLK_SEL			BIT(7)

/* Write/पढ़ो to/from extended रेजिस्टरs */
#घोषणा MII_KSZPHY_EXTREG                       0x0b
#घोषणा KSZPHY_EXTREG_WRITE                     0x8000

#घोषणा MII_KSZPHY_EXTREG_WRITE                 0x0c
#घोषणा MII_KSZPHY_EXTREG_READ                  0x0d

/* Extended रेजिस्टरs */
#घोषणा MII_KSZPHY_CLK_CONTROL_PAD_SKEW         0x104
#घोषणा MII_KSZPHY_RX_DATA_PAD_SKEW             0x105
#घोषणा MII_KSZPHY_TX_DATA_PAD_SKEW             0x106

#घोषणा PS_TO_REG				200

काष्ठा kszphy_hw_stat अणु
	स्थिर अक्षर *string;
	u8 reg;
	u8 bits;
पूर्ण;

अटल काष्ठा kszphy_hw_stat kszphy_hw_stats[] = अणु
	अणु "phy_receive_errors", 21, 16पूर्ण,
	अणु "phy_idle_errors", 10, 8 पूर्ण,
पूर्ण;

काष्ठा kszphy_type अणु
	u32 led_mode_reg;
	u16 पूर्णांकerrupt_level_mask;
	bool has_broadcast_disable;
	bool has_nand_tree_disable;
	bool has_rmii_ref_clk_sel;
पूर्ण;

काष्ठा kszphy_priv अणु
	स्थिर काष्ठा kszphy_type *type;
	पूर्णांक led_mode;
	bool rmii_ref_clk_sel;
	bool rmii_ref_clk_sel_val;
	u64 stats[ARRAY_SIZE(kszphy_hw_stats)];
पूर्ण;

अटल स्थिर काष्ठा kszphy_type ksz8021_type = अणु
	.led_mode_reg		= MII_KSZPHY_CTRL_2,
	.has_broadcast_disable	= true,
	.has_nand_tree_disable	= true,
	.has_rmii_ref_clk_sel	= true,
पूर्ण;

अटल स्थिर काष्ठा kszphy_type ksz8041_type = अणु
	.led_mode_reg		= MII_KSZPHY_CTRL_1,
पूर्ण;

अटल स्थिर काष्ठा kszphy_type ksz8051_type = अणु
	.led_mode_reg		= MII_KSZPHY_CTRL_2,
	.has_nand_tree_disable	= true,
पूर्ण;

अटल स्थिर काष्ठा kszphy_type ksz8081_type = अणु
	.led_mode_reg		= MII_KSZPHY_CTRL_2,
	.has_broadcast_disable	= true,
	.has_nand_tree_disable	= true,
	.has_rmii_ref_clk_sel	= true,
पूर्ण;

अटल स्थिर काष्ठा kszphy_type ks8737_type = अणु
	.पूर्णांकerrupt_level_mask	= BIT(14),
पूर्ण;

अटल स्थिर काष्ठा kszphy_type ksz9021_type = अणु
	.पूर्णांकerrupt_level_mask	= BIT(14),
पूर्ण;

अटल पूर्णांक kszphy_extended_ग_लिखो(काष्ठा phy_device *phydev,
				u32 regnum, u16 val)
अणु
	phy_ग_लिखो(phydev, MII_KSZPHY_EXTREG, KSZPHY_EXTREG_WRITE | regnum);
	वापस phy_ग_लिखो(phydev, MII_KSZPHY_EXTREG_WRITE, val);
पूर्ण

अटल पूर्णांक kszphy_extended_पढ़ो(काष्ठा phy_device *phydev,
				u32 regnum)
अणु
	phy_ग_लिखो(phydev, MII_KSZPHY_EXTREG, regnum);
	वापस phy_पढ़ो(phydev, MII_KSZPHY_EXTREG_READ);
पूर्ण

अटल पूर्णांक kszphy_ack_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	/* bit[7..0] पूर्णांक status, which is a पढ़ो and clear रेजिस्टर. */
	पूर्णांक rc;

	rc = phy_पढ़ो(phydev, MII_KSZPHY_INTCS);

	वापस (rc < 0) ? rc : 0;
पूर्ण

अटल पूर्णांक kszphy_config_पूर्णांकr(काष्ठा phy_device *phydev)
अणु
	स्थिर काष्ठा kszphy_type *type = phydev->drv->driver_data;
	पूर्णांक temp, err;
	u16 mask;

	अगर (type && type->पूर्णांकerrupt_level_mask)
		mask = type->पूर्णांकerrupt_level_mask;
	अन्यथा
		mask = KSZPHY_CTRL_INT_ACTIVE_HIGH;

	/* set the पूर्णांकerrupt pin active low */
	temp = phy_पढ़ो(phydev, MII_KSZPHY_CTRL);
	अगर (temp < 0)
		वापस temp;
	temp &= ~mask;
	phy_ग_लिखो(phydev, MII_KSZPHY_CTRL, temp);

	/* enable / disable पूर्णांकerrupts */
	अगर (phydev->पूर्णांकerrupts == PHY_INTERRUPT_ENABLED) अणु
		err = kszphy_ack_पूर्णांकerrupt(phydev);
		अगर (err)
			वापस err;

		temp = KSZPHY_INTCS_ALL;
		err = phy_ग_लिखो(phydev, MII_KSZPHY_INTCS, temp);
	पूर्ण अन्यथा अणु
		temp = 0;
		err = phy_ग_लिखो(phydev, MII_KSZPHY_INTCS, temp);
		अगर (err)
			वापस err;

		err = kszphy_ack_पूर्णांकerrupt(phydev);
	पूर्ण

	वापस err;
पूर्ण

अटल irqवापस_t kszphy_handle_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक irq_status;

	irq_status = phy_पढ़ो(phydev, MII_KSZPHY_INTCS);
	अगर (irq_status < 0) अणु
		phy_error(phydev);
		वापस IRQ_NONE;
	पूर्ण

	अगर (!(irq_status & KSZPHY_INTCS_STATUS))
		वापस IRQ_NONE;

	phy_trigger_machine(phydev);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक kszphy_rmii_clk_sel(काष्ठा phy_device *phydev, bool val)
अणु
	पूर्णांक ctrl;

	ctrl = phy_पढ़ो(phydev, MII_KSZPHY_CTRL);
	अगर (ctrl < 0)
		वापस ctrl;

	अगर (val)
		ctrl |= KSZPHY_RMII_REF_CLK_SEL;
	अन्यथा
		ctrl &= ~KSZPHY_RMII_REF_CLK_SEL;

	वापस phy_ग_लिखो(phydev, MII_KSZPHY_CTRL, ctrl);
पूर्ण

अटल पूर्णांक kszphy_setup_led(काष्ठा phy_device *phydev, u32 reg, पूर्णांक val)
अणु
	पूर्णांक rc, temp, shअगरt;

	चयन (reg) अणु
	हाल MII_KSZPHY_CTRL_1:
		shअगरt = 14;
		अवरोध;
	हाल MII_KSZPHY_CTRL_2:
		shअगरt = 4;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	temp = phy_पढ़ो(phydev, reg);
	अगर (temp < 0) अणु
		rc = temp;
		जाओ out;
	पूर्ण

	temp &= ~(3 << shअगरt);
	temp |= val << shअगरt;
	rc = phy_ग_लिखो(phydev, reg, temp);
out:
	अगर (rc < 0)
		phydev_err(phydev, "failed to set led mode\n");

	वापस rc;
पूर्ण

/* Disable PHY address 0 as the broadcast address, so that it can be used as a
 * unique (non-broadcast) address on a shared bus.
 */
अटल पूर्णांक kszphy_broadcast_disable(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	ret = phy_पढ़ो(phydev, MII_KSZPHY_OMSO);
	अगर (ret < 0)
		जाओ out;

	ret = phy_ग_लिखो(phydev, MII_KSZPHY_OMSO, ret | KSZPHY_OMSO_B_CAST_OFF);
out:
	अगर (ret)
		phydev_err(phydev, "failed to disable broadcast address\n");

	वापस ret;
पूर्ण

अटल पूर्णांक kszphy_nand_tree_disable(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	ret = phy_पढ़ो(phydev, MII_KSZPHY_OMSO);
	अगर (ret < 0)
		जाओ out;

	अगर (!(ret & KSZPHY_OMSO_न_अंकD_TREE_ON))
		वापस 0;

	ret = phy_ग_लिखो(phydev, MII_KSZPHY_OMSO,
			ret & ~KSZPHY_OMSO_न_अंकD_TREE_ON);
out:
	अगर (ret)
		phydev_err(phydev, "failed to disable NAND tree mode\n");

	वापस ret;
पूर्ण

/* Some config bits need to be set again on resume, handle them here. */
अटल पूर्णांक kszphy_config_reset(काष्ठा phy_device *phydev)
अणु
	काष्ठा kszphy_priv *priv = phydev->priv;
	पूर्णांक ret;

	अगर (priv->rmii_ref_clk_sel) अणु
		ret = kszphy_rmii_clk_sel(phydev, priv->rmii_ref_clk_sel_val);
		अगर (ret) अणु
			phydev_err(phydev,
				   "failed to set rmii reference clock\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (priv->led_mode >= 0)
		kszphy_setup_led(phydev, priv->type->led_mode_reg, priv->led_mode);

	वापस 0;
पूर्ण

अटल पूर्णांक kszphy_config_init(काष्ठा phy_device *phydev)
अणु
	काष्ठा kszphy_priv *priv = phydev->priv;
	स्थिर काष्ठा kszphy_type *type;

	अगर (!priv)
		वापस 0;

	type = priv->type;

	अगर (type->has_broadcast_disable)
		kszphy_broadcast_disable(phydev);

	अगर (type->has_nand_tree_disable)
		kszphy_nand_tree_disable(phydev);

	वापस kszphy_config_reset(phydev);
पूर्ण

अटल पूर्णांक ksz8041_fiber_mode(काष्ठा phy_device *phydev)
अणु
	काष्ठा device_node *of_node = phydev->mdio.dev.of_node;

	वापस of_property_पढ़ो_bool(of_node, "micrel,fiber-mode");
पूर्ण

अटल पूर्णांक ksz8041_config_init(काष्ठा phy_device *phydev)
अणु
	__ETHTOOL_DECLARE_LINK_MODE_MASK(mask) = अणु 0, पूर्ण;

	/* Limit supported and advertised modes in fiber mode */
	अगर (ksz8041_fiber_mode(phydev)) अणु
		phydev->dev_flags |= MICREL_PHY_FXEN;
		linkmode_set_bit(ETHTOOL_LINK_MODE_100baseT_Full_BIT, mask);
		linkmode_set_bit(ETHTOOL_LINK_MODE_100baseT_Half_BIT, mask);

		linkmode_and(phydev->supported, phydev->supported, mask);
		linkmode_set_bit(ETHTOOL_LINK_MODE_FIBRE_BIT,
				 phydev->supported);
		linkmode_and(phydev->advertising, phydev->advertising, mask);
		linkmode_set_bit(ETHTOOL_LINK_MODE_FIBRE_BIT,
				 phydev->advertising);
		phydev->स्वतःneg = AUTONEG_DISABLE;
	पूर्ण

	वापस kszphy_config_init(phydev);
पूर्ण

अटल पूर्णांक ksz8041_config_aneg(काष्ठा phy_device *phydev)
अणु
	/* Skip स्वतः-negotiation in fiber mode */
	अगर (phydev->dev_flags & MICREL_PHY_FXEN) अणु
		phydev->speed = SPEED_100;
		वापस 0;
	पूर्ण

	वापस genphy_config_aneg(phydev);
पूर्ण

अटल पूर्णांक ksz8051_ksz8795_match_phy_device(काष्ठा phy_device *phydev,
					    स्थिर u32 ksz_phy_id)
अणु
	पूर्णांक ret;

	अगर ((phydev->phy_id & MICREL_PHY_ID_MASK) != ksz_phy_id)
		वापस 0;

	ret = phy_पढ़ो(phydev, MII_BMSR);
	अगर (ret < 0)
		वापस ret;

	/* KSZ8051 PHY and KSZ8794/KSZ8795/KSZ8765 चयन share the same
	 * exact PHY ID. However, they can be told apart by the extended
	 * capability रेजिस्टरs presence. The KSZ8051 PHY has them जबतक
	 * the चयन करोes not.
	 */
	ret &= BMSR_ERCAP;
	अगर (ksz_phy_id == PHY_ID_KSZ8051)
		वापस ret;
	अन्यथा
		वापस !ret;
पूर्ण

अटल पूर्णांक ksz8051_match_phy_device(काष्ठा phy_device *phydev)
अणु
	वापस ksz8051_ksz8795_match_phy_device(phydev, PHY_ID_KSZ8051);
पूर्ण

अटल पूर्णांक ksz8081_config_init(काष्ठा phy_device *phydev)
अणु
	/* KSZPHY_OMSO_FACTORY_TEST is set at de-निश्चितion of the reset line
	 * based on the RXER (KSZ8081RNA/RND) or TXC (KSZ8081MNX/RNB) pin. If a
	 * pull-करोwn is missing, the factory test mode should be cleared by
	 * manually writing a 0.
	 */
	phy_clear_bits(phydev, MII_KSZPHY_OMSO, KSZPHY_OMSO_FACTORY_TEST);

	वापस kszphy_config_init(phydev);
पूर्ण

अटल पूर्णांक ksz8061_config_init(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	ret = phy_ग_लिखो_mmd(phydev, MDIO_MMD_PMAPMD, MDIO_DEVID1, 0xB61A);
	अगर (ret)
		वापस ret;

	वापस kszphy_config_init(phydev);
पूर्ण

अटल पूर्णांक ksz8795_match_phy_device(काष्ठा phy_device *phydev)
अणु
	वापस ksz8051_ksz8795_match_phy_device(phydev, PHY_ID_KSZ87XX);
पूर्ण

अटल पूर्णांक ksz9021_load_values_from_of(काष्ठा phy_device *phydev,
				       स्थिर काष्ठा device_node *of_node,
				       u16 reg,
				       स्थिर अक्षर *field1, स्थिर अक्षर *field2,
				       स्थिर अक्षर *field3, स्थिर अक्षर *field4)
अणु
	पूर्णांक val1 = -1;
	पूर्णांक val2 = -2;
	पूर्णांक val3 = -3;
	पूर्णांक val4 = -4;
	पूर्णांक newval;
	पूर्णांक matches = 0;

	अगर (!of_property_पढ़ो_u32(of_node, field1, &val1))
		matches++;

	अगर (!of_property_पढ़ो_u32(of_node, field2, &val2))
		matches++;

	अगर (!of_property_पढ़ो_u32(of_node, field3, &val3))
		matches++;

	अगर (!of_property_पढ़ो_u32(of_node, field4, &val4))
		matches++;

	अगर (!matches)
		वापस 0;

	अगर (matches < 4)
		newval = kszphy_extended_पढ़ो(phydev, reg);
	अन्यथा
		newval = 0;

	अगर (val1 != -1)
		newval = ((newval & 0xfff0) | ((val1 / PS_TO_REG) & 0xf) << 0);

	अगर (val2 != -2)
		newval = ((newval & 0xff0f) | ((val2 / PS_TO_REG) & 0xf) << 4);

	अगर (val3 != -3)
		newval = ((newval & 0xf0ff) | ((val3 / PS_TO_REG) & 0xf) << 8);

	अगर (val4 != -4)
		newval = ((newval & 0x0fff) | ((val4 / PS_TO_REG) & 0xf) << 12);

	वापस kszphy_extended_ग_लिखो(phydev, reg, newval);
पूर्ण

अटल पूर्णांक ksz9021_config_init(काष्ठा phy_device *phydev)
अणु
	स्थिर काष्ठा device *dev = &phydev->mdio.dev;
	स्थिर काष्ठा device_node *of_node = dev->of_node;
	स्थिर काष्ठा device *dev_walker;

	/* The Micrel driver has a deprecated option to place phy OF
	 * properties in the MAC node. Walk up the tree of devices to
	 * find a device with an OF node.
	 */
	dev_walker = &phydev->mdio.dev;
	करो अणु
		of_node = dev_walker->of_node;
		dev_walker = dev_walker->parent;

	पूर्ण जबतक (!of_node && dev_walker);

	अगर (of_node) अणु
		ksz9021_load_values_from_of(phydev, of_node,
				    MII_KSZPHY_CLK_CONTROL_PAD_SKEW,
				    "txen-skew-ps", "txc-skew-ps",
				    "rxdv-skew-ps", "rxc-skew-ps");
		ksz9021_load_values_from_of(phydev, of_node,
				    MII_KSZPHY_RX_DATA_PAD_SKEW,
				    "rxd0-skew-ps", "rxd1-skew-ps",
				    "rxd2-skew-ps", "rxd3-skew-ps");
		ksz9021_load_values_from_of(phydev, of_node,
				    MII_KSZPHY_TX_DATA_PAD_SKEW,
				    "txd0-skew-ps", "txd1-skew-ps",
				    "txd2-skew-ps", "txd3-skew-ps");
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा KSZ9031_PS_TO_REG		60

/* Extended रेजिस्टरs */
/* MMD Address 0x0 */
#घोषणा MII_KSZ9031RN_FLP_BURST_TX_LO	3
#घोषणा MII_KSZ9031RN_FLP_BURST_TX_HI	4

/* MMD Address 0x2 */
#घोषणा MII_KSZ9031RN_CONTROL_PAD_SKEW	4
#घोषणा MII_KSZ9031RN_RX_CTL_M		GENMASK(7, 4)
#घोषणा MII_KSZ9031RN_TX_CTL_M		GENMASK(3, 0)

#घोषणा MII_KSZ9031RN_RX_DATA_PAD_SKEW	5
#घोषणा MII_KSZ9031RN_RXD3		GENMASK(15, 12)
#घोषणा MII_KSZ9031RN_RXD2		GENMASK(11, 8)
#घोषणा MII_KSZ9031RN_RXD1		GENMASK(7, 4)
#घोषणा MII_KSZ9031RN_RXD0		GENMASK(3, 0)

#घोषणा MII_KSZ9031RN_TX_DATA_PAD_SKEW	6
#घोषणा MII_KSZ9031RN_TXD3		GENMASK(15, 12)
#घोषणा MII_KSZ9031RN_TXD2		GENMASK(11, 8)
#घोषणा MII_KSZ9031RN_TXD1		GENMASK(7, 4)
#घोषणा MII_KSZ9031RN_TXD0		GENMASK(3, 0)

#घोषणा MII_KSZ9031RN_CLK_PAD_SKEW	8
#घोषणा MII_KSZ9031RN_GTX_CLK		GENMASK(9, 5)
#घोषणा MII_KSZ9031RN_RX_CLK		GENMASK(4, 0)

/* KSZ9031 has पूर्णांकernal RGMII_IDRX = 1.2ns and RGMII_IDTX = 0ns. To
 * provide dअगरferent RGMII options we need to configure delay offset
 * क्रम each pad relative to build in delay.
 */
/* keep rx as "No delay adjustment" and set rx_clk to +0.60ns to get delays of
 * 1.80ns
 */
#घोषणा RX_ID				0x7
#घोषणा RX_CLK_ID			0x19

/* set rx to +0.30ns and rx_clk to -0.90ns to compensate the
 * पूर्णांकernal 1.2ns delay.
 */
#घोषणा RX_ND				0xc
#घोषणा RX_CLK_ND			0x0

/* set tx to -0.42ns and tx_clk to +0.96ns to get 1.38ns delay */
#घोषणा TX_ID				0x0
#घोषणा TX_CLK_ID			0x1f

/* set tx and tx_clk to "No delay adjustment" to keep 0ns
 * dealy
 */
#घोषणा TX_ND				0x7
#घोषणा TX_CLK_ND			0xf

/* MMD Address 0x1C */
#घोषणा MII_KSZ9031RN_EDPD		0x23
#घोषणा MII_KSZ9031RN_EDPD_ENABLE	BIT(0)

अटल पूर्णांक ksz9031_of_load_skew_values(काष्ठा phy_device *phydev,
				       स्थिर काष्ठा device_node *of_node,
				       u16 reg, माप_प्रकार field_sz,
				       स्थिर अक्षर *field[], u8 numfields,
				       bool *update)
अणु
	पूर्णांक val[4] = अणु-1, -2, -3, -4पूर्ण;
	पूर्णांक matches = 0;
	u16 mask;
	u16 maxval;
	u16 newval;
	पूर्णांक i;

	क्रम (i = 0; i < numfields; i++)
		अगर (!of_property_पढ़ो_u32(of_node, field[i], val + i))
			matches++;

	अगर (!matches)
		वापस 0;

	*update |= true;

	अगर (matches < numfields)
		newval = phy_पढ़ो_mmd(phydev, 2, reg);
	अन्यथा
		newval = 0;

	maxval = (field_sz == 4) ? 0xf : 0x1f;
	क्रम (i = 0; i < numfields; i++)
		अगर (val[i] != -(i + 1)) अणु
			mask = 0xffff;
			mask ^= maxval << (field_sz * i);
			newval = (newval & mask) |
				(((val[i] / KSZ9031_PS_TO_REG) & maxval)
					<< (field_sz * i));
		पूर्ण

	वापस phy_ग_लिखो_mmd(phydev, 2, reg, newval);
पूर्ण

/* Center KSZ9031RNX FLP timing at 16ms. */
अटल पूर्णांक ksz9031_center_flp_timing(काष्ठा phy_device *phydev)
अणु
	पूर्णांक result;

	result = phy_ग_लिखो_mmd(phydev, 0, MII_KSZ9031RN_FLP_BURST_TX_HI,
			       0x0006);
	अगर (result)
		वापस result;

	result = phy_ग_लिखो_mmd(phydev, 0, MII_KSZ9031RN_FLP_BURST_TX_LO,
			       0x1A80);
	अगर (result)
		वापस result;

	वापस genphy_restart_aneg(phydev);
पूर्ण

/* Enable energy-detect घातer-करोwn mode */
अटल पूर्णांक ksz9031_enable_edpd(काष्ठा phy_device *phydev)
अणु
	पूर्णांक reg;

	reg = phy_पढ़ो_mmd(phydev, 0x1C, MII_KSZ9031RN_EDPD);
	अगर (reg < 0)
		वापस reg;
	वापस phy_ग_लिखो_mmd(phydev, 0x1C, MII_KSZ9031RN_EDPD,
			     reg | MII_KSZ9031RN_EDPD_ENABLE);
पूर्ण

अटल पूर्णांक ksz9031_config_rgmii_delay(काष्ठा phy_device *phydev)
अणु
	u16 rx, tx, rx_clk, tx_clk;
	पूर्णांक ret;

	चयन (phydev->पूर्णांकerface) अणु
	हाल PHY_INTERFACE_MODE_RGMII:
		tx = TX_ND;
		tx_clk = TX_CLK_ND;
		rx = RX_ND;
		rx_clk = RX_CLK_ND;
		अवरोध;
	हाल PHY_INTERFACE_MODE_RGMII_ID:
		tx = TX_ID;
		tx_clk = TX_CLK_ID;
		rx = RX_ID;
		rx_clk = RX_CLK_ID;
		अवरोध;
	हाल PHY_INTERFACE_MODE_RGMII_RXID:
		tx = TX_ND;
		tx_clk = TX_CLK_ND;
		rx = RX_ID;
		rx_clk = RX_CLK_ID;
		अवरोध;
	हाल PHY_INTERFACE_MODE_RGMII_TXID:
		tx = TX_ID;
		tx_clk = TX_CLK_ID;
		rx = RX_ND;
		rx_clk = RX_CLK_ND;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	ret = phy_ग_लिखो_mmd(phydev, 2, MII_KSZ9031RN_CONTROL_PAD_SKEW,
			    FIELD_PREP(MII_KSZ9031RN_RX_CTL_M, rx) |
			    FIELD_PREP(MII_KSZ9031RN_TX_CTL_M, tx));
	अगर (ret < 0)
		वापस ret;

	ret = phy_ग_लिखो_mmd(phydev, 2, MII_KSZ9031RN_RX_DATA_PAD_SKEW,
			    FIELD_PREP(MII_KSZ9031RN_RXD3, rx) |
			    FIELD_PREP(MII_KSZ9031RN_RXD2, rx) |
			    FIELD_PREP(MII_KSZ9031RN_RXD1, rx) |
			    FIELD_PREP(MII_KSZ9031RN_RXD0, rx));
	अगर (ret < 0)
		वापस ret;

	ret = phy_ग_लिखो_mmd(phydev, 2, MII_KSZ9031RN_TX_DATA_PAD_SKEW,
			    FIELD_PREP(MII_KSZ9031RN_TXD3, tx) |
			    FIELD_PREP(MII_KSZ9031RN_TXD2, tx) |
			    FIELD_PREP(MII_KSZ9031RN_TXD1, tx) |
			    FIELD_PREP(MII_KSZ9031RN_TXD0, tx));
	अगर (ret < 0)
		वापस ret;

	वापस phy_ग_लिखो_mmd(phydev, 2, MII_KSZ9031RN_CLK_PAD_SKEW,
			     FIELD_PREP(MII_KSZ9031RN_GTX_CLK, tx_clk) |
			     FIELD_PREP(MII_KSZ9031RN_RX_CLK, rx_clk));
पूर्ण

अटल पूर्णांक ksz9031_config_init(काष्ठा phy_device *phydev)
अणु
	स्थिर काष्ठा device *dev = &phydev->mdio.dev;
	स्थिर काष्ठा device_node *of_node = dev->of_node;
	अटल स्थिर अक्षर *clk_skews[2] = अणु"rxc-skew-ps", "txc-skew-ps"पूर्ण;
	अटल स्थिर अक्षर *rx_data_skews[4] = अणु
		"rxd0-skew-ps", "rxd1-skew-ps",
		"rxd2-skew-ps", "rxd3-skew-ps"
	पूर्ण;
	अटल स्थिर अक्षर *tx_data_skews[4] = अणु
		"txd0-skew-ps", "txd1-skew-ps",
		"txd2-skew-ps", "txd3-skew-ps"
	पूर्ण;
	अटल स्थिर अक्षर *control_skews[2] = अणु"txen-skew-ps", "rxdv-skew-ps"पूर्ण;
	स्थिर काष्ठा device *dev_walker;
	पूर्णांक result;

	result = ksz9031_enable_edpd(phydev);
	अगर (result < 0)
		वापस result;

	/* The Micrel driver has a deprecated option to place phy OF
	 * properties in the MAC node. Walk up the tree of devices to
	 * find a device with an OF node.
	 */
	dev_walker = &phydev->mdio.dev;
	करो अणु
		of_node = dev_walker->of_node;
		dev_walker = dev_walker->parent;
	पूर्ण जबतक (!of_node && dev_walker);

	अगर (of_node) अणु
		bool update = false;

		अगर (phy_पूर्णांकerface_is_rgmii(phydev)) अणु
			result = ksz9031_config_rgmii_delay(phydev);
			अगर (result < 0)
				वापस result;
		पूर्ण

		ksz9031_of_load_skew_values(phydev, of_node,
				MII_KSZ9031RN_CLK_PAD_SKEW, 5,
				clk_skews, 2, &update);

		ksz9031_of_load_skew_values(phydev, of_node,
				MII_KSZ9031RN_CONTROL_PAD_SKEW, 4,
				control_skews, 2, &update);

		ksz9031_of_load_skew_values(phydev, of_node,
				MII_KSZ9031RN_RX_DATA_PAD_SKEW, 4,
				rx_data_skews, 4, &update);

		ksz9031_of_load_skew_values(phydev, of_node,
				MII_KSZ9031RN_TX_DATA_PAD_SKEW, 4,
				tx_data_skews, 4, &update);

		अगर (update && phydev->पूर्णांकerface != PHY_INTERFACE_MODE_RGMII)
			phydev_warn(phydev,
				    "*-skew-ps values should be used only with phy-mode = \"rgmii\"\n");

		/* Silicon Errata Sheet (DS80000691D or DS80000692D):
		 * When the device links in the 1000BASE-T slave mode only,
		 * the optional 125MHz reference output घड़ी (CLK125_NDO)
		 * has wide duty cycle variation.
		 *
		 * The optional CLK125_NDO घड़ी करोes not meet the RGMII
		 * 45/55 percent (min/max) duty cycle requirement and thereक्रमe
		 * cannot be used directly by the MAC side क्रम घड़ीing
		 * applications that have setup/hold समय requirements on
		 * rising and falling घड़ी edges.
		 *
		 * Workaround:
		 * Force the phy to be the master to receive a stable घड़ी
		 * which meets the duty cycle requirement.
		 */
		अगर (of_property_पढ़ो_bool(of_node, "micrel,force-master")) अणु
			result = phy_पढ़ो(phydev, MII_CTRL1000);
			अगर (result < 0)
				जाओ err_क्रमce_master;

			/* enable master mode, config & prefer master */
			result |= CTL1000_ENABLE_MASTER | CTL1000_AS_MASTER;
			result = phy_ग_लिखो(phydev, MII_CTRL1000, result);
			अगर (result < 0)
				जाओ err_क्रमce_master;
		पूर्ण
	पूर्ण

	वापस ksz9031_center_flp_timing(phydev);

err_क्रमce_master:
	phydev_err(phydev, "failed to force the phy to master mode\n");
	वापस result;
पूर्ण

#घोषणा KSZ9131_SKEW_5BIT_MAX	2400
#घोषणा KSZ9131_SKEW_4BIT_MAX	800
#घोषणा KSZ9131_OFFSET		700
#घोषणा KSZ9131_STEP		100

अटल पूर्णांक ksz9131_of_load_skew_values(काष्ठा phy_device *phydev,
				       काष्ठा device_node *of_node,
				       u16 reg, माप_प्रकार field_sz,
				       अक्षर *field[], u8 numfields)
अणु
	पूर्णांक val[4] = अणु-(1 + KSZ9131_OFFSET), -(2 + KSZ9131_OFFSET),
		      -(3 + KSZ9131_OFFSET), -(4 + KSZ9131_OFFSET)पूर्ण;
	पूर्णांक skewval, skewmax = 0;
	पूर्णांक matches = 0;
	u16 maxval;
	u16 newval;
	u16 mask;
	पूर्णांक i;

	/* psec properties in dts should mean x pico seconds */
	अगर (field_sz == 5)
		skewmax = KSZ9131_SKEW_5BIT_MAX;
	अन्यथा
		skewmax = KSZ9131_SKEW_4BIT_MAX;

	क्रम (i = 0; i < numfields; i++)
		अगर (!of_property_पढ़ो_s32(of_node, field[i], &skewval)) अणु
			अगर (skewval < -KSZ9131_OFFSET)
				skewval = -KSZ9131_OFFSET;
			अन्यथा अगर (skewval > skewmax)
				skewval = skewmax;

			val[i] = skewval + KSZ9131_OFFSET;
			matches++;
		पूर्ण

	अगर (!matches)
		वापस 0;

	अगर (matches < numfields)
		newval = phy_पढ़ो_mmd(phydev, 2, reg);
	अन्यथा
		newval = 0;

	maxval = (field_sz == 4) ? 0xf : 0x1f;
	क्रम (i = 0; i < numfields; i++)
		अगर (val[i] != -(i + 1 + KSZ9131_OFFSET)) अणु
			mask = 0xffff;
			mask ^= maxval << (field_sz * i);
			newval = (newval & mask) |
				(((val[i] / KSZ9131_STEP) & maxval)
					<< (field_sz * i));
		पूर्ण

	वापस phy_ग_लिखो_mmd(phydev, 2, reg, newval);
पूर्ण

#घोषणा KSZ9131RN_MMD_COMMON_CTRL_REG	2
#घोषणा KSZ9131RN_RXC_DLL_CTRL		76
#घोषणा KSZ9131RN_TXC_DLL_CTRL		77
#घोषणा KSZ9131RN_DLL_CTRL_BYPASS	BIT_MASK(12)
#घोषणा KSZ9131RN_DLL_ENABLE_DELAY	0
#घोषणा KSZ9131RN_DLL_DISABLE_DELAY	BIT(12)

अटल पूर्णांक ksz9131_config_rgmii_delay(काष्ठा phy_device *phydev)
अणु
	u16 rxcdll_val, txcdll_val;
	पूर्णांक ret;

	चयन (phydev->पूर्णांकerface) अणु
	हाल PHY_INTERFACE_MODE_RGMII:
		rxcdll_val = KSZ9131RN_DLL_DISABLE_DELAY;
		txcdll_val = KSZ9131RN_DLL_DISABLE_DELAY;
		अवरोध;
	हाल PHY_INTERFACE_MODE_RGMII_ID:
		rxcdll_val = KSZ9131RN_DLL_ENABLE_DELAY;
		txcdll_val = KSZ9131RN_DLL_ENABLE_DELAY;
		अवरोध;
	हाल PHY_INTERFACE_MODE_RGMII_RXID:
		rxcdll_val = KSZ9131RN_DLL_ENABLE_DELAY;
		txcdll_val = KSZ9131RN_DLL_DISABLE_DELAY;
		अवरोध;
	हाल PHY_INTERFACE_MODE_RGMII_TXID:
		rxcdll_val = KSZ9131RN_DLL_DISABLE_DELAY;
		txcdll_val = KSZ9131RN_DLL_ENABLE_DELAY;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	ret = phy_modअगरy_mmd(phydev, KSZ9131RN_MMD_COMMON_CTRL_REG,
			     KSZ9131RN_RXC_DLL_CTRL, KSZ9131RN_DLL_CTRL_BYPASS,
			     rxcdll_val);
	अगर (ret < 0)
		वापस ret;

	वापस phy_modअगरy_mmd(phydev, KSZ9131RN_MMD_COMMON_CTRL_REG,
			      KSZ9131RN_TXC_DLL_CTRL, KSZ9131RN_DLL_CTRL_BYPASS,
			      txcdll_val);
पूर्ण

अटल पूर्णांक ksz9131_config_init(काष्ठा phy_device *phydev)
अणु
	स्थिर काष्ठा device *dev = &phydev->mdio.dev;
	काष्ठा device_node *of_node = dev->of_node;
	अक्षर *clk_skews[2] = अणु"rxc-skew-psec", "txc-skew-psec"पूर्ण;
	अक्षर *rx_data_skews[4] = अणु
		"rxd0-skew-psec", "rxd1-skew-psec",
		"rxd2-skew-psec", "rxd3-skew-psec"
	पूर्ण;
	अक्षर *tx_data_skews[4] = अणु
		"txd0-skew-psec", "txd1-skew-psec",
		"txd2-skew-psec", "txd3-skew-psec"
	पूर्ण;
	अक्षर *control_skews[2] = अणु"txen-skew-psec", "rxdv-skew-psec"पूर्ण;
	स्थिर काष्ठा device *dev_walker;
	पूर्णांक ret;

	dev_walker = &phydev->mdio.dev;
	करो अणु
		of_node = dev_walker->of_node;
		dev_walker = dev_walker->parent;
	पूर्ण जबतक (!of_node && dev_walker);

	अगर (!of_node)
		वापस 0;

	अगर (phy_पूर्णांकerface_is_rgmii(phydev)) अणु
		ret = ksz9131_config_rgmii_delay(phydev);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	ret = ksz9131_of_load_skew_values(phydev, of_node,
					  MII_KSZ9031RN_CLK_PAD_SKEW, 5,
					  clk_skews, 2);
	अगर (ret < 0)
		वापस ret;

	ret = ksz9131_of_load_skew_values(phydev, of_node,
					  MII_KSZ9031RN_CONTROL_PAD_SKEW, 4,
					  control_skews, 2);
	अगर (ret < 0)
		वापस ret;

	ret = ksz9131_of_load_skew_values(phydev, of_node,
					  MII_KSZ9031RN_RX_DATA_PAD_SKEW, 4,
					  rx_data_skews, 4);
	अगर (ret < 0)
		वापस ret;

	ret = ksz9131_of_load_skew_values(phydev, of_node,
					  MII_KSZ9031RN_TX_DATA_PAD_SKEW, 4,
					  tx_data_skews, 4);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

#घोषणा KSZ8873MLL_GLOBAL_CONTROL_4	0x06
#घोषणा KSZ8873MLL_GLOBAL_CONTROL_4_DUPLEX	BIT(6)
#घोषणा KSZ8873MLL_GLOBAL_CONTROL_4_SPEED	BIT(4)
अटल पूर्णांक ksz8873mll_पढ़ो_status(काष्ठा phy_device *phydev)
अणु
	पूर्णांक regval;

	/* dummy पढ़ो */
	regval = phy_पढ़ो(phydev, KSZ8873MLL_GLOBAL_CONTROL_4);

	regval = phy_पढ़ो(phydev, KSZ8873MLL_GLOBAL_CONTROL_4);

	अगर (regval & KSZ8873MLL_GLOBAL_CONTROL_4_DUPLEX)
		phydev->duplex = DUPLEX_HALF;
	अन्यथा
		phydev->duplex = DUPLEX_FULL;

	अगर (regval & KSZ8873MLL_GLOBAL_CONTROL_4_SPEED)
		phydev->speed = SPEED_10;
	अन्यथा
		phydev->speed = SPEED_100;

	phydev->link = 1;
	phydev->छोड़ो = phydev->asym_छोड़ो = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक ksz9031_get_features(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	ret = genphy_पढ़ो_abilities(phydev);
	अगर (ret < 0)
		वापस ret;

	/* Silicon Errata Sheet (DS80000691D or DS80000692D):
	 * Whenever the device's Asymmetric Pause capability is set to 1,
	 * link-up may fail after a link-up to link-करोwn transition.
	 *
	 * The Errata Sheet is क्रम ksz9031, but ksz9021 has the same issue
	 *
	 * Workaround:
	 * Do not enable the Asymmetric Pause capability bit.
	 */
	linkmode_clear_bit(ETHTOOL_LINK_MODE_Asym_Pause_BIT, phydev->supported);

	/* We क्रमce setting the Pause capability as the core will क्रमce the
	 * Asymmetric Pause capability to 1 otherwise.
	 */
	linkmode_set_bit(ETHTOOL_LINK_MODE_Pause_BIT, phydev->supported);

	वापस 0;
पूर्ण

अटल पूर्णांक ksz9031_पढ़ो_status(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;
	पूर्णांक regval;

	err = genphy_पढ़ो_status(phydev);
	अगर (err)
		वापस err;

	/* Make sure the PHY is not broken. Read idle error count,
	 * and reset the PHY अगर it is maxed out.
	 */
	regval = phy_पढ़ो(phydev, MII_STAT1000);
	अगर ((regval & 0xFF) == 0xFF) अणु
		phy_init_hw(phydev);
		phydev->link = 0;
		अगर (phydev->drv->config_पूर्णांकr && phy_पूर्णांकerrupt_is_valid(phydev))
			phydev->drv->config_पूर्णांकr(phydev);
		वापस genphy_config_aneg(phydev);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ksz8873mll_config_aneg(काष्ठा phy_device *phydev)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक kszphy_get_sset_count(काष्ठा phy_device *phydev)
अणु
	वापस ARRAY_SIZE(kszphy_hw_stats);
पूर्ण

अटल व्योम kszphy_get_strings(काष्ठा phy_device *phydev, u8 *data)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(kszphy_hw_stats); i++) अणु
		strlcpy(data + i * ETH_GSTRING_LEN,
			kszphy_hw_stats[i].string, ETH_GSTRING_LEN);
	पूर्ण
पूर्ण

अटल u64 kszphy_get_stat(काष्ठा phy_device *phydev, पूर्णांक i)
अणु
	काष्ठा kszphy_hw_stat stat = kszphy_hw_stats[i];
	काष्ठा kszphy_priv *priv = phydev->priv;
	पूर्णांक val;
	u64 ret;

	val = phy_पढ़ो(phydev, stat.reg);
	अगर (val < 0) अणु
		ret = U64_MAX;
	पूर्ण अन्यथा अणु
		val = val & ((1 << stat.bits) - 1);
		priv->stats[i] += val;
		ret = priv->stats[i];
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम kszphy_get_stats(काष्ठा phy_device *phydev,
			     काष्ठा ethtool_stats *stats, u64 *data)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(kszphy_hw_stats); i++)
		data[i] = kszphy_get_stat(phydev, i);
पूर्ण

अटल पूर्णांक kszphy_suspend(काष्ठा phy_device *phydev)
अणु
	/* Disable PHY Interrupts */
	अगर (phy_पूर्णांकerrupt_is_valid(phydev)) अणु
		phydev->पूर्णांकerrupts = PHY_INTERRUPT_DISABLED;
		अगर (phydev->drv->config_पूर्णांकr)
			phydev->drv->config_पूर्णांकr(phydev);
	पूर्ण

	वापस genphy_suspend(phydev);
पूर्ण

अटल पूर्णांक kszphy_resume(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	genphy_resume(phydev);

	/* After चयनing from घातer-करोwn to normal mode, an पूर्णांकernal global
	 * reset is स्वतःmatically generated. Wait a minimum of 1 ms beक्रमe
	 * पढ़ो/ग_लिखो access to the PHY रेजिस्टरs.
	 */
	usleep_range(1000, 2000);

	ret = kszphy_config_reset(phydev);
	अगर (ret)
		वापस ret;

	/* Enable PHY Interrupts */
	अगर (phy_पूर्णांकerrupt_is_valid(phydev)) अणु
		phydev->पूर्णांकerrupts = PHY_INTERRUPT_ENABLED;
		अगर (phydev->drv->config_पूर्णांकr)
			phydev->drv->config_पूर्णांकr(phydev);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक kszphy_probe(काष्ठा phy_device *phydev)
अणु
	स्थिर काष्ठा kszphy_type *type = phydev->drv->driver_data;
	स्थिर काष्ठा device_node *np = phydev->mdio.dev.of_node;
	काष्ठा kszphy_priv *priv;
	काष्ठा clk *clk;
	पूर्णांक ret;

	priv = devm_kzalloc(&phydev->mdio.dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	phydev->priv = priv;

	priv->type = type;

	अगर (type->led_mode_reg) अणु
		ret = of_property_पढ़ो_u32(np, "micrel,led-mode",
				&priv->led_mode);
		अगर (ret)
			priv->led_mode = -1;

		अगर (priv->led_mode > 3) अणु
			phydev_err(phydev, "invalid led mode: 0x%02x\n",
				   priv->led_mode);
			priv->led_mode = -1;
		पूर्ण
	पूर्ण अन्यथा अणु
		priv->led_mode = -1;
	पूर्ण

	clk = devm_clk_get(&phydev->mdio.dev, "rmii-ref");
	/* NOTE: clk may be शून्य अगर building without CONFIG_HAVE_CLK */
	अगर (!IS_ERR_OR_शून्य(clk)) अणु
		अचिन्हित दीर्घ rate = clk_get_rate(clk);
		bool rmii_ref_clk_sel_25_mhz;

		priv->rmii_ref_clk_sel = type->has_rmii_ref_clk_sel;
		rmii_ref_clk_sel_25_mhz = of_property_पढ़ो_bool(np,
				"micrel,rmii-reference-clock-select-25-mhz");

		अगर (rate > 24500000 && rate < 25500000) अणु
			priv->rmii_ref_clk_sel_val = rmii_ref_clk_sel_25_mhz;
		पूर्ण अन्यथा अगर (rate > 49500000 && rate < 50500000) अणु
			priv->rmii_ref_clk_sel_val = !rmii_ref_clk_sel_25_mhz;
		पूर्ण अन्यथा अणु
			phydev_err(phydev, "Clock rate out of range: %ld\n",
				   rate);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (ksz8041_fiber_mode(phydev))
		phydev->port = PORT_FIBRE;

	/* Support legacy board-file configuration */
	अगर (phydev->dev_flags & MICREL_PHY_50MHZ_CLK) अणु
		priv->rmii_ref_clk_sel = true;
		priv->rmii_ref_clk_sel_val = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा phy_driver ksphy_driver[] = अणु
अणु
	.phy_id		= PHY_ID_KS8737,
	.phy_id_mask	= MICREL_PHY_ID_MASK,
	.name		= "Micrel KS8737",
	/* PHY_BASIC_FEATURES */
	.driver_data	= &ks8737_type,
	.config_init	= kszphy_config_init,
	.config_पूर्णांकr	= kszphy_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = kszphy_handle_पूर्णांकerrupt,
	.suspend	= genphy_suspend,
	.resume		= genphy_resume,
पूर्ण, अणु
	.phy_id		= PHY_ID_KSZ8021,
	.phy_id_mask	= 0x00ffffff,
	.name		= "Micrel KSZ8021 or KSZ8031",
	/* PHY_BASIC_FEATURES */
	.driver_data	= &ksz8021_type,
	.probe		= kszphy_probe,
	.config_init	= kszphy_config_init,
	.config_पूर्णांकr	= kszphy_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = kszphy_handle_पूर्णांकerrupt,
	.get_sset_count = kszphy_get_sset_count,
	.get_strings	= kszphy_get_strings,
	.get_stats	= kszphy_get_stats,
	.suspend	= genphy_suspend,
	.resume		= genphy_resume,
पूर्ण, अणु
	.phy_id		= PHY_ID_KSZ8031,
	.phy_id_mask	= 0x00ffffff,
	.name		= "Micrel KSZ8031",
	/* PHY_BASIC_FEATURES */
	.driver_data	= &ksz8021_type,
	.probe		= kszphy_probe,
	.config_init	= kszphy_config_init,
	.config_पूर्णांकr	= kszphy_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = kszphy_handle_पूर्णांकerrupt,
	.get_sset_count = kszphy_get_sset_count,
	.get_strings	= kszphy_get_strings,
	.get_stats	= kszphy_get_stats,
	.suspend	= genphy_suspend,
	.resume		= genphy_resume,
पूर्ण, अणु
	.phy_id		= PHY_ID_KSZ8041,
	.phy_id_mask	= MICREL_PHY_ID_MASK,
	.name		= "Micrel KSZ8041",
	/* PHY_BASIC_FEATURES */
	.driver_data	= &ksz8041_type,
	.probe		= kszphy_probe,
	.config_init	= ksz8041_config_init,
	.config_aneg	= ksz8041_config_aneg,
	.config_पूर्णांकr	= kszphy_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = kszphy_handle_पूर्णांकerrupt,
	.get_sset_count = kszphy_get_sset_count,
	.get_strings	= kszphy_get_strings,
	.get_stats	= kszphy_get_stats,
	.suspend	= genphy_suspend,
	.resume		= genphy_resume,
पूर्ण, अणु
	.phy_id		= PHY_ID_KSZ8041RNLI,
	.phy_id_mask	= MICREL_PHY_ID_MASK,
	.name		= "Micrel KSZ8041RNLI",
	/* PHY_BASIC_FEATURES */
	.driver_data	= &ksz8041_type,
	.probe		= kszphy_probe,
	.config_init	= kszphy_config_init,
	.config_पूर्णांकr	= kszphy_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = kszphy_handle_पूर्णांकerrupt,
	.get_sset_count = kszphy_get_sset_count,
	.get_strings	= kszphy_get_strings,
	.get_stats	= kszphy_get_stats,
	.suspend	= genphy_suspend,
	.resume		= genphy_resume,
पूर्ण, अणु
	.name		= "Micrel KSZ8051",
	/* PHY_BASIC_FEATURES */
	.driver_data	= &ksz8051_type,
	.probe		= kszphy_probe,
	.config_init	= kszphy_config_init,
	.config_पूर्णांकr	= kszphy_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = kszphy_handle_पूर्णांकerrupt,
	.get_sset_count = kszphy_get_sset_count,
	.get_strings	= kszphy_get_strings,
	.get_stats	= kszphy_get_stats,
	.match_phy_device = ksz8051_match_phy_device,
	.suspend	= genphy_suspend,
	.resume		= genphy_resume,
पूर्ण, अणु
	.phy_id		= PHY_ID_KSZ8001,
	.name		= "Micrel KSZ8001 or KS8721",
	.phy_id_mask	= 0x00fffffc,
	/* PHY_BASIC_FEATURES */
	.driver_data	= &ksz8041_type,
	.probe		= kszphy_probe,
	.config_init	= kszphy_config_init,
	.config_पूर्णांकr	= kszphy_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = kszphy_handle_पूर्णांकerrupt,
	.get_sset_count = kszphy_get_sset_count,
	.get_strings	= kszphy_get_strings,
	.get_stats	= kszphy_get_stats,
	.suspend	= genphy_suspend,
	.resume		= genphy_resume,
पूर्ण, अणु
	.phy_id		= PHY_ID_KSZ8081,
	.name		= "Micrel KSZ8081 or KSZ8091",
	.phy_id_mask	= MICREL_PHY_ID_MASK,
	/* PHY_BASIC_FEATURES */
	.driver_data	= &ksz8081_type,
	.probe		= kszphy_probe,
	.config_init	= ksz8081_config_init,
	.soft_reset	= genphy_soft_reset,
	.config_पूर्णांकr	= kszphy_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = kszphy_handle_पूर्णांकerrupt,
	.get_sset_count = kszphy_get_sset_count,
	.get_strings	= kszphy_get_strings,
	.get_stats	= kszphy_get_stats,
	.suspend	= kszphy_suspend,
	.resume		= kszphy_resume,
पूर्ण, अणु
	.phy_id		= PHY_ID_KSZ8061,
	.name		= "Micrel KSZ8061",
	.phy_id_mask	= MICREL_PHY_ID_MASK,
	/* PHY_BASIC_FEATURES */
	.config_init	= ksz8061_config_init,
	.config_पूर्णांकr	= kszphy_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = kszphy_handle_पूर्णांकerrupt,
	.suspend	= genphy_suspend,
	.resume		= genphy_resume,
पूर्ण, अणु
	.phy_id		= PHY_ID_KSZ9021,
	.phy_id_mask	= 0x000ffffe,
	.name		= "Micrel KSZ9021 Gigabit PHY",
	/* PHY_GBIT_FEATURES */
	.driver_data	= &ksz9021_type,
	.probe		= kszphy_probe,
	.get_features	= ksz9031_get_features,
	.config_init	= ksz9021_config_init,
	.config_पूर्णांकr	= kszphy_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = kszphy_handle_पूर्णांकerrupt,
	.get_sset_count = kszphy_get_sset_count,
	.get_strings	= kszphy_get_strings,
	.get_stats	= kszphy_get_stats,
	.suspend	= genphy_suspend,
	.resume		= genphy_resume,
	.पढ़ो_mmd	= genphy_पढ़ो_mmd_unsupported,
	.ग_लिखो_mmd	= genphy_ग_लिखो_mmd_unsupported,
पूर्ण, अणु
	.phy_id		= PHY_ID_KSZ9031,
	.phy_id_mask	= MICREL_PHY_ID_MASK,
	.name		= "Micrel KSZ9031 Gigabit PHY",
	.driver_data	= &ksz9021_type,
	.probe		= kszphy_probe,
	.get_features	= ksz9031_get_features,
	.config_init	= ksz9031_config_init,
	.soft_reset	= genphy_soft_reset,
	.पढ़ो_status	= ksz9031_पढ़ो_status,
	.config_पूर्णांकr	= kszphy_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = kszphy_handle_पूर्णांकerrupt,
	.get_sset_count = kszphy_get_sset_count,
	.get_strings	= kszphy_get_strings,
	.get_stats	= kszphy_get_stats,
	.suspend	= genphy_suspend,
	.resume		= kszphy_resume,
पूर्ण, अणु
	.phy_id		= PHY_ID_LAN8814,
	.phy_id_mask	= MICREL_PHY_ID_MASK,
	.name		= "Microchip INDY Gigabit Quad PHY",
	.driver_data	= &ksz9021_type,
	.probe		= kszphy_probe,
	.soft_reset	= genphy_soft_reset,
	.पढ़ो_status	= ksz9031_पढ़ो_status,
	.get_sset_count	= kszphy_get_sset_count,
	.get_strings	= kszphy_get_strings,
	.get_stats	= kszphy_get_stats,
	.suspend	= genphy_suspend,
	.resume		= kszphy_resume,
पूर्ण, अणु
	.phy_id		= PHY_ID_KSZ9131,
	.phy_id_mask	= MICREL_PHY_ID_MASK,
	.name		= "Microchip KSZ9131 Gigabit PHY",
	/* PHY_GBIT_FEATURES */
	.driver_data	= &ksz9021_type,
	.probe		= kszphy_probe,
	.config_init	= ksz9131_config_init,
	.config_पूर्णांकr	= kszphy_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = kszphy_handle_पूर्णांकerrupt,
	.get_sset_count = kszphy_get_sset_count,
	.get_strings	= kszphy_get_strings,
	.get_stats	= kszphy_get_stats,
	.suspend	= genphy_suspend,
	.resume		= kszphy_resume,
पूर्ण, अणु
	.phy_id		= PHY_ID_KSZ8873MLL,
	.phy_id_mask	= MICREL_PHY_ID_MASK,
	.name		= "Micrel KSZ8873MLL Switch",
	/* PHY_BASIC_FEATURES */
	.config_init	= kszphy_config_init,
	.config_aneg	= ksz8873mll_config_aneg,
	.पढ़ो_status	= ksz8873mll_पढ़ो_status,
	.suspend	= genphy_suspend,
	.resume		= genphy_resume,
पूर्ण, अणु
	.phy_id		= PHY_ID_KSZ886X,
	.phy_id_mask	= MICREL_PHY_ID_MASK,
	.name		= "Micrel KSZ8851 Ethernet MAC or KSZ886X Switch",
	/* PHY_BASIC_FEATURES */
	.config_init	= kszphy_config_init,
	.suspend	= genphy_suspend,
	.resume		= genphy_resume,
पूर्ण, अणु
	.name		= "Micrel KSZ87XX Switch",
	/* PHY_BASIC_FEATURES */
	.config_init	= kszphy_config_init,
	.config_aneg	= ksz8873mll_config_aneg,
	.पढ़ो_status	= ksz8873mll_पढ़ो_status,
	.match_phy_device = ksz8795_match_phy_device,
	.suspend	= genphy_suspend,
	.resume		= genphy_resume,
पूर्ण, अणु
	.phy_id		= PHY_ID_KSZ9477,
	.phy_id_mask	= MICREL_PHY_ID_MASK,
	.name		= "Microchip KSZ9477",
	/* PHY_GBIT_FEATURES */
	.config_init	= kszphy_config_init,
	.suspend	= genphy_suspend,
	.resume		= genphy_resume,
पूर्ण पूर्ण;

module_phy_driver(ksphy_driver);

MODULE_DESCRIPTION("Micrel PHY driver");
MODULE_AUTHOR("David J. Choi");
MODULE_LICENSE("GPL");

अटल काष्ठा mdio_device_id __maybe_unused micrel_tbl[] = अणु
	अणु PHY_ID_KSZ9021, 0x000ffffe पूर्ण,
	अणु PHY_ID_KSZ9031, MICREL_PHY_ID_MASK पूर्ण,
	अणु PHY_ID_KSZ9131, MICREL_PHY_ID_MASK पूर्ण,
	अणु PHY_ID_KSZ8001, 0x00fffffc पूर्ण,
	अणु PHY_ID_KS8737, MICREL_PHY_ID_MASK पूर्ण,
	अणु PHY_ID_KSZ8021, 0x00ffffff पूर्ण,
	अणु PHY_ID_KSZ8031, 0x00ffffff पूर्ण,
	अणु PHY_ID_KSZ8041, MICREL_PHY_ID_MASK पूर्ण,
	अणु PHY_ID_KSZ8051, MICREL_PHY_ID_MASK पूर्ण,
	अणु PHY_ID_KSZ8061, MICREL_PHY_ID_MASK पूर्ण,
	अणु PHY_ID_KSZ8081, MICREL_PHY_ID_MASK पूर्ण,
	अणु PHY_ID_KSZ8873MLL, MICREL_PHY_ID_MASK पूर्ण,
	अणु PHY_ID_KSZ886X, MICREL_PHY_ID_MASK पूर्ण,
	अणु PHY_ID_LAN8814, MICREL_PHY_ID_MASK पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(mdio, micrel_tbl);
