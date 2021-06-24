<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/net/ethernet/ibm/emac/phy.c
 *
 * Driver क्रम PowerPC 4xx on-chip ethernet controller, PHY support.
 * Borrowed from sungem_phy.c, though I only kept the generic MII
 * driver क्रम now.
 *
 * This file should be shared with other drivers or eventually
 * merged as the "low level" part of miilib
 *
 * Copyright 2007 Benjamin Herrenschmidt, IBM Corp.
 *                <benh@kernel.crashing.org>
 *
 * Based on the arch/ppc version of the driver:
 *
 * (c) 2003, Benjamin Herrenscmidt (benh@kernel.crashing.org)
 * (c) 2004-2005, Eugene Surovegin <ebs@ebshome.net>
 *
 */
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/mii.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/delay.h>

#समावेश "emac.h"
#समावेश "phy.h"

#घोषणा phy_पढ़ो _phy_पढ़ो
#घोषणा phy_ग_लिखो _phy_ग_लिखो

अटल अंतरभूत पूर्णांक _phy_पढ़ो(काष्ठा mii_phy *phy, पूर्णांक reg)
अणु
	वापस phy->mdio_पढ़ो(phy->dev, phy->address, reg);
पूर्ण

अटल अंतरभूत व्योम _phy_ग_लिखो(काष्ठा mii_phy *phy, पूर्णांक reg, पूर्णांक val)
अणु
	phy->mdio_ग_लिखो(phy->dev, phy->address, reg, val);
पूर्ण

अटल अंतरभूत पूर्णांक gpcs_phy_पढ़ो(काष्ठा mii_phy *phy, पूर्णांक reg)
अणु
	वापस phy->mdio_पढ़ो(phy->dev, phy->gpcs_address, reg);
पूर्ण

अटल अंतरभूत व्योम gpcs_phy_ग_लिखो(काष्ठा mii_phy *phy, पूर्णांक reg, पूर्णांक val)
अणु
	phy->mdio_ग_लिखो(phy->dev, phy->gpcs_address, reg, val);
पूर्ण

पूर्णांक emac_mii_reset_phy(काष्ठा mii_phy *phy)
अणु
	पूर्णांक val;
	पूर्णांक limit = 10000;

	val = phy_पढ़ो(phy, MII_BMCR);
	val &= ~(BMCR_ISOLATE | BMCR_ANENABLE);
	val |= BMCR_RESET;
	phy_ग_लिखो(phy, MII_BMCR, val);

	udelay(300);

	जबतक (--limit) अणु
		val = phy_पढ़ो(phy, MII_BMCR);
		अगर (val >= 0 && (val & BMCR_RESET) == 0)
			अवरोध;
		udelay(10);
	पूर्ण
	अगर ((val & BMCR_ISOLATE) && limit > 0)
		phy_ग_लिखो(phy, MII_BMCR, val & ~BMCR_ISOLATE);

	वापस limit <= 0;
पूर्ण

पूर्णांक emac_mii_reset_gpcs(काष्ठा mii_phy *phy)
अणु
	पूर्णांक val;
	पूर्णांक limit = 10000;

	val = gpcs_phy_पढ़ो(phy, MII_BMCR);
	val &= ~(BMCR_ISOLATE | BMCR_ANENABLE);
	val |= BMCR_RESET;
	gpcs_phy_ग_लिखो(phy, MII_BMCR, val);

	udelay(300);

	जबतक (--limit) अणु
		val = gpcs_phy_पढ़ो(phy, MII_BMCR);
		अगर (val >= 0 && (val & BMCR_RESET) == 0)
			अवरोध;
		udelay(10);
	पूर्ण
	अगर ((val & BMCR_ISOLATE) && limit > 0)
		gpcs_phy_ग_लिखो(phy, MII_BMCR, val & ~BMCR_ISOLATE);

	अगर (limit > 0 && phy->mode == PHY_INTERFACE_MODE_SGMII) अणु
		/* Configure GPCS पूर्णांकerface to recommended setting क्रम SGMII */
		gpcs_phy_ग_लिखो(phy, 0x04, 0x8120); /* AsymPause, FDX */
		gpcs_phy_ग_लिखो(phy, 0x07, 0x2801); /* msg_pg, toggle */
		gpcs_phy_ग_लिखो(phy, 0x00, 0x0140); /* 1Gbps, FDX     */
	पूर्ण

	वापस limit <= 0;
पूर्ण

अटल पूर्णांक genmii_setup_aneg(काष्ठा mii_phy *phy, u32 advertise)
अणु
	पूर्णांक ctl, adv;

	phy->स्वतःneg = AUTONEG_ENABLE;
	phy->speed = SPEED_10;
	phy->duplex = DUPLEX_HALF;
	phy->छोड़ो = phy->asym_छोड़ो = 0;
	phy->advertising = advertise;

	ctl = phy_पढ़ो(phy, MII_BMCR);
	अगर (ctl < 0)
		वापस ctl;
	ctl &= ~(BMCR_FULLDPLX | BMCR_SPEED100 | BMCR_SPEED1000 | BMCR_ANENABLE);

	/* First clear the PHY */
	phy_ग_लिखो(phy, MII_BMCR, ctl);

	/* Setup standard advertise */
	adv = phy_पढ़ो(phy, MII_ADVERTISE);
	अगर (adv < 0)
		वापस adv;
	adv &= ~(ADVERTISE_ALL | ADVERTISE_100BASE4 | ADVERTISE_PAUSE_CAP |
		 ADVERTISE_PAUSE_ASYM);
	अगर (advertise & ADVERTISED_10baseT_Half)
		adv |= ADVERTISE_10HALF;
	अगर (advertise & ADVERTISED_10baseT_Full)
		adv |= ADVERTISE_10FULL;
	अगर (advertise & ADVERTISED_100baseT_Half)
		adv |= ADVERTISE_100HALF;
	अगर (advertise & ADVERTISED_100baseT_Full)
		adv |= ADVERTISE_100FULL;
	अगर (advertise & ADVERTISED_Pause)
		adv |= ADVERTISE_PAUSE_CAP;
	अगर (advertise & ADVERTISED_Asym_Pause)
		adv |= ADVERTISE_PAUSE_ASYM;
	phy_ग_लिखो(phy, MII_ADVERTISE, adv);

	अगर (phy->features &
	    (SUPPORTED_1000baseT_Full | SUPPORTED_1000baseT_Half)) अणु
		adv = phy_पढ़ो(phy, MII_CTRL1000);
		अगर (adv < 0)
			वापस adv;
		adv &= ~(ADVERTISE_1000FULL | ADVERTISE_1000HALF);
		अगर (advertise & ADVERTISED_1000baseT_Full)
			adv |= ADVERTISE_1000FULL;
		अगर (advertise & ADVERTISED_1000baseT_Half)
			adv |= ADVERTISE_1000HALF;
		phy_ग_लिखो(phy, MII_CTRL1000, adv);
	पूर्ण

	/* Start/Restart aneg */
	ctl = phy_पढ़ो(phy, MII_BMCR);
	ctl |= (BMCR_ANENABLE | BMCR_ANRESTART);
	phy_ग_लिखो(phy, MII_BMCR, ctl);

	वापस 0;
पूर्ण

अटल पूर्णांक genmii_setup_क्रमced(काष्ठा mii_phy *phy, पूर्णांक speed, पूर्णांक fd)
अणु
	पूर्णांक ctl;

	phy->स्वतःneg = AUTONEG_DISABLE;
	phy->speed = speed;
	phy->duplex = fd;
	phy->छोड़ो = phy->asym_छोड़ो = 0;

	ctl = phy_पढ़ो(phy, MII_BMCR);
	अगर (ctl < 0)
		वापस ctl;
	ctl &= ~(BMCR_FULLDPLX | BMCR_SPEED100 | BMCR_SPEED1000 | BMCR_ANENABLE);

	/* First clear the PHY */
	phy_ग_लिखो(phy, MII_BMCR, ctl | BMCR_RESET);

	/* Select speed & duplex */
	चयन (speed) अणु
	हाल SPEED_10:
		अवरोध;
	हाल SPEED_100:
		ctl |= BMCR_SPEED100;
		अवरोध;
	हाल SPEED_1000:
		ctl |= BMCR_SPEED1000;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	अगर (fd == DUPLEX_FULL)
		ctl |= BMCR_FULLDPLX;
	phy_ग_लिखो(phy, MII_BMCR, ctl);

	वापस 0;
पूर्ण

अटल पूर्णांक genmii_poll_link(काष्ठा mii_phy *phy)
अणु
	पूर्णांक status;

	/* Clear latched value with dummy पढ़ो */
	phy_पढ़ो(phy, MII_BMSR);
	status = phy_पढ़ो(phy, MII_BMSR);
	अगर (status < 0 || (status & BMSR_LSTATUS) == 0)
		वापस 0;
	अगर (phy->स्वतःneg == AUTONEG_ENABLE && !(status & BMSR_ANEGCOMPLETE))
		वापस 0;
	वापस 1;
पूर्ण

अटल पूर्णांक genmii_पढ़ो_link(काष्ठा mii_phy *phy)
अणु
	अगर (phy->स्वतःneg == AUTONEG_ENABLE) अणु
		पूर्णांक glpa = 0;
		पूर्णांक lpa = phy_पढ़ो(phy, MII_LPA) & phy_पढ़ो(phy, MII_ADVERTISE);
		अगर (lpa < 0)
			वापस lpa;

		अगर (phy->features &
		    (SUPPORTED_1000baseT_Full | SUPPORTED_1000baseT_Half)) अणु
			पूर्णांक adv = phy_पढ़ो(phy, MII_CTRL1000);
			glpa = phy_पढ़ो(phy, MII_STAT1000);

			अगर (glpa < 0 || adv < 0)
				वापस adv;

			glpa &= adv << 2;
		पूर्ण

		phy->speed = SPEED_10;
		phy->duplex = DUPLEX_HALF;
		phy->छोड़ो = phy->asym_छोड़ो = 0;

		अगर (glpa & (LPA_1000FULL | LPA_1000HALF)) अणु
			phy->speed = SPEED_1000;
			अगर (glpa & LPA_1000FULL)
				phy->duplex = DUPLEX_FULL;
		पूर्ण अन्यथा अगर (lpa & (LPA_100FULL | LPA_100HALF)) अणु
			phy->speed = SPEED_100;
			अगर (lpa & LPA_100FULL)
				phy->duplex = DUPLEX_FULL;
		पूर्ण अन्यथा अगर (lpa & LPA_10FULL)
			phy->duplex = DUPLEX_FULL;

		अगर (phy->duplex == DUPLEX_FULL) अणु
			phy->छोड़ो = lpa & LPA_PAUSE_CAP ? 1 : 0;
			phy->asym_छोड़ो = lpa & LPA_PAUSE_ASYM ? 1 : 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		पूर्णांक bmcr = phy_पढ़ो(phy, MII_BMCR);
		अगर (bmcr < 0)
			वापस bmcr;

		अगर (bmcr & BMCR_FULLDPLX)
			phy->duplex = DUPLEX_FULL;
		अन्यथा
			phy->duplex = DUPLEX_HALF;
		अगर (bmcr & BMCR_SPEED1000)
			phy->speed = SPEED_1000;
		अन्यथा अगर (bmcr & BMCR_SPEED100)
			phy->speed = SPEED_100;
		अन्यथा
			phy->speed = SPEED_10;

		phy->छोड़ो = phy->asym_छोड़ो = 0;
	पूर्ण
	वापस 0;
पूर्ण

/* Generic implementation क्रम most 10/100/1000 PHYs */
अटल स्थिर काष्ठा mii_phy_ops generic_phy_ops = अणु
	.setup_aneg	= genmii_setup_aneg,
	.setup_क्रमced	= genmii_setup_क्रमced,
	.poll_link	= genmii_poll_link,
	.पढ़ो_link	= genmii_पढ़ो_link
पूर्ण;

अटल काष्ठा mii_phy_def genmii_phy_def = अणु
	.phy_id		= 0x00000000,
	.phy_id_mask	= 0x00000000,
	.name		= "Generic MII",
	.ops		= &generic_phy_ops
पूर्ण;

/* CIS8201 */
#घोषणा MII_CIS8201_10BTCSR	0x16
#घोषणा  TENBTCSR_ECHO_DISABLE	0x2000
#घोषणा MII_CIS8201_EPCR	0x17
#घोषणा  EPCR_MODE_MASK		0x3000
#घोषणा  EPCR_GMII_MODE		0x0000
#घोषणा  EPCR_RGMII_MODE	0x1000
#घोषणा  EPCR_TBI_MODE		0x2000
#घोषणा  EPCR_RTBI_MODE		0x3000
#घोषणा MII_CIS8201_ACSR	0x1c
#घोषणा  ACSR_PIN_PRIO_SELECT	0x0004

अटल पूर्णांक cis8201_init(काष्ठा mii_phy *phy)
अणु
	पूर्णांक epcr;

	epcr = phy_पढ़ो(phy, MII_CIS8201_EPCR);
	अगर (epcr < 0)
		वापस epcr;

	epcr &= ~EPCR_MODE_MASK;

	चयन (phy->mode) अणु
	हाल PHY_INTERFACE_MODE_TBI:
		epcr |= EPCR_TBI_MODE;
		अवरोध;
	हाल PHY_INTERFACE_MODE_RTBI:
		epcr |= EPCR_RTBI_MODE;
		अवरोध;
	हाल PHY_INTERFACE_MODE_GMII:
		epcr |= EPCR_GMII_MODE;
		अवरोध;
	हाल PHY_INTERFACE_MODE_RGMII:
	शेष:
		epcr |= EPCR_RGMII_MODE;
	पूर्ण

	phy_ग_लिखो(phy, MII_CIS8201_EPCR, epcr);

	/* MII regs override strap pins */
	phy_ग_लिखो(phy, MII_CIS8201_ACSR,
		  phy_पढ़ो(phy, MII_CIS8201_ACSR) | ACSR_PIN_PRIO_SELECT);

	/* Disable TX_EN -> CRS echo mode, otherwise 10/HDX करोesn't work */
	phy_ग_लिखो(phy, MII_CIS8201_10BTCSR,
		  phy_पढ़ो(phy, MII_CIS8201_10BTCSR) | TENBTCSR_ECHO_DISABLE);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mii_phy_ops cis8201_phy_ops = अणु
	.init		= cis8201_init,
	.setup_aneg	= genmii_setup_aneg,
	.setup_क्रमced	= genmii_setup_क्रमced,
	.poll_link	= genmii_poll_link,
	.पढ़ो_link	= genmii_पढ़ो_link
पूर्ण;

अटल काष्ठा mii_phy_def cis8201_phy_def = अणु
	.phy_id		= 0x000fc410,
	.phy_id_mask	= 0x000ffff0,
	.name		= "CIS8201 Gigabit Ethernet",
	.ops		= &cis8201_phy_ops
पूर्ण;

अटल काष्ठा mii_phy_def bcm5248_phy_def = अणु

	.phy_id		= 0x0143bc00,
	.phy_id_mask	= 0x0ffffff0,
	.name		= "BCM5248 10/100 SMII Ethernet",
	.ops		= &generic_phy_ops
पूर्ण;

अटल पूर्णांक m88e1111_init(काष्ठा mii_phy *phy)
अणु
	pr_debug("%s: Marvell 88E1111 Ethernet\n", __func__);
	phy_ग_लिखो(phy, 0x14, 0x0ce3);
	phy_ग_लिखो(phy, 0x18, 0x4101);
	phy_ग_लिखो(phy, 0x09, 0x0e00);
	phy_ग_लिखो(phy, 0x04, 0x01e1);
	phy_ग_लिखो(phy, 0x00, 0x9140);
	phy_ग_लिखो(phy, 0x00, 0x1140);

	वापस  0;
पूर्ण

अटल पूर्णांक m88e1112_init(काष्ठा mii_phy *phy)
अणु
	/*
	 * Marvell 88E1112 PHY needs to have the SGMII MAC
	 * पूर्णांकerace (page 2) properly configured to
	 * communicate with the 460EX/GT GPCS पूर्णांकerface.
	 */

	u16 reg_लघु;

	pr_debug("%s: Marvell 88E1112 Ethernet\n", __func__);

	/* Set access to Page 2 */
	phy_ग_लिखो(phy, 0x16, 0x0002);

	phy_ग_लिखो(phy, 0x00, 0x0040); /* 1Gbps */
	reg_लघु = (u16)(phy_पढ़ो(phy, 0x1a));
	reg_लघु |= 0x8000; /* bypass Auto-Negotiation */
	phy_ग_लिखो(phy, 0x1a, reg_लघु);
	emac_mii_reset_phy(phy); /* reset MAC पूर्णांकerface */

	/* Reset access to Page 0 */
	phy_ग_लिखो(phy, 0x16, 0x0000);

	वापस  0;
पूर्ण

अटल पूर्णांक et1011c_init(काष्ठा mii_phy *phy)
अणु
	u16 reg_लघु;

	reg_लघु = (u16)(phy_पढ़ो(phy, 0x16));
	reg_लघु &= ~(0x7);
	reg_लघु |= 0x6;	/* RGMII Trace Delay*/
	phy_ग_लिखो(phy, 0x16, reg_लघु);

	reg_लघु = (u16)(phy_पढ़ो(phy, 0x17));
	reg_लघु &= ~(0x40);
	phy_ग_लिखो(phy, 0x17, reg_लघु);

	phy_ग_लिखो(phy, 0x1c, 0x74f0);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mii_phy_ops et1011c_phy_ops = अणु
	.init		= et1011c_init,
	.setup_aneg	= genmii_setup_aneg,
	.setup_क्रमced	= genmii_setup_क्रमced,
	.poll_link	= genmii_poll_link,
	.पढ़ो_link	= genmii_पढ़ो_link
पूर्ण;

अटल काष्ठा mii_phy_def et1011c_phy_def = अणु
	.phy_id		= 0x0282f000,
	.phy_id_mask	= 0x0fffff00,
	.name		= "ET1011C Gigabit Ethernet",
	.ops		= &et1011c_phy_ops
पूर्ण;





अटल स्थिर काष्ठा mii_phy_ops m88e1111_phy_ops = अणु
	.init		= m88e1111_init,
	.setup_aneg	= genmii_setup_aneg,
	.setup_क्रमced	= genmii_setup_क्रमced,
	.poll_link	= genmii_poll_link,
	.पढ़ो_link	= genmii_पढ़ो_link
पूर्ण;

अटल काष्ठा mii_phy_def m88e1111_phy_def = अणु

	.phy_id		= 0x01410CC0,
	.phy_id_mask	= 0x0ffffff0,
	.name		= "Marvell 88E1111 Ethernet",
	.ops		= &m88e1111_phy_ops,
पूर्ण;

अटल स्थिर काष्ठा mii_phy_ops m88e1112_phy_ops = अणु
	.init		= m88e1112_init,
	.setup_aneg	= genmii_setup_aneg,
	.setup_क्रमced	= genmii_setup_क्रमced,
	.poll_link	= genmii_poll_link,
	.पढ़ो_link	= genmii_पढ़ो_link
पूर्ण;

अटल काष्ठा mii_phy_def m88e1112_phy_def = अणु
	.phy_id		= 0x01410C90,
	.phy_id_mask	= 0x0ffffff0,
	.name		= "Marvell 88E1112 Ethernet",
	.ops		= &m88e1112_phy_ops,
पूर्ण;

अटल पूर्णांक ar8035_init(काष्ठा mii_phy *phy)
अणु
	phy_ग_लिखो(phy, 0x1d, 0x5); /* Address debug रेजिस्टर 5 */
	phy_ग_लिखो(phy, 0x1e, 0x2d47); /* Value copied from u-boot */
	phy_ग_लिखो(phy, 0x1d, 0xb);    /* Address hib ctrl */
	phy_ग_लिखो(phy, 0x1e, 0xbc20); /* Value copied from u-boot */

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mii_phy_ops ar8035_phy_ops = अणु
	.init		= ar8035_init,
	.setup_aneg	= genmii_setup_aneg,
	.setup_क्रमced	= genmii_setup_क्रमced,
	.poll_link	= genmii_poll_link,
	.पढ़ो_link	= genmii_पढ़ो_link,
पूर्ण;

अटल काष्ठा mii_phy_def ar8035_phy_def = अणु
	.phy_id		= 0x004dd070,
	.phy_id_mask	= 0xfffffff0,
	.name		= "Atheros 8035 Gigabit Ethernet",
	.ops		= &ar8035_phy_ops,
पूर्ण;

अटल काष्ठा mii_phy_def *mii_phy_table[] = अणु
	&et1011c_phy_def,
	&cis8201_phy_def,
	&bcm5248_phy_def,
	&m88e1111_phy_def,
	&m88e1112_phy_def,
	&ar8035_phy_def,
	&genmii_phy_def,
	शून्य
पूर्ण;

पूर्णांक emac_mii_phy_probe(काष्ठा mii_phy *phy, पूर्णांक address)
अणु
	काष्ठा mii_phy_def *def;
	पूर्णांक i;
	u32 id;

	phy->स्वतःneg = AUTONEG_DISABLE;
	phy->advertising = 0;
	phy->address = address;
	phy->speed = SPEED_10;
	phy->duplex = DUPLEX_HALF;
	phy->छोड़ो = phy->asym_छोड़ो = 0;

	/* Take PHY out of isolate mode and reset it. */
	अगर (emac_mii_reset_phy(phy))
		वापस -ENODEV;

	/* Read ID and find matching entry */
	id = (phy_पढ़ो(phy, MII_PHYSID1) << 16) | phy_पढ़ो(phy, MII_PHYSID2);
	क्रम (i = 0; (def = mii_phy_table[i]) != शून्य; i++)
		अगर ((id & def->phy_id_mask) == def->phy_id)
			अवरोध;
	/* Should never be शून्य (we have a generic entry), but... */
	अगर (!def)
		वापस -ENODEV;

	phy->def = def;

	/* Determine PHY features अगर needed */
	phy->features = def->features;
	अगर (!phy->features) अणु
		u16 bmsr = phy_पढ़ो(phy, MII_BMSR);
		अगर (bmsr & BMSR_ANEGCAPABLE)
			phy->features |= SUPPORTED_Autoneg;
		अगर (bmsr & BMSR_10HALF)
			phy->features |= SUPPORTED_10baseT_Half;
		अगर (bmsr & BMSR_10FULL)
			phy->features |= SUPPORTED_10baseT_Full;
		अगर (bmsr & BMSR_100HALF)
			phy->features |= SUPPORTED_100baseT_Half;
		अगर (bmsr & BMSR_100FULL)
			phy->features |= SUPPORTED_100baseT_Full;
		अगर (bmsr & BMSR_ESTATEN) अणु
			u16 esr = phy_पढ़ो(phy, MII_ESTATUS);
			अगर (esr & ESTATUS_1000_TFULL)
				phy->features |= SUPPORTED_1000baseT_Full;
			अगर (esr & ESTATUS_1000_THALF)
				phy->features |= SUPPORTED_1000baseT_Half;
		पूर्ण
		phy->features |= SUPPORTED_MII;
	पूर्ण

	/* Setup शेष advertising */
	phy->advertising = phy->features;

	वापस 0;
पूर्ण

MODULE_LICENSE("GPL");
