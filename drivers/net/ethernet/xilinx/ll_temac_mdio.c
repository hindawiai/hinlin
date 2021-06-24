<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * MDIO bus driver क्रम the Xilinx TEMAC device
 *
 * Copyright (c) 2009 Secret Lab Technologies, Ltd.
 */

#समावेश <linux/पन.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/mutex.h>
#समावेश <linux/phy.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/platक्रमm_data/xilinx-ll-temac.h>

#समावेश "ll_temac.h"

/* ---------------------------------------------------------------------
 * MDIO Bus functions
 */
अटल पूर्णांक temac_mdio_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक reg)
अणु
	काष्ठा temac_local *lp = bus->priv;
	u32 rc;
	अचिन्हित दीर्घ flags;

	/* Write the PHY address to the MIIM Access Initiator रेजिस्टर.
	 * When the transfer completes, the PHY रेजिस्टर value will appear
	 * in the LSW0 रेजिस्टर */
	spin_lock_irqsave(lp->indirect_lock, flags);
	temac_iow(lp, XTE_LSW0_OFFSET, (phy_id << 5) | reg);
	rc = temac_indirect_in32_locked(lp, XTE_MIIMAI_OFFSET);
	spin_unlock_irqrestore(lp->indirect_lock, flags);

	dev_dbg(lp->dev, "temac_mdio_read(phy_id=%i, reg=%x) == %x\n",
		phy_id, reg, rc);

	वापस rc;
पूर्ण

अटल पूर्णांक temac_mdio_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक reg, u16 val)
अणु
	काष्ठा temac_local *lp = bus->priv;
	अचिन्हित दीर्घ flags;

	dev_dbg(lp->dev, "temac_mdio_write(phy_id=%i, reg=%x, val=%x)\n",
		phy_id, reg, val);

	/* First ग_लिखो the desired value पूर्णांकo the ग_लिखो data रेजिस्टर
	 * and then ग_लिखो the address पूर्णांकo the access initiator रेजिस्टर
	 */
	spin_lock_irqsave(lp->indirect_lock, flags);
	temac_indirect_out32_locked(lp, XTE_MGTDR_OFFSET, val);
	temac_indirect_out32_locked(lp, XTE_MIIMAI_OFFSET, (phy_id << 5) | reg);
	spin_unlock_irqrestore(lp->indirect_lock, flags);

	वापस 0;
पूर्ण

पूर्णांक temac_mdio_setup(काष्ठा temac_local *lp, काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ll_temac_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा device_node *np = dev_of_node(&pdev->dev);
	काष्ठा mii_bus *bus;
	u32 bus_hz;
	पूर्णांक clk_भाग;
	पूर्णांक rc;
	काष्ठा resource res;

	/* Get MDIO bus frequency (अगर specअगरied) */
	bus_hz = 0;
	अगर (np)
		of_property_पढ़ो_u32(np, "clock-frequency", &bus_hz);
	अन्यथा अगर (pdata)
		bus_hz = pdata->mdio_clk_freq;

	/* Calculate a reasonable भागisor क्रम the घड़ी rate */
	clk_भाग = 0x3f; /* worst-हाल शेष setting */
	अगर (bus_hz != 0) अणु
		clk_भाग = bus_hz / (2500 * 1000 * 2) - 1;
		अगर (clk_भाग < 1)
			clk_भाग = 1;
		अगर (clk_भाग > 0x3f)
			clk_भाग = 0x3f;
	पूर्ण

	/* Enable the MDIO bus by निश्चितing the enable bit and writing
	 * in the घड़ी config */
	temac_indirect_out32(lp, XTE_MC_OFFSET, 1 << 6 | clk_भाग);

	bus = devm_mdiobus_alloc(&pdev->dev);
	अगर (!bus)
		वापस -ENOMEM;

	अगर (np) अणु
		of_address_to_resource(np, 0, &res);
		snम_लिखो(bus->id, MII_BUS_ID_SIZE, "%.8llx",
			 (अचिन्हित दीर्घ दीर्घ)res.start);
	पूर्ण अन्यथा अगर (pdata) अणु
		snम_लिखो(bus->id, MII_BUS_ID_SIZE, "%.8llx",
			 pdata->mdio_bus_id);
	पूर्ण

	bus->priv = lp;
	bus->name = "Xilinx TEMAC MDIO";
	bus->पढ़ो = temac_mdio_पढ़ो;
	bus->ग_लिखो = temac_mdio_ग_लिखो;
	bus->parent = lp->dev;

	lp->mii_bus = bus;

	rc = of_mdiobus_रेजिस्टर(bus, np);
	अगर (rc)
		वापस rc;

	dev_dbg(lp->dev, "MDIO bus registered;  MC:%x\n",
		temac_indirect_in32(lp, XTE_MC_OFFSET));
	वापस 0;
पूर्ण

व्योम temac_mdio_tearकरोwn(काष्ठा temac_local *lp)
अणु
	mdiobus_unरेजिस्टर(lp->mii_bus);
पूर्ण
