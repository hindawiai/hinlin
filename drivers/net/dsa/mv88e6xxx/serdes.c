<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Marvell 88E6xxx SERDES manipulation, via SMI bus
 *
 * Copyright (c) 2008 Marvell Semiconductor
 *
 * Copyright (c) 2017 Andrew Lunn <andrew@lunn.ch>
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/mii.h>

#समावेश "chip.h"
#समावेश "global2.h"
#समावेश "phy.h"
#समावेश "port.h"
#समावेश "serdes.h"

अटल पूर्णांक mv88e6352_serdes_पढ़ो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक reg,
				 u16 *val)
अणु
	वापस mv88e6xxx_phy_page_पढ़ो(chip, MV88E6352_ADDR_SERDES,
				       MV88E6352_SERDES_PAGE_FIBER,
				       reg, val);
पूर्ण

अटल पूर्णांक mv88e6352_serdes_ग_लिखो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक reg,
				  u16 val)
अणु
	वापस mv88e6xxx_phy_page_ग_लिखो(chip, MV88E6352_ADDR_SERDES,
					MV88E6352_SERDES_PAGE_FIBER,
					reg, val);
पूर्ण

अटल पूर्णांक mv88e6390_serdes_पढ़ो(काष्ठा mv88e6xxx_chip *chip,
				 पूर्णांक lane, पूर्णांक device, पूर्णांक reg, u16 *val)
अणु
	पूर्णांक reg_c45 = MII_ADDR_C45 | device << 16 | reg;

	वापस mv88e6xxx_phy_पढ़ो(chip, lane, reg_c45, val);
पूर्ण

अटल पूर्णांक mv88e6390_serdes_ग_लिखो(काष्ठा mv88e6xxx_chip *chip,
				  पूर्णांक lane, पूर्णांक device, पूर्णांक reg, u16 val)
अणु
	पूर्णांक reg_c45 = MII_ADDR_C45 | device << 16 | reg;

	वापस mv88e6xxx_phy_ग_लिखो(chip, lane, reg_c45, val);
पूर्ण

अटल पूर्णांक mv88e6xxx_serdes_pcs_get_state(काष्ठा mv88e6xxx_chip *chip,
					  u16 status, u16 lpa,
					  काष्ठा phylink_link_state *state)
अणु
	अगर (status & MV88E6390_SGMII_PHY_STATUS_SPD_DPL_VALID) अणु
		state->link = !!(status & MV88E6390_SGMII_PHY_STATUS_LINK);
		state->duplex = status &
				MV88E6390_SGMII_PHY_STATUS_DUPLEX_FULL ?
			                         DUPLEX_FULL : DUPLEX_HALF;

		अगर (status & MV88E6390_SGMII_PHY_STATUS_TX_PAUSE)
			state->छोड़ो |= MLO_PAUSE_TX;
		अगर (status & MV88E6390_SGMII_PHY_STATUS_RX_PAUSE)
			state->छोड़ो |= MLO_PAUSE_RX;

		चयन (status & MV88E6390_SGMII_PHY_STATUS_SPEED_MASK) अणु
		हाल MV88E6390_SGMII_PHY_STATUS_SPEED_1000:
			अगर (state->पूर्णांकerface == PHY_INTERFACE_MODE_2500BASEX)
				state->speed = SPEED_2500;
			अन्यथा
				state->speed = SPEED_1000;
			अवरोध;
		हाल MV88E6390_SGMII_PHY_STATUS_SPEED_100:
			state->speed = SPEED_100;
			अवरोध;
		हाल MV88E6390_SGMII_PHY_STATUS_SPEED_10:
			state->speed = SPEED_10;
			अवरोध;
		शेष:
			dev_err(chip->dev, "invalid PHY speed\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		state->link = false;
	पूर्ण

	अगर (state->पूर्णांकerface == PHY_INTERFACE_MODE_2500BASEX)
		mii_lpa_mod_linkmode_x(state->lp_advertising, lpa,
				       ETHTOOL_LINK_MODE_2500baseX_Full_BIT);
	अन्यथा अगर (state->पूर्णांकerface == PHY_INTERFACE_MODE_1000BASEX)
		mii_lpa_mod_linkmode_x(state->lp_advertising, lpa,
				       ETHTOOL_LINK_MODE_1000baseX_Full_BIT);

	वापस 0;
पूर्ण

पूर्णांक mv88e6352_serdes_घातer(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, पूर्णांक lane,
			   bool up)
अणु
	u16 val, new_val;
	पूर्णांक err;

	err = mv88e6352_serdes_पढ़ो(chip, MII_BMCR, &val);
	अगर (err)
		वापस err;

	अगर (up)
		new_val = val & ~BMCR_PDOWN;
	अन्यथा
		new_val = val | BMCR_PDOWN;

	अगर (val != new_val)
		err = mv88e6352_serdes_ग_लिखो(chip, MII_BMCR, new_val);

	वापस err;
पूर्ण

पूर्णांक mv88e6352_serdes_pcs_config(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				पूर्णांक lane, अचिन्हित पूर्णांक mode,
				phy_पूर्णांकerface_t पूर्णांकerface,
				स्थिर अचिन्हित दीर्घ *advertise)
अणु
	u16 adv, bmcr, val;
	bool changed;
	पूर्णांक err;

	चयन (पूर्णांकerface) अणु
	हाल PHY_INTERFACE_MODE_SGMII:
		adv = 0x0001;
		अवरोध;

	हाल PHY_INTERFACE_MODE_1000BASEX:
		adv = linkmode_adv_to_mii_adv_x(advertise,
					ETHTOOL_LINK_MODE_1000baseX_Full_BIT);
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	err = mv88e6352_serdes_पढ़ो(chip, MII_ADVERTISE, &val);
	अगर (err)
		वापस err;

	changed = val != adv;
	अगर (changed) अणु
		err = mv88e6352_serdes_ग_लिखो(chip, MII_ADVERTISE, adv);
		अगर (err)
			वापस err;
	पूर्ण

	err = mv88e6352_serdes_पढ़ो(chip, MII_BMCR, &val);
	अगर (err)
		वापस err;

	अगर (phylink_स्वतःneg_inband(mode))
		bmcr = val | BMCR_ANENABLE;
	अन्यथा
		bmcr = val & ~BMCR_ANENABLE;

	अगर (bmcr == val)
		वापस changed;

	वापस mv88e6352_serdes_ग_लिखो(chip, MII_BMCR, bmcr);
पूर्ण

पूर्णांक mv88e6352_serdes_pcs_get_state(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				   पूर्णांक lane, काष्ठा phylink_link_state *state)
अणु
	u16 lpa, status;
	पूर्णांक err;

	err = mv88e6352_serdes_पढ़ो(chip, 0x11, &status);
	अगर (err) अणु
		dev_err(chip->dev, "can't read Serdes PHY status: %d\n", err);
		वापस err;
	पूर्ण

	err = mv88e6352_serdes_पढ़ो(chip, MII_LPA, &lpa);
	अगर (err) अणु
		dev_err(chip->dev, "can't read Serdes PHY LPA: %d\n", err);
		वापस err;
	पूर्ण

	वापस mv88e6xxx_serdes_pcs_get_state(chip, status, lpa, state);
पूर्ण

पूर्णांक mv88e6352_serdes_pcs_an_restart(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				    पूर्णांक lane)
अणु
	u16 bmcr;
	पूर्णांक err;

	err = mv88e6352_serdes_पढ़ो(chip, MII_BMCR, &bmcr);
	अगर (err)
		वापस err;

	वापस mv88e6352_serdes_ग_लिखो(chip, MII_BMCR, bmcr | BMCR_ANRESTART);
पूर्ण

पूर्णांक mv88e6352_serdes_pcs_link_up(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				 पूर्णांक lane, पूर्णांक speed, पूर्णांक duplex)
अणु
	u16 val, bmcr;
	पूर्णांक err;

	err = mv88e6352_serdes_पढ़ो(chip, MII_BMCR, &val);
	अगर (err)
		वापस err;

	bmcr = val & ~(BMCR_SPEED100 | BMCR_FULLDPLX | BMCR_SPEED1000);
	चयन (speed) अणु
	हाल SPEED_1000:
		bmcr |= BMCR_SPEED1000;
		अवरोध;
	हाल SPEED_100:
		bmcr |= BMCR_SPEED100;
		अवरोध;
	हाल SPEED_10:
		अवरोध;
	पूर्ण

	अगर (duplex == DUPLEX_FULL)
		bmcr |= BMCR_FULLDPLX;

	अगर (bmcr == val)
		वापस 0;

	वापस mv88e6352_serdes_ग_लिखो(chip, MII_BMCR, bmcr);
पूर्ण

पूर्णांक mv88e6352_serdes_get_lane(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port)
अणु
	u8 cmode = chip->ports[port].cmode;
	पूर्णांक lane = -ENODEV;

	अगर ((cmode == MV88E6XXX_PORT_STS_CMODE_100BASEX) ||
	    (cmode == MV88E6XXX_PORT_STS_CMODE_1000BASEX) ||
	    (cmode == MV88E6XXX_PORT_STS_CMODE_SGMII))
		lane = 0xff; /* Unused */

	वापस lane;
पूर्ण

अटल bool mv88e6352_port_has_serdes(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port)
अणु
	अगर (mv88e6xxx_serdes_get_lane(chip, port) >= 0)
		वापस true;

	वापस false;
पूर्ण

काष्ठा mv88e6352_serdes_hw_stat अणु
	अक्षर string[ETH_GSTRING_LEN];
	पूर्णांक माप_stat;
	पूर्णांक reg;
पूर्ण;

अटल काष्ठा mv88e6352_serdes_hw_stat mv88e6352_serdes_hw_stats[] = अणु
	अणु "serdes_fibre_rx_error", 16, 21 पूर्ण,
	अणु "serdes_PRBS_error", 32, 24 पूर्ण,
पूर्ण;

पूर्णांक mv88e6352_serdes_get_sset_count(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port)
अणु
	अगर (mv88e6352_port_has_serdes(chip, port))
		वापस ARRAY_SIZE(mv88e6352_serdes_hw_stats);

	वापस 0;
पूर्ण

पूर्णांक mv88e6352_serdes_get_strings(काष्ठा mv88e6xxx_chip *chip,
				 पूर्णांक port, uपूर्णांक8_t *data)
अणु
	काष्ठा mv88e6352_serdes_hw_stat *stat;
	पूर्णांक i;

	अगर (!mv88e6352_port_has_serdes(chip, port))
		वापस 0;

	क्रम (i = 0; i < ARRAY_SIZE(mv88e6352_serdes_hw_stats); i++) अणु
		stat = &mv88e6352_serdes_hw_stats[i];
		स_नकल(data + i * ETH_GSTRING_LEN, stat->string,
		       ETH_GSTRING_LEN);
	पूर्ण
	वापस ARRAY_SIZE(mv88e6352_serdes_hw_stats);
पूर्ण

अटल uपूर्णांक64_t mv88e6352_serdes_get_stat(काष्ठा mv88e6xxx_chip *chip,
					  काष्ठा mv88e6352_serdes_hw_stat *stat)
अणु
	u64 val = 0;
	u16 reg;
	पूर्णांक err;

	err = mv88e6352_serdes_पढ़ो(chip, stat->reg, &reg);
	अगर (err) अणु
		dev_err(chip->dev, "failed to read statistic\n");
		वापस 0;
	पूर्ण

	val = reg;

	अगर (stat->माप_stat == 32) अणु
		err = mv88e6352_serdes_पढ़ो(chip, stat->reg + 1, &reg);
		अगर (err) अणु
			dev_err(chip->dev, "failed to read statistic\n");
			वापस 0;
		पूर्ण
		val = val << 16 | reg;
	पूर्ण

	वापस val;
पूर्ण

पूर्णांक mv88e6352_serdes_get_stats(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
			       uपूर्णांक64_t *data)
अणु
	काष्ठा mv88e6xxx_port *mv88e6xxx_port = &chip->ports[port];
	काष्ठा mv88e6352_serdes_hw_stat *stat;
	u64 value;
	पूर्णांक i;

	अगर (!mv88e6352_port_has_serdes(chip, port))
		वापस 0;

	BUILD_BUG_ON(ARRAY_SIZE(mv88e6352_serdes_hw_stats) >
		     ARRAY_SIZE(mv88e6xxx_port->serdes_stats));

	क्रम (i = 0; i < ARRAY_SIZE(mv88e6352_serdes_hw_stats); i++) अणु
		stat = &mv88e6352_serdes_hw_stats[i];
		value = mv88e6352_serdes_get_stat(chip, stat);
		mv88e6xxx_port->serdes_stats[i] += value;
		data[i] = mv88e6xxx_port->serdes_stats[i];
	पूर्ण

	वापस ARRAY_SIZE(mv88e6352_serdes_hw_stats);
पूर्ण

अटल व्योम mv88e6352_serdes_irq_link(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port)
अणु
	u16 bmsr;
	पूर्णांक err;

	/* If the link has dropped, we want to know about it. */
	err = mv88e6352_serdes_पढ़ो(chip, MII_BMSR, &bmsr);
	अगर (err) अणु
		dev_err(chip->dev, "can't read Serdes BMSR: %d\n", err);
		वापस;
	पूर्ण

	dsa_port_phylink_mac_change(chip->ds, port, !!(bmsr & BMSR_LSTATUS));
पूर्ण

irqवापस_t mv88e6352_serdes_irq_status(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
					पूर्णांक lane)
अणु
	irqवापस_t ret = IRQ_NONE;
	u16 status;
	पूर्णांक err;

	err = mv88e6352_serdes_पढ़ो(chip, MV88E6352_SERDES_INT_STATUS, &status);
	अगर (err)
		वापस ret;

	अगर (status & MV88E6352_SERDES_INT_LINK_CHANGE) अणु
		ret = IRQ_HANDLED;
		mv88e6352_serdes_irq_link(chip, port);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक mv88e6352_serdes_irq_enable(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, पूर्णांक lane,
				bool enable)
अणु
	u16 val = 0;

	अगर (enable)
		val |= MV88E6352_SERDES_INT_LINK_CHANGE;

	वापस mv88e6352_serdes_ग_लिखो(chip, MV88E6352_SERDES_INT_ENABLE, val);
पूर्ण

अचिन्हित पूर्णांक mv88e6352_serdes_irq_mapping(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port)
अणु
	वापस irq_find_mapping(chip->g2_irq.करोमुख्य, MV88E6352_SERDES_IRQ);
पूर्ण

पूर्णांक mv88e6352_serdes_get_regs_len(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port)
अणु
	अगर (!mv88e6352_port_has_serdes(chip, port))
		वापस 0;

	वापस 32 * माप(u16);
पूर्ण

व्योम mv88e6352_serdes_get_regs(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, व्योम *_p)
अणु
	u16 *p = _p;
	u16 reg;
	पूर्णांक err;
	पूर्णांक i;

	अगर (!mv88e6352_port_has_serdes(chip, port))
		वापस;

	क्रम (i = 0 ; i < 32; i++) अणु
		err = mv88e6352_serdes_पढ़ो(chip, i, &reg);
		अगर (!err)
			p[i] = reg;
	पूर्ण
पूर्ण

पूर्णांक mv88e6341_serdes_get_lane(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port)
अणु
	u8 cmode = chip->ports[port].cmode;
	पूर्णांक lane = -ENODEV;

	चयन (port) अणु
	हाल 5:
		अगर (cmode == MV88E6XXX_PORT_STS_CMODE_1000BASEX ||
		    cmode == MV88E6XXX_PORT_STS_CMODE_SGMII ||
		    cmode == MV88E6XXX_PORT_STS_CMODE_2500BASEX)
			lane = MV88E6341_PORT5_LANE;
		अवरोध;
	पूर्ण

	वापस lane;
पूर्ण

पूर्णांक mv88e6185_serdes_घातer(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, पूर्णांक lane,
			   bool up)
अणु
	/* The serdes घातer can't be controlled on this चयन chip but we need
	 * to supply this function to aव्योम वापसing -EOPNOTSUPP in
	 * mv88e6xxx_serdes_घातer_up/mv88e6xxx_serdes_घातer_करोwn
	 */
	वापस 0;
पूर्ण

पूर्णांक mv88e6185_serdes_get_lane(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port)
अणु
	/* There are no configurable serdes lanes on this चयन chip but we
	 * need to वापस a non-negative lane number so that callers of
	 * mv88e6xxx_serdes_get_lane() know this is a serdes port.
	 */
	चयन (chip->ports[port].cmode) अणु
	हाल MV88E6185_PORT_STS_CMODE_SERDES:
	हाल MV88E6185_PORT_STS_CMODE_1000BASE_X:
		वापस 0;
	शेष:
		वापस -ENODEV;
	पूर्ण
पूर्ण

पूर्णांक mv88e6185_serdes_pcs_get_state(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				   पूर्णांक lane, काष्ठा phylink_link_state *state)
अणु
	पूर्णांक err;
	u16 status;

	err = mv88e6xxx_port_पढ़ो(chip, port, MV88E6XXX_PORT_STS, &status);
	अगर (err)
		वापस err;

	state->link = !!(status & MV88E6XXX_PORT_STS_LINK);

	अगर (state->link) अणु
		state->duplex = status & MV88E6XXX_PORT_STS_DUPLEX ? DUPLEX_FULL : DUPLEX_HALF;

		चयन (status &  MV88E6XXX_PORT_STS_SPEED_MASK) अणु
		हाल MV88E6XXX_PORT_STS_SPEED_1000:
			state->speed = SPEED_1000;
			अवरोध;
		हाल MV88E6XXX_PORT_STS_SPEED_100:
			state->speed = SPEED_100;
			अवरोध;
		हाल MV88E6XXX_PORT_STS_SPEED_10:
			state->speed = SPEED_10;
			अवरोध;
		शेष:
			dev_err(chip->dev, "invalid PHY speed\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		state->duplex = DUPLEX_UNKNOWN;
		state->speed = SPEED_UNKNOWN;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mv88e6097_serdes_irq_enable(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, पूर्णांक lane,
				bool enable)
अणु
	u8 cmode = chip->ports[port].cmode;

	/* The serdes पूर्णांकerrupts are enabled in the G2_INT_MASK रेजिस्टर. We
	 * need to वापस 0 to aव्योम वापसing -EOPNOTSUPP in
	 * mv88e6xxx_serdes_irq_enable/mv88e6xxx_serdes_irq_disable
	 */
	चयन (cmode) अणु
	हाल MV88E6185_PORT_STS_CMODE_SERDES:
	हाल MV88E6185_PORT_STS_CMODE_1000BASE_X:
		वापस 0;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल व्योम mv88e6097_serdes_irq_link(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port)
अणु
	u16 status;
	पूर्णांक err;

	err = mv88e6xxx_port_पढ़ो(chip, port, MV88E6XXX_PORT_STS, &status);
	अगर (err) अणु
		dev_err(chip->dev, "can't read port status: %d\n", err);
		वापस;
	पूर्ण

	dsa_port_phylink_mac_change(chip->ds, port, !!(status & MV88E6XXX_PORT_STS_LINK));
पूर्ण

irqवापस_t mv88e6097_serdes_irq_status(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
					पूर्णांक lane)
अणु
	u8 cmode = chip->ports[port].cmode;

	चयन (cmode) अणु
	हाल MV88E6185_PORT_STS_CMODE_SERDES:
	हाल MV88E6185_PORT_STS_CMODE_1000BASE_X:
		mv88e6097_serdes_irq_link(chip, port);
		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

पूर्णांक mv88e6390_serdes_get_lane(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port)
अणु
	u8 cmode = chip->ports[port].cmode;
	पूर्णांक lane = -ENODEV;

	चयन (port) अणु
	हाल 9:
		अगर (cmode == MV88E6XXX_PORT_STS_CMODE_1000BASEX ||
		    cmode == MV88E6XXX_PORT_STS_CMODE_SGMII ||
		    cmode == MV88E6XXX_PORT_STS_CMODE_2500BASEX)
			lane = MV88E6390_PORT9_LANE0;
		अवरोध;
	हाल 10:
		अगर (cmode == MV88E6XXX_PORT_STS_CMODE_1000BASEX ||
		    cmode == MV88E6XXX_PORT_STS_CMODE_SGMII ||
		    cmode == MV88E6XXX_PORT_STS_CMODE_2500BASEX)
			lane = MV88E6390_PORT10_LANE0;
		अवरोध;
	पूर्ण

	वापस lane;
पूर्ण

पूर्णांक mv88e6390x_serdes_get_lane(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port)
अणु
	u8 cmode_port = chip->ports[port].cmode;
	u8 cmode_port10 = chip->ports[10].cmode;
	u8 cmode_port9 = chip->ports[9].cmode;
	पूर्णांक lane = -ENODEV;

	चयन (port) अणु
	हाल 2:
		अगर (cmode_port9 == MV88E6XXX_PORT_STS_CMODE_1000BASEX ||
		    cmode_port9 == MV88E6XXX_PORT_STS_CMODE_SGMII ||
		    cmode_port9 == MV88E6XXX_PORT_STS_CMODE_2500BASEX)
			अगर (cmode_port == MV88E6XXX_PORT_STS_CMODE_1000BASEX)
				lane = MV88E6390_PORT9_LANE1;
		अवरोध;
	हाल 3:
		अगर (cmode_port9 == MV88E6XXX_PORT_STS_CMODE_1000BASEX ||
		    cmode_port9 == MV88E6XXX_PORT_STS_CMODE_SGMII ||
		    cmode_port9 == MV88E6XXX_PORT_STS_CMODE_2500BASEX ||
		    cmode_port9 == MV88E6XXX_PORT_STS_CMODE_RXAUI)
			अगर (cmode_port == MV88E6XXX_PORT_STS_CMODE_1000BASEX)
				lane = MV88E6390_PORT9_LANE2;
		अवरोध;
	हाल 4:
		अगर (cmode_port9 == MV88E6XXX_PORT_STS_CMODE_1000BASEX ||
		    cmode_port9 == MV88E6XXX_PORT_STS_CMODE_SGMII ||
		    cmode_port9 == MV88E6XXX_PORT_STS_CMODE_2500BASEX ||
		    cmode_port9 == MV88E6XXX_PORT_STS_CMODE_RXAUI)
			अगर (cmode_port == MV88E6XXX_PORT_STS_CMODE_1000BASEX)
				lane = MV88E6390_PORT9_LANE3;
		अवरोध;
	हाल 5:
		अगर (cmode_port10 == MV88E6XXX_PORT_STS_CMODE_1000BASEX ||
		    cmode_port10 == MV88E6XXX_PORT_STS_CMODE_SGMII ||
		    cmode_port10 == MV88E6XXX_PORT_STS_CMODE_2500BASEX)
			अगर (cmode_port == MV88E6XXX_PORT_STS_CMODE_1000BASEX)
				lane = MV88E6390_PORT10_LANE1;
		अवरोध;
	हाल 6:
		अगर (cmode_port10 == MV88E6XXX_PORT_STS_CMODE_1000BASEX ||
		    cmode_port10 == MV88E6XXX_PORT_STS_CMODE_SGMII ||
		    cmode_port10 == MV88E6XXX_PORT_STS_CMODE_2500BASEX ||
		    cmode_port10 == MV88E6XXX_PORT_STS_CMODE_RXAUI)
			अगर (cmode_port == MV88E6XXX_PORT_STS_CMODE_1000BASEX)
				lane = MV88E6390_PORT10_LANE2;
		अवरोध;
	हाल 7:
		अगर (cmode_port10 == MV88E6XXX_PORT_STS_CMODE_1000BASEX ||
		    cmode_port10 == MV88E6XXX_PORT_STS_CMODE_SGMII ||
		    cmode_port10 == MV88E6XXX_PORT_STS_CMODE_2500BASEX ||
		    cmode_port10 == MV88E6XXX_PORT_STS_CMODE_RXAUI)
			अगर (cmode_port == MV88E6XXX_PORT_STS_CMODE_1000BASEX)
				lane = MV88E6390_PORT10_LANE3;
		अवरोध;
	हाल 9:
		अगर (cmode_port9 == MV88E6XXX_PORT_STS_CMODE_1000BASEX ||
		    cmode_port9 == MV88E6XXX_PORT_STS_CMODE_SGMII ||
		    cmode_port9 == MV88E6XXX_PORT_STS_CMODE_2500BASEX ||
		    cmode_port9 == MV88E6XXX_PORT_STS_CMODE_XAUI ||
		    cmode_port9 == MV88E6XXX_PORT_STS_CMODE_RXAUI)
			lane = MV88E6390_PORT9_LANE0;
		अवरोध;
	हाल 10:
		अगर (cmode_port10 == MV88E6XXX_PORT_STS_CMODE_1000BASEX ||
		    cmode_port10 == MV88E6XXX_PORT_STS_CMODE_SGMII ||
		    cmode_port10 == MV88E6XXX_PORT_STS_CMODE_2500BASEX ||
		    cmode_port10 == MV88E6XXX_PORT_STS_CMODE_XAUI ||
		    cmode_port10 == MV88E6XXX_PORT_STS_CMODE_RXAUI)
			lane = MV88E6390_PORT10_LANE0;
		अवरोध;
	पूर्ण

	वापस lane;
पूर्ण

/* Only Ports 0, 9 and 10 have SERDES lanes. Return the SERDES lane address
 * a port is using अन्यथा Returns -ENODEV.
 */
पूर्णांक mv88e6393x_serdes_get_lane(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port)
अणु
	u8 cmode = chip->ports[port].cmode;
	पूर्णांक lane = -ENODEV;

	अगर (port != 0 && port != 9 && port != 10)
		वापस -EOPNOTSUPP;

	अगर (cmode == MV88E6XXX_PORT_STS_CMODE_1000BASEX ||
	    cmode == MV88E6XXX_PORT_STS_CMODE_SGMII ||
	    cmode == MV88E6XXX_PORT_STS_CMODE_2500BASEX ||
	    cmode == MV88E6393X_PORT_STS_CMODE_5GBASER ||
	    cmode == MV88E6393X_PORT_STS_CMODE_10GBASER)
		lane = port;

	वापस lane;
पूर्ण

/* Set घातer up/करोwn क्रम 10GBASE-R and 10GBASE-X4/X2 */
अटल पूर्णांक mv88e6390_serdes_घातer_10g(काष्ठा mv88e6xxx_chip *chip, पूर्णांक lane,
				      bool up)
अणु
	u16 val, new_val;
	पूर्णांक err;

	err = mv88e6390_serdes_पढ़ो(chip, lane, MDIO_MMD_PHYXS,
				    MV88E6390_10G_CTRL1, &val);

	अगर (err)
		वापस err;

	अगर (up)
		new_val = val & ~(MDIO_CTRL1_RESET |
				  MDIO_PCS_CTRL1_LOOPBACK |
				  MDIO_CTRL1_LPOWER);
	अन्यथा
		new_val = val | MDIO_CTRL1_LPOWER;

	अगर (val != new_val)
		err = mv88e6390_serdes_ग_लिखो(chip, lane, MDIO_MMD_PHYXS,
					     MV88E6390_10G_CTRL1, new_val);

	वापस err;
पूर्ण

/* Set घातer up/करोwn क्रम SGMII and 1000Base-X */
अटल पूर्णांक mv88e6390_serdes_घातer_sgmii(काष्ठा mv88e6xxx_chip *chip, पूर्णांक lane,
					bool up)
अणु
	u16 val, new_val;
	पूर्णांक err;

	err = mv88e6390_serdes_पढ़ो(chip, lane, MDIO_MMD_PHYXS,
				    MV88E6390_SGMII_BMCR, &val);
	अगर (err)
		वापस err;

	अगर (up)
		new_val = val & ~(BMCR_RESET | BMCR_LOOPBACK | BMCR_PDOWN);
	अन्यथा
		new_val = val | BMCR_PDOWN;

	अगर (val != new_val)
		err = mv88e6390_serdes_ग_लिखो(chip, lane, MDIO_MMD_PHYXS,
					     MV88E6390_SGMII_BMCR, new_val);

	वापस err;
पूर्ण

काष्ठा mv88e6390_serdes_hw_stat अणु
	अक्षर string[ETH_GSTRING_LEN];
	पूर्णांक reg;
पूर्ण;

अटल काष्ठा mv88e6390_serdes_hw_stat mv88e6390_serdes_hw_stats[] = अणु
	अणु "serdes_rx_pkts", 0xf021 पूर्ण,
	अणु "serdes_rx_bytes", 0xf024 पूर्ण,
	अणु "serdes_rx_pkts_error", 0xf027 पूर्ण,
पूर्ण;

पूर्णांक mv88e6390_serdes_get_sset_count(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port)
अणु
	अगर (mv88e6390_serdes_get_lane(chip, port) < 0)
		वापस 0;

	वापस ARRAY_SIZE(mv88e6390_serdes_hw_stats);
पूर्ण

पूर्णांक mv88e6390_serdes_get_strings(काष्ठा mv88e6xxx_chip *chip,
				 पूर्णांक port, uपूर्णांक8_t *data)
अणु
	काष्ठा mv88e6390_serdes_hw_stat *stat;
	पूर्णांक i;

	अगर (mv88e6390_serdes_get_lane(chip, port) < 0)
		वापस 0;

	क्रम (i = 0; i < ARRAY_SIZE(mv88e6390_serdes_hw_stats); i++) अणु
		stat = &mv88e6390_serdes_hw_stats[i];
		स_नकल(data + i * ETH_GSTRING_LEN, stat->string,
		       ETH_GSTRING_LEN);
	पूर्ण
	वापस ARRAY_SIZE(mv88e6390_serdes_hw_stats);
पूर्ण

अटल uपूर्णांक64_t mv88e6390_serdes_get_stat(काष्ठा mv88e6xxx_chip *chip, पूर्णांक lane,
					  काष्ठा mv88e6390_serdes_hw_stat *stat)
अणु
	u16 reg[3];
	पूर्णांक err, i;

	क्रम (i = 0; i < 3; i++) अणु
		err = mv88e6390_serdes_पढ़ो(chip, lane, MDIO_MMD_PHYXS,
					    stat->reg + i, &reg[i]);
		अगर (err) अणु
			dev_err(chip->dev, "failed to read statistic\n");
			वापस 0;
		पूर्ण
	पूर्ण

	वापस reg[0] | ((u64)reg[1] << 16) | ((u64)reg[2] << 32);
पूर्ण

पूर्णांक mv88e6390_serdes_get_stats(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
			       uपूर्णांक64_t *data)
अणु
	काष्ठा mv88e6390_serdes_hw_stat *stat;
	पूर्णांक lane;
	पूर्णांक i;

	lane = mv88e6390_serdes_get_lane(chip, port);
	अगर (lane < 0)
		वापस 0;

	क्रम (i = 0; i < ARRAY_SIZE(mv88e6390_serdes_hw_stats); i++) अणु
		stat = &mv88e6390_serdes_hw_stats[i];
		data[i] = mv88e6390_serdes_get_stat(chip, lane, stat);
	पूर्ण

	वापस ARRAY_SIZE(mv88e6390_serdes_hw_stats);
पूर्ण

अटल पूर्णांक mv88e6390_serdes_enable_checker(काष्ठा mv88e6xxx_chip *chip, पूर्णांक lane)
अणु
	u16 reg;
	पूर्णांक err;

	err = mv88e6390_serdes_पढ़ो(chip, lane, MDIO_MMD_PHYXS,
				    MV88E6390_PG_CONTROL, &reg);
	अगर (err)
		वापस err;

	reg |= MV88E6390_PG_CONTROL_ENABLE_PC;
	वापस mv88e6390_serdes_ग_लिखो(chip, lane, MDIO_MMD_PHYXS,
				      MV88E6390_PG_CONTROL, reg);
पूर्ण

पूर्णांक mv88e6390_serdes_घातer(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, पूर्णांक lane,
			   bool up)
अणु
	u8 cmode = chip->ports[port].cmode;
	पूर्णांक err = 0;

	चयन (cmode) अणु
	हाल MV88E6XXX_PORT_STS_CMODE_SGMII:
	हाल MV88E6XXX_PORT_STS_CMODE_1000BASEX:
	हाल MV88E6XXX_PORT_STS_CMODE_2500BASEX:
		err = mv88e6390_serdes_घातer_sgmii(chip, lane, up);
		अवरोध;
	हाल MV88E6XXX_PORT_STS_CMODE_XAUI:
	हाल MV88E6XXX_PORT_STS_CMODE_RXAUI:
		err = mv88e6390_serdes_घातer_10g(chip, lane, up);
		अवरोध;
	पूर्ण

	अगर (!err && up)
		err = mv88e6390_serdes_enable_checker(chip, lane);

	वापस err;
पूर्ण

पूर्णांक mv88e6390_serdes_pcs_config(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				पूर्णांक lane, अचिन्हित पूर्णांक mode,
				phy_पूर्णांकerface_t पूर्णांकerface,
				स्थिर अचिन्हित दीर्घ *advertise)
अणु
	u16 val, bmcr, adv;
	bool changed;
	पूर्णांक err;

	चयन (पूर्णांकerface) अणु
	हाल PHY_INTERFACE_MODE_SGMII:
		adv = 0x0001;
		अवरोध;

	हाल PHY_INTERFACE_MODE_1000BASEX:
		adv = linkmode_adv_to_mii_adv_x(advertise,
					ETHTOOL_LINK_MODE_1000baseX_Full_BIT);
		अवरोध;

	हाल PHY_INTERFACE_MODE_2500BASEX:
		adv = linkmode_adv_to_mii_adv_x(advertise,
					ETHTOOL_LINK_MODE_2500baseX_Full_BIT);
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	err = mv88e6390_serdes_पढ़ो(chip, lane, MDIO_MMD_PHYXS,
				    MV88E6390_SGMII_ADVERTISE, &val);
	अगर (err)
		वापस err;

	changed = val != adv;
	अगर (changed) अणु
		err = mv88e6390_serdes_ग_लिखो(chip, lane, MDIO_MMD_PHYXS,
					     MV88E6390_SGMII_ADVERTISE, adv);
		अगर (err)
			वापस err;
	पूर्ण

	err = mv88e6390_serdes_पढ़ो(chip, lane, MDIO_MMD_PHYXS,
				    MV88E6390_SGMII_BMCR, &val);
	अगर (err)
		वापस err;

	अगर (phylink_स्वतःneg_inband(mode))
		bmcr = val | BMCR_ANENABLE;
	अन्यथा
		bmcr = val & ~BMCR_ANENABLE;

	/* setting ANENABLE triggers a restart of negotiation */
	अगर (bmcr == val)
		वापस changed;

	वापस mv88e6390_serdes_ग_लिखो(chip, lane, MDIO_MMD_PHYXS,
				      MV88E6390_SGMII_BMCR, bmcr);
पूर्ण

अटल पूर्णांक mv88e6390_serdes_pcs_get_state_sgmii(काष्ठा mv88e6xxx_chip *chip,
	पूर्णांक port, पूर्णांक lane, काष्ठा phylink_link_state *state)
अणु
	u16 lpa, status;
	पूर्णांक err;

	err = mv88e6390_serdes_पढ़ो(chip, lane, MDIO_MMD_PHYXS,
				    MV88E6390_SGMII_PHY_STATUS, &status);
	अगर (err) अणु
		dev_err(chip->dev, "can't read Serdes PHY status: %d\n", err);
		वापस err;
	पूर्ण

	err = mv88e6390_serdes_पढ़ो(chip, lane, MDIO_MMD_PHYXS,
				    MV88E6390_SGMII_LPA, &lpa);
	अगर (err) अणु
		dev_err(chip->dev, "can't read Serdes PHY LPA: %d\n", err);
		वापस err;
	पूर्ण

	वापस mv88e6xxx_serdes_pcs_get_state(chip, status, lpa, state);
पूर्ण

अटल पूर्णांक mv88e6390_serdes_pcs_get_state_10g(काष्ठा mv88e6xxx_chip *chip,
	पूर्णांक port, पूर्णांक lane, काष्ठा phylink_link_state *state)
अणु
	u16 status;
	पूर्णांक err;

	err = mv88e6390_serdes_पढ़ो(chip, lane, MDIO_MMD_PHYXS,
				    MV88E6390_10G_STAT1, &status);
	अगर (err)
		वापस err;

	state->link = !!(status & MDIO_STAT1_LSTATUS);
	अगर (state->link) अणु
		state->speed = SPEED_10000;
		state->duplex = DUPLEX_FULL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mv88e6393x_serdes_pcs_get_state_10g(काष्ठा mv88e6xxx_chip *chip,
					       पूर्णांक port, पूर्णांक lane,
					       काष्ठा phylink_link_state *state)
अणु
	u16 status;
	पूर्णांक err;

	err = mv88e6390_serdes_पढ़ो(chip, lane, MDIO_MMD_PHYXS,
				    MV88E6390_10G_STAT1, &status);
	अगर (err)
		वापस err;

	state->link = !!(status & MDIO_STAT1_LSTATUS);
	अगर (state->link) अणु
		अगर (state->पूर्णांकerface == PHY_INTERFACE_MODE_5GBASER)
			state->speed = SPEED_5000;
		अन्यथा
			state->speed = SPEED_10000;
		state->duplex = DUPLEX_FULL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mv88e6390_serdes_pcs_get_state(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				   पूर्णांक lane, काष्ठा phylink_link_state *state)
अणु
	चयन (state->पूर्णांकerface) अणु
	हाल PHY_INTERFACE_MODE_SGMII:
	हाल PHY_INTERFACE_MODE_1000BASEX:
	हाल PHY_INTERFACE_MODE_2500BASEX:
		वापस mv88e6390_serdes_pcs_get_state_sgmii(chip, port, lane,
							    state);
	हाल PHY_INTERFACE_MODE_XAUI:
	हाल PHY_INTERFACE_MODE_RXAUI:
		वापस mv88e6390_serdes_pcs_get_state_10g(chip, port, lane,
							  state);

	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

पूर्णांक mv88e6393x_serdes_pcs_get_state(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				    पूर्णांक lane, काष्ठा phylink_link_state *state)
अणु
	चयन (state->पूर्णांकerface) अणु
	हाल PHY_INTERFACE_MODE_SGMII:
	हाल PHY_INTERFACE_MODE_1000BASEX:
	हाल PHY_INTERFACE_MODE_2500BASEX:
		वापस mv88e6390_serdes_pcs_get_state_sgmii(chip, port, lane,
							    state);
	हाल PHY_INTERFACE_MODE_5GBASER:
	हाल PHY_INTERFACE_MODE_10GBASER:
		वापस mv88e6393x_serdes_pcs_get_state_10g(chip, port, lane,
							   state);

	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

पूर्णांक mv88e6390_serdes_pcs_an_restart(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				    पूर्णांक lane)
अणु
	u16 bmcr;
	पूर्णांक err;

	err = mv88e6390_serdes_पढ़ो(chip, lane, MDIO_MMD_PHYXS,
				    MV88E6390_SGMII_BMCR, &bmcr);
	अगर (err)
		वापस err;

	वापस mv88e6390_serdes_ग_लिखो(chip, lane, MDIO_MMD_PHYXS,
				      MV88E6390_SGMII_BMCR,
				      bmcr | BMCR_ANRESTART);
पूर्ण

पूर्णांक mv88e6390_serdes_pcs_link_up(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				 पूर्णांक lane, पूर्णांक speed, पूर्णांक duplex)
अणु
	u16 val, bmcr;
	पूर्णांक err;

	err = mv88e6390_serdes_पढ़ो(chip, lane, MDIO_MMD_PHYXS,
				    MV88E6390_SGMII_BMCR, &val);
	अगर (err)
		वापस err;

	bmcr = val & ~(BMCR_SPEED100 | BMCR_FULLDPLX | BMCR_SPEED1000);
	चयन (speed) अणु
	हाल SPEED_2500:
	हाल SPEED_1000:
		bmcr |= BMCR_SPEED1000;
		अवरोध;
	हाल SPEED_100:
		bmcr |= BMCR_SPEED100;
		अवरोध;
	हाल SPEED_10:
		अवरोध;
	पूर्ण

	अगर (duplex == DUPLEX_FULL)
		bmcr |= BMCR_FULLDPLX;

	अगर (bmcr == val)
		वापस 0;

	वापस mv88e6390_serdes_ग_लिखो(chip, lane, MDIO_MMD_PHYXS,
				      MV88E6390_SGMII_BMCR, bmcr);
पूर्ण

अटल व्योम mv88e6390_serdes_irq_link_sgmii(काष्ठा mv88e6xxx_chip *chip,
					    पूर्णांक port, पूर्णांक lane)
अणु
	u16 bmsr;
	पूर्णांक err;

	/* If the link has dropped, we want to know about it. */
	err = mv88e6390_serdes_पढ़ो(chip, lane, MDIO_MMD_PHYXS,
				    MV88E6390_SGMII_BMSR, &bmsr);
	अगर (err) अणु
		dev_err(chip->dev, "can't read Serdes BMSR: %d\n", err);
		वापस;
	पूर्ण

	dsa_port_phylink_mac_change(chip->ds, port, !!(bmsr & BMSR_LSTATUS));
पूर्ण

अटल व्योम mv88e6393x_serdes_irq_link_10g(काष्ठा mv88e6xxx_chip *chip,
					   पूर्णांक port, u8 lane)
अणु
	u16 status;
	पूर्णांक err;

	/* If the link has dropped, we want to know about it. */
	err = mv88e6390_serdes_पढ़ो(chip, lane, MDIO_MMD_PHYXS,
				    MV88E6390_10G_STAT1, &status);
	अगर (err) अणु
		dev_err(chip->dev, "can't read Serdes STAT1: %d\n", err);
		वापस;
	पूर्ण

	dsa_port_phylink_mac_change(chip->ds, port, !!(status & MDIO_STAT1_LSTATUS));
पूर्ण

अटल पूर्णांक mv88e6390_serdes_irq_enable_sgmii(काष्ठा mv88e6xxx_chip *chip,
					     पूर्णांक lane, bool enable)
अणु
	u16 val = 0;

	अगर (enable)
		val |= MV88E6390_SGMII_INT_LINK_DOWN |
			MV88E6390_SGMII_INT_LINK_UP;

	वापस mv88e6390_serdes_ग_लिखो(chip, lane, MDIO_MMD_PHYXS,
				      MV88E6390_SGMII_INT_ENABLE, val);
पूर्ण

पूर्णांक mv88e6390_serdes_irq_enable(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, पूर्णांक lane,
				bool enable)
अणु
	u8 cmode = chip->ports[port].cmode;

	चयन (cmode) अणु
	हाल MV88E6XXX_PORT_STS_CMODE_SGMII:
	हाल MV88E6XXX_PORT_STS_CMODE_1000BASEX:
	हाल MV88E6XXX_PORT_STS_CMODE_2500BASEX:
		वापस mv88e6390_serdes_irq_enable_sgmii(chip, lane, enable);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mv88e6390_serdes_irq_status_sgmii(काष्ठा mv88e6xxx_chip *chip,
					     पूर्णांक lane, u16 *status)
अणु
	पूर्णांक err;

	err = mv88e6390_serdes_पढ़ो(chip, lane, MDIO_MMD_PHYXS,
				    MV88E6390_SGMII_INT_STATUS, status);

	वापस err;
पूर्ण

अटल पूर्णांक mv88e6393x_serdes_irq_enable_10g(काष्ठा mv88e6xxx_chip *chip,
					    u8 lane, bool enable)
अणु
	u16 val = 0;

	अगर (enable)
		val |= MV88E6393X_10G_INT_LINK_CHANGE;

	वापस mv88e6390_serdes_ग_लिखो(chip, lane, MDIO_MMD_PHYXS,
				      MV88E6393X_10G_INT_ENABLE, val);
पूर्ण

पूर्णांक mv88e6393x_serdes_irq_enable(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				 पूर्णांक lane, bool enable)
अणु
	u8 cmode = chip->ports[port].cmode;

	चयन (cmode) अणु
	हाल MV88E6XXX_PORT_STS_CMODE_SGMII:
	हाल MV88E6XXX_PORT_STS_CMODE_1000BASEX:
	हाल MV88E6XXX_PORT_STS_CMODE_2500BASEX:
		वापस mv88e6390_serdes_irq_enable_sgmii(chip, lane, enable);
	हाल MV88E6393X_PORT_STS_CMODE_5GBASER:
	हाल MV88E6393X_PORT_STS_CMODE_10GBASER:
		वापस mv88e6393x_serdes_irq_enable_10g(chip, lane, enable);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mv88e6393x_serdes_irq_status_10g(काष्ठा mv88e6xxx_chip *chip,
					    u8 lane, u16 *status)
अणु
	पूर्णांक err;

	err = mv88e6390_serdes_पढ़ो(chip, lane, MDIO_MMD_PHYXS,
				    MV88E6393X_10G_INT_STATUS, status);

	वापस err;
पूर्ण

irqवापस_t mv88e6393x_serdes_irq_status(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
					 पूर्णांक lane)
अणु
	u8 cmode = chip->ports[port].cmode;
	irqवापस_t ret = IRQ_NONE;
	u16 status;
	पूर्णांक err;

	चयन (cmode) अणु
	हाल MV88E6XXX_PORT_STS_CMODE_SGMII:
	हाल MV88E6XXX_PORT_STS_CMODE_1000BASEX:
	हाल MV88E6XXX_PORT_STS_CMODE_2500BASEX:
		err = mv88e6390_serdes_irq_status_sgmii(chip, lane, &status);
		अगर (err)
			वापस ret;
		अगर (status & (MV88E6390_SGMII_INT_LINK_DOWN |
			      MV88E6390_SGMII_INT_LINK_UP)) अणु
			ret = IRQ_HANDLED;
			mv88e6390_serdes_irq_link_sgmii(chip, port, lane);
		पूर्ण
		अवरोध;
	हाल MV88E6393X_PORT_STS_CMODE_5GBASER:
	हाल MV88E6393X_PORT_STS_CMODE_10GBASER:
		err = mv88e6393x_serdes_irq_status_10g(chip, lane, &status);
		अगर (err)
			वापस err;
		अगर (status & MV88E6393X_10G_INT_LINK_CHANGE) अणु
			ret = IRQ_HANDLED;
			mv88e6393x_serdes_irq_link_10g(chip, port, lane);
		पूर्ण
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

irqवापस_t mv88e6390_serdes_irq_status(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
					पूर्णांक lane)
अणु
	u8 cmode = chip->ports[port].cmode;
	irqवापस_t ret = IRQ_NONE;
	u16 status;
	पूर्णांक err;

	चयन (cmode) अणु
	हाल MV88E6XXX_PORT_STS_CMODE_SGMII:
	हाल MV88E6XXX_PORT_STS_CMODE_1000BASEX:
	हाल MV88E6XXX_PORT_STS_CMODE_2500BASEX:
		err = mv88e6390_serdes_irq_status_sgmii(chip, lane, &status);
		अगर (err)
			वापस ret;
		अगर (status & (MV88E6390_SGMII_INT_LINK_DOWN |
			      MV88E6390_SGMII_INT_LINK_UP)) अणु
			ret = IRQ_HANDLED;
			mv88e6390_serdes_irq_link_sgmii(chip, port, lane);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अचिन्हित पूर्णांक mv88e6390_serdes_irq_mapping(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port)
अणु
	वापस irq_find_mapping(chip->g2_irq.करोमुख्य, port);
पूर्ण

अटल स्थिर u16 mv88e6390_serdes_regs[] = अणु
	/* SERDES common रेजिस्टरs */
	0xf00a, 0xf00b, 0xf00c,
	0xf010, 0xf011, 0xf012, 0xf013,
	0xf016, 0xf017, 0xf018,
	0xf01b, 0xf01c, 0xf01d, 0xf01e, 0xf01f,
	0xf020, 0xf021, 0xf022, 0xf023, 0xf024, 0xf025, 0xf026, 0xf027,
	0xf028, 0xf029,
	0xf030, 0xf031, 0xf032, 0xf033, 0xf034, 0xf035, 0xf036, 0xf037,
	0xf038, 0xf039,
	/* SGMII */
	0x2000, 0x2001, 0x2002, 0x2003, 0x2004, 0x2005, 0x2006, 0x2007,
	0x2008,
	0x200f,
	0xa000, 0xa001, 0xa002, 0xa003,
	/* 10Gbase-X */
	0x1000, 0x1001, 0x1002, 0x1003, 0x1004, 0x1005, 0x1006, 0x1007,
	0x1008,
	0x100e, 0x100f,
	0x1018, 0x1019,
	0x9000, 0x9001, 0x9002, 0x9003, 0x9004,
	0x9006,
	0x9010, 0x9011, 0x9012, 0x9013, 0x9014, 0x9015, 0x9016,
	/* 10Gbase-R */
	0x1020, 0x1021, 0x1022, 0x1023, 0x1024, 0x1025, 0x1026, 0x1027,
	0x1028, 0x1029, 0x102a, 0x102b,
पूर्ण;

पूर्णांक mv88e6390_serdes_get_regs_len(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port)
अणु
	अगर (mv88e6xxx_serdes_get_lane(chip, port) < 0)
		वापस 0;

	वापस ARRAY_SIZE(mv88e6390_serdes_regs) * माप(u16);
पूर्ण

व्योम mv88e6390_serdes_get_regs(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, व्योम *_p)
अणु
	u16 *p = _p;
	पूर्णांक lane;
	u16 reg;
	पूर्णांक err;
	पूर्णांक i;

	lane = mv88e6xxx_serdes_get_lane(chip, port);
	अगर (lane < 0)
		वापस;

	क्रम (i = 0 ; i < ARRAY_SIZE(mv88e6390_serdes_regs); i++) अणु
		err = mv88e6390_serdes_पढ़ो(chip, lane, MDIO_MMD_PHYXS,
					    mv88e6390_serdes_regs[i], &reg);
		अगर (!err)
			p[i] = reg;
	पूर्ण
पूर्ण

अटल पूर्णांक mv88e6393x_serdes_port_errata(काष्ठा mv88e6xxx_chip *chip, पूर्णांक lane)
अणु
	u16 reg, pcs;
	पूर्णांक err;

	/* mv88e6393x family errata 4.6:
	 * Cannot clear PwrDn bit on SERDES on port 0 अगर device is configured
	 * CPU_MGD mode or P0_mode is configured क्रम [x]MII.
	 * Workaround: Set Port0 SERDES रेजिस्टर 4.F002 bit 5=0 and bit 15=1.
	 *
	 * It seems that after this workaround the SERDES is स्वतःmatically
	 * घातered up (the bit is cleared), so घातer it करोwn.
	 */
	अगर (lane == MV88E6393X_PORT0_LANE) अणु
		err = mv88e6390_serdes_पढ़ो(chip, MV88E6393X_PORT0_LANE,
					    MDIO_MMD_PHYXS,
					    MV88E6393X_SERDES_POC, &reg);
		अगर (err)
			वापस err;

		reg &= ~MV88E6393X_SERDES_POC_PDOWN;
		reg |= MV88E6393X_SERDES_POC_RESET;

		err = mv88e6390_serdes_ग_लिखो(chip, lane, MDIO_MMD_PHYXS,
					     MV88E6393X_SERDES_POC, reg);
		अगर (err)
			वापस err;

		err = mv88e6390_serdes_घातer_sgmii(chip, lane, false);
		अगर (err)
			वापस err;
	पूर्ण

	/* mv88e6393x family errata 4.8:
	 * When a SERDES port is operating in 1000BASE-X or SGMII mode link may
	 * not come up after hardware reset or software reset of SERDES core.
	 * Workaround is to ग_लिखो SERDES रेजिस्टर 4.F074.14=1 क्रम only those
	 * modes and 0 in all other modes.
	 */
	err = mv88e6390_serdes_पढ़ो(chip, lane, MDIO_MMD_PHYXS,
				    MV88E6393X_SERDES_POC, &pcs);
	अगर (err)
		वापस err;

	pcs &= MV88E6393X_SERDES_POC_PCS_MASK;

	err = mv88e6390_serdes_पढ़ो(chip, lane, MDIO_MMD_PHYXS,
				    MV88E6393X_ERRATA_4_8_REG, &reg);
	अगर (err)
		वापस err;

	अगर (pcs == MV88E6393X_SERDES_POC_PCS_1000BASEX ||
	    pcs == MV88E6393X_SERDES_POC_PCS_SGMII_PHY ||
	    pcs == MV88E6393X_SERDES_POC_PCS_SGMII_MAC)
		reg |= MV88E6393X_ERRATA_4_8_BIT;
	अन्यथा
		reg &= ~MV88E6393X_ERRATA_4_8_BIT;

	वापस mv88e6390_serdes_ग_लिखो(chip, lane, MDIO_MMD_PHYXS,
				      MV88E6393X_ERRATA_4_8_REG, reg);
पूर्ण

पूर्णांक mv88e6393x_serdes_setup_errata(काष्ठा mv88e6xxx_chip *chip)
अणु
	पूर्णांक err;

	err = mv88e6393x_serdes_port_errata(chip, MV88E6393X_PORT0_LANE);
	अगर (err)
		वापस err;

	err = mv88e6393x_serdes_port_errata(chip, MV88E6393X_PORT9_LANE);
	अगर (err)
		वापस err;

	वापस mv88e6393x_serdes_port_errata(chip, MV88E6393X_PORT10_LANE);
पूर्ण

पूर्णांक mv88e6393x_serdes_घातer(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, पूर्णांक lane,
			    bool on)
अणु
	u8 cmode = chip->ports[port].cmode;

	अगर (port != 0 && port != 9 && port != 10)
		वापस -EOPNOTSUPP;

	चयन (cmode) अणु
	हाल MV88E6XXX_PORT_STS_CMODE_SGMII:
	हाल MV88E6XXX_PORT_STS_CMODE_1000BASEX:
	हाल MV88E6XXX_PORT_STS_CMODE_2500BASEX:
		वापस mv88e6390_serdes_घातer_sgmii(chip, lane, on);
	हाल MV88E6393X_PORT_STS_CMODE_5GBASER:
	हाल MV88E6393X_PORT_STS_CMODE_10GBASER:
		वापस mv88e6390_serdes_घातer_10g(chip, lane, on);
	पूर्ण

	वापस 0;
पूर्ण
