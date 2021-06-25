<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Marvell 88E6xxx PHY access
 *
 * Copyright (c) 2008 Marvell Semiconductor
 *
 * Copyright (c) 2017 Andrew Lunn <andrew@lunn.ch>
 */

#अगर_अघोषित _MV88E6XXX_PHY_H
#घोषणा _MV88E6XXX_PHY_H

#घोषणा MV88E6XXX_PHY_PAGE		0x16
#घोषणा MV88E6XXX_PHY_PAGE_COPPER	0x00

/* PHY Registers accesses implementations */
पूर्णांक mv88e6165_phy_पढ़ो(काष्ठा mv88e6xxx_chip *chip, काष्ठा mii_bus *bus,
		       पूर्णांक addr, पूर्णांक reg, u16 *val);
पूर्णांक mv88e6165_phy_ग_लिखो(काष्ठा mv88e6xxx_chip *chip, काष्ठा mii_bus *bus,
			पूर्णांक addr, पूर्णांक reg, u16 val);
पूर्णांक mv88e6185_phy_ppu_पढ़ो(काष्ठा mv88e6xxx_chip *chip, काष्ठा mii_bus *bus,
			   पूर्णांक addr, पूर्णांक reg, u16 *val);
पूर्णांक mv88e6185_phy_ppu_ग_लिखो(काष्ठा mv88e6xxx_chip *chip, काष्ठा mii_bus *bus,
			    पूर्णांक addr, पूर्णांक reg, u16 val);

/* Generic PHY operations */
पूर्णांक mv88e6xxx_phy_पढ़ो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक phy,
		       पूर्णांक reg, u16 *val);
पूर्णांक mv88e6xxx_phy_ग_लिखो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक phy,
			पूर्णांक reg, u16 val);
पूर्णांक mv88e6xxx_phy_page_पढ़ो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक phy,
			    u8 page, पूर्णांक reg, u16 *val);
पूर्णांक mv88e6xxx_phy_page_ग_लिखो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक phy,
			     u8 page, पूर्णांक reg, u16 val);
व्योम mv88e6xxx_phy_init(काष्ठा mv88e6xxx_chip *chip);
व्योम mv88e6xxx_phy_destroy(काष्ठा mv88e6xxx_chip *chip);
पूर्णांक mv88e6xxx_phy_setup(काष्ठा mv88e6xxx_chip *chip);

#पूर्ण_अगर /*_MV88E6XXX_PHY_H */
