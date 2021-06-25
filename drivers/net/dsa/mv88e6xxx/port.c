<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Marvell 88E6xxx Switch Port Registers support
 *
 * Copyright (c) 2008 Marvell Semiconductor
 *
 * Copyright (c) 2016-2017 Savoir-faire Linux Inc.
 *	Vivien Didelot <vivien.didelot@savoirfairelinux.com>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/अगर_bridge.h>
#समावेश <linux/phy.h>
#समावेश <linux/phylink.h>

#समावेश "chip.h"
#समावेश "global2.h"
#समावेश "port.h"
#समावेश "serdes.h"

पूर्णांक mv88e6xxx_port_पढ़ो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, पूर्णांक reg,
			u16 *val)
अणु
	पूर्णांक addr = chip->info->port_base_addr + port;

	वापस mv88e6xxx_पढ़ो(chip, addr, reg, val);
पूर्ण

पूर्णांक mv88e6xxx_port_रुको_bit(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, पूर्णांक reg,
			    पूर्णांक bit, पूर्णांक val)
अणु
	पूर्णांक addr = chip->info->port_base_addr + port;

	वापस mv88e6xxx_रुको_bit(chip, addr, reg, bit, val);
पूर्ण

पूर्णांक mv88e6xxx_port_ग_लिखो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, पूर्णांक reg,
			 u16 val)
अणु
	पूर्णांक addr = chip->info->port_base_addr + port;

	वापस mv88e6xxx_ग_लिखो(chip, addr, reg, val);
पूर्ण

/* Offset 0x00: MAC (or PCS or Physical) Status Register
 *
 * For most devices, this is पढ़ो only. However the 6185 has the MyPause
 * bit पढ़ो/ग_लिखो.
 */
पूर्णांक mv88e6185_port_set_छोड़ो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
			     पूर्णांक छोड़ो)
अणु
	u16 reg;
	पूर्णांक err;

	err = mv88e6xxx_port_पढ़ो(chip, port, MV88E6XXX_PORT_STS, &reg);
	अगर (err)
		वापस err;

	अगर (छोड़ो)
		reg |= MV88E6XXX_PORT_STS_MY_PAUSE;
	अन्यथा
		reg &= ~MV88E6XXX_PORT_STS_MY_PAUSE;

	वापस mv88e6xxx_port_ग_लिखो(chip, port, MV88E6XXX_PORT_STS, reg);
पूर्ण

/* Offset 0x01: MAC (or PCS or Physical) Control Register
 *
 * Link, Duplex and Flow Control have one क्रमce bit, one value bit.
 *
 * For port's MAC speed, ForceSpd (or SpdValue) bits 1:0 program the value.
 * Alternative values require the 200BASE (or AltSpeed) bit 12 set.
 * Newer chips need a ForcedSpd bit 13 set to consider the value.
 */

अटल पूर्णांक mv88e6xxx_port_set_rgmii_delay(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
					  phy_पूर्णांकerface_t mode)
अणु
	u16 reg;
	पूर्णांक err;

	err = mv88e6xxx_port_पढ़ो(chip, port, MV88E6XXX_PORT_MAC_CTL, &reg);
	अगर (err)
		वापस err;

	reg &= ~(MV88E6XXX_PORT_MAC_CTL_RGMII_DELAY_RXCLK |
		 MV88E6XXX_PORT_MAC_CTL_RGMII_DELAY_TXCLK);

	चयन (mode) अणु
	हाल PHY_INTERFACE_MODE_RGMII_RXID:
		reg |= MV88E6XXX_PORT_MAC_CTL_RGMII_DELAY_RXCLK;
		अवरोध;
	हाल PHY_INTERFACE_MODE_RGMII_TXID:
		reg |= MV88E6XXX_PORT_MAC_CTL_RGMII_DELAY_TXCLK;
		अवरोध;
	हाल PHY_INTERFACE_MODE_RGMII_ID:
		reg |= MV88E6XXX_PORT_MAC_CTL_RGMII_DELAY_RXCLK |
			MV88E6XXX_PORT_MAC_CTL_RGMII_DELAY_TXCLK;
		अवरोध;
	हाल PHY_INTERFACE_MODE_RGMII:
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	err = mv88e6xxx_port_ग_लिखो(chip, port, MV88E6XXX_PORT_MAC_CTL, reg);
	अगर (err)
		वापस err;

	dev_dbg(chip->dev, "p%d: delay RXCLK %s, TXCLK %s\n", port,
		reg & MV88E6XXX_PORT_MAC_CTL_RGMII_DELAY_RXCLK ? "yes" : "no",
		reg & MV88E6XXX_PORT_MAC_CTL_RGMII_DELAY_TXCLK ? "yes" : "no");

	वापस 0;
पूर्ण

पूर्णांक mv88e6352_port_set_rgmii_delay(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				   phy_पूर्णांकerface_t mode)
अणु
	अगर (port < 5)
		वापस -EOPNOTSUPP;

	वापस mv88e6xxx_port_set_rgmii_delay(chip, port, mode);
पूर्ण

पूर्णांक mv88e6390_port_set_rgmii_delay(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				   phy_पूर्णांकerface_t mode)
अणु
	अगर (port != 0)
		वापस -EOPNOTSUPP;

	वापस mv88e6xxx_port_set_rgmii_delay(chip, port, mode);
पूर्ण

पूर्णांक mv88e6xxx_port_set_link(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, पूर्णांक link)
अणु
	u16 reg;
	पूर्णांक err;

	err = mv88e6xxx_port_पढ़ो(chip, port, MV88E6XXX_PORT_MAC_CTL, &reg);
	अगर (err)
		वापस err;

	reg &= ~(MV88E6XXX_PORT_MAC_CTL_FORCE_LINK |
		 MV88E6XXX_PORT_MAC_CTL_LINK_UP);

	चयन (link) अणु
	हाल LINK_FORCED_DOWN:
		reg |= MV88E6XXX_PORT_MAC_CTL_FORCE_LINK;
		अवरोध;
	हाल LINK_FORCED_UP:
		reg |= MV88E6XXX_PORT_MAC_CTL_FORCE_LINK |
			MV88E6XXX_PORT_MAC_CTL_LINK_UP;
		अवरोध;
	हाल LINK_UNFORCED:
		/* normal link detection */
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	err = mv88e6xxx_port_ग_लिखो(chip, port, MV88E6XXX_PORT_MAC_CTL, reg);
	अगर (err)
		वापस err;

	dev_dbg(chip->dev, "p%d: %s link %s\n", port,
		reg & MV88E6XXX_PORT_MAC_CTL_FORCE_LINK ? "Force" : "Unforce",
		reg & MV88E6XXX_PORT_MAC_CTL_LINK_UP ? "up" : "down");

	वापस 0;
पूर्ण

पूर्णांक mv88e6xxx_port_sync_link(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, अचिन्हित पूर्णांक mode, bool isup)
अणु
	स्थिर काष्ठा mv88e6xxx_ops *ops = chip->info->ops;
	पूर्णांक err = 0;
	पूर्णांक link;

	अगर (isup)
		link = LINK_FORCED_UP;
	अन्यथा
		link = LINK_FORCED_DOWN;

	अगर (ops->port_set_link)
		err = ops->port_set_link(chip, port, link);

	वापस err;
पूर्ण

पूर्णांक mv88e6185_port_sync_link(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, अचिन्हित पूर्णांक mode, bool isup)
अणु
	स्थिर काष्ठा mv88e6xxx_ops *ops = chip->info->ops;
	पूर्णांक err = 0;
	पूर्णांक link;

	अगर (mode == MLO_AN_INBAND)
		link = LINK_UNFORCED;
	अन्यथा अगर (isup)
		link = LINK_FORCED_UP;
	अन्यथा
		link = LINK_FORCED_DOWN;

	अगर (ops->port_set_link)
		err = ops->port_set_link(chip, port, link);

	वापस err;
पूर्ण

अटल पूर्णांक mv88e6xxx_port_set_speed_duplex(काष्ठा mv88e6xxx_chip *chip,
					   पूर्णांक port, पूर्णांक speed, bool alt_bit,
					   bool क्रमce_bit, पूर्णांक duplex)
अणु
	u16 reg, ctrl;
	पूर्णांक err;

	चयन (speed) अणु
	हाल 10:
		ctrl = MV88E6XXX_PORT_MAC_CTL_SPEED_10;
		अवरोध;
	हाल 100:
		ctrl = MV88E6XXX_PORT_MAC_CTL_SPEED_100;
		अवरोध;
	हाल 200:
		अगर (alt_bit)
			ctrl = MV88E6XXX_PORT_MAC_CTL_SPEED_100 |
				MV88E6390_PORT_MAC_CTL_ALTSPEED;
		अन्यथा
			ctrl = MV88E6065_PORT_MAC_CTL_SPEED_200;
		अवरोध;
	हाल 1000:
		ctrl = MV88E6XXX_PORT_MAC_CTL_SPEED_1000;
		अवरोध;
	हाल 2500:
		अगर (alt_bit)
			ctrl = MV88E6390_PORT_MAC_CTL_SPEED_10000 |
				MV88E6390_PORT_MAC_CTL_ALTSPEED;
		अन्यथा
			ctrl = MV88E6390_PORT_MAC_CTL_SPEED_10000;
		अवरोध;
	हाल 10000:
		/* all bits set, fall through... */
	हाल SPEED_UNFORCED:
		ctrl = MV88E6XXX_PORT_MAC_CTL_SPEED_UNFORCED;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	चयन (duplex) अणु
	हाल DUPLEX_HALF:
		ctrl |= MV88E6XXX_PORT_MAC_CTL_FORCE_DUPLEX;
		अवरोध;
	हाल DUPLEX_FULL:
		ctrl |= MV88E6XXX_PORT_MAC_CTL_FORCE_DUPLEX |
			MV88E6XXX_PORT_MAC_CTL_DUPLEX_FULL;
		अवरोध;
	हाल DUPLEX_UNFORCED:
		/* normal duplex detection */
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	err = mv88e6xxx_port_पढ़ो(chip, port, MV88E6XXX_PORT_MAC_CTL, &reg);
	अगर (err)
		वापस err;

	reg &= ~(MV88E6XXX_PORT_MAC_CTL_SPEED_MASK |
		 MV88E6XXX_PORT_MAC_CTL_FORCE_DUPLEX |
		 MV88E6XXX_PORT_MAC_CTL_DUPLEX_FULL);

	अगर (alt_bit)
		reg &= ~MV88E6390_PORT_MAC_CTL_ALTSPEED;
	अगर (क्रमce_bit) अणु
		reg &= ~MV88E6390_PORT_MAC_CTL_FORCE_SPEED;
		अगर (speed != SPEED_UNFORCED)
			ctrl |= MV88E6390_PORT_MAC_CTL_FORCE_SPEED;
	पूर्ण
	reg |= ctrl;

	err = mv88e6xxx_port_ग_लिखो(chip, port, MV88E6XXX_PORT_MAC_CTL, reg);
	अगर (err)
		वापस err;

	अगर (speed)
		dev_dbg(chip->dev, "p%d: Speed set to %d Mbps\n", port, speed);
	अन्यथा
		dev_dbg(chip->dev, "p%d: Speed unforced\n", port);
	dev_dbg(chip->dev, "p%d: %s %s duplex\n", port,
		reg & MV88E6XXX_PORT_MAC_CTL_FORCE_DUPLEX ? "Force" : "Unforce",
		reg & MV88E6XXX_PORT_MAC_CTL_DUPLEX_FULL ? "full" : "half");

	वापस 0;
पूर्ण

/* Support 10, 100, 200 Mbps (e.g. 88E6065 family) */
पूर्णांक mv88e6065_port_set_speed_duplex(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				    पूर्णांक speed, पूर्णांक duplex)
अणु
	अगर (speed == SPEED_MAX)
		speed = 200;

	अगर (speed > 200)
		वापस -EOPNOTSUPP;

	/* Setting 200 Mbps on port 0 to 3 selects 100 Mbps */
	वापस mv88e6xxx_port_set_speed_duplex(chip, port, speed, false, false,
					       duplex);
पूर्ण

/* Support 10, 100, 1000 Mbps (e.g. 88E6185 family) */
पूर्णांक mv88e6185_port_set_speed_duplex(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				    पूर्णांक speed, पूर्णांक duplex)
अणु
	अगर (speed == SPEED_MAX)
		speed = 1000;

	अगर (speed == 200 || speed > 1000)
		वापस -EOPNOTSUPP;

	वापस mv88e6xxx_port_set_speed_duplex(chip, port, speed, false, false,
					       duplex);
पूर्ण

/* Support 10, 100 Mbps (e.g. 88E6250 family) */
पूर्णांक mv88e6250_port_set_speed_duplex(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				    पूर्णांक speed, पूर्णांक duplex)
अणु
	अगर (speed == SPEED_MAX)
		speed = 100;

	अगर (speed > 100)
		वापस -EOPNOTSUPP;

	वापस mv88e6xxx_port_set_speed_duplex(chip, port, speed, false, false,
					       duplex);
पूर्ण

/* Support 10, 100, 200, 1000, 2500 Mbps (e.g. 88E6341) */
पूर्णांक mv88e6341_port_set_speed_duplex(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				    पूर्णांक speed, पूर्णांक duplex)
अणु
	अगर (speed == SPEED_MAX)
		speed = port < 5 ? 1000 : 2500;

	अगर (speed > 2500)
		वापस -EOPNOTSUPP;

	अगर (speed == 200 && port != 0)
		वापस -EOPNOTSUPP;

	अगर (speed == 2500 && port < 5)
		वापस -EOPNOTSUPP;

	वापस mv88e6xxx_port_set_speed_duplex(chip, port, speed, !port, true,
					       duplex);
पूर्ण

phy_पूर्णांकerface_t mv88e6341_port_max_speed_mode(पूर्णांक port)
अणु
	अगर (port == 5)
		वापस PHY_INTERFACE_MODE_2500BASEX;

	वापस PHY_INTERFACE_MODE_NA;
पूर्ण

/* Support 10, 100, 200, 1000 Mbps (e.g. 88E6352 family) */
पूर्णांक mv88e6352_port_set_speed_duplex(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				    पूर्णांक speed, पूर्णांक duplex)
अणु
	अगर (speed == SPEED_MAX)
		speed = 1000;

	अगर (speed > 1000)
		वापस -EOPNOTSUPP;

	अगर (speed == 200 && port < 5)
		वापस -EOPNOTSUPP;

	वापस mv88e6xxx_port_set_speed_duplex(chip, port, speed, true, false,
					       duplex);
पूर्ण

/* Support 10, 100, 200, 1000, 2500 Mbps (e.g. 88E6390) */
पूर्णांक mv88e6390_port_set_speed_duplex(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				    पूर्णांक speed, पूर्णांक duplex)
अणु
	अगर (speed == SPEED_MAX)
		speed = port < 9 ? 1000 : 2500;

	अगर (speed > 2500)
		वापस -EOPNOTSUPP;

	अगर (speed == 200 && port != 0)
		वापस -EOPNOTSUPP;

	अगर (speed == 2500 && port < 9)
		वापस -EOPNOTSUPP;

	वापस mv88e6xxx_port_set_speed_duplex(chip, port, speed, true, true,
					       duplex);
पूर्ण

phy_पूर्णांकerface_t mv88e6390_port_max_speed_mode(पूर्णांक port)
अणु
	अगर (port == 9 || port == 10)
		वापस PHY_INTERFACE_MODE_2500BASEX;

	वापस PHY_INTERFACE_MODE_NA;
पूर्ण

/* Support 10, 100, 200, 1000, 2500, 10000 Mbps (e.g. 88E6190X) */
पूर्णांक mv88e6390x_port_set_speed_duplex(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				     पूर्णांक speed, पूर्णांक duplex)
अणु
	अगर (speed == SPEED_MAX)
		speed = port < 9 ? 1000 : 10000;

	अगर (speed == 200 && port != 0)
		वापस -EOPNOTSUPP;

	अगर (speed >= 2500 && port < 9)
		वापस -EOPNOTSUPP;

	वापस mv88e6xxx_port_set_speed_duplex(chip, port, speed, true, true,
					       duplex);
पूर्ण

phy_पूर्णांकerface_t mv88e6390x_port_max_speed_mode(पूर्णांक port)
अणु
	अगर (port == 9 || port == 10)
		वापस PHY_INTERFACE_MODE_XAUI;

	वापस PHY_INTERFACE_MODE_NA;
पूर्ण

/* Support 10, 100, 200, 1000, 2500, 5000, 10000 Mbps (e.g. 88E6393X)
 * Function mv88e6xxx_port_set_speed_duplex() can't be used as the रेजिस्टर
 * values क्रम speeds 2500 & 5000 conflict.
 */
पूर्णांक mv88e6393x_port_set_speed_duplex(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				     पूर्णांक speed, पूर्णांक duplex)
अणु
	u16 reg, ctrl;
	पूर्णांक err;

	अगर (speed == SPEED_MAX)
		speed = (port > 0 && port < 9) ? 1000 : 10000;

	अगर (speed == 200 && port != 0)
		वापस -EOPNOTSUPP;

	अगर (speed >= 2500 && port > 0 && port < 9)
		वापस -EOPNOTSUPP;

	चयन (speed) अणु
	हाल 10:
		ctrl = MV88E6XXX_PORT_MAC_CTL_SPEED_10;
		अवरोध;
	हाल 100:
		ctrl = MV88E6XXX_PORT_MAC_CTL_SPEED_100;
		अवरोध;
	हाल 200:
		ctrl = MV88E6XXX_PORT_MAC_CTL_SPEED_100 |
			MV88E6390_PORT_MAC_CTL_ALTSPEED;
		अवरोध;
	हाल 1000:
		ctrl = MV88E6XXX_PORT_MAC_CTL_SPEED_1000;
		अवरोध;
	हाल 2500:
		ctrl = MV88E6XXX_PORT_MAC_CTL_SPEED_1000 |
			MV88E6390_PORT_MAC_CTL_ALTSPEED;
		अवरोध;
	हाल 5000:
		ctrl = MV88E6390_PORT_MAC_CTL_SPEED_10000 |
			MV88E6390_PORT_MAC_CTL_ALTSPEED;
		अवरोध;
	हाल 10000:
	हाल SPEED_UNFORCED:
		ctrl = MV88E6XXX_PORT_MAC_CTL_SPEED_UNFORCED;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	चयन (duplex) अणु
	हाल DUPLEX_HALF:
		ctrl |= MV88E6XXX_PORT_MAC_CTL_FORCE_DUPLEX;
		अवरोध;
	हाल DUPLEX_FULL:
		ctrl |= MV88E6XXX_PORT_MAC_CTL_FORCE_DUPLEX |
			MV88E6XXX_PORT_MAC_CTL_DUPLEX_FULL;
		अवरोध;
	हाल DUPLEX_UNFORCED:
		/* normal duplex detection */
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	err = mv88e6xxx_port_पढ़ो(chip, port, MV88E6XXX_PORT_MAC_CTL, &reg);
	अगर (err)
		वापस err;

	reg &= ~(MV88E6XXX_PORT_MAC_CTL_SPEED_MASK |
		 MV88E6390_PORT_MAC_CTL_ALTSPEED |
		 MV88E6390_PORT_MAC_CTL_FORCE_SPEED);

	अगर (speed != SPEED_UNFORCED)
		reg |= MV88E6390_PORT_MAC_CTL_FORCE_SPEED;

	reg |= ctrl;

	err = mv88e6xxx_port_ग_लिखो(chip, port, MV88E6XXX_PORT_MAC_CTL, reg);
	अगर (err)
		वापस err;

	अगर (speed)
		dev_dbg(chip->dev, "p%d: Speed set to %d Mbps\n", port, speed);
	अन्यथा
		dev_dbg(chip->dev, "p%d: Speed unforced\n", port);
	dev_dbg(chip->dev, "p%d: %s %s duplex\n", port,
		reg & MV88E6XXX_PORT_MAC_CTL_FORCE_DUPLEX ? "Force" : "Unforce",
		reg & MV88E6XXX_PORT_MAC_CTL_DUPLEX_FULL ? "full" : "half");

	वापस 0;
पूर्ण

phy_पूर्णांकerface_t mv88e6393x_port_max_speed_mode(पूर्णांक port)
अणु
	अगर (port == 0 || port == 9 || port == 10)
		वापस PHY_INTERFACE_MODE_10GBASER;

	वापस PHY_INTERFACE_MODE_NA;
पूर्ण

अटल पूर्णांक mv88e6xxx_port_set_cmode(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				    phy_पूर्णांकerface_t mode, bool क्रमce)
अणु
	u16 cmode;
	पूर्णांक lane;
	u16 reg;
	पूर्णांक err;

	/* Default to a slow mode, so मुक्तing up SERDES पूर्णांकerfaces क्रम
	 * other ports which might use them क्रम SFPs.
	 */
	अगर (mode == PHY_INTERFACE_MODE_NA)
		mode = PHY_INTERFACE_MODE_1000BASEX;

	चयन (mode) अणु
	हाल PHY_INTERFACE_MODE_1000BASEX:
		cmode = MV88E6XXX_PORT_STS_CMODE_1000BASEX;
		अवरोध;
	हाल PHY_INTERFACE_MODE_SGMII:
		cmode = MV88E6XXX_PORT_STS_CMODE_SGMII;
		अवरोध;
	हाल PHY_INTERFACE_MODE_2500BASEX:
		cmode = MV88E6XXX_PORT_STS_CMODE_2500BASEX;
		अवरोध;
	हाल PHY_INTERFACE_MODE_5GBASER:
		cmode = MV88E6393X_PORT_STS_CMODE_5GBASER;
		अवरोध;
	हाल PHY_INTERFACE_MODE_XGMII:
	हाल PHY_INTERFACE_MODE_XAUI:
		cmode = MV88E6XXX_PORT_STS_CMODE_XAUI;
		अवरोध;
	हाल PHY_INTERFACE_MODE_RXAUI:
		cmode = MV88E6XXX_PORT_STS_CMODE_RXAUI;
		अवरोध;
	हाल PHY_INTERFACE_MODE_10GBASER:
		cmode = MV88E6393X_PORT_STS_CMODE_10GBASER;
		अवरोध;
	शेष:
		cmode = 0;
	पूर्ण

	/* cmode करोesn't change, nothing to करो क्रम us unless क्रमced */
	अगर (cmode == chip->ports[port].cmode && !क्रमce)
		वापस 0;

	lane = mv88e6xxx_serdes_get_lane(chip, port);
	अगर (lane >= 0) अणु
		अगर (chip->ports[port].serdes_irq) अणु
			err = mv88e6xxx_serdes_irq_disable(chip, port, lane);
			अगर (err)
				वापस err;
		पूर्ण

		err = mv88e6xxx_serdes_घातer_करोwn(chip, port, lane);
		अगर (err)
			वापस err;
	पूर्ण

	chip->ports[port].cmode = 0;

	अगर (cmode) अणु
		err = mv88e6xxx_port_पढ़ो(chip, port, MV88E6XXX_PORT_STS, &reg);
		अगर (err)
			वापस err;

		reg &= ~MV88E6XXX_PORT_STS_CMODE_MASK;
		reg |= cmode;

		err = mv88e6xxx_port_ग_लिखो(chip, port, MV88E6XXX_PORT_STS, reg);
		अगर (err)
			वापस err;

		chip->ports[port].cmode = cmode;

		lane = mv88e6xxx_serdes_get_lane(chip, port);
		अगर (lane < 0)
			वापस lane;

		err = mv88e6xxx_serdes_घातer_up(chip, port, lane);
		अगर (err)
			वापस err;

		अगर (chip->ports[port].serdes_irq) अणु
			err = mv88e6xxx_serdes_irq_enable(chip, port, lane);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mv88e6390x_port_set_cmode(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
			      phy_पूर्णांकerface_t mode)
अणु
	अगर (port != 9 && port != 10)
		वापस -EOPNOTSUPP;

	वापस mv88e6xxx_port_set_cmode(chip, port, mode, false);
पूर्ण

पूर्णांक mv88e6390_port_set_cmode(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
			     phy_पूर्णांकerface_t mode)
अणु
	अगर (port != 9 && port != 10)
		वापस -EOPNOTSUPP;

	चयन (mode) अणु
	हाल PHY_INTERFACE_MODE_NA:
		वापस 0;
	हाल PHY_INTERFACE_MODE_XGMII:
	हाल PHY_INTERFACE_MODE_XAUI:
	हाल PHY_INTERFACE_MODE_RXAUI:
		वापस -EINVAL;
	शेष:
		अवरोध;
	पूर्ण

	वापस mv88e6xxx_port_set_cmode(chip, port, mode, false);
पूर्ण

पूर्णांक mv88e6393x_port_set_cmode(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
			      phy_पूर्णांकerface_t mode)
अणु
	पूर्णांक err;
	u16 reg;

	अगर (port != 0 && port != 9 && port != 10)
		वापस -EOPNOTSUPP;

	/* mv88e6393x errata 4.5: EEE should be disabled on SERDES ports */
	err = mv88e6xxx_port_पढ़ो(chip, port, MV88E6XXX_PORT_MAC_CTL, &reg);
	अगर (err)
		वापस err;

	reg &= ~MV88E6XXX_PORT_MAC_CTL_EEE;
	reg |= MV88E6XXX_PORT_MAC_CTL_FORCE_EEE;
	err = mv88e6xxx_port_ग_लिखो(chip, port, MV88E6XXX_PORT_MAC_CTL, reg);
	अगर (err)
		वापस err;

	वापस mv88e6xxx_port_set_cmode(chip, port, mode, false);
पूर्ण

अटल पूर्णांक mv88e6341_port_set_cmode_writable(काष्ठा mv88e6xxx_chip *chip,
					     पूर्णांक port)
अणु
	पूर्णांक err, addr;
	u16 reg, bits;

	अगर (port != 5)
		वापस -EOPNOTSUPP;

	addr = chip->info->port_base_addr + port;

	err = mv88e6xxx_port_hidden_पढ़ो(chip, 0x7, addr, 0, &reg);
	अगर (err)
		वापस err;

	bits = MV88E6341_PORT_RESERVED_1A_FORCE_CMODE |
	       MV88E6341_PORT_RESERVED_1A_SGMII_AN;

	अगर ((reg & bits) == bits)
		वापस 0;

	reg |= bits;
	वापस mv88e6xxx_port_hidden_ग_लिखो(chip, 0x7, addr, 0, reg);
पूर्ण

पूर्णांक mv88e6341_port_set_cmode(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
			     phy_पूर्णांकerface_t mode)
अणु
	पूर्णांक err;

	अगर (port != 5)
		वापस -EOPNOTSUPP;

	चयन (mode) अणु
	हाल PHY_INTERFACE_MODE_NA:
		वापस 0;
	हाल PHY_INTERFACE_MODE_XGMII:
	हाल PHY_INTERFACE_MODE_XAUI:
	हाल PHY_INTERFACE_MODE_RXAUI:
		वापस -EINVAL;
	शेष:
		अवरोध;
	पूर्ण

	err = mv88e6341_port_set_cmode_writable(chip, port);
	अगर (err)
		वापस err;

	वापस mv88e6xxx_port_set_cmode(chip, port, mode, true);
पूर्ण

पूर्णांक mv88e6185_port_get_cmode(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, u8 *cmode)
अणु
	पूर्णांक err;
	u16 reg;

	err = mv88e6xxx_port_पढ़ो(chip, port, MV88E6XXX_PORT_STS, &reg);
	अगर (err)
		वापस err;

	*cmode = reg & MV88E6185_PORT_STS_CMODE_MASK;

	वापस 0;
पूर्ण

पूर्णांक mv88e6352_port_get_cmode(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, u8 *cmode)
अणु
	पूर्णांक err;
	u16 reg;

	err = mv88e6xxx_port_पढ़ो(chip, port, MV88E6XXX_PORT_STS, &reg);
	अगर (err)
		वापस err;

	*cmode = reg & MV88E6XXX_PORT_STS_CMODE_MASK;

	वापस 0;
पूर्ण

/* Offset 0x02: Jamming Control
 *
 * Do not limit the period of समय that this port can be छोड़ोd क्रम by
 * the remote end or the period of समय that this port can छोड़ो the
 * remote end.
 */
पूर्णांक mv88e6097_port_छोड़ो_limit(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, u8 in,
			       u8 out)
अणु
	वापस mv88e6xxx_port_ग_लिखो(chip, port, MV88E6097_PORT_JAM_CTL,
				    out << 8 | in);
पूर्ण

पूर्णांक mv88e6390_port_छोड़ो_limit(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, u8 in,
			       u8 out)
अणु
	पूर्णांक err;

	err = mv88e6xxx_port_ग_लिखो(chip, port, MV88E6390_PORT_FLOW_CTL,
				   MV88E6390_PORT_FLOW_CTL_UPDATE |
				   MV88E6390_PORT_FLOW_CTL_LIMIT_IN | in);
	अगर (err)
		वापस err;

	वापस mv88e6xxx_port_ग_लिखो(chip, port, MV88E6390_PORT_FLOW_CTL,
				    MV88E6390_PORT_FLOW_CTL_UPDATE |
				    MV88E6390_PORT_FLOW_CTL_LIMIT_OUT | out);
पूर्ण

/* Offset 0x04: Port Control Register */

अटल स्थिर अक्षर * स्थिर mv88e6xxx_port_state_names[] = अणु
	[MV88E6XXX_PORT_CTL0_STATE_DISABLED] = "Disabled",
	[MV88E6XXX_PORT_CTL0_STATE_BLOCKING] = "Blocking/Listening",
	[MV88E6XXX_PORT_CTL0_STATE_LEARNING] = "Learning",
	[MV88E6XXX_PORT_CTL0_STATE_FORWARDING] = "Forwarding",
पूर्ण;

पूर्णांक mv88e6xxx_port_set_state(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, u8 state)
अणु
	u16 reg;
	पूर्णांक err;

	err = mv88e6xxx_port_पढ़ो(chip, port, MV88E6XXX_PORT_CTL0, &reg);
	अगर (err)
		वापस err;

	reg &= ~MV88E6XXX_PORT_CTL0_STATE_MASK;

	चयन (state) अणु
	हाल BR_STATE_DISABLED:
		state = MV88E6XXX_PORT_CTL0_STATE_DISABLED;
		अवरोध;
	हाल BR_STATE_BLOCKING:
	हाल BR_STATE_LISTENING:
		state = MV88E6XXX_PORT_CTL0_STATE_BLOCKING;
		अवरोध;
	हाल BR_STATE_LEARNING:
		state = MV88E6XXX_PORT_CTL0_STATE_LEARNING;
		अवरोध;
	हाल BR_STATE_FORWARDING:
		state = MV88E6XXX_PORT_CTL0_STATE_FORWARDING;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	reg |= state;

	err = mv88e6xxx_port_ग_लिखो(chip, port, MV88E6XXX_PORT_CTL0, reg);
	अगर (err)
		वापस err;

	dev_dbg(chip->dev, "p%d: PortState set to %s\n", port,
		mv88e6xxx_port_state_names[state]);

	वापस 0;
पूर्ण

पूर्णांक mv88e6xxx_port_set_egress_mode(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				   क्रमागत mv88e6xxx_egress_mode mode)
अणु
	पूर्णांक err;
	u16 reg;

	err = mv88e6xxx_port_पढ़ो(chip, port, MV88E6XXX_PORT_CTL0, &reg);
	अगर (err)
		वापस err;

	reg &= ~MV88E6XXX_PORT_CTL0_EGRESS_MODE_MASK;

	चयन (mode) अणु
	हाल MV88E6XXX_EGRESS_MODE_UNMODIFIED:
		reg |= MV88E6XXX_PORT_CTL0_EGRESS_MODE_UNMODIFIED;
		अवरोध;
	हाल MV88E6XXX_EGRESS_MODE_UNTAGGED:
		reg |= MV88E6XXX_PORT_CTL0_EGRESS_MODE_UNTAGGED;
		अवरोध;
	हाल MV88E6XXX_EGRESS_MODE_TAGGED:
		reg |= MV88E6XXX_PORT_CTL0_EGRESS_MODE_TAGGED;
		अवरोध;
	हाल MV88E6XXX_EGRESS_MODE_ETHERTYPE:
		reg |= MV88E6XXX_PORT_CTL0_EGRESS_MODE_ETHER_TYPE_DSA;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस mv88e6xxx_port_ग_लिखो(chip, port, MV88E6XXX_PORT_CTL0, reg);
पूर्ण

पूर्णांक mv88e6085_port_set_frame_mode(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				  क्रमागत mv88e6xxx_frame_mode mode)
अणु
	पूर्णांक err;
	u16 reg;

	err = mv88e6xxx_port_पढ़ो(chip, port, MV88E6XXX_PORT_CTL0, &reg);
	अगर (err)
		वापस err;

	reg &= ~MV88E6XXX_PORT_CTL0_FRAME_MODE_MASK;

	चयन (mode) अणु
	हाल MV88E6XXX_FRAME_MODE_NORMAL:
		reg |= MV88E6XXX_PORT_CTL0_FRAME_MODE_NORMAL;
		अवरोध;
	हाल MV88E6XXX_FRAME_MODE_DSA:
		reg |= MV88E6XXX_PORT_CTL0_FRAME_MODE_DSA;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस mv88e6xxx_port_ग_लिखो(chip, port, MV88E6XXX_PORT_CTL0, reg);
पूर्ण

पूर्णांक mv88e6351_port_set_frame_mode(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				  क्रमागत mv88e6xxx_frame_mode mode)
अणु
	पूर्णांक err;
	u16 reg;

	err = mv88e6xxx_port_पढ़ो(chip, port, MV88E6XXX_PORT_CTL0, &reg);
	अगर (err)
		वापस err;

	reg &= ~MV88E6XXX_PORT_CTL0_FRAME_MODE_MASK;

	चयन (mode) अणु
	हाल MV88E6XXX_FRAME_MODE_NORMAL:
		reg |= MV88E6XXX_PORT_CTL0_FRAME_MODE_NORMAL;
		अवरोध;
	हाल MV88E6XXX_FRAME_MODE_DSA:
		reg |= MV88E6XXX_PORT_CTL0_FRAME_MODE_DSA;
		अवरोध;
	हाल MV88E6XXX_FRAME_MODE_PROVIDER:
		reg |= MV88E6XXX_PORT_CTL0_FRAME_MODE_PROVIDER;
		अवरोध;
	हाल MV88E6XXX_FRAME_MODE_ETHERTYPE:
		reg |= MV88E6XXX_PORT_CTL0_FRAME_MODE_ETHER_TYPE_DSA;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस mv88e6xxx_port_ग_लिखो(chip, port, MV88E6XXX_PORT_CTL0, reg);
पूर्ण

पूर्णांक mv88e6185_port_set_क्रमward_unknown(काष्ठा mv88e6xxx_chip *chip,
				       पूर्णांक port, bool unicast)
अणु
	पूर्णांक err;
	u16 reg;

	err = mv88e6xxx_port_पढ़ो(chip, port, MV88E6XXX_PORT_CTL0, &reg);
	अगर (err)
		वापस err;

	अगर (unicast)
		reg |= MV88E6185_PORT_CTL0_FORWARD_UNKNOWN;
	अन्यथा
		reg &= ~MV88E6185_PORT_CTL0_FORWARD_UNKNOWN;

	वापस mv88e6xxx_port_ग_लिखो(chip, port, MV88E6XXX_PORT_CTL0, reg);
पूर्ण

पूर्णांक mv88e6352_port_set_ucast_flood(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				   bool unicast)
अणु
	पूर्णांक err;
	u16 reg;

	err = mv88e6xxx_port_पढ़ो(chip, port, MV88E6XXX_PORT_CTL0, &reg);
	अगर (err)
		वापस err;

	अगर (unicast)
		reg |= MV88E6352_PORT_CTL0_EGRESS_FLOODS_UC;
	अन्यथा
		reg &= ~MV88E6352_PORT_CTL0_EGRESS_FLOODS_UC;

	वापस mv88e6xxx_port_ग_लिखो(chip, port, MV88E6XXX_PORT_CTL0, reg);
पूर्ण

पूर्णांक mv88e6352_port_set_mcast_flood(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				   bool multicast)
अणु
	पूर्णांक err;
	u16 reg;

	err = mv88e6xxx_port_पढ़ो(chip, port, MV88E6XXX_PORT_CTL0, &reg);
	अगर (err)
		वापस err;

	अगर (multicast)
		reg |= MV88E6352_PORT_CTL0_EGRESS_FLOODS_MC;
	अन्यथा
		reg &= ~MV88E6352_PORT_CTL0_EGRESS_FLOODS_MC;

	वापस mv88e6xxx_port_ग_लिखो(chip, port, MV88E6XXX_PORT_CTL0, reg);
पूर्ण

/* Offset 0x05: Port Control 1 */

पूर्णांक mv88e6xxx_port_set_message_port(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				    bool message_port)
अणु
	u16 val;
	पूर्णांक err;

	err = mv88e6xxx_port_पढ़ो(chip, port, MV88E6XXX_PORT_CTL1, &val);
	अगर (err)
		वापस err;

	अगर (message_port)
		val |= MV88E6XXX_PORT_CTL1_MESSAGE_PORT;
	अन्यथा
		val &= ~MV88E6XXX_PORT_CTL1_MESSAGE_PORT;

	वापस mv88e6xxx_port_ग_लिखो(chip, port, MV88E6XXX_PORT_CTL1, val);
पूर्ण

पूर्णांक mv88e6xxx_port_set_trunk(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
			     bool trunk, u8 id)
अणु
	u16 val;
	पूर्णांक err;

	err = mv88e6xxx_port_पढ़ो(chip, port, MV88E6XXX_PORT_CTL1, &val);
	अगर (err)
		वापस err;

	val &= ~MV88E6XXX_PORT_CTL1_TRUNK_ID_MASK;

	अगर (trunk)
		val |= MV88E6XXX_PORT_CTL1_TRUNK_PORT |
			(id << MV88E6XXX_PORT_CTL1_TRUNK_ID_SHIFT);
	अन्यथा
		val &= ~MV88E6XXX_PORT_CTL1_TRUNK_PORT;

	वापस mv88e6xxx_port_ग_लिखो(chip, port, MV88E6XXX_PORT_CTL1, val);
पूर्ण

/* Offset 0x06: Port Based VLAN Map */

पूर्णांक mv88e6xxx_port_set_vlan_map(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, u16 map)
अणु
	स्थिर u16 mask = mv88e6xxx_port_mask(chip);
	u16 reg;
	पूर्णांक err;

	err = mv88e6xxx_port_पढ़ो(chip, port, MV88E6XXX_PORT_BASE_VLAN, &reg);
	अगर (err)
		वापस err;

	reg &= ~mask;
	reg |= map & mask;

	err = mv88e6xxx_port_ग_लिखो(chip, port, MV88E6XXX_PORT_BASE_VLAN, reg);
	अगर (err)
		वापस err;

	dev_dbg(chip->dev, "p%d: VLANTable set to %.3x\n", port, map);

	वापस 0;
पूर्ण

पूर्णांक mv88e6xxx_port_get_fid(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, u16 *fid)
अणु
	स्थिर u16 upper_mask = (mv88e6xxx_num_databases(chip) - 1) >> 4;
	u16 reg;
	पूर्णांक err;

	/* Port's शेष FID lower 4 bits are located in reg 0x06, offset 12 */
	err = mv88e6xxx_port_पढ़ो(chip, port, MV88E6XXX_PORT_BASE_VLAN, &reg);
	अगर (err)
		वापस err;

	*fid = (reg & 0xf000) >> 12;

	/* Port's शेष FID upper bits are located in reg 0x05, offset 0 */
	अगर (upper_mask) अणु
		err = mv88e6xxx_port_पढ़ो(chip, port, MV88E6XXX_PORT_CTL1,
					  &reg);
		अगर (err)
			वापस err;

		*fid |= (reg & upper_mask) << 4;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mv88e6xxx_port_set_fid(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, u16 fid)
अणु
	स्थिर u16 upper_mask = (mv88e6xxx_num_databases(chip) - 1) >> 4;
	u16 reg;
	पूर्णांक err;

	अगर (fid >= mv88e6xxx_num_databases(chip))
		वापस -EINVAL;

	/* Port's शेष FID lower 4 bits are located in reg 0x06, offset 12 */
	err = mv88e6xxx_port_पढ़ो(chip, port, MV88E6XXX_PORT_BASE_VLAN, &reg);
	अगर (err)
		वापस err;

	reg &= 0x0fff;
	reg |= (fid & 0x000f) << 12;

	err = mv88e6xxx_port_ग_लिखो(chip, port, MV88E6XXX_PORT_BASE_VLAN, reg);
	अगर (err)
		वापस err;

	/* Port's शेष FID upper bits are located in reg 0x05, offset 0 */
	अगर (upper_mask) अणु
		err = mv88e6xxx_port_पढ़ो(chip, port, MV88E6XXX_PORT_CTL1,
					  &reg);
		अगर (err)
			वापस err;

		reg &= ~upper_mask;
		reg |= (fid >> 4) & upper_mask;

		err = mv88e6xxx_port_ग_लिखो(chip, port, MV88E6XXX_PORT_CTL1,
					   reg);
		अगर (err)
			वापस err;
	पूर्ण

	dev_dbg(chip->dev, "p%d: FID set to %u\n", port, fid);

	वापस 0;
पूर्ण

/* Offset 0x07: Default Port VLAN ID & Priority */

पूर्णांक mv88e6xxx_port_get_pvid(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, u16 *pvid)
अणु
	u16 reg;
	पूर्णांक err;

	err = mv88e6xxx_port_पढ़ो(chip, port, MV88E6XXX_PORT_DEFAULT_VLAN,
				  &reg);
	अगर (err)
		वापस err;

	*pvid = reg & MV88E6XXX_PORT_DEFAULT_VLAN_MASK;

	वापस 0;
पूर्ण

पूर्णांक mv88e6xxx_port_set_pvid(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, u16 pvid)
अणु
	u16 reg;
	पूर्णांक err;

	err = mv88e6xxx_port_पढ़ो(chip, port, MV88E6XXX_PORT_DEFAULT_VLAN,
				  &reg);
	अगर (err)
		वापस err;

	reg &= ~MV88E6XXX_PORT_DEFAULT_VLAN_MASK;
	reg |= pvid & MV88E6XXX_PORT_DEFAULT_VLAN_MASK;

	err = mv88e6xxx_port_ग_लिखो(chip, port, MV88E6XXX_PORT_DEFAULT_VLAN,
				   reg);
	अगर (err)
		वापस err;

	dev_dbg(chip->dev, "p%d: DefaultVID set to %u\n", port, pvid);

	वापस 0;
पूर्ण

/* Offset 0x08: Port Control 2 Register */

अटल स्थिर अक्षर * स्थिर mv88e6xxx_port_8021q_mode_names[] = अणु
	[MV88E6XXX_PORT_CTL2_8021Q_MODE_DISABLED] = "Disabled",
	[MV88E6XXX_PORT_CTL2_8021Q_MODE_FALLBACK] = "Fallback",
	[MV88E6XXX_PORT_CTL2_8021Q_MODE_CHECK] = "Check",
	[MV88E6XXX_PORT_CTL2_8021Q_MODE_SECURE] = "Secure",
पूर्ण;

पूर्णांक mv88e6185_port_set_शेष_क्रमward(काष्ठा mv88e6xxx_chip *chip,
				       पूर्णांक port, bool multicast)
अणु
	पूर्णांक err;
	u16 reg;

	err = mv88e6xxx_port_पढ़ो(chip, port, MV88E6XXX_PORT_CTL2, &reg);
	अगर (err)
		वापस err;

	अगर (multicast)
		reg |= MV88E6XXX_PORT_CTL2_DEFAULT_FORWARD;
	अन्यथा
		reg &= ~MV88E6XXX_PORT_CTL2_DEFAULT_FORWARD;

	वापस mv88e6xxx_port_ग_लिखो(chip, port, MV88E6XXX_PORT_CTL2, reg);
पूर्ण

पूर्णांक mv88e6095_port_set_upstream_port(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				     पूर्णांक upstream_port)
अणु
	पूर्णांक err;
	u16 reg;

	err = mv88e6xxx_port_पढ़ो(chip, port, MV88E6XXX_PORT_CTL2, &reg);
	अगर (err)
		वापस err;

	reg &= ~MV88E6095_PORT_CTL2_CPU_PORT_MASK;
	reg |= upstream_port;

	वापस mv88e6xxx_port_ग_लिखो(chip, port, MV88E6XXX_PORT_CTL2, reg);
पूर्ण

पूर्णांक mv88e6xxx_port_set_mirror(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
			      क्रमागत mv88e6xxx_egress_direction direction,
			      bool mirror)
अणु
	bool *mirror_port;
	u16 reg;
	u16 bit;
	पूर्णांक err;

	err = mv88e6xxx_port_पढ़ो(chip, port, MV88E6XXX_PORT_CTL2, &reg);
	अगर (err)
		वापस err;

	चयन (direction) अणु
	हाल MV88E6XXX_EGRESS_सूची_INGRESS:
		bit = MV88E6XXX_PORT_CTL2_INGRESS_MONITOR;
		mirror_port = &chip->ports[port].mirror_ingress;
		अवरोध;
	हाल MV88E6XXX_EGRESS_सूची_EGRESS:
		bit = MV88E6XXX_PORT_CTL2_EGRESS_MONITOR;
		mirror_port = &chip->ports[port].mirror_egress;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	reg &= ~bit;
	अगर (mirror)
		reg |= bit;

	err = mv88e6xxx_port_ग_लिखो(chip, port, MV88E6XXX_PORT_CTL2, reg);
	अगर (!err)
		*mirror_port = mirror;

	वापस err;
पूर्ण

पूर्णांक mv88e6xxx_port_set_8021q_mode(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				  u16 mode)
अणु
	u16 reg;
	पूर्णांक err;

	err = mv88e6xxx_port_पढ़ो(chip, port, MV88E6XXX_PORT_CTL2, &reg);
	अगर (err)
		वापस err;

	reg &= ~MV88E6XXX_PORT_CTL2_8021Q_MODE_MASK;
	reg |= mode & MV88E6XXX_PORT_CTL2_8021Q_MODE_MASK;

	err = mv88e6xxx_port_ग_लिखो(chip, port, MV88E6XXX_PORT_CTL2, reg);
	अगर (err)
		वापस err;

	dev_dbg(chip->dev, "p%d: 802.1QMode set to %s\n", port,
		mv88e6xxx_port_8021q_mode_names[mode]);

	वापस 0;
पूर्ण

पूर्णांक mv88e6xxx_port_set_map_da(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port)
अणु
	u16 reg;
	पूर्णांक err;

	err = mv88e6xxx_port_पढ़ो(chip, port, MV88E6XXX_PORT_CTL2, &reg);
	अगर (err)
		वापस err;

	reg |= MV88E6XXX_PORT_CTL2_MAP_DA;

	वापस mv88e6xxx_port_ग_लिखो(chip, port, MV88E6XXX_PORT_CTL2, reg);
पूर्ण

पूर्णांक mv88e6165_port_set_jumbo_size(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				  माप_प्रकार size)
अणु
	u16 reg;
	पूर्णांक err;

	err = mv88e6xxx_port_पढ़ो(chip, port, MV88E6XXX_PORT_CTL2, &reg);
	अगर (err)
		वापस err;

	reg &= ~MV88E6XXX_PORT_CTL2_JUMBO_MODE_MASK;

	अगर (size <= 1522)
		reg |= MV88E6XXX_PORT_CTL2_JUMBO_MODE_1522;
	अन्यथा अगर (size <= 2048)
		reg |= MV88E6XXX_PORT_CTL2_JUMBO_MODE_2048;
	अन्यथा अगर (size <= 10240)
		reg |= MV88E6XXX_PORT_CTL2_JUMBO_MODE_10240;
	अन्यथा
		वापस -दुस्फल;

	वापस mv88e6xxx_port_ग_लिखो(chip, port, MV88E6XXX_PORT_CTL2, reg);
पूर्ण

/* Offset 0x09: Port Rate Control */

पूर्णांक mv88e6095_port_egress_rate_limiting(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port)
अणु
	वापस mv88e6xxx_port_ग_लिखो(chip, port, MV88E6XXX_PORT_EGRESS_RATE_CTL1,
				    0x0000);
पूर्ण

पूर्णांक mv88e6097_port_egress_rate_limiting(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port)
अणु
	वापस mv88e6xxx_port_ग_लिखो(chip, port, MV88E6XXX_PORT_EGRESS_RATE_CTL1,
				    0x0001);
पूर्ण

/* Offset 0x0B: Port Association Vector */

पूर्णांक mv88e6xxx_port_set_assoc_vector(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				    u16 pav)
अणु
	u16 reg, mask;
	पूर्णांक err;

	err = mv88e6xxx_port_पढ़ो(chip, port, MV88E6XXX_PORT_ASSOC_VECTOR,
				  &reg);
	अगर (err)
		वापस err;

	mask = mv88e6xxx_port_mask(chip);
	reg &= ~mask;
	reg |= pav & mask;

	वापस mv88e6xxx_port_ग_लिखो(chip, port, MV88E6XXX_PORT_ASSOC_VECTOR,
				    reg);
पूर्ण

/* Offset 0x0C: Port ATU Control */

पूर्णांक mv88e6xxx_port_disable_learn_limit(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port)
अणु
	वापस mv88e6xxx_port_ग_लिखो(chip, port, MV88E6XXX_PORT_ATU_CTL, 0);
पूर्ण

/* Offset 0x0D: (Priority) Override Register */

पूर्णांक mv88e6xxx_port_disable_pri_override(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port)
अणु
	वापस mv88e6xxx_port_ग_लिखो(chip, port, MV88E6XXX_PORT_PRI_OVERRIDE, 0);
पूर्ण

/* Offset 0x0E: Policy & MGMT Control Register क्रम FAMILY 6191X 6193X 6393X */

अटल पूर्णांक mv88e6393x_port_policy_पढ़ो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				       u16 poपूर्णांकer, u8 *data)
अणु
	u16 reg;
	पूर्णांक err;

	err = mv88e6xxx_port_ग_लिखो(chip, port, MV88E6393X_PORT_POLICY_MGMT_CTL,
				   poपूर्णांकer);
	अगर (err)
		वापस err;

	err = mv88e6xxx_port_पढ़ो(chip, port, MV88E6393X_PORT_POLICY_MGMT_CTL,
				  &reg);
	अगर (err)
		वापस err;

	*data = reg;

	वापस 0;
पूर्ण

अटल पूर्णांक mv88e6393x_port_policy_ग_लिखो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
					u16 poपूर्णांकer, u8 data)
अणु
	u16 reg;

	reg = MV88E6393X_PORT_POLICY_MGMT_CTL_UPDATE | poपूर्णांकer | data;

	वापस mv88e6xxx_port_ग_लिखो(chip, port, MV88E6393X_PORT_POLICY_MGMT_CTL,
				    reg);
पूर्ण

अटल पूर्णांक mv88e6393x_port_policy_ग_लिखो_all(काष्ठा mv88e6xxx_chip *chip,
					    u16 poपूर्णांकer, u8 data)
अणु
	पूर्णांक err, port;

	क्रम (port = 0; port < mv88e6xxx_num_ports(chip); port++) अणु
		अगर (dsa_is_unused_port(chip->ds, port))
			जारी;

		err = mv88e6393x_port_policy_ग_लिखो(chip, port, poपूर्णांकer, data);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mv88e6393x_set_egress_port(काष्ठा mv88e6xxx_chip *chip,
			       क्रमागत mv88e6xxx_egress_direction direction,
			       पूर्णांक port)
अणु
	u16 ptr;
	पूर्णांक err;

	चयन (direction) अणु
	हाल MV88E6XXX_EGRESS_सूची_INGRESS:
		ptr = MV88E6393X_PORT_POLICY_MGMT_CTL_PTR_INGRESS_DEST;
		err = mv88e6393x_port_policy_ग_लिखो_all(chip, ptr, port);
		अगर (err)
			वापस err;
		अवरोध;
	हाल MV88E6XXX_EGRESS_सूची_EGRESS:
		ptr = MV88E6393X_G2_EGRESS_MONITOR_DEST;
		err = mv88e6xxx_g2_ग_लिखो(chip, ptr, port);
		अगर (err)
			वापस err;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mv88e6393x_port_set_upstream_port(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				      पूर्णांक upstream_port)
अणु
	u16 ptr = MV88E6393X_PORT_POLICY_MGMT_CTL_PTR_CPU_DEST;
	u8 data = MV88E6393X_PORT_POLICY_MGMT_CTL_CPU_DEST_MGMTPRI |
		  upstream_port;

	वापस mv88e6393x_port_policy_ग_लिखो(chip, port, ptr, data);
पूर्ण

पूर्णांक mv88e6393x_port_mgmt_rsvd2cpu(काष्ठा mv88e6xxx_chip *chip)
अणु
	u16 ptr;
	पूर्णांक err;

	/* Consider the frames with reserved multicast destination
	 * addresses matching 01:80:c2:00:00:00 and
	 * 01:80:c2:00:00:02 as MGMT.
	 */
	ptr = MV88E6393X_PORT_POLICY_MGMT_CTL_PTR_01C280000000XLO;
	err = mv88e6393x_port_policy_ग_लिखो_all(chip, ptr, 0xff);
	अगर (err)
		वापस err;

	ptr = MV88E6393X_PORT_POLICY_MGMT_CTL_PTR_01C280000000XHI;
	err = mv88e6393x_port_policy_ग_लिखो_all(chip, ptr, 0xff);
	अगर (err)
		वापस err;

	ptr = MV88E6393X_PORT_POLICY_MGMT_CTL_PTR_01C280000002XLO;
	err = mv88e6393x_port_policy_ग_लिखो_all(chip, ptr, 0xff);
	अगर (err)
		वापस err;

	ptr = MV88E6393X_PORT_POLICY_MGMT_CTL_PTR_01C280000002XHI;
	err = mv88e6393x_port_policy_ग_लिखो_all(chip, ptr, 0xff);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

/* Offset 0x10 & 0x11: EPC */

अटल पूर्णांक mv88e6393x_port_epc_रुको_पढ़ोy(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port)
अणु
	पूर्णांक bit = __bf_shf(MV88E6393X_PORT_EPC_CMD_BUSY);

	वापस mv88e6xxx_port_रुको_bit(chip, port, MV88E6393X_PORT_EPC_CMD, bit, 0);
पूर्ण

/* Port Ether type क्रम 6393X family */

पूर्णांक mv88e6393x_port_set_ether_type(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				   u16 etype)
अणु
	u16 val;
	पूर्णांक err;

	err = mv88e6393x_port_epc_रुको_पढ़ोy(chip, port);
	अगर (err)
		वापस err;

	err = mv88e6xxx_port_ग_लिखो(chip, port, MV88E6393X_PORT_EPC_DATA, etype);
	अगर (err)
		वापस err;

	val = MV88E6393X_PORT_EPC_CMD_BUSY |
	      MV88E6393X_PORT_EPC_CMD_WRITE |
	      MV88E6393X_PORT_EPC_INDEX_PORT_ETYPE;

	वापस mv88e6xxx_port_ग_लिखो(chip, port, MV88E6393X_PORT_EPC_CMD, val);
पूर्ण

/* Offset 0x0f: Port Ether type */

पूर्णांक mv88e6351_port_set_ether_type(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				  u16 etype)
अणु
	वापस mv88e6xxx_port_ग_लिखो(chip, port, MV88E6XXX_PORT_ETH_TYPE, etype);
पूर्ण

/* Offset 0x18: Port IEEE Priority Remapping Registers [0-3]
 * Offset 0x19: Port IEEE Priority Remapping Registers [4-7]
 */

पूर्णांक mv88e6095_port_tag_remap(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port)
अणु
	पूर्णांक err;

	/* Use a direct priority mapping क्रम all IEEE tagged frames */
	err = mv88e6xxx_port_ग_लिखो(chip, port,
				   MV88E6095_PORT_IEEE_PRIO_REMAP_0123,
				   0x3210);
	अगर (err)
		वापस err;

	वापस mv88e6xxx_port_ग_लिखो(chip, port,
				    MV88E6095_PORT_IEEE_PRIO_REMAP_4567,
				    0x7654);
पूर्ण

अटल पूर्णांक mv88e6xxx_port_ieeepmt_ग_लिखो(काष्ठा mv88e6xxx_chip *chip,
					पूर्णांक port, u16 table, u8 ptr, u16 data)
अणु
	u16 reg;

	reg = MV88E6390_PORT_IEEE_PRIO_MAP_TABLE_UPDATE | table |
		(ptr << __bf_shf(MV88E6390_PORT_IEEE_PRIO_MAP_TABLE_PTR_MASK)) |
		(data & MV88E6390_PORT_IEEE_PRIO_MAP_TABLE_DATA_MASK);

	वापस mv88e6xxx_port_ग_लिखो(chip, port,
				    MV88E6390_PORT_IEEE_PRIO_MAP_TABLE, reg);
पूर्ण

पूर्णांक mv88e6390_port_tag_remap(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port)
अणु
	पूर्णांक err, i;
	u16 table;

	क्रम (i = 0; i <= 7; i++) अणु
		table = MV88E6390_PORT_IEEE_PRIO_MAP_TABLE_INGRESS_PCP;
		err = mv88e6xxx_port_ieeepmt_ग_लिखो(chip, port, table, i,
						   (i | i << 4));
		अगर (err)
			वापस err;

		table = MV88E6390_PORT_IEEE_PRIO_MAP_TABLE_EGRESS_GREEN_PCP;
		err = mv88e6xxx_port_ieeepmt_ग_लिखो(chip, port, table, i, i);
		अगर (err)
			वापस err;

		table = MV88E6390_PORT_IEEE_PRIO_MAP_TABLE_EGRESS_YELLOW_PCP;
		err = mv88e6xxx_port_ieeepmt_ग_लिखो(chip, port, table, i, i);
		अगर (err)
			वापस err;

		table = MV88E6390_PORT_IEEE_PRIO_MAP_TABLE_EGRESS_AVB_PCP;
		err = mv88e6xxx_port_ieeepmt_ग_लिखो(chip, port, table, i, i);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/* Offset 0x0E: Policy Control Register */

अटल पूर्णांक
mv88e6xxx_port_policy_mapping_get_pos(क्रमागत mv88e6xxx_policy_mapping mapping,
				      क्रमागत mv88e6xxx_policy_action action,
				      u16 *mask, u16 *val, पूर्णांक *shअगरt)
अणु
	चयन (mapping) अणु
	हाल MV88E6XXX_POLICY_MAPPING_DA:
		*shअगरt = __bf_shf(MV88E6XXX_PORT_POLICY_CTL_DA_MASK);
		*mask = MV88E6XXX_PORT_POLICY_CTL_DA_MASK;
		अवरोध;
	हाल MV88E6XXX_POLICY_MAPPING_SA:
		*shअगरt = __bf_shf(MV88E6XXX_PORT_POLICY_CTL_SA_MASK);
		*mask = MV88E6XXX_PORT_POLICY_CTL_SA_MASK;
		अवरोध;
	हाल MV88E6XXX_POLICY_MAPPING_VTU:
		*shअगरt = __bf_shf(MV88E6XXX_PORT_POLICY_CTL_VTU_MASK);
		*mask = MV88E6XXX_PORT_POLICY_CTL_VTU_MASK;
		अवरोध;
	हाल MV88E6XXX_POLICY_MAPPING_ETYPE:
		*shअगरt = __bf_shf(MV88E6XXX_PORT_POLICY_CTL_ETYPE_MASK);
		*mask = MV88E6XXX_PORT_POLICY_CTL_ETYPE_MASK;
		अवरोध;
	हाल MV88E6XXX_POLICY_MAPPING_PPPOE:
		*shअगरt = __bf_shf(MV88E6XXX_PORT_POLICY_CTL_PPPOE_MASK);
		*mask = MV88E6XXX_PORT_POLICY_CTL_PPPOE_MASK;
		अवरोध;
	हाल MV88E6XXX_POLICY_MAPPING_VBAS:
		*shअगरt = __bf_shf(MV88E6XXX_PORT_POLICY_CTL_VBAS_MASK);
		*mask = MV88E6XXX_PORT_POLICY_CTL_VBAS_MASK;
		अवरोध;
	हाल MV88E6XXX_POLICY_MAPPING_OPT82:
		*shअगरt = __bf_shf(MV88E6XXX_PORT_POLICY_CTL_OPT82_MASK);
		*mask = MV88E6XXX_PORT_POLICY_CTL_OPT82_MASK;
		अवरोध;
	हाल MV88E6XXX_POLICY_MAPPING_UDP:
		*shअगरt = __bf_shf(MV88E6XXX_PORT_POLICY_CTL_UDP_MASK);
		*mask = MV88E6XXX_PORT_POLICY_CTL_UDP_MASK;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	चयन (action) अणु
	हाल MV88E6XXX_POLICY_ACTION_NORMAL:
		*val = MV88E6XXX_PORT_POLICY_CTL_NORMAL;
		अवरोध;
	हाल MV88E6XXX_POLICY_ACTION_MIRROR:
		*val = MV88E6XXX_PORT_POLICY_CTL_MIRROR;
		अवरोध;
	हाल MV88E6XXX_POLICY_ACTION_TRAP:
		*val = MV88E6XXX_PORT_POLICY_CTL_TRAP;
		अवरोध;
	हाल MV88E6XXX_POLICY_ACTION_DISCARD:
		*val = MV88E6XXX_PORT_POLICY_CTL_DISCARD;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mv88e6352_port_set_policy(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
			      क्रमागत mv88e6xxx_policy_mapping mapping,
			      क्रमागत mv88e6xxx_policy_action action)
अणु
	u16 reg, mask, val;
	पूर्णांक shअगरt;
	पूर्णांक err;

	err = mv88e6xxx_port_policy_mapping_get_pos(mapping, action, &mask,
						    &val, &shअगरt);
	अगर (err)
		वापस err;

	err = mv88e6xxx_port_पढ़ो(chip, port, MV88E6XXX_PORT_POLICY_CTL, &reg);
	अगर (err)
		वापस err;

	reg &= ~mask;
	reg |= (val << shअगरt) & mask;

	वापस mv88e6xxx_port_ग_लिखो(chip, port, MV88E6XXX_PORT_POLICY_CTL, reg);
पूर्ण

पूर्णांक mv88e6393x_port_set_policy(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
			       क्रमागत mv88e6xxx_policy_mapping mapping,
			       क्रमागत mv88e6xxx_policy_action action)
अणु
	u16 mask, val;
	पूर्णांक shअगरt;
	पूर्णांक err;
	u16 ptr;
	u8 reg;

	err = mv88e6xxx_port_policy_mapping_get_pos(mapping, action, &mask,
						    &val, &shअगरt);
	अगर (err)
		वापस err;

	/* The 16-bit Port Policy CTL रेजिस्टर from older chips is on 6393x
	 * changed to Port Policy MGMT CTL, which can access more data, but
	 * indirectly. The original 16-bit value is भागided पूर्णांकo two 8-bit
	 * रेजिस्टरs.
	 */
	ptr = shअगरt / 8;
	shअगरt %= 8;
	mask >>= ptr * 8;

	err = mv88e6393x_port_policy_पढ़ो(chip, port, ptr, &reg);
	अगर (err)
		वापस err;

	reg &= ~mask;
	reg |= (val << shअगरt) & mask;

	वापस mv88e6393x_port_policy_ग_लिखो(chip, port, ptr, reg);
पूर्ण
