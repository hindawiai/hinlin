<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* $Date: 2005/10/24 23:18:13 $ $RCSfile: mv88e1xxx.c,v $ $Revision: 1.49 $ */
#समावेश "common.h"
#समावेश "mv88e1xxx.h"
#समावेश "cphy.h"
#समावेश "elmer0.h"

/* MV88E1XXX MDI crossover रेजिस्टर values */
#घोषणा CROSSOVER_MDI   0
#घोषणा CROSSOVER_MDIX  1
#घोषणा CROSSOVER_AUTO  3

#घोषणा INTR_ENABLE_MASK 0x6CA0

/*
 * Set the bits given by 'bitval' in PHY register 'reg'.
 */
अटल व्योम mdio_set_bit(काष्ठा cphy *cphy, पूर्णांक reg, u32 bitval)
अणु
	u32 val;

	(व्योम) simple_mdio_पढ़ो(cphy, reg, &val);
	(व्योम) simple_mdio_ग_लिखो(cphy, reg, val | bitval);
पूर्ण

/*
 * Clear the bits given by 'bitval' in PHY register 'reg'.
 */
अटल व्योम mdio_clear_bit(काष्ठा cphy *cphy, पूर्णांक reg, u32 bitval)
अणु
	u32 val;

	(व्योम) simple_mdio_पढ़ो(cphy, reg, &val);
	(व्योम) simple_mdio_ग_लिखो(cphy, reg, val & ~bitval);
पूर्ण

/*
 * NAME:   phy_reset
 *
 * DESC:   Reset the given PHY's port. NOTE: This is not a global
 *         chip reset.
 *
 * PARAMS: cphy     - Poपूर्णांकer to PHY instance data.
 *
 * RETURN:  0 - Successful reset.
 *         -1 - Timeout.
 */
अटल पूर्णांक mv88e1xxx_reset(काष्ठा cphy *cphy, पूर्णांक रुको)
अणु
	u32 ctl;
	पूर्णांक समय_out = 1000;

	mdio_set_bit(cphy, MII_BMCR, BMCR_RESET);

	करो अणु
		(व्योम) simple_mdio_पढ़ो(cphy, MII_BMCR, &ctl);
		ctl &= BMCR_RESET;
		अगर (ctl)
			udelay(1);
	पूर्ण जबतक (ctl && --समय_out);

	वापस ctl ? -1 : 0;
पूर्ण

अटल पूर्णांक mv88e1xxx_पूर्णांकerrupt_enable(काष्ठा cphy *cphy)
अणु
	/* Enable PHY पूर्णांकerrupts. */
	(व्योम) simple_mdio_ग_लिखो(cphy, MV88E1XXX_INTERRUPT_ENABLE_REGISTER,
		   INTR_ENABLE_MASK);

	/* Enable Marvell पूर्णांकerrupts through Elmer0. */
	अगर (t1_is_asic(cphy->adapter)) अणु
		u32 elmer;

		t1_tpi_पढ़ो(cphy->adapter, A_ELMER0_INT_ENABLE, &elmer);
		elmer |= ELMER0_GP_BIT1;
		अगर (is_T2(cphy->adapter))
		    elmer |= ELMER0_GP_BIT2 | ELMER0_GP_BIT3 | ELMER0_GP_BIT4;
		t1_tpi_ग_लिखो(cphy->adapter, A_ELMER0_INT_ENABLE, elmer);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mv88e1xxx_पूर्णांकerrupt_disable(काष्ठा cphy *cphy)
अणु
	/* Disable all phy पूर्णांकerrupts. */
	(व्योम) simple_mdio_ग_लिखो(cphy, MV88E1XXX_INTERRUPT_ENABLE_REGISTER, 0);

	/* Disable Marvell पूर्णांकerrupts through Elmer0. */
	अगर (t1_is_asic(cphy->adapter)) अणु
		u32 elmer;

		t1_tpi_पढ़ो(cphy->adapter, A_ELMER0_INT_ENABLE, &elmer);
		elmer &= ~ELMER0_GP_BIT1;
		अगर (is_T2(cphy->adapter))
		    elmer &= ~(ELMER0_GP_BIT2|ELMER0_GP_BIT3|ELMER0_GP_BIT4);
		t1_tpi_ग_लिखो(cphy->adapter, A_ELMER0_INT_ENABLE, elmer);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mv88e1xxx_पूर्णांकerrupt_clear(काष्ठा cphy *cphy)
अणु
	u32 elmer;

	/* Clear PHY पूर्णांकerrupts by पढ़ोing the रेजिस्टर. */
	(व्योम) simple_mdio_पढ़ो(cphy,
			MV88E1XXX_INTERRUPT_STATUS_REGISTER, &elmer);

	/* Clear Marvell पूर्णांकerrupts through Elmer0. */
	अगर (t1_is_asic(cphy->adapter)) अणु
		t1_tpi_पढ़ो(cphy->adapter, A_ELMER0_INT_CAUSE, &elmer);
		elmer |= ELMER0_GP_BIT1;
		अगर (is_T2(cphy->adapter))
		    elmer |= ELMER0_GP_BIT2|ELMER0_GP_BIT3|ELMER0_GP_BIT4;
		t1_tpi_ग_लिखो(cphy->adapter, A_ELMER0_INT_CAUSE, elmer);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Set the PHY speed and duplex.  This also disables स्वतः-negotiation, except
 * क्रम 1Gb/s, where स्वतः-negotiation is mandatory.
 */
अटल पूर्णांक mv88e1xxx_set_speed_duplex(काष्ठा cphy *phy, पूर्णांक speed, पूर्णांक duplex)
अणु
	u32 ctl;

	(व्योम) simple_mdio_पढ़ो(phy, MII_BMCR, &ctl);
	अगर (speed >= 0) अणु
		ctl &= ~(BMCR_SPEED100 | BMCR_SPEED1000 | BMCR_ANENABLE);
		अगर (speed == SPEED_100)
			ctl |= BMCR_SPEED100;
		अन्यथा अगर (speed == SPEED_1000)
			ctl |= BMCR_SPEED1000;
	पूर्ण
	अगर (duplex >= 0) अणु
		ctl &= ~(BMCR_FULLDPLX | BMCR_ANENABLE);
		अगर (duplex == DUPLEX_FULL)
			ctl |= BMCR_FULLDPLX;
	पूर्ण
	अगर (ctl & BMCR_SPEED1000)  /* स्वतः-negotiation required क्रम 1Gb/s */
		ctl |= BMCR_ANENABLE;
	(व्योम) simple_mdio_ग_लिखो(phy, MII_BMCR, ctl);
	वापस 0;
पूर्ण

अटल पूर्णांक mv88e1xxx_crossover_set(काष्ठा cphy *cphy, पूर्णांक crossover)
अणु
	u32 data32;

	(व्योम) simple_mdio_पढ़ो(cphy,
			MV88E1XXX_SPECIFIC_CNTRL_REGISTER, &data32);
	data32 &= ~V_PSCR_MDI_XOVER_MODE(M_PSCR_MDI_XOVER_MODE);
	data32 |= V_PSCR_MDI_XOVER_MODE(crossover);
	(व्योम) simple_mdio_ग_लिखो(cphy,
			MV88E1XXX_SPECIFIC_CNTRL_REGISTER, data32);
	वापस 0;
पूर्ण

अटल पूर्णांक mv88e1xxx_स्वतःneg_enable(काष्ठा cphy *cphy)
अणु
	u32 ctl;

	(व्योम) mv88e1xxx_crossover_set(cphy, CROSSOVER_AUTO);

	(व्योम) simple_mdio_पढ़ो(cphy, MII_BMCR, &ctl);
	/* restart स्वतःneg क्रम change to take effect */
	ctl |= BMCR_ANENABLE | BMCR_ANRESTART;
	(व्योम) simple_mdio_ग_लिखो(cphy, MII_BMCR, ctl);
	वापस 0;
पूर्ण

अटल पूर्णांक mv88e1xxx_स्वतःneg_disable(काष्ठा cphy *cphy)
अणु
	u32 ctl;

	/*
	 * Crossover *must* be set to manual in order to disable स्वतः-neg.
	 * The Alaska FAQs करोcument highlights this poपूर्णांक.
	 */
	(व्योम) mv88e1xxx_crossover_set(cphy, CROSSOVER_MDI);

	/*
	 * Must include स्वतःneg reset when disabling स्वतः-neg. This
	 * is described in the Alaska FAQ करोcument.
	 */
	(व्योम) simple_mdio_पढ़ो(cphy, MII_BMCR, &ctl);
	ctl &= ~BMCR_ANENABLE;
	(व्योम) simple_mdio_ग_लिखो(cphy, MII_BMCR, ctl | BMCR_ANRESTART);
	वापस 0;
पूर्ण

अटल पूर्णांक mv88e1xxx_स्वतःneg_restart(काष्ठा cphy *cphy)
अणु
	mdio_set_bit(cphy, MII_BMCR, BMCR_ANRESTART);
	वापस 0;
पूर्ण

अटल पूर्णांक mv88e1xxx_advertise(काष्ठा cphy *phy, अचिन्हित पूर्णांक advertise_map)
अणु
	u32 val = 0;

	अगर (advertise_map &
	    (ADVERTISED_1000baseT_Half | ADVERTISED_1000baseT_Full)) अणु
		(व्योम) simple_mdio_पढ़ो(phy, MII_GBCR, &val);
		val &= ~(GBCR_ADV_1000HALF | GBCR_ADV_1000FULL);
		अगर (advertise_map & ADVERTISED_1000baseT_Half)
			val |= GBCR_ADV_1000HALF;
		अगर (advertise_map & ADVERTISED_1000baseT_Full)
			val |= GBCR_ADV_1000FULL;
	पूर्ण
	(व्योम) simple_mdio_ग_लिखो(phy, MII_GBCR, val);

	val = 1;
	अगर (advertise_map & ADVERTISED_10baseT_Half)
		val |= ADVERTISE_10HALF;
	अगर (advertise_map & ADVERTISED_10baseT_Full)
		val |= ADVERTISE_10FULL;
	अगर (advertise_map & ADVERTISED_100baseT_Half)
		val |= ADVERTISE_100HALF;
	अगर (advertise_map & ADVERTISED_100baseT_Full)
		val |= ADVERTISE_100FULL;
	अगर (advertise_map & ADVERTISED_PAUSE)
		val |= ADVERTISE_PAUSE;
	अगर (advertise_map & ADVERTISED_ASYM_PAUSE)
		val |= ADVERTISE_PAUSE_ASYM;
	(व्योम) simple_mdio_ग_लिखो(phy, MII_ADVERTISE, val);
	वापस 0;
पूर्ण

अटल पूर्णांक mv88e1xxx_set_loopback(काष्ठा cphy *cphy, पूर्णांक on)
अणु
	अगर (on)
		mdio_set_bit(cphy, MII_BMCR, BMCR_LOOPBACK);
	अन्यथा
		mdio_clear_bit(cphy, MII_BMCR, BMCR_LOOPBACK);
	वापस 0;
पूर्ण

अटल पूर्णांक mv88e1xxx_get_link_status(काष्ठा cphy *cphy, पूर्णांक *link_ok,
				     पूर्णांक *speed, पूर्णांक *duplex, पूर्णांक *fc)
अणु
	u32 status;
	पूर्णांक sp = -1, dplx = -1, छोड़ो = 0;

	(व्योम) simple_mdio_पढ़ो(cphy,
			MV88E1XXX_SPECIFIC_STATUS_REGISTER, &status);
	अगर ((status & V_PSSR_STATUS_RESOLVED) != 0) अणु
		अगर (status & V_PSSR_RX_PAUSE)
			छोड़ो |= PAUSE_RX;
		अगर (status & V_PSSR_TX_PAUSE)
			छोड़ो |= PAUSE_TX;
		dplx = (status & V_PSSR_DUPLEX) ? DUPLEX_FULL : DUPLEX_HALF;
		sp = G_PSSR_SPEED(status);
		अगर (sp == 0)
			sp = SPEED_10;
		अन्यथा अगर (sp == 1)
			sp = SPEED_100;
		अन्यथा
			sp = SPEED_1000;
	पूर्ण
	अगर (link_ok)
		*link_ok = (status & V_PSSR_LINK) != 0;
	अगर (speed)
		*speed = sp;
	अगर (duplex)
		*duplex = dplx;
	अगर (fc)
		*fc = छोड़ो;
	वापस 0;
पूर्ण

अटल पूर्णांक mv88e1xxx_करोwnshअगरt_set(काष्ठा cphy *cphy, पूर्णांक करोwnshअगरt_enable)
अणु
	u32 val;

	(व्योम) simple_mdio_पढ़ो(cphy,
		MV88E1XXX_EXT_PHY_SPECIFIC_CNTRL_REGISTER, &val);

	/*
	 * Set the करोwnshअगरt counter to 2 so we try to establish Gb link
	 * twice beक्रमe करोwnshअगरting.
	 */
	val &= ~(V_DOWNSHIFT_ENABLE | V_DOWNSHIFT_CNT(M_DOWNSHIFT_CNT));

	अगर (करोwnshअगरt_enable)
		val |= V_DOWNSHIFT_ENABLE | V_DOWNSHIFT_CNT(2);
	(व्योम) simple_mdio_ग_लिखो(cphy,
			MV88E1XXX_EXT_PHY_SPECIFIC_CNTRL_REGISTER, val);
	वापस 0;
पूर्ण

अटल पूर्णांक mv88e1xxx_पूर्णांकerrupt_handler(काष्ठा cphy *cphy)
अणु
	पूर्णांक cphy_cause = 0;
	u32 status;

	/*
	 * Loop until cause पढ़ोs zero. Need to handle bouncing पूर्णांकerrupts.
	 */
	जबतक (1) अणु
		u32 cause;

		(व्योम) simple_mdio_पढ़ो(cphy,
				MV88E1XXX_INTERRUPT_STATUS_REGISTER,
				&cause);
		cause &= INTR_ENABLE_MASK;
		अगर (!cause)
			अवरोध;

		अगर (cause & MV88E1XXX_INTR_LINK_CHNG) अणु
			(व्योम) simple_mdio_पढ़ो(cphy,
				MV88E1XXX_SPECIFIC_STATUS_REGISTER, &status);

			अगर (status & MV88E1XXX_INTR_LINK_CHNG)
				cphy->state |= PHY_LINK_UP;
			अन्यथा अणु
				cphy->state &= ~PHY_LINK_UP;
				अगर (cphy->state & PHY_AUTONEG_EN)
					cphy->state &= ~PHY_AUTONEG_RDY;
				cphy_cause |= cphy_cause_link_change;
			पूर्ण
		पूर्ण

		अगर (cause & MV88E1XXX_INTR_AUTONEG_DONE)
			cphy->state |= PHY_AUTONEG_RDY;

		अगर ((cphy->state & (PHY_LINK_UP | PHY_AUTONEG_RDY)) ==
			(PHY_LINK_UP | PHY_AUTONEG_RDY))
				cphy_cause |= cphy_cause_link_change;
	पूर्ण
	वापस cphy_cause;
पूर्ण

अटल व्योम mv88e1xxx_destroy(काष्ठा cphy *cphy)
अणु
	kमुक्त(cphy);
पूर्ण

अटल स्थिर काष्ठा cphy_ops mv88e1xxx_ops = अणु
	.destroy              = mv88e1xxx_destroy,
	.reset                = mv88e1xxx_reset,
	.पूर्णांकerrupt_enable     = mv88e1xxx_पूर्णांकerrupt_enable,
	.पूर्णांकerrupt_disable    = mv88e1xxx_पूर्णांकerrupt_disable,
	.पूर्णांकerrupt_clear      = mv88e1xxx_पूर्णांकerrupt_clear,
	.पूर्णांकerrupt_handler    = mv88e1xxx_पूर्णांकerrupt_handler,
	.स्वतःneg_enable       = mv88e1xxx_स्वतःneg_enable,
	.स्वतःneg_disable      = mv88e1xxx_स्वतःneg_disable,
	.स्वतःneg_restart      = mv88e1xxx_स्वतःneg_restart,
	.advertise            = mv88e1xxx_advertise,
	.set_loopback         = mv88e1xxx_set_loopback,
	.set_speed_duplex     = mv88e1xxx_set_speed_duplex,
	.get_link_status      = mv88e1xxx_get_link_status,
पूर्ण;

अटल काष्ठा cphy *mv88e1xxx_phy_create(काष्ठा net_device *dev, पूर्णांक phy_addr,
					 स्थिर काष्ठा mdio_ops *mdio_ops)
अणु
	काष्ठा adapter *adapter = netdev_priv(dev);
	काष्ठा cphy *cphy = kzalloc(माप(*cphy), GFP_KERNEL);

	अगर (!cphy)
		वापस शून्य;

	cphy_init(cphy, dev, phy_addr, &mv88e1xxx_ops, mdio_ops);

	/* Configure particular PHY's to run in a dअगरferent mode. */
	अगर ((board_info(adapter)->caps & SUPPORTED_TP) &&
	    board_info(adapter)->chip_phy == CHBT_PHY_88E1111) अणु
		/*
		 * Configure the PHY transmitter as class A to reduce EMI.
		 */
		(व्योम) simple_mdio_ग_लिखो(cphy,
				MV88E1XXX_EXTENDED_ADDR_REGISTER, 0xB);
		(व्योम) simple_mdio_ग_लिखो(cphy,
				MV88E1XXX_EXTENDED_REGISTER, 0x8004);
	पूर्ण
	(व्योम) mv88e1xxx_करोwnshअगरt_set(cphy, 1);   /* Enable करोwnshअगरt */

	/* LED */
	अगर (is_T2(adapter)) अणु
		(व्योम) simple_mdio_ग_लिखो(cphy,
				MV88E1XXX_LED_CONTROL_REGISTER, 0x1);
	पूर्ण

	वापस cphy;
पूर्ण

अटल पूर्णांक mv88e1xxx_phy_reset(adapter_t* adapter)
अणु
	वापस 0;
पूर्ण

स्थिर काष्ठा gphy t1_mv88e1xxx_ops = अणु
	.create = mv88e1xxx_phy_create,
	.reset =  mv88e1xxx_phy_reset
पूर्ण;
