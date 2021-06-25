<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause)
/* Copyright 2020 NXP
 * Lynx PCS MDIO helpers
 */

#समावेश <linux/mdपन.स>
#समावेश <linux/phylink.h>
#समावेश <linux/pcs-lynx.h>

#घोषणा SGMII_CLOCK_PERIOD_NS		8 /* PCS is घड़ीed at 125 MHz */
#घोषणा LINK_TIMER_VAL(ns)		((u32)((ns) / SGMII_CLOCK_PERIOD_NS))

#घोषणा SGMII_AN_LINK_TIMER_NS		1600000 /* defined by SGMII spec */
#घोषणा IEEE8023_LINK_TIMER_NS		10000000

#घोषणा LINK_TIMER_LO			0x12
#घोषणा LINK_TIMER_HI			0x13
#घोषणा IF_MODE				0x14
#घोषणा IF_MODE_SGMII_EN		BIT(0)
#घोषणा IF_MODE_USE_SGMII_AN		BIT(1)
#घोषणा IF_MODE_SPEED(x)		(((x) << 2) & GENMASK(3, 2))
#घोषणा IF_MODE_SPEED_MSK		GENMASK(3, 2)
#घोषणा IF_MODE_HALF_DUPLEX		BIT(4)

क्रमागत sgmii_speed अणु
	SGMII_SPEED_10		= 0,
	SGMII_SPEED_100		= 1,
	SGMII_SPEED_1000	= 2,
	SGMII_SPEED_2500	= 2,
पूर्ण;

#घोषणा phylink_pcs_to_lynx(pl_pcs) container_of((pl_pcs), काष्ठा lynx_pcs, pcs)

अटल व्योम lynx_pcs_get_state_usxgmii(काष्ठा mdio_device *pcs,
				       काष्ठा phylink_link_state *state)
अणु
	काष्ठा mii_bus *bus = pcs->bus;
	पूर्णांक addr = pcs->addr;
	पूर्णांक status, lpa;

	status = mdiobus_c45_पढ़ो(bus, addr, MDIO_MMD_VEND2, MII_BMSR);
	अगर (status < 0)
		वापस;

	state->link = !!(status & MDIO_STAT1_LSTATUS);
	state->an_complete = !!(status & MDIO_AN_STAT1_COMPLETE);
	अगर (!state->link || !state->an_complete)
		वापस;

	lpa = mdiobus_c45_पढ़ो(bus, addr, MDIO_MMD_VEND2, MII_LPA);
	अगर (lpa < 0)
		वापस;

	phylink_decode_usxgmii_word(state, lpa);
पूर्ण

अटल व्योम lynx_pcs_get_state_2500basex(काष्ठा mdio_device *pcs,
					 काष्ठा phylink_link_state *state)
अणु
	काष्ठा mii_bus *bus = pcs->bus;
	पूर्णांक addr = pcs->addr;
	पूर्णांक bmsr, lpa;

	bmsr = mdiobus_पढ़ो(bus, addr, MII_BMSR);
	lpa = mdiobus_पढ़ो(bus, addr, MII_LPA);
	अगर (bmsr < 0 || lpa < 0) अणु
		state->link = false;
		वापस;
	पूर्ण

	state->link = !!(bmsr & BMSR_LSTATUS);
	state->an_complete = !!(bmsr & BMSR_ANEGCOMPLETE);
	अगर (!state->link)
		वापस;

	state->speed = SPEED_2500;
	state->छोड़ो |= MLO_PAUSE_TX | MLO_PAUSE_RX;
	state->duplex = DUPLEX_FULL;
पूर्ण

अटल व्योम lynx_pcs_get_state(काष्ठा phylink_pcs *pcs,
			       काष्ठा phylink_link_state *state)
अणु
	काष्ठा lynx_pcs *lynx = phylink_pcs_to_lynx(pcs);

	चयन (state->पूर्णांकerface) अणु
	हाल PHY_INTERFACE_MODE_1000BASEX:
	हाल PHY_INTERFACE_MODE_SGMII:
	हाल PHY_INTERFACE_MODE_QSGMII:
		phylink_mii_c22_pcs_get_state(lynx->mdio, state);
		अवरोध;
	हाल PHY_INTERFACE_MODE_2500BASEX:
		lynx_pcs_get_state_2500basex(lynx->mdio, state);
		अवरोध;
	हाल PHY_INTERFACE_MODE_USXGMII:
		lynx_pcs_get_state_usxgmii(lynx->mdio, state);
		अवरोध;
	हाल PHY_INTERFACE_MODE_10GBASER:
		phylink_mii_c45_pcs_get_state(lynx->mdio, state);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	dev_dbg(&lynx->mdio->dev,
		"mode=%s/%s/%s link=%u an_enabled=%u an_complete=%u\n",
		phy_modes(state->पूर्णांकerface),
		phy_speed_to_str(state->speed),
		phy_duplex_to_str(state->duplex),
		state->link, state->an_enabled, state->an_complete);
पूर्ण

अटल पूर्णांक lynx_pcs_config_1000basex(काष्ठा mdio_device *pcs,
				     अचिन्हित पूर्णांक mode,
				     स्थिर अचिन्हित दीर्घ *advertising)
अणु
	काष्ठा mii_bus *bus = pcs->bus;
	पूर्णांक addr = pcs->addr;
	u32 link_समयr;
	पूर्णांक err;

	link_समयr = LINK_TIMER_VAL(IEEE8023_LINK_TIMER_NS);
	mdiobus_ग_लिखो(bus, addr, LINK_TIMER_LO, link_समयr & 0xffff);
	mdiobus_ग_लिखो(bus, addr, LINK_TIMER_HI, link_समयr >> 16);

	err = mdiobus_modअगरy(bus, addr, IF_MODE,
			     IF_MODE_SGMII_EN | IF_MODE_USE_SGMII_AN,
			     0);
	अगर (err)
		वापस err;

	वापस phylink_mii_c22_pcs_config(pcs, mode,
					  PHY_INTERFACE_MODE_1000BASEX,
					  advertising);
पूर्ण

अटल पूर्णांक lynx_pcs_config_sgmii(काष्ठा mdio_device *pcs, अचिन्हित पूर्णांक mode,
				 स्थिर अचिन्हित दीर्घ *advertising)
अणु
	काष्ठा mii_bus *bus = pcs->bus;
	पूर्णांक addr = pcs->addr;
	u16 अगर_mode;
	पूर्णांक err;

	अगर_mode = IF_MODE_SGMII_EN;
	अगर (mode == MLO_AN_INBAND) अणु
		u32 link_समयr;

		अगर_mode |= IF_MODE_USE_SGMII_AN;

		/* Adjust link समयr क्रम SGMII */
		link_समयr = LINK_TIMER_VAL(SGMII_AN_LINK_TIMER_NS);
		mdiobus_ग_लिखो(bus, addr, LINK_TIMER_LO, link_समयr & 0xffff);
		mdiobus_ग_लिखो(bus, addr, LINK_TIMER_HI, link_समयr >> 16);
	पूर्ण
	err = mdiobus_modअगरy(bus, addr, IF_MODE,
			     IF_MODE_SGMII_EN | IF_MODE_USE_SGMII_AN,
			     अगर_mode);
	अगर (err)
		वापस err;

	वापस phylink_mii_c22_pcs_config(pcs, mode, PHY_INTERFACE_MODE_SGMII,
					 advertising);
पूर्ण

अटल पूर्णांक lynx_pcs_config_usxgmii(काष्ठा mdio_device *pcs, अचिन्हित पूर्णांक mode,
				   स्थिर अचिन्हित दीर्घ *advertising)
अणु
	काष्ठा mii_bus *bus = pcs->bus;
	पूर्णांक addr = pcs->addr;

	अगर (!phylink_स्वतःneg_inband(mode)) अणु
		dev_err(&pcs->dev, "USXGMII only supports in-band AN for now\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	/* Configure device ability क्रम the USXGMII Replicator */
	वापस mdiobus_c45_ग_लिखो(bus, addr, MDIO_MMD_VEND2, MII_ADVERTISE,
				 MDIO_USXGMII_10G | MDIO_USXGMII_LINK |
				 MDIO_USXGMII_FULL_DUPLEX |
				 ADVERTISE_SGMII | ADVERTISE_LPACK);
पूर्ण

अटल पूर्णांक lynx_pcs_config(काष्ठा phylink_pcs *pcs, अचिन्हित पूर्णांक mode,
			   phy_पूर्णांकerface_t अगरmode,
			   स्थिर अचिन्हित दीर्घ *advertising,
			   bool permit)
अणु
	काष्ठा lynx_pcs *lynx = phylink_pcs_to_lynx(pcs);

	चयन (अगरmode) अणु
	हाल PHY_INTERFACE_MODE_1000BASEX:
		वापस lynx_pcs_config_1000basex(lynx->mdio, mode, advertising);
	हाल PHY_INTERFACE_MODE_SGMII:
	हाल PHY_INTERFACE_MODE_QSGMII:
		वापस lynx_pcs_config_sgmii(lynx->mdio, mode, advertising);
	हाल PHY_INTERFACE_MODE_2500BASEX:
		अगर (phylink_स्वतःneg_inband(mode)) अणु
			dev_err(&lynx->mdio->dev,
				"AN not supported on 3.125GHz SerDes lane\n");
			वापस -EOPNOTSUPP;
		पूर्ण
		अवरोध;
	हाल PHY_INTERFACE_MODE_USXGMII:
		वापस lynx_pcs_config_usxgmii(lynx->mdio, mode, advertising);
	हाल PHY_INTERFACE_MODE_10GBASER:
		/* Nothing to करो here क्रम 10GBASER */
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम lynx_pcs_an_restart(काष्ठा phylink_pcs *pcs)
अणु
	काष्ठा lynx_pcs *lynx = phylink_pcs_to_lynx(pcs);

	phylink_mii_c22_pcs_an_restart(lynx->mdio);
पूर्ण

अटल व्योम lynx_pcs_link_up_sgmii(काष्ठा mdio_device *pcs, अचिन्हित पूर्णांक mode,
				   पूर्णांक speed, पूर्णांक duplex)
अणु
	काष्ठा mii_bus *bus = pcs->bus;
	u16 अगर_mode = 0, sgmii_speed;
	पूर्णांक addr = pcs->addr;

	/* The PCS needs to be configured manually only
	 * when not operating on in-band mode
	 */
	अगर (mode == MLO_AN_INBAND)
		वापस;

	अगर (duplex == DUPLEX_HALF)
		अगर_mode |= IF_MODE_HALF_DUPLEX;

	चयन (speed) अणु
	हाल SPEED_1000:
		sgmii_speed = SGMII_SPEED_1000;
		अवरोध;
	हाल SPEED_100:
		sgmii_speed = SGMII_SPEED_100;
		अवरोध;
	हाल SPEED_10:
		sgmii_speed = SGMII_SPEED_10;
		अवरोध;
	हाल SPEED_UNKNOWN:
		/* Silently करोn't करो anything */
		वापस;
	शेष:
		dev_err(&pcs->dev, "Invalid PCS speed %d\n", speed);
		वापस;
	पूर्ण
	अगर_mode |= IF_MODE_SPEED(sgmii_speed);

	mdiobus_modअगरy(bus, addr, IF_MODE,
		       IF_MODE_HALF_DUPLEX | IF_MODE_SPEED_MSK,
		       अगर_mode);
पूर्ण

/* 2500Base-X is SerDes protocol 7 on Felix and 6 on ENETC. It is a SerDes lane
 * घड़ीed at 3.125 GHz which encodes symbols with 8b/10b and करोes not have
 * स्वतः-negotiation of any link parameters. Electrically it is compatible with
 * a single lane of XAUI.
 * The hardware reference manual wants to call this mode SGMII, but it isn't
 * really, since the fundamental features of SGMII:
 * - Downgrading the link speed by duplicating symbols
 * - Auto-negotiation
 * are not there.
 * The speed is configured at 1000 in the IF_MODE because the घड़ी frequency
 * is actually given by a PLL configured in the Reset Configuration Word (RCW).
 * Since there is no dअगरference between fixed speed SGMII w/o AN and 802.3z w/o
 * AN, we call this PHY पूर्णांकerface type 2500Base-X. In हाल a PHY negotiates a
 * lower link speed on line side, the प्रणाली-side पूर्णांकerface reमुख्यs fixed at
 * 2500 Mbps and we करो rate adaptation through छोड़ो frames.
 */
अटल व्योम lynx_pcs_link_up_2500basex(काष्ठा mdio_device *pcs,
				       अचिन्हित पूर्णांक mode,
				       पूर्णांक speed, पूर्णांक duplex)
अणु
	काष्ठा mii_bus *bus = pcs->bus;
	पूर्णांक addr = pcs->addr;
	u16 अगर_mode = 0;

	अगर (mode == MLO_AN_INBAND) अणु
		dev_err(&pcs->dev, "AN not supported for 2500BaseX\n");
		वापस;
	पूर्ण

	अगर (duplex == DUPLEX_HALF)
		अगर_mode |= IF_MODE_HALF_DUPLEX;
	अगर_mode |= IF_MODE_SPEED(SGMII_SPEED_2500);

	mdiobus_modअगरy(bus, addr, IF_MODE,
		       IF_MODE_HALF_DUPLEX | IF_MODE_SPEED_MSK,
		       अगर_mode);
पूर्ण

अटल व्योम lynx_pcs_link_up(काष्ठा phylink_pcs *pcs, अचिन्हित पूर्णांक mode,
			     phy_पूर्णांकerface_t पूर्णांकerface,
			     पूर्णांक speed, पूर्णांक duplex)
अणु
	काष्ठा lynx_pcs *lynx = phylink_pcs_to_lynx(pcs);

	चयन (पूर्णांकerface) अणु
	हाल PHY_INTERFACE_MODE_SGMII:
	हाल PHY_INTERFACE_MODE_QSGMII:
		lynx_pcs_link_up_sgmii(lynx->mdio, mode, speed, duplex);
		अवरोध;
	हाल PHY_INTERFACE_MODE_2500BASEX:
		lynx_pcs_link_up_2500basex(lynx->mdio, mode, speed, duplex);
		अवरोध;
	हाल PHY_INTERFACE_MODE_USXGMII:
		/* At the moment, only in-band AN is supported क्रम USXGMII
		 * so nothing to करो in link_up
		 */
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा phylink_pcs_ops lynx_pcs_phylink_ops = अणु
	.pcs_get_state = lynx_pcs_get_state,
	.pcs_config = lynx_pcs_config,
	.pcs_an_restart = lynx_pcs_an_restart,
	.pcs_link_up = lynx_pcs_link_up,
पूर्ण;

काष्ठा lynx_pcs *lynx_pcs_create(काष्ठा mdio_device *mdio)
अणु
	काष्ठा lynx_pcs *lynx_pcs;

	lynx_pcs = kzalloc(माप(*lynx_pcs), GFP_KERNEL);
	अगर (!lynx_pcs)
		वापस शून्य;

	lynx_pcs->mdio = mdio;
	lynx_pcs->pcs.ops = &lynx_pcs_phylink_ops;
	lynx_pcs->pcs.poll = true;

	वापस lynx_pcs;
पूर्ण
EXPORT_SYMBOL(lynx_pcs_create);

व्योम lynx_pcs_destroy(काष्ठा lynx_pcs *pcs)
अणु
	kमुक्त(pcs);
पूर्ण
EXPORT_SYMBOL(lynx_pcs_destroy);

MODULE_LICENSE("Dual BSD/GPL");
