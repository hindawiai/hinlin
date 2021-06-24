<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम the Texas Instruments DP83848 PHY
 *
 * Copyright (C) 2015-2016 Texas Instruments Incorporated - http://www.ti.com/
 */

#समावेश <linux/module.h>
#समावेश <linux/phy.h>

#घोषणा TI_DP83848C_PHY_ID		0x20005ca0
#घोषणा TI_DP83620_PHY_ID		0x20005ce0
#घोषणा NS_DP83848C_PHY_ID		0x20005c90
#घोषणा TLK10X_PHY_ID			0x2000a210

/* Registers */
#घोषणा DP83848_MICR			0x11 /* MII Interrupt Control Register */
#घोषणा DP83848_MISR			0x12 /* MII Interrupt Status Register */

/* MICR Register Fields */
#घोषणा DP83848_MICR_INT_OE		BIT(0) /* Interrupt Output Enable */
#घोषणा DP83848_MICR_INTEN		BIT(1) /* Interrupt Enable */

/* MISR Register Fields */
#घोषणा DP83848_MISR_RHF_INT_EN		BIT(0) /* Receive Error Counter */
#घोषणा DP83848_MISR_FHF_INT_EN		BIT(1) /* False Carrier Counter */
#घोषणा DP83848_MISR_ANC_INT_EN		BIT(2) /* Auto-negotiation complete */
#घोषणा DP83848_MISR_DUP_INT_EN		BIT(3) /* Duplex Status */
#घोषणा DP83848_MISR_SPD_INT_EN		BIT(4) /* Speed status */
#घोषणा DP83848_MISR_LINK_INT_EN	BIT(5) /* Link status */
#घोषणा DP83848_MISR_ED_INT_EN		BIT(6) /* Energy detect */
#घोषणा DP83848_MISR_LQM_INT_EN		BIT(7) /* Link Quality Monitor */

#घोषणा DP83848_INT_EN_MASK		\
	(DP83848_MISR_ANC_INT_EN |	\
	 DP83848_MISR_DUP_INT_EN |	\
	 DP83848_MISR_SPD_INT_EN |	\
	 DP83848_MISR_LINK_INT_EN)

#घोषणा DP83848_MISR_RHF_INT		BIT(8)
#घोषणा DP83848_MISR_FHF_INT		BIT(9)
#घोषणा DP83848_MISR_ANC_INT		BIT(10)
#घोषणा DP83848_MISR_DUP_INT		BIT(11)
#घोषणा DP83848_MISR_SPD_INT		BIT(12)
#घोषणा DP83848_MISR_LINK_INT		BIT(13)
#घोषणा DP83848_MISR_ED_INT		BIT(14)

#घोषणा DP83848_INT_MASK		\
	(DP83848_MISR_ANC_INT |	\
	 DP83848_MISR_DUP_INT |	\
	 DP83848_MISR_SPD_INT |	\
	 DP83848_MISR_LINK_INT)

अटल पूर्णांक dp83848_ack_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err = phy_पढ़ो(phydev, DP83848_MISR);

	वापस err < 0 ? err : 0;
पूर्ण

अटल पूर्णांक dp83848_config_पूर्णांकr(काष्ठा phy_device *phydev)
अणु
	पूर्णांक control, ret;

	control = phy_पढ़ो(phydev, DP83848_MICR);
	अगर (control < 0)
		वापस control;

	अगर (phydev->पूर्णांकerrupts == PHY_INTERRUPT_ENABLED) अणु
		ret = dp83848_ack_पूर्णांकerrupt(phydev);
		अगर (ret)
			वापस ret;

		control |= DP83848_MICR_INT_OE;
		control |= DP83848_MICR_INTEN;

		ret = phy_ग_लिखो(phydev, DP83848_MISR, DP83848_INT_EN_MASK);
		अगर (ret < 0)
			वापस ret;

		ret = phy_ग_लिखो(phydev, DP83848_MICR, control);
	पूर्ण अन्यथा अणु
		control &= ~DP83848_MICR_INTEN;
		ret = phy_ग_लिखो(phydev, DP83848_MICR, control);
		अगर (ret)
			वापस ret;

		ret = dp83848_ack_पूर्णांकerrupt(phydev);
	पूर्ण

	वापस ret;
पूर्ण

अटल irqवापस_t dp83848_handle_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक irq_status;

	irq_status = phy_पढ़ो(phydev, DP83848_MISR);
	अगर (irq_status < 0) अणु
		phy_error(phydev);
		वापस IRQ_NONE;
	पूर्ण

	अगर (!(irq_status & DP83848_INT_MASK))
		वापस IRQ_NONE;

	phy_trigger_machine(phydev);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक dp83848_config_init(काष्ठा phy_device *phydev)
अणु
	पूर्णांक val;

	/* DP83620 always reports Auto Negotiation Ability on BMSR. Instead,
	 * we check initial value of BMCR Auto negotiation enable bit
	 */
	val = phy_पढ़ो(phydev, MII_BMCR);
	अगर (!(val & BMCR_ANENABLE))
		phydev->स्वतःneg = AUTONEG_DISABLE;

	वापस 0;
पूर्ण

अटल काष्ठा mdio_device_id __maybe_unused dp83848_tbl[] = अणु
	अणु TI_DP83848C_PHY_ID, 0xfffffff0 पूर्ण,
	अणु NS_DP83848C_PHY_ID, 0xfffffff0 पूर्ण,
	अणु TI_DP83620_PHY_ID, 0xfffffff0 पूर्ण,
	अणु TLK10X_PHY_ID, 0xfffffff0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(mdio, dp83848_tbl);

#घोषणा DP83848_PHY_DRIVER(_id, _name, _config_init)		\
	अणु							\
		.phy_id		= _id,				\
		.phy_id_mask	= 0xfffffff0,			\
		.name		= _name,			\
		/* PHY_BASIC_FEATURES */			\
								\
		.soft_reset	= genphy_soft_reset,		\
		.config_init	= _config_init,			\
		.suspend	= genphy_suspend,		\
		.resume		= genphy_resume,		\
								\
		/* IRQ related */				\
		.config_पूर्णांकr	= dp83848_config_पूर्णांकr,		\
		.handle_पूर्णांकerrupt = dp83848_handle_पूर्णांकerrupt,	\
	पूर्ण

अटल काष्ठा phy_driver dp83848_driver[] = अणु
	DP83848_PHY_DRIVER(TI_DP83848C_PHY_ID, "TI DP83848C 10/100 Mbps PHY",
			   शून्य),
	DP83848_PHY_DRIVER(NS_DP83848C_PHY_ID, "NS DP83848C 10/100 Mbps PHY",
			   शून्य),
	DP83848_PHY_DRIVER(TI_DP83620_PHY_ID, "TI DP83620 10/100 Mbps PHY",
			   dp83848_config_init),
	DP83848_PHY_DRIVER(TLK10X_PHY_ID, "TI TLK10X 10/100 Mbps PHY",
			   शून्य),
पूर्ण;
module_phy_driver(dp83848_driver);

MODULE_DESCRIPTION("Texas Instruments DP83848 PHY driver");
MODULE_AUTHOR("Andrew F. Davis <afd@ti.com>");
MODULE_LICENSE("GPL v2");
