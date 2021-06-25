<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * drivers/net/phy/lxt.c
 *
 * Driver क्रम Intel LXT PHYs
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

/* The Level one LXT970 is used by many boards				     */

#घोषणा MII_LXT970_IER       17  /* Interrupt Enable Register */

#घोषणा MII_LXT970_IER_IEN	0x0002

#घोषणा MII_LXT970_ISR       18  /* Interrupt Status Register */

#घोषणा MII_LXT970_IRS_MINT  BIT(15)

#घोषणा MII_LXT970_CONFIG    19  /* Configuration Register    */

/* ------------------------------------------------------------------------- */
/* The Level one LXT971 is used on some of my custom boards                  */

/* रेजिस्टर definitions क्रम the 971 */
#घोषणा MII_LXT971_IER		18  /* Interrupt Enable Register */
#घोषणा MII_LXT971_IER_IEN	0x00f2

#घोषणा MII_LXT971_ISR		19  /* Interrupt Status Register */
#घोषणा MII_LXT971_ISR_MASK	0x00f0

/* रेजिस्टर definitions क्रम the 973 */
#घोषणा MII_LXT973_PCR 16 /* Port Configuration Register */
#घोषणा PCR_FIBER_SELECT 1

MODULE_DESCRIPTION("Intel LXT PHY driver");
MODULE_AUTHOR("Andy Fleming");
MODULE_LICENSE("GPL");

अटल पूर्णांक lxt970_ack_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	err = phy_पढ़ो(phydev, MII_BMSR);

	अगर (err < 0)
		वापस err;

	err = phy_पढ़ो(phydev, MII_LXT970_ISR);

	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक lxt970_config_पूर्णांकr(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	अगर (phydev->पूर्णांकerrupts == PHY_INTERRUPT_ENABLED) अणु
		err = lxt970_ack_पूर्णांकerrupt(phydev);
		अगर (err)
			वापस err;

		err = phy_ग_लिखो(phydev, MII_LXT970_IER, MII_LXT970_IER_IEN);
	पूर्ण अन्यथा अणु
		err = phy_ग_लिखो(phydev, MII_LXT970_IER, 0);
		अगर (err)
			वापस err;

		err = lxt970_ack_पूर्णांकerrupt(phydev);
	पूर्ण

	वापस err;
पूर्ण

अटल irqवापस_t lxt970_handle_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक irq_status;

	/* The पूर्णांकerrupt status रेजिस्टर is cleared by पढ़ोing BMSR
	 * followed by MII_LXT970_ISR
	 */
	irq_status = phy_पढ़ो(phydev, MII_BMSR);
	अगर (irq_status < 0) अणु
		phy_error(phydev);
		वापस IRQ_NONE;
	पूर्ण

	irq_status = phy_पढ़ो(phydev, MII_LXT970_ISR);
	अगर (irq_status < 0) अणु
		phy_error(phydev);
		वापस IRQ_NONE;
	पूर्ण

	अगर (!(irq_status & MII_LXT970_IRS_MINT))
		वापस IRQ_NONE;

	phy_trigger_machine(phydev);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक lxt970_config_init(काष्ठा phy_device *phydev)
अणु
	वापस phy_ग_लिखो(phydev, MII_LXT970_CONFIG, 0);
पूर्ण


अटल पूर्णांक lxt971_ack_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err = phy_पढ़ो(phydev, MII_LXT971_ISR);

	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक lxt971_config_पूर्णांकr(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	अगर (phydev->पूर्णांकerrupts == PHY_INTERRUPT_ENABLED) अणु
		err = lxt971_ack_पूर्णांकerrupt(phydev);
		अगर (err)
			वापस err;

		err = phy_ग_लिखो(phydev, MII_LXT971_IER, MII_LXT971_IER_IEN);
	पूर्ण अन्यथा अणु
		err = phy_ग_लिखो(phydev, MII_LXT971_IER, 0);
		अगर (err)
			वापस err;

		err = lxt971_ack_पूर्णांकerrupt(phydev);
	पूर्ण

	वापस err;
पूर्ण

अटल irqवापस_t lxt971_handle_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक irq_status;

	irq_status = phy_पढ़ो(phydev, MII_LXT971_ISR);
	अगर (irq_status < 0) अणु
		phy_error(phydev);
		वापस IRQ_NONE;
	पूर्ण

	अगर (!(irq_status & MII_LXT971_ISR_MASK))
		वापस IRQ_NONE;

	phy_trigger_machine(phydev);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * A2 version of LXT973 chip has an ERRATA: it अक्रमomly वापस the contents
 * of the previous even रेजिस्टर when you पढ़ो a odd रेजिस्टर regularly
 */

अटल पूर्णांक lxt973a2_update_link(काष्ठा phy_device *phydev)
अणु
	पूर्णांक status;
	पूर्णांक control;
	पूर्णांक retry = 8; /* we try 8 बार */

	/* Do a fake पढ़ो */
	status = phy_पढ़ो(phydev, MII_BMSR);

	अगर (status < 0)
		वापस status;

	control = phy_पढ़ो(phydev, MII_BMCR);
	अगर (control < 0)
		वापस control;

	करो अणु
		/* Read link and स्वतःnegotiation status */
		status = phy_पढ़ो(phydev, MII_BMSR);
	पूर्ण जबतक (status >= 0 && retry-- && status == control);

	अगर (status < 0)
		वापस status;

	अगर ((status & BMSR_LSTATUS) == 0)
		phydev->link = 0;
	अन्यथा
		phydev->link = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक lxt973a2_पढ़ो_status(काष्ठा phy_device *phydev)
अणु
	पूर्णांक adv;
	पूर्णांक err;
	पूर्णांक lpa;

	/* Update the link, but वापस अगर there was an error */
	err = lxt973a2_update_link(phydev);
	अगर (err)
		वापस err;

	अगर (AUTONEG_ENABLE == phydev->स्वतःneg) अणु
		पूर्णांक retry = 1;

		adv = phy_पढ़ो(phydev, MII_ADVERTISE);

		अगर (adv < 0)
			वापस adv;

		करो अणु
			lpa = phy_पढ़ो(phydev, MII_LPA);

			अगर (lpa < 0)
				वापस lpa;

			/* If both रेजिस्टरs are equal, it is suspect but not
			* impossible, hence a new try
			*/
		पूर्ण जबतक (lpa == adv && retry--);

		mii_lpa_to_linkmode_lpa_t(phydev->lp_advertising, lpa);

		lpa &= adv;

		phydev->speed = SPEED_10;
		phydev->duplex = DUPLEX_HALF;
		phydev->छोड़ो = phydev->asym_छोड़ो = 0;

		अगर (lpa & (LPA_100FULL | LPA_100HALF)) अणु
			phydev->speed = SPEED_100;

			अगर (lpa & LPA_100FULL)
				phydev->duplex = DUPLEX_FULL;
		पूर्ण अन्यथा अणु
			अगर (lpa & LPA_10FULL)
				phydev->duplex = DUPLEX_FULL;
		पूर्ण

		phy_resolve_aneg_छोड़ो(phydev);
	पूर्ण अन्यथा अणु
		err = genphy_पढ़ो_status_fixed(phydev);
		अगर (err < 0)
			वापस err;

		phydev->छोड़ो = phydev->asym_छोड़ो = 0;
		linkmode_zero(phydev->lp_advertising);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lxt973_probe(काष्ठा phy_device *phydev)
अणु
	पूर्णांक val = phy_पढ़ो(phydev, MII_LXT973_PCR);

	अगर (val & PCR_FIBER_SELECT) अणु
		/*
		 * If fiber is selected, then the only correct setting
		 * is 100Mbps, full duplex, and स्वतः negotiation off.
		 */
		val = phy_पढ़ो(phydev, MII_BMCR);
		val |= (BMCR_SPEED100 | BMCR_FULLDPLX);
		val &= ~BMCR_ANENABLE;
		phy_ग_लिखो(phydev, MII_BMCR, val);
		/* Remember that the port is in fiber mode. */
		phydev->priv = lxt973_probe;
		phydev->port = PORT_FIBRE;
	पूर्ण अन्यथा अणु
		phydev->priv = शून्य;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक lxt973_config_aneg(काष्ठा phy_device *phydev)
अणु
	/* Do nothing अगर port is in fiber mode. */
	वापस phydev->priv ? 0 : genphy_config_aneg(phydev);
पूर्ण

अटल काष्ठा phy_driver lxt97x_driver[] = अणु
अणु
	.phy_id		= 0x78100000,
	.name		= "LXT970",
	.phy_id_mask	= 0xfffffff0,
	/* PHY_BASIC_FEATURES */
	.config_init	= lxt970_config_init,
	.config_पूर्णांकr	= lxt970_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = lxt970_handle_पूर्णांकerrupt,
पूर्ण, अणु
	.phy_id		= 0x001378e0,
	.name		= "LXT971",
	.phy_id_mask	= 0xfffffff0,
	/* PHY_BASIC_FEATURES */
	.config_पूर्णांकr	= lxt971_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = lxt971_handle_पूर्णांकerrupt,
	.suspend	= genphy_suspend,
	.resume		= genphy_resume,
पूर्ण, अणु
	.phy_id		= 0x00137a10,
	.name		= "LXT973-A2",
	.phy_id_mask	= 0xffffffff,
	/* PHY_BASIC_FEATURES */
	.flags		= 0,
	.probe		= lxt973_probe,
	.config_aneg	= lxt973_config_aneg,
	.पढ़ो_status	= lxt973a2_पढ़ो_status,
	.suspend	= genphy_suspend,
	.resume		= genphy_resume,
पूर्ण, अणु
	.phy_id		= 0x00137a10,
	.name		= "LXT973",
	.phy_id_mask	= 0xfffffff0,
	/* PHY_BASIC_FEATURES */
	.flags		= 0,
	.probe		= lxt973_probe,
	.config_aneg	= lxt973_config_aneg,
	.suspend	= genphy_suspend,
	.resume		= genphy_resume,
पूर्ण पूर्ण;

module_phy_driver(lxt97x_driver);

अटल काष्ठा mdio_device_id __maybe_unused lxt_tbl[] = अणु
	अणु 0x78100000, 0xfffffff0 पूर्ण,
	अणु 0x001378e0, 0xfffffff0 पूर्ण,
	अणु 0x00137a10, 0xfffffff0 पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(mdio, lxt_tbl);
