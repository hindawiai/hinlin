<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2013-2016, The Linux Foundation. All rights reserved.
 */

/* Qualcomm Technologies, Inc. EMAC PHY Controller driver.
 */

#समावेश <linux/of_mdपन.स>
#समावेश <linux/phy.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/acpi.h>
#समावेश "emac.h"

/* EMAC base रेजिस्टर offsets */
#घोषणा EMAC_MDIO_CTRL                                        0x001414
#घोषणा EMAC_PHY_STS                                          0x001418
#घोषणा EMAC_MDIO_EX_CTRL                                     0x001440

/* EMAC_MDIO_CTRL */
#घोषणा MDIO_MODE                                              BIT(30)
#घोषणा MDIO_PR                                                BIT(29)
#घोषणा MDIO_AP_EN                                             BIT(28)
#घोषणा MDIO_BUSY                                              BIT(27)
#घोषणा MDIO_CLK_SEL_BMSK                                    0x7000000
#घोषणा MDIO_CLK_SEL_SHFT                                           24
#घोषणा MDIO_START                                             BIT(23)
#घोषणा SUP_PREAMBLE                                           BIT(22)
#घोषणा MDIO_RD_NWR                                            BIT(21)
#घोषणा MDIO_REG_ADDR_BMSK                                    0x1f0000
#घोषणा MDIO_REG_ADDR_SHFT                                          16
#घोषणा MDIO_DATA_BMSK                                          0xffff
#घोषणा MDIO_DATA_SHFT                                               0

/* EMAC_PHY_STS */
#घोषणा PHY_ADDR_BMSK                                         0x1f0000
#घोषणा PHY_ADDR_SHFT                                               16

#घोषणा MDIO_CLK_25_4                                                0
#घोषणा MDIO_CLK_25_28                                               7

#घोषणा MDIO_WAIT_TIMES                                           1000
#घोषणा MDIO_STATUS_DELAY_TIME                                       1

अटल पूर्णांक emac_mdio_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक addr, पूर्णांक regnum)
अणु
	काष्ठा emac_adapter *adpt = bus->priv;
	u32 reg;

	emac_reg_update32(adpt->base + EMAC_PHY_STS, PHY_ADDR_BMSK,
			  (addr << PHY_ADDR_SHFT));

	reg = SUP_PREAMBLE |
	      ((MDIO_CLK_25_4 << MDIO_CLK_SEL_SHFT) & MDIO_CLK_SEL_BMSK) |
	      ((regnum << MDIO_REG_ADDR_SHFT) & MDIO_REG_ADDR_BMSK) |
	      MDIO_START | MDIO_RD_NWR;

	ग_लिखोl(reg, adpt->base + EMAC_MDIO_CTRL);

	अगर (पढ़ोl_poll_समयout(adpt->base + EMAC_MDIO_CTRL, reg,
			       !(reg & (MDIO_START | MDIO_BUSY)),
			       MDIO_STATUS_DELAY_TIME, MDIO_WAIT_TIMES * 100))
		वापस -EIO;

	वापस (reg >> MDIO_DATA_SHFT) & MDIO_DATA_BMSK;
पूर्ण

अटल पूर्णांक emac_mdio_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक addr, पूर्णांक regnum, u16 val)
अणु
	काष्ठा emac_adapter *adpt = bus->priv;
	u32 reg;

	emac_reg_update32(adpt->base + EMAC_PHY_STS, PHY_ADDR_BMSK,
			  (addr << PHY_ADDR_SHFT));

	reg = SUP_PREAMBLE |
		((MDIO_CLK_25_4 << MDIO_CLK_SEL_SHFT) & MDIO_CLK_SEL_BMSK) |
		((regnum << MDIO_REG_ADDR_SHFT) & MDIO_REG_ADDR_BMSK) |
		((val << MDIO_DATA_SHFT) & MDIO_DATA_BMSK) |
		MDIO_START;

	ग_लिखोl(reg, adpt->base + EMAC_MDIO_CTRL);

	अगर (पढ़ोl_poll_समयout(adpt->base + EMAC_MDIO_CTRL, reg,
			       !(reg & (MDIO_START | MDIO_BUSY)),
			       MDIO_STATUS_DELAY_TIME, MDIO_WAIT_TIMES * 100))
		वापस -EIO;

	वापस 0;
पूर्ण

/* Configure the MDIO bus and connect the बाह्यal PHY */
पूर्णांक emac_phy_config(काष्ठा platक्रमm_device *pdev, काष्ठा emac_adapter *adpt)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा mii_bus *mii_bus;
	पूर्णांक ret;

	/* Create the mii_bus object क्रम talking to the MDIO bus */
	adpt->mii_bus = mii_bus = devm_mdiobus_alloc(&pdev->dev);
	अगर (!mii_bus)
		वापस -ENOMEM;

	mii_bus->name = "emac-mdio";
	snम_लिखो(mii_bus->id, MII_BUS_ID_SIZE, "%s", pdev->name);
	mii_bus->पढ़ो = emac_mdio_पढ़ो;
	mii_bus->ग_लिखो = emac_mdio_ग_लिखो;
	mii_bus->parent = &pdev->dev;
	mii_bus->priv = adpt;

	अगर (has_acpi_companion(&pdev->dev)) अणु
		u32 phy_addr;

		ret = mdiobus_रेजिस्टर(mii_bus);
		अगर (ret) अणु
			dev_err(&pdev->dev, "could not register mdio bus\n");
			वापस ret;
		पूर्ण
		ret = device_property_पढ़ो_u32(&pdev->dev, "phy-channel",
					       &phy_addr);
		अगर (ret)
			/* If we can't पढ़ो a valid phy address, then assume
			 * that there is only one phy on this mdio bus.
			 */
			adpt->phydev = phy_find_first(mii_bus);
		अन्यथा
			adpt->phydev = mdiobus_get_phy(mii_bus, phy_addr);

		/* of_phy_find_device() claims a reference to the phydev,
		 * so we करो that here manually as well. When the driver
		 * later unloads, it can unilaterally drop the reference
		 * without worrying about ACPI vs DT.
		 */
		अगर (adpt->phydev)
			get_device(&adpt->phydev->mdio.dev);
	पूर्ण अन्यथा अणु
		काष्ठा device_node *phy_np;

		ret = of_mdiobus_रेजिस्टर(mii_bus, np);
		अगर (ret) अणु
			dev_err(&pdev->dev, "could not register mdio bus\n");
			वापस ret;
		पूर्ण

		phy_np = of_parse_phandle(np, "phy-handle", 0);
		adpt->phydev = of_phy_find_device(phy_np);
		of_node_put(phy_np);
	पूर्ण

	अगर (!adpt->phydev) अणु
		dev_err(&pdev->dev, "could not find external phy\n");
		mdiobus_unरेजिस्टर(mii_bus);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण
