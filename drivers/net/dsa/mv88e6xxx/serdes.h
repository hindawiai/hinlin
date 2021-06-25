<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Marvell 88E6xxx SERDES manipulation, via SMI bus
 *
 * Copyright (c) 2008 Marvell Semiconductor
 *
 * Copyright (c) 2016 Andrew Lunn <andrew@lunn.ch>
 */

#अगर_अघोषित _MV88E6XXX_SERDES_H
#घोषणा _MV88E6XXX_SERDES_H

#समावेश "chip.h"

#घोषणा MV88E6352_ADDR_SERDES		0x0f
#घोषणा MV88E6352_SERDES_PAGE_FIBER	0x01
#घोषणा MV88E6352_SERDES_IRQ		0x0b
#घोषणा MV88E6352_SERDES_INT_ENABLE	0x12
#घोषणा MV88E6352_SERDES_INT_SPEED_CHANGE	BIT(14)
#घोषणा MV88E6352_SERDES_INT_DUPLEX_CHANGE	BIT(13)
#घोषणा MV88E6352_SERDES_INT_PAGE_RX		BIT(12)
#घोषणा MV88E6352_SERDES_INT_AN_COMPLETE	BIT(11)
#घोषणा MV88E6352_SERDES_INT_LINK_CHANGE	BIT(10)
#घोषणा MV88E6352_SERDES_INT_SYMBOL_ERROR	BIT(9)
#घोषणा MV88E6352_SERDES_INT_FALSE_CARRIER	BIT(8)
#घोषणा MV88E6352_SERDES_INT_FIFO_OVER_UNDER	BIT(7)
#घोषणा MV88E6352_SERDES_INT_FIBRE_ENERGY	BIT(4)
#घोषणा MV88E6352_SERDES_INT_STATUS	0x13


#घोषणा MV88E6341_PORT5_LANE		0x15

#घोषणा MV88E6390_PORT9_LANE0		0x09
#घोषणा MV88E6390_PORT9_LANE1		0x12
#घोषणा MV88E6390_PORT9_LANE2		0x13
#घोषणा MV88E6390_PORT9_LANE3		0x14
#घोषणा MV88E6390_PORT10_LANE0		0x0a
#घोषणा MV88E6390_PORT10_LANE1		0x15
#घोषणा MV88E6390_PORT10_LANE2		0x16
#घोषणा MV88E6390_PORT10_LANE3		0x17

/* 10GBASE-R and 10GBASE-X4/X2 */
#घोषणा MV88E6390_10G_CTRL1		(0x1000 + MDIO_CTRL1)
#घोषणा MV88E6390_10G_STAT1		(0x1000 + MDIO_STAT1)
#घोषणा MV88E6393X_10G_INT_ENABLE	0x9000
#घोषणा MV88E6393X_10G_INT_LINK_CHANGE	BIT(2)
#घोषणा MV88E6393X_10G_INT_STATUS	0x9001

/* 1000BASE-X and SGMII */
#घोषणा MV88E6390_SGMII_BMCR		(0x2000 + MII_BMCR)
#घोषणा MV88E6390_SGMII_BMSR		(0x2000 + MII_BMSR)
#घोषणा MV88E6390_SGMII_ADVERTISE	(0x2000 + MII_ADVERTISE)
#घोषणा MV88E6390_SGMII_LPA		(0x2000 + MII_LPA)
#घोषणा MV88E6390_SGMII_INT_ENABLE	0xa001
#घोषणा MV88E6390_SGMII_INT_SPEED_CHANGE	BIT(14)
#घोषणा MV88E6390_SGMII_INT_DUPLEX_CHANGE	BIT(13)
#घोषणा MV88E6390_SGMII_INT_PAGE_RX		BIT(12)
#घोषणा MV88E6390_SGMII_INT_AN_COMPLETE		BIT(11)
#घोषणा MV88E6390_SGMII_INT_LINK_DOWN		BIT(10)
#घोषणा MV88E6390_SGMII_INT_LINK_UP		BIT(9)
#घोषणा MV88E6390_SGMII_INT_SYMBOL_ERROR	BIT(8)
#घोषणा MV88E6390_SGMII_INT_FALSE_CARRIER	BIT(7)
#घोषणा MV88E6390_SGMII_INT_STATUS	0xa002
#घोषणा MV88E6390_SGMII_PHY_STATUS	0xa003
#घोषणा MV88E6390_SGMII_PHY_STATUS_SPEED_MASK	GENMASK(15, 14)
#घोषणा MV88E6390_SGMII_PHY_STATUS_SPEED_1000	0x8000
#घोषणा MV88E6390_SGMII_PHY_STATUS_SPEED_100	0x4000
#घोषणा MV88E6390_SGMII_PHY_STATUS_SPEED_10	0x0000
#घोषणा MV88E6390_SGMII_PHY_STATUS_DUPLEX_FULL	BIT(13)
#घोषणा MV88E6390_SGMII_PHY_STATUS_SPD_DPL_VALID BIT(11)
#घोषणा MV88E6390_SGMII_PHY_STATUS_LINK		BIT(10)
#घोषणा MV88E6390_SGMII_PHY_STATUS_TX_PAUSE	BIT(3)
#घोषणा MV88E6390_SGMII_PHY_STATUS_RX_PAUSE	BIT(2)

/* Packet generator pad packet checker */
#घोषणा MV88E6390_PG_CONTROL		0xf010
#घोषणा MV88E6390_PG_CONTROL_ENABLE_PC		BIT(0)

#घोषणा MV88E6393X_PORT0_LANE			0x00
#घोषणा MV88E6393X_PORT9_LANE			0x09
#घोषणा MV88E6393X_PORT10_LANE			0x0a

/* Port Operational Configuration */
#घोषणा MV88E6393X_SERDES_POC			0xf002
#घोषणा MV88E6393X_SERDES_POC_PCS_1000BASEX	0x0000
#घोषणा MV88E6393X_SERDES_POC_PCS_2500BASEX	0x0001
#घोषणा MV88E6393X_SERDES_POC_PCS_SGMII_PHY	0x0002
#घोषणा MV88E6393X_SERDES_POC_PCS_SGMII_MAC	0x0003
#घोषणा MV88E6393X_SERDES_POC_PCS_5GBASER	0x0004
#घोषणा MV88E6393X_SERDES_POC_PCS_10GBASER	0x0005
#घोषणा MV88E6393X_SERDES_POC_PCS_USXGMII_PHY	0x0006
#घोषणा MV88E6393X_SERDES_POC_PCS_USXGMII_MAC	0x0007
#घोषणा MV88E6393X_SERDES_POC_PCS_MASK		0x0007
#घोषणा MV88E6393X_SERDES_POC_RESET		BIT(15)
#घोषणा MV88E6393X_SERDES_POC_PDOWN		BIT(5)

#घोषणा MV88E6393X_ERRATA_4_8_REG		0xF074
#घोषणा MV88E6393X_ERRATA_4_8_BIT		BIT(14)

पूर्णांक mv88e6185_serdes_get_lane(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port);
पूर्णांक mv88e6341_serdes_get_lane(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port);
पूर्णांक mv88e6352_serdes_get_lane(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port);
पूर्णांक mv88e6390_serdes_get_lane(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port);
पूर्णांक mv88e6390x_serdes_get_lane(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port);
पूर्णांक mv88e6393x_serdes_get_lane(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port);
पूर्णांक mv88e6352_serdes_pcs_config(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				पूर्णांक lane, अचिन्हित पूर्णांक mode,
				phy_पूर्णांकerface_t पूर्णांकerface,
				स्थिर अचिन्हित दीर्घ *advertise);
पूर्णांक mv88e6390_serdes_pcs_config(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				पूर्णांक lane, अचिन्हित पूर्णांक mode,
				phy_पूर्णांकerface_t पूर्णांकerface,
				स्थिर अचिन्हित दीर्घ *advertise);
पूर्णांक mv88e6185_serdes_pcs_get_state(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				   पूर्णांक lane, काष्ठा phylink_link_state *state);
पूर्णांक mv88e6352_serdes_pcs_get_state(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				   पूर्णांक lane, काष्ठा phylink_link_state *state);
पूर्णांक mv88e6390_serdes_pcs_get_state(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				   पूर्णांक lane, काष्ठा phylink_link_state *state);
पूर्णांक mv88e6393x_serdes_pcs_get_state(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				    पूर्णांक lane, काष्ठा phylink_link_state *state);
पूर्णांक mv88e6352_serdes_pcs_an_restart(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				    पूर्णांक lane);
पूर्णांक mv88e6390_serdes_pcs_an_restart(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				    पूर्णांक lane);
पूर्णांक mv88e6352_serdes_pcs_link_up(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				 पूर्णांक lane, पूर्णांक speed, पूर्णांक duplex);
पूर्णांक mv88e6390_serdes_pcs_link_up(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				 पूर्णांक lane, पूर्णांक speed, पूर्णांक duplex);
अचिन्हित पूर्णांक mv88e6352_serdes_irq_mapping(काष्ठा mv88e6xxx_chip *chip,
					  पूर्णांक port);
अचिन्हित पूर्णांक mv88e6390_serdes_irq_mapping(काष्ठा mv88e6xxx_chip *chip,
					  पूर्णांक port);
पूर्णांक mv88e6185_serdes_घातer(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, पूर्णांक lane,
			   bool up);
पूर्णांक mv88e6352_serdes_घातer(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, पूर्णांक lane,
			   bool on);
पूर्णांक mv88e6390_serdes_घातer(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, पूर्णांक lane,
			   bool on);
पूर्णांक mv88e6393x_serdes_घातer(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, पूर्णांक lane,
			    bool on);
पूर्णांक mv88e6393x_serdes_setup_errata(काष्ठा mv88e6xxx_chip *chip);
पूर्णांक mv88e6097_serdes_irq_enable(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, पूर्णांक lane,
				bool enable);
पूर्णांक mv88e6352_serdes_irq_enable(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, पूर्णांक lane,
				bool enable);
पूर्णांक mv88e6390_serdes_irq_enable(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, पूर्णांक lane,
				bool enable);
पूर्णांक mv88e6393x_serdes_irq_enable(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
				 पूर्णांक lane, bool enable);
irqवापस_t mv88e6097_serdes_irq_status(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
					पूर्णांक lane);
irqवापस_t mv88e6352_serdes_irq_status(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
					पूर्णांक lane);
irqवापस_t mv88e6390_serdes_irq_status(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
					पूर्णांक lane);
irqवापस_t mv88e6393x_serdes_irq_status(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
					 पूर्णांक lane);
पूर्णांक mv88e6352_serdes_get_sset_count(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port);
पूर्णांक mv88e6352_serdes_get_strings(काष्ठा mv88e6xxx_chip *chip,
				 पूर्णांक port, uपूर्णांक8_t *data);
पूर्णांक mv88e6352_serdes_get_stats(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
			       uपूर्णांक64_t *data);
पूर्णांक mv88e6390_serdes_get_sset_count(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port);
पूर्णांक mv88e6390_serdes_get_strings(काष्ठा mv88e6xxx_chip *chip,
				 पूर्णांक port, uपूर्णांक8_t *data);
पूर्णांक mv88e6390_serdes_get_stats(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port,
			       uपूर्णांक64_t *data);

पूर्णांक mv88e6352_serdes_get_regs_len(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port);
व्योम mv88e6352_serdes_get_regs(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, व्योम *_p);
पूर्णांक mv88e6390_serdes_get_regs_len(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port);
व्योम mv88e6390_serdes_get_regs(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, व्योम *_p);

/* Return the (first) SERDES lane address a port is using, -त्रुटि_सं otherwise. */
अटल अंतरभूत पूर्णांक mv88e6xxx_serdes_get_lane(काष्ठा mv88e6xxx_chip *chip,
					    पूर्णांक port)
अणु
	अगर (!chip->info->ops->serdes_get_lane)
		वापस -EOPNOTSUPP;

	वापस chip->info->ops->serdes_get_lane(chip, port);
पूर्ण

अटल अंतरभूत पूर्णांक mv88e6xxx_serdes_घातer_up(काष्ठा mv88e6xxx_chip *chip,
					    पूर्णांक port, पूर्णांक lane)
अणु
	अगर (!chip->info->ops->serdes_घातer)
		वापस -EOPNOTSUPP;

	वापस chip->info->ops->serdes_घातer(chip, port, lane, true);
पूर्ण

अटल अंतरभूत पूर्णांक mv88e6xxx_serdes_घातer_करोwn(काष्ठा mv88e6xxx_chip *chip,
					      पूर्णांक port, पूर्णांक lane)
अणु
	अगर (!chip->info->ops->serdes_घातer)
		वापस -EOPNOTSUPP;

	वापस chip->info->ops->serdes_घातer(chip, port, lane, false);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
mv88e6xxx_serdes_irq_mapping(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port)
अणु
	अगर (!chip->info->ops->serdes_irq_mapping)
		वापस 0;

	वापस chip->info->ops->serdes_irq_mapping(chip, port);
पूर्ण

अटल अंतरभूत पूर्णांक mv88e6xxx_serdes_irq_enable(काष्ठा mv88e6xxx_chip *chip,
					      पूर्णांक port, पूर्णांक lane)
अणु
	अगर (!chip->info->ops->serdes_irq_enable)
		वापस -EOPNOTSUPP;

	वापस chip->info->ops->serdes_irq_enable(chip, port, lane, true);
पूर्ण

अटल अंतरभूत पूर्णांक mv88e6xxx_serdes_irq_disable(काष्ठा mv88e6xxx_chip *chip,
					       पूर्णांक port, पूर्णांक lane)
अणु
	अगर (!chip->info->ops->serdes_irq_enable)
		वापस -EOPNOTSUPP;

	वापस chip->info->ops->serdes_irq_enable(chip, port, lane, false);
पूर्ण

अटल अंतरभूत irqवापस_t
mv88e6xxx_serdes_irq_status(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port, पूर्णांक lane)
अणु
	अगर (!chip->info->ops->serdes_irq_status)
		वापस IRQ_NONE;

	वापस chip->info->ops->serdes_irq_status(chip, port, lane);
पूर्ण

#पूर्ण_अगर
